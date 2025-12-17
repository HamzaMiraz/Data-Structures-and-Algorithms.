#include<bits/stdc++.h>
using namespace std;

//For Debugging
#define debug(a...)          {cout<<__LINE__<<" #--> ";dbg,a; cout<<endl;}
struct debugger
{
    template<typename T> debugger& operator , (const T v)
    {
        cout<<v<<" ";
        return *this;
    }
} dbg;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>using iset=tree<T,null_type,less<T>,///descending_order=greater<T>,multi_iset=less_equal<T>
rb_tree_tag,tree_order_statistics_node_update> ;///exmp= iset<double>st
///who is k'th position= *(set.find_by_order(k)),index of v = set.order_of_key(v);

typedef long long ll;/// 1e18;
//typedef __int128_t LL;/// 1e32;
template <typename T>
T BIGMOD(T base,T power,T Mod=1e9+7){T ans = 1;
while(power){if(power & 1)ans = (ans * base) % Mod;
base = (base * base) % Mod;power = power >> 1;}return ans;}

template <typename T>
T INV(T base,T mod=1e9+7){//defult mod=1e9+7
    return BIGMOD(base%mod,mod-2,mod)%mod;///base^-1
}

template <typename T>
T nCr(T n, T r){T res=1;for (T i=0;i<r;i++){
res *= (n-i);res /= (i+1);}return res;}/// NCR

template <typename T>
T fact(T n){if(n<=1)return 1;return n*fact(n-1);}

template <typename T>
T nPr(T n, T r){return fact(n)/fact(n-r);}///NPR


#define deb(a)     cout<<__LINE__<<"# "<<#a<<" -> "<<a<<endl;
#define all(x) x.begin(), x.end()
#define loop(IV,INIT,NV) for(int IV=INIT;IV<=NV;IV++)
#define lbv(vec,x) lower_bound(all(vec),x)-vec.begin()//retrun index
#define ubv(vec,x) upper_bound(all(vec),x)-vec.begin()
#define lba(ar,n,x) lower_bound(ar,ar+n,x)-&ar[0];//return index
#define uba(ar,n,x) upper_bound(ar,ar+n,x)-&ar[0];
#define lb(mp,x) mp.lower_bound(x);///for set,map
#define ub(st,x) st.upper_bound(x);///return pointer address
#define GCD(a,b)  __gcd(a,b)
#define LCM(a,b)  (a*b)/__gcd(a,b)
#define sqr(a)    ((a)*(a))
#define deg(n)  n*PI/180 /// redian to degree
#define sp(n,d)  fixed << setprecision(d) <<n
#define pb emplace_back
#define F  first
#define S  second
#define ss " "
#define nn printf("\n");
#define el cout<<"\n";
#define yes cout<<"Yes\n";
#define no cout<<"No\n";
#define YES cout<<"YES\n";
#define NO cout<<"NO\n";

template <typename T>
using minHeap = priority_queue<T, vector<T>, greater<T>>;

const double PI = acos(-1);
const double EPS = 1e-9; ///1*10^-7
const int oo = 1e9+10;
const ll MOD = 1e9 +7;// Prime


struct P
{
    double x,y;
    // P(){
    //     x=y=0;
    // }

    // P(double x,double y){
    //     this->x=x;
    //     this->y=y;
    // }

    // bool operator<(const P &b)const{
    //     if(x!=b.x)  return x<b.x;
    //     return y<b.y;
    // }

    // void scan(){cin>>x>>y;}
    // void print(){cout<<x<<"  "<<y<<endl;}
};

P pvt;
P vec(P a,P b){return {b.x-a.x,b.y-a.y};}
double Cross(P a,P b){return a.x*b.y-a.y*b.x;}
double eDis(P a,P b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}

bool comp(P a,P b)
{
    double c = Cross(vec(pvt,a),vec(pvt,b));

    if(c) return c>0;
    return eDis(pvt,a)<eDis(pvt,b);

}

vector<P> makeConvexHull(vector<P> p)
{
    int nConvex=p.size(),i,j;

    if(nConvex<2) return p;

/**     IF ALL POINTS ARE CO-LINER   */

//    j=0;
//    for(i=2;i<nConvex;i++)
//        if(Cross(vec(p[0],p[1]),vec(p[0],p[i]))==0)
//            j++;
//    if(j+2==nConvex)  return P

    pvt=p[0];
    for(int i=1;i<nConvex;i++)
        if(pvt.y>p[i].y)    pvt=p[i];
        else if(pvt.y==p[i].y && pvt.x>p[i].x)    pvt=p[i];

    sort(all(p),comp);

    j=2;
    for(int i=2;i<nConvex;i++)
    {
        //while(j>1 && Cross(vec(p[j-2],p[j-1]),vec(p[j-2],p[i]))<=0) skip same line
        while(j>1 && Cross(vec(p[j-2],p[j-1]),vec(p[j-2],p[i]))<0)    j--;
        p[j++]=p[i];
    }
    p.resize(j);
    return p;
}

void solve(int n) {
    
    vector<P>v;
    for(int i=0;i<n;i++){
        double x,y;cin>>x>>y;
        v.push_back({x,y});
    }
    double Perimeter=0;
    if(n==1){
        cout<<"("<<sp(v[0].x,1)<<","<<sp(v[0].y,1)<<")\n";
        cout<<"Perimeter length = "<<sp(Perimeter,2)<<"\n";
        return;
    }


    v=makeConvexHull(v);
    reverse(all(v));
    for(int i=0;i<v.size();i++){
        cout<<"("<<sp(v[i].x,1)<<","<<sp(v[i].y,1)<<")-";
        Perimeter+=(eDis(v[i],v[(i+1)%v.size()]));
    }
    cout<<"("<<sp(v[0].x,1)<<","<<sp(v[0].y,1)<<")\n";
    cout<<"Perimeter length = "<<sp(Perimeter,2)<<"\n";
    
}

signed main()
{
#ifndef ONLINE_JUDGE
     freopen("inputf.in", "r", stdin);  ///To read from a file.
//    freopen("outputf.in", "w", stdout);  ///To write  a file.
#endif
    cin.tie(nullptr)->sync_with_stdio(false);
    ll tks=1;
    int n;
    while(cin>>n){
        if(n==0)break;
        if(tks!=1){
            cout<<"\n";
        }
        cout<<"Region #"<<tks<<":\n";
        solve(n);
        tks++;
    }
    //cerr<<"\nTime:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}
///invisible =  