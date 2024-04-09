#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct number
{
    char *str;
    int size;
};

struct division
{
    struct number *quotient;
    struct number *remainder;
};

int max(int a,int b)
{
    return a>b?a:b;
}

void printstr(struct number *num)
{
    printf("%s",num->str);
    printf("\n");
    return; 
}

void trim(struct number *num)
{
    int i = 0;
    int j = 0;
    while(i<num->size && num->str[i]=='0')
    {
        i++;
    }
    if(num->size-i == 0)
    {
        free(num->str);
        num->size = 1;
        num->str = (char*)malloc(2*sizeof(char));
        num->str[0] = '0';
        num->str[1] = '\0';
        return;
    }
    char *temp = (char*)malloc((num->size-i+1)*sizeof(char));
    for(;j<num->size-i;j++)
    {
        temp[j] = num->str[i+j];
    }
    temp[j] = '\0';
    free(num->str);
    num->str = temp;
    num->size = num->size-i;
    return;
}

bool greaterstr(struct number *num1,struct number *num2)
{
    trim(num1);
    trim(num2);
    if(num1->size!=num2->size)
    return num1->size>num2->size;
    for(int i=0;i<num1->size;i++)
    {
        if(num1->str[i]!=num2->str[i])
        return num1->str[i]>num2->str[i];
    }
    return false;
}

bool equalto(struct number *num1,struct number *num2)
{
    trim(num1);
    trim(num2);
    if(num1->size!=num2->size)
    return false;
    for(int i=0;i<num1->size;i++)
    {
        if(num1->str[i]!=num2->str[i])
        return false;
    }
    return true;
}

struct number* takeinput()
{
    struct number *num = (struct number*)malloc(sizeof(struct number));
    printf("Enter the number of digits\n");
    scanf("%d",&num->size);
    num->str = (char*)malloc((num->size+1)*sizeof(char));
    printf("Enter the number without space\n");
    for(int i=0;i<num->size;i++)
    {
        scanf(" %c",&num->str[i]);
    }
    num->str[num->size] = '\0';
    trim(num);
    return num;
}

struct number* addition(struct number *num1,struct number *num2)
{
    struct number *add = (struct number*)malloc(sizeof(struct number));
    add->size = max(num1->size,num2->size)+1;
    add->str = (char*)malloc(add->size*sizeof(char));
    int i = num1->size-1;
    int j = num2->size-1;
    int k = add->size-1;
    int sum = 0;
    int carry = 0;
    while(i>=0 && j>=0)
    {
        sum = (num1->str[i]-'0')+(num2->str[j]-'0')+carry;
        carry = sum/10;
        add->str[k] = sum%10 + '0';
        i--;
        j--;
        k--;
    }
    while(i>=0)
    {
        sum = (num1->str[i]-'0')+carry;
        carry = sum/10;
        add->str[k] = sum%10 + '0';
        i--;
        k--;
    }
    while(j>=0)
    {
        sum = (num2->str[j]-'0')+carry;
        carry = sum/10;
        add->str[k] = sum%10 + '0';
        j--;
        k--;
    }
    while(k>=0)
    {
        add->str[k] = carry + '0';
        carry = 0;
        k--;
    }
    trim(add);
    return add;
}

struct number* subtraction(struct number *num1,struct number *num2)
{
    struct number *sub = (struct number*)malloc(sizeof(struct number));
    if(greaterstr(num2,num1))
    {
        printf("Cannot Subtract\n");
        sub->size = 0;
        sub->str = NULL;
        return sub;
    }
    sub->size = max(num1->size,num2->size);
    sub->str = (char*)malloc(sub->size*sizeof(char));
    int i = num1->size-1;
    int j = num2->size-1;
    int k = sub->size-1;
    int borrow = 0;
    while(i>=0 && j>=0)
    {
        int diff = ((num1->str[i]-'0')-borrow)-(num2->str[j]-'0');
        if(diff<0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        borrow = 0;
        sub->str[k] = diff + '0';
        i--;
        j--;
        k--;
    }
    while(i>=0)
    {
        sub->str[k] = ((num1->str[i]-'0') - borrow) + '0';
        borrow = 0;
        i--;
        k--;
    }
    trim(sub);
    return sub;
}

struct number* multiplication(struct number *num1,struct number *num2)
{
    struct number *mul = (struct number*)malloc(sizeof(struct number));
    mul->size = num1->size+num2->size;
    mul->str = (char*)malloc(mul->size*sizeof(char));
    for(int x=0;x<mul->size;x++)
    {
        mul->str[x] = '0';
    }
    for(int j=num2->size-1;j>=0;j--)
    {
        int i = num1->size-1;
        int k=num1->size+j;
        int carry1 = 0;
        int carry2 = 0;
        for(;i>=0;k--)
        {
            int mult = ((num1->str[i]-'0')*(num2->str[j]-'0'))+carry1;
            carry1 = mult/10;
            mul->str[k] = ((mult%10)+carry2+(mul->str[k]-'0'))+'0';
            carry2 = (mul->str[k]-'0')/10;
            mul->str[k] = ((mul->str[k]-'0')%10) + '0';
            i--;
        }
        while(carry1 || carry2)
        {
            mul->str[k] = ((mul->str[k]-'0')+carry2+carry1)+'0';
            carry2 = (mul->str[k]-'0')/10;
            mul->str[k] = ((mul->str[k]-'0')%10) + '0';
            carry1 /= 10;
            k--;
        }
    }
    trim(mul);
    return mul;
}

struct division* division(struct number *num1,struct number *num2)
{
    struct division *div = (struct division*)malloc(sizeof(struct division));
    div->quotient = (struct number*)malloc(sizeof(struct number));
    div->quotient->size = 1;
    div->quotient->str = (char*)malloc(sizeof(char));
    div->quotient->str[0] = '0';
    div->remainder = num1;
    struct number *qadd = (struct number*)malloc(sizeof(struct number));
    qadd->size = 1;
    qadd->str = (char*)malloc(sizeof(char));
    qadd->str[0] = '1';
    while(greaterstr(div->remainder,num2) || equalto(div->remainder,num2))
    {
        div->quotient = addition(div->quotient,qadd);
        div->remainder = subtraction(div->remainder,num2);
    }
    trim(div->quotient);
    trim(div->remainder);
    return div;
}

int main()
{
    printf("Enter the details of first number\n");
    struct number *num1 = takeinput();
    printf("Enter the details of second number\n");
    struct number *num2 = takeinput();
    struct number *add = addition(num1,num2);
    struct number *sub = subtraction(num1,num2);
    struct number *mul = multiplication(num1,num2);
    struct division *div = division(num1,num2);
    printf("First Number:   ");printstr(num1);
    printf("Second Number:  ");printstr(num2);
    printf("Addition:       ");printstr(add);
    printf("Subtraction:    ");printstr(sub);
    printf("Multiplication: ");printstr(mul);
    printf("Quotient:       ");printstr(div->quotient);
    printf("Remainder:      ");printstr(div->remainder);
    return 0;
}