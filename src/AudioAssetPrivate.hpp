/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_AUDIOASSETPRIVATE
#define BB_AUDIOASSETPRIVATE

#include "AudioResource.hpp"
#include "TrackerSample.hpp"
#include "helpers/Class.hpp"
#include "helpers/Referenced.hpp"
#include "helpers/ReferencedPointer.hpp"
#include "helpers/Mutex.hpp"
#include <string>
#include <set>

namespace bb
{
    class AudioAssetPrivate: public Referenced, private TrackerSampleObserver
    {
    public:
        BB_CLASS_UNCOPYABLE(AudioAssetPrivate)

        AudioAssetPrivate(const std::string& filename, bool parallelPlay, bool looping);
        ~AudioAssetPrivate();
        bool play(float volume);
        void setVolume(float volume);
        void fadeOut(unsigned int fadeOutTimeMilliseconds);

    private:
        void handleTrackerSampleEnd(unsigned int id);
        Mutex mutex_;
        std::list<ReferencedPointer<TrackerSample> > playing_;
        ReferencedPointer<AudioResource> resource_;
        bool parallerPlay_;
        bool looping_;
    };
}

#endif
