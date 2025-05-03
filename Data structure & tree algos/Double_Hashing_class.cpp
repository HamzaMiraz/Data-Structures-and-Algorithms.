#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define F  first
#define S  second
const int MAX = 1e6 + 10;// string max size
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll base1 = 269;//31,//53
const ll base2 = 277;//31,//53
pair<ll,ll> pw[MAX], inv_pw[MAX];

ll BIGMOD(ll b,ll power,ll Mod){
    ll ans = 1;
    while(power){
        if(power & 1)ans = (ans * b) % Mod;
        b = (b * b) % Mod;power = power >> 1;}
    return ans%Mod;
}

void pow_clc(){
    ll rev_base1=BIGMOD(base1,MOD1-2,MOD1);///base1^-1
    ll rev_base2=BIGMOD(base2,MOD2-2,MOD2);///base2^-1
    pw[0]={1,1};
    inv_pw[0]={1,1};
    for(int i=1;i<MAX;i++){
        
        pw[i].F = 1LL * pw[i-1].F * base1 % MOD1;
        inv_pw[i].F = 1LL * inv_pw[i-1].F * rev_base1 % MOD1;
        
        pw[i].S = 1LL * pw[i-1].S * base2 % MOD2;
        inv_pw[i].S = 1LL * inv_pw[i-1].S * rev_base2 % MOD2;
    }
}
struct Hashing{
    vector<pair<ll,ll>>prehsh,sufhsh;
    int len;
    Hashing(){len=0;}
    Hashing(string const &s){///make a hash array in O(string size)
        build(s);
    }
    void build(string const &s){///make a hash array in O(string size)
        len=s.size();
        prehsh.resize(len+2);
        sufhsh.resize(len+2);
        for(int i=0;i<len;i++){
            prehsh[i].F= (1LL*s[i]*pw[i].F) %MOD1;
            prehsh[i].S= (1LL*s[i]*pw[i].S) %MOD2;
            if(i){
                prehsh[i].F= (prehsh[i].F + prehsh[i-1].F) %MOD1;
                prehsh[i].S= (prehsh[i].S + prehsh[i-1].S) %MOD2;
            }
            sufhsh[i].F= (1LL*s[i]*pw[len-i-1].F) %MOD1;
            sufhsh[i].S= (1LL*s[i]*pw[len-i-1].S) %MOD2;
            if(i){
                sufhsh[i].F= (sufhsh[i].F + sufhsh[i-1].F) %MOD1;
                sufhsh[i].S= (sufhsh[i].S + sufhsh[i-1].S) %MOD2;
            }
        }
    }
    ll get_hash(int i,int j){///O(1)
        assert(i<=j);
        pair<ll,ll>hs({0,0});
        hs.F=prehsh[j].F;
        hs.S=prehsh[j].S;
        if(i){
            hs.F=(hs.F- prehsh[i-1].F +MOD1)%MOD1;
            hs.S=(hs.S- prehsh[i-1].S +MOD2)%MOD2;
        }
        hs.F= (1LL* hs.F * inv_pw[i].F)%MOD1;
        hs.S= (1LL* hs.S * inv_pw[i].S)%MOD2;
        
        return (hs.F*MOD2 + hs.S);
    }
    ll rev_hash(int i,int j){
        assert(i<=j);
        pair<ll,ll>hs({0,0});
        hs.F=sufhsh[j].F;
        hs.S=sufhsh[j].S;
        if(i){
            hs.F=(hs.F- sufhsh[i-1].F +MOD1)%MOD1;
            hs.S=(hs.S- sufhsh[i-1].S +MOD2)%MOD2;
        }
        hs.F= (1LL* hs.F * inv_pw[len-j-1].F)%MOD1;
        hs.S= (1LL* hs.S * inv_pw[len-j-1].S)%MOD2;
        
        return (hs.F*MOD2 + hs.S);
    }
    ll get_hash(){
        return get_hash(0,len-1);
    }
    bool IsPallindrome(int l , int r) {
        return (get_hash(l , r) == rev_hash(l , r));
    }

};
void string_matching(string const &txt,string const &pat){///O(N)///Rabin Karp
    Hashing tx,pt(pat);
    tx.build(txt);
    ll pat_hsh=pt.get_hash();
    int substr_len=pat.size();
    vector<int>idx;
    for(int i=0;i+substr_len-1<txt.size();i++){
        ll substr_hsh=tx.get_hash(i,i+substr_len-1);
        if(substr_hsh==pat_hsh)idx.push_back(i+1);
    }
    if(idx.size()){
        cout<<"pattern found at index : ";
        for(auto it: idx)cout<<it<<" ";
        cout<<"\n";
    }else{
        cout<<"pattern not found\n";
    }
}
int main() {
    ///zero based
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    pow_clc();

    string txt,pat;
    while(cin>>txt>>pat){
        string_matching(txt,pat);
        
    }
    return 0;
}