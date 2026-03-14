#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int id;
    char name[31];
    int kode;
    int timestamp;
    struct node *next;
} node;

void insert_at_end(node **head, int id, char name[31], int kode, int *timestamp)
{
    node *new = malloc(sizeof(node));
    new->id = id;
    strcpy(new->name, name);
    new->kode = kode;
    new->timestamp = (*timestamp)++;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new;
}

void delete_highest_priority(node **head)
{
    if (*head == NULL)
    {
        printf("List kosong!\n");
        return;
    }

    node *curr = *head;
    node *prev = NULL;

    node *min_node = curr;
    node *min_prev = NULL;

    while (curr != NULL)
    {
        if (curr->kode < min_node->kode || (curr->kode == min_node->kode && curr->timestamp < min_node->timestamp))
        {
            min_node = curr;
            min_prev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    if (min_prev == NULL)
    {
        *head = min_node->next;
    }
    else
    {
        min_prev->next = min_node->next;
    }

    printf("Laporan diproses:\n");
    printf("ID: %d\n", min_node->id);
    printf("Name: %s\n", min_node->name);
    printf("Kode: %d\n", min_node->kode);
    printf("Timestamp: %d\n", min_node->timestamp);
    free(min_node);
}

void print_data(node *head)
{
    if (head == NULL)
    {
        printf("List kosong!\n");
        return;
    }

    node *trav = head;
    printf("Daftar laporan dalam list:\n");
    while (trav != NULL)
    {
        printf("ID: %d\n", trav->id);
        printf("Name: %s\n", trav->name);
        printf("Kode: %d\n", trav->kode);
        printf("Timestamp: %d\n", trav->timestamp);
        printf("------------------------\n");
        trav = trav->next;
    }
}

int main()
{
    node *head = NULL;
    int id, kode;
    int timestamp = 0;
    char name[31];

    while (1)
    {
        int input;
        printf("\nPilih menu:\n");
        printf("1. Tambah laporan baru\n");
        printf("2. Proses laporan (hapus dari list dan tampilkan datanya)\n");
        printf("3. Tampilkan semua laporan dalam antrean\n");
        printf("4. Keluar dari program\n");
        printf("Masukkan nomor menu: ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            printf("ID: ");
            scanf("%d", &id);
            printf("Name: ");
            scanf("%s", name);
            printf("Kode (1-5): ");
            scanf("%d", &kode);
            insert_at_end(&head, id, name, kode, &timestamp);
            break;

        case 2:
            delete_highest_priority(&head);
            break;

        case 3:
            print_data(head);
            break;

        case 4:
            printf("Keluar dari program...\n");
            exit(0);

        default:
            printf("Pilihan tidak valid!\n");
            break;
        }
    }
}
