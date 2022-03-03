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



int ProcessCmd(int argc, char* argv[])
{
	int i = 0;

	if (argc == 0)
		return 0;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], CMD_HELP) == 0 ||
			strcmp(argv[i], CMD_HELP) == 0)
			return 1;
	}

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], CMD_DECKS) == 0 ||
			strcmp(argv[i], CMD_DECKS_) == 0)
			(gsinfo.g_nDecks) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_NPLAYER) == 0 ||
			strcmp(argv[i], CMD_NPLAYER_) == 0)
			(gsinfo.g_nPlayers) = atoi(argv[i + 1]);
		
		if (strcmp(argv[i], CMD_INITCARD) == 0 ||
			strcmp(argv[i], CMD_INITCARD_) == 0)
			(gsinfo.g_nInitCards) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_ROUND) == 0 ||
			strcmp(argv[i], CMD_ROUND_) == 0)
			(gsinfo.g_nRounds) = atoi(argv[i + 1]);

		if (strcmp(argv[i], CMD_DEMO) == 0 ||
			strcmp(argv[i], CMD_DEMO_) == 0)
			gsinfo.g_iAuto = 1;
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
	srand(p->tm_sec);
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

void InitDecks(StCard** ppDecks)
{
	int i = 0;
	int j = 0;
	int iDeckID = 0;

	sprintf(g_szLog, "*************************");
	UpdateLog();
	sprintf(g_szLog, "*                       *");
	UpdateLog();
	sprintf(g_szLog, "*   Welcome to OneCard  *");
	UpdateLog();
	sprintf(g_szLog, "*                       *");
	UpdateLog();
	sprintf(g_szLog, "*************************");
	UpdateLog();

	sprintf(g_szLog, "-------Initial Setup-----");
	UpdateLog();
	sprintf(g_szLog, "Number of Decks:%d", (gsinfo.g_nDecks));
	UpdateLog();
	sprintf(g_szLog, "Number of Players(4 by default):%d", (gsinfo.g_nPlayers));
	UpdateLog();
	sprintf(g_szLog, "Number of Rounds:%d", gsinfo.g_nRounds);
	UpdateLog();
	sprintf(g_szLog, "Number of Initial Cards:%d", (gsinfo.g_nInitCards));
	UpdateLog();

	*ppDecks = malloc(sizeof(StCard) * DECKSIZE * (gsinfo.g_nDecks));
	for (i = 0; i < (gsinfo.g_nDecks); i++)
	{
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Spades, j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Hearts, j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Diamonds, j};
			(*ppDecks)[iDeckID++] = card;
		}
		for (j = MINRANK; j <= MINRANK + ALLRANKS - 1; j++)
		{
			StCard card = {Clubs, j};
			(*ppDecks)[iDeckID++] = card;
		}
	}
	(gsinfo.g_pDiscarded) = NULPTR;
	(gsinfo.g_nStockPile) = (gsinfo.g_nDecks) * DECKSIZE;
	(gsinfo.g_nDiscardedPile) = 0;
}

void InitPlayers()
{
	int i = 0;
	(gsinfo.g_ppPlayers) = malloc((gsinfo.g_nPlayers) * sizeof(StCard*));
	(gsinfo.g_pScore) = malloc((gsinfo.g_nPlayers) * sizeof(int));
	(gsinfo.g_pPlayerNCard) = malloc((gsinfo.g_nPlayers) * sizeof(int));
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
	{
		(gsinfo.g_ppPlayers)[i] = malloc(sizeof(StCard) * (gsinfo.g_nInitCards));
		(gsinfo.g_pScore)[i] = 0;
		(gsinfo.g_pPlayerNCard)[i] = 0;
	}
}

int DealingOrderCards()
{
	int i = 0, iMinPlayer = 0;
	unsigned char ucMinRank = 0xFF;
	StCard* pOrderCard = NULPTR;
	StCard* pTmp = NULPTR;
	pOrderCard = malloc(sizeof(StCard) * (gsinfo.g_nPlayers));
	memcpy(pOrderCard, (gsinfo.g_pDecks), sizeof(StCard) * (gsinfo.g_nPlayers));
	printf("Dealing cards to determine the playing order...\n");
	DrawCards(pOrderCard, (gsinfo.g_nPlayers));
	sprintf(g_szLog, "Dealing cards to determine the playing order...\n");
	UpdateLog();
	FDrawCards(pOrderCard, (gsinfo.g_nPlayers));
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
	{
		if (pOrderCard[i].m_ucRank < ucMinRank)
		{
			ucMinRank = pOrderCard[i].m_ucRank;
			iMinPlayer = i;
		}
	}
	(gsinfo.g_pDiscarded) = (StCard*)malloc((gsinfo.g_nPlayers) * sizeof(StCard));
	memcpy((gsinfo.g_pDiscarded), pOrderCard, (gsinfo.g_nPlayers) * sizeof(StCard));
	(gsinfo.g_nDiscardedPile) = (gsinfo.g_nPlayers);
	(gsinfo.g_nStockPile) -= (gsinfo.g_nDiscardedPile);
	free(pOrderCard);

	pTmp = (StCard*)malloc((gsinfo.g_nStockPile)*sizeof(StCard));
	memcpy(pTmp, (gsinfo.g_pDecks) + (gsinfo.g_nPlayers), ((gsinfo.g_nStockPile)) * sizeof(StCard));
	free((gsinfo.g_pDecks));
	(gsinfo.g_pDecks) = pTmp;
	printf("(4 players default, see ./onecard -h for more)The game will starts with player %d\n", iMinPlayer + 1);
	sprintf(g_szLog, "(4 players default, see ./onecard -h for more)The game will starts with player %d\n", iMinPlayer + 1);
	UpdateLog();

	printf("Press 'Y' to continue...\n");
	if ((gsinfo.g_iAuto))
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

int DealingInitCards()
{
	int i = 0;
	StCard* pTmp = NULPTR;
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
	{
		memcpy(gsinfo.g_ppPlayers[i], gsinfo.g_pDecks + i * (gsinfo.g_nInitCards), sizeof(StCard) * (gsinfo.g_nInitCards));
		(gsinfo.g_nStockPile) -= (gsinfo.g_nInitCards);
		(gsinfo.g_pPlayerNCard)[i] = (gsinfo.g_nInitCards);
		//printf("Player %d\n", i + 1);
		//DrawCards(g_ppPlayers[i], (gsinfo.g_nInitCards));
		sprintf(g_szLog, "Player %d\n", i + 1);
		UpdateLog();
		FDrawCards((gsinfo.g_ppPlayers)[i], (gsinfo.g_nInitCards));
	}

	pTmp = (StCard*)malloc((gsinfo.g_nStockPile)*sizeof(StCard));
	memcpy(pTmp, (gsinfo.g_pDecks) + (gsinfo.g_nPlayers) * (gsinfo.g_nInitCards), ((gsinfo.g_nStockPile)) * sizeof(StCard));
	free((gsinfo.g_pDecks));
	(gsinfo.g_pDecks) = pTmp;
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

int RunGame(int iStartUser)
{
	int iCurrenPlayer = iStartUser;
	int iRound = 0;
	int i = 0;
	int iPass = 0;
	
	for (iRound = 0; iRound < (gsinfo.g_nRounds); iRound++)
	{
		StCard* pTmp = NULPTR;
		StCard lastCard = (gsinfo.g_pDecks)[0];
		int iChoice = -1;
		(gsinfo.g_nAttacks) = 0;
		gsinfo.g_nDir = 0;
		(gsinfo.g_nStockPile) -= 1;
		pTmp = (StCard*)malloc(sizeof(StCard) * (gsinfo.g_nStockPile));
		memcpy(pTmp, (gsinfo.g_pDecks) + 1, sizeof(StCard) * (gsinfo.g_nStockPile));
		free((gsinfo.g_pDecks));
		(gsinfo.g_pDecks) = pTmp;
		
		if (lastCard.m_ucRank == 2)
			(gsinfo.g_nAttacks) += 2;
		else if (lastCard.m_ucRank == 3)
			(gsinfo.g_nAttacks) += 3;
		else if (lastCard.m_ucRank == 7)
			(gsinfo.g_nAttacks) = 0;
		else if (lastCard.m_ucRank == 12)
			gsinfo.g_nDir = !(gsinfo.g_nDir);

		while (1)
		{
			//clear the screen
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
			system("cls");	
#else 
			system("clear");
#endif
		
			//printing the cards
			if (DeadStatus(lastCard))
			{
				printf("No suitable cards...game over, calculating scores for each player...\n");
				CalcScore();
				for (i = 0; i < (gsinfo.g_nPlayers); i++)
				{
					printf("Player %d has %d card(s) remained, score=%d\n", i + 1, (gsinfo.g_pPlayerNCard)[i], (gsinfo.g_pScore)[i]);
				}
				break;
			}

			printf("------player %d's turn, round %d------\n", iCurrenPlayer + 1, iRound);
			for (i = 0; i < (gsinfo.g_nPlayers); i++)
				printf("Player %d has %d card(s)\n", i + 1, (gsinfo.g_pPlayerNCard)[i]);
			printf("Current Attack:%d\n", (gsinfo.g_nAttacks));
			printf("Last card:");
			DrawCards(&lastCard, 1);
			printf("\n");
			printf("Player %d cards:", iCurrenPlayer + 1);
			DrawCards((gsinfo.g_ppPlayers)[iCurrenPlayer], (gsinfo.g_pPlayerNCard)[iCurrenPlayer]);
			
			iPass = 0;
			do
			{
				printf("Input 1~%d to play a card or 0 to pass the turn.\n", (gsinfo.g_pPlayerNCard)[iCurrenPlayer]);
				if (!(gsinfo.g_iAuto))
				{
					scanf("%d", &iChoice);
				}
				else
				{
					int iRet = FindFirstAvailableCard((gsinfo.g_ppPlayers)[iCurrenPlayer], (gsinfo.g_pPlayerNCard)[iCurrenPlayer], lastCard);
					if (iRet < 0)
						iChoice = 0;
					else
						iChoice = iRet + 1;
					printf("%d was chosen\n", iChoice);
					Delay(AUTO_DELAY);
				}

				if (iChoice < 0 || iChoice > (gsinfo.g_pPlayerNCard)[iCurrenPlayer])
				{
					printf("Invailid input, press anykey to continue...");
					continue;
				}
				else if (iChoice > 0)
				{
					int iRealChoice = iChoice - 1;
					if ((gsinfo.g_ppPlayers)[iCurrenPlayer][iRealChoice].m_eSuit != lastCard.m_eSuit &&
						(gsinfo.g_ppPlayers)[iCurrenPlayer][iRealChoice].m_ucRank != lastCard.m_ucRank)
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
					if ((gsinfo.g_nAttacks))
					{
						int iCnt = 0;
						iNextPlayer = (iCurrenPlayer + 1) % (gsinfo.g_nPlayers);
						pTmp = malloc(sizeof(StCard) * ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] + (gsinfo.g_nAttacks)));
						for (i = 0; i < (gsinfo.g_pPlayerNCard)[iCurrenPlayer]; i++)
							pTmp[iCnt++] = (gsinfo.g_ppPlayers)[iCurrenPlayer][i];
						for (i = 0; i < (gsinfo.g_nAttacks); i++)
						{
							if ((gsinfo.g_nStockPile) > 1)
							{
								StCard* pTmp2 = NULPTR;
								pTmp[iCnt++] = (gsinfo.g_pDecks)[0];
								pTmp2 = malloc(sizeof(StCard) * ((gsinfo.g_nStockPile) - 1));
								memcpy(pTmp2, (gsinfo.g_pDecks) + 1, sizeof(StCard) * ((gsinfo.g_nStockPile) - 1));
								(gsinfo.g_nStockPile)--;
								free((gsinfo.g_pDecks));
								(gsinfo.g_pDecks) = pTmp2;
							}
							else if ((gsinfo.g_nStockPile) == 1)
							{
								pTmp[iCnt++] = (gsinfo.g_pDecks)[0];
								free((gsinfo.g_pDecks));
								(gsinfo.g_pDecks) = (gsinfo.g_pDiscarded);
								(gsinfo.g_nStockPile) = (gsinfo.g_nDiscardedPile);
								(gsinfo.g_nDiscardedPile) = 0;
								(gsinfo.g_pDiscarded) = NULPTR;
								Shuffle((gsinfo.g_pDecks), (gsinfo.g_nStockPile), (gsinfo.g_nStockPile) * 50);
							}
						}
						free( (gsinfo.g_ppPlayers)[iCurrenPlayer]);
						(gsinfo.g_ppPlayers)[iCurrenPlayer] = pTmp;
						(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] + (gsinfo.g_nAttacks);
						(gsinfo.g_nAttacks) = 0;
					}
					else
					{
						iNextPlayer = (iCurrenPlayer + 1) % (gsinfo.g_nPlayers);
						iCurrenPlayer = iNextPlayer;
						continue;
					}
				}

				iRet = PlayCard(&lastCard, &((gsinfo.g_ppPlayers)[iCurrenPlayer][iRealChoice]), &(gsinfo.g_nAttacks), &iIsAttack, &iSkip, &iDirFlip, &iDefense);
				if (iRet != 0)
				{
					printf("Invailid input, neither suit nor rank matches last card, press anykey to continue...");
					continue;	
				}
			
				//last card->discard.
				pTmp = malloc(sizeof(StCard)*((gsinfo.g_nDiscardedPile) + 1));
				memcpy(pTmp, (gsinfo.g_pDiscarded), (gsinfo.g_nDiscardedPile) * sizeof(StCard));
				free((gsinfo.g_pDiscarded));
				(gsinfo.g_pDiscarded) = pTmp;
				(gsinfo.g_pDiscarded)[(gsinfo.g_nDiscardedPile)] = lastCard;
				(gsinfo.g_nDiscardedPile)++;
			
				//played card->last
				lastCard = (gsinfo.g_ppPlayers)[iCurrenPlayer][iRealChoice];
			
				sprintf(g_szLog, "Player %d played (%c %s)", iCurrenPlayer + 1, Suit2Char(lastCard.m_eSuit), Rank2Char(lastCard.m_ucRank));
				UpdateLog();

				//draw extra card?
				if ((gsinfo.g_nAttacks) > 0 && ((!iIsAttack)&&(!iSkip) && (!iDirFlip) && (!iDefense)))
				{
					//draw extra card
					int iCnt = 0;

					sprintf(g_szLog, "Player %d Draw extra card, attack", iCurrenPlayer + 1);
					UpdateLog();

					iNextPlayer = (iCurrenPlayer + 1) % (gsinfo.g_nPlayers);
					pTmp = malloc(sizeof(StCard) * ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1/**/ + (gsinfo.g_nAttacks)));
					for (i = 0; i < (gsinfo.g_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (gsinfo.g_ppPlayers)[iCurrenPlayer][i];
						}
					for (i = 0; i < (gsinfo.g_nAttacks); i++)
					{
						if ((gsinfo.g_nStockPile) > 1)
						{
							StCard* pTmp2 = NULPTR;
							pTmp[iCnt++] = (gsinfo.g_pDecks)[0];
							pTmp2 = malloc(sizeof(StCard) * ((gsinfo.g_nStockPile) - 1));
							memcpy(pTmp2, (gsinfo.g_pDecks) + 1, sizeof(StCard) * ((gsinfo.g_nStockPile) - 1));
							(gsinfo.g_nStockPile)--;
							free((gsinfo.g_pDecks));
							(gsinfo.g_pDecks) = pTmp2;
						}
						else if ((gsinfo.g_nStockPile) == 1)
						{
							pTmp[iCnt++] = (gsinfo.g_pDecks)[0];
							free((gsinfo.g_pDecks));
							(gsinfo.g_pDecks) = (gsinfo.g_pDiscarded);
							(gsinfo.g_nStockPile) = (gsinfo.g_nDiscardedPile);
							(gsinfo.g_nDiscardedPile) = 0;
							(gsinfo.g_pDiscarded) = NULPTR;
							Shuffle((gsinfo.g_pDecks), (gsinfo.g_nStockPile), (gsinfo.g_nStockPile) * 50);
						}
					}
					free( (gsinfo.g_ppPlayers)[iCurrenPlayer]);
					(gsinfo.g_ppPlayers)[iCurrenPlayer] = pTmp;
					(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1 + (gsinfo.g_nAttacks);

					(gsinfo.g_nAttacks) = 0;	// release attack
				}
				else if (iSkip)
				{
					//skip
					int iCnt = 0;
					sprintf(g_szLog, "Player %d Draw skip", iCurrenPlayer + 1);
					UpdateLog();
					if ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
						free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer);
						break;
					}

					iNextPlayer = (iCurrenPlayer + 2) % (gsinfo.g_nPlayers);
					pTmp = malloc(sizeof(StCard) * ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1));
					for (i = 0; i < (gsinfo.g_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (gsinfo.g_ppPlayers)[iCurrenPlayer][i];
						}
					free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
					(gsinfo.g_ppPlayers)[iCurrenPlayer] = pTmp;
					(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
				}
				else if (iDirFlip)
				{
					//reverse
					int iCnt = 0;
					sprintf(g_szLog, "Player %d Draw reverse", iCurrenPlayer + 1);
					UpdateLog();
					if ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
						free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer);
						break;
					}
					iNextPlayer = (iCurrenPlayer + (gsinfo.g_nPlayers) - 1) % (gsinfo.g_nPlayers);
					pTmp = malloc(sizeof(StCard) * ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1));
					for (i = 0; i < (gsinfo.g_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (gsinfo.g_ppPlayers)[iCurrenPlayer][i];
						}
					free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
					(gsinfo.g_ppPlayers)[iCurrenPlayer] = pTmp;
					(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
				}
				else
				{
					//defense
					int iCnt = 0;
					if (!iIsAttack)
						(gsinfo.g_nAttacks) = 0;
					if ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1 == 0)
					{
						(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
						free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
						WinPlayer(iCurrenPlayer);
						break;
					}
					iNextPlayer = (iCurrenPlayer + 1) % (gsinfo.g_nPlayers);
					pTmp = malloc(sizeof(StCard) * ((gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1));
					for (i = 0; i < (gsinfo.g_pPlayerNCard)[iCurrenPlayer]; i++)
						if (i != iRealChoice)
						{
							pTmp[iCnt++] = (gsinfo.g_ppPlayers)[iCurrenPlayer][i];
						}
					free((gsinfo.g_ppPlayers)[iCurrenPlayer]);
					(gsinfo.g_ppPlayers)[iCurrenPlayer] = pTmp;
					(gsinfo.g_pPlayerNCard)[iCurrenPlayer] = (gsinfo.g_pPlayerNCard)[iCurrenPlayer] - 1;
				}

				iCurrenPlayer = iNextPlayer;
				
				//update dir and next
				if ((gsinfo.g_iAuto))
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

int WinPlayer(int iPlayer)
{
	int i = 0;
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif
	CalcScore();
	printf("Player %d won the game.\n", iPlayer + 1);
	sprintf(g_szLog, "Player %d won the game.\n", iPlayer + 1);
	UpdateLog();
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
	{
		printf("Player %d has %d card(s) remained, score=%d\n", i + 1, (gsinfo.g_pPlayerNCard)[i], (gsinfo.g_pScore)[i]);

		sprintf(g_szLog, "Player %d has %d card(s) remained, score=%d\n", i + 1, (gsinfo.g_pPlayerNCard)[i], (gsinfo.g_pScore)[i]);
		UpdateLog();
	}
	Delay(AUTO_DELAY * 5);

	return iPlayer;
}

int DeadStatus(StCard lastCard)
{
	int i = 0, j = 0;
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
	{
		for (j = 0; j < (gsinfo.g_pPlayerNCard)[i]; j++)
		{
			if ((gsinfo.g_ppPlayers)[i][j].m_eSuit == lastCard.m_eSuit ||
				(gsinfo.g_ppPlayers)[i][j].m_ucRank == lastCard.m_ucRank)
				return 0;
		}
	}

	return 1;
}

void CalcScore()
{
	int i = 0;
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
		(gsinfo.g_pScore)[i] -= (gsinfo.g_pPlayerNCard)[i];
}

void ReleaseDecks(StCard** ppDecks)
{
	if(ppDecks != NULPTR && (*ppDecks) != NULPTR)
		free(*ppDecks);
}

void ReleasePlayers()
{
	int i = 0;
	for (i = 0; i < (gsinfo.g_nPlayers); i++)
		free((gsinfo.g_ppPlayers)[i]);
	
	free((gsinfo.g_ppPlayers));
}

