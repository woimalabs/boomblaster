/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/FileHandle.hpp"
#include "helpers/Exception.hpp"
#include "helpers/Log.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string>

namespace bb
{
    #ifdef ANDROID
        FileHandle::FileHandle(const std::string& filename, AAssetManager* androidAssetManager):
    #else // linux
        FileHandle::FileHandle(const std::string& filename):
    #endif
        filename_(filename),
        currentReadIndex_(0),
        #ifdef ANDROID
            androidAssetManager_(androidAssetManager),
        #endif
        byteSize_(0)
    {
        open();
    }

    FileHandle::~FileHandle()
    {
        close();
    }

    // Opens the file and defines byte size
    void FileHandle::open()
    {
        // LOGD("opening file: %s", filename_.c_str());

        #ifdef ANDROID
            file_ = AAssetManager_open(androidAssetManager_, filename_.c_str(), AASSET_MODE_STREAMING);
            if (file_ == NULL)
            {
                LOGE("Failed to load filename: %s", filename_.c_str());
                throw Exception("FileResource::open() failed");
            }
            byteSize_ = AAsset_getLength(file_);
        #else // Linux
            file_ = fopen(filename_.c_str(), "rb");
            if (file_ == NULL)
            {
                LOGE("Failed to load filename: %s", filename_.c_str());
                throw Exception("FileResource::open() failed");
            }

            fseek(file_, 0, SEEK_END);
            byteSize_ = ftell(file_);
            rewind (file_);
        #endif
    }

    unsigned int FileHandle::read(char* targetBuffer, unsigned int byteAmountToRead)
    {
        unsigned int bytesRead = 0;
        unsigned int bytesToBeRead = byteAmountToRead;
        while(true)
        {
            #ifdef ANDROID
                unsigned int readAmount = AAsset_read(file_, targetBuffer, bytesToBeRead);
            #else // linux
                size_t readAmount = fread(targetBuffer, 1, bytesToBeRead, file_);
            #endif

            bytesRead += readAmount;
            bytesToBeRead -= readAmount;

            if(readAmount == 0 || bytesToBeRead <= 0)
            {
                break;
            }
        }
        currentReadIndex_ += bytesRead;
        return bytesRead;
    }

    std::string FileHandle::filename()
    {
        return filename_;
    }

    unsigned int FileHandle::byteSize()
    {
        return byteSize_;
    }

#ifdef ANDROID
    AAsset* FileHandle::pointer()
    {
        return file_;
    }
#else // linux
    FILE* FileHandle::pointer()
    {
        return file_;
    }
#endif

    void FileHandle::close()
    {
        #ifdef ANDROID
            AAsset_close(file_);
        #else // linux
            fclose(file_);
        #endif
    }
}
