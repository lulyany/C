#ifndef __LOG_H__
#define __LOG_H__
#define LOGBUFFER char g_szLog[1024];
#include "Defs.h"
extern LOGBUFFER
void UpdateLog();
void PrintCards(StCard* pCards, int nCards);
void FDrawCards(StCard* pCards, int nCards);
LOGBUFFER
#endif