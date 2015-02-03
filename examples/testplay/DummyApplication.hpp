/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef TESTPLAY_DUMMYAPPLICATION
#define TESTPLAY_DUMMYAPPLICATION

#include <bb/AudioEngine.hpp>
#include <bb/AudioAsset.hpp>

class DummyApplication
{
public:
    DummyApplication():
        audioEngine_(true, "./"),
        audioAsset_("teleport.wav"),
    {

    }

    ~DummyApplication()
    {
    }

    void run()
    {
        audioAsset_.play();
    }

private:
    bb::AudioEngine audioEngine_;
    bb::AudioAsset audioAsset_;
};

#endif
