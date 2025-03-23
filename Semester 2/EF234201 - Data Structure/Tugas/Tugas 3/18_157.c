#include <stdio.h>
#include <stdlib.h>

#define MAX 101

typedef struct
{
    int top;
    int data[MAX];
} Stack;

void init(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX - 1;
}

void push(Stack *s, int value)
{
    if (!isFull(s))
    {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->data[(s->top)--];
    }
    return -1; // Stack kosong
}

int peek(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->data[s->top];
    }
    return -1;
}

void printStack(Stack *s)
{
    printf("Stack: ");
    for (int i = s->top; i >= 0; i--)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void sortStack(Stack *s1)
{
    Stack s2;
    init(&s2);

    while (!isEmpty(s1))
    {
        int temp = pop(s1);

        while (!isEmpty(&s2) && peek(&s2) > temp)
        {
            push(s1, pop(&s2));
        }

        push(&s2, temp);
    }

    while (!isEmpty(&s2))
    {
        push(s1, pop(&s2));
    }
}

int main()
{
    Stack s1;
    init(&s1);
    int choice;
    int data;

    while (1)
    {
        printf("Select 1 for push, 2 for sorting, and 3 to close program: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter data to be push: ");
            scanf("%d", &data);
            push(&s1, data);
        }
        else if (choice == 2)
        {
            printf("Before sorting:\n");
            printStack(&s1);

            sortStack(&s1);

            printf("After sorting:\n");
            printStack(&s1);
        }
        else if (choice == 3)
        {
            printf("Exiting program...\n");
            break;
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
}
