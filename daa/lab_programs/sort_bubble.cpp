#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl, std::vector;

// in each iteration, the largest element will get bubbled up (placed at last)
// first loop indicates how many element/s has been sorted
// starts by comparing very first two elements in every iteration
void sort_bubble(vector<int>& list)
{
    bool swapped {true};
    for (int i = 0; i < list.size() - 1 and swapped; ++i)
    {
        swapped = false;
        for (int j = 0; j < list.size() - 1 - i; ++j)
            if (list[j] > list[j+1])
            {
                std::swap(list[j], list[j+1]);
                swapped = true;
            }
    }
}

int main()
{
    size_t n;
    cin >> n;

    vector<int> list(n);
    for (int& el: list)
        cin >> el;

    {
        Timer timer;
        sort_bubble(list);
    }

    cout << "\nSorted elements are: \n";
    for (int el: list)
        cout << el << ' ';
    cout << endl;

    return 0;
}
