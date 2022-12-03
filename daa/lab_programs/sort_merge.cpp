#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Timer.hpp"

// iteratively moves the smallest leftmost item from both array to the result array
void merge(std::vector<int>& list, int left, const int middle, int right, std::vector<int>& storage)
{
    for (int i = left, j = middle + 1; left <= right; ++left)
    {
        bool use_right = i > middle or (j <= right and (storage[j] < storage[i]));
        list[left] = storage[(use_right ? j : i)++];
    }
}

// time complexity: O(n*log(n))
// space complexity: O(n) + O(log(n)) = O(n)
// recursive call and merge assumes that for a range [left,right] the items are in the temporary storage array, 
// so that the original [left,right] slice is overwritten with the sorted result
void sort_merge(std::vector<int>& list, int left, int right, std::vector<int>& storage)
{
    if (left >= right)
        return;

    int middle = (left + right) / 2;
    sort_merge(storage, left, middle, list);
    sort_merge(storage, middle + 1, right, list);
    merge(list, left, middle, right, storage);
}

std::ostream& operator<< (std::ostream &out, std::vector<int> const &v)
{
    for (int el: v)
        out << el << ' ';
    return out;
}

int main(int argc, char** argv)
{
    int N = argv[1] ? atoi(argv[1]) : 10;
    
    // generate random elements
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int32_t> distributor(-90, 900);
    auto rand_int = std::bind(distributor, generator);
    std::vector<int> list(N);
    for (int& el: list)
        el = rand_int();
    std::cout << "Auto generated vector: \n" << list << std::endl;

    // begin merge sort
    std::vector<int> storage(list);
    {
        Timer timer;
        sort_merge(list, 0, N-1, storage);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
