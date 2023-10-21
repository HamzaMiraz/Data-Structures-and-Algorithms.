#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;
int spf[N];///smallest prime factor
void spf_pre_clc(){///nlog(log(n))
    for(int i=2;i<=N;i++){
        spf[i]=i;/// initilize spf of all each self
    }
    for(int div=2;div<=N;div++){/// div=divisor
        for(int i=div;i<=N;i+=div){///i is a number which is contain divisor div
            spf[i]=min(spf[i],div);
        }
    }
}
void prime_factors(int n){///log(n)
    while(n>1){
        cout<<spf[n]<<" ";
        n/=spf[n];
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    spf_pre_clc();
    int n;
    cin>>n;
    prime_factors(n);
  
  return 0;
}