/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/ResourceManager.hpp"
#include "helpers/ResourceManagerPrivate.hpp"
#include <string>

namespace bb
{
    #ifdef ANDROID
        ResourceManager::ResourceManager(AAssetManager* androidAssetManager):
            private_(new ResourceManagerPrivate("."))
        {
            private_->setAndroidAssetManager(androidAssetManager);
        }
    #elif linux
        ResourceManager::ResourceManager(const std::string& basePath):
            private_(new ResourceManagerPrivate(basePath))
        {
        }
    #elif __APPLE__
        ResourceManager::ResourceManager():
            private_(new ResourceManagerPrivate("."))
        {
        }
    #endif

    ResourceManager::ResourceManager(ResourceManager const& r):
        private_(r.private_)
    {
        private_->increment();
    }

    ResourceManager::~ResourceManager()
    {
        private_->decrement();
    }

    ResourceManager& ResourceManager::operator=(ResourceManager const& r)
    {
        if (this != &r)
        {
            private_ = r.private_;
            private_->increment();
        }
        return *this;
    }

    bool ResourceManager::exists(const std::string& filename)
    {
        return ResourceManagerPrivate::exists(filename);
    }
}
