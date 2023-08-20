#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mxn=2e5+10;
vector<ll>g[mxn+10],cyl[mxn+10];
ll par[mxn+10];
ll vis[mxn+10],cnt;


void cycle(ll snode,ll enode)
{
    cyl[cnt].push_back(enode);
    while(snode!=enode)
    {
        cyl[cnt].push_back(snode);
        snode=par[snode];
    }
    cyl[cnt].push_back(enode);
    ///reverse(vc[cnt].begin(),vc[cnt].end());
}

void DFS(ll u){

    vis[u]=1;
    for(auto v:g[u]){
        if(vis[v]==0){
            par[v]=u;
            DFS(v);
        }
        else if(vis[v]==1&&v!=par[u]){///if(vis[v]==1) for directed graph
            ll snode=u;
            ll enode=v;
            cycle(snode,enode);
            cnt++;///number of cycle
        }
    }
    vis[u]=2;/// u nodes all adj nodes r visited
}

int main()
{
    ///for undirected = minimum three nodes make a cycle for this code
    ///for directed = also one node can be make a cycle for this code
    ll V,E,u,v;
    while(cin>>V>>E){
        for(int i=0;i<=V+5;i++){
            vis[i]=0;
            par[i]=-1;
            g[i].clear();
            cyl[i].clear();
        }
        for(ll i=0; i<E; i++)
        {
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);///off the line for directed graph
        }
        cnt=0;
        for(ll i=1;i<=V;i++)
        {
            if(vis[i]==0)
            DFS(i);
        }
        for(ll i=0; i<cnt; i++)
        {
            for(auto v:cyl[i])
                cout<<v<<" ";
            cout<<endl;
        }
        if(cnt==0)
        {
             cout<<"IMPOSSIBLE"<<endl;
        }
    }
    return 0;
}
/**
13 15

1 2
2 3
3 4
4 6
4 7
5 6
3 5
7 8
6 10
5 9
10 9
10 11
11 12
11 13
12 13

**/
