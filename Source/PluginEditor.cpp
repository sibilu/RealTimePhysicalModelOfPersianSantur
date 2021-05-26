/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DampedString.hpp"

//==============================================================================
SanturTestAudioProcessorEditor::SanturTestAudioProcessorEditor (SanturTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400); // prev 700,350
}

SanturTestAudioProcessorEditor::~SanturTestAudioProcessorEditor()
{
}

//==============================================================================
void SanturTestAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (Colour(255,255,247));
    Image background = ImageCache::getFromMemory(BinaryData::screensize_png, BinaryData::screensize_pngSize);
    g.drawImageAt(background,0, 0);
}

void SanturTestAudioProcessorEditor::resized()
{

//    //    EXCITATION MENU
//    excitationMenu.setBounds(570, 280, 100, 20);
//    excitationMenu.addItem("Triangle", 1);
//    excitationMenu.addItem("Hammer", 2);
//    excitationMenu.onChange = [this] {excitationMenuChanged(); };
//    excitationMenu.setSelectedId(1);
//    addAndMakeVisible(excitationMenu);
//        
//    excitationLabel.setText("Excitation", dontSendNotification);
//    excitationLabel.attachToComponent(&excitationMenu, false);
//    excitationLabel.setJustificationType(Justification::centred);
//    excitationLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(excitationLabel);

}

void SanturTestAudioProcessorEditor::sliderValueChanged(Slider * slider) {

}

void SanturTestAudioProcessorEditor::excitationMenuChanged() {
    switch (excitationMenu.getSelectedId()) {
        case 1: audioProcessor.excitationSelection = 1; break;
        case 2: audioProcessor.excitationSelection = 2; break;
            
        default:
            break;
    }
}
