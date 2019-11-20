#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int cardIndex;
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
	while (!(n_user>=1) || !(n_user<=N_MAX_USER)); //잘못된 수나 문자를 입력할 시 다시 입력받는 것을 반복 
	printf(" --> card is mixed and put into the tray\n\n");
}


//betting
int betDollar(void) {
	int i;
	
	printf(" ------- BETTING STEP -------\n");
	
	//나의 배팅 금액을 입력받음 
	do
	{
		printf("   -> your betting (total:$%d) : ", dollar[0]); 
		bet[0] = getIntegerInput();                                 
		if (bet[0]>dollar[0]) //내가 보유한 자본 한도에서 배팅 금액을 입력 받음 
		{
			printf("   -> you only have $%d! bet again\n", dollar[0]);
		}
		else if (bet[0]<1)
		{
			printf("   -> invalid input for betting $%d\n", bet[0]);
		}
	}
	while (!(bet[0]>=1) || !(bet[0]<=dollar[0])); //잘못된 값을 배팅할 시 다시 입력받는 것을 반복 
	
	//computer players의 배팅 금액을 할당함 
	for(i=1;i<n_user;i++)
	{
		bet[i]=1+rand() % N_MAX_BET; //최소 1에서 최대 N_MAX_BET 중 임의 지정 
		printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);	
	}
	
	printf("----------------------------\n\n");	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	int j;
	
	for (i=0;i<2;i++) //server, me, players 순으로 한장씩 카드를 주는 것을 두 번 반복함 
	{
		//give one card for the server
		cardhold[n_user][i] = pullCard(); 
		
		checkCardIndex(); //카드를 꺼낼 때마다 카드 소진 검사 실행
		if (gameEnd != 0)
		{
			break;
		}               
	
		//give one card for each players including me
		for (j=0;j<n_user;j++)
		{
			cardhold[j][i] = pullCard();
			
			checkCardIndex(); //카드를 꺼낼 때마다 카드 소진 검사 실행
			if (gameEnd != 0)
			{
				break;
			}
		}
	}
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i;
	
	printf(" ----------- CARD OFFERING ---------------\n");

	//server's card status
	printf(" --- server      : X "); //server의 첫번째 카드 자리에는 X를 출력함 
	printCard(cardhold[n_user][1]); //server의 두번째 카드는 보여줌
	
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

//갖고 있는 카드의 장수
int cardcnt(int user) {
	int cardcnt = 0;
	int i;
	
	for (i=0;cardhold[user][i] != -1;i++)       //비어있는 카드 덱에서 덧셈을 멈춤
		cardcnt++;
	
	return cardcnt;
}


int getAction(int user) {
	int action;     //go 또는 stay를 입력받는 변수 
	
	//my turn
	if (user == 0) 
	{
		do {
			printf("Action? (0 - go, others - stay) :");
			action = getIntegerInput();
			
			if (action == 0)
				{
				cardhold[0][cardcnt(0)] = pullCard(); //비어 있는 cardhold 변수(=(cardcnt(0)+1)번째 cardhold 변수)에 새 카드를 받음 
			
				checkCardIndex(); //카드를 꺼낼 때마다 카드 소진 검사 실행
				if (gameEnd != 0)
				{
					break;
				}
			
				printUserCardStatus(0); //새로 받은 카드를 포함한 현재 카드 상태 출력 
			}
			else
				break;
		} while (calcStepResult(0) < 21);
	}
	
	//players & server's turn
	else 
	{
		do {
			printf("GO!\n");
			cardhold[user][cardcnt(user)] = pullCard(); //비어 있는 cardhold 변수(=(cardcnt(user)+1)번째 cardhold 변수)에 새 카드를 받음
		
			checkCardIndex(); //카드를 꺼낼 때마다 카드 소진 검사 실행
			if (gameEnd != 0)
			{
				break;
			}
		
			printUserCardStatus(user); //새로 받은 카드를 포함한 현재 카드 상태 출력
		} while (calcStepResult(user) < 17); //카드 합이 17 미만일 경우 go를 선택하는 것을 반복 
					
		if ((calcStepResult(user) >= 17) && (calcStepResult(user) < 21))
		{
			printf("STAY!\n");
		}
	}
	return;
}


//print current card status
int printUserCardStatus(int user) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt(user);i++) //채워져 있는 cardhold 변수까지의 카드들을 출력 
	{
		printCard(cardhold[user][i]);
		printf(" ");
	}
	printf("\t ::: ");
}


// calculate the card sum
int calcStepResult(int user) {         
	int i;
	
	for (i=0;i<n_user+1;i++)
		cardSum[i] = 0;      // 처음 카드 합을 0으로 초기화
	
	for (i=0;i<cardcnt(user);i++)
	{
		cardSum[user] += getCardNum(cardhold[user][i]); //채워져 있는 cardhold 변수까지의 카드 값을 합함
	}
	
	if (cardSum[user] > 21) //card sum이 21이상이면 Ace카드의 값을 11에서 1로 변경 
	{
		for (i=0;i<cardcnt(user);i++)
		{
			if (getCardNum(cardhold[user][i]) == 11) //Ace카드가 있는지 검사 
			{
				cardSum[user] -= 10; //Ace카드의 값을 11에서 1로 변경 
			}
			if (cardSum[user] <= 21)
				break;
		}
	}
	
	return cardSum[user];
}

//win? lose?
int checkResult(int user) {
	if ((cardcnt(user) == 2) && (calcStepResult(user) == 21)) //두 장의 카드 합이 21이면 블랙잭 (dollar 계산은 메인함수에서 이미 처리)
	{
		printf("BlackJack! win ($%d)", dollar[user]); 
	}
	else if ((cardcnt(n_user) == 2) && (calcStepResult(n_user) == 21)) //user가 블랙잭이 아닌데 server가 블랙잭이면 바로 패배 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) > 21) //user의 카드 합이 21을 초과하면 바로 패배 (dollar 계산은 메인함수에서 이미 처리)
	{
		printf("lose due to overflow! ($%d)\n", dollar[user]);
	}
	else if (calcStepResult(n_user) > 21) //user의 카드 합이 21 이하인데 server의 카드 합이 21을 초과하면 user는 승리 
	{
		dollar[user] += bet[user];          
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]); 		
	}
	else if (calcStepResult(user) >= calcStepResult(n_user)) //server의 카드 합보다 user의 카드 합이 같거나 크면 승리 
	{
		dollar[user] += bet[user];
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) < calcStepResult(n_user)) //server의 카드 합보다 user의 카드 합이 작으면 패배 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
}

//카드 소진 검사 
int checkCardIndex() {
	if (cardIndex == N_CARD) //card tray에 카드가 소진됨
	{	
		gameEnd = 1; //game end flag(1)
	}
}

//파산 검사
int checkDollar() {
	int i;
	
	for (i=0;i<n_user;i++)
	{
		if (dollar[i] == 0) //player 한명이 파산
		{
			gameEnd = i+2; //game end flag(2): gameEnd 값이 0이면 게임이 끝나지 않고 1이면 game end flag(1)과 겹치므로 2를 더해줌 
		}
	}
}

 
int checkWinner() {
	int dollarMax = 0; //변수의 값을 0으로 초기화 
	int winner;
	int i;
	
	for(i=0;i<n_user;i++) //나를 포함한 player들의 dollar을 비교 
	{
		if (dollar[i] > dollarMax)
		{
			dollarMax = dollar[i];
			winner = i;
		}
	}	
	
	return winner; //승리한 플레이어 번호를 반환 
}
