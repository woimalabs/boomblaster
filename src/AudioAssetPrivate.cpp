/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "AudioAssetPrivate.hpp"
#include "AudioEnginePrivate.hpp"
#include "TrackerSample.hpp"
#include "helpers/Log.hpp"
#include "helpers/Utilities.hpp"
#include "helpers/Lock.hpp"

namespace bb
{
    AudioAssetPrivate::AudioAssetPrivate(const std::string& filename, bool parallelPlay, bool looping):
        Referenced(),
        resource_(AudioEnginePrivate::get(filename)),
        parallerPlay_(parallelPlay),
        looping_(looping)
    {
    }

    AudioAssetPrivate::~AudioAssetPrivate()
    {
        // End playing
        fadeOut(0);

        while(playing_.size() > 0);
    }

    bool AudioAssetPrivate::play(float volume)
    {
        bool r = false;

        // Sanity check for volume value
        volume = bb::clamp(volume, 0.0f, 1.0f);

        LOCK

        if(parallerPlay_ || (!parallerPlay_ && playing_.size() == 0))
        {
            LOGD("parallelPlay: %d, file %s", parallerPlay_, resource_.pointer()->filename().c_str());
            ReferencedPointer<TrackerSample> tmp(new TrackerSample(resource_, volume, looping_, this));
            // tmp.pointer()->audioAssetInterestedFromEnd = tmp.pointer()->ended.connect(sigc::mem_fun(this, &AudioAssetPrivate::handleTrackerSampleEnd));
            r = AudioEnginePrivate::play(tmp);
            if(r == true)
            {
                playing_.push_back(tmp);
            }
        }
        return r;
    }

    void AudioAssetPrivate::handleTrackerSampleEnd(unsigned int id)
    {
        LOCK

        for(std::list<ReferencedPointer<TrackerSample> >::iterator i = playing_.begin();
            i != playing_.end();
            i++)
        {
            if((*i).pointer()->id() == id)
            {
                playing_.erase(i);
                break;
            }
        }
    }

    void AudioAssetPrivate::setVolume(float volume)
    {
        // Sanity check for the new value
        volume = bb::clamp(volume, 0.0f, 1.0f);

        // Tune volume of this asset's trackersamples
        LOCK
        for(std::list<ReferencedPointer<TrackerSample> >::iterator i = playing_.begin();
            i != playing_.end();
            i++)
        {
            (*i).pointer()->setVolume(volume);
        }
    }

    void AudioAssetPrivate::fadeOut(unsigned int fadeOutTimeMilliseconds)
    {
        // Sanity check for the new value
        fadeOutTimeMilliseconds = bb::clamp(fadeOutTimeMilliseconds, 0, 1000);

        // Fade out the playing samples. This also disconnects the "ended"
        // signal listening.
        LOCK
        while(playing_.begin() != playing_.end())
        {
            std::list<ReferencedPointer<TrackerSample> >::iterator i = playing_.begin();
            (*i).pointer()->fadeOut(fadeOutTimeMilliseconds);
            playing_.erase(i);
        }
    }
}
