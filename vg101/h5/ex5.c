#include "assignment.h"
//#include <stdio.h> 
#include <string.h>
#define S "Spades"
#define H "Hearts"
#define D "Diamonds"
#define C "Club"
// ex. 5 function: disptach work to other functions for exercise 1
typedef struct cardset
{
    int rank;
    char suit[9];
} cardset;
void print_answer(int i,cardset card[]);
void main() {
    
    cardset card[52];
    for (int i=0;i<=51;i++) {
        int rem=0;
        rem=(i%4);int normal_i=(i+8);
            if (rem==0||rem==4)
            {
                card[i].rank=normal_i/4;
                strcpy(card[i].suit,S);
            }
            else if (rem==1)
            {
                card[i].rank=normal_i/4;
                strcpy(card[i].suit,H);
            }
            else if (rem==2)
            {
                card[i].rank=normal_i/4;
                strcpy(card[i].suit,D);
            }
            else if (rem==3)
            {
                card[i].rank=normal_i/4;
                strcpy(card[i].suit,C);
            }
            if (normal_i/4==11)
            {
                
 
            }
            
        print_answer(i,card); 
    }
    return 0;
}
void print_answer(int i,cardset card[]) {
    if ((i+8)/4==11)
    {
        printf("%s %s\n","Jack",card[i].suit);
    }
    else if ((i+8)/4==12)
    {
        printf("%s %s\n","Queen",card[i].suit);
    } 
    else if ((i+8)/4==13)
    {
        printf("%s %s\n","King",card[i].suit);
    }
    else if ((i+8)/4==14)
    {
        printf("%s %s\n","Ace",card[i].suit);
    }
    else 
        printf("%d %s\n",card[i].rank,card[i].suit); 
}