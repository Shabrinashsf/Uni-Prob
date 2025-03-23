#include <stdio.h>

int aman(char arr[][8], int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8 && arr[x][y] == '.');
}

int check_direction(char arr[][8], int x, int y)
{
    // Stop if we reach the destination
    if (x == 7 && y == 7)
    {
        printf("Reached destination: (%d, %d)\n", x, y);
        arr[x][y] = 'O';
        return 1; // Return success
    }

    // Mark the current cell as visited
    arr[x][y] = 'O';

    printf("Checking from (%d, %d)\n", x, y);

    // Check all four directions (up, down, left, right)
    // If we find a valid move, we continue the recursion
    if (aman(arr, x - 1, y))
    {
        if (check_direction(arr, x - 1, y))
            return 1; // If destination found, return success
    }
    if (aman(arr, x + 1, y))
    {
        if (check_direction(arr, x + 1, y))
            return 1;
    }
    if (aman(arr, x, y - 1))
    {
        if (check_direction(arr, x, y - 1))
            return 1;
    }
    if (aman(arr, x, y + 1))
    {
        if (check_direction(arr, x, y + 1))
            return 1;
    }

    // If no valid move is found, backtrack
    return 0;
}

void clear_path(char arr[][8])
{
    // Start checking from position (0, 1)
    if (aman(arr, 0, 1))
    {
        if (!check_direction(arr, 0, 1))
        {
            printf("No path exists\n");
        }
    }
}

int main()
{
    char maze[8][8];
    printf("Enter the maze of 8 x 8 block (X is a blocked path, . is a clear path):\n");
    printf("The maze will be started at position (0, 1) and will be finished at position (7,7)\n");

    // Input the maze
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf(" %c", &maze[i][j]);
        }
    }

    // Solve the maze
    clear_path(maze);

    // Output the final state of the maze
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }

    return 0;
}