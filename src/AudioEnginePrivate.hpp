/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_AUDIOENGINEPRIVATE
#define BB_AUDIOENGINEPRIVATE

#include "Tracker.hpp"
#include "TrackerSample.hpp"
#include "helpers/FileHandle.hpp"
#include "helpers/Log.hpp"
#include "helpers/Mutex.hpp"
#include "helpers/ResourceManager.hpp"
#include "helpers/ResourceManagerPrivate.hpp"
#include "helpers/Class.hpp"
#include <string>
#ifdef __ANDROID__
    // OpenSL ES is used on Android for audio
    #include <SLES/OpenSLES.h>
    #include <SLES/OpenSLES_Android.h>
#elif __APPLE__
    #import <AudioToolbox/AudioToolbox.h>
    #import <AVFoundation/AVFoundation.h>
#elif __linux__
    // Linux uses pulse audio
    #include <pulse/pulseaudio.h>
#endif

namespace bb
{
    class AudioEnginePrivate
    {
    public:
        BB_CLASS_UNCOPYABLE(AudioEnginePrivate)

        friend class AudioEngine;

        static float const VolumeOffThreshold = 0.001f;

        struct State
        {
            enum Enum
            {
                Start,
                Starting,
                Run,
                ShuttingDown,
                End
            };
        };

        void setMute(bool value)
        {
            tracker_.setMute(value);
        }

        bool mute()
        {
            return tracker_.mute();
        }

        static AudioResource* get(const std::string& filename)
        {
            std::string id = std::string("Audio:") + filename;
            AudioResource* r = dynamic_cast<AudioResource*>(ResourceManagerPrivate::assetPrivate(id));
            if (r == NULL)
            {
                FileHandle* tmp = ResourceManagerPrivate::getFileHandle(filename);
                if (tmp != NULL)
                {
                    r = new AudioResource(tmp);
                    ResourceManagerPrivate::setAssetPrivate(id, r);
                    delete tmp;
                }
            }

            return r;
        }

        static bool play(ReferencedPointer<TrackerSample> const& sample)
        {
            return singleton_->tracker_.place(sample);
        }

#ifdef __ANDROID__
        void writeCallback();
#elif __linux__
        void writeCallback(size_t size);
#elif __APPLE__
        void writeCallback(size_t size, SInt16* targetBuffer);
#endif

    private:
        AudioEnginePrivate(bool mute, ResourceManager& resourceManager);
        ~AudioEnginePrivate();
        static AudioEnginePrivate* singleton_;
        ResourceManager resourceManager_; // Holding a reference so that AudioEnginePrivate can call ResourceManagerPrivate functions safely
        Tracker tracker_;
        State::Enum state_;
        Mutex mutex_;
        float volumeAtStart_;
        volatile bool mute_;

        #ifdef __ANDROID__
            void createEngine();
            void createBufferQueueAudioPlayer();
            void shutdown();
            void test();

            // Engine interfaces
            SLObjectItf engineObject_;
            SLEngineItf engineEngine_;

            // Output mix interfaces
            SLObjectItf outputMixObject_;

            // Buffer queue player interfaces
            SLObjectItf bqPlayerObject_;
            SLPlayItf bqPlayerPlay_;
            SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue_;
            SLEffectSendItf bqPlayerEffectSend_;
            SLMuteSoloItf bqPlayerMuteSolo_;
            SLVolumeItf bqPlayerVolume_;

            unsigned char buffer_[44100];

        #elif __APPLE__
            void setupAudioUnitSession();
            void setupAudioGraph(UInt32 busCount);
            void audioRouteChangeListenerCallback(void* inUserData,
                AudioSessionPropertyID inPropertyID, UInt32 inPropertyValueSize,
                const void* inPropertyValue);
            AudioStreamBasicDescription streamFormat_;
            AudioComponentInstance ioUnit_;

        #elif __linux__
            void configureStream();
            pa_threaded_mainloop* mainloop_;
            pa_context* context_;
            pa_stream* stream_;

        #endif
    };
}

#endif
