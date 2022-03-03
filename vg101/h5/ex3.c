#include "assignment.h"    //ex. 3 function: disptach work to other functions for exercise 3
//#include <string.h>

void ex3() {
    char ch[11000];char word[100];char *tmp;int i = 0;
    //printf("Input a sentence:");
    char *chp = fgets( ch, 11000, stdin );
   // printf("Input a string:");
    if(scanf("%s",word)) {
        tmp=strstr(chp,word);
    while (tmp)
    {
        i++;
        tmp=strstr(tmp+1,word);
    }
    printf("The string '%s' occurs %d times\n",word,i);
    }
}