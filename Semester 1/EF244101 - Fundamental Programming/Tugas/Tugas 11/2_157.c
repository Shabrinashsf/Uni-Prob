#include <stdio.h>
#include <stdlib.h>

void merge_files(char *file1_path, const char *file2_path, char *output_file_path)
{
    FILE *file1, *file2, *output_file;
    char ch;

    file2 = fopen(file2_path, "r");
    if (file2 == NULL)
    {
        printf("Gagal membuka file %s\n", file2_path);
        return;
    }

    file1 = fopen(file1_path, "r");
    if (file1 == NULL)
    {
        printf("Gagal membuka file %s\n", file1_path);
        fclose(file2);
        return;
    }

    output_file = fopen(output_file_path, "w");
    if (output_file == NULL)
    {
        printf("Gagal membuat file output %s\n", output_file_path);
        fclose(file1);
        fclose(file2);
        return;
    }

    while ((ch = fgetc(file2)) != EOF)
    {
        fputc(ch, output_file);
    }

    fputc('\n', output_file);

    while ((ch = fgetc(file1)) != EOF)
    {
        fputc(ch, output_file);
    }

    fclose(file1);
    fclose(file2);
    fclose(output_file);

    printf("File berhasil digabung ke dalam '%s'\n", output_file_path);
}

int main()
{
    char *file1 = "file1.txt";
    char *file2 = "file2.txt";
    char *output_file = "merged_output.txt";

    merge_files(file1, file2, output_file);

    return 0;
}
