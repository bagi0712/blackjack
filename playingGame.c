#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int dollar[N_MAX_USER];
extern int n_user;
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern int cardSum[N_MAX_USER+1];
extern int bet[N_MAX_USER];


//playing game functions -----------------------------


//player settiing
int configUser(void) {
	do
	{	
		printf("Input the number of players (MAX:%d): ", N_MAX_USER);
		n_user = getIntegerInput();
		if (n_user>N_MAX_USER)
		{
			printf("Too many players!\n");
		}
		else if (n_user<1)
		{
			printf("invalid input players (%d)\n", n_user);
		}
	}
	while (!(n_user>=1) || !(n_user<=N_MAX_USER));
	printf(" --> card is mixed and put into the tray\n\n");
}


//betting
int betDollar(void) {
	int i;
	
	printf(" ------- BETTING STEP -------\n");
	
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
	while (!(bet[0]>=1) || !(bet[0]<=dollar[0]));
	
	for(i=1;i<n_user;i++)
	{
		bet[i]=1+rand() % N_MAX_BET;
		printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);		
	}
	
	printf("----------------------------\n\n");	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	int j;
	
	for (i=0;i<2;i++)
	{
		//give one card for the server
		cardhold[n_user][i] = pullCard();
	
		//give one card for each players
		for (j=0;j<n_user;j++)
		{
			cardhold[j][i] = pullCard();
		}
	}
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i;
	
	printf(" ----------- CARD OFFERING ---------------\n");

	printf(" --- server      : X ");
	printCard(cardhold[n_user][1]);
	printf("\n   -> you        : ");
	printCard(cardhold[0][0]);
	printf(" ");
	printCard(cardhold[0][1]);
	
	for (i=1;i<n_user;i++)
	{
		printf("\n   -> player %d   : ", i);
		printCard(cardhold[i][0]);
		printf(" ");
		printCard(cardhold[i][1]);
	}
	
	printf("\n"); 
}

int getAction(int user) {
	int input;     //go 또는 stop을 입력받음
	
	if (user == 0)
	{
		do {
			printf("Action? (0 - go, others - stay) :");
			input = getIntegerInput();
			
			if (input == 0)
				{
				cardhold[0][cardcnt(0)] = pullCard();
				printUserCardStatus(0, cardcnt(0));
			}
			else
				break;
		} while (calcStepResult(0) < 21);
	}
	else
	{
		do {
			printf("GO!\n");
			cardhold[user][cardcnt(user)] = pullCard();
			printUserCardStatus(user, cardcnt(user));
		} while (calcStepResult(user) < 17);
					
		if ((calcStepResult(user) >= 17) && (calcStepResult(user) < 21))
		{
			printf("STAY!\n");
		}
	}
	return;
}


//print current card status
int printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
	{
		printCard(cardhold[user][i]);
		printf(" ");
	}
	printf("\t ::: ");
}


//갖고 있는 카드의 장수
int cardcnt(int user) {
	int cardcnt = 0;
	int i;
	
	for (i=0;cardhold[user][i] != -1;i++)       //비어있는 카드 덱에서 덧셈을 멈춤
		cardcnt++;
	
	return cardcnt;
}


// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user) {         //user: 플레이어 번호 - server: N+1, me: 0, player N: N)
	int i;
	
	for (i=0;i<n_user+1;i++)
		cardSum[i] = 0;      // 처음 카드 합을 0으로 초기화
	
	for (i=0;i<cardcnt(user);i++)
		cardSum[user] += getCardNum(cardhold[user][i]);
	
	return cardSum[user];
}

int checkResult(int user) {
	if (calcStepResult(user) > 21)
		printf("lose due to overflow! ($%d)\n", dollar[user]);
	else if (calcStepResult(n_user) > 21)            
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]); 		
	else if (calcStepResult(user) >= calcStepResult(n_user))
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	else if (calcStepResult(user) < calcStepResult(n_user)) 
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
}
int checkWinner() {
	
}
