/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_AUDIORESOURCE
#define BOOMBOX_AUDIORESOURCE

#include "helpers/Class.hpp"
#include "helpers/Resource.hpp"
#include "helpers/FileHandle.hpp"
#include <string>
#include <stdint.h>

namespace boombox
{
    class AudioResource: public Resource
    {
    public:
        BOOMBOX_CLASS_UNCOPYABLE(AudioResource)

        AudioResource(FileHandle* fileHandle);
        ~AudioResource();
        unsigned int channels() const;
        unsigned int bitPerSample(void) const;
        unsigned int bytesPerSample(void) const;
        int playBackRate(void) const;
        unsigned int sizeInBytes(void) const;
        bool isSigned(void) const;
        const unsigned char* data(void) const;
        int16_t sample(unsigned int location, bool& end) const;

    private:
        void load(FileHandle*);
        bool channels_;
        unsigned int bit_;
        unsigned int bytesPerSample_;
        int rate_;
        unsigned int sizeInBytes_;
        bool isSigned_;
        unsigned char* data_;
    };
}

#endif
