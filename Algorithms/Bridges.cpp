#include<bits/stdc++.h>
using namespace std;
/**
bridge algorithm : if we remove  a edge from the graph
and thats makes the graph to one more parts of graph
thats kind of edges call by Bridge
**/
const int nodes=105;
int timer;
int vis[nodes],tin[nodes],tlow[nodes];
vector<int>adj[nodes];
vector<pair<int,int>>bridge;
void bridge_dfs(int node,int parent){
    vis[node]=1;
    tin[node]=tlow[node]=timer;
    timer++;
    for(auto v : adj[node]){
        if(v==parent)continue;
        if(vis[v]==0){
            bridge_dfs(v,node);
            tlow[node]=min(tlow[v],tlow[node]);
            if(tlow[v]>tin[node]){
                bridge.push_back({node,v});
            }
        }else{
            tlow[node]=min(tlow[v],tlow[node]);
        }
    }
}
void init(int V){
    for(int i=0;i<V+5;i++){
        vis[i]=0;
        adj[i].clear();
    }
    bridge.clear();
}

int main(){
    int V,E;
    while(cin>>V>>E){
        init(V);

        for(int i=0;i<E;i++){
           int u,v;
           cin>>u>>v;
           adj[u].push_back(v);
           adj[v].push_back(u);///underected graph

        }
        int timer=1;
        for(int i=0;i<V;i++){///zero based;
            if(vis[i]==0){
                bridge_dfs(i,-1);
            }
        }
        for(auto it : bridge){
            cout<<it.first<<"->"<<it.second<<"\n";
        }
        if(bridge.size()==0)cout<<"No Bridges\n";
        cout<<"\n";

    }
    return 0;
}
/**
5 5
1 0
0 3
3 4
0 2
1 2

12 14
0 1
0 3
1 2
3 2
3 4
4 5
5 6
6 7
7 8
7 9
9 10
10 11
11 9
8 6

12 14
0 1
0 3
1 2
3 2
3 4
4 5
5 6
6 7
7 8
7 9
9 10
10 11
11 9
8 5

**/
