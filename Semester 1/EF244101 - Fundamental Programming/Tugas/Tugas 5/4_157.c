#include <stdio.h>
#include <string.h>

void get_problem(int *input)
{
    printf("Select the form that you would like to convert to slope-intercept form:\n");
    printf("1) Two-point form (you know two points on the line)\n");
    printf("2) Point-slope form (you know the line's slope and one point)\n");
    printf("Select either 1 or 2:\n");
    scanf("%d", input);
}

void get2_pt(double *a1, double *b1, double *a2, double *b2)
{
    printf("Enter the x-y coordinates of the first point separated by a space:\n");
    scanf("%lf %lf", a1, b1);
    printf("Enter the x-y coordinates of the second point separated by a space:\n");
    scanf("%lf %lf", a2, b2);
}

void get_pt_slope(double *slope, double *a1, double *b1)
{
    printf("Enter the slope:\n");
    scanf("%lf", slope);
    printf("Enter the x-y coordinates of the point separated by a space:\n");
    scanf("%lf %lf", a1, b1);
}

void slope_intcpt_from2_pt(double *slope, double *yIntercept, double *a1, double *b1, double *a2, double *b2)
{
    *slope = (*b2 - *b1) / (*a2 - *a1);
    *yIntercept = -(*slope * *a1) + *b1;
}

void intcpt_from_pt_slope(double *yIntercept, double *slope, double *a1, double *b1)
{
    *yIntercept = -(*slope * *a1) + *b1;
}

void display2_pt(double *slope, double *yIntercept, double *a1, double *b1, double *a2, double *b2)
{
    printf("Two-point form\n");
    printf("%3c (%.2lf - %.2lf)\n", ' ', *b2, *b1);
    printf("m = --------------\n");
    printf("%3c (%.2lf - %.2lf)\n", ' ', *a2, *a1);
}

void display_pt_slope(double *yIntercept, double *slope, double *a1, double *b1)
{
    printf("Point-slope form\n");
    if (*b1 > 0 && *a1 > 0)
    {
        printf("y - %.2lf = %.2lf(x - %.2lf)\n", *b1, *slope, *a1);
    }
    else if (*b1 > 0 && *a1 < 0)
    {
        printf("y - %.2lf = %.2lf(x + %.2lf)\n", *b1, *slope, *a1);
    }
    else if (*b1 < 0 && *b1 > 0)
    {
        printf("y + %.2lf = %.2lf(x - %.2lf)\n", *b1, *slope, *a1);
    }
    else if (*b1 < 0 && *a1 < 0)
    {
        printf("y + %.2lf = %.2lf(x + %.2lf)\n", *b1, *slope, *a1);
    }
}

void display_slope_intcpt(double *slope, double *yIntercept)
{
    printf("Slope-intercept form\n");
    if (*yIntercept > 0)
    {
        printf("y = %.2lfx + %.2lf\n", *slope, *yIntercept);
    }
    else
    {
        printf("y = %.2lfx + %.2lf\n", *slope, *yIntercept);
    }
}

int main()
{
    double m, x1, y1, x2, y2, b;
    int cmd;
    int yesOrNo = 1;
    char lanjut;

    while (yesOrNo == 1)
    {
        get_problem(&cmd);

        if (cmd == 1)
        {
            get2_pt(&x1, &y1, &x2, &y2);
            printf("\n");
            slope_intcpt_from2_pt(&m, &b, &x1, &y1, &x2, &y2);
            display2_pt(&m, &b, &x1, &y1, &x2, &y2);
            printf("\n");
            display_slope_intcpt(&m, &b);
            printf("\n");
        }
        else if (cmd == 2)
        {
            get_pt_slope(&m, &x1, &y1);
            printf("\n");
            intcpt_from_pt_slope(&b, &m, &x1, &y1);
            display_pt_slope(&b, &m, &x1, &y1);
            printf("\n");
            display_slope_intcpt(&m, &b);
            printf("\n");
        }

        printf("Do another conversion (Y or N):\n");
        getchar();
        scanf("%c", &lanjut);
        if (lanjut == 'Y')
        {
            yesOrNo = 1;
        }
        else
        {
            yesOrNo = 0;
        }
    }
}
