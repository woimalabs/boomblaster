/**
 * boombox
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#include "AudioEnginePrivate.hpp"
#include "helpers/Log.hpp"
#include "helpers/Exception.hpp"
#include "helpers/Timer.hpp"

namespace boombox
{
    AudioEnginePrivate* AudioEnginePrivate::singleton_ = NULL;

    static OSStatus playbackCallback(void* selfPointer, AudioUnitRenderActionFlags* ioActionFlags,
        const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames,
        AudioBufferList* ioData)
    {
        AudioEnginePrivate::AudioEnginePrivate* self = (AudioEnginePrivate::AudioEnginePrivate*)selfPointer;
        SInt16* outSamples = (SInt16*)ioData->mBuffers[0].mData;
        self->writeCallback(inNumberFrames * 2 /* 2 bytes per sample */, outSamples);
        return noErr;
    }

    static OSStatus recordingCallback(void* self,
        AudioUnitRenderActionFlags* ioActionFlags,
        const AudioTimeStamp* inTimeStamp,
        UInt32 inBusNumber,
        UInt32  inNumberFrames,
        AudioBufferList* ioData)
    {
        return noErr;
    }

    AudioEnginePrivate::AudioEnginePrivate(bool mute):
        resourceManager_(),
        tracker_(mute == true ? 0.0f : 1.0f)
    {
        // iOS's AudioUnit initialization
        setupAudioUnitSession();
        setupAudioGraph(mute);

        singleton_ = this;
    }

    AudioEnginePrivate::~AudioEnginePrivate()
    {
        LOGI("AudioEnginePrivate::shutting down...");
        OSStatus status = AudioOutputUnitStop(ioUnit_);
        if (noErr != status)
        {
            throw Exception("AudioOutputUnitStop failed");
        }

        // TODO: polish with condition
        Timer::sleepMilliseconds(500); // wait until shutdown is completed

        AudioComponentInstanceDispose(ioUnit_);
        LOGI("AudioEnginePrivate::shutdown completed.");
    }

    void AudioEnginePrivate::setupAudioUnitSession()
    {
        AVAudioSession* session = [AVAudioSession sharedInstance];

        // TODO: Specify that this object is the delegate of the audio session, so that
        //       this object's endInterruption method will be invoked when needed.

        // Set to handle interrupts (call, alarm, etc.)
        NSError *error = nil;
        [session setCategory: AVAudioSessionCategoryAmbient error: &error];
        if (error != nil)
        {
            throw Exception("AVAudioSession setCategory() failed.");
            return;
        }

        // Activate
        [session setActive: YES error: &error];
        if (error != nil)
        {
            throw Exception("Error activating audio session during initial setup.");
            return;
        }
    }

    void AudioEnginePrivate::setupAudioGraph(UInt32 busCount)
    {
        OSStatus result = noErr;
        UInt32 outputUnitId = 0; // create id for output element unit

        // Setup audio units
        AudioComponentDescription iODescription;
        iODescription.componentType = kAudioUnitType_Output; // is both: i and o, NOTE Recording to be removed!
        iODescription.componentSubType = kAudioUnitSubType_RemoteIO;
        iODescription.componentManufacturer = kAudioUnitManufacturer_Apple;
        iODescription.componentFlags = 0;
        iODescription.componentFlagsMask = 0;

        // Get component
        AudioComponent component = AudioComponentFindNext(NULL, &iODescription);

        // Get audio units
        result = AudioComponentInstanceNew(component, &ioUnit_);
        if (noErr != result)
        {
            throw Exception("AudioComponentInstanceNew failed");
        }

        // Enable IO for playback
        UInt32 data1 = 1;
        result = AudioUnitSetProperty(ioUnit_,
            kAudioOutputUnitProperty_EnableIO,
            kAudioUnitScope_Output,
            outputUnitId, // output
            &data1,
            sizeof(data1));

        if (noErr != result)
        {
            throw Exception("AudioUnitSetProperty (output) failed");
        }

        // Describe format
        streamFormat_.mSampleRate       = 44100.00;
        streamFormat_.mFormatID         = kAudioFormatLinearPCM;
        streamFormat_.mFormatFlags      = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
        streamFormat_.mFramesPerPacket  = 1;
        streamFormat_.mChannelsPerFrame = 1;
        streamFormat_.mBitsPerChannel   = 16;
        streamFormat_.mBytesPerPacket   = 2;
        streamFormat_.mBytesPerFrame    = 2;

        result = AudioUnitSetProperty(ioUnit_,
            kAudioUnitProperty_StreamFormat,
            kAudioUnitScope_Input,
            outputUnitId, // output
            &streamFormat_,
            sizeof(streamFormat_));

        if (noErr != result)
        {
            throw Exception("AudioUnitSetProperty (output format) failed");
        }

        // Set output callback
        AURenderCallbackStruct callbackStruct;
        callbackStruct.inputProc = playbackCallback;
        callbackStruct.inputProcRefCon = this;
        result = AudioUnitSetProperty(ioUnit_,
            kAudioUnitProperty_SetRenderCallback,
            kAudioUnitScope_Global,
            outputUnitId,
            &callbackStruct,
            sizeof(callbackStruct));
        if (noErr != result)
        {
            throw Exception("AudioUnitSetProperty (playbackCallback) failed");
        }
        
        // Init
        result = AudioUnitInitialize(ioUnit_);
        if (noErr != result)
        {
            throw Exception("AudioUnitInitialize failed");
        }

        // Start
        result = AudioOutputUnitStart(ioUnit_);
        if (noErr != result)
        {
            throw Exception("AudioOutputUnitStart failed");
        }

        // debug print the setup
        // CAShow (ioUnit_);
        
        // Get the hardware sample rate
        Float64 hardwareSampleRate = 44100.0f;
        hardwareSampleRate = [[AVAudioSession sharedInstance] sampleRate];
        LOGD("hw samplerate: %f", hardwareSampleRate);
    }

    void AudioEnginePrivate::writeCallback(size_t size, SInt16* targetBuffer)
    {
        tracker_.getData(size, (unsigned char*)targetBuffer);
    }

    void audioRouteChangeListenerCallback (void *inUserData,
        AudioSessionPropertyID inPropertyID, UInt32 inPropertyValueSize,
        const void* inPropertyValue)
    {
        // TODO
        LOGE("Stub function called: audioRouteChangeListenerCallback");
    }
}
