#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define U 1
#define D 2
#define R 3
#define L 4

void drawCharRed();
void matrixRotateLeft(unsigned char *);
void flush() ;
void trans();

volatile unsigned int status;

int enemiesr[5], enemiesc[5], enemiess[5];

ISR(INT0_vect)
{
    if (status==1)
    {
        right();
    }
    else if (status==2)
    {
        left();
    }
    else if (status==3)
    {
        down();
    }
    else if (status==4)
    {
        up();
    }
    _delay_ms(200);
    GIFR |= 0b11111111;
}

ISR(INT1_vect)
{
    if (status==1)
    {
        left();
    }
    else if (status==2)
    {
        right();
    }
    else if (status==3)
    {
        up();
    }
    else if (status==4)
    {
        down();
    }
    _delay_ms(200);
    GIFR |= 0b11111111;
}

char in[4]={'w', 's', 'd', 'a'};
char s1[]="ssddwwaas";
char s2[]="ssaawwdds";
char s3[]="wwddssaaw";
char s4[]="wwaassddw";

unsigned char out1[8], out2[8];
int arr[16][8]={0, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 1, 1, 1, 1, 1, 1,
                1, 1, 0, 1, 1, 1, 1, 1,
                1, 1, 1, 0, 1, 1, 1, 1,
                1, 1, 0, 1, 1, 1, 1, 1,
                1, 0, 1, 1, 1, 1, 1, 1,
                0, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 1, 1, 1, 1, 1, 1,

				1, 1, 0, 1, 1, 1, 1, 1,
                1, 1, 1, 0, 1, 1, 1, 1,
                1, 1, 0, 1, 1, 1, 1, 1,
                1, 0, 1, 1, 1, 1, 1, 1,
                0, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 1, 1, 1, 1, 1, 1,
                1, 1, 0, 1, 1, 1, 1, 1,
                1, 1, 1, 0, 1, 1, 1, 1,};
unsigned char Gout1[8], Gout2[8];
int arg[16][8]={1, 1, 1, 1, 1, 1, 1, 0,
                1, 1, 1, 1, 1, 1, 0, 1,
                1, 1, 1, 1, 1, 0, 1, 1,
                1, 1, 1, 1, 0, 1, 1, 1,
                1, 1, 1, 1, 1, 0, 1, 1,
                1, 1, 1, 1, 1, 1, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 0,
                1, 1, 1, 1, 1, 1, 0, 1,

				1, 1, 1, 1, 1, 0, 1, 1,
                1, 1, 1, 1, 0, 1, 1, 1,
                1, 1, 1, 1, 1, 0, 1, 1,
                1, 1, 1, 1, 1, 1, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 0,
                1, 1, 1, 1, 1, 1, 0, 1,
                1, 1, 1, 1, 1, 0, 1, 1,
                1, 1, 1, 1, 0, 1, 1, 1,};


char game[16][8];

int r, c;


void init()
{
	int i, j, k;
    for (i=0; i<16; i++)
    {
        for (j=0; j<8; j++)
        {
            game[i][j]='.';
        }
    }
    game[11][2]=game[11][3]=game[11][4]='*';
    game[10][3]='*';
    status=1;
    r=10, c=3;
    game[0][0]=game[0][1]=game[0][2]=game[0][5]=game[0][6]=game[0][7]='*';
    game[15][0]=game[15][1]=game[15][2]=game[15][5]=game[15][6]=game[15][7]='*';
    game[1][1]=game[1][6]='*';
    game[14][1]=game[14][6]='*';

    enemiesr[1]=1, enemiesr[2]=1, enemiesr[3]=14, enemiesr[4]=14;
    enemiesc[1]=1, enemiesc[2]=6, enemiesc[3]=1, enemiesc[4]=6;
    enemiess[1]=2, enemiess[2]=2, enemiess[3]=1, enemiess[4]=1;
}

int check (int i, int j)
{
    if (i<=0 || i>=15 || j<=0 || j>=7) return 0;
    return 1;
}

void enemyup(int *r, int *c, int *status)
{
    if (*status==1)
    {
        game[*r+1][*c-1]=game[*r+1][*c]=game[*r+1][*c+1]='.';
        game[*r][*c-1]=game[*r][*c]=game[*r][*c+1]='*';
        game[*r-1][*c]='*';
        *r-=1;
    }
    if (*status==2)
    {
        game[*r][*c]='.';
        game[*r-2][*c]='*';
        *r-=2;
    }
    if (*status==3)
    {
        game[*r+1][*c-1]='.';
        game[*r][*c-2]='*';
        *r-=1;
        *c-=1;
    }
    if (*status==4)
    {
        game[*r+1][*c+1]='.';
        game[*r][*c+2]='*';
        *r-=1;
        *c+=1;
    }
    *status=1;
}

void up()
{
    if (r>4)
    {
        if (status==1)
        {
            game[r+1][c-1]=game[r+1][c]=game[r+1][c+1]='.';
            game[r][c-1]=game[r][c]=game[r][c+1]='*';
            game[r-1][c]='*';
            r--;
        }
        if (status==2)
        {
            game[r][c]='.';
            game[r-2][c]='*';
            r-=2;
        }
        if (status==3)
        {
            game[r+1][c-1]='.';
            game[r][c-2]='*';
            r--;
            c--;
        }
        if (status==4)
        {
            game[r+1][c+1]='.';
            game[r][c+2]='*';
            r--;
            c++;
        }
        status=1;
    }
}

void enemydown(int *r, int *c, int *status)
{
    if (*status==2)
    {
        game[*r-1][*c-1]=game[*r-1][*c]=game[*r-1][*c+1]='.';
        game[*r][*c-1]=game[*r][*c]=game[*r][*c+1]='*';
        game[*r+1][*c]='*';
        *r+=1;
    }
    if (*status==1)
    {
        game[*r][*c]='.';
        game[*r+2][*c]='*';
        *r+=2;
    }
    if (*status==3)
    {
        game[*r-1][*c-1]='.';
        game[*r][*c-2]='*';
        *r+=1;
        *c-=1;
    }
    if (*status==4)
    {
        game[*r-1][*c+1]='.';
        game[*r][*c+2]='*';
        *r+=1;
        *c+=1;
    }
    *status=2;
}

void down()
{
    if (r<11)
    {
        if (status==2)
        {
            game[r-1][c-1]=game[r-1][c]=game[r-1][c+1]='.';
            game[r][c-1]=game[r][c]=game[r][c+1]='*';
            game[r+1][c]='*';
            r++;
        }
        if (status==1)
        {
            game[r][c]='.';
            game[r+2][c]='*';
            r+=2;
        }
        if (status==3)
        {
            game[r-1][c-1]='.';
            game[r][c-2]='*';
            r++;
            c--;
        }
        if (status==4)
        {
            game[r-1][c+1]='.';
            game[r][c+2]='*';
            r++;
            c++;
        }
        status=2;
    }
}

void enemyright(int *r, int *c, int *status)
{
    if (*status==3)
    {
        game[*r-1][*c-1]=game[*r][*c-1]=game[*r+1][*c-1]='.';
        game[*r-1][*c]=game[*r][*c]=game[*r+1][*c]='*';
        game[*r][*c+1]='*';
        *c+=1;
    }
    if (*status==1)
    {
        game[*r+1][*c-1]='.';
        game[*r+2][*c]='*';
        *r+=1;
        *c+=1;
    }
    if (*status==2)
    {
        game[*r-1][*c-1]='.';
        game[*r-2][*c]='*';
        *r-=1;
        *c+=1;
    }
    if (*status==4)
    {
        game[*r][*c]='.';
        game[*r][*c+2]='*';
        *c+=2;
    }
    *status=3;
}

void right()
{
    if (c!=7)
    {
        if (status==3)
        {
            game[r-1][c-1]=game[r][c-1]=game[r+1][c-1]='.';
            game[r-1][c]=game[r][c]=game[r+1][c]='*';
            game[r][c+1]='*';
            c++;
        }
        if (status==1)
        {
            game[r+1][c-1]='.';
            game[r+2][c]='*';
            r++;
            c++;
        }
        if (status==2)
        {
            game[r-1][c-1]='.';
            game[r-2][c]='*';
            r--;
            c++;
        }
        if (status==4)
        {
            game[r][c]='.';
            game[r][c+2]='*';
            c+=2;
        }
        status=3;
    }
}

void enemyleft(int *r, int *c, int *status)
{
    if (*status==4)
    {
        game[*r-1][*c+1]=game[*r][*c+1]=game[*r+1][*c+1]='.';
        game[*r-1][*c]=game[*r][*c]=game[*r+1][*c]='*';
        game[*r][*c-1]='*';
        *c-=1;
    }
    if (*status==1)
    {
        game[*r+1][*c+1]='.';
        game[*r+2][*c]='*';
        *r+=1;
        *c-=1;
    }
    if (*status==2)
    {
        game[*r-1][*c+1]='.';
        game[*r-2][*c]='*';
        *r-=1;
        *c-=1;
    }
    if (*status==3)
    {
        game[*r][*c]='.';
        game[*r][*c-2]='*';
        *c-=2;
    }
    *status=4;
}

void left()
{
    if (c!=0)
    {
        if (status==4)
        {
            game[r-1][c+1]=game[r][c+1]=game[r+1][c+1]='.';
            game[r-1][c]=game[r][c]=game[r+1][c]='*';
            game[r][c-1]='*';
            c--;
        }
        if (status==1)
        {
            game[r+1][c+1]='.';
            game[r+2][c]='*';
            r++;
            c--;
        }
        if (status==2)
        {
            game[r-1][c+1]='.';
            game[r-2][c]='*';
            r--;
            c--;
        }
        if (status==3)
        {
            game[r][c]='.';
            game[r][c-2]='*';
            c-=2;
        }
        status=4;
    }
}

void make()
{
	int i, j;
	for (i=0; i<16; i++)
	{
		for (j=0; j<8; j++)
		{
			if (game[i][j]=='.')
			{
				arr[i][j]=1;
			}
			else
				arr[i][j]=0;
		}
	}
}



int main(void)
{
	//srand(time(null));
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD = 0xf0;
//	MCUCSR = (1<<JTD);
	init();
	char ch;
	int count=0;
    int countenemy=0;
    int pos=0, pos1=0, pos2=0, pos3=0, pos4=0;

	GICR = (1<<INT1 | 1<<INT0);
	MCUCR = MCUCR | 0b00001010;
	MCUCR = MCUCR & 0b11111010;
	sei();
	while(1)
	{
		//int temp = rand()%4;
//        ch = in[temp];
        // if (pos%5==0)
        // {
        //     for (i=0; i<200000000; i++){};
        //     shoot(status);
        // }
        count++;
        countenemy++;
        make();
        trans();
        drawCharRed();
        int i;
        char ch;
        if(count>10)
        {
	        if (status==1)
	        {
	            up();
	        }
	        if (status==2)
	        {
	            down();
	        }
	        if (status==3)
	        {
	            right();
	        }
	        if (status==4)
	        {
	            left();
	        }
	        count = 0;
        }
        if (countenemy>20)
        {
            ch=s1[pos1%9];
            if (ch=='w')
            {
                enemyup(&enemiesr[1], &enemiesc[1], &enemiess[1]);
            }
            if (ch=='s')
            {
                enemydown(&enemiesr[1], &enemiesc[1], &enemiess[1]);
            }
            if (ch=='d')
            {
                enemyright(&enemiesr[1], &enemiesc[1], &enemiess[1]);
            }
            if (ch=='a')
            {
                enemyleft(&enemiesr[1], &enemiesc[1], &enemiess[1]);
            }

            ch=s2[pos2%9];
            if (ch=='w')
            {
                enemyup(&enemiesr[2], &enemiesc[2], &enemiess[2]);
            }
            if (ch=='s')
            {
                enemydown(&enemiesr[2], &enemiesc[2], &enemiess[2]);
            }
            if (ch=='d')
            {
                enemyright(&enemiesr[2], &enemiesc[2], &enemiess[2]);
            }
            if (ch=='a')
            {
                enemyleft(&enemiesr[2], &enemiesc[2], &enemiess[2]);
            }

            ch=s3[pos3%9];
            if (ch=='w')
            {
                enemyup(&enemiesr[3], &enemiesc[3], &enemiess[3]);
            }
            if (ch=='s')
            {
                enemydown(&enemiesr[3], &enemiesc[3], &enemiess[3]);
            }
            if (ch=='d')
            {
                enemyright(&enemiesr[3], &enemiesc[3], &enemiess[3]);
            }
            if (ch=='a')
            {
                enemyleft(&enemiesr[3], &enemiesc[3], &enemiess[3]);
            }

            ch=s4[pos4%9];
            if (ch=='w')
            {
                enemyup(&enemiesr[4], &enemiesc[4], &enemiess[4]);
            }
            if (ch=='s')
            {
                enemydown(&enemiesr[4], &enemiesc[4], &enemiess[4]);
            }
            if (ch=='d')
            {
                enemyright(&enemiesr[4], &enemiesc[4], &enemiess[4]);
            }
            if (ch=='a')
            {
                enemyleft(&enemiesr[4], &enemiesc[4], &enemiess[4]);
            }
            pos1++;
            pos1%=9;
            if (pos1==0) pos1++;

            pos2++;
            pos2%=9;
            if (pos2==0) pos2++;

            pos3++;
            pos3%=9;
            if (pos3==0) pos3++;

            pos4++;
            pos4%=9;
            if (pos4==0) pos4++;
            countenemy=0;
        }
		// trans();
		// drawCharRed();
		//flush();
		//matrixRotateLeft(M);
		//_delay_ms(50);
		
	}
}

void flush(){
	DDRB = 0xff;
	_delay_ms(400) ;	
}



void drawCharRed()
{
	unsigned char i,j,k=0b10000000;
	PORTB = 0x00;
	// for (j = 0; j < 8; ++j)
	// {
	// 	PORTD = j;
	// 	PORTA = 0b10101010;
	// 	PORTB = 0b10101010;
	// 	_delay_ms(3);
	// }
	for (j = 8; j < 16; ++j)
	{
		PORTC = 0x00;
		PORTD = j<<4;
		PORTB = out1[j-8];
		PORTA = out2[j-8];
		_delay_ms(1);
        PORTB = 0x00;
        PORTA = 0x00;
		PORTC = 0x01;
	}
	// for (j = 8; j < 16; ++j)
	// {
	// 	PORTC = 0x00;
	// 	PORTD = j<<4;
	// 	PORTB = out1[j-8];
	// 	PORTA = out2[j-8];
	// 	_delay_ms(1);
 //        PORTB = 0x00;
 //        PORTA = 0x00;
	// 	PORTC = 0x01;
	// }
}


void matrixRotateLeft(unsigned char *character)
{
	int i;
	for (i=0; i<=7; i++)
	{
		unsigned char MSB = character[i] & 0b10000000;
		MSB = MSB >> 7;
		character[i] = character[i] << 1;
		character[i] = character[i] | MSB;
	}
}

void trans()
{
	int now, i, j;
    for (i=0; i<8; i++)
    {
        now=0;
        for (j=7; j>=0; j--)
        {
            if (arr[j][i]==1)
            {
                now*=2;
            }
            else
            {
                now*=2;
                now++;
            }
        }
        out1[i]=now;
    }
    for (i=0; i<8; i++)
    {
        now=0;
        for (j=15; j>=8; j--)
        {
            if (arr[j][i]==1)
            {
                now*=2;
            }
            else
            {
                now*=2;
                now++;
            }
        }
        out2[i]=now;
    }
    //Now for green
    for (i=0; i<8; i++)
    {
        now=0;
        for (j=0; j<8; j++)
        {
            if (arg[j][i]==0)
            {
                now*=2;
            }
            else
            {
                now*=2;
                now++;
            }
        }
        Gout1[i]=now;
    }
    for (i=0; i<8; i++)
    {
        now=0;
        for (j=8; j<16; j++)
        {
            if (arg[j][i]==0)
            {
                now*=2;
            }
            else
            {
                now*=2;
                now++;
            }
        }
        Gout2[i]=now;
    }
}