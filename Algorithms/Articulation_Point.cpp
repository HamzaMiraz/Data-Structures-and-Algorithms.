#include<bits/stdc++.h>
using namespace std;
/**
Articulation_Point algorithm : if we remove  a node from
the graph and thats makes the graph to one more parts of graph
thats kind of nodes call by Articulation_Point
**/
void art_point_dfs(int node,int parent,int vis[],int timer,int tin[],
        int tlow[],vector<int>adj[],set<int>&art_points){
    vis[node]=1;
    tin[node]=tlow[node]=timer;
    timer++;
    int child=0;
    for(auto v : adj[node]){
        if(v==parent)continue;
        if(vis[v]==0){
            art_point_dfs(v,node,vis,timer,tin,tlow,adj,art_points);
            tlow[node]=min(tlow[v],tlow[node]);
            if(tlow[v]>=tin[node] && parent!=-1){
                art_points.insert(node);
            }
            child++;
        }else{
            tlow[node]=min(tin[v],tlow[node]);
        }
    }
    if(child>1 && parent ==-1){
        art_points.insert(node);
    }
}

int main(){
    int V,E;
    while(cin>>V>>E){
        int vis[V+5]={0},tin[V+5],tlow[V+5];
        vector<int>adj[V+5];
        set<int>art_points;
        for(int i=0;i<E;i++){
           int u,v;
           cin>>u>>v;
           adj[u].push_back(v);
           adj[v].push_back(u);///underected graph

        }
        int timer=1;
        for(int i=0;i<V;i++){///zero based;
            if(vis[i]==0)
                art_point_dfs(i,-1,vis,timer,tin,tlow,adj,art_points);
        }
        for(auto it : art_points){
            cout<<it<<", ";
        }
        if(art_points.size()==0)
            cout<<"There is no Articulation Points";
        cout<<"\n";

    }
    return 0;
}
/**

7 8

0 1
0 2
0 3
2 3
2 4
2 5
4 6
5 6

**/
