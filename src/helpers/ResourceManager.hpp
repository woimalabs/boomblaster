/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_RESOURCEMANAGER
#define BB_RESOURCEMANAGER

#include <w/base/Class.hpp>
#include <string>
#ifdef ANDROID
    #include <jni.h>
    #include <sys/types.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif

namespace bb
{
    class ResourceManager
    {
    public:
        COPYABLE(ResourceManager);

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
