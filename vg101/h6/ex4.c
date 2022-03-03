#include "assignment.h"
//#include <stdio.h>
void ex4(){
    FILE *fp1=fopen("matrices.txt","w"); 
    int A[8];
    int B[8];
    for (int i=0;i<=6;i=i+3)
        fscanf(fp1,"%d%d%d\n",&A[i],&A[i+1],&A[i+2]);
    for (int i=0;i<=6;i=i+3)
        fscanf(fp1,"%d%d%d\n",&B[i],&B[i+1],&B[i+2]);
    fclose(fp1);
    FILE *fp2=fopen("result.txt","w"); 
    for (int i=0;i<=6;i=i+3)
        fprintf(fp1,"%d %d %d\n",A[i],A[i+1],A[i+2]);
    for (int i=0;i<=6;i=i+3)
        fprintf(fp1,"%d %d %d\n",B[i],B[i+1],B[i+2]);
    fclose(fp1);
    fclose(fp2);
    return ;
}