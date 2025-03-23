#include <stdio.h>
#define MAX_STACK 101

typedef struct STACK
{
    int top;
    int data[MAX_STACK];
} STACK;

void init(STACK *s)
{
    s->top = -1;
}

int isEmpty(STACK *s)
{
    return s->top == -1;
}

int isFull(STACK *s)
{
    return s->top == MAX_STACK - 1;
}

void push(STACK *s, int data)
{
    if (isFull(s))
    {
        printf("Stack is full!\n");
        return;
    }
    s->data[++(s->top)] = data; // ntar topnya juga ikut nambah satu
}

int pop(STACK *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty, cannot pop stack!\n");
        return -1;
    }
    return s->data[s->top--];
}

void printStack(STACK *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack data: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void findAndReplace(STACK *main, STACK *temp, int target, int change)
{
    int found = 0;
    while (main->top != -1)
    {
        // peek
        if (main->data[main->top] == target)
        {
            main->data[main->top] = change;
            found = 1;
            break;
        }
        // push elemen yang di pop ke stack temp
        temp->data[++(temp->top)] = main->data[main->top--];
    }

    if (!found)
    {
        printf("Cannot find number %d\n", target);
        return;
    }

    // kembalikan stack temp ke main
    while (temp->top != -1)
    {
        main->data[++(main->top)] = temp->data[temp->top--];
    }
}

int main()
{
    STACK main;
    STACK temp;
    init(&main);
    init(&temp);
    int choice;
    int value;
    int target;
    int change;
    while (1)
    {
        printf("Select 1 for push, 2 for pop, 3 for find and replace, and 4 to close program: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter value to be push: ");
            scanf("%d", &value);
            push(&main, value);
        }
        else if (choice == 2)
        {
            pop(&main);
        }
        else if (choice == 3)
        {
            printf("Enter number you want to find: ");
            scanf("%d", &target);
            printf("Change with: ");
            scanf("%d", &change);
            findAndReplace(&main, &temp, target, change);
        }
        else if (choice == 4)
        {
            printf("Exiting program...\n");
            break;
        }
        else
        {
            printf("Invalid choice\n");
        }
        printStack(&main);
    }
}