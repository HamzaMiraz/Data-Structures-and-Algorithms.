#include<bits/stdc++.h>
using namespace std;


struct custom_hash {
    static uint32_t splitmix32(uint32_t x) {//uint64_t
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint32_t x) const {//uint64_t
        static const uint32_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix32(x + FIXED_RANDOM);
    }
}rng;///Random number generator

signed main()
{
    int a=rng(1);
    int b=rng(2);
    int c=rng(3);
    

    cout<<a<<" "<<bitset<32>(a)<<"\n";
    cout<<b<<" "<<bitset<32>(b)<<"\n";
    cout<<c<<" "<<bitset<32>(c)<<"\n";

    /// if xor 1,2,3 then generally ans will be zero.because (1^2=3) ^ 3 =0
    /// if we this function then ans will never been zero because 
    /// (rng(1)^rng(2) != rng(3)) ^ rng(3) = 0
    /// There can be only one way ans will be zero when we xor the same number with it.
    /// rng(num)^rng(num) = 0 //   rng(num)-rng(num)=0

    /// for better example : https://codeforces.com/contest/2014/problem/H

}
///invisible =  