#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;
class paranode{
    public:
    Node* node;
     long double count=0;
    paranode* next=nullptr;
};
class Heap{
    public:
    vector<paranode*> mainvec;
    void heapifyup(int idx){
       if(((idx-1)/2)<0){
        return;
       }
       else{
        if(mainvec[idx]->count>mainvec[((idx-1)/2)]->count){
            paranode*  a=mainvec[idx];
            mainvec[idx]=mainvec[((idx-1)/2)];
            mainvec[((idx-1)/2)]=a;
            heapifyup((idx-1)/2);
        }
       }
    }

    void heapifydown(int idx){
       int maxidx=idx;
       if(2*idx+1>=mainvec.size()){
        return;
       }
       if(mainvec[2*idx+1]->count>mainvec[maxidx]->count){
           maxidx=2*idx+1;
       }
       if(2*idx+2<mainvec.size()&&mainvec[2*idx+2]->count>mainvec[maxidx]->count){
        maxidx=2*idx+2;
       }
      if(maxidx!=idx){
            paranode* a=mainvec[idx];
            mainvec[idx]=mainvec[maxidx];
            mainvec[maxidx]=a;
            heapifydown(maxidx);       
      }
    }
    void buildheap(vector<paranode*> unsortedarr)
    {
      int sz=unsortedarr.size();
      mainvec=unsortedarr;
      for(int idx=sz/2-1;idx>=0;--idx){
       heapifydown(idx);
      }
    return;
    }
    Node* gettopk(int k,paranode* first){
         vector<paranode*> vec1;
         paranode* curr=first;
         while (curr!=nullptr){
            vec1.push_back(curr);
            curr=curr->next;
         }
         buildheap(vec1);
         Node* start=mainvec[0]->node;
        //  cout<<mainvec[0]->count<<endl;
         mainvec[0]=mainvec[mainvec.size()-1];mainvec.pop_back();
        if(mainvec.size()!=0){
         buildheap(mainvec);}
         Node* ans=start;
         for(int i=0;i<k-1;++i){
         ans->right=mainvec[0]->node;
        // cout<<mainvec[0]->count<<endl;
        mainvec[0]=mainvec[mainvec.size()-1];
        mainvec.pop_back();
        if(mainvec.size()!=0){
         buildheap(mainvec);}
         ans=ans->right;
         }
         ans->right=nullptr;
         return start;
    }
};
class TrieNode {
 public:
    vector<TrieNode*> children;   
    bool isEndOfWord=false;
    long double count;

TrieNode(){
    children=vector<TrieNode*>(123,nullptr);
    isEndOfWord=false;
    count=0;
}
// Insert a word into  Trie
void insertWord(const std::string& word, long double count) {
    TrieNode* current = this;
    for (char c : word) {      
        if (current->children[(int)c] == nullptr){
            current->children[(int)c] = new TrieNode();
        }
        current = current->children[(int)c];
    }
    current->isEndOfWord=true;
    current->count=count;
}

TrieNode* create(string a) {
    std::string file_path = a;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open  file.2" << std::endl;
        return 0;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string word;
        std::string countStr;  // Read count as a string
        if (std::getline(lineStream, word, ',') && std::getline(lineStream, countStr)) {
            if(countStr=="count"){continue;} 
            long double count = std::stoll(countStr);  // Convert countStr to an integer
            this->insertWord(word,count);           
        }
    }
    return this;
    // Free memory by deleting  Trie
    // Implement a function to free  memory for  Trie nodes.
}
long double csvsearch(TrieNode* root,string s){
    TrieNode* curr=root;
    for(int i=0;i<s.length();++i){
        if((curr->children[(int)s[i]])==nullptr){
            return 0;
        }
        else if(i!=s.length()-1){
            curr=curr->children[(int)s[i]];
        }
        else {
            curr=curr->children[(int)s[i]];
            if(curr->isEndOfWord==false){
                return 0;
            }
            else{return curr->count;}
        }
    }
    return 0;
}
};
void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
   	mysearch.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    d.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}
QNA_tool::QNA_tool(){
     SearchEngine* n=new SearchEngine;
     mysearch=*n;
    // Implement your function here  
}
QNA_tool::~QNA_tool(){
    // Implement your function here  
}
bool find(string s,char c){
    for(int i=0;i<s.length();++i){
        if(s[i]==c){return true;}
    }
    return false;
 }
void tolowerC(std::string& str){
    for (char& c : str) {
        c = tolower(c);
    }
    return ;
}
 void QNA_tool:: insertparasearchcorpus(){
    for(int i=1;i<=98;++i){       
    string FILE="mahatma-gandhi-collected-works-volume-"+to_string(i)+".txt";
    std::ifstream inputFile(FILE);
    if (!inputFile.is_open()){
        std::cerr << "Error: Unable to open  input file.1" << std::endl;
        return ;
    }
    std::string tuple;
    std::string sentence;
    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)){
        // Get a line in  sentence
        tuple += ')';
        std::vector<int> metadata;    
        std::istringstream iss(tuple);
        // Temporary variables for parsing
        std::string token;
        // Ignore  first character ( opening parenthesis)
        iss.ignore(1);
        // Parse and convert  elements to integers
        while (std::getline(iss, token, ',')){
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start!=std::string::npos && end != std::string::npos) {
                token=token.substr(start, end - start + 1);
            }
            // Check if  element is a number or a string
            if (token[0] == '\'') {
                // Remove  single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata.push_back(num);
            } else {
                // Convert  element to integer
                int num = std::stoi(token);
                metadata.push_back(num);
            }
        }
    mysearch.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
    d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
    }  
  }
 }
bool ahead(paranode* curr,Node* curr1){
    if (curr==nullptr) return true;
    if(curr->node->book_code>curr1->book_code){
        return true;
    }
    else if(curr->node->book_code==curr1->book_code){
     if(curr->node->page>curr1->page){
        return true;
    }
    else if(curr->node->page==curr1->page){
      if(curr->node->paragraph>curr1->paragraph){
        return true;
      }
      else{return false;}
    }
    else{return false;}
    } 
    else {return false;}
    return false;
}
bool matches(paranode* curr,Node* curr1){
    if(curr1->book_code==curr->node->book_code&&curr1->paragraph==curr->node->paragraph&&curr1->page==curr->node->page){
        return true;
    }
    return false;
}
Node* QNA_tool::get_top_k_para(string question, int k){
     TrieNode* root=new TrieNode();
     root=root->create("unigram_freq.csv");
     string punctuations=" .,-:!\"\'()?—[]“”‘’˙;@";
     string currwd="";
            Node* ni=new Node();
            ni->book_code=1;
            ni->offset=0;
            ni->paragraph=0;
            ni->sentence_no=0;
            ni->page=0;
            paranode* first=new paranode;
            first->node=ni;
            first->count=0;
            first->next=nullptr;
     for(int it=0;it<question.length();++it){     
         if(!find(punctuations,question[it])){
             currwd+=question.substr(it,1);
         }
         else if(currwd!="")
    {       int n_matches=0;
            tolowerC(currwd);  
            long double csvcount=root->csvsearch(root,currwd);
            Node* first1=mysearch.search(currwd,n_matches);
            long double cnt=d.get_word_count(currwd);
            // cout<<currwd<<" "<<n_matches<<" "<<cnt<<" "<<csvcount<<endl;         
            long double score=((1.0*(cnt+1))/((csvcount+1)));
            Node* curr1=first1;
            int tempcount=0;
            paranode* curr=first;
   while(curr1!=nullptr){
    if(matches(curr,curr1))
         {                          
         ++tempcount;
         curr1=curr1->right;
         if(curr1==NULL){
           long double weight=tempcount*score;
           curr->count+=weight;
          }
         }
    else
    {   
       long double weight=tempcount*score;
      curr->count+=weight;
      paranode* prev=curr;
      curr=curr->next;
      tempcount=0;
     if(ahead(curr,curr1)){   
      paranode* tobeinsertedinbtw=new paranode;
      tobeinsertedinbtw->node=curr1;
      tobeinsertedinbtw->count=0;
      prev->next=tobeinsertedinbtw;
      tobeinsertedinbtw->next=curr;
      curr=tobeinsertedinbtw;
      }
    }
   }
  currwd="";
  }
 }
//    while(trial!=nullptr){
//     if(trial->node->book_code==51&&trial->node->page==322&&trial->node->paragraph==1){
//     cout<<trial->count<<" "<<trial->node->book_code<<" "<<trial->node->page<<" "<<trial->node->paragraph<<endl;}
//     trial=trial->next;
//    }
   Heap H;
   Node* topk=H.gettopk(k,first);
   Node* curr=topk;
   return topk;
}
void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){
    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";
    std::ifstream inputFile(filename);
    std::string tuple;
    std::string sentence;
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open  input file " << filename << "." << std::endl;
        exit(1);
    }
    std::string res = "";
    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in  sentence
        tuple += ')';
        int metadata[5];
        std::istringstream iss(tuple);
        // Temporary variables for parsing
        std::string token;
        // Ignore  first character ( opening parenthesis)
        iss.ignore(1);
        // Parse and convert  elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }          
            // Check if  element is a number or a string
            if (token[0] == '\'') {
                // Remove  single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert  element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }
        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }
    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){
    // first write  k paragraphs into different files
    Node* traverse = root;
    int num_paragraph = 0;
    while(num_paragraph < k){       
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete  file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;      
    }
    // write  query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are  excerpts from Mahatma Gandhi's books.\nOn  basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
    // you do not need to necessarily provide k paragraphs - can configure yourself
    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";
    system(command.c_str());
    return;
}
// int main() {
//     QNA_tool qnaTool;
//     // Call  insertparasearchcorpus function to populate your data structures
//     qnaTool.insertparasearchcorpus();
//     // Create a sample question and specify  number of top paragraphs (k)
//     std::string question = "Who was Mahatma Gandhi?";
//     int k = 8;
//     // Call  get_top_k_para function to get  top paragraphs
//     Node* top = qnaTool.get_top_k_para(question, k);
//     Node* topParagraph=top;
//     // Print  details of  top paragraphs
//     if (topParagraph != nullptr) {
//         std::cout << "Top " << k << " Paragraphs:" << std::endl;
//         for (int i = 0; i < k; ++i) {
//             // You can use topParagraph->book_code, topParagraph->page, topParagraph->paragraph, etc. to access paragraph details
//             std::cout << "Paragraph " << i + 1 << ": Book Code = " << topParagraph->book_code << ", Page = " << topParagraph->page << ", Paragraph = " << topParagraph->paragraph << std::endl;
//             topParagraph = topParagraph->right; // Move to  next top paragraph
//         }
//     } else {
//         std::cout << "No top paragraphs found for  given question." << std::endl;
//     }

//     // Specify  filename and API_KEY
//     std::string filename = "api_call.py";  // Replace with  actual filename
//     std::string API_KEY = "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";      // Replace with  actual API_KEY

//     // Call  query_llm function
//     qnaTool.query_llm(filename, top, k, API_KEY, question);
//     return 0;
// }

