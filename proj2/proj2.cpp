//Oscar Banh
//October 14, 2018

#include <iostream>
using namespace std;

// function prototypes
template <class T>
T power1(T x, unsigned int n, unsigned int& mults);

template <class T>
T power2(T x, unsigned int n, unsigned int& mults);

template <class T>
T power3(T x, unsigned int n, unsigned int& mults);

template <class T>
void printReport(T base, unsigned int pow,
                 T result1, T result2, T result3,
                 unsigned int mults1, unsigned int mults2,
                 unsigned int mults3);

int main()
{
    unsigned int mults1, mults2, mults3;
    cout << "Test for integer base:\n";
    for (unsigned int pow = 0; pow <= 32; pow++) {
        unsigned int base = 2;
        unsigned int result1 = power1(base, pow, mults1);
        unsigned int result2 = power2(base, pow, mults2);
        unsigned int result3 = power3(base, pow, mults3);
        printReport(base, pow, result1, result2, result3, mults1, mults2, mults3);
    }
    cout << "\nTest for floating-point base:\n";
    for (unsigned int pow = 0; pow <= 64; pow++) {
        double base = 0.5;
        double result1 = power1(base, pow, mults1);
        double result2 = power2(base, pow, mults2);
        double result3 = power3(base, pow, mults3);
        printReport(base, pow, result1, result2, result3, mults1, mults2, mults3);
    }
    return 0;
}

//Iterative function to compute a power <em>x<sup>n</sup></em>.
template <class T>
T power1(T x, unsigned int n, unsigned int& mults)
{
    mults = 0;
    T product = 1;

    for (int i = 0; i < n; i++)
    {
        product *= x;
        mults++;
    }

    return product;
}

//naive tail recursion
template <class T>
T power2(T x, unsigned int n, unsigned int& mults)
{
    mults = 0;
    T product;

    if (n == 0)
        return 1;
    else if (n == 1)
        return x;
    else
    {
        product = x*power2(x, n-1, mults);
        mults++;
    }
    return product;
}

//divide and conquer
template <class T>
T power3(T x, unsigned int n, unsigned int& mults)
{
    mults = 0;
    T product;

    if (n == 0)
        return 1;
    else if (n == 1)
        return x;
    else if (n >= 2 && n % 2 == 0)
    {
        product = power3(x, n/2, mults);
        mults++;
        return product * product;
    }
    else
    {
        product = power3(x, (n-1)/2, mults);
        mults+=2;
        return product * product * x;
    }
}

//Report the results of three different exponentiation calculations.
template <class T>
void printReport(T base, unsigned int pow,
                 T result1, T result2, T result3,
                 unsigned int mults1, unsigned int mults2,
                 unsigned int mults3)
{
   cout << base << "^" << pow << " = ";
   if (result1 == result2 && result2 == result3)
      cout << result1 << ": ";
   else
      cout << "(" << result1 << ", " << result2 << ", " << result3
           << ") [ERROR!]: ";
   cout << "mults1 = " << mults1 << ", mults2 = " << mults2
        << ", mults3 = " << mults3 << endl;
}
