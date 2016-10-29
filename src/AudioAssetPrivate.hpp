/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_AUDIOASSETPRIVATE
#define BOOMBOX_AUDIOASSETPRIVATE

#include "AudioResource.hpp"
#include "TrackerSample.hpp"
#include "helpers/Class.hpp"
#include "helpers/Referenced.hpp"
#include "helpers/ReferencedPointer.hpp"
#include "helpers/Mutex.hpp"
#include <string>
#include <list>
#include <set>

namespace boombox
{
    class AudioAssetPrivate: public Referenced, private TrackerSampleObserver
    {
    public:
        BOOMBOX_CLASS_UNCOPYABLE(AudioAssetPrivate)

        AudioAssetPrivate(const std::string& filename, bool parallelPlay, bool looping);
        ~AudioAssetPrivate();
        bool play(float volume);
        void setVolume(float volume);
        void fadeOut(unsigned int fadeOutTimeMilliseconds);

    private:
        void handleTrackerSampleEnd(unsigned int id);
        Mutex mutex_; // this mutex protects the playing list
        std::list<ReferencedPointer<TrackerSample> > playing_;
        ReferencedPointer<AudioResource> resource_;
        bool parallerPlay_;
        bool looping_;
    };
}

#endif
