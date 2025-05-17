#include <stdio.h>
#define MAX 101

typedef struct
{
    int head;
    int tail;
    int data[MAX];
} QUEUE;

void init(QUEUE *q)
{
    q->head = -1;
    q->tail = -1;
}

// headnya gak akan pindah pindah kalau push, yang pindah adalah tail, tapi kalau mau pop headnya yang gerak
int isEmpty(QUEUE *q)
{
    return q->head == -1;
}

int isFull(QUEUE *q)
{
    return q->tail == MAX - 1;
}

void printQueue(QUEUE *q)
{
    if (isEmpty(q))
    {
        printf("Data is empty\n");
        return;
    }

    int i = q->head;
    while (1)
    {
        printf("%d ", q->data[i]);
        if (i == q->tail)
        {
            break;
        }
        i = (i + 1) % MAX;
    }
}

void push(QUEUE *q, int data)
{
    if (!isFull(q))
    {
        if (isEmpty(q))
        {
            q->head = q->tail = 0;
        }
        else
        {
            q->tail = (q->tail + 1) % MAX;
        }
        q->data[q->tail] = data;
    }
    else
    {
        printf("Queue is full\n");
    }
}

int pop(QUEUE *q)
{
    if (!isEmpty(q))
    {
        int value = q->data[q->head];
        if (q->head == q->tail)
        {
            q->head = -1;
            q->tail = -1;
        }
        else
        {
            q->head = (q->head + 1) % MAX;
        }
        return value;
    }
    printf("Queue is empty\n");
    return -1;
}

void findAndReplace(QUEUE *q, int findValue, int replaceValue)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }

    int i = q->head;
    int found = 0;
    while (1)
    {
        if (q->data[i] == findValue)
        {
            q->data[i] = replaceValue;
            found = 1;
        }
        if (i == q->tail)
            break;
        i = (i + 1) % MAX;
    }

    if (found)
    {
        printf("Element %d replaced with %d\n", findValue, replaceValue);
    }
    else
    {
        printf("Element %d not found in queue\n", findValue);
    }
}

int getTotal(QUEUE *q)
{
    if (isEmpty(q))
        return 0;

    int total = 0;
    int i = q->head;
    while (1)
    {
        total += q->data[i];
        if (i == q->tail)
            break;
        i = (i + 1) % MAX;
    }
    return total;
}

float getAverage(QUEUE *q)
{
    if (isEmpty(q))
        return 0;

    int total = getTotal(q);
    int count = 0;
    int i = q->head;
    while (1)
    {
        count++;
        if (i == q->tail)
            break;
        i = (i + 1) % MAX;
    }
    return (float)total / count;
}

int getMax(QUEUE *q)
{
    if (isEmpty(q))
        return -1;

    int maxVal = q->data[q->head];
    int i = q->head;
    while (1)
    {
        if (q->data[i] > maxVal)
            maxVal = q->data[i];
        if (i == q->tail)
            break;
        i = (i + 1) % MAX;
    }
    return maxVal;
}

int getMin(QUEUE *q)
{
    if (isEmpty(q))
        return -1;

    int minVal = q->data[q->head];
    int i = q->head;
    while (1)
    {
        if (q->data[i] < minVal)
            minVal = q->data[i];
        if (i == q->tail)
            break;
        i = (i + 1) % MAX;
    }
    return minVal;
}

int main()
{
    QUEUE q;
    init(&q);
    int choice;
    int value;
    int replaceValue;
    while (1)
    {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Find and replace\n");
        printf("4. Statistic\n");
        printf("5. Close program\n");
        printf("What do you want to do: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter value to be push: ");
            scanf("%d", &value);
            push(&q, value);
        }
        else if (choice == 2)
        {
            printf("%d deleted from Queue\n", pop(&q));
        }
        else if (choice == 3)
        {
            printf("Enter number you want to find: ");
            scanf("%d", &value);
            printf("Change with: ");
            scanf("%d", &replaceValue);
            findAndReplace(&q, value, replaceValue);
        }
        else if (choice == 4)
        {
            printf("Total value of queue: %d\n", getTotal(&q));
            printf("Avarage value of queue: %.2f\n", getAverage(&q));
            printf("Max value of queue: %d\n", getMax(&q));
            printf("Min value of queue: %d\n", getMin(&q));
        }
        else if (choice == 5)
        {
            printf("Exiting program...\n");
            break;
        }
        else
        {
            printf("Invalid choice\n");
        }
        printQueue(&q);
        printf("\n");
    }
}
