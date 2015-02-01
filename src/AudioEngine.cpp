/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "boomblaster/AudioEngine.hpp"
#include "AudioEnginePrivate.hpp"
#include "helpers/Log.hpp"
#include "helpers/Exception.hpp"
#include "helpers/ResourceManager.hpp"

namespace bb
{
    AudioEnginePrivate* AudioEngine::private_ = NULL;

    AudioEngine::AudioEngine(bool mute)
    {
        if(private_ != NULL)
        {
            throw Exception("Only one AudioEngine can exist once.");
        }
        ResourceManager tmp(".");
        private_ = new AudioEnginePrivate(mute, tmp);
        LOGI("Created AudioEngine.")
    }

    AudioEngine::~AudioEngine()
    {
        LOGI("Shutting down AudioEngine...")
        if(private_ != NULL)
        {
            delete private_;
            private_ = NULL;
        }
        else
        {
            LOGE("AudioEngine::~AudioEngine(), private == NULL, AudioEngine in corrupted state!")
        }
        LOGI("Shutdown AudioEngine.")
    }

    void AudioEngine::setMute(bool value)
    {
        if(private_ != NULL)
        {
            private_->setMute(value);
        }
        else
        {
            throw Exception("AudioEngine::volume(), AudioEngine does not exist.");
        }
    }

    bool AudioEngine::mute()
    {
        if(private_ != NULL)
        {
            return private_->mute();
        }
        else
        {
            throw Exception("AudioEngine::volume(), AudioEngine does not exist.");
        }
    }
}
