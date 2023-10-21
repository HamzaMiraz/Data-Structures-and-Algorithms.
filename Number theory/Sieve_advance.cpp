#include <bits/stdc++.h>
using namespace std;

/// nlog(n)
#define SIZE_N 10010000///finding all prime number under SIZE_N
bool isprime [SIZE_N];
vector<int>prime;

void sieve()
{
    int i, j, r;
    for ( i = 3; i <= SIZE_N; i += 2 )
        isprime[i] = true ;
    
    isprime [2] = true ;
    prime.push_back(2);

    for ( i = 3; i <= SIZE_N; i += 2 )
        if ( isprime[i] == true )
        {
            prime.push_back(i);

            if ( SIZE_N/i >= i )
            {
                r = i * 2 ;
                for ( j = i * i; j <= SIZE_N; j += r )
                    isprime[j] = false ;///unprime all nums which is divisible by i
            }
        }
}
int main()
{
    sieve();
    int n;
    cin>>n;
///first n prime numbers
    for(int i=0;i<n;i++)
       cout<<prime[i]<<", ";///i'th prime number
       cout<<"\n";
    for(int i=1;i<=n;i++){///number of prime under n
        if(isprime[i])cout<<i<<", ";
    }cout<<"\n";

    return 0;
}




