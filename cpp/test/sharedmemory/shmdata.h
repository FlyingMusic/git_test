#ifndef __SHMDATA_H__
#define __SHMDATA_H__

#include <pthread.h>

typedef struct shared_data_st {
    int number;
    pthread_mutex_t mutex;
}shared_data;

#endif
