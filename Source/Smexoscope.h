#pragma once

#include <JuceHeader.h>
#include "Defines.h"

/*
  This was CSmartelectronixDisplay in the original code, but that class also
  functioned as the main plug-in object. Here it only captures the audio.
*/
class Smexoscope
{
public:
    // Parameters
    enum
    {
        kTriggerSpeed,  // internal trigger speed, knob
        kTriggerType,   // trigger type, selection
        kTriggerLevel,  // trigger level, slider
        kTriggerLimit,  // retrigger threshold, knob
        kTimeWindow,    // X-range, knob
        kAmpWindow,     // Y-range, knob
        kSyncDraw,      // sync redraw, on/off
        kChannel,       // channel selection, left/right
        kFreeze,        // freeze display, on/off
        kDCKill,        // kill DC, on/off
        kNumParams
    };

    // Trigger types
    enum
    {
        kTriggerFree = 0,
        //kTriggerTempo,
        kTriggerRising,
        kTriggerFalling,
        kTriggerInternal,
        //kTriggerExternal,
        kNumTriggerTypes
    };

    Smexoscope();

    void prepareToPlay(double sampleRate);
    void reset();

    void process(juce::AudioBuffer<float>& buffer);

    void setParameter(int index, float value);
    float getParameter(int index) const;

    float* getSaveBlock() { return SAVE; }
    constexpr size_t getSaveBlockSize() { return sizeof(float) * kNumParams; }

    double getSampleRate() const { return sampleRate; }

    const std::vector<juce::Point<int>>& getPeaks() const { return peaks; }
    const std::vector<juce::Point<int>>& getCopy() const { return copy; }

protected:
    // Array containing the waveform readings. The `copy` array is only
    // updated when the trigger hits and is used in Sync Redraw mode.
    std::vector<juce::Point<int>> peaks;
    std::vector<juce::Point<int>> copy;

    // Current write position into the peaks array.
    size_t index;

    // How often we taken a reading, i.e. the amount of samples / pixel.
    double counter;

    // Largest and smallest samples seen in this block.
    float max, min;

    // Whether the last peak we encountered was a maximum or minimum.
    bool lastIsMax;

    // The previous sample (for edge triggers).
    float previousSample;

    // Oscillator used for Internal trigger mode.
    double triggerPhase;

    // Counter that limits how soon the trigger may happen again.
    int triggerLimitPhase;

    // DC killer filter state.
    double dcKill, dcFilterTemp;

    // This array holds the parameter values. They're stored in an array so
    // they can be loaded/saved easily by copying (into) the whole array.
    float SAVE[kNumParams];

    // Sample rate that was passed into `prepareToPlay`.
    double sampleRate = 44100.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Smexoscope)
};
