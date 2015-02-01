/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "AudioEnginePrivate.hpp"
#include "AudioAssetPrivate.hpp"
#include "helpers/AudioAsset.hpp"
#include "helpers/Log.hpp"

namespace bb
{
    AudioAsset::AudioAsset(const std::string& filename, bool parallelPlay, bool looping):
        private_(new AudioAssetPrivate(filename, parallelPlay, looping))
    {
        private_->increment();
    }

    AudioAsset::AudioAsset(AudioAsset const& r):
        private_(r.private_)
    {
        private_->increment();
    }

    AudioAsset::~AudioAsset()
    {
        private_->decrement();
        private_ = NULL;
    }

    AudioAsset& AudioAsset::operator=(AudioAsset const& r)
    {
        if (this != &r)
        {
            private_ = r.private_;
            private_->increment();
        }
        return *this;
    }

    bool AudioAsset::play(float volume)
    {
        return private_->play(volume);
    }

    void AudioAsset::setVolume(float volume)
    {
        private_->setVolume(volume);
    }

    void AudioAsset::fadeOut(unsigned int fadeOutTimeMilliseconds)
    {
        private_->fadeOut(fadeOutTimeMilliseconds);
    }
}
