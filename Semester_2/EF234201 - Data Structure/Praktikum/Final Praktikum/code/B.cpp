#include <bits/stdc++.h>
using namespace std;

long long getMaxArea(vector<long long> &h, vector<long long> &w)
{
    int n = h.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + w[i];

    stack<int> s;
    long long res = 0;

    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && h[s.top()] >= h[i])
        {
            int tp = s.top();
            s.pop();

            int left = s.empty() ? 0 : s.top() + 1;
            int right = i - 1;

            long long totalWidth = prefix[right + 1] - prefix[left];
            res = max(res, h[tp] * totalWidth);
        }
        s.push(i);
    }

    while (!s.empty())
    {
        int tp = s.top();
        s.pop();

        int left = s.empty() ? 0 : s.top() + 1;
        int right = n - 1;

        long long totalWidth = prefix[right + 1] - prefix[left];
        res = max(res, h[tp] * totalWidth);
    }

    return res;
}

int main()
{
    int n;
    cin >> n;

    vector<long long> h(n), w(n);
    for (int i = 0; i < n; ++i)
        cin >> h[i];
    for (int i = 0; i < n; ++i)
        cin >> w[i];

    cout << getMaxArea(h, w) << endl;
    return 0;
}

/*
3
24 58 16
1 1 1

58
*/