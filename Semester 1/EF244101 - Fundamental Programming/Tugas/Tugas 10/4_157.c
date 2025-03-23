#include <stdio.h>
#include <stdlib.h>

void scan_matrix(const char *input_file, int *rows, int *cols, int ***matrix)
{
    FILE *file = fopen(input_file, "r");
    if (!file)
    {
        printf("Failed to open input file.\n");
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);

    *matrix = (int **)malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++)
    {
        (*matrix)[i] = (int *)malloc(*cols * sizeof(int));
    }

    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *cols; j++)
        {
            fscanf(file, "%d", &(*matrix)[i][j]);
        }
    }

    fclose(file);
}

void write_sparse(const char *output_file, int rows, int cols, int **matrix)
{
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        printf("Failed to open output file.\n");
        exit(1);
    }

    int non_zero_count = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                non_zero_count++;
            }
        }
    }

    fprintf(file, "%d %d\n", rows, cols);
    fprintf(file, "%d\n", non_zero_count);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                fprintf(file, "%d %d %d\n", i, j, matrix[i][j]);
            }
        }
    }

    fclose(file);
}

void scan_sparse(const char *input_file, int *rows, int *cols, int *non_zero_count, int ***sparse_data)
{
    FILE *file = fopen(input_file, "r");
    if (!file)
    {
        printf("Failed to open input file.\n");
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);
    fscanf(file, "%d", non_zero_count);

    *sparse_data = (int **)malloc(*non_zero_count * sizeof(int *));
    for (int i = 0; i < *non_zero_count; i++)
    {
        (*sparse_data)[i] = (int *)malloc(3 * sizeof(int));
    }

    for (int i = 0; i < *non_zero_count; i++)
    {
        fscanf(file, "%d %d %d", &(*sparse_data)[i][0], &(*sparse_data)[i][1], &(*sparse_data)[i][2]);
    }

    fclose(file);
}

void write_matrix(const char *output_file, int rows, int cols, int **sparse_data, int non_zero_count)
{
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        printf("Failed to open output file.\n");
        exit(1);
    }

    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)calloc(cols, sizeof(int));
    }

    for (int i = 0; i < non_zero_count; i++)
    {
        int r = sparse_data[i][0];
        int c = sparse_data[i][1];
        int value = sparse_data[i][2];
        matrix[r][c] = value;
    }

    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    fclose(file);
}

int main()
{
    int choice;

    printf("\n--- Sparse Matrix Converter ---\n");
    printf("1. Konversi Matriks Tradisional ke Sparse Matrix\n");
    printf("2. Konversi Sparse Matrix ke Matriks Tradisional\n");
    printf("Input your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        const char *input_file = "traditional_matrix.txt";
        const char *output_file = "sparse_matrix.txt";

        int rows, cols;
        int **matrix;

        scan_matrix(input_file, &rows, &cols, &matrix);

        write_sparse(output_file, rows, cols, matrix);

        for (int i = 0; i < rows; i++)
        {
            free(matrix[i]);
        }
        free(matrix);

        printf("Traditional matrix has successfully convert to sparse matrix.\n");
    }
    else if (choice == 2)
    {
        const char *input_file = "sparse_matrix.txt";
        const char *output_file = "traditional_matrix.txt";

        int rows, cols, non_zero_count;
        int **sparse_data;

        scan_sparse(input_file, &rows, &cols, &non_zero_count, &sparse_data);

        write_matrix(output_file, rows, cols, sparse_data, non_zero_count);

        for (int i = 0; i < non_zero_count; i++)
        {
            free(sparse_data[i]);
        }
        free(sparse_data);

        printf("Sparse matrix has successfully convert to traditional matrix.\n");
    }
    else
    {
        printf("Your choice is not valid.\n");
    }
}
