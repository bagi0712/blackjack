#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h"


extern int cardIndex;
extern int dollar[N_MAX_USER];
extern int n_user;
extern int gameEnd;


//ending game functions -----------------------------


//카드 소진 검사 
int checkCardIndex() {
	if (cardIndex >= N_CARD) //card tray에 카드가 소진됨
	{	
		gameEnd = 1; //game end flag(1)
	}
	
	return 0;
}

//파산 검사
int checkDollar() {
	int i;
	
	for (i=0;i<n_user;i++)
	{
		if (dollar[i] <= 0) //player 한명이 파산
		{
			gameEnd = i+2; //game end flag(2): gameEnd 값이 0이면 게임이 끝나지 않고 1이면 game end flag(1)과 겹치므로 player number에 2를 더해줌 
		}
	}
	
	return 0;
}

//최종 승자 체크 
int checkWinner() {
	int dollarMax = 0; //최종 자산에서 제일 큰 값 
	int winner;
	int i;
	
	for(i=0;i<n_user;i++) //나를 포함한 player들의 자산을 비교 
	{
		if (dollar[i] > dollarMax)
		{
			dollarMax = dollar[i];
			winner = i;
		}
	}	
	
	return winner; //최종 승리한 player의 number을 반환 
}
