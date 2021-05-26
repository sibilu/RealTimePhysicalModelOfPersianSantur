/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DampedString.hpp"
#include "SanturString.h"

//==============================================================================
/**
*/
class SanturTestAudioProcessor  : public juce::AudioProcessor, juce::Timer
{
public:
    //==============================================================================
    SanturTestAudioProcessor();
    ~SanturTestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override; 

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float limit(float input, float min, float max);

    void checkActiveNotes();
    void processAndUpdateStrings();
    double outputSound();
    
    void removeExpired();
    void enqueue(int value);
    void dequeue();
    void displayQueue();
    void showFront();
    bool isEmpty();

    
    void timerCallback() override;
    
//    double stringLength = 0.5f;
    double B = 0.00031;
    int excitationSelection = 1;
    int fs;

private:
    //==============================================================================
    
    double outPos = 0.12f;
    double pluckLoc = 0.7f;
    
    double s0 = 1.14f;
//    double s1 = 0.00030f;
    double s1 = 0.0006;
    
    double damp, stiffness, stringDiameter, stringRadius;
    
    double pBrass = 8400;
    double pSteel = 7700;
    double Ebrass = 113500000000;
    double Esteel = 180000000000;
    
    int detuneValue;
 
    OwnedArray<SanturString> santurStrings;
    
    std::unique_ptr<SanturString> string1; // dSharpLow51
    std::unique_ptr<SanturString> string2; // d62
    std::unique_ptr<SanturString> string3; // fLow53
    std::unique_ptr<SanturString> string4; // f65
    std::unique_ptr<SanturString> string5; // gLow55
    std::unique_ptr<SanturString> string6; // g67
    std::unique_ptr<SanturString> string7; // aLow57
    std::unique_ptr<SanturString> string8; // a69
    std::unique_ptr<SanturString> string9; // aSharpLow58
    std::unique_ptr<SanturString> string10; // aSharp70
    std::unique_ptr<SanturString> string11; // cLow60
    std::unique_ptr<SanturString> string12; // c72
    std::unique_ptr<SanturString> string13; // dlow62
    std::unique_ptr<SanturString> string14; // d74
    std::unique_ptr<SanturString> string15; // dSharpLow63
    std::unique_ptr<SanturString> string16; // dSharp75
    std::unique_ptr<SanturString> string17; // fLow65
    std::unique_ptr<SanturString> string18; // f77
     

    std::vector<double> stringTensions{11800.f, 39003.f, 16079.f, 68503.f, 22079.f, 98926.f, 29772.f, 138692.f, 31010.f, 147464.f, 42466.f, 200700.f, 54010.f, 263315.f, 53351.f, 273722.f, 60384.f, 352863.f};
    
    std::vector<double> stringLengths{0.73, 0.53, 0.69, 0.50, 0.64, 0.48, 0.59, 0.45, 0.54, 0.42, 0.50, 0.39, 0.45, 0.36, 0.40, 0.33, 0.34, 0.3};
    
    std::vector<double> rValues, aValues, iValues;
    
    std::vector<int> midiValues{48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65};
    
    std::vector<bool> playNote{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    
    std::vector<bool> triggerProcess{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    
    double stringOut0, stringOut1, stringOut2, stringOut3,stringOut4, stringOut5, stringOut6, stringOut7,stringOut8, stringOut9, stringOut10, stringOut11, stringOut12, stringOut13, stringOut14, stringOut15, stringOut16, stringOut17, mainOut;
    
    double vel[18] = {0.0};
    double velocityFullRange, velocityNormalized;
    
    int maxActiveNotes = 6;
    int currentActiveNotes = 0;
    
    int currentMidiNotes[6] = {0};

    int A[6] = {0};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessor)
};
