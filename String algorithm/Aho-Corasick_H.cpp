#include<bits/stdc++.h>
using namespace std;


struct Nod{
    int ch[26];
    int link;
    bitset<510>output;
    Nod(){
        build_Node();
    }
    void build_Node(){
        link=0;
        output.reset();
        memset(ch,0,sizeof ch);
    }

};

Nod nod[250010];/// (number_of_patterns x sizeof(pattern))

void create_Trie(string arr[],int n){

    int state=0;
    nod[0].build_Node();
    for(int i=0;i<n;i++){
        int currentState=0;
        for(int j=0;j<arr[i].size();j++){
            int c=arr[i][j]-'a';
            if(!nod[currentState].ch[c]){
                nod[currentState].ch[c]=++state;
                nod[state].build_Node();

            }
            currentState=nod[currentState].ch[c];
        }
        nod[currentState].output[i]=1;
    }
}

void build_Automaton(){
    queue<int>Q;
    for(int c=0;c<26;c++){
        if(nod[0].ch[c]!=0){
            nod[nod[0].ch[c]].link=0;
            Q.push(nod[0].ch[c]);
        }  
    }
    nod[0].link=0;
    while(Q.size()){
        int cur=Q.front();Q.pop();
        for(int c=0;c<26;c++){
            if(nod[cur].ch[c]){
                int failure=nod[cur].link;
                while(failure && !nod[failure].ch[c]){
                    failure=nod[failure].link;
                }
                failure=nod[failure].ch[c];
                nod[nod[cur].ch[c]].link=failure;
                nod[nod[cur].ch[c]].output|= nod[failure].output;
                Q.push(nod[cur].ch[c]);
            }
        }
    }
}
int find_NextState(int currentState,int nxt_ch){
    while(currentState && !nod[currentState].ch[nxt_ch]){
        currentState=nod[currentState].link;
    }
    return nod[currentState].ch[nxt_ch];
}
void searchWords(string arr[],int n,string &text){
    create_Trie(arr,n);
    build_Automaton();
    int currentState=0;
    for(int i=0;i<text.size();i++){
        int ch=text[i]-'a';
        currentState=find_NextState(currentState,text[i]-'a');
        if(nod[currentState].output.any()){
            for(int j=0;j<n;j++){
                if(nod[currentState].output[j]){// if i'th bit is on 
                    cout<<arr[j]<<" appears from "<<i-arr[j].size()+1<<" to "<<i<<"\n";
                }
            } 
        }
          

    }
}
void solve(int ks){
    //cout<<"Case "<<ks<<": ";
    string arr[] = {"he", "she", "hers", "his"}; 
    string text = "ahishers"; 
    int n = sizeof(arr)/sizeof(arr[0]); 

    searchWords(arr, n, text);

    
}

signed main()
{
#ifndef ONLINE_JUDGE
     freopen("inputf.in", "r", stdin);  ///To read from a file.
//    freopen("outputf.in", "w", stdout);  ///To write  a file.
#endif
    cin.tie(nullptr)->sync_with_stdio(false);
    int tks=1;
    //cin>>tks;
    for(int ks=1;ks<=tks;ks++){
        solve(ks);
    }
    //cerr<<"\nTime:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}
///invisible =  
