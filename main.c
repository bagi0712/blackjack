#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


//All cards are given the actual value used for calculation 
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
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold- my number: 0, player N's number: N, server's number: n_user
int cardSum[N_MAX_USER+1];					//sum of the cards- my number: 0, player N's number: N, server's number: n_user
int bet[N_MAX_USER];						//current betting- my number: 0, player N's number: N
int gameEnd = 0; 							//game end flag


//main function
int main(int argc, char *argv[]) {
	int roundIndex = 1; //Start with the first round 
	int i; 
	int j;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();
	
	
	//Game initialization --------
	//1. players' dollar
	for (i=0;i<n_user;i++)
		dollar[i] = N_DOLLAR; //All players start with initial asset N_DOLLAR 
	
	//2. card tray
	mixCardTray(); //Mix the cards and put them in the card tray 
       



	//Game start --------
	do {
		//Initialize the value of all cardhold variables to -1 (to differentiate between empty and filled cardhold variables)
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
		
		betDollar(); //betting step
		
		offerCards(); //give cards to all the players	
		if (gameEnd != 0) //game end flag --> Loop Out
		{
			break;
		}
		
		printCardInitialStatus(); //print initial card status
		printf("\n------------------ GAME start --------------------------\n");
		
		
		
		
		//my turn --------
		printf(">>> my turn! -------------\n");
		printUserCardStatus(0); //print current card status
		
		//check the card status
		if (calcStepResult(0) == 21) //If the first two cards add up to 21, blackjack- a direct victory 
		{
			dollar[0] += bet[0]*2;
			printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[0]*2, dollar[0]);
		}
		else if (calcStepResult(0) < 21)		
		{
			getAction(0); //go? stay? repeated cycle 
			if (gameEnd != 0) //game end flag --> Loop Out
			{
				break;
			}
		
			if (calcStepResult(0) > 21) //If the sum of the cards exceeds 21, a direct defeat 
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
			if (calcStepResult(i) == 21) //If the first two cards add up to 21, blackjack- a direct victory 
			{
				dollar[i] += bet[i]*2;
				printf("Black Jack!congratulation, you win!! --> +$%d ($%d)\n", bet[i]*2, dollar[i]);
			}
			else if (calcStepResult(i) < 17)
			{
				getAction(i); //If the card sum is less than 17 then repeat 'go', 'stay' if the card is more than 17 and less than 21
				if (gameEnd != 0) //game end flag --> Loop Out (for-loop) 
				{
					break;
				} 
				
				if (calcStepResult(i) > 21) //If the player 'go' and the sum of the cards exceeds 21, a direct defeat
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
		if (gameEnd != 0) //game end flag --> Loop Out (do-while loop) 
		{
			break;
		} 
		
		
		
		
		//server's turn --------
		printf("\n\n>>> server turn! ------------------------\n");
		printUserCardStatus(n_user); //print current card status
		
		//check the card status
		if (calcStepResult(n_user) == 21) //If the first two cards add up to 21, blackjack
		{
			printf("Black Jack!T_T... server win\n");
			printf("[[[[[[[ server result is ....  Blackjack, T_T all remained players lose! ]]]]]]]\n");
		}
		else if (calcStepResult(n_user) < 17)
		{
			getAction(n_user); //If the card sum is less than 17 then repeat 'go', 'stay' if the card is more than 17 and less than 21 
			if (gameEnd != 0) //game end flag --> Loop Out
			{
				break;
			}
			
			if (calcStepResult(n_user) > 21) //If the server 'go' and the sum of the cards exceeds 21, all the remaining players will win 
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
		
		//my result
		printf("   -> your result : ");
		checkResult(0);
		
		//computer player's result
		for (i=1;i<n_user;i++) 
		{
			printf("   -> %d'th player's result : ", i);
			checkResult(i); 
		}
		printf("\n");
		
		checkDollar(); //Run bankruptcy check at the end of each round 
		if (gameEnd != 0) //game end flag --> Loop Out
		{
			break;
		}
		
		roundIndex++;
		
	} while (gameEnd == 0);
	
	
	
	
	//Game result --------
	//game end flag(1): card exhaustion
	if (gameEnd == 1) 
	{
		printf("card ran out of the tray!! finishing the game...\n\n\n\n");
	}
	
	//game end flag(2): one player bankrupted
	else if (gameEnd == 2) //in case of my bankruptcy (gameEnd == (0 + 2))
	{ 
	printf("   -> you are bankrupted! game will be ended\n\n\n\n");
	}
	else //in case of computer player's bankruptcy (gameEnd == (N + 2))
	{
		printf("   -> player %d's bankrupted! game will be ended\n\n\n\n", gameEnd - 2);
	}
	
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n\n");
	printf(" -------------------------------------------\n");
	
	printf("game end! your money :$ %d, players's money :", dollar[0]);
	if (n_user > 1)
	{
		for (i=1;i<n_user;i++)
			printf("$%d ", dollar[i]);
	}
	
	if (checkWinner() == 0) //when I'm the final winner 
	{
		printf("\n\n\nyou win!!!!\n");
	}
	else //when computer player's the final winner
	{
		printf("\n\n\nplayer %d's win\n", checkWinner());
	}
	
	
	return 0;
}
