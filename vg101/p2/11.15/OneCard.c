#include "Defs.h"
#include "UI.h"
#include "Objs.h"
#include "Log.h"

int main(int argc, char* argv[])
{
	int iStartPlayer = 0;

	gsinfo.g_pDecks = NULPTR;
	gsinfo.g_pDiscarded= NULPTR;
	gsinfo.g_ppPlayers = NULPTR;
	gsinfo.g_pScore = NULPTR;
	gsinfo.g_pPlayerNCard = NULPTR;

	gsinfo.g_nAttacks= 0;
	gsinfo.g_nDir = DIR_COUNTERCLOCKWISE;
	gsinfo.g_nRounds = 2;
	gsinfo.g_nDecks = 2;
	gsinfo.g_nInitCards = 5;
	gsinfo.g_nPlayers = 4;
	gsinfo.g_iAuto= 0;
	gsinfo.g_iStartID = -1;
	gsinfo.g_nDiscardedPile = 0;
	gsinfo.g_nStockPile = 0;

	//command processing
	if (ProcessCmd(argc, argv) == 1)
	{
		PrintHelpInfo();
		return 0;
	}
	
	//initialize decks;
	InitDecks(&(gsinfo.g_pDecks));
	
	//Shuffling
	Shuffle(gsinfo.g_pDecks, 2 * DECKSIZE, 1000);
 	PrintCards(gsinfo.g_pDecks, 2 * DECKSIZE);
	
	//Initilize players
	InitPlayers();
	
	//dealing order cards (once only)
	iStartPlayer = DealingOrderCards((gsinfo.g_nPlayers));
	DealingInitCards();
	
	//start a loop for game
	RunGame(iStartPlayer);
	return 0;
}
