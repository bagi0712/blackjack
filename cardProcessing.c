#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int TrumpCard[N_CARD];


//card processing functions ---------------
						 

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int actualNum;                         //카드가 갖는 실제 값 
	
	actualNum = TrumpCard[cardnum];        //이미 배열 변수 TrumpCard[]를 선언할 때 카드가 갖는 실제 값을 할당했으므로 그 값을 그대로 가져옴  
	return actualNum;
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {              //카드 한장한장에 문양과 숫자를 할당 
	
	//heart pattern
	if (cardnum == 0)
		printf("HRTA");
	else if ((cardnum >= 1) && (cardnum <= 9))  
		printf("HRT%d", TrumpCard[cardnum]);
	else if (cardnum == 10)
		printf("HRTJack");
	else if (cardnum == 11)
		printf("HRTQueen");
	else if (cardnum == 12)
		printf("HRTKing");	
	
	//dia pattern
	else if (cardnum == 13)
		printf("DIAA");
	else if ((cardnum >= 14) && (cardnum <= 22))
		printf("DIA%d", TrumpCard[cardnum]);
	else if (cardnum == 23)
		printf("DIAJack");
	else if (cardnum == 24)
		printf("DIAQueen");
	else if (cardnum == 25)
		printf("DIAKing");
	
	//spade pattern
	else if (cardnum == 26)
		printf("SPDA");
	else if ((cardnum >= 27) && (cardnum <= 35))
		printf("SPD%d", TrumpCard[cardnum]);
	else if (cardnum == 36)
		printf("SPDJack");
	else if (cardnum == 37)
		printf("SPDQueen");
	else if (cardnum == 38)
		printf("SPDKing");
		
	//clover pattern 
	else if (cardnum == 39)
		printf("CLVA");
	else if ((cardnum >= 40) && (cardnum <= 48))
		printf("CLV%d", TrumpCard[cardnum]);
	else if (cardnum == 49)
		printf("CLVJack");
	else if (cardnum == 50)
		printf("CLVQueen");
	else if (cardnum == 51)
		printf("CLVKing");
}
