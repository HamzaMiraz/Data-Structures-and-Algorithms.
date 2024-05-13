#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int Size=30000+10;
vector<ll>ar;
vector<vector<ll>>tree;
vector<ll> marge(vector<ll>&a,vector<ll>&b){
    int n=a.size(),m=b.size();
    vector<ll>c;
    int i=0,j=0;
    while(i<n && j<m){
        if(a[i]<=b[j]){
            c.push_back(a[i]);
            i++;
        }else{
            c.push_back(b[j]);
            j++;
        }
    }
    while(i<n)c.push_back(a[i]),i++;
    while(j<m)c.push_back(b[j]),j++;
    return c;
}
void build(int node,int left,int right){
    if(left==right){
        tree[node].push_back(ar[left]);
        return ;
    }
    int mid=(left+right)/2;
    build(node*2,left,mid);
    build(node*2+1,mid+1,right);
    tree[node]=marge(tree[node*2],tree[node*2+1]);
}
int query(int node,int left,int right,int ql,int qr,ll k){///query left=ql,right=qr
    if(left>=ql && right<=qr){
        int ans= (int)tree[node].size()
        -(upper_bound(tree[node].begin(),tree[node].end(),k)-tree[node].begin());
        return ans;
    }
    int mid=(left+right)/2;
    if(qr<=mid){
        return query(2*node,left,mid,ql,qr,k);
    }
    else if(mid<ql){
        return query(2*node+1,mid+1,right,ql,qr,k);
    }
    else{
        int left_node=query(2*node,left,mid,ql,mid,k);
        int right_node=query(2*node+1,mid+1,right,mid+1,qr,k);
        return left_node+right_node;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,ql,qr,pos,new_val;
        cin>>n;
        ar.resize(n+5);
        tree.resize(4*(n+5));
        for(int i=1;i<=n;i++){
            cin>>ar[i];
        }
        build(1,1,n);
        // int q;cin>>q;
        // while(q--){
        //     ll k;
        //     cin>>ql>>qr>>k;
        //     cout<<query(1,1,n,ql,qr,k)<<"\n";

        // }

    return 0;
}
