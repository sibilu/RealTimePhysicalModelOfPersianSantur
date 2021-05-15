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
    setSize (700, 591); // prev 700,350
}

SanturTestAudioProcessorEditor::~SanturTestAudioProcessorEditor()
{
}

//==============================================================================
void SanturTestAudioProcessorEditor::paint (juce::Graphics& g)
{

//    g.fillAll (Colour(255,255,247));
//    g.fillAll (juce::Colours::black);
    Image background = ImageCache::getFromMemory(BinaryData::santur2_jpg, BinaryData::santur2_jpgSize);
    g.drawImageAt(background,0, 0);
    
//    g.setColour(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(60.f);
    g.drawText("The Santur", getLocalBounds(), Justification::centred, true);


}

void SanturTestAudioProcessorEditor::resized()
{
    

    // S1 DAMPING SLIDER
//    s1DampingSlider.addListener(this);
//    s1DampingSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    s1DampingSlider.setColour(Slider::rotarySliderFillColourId, Colour(18,18,17));
//    s1DampingSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(18,18,17));
//    s1DampingSlider.setColour(Slider::thumbColourId, Colour(68,102,187));
//    s1DampingSlider.setBounds(170, 280, 80, 80);
//    s1DampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
//    s1DampingSlider.setRange(0.00001, 0.005, 0.00001f);
//    s1DampingSlider.setColour(Slider::textBoxTextColourId, Colour(18,18,17));
//    s1DampingSlider.setColour(Slider::textBoxOutlineColourId, Colour(255,255,247));
//    s1DampingSlider.setValue(0.00015);
//    addAndMakeVisible(s1DampingSlider);
//
//    s1DampingSliderLabel.setText("Damping", dontSendNotification);
//    s1DampingSliderLabel.attachToComponent(&s1DampingSlider, false);
//    s1DampingSliderLabel.setJustificationType(Justification::centred);
//    s1DampingSliderLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(s1DampingSliderLabel);
    
    // INPUT POSITION SLIDER
//    pluckLocSlider.addListener(this);
//    pluckLocSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    pluckLocSlider.setColour(Slider::rotarySliderFillColourId, Colour(18,18,17));
//    pluckLocSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(18,18,17));
//    pluckLocSlider.setColour(Slider::thumbColourId, Colour(68,102,187));
//    pluckLocSlider.setBounds(270, 280, 80, 80);
//    pluckLocSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
//    pluckLocSlider.setRange(0.1, 1.0, 0.01f);
//    pluckLocSlider.setColour(Slider::textBoxTextColourId, Colour(18,18,17));
//    pluckLocSlider.setColour(Slider::textBoxOutlineColourId, Colour(255,255,247));
//    pluckLocSlider.setValue(0.70f);
//    addAndMakeVisible(pluckLocSlider);
//
//    pluckLocLabel.setText("Pluck Location", dontSendNotification);
//    pluckLocLabel.attachToComponent(&pluckLocSlider, false);
//    pluckLocLabel.setJustificationType(Justification::centred);
//    pluckLocLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(pluckLocLabel);

    
    // OUTPUT POSITION SLIDER
//    outputPosSlider.addListener(this);
//    outputPosSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    outputPosSlider.setColour(Slider::rotarySliderFillColourId, Colour(18,18,17));
//    outputPosSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(18,18,17));
//    outputPosSlider.setColour(Slider::thumbColourId, Colour(68,102,187));
//    outputPosSlider.setBounds(370, 280, 80, 80);
//    outputPosSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
//    outputPosSlider.setRange(0.1, 1.0, 0.01f);
//    outputPosSlider.setColour(Slider::textBoxTextColourId, Colour(18,18,17));
//    outputPosSlider.setColour(Slider::textBoxOutlineColourId, Colour(255,255,247));
//    outputPosSlider.setValue(0.12f);
//    addAndMakeVisible(outputPosSlider);
//
//    outputPosLabel.setText("Output Pos", dontSendNotification);
//    outputPosLabel.attachToComponent(&outputPosSlider, false);
//    outputPosLabel.setJustificationType(Justification::centred);
//    outputPosLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(outputPosLabel);
    
    // TENSION SLIDER
//    tensionSlider.addListener(this);
//    tensionSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    tensionSlider.setColour(Slider::rotarySliderFillColourId, Colour(18,18,17));
//    tensionSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(18,18,17));
//    tensionSlider.setColour(Slider::thumbColourId, Colour(68,102,187));
//    tensionSlider.setBounds(470, 280, 80, 80);
//    tensionSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
//    tensionSlider.setRange(1.0, 80000.0, 1.f);
//    tensionSlider.setColour(Slider::textBoxTextColourId, Colour(18,18,17));
//    tensionSlider.setColour(Slider::textBoxOutlineColourId, Colour(255,255,247));
//    tensionSlider.setValue(5000.f);
//    addAndMakeVisible(tensionSlider);
//
//    tensionLabel.setText("Tension", dontSendNotification);
//    tensionLabel.attachToComponent(&tensionSlider, false);
//    tensionLabel.setJustificationType(Justification::centred);
//    tensionLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(tensionLabel);
    
//    DETUNE SLIDER
//    detuneSlider.addListener(this);
//    detuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    detuneSlider.setColour(Slider::rotarySliderFillColourId, Colour(18,18,17));
//    detuneSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(18,18,17));
//    detuneSlider.setColour(Slider::thumbColourId, Colour(68,102,187));
//    detuneSlider.setBounds(470, 280, 80, 80);
//    detuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
//    detuneSlider.setRange(1, 5, 1);
//    detuneSlider.setColour(Slider::textBoxTextColourId, Colour(18,18,17));
//    detuneSlider.setColour(Slider::textBoxOutlineColourId, Colour(255,255,247));
//    detuneSlider.setValue(1);
//    addAndMakeVisible(detuneSlider);
//
//    detuneLabel.setText("Detune", dontSendNotification);
//    detuneLabel.attachToComponent(&detuneSlider, false);
//    detuneLabel.setJustificationType(Justification::centred);
//    detuneLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
//    addAndMakeVisible(detuneLabel);

//    EXCITATION MENU
    excitationMenu.setBounds(570, 280, 100, 20);
    excitationMenu.addItem("Hanning", 1);
    excitationMenu.addItem("Triangle", 2);
    excitationMenu.addItem("Hammer", 3);
    excitationMenu.onChange = [this] {excitationMenuChanged(); };
    excitationMenu.setSelectedId(2);
    addAndMakeVisible(excitationMenu);
    
    excitationLabel.setText("Excitation", dontSendNotification);
    excitationLabel.attachToComponent(&excitationMenu, false);
    excitationLabel.setJustificationType(Justification::centred);
//    excitationLabel.setColour(Label::textColourId, Colour(juce::Colours::black));
    excitationLabel.setColour(Label::textColourId, Colour(juce::Colours::white));
    addAndMakeVisible(excitationLabel);
}

void SanturTestAudioProcessorEditor::sliderValueChanged(Slider * slider) {

    
    if(slider == & outputPosSlider) {
//        audioProcessor.setOutPosition(outputPosSlider.getValue());
    }
    
    if(slider == & pluckLocSlider) {
//        audioProcessor.setPluckLoc(pluckLocSlider.getValue());
    }
    
    
    if(slider == & s1DampingSlider) {
//        audioProcessor.setS1(s1DampingSlider.getValue());
//        audioProcessor.updateStringClassCoefficients();
    }
    
    if(slider == & tensionSlider) {
//        audioProcessor.setTension(tensionSlider.getValue());
//        audioProcessor.updateStringClassCoefficients();
    }
    
//    if(slider == & detuneSlider) {
//        audioProcessor.setDetune(detuneSlider.getValue());
//        audioProcessor.updateStringClassCoefficients();
//    }
}

void SanturTestAudioProcessorEditor::mouseDown(const MouseEvent &e) {
    audioProcessor.mousePressed = true;
}

void SanturTestAudioProcessorEditor::mouseUp(const MouseEvent &e) {
    audioProcessor.mousePressed = false;
    audioProcessor.playOnce = true;
}

void SanturTestAudioProcessorEditor::excitationMenuChanged() {
    switch (excitationMenu.getSelectedId()) {
        case 1: audioProcessor.excitationSelection = 1; break;
        case 2: audioProcessor.excitationSelection = 2; break;
        case 3: audioProcessor.excitationSelection = 3; break;
            
        default:
            break;
    }
}
