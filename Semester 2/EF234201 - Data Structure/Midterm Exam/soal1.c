#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *next;
    int x;
    int y;
} node;

void push(char data, node **top, int x, int y)
{
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->x = x;
    temp->y = y;
    temp->next = *top;
    *top = temp;
}

char pop(node **head)
{
    if (*head == NULL)
        return '\0';
    node *temp = *head;
    char x = temp->data;
    *head = temp->next;
    free(temp);
    return x;
}

void sum_node(node *head)
{
    int finalX = 0;
    int finalY = 0;
    while (head != NULL)
    {
        finalX += head->x;
        finalY += head->y;
        head = head->next;
    }
    printf("Posisi akhir robot: (%d, %d)\n", finalX, finalY);
}

int main()
{
    char input[1000];
    node *top = NULL;
    char cmd;
    int len;

    scanf("%s", input);
    len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        if (input[i] == 'U')
        {
            push(cmd, &top, 0, 1);
        }
        else if (input[i] == 'D')
        {
            push(cmd, &top, 0, -1);
        }
        else if (input[i] == 'L')
        {
            push(cmd, &top, -1, 0);
        }
        else if (input[i] == 'R')
        {
            push(cmd, &top, 1, 0);
        }
        else if (input[i] == 'B')
        {
            pop(&top);
        }
    }

    sum_node(top);
}

// UURDBBL