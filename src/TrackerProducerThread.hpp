/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_TRACKERPRODUCERTHREAD
#define BB_TRACKERPRODUCERTHREAD

#include "helpers/Thread.hpp"
#include "helpers/Class.hpp"

namespace bb
{
    class Tracker;

    class TrackerProducerThread: public Thread
    {
    public:
        BB_CLASS_UNCOPYABLE(TrackerProducerThread);

    protected:
        void threadFunction();

    private:
        friend class Tracker;

        TrackerProducerThread(Tracker* tracker);
        ~TrackerProducerThread();

        pthread_t thread_;
        Tracker* tracker_;
        friend struct ThreadCToCppWrapper;
    };
}

#endif
