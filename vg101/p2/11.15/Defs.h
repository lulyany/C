#ifndef __DEFS_H__
#define __DEFS_H__
//#define _WINOS_
#define  _UNIX_

#define NULPTR ((void*)(0))

#define CMD_HELP		"-h"
#define CMD_HELP_		"-help"
#define CMD_NPLAYER		"-n"
#define CMD_NPLAYER_	"--player-number="
#define CMD_INITCARD	"-c"
#define CMD_INITCARD_	"--initial-cards="
#define CMD_DECKS		"-d"
#define CMD_DECKS_		"--decks="
#define CMD_ROUND		"-r"
#define CMD_ROUND_		"--rounds="
#define CMD_DEMO		"-a"
#define CMD_DEMO_		"--auto"

#define DECKSIZE 52
#define ALLRANKS 13
#define MINRANK  2

typedef enum 
{
	Spades,
	Hearts,
	Diamonds,
	Clubs
}
Suit;

typedef struct  
{
	Suit m_eSuit;
	unsigned char m_ucRank;
}
StCard;

#endif
