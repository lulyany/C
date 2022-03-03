//#include <malloc.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WINOS_
#include <conio.h>
#endif
#include <string.h>
#include "Defs.h"
#include "Objs.h"
#include "UI.h"
#include "Log.h"



int ProcessCmd(int argc, char* argv[], STINFO* pinfo)
{
	int i = 0;

	if (argc == 0)
		return 0;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], CMD_HELP) == 0 ||
			strcmp(argv[i], CMD_HELP_) == 0)
			return 1;
	}

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], CMD_DECKS) == 0 ||
			strcmp(argv[i], CMD_DECKS_) == 0)
			(pinfo->m_nDecks) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_LOG_) == 0)
			strcpy(pinfo->m_szLogFile, argv[i + 1]);

		if (strcmp(argv[i], CMD_NPLAYER) == 0 ||
			strcmp(argv[i], CMD_NPLAYER_) == 0)
			(pinfo->m_nPlayers) = atoi(argv[i + 1]);
		
		if (strcmp(argv[i], CMD_INITCARD) == 0 ||
			strcmp(argv[i], CMD_INITCARD_) == 0)
			(pinfo->m_nInitCards) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_ROUND) == 0 ||
			strcmp(argv[i], CMD_ROUND_) == 0)
			(pinfo->m_nRounds) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_DEMO) == 0 ||
			strcmp(argv[i], CMD_DEMO_) == 0)
			pinfo->m_iAuto = 1;
	}
	return 0;
}

//Print help information for cmd line
void PrintHelpInfo()
{
	printf("-h|--help               printf this help message\n");
	printf("--log filename          write the logs in filename(default: onecard.log)\n");
	printf("-n n|--player-number=n  n players, n must be larger than 2 (default: 4)\n");
	printf("-c c|--initial-cards=c  deal c cards per player, c must be at least 2 (default: 5)\n");
	printf("-d c|--decks=d          use d decks 52 cards each, d must be at least 2 (default: 2)\n");
	printf("-r r|--rounds=r         play r rounds, r must be at least 1 (default: 1)\n");
	printf("-a|--auto               run in demo mode\n");
}

void Shuffle(StCard* pDecks, int nCards, int nShuffle)
{
	time_t timep;
	struct tm *p;
	int i = 0;
	time (&timep);
	p= gmtime(&timep);
	srand((unsigned int)(p->tm_sec));
	for (i = 0; i < nShuffle; i++)
	{
		int id1 = (int)(rand() / (double)RAND_MAX * nCards + 0.5) % nCards;
		int id2 = (int)(rand() / (double)RAND_MAX * nCards + 0.5) % nCards;
		if (id1 != id2)
		{
			StCard tmp = pDecks[id1];
			pDecks[id1] = pDecks[id2];
			pDecks[id2] = tmp;
		}
	}
}

void InitDecks(StCard** ppDecks, STINFO* pInfo)
{
	int i = 0;
	int j = 0;
	int iDeckID = 0;

	
	UpdateLog(pInfo->m_szLogFile, "*************************");
	UpdateLog(pInfo->m_szLogFile, "*                       *");
	UpdateLog(pInfo->m_szLogFile, "*   Welcome to OneCard  *");
	UpdateLog(pInfo->m_szLogFile, "*                       *");
	UpdateLog(pInfo->m_szLogFile, "*************************");

	UpdateLog(pInfo->m_szLogFile, "-------Initial Setup-----");
	UpdateLog(pInfo->m_szLogFile, "Number of Decks:%d", (pInfo->m_nDecks));
	UpdateLog(pInfo->m_szLogFile, "Number of Players(4 by default):%d", (pInfo->m_nPlayers));
	UpdateLog(pInfo->m_szLogFile, "Number of Rounds:%d", pInfo->m_nRounds);
	UpdateLog(pInfo->m_szLogFile, "Number of Initial Cards:%d", (pInfo->m_nInitCards));

	*ppDecks = malloc((long unsigned int)(sizeof(StCard) * DECKSIZE * (long unsigned int)(pInfo->m_nDecks)));
	for (i = 0; i < (pInfo->m_nDecks); i++)
	{
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Spades, (unsigned char)j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Hearts, (unsigned char)j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Diamonds, (unsigned char)j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Clubs, (unsigned char)j};
			(*ppDecks)[iDeckID++] = card;
		}
	}
	(pInfo->m_pDiscarded) = NULPTR;
	(pInfo->m_nStockPile) = (pInfo->m_nDecks) * DECKSIZE;
	(pInfo->m_nDiscardedPile) = 0;
}

void InitPlayers(STINFO* pInfo)
{
	int i = 0;
	
	(pInfo->m_ppPlayers) = malloc((unsigned long int)(pInfo->m_nPlayers) * sizeof(StCard*));
	(pInfo->m_pScore) = malloc((unsigned long int)(pInfo->m_nPlayers) * sizeof(int));
	(pInfo->m_pPlayerNCard) = malloc((unsigned long int)(pInfo->m_nPlayers) * sizeof(int));
	pInfo->m_pHeadPlayer = pInfo->m_pCurrentPlayer = NULPTR;
	for (i = 0; i < (pInfo->m_nPlayers); i++)
	{
		STPLAYER* pPlayer;
		(pInfo->m_ppPlayers)[i] = malloc(sizeof(StCard) * (unsigned long int)(pInfo->m_nInitCards));
		(pInfo->m_pScore)[i] = 0;
		(pInfo->m_pPlayerNCard)[i] = 0;
		pPlayer = (STPLAYER*)malloc(sizeof(STPLAYER));
		pPlayer->m_iPlayerID = i;
		if (pInfo->m_pCurrentPlayer)
		{
			pPlayer->pPrev = pInfo->m_pCurrentPlayer;
			pInfo->m_pCurrentPlayer->pNext = pPlayer;
			pInfo->m_pCurrentPlayer = pPlayer;
		}
		else
		{
			pInfo->m_pCurrentPlayer = pPlayer;
			pInfo->m_pHeadPlayer = pPlayer;
		}
	}
	pInfo->m_pCurrentPlayer->pNext = pInfo->m_pHeadPlayer;
	pInfo->m_pHeadPlayer->pPrev = pInfo->m_pCurrentPlayer;
	pInfo->m_nDir = DIR_COUNTERCLOCKWISE;
}

int DealingOrderCards(STINFO* pinfo)
{
	int i = 0, iMinPlayer = 0;
	unsigned char ucMinRank = 0xFF;
	StCard* pOrderCard = NULPTR;
	StCard* pTmp = NULPTR;
	pOrderCard = malloc(sizeof(StCard) * (unsigned long int)(pinfo->m_nPlayers));
	memcpy(pOrderCard, (pinfo->m_pDecks), sizeof(StCard) * (unsigned long int)(pinfo->m_nPlayers));
	printf("Dealing cards to determine the playing order...\n");
	DrawCards(pOrderCard, (pinfo->m_nPlayers));
	UpdateLog(pinfo->m_szLogFile, "Dealing cards to determine the playing order...\n");
	FDrawCards(pinfo->m_szLogFile, pOrderCard, (pinfo->m_nPlayers));
	for (i = 0; i < (pinfo->m_nPlayers); i++)
	{
		if (pOrderCard[i].m_ucRank < ucMinRank)
		{
			ucMinRank = pOrderCard[i].m_ucRank;
			iMinPlayer = i;
		}
	}
	(pinfo->m_pDiscarded) = (StCard*)malloc((unsigned long int)(pinfo->m_nPlayers) * sizeof(StCard));
	memcpy((pinfo->m_pDiscarded), pOrderCard, (unsigned long int)(pinfo->m_nPlayers) * sizeof(StCard));
	(pinfo->m_nDiscardedPile) = (pinfo->m_nPlayers);
	(pinfo->m_nStockPile) -= (pinfo->m_nDiscardedPile);
	free(pOrderCard);

	pTmp = (StCard*)malloc((unsigned long int)(pinfo->m_nStockPile)*sizeof(StCard));
	memcpy(pTmp, (pinfo->m_pDecks) + (pinfo->m_nPlayers), (unsigned long int)((pinfo->m_nStockPile)) * sizeof(StCard));
	free((pinfo->m_pDecks));
	(pinfo->m_pDecks) = pTmp;
	printf("(4 players default, see ./onecard -h for more)The game will starts with player %d\n", iMinPlayer + 1);
	UpdateLog(pinfo->m_szLogFile, "(4 players default, see ./onecard -h for more)The game will starts with player %d\n", iMinPlayer + 1);

	printf("Press 'Y' to continue...\n");
	if ((pinfo->m_iAuto))
	{
		Delay(AUTO_DELAY);
	}
	else
	{
#ifdef _WINOS_
		getch();
#else
		getchar();
#endif
	}
	return iMinPlayer;
}

int DealingInitCards(STINFO* pinfo)
{
	int i = 0;
	StCard* pTmp = NULPTR;
	for (i = 0; i < (pinfo->m_nPlayers); i++)
	{
		memcpy(pinfo->m_ppPlayers[i], pinfo->m_pDecks + i * (pinfo->m_nInitCards), sizeof(StCard) * (unsigned long int)(pinfo->m_nInitCards));
		(pinfo->m_nStockPile) -= (pinfo->m_nInitCards);
		(pinfo->m_pPlayerNCard)[i] = (pinfo->m_nInitCards);
		UpdateLog(pinfo->m_szLogFile, "Player %d\n", i + 1);
		FDrawCards(pinfo->m_szLogFile, (pinfo->m_ppPlayers)[i], (pinfo->m_nInitCards));
	}

	pTmp = (StCard*)malloc((unsigned long int)(pinfo->m_nStockPile)*sizeof(StCard));
	memcpy(pTmp, (pinfo->m_pDecks) + (pinfo->m_nPlayers) * (pinfo->m_nInitCards), (long unsigned int)((pinfo->m_nStockPile)) * sizeof(StCard));
	free((pinfo->m_pDecks));
	(pinfo->m_pDecks) = pTmp;
	return 0;
}

int PlayCard(const StCard* pLastCard, const StCard* pCurrentCard, int* pnAttack, int* pIsAttack, int* pSkip, int* pDir, int* pnDefense)
{
	if (pLastCard == NULPTR)
		return -1;
	if (pLastCard->m_eSuit != pCurrentCard->m_eSuit &&
		pLastCard->m_ucRank != pCurrentCard->m_ucRank)
		return -1;
	
	if (pCurrentCard->m_ucRank == 7)
	{
		*pnDefense = 1;
		*pnAttack = 0;
		return 0;
	}
	else if (pCurrentCard->m_ucRank == 2 || pCurrentCard->m_ucRank == 3)
	{
		*pIsAttack = 1;
		*pnAttack += pCurrentCard->m_ucRank;
		return 0;
	}
	else if (pCurrentCard->m_ucRank == 11)
	{
		*pSkip = 1;
		return 0;
	}
	else if (pCurrentCard->m_ucRank == 12)
	{
		*pDir = 1;
		return 0;
	}
	else
	{
		return 0;
	}
	
}

int RunGame(int iStartUser, STINFO* pinfo)
{
	int iCurrenPlayer = iStartUser;
	while (pinfo->m_pCurrentPlayer->m_iPlayerID != iStartUser)
		pinfo->m_pCurrentPlayer = pinfo->m_pCurrentPlayer->pNext;
	int iRound = 0;
	int i = 0;
	int iPass = 0;
	
	for (iRound = 0; iRound < (pinfo->m_nRounds); iRound++)
	{
		StCard* pTmp = NULPTR;
		StCard lastCard = (pinfo->m_pDecks)[0];
		int iChoice = -1;
		(pinfo->m_nAttacks) = 0;
		pinfo->m_nDir = 0;
		(pinfo->m_nStockPile) -= 1;
		pTmp = (StCard*)malloc(sizeof(StCard) * (long unsigned int)(pinfo->m_nStockPile));
		memcpy(pTmp, (pinfo->m_pDecks) + 1, sizeof(StCard) *(long unsigned int) (pinfo->m_nStockPile));
		free((pinfo->m_pDecks));
		(pinfo->m_pDecks) = pTmp;
		
		if (lastCard.m_ucRank == 2)
			(pinfo->m_nAttacks) += 2;
		else if (lastCard.m_ucRank == 3)
			(pinfo->m_nAttacks) += 3;
		else if (lastCard.m_ucRank == 7)
			(pinfo->m_nAttacks) = 0;
		else if (lastCard.m_ucRank == 12)
			pinfo->m_nDir = !(pinfo->m_nDir);

		while (1)
		{
			int iNuse = 0;
			//clear the screen
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
			iNuse = system("cls");	
#else 
			iNuse = system("clear");
#endif
			//iNuse = iNuse;
			//printing the cards
			if (DeadStatus(lastCard,pinfo))
			{
				printf("No suitable cards...game over, calculating scores for each player...\n");
				CalcScore(pinfo);
				for (i = 0; i < (pinfo->m_nPlayers); i++)
				{
					printf("Player %d has %d card(s) remained, score=%d\n", i + 1, (pinfo->m_pPlayerNCard)[i], (pinfo->m_pScore)[i]);
				}
				break;
			}

			printf("------player %d's turn, round %d------\n", iCurrenPlayer + 1, iRound);
			for (i = 0; i < (pinfo->m_nPlayers); i++)
				printf("Player %d has %d card(s)\n", i + 1, (pinfo->m_pPlayerNCard)[i]);
			printf("Current Attack:%d\n", (pinfo->m_nAttacks));
			printf("Last card:");
			DrawCards(&lastCard, 1);
			printf("\n");
			printf("Player %d cards:", iCurrenPlayer + 1);
			DrawCards((pinfo->m_ppPlayers)[iCurrenPlayer], (pinfo->m_pPlayerNCard)[iCurrenPlayer]);
			
			iPass = 0;
			do
			{
				printf("Input 1~%d to play a card or 0 to pass the turn.\n", (pinfo->m_pPlayerNCard)[iCurrenPlayer]);
				if (!(pinfo->m_iAuto))
				{
					int _temp=0;
					int nTmp = scanf("%d", &iChoice);
					_temp = nTmp;
					fflush(stdin);
				}
				else
				{
					int iRet = FindFirstAvailableCard((pinfo->m_ppPlayers)[iCurrenPlayer], (pinfo->m_pPlayerNCard)[iCurrenPlayer], lastCard);
					if (iRet < 0)
						iChoice = 0;
					else
						iChoice = iRet + 1;
					printf("%d was chosen\n", iChoice);
					Delay(AUTO_DELAY);
				}

				if (iChoice < 0 || iChoice > (pinfo->m_pPlayerNCard)[iCurrenPlayer])
				{
					printf("Invailid input, press anykey to continue...");
					continue;
				}
				else if (iChoice > 0)
				{
					int iRealChoice = iChoice - 1;
					if ((pinfo->m_ppPlayers)[iCurrenPlayer][iRealChoice].m_eSuit != lastCard.m_eSuit &&
						(pinfo->m_ppPlayers)[iCurrenPlayer][iRealChoice].m_ucRank != lastCard.m_ucRank)
					{
						printf("Invailid input, neither suit nor rank matches last card, press anykey to continue...");
						continue;
					}
					else
						break;
				}
				else if (iChoice == 0)
				{
					iPass = 1;
					break;
				}
				else
				{
					break;
				}
			}
			while(1);
			

			//checking for reverse/skip/attack/defense
			//////////////////////////////////////////////////////////////////////////
			{
				int iRealChoice = iChoice - 1;
				int iSkip = 0;
				int iIsAttack = 0;
				int iDirFlip = 0;
				int iDefense = 0;
				int iNextPlayer = 0;
				int iRet = 0;

				if (iPass)
				{
					if ((pinfo->m_nAttacks))
					{
						int iCnt = 0;
						//iNextPlayer = (iCurrenPlayer + 1) % (pinfo->m_nPlayers);
						if (pinfo->m_nDir == DIR_COUNTERCLOCKWISE)
							iNextPlayer = (pinfo->m_pCurrentPlayer)->pNext->m_iPlayerID;
						else
							iNextPlayer = (pinfo->m_pCurrentPlayer)->pPrev->m_iPlayerID;
						pTmp = malloc(sizeof(StCard) * (long unsigned int)((pinfo->m_pPlayerNCard)[iCurrenPlayer] + (pinfo->m_nAttacks)));
						for (i = 0; i < (pinfo->m_pPlayerNCard)[iCurrenPlayer]; i++)
							pTmp[iCnt++] = (pinfo->m_ppPlayers)[iCurrenPlayer][i];
						for (i = 0; i < (pinfo->m_nAttacks); i++)
						{
							if ((pinfo->m_nStockPile) > 1)
							{
								StCard* pTmp2 = NULPTR;
								pTmp[iCnt++] = (pinfo->m_pDecks)[0];
								pTmp2 = malloc(sizeof(StCard) * (long unsigned int)((pinfo->m_nStockPile) - 1));
								memcpy(pTmp2, (pinfo->m_pDecks) + 1, sizeof(StCard) * (long unsigned int)((pinfo->m_nStockPile) - 1));
								(pinfo->m_nStockPile)--;
								free((pinfo->m_pDecks));
								(pinfo->m_pDecks) = pTmp2;
							}
							else if ((pinfo->m_nStockPile) == 1)
							{
								pTmp[iCnt++] = (pinfo->m_pDecks)[0];
								free((pinfo->m_pDecks));
								(pinfo->m_pDecks) = (pinfo->m_pDiscarded);
								(pinfo->m_nStockPile) = (pinfo->m_nDiscardedPile);
								(pinfo->m_nDiscardedPile) = 0;
								(pinfo->m_pDiscarded) = NULPTR;
								Shuffle((pinfo->m_pDecks), (pinfo->m_nStockPile), (pinfo->m_nStockPile) * 50);
							}
						}
						free( (pinfo->m_ppPlayers)[iCurrenPlayer]);
						(pinfo->m_ppPlayers)[iCurrenPlayer] = pTmp;
						(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] + (pinfo->m_nAttacks);
						(pinfo->m_nAttacks) = 0;
					}
					else
					{
						//iNextPlayer = (iCurrenPlayer + 1) % (pinfo->m_nPlayers);
						if (pinfo->m_nDir == DIR_COUNTERCLOCKWISE)
						{
							iNextPlayer = pinfo->m_pCurrentPlayer->pNext->m_iPlayerID;
							pinfo->m_pCurrentPlayer = pinfo->m_pCurrentPlayer->pNext;
						}
						else
						{
							iNextPlayer = pinfo->m_pCurrentPlayer->pPrev->m_iPlayerID;
							pinfo->m_pCurrentPlayer = pinfo->m_pCurrentPlayer->pPrev;
						}
						iCurrenPlayer = iNextPlayer;
						continue;
					}
				}

				iRet = PlayCard(&lastCard, &((pinfo->m_ppPlayers)[iCurrenPlayer][iRealChoice]), &(pinfo->m_nAttacks), &iIsAttack, &iSkip, &iDirFlip, &iDefense);
				if (iRet != 0)
				{
					printf("Invailid input, neither suit nor rank matches last card, press anykey to continue...");
					continue;	
				}
			
				//last card->discard.
				pTmp = malloc(sizeof(StCard)*(long unsigned int)((pinfo->m_nDiscardedPile) + 1));
				memcpy(pTmp, (pinfo->m_pDiscarded), (long unsigned int)(pinfo->m_nDiscardedPile) * sizeof(StCard));
				free((pinfo->m_pDiscarded));
				(pinfo->m_pDiscarded) = pTmp;
				(pinfo->m_pDiscarded)[(pinfo->m_nDiscardedPile)] = lastCard;
				(pinfo->m_nDiscardedPile)++;
			
				//played card->last
				lastCard = (pinfo->m_ppPlayers)[iCurrenPlayer][iRealChoice];
			
				UpdateLog(pinfo->m_szLogFile, "Player %d played (%c %s)", iCurrenPlayer + 1, Suit2Char(lastCard.m_eSuit), Rank2Char(lastCard.m_ucRank));

				//draw extra card?
				if ((pinfo->m_nAttacks) > 0 && ((!iIsAttack)&&(!iSkip) && (!iDirFlip) && (!iDefense)))
				{
					//draw extra card
					int iCnt = 0;

					UpdateLog(pinfo->m_szLogFile, "Player %d Draw extra card, attack", iCurrenPlayer + 1);

					//iNextPlayer = (iCurrenPlayer + 1) % (pinfo->m_nPlayers);
					if (pinfo->m_nDir)
					{
						iNextPlayer = pinfo->m_pCurrentPlayer->pNext->m_iPlayerID;
					}
					else
						iNextPlayer = pinfo->m_pCurrentPlayer->pPrev->m_iPlayerID;
					pTmp = malloc(sizeof(StCard) *(long unsigned int) ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1/**/ + (pinfo->m_nAttacks)));
					for (i = 0; i < (pinfo->m_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (pinfo->m_ppPlayers)[iCurrenPlayer][i];
						}
					for (i = 0; i < (pinfo->m_nAttacks); i++)
					{
						if ((pinfo->m_nStockPile) > 1)
						{
							StCard* pTmp2 = NULPTR;
							pTmp[iCnt++] = (pinfo->m_pDecks)[0];
							pTmp2 = malloc(sizeof(StCard) * (long unsigned int)((pinfo->m_nStockPile) - 1));
							memcpy(pTmp2, (pinfo->m_pDecks) + 1, sizeof(StCard) *(long unsigned int) ((pinfo->m_nStockPile) - 1));
							(pinfo->m_nStockPile)--;
							free((pinfo->m_pDecks));
							(pinfo->m_pDecks) = pTmp2;
						}
						else if ((pinfo->m_nStockPile) == 1)
						{
							pTmp[iCnt++] = (pinfo->m_pDecks)[0];
							free((pinfo->m_pDecks));
							(pinfo->m_pDecks) = (pinfo->m_pDiscarded);
							(pinfo->m_nStockPile) = (pinfo->m_nDiscardedPile);
							(pinfo->m_nDiscardedPile) = 0;
							(pinfo->m_pDiscarded) = NULPTR;
							Shuffle((pinfo->m_pDecks), (pinfo->m_nStockPile), (pinfo->m_nStockPile) * 50);
						}
					}
					free( (pinfo->m_ppPlayers)[iCurrenPlayer]);
					(pinfo->m_ppPlayers)[iCurrenPlayer] = pTmp;
					(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1 + (pinfo->m_nAttacks);

					(pinfo->m_nAttacks) = 0;	// release attack
				}
				else if (iSkip)
				{
					//skip
					int iCnt = 0;
					UpdateLog(pinfo->m_szLogFile, "Player %d Draw skip", iCurrenPlayer + 1);
					if ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
						free((pinfo->m_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer, pinfo);
						break;
					}

					//iNextPlayer = (iCurrenPlayer + 2) % (pinfo->m_nPlayers);
					
					pTmp = malloc(sizeof(StCard) *(long unsigned int) ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1));
					for (i = 0; i < (pinfo->m_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (pinfo->m_ppPlayers)[iCurrenPlayer][i];
						}
					free((pinfo->m_ppPlayers)[iCurrenPlayer]);
					(pinfo->m_ppPlayers)[iCurrenPlayer] = pTmp;
					(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
				}
				else if (iDirFlip)
				{
					//reverse
					int iCnt = 0;
					UpdateLog(pinfo->m_szLogFile, "Player %d Draw reverse", iCurrenPlayer + 1);
					if ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
						free((pinfo->m_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer,pinfo);
						break;
					}
					
					if (pinfo->m_nDir == DIR_COUNTERCLOCKWISE)
					{
						iNextPlayer = pinfo->m_pCurrentPlayer->pNext->m_iPlayerID;
						pinfo->m_nDir = DIR_CLOCKWISE;
					}
					else 
					{
						iNextPlayer = pinfo->m_pCurrentPlayer->pPrev->m_iPlayerID;
						pinfo->m_nDir = DIR_COUNTERCLOCKWISE;
					}
					pTmp = malloc(sizeof(StCard) *(long unsigned int) ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1));
					for (i = 0; i < (pinfo->m_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (pinfo->m_ppPlayers)[iCurrenPlayer][i];
						}
					free((pinfo->m_ppPlayers)[iCurrenPlayer]);
					(pinfo->m_ppPlayers)[iCurrenPlayer] = pTmp;
					(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
				}
				else
				{
					//defense
					int iCnt = 0;
					if (!iIsAttack)
						(pinfo->m_nAttacks) = 0;
					if ((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
						free((pinfo->m_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer,pinfo);
						break;
					}
					//iNextPlayer = (iCurrenPlayer + 1) % (pinfo->m_nPlayers);
					if (pinfo->m_nDir == DIR_COUNTERCLOCKWISE)
						iNextPlayer = pinfo->m_pCurrentPlayer->pNext->m_iPlayerID;
					else
						iNextPlayer = pinfo->m_pCurrentPlayer->pPrev->m_iPlayerID;
					pTmp = malloc((long unsigned int)(sizeof(StCard) * (long unsigned int)((pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1)));
					for (i = 0; i < (pinfo->m_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (pinfo->m_ppPlayers)[iCurrenPlayer][i];
						}
					free((pinfo->m_ppPlayers)[iCurrenPlayer]);
					(pinfo->m_ppPlayers)[iCurrenPlayer] = pTmp;
					(pinfo->m_pPlayerNCard)[iCurrenPlayer] = (pinfo->m_pPlayerNCard)[iCurrenPlayer] - 1;
				}

				iCurrenPlayer = iNextPlayer;
				pinfo->m_pCurrentPlayer = pinfo->m_pHeadPlayer;
				while (pinfo->m_pCurrentPlayer->m_iPlayerID != iCurrenPlayer)
					pinfo->m_pCurrentPlayer = pinfo->m_pCurrentPlayer->pNext;

				//update dir and next
				if ((pinfo->m_iAuto))
				{
					Delay(AUTO_DELAY);
				}
				else
				{
					printf("Press anykey to continue...");
#ifdef _WINOS_
		getch();
#else
		getchar();
#endif
				}
				//
			}
		}
	}
	return 0;
}

int FindFirstAvailableCard(StCard* pCards, int nCards, StCard lastCard)
{
	int i = 0;
	for (i = 0; i < nCards; i++)
	{
		if (pCards[i].m_eSuit == lastCard.m_eSuit ||
			pCards[i].m_ucRank == lastCard.m_ucRank)
			return i;
	}
	return -1;
}

int WinPlayer(int iPlayer, STINFO* pinfo)
{
	int i = 0;
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
	i=system("cls");
#else
	i=system("clear");
#endif
	i=0;
	CalcScore(pinfo);
	printf("Player %d won the game.\n", iPlayer + 1);
	UpdateLog(pinfo->m_szLogFile, "Player %d won the game.\n", iPlayer + 1);
	for (i = 0; i < (pinfo->m_nPlayers); i++)
	{
		printf("Player %d has %d card(s) remained, score=%d\n", i + 1, (pinfo->m_pPlayerNCard)[i], (pinfo->m_pScore)[i]);

		UpdateLog(pinfo->m_szLogFile, "Player %d has %d card(s) remained, score=%d\n", i + 1, (pinfo->m_pPlayerNCard)[i], (pinfo->m_pScore)[i]);
	}
	Delay(AUTO_DELAY * 5);

	return iPlayer;
}

int DeadStatus(StCard lastCard, STINFO* pinfo)
{
	int i = 0, j = 0;
	for (i = 0; i < (pinfo->m_nPlayers); i++)
	{
		for (j = 0; j < (pinfo->m_pPlayerNCard)[i]; j++)
		{
			if ((pinfo->m_ppPlayers)[i][j].m_eSuit == lastCard.m_eSuit ||
				(pinfo->m_ppPlayers)[i][j].m_ucRank == lastCard.m_ucRank)
				return 0;
		}
	}

	return 1;
}

void CalcScore(STINFO *pinfo)
{
	int i = 0;
	for (i = 0; i < (pinfo->m_nPlayers); i++)
		(pinfo->m_pScore)[i] -= (pinfo->m_pPlayerNCard)[i];
}

void ReleaseDecks(StCard** ppDecks)
{
	if(ppDecks != NULPTR && (*ppDecks) != NULPTR)
		free(*ppDecks);
}

void ReleasePlayers(STINFO* pinfo)
{
	int i = 0;
	for (i = 0; i < (pinfo->m_nPlayers); i++)
		free((pinfo->m_ppPlayers)[i]);
	
	free((pinfo->m_ppPlayers));
}

