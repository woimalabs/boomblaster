/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_CLASS
#define BOOMBOX_CLASS

namespace w
{
    #define BOOMBOX_CLASS_COPYABLE(ClassName) \
        ClassName(ClassName const& instance); \
        ClassName& operator=(ClassName const& r);

    #define BOOMBOX_CLASS_UNCOPYABLE(ClassName) \
    private: \
        ClassName(const ClassName&); \
        ClassName& operator=(const ClassName&); \
    public:
}

#endif
