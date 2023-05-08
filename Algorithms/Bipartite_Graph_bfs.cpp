#include<bits/stdc++.h>
using namespace std;

const int SIZE=100;

vector<int>adj[SIZE];
int color[SIZE],V,E,u,v;
bool BFS(int s){
    color[s]=0;
    queue<int>Q;
    Q.push(s);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(auto v : adj[u]){
            if(color[v]==-1){
                color[v]=!color[u];///coloring v with reverse color of u
                Q.push(v);
            }
            else if(color[v]==color[u]){
                return false;
            }
        }
    }
    return true;
}

signed main(){
    while(cin>>V>>E){
        for(int i=0;i<V+5;i++){
            color[i]=-1;
            adj[i].clear();
        }
        for(int i=0;i<E;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int flg=1;
        for(int i=1;i<=V;i++){///1 based
            if(color[i]==-1){
                if(BFS(i)==false){
                    flg=0;
                    break;
                }
            }
        }
        ///if graph has a cycle which is contain odd number of nodes
        ///in that case graph is not  Bipartite Graph
        if(flg){
            cout<<"Yes\n";
        }
        else{
            cout<<"No\n";
        }
    }
    return 0;
}
/**
8 8

1 2
2 3
2 6
3 4
6 5
4 5
4 7
7 8

8 9

1 2
2 3
3 8
1 8
3 4
8 7
4 5
7 6
5 6

9 10

1 2
2 3
1 9
9 8
3 8
3 4
8 7
4 5
7 6
5 6
**/
