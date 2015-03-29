/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/Thread.hpp"
#include "helpers/Log.hpp"
#include "helpers/Exception.hpp"
#include <stdlib.h>
#include <errno.h>
#include <stdexcept>
#ifdef __APPLE__
    #import <Foundation/Foundation.h>
#endif

namespace boombox
{
    void* threadFunction_(void* instance)
    {
        try
        {
            #ifdef __APPLE__
             //   NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init]; // Top-level pool
            #endif

            Thread* tmp = (Thread*)instance;
            ThreadCppWrapper::protectedCppRun(tmp);

            #ifdef __APPLE__
             //   [pool release];  // Release the objects in the pool.
            #endif

        }
        catch (Exception const& e)
        {
            LOGE("Exception inside thread! &s\n", e.what());
        }
        catch (...)
        {
            LOGE("Exception inside thread!\n");
        }

        return NULL;
    }

    Thread::Thread()
    {
    }

    Thread::~Thread()
    {
    }

    void Thread::start()
    {
        pthread_attr_t type;
        if (pthread_attr_init(&type) != 0)
        {
            throw Exception("pthread_attr_init failed");
        }
        pthread_attr_setdetachstate(&type, PTHREAD_CREATE_DETACHED);

        int result = pthread_create(&thread_, &type, threadFunction_, (void*)this);
        if (result == EAGAIN)
        {
            throw Exception("Thread::start, errno:EAGAIN");
        }
        else if (result == EINVAL)
        {
            throw Exception("Thread::start, errno:EINVAL");
        }
        else if (result == EPERM)
        {
            throw Exception("Thread::start, errno:EPERM");
        }
    }

    /*void Thread::join()
    {
        int result = pthread_join(thread_, NULL);
        if (result == EINVAL)
        {
            throw Exception("Thread::join, errno:EINVAL");
        }
        else if (result == ESRCH)
        {
            throw Exception("Thread::join, errno:ESRCH");
        }
        else if (result == EDEADLK)
        {
            throw Exception("Thread::join, errno:EDEADLK");
        }
    }*/
}
