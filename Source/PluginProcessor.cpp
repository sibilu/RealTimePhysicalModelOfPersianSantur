/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SanturTestAudioProcessor::SanturTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

SanturTestAudioProcessor::~SanturTestAudioProcessor()
{
}

//==============================================================================
const juce::String SanturTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SanturTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SanturTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SanturTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SanturTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SanturTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SanturTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SanturTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SanturTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void SanturTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SanturTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..


   // dBrassSharpTension = 2817.f;
    rValues.resize(18);
    aValues.resize(18);
    iValues.resize(18);
    
    Ebrass = 113500000000;
    Esteel = 180000000000;
    pBrass = 8600;
    pSteel = 7700;
    
    for(int i = 0; i < 18; ++i) {
        rValues[i] = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[i],0.25)*pow(stringLengths[i],0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
        aValues[i] = double_Pi * (rValues[i] * rValues[i]);
        iValues[i] = double_Pi * rValues[i] * rValues[i] * rValues[i] * rValues[i] * 0.25;
    }
    
//    double rBrass = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[0],0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
//    
//    double rSteel = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[0],0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Esteel,0.25));
//    
//    ABrass = double_Pi * (rBrass * rBrass);
//    ASteel = double_Pi * (rSteel * rSteel);
//    
//    IBrass = double_Pi * rBrass * rBrass * rBrass * rBrass * 0.25;
//    ISteel = double_Pi * rSteel * rSteel * rSteel * rSteel * 0.25;
    
    s0 = 1.3f;
    s1 = 0.00060f;
    
    fs = getSampleRate();
//    k = stringLength / sampleRate;              // Time-step
    /*
    for (int i = 0; i < 16; i++){
        santurStrings[i] = std::make_unique<SanturString>(stringLength, s0, s1, stringTensions[i], pBrass, ABrass, Ebrass, IBrass, rBrass, fs);

    }
    */
    // Initialise the string pointers with appropriate values
    
    
    dSharpLow51 = std::make_unique<SanturString>(stringLengths[0], s0, s1, stringTensions[0], pBrass, aValues[0], Ebrass, iValues[0], rValues[0], fs);
    
    d62 = std::make_unique<SanturString>(stringLengths[1], s0, s1, stringTensions[1], pBrass, aValues[1], Ebrass, iValues[1], rValues[1], fs);
    
    fLow53 = std::make_unique<SanturString>(stringLengths[2], s0, s1, stringTensions[2], pBrass, aValues[2], Ebrass, iValues[2], rValues[2], fs);

    f65 = std::make_unique<SanturString>(stringLengths[3], s0, s1, stringTensions[3], pBrass, aValues[3], Ebrass, iValues[3], rValues[3], fs);
    
    gLow55 = std::make_unique<SanturString>(stringLengths[4], s0, s1, stringTensions[4], pBrass, aValues[4], Ebrass, iValues[4], rValues[4], fs);

    g67 = std::make_unique<SanturString>(stringLengths[5], s0, s1, stringTensions[5], pBrass, aValues[5], Ebrass, iValues[5], rValues[5], fs);

    aLow57 = std::make_unique<SanturString>(stringLengths[6], s0, s1, stringTensions[6], pBrass, aValues[6], Ebrass, iValues[6], rValues[6], fs);

    a69 = std::make_unique<SanturString>(stringLengths[7], s0, s1, stringTensions[7], pBrass, aValues[7], Ebrass, iValues[7], rValues[7], fs);
    
    aSharpLow58 = std::make_unique<SanturString>(stringLengths[8], s0, s1, stringTensions[8], pBrass, aValues[8], Ebrass, iValues[8], rValues[8], fs);

    aSharp70 = std::make_unique<SanturString>(stringLengths[9], s0, s1, stringTensions[9], pBrass, aValues[9], Ebrass, iValues[9], rValues[9], fs);
    
    dSharpLow51.get();
    d62.get();
    fLow53.get();
    f65.get();
    gLow55.get();
    g67.get();
    aLow57.get();
    a69.get();
    aSharpLow58.get();
    aSharp70.get();
    
   
    DBG("sample rate:");
    DBG(fs);

}

void SanturTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SanturTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SanturTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    MidiBuffer processMidi;
    
    
    
    
    for (const auto metadata : midiMessages) {
        auto message = metadata.getMessage();
        
        if(message.isNoteOn()) {
            for (int n = 0; n < 10; n++){
                if(message.getNoteNumber() == midiValues[n]) {
                        playNote[n] = true;
                }
            }
        }
    }

    if (playNote[0]) {
        dSharpLow51->setPluckLoc(pluckLoc);
        dSharpLow51->exciteTri();
        playNote[0]=false;
    } else if (playNote[1]) {
        d62->setPluckLoc(pluckLoc);
        d62->exciteTri();
        playNote[1]=false;
    } else if (playNote[2]) {
        fLow53->setPluckLoc(pluckLoc);
        fLow53->exciteTri();
        playNote[2]=false;
    } else if (playNote[3]) {
        f65->setPluckLoc(pluckLoc);
        f65->exciteTri();
        playNote[3]=false;
    }else if (playNote[4]) {
        gLow55->setPluckLoc(pluckLoc);
        gLow55->exciteTri();
        playNote[4]=false;
    }else if (playNote[5]) {
        g67->setPluckLoc(pluckLoc);
        g67->exciteTri();
        playNote[5]=false;
    }else if (playNote[6]) {
        aLow57->setPluckLoc(pluckLoc);
        aLow57->exciteTri();
        playNote[6]=false;
    } else if (playNote[7]) {
        a69->setPluckLoc(pluckLoc);
        a69->exciteTri();
        playNote[7]=false;
    }else if (playNote[8]) {
        aSharpLow58->setPluckLoc(pluckLoc);
        aSharpLow58->exciteTri();
        playNote[8]=false;
    }else if (playNote[9]) {
        aSharp70->setPluckLoc(pluckLoc);
        aSharp70->exciteTri();
        playNote[9]=false;
    }
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


        // ..do something to the data...
        float* const channelData1 = buffer.getWritePointer(0);
        float* const channelData2 = buffer.getWritePointer(1);
            for (int i = 0; i < buffer.getNumSamples(); ++i) {
                
                dSharpLow51->processScheme();
                dSharpLow51->updateStates();

                d62->processScheme();
                d62->updateStates();

                fLow53->processScheme();
                fLow53->updateStates();
                
                f65->processScheme();
                f65->updateStates();
                
                gLow55->processScheme();
                gLow55->updateStates();
               
                g67->processScheme();
                g67->updateStates();
                
                aLow57->processScheme();
                aLow57->updateStates();
                               
                a69->processScheme();
                a69->updateStates();
                               
                aSharpLow58->processScheme();
                aSharpLow58->updateStates();
                              
                aSharp70->processScheme();
                aSharp70->updateStates();
                
                stringOut1 = dSharpLow51->getOutput(outPos);
                stringOut2 = d62->getOutput(outPos);
                stringOut3 = fLow53->getOutput(outPos);
                stringOut4 = f65->getOutput(outPos);
                stringOut5 = gLow55->getOutput(outPos);
                stringOut6 = g67->getOutput(outPos);
                stringOut7 = aLow57->getOutput(outPos);
                stringOut8 = a69->getOutput(outPos);
                stringOut9 = aSharpLow58->getOutput(outPos);
                stringOut10 = aSharp70->getOutput(outPos);
                mainOut = (stringOut1 + stringOut2 + stringOut3 + stringOut4 + stringOut5 + stringOut6 + stringOut7 + stringOut8 + stringOut9 + stringOut10) * 0.16f;

                channelData1[i] = limit(mainOut, -1.f, 1.f);
                channelData2[i] = limit(mainOut, -1.f, 1.f);
            }
}

//==============================================================================
bool SanturTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SanturTestAudioProcessor::createEditor()
{
    return new SanturTestAudioProcessorEditor (*this);
}

//==============================================================================
void SanturTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SanturTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void SanturTestAudioProcessor::updateStringClassCoefficients() {

    dSharpLow51->setDamping(s1);
    d62->setDamping(s1);
    
    fLow53->setDamping(s1);
    f65->setDamping(s1);
    
    gLow55->setDamping(s1);
    g67->setDamping(s1);
    
    aLow57->setDamping(s1);
    a69->setDamping(s1);
      
    aSharpLow58->setDamping(s1);
    aSharp70->setDamping(s1);
//-------------------------------------------------
    dSharpLow51->setTension(stringTensions[0], detuneValue);
    d62->setTension(stringTensions[1], detuneValue);
    
    fLow53->setTension(stringTensions[2], detuneValue);
    f65->setTension(stringTensions[3], detuneValue);
    
    gLow55->setTension(stringTensions[4], detuneValue);
    g67->setTension(stringTensions[5], detuneValue);
    
    aLow57->setTension(stringTensions[6], detuneValue);
      a69->setTension(stringTensions[7], detuneValue);
      
      aSharpLow58->setTension(stringTensions[8], detuneValue);
      aSharp70->setTension(stringTensions[9], detuneValue);
      
    
//-------------------------------------------------

    
    dSharpLow51->updateCoefficientsBrass();
    d62->updateCoefficientsBrass();
    
    fLow53->updateCoefficientsBrass();
    f65->updateCoefficientsBrass();
    
      gLow55->updateCoefficientsBrass();
      g67->updateCoefficientsBrass();

    
      aLow57->updateCoefficientsBrass();
      a69->updateCoefficientsBrass();
      
        aSharpLow58->updateCoefficientsBrass();
        aSharp70->updateCoefficientsBrass();
}

// I think in the future, we might not need to control this, unless we want the user to control the damping
void SanturTestAudioProcessor::setS1(double newS1) {
    this-> s1 = newS1;
}

void SanturTestAudioProcessor::setPluckLoc(float pluckLoc) {
    this-> pluckLoc = pluckLoc;
}

void SanturTestAudioProcessor::setOutPosition(double newOutPos) {
    this-> outPos = newOutPos;
}

void SanturTestAudioProcessor::setDetune(int detuneValue) {
    this-> detuneValue = detuneValue;
}


// When we have 'hardcoded' strings, this function will not be needed
// At the moment it only affects one string at a time and can be useful to find the correct tension value for pitch/tuning
void SanturTestAudioProcessor::setTension(double newTension) {
//    this-> aBrassTension = newTension;
}
float SanturTestAudioProcessor::limit(float input, float min, float max) {
    if(input > max)
        return max;
    else if (input < min)
        return min;
        
        return input;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SanturTestAudioProcessor();
}
