#ifndef __UI_H__
#define __UI_H__
#include "Defs.h"

#define UI_MAX_LINE_CARDS	5
#define AUTO_DELAY 1500

//convert suit to char
char Suit2Char(Suit st);

//convert rank to string
char* Rank2Char(unsigned char ucRank);

//drawing cards on the terminal
void DrawCards(StCard* pCards, int nCards);
void Delay(unsigned long msec);

//sorting cards
void Sort(StCard* pCards, int nCards);
#endif
