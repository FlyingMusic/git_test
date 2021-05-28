#include <unordered_map>

#define MAX_CHID_NUM 10

struct trie_node_st;

typedef struct trie_pair_st {
    int text_lable;
    trie_node_st *child; 
} *trie_pair_t;

typedef struct trie_node_st {
	float finish_rate;
	trie_pair_st pairs[MAX_CHID_NUM];
	int pair_num;
    trie_node_st() : text_lable(0), chid_num(0), finish_rate(0.0) {
        memset(pairs, 0, sizeof(pairs));
    }
} *trie_node_t;

class Trie {
public:
    int insert(const char *text);
    int getFinishRate(const char *text, float &rate);
private:
    int insert_node(int num);
    unordered_map<int, trie_node_t> virtual_root;
};

int Trie::insert(const char *text) {
    char *start = text;
    int lable_arr[30] = {0};
    int index = 0;
    while(*start != '\0' && *start != '\r' && *start != '\n') {
        if(isprint(*start)) {
            lable_arr[index] = *start;
            start++;
        } else {
            lable_arr[index] = *start;
            start += 3;
        }
        index++;
    }
    insert(lable_arr, index);
}
