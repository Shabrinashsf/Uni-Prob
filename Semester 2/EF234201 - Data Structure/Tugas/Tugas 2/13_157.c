#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int digit;
    struct node *next;
    struct node *prev;
} node;

void push_back(node **head, char digit)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Failed to alocate memmory\n");
        exit(1);
    }

    new->digit = digit;
    new->next = NULL;
    new->prev = NULL;

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
        new->prev = temp;
    }
}

void print_node(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->digit);
        head = head->next;
    }
}

void reverse(node **head)
{
    node *temp = NULL;
    node *current = *head;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL)
    {
        *head = temp->prev;
    }
}

void add(node *num1, node *num2, node **result)
{
    reverse(&num1);
    reverse(&num2);

    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0)
    {
        int sum = carry;
        if (num1 != NULL)
        {
            sum += num1->digit;
            num1 = num1->next;
        }
        if (num2 != NULL)
        {
            sum += num2->digit;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        push_back(result, sum);
    }
    reverse(result);
}

int main()
{
    node *head1 = NULL;
    node *head2 = NULL;

    char num1[100];
    char num2[100];
    char sum[101];
    int size1, size2;
    node *sumRes = NULL;

    printf("Enter first number: ");
    scanf("%s", num1);
    printf("Enter second number: ");
    scanf("%s", num2);

    size1 = strlen(num1);
    size2 = strlen(num2);

    for (int i = 0; i < size1; i++)
    {
        push_back(&head1, num1[i] - '0');
    }
    for (int i = 0; i < size2; i++)
    {
        push_back(&head2, num2[i] - '0');
    }

    add(head1, head2, &sumRes);

    printf("Sum: ");
    print_node(sumRes);

    return 0;
}