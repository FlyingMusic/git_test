/* Data structures for mutex handling.  The structure of the attribute
   type is not exposed on purpose.  */
/*删减了32位的代码*/

# define PTHREAD_MUTEX_INITIALIZER \
{ { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { 0, 0 } } } 

typedef union
{
    struct __pthread_mutex_s
    {
        int __lock; //0
        unsigned int __count; //0
        int __owner; //0
#ifdef __x86_64__
        unsigned int __nusers; //0
#endif
        /* KIND must stay at this position in the structure to maintain
           binary compatibility with static initializers.  */
        int __kind; //0
#ifdef __x86_64__
        short __spins; //__PTHREAD_SPINS
        short __elision; //0
        __pthread_list_t __list; //0
# define __PTHREAD_MUTEX_HAVE_PREV    1
        /* Mutex __spins initializer used by PTHREAD_MUTEX_INITIALIZER.  */
# define __PTHREAD_SPINS             0, 0
#else
#endif
    } __data;
    char __size[__SIZEOF_PTHREAD_MUTEX_T];
    long int __align;
} pthread_mutex_t;

#ifndef __pthread_mutex_lock
    strong_alias (__pthread_mutex_lock, pthread_mutex_lock)
hidden_def (__pthread_mutex_lock)
#endif

int
__pthread_mutex_lock (pthread_mutex_t *mutex)
{
    assert (sizeof (mutex->__size) >= sizeof (mutex->__data));

    unsigned int type = PTHREAD_MUTEX_TYPE_ELISION (mutex);

    LIBC_PROBE (mutex_entry, 1, mutex);

    if (__builtin_expect (type & ~(PTHREAD_MUTEX_KIND_MASK_NP
                    | PTHREAD_MUTEX_ELISION_FLAGS_NP), 0))
        return __pthread_mutex_lock_full (mutex);

    if (__glibc_likely (type == PTHREAD_MUTEX_TIMED_NP)) {
        FORCE_ELISION (mutex, goto elision);
simple:
        /* Normal mutex.  */
        LLL_MUTEX_LOCK (mutex);
        assert (mutex->__data.__owner == 0);
    }
#ifdef HAVE_ELISION
    else if (__glibc_likely (type == PTHREAD_MUTEX_TIMED_ELISION_NP)) {
elision: __attribute__((unused))
             /* This case can never happen on a system without elision,
                as the mutex type initialization functions will not
                allow to set the elision flags.  */
             /* Don't record owner or users for elision case.  This is a
                tail call.  */
             return LLL_MUTEX_LOCK_ELISION (mutex);
    }
#endif
    else if (__builtin_expect (PTHREAD_MUTEX_TYPE (mutex)
                == PTHREAD_MUTEX_RECURSIVE_NP, 1))
    {
        /* Recursive mutex.  */
        pid_t id = THREAD_GETMEM (THREAD_SELF, tid);

        /* Check whether we already hold the mutex.  */
        if (mutex->__data.__owner == id)
        {
            /* Just bump the counter.  */
            if (__glibc_unlikely (mutex->__data.__count + 1 == 0))
                /* Overflow of the counter.  */
                return EAGAIN;

            ++mutex->__data.__count;

            return 0;
        }

        /* We have to get the mutex.  */
        LLL_MUTEX_LOCK (mutex);

        assert (mutex->__data.__owner == 0);
        mutex->__data.__count = 1;
    }
    else if (__builtin_expect (PTHREAD_MUTEX_TYPE (mutex)
                == PTHREAD_MUTEX_ADAPTIVE_NP, 1))
    {
        if (! __is_smp)
            goto simple;

        if (LLL_MUTEX_TRYLOCK (mutex) != 0)
        {
            int cnt = 0;
            int max_cnt = MIN (MAX_ADAPTIVE_COUNT,
                    mutex->__data.__spins * 2 + 10);
            do
            {
                if (cnt++ >= max_cnt)
                {
                    LLL_MUTEX_LOCK (mutex);
                    break;
                }
                atomic_spin_nop ();
            }
            while (LLL_MUTEX_TRYLOCK (mutex) != 0);

            mutex->__data.__spins += (cnt - mutex->__data.__spins) / 8;
        }
        assert (mutex->__data.__owner == 0);
    }
    else
    {
        pid_t id = THREAD_GETMEM (THREAD_SELF, tid);
        assert (PTHREAD_MUTEX_TYPE (mutex) == PTHREAD_MUTEX_ERRORCHECK_NP);
        /* Check whether we already hold the mutex.  */
        if (__glibc_unlikely (mutex->__data.__owner == id))
            return EDEADLK;
        goto simple;
    }

    pid_t id = THREAD_GETMEM (THREAD_SELF, tid);

    /* Record the ownership.  */
    mutex->__data.__owner = id;
#ifndef NO_INCR
    ++mutex->__data.__nusers;
#endif

    LIBC_PROBE (mutex_acquired, 1, mutex);

    return 0;
}
