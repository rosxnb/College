#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Timer.hpp"

class CompleteBinaryTree
{
    std::vector<int> bucket;

    int left_child(int idx)
    { return idx * 2 + 1; }
    
    int right_child(int idx)
    { return idx * 2 + 2; }

    int parent(int idx)
    { return (idx - 1) / 2; }
    
    bool has_smaller_child(int idx)
    {
        int right = right_child(idx);
        int left = left_child(idx);
        int N = bucket.size();
        if (right >= N or left >= N) return false;
        return bucket[idx] > bucket[right] or bucket[idx] > bucket[left];
    }

    int smaller_child_idx(int idx)
    {
        int right = right_child(idx);
        int left = left_child(idx);
        return bucket[right] < bucket[left] ? right : left;
    }

public:
    void push(int num)
    {
        bucket.push_back(num);
        int cur_pos = bucket.size() - 1;

        // up-heapifying
        while (cur_pos > 0 and bucket[cur_pos] < bucket[parent(cur_pos)])
        {
            std::swap(bucket[cur_pos], bucket[parent(cur_pos)]);
            cur_pos = parent(cur_pos);
        }
    }

    int pop()
    {
        int ret_val = bucket.front();
        std::swap(bucket[0], bucket[bucket.size() - 1]);
        bucket.pop_back();

        int push_down_idx = 0;
        while (has_smaller_child(push_down_idx))
        {
            int idx = smaller_child_idx(push_down_idx);
            std::swap(bucket[push_down_idx], bucket[idx]);
            push_down_idx = idx;
        }

        return ret_val;
    }
};

void sort_heap(std::vector<int>& list)
{
    CompleteBinaryTree heap;
    for (int el: list)
        heap.push(el);

    for (int& el: list)
        el = heap.pop();
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
        sort_heap(list);
    }
    std::cout << "\nSorted vector: \n" << list << std::endl;

    return 0;
}
