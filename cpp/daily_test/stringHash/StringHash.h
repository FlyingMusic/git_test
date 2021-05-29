#ifndef __PACHIRA_CTD_STRING_HASH_H__
#define __PACHIRA_CTD_STRING_HASH_H__

#include "pachira_mem.h"
namespace pachira_ctd{

typedef struct HashTableSt{
    char *key;
    char *value;
    struct HashTableSt* next;
    HashTableSt(){
        key = NULL;
        value = NULL;
        next = NULL;
    }
    ~HashTableSt(){
        PACHIRA_FREE(key);
        PACHIRA_FREE(value);
    }
}*HashTableT;

class StringHash{
public:
    StringHash();
    ~StringHash();
    int init(int size);
    int addMap(const char *key, const char *value = NULL);
    bool existKey(const char *key, char **value = (char**)NULL);
private:
    unsigned int getHashCode(const char *key);
    int destroy();
private:
    HashTableT m_hashTable;
    int m_hashTableSize;
    int m_elemSize;
};

}

#endif
