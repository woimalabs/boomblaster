/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_CLASS
#define BB_CLASS

namespace w
{
    #define BB_CLASS_COPYABLE(ClassName) \
        ClassName(ClassName const& instance); \
        ClassName& operator=(ClassName const& r);

    #define BB_CLASS_UNCOPYABLE(ClassName) \
    private: \
        ClassName(const ClassName&); \
        ClassName& operator=(const ClassName&); \
    public:
}

#endif
