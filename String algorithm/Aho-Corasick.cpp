#include <bits/stdc++.h>

using namespace std;

struct AC {
  int N, P;
  const int A = 26;
  vector <vector <int>> next;
  vector <int> link, out_link;
  vector <vector <int>> out;
  vector<int>occr;
  AC(): N(0), P(0) {node();}
  
  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    occr.emplace_back(0);
    return N++;
  }

  inline int get (char c) {
    return c - 'a';
  }

  int add_pattern (const string &T) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    out[u].push_back(P);
    return P++;
  }

  void compute() {
    queue <int> q;
    for (q.push(0); !q.empty();) {
      int u = q.front(); q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c];
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
      }
    }
  }

  int advance (int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)];
    return u;
  }

  void match (const string &text,string pattern[]){
    int u = 0;
    for (int i=0;i<text.size();i++) {
      u = advance(u, text[i]);
      for (int v = u; v; v = out_link[v]) {
        for (auto p : out[v]) 
            cout << "found " << pattern[p] <<" form "<<i-pattern[p].size()+1<<" to "<<i<<"\n"
            ,occr[p]++;
      }
    }
  }
};

int main() {
int n; 
  while(cin >> n){;
  AC aho;
  string pattern[n+2];
  for(int i=0;i<n;i++) {
    cin >> pattern[i];
    aho.add_pattern(pattern[i]);
  }
  aho.compute();
  string text; cin >> text;
  aho.match(text,pattern);
  for(int i=0;i<n;i++){
    cout<<pattern[i]<<" occurs "<<aho.occr[i]<<" times\n";
  }
}
  return 0;
}
/*

5
hamza miraz jahid bipul naim
hamzaamirmirazjahidbipulbipulrajuhamzahamzajahid

*/