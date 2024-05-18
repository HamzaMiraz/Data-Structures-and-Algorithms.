#include<bits/stdc++.h>
using namespace std;

/// sl = segment left,sr = segment right, tree[nod] contain [sl-sr] range

typedef long long ll;/// 1e18;
//typedef __int128_t LL;/// 1e32;
#define F  first
#define S  second
const ll MOD = 1e9 +7;// Prime
const ll oo = 1e18+10;

struct LazyPropagation{
    int n;
    vector<ll>tre,lazy;///change data type
public:
    LazyPropagation(const vector<ll>&ar){///change data type
        n=ar.size();
        tre.resize(4*n + 10);
        lazy.resize(4*n + 10);
        build(ar,0,0,n-1);
    }
    inline ll query(int l, int r){return query(0, 0, n-1, l, r);}///change data type
    inline void update(int l,int r, ll val){return update(0, 0, n-1, l, r, val);}///change data type
    inline ll marge(ll left_node_val,ll right_node_val){///change data type
        return (left_node_val+right_node_val);///change
    }
    inline void lazyUpdate(int nod,int sl,int sr){
        if(lazy[nod]==0)return;
        //tre[nod] += lazy[nod];// change += or = // if we chaking for max,min 
        tre[nod] += lazy[nod]*(sr-sl+1);// change += or =
        if(sl!=sr){
            int left_child = 2*nod+1 , right_child = 2*nod+2;
            lazy[left_child] += lazy[nod], lazy[right_child] += lazy[nod];// change += or =
        }
        lazy[nod]=0;
    } 
private:
    void build(const vector<ll>&ar,int nod,int sl,int sr){///change data type
        lazy[nod]=0;
        if(sl==sr){
            tre[nod]=ar[sr];// root node
            return;
        }
        int mid = (sl+sr)/2;
        int left_child = 2*nod+1 , right_child = 2*nod+2;

        build(ar,left_child , sl , mid);
        build(ar,right_child , mid+1, sr);

        tre[nod] = marge(tre[left_child],tre[right_child]);
    }
    ll query(int nod,int sl,int sr,int ql,int qr){///change data type
        lazyUpdate(nod,sl,sr);
        if(ql<=sl && sr<=qr){///fully overlaped
            return tre[nod];
        }
        if(qr<sl || sr<ql)return 0;/// out of the range ,0/1/-oo/oo;
        int mid = (sl+sr)/2;
        int left_child = 2*nod+1 , right_child = 2*nod+2;

        return marge(query(left_child,sl,mid,ql,qr),query(right_child,mid+1,sr,ql,qr));
    }
    void update(int nod,int sl,int sr,int ql,int qr,ll val){///change data type
        lazyUpdate(nod,sl,sr);
        if(ql<=sl && sr<=qr){///fully overlaped
            lazy[nod]+=val;//+= or = both r same
            lazyUpdate(nod,sl,sr);
            return;
        }
        if(qr<sl || sr<ql)return;/// position is out of the range

        int mid = (sl+sr)/2;
        int left_child = 2*nod+1 , right_child = 2*nod+2;

        update(left_child,sl,mid,ql,qr,val);
        update(right_child,mid+1,sr,ql,qr,val);

        tre[nod]=marge(tre[left_child],tre[right_child]);
    }
};
void solve(){

    //zero based
    int n,q,ql,qr,ty;
    ll val;///change data type
    cin>>n>>q;
    vector<ll>ar(n);
    for(int i=0;i<n;i++) cin>>ar[i];

    LazyPropagation lt(ar);
    while(q--){
        cin>>ty;
        if(ty==1){
            cin>>ql>>qr>>val;
            lt.update(ql,qr,val);
        }else if(ty==2){
            cin>>ql>>qr;
            cout<<lt.query(ql,qr)<<"\n";
        }else{
            break;
        }
    }

}
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int t=1;
    //cin>>t;
    while(t--){
        solve();
    }
    //cerr<<"\nTime:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}
///invisible =  
