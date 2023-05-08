#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <stack>
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
#include <ctime>
#include <assert.h>

#include <unordered_set>
#include <unordered_map>

#include <bits/stdc++.h>
using namespace std;

#include<cmath>
#include<math.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

const int NUMBER_OF_VERTICS = 33;
const int oo = 100;

vector<int>adj[NUMBER_OF_VERTICS];

int par[NUMBER_OF_VERTICS];
int dis[NUMBER_OF_VERTICS];
bool col[NUMBER_OF_VERTICS];

void BFS(int source)
{
    queue<int>Q;

    col[source] = false;
    dis[source] = 0;
    par[source]  = -1;
    Q.push(source);

    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        for(int i=0;i<adj[u].size();i++)
        {
            int v = adj[u][i];

            if(col[v]==false) continue;

            col[v] = false;
            dis[v] = 1 + dis[u];
            par[v] = u;
            Q.push(v);
        }
    }
}


int main()
{
    //freopen("bfs.in","r",stdin);

    int V, E, source;

    while(cin>>V>>E>>source)
    {
        for(int i=1;i<=V;i++){
            adj[i].clear();
            dis[i] = oo;
            col[i] = true;
            par[i] = -1;
        }

        for(int i=0;i<E;i++)
        {
            int u,v;
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        BFS(source);

        for(int i=1;i<=V;i++)
        {
            printf("VertexNo:%3d, Distance:%4d, Parent:%3d, Color:%2d\n", i, dis[i], par[i], col[i]);
        }
    }

    return 0;
}


/*
Sample Input for a Graph:
7 7 1

1 2
1 3
2 3
2 4
3 4
4 5
5 6

*/

