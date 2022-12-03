#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl, std::vector;

int search_sequential(const std::vector<int>& list, int target)
{
    // returns index of searched element if present else return -1
    for (int i = 1; i < list.size(); ++i)
        if (list[i] == target)
            return i;

    return -1;
}

int main()
{
    size_t n;
    cin >> n;

    vector<int> list(n);
    for (int& el: list)
        cin >> el;

    cout << "Enter elemenet to be searched: ";
    int target;
    cin >> target;

    {
        Timer timer;
        cout << "Element is at index: " << search_sequential(list, target) << endl;
    }

    return 0;
}
