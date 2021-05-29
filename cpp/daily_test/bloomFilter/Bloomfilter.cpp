#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "Bloomfilter.h"
#include "dlog.h"

namespace pachira_ctd{

BloomFilter::BloomFilter(const unsigned long max_elem_num, const double err_rate){

    unsigned long tmp = (unsigned long)(19.2 * max_elem_num);
    m_bloom = bloom_create(tmp, 11, RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash, DJBHash,
                           DEKHash, BPHash, FNVHash, APHash);
    if(m_bloom == NULL){
        LOG_ERROR("create bloom failed.");
    }
    
}

BloomFilter::~BloomFilter(){
    if(m_bloom != NULL){
        bloom_destroy(m_bloom);
    }
}

bool BloomFilter::add(const char* str){
	if(NULL == str || NULL == m_bloom){
		return false;
    }
    unsigned int strLen = strlen(str);
    if(bloom_check(m_bloom, str, strLen) == 1){
        return false;
    }
    bloom_add(m_bloom, str, strLen);
    return true;
}

bool BloomFilter::exists(const char* str){
    if(NULL == str || NULL == m_bloom){
        return false;
    }
    unsigned int strLen = strlen(str);
    int ret = bloom_check(m_bloom, str, strLen);
    if(ret == 0){
        return false;
    }
    return true;
}

int BloomFilter::storeModel(const char *path){
    if(m_bloom == NULL || path == NULL){
        return -1;
    }
    FILE *fp = fopen(path,"wb");
    if(fp == NULL){
        LOG_ERROR("open path failed about store bloom model.");
        return -1;
    }
    int ret = 0;
    ret = fwrite(&(m_bloom->asize), sizeof(size_t), 1, fp);
    if(ret != 1){
        LOG_ERROR("write model error.");
        return -1;
    }
    int bit_len = (m_bloom->asize + CHAR_BIT - 1) / CHAR_BIT * sizeof(char);
     
    ret = fwrite(m_bloom->a, sizeof(char), bit_len, fp);
    if(ret != bit_len){
        LOG_ERROR("write model error.");
        return -1;
    }
    fclose(fp);    
    return 0;
}   

int BloomFilter::loadModel(const char *path){
    if(m_bloom == NULL || path == NULL){
        return -1;
    }
     
    FILE *fp = fopen(path,"rb");
    if(fp == NULL){
        LOG_ERROR("open path failed about store bloom model.");
        return -1;
    }
    int ret = 0;
    int asize = m_bloom->asize;
    ret = fread(&(m_bloom->asize), sizeof(size_t), 1, fp);
    if(ret != 1 || asize != m_bloom->asize){
        LOG_ERROR("read model error.");
        return -1;
    }
    int bit_len = (m_bloom->asize + CHAR_BIT - 1) / CHAR_BIT * sizeof(char);
    ret = fread(m_bloom->a, sizeof(char), bit_len, fp);
    if(ret != bit_len){
        LOG_ERROR("read model error.");
        return -1;
    }
    fclose(fp);
    return 0;
}

}
