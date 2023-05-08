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
int col[V_SZ];
int par[V_SZ];

int startTime[V_SZ];
int finishTime[V_SZ];

vector<int>order;

int Time;
int V,E;

void init(){
    for(int i =1;i<=V;i++)
    {
        col[i] = WHITE;
        par[i] = -1;
        g[i].clear();

        startTime[i] = finishTime[i] = -1;
    }
    Time = 1;
    order.clear();
}

void dfs(int u)
{
    startTime[u] = Time++;
    col[u] = GRAY;

    for(auto v: g[u])
    {
        if(col[v]==WHITE){
            par[v] = u;
            dfs(v);
        }
    }

    col[u] = BLACK;

    order.push_back(u);

    finishTime[u] = Time++;
}


int main()
{
//    freopen("dfs.in","r",stdin);
//    freopen("out.txt","w",stdout);

    while(cin>>V>>E)
    {
        init();

        int u,v;

        for(int i=0;i<E;i++)
        {
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u); ///then it will be nonderected graph
        }

        for(int i=1;i<=V;i++)
            if(col[i]==WHITE){
                dfs(i);
            }

        puts("Parent:");
        for(int i=1;i<=V;i++)   printf("[%d:%d], ",i, par[i]);  printf("\n");

        puts("Time:");
        for(int i=1;i<=V;i++)   printf("%d:[%d-%d], ",i, startTime[i], finishTime[i]); puts("");

        puts("Final visited Order:");
        for(auto v: order)  printf("%d, ", v);  puts("");
    }



    return 0;
}
/*
7 8

1 2
1 3
1 4
2 3
2 4
3 4
5 6
5 7
*/

