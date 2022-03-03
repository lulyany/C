# README

# Project 3 (!!!important!remember to input `./onecard -h` before do anything!)

*This is P3 work:*

​				*created by 陆衍*

​				*student number:520370910039*

## How to use

### *1.How to compile*

* Mac/Linix , there are two ways,choose one of it:

1.`gcc *.c -o onecard`
2. `make`

* Windows

`gcc *.c -o onecard`

* Make

  input `make`

### 2.Before running

1.Remember to input `./onecard -h` for help.

("-h|--help               printf this help message\n");
("--log filename          write the logs in filename(default: onecard.log)\n");
("-n n|--player-number=n  n players, n must be larger than 2 (default: 4)\n");
("-c c|--initial-cards=c  deal c cards per player, c must be at least 2 (default: 5)\n");
("-d c|--decks=d          use d decks 52 cards each, d must be at least 2 (default: 2)\n");
("-r r|--rounds=r         play r rounds, r must be at least 1 (default: 1)\n");
("-a|--auto               run in demo mode\n");

### important!!!to help players start a game quicker, players by default are 4.


### *3.How to run*

1. `./onecard` or `.\onecard` 

​       depend on the environment 

###  

### Extra : some description 

1.OneCard.c: the main program. To initialize.

2.UI.c：UI for users

3.Log.c: keep logs down.

4.Defs.h: some definations.

5.Objs.c: Shuffle, InitDecks, InitPlayers, RunGame 

### 中文附录，一些重要文件的说明

1. OneCard.c: 程序入口点，main函数，从这里启动开始运行。
	主要执行了 	a.用户命令行参数的解析
			b.初始化牌堆
			c.洗牌
			d.初始化玩家信息
			e.首轮发额外的牌来确定初始的玩牌顺序DealingOrderCards
			f.初始发牌
			g.RunGame开始运行游戏主体逻辑
2. UI.c：
  这个模块主要实现了和用户交互界面相关的功能：
  花色转为表达的字符串 Suit2Char
  点数转为表达的字符串 Rank2Char
  手中的牌的排序Sort，牌的展示需要按照花色顺序
  在界面上绘制扑克牌DrawCards
3. Log.c:
  主要是记录日志的功能函数
4. Defs.h: 
  包含了数据类型的定义和常量的定义。其中最重要的是StCard结构体，这个是关于扑克牌的定义，包括花色和点数。
5. Objs.c：
  游戏主体过程的函数定义在这里面。比较重要的包括Shuffle洗牌，InitDecks初始化牌堆（创建牌）， InitPlayers初始化 玩家信息，RunGame游戏运行。

