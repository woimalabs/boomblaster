/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_FILEHANDLE
#define BB_FILEHANDLE

#include "helpers/Exception.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string>
#ifdef ANDROID
    #include <jni.h>
    #include <sys/types.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif

namespace bb
{
    class FileHandle
    {
    public:
        ~FileHandle();
        unsigned int read(char* targetBuffer, unsigned int byteAmountToRead);
        std::string filename();
        unsigned int byteSize();
        #ifdef ANDROID
            AAsset* pointer();
        #else // linux or iOS
            FILE* pointer();
        #endif

    private:
        friend class ResourceManagerPrivate;

        void open();
        void close();
        std::string filename_;
        unsigned int currentReadIndex_;
        unsigned int byteSize_;
        #ifdef ANDROID
            FileHandle(const std::string& filename, AAssetManager* androidAssetManager);
            AAssetManager* androidAssetManager_;
            AAsset* file_;
        #else // linux or iOS
            FileHandle(const std::string& filename);
            FILE *file_;
        #endif
    };
}

#endif
