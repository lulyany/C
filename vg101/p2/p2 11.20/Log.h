#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include "Defs.h"
void UpdateLog(const char* pszLogFile, const char* fmt, ...);
void FDrawCards(const char* pszLogFile, StCard* pCards, int nCards);
#endif
