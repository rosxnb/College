#include <iostream>
#include "Timer.hpp"

using std::cout;
using std::cin;
using std::endl;

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

// Time complexity: O(log(min(a,b)))
// Space complexity: O(1)
int iterative_gcd(int a, int b)
{
    int rem {};
    while(a % b)
    {
        rem = a % b;
        a = b;
        b = rem;
    }
    return b;
}

int main()
{
    int a, b;
    cin >> a >> b;

    cout << "GCD of " << a << " and " << b << " is: \n";
    cout << std::string(30, '-') << "\n";

    cout << "Iterative GCD: ";
    {
        Timer timer;
        cout << iterative_gcd(a, b) << "\n";
    }
    cout << std::string(30, '-') << "\n";

    cout << "Recursive GCD: ";
    {
        Timer timer;
        cout << recursive_gcd(a, b) << "\n";
    }
    cout << std::string(30, '-') << "\n";

    return 0;
}
