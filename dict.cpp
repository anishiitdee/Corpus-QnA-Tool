// Do NOT add any other includes
#include "dict.h"
#include <iostream>
class FNVHash {
public:
    static unsigned long int CalculateHash(string p, unsigned long int length) {    
        unsigned long int h = 2166136261UL;
        for (unsigned long int i = 0; i < length; i++) {
            h = (h ^ p[i]) * 16777619;
        }
        return h;
    }
};
Dict::Dict(){
  size=0;
  capacity=200003;
  storage=vector<pair<string,int>>(capacity,make_pair("",0));
}

Dict::~Dict(){
   
}
string converter(string s){
    string out="";
  for(int i=0;i<s.length();++i){
    if(isupper(s[i])){out.push_back(_tolower(s[i]));}
    else{out.push_back(s[i]);}
  }
  return out;
}

vector<pair<string,int>> rehash(vector<pair<string,int>> storage,int inicap){
    vector<pair<string,int>> out(2*inicap,make_pair("",0));
    int newcap=2*inicap;
    for(int i=0;i<inicap;++i){
      if(storage[i].first==""){continue;}
      else{
        unsigned long int hash = FNVHash::CalculateHash(storage[i].first, storage[i].first.length());
        hash=hash%newcap;
        if(out[hash].first==""){
            out[hash]=storage[i];
        }
        else {
        int probe=0;
        while(out[hash].first != ""){
           int a=(i*i)%newcap;
           a=(a*i)%newcap;
           hash+=newcap;
           hash%=newcap;
            ++i;
        }
          out[hash]=storage[i];
        } 
      }
    }
 return out;
}


void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    sentence=converter(sentence);
    int p=capacity;
    string mystring="";
    string stop=" .,-:!\"\'()?—[]“”‘’˙;@";
   for(int i=0;i<=sentence.length()-1;++i){
    int s=0;
    char chara=sentence[i];
    while(chara!=stop[s]){++s;if(s==stop.length()){break;}}
    if(s==stop.length()){
        mystring=mystring+chara;
    }
    if(mystring!=""){
    if(s!=stop.length()||i==sentence.length()-1){
      int length=(mystring).length() - 1;
      unsigned long int hash = FNVHash::CalculateHash(mystring, length);
      hash=hash%p;
      if(storage[hash].first == ""){
      storage[hash].second+=1;
      storage[hash].first=mystring;
      ++size;
      }
      else {
        int i=0;
        while(storage[hash].first != ""){
           if(storage[hash].first==mystring){break;}
           int a=(i*i)%p;
           a=(a*i)%p;
           hash+=a;
           hash%=p;
            ++i;
        }
       storage[hash].second+=1;
       if(storage[hash].first==""){++size;}
       storage[hash].first=mystring;
      }
      mystring="";
    }
   }
    if(size>capacity*(0.75)){
        storage=rehash(storage,capacity);
        capacity=2*capacity;
    }
   }
    return;
}

int Dict::get_word_count(string word){
    word=converter(word);
    int p=capacity;
    // Implement your function here  
    int length=word.length() - 1;
    unsigned long int hash = FNVHash::CalculateHash(word, length);
      hash=hash%p;
        int i=0;
        while(storage[hash].first!=""&&storage[hash].first!=word){
           int a=(i*i)%p;
           a=(a*i)%p;
           hash+=a;
           hash%=p;
            ++i;
        }
        if(storage[hash].first==""){
            return 0;
        }
        else if(storage[hash].first==word){
            return storage[hash].second;
        }
    return -1;
}

void Dict::dump_dictionary(std::string filename) {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for(auto it:storage){
               if(it.first != ""){
                outputFile << it.first + "," + to_string(it.second) << endl;}
            }
            outputFile.close(); // Close the file when done
            }
        else {
            std::cerr << "Unable to open file" << std::endl;
        }
    } 
    