# README

陆衍 520370910039



## ex1 

### (1)

​	void transfer(){



}



we mainly use malloc to solve the problem 

### (2)

​	we fix a[ ], and b[ ], 

a[0] * b[0]

a[0] * b[1].....

a[1] * b[0]

### (3)

​	

### (4)

​	

### (5)

``int *fd=FILE* ``



fp=fopen("polynomial.txt","r");





### (6)

fputs(fd,result)

​	



## ex2 

### (1.a)

​	Base: numbers in 10.

### (1.b)

we first divide some intervals: 1-10, 10-99,  100-999, 1000-10000......

ABC,DEF         ***P*** :ABC         ***Q***:DEF 

first we judge and then, if can, devide  a number input by 1000, seperate it to two parts ***P*** and ***Q***, the last number of  ***P***  is the number of thousands,that is, c. Q/100 is the number of hundreds.,that is, D.

what we do is keeping doing is lowering the positions of the number until get number in 10. 



### (2)

1502 is bigger than 1000, but <10000, 1502/1000=1, it has 1 thousand remains, 502, which <1000 and  >100,502/100=5, it has 5 hundres .remains 2. That is "two"

### (3)

See ex2.c for the codes.

it's troughly the main 

```c
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
```
and we need another function

`void seperate(long n, int flag){`

`}`

to do thing recursively



## ex3 

### (1.a)

We define a a[13] [13]

from line to line, we first, list the numbers

### (1.b)

We define a a[n] [n]

from line to line, we first, list the numbers

### (2)

​	printf("please input an integer");

​	char a[];

​	a=gets(stdin);

​	



### 

