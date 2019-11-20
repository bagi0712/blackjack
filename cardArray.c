#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int CardTray[N_CARDSET*N_CARD];
extern int cardIndex;


//card array controllers -------------------------------


//mix the card sets and put in the array
int mixCardTray(void) {
	int i;      
	int j;    
	
	for (i=0;i<N_CARD;i++)             //���� �Ҵ��� �ߺ��� ���� ���� for�� ��ø   
	{
		CardTray[i] = rand() % N_CARD;
		for (j=0;j<i;j++)	           //i���� ���� ��ȣ�� card tray�� i��° ī��� �ߺ��Ǵ� ���� �ִ��� �˻� 
		{
			if (CardTray[i] == CardTray[j])
				i--;                   //�ߺ��� ������ i�� card tray�� ī�带 �ٽ� ���� 
		}
	}
	return;
}

//get one card from the tray
int pullCard(void) {
	if (cardIndex >= N_CARD)           //ī�带 �� �� ��� ���̻� ī�带 ������ ���� 
	{
		return -1;
	}  
	
	cardIndex++;                       //ī�带 ���� ������ card index�� ���� 1�� ����  
	return CardTray[cardIndex-1];      //��ȯ ���� card index�� ���� 1�� �������Ƿ� �ٽ� 1�� ���� card tray���� ī�带 ������ 
}
