#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MAX = 1e6 + 10;
const ll MOD = 1e9 + 9;
const ll base = 269;//53
ll pw[MAX], inv_pw[MAX];
ll len;
vector<ll>prehsh,sufhsh;
ll BIGMOD(ll b,ll power,ll Mod){
    ll ans = 1;
    while(power){
        if(power & 1)ans = (ans * b) % Mod;
        b = (b * b) % Mod;power = power >> 1;}
    return ans%Mod;
}

void pow_clc(){
    ll rev_base=BIGMOD(base,MOD-2,MOD);///base^-1
    pw[0]=1;
    inv_pw[0]=1;
    for(int i=1;i<MAX;i++){
        pw[i]=pw[i-1]*base%MOD;
        inv_pw[i]=inv_pw[i-1]*rev_base%MOD;
    }
}
void hashing(string const &s){///make a hash array in O(string size)
    len=s.size();
    prehsh.resize(len+5);
    sufhsh.resize(len+5);
    prehsh[0]=0;
    sufhsh[0]=0;
    for(int i=0;i<len;i++){
        prehsh[i+1]=(prehsh[i]+(s[i]*pw[i])%MOD)%MOD;
        sufhsh[i+1]=(sufhsh[i]+(s[i]*pw[len-i])%MOD)%MOD;
    }
}
ll compute_hash(string const &s){///O(string size)
    ll hash_value=0;
    for(int i=0;i<s.size();i++){
        hash_value=(hash_value+(s[i]*pw[i])%MOD)%MOD;
    }return hash_value;
}

ll substring_hash(int i,int j){///O(1)
    return (((prehsh[j+1]-prehsh[i]+MOD)%MOD)*(inv_pw[i]%MOD))%MOD;
}
ll GetPrefixHash(int i,int j){
    return substring_hash(i, j);
}
ll GetSuffixHash(int i,int j){
    return (((sufhsh[j+1]-sufhsh[i]+MOD)%MOD)*(inv_pw[len-j]%MOD))%MOD;
}
bool IsPallindrome(int l , int r) {
    return (GetPrefixHash(l , r) == GetSuffixHash(l , r));
}

void string_matching(string const &txt,string const &pat){///O(N)
    hashing(txt);
    ll pat_hsh=compute_hash(pat);
    int substr_len=pat.size();
    vector<int>idx;
    for(int i=0;i+substr_len<=txt.size();i++){
        ll substr_hsh=substring_hash(i,i+substr_len-1);
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
    vector<pair<ll, int>> hashes(n);
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
    hashing(s);
    int cnt = 0;
    for (int len = 1; len <= n; len++) {
        unordered_set<ll> hs;
        for (int i = 0; i+len <= n; i++) {
            ll cur_hsh = substring_hash(i,i+len-1);
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
    while(cin>>txt){
        count_unique_substrings(txt);
    }

    return 0;
}