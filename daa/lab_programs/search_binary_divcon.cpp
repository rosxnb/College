#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl, std::vector;

// time complexity: O(log(n))
// space complexity: O(log(n))
int search_binary(const vector<int>& list, const int target, int left, int right)
{
    if (left > right)
        return -1;

    int mid = (left + right) / 2;
    
    if (list[mid] == target)
        return mid;

    if (list[mid] > target)
        return search_binary(list, target, left, mid-1);

    return search_binary(list, target, mid+1, right);
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
        cout << "Element is found at index: " << search_binary(list, target, 0, list.size()-1) << endl;
    }

    return 0;
}
