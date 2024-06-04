#include "search.h"
using namespace std;
const char separators[] = " .,-:!\"\'()?—[]“”‘’˙;@";
bool find(const char* text,int idx,int sz) {
    if(idx<0){return false;}
    else if(idx>=sz){return false;}
    else{for (int k = 0; separators[k] != '\0'; k++) {
        if (separators[k] == text[idx]) {
            return true;
        }
    }
    }
    return false;
}
Node* KMPSearch(const char* text,vector<int>w2, const char* pattern, int m, int n,Node* start,int &n_matches)
{   
    if (*pattern == '\0' || n == 0) {
        return start;
    }
    if (*text == '\0' || n > m) {
        return start;
    }
    int next[n + 1];
    for (int i = 0; i < n + 1; i++) {
        next[i] = 0;
    }
    for (int i = 1; i < n; i++)
    {
        int j = next[i];
        while (j > 0 && tolower(pattern[j]) != tolower(pattern[i])) {
            j = next[j];
        }
        if (j > 0 || tolower(pattern[j]) == tolower(pattern[i])) {
            next[i + 1] = j + 1;
        }
    }
    for (int i = 0, j = 0; i < m; i++)
    {
        if ( tolower(*(text + i)) == tolower(*(pattern + j)))
        {
            if (++j == n) 
            { 
             if((i-j+1==0||find(text,i-j,m))&&(i-j+n==m-1||find(text,i-j+n+1,m)))
             {Node* nainode=new Node(w2[0],w2[1],w2[2],w2[3],i-j+1);
             start->right=nainode;
             start=nainode;
             ++n_matches;}
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;   
        }
    }
    return start;
}
SearchEngine::SearchEngine(){
    vector<pair<vector<int>,string>> Corpus;
}

SearchEngine::~SearchEngine(){
   
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
  Corpus.push_back({{book_code,page,paragraph,sentence_no},sentence});
}

Node* SearchEngine::search(string pattern, int& n_matches) {
    Node* root=new Node();
    Node* p1=new Node();
    p1=root;
    n_matches=0;
    for(auto it=Corpus.begin();it!=Corpus.end();++it){
        int m=pattern.size(); 
        int n=it->second.size();
         const char* p=pattern.c_str();
         const char* w1=it->second.c_str();
         vector<int> w2=it->first;
        p1=KMPSearch(w1,w2,p,n,m,p1,n_matches);
    }
    return root->right;
    }
