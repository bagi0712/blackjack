#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int TrumpCard[N_CARD];


//card processing functions ---------------
						 

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	//�̹� �迭 ���� TrumpCard[]�� ������ �� ī�尡 ���� ���� ���� �Ҵ������Ƿ� �� ���� �״�� ������
	return TrumpCard[cardnum]; //���� �Լ��� ���� �ʿ� ������ �Լ� �̸��� Ȱ�� �� ���ذ� ���� �Լ�ȭ���� 
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {              //ī�� �������忡 ����� ���ڸ� �Ҵ� 
	
	//heart pattern
	if (cardnum == 0)
		printf("HRTAce");
	else if ((cardnum >= 1) && (cardnum <= 9)) //ī�� ���ڿ� ī�尪�� ���� ��� 
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
	else if ((cardnum >= 14) && (cardnum <= 22)) //ī�� ���ڿ� ī�尪�� ���� ���
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
	else if ((cardnum >= 27) && (cardnum <= 35)) //ī�� ���ڿ� ī�尪�� ���� ���
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
	else if ((cardnum >= 40) && (cardnum <= 48)) //ī�� ���ڿ� ī�尪�� ���� ���
		printf("CLV%d", TrumpCard[cardnum]);
	else if (cardnum == 49)
		printf("CLVJack");
	else if (cardnum == 50)
		printf("CLVQueen");
	else if (cardnum == 51)
		printf("CLVKing");
}
