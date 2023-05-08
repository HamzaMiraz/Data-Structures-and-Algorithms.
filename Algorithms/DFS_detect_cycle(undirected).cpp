#include<bits/stdc++.h>
using namespace std;
const int SZ = 101;
vector<int>g[SZ];
int vis[SZ];

vector<int>order;

int V,E;
void clr(){
    for(int i =1;i<=V;i++)
    {
        vis[i] = 0;
        g[i].clear();

    }
    order.clear();
}
bool dfs(int u,int par)
{
    vis[u] = 1;
    for(v: g[u])
    {
        if(vis[v]==0){
            if(dfs(v,u)==true)
                return true;
        }
        else if(vis[v] && par!=v)
            return true;
    }

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
            g[v].push_back(u);
        }
        int flg=0;
        for(int i=1;i<=V;i++){
            if(vis[i]==0){
                if(dfs(i,-1)==true){
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
7 8

1 2
1 3
1 4
2 3
2 4
3 4
5 6
5 7
*/
