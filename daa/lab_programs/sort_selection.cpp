#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

// finds the minimum element in each iteration
// in every subsequent iteration, the minimum element is greater or equal 
// to the last iteration's minimum element
void sort_selection(std::vector<int>& list)
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

    {
        Timer timer;
        sort_selection(list);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
