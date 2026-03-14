#include <stdio.h>
#define MAX 7
// acc
int jalan_oren(int matrix[MAX][MAX], int visited[MAX][MAX], int startX, int startY, int n, int m)
{
    if (matrix[startX][startY] == 1)
    {
        return 1;
    }

    int totalPaths = 0;
    visited[startX][startY] = 1;

    int sumbuX[4] = {-1, 1, 0, 0};
    int sumbuY[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int batasX = startX + sumbuX[i];
        int batasY = startY + sumbuY[i];

        if (batasX >= 0 && batasX < n && batasY >= 0 && batasY < m && matrix[batasX][batasY] % 2 == 1 && !visited[batasX][batasY])
        {
            totalPaths += jalan_oren(matrix, visited, batasX, batasY, n, m);
        }
    }

    visited[startX][startY] = 0;
    return totalPaths;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int matrix[MAX][MAX];
    int visited[MAX][MAX] = {0};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int startX = -1, startY = -1;
    for (int i = 0; i < n && startX == -1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    if (startX == -1 || startY == -1)
    {
        printf("Kucing oren tidak bisa pulang ke rumah :(\n");
        return 0;
    }

    int totalPaths = jalan_oren(matrix, visited, startX, startY, n, m);

    if (totalPaths == 0)
    {
        printf("Kucing oren tidak bisa pulang ke rumah :(\n");
    }
    else
    {
        printf("Terdapat %d jalan untuk kucing oren pulang\n", totalPaths);
    }
}
