/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_LOCK
#define BB_LOCK

#include "helpers/Mutex.hpp"

#define LOCK bb::Lock lock(mutex_);
#define LOCK_(x) bb::Lock lock(x);

namespace bb
{
    class Lock
    {
    public:
        Lock(Mutex& mutex):
            mutex_(&mutex)
        {
            mutex_->lock();
        }

        ~Lock()
        {
            mutex_->unlock();
        }

    private:
        Mutex* mutex_;
    };
}

#endif
