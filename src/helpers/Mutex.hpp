/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_MUTEX
#define BOOMBOX_MUTEX

#include <pthread.h>

namespace boombox
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
