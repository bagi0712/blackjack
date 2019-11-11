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
	
	for (i=0;i<N_CARD;i++)     //난수 할당의 중복을 막기 위한 for문 중첩   
	{
		CardTray[i] = rand() % N_CARD;
		for (j=0;j<i;j++)	
		{
			if (CardTray[i] == CardTray[j])
				i--;
		}
	}
	return;
}

//get one card from the tray
int pullCard(void) {
	cardIndex++;
	return CardTray[cardIndex-1];
}
