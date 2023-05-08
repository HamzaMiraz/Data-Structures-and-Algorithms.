//#include<bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <ctype.h>
#include <cctype>
#include <set>
#include <bitset>
#include <algorithm>
#include <list>
#include <utility>
#include <functional>
#include <deque>
#include <numeric>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cTime>
#include <assert.h>

#include <unordered_set>
#include <unordered_map>

using namespace std;

#include<cmath>
#include<math.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//For Debugging
#define debug(a...)          {cout<<__LINE__<<" #--> ";dbg,a; cout<<endl;}
struct debugger
{
    template<typename T> debugger& operator , (const T v)
    {
        cout<<v<<" ";
        return *this;
    }
} dbg;



#define deb(a)     cout<<__LINE__<<"# "<<#a<<" -> "<<a<<endl;
#define GCD(a,b)  __gcd(a,b)
#define LCM(a,b)  (a*b)/__gcd(a,b)
#define sqr(a)    ((a)*(a))
#define el         "\n"
#define dec(n,x)  fixed << setprecision(x) <<n
typedef long long LL;
LL BIGMOD(LL b,LL power,LL Mod){LL ans = 1;
while(power){if(power & 1)ans = (ans * b) % Mod;
b = (b * b) % Mod;power = power >> 1;}return ans;}

vector<int>primeFactors(int n){vector<int>PRIME;int c=2;while///prime factor
(n>1){if(n%c==0){PRIME.push_back(c);n/=c;}else c++;}return PRIME;}

LL nCr(LL n, LL r){LL res=1;for (LL i=0;i<r;i++){
res *= (n-i);res /= (i+1);}return res;}/// NCR

LL fact(LL n){if(n<=1)return 1;return n*fact(n-1);}
LL nPr(LL n, LL r){return fact(n)/fact(n-r);}///NPR

const double PI = acos(-1);
const double EPS = 1e-7; ///1*10^-7
const int oo = 2e9+10;
const int MOD = 1e9+7;
const int Size = 1000;
struct node{
    int idx,st,fin;
};
node Time[Size];
vector<int>adj[Size];
vector<int>radj[Size];
vector<int>component[Size];
int vis[Size],scc[Size],ti,mrk;

bool com(node a,node b){
    return a.fin>b.fin;
}
bool comidx(node a,node b){
    return a.idx<b.idx;
}

void dfs(int u){
    Time[u].st=ti++;
    vis[u]=1;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(vis[v]==0){
            dfs(v);
        }
    }
    Time[u].fin=ti++;
}
void rdfs(int u,int mrk){

    vis[u]=1;
    scc[u]=mrk;
    component[mrk].push_back(u);
    for(int i=0;i<radj[u].size();i++){
        int v=radj[u][i];
        if(vis[v]==0){
            rdfs(v,mrk);
        }
    }

}

int main()
{
//   freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
//    ios_base::sync_with_stdio(0); cin.tie(0);
    int V,E,u,v;
    while(cin>>V>>E)
    {
    /// SCC works only for directional graph
        for(int i=0;i<=E+5;i++){
            adj[i].clear();
            radj[i].clear();
            component[i].clear();
            vis[i]=0;
        }
        for(int i=1;i<=E;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            radj[v].push_back(u);/// for reverce edges direction
        }
        ti=1;
        for(int i=1;i<=V;i++){/// 1 based graph
            Time[i].idx=i;
            if(vis[i]==0){
                dfs(i);
            }
        }
        memset(vis,0,sizeof vis),mrk=1;/// mark = n'th component
        sort(&Time[1],&Time[V+1],com);///precedency by finish time
        for(int i=1;i<=V;i++){
            if(vis[Time[i].idx]==0){
                rdfs(Time[i].idx,mrk),mrk++;///dfs traverce for reverse direction
            }
        }
        sort(&Time[1],&Time[V+1],comidx);
        for(int i=1;i<mrk;i++){
            cout<<"SCC("<<scc[component[i][0]]<<")-> ";
            for(auto v : component[i]){
                cout<<v<<" ";
                //cout<<"-> SCC("<<scc[v]<<") ,";
            }
            cout<<el;
        }

    }
    return 0;
}
/**
exmp two inputs :
8 9

1 2
2 3
3 4
4 1
3 5
5 6
6 7
7 5
7 8

8 10

1 2
2 3
3 1
3 4
4 5
5 6
5 8
6 7
7 5
7 8

**/
