/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_REFERENCED
#define BOOMBOX_REFERENCED

#include "helpers/Lock.hpp"
#include "helpers/Log.hpp"
#include <cstddef>

namespace boombox
{
    class ReferencedObserver
    {
    public:
        ReferencedObserver()
        {
        }

        virtual ~ReferencedObserver()
        {
        }

        virtual void handleReferencedDestroy(unsigned int id)
        {
            (void)(id);
        }
    };

    class Referenced
    {
    public:
        unsigned int increment()
        {
            referenceCount_++;
            return referenceCount_;
        }

        unsigned int decrement()
        {
            referenceCount_--;
            unsigned int r = referenceCount_;
            if (r == 0)
            {
                if(observer_ != NULL)
                {
                    observer_->handleReferencedDestroy(id_);
                }
                delete this;
            }
            return r;
        }

        unsigned int referenceCount()
        {
            return referenceCount_;
        }

        unsigned int id()
        {
            return id_;
        }

        void setObserver(ReferencedObserver* observer)
        {
            observer_ = observer;
        }

    protected:
        Referenced():
            referenceCount_(0),
            id_(0),
            observer_(NULL)
        {
            Lock lock(mutex_);
            id_ = ++lastId_;
        }

        Referenced(ReferencedObserver* observer):
            referenceCount_(0),
            id_(0),
            observer_(observer)
        {
            Lock lock(mutex_);
            id_ = ++lastId_;
        }

        virtual ~Referenced()
        {
        }

    private:
        unsigned int referenceCount_;
        unsigned int id_;
        ReferencedObserver* observer_;
        static Mutex mutex_;
        static unsigned int lastId_;
    };
}

#endif
