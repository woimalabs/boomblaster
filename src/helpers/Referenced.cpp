/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "helpers/Referenced.hpp"

namespace bb
{
    Mutex Referenced::mutex_;
    unsigned int Referenced::lastId_ = 0;
}

