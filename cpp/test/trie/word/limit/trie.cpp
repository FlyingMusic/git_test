#include <unordered_map>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>


#define MAX_CHID_NUM 100

int max_child_num = 100;
using namespace std;

struct trie_node_st;

typedef struct trie_pair_st {
    unsigned int text_lable;
    trie_node_st *child; 
} *trie_pair_t;

typedef struct trie_node_st {
	trie_pair_st pairs[MAX_CHID_NUM];
	int pair_num;
    bool is_finish;
    trie_node_st() : pair_num(0), is_finish(false) {
        memset(pairs, 0, sizeof(pairs));
    }
    ~trie_node_st() {
        for(int i = 0; i < pair_num; ++i) {
            delete pairs[i].child;
        }
    }
} *trie_node_t;

#if 1
class Trie {
public:
    Trie() { }
    ~Trie() {
        for(auto node : root_nodes) {
            delete node.second;
        }
    }
    int insert(const char *text);
    int getFinishRate(const char *text, float *rate);
private:
    int insert(unsigned int arr[], int num);
    int insert(trie_node_t node, unsigned int arr[], int num, int id = 0);
    int getFinishRate(unsigned int arr[], int num, float *rate);
    int getFinishRate(trie_node_t node, unsigned int arr[], int num, int id = 0, float *rate = NULL);
    int insert_node(int num);
    unordered_map<int, trie_node_t> root_nodes;
};

int Trie::insert(const char *text) {
    unsigned int text_arr[64] = {0};
    int index = 0;
    char split[4] = {0};
    const char *start = text;
    while(*start != '\0') {
        if(isprint(*start)) {
            text_arr[index++] = *start;
            start++;
        } else {
            memcpy(split, start, 3);
            unsigned int tmp = *((int*)split);
            text_arr[index++] = tmp;
            start += 3;
        }
        if(index >= 64) {
            printf("input text is too long!\n");
            return -1;
        }
    }
    return insert(text_arr, index);
}

int Trie::insert(unsigned int arr[], int num) {
    if(root_nodes[arr[0]] == NULL) {
        root_nodes[arr[0]] = new trie_node_st;
        if(root_nodes[arr[0]] == NULL) {
            printf("malloc trie node failed!!!\n");
            return -1;
        }
    }
    return insert(root_nodes[arr[0]], arr, num);
}
int Trie::insert(trie_node_t node, unsigned int arr[], int num, int id) {
    if(id == num) {
        node->is_finish = true;
        return 0;
    }
    if(node->pair_num >= max_child_num) {
        return 0;
    }
    int i = 0;
    for(; i < node->pair_num; ++i) {
        if(node->pairs[i].text_lable == arr[id]) {
            return insert(node->pairs[i].child, arr, num, id+1);
        }
    }
    node->pairs[i].text_lable = arr[id];
    node->pairs[i].child = new trie_node_st;
    if(node->pairs[i].child == NULL) {
        printf("malloc trie node fail\n");
        return -1;
    }
    node->pair_num++;
    return insert(node->pairs[i].child, arr, num, id+1);
}
int Trie::getFinishRate(const char *text, float *rate) {
    if(text == NULL) {
        printf("input text is NULL!!!\n");
        return -1;
    }
    if(*text == '\0') {
        printf("input text length is 0\n");
        return -1;
    }
    unsigned int text_arr[64] = {0};
    int index = 0;
    char split[4] = {0};
    const char *start = text;
    while(*start != '\0') {
        if(isprint(*start)) {
            text_arr[index++] = *start;
            start++;
        } else {
            memcpy(split, start, 3);
            unsigned int tmp = *((int*)split);
            text_arr[index++] = tmp;
            start += 3;
        }
        if(index >= 64) {
            printf("input text is too long!\n");
            return -1;
        }
    }
    return getFinishRate(text_arr, index, rate);
}

int Trie::getFinishRate(unsigned int arr[], int num, float *rate) {
    if(root_nodes[arr[0]] == NULL) {
        return -1;
    }
    return getFinishRate(root_nodes[arr[0]], arr, num, 0, rate);
}
int Trie::getFinishRate(trie_node_t node, unsigned int arr[], int num, int id, float *rate) {
    if(id == num) {
        if(node->is_finish == false) {
            *rate = 0.0;
        } else {
            *rate = 1.0 / (node->pair_num + 1);
        }
        return 0;
    }
    int i = 0;
    for(; i < node->pair_num; ++i) {
        if(node->pairs[i].text_lable == arr[id]) {
            return getFinishRate(node->pairs[i].child, arr, num, id+1, rate);
        }
    }
    return -1;
}
#endif 
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
        if(0 == trie.getFinishRate(szTest, &finish_rate)){
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
