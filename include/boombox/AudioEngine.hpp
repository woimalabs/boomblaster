/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_AUDIOENGINE
#define BOOMBOX_AUDIOENGINE

#ifdef ANDROID
    #include <jni.h>
    #include <sys/types.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif
#include <string>

/**
 * AudioEngine is a class that manages audio.
 *
 * @note This class must be existing to have and play AudioAssets.
 */
namespace boombox
{
    class AudioEngine
    {
    public:
#ifdef ANDROID
        AudioEngine(bool mute, AAssetManager* androidAssetManager);
#elif __linux__
        AudioEngine(bool mute, const std::string& basePath);
#elif __APPLE__
        AudioEngine(bool mute);
#endif

        ~AudioEngine();
        static void setMute(bool);
        static bool mute();

    private:
        /**
         * AudioEngine class is not copyable.
         */
        AudioEngine(AudioEngine const& instance);
        AudioEngine& operator=(AudioEngine const& r);
        static class AudioEnginePrivate* private_;
    };
}

#endif
