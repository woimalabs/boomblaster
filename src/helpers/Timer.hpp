/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_TIMER
#define BOOMBOX_TIMER

#include <time.h>
#include <stdint.h> // For uint64_t

namespace boombox
{
    class Timer
    {
    public:
        Timer();
        ~Timer();

        /**
         * @return milliseconds. NOTE: start time undefined. Values
         *     are useful only for example when looking time differences.
         */
        static unsigned int milliseconds();

        /**
         * @return nanoseconds. NOTE: start time undefined. Values
         *     are useful only for example when looking time differences.
         */
        static uint64_t nanoseconds();

        static void sleepMilliseconds(unsigned int milliseconds);

    private:
        static void nanoSleepFromMilliseconds(unsigned int milliseconds);
    };
}

#endif
