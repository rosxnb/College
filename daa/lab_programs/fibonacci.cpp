#include <iostream>
#include <vector>
#include "Timer.hpp"

using std::cout, std::cin, std::endl;

void fib(size_t n)
{
    std::vector<int> list(n+1);
    list[0] = 0;
    list[1] = 1;

    for (int i = 2; i <= n; ++i)
        list[i] = list[i-1] + list[i-2];

    for (int el: list)
        cout << el << ' ';
}

int main()
{
    size_t n;
    cin >> n;

    {
        Timer timer;
        fib(n);
    }

    return 0;
}
