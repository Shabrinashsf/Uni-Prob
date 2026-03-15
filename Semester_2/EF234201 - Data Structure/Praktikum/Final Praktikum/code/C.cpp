#include <iostream>
#include <vector>
using namespace std;

int trap(vector<int> &height)
{
    int total = 0;
    int l = 0, r = height.size() - 1;
    int lmax = 0, rmax = height[r];

    while (l < r)
    {
        if (height[l] <= height[r])
        {
            if (height[l] < lmax)
            {
                total += lmax - height[l];
            }
            else
            {
                lmax = height[l];
            }
            l++;
        }
        else
        {
            if (height[r] < rmax)
            {
                total += rmax - height[r];
            }
            else
            {
                rmax = height[r];
            }
            r--;
        }
    }
    return total;
}

int main()
{
    int n;
    cin >> n;
    vector<int> height(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> height[i];
    }

    int total = trap(height);

    cout << total;
}
