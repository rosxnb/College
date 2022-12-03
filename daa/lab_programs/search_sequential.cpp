#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

// also known as linear search
// time complexity: O(n)
// space complexity: O(1)
int search_sequential(const std::vector<int>& list, int target)
{
    // returns index of searched element if present else return -1
    for (int i = 1; i < list.size(); ++i)
        if (list[i] == target)
            return i;

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
    std::cout << "Auto generated vector: \n" << list << std::endl;

    int target;
    std::cout << "\nEnter the element to be searched: ";
    std::cin >> target;
    {
        Timer timer;
        std::cout << "Element is found at index: " << search_sequential(list, target) << std::endl;
    }

    return 0;
}
