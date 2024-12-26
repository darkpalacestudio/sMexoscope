#include "PluginProcessor.h"
#include "PluginEditor.h"

SmexoscopeAudioProcessorEditor::SmexoscopeAudioProcessorEditor(SmexoscopeAudioProcessor& p) :
    juce::AudioProcessorEditor(&p),
    audioProcessor(p),
    effect(audioProcessor.smexoscope),
    waveDisplay(effect, headsImage, readoutImage)
{
    // Filmstrip has 5 images but External triggering mode is not implemented.
    retriggerModeButton.setNumStates(4);

    addAndMakeVisible(timeKnob, 2);
    addAndMakeVisible(timeText, 2);
    addAndMakeVisible(ampKnob, 2);
    addAndMakeVisible(ampText, 2);
    addAndMakeVisible(intTrigSpeedKnob, 2);
    addAndMakeVisible(speedText, 2);
    addAndMakeVisible(retrigThreshKnob, 2);
    addAndMakeVisible(threshText, 2);
    addAndMakeVisible(retrigLevelSlider, 2);
    addAndMakeVisible(retriggerModeButton, 2);
    addAndMakeVisible(syncRedrawButton, 2);
    addAndMakeVisible(freezeButton, 2);
    addAndMakeVisible(dcKillButton, 2);
    addAndMakeVisible(channelSelectionButton, 2);
    addAndMakeVisible(waveDisplay, 1);

    // Load the current parameter values into the controls.
    // Note: This only works correctly if setStateInformation is called by
    // the host before the editor window is constructed.
    timeKnob.setValue(effect.getParameter(Smexoscope::kTimeWindow));
    ampKnob.setValue(effect.getParameter(Smexoscope::kAmpWindow));
    intTrigSpeedKnob.setValue(effect.getParameter(Smexoscope::kTriggerSpeed));
    retrigThreshKnob.setValue(effect.getParameter(Smexoscope::kTriggerLimit));
    retrigLevelSlider.setValue(effect.getParameter(Smexoscope::kTriggerLevel));
    retriggerModeButton.setValue(effect.getParameter(Smexoscope::kTriggerType));
    syncRedrawButton.setValue(effect.getParameter(Smexoscope::kSyncDraw));
    freezeButton.setValue(effect.getParameter(Smexoscope::kFreeze));
    dcKillButton.setValue(effect.getParameter(Smexoscope::kDCKill));
    channelSelectionButton.setValue(effect.getParameter(Smexoscope::kChannel));

    setSize(825, 300);
    startTimerHz(30);
}

void SmexoscopeAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    g.drawImageAt(backgroundImage, 0, 0);
}

void SmexoscopeAudioProcessorEditor::resized()
{
    waveDisplay.setBounds(36, 16, 627, 269);

    timeKnob.setBounds(697, 31, 33, 33);
    timeText.setBounds(698, 71, 30, 12);

    ampKnob.setBounds(762, 31, 33, 33);
    ampText.setBounds(762, 71, 30, 12);

    retriggerModeButton.setBounds(718, 94, 60, 13);
    retrigLevelSlider.setBounds(11, 13, 12, 276);

    intTrigSpeedKnob.setBounds(700, 134, 33, 33);
    speedText.setBounds(700, 174, 30, 12);

    retrigThreshKnob.setBounds(765, 134, 33, 33);
    threshText.setBounds(767, 174, 30, 12);

    syncRedrawButton.setBounds(696, 222, 41, 17);
    freezeButton.setBounds(754, 222, 41, 17);
    dcKillButton.setBounds(690, 259, 41, 17);
    channelSelectionButton.setBounds(748, 259, 41, 17);
}

void SmexoscopeAudioProcessorEditor::timerCallback()
{
    waveDisplay.repaint();
    updateParameters();
}

void SmexoscopeAudioProcessorEditor::updateParameters()
{
    // This function is called from a timer on the UI thread to read the
    // positions of the knobs and buttons and update the parameter values.
    // Since this was based on a VST2, all parameters have values between
    // 0.0f and 1.0f. The parameters are not exposed to the host.
    effect.setParameter(Smexoscope::kTimeWindow, float(timeKnob.getValue()));
    effect.setParameter(Smexoscope::kAmpWindow, float(ampKnob.getValue()));
    effect.setParameter(Smexoscope::kTriggerSpeed, float(intTrigSpeedKnob.getValue()));
    effect.setParameter(Smexoscope::kTriggerLimit, float(retrigThreshKnob.getValue()));
    effect.setParameter(Smexoscope::kTriggerType, retriggerModeButton.getValue());
    effect.setParameter(Smexoscope::kSyncDraw, syncRedrawButton.getValue());
    effect.setParameter(Smexoscope::kFreeze, freezeButton.getValue());
    effect.setParameter(Smexoscope::kDCKill, dcKillButton.getValue());
    effect.setParameter(Smexoscope::kChannel, channelSelectionButton.getValue());
    effect.setParameter(Smexoscope::kTriggerLevel, float(retrigLevelSlider.getValue()));

//TODO: not thread safe
    double sampleRate = effect.getSampleRate();

    // The TIME knob sets the number of pixels per sample. It ranges from 31.62
    // pixels per sample to 0.0003162 pixels/sample, which is 3162 samples/pixel.
    // If the TIME knob is at 0.3 or 30%, there is exactly one pixel per sample.
    // The default of 0.75 or 75% is ~178 samples per pixel.
    // The original code had a comment here, `[0=>10 1=>0.001`, so perhaps the
    // range at some point was from 10 pixels/sample to 1000 samples/pixel.
    // The formula for that would be `pow(10, 1 - knob*4)` and the knob at 25%
    // would now be one pixel/sample. Not sure why this got changed.
    timeText.setValue(float(std::pow(10.0, 1.5 - timeKnob.getValue() * 5.0)));

    ampText.setValue(powf(10.f, ampKnob.getValue()*6.f-3.f));
    speedText.setValue(pow(10.0, 2.5*intTrigSpeedKnob.getValue()-5)*sampleRate);
    threshText.setValue(pow(10.f, retrigThreshKnob.getValue()*4.f));

//TODO: fix warnings
}
