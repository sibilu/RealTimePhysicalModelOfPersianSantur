/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DampedString.hpp"

//==============================================================================
/**
*/
class SanturTestAudioProcessorEditor  : public juce::AudioProcessorEditor, public Slider::Listener
{
public:
    SanturTestAudioProcessorEditor (SanturTestAudioProcessor&);
    ~SanturTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;
    
    void mouseDown (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    float getOutputPosition();
    
    void excitationMenuChanged();
    
//    bool mousePressed, playOnce;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SanturTestAudioProcessor& audioProcessor;
    
    
    Slider freqSlider;
    Slider s0DampingSlider;
    Slider s1DampingSlider;
    Slider pluckLocSlider;
    Slider stringLengthSlider;
    Slider stiffnessSlider;
    Slider tensionSlider;
    Slider outputPosSlider;
//    -----------------------
    Label freqSliderLabel;
    Label s0DampingSliderLabel;
    Label s1DampingSliderLabel;
    Label pluckLocLabel;
    Label stringLengthLabel;
    Label stiffnessLabel;
    Label tensionLabel;
    Label outputPosLabel;
    
    Label excitationLabel;
    ComboBox excitationMenu;
    
    Path stringPath, boundaryPath;
    
    float stringLineLength = 100;
    
    float outputPositionEllipse = 200;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessorEditor)
};
