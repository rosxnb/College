#include <algorithm>
#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl;
using std::vector, std::sort, std::min;

struct Job
{
    char id;
    int dead;
    int profit;
};

bool cmp(Job a, Job b)
{
    return a.profit > b.profit;
}

void printJobScheduling(vector<Job>& arr)
{
    sort(arr.begin(), arr.end(), cmp);

    int n = arr.size();
    vector<int> result(n); // resulting sequence of jobs
    vector<bool> slot(n, false);  // All slots are free initially

    for (int i = 0; i < n; i++)
    {
        // Find a free slot for this job starting from last possible slot
        for (int j = min(n, arr[i].dead) - 1; j >= 0; j--)
        {
            if (slot[j] == false)
            {
                result[j] = i;  // Add this job to result
                slot[j] = true; // Make this slot occupied
                break;
            }
        }
    }

    // Print job sequence and calculate total profit
    int profit = 0;
    for (int i = 0; i < n; i++)
        if (slot[i])
        {
            profit += arr[result[i]].profit;
            cout << " " << arr[result[i]].id;
        }

    cout << "\nTotal Profit: " << profit << endl;
}

int main()
{
    vector<Job> arr { {'a', 2, 20}, {'b', 2, 15}, {'c', 1, 10}, {'d', 3, 5}, {'e', 3, 1}};

    cout << "Following is maximum profit sequence of jobs\n";
    {
        Timer timer;
        printJobScheduling(arr);
    }

    return 0;
}
