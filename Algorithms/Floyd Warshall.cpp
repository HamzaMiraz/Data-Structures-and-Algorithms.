#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define nn printf("\n");
#define el cout<<"\n";

typedef long long LL;

const int oo = 1e8;
const int Size = 100;
int dis[Size][Size],N,E;
int main()
{
//   freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
//    ios_base::sync_with_stdio(0); cin.tie(0);

    while(cin>>N>>E)/// N=number of nodes,E=number of edges
    {
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                dis[i][j]=oo;
                if(i==j)dis[i][j]=0;
            }
        }
        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;
            dis[u][v]=w;/// directed graph;
        }

        for(int via=1;via<=N;via++){
            for(int u=1;u<=N;u++){
                for(int v=1;v<=N;v++){
                    dis[u][v]=min(dis[u][v] , dis[u][via]+dis[via][v]);
                }
            }
        }
        cout<<"All nodes distance matrix:\n";
        for(int u=1;u<=N;u++){
            for(int v=1;v<=N;v++){
                if(dis[u][v]==oo){
                    cout<<"oo ";
                }
                else
                cout<<dis[u][v]<< " ";
            }
            el;
        }
        /// if any node dist[u][u]<0 then
        /// we call it has nagtive cycle

    }
    return 0;
}
/**
5 7
1 2 6
1 3 2
1 4 4
3 5 1
3 2 3
4 2 1
5 2 1

**/
