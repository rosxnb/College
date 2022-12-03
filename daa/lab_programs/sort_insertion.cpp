#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

// maintains sorted and unsorted part
// in each iteration, insert an element from unsorted section
// into the sorted section's correct position
// assumes the first element is already sorted
void sort_insertion(std::vector<int>& list)
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
    {
        Timer timer;
        sort_insertion(list);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
