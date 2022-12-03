#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

// in each iteration, the largest element will get bubbled up (placed at last)
// first loop indicates how many element/s has been sorted
// starts by comparing very first two elements in every iteration
void sort_bubble(std::vector<int>& list)
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

    // begin bubble sort
    {
        Timer timer;
        sort_bubble(list);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
