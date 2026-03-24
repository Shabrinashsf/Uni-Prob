#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int b;
    cin >> b;

    for (int r = 1; r <= b; r++)
    {
        int s;
        cin >> s;

        int curr_sum = 0;
        int curr_start = 1;
        int best_sum = INT_MIN;
        int best_start = 1;
        int best_end = 1;

        for (int i = 1; i <= s - 1; i++)
        {
            int n;
            cin >> n;

            curr_sum = curr_sum + n;

            if (curr_sum > best_sum)
            {
                best_sum = curr_sum;
                best_start = curr_start;
                best_end = i + 1;
            }
            else if (curr_sum == best_sum)
            {
                int curr_len = (i + 1) - curr_start;
                int best_len = best_end - best_start;

                if (curr_len > best_len)
                {
                    best_sum = curr_sum;
                    best_start = curr_start;
                    best_end = i + 1;
                }
                else if (curr_len == best_len && curr_start < best_start)
                {
                    best_sum = curr_sum;
                    best_start = curr_start;
                    best_end = i + 1;
                }
            }

            if (curr_sum < 0)
            {
                curr_sum = 0;
                curr_start = i + 1;
            }
        }

        if (best_sum <= 0)
        {
            cout << "Route " << r << " has no nice parts" << "\n";
        }
        else
        {
            cout << "The nicest part of route " << r << " is between stops " << best_start << " and " << best_end << "\n";
        }
    }

    return 0;
}