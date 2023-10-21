// C++ program to find largest x such that p*x divides n! 
#include <iostream>
using namespace std; 

// Returns largest power of p that divides n! 
int largestPower(int n, int p) 
{ 
    // Initialize result 
    int x = 0; 

    // Calculate x = n/p + n/(p^2) + n/(p^3) + .... 
    while (n) 
    { 
        n /= p; 
        x += n; 
    } 
    return x; 
} 

// Driver code 
int main() 
{ 
    int n = 10, p = 3; 
    cout << "The largest power of prime "<< p <<
            " that divides " << n << "! is "<< 
            largestPower(n, p) << endl; 
    return 0; 
} 

//Given an integer n and a prime number p, find the largest x 
///such that p^x (p raised to power x) divides n! (factorial) 
