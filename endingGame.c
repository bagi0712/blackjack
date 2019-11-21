#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int cardIndex;
extern int dollar[N_MAX_USER];
extern int n_user;
extern int gameEnd;


//ending game functions -----------------------------


//card exhaustion check 
int checkCardIndex() {
	if (cardIndex >= N_CARD)
	{	
		gameEnd = 1; //game end flag(1)
	}
	
	return 0;
}

//bankruptcy check
int checkDollar() {
	int i;
	
	for (i=0;i<n_user;i++)
	{
		if (dollar[i] <= 0) 
		{
			gameEnd = i+2; //game end flag(2): If the gameEnd value is 0 then the game is not over and 1 overlaps the game end flag (1) so adds 2 to the player number 
		}
	}
	
	return 0;
}

//final winner check 
int checkWinner() {
	int dollarMax = 0; //the largest value of the final asset 
	int winner;
	int i;
	
	for(i=0;i<n_user;i++) //Compare the assets of players including me 
	{
		if (dollar[i] >= dollarMax)
		{
			dollarMax = dollar[i];
			winner = i;
		}
	}	
	
	return winner; //Return the number of the final winning player 
}
