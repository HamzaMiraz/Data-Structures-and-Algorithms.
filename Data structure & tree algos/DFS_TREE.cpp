#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

#define deb(a)     cout<<__LINE__<<"# "<<#a<<" -> "<<a<<endl;

//For Debugging
#define debug(a...)          {cout<<__LINE__<<"#--> ";dbg,a; cout<<endl;}
struct debugger
{
    template<typename T> debugger& operator , (const T v)
    {
        cout<<v<<" ";
        return *this;
    }
} dbg;


typedef long long LL;
const LL MOD = 1000000007;
const double EPS = 1e-7; ///1*10^-7


const int V_SZ = 101;

/**
enum Color{
    WHITE,
    GRAY,
    BLACK
};
*/

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

vector<int>g[V_SZ];

int startTime[V_SZ];
int finishTime[V_SZ];
int Flattening_tree[2*V_SZ];
int depth[V_SZ];
int height[V_SZ];
int subtree_sum[V_SZ];

vector<int>order;

int Time;
int V,E;
void init(){
    for(int i =1;i<=V;i++)
    {
        g[i].clear();

        startTime[i] = finishTime[i] = -1;
        Flattening_tree[i]=Flattening_tree[V-i+1]=-1;

        height[i]=0;
        depth[i]=0;
        subtree_sum[i]=i;
    }
    Time = 1;
    order.clear();
}

void dfs(int u,int par=-1)
{
    startTime[u] = Time;
    Flattening_tree[Time]=u;
    Time++;
    for(auto v: g[u])
    {
        if(v!=par){
            depth[v]=depth[u]+1;
            dfs(v,u);
            height[u]=max(height[u],height[v]+1);
            subtree_sum[u]+=subtree_sum[v];
        }
    }


    order.push_back(u);

    finishTime[u] = Time;
    Flattening_tree[Time]=u;// change 0,-u
    Time++;
}


int main()
{
//    freopen("dfs.in","r",stdin);
//    freopen("out.txt","w",stdout);
    /// in tree problem E = V-1
    while(cin>>V)
    {
        E=V-1;
        init();

        int u,v;
        for(int i=0;i<E;i++)
        {
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u); ///then it will be nonderected graph
        }

        dfs(1);

        puts("\nTime:");
        for(int i=1;i<=V;i++)   printf("%d:[%d-%d], ",i, startTime[i], finishTime[i]); puts("");
        puts("\nFlattening Tree :");
        for(int i=1;i<=2*V;i++)   printf("%d, ",Flattening_tree[i]); puts("");

        puts("\ndepth of all vertex:");
        for(int i=1;i<=V;i++){
            cout<<"["<<i<<":"<<depth[i]<<"] ,";
        }
        puts("\n\nheight of all vertex:");
        for(int i=1;i<=V;i++){
            cout<<"["<<i<<":"<<height[i]<<"] ,";
        }
         puts("\n\nSub tree sum:");
        for(int i=1;i<=V;i++){
            cout<<"["<<i<<":"<<subtree_sum[i]<<"] ,";
        }

        puts("\n\nFinal complite  visited Order:");
        for(auto v: order)  printf("%d, ", v);  puts("");

    }



    return 0;
}
/*
9

1 2
1 7
2 3
2 5
3 4
5 6
7 8
7 9

13
1 2
1 3
1 13
2 5
5 6
5 7
5 8
8 12
3 4
4 9
4 10
10 11

*/

