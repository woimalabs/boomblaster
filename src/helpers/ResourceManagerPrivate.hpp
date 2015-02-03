/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_RESOURCEMANAGERPRIVATE
#define BOOMBOX_RESOURCEMANAGERPRIVATE

#include "helpers/Resource.hpp"
#include "helpers/Referenced.hpp"
#include "helpers/Mutex.hpp"
#include "helpers/FileHandle.hpp"
#include <map>
#include <string>
#include <vector>
#ifdef ANDROID
    #include <jni.h>
    #include <sys/types.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif

namespace boombox
{
    class ResourceManagerPrivate: public Referenced, private ReferencedObserver
    {
    public:
        ~ResourceManagerPrivate();
        static Referenced* assetPrivate(const std::string& id);
        static void setAssetPrivate(const std::string& id, Referenced* resource);
        static FileHandle* getFileHandle(const std::string& filename);
        #ifdef ANDROID
            static AAssetManager* androidAssetManager();
            static void setAndroidAssetManager(AAssetManager* androidAssetManager);
        #endif
        static bool exists(const std::string& filename);
        void handleReferencedDestroy(unsigned int);

    private:
        friend class ResourceManager;
        ResourceManagerPrivate(const std::string & basePath);
        static ResourceManagerPrivate* singleton_;
        std::string basePath_;
        Mutex mutex_;
        std::map<std::string, Referenced*> assetPrivates_;

        // assetPrivateConnections_ note:
        // We don't hold reference count in ResourceManager
        // so we delete the listening connection when assetPrivate
        // is freed by the user.
        //std::map<unsigned int, sigc::connection> assetPrivateConnections_;
        #ifdef ANDROID
            static AAssetManager* androidAssetManager_;
        #endif
    };
}

#endif
