#include <bits/stdc++.h>
using namespace std;

/// sl = segment left,sr = segment right, tree[nod] contain [sl-sr] range
#define ll long long
const int MAX_N =100007;
const int oo = 2e9+10;
int ar[MAX_N];
struct ST{
    ll tree[4*MAX_N];
    ST(){
        clear();
    }
    void clear(){
        memset(tree,0,sizeof tree);
        //memset(ar,0,sizeof ar);
    }
    void build(int nod,int sl,int sr){
        if(sl==sr){
            tree[nod]=ar[sr];// root node
            return;
        }
        int mid = (sl+sr)/2;
        int left_child = 2*nod , right_child = 2*nod+1;

        build(left_child , sl , mid);
        build(right_child , mid+1, sr);

        tree[nod] = tree[left_child] + tree[right_child];///change
    }
    int query(int nod,int sl,int sr,int ql,int qr){
        if(sl>=ql && sr<=qr){///fully overlaped
            return tree[nod];
        }
        if(qr<sl || ql>sr)return 0;/// out of the range ,0/-oo/oo;
        int mid = (sl+sr)/2;
        int left_child = 2*nod , right_child = 2*nod+1;
        
        return query(left_child,sl,mid,ql,qr)+query(right_child,mid+1,sr,ql,qr);///change
    }
    void update(int nod,int sl,int sr , int pos,int val){
        if(pos==sl && pos==sr){
            tree[nod]=val;//ar[pos];
            return;
        }
        if(pos>sr || pos<sl)return;/// position is out of the range

        int mid = (sl+sr)/2;
        int left_child = 2*nod , right_child = 2*nod+1;

        update(left_child,sl,mid,pos,val);
        update(right_child,mid+1,sr,pos,val);

        tree[nod]=tree[left_child]+tree[right_child];///change
    }
}st;

signed main(){
    int n,q,ql,qr,ty,pos;
    int val;
    while(cin>>n){
        for(int i=1;i<=n;i++){
            cin>>ar[i];
        }
        st.build(1,1,n);
        while(1){
            cin>>ty;
            if(ty==1){
                cin>>pos>>val;
                ar[pos]=val;
                st.update(1,1,n,pos,val);
            }else if(ty==2){
                cin>>ql>>qr;
                cout<<st.query(1,1,n,ql,qr)<<"\n";
            }else{
                break;
            }
        }
        st.clear();


    }
    return 0;
}


