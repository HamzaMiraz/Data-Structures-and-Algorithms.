#include <bits/stdc++.h>
using namespace std;

vector<int>make_lps(string &s){
    vector<int>lps(s.size()+1,0);/// longest prefix also a suffix
    for(int i=1;i<s.size();i++){
        int j=lps[i-1];
        while(j>0 && s[i]!=s[j])j=lps[j-1];

        if(s[i]==s[j])lps[i]=++j;
    }
    return lps;
}
void kmp(string &txt,string &pat){

    vector<int>lps=make_lps(pat);

    int t(0),p(0);
    while(t<txt.size()){
        if(txt[t]==pat[p])++t,++p;
        else{
            if(p!=0)p=lps[p-1];
            else{
                ++t;
            }
        }
        if(p==pat.size()){
            int pos=t-pat.size()+1;///one add for one based
            cout<<pos<<"\n";
            p=lps[p-1];
        }
    }
}
int main(){
    string pat,txt;
    while(cin>>txt>>pat){
        kmp(txt,pat);
    }
    return 0;
}
