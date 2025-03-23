#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void extract_uppercase(char *input_file, char *output_file)
{
    FILE *infile, *outfile;
    char ch;

    infile = fopen(input_file, "r");
    if (infile == NULL)
    {
        printf("Error: Could not open file %s for reading.\n", input_file);
        return;
    }

    outfile = fopen(output_file, "w");
    if (outfile == NULL)
    {
        printf("Error: Could not open file %s for writing.\n", output_file);
        fclose(infile);
        return;
    }

    while ((ch = fgetc(infile)) != EOF)
    {
        if (isupper(ch))
        {
            fputc(ch, outfile);
        }
    }

    printf("Uppercase letters extracted to %s\n", output_file);

    fclose(infile);
    fclose(outfile);
}

void print_lines_starting_with_A(char *input_file)
{
    FILE *infile;
    char line[256];

    infile = fopen(input_file, "r");
    if (infile == NULL)
    {
        printf("Error: Could not open file %s for reading.\n", input_file);
        return;
    }

    printf("Lines starting with 'A':\n");
    while (fgets(line, sizeof(line), infile) != NULL)
    {
        if (line[0] == 'A')
        {
            printf("%s", line);
        }
    }

    fclose(infile);
}

int main()
{
    char *input_file = "input.txt";
    char *output_file = "uppercase_output.txt";

    extract_uppercase(input_file, output_file);
    print_lines_starting_with_A(input_file);

    return 0;
}
