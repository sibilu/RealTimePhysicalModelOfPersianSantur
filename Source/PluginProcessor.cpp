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

    aBrassTension = 17311.f;
    aSteelTension = 34622.f;
    
    dBrassSharpTension = 2817.f;
    
    Ebrass = 113500000000;
    Esteel = 180000000000;
    pBrass = 8600;
    pSteel = 7700;
    
    double rBrass = (pow(4,0.25)*pow(B,0.25)*pow(aBrassTension,0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
    
    double rSteel = (pow(4,0.25)*pow(B,0.25)*pow(aSteelTension,0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Esteel,0.25));
    
    ABrass = double_Pi * (rBrass * rBrass);
    ASteel = double_Pi * (rSteel * rSteel);
    
    IBrass = double_Pi * rBrass * rBrass * rBrass * rBrass * 0.25;
    ISteel = double_Pi * rSteel * rSteel * rSteel * rSteel * 0.25;
    
    s0 = 1.2f;
    s1 = 0.00015f;
    
    k = stringLength / sampleRate;              // Time-step
    
    // Initialise the string pointers with appropriate values
    aBrass = std::make_unique<SanturString>(stringLength, s0, s1, aBrassTension, pBrass, ABrass, Ebrass, IBrass, rBrass, k);
    aSteel = std::make_unique<SanturString>(stringLength, s0, s1, aSteelTension, pSteel, ASteel, Esteel, ISteel, rSteel, k);
    
        
    DBG("sample rate:");
    DBG(sampleRate);

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
    
    double stringOut1, stringOut2, out;
    
    
    for (const auto metadata : midiMessages) {
        auto message = metadata.getMessage();
        
        if(message.isNoteOn() && message.getNoteNumber() == 51) {
            playAbrass = true;

        } else if (message.isNoteOn() && message.getNoteNumber() == 52){
            playAsteel = true;
        } if(message.isNoteOff()) {
            playOnce = false;
            playAbrass = false;
            playAsteel = false;
        }
    }

    
    if ((mousePressed == true && playOnce == true) || playAbrass){
//        DBG("aSteelTension");
//        DBG(aSteelTension);
            if(excitationSelection == 1) {
                aBrass->setPluckLoc(pluckLoc);
//                aSteel->setPluckLoc(pluckLoc);
                
                aBrass->exciteHann();
//                aSteel->exciteHann();

            }
            else if(excitationSelection == 2) {
                aBrass->setPluckLoc(pluckLoc);
//                aSteel->setPluckLoc(pluckLoc);
                
                aBrass->exciteTri();
//                aSteel->exciteTri();

                }
            playOnce = false;
        }
    
        if ((mousePressed == true && playOnce == true) || playAsteel){
//            DBG("aSteelTension");
//            DBG(aSteelTension);
                if(excitationSelection == 1) {
//                    aBrass->setPluckLoc(pluckLoc);
                    aSteel->setPluckLoc(pluckLoc);
                    
//                    aBrass->exciteHann();
                    aSteel->exciteHann();

                }
                else if(excitationSelection == 2) {
//                    aBrass->setPluckLoc(pluckLoc);
                    aSteel->setPluckLoc(pluckLoc);
                    
//                    aBrass->exciteTri();
                    aSteel->exciteTri();

                    }
                playOnce = false;
            }
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


        // ..do something to the data...
        float* const channelData1 = buffer.getWritePointer(0);
        float* const channelData2 = buffer.getWritePointer(1);
            for (int i = 0; i < buffer.getNumSamples(); ++i) {
                aBrass->processScheme();
                aBrass->updateStates();

                aSteel->processScheme();
                aSteel->updateStates();

                stringOut1 = aBrass->getOutput(outPos);
                stringOut2 = aSteel->getOutput(outPos);
                
                out = (stringOut1 + stringOut2) * 0.5;

                channelData1[i] = limit(out, -1.f, 1.f);
                channelData2[i] = limit(out, -1.f, 1.f);
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

    aBrass->setDamping(s1);
    aSteel->setDamping(s1);

    aBrass->setTension(aBrassTension);
    aSteel->setTension(aSteelTension);

    aBrass->updateCoefficientsBrass();
    aSteel->updateCoefficientsSteel();

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
