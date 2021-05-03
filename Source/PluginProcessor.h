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
    
    
    void updateStringClassCoefficients();

    void setS1(double newS1);
    void setPluckLoc(float pluckLoc);
    void setOutPosition(double newOutPos);
    void setTension(double newTension);
    void setDetune(int detuneFactor);


    
    double stringLength = 0.5f;
    double B = 0.00031;
    bool mousePressed, playOnce;
    int excitationSelection;
    int fs;

private:
    //==============================================================================
    
    
    double c, k, s0, s1, h, N, lambdaSq, muSq, pluckLoc, stringPluckRatio, kappa;


    double width, outPos;
    
    double damp, stiffness, stringDiameter, stringRadius, p, A, Ebrass, Esteel, I;
    
    double pBrass, ABrass, IBrass, pSteel, ASteel, ISteel;
    
    // These tension values have to be declared for each string pointer individually at this point
    double aTension, bTension, cTension;
    int detuneValue;
 
   
   //   std::unique_ptr<SanturString[]> santurStrings(SanturString[16]);
    
    

    // Initialise the string pointers
    std::unique_ptr<SanturString> dSharpLow51;
    std::unique_ptr<SanturString> d62;
    std::unique_ptr<SanturString> fLow53;
    std::unique_ptr<SanturString> f65;
    std::unique_ptr<SanturString> gLow55;
    std::unique_ptr<SanturString> g67;
    std::unique_ptr<SanturString> aLow57;
    std::unique_ptr<SanturString> a69;
    std::unique_ptr<SanturString> aSharpLow58;
    std::unique_ptr<SanturString> aSharp70;
    std::unique_ptr<SanturString> cLow60;
    std::unique_ptr<SanturString> c72;
    std::unique_ptr<SanturString> dlow62;
    std::unique_ptr<SanturString> d74;
    std::unique_ptr<SanturString> dSharpLow63;
    std::unique_ptr<SanturString> dSharp75;
    std::unique_ptr<SanturString> fLow65;
    std::unique_ptr<SanturString> f77;
    

    
    bool playAbrass = false;
    bool playAsteel = false;
    bool playDBrassSharp = false;
   /*
    std::vector<double> stringTensions{2299.5109, 9063.3346, 3032.40978, 12734.7204,3931.66534, 15931.5895, 5036.77625, 19903.8497, 5999.000, 22239.9255, 7194.77901, 27757.4324, 9063.3346, 34635.6634, 10158.8033, 38690.168, 12734.7204, 48282.3454};
    
    std::vector<int> midiValues{51, 62, 53, 65, 55, 67, 57, 69, 58, 70, 60, 72, 62, 74, 63, 75, 65, 77};
   */
    
    
    std::vector<double> stringTensions{7194.22391, 8079.31626, 9063.3346, 10158.1608, 11376.9046, 12734.0107, 14246.8646, 15931.5895, 17809.006, 19903.8497, 22239.9255, 24847.1043, 27758.4493, 31006.2128, 34634.5335, 38690.168, 43219.7992, 48282.3454};
    
//    std::vector<double> stringLengths{0.3, 0.34, 0.33, 0.40, 0.36, 0.45, 0.39, 0.50, 0.42, 0.54, 0.45, 0.59, 0.48, 0.64, 0.50, 0.69, 0.53, 0.73};
    std::vector<double> stringLengths{0.73, 0.53, 0.69, 0.50, 0.64, 0.48, 0.59, 0.45, 0.54, 0.42, 0.50, 0.39, 0.45, 0.36, 0.40, 0.33, 0.34, 0.3};
    
    std::vector<double> rValues, aValues, iValues;
    
     std::vector<int> midiValues{48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65};
    std::vector<bool> playNote{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    
    double stringOut1, stringOut2, stringOut3,stringOut4, stringOut5, stringOut6, stringOut7,stringOut8, stringOut9, stringOut10, mainOut;
    



    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SanturTestAudioProcessor)
};
