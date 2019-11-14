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
	
	for (i=0;i<N_CARD;i++)             //난수 할당의 중복을 막기 위한 for문 중첩   
	{
		CardTray[i] = rand() % N_CARD;
		for (j=0;j<i;j++)	           //i보다 작은 번호의 카드트레이에 i번째 카드와 중복되는 것이 있는지 검사 
		{
			if (CardTray[i] == CardTray[j])
				i--;                   //중복이 있으면 i번 카드트레이의 카드를 다시 설정 
		}
	}
	return;
}

//get one card from the tray
int pullCard(void) {
	cardIndex++;                       //카드를 꺼낼 때마다 카드인덱스의 값에 1을 더함  
	return CardTray[cardIndex-1];      //반환 전에 카드인덱스에 먼저 1을 더했으므로 다시 1을 빼고 카드트레이에서 카드를 가져옴 
}
