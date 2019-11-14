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
		for (j=0;j<i;j++)	           //i���� ���� ��ȣ�� ī��Ʈ���̿� i��° ī��� �ߺ��Ǵ� ���� �ִ��� �˻� 
		{
			if (CardTray[i] == CardTray[j])
				i--;                   //�ߺ��� ������ i�� ī��Ʈ������ ī�带 �ٽ� ���� 
		}
	}
	return;
}

//get one card from the tray
int pullCard(void) {
	cardIndex++;                       //ī�带 ���� ������ ī���ε����� ���� 1�� ����  
	return CardTray[cardIndex-1];      //��ȯ ���� ī���ε����� ���� 1�� �������Ƿ� �ٽ� 1�� ���� ī��Ʈ���̿��� ī�带 ������ 
}
