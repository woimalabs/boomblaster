/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_THREAD
#define BB_THREAD

#include <pthread.h>
#include <string>

namespace bb
{
    struct ThreadCppWrapper;

    /**
     * @class Thread
     *
     * Base class for thread classes.
     */
    class Thread
    {
    public:
        Thread();
        virtual ~Thread();
        void start();
        virtual void threadFunction() = 0;

    private:
        pthread_t thread_;
        friend struct ThreadCToCppWrapper;
    };

    struct ThreadCppWrapper
    {
        static void protectedCppRun(Thread* other)
        {
            other->threadFunction();
        }
    };
}

#endif
