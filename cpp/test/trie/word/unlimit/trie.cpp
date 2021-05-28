#include <unordered_map>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

using namespace std;

int new_count = 0;

typedef struct trie_node_st {
    unordered_map<unsigned int, trie_node_st*> childs;
    bool is_finish;
    trie_node_st() : is_finish(false) { }
    ~trie_node_st() {
        for(auto child : childs) {
            delete child.second;
        }
    }
} *trie_node_t;

#if 1
class Trie {
public:
    Trie() : root_node(NULL){ }
    ~Trie() {
        if(root_node != NULL) {
            delete root_node;
            root_node = NULL;
        }
    }
    int init();
    int insert(const char *text);
    int getFinishRate(const char *text, float *rate);
private:
    int insert(unsigned int arr[], int num);
    int insert(trie_node_t node, unsigned int arr[], int num, int id = 0);
    int getFinishRate(unsigned int arr[], int num, float *rate);
    int getFinishRate(trie_node_t node, unsigned int arr[], int num, int id = 0, float *rate = NULL);
    int insert_node(int num);
    trie_node_t root_node;
};

int Trie::init() {
    if(root_node == NULL) {
        root_node = new trie_node_st;
        new_count++;
        if(root_node == NULL) {
            printf("root_node new fail!!!\n");
            return -1;
        }
    }
    return 0;
}
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
    return insert(root_node, arr, num, 0);
}
int Trie::insert(trie_node_t node, unsigned int arr[], int num, int id) {
    if(id == num) {
        node->is_finish = true;
        return 0;
    }
    for(auto child : node->childs) {
        if(arr[id] == child.first) {
            return insert(child.second, arr, num, id+1);
        }
    }
    node->childs[arr[id]] = new trie_node_st;
    new_count++;
    if(node->childs[arr[id]] == NULL) {
        printf("malloc trie node fail\n");
        return -1;
    }
    return insert(node->childs[arr[id]], arr, num, id+1);
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
    return getFinishRate(root_node, arr, num, 0, rate);
}
int Trie::getFinishRate(trie_node_t node, unsigned int arr[], int num, int id, float *rate) {
    if(id == num) {
        if(node->is_finish == false) {
            *rate = 0.0;
        } else {
            *rate = 1.0 / (node->childs.size() + 1);
        }
        return 0;
    }
    for(auto child : node->childs) {
        if(arr[id] == child.first) {
            return getFinishRate(child.second, arr, num, id+1, rate);
        }
    }
    return -1;
}
#endif 
int main(int argc, char *argv[]) {
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
    Trie trie;
    trie.init();
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
    printf("new_count = %d\n", new_count);
    return 0;
}
