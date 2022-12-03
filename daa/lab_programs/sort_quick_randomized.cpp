#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

int rand_idx(int left, int right)
{
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> dist(left, right);
    return dist(generator);
}

int partition(std::vector<int>& list, int left, int right)
{
    int p_idx = right;
    int first_high = left;

    for (int i = left; i < right; ++i)
        if (list[i] < list[p_idx])
            std::swap(list[i], list[first_high++]);
    
    std::swap(list[p_idx], list[first_high]);
    return first_high;
}

// in each iteration, picks a random index from valid range to be pivot element
int random_partition(std::vector<int>& list, int left, int right)
{
    std::swap(list[rand_idx(left, right)], list[right]);
    return partition(list, left, right);
}

// time complexity: O(n * log(n))
void sort_quick(std::vector<int>& list, int left, int right)
{
    if (left >= right) return;
    int pivot_idx = random_partition(list, left, right);
    sort_quick(list, left, pivot_idx - 1);
    sort_quick(list, pivot_idx + 1, right);
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
        sort_quick(list, 0, N-1);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
