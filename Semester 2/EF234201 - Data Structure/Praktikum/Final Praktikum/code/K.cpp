#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isValueUsed(map<string, vector<string>> &dataMap, string &value, string &targetKey)
{
    for (auto &pair : dataMap)
    {
        if (pair.first != targetKey)
        {
            if (find(pair.second.begin(), pair.second.end(), value) != pair.second.end())
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    map<string, vector<string>> data;
    string cmd, key, value;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> cmd;
        if (cmd == "RECRUIT")
        {
            cin >> key >> value;

            if (isValueUsed(data, value, key))
            {
                //
            }
            else
            {
                data[key].push_back(value);
            }
        }
        else if (cmd == "ALLY")
        {
            //
        }
        else if (cmd == "CHECK")
        {
            //
        }
    }
}