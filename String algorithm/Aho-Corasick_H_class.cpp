#include<bits/stdc++.h>
using namespace std;


///Time Complexity: O(n + l + z), where ‘n’ is the length of the text, ‘l’(sum of all ptrns len) is the length of keywords, and ‘z’ is the number of matches.

const int MX_P = 100;/// maximum number of patterns
struct AhoCorasick{

    int nod_no,ptrn_no;
    const int root = 0;
    vector<vector<int>>next;
    vector<int>link;///suffix link/failure link
    vector<bitset<MX_P>>output;///bitset points which which patterns output indicated by this state
    bitset<MX_P>zero;/// zero
    vector<int>occr;

    AhoCorasick(): nod_no(0),ptrn_no(0){node();}

    int node(){
        next.emplace_back(26,0);
        link.emplace_back(root);/// all link initilize by root; 
        output.emplace_back(zero);/// each node initilize by 0 set bit
        occr.emplace_back(0);///each pattern occraance initilize by zero
        return nod_no++;/// increase node count 
    }

    void add_pattern(const string &s){///trie building
        int currentState=root;
        for(auto c : s){
            int ch=c-'a';
            if(!next[currentState][ch])
                next[currentState][ch]=node();/// node()=create a new node in this state and also next[currentState][ch] set with a state number 
            currentState=next[currentState][ch];
        }
        output[currentState][ptrn_no]=1;/// this states end point of  prth_no th pattern
        //output[currentState].set(patn_no,1);
        ptrn_no++;//increse pattern count 
   
    }

    void build_Automaton(){
        queue<int>Q;
        for(int ch=0;ch<26;ch++){
            if(next[root][ch]){
                int stat_lvl1=next[root][ch];/// stat_lvl1=state which connect with root
                link[stat_lvl1]=root;///make level 1 states failure link with root  
                Q.push(stat_lvl1);
            }
        }
        while(Q.size()){
            int currentState=Q.front();Q.pop();
            for(int ch =0;ch<26;ch++){
                if(next[currentState][ch]){
                    int child_state=next[currentState][ch];
                    int failure=link[currentState];

                    while(failure!=root && !next[failure][ch])///finding failure node
                        failure=link[failure];
                    failure=next[failure][ch];

                    link[child_state]=failure;
                    output[child_state]|=output[failure];///a state also indicate failure_states all outputs 
                    Q.push(child_state);
                }
            }
        }
    }
    int find_NextState(int currentState,int ch){
        while(currentState!=root && !next[currentState][ch])
            currentState=link[currentState];
        
        return currentState=next[currentState][ch];
    }
    void searchWords(string pattern[],string &text){
        int currentState=0;
        for(int i=0;i<text.size();i++){
            int ch=text[i]-'a';
            currentState=find_NextState(currentState,ch);
            if(output[currentState].any()){// chacking this state point any output
                for(int j=0;j<ptrn_no;j++){
                    if(output[currentState][j]){// if i'th bit is on 
                        cout<<pattern[j]<<" appears from "<<i-pattern[j].size()+1<<" to "<<i<<"\n";
                        occr[j]++;/// increse j'th patterns occarence
                    }
                }
            }
        }
    }
};

void solve(int ks){
    //cout<<"Case "<<ks<<": ";
    int n;cin>>n;
    string pattern[n+1];
    string text;
    AhoCorasick aho;
    for(int i=0;i<n;i++){
        cin>>pattern[i];
        aho.add_pattern(pattern[i]);
    }
    cin>>text;
    aho.build_Automaton();
    aho.searchWords(pattern,text);
    for(int i=0;i<n;i++){
        cout<<pattern[i]<<" occurs "<<aho.occr[i]<<" times\n";
    }
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

/*
5
hamza miraz jahid bipul naim
hamzaamirmirazjahidbipulbipulrajuhamzahamzajahid
*/
