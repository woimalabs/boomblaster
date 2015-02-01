/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_LOG
#define BB_LOG

#ifdef __APPLE__
#include <stdio.h>
#else
#include <cstdio>
#endif

#define DEBUG 1

#define LOG bb::Log::D("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
#define LOGD(...) bb::Log::D(__VA_ARGS__);
#define LOGI(...) bb::Log::I(__VA_ARGS__);
#define LOGE(...) bb::Log::E(__VA_ARGS__);

namespace bb
{
    class Log
    {
    public:
#ifdef DEBUG
        static void D(const char *fmt, ...);
#else
        static void D(const char *fmt, ...) {}
#endif
        static void I(const char *fmt, ...);
        static void E(const char *fmt, ...);
    };
}

#endif
