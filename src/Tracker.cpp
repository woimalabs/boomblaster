/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "Tracker.hpp"
#include "helpers/Timer.hpp"
#include "helpers/Lock.hpp"
#include "helpers/Exception.hpp"
#include "helpers/Log.hpp"
#include "helpers/Helpers.hpp"
#include <stdint.h>

namespace bb
{
    Tracker::Tracker(bool muteAtStart):
        mute_(muteAtStart),
        shutdownStarted_(false),
        shutdownDone_(false),
        ringBuffer_(44100 * 2 / 20), /* one second divided by 20 to have max 50ms lag here */
        producerThread_(this)
    {
        for(unsigned int i = 0; i < Tracker::TrackAmount; i++)
        {
            tracks_[i] = NULL;
        }
        producerThread_.start();
    }

    Tracker::~Tracker()
    {
    }

    void Tracker::shutdown()
    {
        LOCK

        if(shutdownStarted_ == false)
        {
            for (unsigned int i = 0; i < Tracker::TrackAmount; i++)
            {
                if(tracks_[i].pointer() != NULL)
                {
                    tracks_[i].pointer()->fadeOut(100);
                }
            }

            shutdownStarted_ = true;
        }
    }

    bool Tracker::shutdownIsDone()
    {
        return shutdownDone_;
    }

    bool Tracker::place(ReferencedPointer<TrackerSample> const& trackerSample)
    {
        bool r = false;

        LOCK

        if(shutdownStarted_ == false)
        {
            for (unsigned int i = 0; i < Tracker::TrackAmount; i++)
            {
                // Try to find an empty track to get in the new sample
                if(tracks_[i].pointer() == NULL)
                {
                    tracks_[i] = trackerSample;
                    r = true;
                    break;
                }
            }
        }

        return r;
    }

    unsigned int Tracker::getData(unsigned int size, unsigned char* data)
    {
        unsigned int r = 0;

        for (unsigned int i = 0; i < size; i += 2)
        {
            int16_t a = 0;
            while (ringBuffer_.get(a) == false)
            {
                if(shutdownStarted_ == true)
                {
                    //LOG
                    break;
                }
            }
            data[i] = ((char*)&a)[0];
            data[i+1] = ((char*)&a)[1];
            r = i;
        }

        return r;
    }

    bool Tracker::produceData()
    {
        LOCK

        bool r = true;
        unsigned int bytesProduced = 0;
        bool mute = mute_;

        while (true)
        {
            if(ringBuffer_.full() == true)
            {
                //LOGD("Tracker::produceData(), ring buffer is full.");
                break;
            }

            int a = 0;
            bool tracksWithAudio = false;
            for(unsigned int t = 0; t < Tracker::TrackAmount; t++)
            {
                if(tracks_[t].pointer() != NULL)
                {
                    tracksWithAudio = true;
                    bool end = false;
                    a += tracks_[t].pointer()->sampleForTracker(end);
                    if(end == true)
                    {
                        tracks_[t] = ReferencedPointer<TrackerSample>(NULL);
                    }
                }
            }
            if(mute)
            {
                a = 0;
            }
            else
            {
                a = (float)a / (float)Tracker::TrackAmount;
            }

            // Put to data
            int16_t data = a;
            bytesProduced += 2;

            if(shutdownStarted_ && tracksWithAudio == false)
            {
                r = false;
                shutdownDone_ = true;
                break; // buffer is full OR we are shutting down
            }

            if(ringBuffer_.put(data) == false)
            {
                throw Exception("Tracker::produceData(), ring buffer was full even if we checked that it is not!");
                break;
            }
        }

        //LOGD("bytes produced: %d", bytesProduced);
        return r;
    }

    void volumeZeroProcess()
    {
        // TODO
    }

    void Tracker::setMute(bool value)
    {
        mute_ = value;
    }

    bool Tracker::mute()
    {
        return mute_;
    }
}
