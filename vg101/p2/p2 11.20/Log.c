#include <stdio.h>
#include <stdarg.h>
#include "Defs.h"
#include "UI.h"
#include "Log.h"
//#define POSITION_LOG "onecard.log";

void UpdateLog(const char* pszLogFile,  const char* fmt, ...)
{
	va_list args;
	char szBuffer[1024];
	//memset(szBuffer, 0x00, sizeof(szBuffer));
	va_start(args, fmt);
	vsprintf(szBuffer, fmt, args);
	va_end(args);
	FILE* fp = fopen(pszLogFile, "a");
	fprintf(fp, "%s\n", szBuffer);
	fclose(fp);
}

void FDrawCards(const char* pszLogFile, StCard* pCards, int nCards)
{
	FILE* fp;
	int i = 0, j = 0, iLastRowInd = 0;
	int iCardID = 0;
	if (pCards == NULPTR || nCards == 0)
		return;

	fp = fopen(pszLogFile, "a");
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
