/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "DummyApplication.hpp"

int main(int argc, char *argv[])
{
    try
    {
        DummyApplication dummyApplication;
        dummyApplication.run();
    }
    catch(...)
    {
        LOGE("Unknown exception");
    }

    return 0;
}

