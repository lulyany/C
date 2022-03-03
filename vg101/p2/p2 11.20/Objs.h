#ifndef __OBJS_H__
#define __OBJS_H__
#include "Defs.h"

#define DIR_COUNTERCLOCKWISE 0x00
#define DIR_CLOCKWISE		(!DIR_COUNTERCLOCKWISE)

typedef struct STPLAYER
{
	int m_iPlayerID;
	struct STPLAYER* pNext;
	struct STPLAYER* pPrev;
}STPLAYER;

typedef struct
{
	StCard* m_pDecks;// = NULPTR;
	StCard* m_pDiscarded; //= NULPTR;
	StCard** m_ppPlayers;// = NULPTR;
	int* m_pScore;// = NULPTR;
	int* m_pPlayerNCard;// = NULPTR;

	int m_nAttacks;//= 0;
	int m_nDir;// = DIR_COUNTERCLOCKWISE;
	int m_nRounds;// = 2;
	int m_nDecks;// = 2;
	int m_nInitCards;// = 5;
	int m_nPlayers;// = 4;
	int m_iAuto;//= 0;
	int m_iStartID;// = -1;
	int m_nDiscardedPile;// = 0;
	int m_nStockPile;// = 0;
	STPLAYER* m_pCurrentPlayer;
	STPLAYER* m_pHeadPlayer;
	char m_szLogFile[256];
}STINFO;

/*
	return value:
			1: help
			2: 
*/
int ProcessCmd(int argc, char* argv[], STINFO* pinfo);

//print help information
void PrintHelpInfo();

//shuffling cardss
void Shuffle(StCard* pDecks, int nCards, int nShuffle);

//initialize decks
void InitDecks(StCard** ppDecks, STINFO* pInfo);
void InitPlayers(STINFO* pInfo);

//dealing cards to initialize the order
int DealingOrderCards(STINFO* pinfo);

//dealing initial cards
int DealingInitCards(STINFO* pinfo);

//play one card
int PlayCard(const StCard* pLastCard, const StCard* pCurrentCard, int* pnAttack, int* pIsAttack, int* pSkip, int* pDir, int* pnDefense);

//run game. iStartUser: firt player
int RunGame(int iStartUser, STINFO* pinfo);
int DeadStatus(StCard lastCard, STINFO* pinfo);
void CalcScore(STINFO* pinfo);
int FindFirstAvailableCard(StCard* pCards, int nCards, StCard lastCard);
int WinPlayer(int iPlayer, STINFO* pinfo);
#endif
