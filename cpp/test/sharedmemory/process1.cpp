#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"
#include <unistd.h>

int main()
{
    void *shm = NULL;
    shared_data *shared;
    int shmid;

    shmid = shmget((key_t)1234, sizeof(shared_data), 0666|IPC_CREAT);
    if(shmid == -1) {
        printf("shmget failed!!!\n");
        return -1;
    }

    shm = shmat(shmid, 0, 0);
    if(shmid == -1) {
        printf("shmat failed!!!\n");
        return -1;
    }

    shared = (shared_data *)shm;
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shared->mutex, &mutexAttr);
   
    while(true) {
        pthread_mutex_lock(&shared->mutex);
        for(int i = 0; i < 10; ++i) {
            printf("%d\n", i);
            sleep(1);
        }
        pthread_mutex_unlock(&shared->mutex);
        sleep(10);
    }
    
    printf("process1: %d\n", shared->number);
    if(shmdt(shm) == -1) {
        printf("shmdt failed!!!\n");
        return -1;
    }
    if(shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("shmctl failed!!!\n");
        return -1;
    }
    return 0;
}
