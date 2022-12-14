#include <iostream>
#include "Timer.hpp"

// following function uses Euclidean Algorithm to calculate GCD of two numbers recursively
// time complexity = O(log(min(a,b)))
// space complexity = O(log(min(a,b)))
int recursive_gcd(int a, int b)
{
    // if remainder = 0, last remainder is the GCD
    if (b == 0)
        return a;

    // if remainder ≠ 0, swap as followings
    // next_dividend = last_divisor
    // next_divisor = remainder of current dividend (a) and divisor (b)
    return recursive_gcd(b, a % b);
}

int main()
{
    int a, b;
    std::cin >> a >> b;

    std::cout << "GCD of " << a << " and " << b << " is: ";
    {
        Timer timer;
        std::cout << recursive_gcd(a, b) << "\n";
    }

    return 0;
}
