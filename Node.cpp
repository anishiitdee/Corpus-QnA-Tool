#include "Node.h"

Node::Node() {
    right=nullptr;
    left=nullptr;
}

Node::Node(int b_code, int pg, int para, int s_no, int off){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
    right=nullptr;
}