#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct dnode_t
{
    int data;
    struct dnode_t
        *next,
        *prev;
} DListNode;

/* Struktur ADT Deque */
/* Implementasi didasarkan pada Doubly-Linked List */

typedef struct deque_t
{
    DListNode
        *_head,
        *_tail;
    unsigned _size;
} Deque;

/* DAFTAR FUNGSI YANG TERSEDIA */

DListNode *__dlist_createNode(int value);
void deq_init(Deque *deque);
bool deq_isEmpty(Deque *deque);
void deq_pushFront(Deque *deque, int value);
void deq_pushBack(Deque *deque, int value);
int deq_front(Deque *deque);
int deq_back(Deque *deque);
void deq_popFront(Deque *deque);
void deq_popBack(Deque *deque);

/* Definisi Fungsi */

DListNode *__dlist_createNode(int value)
{
    DListNode *newNode =
        (DListNode *)malloc(sizeof(DListNode));

    if (!newNode)
        return NULL;
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return (DListNode *)newNode;
}

void deq_init(Deque *deque)
{
    deque->_head = deque->_tail = NULL;
    deque->_size = (unsigned)0;
}

bool deq_isEmpty(Deque *deque)
{
    return (deque->_head == NULL &&
            deque->_tail == NULL);
}

void deq_pushFront(Deque *deque, int value)
{
    DListNode *newNode = __dlist_createNode(value);
    if (newNode)
    {
        deque->_size++;
        if (deq_isEmpty(deque))
        {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
}

void deq_pushBack(Deque *deque, int value)
{
    DListNode *newNode = __dlist_createNode(value);
    if (newNode)
    {
        deque->_size++;
        if (deq_isEmpty(deque))
        {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        deque->_tail->next = newNode;
        newNode->prev = deque->_tail;
        deque->_tail = newNode;
    }
}

int deq_front(Deque *deque)
{
    if (!deq_isEmpty(deque))
    {
        return (deque->_head->data);
    }
    return 0;
}

int deq_back(Deque *deque)
{
    if (!deq_isEmpty(deque))
    {
        return (deque->_tail->data);
    }
    return 0;
}

void deq_popFront(Deque *deque)
{
    if (!deq_isEmpty(deque))
    {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail)
        {
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else
        {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_popBack(Deque *deque)
{
    if (!deq_isEmpty(deque))
    {
        DListNode *temp;
        if (deque->_head == deque->_tail)
        {
            temp = deque->_head;
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else
        {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_reverse(Deque *deque)
{
    if (deq_isEmpty(deque))
        return;

    DListNode *curr = deque->_head;
    DListNode *temp = NULL;

    while (curr != NULL)
    {
        // Tuker prev dan next
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // Lanjut ke "sebelumnya", yang sekarang jadi next
        curr = curr->prev;
    }

    // Setelah dibalik, tuker head dan tail-nya
    temp = deque->_head;
    deque->_head = deque->_tail;
    deque->_tail = temp;
}

int main(int argc, char const *argv[])
{
    Deque mydeq;
    deq_init(&mydeq);
    int t;
    char cmd[15];
    int x;
    int f;

    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "depan") == 0)
        {
            f = deq_front(&mydeq);
            if (f == 0)
            {
                printf("\n");
            }
            else
            {
                printf("%d\n", f);
                deq_popFront(&mydeq);
            }
        }
        else if (strcmp(cmd, "belakang") == 0)
        {
            f = deq_back(&mydeq);
            if (f == 0)
            {
                printf("\n");
            }
            else
            {
                printf("%d\n", f);
                deq_popBack(&mydeq);
            }
        }
        else if (strcmp(cmd, "tambahDepan") == 0)
        {
            getchar();
            scanf("%d", &x);
            deq_pushFront(&mydeq, x);
        }
        else if (strcmp(cmd, "tambahBelakang") == 0)
        {
            getchar();
            scanf("%d", &x);
            deq_pushBack(&mydeq, x);
        }
        else if (strcmp(cmd, "balik") == 0)
        {
            deq_reverse(&mydeq);
        }
    }

    return 0;
}

/*
Sample Input
14
tambahDepan 101
tambahBelakang 3
balik
depan
tambahBelakang 99
tambahDepan 23
balik
belakang
balik
depan
belakang
depan
tambahDepan 10
belakang
Sample Output
3
23
101
99
10
*/