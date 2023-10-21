#include<bits/stdc++.h>
using namespace std;
using ll= long long;
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
i/// it can find 1e18 numbers prime fectors
void prime_factors(int n){
    for(int i=0; prime[i]*prime[i]<=n && i<prime.size() ; i++){
        while(n%prime[i]==0){
            cout<<prime[i]<<" ";
            n/=prime[i];
        }
    }
    if(n>1)cout<<n<<" ";
    cout<<"\n";
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  sieve();
  prime_factors(100000000);
  return 0;
}