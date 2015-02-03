/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef TESTPLAY_DUMMYAPPLICATION
#define TESTPLAY_DUMMYAPPLICATION

#include <boombox/AudioEngine.hpp>
#include <boombox/AudioAsset.hpp>
#include <unistd.h>

class DummyApplication
{
public:
    DummyApplication():
        audioEngine_(false, "."),
        audioAsset_("teleport.wav", true)
    {
    }

    ~DummyApplication()
    {
    }

    void run()
    {
        audioAsset_.play();
        sleep(2);
    }

private:
    boombox::AudioEngine audioEngine_;
    boombox::AudioAsset audioAsset_;
};

#endif
