#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
} node;

void create_circle(node **head, int child)
{
    node *temp = NULL;
    node *prev = NULL;

    for (int i = 1; i <= child; i++)
    {
        temp = malloc(sizeof(node));
        temp->num = i;
        temp->next = NULL;

        if (*head == NULL)
        {
            *head = temp;
        }
        else
        {
            prev->next = temp;
        }
        prev = temp;
    }

    prev->next = *head;
}

int get_winner(node *head, int m)
{
    node *current = head;
    node *prev = NULL;

    while (current != current->next)
    {
        for (int count = 1; count < m; count++)
        {
            prev = current;
            current = current->next;
        }

        printf("Eliminating child: %d\n", current->num);
        prev->next = current->next;
        free(current);
        current = prev->next;
    }

    return current->num;
}

int main()
{
    int child, words;
    node *head = NULL;
    printf("Enter the number of child: ");
    scanf("%d", &child);
    printf("Enter the number of words: ");
    scanf("%d", &words);

    create_circle(&head, child);
    int winner = get_winner(head, words);
    printf("The last remaining child is: %d\n", winner);
    return 0;
}