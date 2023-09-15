#include <bits/stdc++.h>

using namespace std;
struct Node {
    Node * links[26];
    int cntword = 0;
    int cntPrefix = 0;

    bool next_exist(char ch) {
        return (links[ch - 'a'] != NULL);
    }
    void create_ref_nod(char ch, Node * node) {
        links[ch - 'a'] = node;
    }
    Node * next(char ch) {
        return links[ch - 'a'];
    }
    void increaseWordFrequency() {
        cntword++;
    }
    void increasePrefixFrequency() {
        cntPrefix++;
    }
    void deleteWordFrequency() {
        cntword--;
    }
    void reducePrefixFrequency() {
        cntPrefix--;
    }
    int WordFrequency() {
        return cntword;
    }
    int PrefixFrequency() {
        return cntPrefix;
    }
};
class Trie {
private:
    Node * root;
public:
/** Initialize your data structure here. */
    Trie() {
    root = new Node();
}

/** Inserts a word into the trie. */
    void insert(string word) {
        Node * node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node -> next_exist(word[i])) {
                node -> create_ref_nod(word[i], new Node());
            }
            node = node -> next(word[i]);
            node -> increasePrefixFrequency();
        }
        node -> increaseWordFrequency();
    }

    int countWordsEqualTo(string &word){
        Node *node = root;
        for (int i = 0; i < word.length(); i++){
            if (!node->next_exist(word[i])){
                return 0;
            }
            node = node->next(word[i]);
        }
        return node->WordFrequency();
    }

    int countWordsStartingWith(string & word) {
        Node * node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node -> next_exist(word[i])) {
                return 0;  
            } 
            node = node -> next(word[i]);
        }
        return node -> PrefixFrequency();
    }

    void erase(string & word) {
        Node * node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node -> next_exist(word[i])) {
                return ;
            } 
            node = node -> next(word[i]);
            node -> reducePrefixFrequency();
        }
        node -> deleteWordFrequency();
    }
};

int main() {
  Trie T;
  T.insert("apple");
  T.insert("apple");
  T.insert("apps");
  T.insert("apps");
  string word1 = "apps";
  cout<<"Count Words Equal to "<< word1<<" "<<T.countWordsEqualTo(word1)<<endl;
  string word2 = "abc";
  cout<<"Count Words Equal to "<< word2<<" "<<T.countWordsEqualTo(word2)<<endl;
  string word3 = "ap";
  cout<<"Count Words Starting With "<<word3<<" "<<T.countWordsStartingWith(word3)
  <<endl;
  string word4 = "appl";
  cout<<"Count Words Starting With "<< word4<<" "<<T.countWordsStartingWith(word4)
  <<endl;
  T.erase(word1);
  cout<<"Count Words equal to "<< word1<<" "<<T.countWordsEqualTo(word1)<<endl;
  return 0;
}