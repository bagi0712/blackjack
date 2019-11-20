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
		n_user = getIntegerInput(); //player ���� �Է¹��� 
		if (n_user>N_MAX_USER) 
		{
			printf("Too many players!\n");
		}
		else if (n_user<1)
		{
			printf("invalid input players (%d)\n", n_user);
		}
	}
	while (!(n_user>=1) || !(n_user<=N_MAX_USER)); //�ִ� player ���� �ʰ��ϰų� �߸��� ���� �Է��� �� �ٽ� �Է¹޴� ���� �ݺ� 
	printf(" --> card is mixed and put into the tray\n\n");
	
	return 0;
}


//betting
int betDollar(void) {
	int i;
	
	printf(" ------- BETTING STEP -------\n");
	
	//���� ���� �ݾ�(bet[0])�� �Է¹���
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
	while (!(bet[0]>=1) || !(bet[0]<=dollar[0])); //������ �ں� �ѵ��� �ʰ��ϰų� �߸��� ���� ������ �� �ٽ� �Է¹޴� ���� �ݺ� 
	
	//computer players�� ���� �ݾ�(bet[N])�� �Ҵ��� 
	for(i=1;i<n_user;i++)
	{
		bet[i] = 1 + rand() % N_MAX_BET; //�ּ� 1���� �ִ� N_MAX_BET �� ���� ���� 
		printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);	
	}
	
	printf("----------------------------\n\n");	
	
	return 0;
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	int j;
	
	for (i=0;i<2;i++) //server, me, players ������ ���徿 ī�带 �ִ� ���� �� �� �ݺ��� 
	{
		//give one card for the server
		cardhold[n_user][i] = pullCard(); //(n_user + 1)��° ���� cardhold ���� = server�� cardhold ���� 
		
		checkCardIndex(); //ī�带 ���� ������ ī�� ���� �˻� ����
		if (gameEnd != 0) //game end flag --> ���� ���������� 
		{
			break;
		}               
	
		//give one card for each players including me
		for (j=0;j<n_user;j++)
		{
			cardhold[j][i] = pullCard(); //0��° ���� cardhold ���� = ���� cardhold ����, N��° ���� cardhold ���� = player N�� cardhold ���� 
			
			checkCardIndex(); //ī�带 ���� ������ ī�� ���� �˻� ����
			if (gameEnd != 0) //game end flag --> ���� ����������
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
	printf(" --- server      : X "); //server�� ù��° ī�� �ڸ����� X�� ����� 
	printCard(cardhold[n_user][1]); //server�� �ι�° ī��� ������
	
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

//���� �ִ� ī���� ���
int cardcnt(int user) {
	int cardcnt = 0; //ī�� ����� ���� �� cardcnt ���� 0���� �ʱ�ȭ 
	int i;
	
	for (i=0;cardhold[user][i] != -1;i++) //cardhold ������ ����ִ� ��(������ �� = -1)���� ������ ����
		cardcnt++;
	
	return cardcnt;
}


int getAction(int user) {
	int action;     //go �Ǵ� stay�� �Է¹޴� ���� 
	
	//my turn: go �Ǵ� stay�� ���� �Է¹��� 
	if (user == 0) 
	{
		do {
			printf("Action? (0 - go, others - stay) :");
			action = getIntegerInput();
			
			if (action == 0)
			{
				cardhold[0][cardcnt(0)] = pullCard(); //cardhold ������ ����ִ� ��( = (cardcnt(0) + 1)��° ��)�� �� ī�带 ���� 
			
				checkCardIndex(); //ī�带 ���� ������ ī�� ���� �˻� ����
				if (gameEnd != 0) //game end flag --> ���� ����������
				{
					break;
				}
			
				printUserCardStatus(0); //���� ���� ī�带 ������ ���� ī�� ���� ��� 
			}
			else
				break;
		} while (calcStepResult(0) < 21);
	}
	
	//players & server's turn: ī�� ���� 17 �̸��� ��� go�� �ݺ� 
	else 
	{
		do {
			printf("GO!\n"); //ī�� ���� 17 �̸��� �� �Լ��� ����ǹǷ� �ϴ� go  
			cardhold[user][cardcnt(user)] = pullCard(); //cardhold ������ ����ִ� ��( = (cardcnt(user) + 1)��° ��)�� �� ī�带 ����
		
			checkCardIndex(); //ī�带 ���� ������ ī�� ���� �˻� ����
			if (gameEnd != 0) //game end flag --> ���� ����������
			{
				break;
			}
		
			printUserCardStatus(user); //���� ���� ī�带 ������ ���� ī�� ���� ���
		} while (calcStepResult(user) < 17); //ī�� ���� 17 �̸��� ��� go�� �����ϴ� ���� �ݺ� 
					
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
	for (i=0;i<cardcnt(user);i++) //cardhold ������ ä���� ī����� ��� 
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
		cardSum[i] = 0;      // ó�� ī�� ���� 0���� �ʱ�ȭ
	
	for (i=0;i<cardcnt(user);i++)
	{
		cardSum[user] += getCardNum(cardhold[user][i]); //cardhold ������ ä���� �������� ī�� ���� ����
	}
	
	if (cardSum[user] > 21) //ī�� ���� 21�̻��̸� Aceī���� ���� ���� 
	{
		for (i=0;i<cardcnt(user);i++)
		{
			if (getCardNum(cardhold[user][i]) == 11) //Aceī�尡 �ִ��� �˻� 
			{
				cardSum[user] -= 10; //Aceī���� ���� 11���� 1�� ���� 
			}
			if (cardSum[user] <= 21) //ī�� ���� 21 ���ϰ� �Ǹ� Aceī�� �� ���� �ߴ� 
				break;
		}
	}
	
	return cardSum[user];
}

//win? lose? Round result 
int checkResult(int user) {
	if ((cardcnt(user) == 2) && (calcStepResult(user) == 21)) //�� ���� ī�� ���� 21�̸� ���� (dollar ����� �����Լ����� �̹� ó��)
	{
		printf("BlackJack! win ($%d)\n", dollar[user]); 
	}
	else if ((cardcnt(n_user) == 2) && (calcStepResult(n_user) == 21)) //user�� ������ �ƴѵ� server�� �����̸� �ٷ� �й� 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) > 21) //user�� ī�� ���� 21�� �ʰ��ϸ� �ٷ� �й� (dollar ����� �����Լ����� �̹� ó��)
	{
		printf("lose due to overflow! ($%d)\n", dollar[user]);
	}
	else if (calcStepResult(n_user) > 21) //user�� ī�� ���� 21 �����ε� server�� ī�� ���� 21�� �ʰ��ϸ� user�� �¸� 
	{
		dollar[user] += bet[user];          
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]); 		
	}
	else if (calcStepResult(user) >= calcStepResult(n_user)) //server�� ī�� �պ��� user�� ī�� ���� ���ų� ũ�� �¸� 
	{
		dollar[user] += bet[user];
		printf("win (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	else if (calcStepResult(user) < calcStepResult(n_user)) //server�� ī�� �պ��� user�� ī�� ���� ������ �й� 
	{
		dollar[user] -= bet[user];
		printf("lose! (sum:%d) --> $%d\n", calcStepResult(user), dollar[user]);
	}
	
	return 0; 
}
