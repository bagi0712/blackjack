#include <stdio.h>
#include <stdlib.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//52장의 모든 카드에 값 부여 
int TrumpCard[N_CARD] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
						 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
						 

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER]; 					//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag


//main function
int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
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
		printf("------------------------------------------------\n------------ ROUND %d (cardIndex:%d)--------------------------\n------------------------------------------------\n\n", roundIndex+1, cardIndex);
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
