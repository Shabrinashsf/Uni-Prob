#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0)
    {
        vector<long long> h(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> h[i];
        }

        vector<int> stack(n + 2);
        int top = 0;
        long long max_area = 0;

        for (int i = 1; i <= n + 1; i++)
        {
            long long cur_height;
            if (i == n + 1)
                cur_height = 0;
            else
                cur_height = h[i];

            while (top > 0 && h[stack[top]] >= cur_height)
            {
                long long height = h[stack[top]];
                top--;
                long long width;
                if (top == 0)
                    width = i - 1;
                else
                    width = i - stack[top] - 1;

                long long area = height * width;
                if (area > max_area)
                    max_area = area;
            }
            top++;
            stack[top] = i;
        }

        cout << max_area << "\n";
    }

    return 0;
}