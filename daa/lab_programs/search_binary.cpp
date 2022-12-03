#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

// time complexity: O(log(n))
// space complexity: O(1)
int search_binary(const std::vector<int>& list, const int target)
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
    std::sort(list.begin(), list.end());
    std::cout << "Auto generated vector: \n" << list << std::endl;

    int target;
    std::cout << "\nEnter the element to be searched: ";
    std::cin >> target;
    {
        Timer timer;
        std::cout << "Element is found at index: " << search_binary(list, target) << std::endl;
    }

    return 0;
}
