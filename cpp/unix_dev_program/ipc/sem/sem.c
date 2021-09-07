#include <stdio.h>
#include <errno.h>
#include <sys/sem.h>
 
int main (void) {
    
    key_t key = ftok (".", 100);
    if (key == -1) {
        perror("ftok error\n");
        return -1;
    }
    
    int semid = semget (key, 1, 0644 | IPC_CREAT | IPC_EXCL);
    if (semid == -1) {
        perror("semget error");
        return -1;
    }
 
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror ("semctl");
        return -1;
    }

    while (1) {
        struct sembuf sops = {0, -1, IPC_WAIT};
        if (semop (semid, &sops, 1) == -1) {
            if (errno == EINTR) {
                continue;
            }
            else {
                perror("semop error\n");
                return -1;
            }
        }

        /* 互斥区间
         *
         * 
         *
         */
        struct sembuf sops = {0, 1, IPC_WAIT};
        if (semop(semid, &sops, 1) == -1) {
            perror("semop error\n");
            return -1;
        }

    }
    printf("销毁信号量...\n");
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl error\n");
        return -1;
    }
    return 0;
}
