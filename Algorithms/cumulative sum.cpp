#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    int ar[n+5],pre[n+5];
    for(int i=1;i<=n;i++)cin>>ar[i];
    pre[0]=0;
    pre[1]=ar[1];
    for(int i=2;i<=n;i++){
        pre[i]=pre[i-1]+ar[i];
    }
    for(int i=1;i<=n;i++){
        cout<<pre[i]<< " ";
    }
    cout<< "\n";

    int l,r;
    cin>>l>>r;///range
    cout<<"sum of "<<l<<"to "<<r<<" range is "<<pre[r]-pre[l-1]<<endl;

  return 0;
}

