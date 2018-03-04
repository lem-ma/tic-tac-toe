/*
Copying and distribution of this file, with or without modification, are permitted in any medium without royalty
provided the copyright notice and this notice are preserved.  This file is offered as-is, without any warranty.
*/

#include <stdio.h>
#include <stdlib.h>

void version()
{
	int MainVersion=2;
	int SubVersion=1;
	char Build='b';
	printf("Welcome to TIC-TAC-TOE version %d.%d%c\nAuthor: BAI (lem-ma on GitHub)\n",MainVersion,SubVersion,Build);
}

char change(int ori)
{
	switch(ori)
	{
		case 1:
			return 'O';
			break;
		case 0:
			return 'X';
			break;
		default:
			return ' ';
			break;
	}
}

void printboard(int* st,int rd)
{
	for(int i=1;i<10;i++)
	{
		printf("\n");
	}
	/*
	____________________________
	|1       |2       |3       |
	|        |        |        |
	
	----------------------------
	|4       |5       |6       |
	|        |        |        |
	
	----------------------------
	|7       |8       |9       |
	|        |        |        |
	____________________________
	*/
	if(rd!=-1)
	{
		printf("%c turn.\n",change(rd%2));
	}
	printf("____________________________\n");
	for(int i=0;i<3;i++)
	{
		printf("|%d       |%d       |%d       |\n",3*i+1,3*i+2,3*i+3);
		printf("|   %c    |   %c    |   %c    |\n\n",change(st[3*i]),change(st[3*i+1]),change(st[3*i+2]));
		if(i<2)
		{
			printf("----------------------------\n");
		}
	}
	printf("____________________________\n");
}

void getinput(int* st,int rd)
{
	printf("Please choose a place by enter a number from 1 to 9.\n");
	int uenter;
	char invalid=1;
	while(invalid)
	{
		scanf("%d",&uenter);
		if(uenter<=9&&uenter>=1)
		{
			if(st[uenter-1]==-1)
			{
				st[uenter-1]=rd%2;
				break;
			}
			else
			{
				printf("This place already have a stone! Please input again.\n");
			}
		}
		else
		{
			printf("Your input is invalid! Please enter a number from 1 to 9.\n");
		}
	}
}

int havewon(int* st)
{
	int winner=-1;
	int done=0;
	for(int i=0;i<9;i++)
	{
		if(st[i]!=-1)
		{
			switch(i%3)
			{
				case 0:
					for(int j=1;j<=4;j++)
					{
						if(j!=2)
						{
							if(st[i]==st[i+j]&&st[i]==st[i+2*j])
							{
								winner=st[i];
								done=1;
								break;
							}
						}
					}
					break;
				case 1:
					if(st[i]==st[i+3]&&st[i]==st[i+6])
					{
						winner=st[i];
						done=1;
					}
					break;
				default:
					for(int j=2;j<=3;j++)
					{
						if(st[i]==st[i+j]&&st[i]==st[i+2*j])
						{
							winner=st[i];
							done=1;
							break;
						}
					}
			}
			if(done)
			{
				break;
			}
		}
	}
	return winner;
}

char two()
{
	int* state;
	state=malloc(sizeof(int)*16);
	for(int i=0;i<16;i++)
	{
		state[i]=-1;
	}
	int round=1;
	int result=-1;
	while(round<10)
	{
		printboard(state,round);
		getinput(state,round);
		if(havewon(state)!=-1)
		{
			result=havewon(state);
			break;
		}
		round++;
	}
	printboard(state,-1);
	free(state);
	return change(result);
}

void aiinput(int* st,int ur)
{
	int* tempstate;
	tempstate=malloc(sizeof(int)*16);
	for(int i=0;i<16;i++)
	{
		tempstate[i]=st[i];
	}
	int machine=(!ur);
	int done=0;
	for(int i=0;i<9;i++)
	{
		if(tempstate[i]==-1)
		{
			tempstate[i]=machine;
			if(havewon(tempstate)!=-1)
			{
				st[i]=machine;
				done=1;
				break;
			}
			else
			{
				tempstate[i]=-1;
			}
		}
	}
	if(!done)
	{
		for(int i=0;i<9;i++)
		{
			if(tempstate[i]==-1)
			{
				tempstate[i]=(!machine);
				if(havewon(tempstate)!=-1)
				{
					st[i]=machine;
					done=1;
					break;
				}
				else
				{
					tempstate[i]=-1;
				}
			}
		}
	}
	if(!done)
	{
		int choice[]={4,0,2,6,8,1,4,5,7};
		int j;
		for(int i=0;i<9;i++)
		{
			j=choice[i];
			if(st[j]==-1)
			{
				st[j]=machine;
				break;
			}
		}
	}
	free(tempstate);
}

char ai()
{
	int* state;
	state=malloc(sizeof(int)*16);
	for(int i=0;i<16;i++)
	{
		state[i]=-1;
	}
	printf("Do you want to be \"O\" (go first)? If so, enter \"1\", enter any other key otherwise.");
	int tt;
	scanf("%d",&tt);
	if(tt!=1)
	{
		tt=0;
	}
	int round=1;
	int result=-1;
	while(round<10)
	{
		if(tt==round%2)
		{
			printboard(state,round);
			getinput(state,round);
		}
		else
		{
			aiinput(state,tt);
		}
		if(havewon(state)!=-1)
		{
			result=havewon(state);
			break;
		}
		round++;
	}
	printboard(state,-1);
	free(state);
	return change(result);
}

void game()
{
	char mode;
	char win;
	printf("Enter \"m\" for gaming with the machine, enter any other key otherwise.\n");
	scanf("%c",&mode);
	switch(mode)//for further extensions
	{
		case 'm':
			win=ai();
			break;
		default:
			win=two();
			break;
	}
	if(win==' ')
	{
		printf("Tie.\n");
	}
	else
	{
		printf("%c wins.\n",win);
	}
}

int main(void)
{
	version();
	char resp=0;
	while(resp!='n')
	{
		game();
		printf("Enter \"n\" to exist, enter any other key to start a new game.\n");
		getchar();
		scanf("%c",&resp);
	}
	printf("Thanks for gaming. Enter any key to continue.\n");
	getchar();
	getchar();
	return 0;
}
