#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void insert_at_end(node **head, int data)
{
    node *new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;
}

void rev(node **head)
{
    node *current = *head;

    while (current != NULL && current->next != NULL)
    {
        int temp = current->data;
        current->data = current->next->data;
        current->next->data = temp;

        current = current->next->next;
    }
}

void printNode(node **head)
{
    node *temp = *head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main()
{
    int n, temp;
    node *head = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        insert_at_end(&head, temp);
    }

    rev(&head);
    printNode(&head);
}
