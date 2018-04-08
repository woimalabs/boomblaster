/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BOOMBOX_LOG
#define BOOMBOX_LOG

#ifdef __APPLE__
#include <stdio.h>
// Don't define DEBUG here, control its definition with xcodeproj build settings on iOS
#else
#include <cstdio>
#define DEBUG 1
#endif

#define LOG boombox::Log::D("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
#define LOGD(...) boombox::Log::D(__VA_ARGS__);
#define LOGI(...) boombox::Log::I(__VA_ARGS__);
#define LOGE(...) boombox::Log::E(__VA_ARGS__);

namespace boombox
{
    class Log
    {
    public:
#ifdef DEBUG
        static void D(const char *fmt, ...);
        static void I(const char *fmt, ...);
#else
        static void D(const char *fmt, ...) {}
        static void I(const char *fmt, ...) {}
#endif
        
        static void E(const char *fmt, ...);
    };
}

#endif
