#include<bits/stdc++.h>
using namespace std;

const int Size=100;
const int oo=2e9+10;
set<pair<int,int>>st;
vector<int>adj[Size];
vector<int>waight[Size];
int par[Size],dist[Size];
int V,E,S,D;

void init(){
    for(int i=0;i<V+5;i++){
        adj[i].clear();
        waight[i].clear();
        dist[i]=oo;
        par[i]=i;
    }
    st.clear();
}

void dijkstra(int s){
    dist[s]=0;
    st.insert({0,s});/// set is also min heap but not contain duplicates

    while(!st.empty()){/// if we use only queue then it consider all possible paths
                    /// But if we use set or priority_queue then its only consider
                    /// minimum dist[node] s paths from to the source node

        auto it = *(st.begin());///we r pointing minimum dist of the set
        int u=it.second;///node
        int udis=it.first;/// source to distance of u
        st.erase(it);

        for(int i=0;i<adj[u].size();i++){

            int v=adj[u][i];///richable node from to u
            int vw=waight[u][i];/// u to v edge waight

            if(dist[v] > udis + vw){/// dist[u] = udis

                if(dist[v] != oo){///if dist[v] is already updated before
                    st.erase({dist[v],v});///so to need erase this becouse
                }                      ///set can't contain duplicate value

                par[v]=u;
                dist[v] = udis + vw;/// dist[v] update

                st.insert({dist[v],v});
            }
        }
    }
}
vector<int> getPaht(int source, int destination){
    int v = destination;
    vector<int>path;

    while(source != v){
        path.emplace_back(v);
        v = par[v];
    }
    path.emplace_back(source);
    reverse(path.begin(), path.end());
    return path;
}

signed main(){
    while(cin>>V>>E>>S){//S=source ,D=destinitation
        init();int u,v,w;
        for(int i=0;i<E;i++){
            cin>>u>>v>>w;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
            waight[u].emplace_back(w);
            waight[v].emplace_back(w);
        }
        dijkstra(S);

        for(int i=1;i<=V;i++){

            cout<<"Distance "<<S<<" to "<<i<<" = "<<dist[i]<<"\n";
            cout<<"Path : ";
            vector<int>path = getPaht(S,i);
            for(auto it: path){
                cout<<"->"<<it;
            }
            cout<<"\n\n";
        }
        cout<<"\n";

    }
    return 0;
}
/**
6 6 1

1 2 3
1 3 1
2 4 4
3 4 2
4 5 2
4 6 1

5 6 1

1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
**/
