#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


//52���� ��� ī�忡 ��꿡 ���Ǵ� ���� �� �ο� 
int TrumpCard[N_CARD] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
						 

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER]; 					//dollars that each player has- my number: 0, player N's number: N
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold- my number: 0, player N's number: N, server: n_user + 1
int cardSum[N_MAX_USER+1];					//sum of the cards- my number: 0, player N's number: N, server: n_user + 1
int bet[N_MAX_USER];						//current betting- my number: 0, player N's number: N
int gameEnd = 0; 							//game end flag


//main function
int main(int argc, char *argv[]) {
	int roundIndex = 1; //1������� ���� 
	int max_user;
	int i; 
	int j;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();
	
	
	//Game initialization --------
	//1. players' dollar
	for (i=0;i<n_user;i++)
		dollar[i] = N_DOLLAR; //��� �÷��̾ �ʱ� �ں� N_DOLLAR�� ������ ������ 
	
	//2. card tray
	mixCardTray(); //ī�带 ��� card tray�� ���� 
       



	//Game start --------
	do {
		//�÷��̾���� ��� ī�� ���� ���� -1�� �ʱ�ȭ (�� ī�� ���� ä���� ī�� ���� ������ ����)
		for (i=0;i<n_user+1;i++) 
		{
			for (j=0;j<N_MAX_CARDHOLD;j++)
			{
				cardhold[i][j] = -1;
			}
		}
	
		printf("------------------------------------------------\n");
		printf("------------ ROUND %d (cardIndex:%d)--------------------------\n", roundIndex, cardIndex);
		printf("------------------------------------------------\n\n");
		
		betDollar(); // betting step
		
		offerCards(); // give cards to all the players	
		if (gameEnd != 0)
		{
			break;
		}
		
		printCardInitialStatus(); //print initial card status
		printf("\n------------------ GAME start --------------------------\n");
		
		
		
		
		//my turn --------
		printf(">>> my turn! -------------\n");
		printUserCardStatus(0); //print current card status
		
		//check the card status
		if (calcStepResult(0) == 21) //ó�� �� ���� ī�� ���� 21�̸� ���� 
		{
			dollar[0] += bet[0]*2;
			printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[0]*2, dollar[0]);
		}
		else if (calcStepResult(0) < 21)		
		{
			getAction(0); //go? stay? �ݺ���ȯ 
			if (gameEnd != 0)
			{
				break;
			}
		
			if (calcStepResult(0) > 21) //ī�� ���� 21�� �ʰ��ϰ� �Ǹ� �й� 
			{
				dollar[0] -= bet[0];
				printf("DEAD (sum:%d) --> -$%d ($%d)\n", calcStepResult(0), bet[0], dollar[0]);				
			}
		}
		else
			printf("\n");
			
		
		
		
		//each computer player's turn --------
		for (i=1;i<n_user;i++) //each computer player 
		{
			printf("\n\n>>> player %d turn! -------------\n", i);
			printUserCardStatus(i); //print current card status
			
			//check the card status
			if (calcStepResult(i) == 21) //ó�� �� ���� ī�� ���� 21�̸� ����
			{
				dollar[i] += bet[i]*2;
				printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[i]*2, dollar[i]);
			}
			else if (calcStepResult(i) < 17)
			{
				getAction(i); //ī�� ���� 17 �̸��̸� go �ݺ�, 17 �̻� 21 �̸��̸� stay (21�Ͻ� �ٷ� ���� �ڵ�� �Ѿ) 
				if (gameEnd != 0)
				{
					break;
				} 
				
				if (calcStepResult(i) > 21) //go�� �Ͽ� ī�� ���� 21�� �ʰ��ϰ� �Ǹ� �й�
				{
					dollar[i] -= bet[i];
					printf("DEAD (sum:%d) --> -$%d ($%d)\n", calcStepResult(i), bet[i], dollar[i]);	
				}
			}
			else if ((calcStepResult(i) >= 17) && (calcStepResult(i) < 21))
			{
				printf("STAY!\n");
			}
		}
		
		
		
		
		//server's turn --------
		printf("\n\n>>> server turn! ------------------------\n");
		printUserCardStatus(n_user); //print current card status
		
		//check the card status
		if (calcStepResult(n_user) == 21) //ó�� �� ���� ī�� ���� 21�̸� ����
		{
			printf("Black Jack!T_T... server win\n");
			printf("[[[[[[[ server result is ....  Blackjack, T_T all remained players lose! ]]]]]]]\n");
		}
		else if (calcStepResult(n_user) < 17)
		{
			getAction(n_user); //ī�� ���� 17 �̸��̸� go �ݺ�, 17 �̻� 21 �̸��̸� stay (21�Ͻ� �ٷ� ���� �ڵ�� �Ѿ) 
			if (gameEnd != 0)
			{
				break;
			}
			
			if (calcStepResult(n_user) > 21) //go�� �Ͽ� server�� ī�� ���� 21�� �ʰ��ϴ� ��� ���� player���� ��� �¸� 
			{
				printf("server DEAD (sum:%d)\n", calcStepResult(n_user));
				printf("[[[[[[[ server result is .... ....overflow!! ]]]]]]]\n\n\n");
			}
			else 
			{
				printf("[[[[[[[ server result is ....  %d ]]]]]]]\n\n\n", calcStepResult(n_user));
			}
		}
		else if ((calcStepResult(n_user) >= 17) && (calcStepResult(n_user) < 21))
		{
			printf("STAY!\n");
			printf("[[[[[[[ server result is ....  %d ]]]]]]]\n\n\n", calcStepResult(n_user));
		}
		
		
		 
		
		//Round result --------
		printf(" -------------------- ROUND %d result ....\n", roundIndex);
		printf("   -> your result : ");
		checkResult(0); //my result
		for (i=1;i<n_user;i++)
		{
			printf("   -> %d'th player's result : ", i);
			checkResult(i); //computer player's result
		}
		printf("\n");
		
		checkDollar(); //round�� ���� ������ �Ļ� �˻� ���� 
		
		roundIndex++;
		
	} while (gameEnd == 0);
	
	
	
	
	//Game result --------
	if (gameEnd == 1) //game end flag(1): card tray�� ī�尡 ������
	{
		printf("card ran out of the tray!! finishing the game...\n\n\n\n");
	}
	else //game end flag(2): player �Ѹ��� �Ļ�
	{
		if (gameEnd == 2) //���� �Ļ��� ��� (gameEnd == (0 + 2))
		{ 
		printf("   -> you are bankrupted! game will be ended\n\n\n\n");
		}
		else //computer player�� �Ļ��� ��� (gameEnd == (i + 2))
		{
			for (i=1;i<n_user;i)
			{
				if (gameEnd == i+2)
				{
					printf("   -> player %d's bankrupted! game will be ended\n\n\n\n", i);
				}
			}
		}
	}
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n");
	printf("game end! your money :$ %d,", dollar[0]);
	if (n_user > 2)
	{
		printf(" players's money :");
		for (i=1;i<n_user;i++)
			printf("$%d ", dollar[i]);
	}
	
	if (checkWinner() == 0) //���� ���� ������ �� 
	{
		printf("\n\n\nyou win!!!!\n");
	}
	else //computer player�� ���� ������ ��
	{
		printf("\n\n\nplayer %d's win\n", checkWinner());
	}
	
	
	return 0;
}
