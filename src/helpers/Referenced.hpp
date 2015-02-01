/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_REFERENCED
#define BB_REFERENCED

#include "helpers/Lock.hpp"
#include "helpers/Log.hpp"
#include <cstddef>
using std::ptrdiff_t; // NOTE: sigc++ needs this line
#include <sigc++/signal.h>

namespace bb
{
    class Referenced
    {
    public:
        sigc::signal<void, unsigned int> destroy;

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
                destroy.emit(id_);
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

    protected:
        Referenced():
            referenceCount_(0),
            id_(0)
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

        static Mutex mutex_;
        static unsigned int lastId_;
    };
}

#endif
