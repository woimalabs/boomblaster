/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef TESTPLAY_DUMMYAPPLICATION
#define TESTPLAY_DUMMYAPPLICATION

#include <boomblaster/AudioEngine.hpp>
#include <boomblaster/AudioAsset.hpp>
#include <unistd.h>

class DummyApplication
{
public:
    DummyApplication():
        audioEngine_(true, "./"),
        audioAsset_("teleport.wav")
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
    bb::AudioEngine audioEngine_;
    bb::AudioAsset audioAsset_;
};

#endif
