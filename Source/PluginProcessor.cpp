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
    
    Ebrass = 113500000000;
    Esteel = 180000000000;
    pBrass = 8600;
    pSteel = 7700;
    
    double rBrass = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[0],0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
    
    double rSteel = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[0],0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Esteel,0.25));
    
    ABrass = double_Pi * (rBrass * rBrass);
    ASteel = double_Pi * (rSteel * rSteel);
    
    IBrass = double_Pi * rBrass * rBrass * rBrass * rBrass * 0.25;
    ISteel = double_Pi * rSteel * rSteel * rSteel * rSteel * 0.25;
    
    s0 = 1.2f;
    s1 = 0.00030f;
    
    fs = getSampleRate();
//    k = stringLength / sampleRate;              // Time-step
    
    // Initialise the string pointers with appropriate values
    dSharpLow51 = std::make_unique<SanturString>(stringLength, s0, s1, stringTensions[0], pBrass, ABrass, Ebrass, IBrass, rBrass, fs);
    
    d62 = std::make_unique<SanturString>(stringLength, s0, s1, stringTensions[1], pBrass, ABrass, Ebrass, IBrass, rBrass, fs);
    
    fLow53 = std::make_unique<SanturString>(stringLength, s0, s1, stringTensions[2], pBrass, ABrass, Ebrass, IBrass, rBrass, fs);

//    aSteel = std::make_unique<SanturString>(stringLength, s0, s1, aSteelTension, pSteel, ASteel, Esteel, ISteel, rSteel, k);
    
   
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
            for (int n = 0; n < 3; n++){
                if(message.getNoteNumber() == midiValues[n]) {
                        playNote[n] = true;
                }
            }
        }
    }

    if (playNote[0]) {
        dSharpLow51->setPluckLoc(pluckLoc);
        dSharpLow51->exciteHann();
        playNote[0]=false;
    } else if (playNote[1]) {
        d62->setPluckLoc(pluckLoc);
        d62->exciteHann();
        playNote[1]=false;
    } else if (playNote[2]) {
        fLow53->setPluckLoc(pluckLoc);
        fLow53->exciteHann();
        playNote[2]=false;
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
                
                stringOut1 = dSharpLow51->getOutput(outPos);
                stringOut2 = d62->getOutput(outPos);
                stringOut3 = fLow53->getOutput(outPos);

                mainOut = (stringOut1 + stringOut2 + stringOut3) * 0.33;

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
        
    dSharpLow51->setTension(stringTensions[0]);
    d62->setTension(stringTensions[1]);
    fLow53->setTension(stringTensions[2]);

    dSharpLow51->updateCoefficientsBrass();
    d62->updateCoefficientsBrass();
    fLow53->updateCoefficientsBrass();

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
