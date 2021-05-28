#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <ctype.h>

#define MAX_CHID_NUM 256
#define CODE_BYTE 3

struct trie_node_st;

typedef struct trie_pair_st {
    unsigned char text_lable;
    trie_node_st *child; 
} *trie_pair_t;

typedef struct trie_node_st {
	trie_pair_st pairs[MAX_CHID_NUM];
	int pair_num;
	bool is_finish;
    trie_node_st() : is_finish(false), pair_num(0) {
        memset(pairs, 0, sizeof(pairs));
    }
    ~trie_node_st() {
        for(int i = 0; i < pair_num; ++i) {
            delete pairs[i].child;
        }
    }
} *trie_node_t;

class Trie {
public:
    Trie() {
        memset(root_nodes, 0, sizeof(root_nodes));
    }
    ~Trie() {
        for(int i = 0; i < 256; ++i) {
            delete root_nodes[i];
        }
    }
    int insert(const char *text);
    int getFinishRate(const char *text, float &rate);
private:
    int insert(trie_node_t node, const char *text);
    int getFinishRate(trie_node_t node, const char *text, float &rate);
    int getBranchNum(trie_node_t node, int level = 0);
    int m_high;
    trie_node_t root_nodes[256];
};

int Trie::insert(const char *text) {
    if(text == NULL) {
        printf("input text is NULL!!!\n");
        return -1;
    }
    if(*text == '\0') {
        printf("input text length is 0\n");
        return 0;
    }
    unsigned char index = (unsigned char)*text;
    if(root_nodes[index] == NULL) {
        root_nodes[index] = new trie_node_st;
        if(root_nodes[index] == NULL) {
            printf("malloc trie node fail\n");
            return -1;
        }
    }
    m_high = 0;
    return insert(root_nodes[index], text+1);
}
int Trie::insert(trie_node_t node, const char *text) {
    m_high++;
    if(*text == '\0') {
        node->is_finish = true;
        return 0;
    }
    int max_child_num = 0;
    switch(m_high / CODE_BYTE) {
        case 0: max_child_num = 256; break;
        case 1: max_child_num = 256; break;
        default: max_child_num = 256; break;
    }
    if(node->pair_num >= max_child_num) {
        return 0;
    }
    int i = 0;
    unsigned char index = (unsigned char)*text;
    for(; i < node->pair_num; ++i) {
        if(node->pairs[i].text_lable == index) {
            return insert(node->pairs[i].child, text+1);
        }
    }    
    node->pairs[i].text_lable = index;
    node->pairs[i].child = new trie_node_st;
    if(node->pairs[i].child == NULL) {
        printf("malloc trie node fail\n");
        return -1;
    }
    node->pair_num++;
    return insert(node->pairs[i].child, text+1);
}

int Trie::getFinishRate(const char *text, float &rate) {
    if(text == NULL) {
        printf("input text is NULL!!!\n");
        return -1;
    }
    if(*text == '\0') {
        printf("input text length is 0\n");
        return -1;
    }
    unsigned char index = (unsigned char)*text;
    if(root_nodes[index] == NULL) {
        return -1;
    }
    return getFinishRate(root_nodes[index], text+1, rate);    
}
int Trie::getFinishRate(trie_node_t node, const char *text, float &rate) {
    if(*text == '\0') {
        if(node->is_finish == false) {
            rate = 0.0;
        } else {
            //rate = 1.0 / (node->pair_num + 1);
            rate = 1.0 / (getBranchNum(node) + 1);
        }
        return 0;
    }
    int i = 0;
    unsigned char index = (unsigned char)*text;
    for(; i < node->pair_num; ++i) {
        if(node->pairs[i].text_lable == index) {
            return getFinishRate(node->pairs[i].child, text+1, rate);
        }
    }
    return -1;
}
int Trie::getBranchNum(trie_node_t node, int level) {
   if(level < CODE_BYTE-1) {
        int branchNum = 0;
        for(int i = 0; i < node->pair_num; ++i) {
            if(isprint(node->pairs[i].text_lable)) {
                branchNum += 1;
            } else {
                branchNum += getBranchNum(node->pairs[i].child, level+1);
            }
        }
        return branchNum;
    }
    if(level == CODE_BYTE-1) {
        return node->pair_num;
    }
    if(level > CODE_BYTE-1) { 
        return 0; 
    }  
}
int main(int argc, char *argv[]) {
    Trie trie;
    if(argc < 3) {
        printf("please input filename!!!\n");
        printf("usage: %s train.txt test.txt\n", argv[0]);
        return -1;
    }
    FILE *fpR = fopen(argv[1],"r");
    if(fpR == NULL){
        printf("open file %s failed!", argv[1]);
        return -1;
    }
    char szTest[512] = {0};
    memset(szTest, 0, sizeof(szTest));
    while(fgets(szTest, sizeof(szTest) - 1, fpR) != NULL){
        int len = strlen(szTest);
        if('\r' == szTest[len - 2] || '\n' == szTest[len - 2]){
            szTest[len - 2] = '\0';
        }
        szTest[len - 1] = '\0';
        if(0 != trie.insert(szTest)){
            printf("insert(%s) failed!!!\n");
            return -1;
        }
        memset(szTest, 0, sizeof(szTest));
    }
    fclose(fpR);
    fpR = fopen(argv[2],"r");
    if(fpR == NULL){
        printf("open file %s failed!", argv[2]);
        return -1;
    }
    while(fgets(szTest, sizeof(szTest) - 1, fpR) != NULL){
        int len = strlen(szTest);
        if('\r' == szTest[len - 2] || '\n' == szTest[len - 2]){
            szTest[len - 2] = '\0';
        }
        szTest[len - 1] = '\0';
        float finish_rate = 0.0;
        struct timeval start;
        struct timeval end;
        gettimeofday(&start,NULL); 
        if(0 == trie.getFinishRate(szTest, finish_rate)){
            gettimeofday(&end,NULL);
            float time = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
            printf("%s: rate(%f) time(%f us)\n", szTest, finish_rate, time);
        } else {
            printf("%s: unknown\n", szTest);
        }
        memset(szTest, 0, sizeof(szTest));
    }
    fclose(fpR);
    return 0;
}
