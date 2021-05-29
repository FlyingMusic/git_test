#ifndef __PACHIRA_CTD_BLOOMFILTER_H__
#define __PACHIRA_CTD_BLOOMFILTER_H__

#include <cmath>
#include "bloom_filter.h"
#include "hash_function.h"
namespace pachira_ctd{

class BloomFilter{

public:

    BloomFilter(const unsigned long max_elem_num = 10000, const double err_rate = 0.0001);

    ~BloomFilter();

    bool add(const char* str);

    bool exists(const char* str);

    int storeModel(const char *path);
    int loadModel(const char *path);
private:
    BLOOM *m_bloom;
};

}
#endif
