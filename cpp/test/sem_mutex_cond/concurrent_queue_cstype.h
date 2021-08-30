#ifndef _CONCURRENT_QUEUE_H_
#define _CONCURRENT_QUEUE_H_

#ifdef _DEBUG_CONCURRENT_QUEUE_
#include <stdio.h>
#endif

#include <queue>
#include <pthread.h>


template<typename Type>
class concurrent_queue
{
public:
    concurrent_queue(int cap = 100) {
        m_capacity = size;
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_not_empty_cond, NULL);
        pthread_cond_init(&m_not_full_cond, NULL);
    }
    ~concurrent_queue() {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_not_empty_cond);
        pthread_cond_destroy(&m_not_full_cond);
    }
    void push(Type const& item)
    {
        pthread_mutex_lock(&m_mutex);
        while(m_queue.size() > m_capacity) {
            pthread_cond_wait(&m_not_full_cond, &m_mutex);
        }
        m_queue.push(item);
        pthread_cond_signal(&m_not_empty_cond);
        pthread_mutex_unlock(&m_mutex);
    }

    Type pop()
    {
        pthread_mutex_lock(&m_mutex);
        while(m_queue.empty()) {
            pthread_cond_wait(&m_not_empty_cond, &m_mutex);
        }

        Type item = m_queue.front();
        m_queue.pop();
        pthread_cond_signal(&m_not_full_cond);
        pthread_mutex_unlock(&m_mutex);
        return item;
    }

private:
    std::queue<Type> m_queue;
    int m_capacity;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_not_empty_cond;
    pthread_cond_t m_not_full_cond;
};

#endif
