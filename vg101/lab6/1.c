#include <stdio.h>
int main(){
    int ra,rb;double k;
    printf("input:ra,rb,k\n");
    scanf("%d%d%lf",&ra,&rb,&k);
    //srand((unsigned int) time(NULL));
    printf("the winning rate of the match equals:%lf\n",(ra+k)/(ra+rb+k));
    return 0;
}

/*
int rand_int(int lb, int ub){
    printf("%d\n", rand() % 50);
}
*/