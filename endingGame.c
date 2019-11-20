#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int cardIndex;
extern int dollar[N_MAX_USER];
extern int n_user;
extern int gameEnd;


//ending game functions -----------------------------


//ī�� ���� �˻� 
int checkCardIndex() {
	if (cardIndex >= N_CARD) //card tray�� ī�尡 ������
	{	
		gameEnd = 1; //game end flag(1)
	}
	
	return 0;
}

//�Ļ� �˻�
int checkDollar() {
	int i;
	
	for (i=0;i<n_user;i++)
	{
		if (dollar[i] <= 0) //player �Ѹ��� �Ļ�
		{
			gameEnd = i+2; //game end flag(2): gameEnd ���� 0�̸� ������ ������ �ʰ� 1�̸� game end flag(1)�� ��ġ�Ƿ� player number�� 2�� ������ 
		}
	}
	
	return 0;
}

//���� ���� üũ 
int checkWinner() {
	int dollarMax = 0; //���� �ڻ꿡�� ���� ū �� 
	int winner;
	int i;
	
	for(i=0;i<n_user;i++) //���� ������ player���� �ڻ��� �� 
	{
		if (dollar[i] > dollarMax)
		{
			dollarMax = dollar[i];
			winner = i;
		}
	}	
	
	return winner; //���� �¸��� player�� number�� ��ȯ 
}
