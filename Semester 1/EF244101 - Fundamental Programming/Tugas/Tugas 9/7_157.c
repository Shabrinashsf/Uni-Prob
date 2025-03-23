#include <stdio.h>

typedef struct
{
    double N1;
    double N2;
    double V1;
    double I1;
} transformer_t;

void scan_transformer(transformer_t *t)
{
    printf("Enter the number for N1, N2, V1, and I1 (I in ampere and V in volt):\n");
    printf("Enter N1: ");
    scanf("%lf", &t->N1);
    printf("Enter N2: ");
    scanf("%lf", &t->N2);
    printf("Enter V1: ");
    scanf("%lf", &t->V1);
    printf("Enter I1: ");
    scanf("%lf", &t->I1);
}

double v_out(transformer_t t)
{
    if (t.N1 == 0)
    {
        printf("Error: N1 cannot be zero.\n");
        return 0;
    }
    return (double)(t.V1 * t.N2) / (double)t.N1;
}

double i_out(transformer_t t)
{
    if (t.N2 == 0)
    {
        printf("Error: N2 cannot be zero.\n");
        return 0;
    }
    return (double)(t.I1 * t.N1) / (double)t.N2;
}

void set_n1_for_v2(transformer_t *t, double v2)
{
    if (v2 == 0)
    {
        printf("Error: V2 cannot be zero.\n");
        return;
    }
    t->N1 = (double)(t->V1 * t->N2) / (double)v2;
}

void set_v1_for_v2(transformer_t *t, double v2)
{
    if (v2 == 0)
    {
        printf("Error: V2 cannot be zero.\n");
        return;
    }
    t->V1 = (double)(t->N1 * v2) / (double)t->N2;
}

void set_n2_for_v2(transformer_t *t, double v2)
{
    if (v2 == 0)
    {
        printf("Error: V2 cannot be zero.\n");
        return;
    }
    t->N2 = (double)(t->N1 * v2) / (double)t->V1;
}

void set_n2_for_i2(transformer_t *t, double i2)
{
    if (i2 == 0)
    {
        printf("Error: I2 cannot be zero.\n");
        return;
    }
    t->N2 = (double)(t->N1 * t->I1) / (double)i2;
}

void print_transformer(transformer_t t)
{
    printf("Transformator:\n");
    printf("N1: %.0lf\n", t.N1);
    printf("N2: %.0lf\n", t.N2);
    printf("V1: %.2lf V\n", t.V1);
    printf("I1: %.2lf A\n", t.I1);
    printf("V2: %.2lf V\n", v_out(t));
    printf("I2: %.2lf A\n", i_out(t));
    printf("\n");
}

int main()
{
    transformer_t transformer;
    scan_transformer(&transformer);
    printf("\nInitial Transformer Configuration:\n");
    print_transformer(transformer);

    double v2_target, i2_target;
    printf("Enter V2 target: ");
    scanf("%lf", &v2_target);
    printf("Enter I2 target: ");
    scanf("%lf", &i2_target);

    printf("\nAfter setting N1 to produce V2 = %.2lf:\n", v2_target);
    set_n1_for_v2(&transformer, v2_target);
    print_transformer(transformer);

    printf("After setting V1 to produce V2 = %.2lf:\n", v2_target);
    set_v1_for_v2(&transformer, v2_target);
    print_transformer(transformer);

    printf("After setting N2 to produce V2 = %.2lf:\n", v2_target);
    set_n2_for_v2(&transformer, v2_target);
    print_transformer(transformer);

    printf("After setting N2 to produce I2 = %.2lf:\n", i2_target);
    set_n2_for_i2(&transformer, i2_target);
    print_transformer(transformer);
}
