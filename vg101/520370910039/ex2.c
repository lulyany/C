#include "assignment.h"

// ex. 2 function: disptach work to other functions for exercise 2
void ex2() {

    char unit1[100] = {
    "one","two", "three", "four", "five", "six", "seven", "eight",
    "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen"
    };
    char unit2[100] = {
    "twenty","thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninty"
    };
    char hundred[] = "hundred";
    char thousand[] = "thousand";
    void seperate(long n, int flag);
    long n, n1, n2;
    scanf("%ld", &n);//input the number
    n1 = n / 1000;
    n2 = n % 1000;
    seperate(n1, 0);
    if (n1 != 0) {
    printf("%s ", thousand);
    if (n2 != 0)
    printf(n2 >= 100 ? "" : "and ");
    }
}
void seperate(long n, int flag){

}
