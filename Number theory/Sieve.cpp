#include<bits/stdc++.h>
using namespace std;

///Nlog(N)
const int N = 1e7 + 9;
bitset<N> not_prime;
vector<int> primes;
void sieve(){
    not_prime[1] = true;
    for (int i = 2; i * i <= N; i++) {
        if (!not_prime[i]) {
          for (int j = i * i; j <= N; j += i) {
            not_prime[j] = true;
          }
        }
    }
    for (int i = 2; i <= N; i++) {
        if (!not_prime[i]) { 
          primes.push_back(i);
        }
    }
}
int32_t main() {
    ///zero based
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<primes[i]<<" ";
    }cout<<"\n";
    
    ///number of prime number under n
    for(int i=1;i<=n;i++){
        if(!not_prime[i])
        cout<<i<<", ";
    }

  return 0;
}