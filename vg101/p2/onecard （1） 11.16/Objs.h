#ifndef __OBJS_H__
#define __OBJS_H__
#include "Defs.h"

#define DIR_COUNTERCLOCKWISE 0x00
#define DIR_CLOCKWISE		(!DIR_COUNTERCLOCKWISE)

typedef struct
{
	StCard* g_pDecks;// = NULPTR;
	StCard* g_pDiscarded; //= NULPTR;
	StCard** g_ppPlayers;// = NULPTR;
	int* g_pScore;// = NULPTR;
	int* g_pPlayerNCard;// = NULPTR;

	int g_nAttacks;//= 0;
	int g_nDir;// = DIR_COUNTERCLOCKWISE;
	int g_nRounds;// = 2;
	int g_nDecks;// = 2;
	int g_nInitCards;// = 5;
	int g_nPlayers;// = 4;
	int g_iAuto;//= 0;
	int g_iStartID;// = -1;
	int g_nDiscardedPile;// = 0;
	int g_nStockPile;// = 0;
}STINFO;
extern STINFO gsinfo;
STINFO gsinfo;

//extern StCard* g_pDecks;
//extern int g_nRounds;
//extern int (gsinfo.g_nDecks);
//extern int (gsinfo.g_nInitCards);
//extern int (gsinfo.g_nPlayers);

/*
	return value:
			1: help
			2: 
*/
int ProcessCmd(int argc, char* argv[]);

//print help information
void PrintHelpInfo();

//shuffling cardss
void Shuffle(StCard* pDecks, int nCards, int nShuffle);

//initialize decks
void InitDecks(StCard** pDecks);
void InitPlayers();

//dealing cards to initialize the order
int DealingOrderCards();

//dealing initial cards
int DealingInitCards();

//play one card
int PlayCard(const StCard* pLastCard, const StCard* pCurrentCard, int* pnAttack, int* pIsAttack, int* pSkip, int* pDir, int* pnDefense);

//run game. iStartUser: firt player
int RunGame(int iStartUser);
int DeadStatus(StCard lastCard);
void CalcScore();
int FindFirstAvailableCard(StCard* pCards, int nCards, StCard lastCard);
int WinPlayer(int iPlayer);
#endif
