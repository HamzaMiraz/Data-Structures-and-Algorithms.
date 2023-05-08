#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double EPS = 1e-7; ///1*10^-7
const int oo = 1e8+0.5;

vector<int>V[1000];
vector<int>W[1000];
int dist[1000],par[1000];
bool vis[1000];

void init(int n){
    for(int i=1;i<=n;i++){
        dist[i]=oo;
        par[i]=-1;
        vis[i]=false;
        V[i].clear();
        W[i].clear();
    }
}
int Prims(int s)
{
    int SumDis=0;
    dist[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

    pq.push({0,s});///({distance,node})
    while(!pq.empty())
    {
        auto it =pq.top();
        pq.pop();

        int u=it.second;
        int udis=it.first;
        if(dist[u]<udis ||vis[u]==true)
            continue;

        vis[u]=true;
        SumDis+=udis;
        for(int i=0;i<V[u].size();i++)
        {
            int v=V[u][i];
            int w=W[u][i];

            if(vis[v]==false && dist[v]>w)
            {
                dist[v]=w;
                par[v]=u;
                pq.push({dist[v],v});

            }
        }
    }
    return SumDis;
}

int main()
{
//    freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
    int N,E,S,D;
    while(3==scanf("%d%d%d",&N,&E,&S))///S=source
    {
        init(N);
        int u,v,w;
        for(int i=1;i<=E;i++)
        {
            cin>>u>>v>>w;
            V[u].push_back(v);
            V[v].push_back(u);
            W[u].push_back(w);
            W[v].push_back(w);
        }

        int Cost=Prims(S);
        cout<<"MST Cost : "<<Cost<<"\n";
    }
    return 0;
}
/*

4 6 1
1 4 100
1 2 5
2 4 50
2 3 7
3 4 20
3 4 10

6 10 1
1 2 10
2 3 20
3 4 20
4 5 20
4 6 9
6 1 8
5 6 4
5 1 19
5 2 17
5 3 15

*/

