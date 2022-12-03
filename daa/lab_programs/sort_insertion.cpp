#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl, std::vector;

// maintains sorted and unsorted part
// in each iteration, insert an element from unsorted section
// into the sorted section's correct position
// assumes the first element is already sorted
void sort_insertion(vector<int>& list)
{
    // this loop selects an element from unsorted part
    for (int i = 1; i < list.size(); ++i)
    {
        int selected = list[i];
        
        // this loop empties the correct position to insert the selected element in sorted section
        int j;
        for (j = i - 1; j >= 0 and selected < list[j]; --j)
            list[j+1] = list[j];

        list[j+1] = selected;
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
        sort_insertion(list);
    }

    cout << "\nSorted elements are: \n";
    for (int el: list)
        cout << el << ' ';
    cout << endl;

    return 0;
}
