#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *next;
} node;

// (a, i, u, e, o, A, I, U, E, O) akan disimpan dua kali di stack sebelum dibalik

void push(char data, node **top)
{
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->next = *top;
    *top = temp;
}

char pop(node **head)
{
    node *temp = *head;
    char x = temp->data;
    *head = temp->next;
    free(temp);
    return x;
}

void printNode(node **head)
{
    node *temp = *head;
    while (temp != NULL)
    {
        printf("%c", temp->data);
        temp = temp->next;
    }
}

void reverse(node **head, node **rev)
{
    char temp;
    node *trav = *head;
    while (trav != NULL)
    {
        temp = pop(&trav);
        push(temp, rev);
        trav = trav->next;
    }
}

int main()
{
    node *top = NULL;
    node *rev = NULL;
    char huruf[101];
    scanf("%s", huruf);
    int len = strlen(huruf);

    for (int i = 0; i < len; i++)
    {
        push(huruf[i], &top);
        if (huruf[i] == 'a' || huruf[i] == 'A' || huruf[i] == 'i' || huruf[i] == 'I' || huruf[i] == 'u' || huruf[i] == 'U' || huruf[i] == 'e' || huruf[i] == 'E' || huruf[i] == 'o' || huruf[i] == 'O')
        {
            push(huruf[i], &top);
        }
    }

    printNode(&top);
}