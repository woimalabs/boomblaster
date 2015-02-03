/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_EXCEPTION
#define BOOMBOX_EXCEPTION

#include <stdexcept>

namespace boombox
{
    class Exception: public std::exception
    {
    public:
        explicit Exception(const char* message):
            std::exception(),
            message_(message)
        {
        }

        virtual ~Exception() throw()
        {
        }

        virtual void raise()
        {
            throw *this;
        }

        virtual const char* what() const throw()
        {
            return message_;
        }

        Exception(Exception const& other):
            message_(other.message_)
        {
        }

    private:
        const char* message_;
    };
}

#endif
