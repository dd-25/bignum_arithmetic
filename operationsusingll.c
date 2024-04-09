#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
    int data;
    struct node *next;
};

struct number
{
    int size;
    struct node *head;
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

void trim(struct number *num)
{
    int i = 0;
    struct node *curr = num->head;
    while(curr!=NULL && curr->data==0)
    {
        curr = curr->next;
        i++;
    }
    num->size = num->size-i;
    if(curr==NULL)
    {
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->data = 0;
        temp->next = NULL;
        num->head = temp;
        num->size = 1;
        return;
    }
    num->head = curr;
    return;
}

bool greaterll(struct number *num1,struct number *num2)
{
    trim(num1);
    trim(num2);
    if(num1->size!=num2->size)
    return num1->size > num2->size;
    struct node *temp1 = num1->head;
    struct node *temp2 = num2->head;
    while(temp1!=NULL)
    {
        if(temp1->data!=temp2->data)
        return temp1->data > temp2->data;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return false;
}

bool equalto(struct number *num1,struct number *num2)
{
    trim(num1);
    trim(num2);
    if(num1->size != num2->size)
    return false;
    struct node *temp1 = num1->head;
    struct node *temp2 = num2->head;
    while(temp1!=NULL)
    {
        if(temp1->data!=temp2->data)
        return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

void printll(struct number *num)
{
    struct node *temp = num->head;
    for(int i=0;i<num->size;i++)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
    return;
}

void insert_begin(struct node **num,int x)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->next = *num;
    *num = temp;
    return;
}

void insert_end(struct node** num,int x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->next = NULL;
    if(*num == NULL)
    {
        *num = temp;
        return;
    }
    struct node *curr = *num;
    while(curr->next!=NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    return;
}

void reverse(struct node **num)
{
    struct node *prev = NULL;
    struct node *curr = *num;
    struct node *next = NULL;
    while(curr!=NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *num = prev;
    return;
}

struct number* takeinput()
{
    printf("Enter the number of digits\n");
    int n;
    scanf("%d",&n);
    struct node *num = NULL;
    struct number *nm = (struct number*)malloc(sizeof(struct number));
    printf("Enter the number with space\n");
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        insert_begin(&num,x);
    }
    nm->size = n;
    reverse(&num);
    nm->head = num;
    trim(nm);
    return nm;
}

struct number *addition(struct number *num1,struct number *num2)
{
    struct number *add = (struct number*)malloc(sizeof(struct number));
    add->size = 0;
    add->head = NULL;
    reverse(&num1->head);
    reverse(&num2->head);
    struct node *curr1 = num1->head;
    struct node *curr2 = num2->head;
    int sum = 0;
    int carry = 0;
    while(curr1!=NULL && curr2!=NULL)
    {
        sum = curr1->data+curr2->data+carry;
        carry = sum/10;
        insert_begin(&add->head,sum%10);
        add->size++;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while(curr1!=NULL)
    {
        sum = curr1->data+carry;
        carry = sum/10;
        insert_begin(&add->head,sum%10);
        add->size++;
        curr1 = curr1->next;
    }
    while(curr2!=NULL)
    {
        sum = curr2->data+carry;
        carry = sum/10;
        insert_begin(&add->head,sum%10);
        add->size++;
        curr2 = curr2->next;
    }
    if(carry)
    {
        insert_begin(&add->head,carry);
        add->size++;
    }
    reverse(&num1->head);
    reverse(&num2->head);
    trim(add);
    return add;
}

struct number* subtraction(struct number *num1,struct number *num2)
{
    struct number *sub = (struct number*)malloc(sizeof(struct number));
    sub->size = 0;
    sub->head = NULL;
    if(greaterll(num2,num1))
    {
        printf("Cannot Subtract\n");
        return sub;
    }
    reverse(&num1->head);
    reverse(&num2->head);
    struct node *curr1 = num1->head;
    struct node *curr2 = num2->head;
    int borrow = 0;
    while(curr2!=NULL)
    {
        int diff = (curr1->data-borrow)-curr2->data;
        if(diff<0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        borrow = 0;
        insert_begin(&sub->head,diff);
        sub->size++;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while(curr1!=NULL)
    {
        insert_begin(&sub->head,curr1->data-borrow);
        borrow = 0;
        sub->size++;
        curr1 = curr1->next;
    }
    reverse(&num1->head);
    reverse(&num2->head);
    trim(sub);
    return sub;
}

struct number* multiplication(struct number* num1,struct number* num2)
{
    struct number *mul = (struct number*)malloc(sizeof(struct number));
    mul->size = 1;
    mul->head = (struct node*)malloc(sizeof(struct node));
    mul->head->data = 0;
    mul->head->next = NULL;
    reverse(&num1->head);
    reverse(&num2->head);
    struct node *curr1 = num1->head;
    struct node *curr2 = num2->head;
    struct number *temp[num2->size];
    for(int i=0;i<num2->size;i++)
    {
        temp[i] = (struct number*)malloc(sizeof(struct number));
        temp[i]->size = 0;
        temp[i]->head = NULL;
    }
    int j = 0;
    while(curr2!=NULL)
    {
        curr1 = num1->head;
        int carry = 0;
        for(int k=0;k<j;k++)
        {
            insert_begin(&temp[j]->head,0);
            temp[j]->size++;
        }
        while(curr1!=NULL)
        {
            int mult = curr2->data*curr1->data+carry;
            carry = mult/10;
            insert_begin(&temp[j]->head,mult%10);
            temp[j]->size++;
            curr1 = curr1->next;
        }
        while(carry)
        {
            insert_begin(&temp[j]->head,carry%10);
            temp[j]->size++;
            carry /= 10;
        }
        j++;
        curr2 = curr2->next;
    }
    for(int i=0;i<num2->size;i++)
    {
        mul = addition(mul,temp[i]);
    }
    reverse(&num1->head);
    reverse(&num2->head);
    trim(mul);
    return mul;
}

struct division* division(struct number *num1,struct number *num2)
{
    struct division *div = (struct division*)malloc(sizeof(struct division));
    div->quotient = (struct number*)malloc(sizeof(struct number));
    div->remainder = (struct number*)malloc(sizeof(struct number));
    div->quotient->size = 1;
    div->quotient->head = (struct node*)malloc(sizeof(struct node));
    div->quotient->head->data = 0;
    div->quotient->head->next = NULL;
    struct number *qadd = (struct number*)malloc(sizeof(struct number));
    qadd->size = 1;
    qadd->head = (struct node*)malloc(sizeof(struct node));
    qadd->head->data = 1;
    qadd->head->next = NULL;
    struct number *temp = num1;
    while(greaterll(temp,num2) || equalto(temp,num2))
    {
        temp = subtraction(temp,num2);
        div->quotient = addition(div->quotient,qadd);
    }
    div->remainder = temp;
    trim(div->quotient);
    trim(div->remainder);
    return div;
}

int main()
{
    printf("Enter the first number\n");
    struct number *num1 = takeinput();
    printf("Enter the second number\n");
    struct number *num2 = takeinput();
    struct number *add = addition(num1,num2);
    struct number *sub = subtraction(num1,num2);
    struct number *mul = multiplication(num1,num2);
    struct division *div = division(num1,num2);
    printf("First Number:   ");printll(num1);
    printf("Second Number:  ");printll(num2);
    printf("Addition:       ");printll(add);
    printf("Subtraction:    ");printll(sub);
    printf("Multiplication: ");printll(mul);
    printf("Quotient:       ");printll(div->quotient);
    printf("Remainder:      ");printll(div->remainder);
    return 0;
}