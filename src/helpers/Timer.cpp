/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/Timer.hpp"
#include "helpers/Exception.hpp"
#include "helpers/Log.hpp"
#include <time.h>
#include <unistd.h>
#include <ctime>
#ifdef __APPLE__
    #include <mach/mach_time.h>
#endif

namespace boombox
{
    Timer::Timer()
    {
    }

    Timer::~Timer()
    {
    }

    unsigned int Timer::milliseconds()
    {
    #ifdef __APPLE__
        return nanoseconds() / 1000000LL;
    #else // Android and Linux
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return now.tv_sec * 1000LL + now.tv_nsec / 1000000LL;
    #endif
    }

    uint64_t Timer::nanoseconds()
    {
    #ifdef __APPLE__
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);

        uint64_t tmp = mach_absolute_time();
        tmp *= info.numer;
        tmp /= info.denom;

        return tmp;
    #else // Android and Linux
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return now.tv_sec * 1000000000LL + now.tv_nsec;
    #endif
    }

    void Timer::sleepMilliseconds(unsigned int ms)
    {
        nanoSleepFromMilliseconds(ms);
    }

    void Timer::nanoSleepFromMilliseconds(unsigned int milliseconds)
    {
        struct timespec tim, tim2;
        tim.tv_sec = milliseconds / 1000;
        tim.tv_nsec = (milliseconds % 1000) * 1000000LL;

        if (nanosleep(&tim , &tim2) < 0)
        {
            throw Exception("Timer::nanoSleep call to nanosleep() failed.");
        }
    }
}
