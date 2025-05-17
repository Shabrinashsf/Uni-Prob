#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

typedef struct
{
    int job_num[MAX_SIZE];
    int priority[MAX_SIZE];
    int size;
} PQueue;

void init(PQueue *pq)
{
    pq->size = 0;
}

void add_pqueue(PQueue *pq, int job_num, int priority)
{
    if (pq->size >= MAX_SIZE)
    {
        printf("Queue is full!\n");
        return;
    }

    // kalau arraynya gak kosong dan ada priority yang lebih tinggi maka priority yang rendah akan geser ke kanan
    int i = pq->size - 1;
    while (i >= 0 && pq->priority[i] > priority)
    {
        pq->job_num[i + 1] = pq->job_num[i];
        pq->priority[i + 1] = pq->priority[i];
        i--;
    }

    pq->job_num[i + 1] = job_num;
    pq->priority[i + 1] = priority;
    pq->size++;
}

void delete_head(PQueue *pq)
{
    if (pq->size == 0)
    {
        printf("Queue is empty!\n");
        return;
    }

    // cara ngehapusnya dia ntar ngegeser ke kiri, jadi dia bakal nimpa dan overwrite gitu
    for (int i = 0; i < pq->size - 1; i++)
    {
        pq->job_num[i] = pq->job_num[i + 1];
        pq->priority[i] = pq->priority[i + 1];
    }
    pq->size--;
}

void remove_based_jobnunm(PQueue *pq, int job_num)
{
    if (pq->size == 0)
    {
        printf("Queue is empty!\n");
        return;
    }

    int i;
    // iterasi nyari yang jobnumnya sama
    for (i = 0; i < pq->size; i++)
    {
        if (pq->job_num[i] == job_num)
        {
            break;
        }
    }

    if (i == pq->size)
    {
        printf("Job not found!\n");
        return;
    }

    // cara ngehapusnya dia ntar ngegeser ke kiri, jadi dia bakal nimpa dan overwrite gitu
    for (; i < pq->size - 1; i++)
    {
        pq->job_num[i] = pq->job_num[i + 1];
        pq->priority[i] = pq->priority[i + 1];
    }
    pq->size--;
}

void print_pqueue(PQueue *pq)
{
    for (int i = 0; i < pq->size; i++)
    {
        printf("Job %d (Priority %d)\n", pq->job_num[i], pq->priority[i]);
    }
}

int main()
{
    PQueue pq;
    init(&pq);
    int choice;
    int job_num, prior;

    while (1)
    {
        printf("1. Add data\n");
        printf("2. Delete head\n");
        printf("3. Delete x job number\n");
        printf("4. Print data\n");
        printf("5. Close program\n");
        printf("What do you want to do: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter job number: ");
            scanf("%d", &job_num);
            printf("Enter priority number (1 is the highest priosity number): ");
            scanf("%d", &prior);
            add_pqueue(&pq, job_num, prior);
        }
        else if (choice == 2)
        {
            delete_head(&pq);
            printf("Head of priority queue is deleted successfully\n");
        }
        else if (choice == 3)
        {
            printf("Enter number job number you want to delete: ");
            scanf("%d", &job_num);
            remove_based_jobnunm(&pq, job_num);
        }
        else if (choice == 4)
        {
            print_pqueue(&pq);
            ;
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
    }

    return 0;
}
