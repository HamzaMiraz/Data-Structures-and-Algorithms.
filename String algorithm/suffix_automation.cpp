#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomatonNode {
    unordered_map<char, int> next; 
    int link = -1;
    int length = 0;
};

vector<SuffixAutomatonNode> sa;
int last;

void initialize() {
    sa.clear();
    sa.push_back(SuffixAutomatonNode()); // root
    last = 0;
}

void extendAutomaton(char c) {
    int cur = sa.size();
    sa.push_back(SuffixAutomatonNode());
    sa[cur].length = sa[last].length + 1;

    int par = last;
    while (par != -1 && !sa[par].next.count(c)) {
        sa[par].next[c] = cur;
        par = sa[par].link;
    }

    if (par == -1) {
        sa[cur].link = 0;  // link to root
    } else {
        int q = sa[par].next[c];//q= char founded node
        if (sa[par].length + 1 == sa[q].length) {
            sa[cur].link = q;
        } else {
            int clone = sa.size();
            sa.push_back(sa[q]);   // copy q
            sa[clone].length = sa[par].length + 1;
            // change all the nodes direction to clone, whos are pointing node q
            while (par != -1 && sa[par].next[c] == q) {
                sa[par].next[c] = clone;
                par = sa[par].link;
            }

            sa[q].link = sa[cur].link = clone;
        }
    }

    last = cur;
}

void traverseAutomaton() {
    cout << "Traversing Suffix Automaton:\n";
    for (int i = 0; i < sa.size(); ++i) {
        cout << "State " << i << ", Length: " << sa[i].length 
             << ", Suffix Link: " << sa[i].link << "\n";
        for (auto &t : sa[i].next) {
            cout << "  '" << t.first << "' -> " << t.second << "\n";
        }
    }
}

int main() {
    string input = "abab";
    initialize();

    for (char c : input) extendAutomaton(c);
    traverseAutomaton();

    return 0;
}
