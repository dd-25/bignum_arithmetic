#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct array
{
    int size;
    int *arr;
};

struct division
{
    struct array *quotient;
    struct array *remainder;
};

int max(int a,int b)
{
    return a>b?a:b;
}

struct array* trim(struct array *num)
{
    int i = 0;
    int j = 0;
    while(i<num->size && num->arr[i]==0)
    i++;
    int sz = num->size-i;
    struct array *temp = (struct array*)calloc(1,sizeof(struct array));
    if(sz == 0)
    {
        temp->size = 1;
        temp->arr = (int*)calloc(1,sizeof(int));
        temp->arr[0] = 0;
        return temp;
    }
    temp->size = sz;
    temp->arr = (int*)calloc(sz,sizeof(int));
    while(i<num->size)
    {
        temp->arr[j] = num->arr[i];
        i++;
        j++;
    }
    return temp;
}

bool greaterarr(struct array *num1,struct array *num2)
{
    num1 = trim(num1);
    num2 = trim(num2);
    if(num1->size != num2->size)
    return num1->size > num2->size;
    for(int i=0;i<num1->size;i++)
    {
        if(num1->arr[i] != num2->arr[i])
        return num1->arr[i] > num2->arr[i];
    }
    return false;
}

bool equalto(struct array *num1,struct array *num2)
{
    int i = 0;
    int j = 0;
    while(i<num1->size && num1->arr[i]==0)
    i++;
    while(num2->size && num2->arr[j]==0)
    j++;
    if(num1->size-i != num2->size-j)
    return false;
    while(i<num1->size && j<num2->size)
    {
        if(num1->arr[i] != num2->arr[j])
        return false;
        i++;
        j++;
    }
    return true;
}

struct array* takeinput()
{
    printf("Enter the number of digits in number\n");
    struct array *num = (struct array*)calloc(1,sizeof(struct array)); // to handle trialing zeroes
    scanf("%d",&(num->size));
    num->arr = (int*)calloc(num->size,sizeof(int));
    printf("Enter the digits with space\n");
    for(int i=0;i<num->size;i++)
    {
        scanf("%d",&(num->arr[i]));
    }
    return trim(num);
}

void printarr(struct array* num)
{
    for(int i=0;i<num->size;i++)
    {
        printf("%d ",num->arr[i]);
    }
    printf("\n");
    return;
}

struct array* addition(struct array* num1, struct array* num2)
{
    struct array* add = (struct array*)calloc(1,sizeof(struct array));
    add->size = max(num1->size,num2->size) + 1;
    add->arr = (int*)calloc(add->size,sizeof(int));
    int i = num1->size-1;
    int j = num2->size-1;
    int k = add->size-1;
    int sum = 0;
    int carry = 0;
    while(i>=0 && j>=0)
    {
        sum = num1->arr[i]+num2->arr[j];
        add->arr[k] = sum%10 + carry;
        carry = sum/10;
        i--;
        j--;
        k--;
    }
    while(i>=0)
    {
        sum = num1->arr[i];
        add->arr[k] = sum%10 + carry;
        carry = sum/10;
        i--;
        k--;
    }
    while(j>=0)
    {
        sum = num2->arr[j];
        add->arr[k] = sum%10 + carry;
        carry = sum/10;
        j--;
        k--;
    }
    add->arr[k] = carry;
    return trim(add);
}

struct array* subtraction(struct array *num1,struct array *num2)
{
    struct array* sub = (struct array*)calloc(1,sizeof(struct array));
    sub->size = max(num1->size,num2->size);
    sub->arr = (int*)calloc(sub->size,sizeof(int));
    if(greaterarr(num2,num1))
    {
        sub->size = 0;
        free(sub->arr);
        printf("Cannot Subract\n");
        return sub;
    }
    int i = num1->size-1;
    int j = num2->size-1;
    int k = sub->size-1;
    int borrow = 0;
    while(i>=0 && j>=0)
    {
        int diff = (num1->arr[i]-borrow)-num2->arr[j];
        if(diff<0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        sub->arr[k] = diff;
        i--;
        j--;
        k--;
    }
    while(i>=0)
    {
        sub->arr[k] = num1->arr[i]-borrow;
        borrow = 0;
        i--;
        k--;
    }
    return trim(sub);
}

struct array* multiplication(struct array *num1,struct array *num2)
{
    struct array *mul = (struct array*)calloc(1,sizeof(struct array));
    mul->size = num1->size+num2->size;
    mul->arr = (int*)calloc(mul->size,sizeof(int));
    int i = num2->size-1;
    while(i>=0)
    {
        int j = num1->size-1;
        int carry1 = 0;
        int carry2 = 0;
        int k = num1->size+i;
        while(j>=0)
        {
            int mult = num1->arr[j]*num2->arr[i]+carry1;
            carry1 = mult/10;
            mul->arr[k] += mult%10 + carry2;
            carry2 = mul->arr[k]/10;
            mul->arr[k] %= 10;
            j--;
            k--;
        }
        while(carry1)
        {
            int mult = carry1;
            carry1 = mult/10;
            mul->arr[k] += mult%10 + carry2;
            carry2 = mul->arr[k]/10;
            mul->arr[k] %= 10;
        }
        if(carry2)
        mul->arr[k] = carry2;
        i--;
    }
    return trim(mul);
}

struct division* division(struct array *num1,struct array* num2)
{
    struct division *div = (struct division*)calloc(1,sizeof(struct division));
    div->quotient = (struct array*)calloc(1,sizeof(struct array));
    div->remainder = (struct array*)calloc(1,sizeof(struct array));
    div->quotient->size = 1; // for default quotient to be zero
    div->quotient->arr = (int*)calloc(1,sizeof(int));
    div->remainder = num1;
    struct array *qadd = (struct array*)calloc(1,sizeof(struct array));
    qadd->size = 1;
    qadd->arr = (int*)calloc(1,sizeof(int));
    qadd->arr[0] = 1;
    while(greaterarr(div->remainder,num2) || equalto(div->remainder,num2))
    {
        div->quotient = addition(div->quotient,qadd);
        div->remainder = subtraction(div->remainder,num2);
    }
    div->quotient = trim(div->quotient);
    div->remainder = trim(div->remainder);
    return div;
}

int main()
{
    printf("Enter the details of first number\n");
    struct array *num1 = takeinput();
    printf("Enter the details of second number\n");
    struct array *num2 = takeinput();
    struct array *add = addition(num1,num2);
    struct array *sub = subtraction(num1,num2);
    struct array *mul = multiplication(num1,num2);
    struct division *div = division(num1,num2);
    printf("First Number:   ");printarr(num1);
    printf("Second Number:  ");printarr(num2);
    printf("Addition:       ");printarr(add);
    printf("Subtraction:    ");printarr(sub);
    printf("Multiplication: ");printarr(mul);
    printf("Quotient:       ");printarr(div->quotient);
    printf("Remainder:      ");printarr(div->remainder);
    return 0;
}