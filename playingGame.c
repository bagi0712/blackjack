#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int dollar[N_MAX_USER];
extern int n_user;
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern int cardSum[N_MAX_USER+1];
extern int bet[N_MAX_USER];
extern int gameEnd;


//playing game functions -----------------------------


//player settiing
int configUser(void) {
	do
	{	
		printf("Input the number of players (MAX:%d): ", N_MAX_USER);
		n_user = getIntegerInput(); //Enter number of players 
		if (n_user>N_MAX_USER) 
		{
			printf("Too many players!\n");
		}
		else if (n_user<1)
		{
			printf("invalid input players (%d)\n", n_user);
		}
	}
	while (!(n_user>=1) || !(n_user<=N_MAX_USER)); //Repeat receiving re-entering if the maximum number of players is exceeded or an invalid value is entered 
	printf(" --> card is mixed and put into the tray\n\n");
	
	return 0;
}


//betting
int betDollar(void) {
	int i;
	
	printf(" ------- BETTING STEP -------\n");
	
	//Receive my betting amount (bet[0])
	do
	{
		printf("   -> your betting (total:$%d) : ", dollar[0]); 
		bet[0] = getIntegerInput();                              
		if (bet[0]>dollar[0])
		{
			printf("   -> you only have $%d! bet again\n", dollar[0]);
		}
		else if (bet[0]<1)
		{
			printf("   -> invalid input for betting $%d\n", bet[0]);
		}
	}
	while (!(bet[0]>=1) || !(bet[0]<=dollar[0])); //Repeat receiving re-entering if asset limits are exceeded or incorrect values are betted 
	
	//Allocated the betting amount (bet[N]) of the computer players 
	for(i=1;i<n_user;i++)
	{
		bet[i] = 1 + rand() % N_MAX_BET; //Randomly allocate the betting amount between maximum N_MAX_BET and minimum 1 
		printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);	
	}
	
	printf("----------------------------\n\n");	
	
	return 0;
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	int j;
	
	for (i=0;i<2;i++) //Repeat giving one card to server, me, and players twice. 
	{
		//give one card for the server
		cardhold[n_user][i] = pullCard(); //Cardhold variable in the (n_user + 1)th row =  server's cardhold variable 
		
		checkCardIndex(); //Run the card exhaustion check each time you eject the card
		if (gameEnd != 0) //game end flag --> Loop Out 
		{
			break;
		}               
	
		//give one card for each players including me
		for (j=0;j<n_user;j++)
		{
			cardhold[j][i] = pullCard(); //Cardhold variable in the first row =  my cardhold variable, Cardhold variable in the (N + 1)th row =  player N's cardhold variable 
			
			checkCardIndex(); //Run the card exhaustion check each time you eject the card
			if (gameEnd != 0) //game end flag --> Loop Out
			{
				break;
			}
		}
	}
}

//print initial card status
void printCardInitialStatus(void) {
	int i;
	
	printf(" ----------- CARD OFFERING ---------------\n");

	//server's card status
	printf(" --- server      : X "); //X is printed on the first card digit of the server 
	printCard(cardhold[n_user][1]); //Show the second card of the server
	
	//my card status
	printf("\n   -> you        : ");
	printCard(cardhold[0][0]);
	printf(" ");
	printCard(cardhold[0][1]);
	
	//each player's card status
	for (i=1;i<n_user;i++)
	{
		printf("\n   -> player %d   : ", i);
		printCard(cardhold[i][0]);
		printf(" ");
		printCard(cardhold[i][1]);
	}
	
	printf("\n"); 
}

//the number of cards in the cardhold
int cardcnt(int user) {
	int cardcnt = 0; //The cardcnt value is reset to zero before cards are counted 
	int i;
	
	for (i=0;cardhold[user][i] != -1;i++) //Stop adding at empty column of cardhold variable (value of empty variable is initialized to -1 by main function)
		cardcnt++;
	
	return cardcnt;
}


int getAction(int user) {
	int action;     //variable that receive 'go' or 'stay' 
	
	//my turn: 'go' or 'stay' entered directly 
	if (user == 0) 
	{
		do {
			printf("Action? (0 - go, others - stay) :");
			action = getIntegerInput();
			
			if (action == 0)
			{
				cardhold[0][cardcnt(0)] = pullCard(); //Get a new card in empty column of cardhold variable
			
				checkCardIndex(); //Run the card exhaustion check each time you eject the card
				if (gameEnd != 0) //game end flag --> Loop Out
				{
					break;
				}
			
				printUserCardStatus(0); //Print current card status, including newly received card 
			}
			else
				break;
		} while (calcStepResult(0) < 21);
	}
	
	//players & server's turn: Repeat 'go' if card sum is less than 17 
	else 
	{
		do {
			printf("GO!\n");  
			cardhold[user][cardcnt(user)] = pullCard(); //Get a new card in empty column of cardhold variable
		
			checkCardIndex(); //Run the card exhaustion check each time you eject the card
			if (gameEnd != 0) //game end flag --> Loop Out
			{
				break;
			}
		
			printUserCardStatus(user); //Print current card status, including newly received card 
		} while (calcStepResult(user) < 17); //Repeat 'go' if card sum is less than 17 
					
		if ((calcStepResult(user) >= 17) && (calcStepResult(user) < 21))
		{
			printf("STAY!\n");
		}
	}
	return 0;
}


//print current card status
int printUserCardStatus(int user) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt(user);i++) //Print cards filled in cardhold variable 
	{
		printCard(cardhold[user][i]);
		printf(" ");
	}
	printf("\t ::: ");
	
	return 0;
}


// calculate the card sum
int calcStepResult(int user) {         
	int i;
	
	for (i=0;i<n_user+1;i++)
		cardSum[i] = 0;      //Initialize first card sum to zero
	
	for (i=0;i<cardcnt(user);i++)
	{
		cardSum[user] += getCardNum(cardhold[user][i]); //Sum cards filled in cardhold variable
	}
	
	if (cardSum[user] > 21) //Change the value of the Ace card if the sum of the cards exceeds 21 
	{
		for (i=0;i<cardcnt(user);i++)
		{
			if (getCardNum(cardhold[user][i]) == 11) //Inspect for Ace Card 
			{
				cardSum[user] -= 10; //Change the value of the Ace card from 11 to 1 
			}
			if (cardSum[user] <= 21) //Stop changing the Ace card value if the sum of the cards is 21 or less than 21 
				break;
		}
	}
	
	return cardSum[user];
}

//win? lose? Round result 
int checkResult(int user) {
	if ((cardcnt(user) == 2) && (calcStepResult(user) == 21)) //Blackjack if two cards total 21 (dollar calculation already handled by main function)
	{
		printf("BlackJack! win ($%d)\n", dollar[user]); 
	}
	else if ((cardcnt(n_user) == 2) && (calcStepResult(n_user) == 21)) //If the player's not blackjack, but the server's blackjack, the player loses 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) > 21) //If the sum of the players' cards exceeds 21, the player loses immediately (dollar calculation already handled by main function)
	{
		printf("lose due to overflow! ($%d)\n", dollar[user]);
	}
	else if (calcStepResult(n_user) > 21) //If the sum of the players' cards is less than 21 and the sum of the server's exceeds 21, the player wins 
	{
		dollar[user] += bet[user];          
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]); 		
	}
	else if (calcStepResult(user) >= calcStepResult(n_user)) //If the sum of the player's cards is equal or greater than the sum of the server's, the player wins
	{
		dollar[user] += bet[user];
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) < calcStepResult(n_user)) //If the sum of the player's cards is smaller than the sum of the server's, the player loses 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	
	return 0; 
}
