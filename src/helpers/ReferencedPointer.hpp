/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_REFERENCEDPOINTER
#define BB_REFERENCEDPOINTER

#include "helpers/Referenced.hpp"
#include "helpers/Exception.hpp"

namespace bb
{
    /**
    * @class ReferencedPointer
    *
    * Class to hold reference from classes that are inherited from Referenced class
    */
    template <class T> class ReferencedPointer
    {
    public:
        ReferencedPointer():
            instance_(NULL)
        {
        }

        ReferencedPointer(T* instance):
            instance_(instance)
        {
            if (instance_ != NULL)
            {
                Referenced* tmp = reinterpret_cast<Referenced*>(instance);
                if (tmp == NULL)
                {
                    throw Exception("ReferencedPointer can hold only Referenced classes.");
                }
                instance_->increment();
            }
        }

        ~ReferencedPointer()
        {
            if (instance_ != NULL)
            {
                instance_->decrement();
                instance_ = NULL;
            }
        }

        ReferencedPointer& operator=(ReferencedPointer const& r)
        {
            if (this != &r)
            {
                if (instance_ != r.instance_)
                {
                    if (instance_ != NULL)
                    {
                        instance_->decrement();
                        instance_ = NULL;
                    }
                }

                // Assign r instance if it's other than NULL. NULL is our initial value.
                if (r.instance_ != NULL)
                {
                    instance_ = r.instance_;
                    instance_->increment();
                }
            }
            return *this;
        }

        ReferencedPointer(ReferencedPointer const& r)
        {
            instance_ = r.instance_;
            if (instance_ != NULL)
            {
                instance_->increment();
            }
        }

        bool isNull() const
        {
            return (instance_ == NULL) ? true : false;
        }

        bool exists() const
        {
            return (instance_ != NULL) ? true : false;
        }

        T* pointer() const
        {
            return instance_;
        }

    private:
        T* instance_;
    };
}

#endif
