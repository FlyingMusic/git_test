#include <string.h>
#include "dlog.h"
#include "pachira_mem.h"
#include "StringHash.h"

namespace pachira_ctd{

StringHash::StringHash(){
    m_hashTable = NULL;
    m_hashTableSize = 0;
    m_elemSize = 0;
}

StringHash::~StringHash(){
    destroy();
}

int StringHash::destroy(){
    if(m_hashTable != NULL){
        int i = 0;
        for(i = 0;i < m_hashTableSize;i++){
            HashTableT hash = m_hashTable + i;
            HashTableT next = hash->next;
            while(next != NULL){
                hash = next;
                next = next->next;
                delete hash;
            }
        }
        delete [] m_hashTable;
    }
    return 0;
}

int StringHash::init(int size){
    if(m_hashTable == NULL){
        if(size < 24){
            size = 24;
        }
        m_hashTableSize = size/24;
        m_hashTable = new HashTableSt[m_hashTableSize];
        if(m_hashTable == NULL){
            LOG_ERROR("alloc mem for Hash Table failed");
            return -1;
        }
        m_elemSize = 0;
    }
    return 0;
}

int StringHash::addMap(const char *key, const char *value){
    if(key == NULL || key[0] == 0){
        return 0;
    }
    HashTableT hash, newhash;
    int id = getHashCode(key);
    hash = m_hashTable + id;
    if(hash->key == NULL){
        hash->key = strdup(key);
        if(value != NULL)
            hash->value = strdup(value);
    }else{
        newhash = new HashTableSt;
        newhash->key = strdup(key);
        if(value != NULL)
            newhash->value = strdup(value);
        newhash->next = hash->next;
        hash->next = newhash;
    }
    m_elemSize ++;
    return 0;
}

bool StringHash::existKey(const char *key, char **value){
    if(key == NULL){
        LOG_ERROR("key is null.");
        return false;
    }
    for(HashTableT hash = m_hashTable + getHashCode(key); hash != NULL; hash = hash->next){
        if(hash->key == NULL){
            return false;
        }else if(strcmp(hash->key, key) == 0){
            if(hash->value != NULL && value != NULL)
                strcpy(*value, hash->value);
            return true;
        }
    }
    return false;
}

unsigned int StringHash::getHashCode(const char *key){
    register unsigned int hashValue;
    hashValue = 0;
    while(*key != '\0'){
        hashValue = hashValue * 101 + *(key++);
    }
    return (hashValue%m_hashTableSize);
}

}
