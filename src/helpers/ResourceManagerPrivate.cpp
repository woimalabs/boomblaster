/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/ResourceManagerPrivate.hpp"
#include "helpers/FileHandle.hpp"
#include "helpers/Lock.hpp"
#include "helpers/Exception.hpp"
#include "helpers/Log.hpp"
#include <utility> // std::pair
#include <functional>
using std::make_pair;

namespace bb
{
    ResourceManagerPrivate* ResourceManagerPrivate::singleton_ = NULL;
    #ifdef ANDROID
        AAssetManager* ResourceManagerPrivate::androidAssetManager_ = NULL;
    #endif

    ResourceManagerPrivate::ResourceManagerPrivate(const std::string& basePath):
        basePath_(basePath)
    {
        if (singleton_ != NULL)
        {
            LOGE("ResourceManagerPrivate (==ResourceManager in public API!) exists already.");
            throw Exception("ResourceManagerPrivate exists already.");
        }
        else
        {
            //LOGI("ResourceManagerPrivate created.");
        }
        singleton_ = this;
    }

    ResourceManagerPrivate::~ResourceManagerPrivate()
    {
        if (singleton_->assetPrivates_.size() == 0)
        {
            LOGI("ResourceManager: all freed.");
        }
        else
        {
            LOGI("ResourceManager: existing references:");
            std::map<std::string, Referenced*>::iterator i;
            for (i = singleton_->assetPrivates_.begin(); i != singleton_->assetPrivates_.end(); i++)
            {
                std::string id = i->first;
                Referenced* referenced = i->second;
                LOGI(" -(id:%s)(refcount:%d)", id.c_str(), referenced->referenceCount());
            }
        }
        singleton_ = NULL;
    }

    Referenced* ResourceManagerPrivate::assetPrivate(const std::string& id)
    {
        if (singleton_ == NULL)
        {
            throw Exception("ResourceManager needed to load resources.");
        }

        Lock lock(singleton_->mutex_);

        Referenced* r = NULL;
        std::string key(id);
        std::map<std::string, Referenced*>::const_iterator i = singleton_->assetPrivates_.find(key);
        if (i != singleton_->assetPrivates_.end())
        {
            r = i->second;
        }
        return r;
    }

    void ResourceManagerPrivate::setAssetPrivate(const std::string& id, Referenced* assetPrivate)
    {
        Lock lock(singleton_->mutex_);

        assetPrivate->setObserver(singleton_);

        std::pair<std::string, Referenced*> tmp0 = std::make_pair(id, assetPrivate);
        singleton_->assetPrivates_.insert(tmp0);

        //sigc::connection connection = assetPrivate->destroy.connect(
        //    sigc::mem_fun(singleton_, &ResourceManagerPrivate::handleResourceDestroy));

        //std::pair<unsigned int, sigc::connection> tmp1 = std::make_pair(assetPrivate->id(), connection);
        //singleton_->assetPrivateConnections_.insert(tmp1);
    }

    void ResourceManagerPrivate::handleReferencedDestroy(unsigned int id)
    {
        Lock lock(singleton_->mutex_);

        // Remove Resource from loaded resources list and signal listener list
        std::map<std::string, Referenced*>::iterator i;
        for (i = singleton_->assetPrivates_.begin(); i != singleton_->assetPrivates_.end(); i++)
        {
            Referenced* assetPrivate = i->second;
            if (assetPrivate->id() == id)
            {
                // Remove Resource's destroy signal connection
                //std::map<unsigned int, sigc::connection>::iterator i2;
                //i2 = singleton_->assetPrivateConnections_.find(id);
                //singleton_->assetPrivateConnections_.erase(i2);

                // Resource will delete itself, look Referenced.hpp
                singleton_->assetPrivates_.erase(i);

                break;
            }
        }
    }

    FileHandle* ResourceManagerPrivate::getFileHandle(const std::string& filename)
    {
        #ifdef ANDROID
            return new FileHandle(filename, androidAssetManager_);
        #elif __linux__
            return new FileHandle(singleton_->basePath_ + "/" + filename);
        #elif __APPLE__
            NSBundle *b = [NSBundle mainBundle];
            NSString *dir = [b resourcePath];
            char const* tmp = [dir UTF8String];
            return new FileHandle(std::string(tmp) + "/" + filename);
        #endif
    }

    #ifdef ANDROID
        AAssetManager* ResourceManagerPrivate::androidAssetManager()
        {
            if (androidAssetManager_ == NULL)
            {
                throw Exception("androidAssetManager not set.");
            }
            return androidAssetManager_;
        }

        void ResourceManagerPrivate::setAndroidAssetManager(AAssetManager* assetManager)
        {
            androidAssetManager_ = assetManager;
        }
    #endif

    bool ResourceManagerPrivate::exists(const std::string& filename)
    {
        bool r = false;

        #ifdef ANDROID
            AAsset* asset = AAssetManager_open(assetManager_, filename, AASSET_MODE_STREAMING);
            if(asset != NULL)
            {
                r = true;
                AAsset_close(asset);
            }
        #else
            // TODO: this is now bit heavy, file opening can be polished away
            std::string fullName;
            fullName += singleton_->basePath_;
            fullName += "/";
            fullName += std::string(filename);
            FILE *file = fopen(fullName.c_str(), "rb");
            if(file)
            {
                r = true;
                fclose(file);
            }
        #endif

        return r;
    }
}
