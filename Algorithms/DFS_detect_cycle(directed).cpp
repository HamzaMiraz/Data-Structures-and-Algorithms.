#include<bits/stdc++.h>
using namespace std;
const int SZ = 101;
vector<int>g[SZ];
int vis[SZ];
int pathvis[SZ];

vector<int>order;

int V,E;
void clr(){
    for(int i =1;i<=V;i++)
    {
        pathvis[i]=0;
        vis[i] = 0;
        g[i].clear();

    }
    order.clear();
}
bool dfs(int u,int par)
{
    vis[u] = 1;
    pathvis[u]=1;
    for(auto v :g[u])
    {
        if(vis[v]==0){
            if(dfs(v,u)==true)
                return true;
        }
        else if(pathvis[v])
            return true;
    }
    pathvis[u]=0;
    return  false;
}
int main()
{
//    freopen("dfs.in","r",stdin);
//    freopen("out.txt","w",stdout);
    while(cin>>V>>E)
    {
        clr();
        int u,v;
        for(int i=0;i<E;i++)
        {
            cin>>u>>v;
            g[u].push_back(v);
        }
        int flg=0;
        for(int i=1;i<=V;i++){
            if(vis[i]==0){
                if(dfs(i,i)==true){
                    flg=1;
                    break;
                }
            }
        }
        if(flg==1){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
        }
    }
    return 0;
}
/*
7 7

1 2
3 5
3 4
4 6
5 6
6 7
2 3


11 12

1 2
2 3
3 5
3 4
5 6
4 6
6 7
8 2
8 9
9 10
10 8
11 9
*/
