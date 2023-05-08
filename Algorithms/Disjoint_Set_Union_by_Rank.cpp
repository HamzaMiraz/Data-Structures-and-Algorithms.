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
vector<int>Rank,parant;

void disjoinset(int V){
    Rank.resize(V+5,0);
    parant.resize(V+5);

    for(int i=0;i<=V;i++){
       parant[i]=i;
    }
}
/// finding root node and make all nodes parant node is root node
int FindRootParant(int node){
    if(node== parant[node])
        return node;
    return parant[node]=FindRootParant(parant[node]);
}
/// joining two  components
void union_by_rank(int u,int v){

    int u_parant=FindRootParant(u);
    int v_parant=FindRootParant(v);

    if(u_parant==v_parant)///both r alrady joined
        return ;
    if(Rank[u_parant]>Rank[v_parant]){
        parant[v_parant]=u_parant;
    }
    else if(Rank[u_parant]<Rank[v_parant]){
        parant[u_parant]=v_parant;
    }
    else{
        parant[v_parant]=u_parant;
        ++Rank[u_parant];
    }
}

int main()
{
//   freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
//    ios_base::sync_with_stdio(0); cin.tie(0);
    int V,E;
    while(cin>>V>>E)
    {
        disjoinset(V);
        for(int i=0;i<E;i++){
            int u,v;
            cin>>u>>v;
            union_by_rank(u,v);
        }
    ///chacking 3 and 7 r connected in a same component or not
        if(FindRootParant(3)==FindRootParant(7)){
            cout<<"same\n";
        }else{
            cout<<"Not same\n";
        }


        union_by_rank(3,7);/// joining two components

        cout<<"After joining them\n";

        ///chacking 3 and 7 r connected in a same component or not
        if(FindRootParant(3)==FindRootParant(7)){
            cout<<"same\n";
        }else{
            cout<<"Not same\n";
        }

        Rank.clear();
        parant.clear();
    }
    return 0;
}
/**
7 5

1 2
2 3
4 5
6 7
5 6

**/

