#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main () {
    //int a=123;
    //int b=a;
    //printf("%d\n%p\n",a,&a);
    //srand(time(NULL));float a=rand();
    //double b = (double ) a;
    //printf("%f\n",a);
    int a[10];a[0]=18;a[1]=19;a[2]=20;int *x=a;int *y=&a;
    printf(" %p\n %d\n %p\n %p\n %d\n",a[2],*x,x,a,*(x+2)); 
} 