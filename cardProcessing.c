//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int actualNum;
	
	actualNum = TrumpCard[cardnum];
	return actualNum;
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	if ((cardnum>=0) && (cardnum<=9))
		printf("HRT%d", TrumpCard[cardnum]);
	else if (cardnum=10)
		printf("HRTJack");
	else if (cardnum=11)
		printf("HRTQueen");
	else if (cardnum=12)
		printf("HRTKing");
	
	else if ((cardnum>=13) && (cardnum<=22))
		printf("DIA%d", TrumpCard[cardnum]);
	else if (cardnum=23)
		printf("DIAJack");
	else if (cardnum=24)
		printf("DIAQueen");
	else if (cardnum=25)
		printf("DIAKing");
	
	else if ((cardnum>=26) && (cardnum<=35))
		printf("SPD%d", TrumpCard[cardnum]);
	else if (cardnum=36)
		printf("SPDJack");
	else if (cardnum=37)
		printf("SPDQueen");
	else if (cardnum=38)
		printf("SPDKing");
		
	else if ((cardnum>=39) && (cardnum<=48))
		printf("CLV%d", TrumpCard[cardnum]);
	else if (cardnum=49)
		printf("CLVJack");
	else if (cardnum=50)
		printf("CLVQueen");
	else if (cardnum=51)
		printf("CLVKing");
}
