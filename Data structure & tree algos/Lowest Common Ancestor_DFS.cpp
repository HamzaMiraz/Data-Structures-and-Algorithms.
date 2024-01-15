#include<bits/stdc++.h>
using namespace std;

const int no_node=1000;
vector<int>adj[no_node];
int par[no_node];

void init(int V){
    for(int i=0;i<V+5;i++){
        adj[i].clear();
        par[i]=-1;
    }
}

void dfs(int u){
    for(auto v : adj[u]){
        if(v==par[u])continue;
        par[v]=u;
        dfs(v);
    }
}
vector<int>ancestors(int node){
    vector<int>ans;
    while(node != -1){///node no. 1 s parent in -1
        ans.push_back(node);
        node=par[node];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
int LCA(int nod1,int nod2){
    vector<int>anc1=ancestors(nod1);
    vector<int>anc2=ancestors(nod2);
    int len=min(anc1.size(),anc2.size());
    int lca=-1;
    for(int i=0;i<len;i++){
        if(anc1[i]==anc2[i]){
            lca=anc1[i];
        }else{
            break;
        }
    }
    return lca;

}
int main(){
    int V,E,u,v;
    while(cin>>V){
        init(V);
        E=V-1;
        for(int i=0;i<E;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1);
        int nod1,nod2;
        while(1){
            cin>>nod1>>nod2;///query
            if(nod1==0 || nod2==0)break;
            cout<<"LCA["<<nod1<<","<<nod2<<"]="<<LCA(nod1,nod2)<<"\n";
        }
    }
    return 0;
}
/**

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

5 11
11 9
**/
