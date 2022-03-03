#include "Defs.h"
#include "UI.h"
#include "Objs.h"
#include "Log.h"

int main(int argc, char* argv[])
{
	int iStartPlayer = 0;
	STINFO gsinfo;
	gsinfo.m_pDecks = NULPTR;
	gsinfo.m_pDiscarded= NULPTR;
	gsinfo.m_ppPlayers = NULPTR;
	gsinfo.m_pScore = NULPTR;
	gsinfo.m_pPlayerNCard = NULPTR;

	gsinfo.m_pCurrentPlayer = NULPTR;
	gsinfo.m_pHeadPlayer = NULPTR;
	gsinfo.m_nAttacks= 0;
	gsinfo.m_nDir = DIR_COUNTERCLOCKWISE;
	gsinfo.m_nRounds = 2;
	gsinfo.m_nDecks = 2;
	gsinfo.m_nInitCards = 5;
	gsinfo.m_nPlayers = 4;
	gsinfo.m_iAuto= 0;
	gsinfo.m_iStartID = -1;
	gsinfo.m_nDir = DIR_COUNTERCLOCKWISE;
	gsinfo.m_nDiscardedPile = 0;
	gsinfo.m_nStockPile = 0;
	sprintf(gsinfo.m_szLogFile, "onecard.log");

	//command processing
	if (ProcessCmd(argc, argv, &gsinfo) == 1)
	{
		PrintHelpInfo();
		return 0;
	}
	
	//initialize decks;
	InitDecks(&(gsinfo.m_pDecks), &gsinfo);
	
	//Shuffling
	Shuffle(gsinfo.m_pDecks, 2 * DECKSIZE, 1000);
	
	//Initilize players
	InitPlayers(&gsinfo);
	
	//dealing order cards (once only)
	iStartPlayer = DealingOrderCards(&gsinfo);
	DealingInitCards(&gsinfo);
	
	//start a loop for game
	RunGame(iStartPlayer, &gsinfo);
	return 0;
}
