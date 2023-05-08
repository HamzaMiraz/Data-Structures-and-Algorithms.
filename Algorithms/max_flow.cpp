#include <bits/stdc++.h>

using namespace std;

int bfs(int source,int target,int V,vector<int>& parent,vector<vector<int>>& graph){
        fill(parent.begin(),parent.end(),-1);
        parent[source] = -2;
        queue<pair<int,int>> q;
        q.push({source,1e9});

        while(!q.empty()){
            int u = q.front().first;
            int cap = q.front().second;
            q.pop();
            for(int v=0;v<V;v++){
                if(u!=v && graph[u][v]>0 && parent[v]==-1){
                    parent[v] = u;
                    int min_cap = min(cap,graph[u][v]);
                    if(v==target){
                        return min_cap;
                    }

                    q.push({v,min_cap});
                }
            }
        }
        return 0;
}

int Ford_Fulkerson(int source,int target,int V,vector<vector<int>>& graph){
        vector<int> parent(V+5,-1);
        int max_flow = 0;
        int min_cap = 0;

        while(min_cap = bfs(source,target,V,parent,graph)){
            max_flow += min_cap;
            int v = target;

            while(v!=source){
                int u = parent[v];

                graph[u][v] -= min_cap;
                graph[v][u] += min_cap;
                v=u;
            }
        }
        return max_flow;
    }


int main()
{
    //Intializing the graph in 2d vector
    int V,E,s,e;
    /// zero based graph
    while(cin>>V>>E>>s>>e){/// s = start node,e = target node
        vector<vector<int>> graph(V+5, vector<int> (V+5, 0));
        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;
            graph[u][v]=w;
        }

        cout << "Maximum Flow Using Ford Fulkerson Algo: " << Ford_Fulkerson(s,e,V,graph) << endl;
    }
    return 0;
}
///invisible =  
/**
6 9 0 5
0 1 7
0 2 4
2 1 3
1 3 3
2 3 2
1 4 5
3 4 3
3 5 5
4 5 8


6 7 0 5
0 1 4
0 3 3
1 2 4
2 3 3
2 5 2
3 4 6
4 5 6
**/
