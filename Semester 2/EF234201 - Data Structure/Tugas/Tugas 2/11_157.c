#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char huruf;
    struct node *next;
} node;

void push_back(node **head, char huruf)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Failed to alocate memmory\n");
        exit(1);
    }

    new->huruf = huruf;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
}

void anagram(node **head_a, node **head_b, int size_a, int size_b)
{
    int count = 0;
    node *temp_a = *head_a;
    while (temp_a != NULL)
    {
        node *temp_b = *head_b;
        int found = 0;
        while (temp_b != NULL)
        {
            if (temp_a->huruf == temp_b->huruf && temp_b->huruf != ' ')
            {
                count++;
                temp_b->huruf = ' ';
                found = 1;
                break;
            }
            temp_b = temp_b->next;
        }
        if (!found)
        {
            break;
        }
        temp_a = temp_a->next;
    }

    if (count == size_a)
    {
        printf("THIS IS AN ANAGRAM!\n");
    }
    else
    {
        printf("NOT AN ANAGRAM!\n");
    }
}

void print_node(node **head)
{
    node *temp = *head;
    while (temp != NULL)
    {
        printf("%c", temp->huruf);
        temp = temp->next;
    }
}

void main()
{
    char a[100];
    char b[100];
    int size_a;
    int size_b;

    node *head_a = NULL;
    node *head_b = NULL;

    printf("Enter first word: ");
    scanf("%s", a);
    printf("Enter second word: ");
    scanf("%s", b);

    size_a = strlen(a);
    size_b = strlen(b);

    if (size_a != size_b)
    {
        printf("NOT AN ANAGRAM!\n");
        return;
    }

    for (int i = 0; i < size_a; i++)
    {
        push_back(&head_a, a[i]);
        push_back(&head_b, b[i]);
    }
    anagram(&head_a, &head_b, size_a, size_b);
}