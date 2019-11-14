#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


//52장의 모든 카드에 계산에 사용되는 실제 값 부여 
int TrumpCard[N_CARD] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
						 

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
	int roundIndex = 1; //1라운드부터 시작 
	int max_user;
	int i; 
	int j;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();
	
	
	//Game initialization --------
	//1. players' dollar
	for (i=0;i<n_user;i++)
		dollar[i] = N_DOLLAR;
	
	//2. card tray
	mixCardTray();
       



	//Game start --------
	do {
		//플레이어들의 모든 카드 덱의 값을 -1로 초기화 (빈 카드 덱과 채워진 카드 덱의 구분을 위해)
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
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		
		//my turn
		printf(">>> my turn! -------------\n");
		printUserCardStatus(0, cardcnt(0)); //print current card status
		
		//check the card status
		if (calcStepResult(0) == 21) //처음 두 장의 카드 합이 21이면 블랙잭 
		{
			dollar[0] += bet[0]*2;
			printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[0]*2, dollar[0]);
		}
		else if (calcStepResult(0) < 21)		
		{
			getAction(0);
		
			if (calcStepResult(0) > 21)
			{
				dollar[0] -= bet[0];
				printf("DEAD (sum:%d) --> -$%d ($%d)\n", calcStepResult(0), bet[0], dollar[0]);				
			}
		}
		else
			printf("\n");
			
		
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{
			printf("\n\n>>> player %d turn! -------------\n", i);
			printUserCardStatus(i, cardcnt(i)); //print current card status
			
			//check the card status
			if (calcStepResult(i) == 21) //처음 두 장의 카드 합이 21이면 블랙잭
			{
				dollar[i] += bet[i]*2;
				printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[i]*2, dollar[i]);
			}
			else if (calcStepResult(i) < 17) 
			{
				getAction(i);
				
				if (calcStepResult(i) > 21)
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
		
		
		//server's turn 
		printf("\n\n>>> server turn! ------------------------\n");
		printUserCardStatus(n_user, cardcnt(n_user)); //print current card status
		
		//check the card status
		if (calcStepResult(n_user) == 21) //처음 두 장의 카드 합이 21이면 블랙잭
		{
			printf("Black Jack!T_T... server win\n");
			printf("[[[[[[[ server result is ....  Blackjack, T_T all remained players lose! ]]]]]]]\n");
		}
		else if (calcStepResult(n_user) < 17)
		{
			do {
				getAction(n_user);
			} while (calcStepResult(n_user) < 17);
			
			if (calcStepResult(n_user) > 21)
			{
				printf("server DEAD (sum:%d)\n", calcStepResult(n_user));
				printf("[[[[[[[ server result is .... ....overflow!! ]]]]]]]\n\n\n");
			}
			else if ((calcStepResult(n_user) >= 17) && (calcStepResult(n_user) <= 21))
			{
				printf("STAY!\n");
				printf("[[[[[[[ server result is ....  %d ]]]]]]]\n\n\n", calcStepResult(n_user));
			}
		}
		else if ((calcStepResult(n_user) >= 17) && (calcStepResult(n_user) < 21))
		{
			printf("STAY!\n");
			printf("[[[[[[[ server result is ....  %d ]]]]]]]\n\n\n", calcStepResult(n_user));
		}
		
		//result
		printf(" -------------------- ROUND %d result ....\n", roundIndex);
		printf("   -> your result : ");
		checkResult(0);
		for (i=1;i<n_user;i++)
		{
			printf("   -> %d'th player's result : ", i);
			checkResult(i);
		}
		printf("\n");
		
		roundIndex++;
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
