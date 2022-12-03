#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::endl, std::cin, std::vector;

// time complexity: O(log(n))
// space complexity: O(1)
int search_binary(const vector<int>& list, const int target)
{
    int left = 0;
    int right = list.size();

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (list[mid] == target)
            return mid;

        if (list[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main()
{
    size_t n;
    cin >> n;

    vector<int> list(n);
    for (int& el: list)
        cin >> el;

    int target;
    cout << "Enter the element to be searched: ";
    cin >> target;
    {
        Timer timer;
        cout << "Element is found at index: " << search_binary(list, target) << endl;
    }

    return 0;
}
