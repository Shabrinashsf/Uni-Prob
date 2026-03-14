#include <stdio.h>
#include <string.h>
#include <math.h>
// testcase udah bener, tinggal sbmit aja supaya tau ac atau nggak
void chess_to_index(const char pos[], int row[], int col[])
{
    *row = pos[0] - 'a';
    *col = 8 - (pos[1] - '0');
}

int target_is_in_range(int queen_row, int queen_col, int target_row, int target_col)
{
    if (queen_row == target_row || queen_col == target_col)
    {
        return 1;
    }
    if (abs(queen_row - target_row) == abs(queen_col - target_col))
    {
        return 1;
    }
    return 0;
}

int is_path_clear(int queen_row, int queen_col, int king_row, int king_col, int wk_row, int wk_col, int bk_row, int bk_col, int wq_row, int wq_col, int bq_row, int bq_col)
{
    int temp_row, temp_col;
    // untuk aku supaya gak lupa: 1 == kanan or atas, -1 == kiri or bawah

    if (king_row > queen_row)
        temp_row = 1;
    else if (king_row < queen_row)
        temp_row = -1;
    else
        temp_row = 0;

    if (king_col > queen_col)
        temp_col = 1;
    else if (king_col < queen_col)
        temp_col = -1;
    else
        temp_col = 0;

    int current_row = queen_row + temp_row;
    int current_col = queen_col + temp_col;

    while (current_row != king_row || current_col != king_col)
    {
        if ((current_row == wk_row && current_col == wk_col) ||
            (current_row == bk_row && current_col == bk_col) ||
            (current_row == wq_row && current_col == wq_col) ||
            (current_row == bq_row && current_col == bq_col))
        {
            return 0;
        }

        current_row += temp_row;
        current_col += temp_col;
    }

    // bersih bang
    return 1;
}

void chessChecker(const char wk[], const char wq[], const char bk[], const char bq[], char x)
{
    int wk_row, wk_col, wq_row, wq_col, bk_row, bk_col, bq_row, bq_col;

    chess_to_index(wk, &wk_row, &wk_col);
    chess_to_index(wq, &wq_row, &wq_col);
    chess_to_index(bk, &bk_row, &bk_col);
    chess_to_index(bq, &bq_row, &bq_col);

    if (x == 'w')
    {
        if (target_is_in_range(wq_row, wq_col, bk_row, bk_col) && is_path_clear(wq_row, wq_col, bk_row, bk_col, wk_row, wk_col, bk_row, bk_col, wq_row, wq_col, bq_row, bq_col))
        {
            printf("White checked Black!\n");
            return;
        }
    }
    else if (x == 'b')
    {
        if (target_is_in_range(bq_row, bq_col, wk_row, wk_col) && is_path_clear(bq_row, bq_col, wk_row, wk_col, wk_row, wk_col, bk_row, bk_col, wq_row, wq_col, bq_row, bq_col))
        {
            printf("Black checked White!\n");
            return;
        }
    }

    printf("Game is still going!\n");
}

int main()
{
    char wk[3], wq[3], bk[3], bq[3], x;
    scanf("%s %s ", wk, wq);
    scanf("%s %s ", bk, bq);
    scanf("%c", &x);
    chessChecker(wk, wq, bk, bq, x);
    return 0;
}