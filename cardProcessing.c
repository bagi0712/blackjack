#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int TrumpCard[N_CARD];


//card processing functions ---------------
						 

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	//You have already assigned the actual value of the card when you declared the array variable TrumpCard[], so keep that value
	return TrumpCard[cardnum]; //No function required, but function name is easily understood when used, so functioned 
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {              //Allocate patterns and numbers on a single deck of cards and print them out 
	
	//heart pattern
	if (cardnum == 0)
		printf("HRTAce");
	else if ((cardnum >= 1) && (cardnum <= 9)) //when the number of cards and the value of the cards are the same 
		printf("HRT%d", getCardNum(cardnum));
	else if (cardnum == 10)
		printf("HRTJack");
	else if (cardnum == 11)
		printf("HRTQueen");
	else if (cardnum == 12)
		printf("HRTKing");	
	
	//dia pattern
	else if (cardnum == 13)
		printf("DIAAce");
	else if ((cardnum >= 14) && (cardnum <= 22)) //when the number of cards and the value of the cards are the same
		printf("DIA%d", getCardNum(cardnum));
	else if (cardnum == 23)
		printf("DIAJack");
	else if (cardnum == 24)
		printf("DIAQueen");
	else if (cardnum == 25)
		printf("DIAKing");
	
	//spade pattern
	else if (cardnum == 26)
		printf("SPDAce");
	else if ((cardnum >= 27) && (cardnum <= 35)) //when the number of cards and the value of the cards are the same
		printf("SPD%d", getCardNum(cardnum));
	else if (cardnum == 36)
		printf("SPDJack");
	else if (cardnum == 37)
		printf("SPDQueen");
	else if (cardnum == 38)
		printf("SPDKing");
		
	//clover pattern 
	else if (cardnum == 39)
		printf("CLVAce");
	else if ((cardnum >= 40) && (cardnum <= 48)) //when the number of cards and the value of the cards are the same
		printf("CLV%d", getCardNum(cardnum));
	else if (cardnum == 49)
		printf("CLVJack");
	else if (cardnum == 50)
		printf("CLVQueen");
	else if (cardnum == 51)
		printf("CLVKing");
}
