struct node{
    bool End;
    vector<node*>next;
    node(): End(false),next(26,nullptr){}
    // node(){
    //     End=false;
    //     next.resize(26,nullptr);
    // }
};

class Trie {
public:
    node* root;
    Trie() {
        root=new node();
    }
    
    void insert(string &word) {
        node*cur=root;
        for(auto ch : word){
            if(!cur->next[ch-'a'])cur->next[ch-'a']=new node();
            cur=cur->next[ch-'a'];
        }
        cur->End=true;
    }
    
    bool search(string &word) {
        node*cur=root;
        for(auto ch : word){
            if(!cur->next[ch-'a'])return false;
            cur=cur->next[ch-'a'];
        }
        return cur->End;
    }
    
    bool startsWith(string &prefix) {
        node*cur=root;
        for(auto ch : prefix){
            if(!cur->next[ch-'a'])return false;
            cur=cur->next[ch-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */