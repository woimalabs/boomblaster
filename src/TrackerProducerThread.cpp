/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "TrackerProducerThread.hpp"
#include "Tracker.hpp"
#include "helpers/Timer.hpp"
#include "helpers/Log.hpp"

namespace boombox
{
    TrackerProducerThread::TrackerProducerThread(Tracker* tracker):
        tracker_(tracker)
    {
    }

    TrackerProducerThread::~TrackerProducerThread()
    {
    }

    void TrackerProducerThread::threadFunction()
    {
        while (tracker_->produceData() == true)
        {
            Timer::sleepMilliseconds(1); // TODO, signal etc replacing the sleep
        }
    }
}
