#include<bits/stdc++.h>
using namespace std;


#define deb(a)     cout<<__LINE__<<"# "<<#a<<" -> "<<a<<endl;
#define GCD(a,b)  __gcd(a,b)
#define LCM(a,b)  (a*b)/__gcd(a,b)
#define sqr(a)    ((a)*(a))
#define dec(n,x)  fixed << setprecision(x) <<n
#define pb emplace_back
#define nl printf("\n");
#define el cout<<"\n";
#define yes cout<<"Yes\n";
#define no cout<<"No\n";

typedef long long LL;

const int oo = 2e9+10;
struct Edge{
    int u,v,w;
    Edge(int ui,int vi,int wi){
        u=ui;
        v=vi;
        w=wi;
    }
};
vector<Edge>edgeList;
vector<int>parant;
vector<int>compoSize;
void disjoint(int V){
    edgeList.clear();
    compoSize.resize(V+5,1);
    parant.resize(V+5);
    for(int i=0;i<=V;i++){
        parant[i]=i;///call by make func in DSU
    }
}
/// finding root node of this component and
/// make root node is parant of the all nodes of this component
int FindRootParant(int node){
    if(node == parant[node])
        return node;
    return parant[node]=FindRootParant(parant[node]);
}
/// joining two components
void join_components(int u,int v){///union/makelink  u nodes component
                                /// to v nodes component and
                                 /// make them as a same component

    int u_parant=FindRootParant(u); /// finding u 's root node
    int v_parant=FindRootParant(v); /// finding v 's root node

    if(u_parant==v_parant)///both r alrady joined
        return ;
    if(compoSize[u_parant]>compoSize[v_parant]){
        parant[v_parant]=u_parant;
        compoSize[u_parant]+=compoSize[v_parant];
    }
    else{
        parant[v_parant]=u_parant;
        compoSize[v_parant]+=compoSize[u_parant];
    }
}
bool com_by_waight(Edge a,Edge b){
    return a.w<b.w;
}

int kruskal(){
    int cost=0;
    sort(edgeList.begin(),edgeList.end(),com_by_waight);

    for(int i=0;i<edgeList.size();i++){
        ///if two vertex or groups root parent r same
        ///then it will be creat a cycle
        ///Then we won't add them
        ///else ↓
        if(FindRootParant(edgeList[i].u) != FindRootParant(edgeList[i].v)){

            join_components(edgeList[i].u , edgeList[i].v);
            cost+=edgeList[i].w;

            ///connecting edges
            cout<<edgeList[i].u<<"<->"<<edgeList[i].v<<" = "<<edgeList[i].w;el;
        }
    }
    return cost;
}

int main()
{
//   freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
//    ios_base::sync_with_stdio(0); cin.tie(0);
    int V,E;
    while(cin>>V>>E)
    {
        disjoint(V);///init

        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;
            edgeList.push_back({u,v,w});
        }
        int MST_Cost = kruskal();
        cout<<"MST COST = "<<MST_Cost;el;
    }
    return 0;
}
/**
INPUT Graph:
---------------

4 6
1 4 100
1 2 5
2 4 50
2 3 7
3 4 20
3 4 10

6 10
1 2 10
2 3 20
3 4 20
4 5 20
4 6 9
6 1 8
5 6 4
5 1 19
5 2 17
5 3 15
**/



