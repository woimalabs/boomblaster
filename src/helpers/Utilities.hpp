/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_HELPERS
#define BOOMBOX_HELPERS

namespace boombox
{
    inline float clamp(float source, float min, float max)
    {
        return source < min ? min : (source > max ? max : source);
    }

    inline unsigned int clamp(unsigned int source, unsigned int min, unsigned int max)
    {
        return source < min ? min : (source > max ? max : source);
    }
}

#endif
