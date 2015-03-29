/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_RESOURCEMANAGER
#define BOOMBOX_RESOURCEMANAGER

#include "Class.hpp"
#include <string>
#ifdef ANDROID
    #include <jni.h>
    #include <sys/types.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif

namespace boombox
{
    class ResourceManager
    {
    public:
        BOOMBOX_CLASS_COPYABLE(ResourceManager);

#ifdef ANDROID
        ResourceManager(AAssetManager* androidAssetManager);
#elif __linux__
        ResourceManager(const std::string& basePath);
#elif __APPLE__
        ResourceManager();
#endif
        virtual ~ResourceManager();
        static bool exists(const std::string& filename);

    private:
        class ResourceManagerPrivate* private_;
    };
}

#endif
