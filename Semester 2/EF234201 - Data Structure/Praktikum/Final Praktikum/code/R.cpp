#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int H, W;

int bfs(int x, int y, vector<vector<int>> &grid, vector<vector<bool>> &visited)
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    int size = 1;

    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            if (nx >= 0 && ny >= 0 && nx < H && ny < W &&
                grid[nx][ny] == 1 && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                size++;
            }
        }
    }

    return size;
}

int main()
{
    cin >> H >> W;
    vector<vector<int>> grid(H, vector<int>(W));
    vector<vector<bool>> visited(H, vector<bool>(W, false));

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            char c;
            cin >> c;
            grid[i][j] = (c == '+') ? 1 : 0;
        }
    }

    int jumlahKoloni = 0;
    int maxUkuran = 0;
    int koloniGenap = 0;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                int ukuran = bfs(i, j, grid, visited);
                jumlahKoloni++;
                maxUkuran = max(maxUkuran, ukuran);
                if (ukuran % 2 == 0)
                    koloniGenap++;
            }
        }
    }

    cout << jumlahKoloni << " " << maxUkuran << " " << koloniGenap << endl;
    return 0;
}
