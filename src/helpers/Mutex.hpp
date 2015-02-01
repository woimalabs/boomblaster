/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_MUTEX
#define BB_MUTEX

#include <pthread.h>

namespace bb
{
    class Mutex
    {
    public:
        Mutex();
        ~Mutex();
        int lock();
        int unlock();

    private:
        pthread_mutex_t mutex_;
    };
}

#endif
