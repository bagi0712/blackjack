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
	
	for (i=0;i<N_CARD;i++)             //for-statement overlay to prevent duplication of random number allocation   
	{
		CardTray[i] = rand() % N_CARD;
		for (j=0;j<i;j++)	           //Check if a card tray with a number smaller than 'i' duplicates the 'i'th card tray 
		{
			if (CardTray[i] == CardTray[j])
				i--;                   //Re-set the card on 'i'th card tray if there is overlap 
		}
	}
	return;
}

//get one card from the tray
int pullCard(void) {
	if (cardIndex >= N_CARD)           //If you have used up your card, do not take it out anymore 
	{
		return -1;                     //The empty column of the cardhold variable has -1 as a value so returns -1 
	}  
	
	cardIndex++;                       //Add 1 to the value of the card index each time the card is ejected  
	return CardTray[cardIndex-1];      //1 was added to the card index first before returning, so remove 1 again and take the card from the card tray 
}
