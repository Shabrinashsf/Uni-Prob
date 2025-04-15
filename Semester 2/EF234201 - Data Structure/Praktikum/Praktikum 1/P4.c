#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

int isEmpty(node *top)
{
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(node **top, int data)
{
    node *new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    if (*top == NULL)
    {
        *top = new;
        return;
    }

    if (data > (*top)->data)
    {
        // push ke depan
        new->next = *top;
        *top = new;
        return;
    }

    node *temp1 = *top;
    node *temp2 = temp1->next;
    while (temp1->next != NULL && temp2->data >= data)
    {
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    new->next = temp1->next;
    temp1->next = new;
}

void pop(node **top)
{
    node *temp = *top;
    *top = temp->next;
    free(temp);
    temp = NULL;
}

int front(node *top)
{
    if (isEmpty(top))
    {
        return -1;
    }
    else
    {
        return top->data;
    }
}

int main()
{
    int n, m;
    char str[6];
    node *top = NULL;
    scanf("%d %d", &n, &m);
    while (n--)
    {
        scanf("%5s", str);
        int len = strlen(str);
        char berat[6] = "";
        for (int i = 0; i < len; i++)
        {
            int nilai = 0;
            switch (str[i])
            {
            case ')':
                nilai = 0;
                break;
            case '!':
                nilai = 1;
                break;
            case '@':
                nilai = 2;
                break;
            case '#':
                nilai = 3;
                break;
            case '$':
                nilai = 4;
                break;
            case '%':
                nilai = 5;
                break;
            case '^':
                nilai = 6;
                break;
            case '&':
                nilai = 7;
                break;
            case '*':
                nilai = 8;
                break;
            case '(':
                nilai = 9;
                break;
            }

            char digit[2];
            sprintf(digit, "%d", nilai);
            strcat(berat, digit);
        }
        int numBerat = atoi(berat);

        if (numBerat < m)
        {
            push(&top, numBerat);
            printf("\n");
        }
        else if (numBerat == m)
        {
            printf("%d ", numBerat);
            printf("\n");
            m--;
        }

        int nilaiFront = front(top);
        while (nilaiFront == m && !isEmpty(top))
        {
            printf("%d ", nilaiFront);
            printf("\n");
            pop(&top);
            m--;
            nilaiFront = front(top);
        }
    }
}