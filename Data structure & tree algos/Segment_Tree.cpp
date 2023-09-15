#include<bits/stdc++.h>
using namespace std;

const int Size=10000;
int ar[Size];
int tree[4*Size];
void build(int node,int left,int right){
    if(left==right){
        tree[node]=ar[left];
        return ;
    }
    int mid=(left+right)/2;
    build(node*2,left,mid);
    build(node*2+1,mid+1,right);
    tree[node]=tree[node*2]+tree[node*2+1];
    //tree[node]=max(tree[node*2],tree[node*2+1]);
    //tree[node]=min(tree[node*2],tree[node*2+1]);
}
int query(int node,int left,int right,int ql,int qr){///query left=ql,right=qr
    if(left>=ql && right<=qr){
        return tree[node];
    }
    int mid=(left+right)/2;
    if(qr<=mid){/// range is left of mid
        return query(2*node,left,mid,ql,qr);
    }
    else if(mid<ql){/// range is right of mid
        return query(2*node+1,mid+1,right,ql,qr);
    }
    else{/// range is partially overlap
        int left_node=query(2*node,left,mid,ql,mid);
        int right_node=query(2*node+1,mid+1,right,mid+1,qr);
        return left_node+right_node;
        //return max(left_node,right_node);
        //return min(left_node,right_node);
    }
}
void update(int node,int left,int right,int pos)
{
    if(left==pos && right==pos){
        tree[node]= ar[pos];
        return;
    }
    int mid = (left+right)/2;
    if(pos<=mid && pos>=left)///if pos in lower left
        update(node*2,left,mid,pos);
    else
        update(node*2+1,mid+1,right,pos);/// if pos in lower right
    tree[node] = tree[node*2] + tree[(node*2)+1];
//    tree[node] = min(tree[node*2],tree[(node*2)+1]);
//    tree[node] = max(tree[node*2],tree[(node*2)+1]);
}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int n,ql,qr,pos,new_val;;
    while(cin>>n){
        for(int i=1;i<=n;i++){
            cin>>ar[i];
        }
        build(1,1,n);
        while(1){
            int qtype;cin>>qtype;
            if(qtype==1){///query
                cin>>ql>>qr;
                cout<<query(1,1,n,ql,qr)<<"\n";
            }else if(qtype==2){///update
                cin>>pos>>new_val;
                ar[pos]=new_val;
                update(1,1,n,pos);
            }else{
                break;
            }
        }
    }
    return 0;
}
