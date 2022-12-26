/*
   generate random numbers using linear congurential method
*/

#include <iostream>
using std::cout, std::cin, std::endl;

static long m = 100;
static long a = 19;
static long c = 0;
static long seed = 63;
static long last_randnum = seed;

long randint()
{
    long res =  a * last_randnum + c;
    return last_randnum = res % m;
}

int main()
{
    size_t counts; 
    cout << "How many random numbers you want: "; cin >> counts;

    cout << "\nGenerated random numbers: \n";
    while(counts--)
        cout << randint() << endl;

    return 0;
}
