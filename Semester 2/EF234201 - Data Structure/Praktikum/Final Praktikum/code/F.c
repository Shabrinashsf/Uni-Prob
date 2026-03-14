/**
 * Implementasi ADT Stack (Stack menggunakan Linked List)
 *
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 *
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct stackNode_t
{
    int data;
    struct stackNode_t *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t
{
    StackNode *_top;
    unsigned _size;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack)
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack)
{
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode)
    {
        stack->_size++;
        newNode->data = value;

        if (stack_isEmpty(stack))
            newNode->next = NULL;
        else
            newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack)
{
    if (!stack_isEmpty(stack))
    {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int stack_top(Stack *stack)
{
    if (!stack_isEmpty(stack))
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack)
{
    return stack->_size;
}

int main()
{
    Stack myStack;
    stack_init(&myStack);

    char input[1001];
    fgets(input, sizeof(input), stdin);

    char *arr = strtok(input, " \n");
    while (arr != NULL)
    {
        if (strcmp(arr, "C") == 0)
        {
            stack_pop(&myStack);
        }
        else if (strcmp(arr, "D") == 0)
        {
            int top = stack_top(&myStack);
            stack_push(&myStack, 2 * top);
        }
        else if (strcmp(arr, "+") == 0)
        {
            int top1 = stack_top(&myStack);
            stack_pop(&myStack);
            int top2 = stack_top(&myStack);
            stack_push(&myStack, top1);
            stack_push(&myStack, top1 + top2);
        }
        else
        {
            stack_push(&myStack, atoi(arr));
        }
        arr = strtok(NULL, " \n");
    }

    int total = 0;
    while (!stack_isEmpty(&myStack))
    {
        total += stack_top(&myStack);
        stack_pop(&myStack);
    }

    printf("%d\n", total);
}