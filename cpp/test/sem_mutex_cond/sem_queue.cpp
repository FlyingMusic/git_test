/*===============================================================
*   Author: giturtle
*   描    述：实现线程安全的环形队列 （线性表实现的环形队列）
*   使用信号量实现队列操作的同步与互斥
================================================================*/
#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

class RingQueue{
    public:
    RingQueue(int cap = 10):_queue(10), _capacity(cap),
        _write_step(0), _read_step(0){
        
        sem_init(&_sem_data, 0, 0);
        pthread_cond_init(&m_not_full_cond, NULL);
        pthread_mutex_init(&m_mutex, NULL);
    }
    ~RingQueue(){
        sem_destroy(&_sem_data);
        pthread_cond_destroy(&m_not_full_cond);
        pthread_mutex_destroy(&m_mutex);
    }
    bool  QueuePush(int data){
        QueueLock();
        ProductorWait();
        _queue[_write_step] = data;
        _write_step = (_write_step + 1) % _capacity;
        QueueUnLock();
        ConsumerWakeUp();
        return true;
    }
    bool  QueuePop(int *data){
        ConsumerWait();
        QueueLock();
        *data = _queue[_read_step];
        _read_step = (_read_step + 1) % _capacity;
        QueueUnLock();
        ProductorWakeUp();
        return true;
    }
    private:
    void QueueLock(){
        //通过计数判断是否有资源可操作 （计数-1 + 等待）
        pthread_mutex_lock(&m_mutex);
    }
    void QueueUnLock(){
        //计数+1 ，并唤醒等待
        pthread_mutex_unlock(&m_mutex);
    }
    void ProductorWait(){
        while(_queue.size() > _capacity) {
            pthread_cond_wait(&m_not_full_cond, &m_mutex);
        }
    }
    void ProductorWakeUp(){
        pthread_cond_signal(&m_not_full_cond);
    }
    void ConsumerWait(){
        sem_wait(&_sem_data);
    }
    void ConsumerWakeUp(){
        sem_post(&_sem_data);
    }
    private:
    std::vector<int> _queue;
    int  _capacity;
    int  _write_step;
    int  _read_step;
    sem_t _sem_data;    //空闲资源计数
    pthread_cond_t m_not_full_cond;    
    pthread_mutex_t m_mutex;
};
void *thr_consumer(void *arg){
    RingQueue *q = (RingQueue*)arg;
    int cnt = 100;
    while(cnt--) {
        int data;
        q->QueuePop(&data);
        std::cout<<"consumer thread get data:"<<data<<std::endl;
        usleep(20);
    }
    return NULL;
}
void *thr_productor(void *arg){
    RingQueue *q = (RingQueue*)arg;
    int i = 0;
    int cnt = 100;
    while(cnt--) {
        q->QueuePush(i);
        std::cout<<"productor thread put data:"<<i<<std::endl;
        i++;
        usleep(20);
    }
    return NULL;
}
int main (int argc, char *argv[]){
    int consumer_num = 1;
    int productor_num = 1;
    pthread_t ctid[consumer_num], ptid[productor_num];
    int ret, i;
    RingQueue q;

    for (i = 0; i < consumer_num; i++) {
        ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
        if (ret != 0) {
            std::cout<<"thread create error\n";
            return -1;
        }
    }
    for (i = 0; i < productor_num; i++) {
        ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
        if (ret != 0) {
            std::cout<<"thread create error\n";
            return -1;
        }
    }
    for (i = 0; i < consumer_num; i++) {
        pthread_join(ctid[i], NULL);
    }
    for (i = 0; i < productor_num; i++) {
        pthread_join(ptid[i], NULL);
    }
    return 0;
}

