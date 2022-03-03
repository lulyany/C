#ifndef __LOG_H__
#define __LOG_H__
#include "Defs.h"
extern char g_szLog[1024];
void UpdateLog();
void PrintCards(StCard* pCards, int nCards);
void FDrawCards(StCard* pCards, int nCards);
#endif