/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_RESOURCE
#define BOOMBOX_RESOURCE

#include "helpers/Referenced.hpp"
#include <string>

namespace boombox
{
    class Resource: public Referenced
    {
    public:
        Resource(const std::string& filename):
            Referenced(),
            filename_(filename)
        {
        }

        virtual ~Resource()
        {
        }

        const std::string& filename()  const
        {
            return filename_;
        }

    private:
        std::string filename_;
    };
}

#endif
