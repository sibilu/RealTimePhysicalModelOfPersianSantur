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

    float getOutputPosition();
    
    void excitationMenuChanged();
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SanturTestAudioProcessor& audioProcessor;
    
    Label excitationLabel;
    ComboBox excitationMenu;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessorEditor)
};
