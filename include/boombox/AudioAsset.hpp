/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_AUDIOASSET
#define BOOMBOX_AUDIOASSET

#include <string>

/**
 * AudioAsset is a class for sound samples.
 *
 * Supported format(s):
 *  - wav, PCM mono 44100Hz 16bit, signed integer, linear, little endian
 */
namespace boombox
{
    class AudioAsset
    {
    public:
        /**
         * Creates audio asset
         *
         * @note Resources are automatically shared meaning that same audio resource
         * file is loaded only once.
         *
         * @param [in]  filename    filename asset
         */
        AudioAsset(const std::string& filename, bool parallelPlay = false, bool looping = false);
        ~AudioAsset();

        /**
         * AudioAsset class is copyable.
         */
        AudioAsset(AudioAsset const& instance);
        AudioAsset& operator=(AudioAsset const& r);

        /**
         * Plays the sample.
         *
         * @param [in]  volume      Volume level [0.0 - 1.0], value is checked & limited.
         * @return                  TRUE if sample started to play.
         *                           FALSE if tracks were full and sample could not be played.
         *
         * @note AudioEngine must exist to succesfully make a play() call.
         */
        bool play(float volume = 1.0f);

        /**
         * Set volume level.
         *
         * @param [in]  volume      Volume level [0.0 - 1.0], value is checked & limited.
         */
        void setVolume(float volume);

        /**
         * Fades the sample away with linear fade.
         *
         * @param [in]  fadeOutTime    Millisecond time to fadeout the sound.
         *                              Maximum fadeout time is 1000ms.
         */
        void fadeOut(unsigned int fadeOutTimeMilliseconds = 0);

    private:
        class AudioAssetPrivate* private_;
    };
}

#endif
