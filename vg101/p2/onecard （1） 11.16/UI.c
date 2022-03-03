#include <stdio.h>
#include <time.h>
#include "UI.h"

char Suit2Char(Suit st)
{
	switch(st)
	{
	case Spades: return 'S';
	case Hearts: return 'H';
	case Clubs: return 'C';
	case Diamonds: return 'D';
	default: return 'X';
	}
}

char* Rank2Char(unsigned char ucRank)
{
	switch(ucRank)
	{
	case MINRANK: return "2";
	case MINRANK + 1: return "3";
	case MINRANK + 2: return "4";
	case MINRANK + 3: return "5";
	case MINRANK + 4: return "6";
	case MINRANK + 5: return "7";
	case MINRANK + 6: return "8";
	case MINRANK + 7: return "9";
	case MINRANK + 8: return "10";
	case MINRANK + 9: return "J";
	case MINRANK + 10: return "Q";
	case MINRANK + 11: return "K";
	case MINRANK + 12: return "A";
	default: return "x";
	}
}

int Compare2Cards(StCard* pCard1, StCard* pCard2)
{
	if (pCard1->m_eSuit == pCard2->m_eSuit &&
		pCard1->m_ucRank == pCard2->m_ucRank)
		return 0;

	if (pCard1->m_eSuit < pCard2->m_eSuit)
		return -1;
	else if (pCard1->m_eSuit > pCard2->m_eSuit)
		return 1;
	else
	{
		if (pCard1->m_ucRank < pCard2->m_ucRank)
			return -1;
		else
			return 1;
	}
}

void Sort(StCard* pCards, int nCards)
{
	int i = 0, j = 0;
	int Counts = nCards - 1; // ÅÅÐò×ÜÂÖÊý
	for (i = 0; i < Counts; i++)
	{
		for (j = 0; j < Counts - i; j++)
		{
			if (Compare2Cards(&(pCards[j]), &(pCards[j + 1])) > 0)
			{
				StCard tmp = pCards[j + 1];
				pCards[j + 1] = pCards[j];
				pCards[j] = tmp;
			}
		}
	}
}

void DrawCards(StCard* pCards, int nCards)
{
	int nCnt = 0;
	int i = 0, j = 0, iLastRowInd = 0;
	int iCardID = 0;
	if (pCards == NULPTR || nCards == 0)
		return;
	
 	printf("\n");

	Sort(pCards, nCards);

	//Print rows of cards, UI_MAX_LINE_CARDS cards each row.
	for (i = 0; i < (int)(nCards / UI_MAX_LINE_CARDS); i++)
	{	
		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			printf("_____");
			printf(" ");
		}
		
		printf("\n");
		
		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if (pCards[iCardID].m_ucRank != 10)
				printf("|%s  |", Rank2Char(pCards[iCardID].m_ucRank));
			else
				printf("|%s |", Rank2Char(pCards[iCardID].m_ucRank));
			printf(" ");
		}
		
		printf("\n");
		
		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			printf("| %c |", Suit2Char(pCards[iCardID].m_eSuit));
			printf(" ");
		}
		
		printf("\n");
		
		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if (pCards[iCardID].m_ucRank != 10)
				printf("|__%s|", Rank2Char(pCards[iCardID].m_ucRank));
			else
				printf("|_%s|", Rank2Char(pCards[iCardID].m_ucRank));
			printf(" ");
		}
		printf("\n");

		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if(iCardID + 1 < 10)
				printf("  %d  ", iCardID + 1);
			else if (iCardID + 1 < 100)
				printf("  %d ", iCardID + 1);
			else if (iCardID + 1 < 1000)
				printf(" %d ", iCardID + 1);
			else if (iCardID + 1 < 10000)
				printf(" %d", iCardID + 1);
			else
				printf("*****");
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	
	//Print Last Row of Card
	iLastRowInd = nCards - nCards % UI_MAX_LINE_CARDS;
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		printf("_____");
		printf(" ");
	}
	
	printf("\n");
	
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if (pCards[iCardID].m_ucRank != 10)
			printf("|%s  |", Rank2Char(pCards[iCardID].m_ucRank));
		else
			printf("|%s |", Rank2Char(pCards[iCardID].m_ucRank));
		printf(" ");
	}
	
	printf("\n");
	
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		printf("| %c |", Suit2Char(pCards[iCardID].m_eSuit));
		printf(" ");
	}
	
	printf("\n");
	
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if (pCards[iCardID].m_ucRank != 10)
			printf("|__%s|", Rank2Char(pCards[iCardID].m_ucRank));
		else
			printf("|_%s|", Rank2Char(pCards[iCardID].m_ucRank));
		printf(" ");
	}

	printf("\n");
	
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if(iCardID + 1 < 10)
			printf("  %d  ", iCardID + 1);
		else if (iCardID + 1 < 100)
			printf("  %d ", iCardID + 1);
		else if (iCardID + 1 < 1000)
			printf(" %d ", iCardID + 1);
		else if (iCardID + 1 < 10000)
			printf(" %d", iCardID + 1);
		else
			printf("*****");
		printf(" ");
	}
	printf("\n");
	return;
}

void Delay(unsigned long msec)
{
	clock_t now, start;

	start = clock();
	do
	{
		now = clock();
	} while (now - start < msec);
}