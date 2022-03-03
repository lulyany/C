# README

## *Project 3*

## *( important!remember to input `./onecard -h` before do anything! )*

- *This is P3 work:*

*created by 陆衍*

*student number:520370910039* 

- *Missions completed:*: m1, m2, m3

## How to use

### 1.How to compile

#### 1. Mac/Linix, open Termina, enter the directory of the peoject. Then there are two ways, choose either one of it:

- `make`

- `gcc *.c -o onecard`

#### 2. Windows

`gcc *.c -o onecard`

### 2.Before running

1.Remember to input `./onecard -h` for help.

```c
-h|--help               printf this help message\n
--log filename          write the logs in filename(default: onecard.log)\n
-n n|--player-number=n  n players, n must be larger than 2 (default: 4)\n
-c c|--initial-cards=c  deal c cards per player, c must be at least 2 (default: 5)\n
-d c|--decks=d          use d decks 52 cards each, d must be at least 2 (default: 2)\n
-r r|--rounds=r         play r rounds, r must be at least 1 (default: 1)\n
-a|--auto               run in demo mode\n
```

### *important !!!*   

### *To help players start a game quicker, players by default are 4.*


### 3.How to run

1. after compiling , `./onecard` or `.\onecard` 

​       depend on the environment 

### Extra : instructions

1.OneCard.c: the main program. To initialize the whole project.

missions  finished:

-  initialize all parameter
- process command argument
- initialize decks
- Shuffling cards
- initialize players
- dealing order cards (once only)
- start a loop for game

2.UI.c：UI for users

​			suit2char

​			rank2char

​			sort the card, show it in the order of suit

​			draw cards

3.Log.c: keep logs down.

4.Defs.h: some definations.

5.Objs.c: Shuffle, InitDecks, InitPlayers, RunGame 

