#include "assignment.h"
#define PI 3.1415926535898
typedef struct _numbers{
    double x;
    double y;
}numbers_set;

void print_answer();

void change();

 void ex2(){
    numbers_set complex_numbers[3]={{3.0, 4.0 / 5.0},
    {0.0, log(4)}, {45.245, 0.235}};
    numbers_set polar_numbers[3]={{ 3, PI / 17 }, 
    { 4, PI / 9 }, { 1, PI / 12 }};

    void change(numbers_set complex_numbers[]);
    for(int i=0;i<=2;i++){
        printf("%.5lf+%.5lfi %.5lfe%.5lfi\n",complex_numbers[i].x,complex_numbers[i].y,cos(polar_numbers[i].x),sin(polar_numbers[i].y));
    }   
    return ;
}
void change(numbers_set complex_numbers[]){
    for(int i=0;i<=2;i++){
        if (complex_numbers[i].x>1||complex_numbers[i].x<-1){
            while (complex_numbers[i].x>1||complex_numbers[i].x<-1)
                complex_numbers[i].x=2*PI-complex_numbers[i].x;
        }
        if (complex_numbers[i].y>1||complex_numbers[i].y<-1){
            while (complex_numbers[i].y>1||complex_numbers[i].y<-1)
                complex_numbers[i].y=2*PI-complex_numbers[i].y;
        }
    }
  //return complex_numbers[];
}