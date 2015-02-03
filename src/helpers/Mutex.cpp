/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/Mutex.hpp"
#include "helpers/Log.hpp"
#include "helpers/Exception.hpp"
#include <stdlib.h>
#include <errno.h>

namespace boombox
{
    Mutex::Mutex()
    {
        int r = pthread_mutex_init(&mutex_, NULL);

        if (r == EINVAL)
        {
            throw Exception("Mutex(), errno:EAGAIN");
        }
        else if (r == ENOMEM)
        {
            throw Exception("Mutex(), errno:ENOMEM");
        }
        else if (r == EPERM)
        {
            throw Exception("Mutex(), errno:EPERM");
        }
    }

    Mutex::~Mutex()
    {
        int r = 0;

        r = pthread_mutex_destroy(&mutex_);
        if (r == EINVAL)
        {
            throw Exception("~Mutex, errno:EINVAL");
        }
        else if (r == EBUSY)
        {
            throw Exception("~Mutex, errno:EBUSY");
        }
    }

    int Mutex::lock()
    {
        return pthread_mutex_lock(&mutex_);
    }

    int Mutex::unlock()
    {
        return pthread_mutex_unlock(&mutex_);
    }
}
