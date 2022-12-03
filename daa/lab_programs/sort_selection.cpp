#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl, std::vector;

// finds the minimum element in each iteration
// in every subsequent iteration, the minimum element is greater or equal 
// to the last iteration's minimum element
void sort_selection(vector<int>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        int min_idx = i;
        for (int j = i; j < list.size(); ++j)
            if (list[min_idx] > list[j])
                min_idx = j;

        if (min_idx != i)
            std::swap(list[i], list[min_idx]);
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
        sort_selection(list);
    }

    cout << "\nSorted elements are: \n";
    for (int el: list)
        cout << el << ' ';
    cout << endl;

    return 0;
}
