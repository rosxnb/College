/*
   O-1 knapsack problem:
    We can take a object once only not multiple times unline 0-N knapsack.
    We have to take whole object and not the fraction of it.
    Greedy doesn't always work in this approach so we use dynamic programming.
*/

#include <iostream>
#include <cstring>
#include "Timer.hpp"

using namespace std;

int main()
{
	constexpr int size = 4, n = 5;
	int s[n + 1] {0, 1, 2, 3, 2, 2};
    int v[n + 1] {0, 8, 4, 0, 5, 3};
	int dp[size + 1];
	memset(dp, 0, sizeof(dp));

    {
        Timer timer;

        for (int i = 1; i <= n; i++)
            for (int j = size; j >= 0; j--)
                if (j - s[i] >= 0) dp[j] = max(dp[j], dp[j - s[i]] + v[i]);

        cout << "Maximum profit: " << dp[size] << endl;
    }

	return 0;
}
