#include <stdio.h>
#include <mutex>
#include <thread>
#include <unistd.h>

std::mutex g_mutex1;
std::mutex g_mutex2;
std::mutex g_mutex3;

static int sum = 0;

void thread_func1() {
    std::lock(g_mutex1, g_mutex2, g_mutex3);
    std::lock_guard<std::mutex> lock1(g_mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(g_mutex2, std::adopt_lock);
    std::lock_guard<std::mutex> lock3(g_mutex3, std::adopt_lock);
    sum++;
}

void thread_func2() {
    std::lock(g_mutex1, g_mutex2);
    std::lock_guard<std::mutex> lock1(g_mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(g_mutex2, std::adopt_lock);
    std::lock_guard<std::mutex> lock3(g_mutex3, std::adopt_lock);
    sum++;
}

int main() {
    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    t1.join();
    t2.join();
    printf("sum = %d\n", sum);
    return 0;
}
