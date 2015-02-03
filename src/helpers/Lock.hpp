/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_LOCK
#define BOOMBOX_LOCK

#include "helpers/Mutex.hpp"

#define LOCK boombox::Lock lock(mutex_);
#define LOCK_(x) boombox::Lock lock(x);

namespace boombox
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
