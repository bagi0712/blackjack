//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i;     //for���� ���� ���� ����  
	int j;     //for���� ���� ���� ����  
	
	for (i=0;i<N_CARD;i++)     //���� �Ҵ��� �ߺ��� ���� ���� for�� ��ø   
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
