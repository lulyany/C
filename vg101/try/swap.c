#include <stdio.h>
int swap(int a,int b);
int main(){
    int a; int b;
    scanf(" %d %d",&a, &b);
    //int c ;
    int c=swap(a,b);
    printf("%d",c);
    return 0;   
}
int swap(int a,int b){
    int c;
    c=a; a=b; b=c;
    return c;
}