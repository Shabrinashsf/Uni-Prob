#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t
{
    int key;
    char nama[31];
    bool hidup;
    int warisan;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t
{
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode *__bst__createNode(int value, char *nama, int warisan, bool hidup)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = value;
    strncpy(newNode->nama, nama, 30);
    newNode->nama[30] = '\0';
    newNode->warisan = warisan;
    newNode->hidup = hidup;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *__bst__insert(BSTNode *root, int value, char *nama, int warisan, bool hidup)
{
    if (root == NULL)
        return __bst__createNode(value, nama, warisan, hidup);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, nama, warisan, hidup);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, nama, warisan, hidup);

    return root;
}

BSTNode *__bst__search(BSTNode *root, int value)
{
    while (root != NULL)
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode *__bst__findMinNode(BSTNode *node)
{
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;

    return currNode;
}

BSTNode *__bst__remove(BSTNode *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value > root->key)
        root->right = __bst__remove(root->right, value);
    else if (value < root->key)
        root->left = __bst__remove(root->left, value);
    else
    {
        if (root->left == NULL)
        {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL)
        {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key = temp->key;
        root->right = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root)
{
    if (root)
    {
        __bst__inorder(root->left);
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void bst_init(BST *bst)
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst)
{
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value)
{
    BSTNode *temp = __bst__search(bst->_root, value);
    return temp != NULL && temp->key == value;
}

void bst_insert(BST *bst, int value, char *nama, int warisan, bool hidup)
{
    if (!bst_find(bst, value))
    {
        bst->_root = __bst__insert(bst->_root, value, nama, warisan, hidup);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value)
{
    if (bst_find(bst, value))
    {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

void bst_inorder(BST *bst)
{
    __bst__inorder(bst->_root);
}

void proses_warisan(BSTNode *node, int total_warisan);

void distribusi_warisan(BSTNode *anak, int jumlah)
{
    if (anak == NULL)
        return;

    if (anak->hidup)
    {
        anak->warisan += jumlah;
        printf("ID %d Telah Menerima Warisan Sebesar %d, Harta Warisannya Sekarang: %d\n", anak->key, jumlah, anak->warisan);
    }
    else
    {
        proses_warisan(anak, jumlah); // rekursif lagi kalau anaknya udah meninggal
    }
}

void proses_warisan(BSTNode *node, int total_warisan)
{
    if (node == NULL)
        return;

    int kiri = 0, kanan = 0;

    if ((node->left && !node->right) || (!node->left && node->right))
    {
        kiri = total_warisan;
        kanan = total_warisan;
    }
    else if (node->left && node->right)
    {
        kiri = (int)(0.6 * total_warisan);
        kanan = (int)(0.4 * total_warisan);
    }

    distribusi_warisan(node->left, kiri);
    distribusi_warisan(node->right, kanan);
}

int main()
{
    BST tree;
    bst_init(&tree);

    int input = -1;
    int id, warisan, search;
    char nama[31];

    while (input != 4)
    {
        printf("Pilih menu:\n");
        printf("1. Menambahkan anggota baru ke dalam pohon keluarga.\n");
        printf("2. Menampilkan struktur pohon keluarga secara inorder.\n");
        printf("3. Simulasi Kematian Anggota.\n");
        printf("4. Keluar\n");
        printf("Apa Yang Ingin Anda Lakukan: ");
        scanf("%d", &input);

        if (input == 1)
        {
            printf("ID: ");
            scanf("%d", &id);
            getchar();

            printf("Nama: ");
            fgets(nama, 30, stdin);
            nama[strcspn(nama, "\n")] = 0;

            printf("Warisan: ");
            scanf("%d", &warisan);
            bst_insert(&tree, id, nama, warisan, true);

            printf("Data Berhasil Dimasukkan\n");
        }
        else if (input == 2)
        {
            if (bst_isEmpty(&tree))
            {
                printf("Pohon Kosong\n");
            }
            else
            {
                printf("Urutan ID struktur pohon menurut inorder adalah: \n");
                bst_inorder(&tree);
                printf("\n");
            }
        }
        else if (input == 3)
        {
            printf("Masukkan ID yang ingin disimulasikan meninggal: ");
            scanf("%d", &search);
            BSTNode *target = __bst__search(tree._root, search);

            if (target == NULL)
            {
                printf("ID tidak ditemukan\n");
            }
            else if (!target->hidup)
            {
                printf("Anggota keluarga sudah meninggal\n");
            }
            else
            {
                target->hidup = false;

                if (target->left == NULL && target->right == NULL)
                {
                    printf("Anggota Dengan ID Tersebut Tidak Mempunyai Ahli Waris\n");
                }
                else
                {
                    proses_warisan(target, target->warisan);
                }

                target->warisan = 0;
            }
        }
    }
}
