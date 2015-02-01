/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_AUDIORESOURCE
#define BB_AUDIORESOURCE

#include "helpers/Resource.hpp"
#include "helpers/FileHandle.hpp"
#include <string>
#include <stdint.h>

namespace bb
{
    class AudioResource: public Resource
    {
    public:
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
