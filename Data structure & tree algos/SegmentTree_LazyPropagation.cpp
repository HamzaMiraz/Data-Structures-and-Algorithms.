#include<bits/stdc++.h>
using namespace std;

const int Size=10000;
int ar[Size];
int tree[4*Size];
int lazy[4*Size];

void lazyUpdate(int node,int left,int right,int lazy_val){
    ///left to right all values add by lazy val
    tree[node]+=(right-left+1)*lazy_val;
    if(left!=right){
        lazy[node*2]+=lazy_val;
        lazy[node*2+1]+=lazy_val;
    }

    ///left to right all values convert to lazy val
//    tree[node]=(right-left+1)*lazy_val;
//    if(left!=right){
//        lazy[node*2]=lazy_val;
//        lazy[node*2+1]=lazy_val;
//    }
}
void LPUpdate(int node,int left,int right,int ql,int qr,int val){
    if(lazy[node]!=0){
        lazyUpdate(node,left,right,lazy[node]);
        lazy[node]=0;
    }
    if(ql>right || qr<left || left>right)return;
    if(left>=ql && right<=qr){
        lazyUpdate(node,left,right,val);
        return;
    }
    int mid=(left+right)/2;
    LPUpdate(node*2,left,mid,ql,qr,val);
    LPUpdate(node*2+1,mid+1,right,ql,qr,val);

    tree[node]=tree[node*2]+tree[node*2+1];
    //tree[node]=max(tree[node*2],tree[node*2+1]);
    //tree[node]=min(tree[node*2],tree[node*2+1]);

}
int query(int node,int left,int right,int ql,int qr){///query left= ql,query right =qr
    if(lazy[node]!=0){
        lazyUpdate(node,left,right,lazy[node]);
        lazy[node]=0;
    }
    if(ql>right || qr<left || left>right) return 0;///return for max =-oo, for min=oo
    if(left>=ql && right<=qr){
        return tree[node];
    }
    int mid=(left+right)/2;
    int left_node=query(node*2,left,mid,ql,qr);
    int right_node=query(node*2 +1,mid+1,right,ql,qr);

    return left_node+right_node;
    //return max(left_node,right_node);
    //return min(left_node,right_node);
}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int n,ql,qr,val;;
    while(cin>>n){
        memset(tree,0,sizeof tree);
        memset(lazy,0,sizeof lazy);
        for(int i=1;i<=n;i++){
            cin>>ar[i];
            LPUpdate(1,1,n,i,i,ar[i]);
        }
        while(1){
            int qt;cin>>qt;
            if(qt==1){///query
                cin>>ql>>qr;
                cout<<query(1,1,n,ql,qr)<<endl;
            }
            else if(qt==2){///range update by val
                cin>>ql>>qr>>val;
                LPUpdate(1,1,n,ql,qr,val);
            }
            else{
                break;
            }
        }

    }
    return 0;
}
