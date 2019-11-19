#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int TrumpCard[N_CARD];


//card processing functions ---------------
						 

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	//이미 배열 변수 TrumpCard[]를 선언할 때 카드가 갖는 실제 값을 할당했으므로 그 값을 그대로 가져옴
	return TrumpCard[cardnum]; //굳이 함수로 만들 필요 없지만 함수 이름이 활용 시 이해가 쉬워 함수화했음 
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {              //카드 한장한장에 문양과 숫자를 할당 
	
	//heart pattern
	if (cardnum == 0)
		printf("HRTAce");
	else if ((cardnum >= 1) && (cardnum <= 9)) //카드 숫자와 카드값이 같은 경우 
		printf("HRT%d", TrumpCard[cardnum]);
	else if (cardnum == 10)
		printf("HRTJack");
	else if (cardnum == 11)
		printf("HRTQueen");
	else if (cardnum == 12)
		printf("HRTKing");	
	
	//dia pattern
	else if (cardnum == 13)
		printf("DIAAce");
	else if ((cardnum >= 14) && (cardnum <= 22)) //카드 숫자와 카드값이 같은 경우
		printf("DIA%d", TrumpCard[cardnum]);
	else if (cardnum == 23)
		printf("DIAJack");
	else if (cardnum == 24)
		printf("DIAQueen");
	else if (cardnum == 25)
		printf("DIAKing");
	
	//spade pattern
	else if (cardnum == 26)
		printf("SPDAce");
	else if ((cardnum >= 27) && (cardnum <= 35)) //카드 숫자와 카드값이 같은 경우
		printf("SPD%d", TrumpCard[cardnum]);
	else if (cardnum == 36)
		printf("SPDJack");
	else if (cardnum == 37)
		printf("SPDQueen");
	else if (cardnum == 38)
		printf("SPDKing");
		
	//clover pattern 
	else if (cardnum == 39)
		printf("CLVAce");
	else if ((cardnum >= 40) && (cardnum <= 48)) //카드 숫자와 카드값이 같은 경우
		printf("CLV%d", TrumpCard[cardnum]);
	else if (cardnum == 49)
		printf("CLVJack");
	else if (cardnum == 50)
		printf("CLVQueen");
	else if (cardnum == 51)
		printf("CLVKing");
}
