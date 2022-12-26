/*
   Fractional Knapsack:
    In this knapsack, the greedy method is applicable because we are allowed to 
    take the fraction of the object and is not constrained to take the whole object.

    We first calcuate the profit/weight ratio for all the objects then choose those
    objects with high profit/weight ratio.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl;
using std::vector, std::sort;

struct Object
{
    int profit, weight;
    Object(int profit, int weight) : profit(profit), weight(weight) {}
};

bool cmp(Object a, Object b)
{
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(vector<Object>& arr, int W)
{
    sort(arr.begin(), arr.end(), cmp);

    int curWeight = 0;
    double finalprofit = 0.0;

    for (int i = 0; i < arr.size(); i++)
    {
        // if possible, add whole item
        if (curWeight + arr[i].weight <= W)
        {
            curWeight += arr[i].weight;
            finalprofit += arr[i].profit;
        }

        //  else add fractional part of it if space remains
        else
        {
            int remain = W - curWeight;
            finalprofit += arr[i].profit * ((double) remain / arr[i].weight);
            break;
        }
    }

    return finalprofit;
}

int main()
{
    int W = 69;   // Weight of knapsack
    vector<Object> arr { {39, 7}, {87, 16}, {41, 10}, {69, 6}, {135, 20}, {167, 15}, {310, 27} };

    int profit;
    {
        Timer timer;
        profit = fractionalKnapsack(arr, W); 
    }

    cout << "\nMax profit: " << profit << endl;
    return 0;
}
