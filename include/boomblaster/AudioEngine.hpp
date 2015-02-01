/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_AUDIOENGINE
#define BB_AUDIOENGINE

#include "bb/ResourceManager.hpp"
#include "bb/Class.hpp"
#include <string>

/**
 * AudioEngine is a class that manages audio.
 *
 * @note This class must be existing to have and play AudioAssets.
 */
namespace bb
{
    class AudioEngine
    {
    public:
        BB_CLASS_UNCOPYABLE(AudioEngine)

        /**
         * Creates AudioEngine instance which makes possible to play AudioAssets.
         *
         * @param [in]  mute            Is mute on or off at start.
         * @param [in]  resourceManager Manages loading of files
         */
        AudioEngine(bool mute, ResourceManager& resourceManager);
        ~AudioEngine();
        static void setMute(bool);
        static bool mute();

    private:
        static class AudioEnginePrivate* private_;
    };
}

#endif
