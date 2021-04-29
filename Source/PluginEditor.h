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

    Slider s1DampingSlider;
    Slider pluckLocSlider;
    
    Slider tensionSlider;
    Slider outputPosSlider;
//    -----------------------
    Label s1DampingSliderLabel;
    Label pluckLocLabel;
    
    Label tensionLabel;
    Label outputPosLabel;
    
    Label excitationLabel;
    ComboBox excitationMenu;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessorEditor)
};
