/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_TRACKER
#define BOOMBOX_TRACKER

#include "TrackerSample.hpp"
#include "TrackerProducerThread.hpp"
#include "helpers/Mutex.hpp"
#include "helpers/Class.hpp"
#include "helpers/RingBuffer.hpp"
#include "helpers/ReferencedPointer.hpp"
#include <stdint.h>

namespace boombox
{
    class Tracker
    {
    public:
        BOOMBOX_CLASS_UNCOPYABLE(Tracker);

        static unsigned int const TrackAmount = 8;
        static unsigned int const VolumeTransitionMilliSeconds = 450;
        static float const VolumeOffThreshold; // = 0.001f;

        Tracker(bool muteAtStart);
        ~Tracker();

        /**
         * Ends playing of TrackerSamples on Tracks so that eventually
         * no TrackerSamples exist and AudioSystemPrivate destructor
         * can proceed.
         */
        void shutdown();
        bool shutdownIsDone();
        bool place(ReferencedPointer<TrackerSample> const& trackerSample);
        unsigned int getData(unsigned int size, unsigned char* data);
        bool produceData();
        float volumeZeroProcess();
        void setMute(bool value);
        bool mute();

    private:
        Mutex mutex_;
        ReferencedPointer<TrackerSample> tracks_[TrackAmount];
        bool mute_;
        bool shutdownStarted_;
        bool shutdownDone_;
        RingBuffer<int16_t> ringBuffer_;
        TrackerProducerThread producerThread_;
    };
}

#endif
