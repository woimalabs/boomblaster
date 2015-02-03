/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "TrackerSample.hpp"
#include "AudioResource.hpp"
#include "helpers/Timer.hpp"
#include "helpers/Log.hpp"

namespace boombox
{
    TrackerSample::TrackerSample(const ReferencedPointer<AudioResource>& resource, float volume, bool looping, TrackerSampleObserver* owner):
        Referenced(),
        volume_(volume),
        owner_(owner),
        resource_(resource),
        byteSize_(resource.pointer()->sizeInBytes()),
        byteLocation_(0),
        looping_(looping)
    {
        fadeOut_.on_ = false;
        fadeOut_.start_ = 0;
    }

    TrackerSample::~TrackerSample()
    {
    }

    float TrackerSample::volume()
    {
        return volume_;
    }

    void TrackerSample::setVolume(float volume)
    {
        volume_ = volume;
    }

    int16_t TrackerSample::sampleForTracker(bool& end)
    {
        int16_t r = resource_.pointer()->sample(byteLocation_, end);
        byteLocation_ += BytesPerSample;

        if(looping_ == true && byteLocation_ >= byteSize_)
        {
            byteLocation_ = 0;
            end = false;
        }

        if(fadeOut_.on_ == true)
        {
            volume_ -= fadeOut_.ramp_;
            if(volume_ <= 0.0f)
            {
                end = true;
                // we are not interested from this end at parent side, because
                // it is a fadeout end and we have disconnected already from "ended"
                volume_ = 0.0f;
            }
            r = int16_t(volume_ * (float)r);
        }
        else
        {
            r = int16_t(volume_ * (float)r);
            if(end == true)
            {
                LOCK
                owner_->handleTrackerSampleEnd(id());
            }
        }

        return r;
    }

    void TrackerSample::fadeOut(unsigned int fadeTimeMilliseconds)
    {
        LOCK
        if(fadeOut_.on_ == false)
        {
            fadeOut_.start_ = Timer::milliseconds();
            fadeOut_.on_ = true;
            if(fadeTimeMilliseconds == 0)
            {
                fadeOut_.ramp_ = 1.0f;
            }
            else
            {
                fadeOut_.ramp_ = 1.0f / ((float)resource_.pointer()->playBackRate() / 1000.0f * (float)fadeTimeMilliseconds);
            }
        }
    }
}
