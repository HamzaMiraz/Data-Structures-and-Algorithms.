#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define F  first
#define S  second
const int MAX = 1e6 + 10;
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
vector<pair<ll,ll>>hashing(string const &s){///make a hash array in O(string size)
    int len=s.size();
    vector<pair<ll,ll>>hsh(len+5,{0,0});
    for(int i=0;i<len;i++){
        hsh[i+1].F = (hsh[i].F + (s[i] * pw[i].F)%MOD1)%MOD1;
        hsh[i+1].S = (hsh[i].S + (s[i] * pw[i].S)%MOD2)%MOD2;
    }
    return hsh;
}
pair<ll,ll> compute_hash(string const &s){///O(string size)
    pair<ll,ll> hash_value={0,0};
    for(int i=0;i<s.size();i++){
        hash_value.F = (hash_value.F + (s[i]*pw[i].F)%MOD1)%MOD1;
        hash_value.S = (hash_value.S + (s[i]*pw[i].S)%MOD2)%MOD2;
    }return hash_value;
}
pair<ll,ll> substring_hash(int i,int substr_len,vector<pair<ll,ll>> const &hsh){///O(1)
    pair<ll,ll>hs;
    hs.F=(((hsh[i+substr_len].F-hsh[i].F+MOD1)%MOD1)*(inv_pw[i].F%MOD1))%MOD1;
    hs.S=(((hsh[i+substr_len].S-hsh[i].S+MOD2)%MOD2)*(inv_pw[i].S%MOD2))%MOD2;
    return hs;
}
void string_matching(string const &txt,string const &pat){///O(N)///Rabin Karp
    vector<pair<ll,ll>>txt_hsh=hashing(txt);
    pair<ll,ll> pat_hsh=compute_hash(pat);
    int substr_len=pat.size();
    vector<int>idx;
    for(int i=0;i+substr_len<=txt.size();i++){
        pair<ll,ll> substr_hsh=substring_hash(i,substr_len,txt_hsh);
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
// find same strings index & insert a group .O(nm +nlogn)
void group_identical_strings(vector<string> const& s) {
    ///example s={"aa","bb","ac","ab","aa","ab","dd","aa"};
    int n = s.size();
    vector<pair<pair<ll,ll>, int>> hashes(n);
    for (int i = 0; i < n; i++)
        hashes[i] = {compute_hash(s[i]), i};

    sort(hashes.begin(), hashes.end());

    vector<vector<int>> groups;
    for (int i = 0; i < n; i++) {
        if (i == 0 || hashes[i].first != hashes[i-1].first)
            groups.emplace_back();
        groups.back().push_back(hashes[i].second);
    }
    cout<<"Number of Distinct strings: "<<groups.size()<<"\n";
    cout<<"identical group of strings:\n";///denote by indexs
    for(auto it : groups){
        for(auto i : it){
            cout<<i<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
//number of unique substring,O(n^2)
void count_unique_substrings(string const& s) {
    int n = s.size();
    vector<pair<ll,ll>>hsh=hashing(s);
    int cnt = 0;
    for (int len = 1; len <= n; len++) {
        set<pair<ll,ll>>hs;
        for (int i = 0; i+len <= n; i++) {
            pair<ll,ll> cur_hsh = substring_hash(i,len,hsh);
            hs.insert(cur_hsh);
        }
        cnt += hs.size();
    }
    cout<<"Number of unique substrings :"<<cnt<<"\n";
}
int main() {
  
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    pow_clc();

    string txt,pat;
    while(cin>>txt>>pat){
        string_matching(txt,pat);
    }

    return 0;
}