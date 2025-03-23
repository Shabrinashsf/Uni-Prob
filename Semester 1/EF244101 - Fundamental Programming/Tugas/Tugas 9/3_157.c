#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct
{
    double mantissa;
    int eksponen;
} sci_not_t;

// 0.1 <= mantissa < 1.0
void normalize_sci(sci_not_t *sci)
{
    while (sci->mantissa >= 1.0)
    {
        sci->mantissa /= 10;
        sci->eksponen++;
    }
    while (sci->mantissa < 0.1 && sci->mantissa != 0)
    {
        sci->mantissa *= 10;
        sci->eksponen--;
    }
}

sci_not_t scan_sci(const char *input)
{
    sci_not_t sci = {0.0, 0};
    sscanf(input, "%lfe%d", &sci.mantissa, &sci.eksponen);
    normalize_sci(&sci);
    return sci;
}

void print_sci(const sci_not_t sci)
{
    printf("%.5fe%d", sci.mantissa, sci.eksponen);
}

sci_not_t add_sci(const sci_not_t a, const sci_not_t b)
{
    sci_not_t result;
    int diff = a.eksponen - b.eksponen;
    if (diff > 0)
    {
        result.mantissa = a.mantissa + b.mantissa / pow(10, diff);
        result.eksponen = a.eksponen;
    }
    else
    {
        result.mantissa = b.mantissa + a.mantissa / pow(10, -diff);
        result.eksponen = b.eksponen;
    }
    normalize_sci(&result);
    return result;
}

sci_not_t subtract_sci(const sci_not_t a, const sci_not_t b)
{
    sci_not_t result;
    int diff = a.eksponen - b.eksponen;
    if (diff > 0)
    {
        result.mantissa = a.mantissa - b.mantissa / pow(10, diff);
        result.eksponen = a.eksponen;
    }
    else
    {
        result.mantissa = a.mantissa / pow(10, -diff) - b.mantissa;
        result.eksponen = b.eksponen;
    }
    normalize_sci(&result);
    return result;
}

sci_not_t multiply_sci(const sci_not_t a, const sci_not_t b)
{
    sci_not_t result;
    result.mantissa = a.mantissa * b.mantissa;
    result.eksponen = a.eksponen + b.eksponen;
    normalize_sci(&result);
    return result;
}

sci_not_t divide_sci(const sci_not_t a, const sci_not_t b)
{
    sci_not_t result;
    result.mantissa = a.mantissa / b.mantissa;
    result.eksponen = a.eksponen - b.eksponen;
    normalize_sci(&result);
    return result;
}

int main()
{
    char input1[20], input2[20];
    printf("Masukkan dua angka dalam notasi ilmiah (contoh: 0.25000e3):\n");
    scanf("%s %s", input1, input2);

    sci_not_t num1 = scan_sci(input1);
    sci_not_t num2 = scan_sci(input2);

    printf("Input pertama: ");
    print_sci(num1);
    printf("\n");
    printf("Input kedua: ");
    print_sci(num2);
    printf("\n");

    sci_not_t sum = add_sci(num1, num2);
    sci_not_t diff = subtract_sci(num1, num2);
    sci_not_t prod = multiply_sci(num1, num2);
    sci_not_t quot = divide_sci(num1, num2);

    printf("Sum: ");
    print_sci(sum);
    printf("\n");

    printf("Difference: ");
    print_sci(diff);
    printf("\n");

    printf("Product: ");
    print_sci(prod);
    printf("\n");

    printf("Quotient: ");
    print_sci(quot);
    printf("\n");
}
