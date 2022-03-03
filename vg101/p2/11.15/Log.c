#include <stdio.h>
#include "Defs.h"
#include "UI.h"

char g_szLog[1024];

//#define POSITION_LOG "onecard.log";total 2 places.line 21/line35.

void PrintCards(StCard* pCards, int nCards)
{
	int i = 0;
	FILE* fp = fopen("log.txt", "w");
	for (i = 0; i < nCards; i++)
		fprintf(fp, "%c %s\n", Suit2Char(pCards[i].m_eSuit), Rank2Char(pCards[i].m_ucRank));
	fclose(fp);
	return;
}

void UpdateLog()
{
	FILE* fp = fopen("onecard.log", "a");
	fprintf(fp, "%s\n", g_szLog);
	fclose(fp);
}

void FDrawCards(StCard* pCards, int nCards)
{
	FILE* fp;
	int nCnt = 0;
	int i = 0, j = 0, iLastRowInd = 0;
	int iCardID = 0;
	if (pCards == NULPTR || nCards == 0)
		return;

	fp = fopen("onecard.log", "a");
	fprintf(fp, "\n");

	Sort(pCards, nCards);

	//Print rows of cards, UI_MAX_LINE_CARDS cards each row.
	for (i = 0; i < (int)(nCards / UI_MAX_LINE_CARDS); i++)
	{
		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			fprintf(fp, "_____");
			fprintf(fp, " ");
		}

		fprintf(fp, "\n");

		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if (pCards[iCardID].m_ucRank != 10)
				fprintf(fp, "|%s  |", Rank2Char(pCards[iCardID].m_ucRank));
			else
				fprintf(fp, "|%s |", Rank2Char(pCards[iCardID].m_ucRank));
			fprintf(fp, " ");
		}

		fprintf(fp, "\n");

		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			fprintf(fp, "| %c |", Suit2Char(pCards[iCardID].m_eSuit));
			fprintf(fp, " ");
		}

		fprintf(fp, "\n");

		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if (pCards[iCardID].m_ucRank != 10)
				fprintf(fp, "|__%s|", Rank2Char(pCards[iCardID].m_ucRank));
			else
				fprintf(fp, "|_%s|", Rank2Char(pCards[iCardID].m_ucRank));
			fprintf(fp, " ");
		}
		fprintf(fp, "\n");

		for (j = 0; j < UI_MAX_LINE_CARDS; j++)
		{
			iCardID = i * UI_MAX_LINE_CARDS + j;
			if (iCardID + 1 < 10)
				fprintf(fp, "  %d  ", iCardID + 1);
			else if (iCardID + 1 < 100)
				fprintf(fp, "  %d ", iCardID + 1);
			else if (iCardID + 1 < 1000)
				fprintf(fp, " %d ", iCardID + 1);
			else if (iCardID + 1 < 10000)
				fprintf(fp, " %d", iCardID + 1);
			else
				fprintf(fp, "*****");
			fprintf(fp, " ");
		}
	}
	fprintf(fp, "\n");

	//Print Last Row of Card
	iLastRowInd = nCards - nCards % UI_MAX_LINE_CARDS;
	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		fprintf(fp, "_____");
		fprintf(fp, " ");
	}

	fprintf(fp, "\n");

	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if (pCards[iCardID].m_ucRank != 10)
			fprintf(fp, "|%s  |", Rank2Char(pCards[iCardID].m_ucRank));
		else
			fprintf(fp, "|%s |", Rank2Char(pCards[iCardID].m_ucRank));
		fprintf(fp, " ");
	}

	fprintf(fp, "\n");

	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		fprintf(fp, "| %c |", Suit2Char(pCards[iCardID].m_eSuit));
		fprintf(fp, " ");
	}

	fprintf(fp, "\n");

	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if (pCards[iCardID].m_ucRank != 10)
			fprintf(fp, "|__%s|", Rank2Char(pCards[iCardID].m_ucRank));
		else
			fprintf(fp, "|_%s|", Rank2Char(pCards[iCardID].m_ucRank));
		fprintf(fp, " ");
	}

	fprintf(fp, "\n");

	for (j = iLastRowInd; j < iLastRowInd + nCards % UI_MAX_LINE_CARDS; j++)
	{
		iCardID = j;
		if (iCardID + 1 < 10)
			fprintf(fp, "  %d  ", iCardID + 1);
		else if (iCardID + 1 < 100)
			fprintf(fp, "  %d ", iCardID + 1);
		else if (iCardID + 1 < 1000)
			fprintf(fp, " %d ", iCardID + 1);
		else if (iCardID + 1 < 10000)
			fprintf(fp, " %d", iCardID + 1);
		else
			fprintf(fp, "*****");
		fprintf(fp, " ");
	}
	fprintf(fp, "\n");
	fclose(fp);
	return;
}