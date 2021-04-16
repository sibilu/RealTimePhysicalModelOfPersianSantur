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
class SanturTestAudioProcessor  : public juce::AudioProcessor
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
    
    void updateCoefficients();
    void updateStringClassCoefficients();
    
    
    double getKappa();
    void setKappa(double newKappa);
    void setS1(double newS1);
    void setPluckLoc(float pluckLoc);
    void setOutPosition(double newOutPos);
    double getN();
    double getStringLength();
    void setTension(double newTension);
    
    double getE();
    void setE(double newE);

    
    double stringLength = 0.5;
    double B = 0.00031;
    bool mousePressed, playOnce;
    double currentSample;
    int excitationSelection;
//    juce::AudioParameterFloat outputPositionParameter;
    AudioParameterFloat* outPutParam;

private:
    //==============================================================================
    
    
    double fs, f0, c, k, s0, s1, h, N, lambdaSq, muSq, pluckLoc, stringPluckRatio, kappa;


    double width, excitationRange, outPos;
     std::vector<double> u, uPrev, uNext;
        double sampleRate = 44100;
        int expectedSamplesPerBlock = 0;
        juce::Random random;
    
    double damp, stiffness, tension, stringDiameter, stringRadius, p, A, Ebrass, Esteel, I;
    
    
    int noStrings;
    
//    AutoString string1, string2;
    
//    std::vector<double> stringCollection;
    
//    std::unique_ptr<DampedString> string1;
//    std::unique_ptr<DampedString> string2;
    
    SanturString santurString1;
    
    

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessor)
};
