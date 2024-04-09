#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

struct type1
{
    int a;
    char c;
};

struct type2
{
    char c;
    int a;
};

int addi(int a,int b)
{
    int p;
    int q;
    int c;
    return a+b;
}

int* add(int a,int b)
{
    int p;
    int q;
    int r = a+b;
    int *c = &r;
    return c;
}

int main()
{
    int a=2;
    int *b=&a;
    int c[10];
    int *d[10];
    d[0] = c;
    int (*e)[10] = &c; // this doesn't create an array, rather it just creates a pointer capable of pointing to an array of defined size, here, i.e. 10
    (*e)[5] = 25;
    // printf("Value of a: %d\n",a);
    // printf("Value of integer type stored at address b: %d\n",*b);
    // printf("Address of variable a: %d\n",&a);
    // printf("Value of pointer variable b: %d\n",b);
    // printf("Next location of b: %d\n",b+1);
    // printf("Address of c: %d\n",c);
    // printf("Address of c+1: %d\n",c+1);
    // printf("Value of c: %d\n",*c);
    // printf("Value of first element of c: %d\n",c[0]);
    // printf("Address of first element of c: %d\n",&c[0]);
    // printf("Address of c[1]: %d\n",&c[1]);
    // printf("Next location of c: %d\n",c+1);
    // printf("Value of d: %d\n",d);
    // printf("Value at d: %d\n",*d);
    printf("%d\n",sizeof(*d));
    printf("%d\n",sizeof(*d[0]));
    // printf("Value of first element of d: %d\n",d[0]);
    // printf("Value of d[0][0]: %d\n",d[0][0]);
    // printf("Value of *d[0]: %d\n",*d[0]);
    // printf("Next location of d: %d\n",d+1);
    // printf("Value of second element of c: %d\n",c[1]);
    // printf("Value of d[0][1]: %d\n",d[0][1]);
    // printf("Address of e: %d\n",&e);
    printf("Value of e: %d\n",e);
    // printf("Value at e: %d\n",*e);
    // printf("Value of first element of e: %d\n",e[0]);
    printf("Next location of e: %d\n",e+1);
    printf("%d\n",**e);
    printf("%d\n",(*e)+1);
    // printf("6th value1 of e: %d\n",e[5]);
    // printf("2nd value2 of e: %d\n",(*e)[1]);
    // // printf("6th value3 of e: %d\n",*e[5]);
    // printf("Value of e[10]: %d\n",e[10]);
    // // printf("Address of e[10]: %d\n",&e[10]);
    // printf("Value of e[2]: %d\n",e[2]);
    // // printf("Value of e[0][0]: %d\n",e[0][0]);
    // printf("Size of type1: %d\n",sizeof(struct type1));
    // printf("Size of type2: %d\n",sizeof(struct type2));
    // printf("size of addi: %d\n",sizeof(addi));
    // printf("size of add: %d\n",sizeof(add));
    // printf("location of addi: %d\n",addi);
    // printf("location of add: %d\n",add);
    // printf("next location of addi: %d\n",addi+1);
    // printf("next location of add: %d\n",add+1);
    // printf("add: %d\n",*add(2,3));
    // printf("addi: %d\n",addi(2,3));
    // int (*add)(int a,int b) = addi;
    // printf("add: %d\n",add);
    // printf("add(): %d\n",add(2,3));
    // printf("%d\n",sizeof(*e));
    return 0;
}