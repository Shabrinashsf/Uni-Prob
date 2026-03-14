#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    map<string, int> inventory;

    for (int i = 0; i < n; i++)
    {
        string cmd, fruit;
        int quantity;
        cin >> cmd >> fruit >> quantity;

        if (cmd == "ADD")
        {
            inventory[fruit] += quantity;
        }
        else if (cmd == "SELL")
        {
            if (inventory.count(fruit) == 0)
            {
                cout << "item not found" << endl;
            }
            else if (inventory[fruit] < quantity)
            {
                cout << "not enough stock" << endl;
            }
            else
            {
                inventory[fruit] -= quantity;
                cout << "SUCCESS" << endl;
            }
        }
    }

    return 0;
}

/*
Sample Input 0
9
ADD mango 20
ADD rambutan 15
SELL mango 5
SELL durian 1
ADD mango 10
SELL rambutan 20
SELL mango 25
ADD salak 30
SELL mango 1
Sample Output 0
SUCCESS
item not found
not enough stock
SUCCESS
not enough stock
*/
