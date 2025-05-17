#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

typedef struct
{
    int arr[MAX_SIZE];
    int top;
} Stack;

typedef struct
{
    Stack stack1;
    Stack stack2;
} Queue;

void init_stack(Stack *s)
{
    s->top = -1;
}

void push(Stack *s, int value)
{
    if (s->top == MAX_SIZE - 1)
    {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

int pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int is_empty(Stack *s)
{
    return s->top == -1;
}

void init_queue(Queue *q)
{
    init_stack(&(q->stack1));
    init_stack(&(q->stack2));
}

void enqueue(Queue *q, int value)
{
    push(&(q->stack1), value);
}

int dequeue(Queue *q)
{
    if (is_empty(&(q->stack2)))
    {
        while (!is_empty(&(q->stack1)))
        {
            push(&(q->stack2), pop(&(q->stack1)));
        }
    }

    if (is_empty(&(q->stack2)))
    {
        printf("Queue is empty!\n");
        return -1;
    }

    return pop(&(q->stack2));
}

void print_queue(Queue *q)
{
    if (!is_empty(&(q->stack2)))
    {
        for (int i = q->stack2.top; i >= 0; i--)
        {
            printf("%d ", q->stack2.arr[i]);
        }
    }

    if (!is_empty(&(q->stack1)))
    {
        for (int i = 0; i <= q->stack1.top; i++)
        {
            printf("%d ", q->stack1.arr[i]);
        }
    }

    printf("\n");
}

int main()
{
    Queue q;
    init_queue(&q);
    int choice;
    int value;

    while (1)
    {
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(&q, value);
            break;
        case 2:
            value = dequeue(&q);
            if (value != -1)
                printf("Dequeued: %d\n", value);
            break;
        case 3:
            print_queue(&q);
            break;
        case 4:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
