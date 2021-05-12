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
    
//    santurStrings.reserve(18);
//    stringOuts.resize(18);
  

    DBG("prepareToPlay Called");
    
    rValues.resize(18);
    aValues.resize(18);
    iValues.resize(18);

    
    for(int i = 0; i < 18; ++i) {
        if(i % 2 == 0) {
            rValues[i] = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[i],0.25)*pow(stringLengths[i],0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
            aValues[i] = double_Pi * (rValues[i] * rValues[i]);
            iValues[i] = double_Pi * rValues[i] * rValues[i] * rValues[i] * rValues[i] * 0.25;
        } else {
            rValues[i] = (pow(4,0.25)*pow(B,0.25)*pow(stringTensions[i],0.25)*pow(stringLengths[i],0.5))/(pow(double_Pi,0.25)*pow(Esteel,0.25));
            aValues[i] = double_Pi * (rValues[i] * rValues[i]);
            iValues[i] = double_Pi * rValues[i] * rValues[i] * rValues[i] * rValues[i] * 0.25;
        }
    }
    
    fs = getSampleRate();
    
    // Initialise the string pointers with appropriate values
    string1 = std::make_unique<SanturString>(stringLengths[0], s0, s1, stringTensions[0], pBrass, aValues[0], Ebrass, iValues[0], rValues[0], fs);

    string2 = std::make_unique<SanturString>(stringLengths[1], s0, s1, stringTensions[1], pSteel, aValues[1], Esteel, iValues[1], rValues[1], fs);

    string3 = std::make_unique<SanturString>(stringLengths[2], s0, s1, stringTensions[2], pBrass, aValues[2], Ebrass, iValues[2], rValues[2], fs);

    string4 = std::make_unique<SanturString>(stringLengths[3], s0, s1, stringTensions[3], pSteel, aValues[3], Esteel, iValues[3], rValues[3], fs);

    string5 = std::make_unique<SanturString>(stringLengths[4], s0, s1, stringTensions[4], pBrass, aValues[4], Ebrass, iValues[4], rValues[4], fs);

    string6 = std::make_unique<SanturString>(stringLengths[5], s0, s1, stringTensions[5], pSteel, aValues[5], Esteel, iValues[5], rValues[5], fs);

    string7 = std::make_unique<SanturString>(stringLengths[6], s0, s1, stringTensions[6], pBrass, aValues[6], Ebrass, iValues[6], rValues[6], fs);

    string8 = std::make_unique<SanturString>(stringLengths[7], s0, s1, stringTensions[7], pSteel, aValues[7], Esteel, iValues[7], rValues[7], fs);

    string9 = std::make_unique<SanturString>(stringLengths[8], s0, s1, stringTensions[8], pBrass, aValues[8], Ebrass, iValues[8], rValues[8], fs);

    string10 = std::make_unique<SanturString>(stringLengths[9], s0, s1, stringTensions[9], pSteel, aValues[9], Esteel, iValues[9], rValues[9], fs);

    string11  = std::make_unique<SanturString>(stringLengths[10], s0, s1, stringTensions[10], pBrass, aValues[10], Ebrass, iValues[10], rValues[10], fs);

    string12  = std::make_unique<SanturString>(stringLengths[11], s0, s1, stringTensions[11], pSteel, aValues[11], Esteel, iValues[11], rValues[11], fs);

    string13  = std::make_unique<SanturString>(stringLengths[12], s0, s1, stringTensions[12], pBrass, aValues[12], Ebrass, iValues[12], rValues[12], fs);

    string14  = std::make_unique<SanturString>(stringLengths[13], s0, s1, stringTensions[13], pSteel, aValues[13], Esteel, iValues[13], rValues[13], fs);

    string15  = std::make_unique<SanturString>(stringLengths[14], s0, s1, stringTensions[14], pBrass, aValues[14], Ebrass, iValues[14], rValues[14], fs);

    string16  = std::make_unique<SanturString>(stringLengths[15], s0, s1, stringTensions[15], pSteel, aValues[15], Esteel, iValues[15], rValues[15], fs);

    string17 = std::make_unique<SanturString>(stringLengths[16], s0, s1, stringTensions[16], pBrass, aValues[16], Ebrass, iValues[16], rValues[16], fs);

    string18 = std::make_unique<SanturString>(stringLengths[17], s0, s1, stringTensions[17], pSteel, aValues[17], Esteel, iValues[17], rValues[17], fs);
    
    string1.get();
    string2.get();
    string3.get();
    string4.get();
    string5.get();
    string6.get();
    string7.get();
    string8.get();
    string9.get();
    string10.get();
    string11.get();
    string12.get();
    string13.get();
    string14.get();
    string15.get();
    string16.get();
    string17.get();
    string18.get();
    
    santurStrings.clear();
    santurStrings.add(std::move(string1));
    santurStrings.add(std::move(string2));
    santurStrings.add(std::move(string3));
    santurStrings.add(std::move(string4));
    santurStrings.add(std::move(string5));
    santurStrings.add(std::move(string6));
    santurStrings.add(std::move(string7));
    santurStrings.add(std::move(string8));
    santurStrings.add(std::move(string9));
    santurStrings.add(std::move(string10));
    santurStrings.add(std::move(string11));
    santurStrings.add(std::move(string12));
    santurStrings.add(std::move(string13));
    santurStrings.add(std::move(string14));
    santurStrings.add(std::move(string15));
    santurStrings.add(std::move(string16));
    santurStrings.add(std::move(string17));
    santurStrings.add(std::move(string18));
    DBG(santurStrings.size());
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
            for (int n = 0; n < 18; n++){
                if(message.getNoteNumber() == midiValues[n]) {
                    velocityFullRange = message.getVelocity();
                    velocityNormalized = (velocityFullRange/127);

                    vel[n] = velocityNormalized;
                    playNote[n] = true;
                }
            }
        }
    }
    
    checkActiveNotes();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    // ..do something to the data...
    float* const channelData1 = buffer.getWritePointer(0);
    float* const channelData2 = buffer.getWritePointer(1);
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        
        processAndUpdateStrings();
        
        mainOut = outputSound();
        
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
    
    for (int i = 0; i < 18; ++i) {
        santurStrings[i]->setDamping(s1);
    }

    
    //-------------------------------------------------
    for (int i = 0; i < 18; ++i) {
        santurStrings[i]->setTension(stringTensions[i]);
    }

    //-------------------------------------------------
    for (int i = 0; i < 18; ++i) {
        santurStrings[i]->updateCoefficients();
    }
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

//void SanturTestAudioProcessor::setDetune(int detuneValue) {
//    this-> detuneValue = detuneValue;
//}


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

void SanturTestAudioProcessor::checkActiveNotes() {
    
    for(int i = 0; i < 18; ++i) {
        if(playNote[i]) {
            santurStrings[i]->setPluckLoc(pluckLoc);
            santurStrings[i]->excite(excitationSelection, vel[i]);
            playNote[i] = false;
        }
    }
}

void SanturTestAudioProcessor::processAndUpdateStrings() {
    for(int i = 0; i < 18; ++i) {
        santurStrings[i]->processScheme();
        santurStrings[i]->updateStates();
    }
}

double SanturTestAudioProcessor::outputSound() {
    double out;
    stringOut0 = santurStrings[0]->getOutput(outPos);
    stringOut1 = santurStrings[1]->getOutput(outPos);
    stringOut2 = santurStrings[2]->getOutput(outPos);
    stringOut3 = santurStrings[3]->getOutput(outPos);
    stringOut4 = santurStrings[4]->getOutput(outPos);
    stringOut5 = santurStrings[5]->getOutput(outPos);
    stringOut6 = santurStrings[6]->getOutput(outPos);
    stringOut7 = santurStrings[7]->getOutput(outPos);
    stringOut8 = santurStrings[8]->getOutput(outPos);
    stringOut9 = santurStrings[9]->getOutput(outPos);
    stringOut10 = santurStrings[10]->getOutput(outPos);
    stringOut11 = santurStrings[11]->getOutput(outPos);
    stringOut12 = santurStrings[12]->getOutput(outPos);
    stringOut13 = santurStrings[13]->getOutput(outPos);
    stringOut14 = santurStrings[14]->getOutput(outPos);
    stringOut15 = santurStrings[15]->getOutput(outPos);
    stringOut16 = santurStrings[16]->getOutput(outPos);
    stringOut17 = santurStrings[17]->getOutput(outPos);
    
    
    out = (stringOut0 + stringOut1 + stringOut2 + stringOut3 + stringOut4 + stringOut5 + stringOut6 + stringOut7 + stringOut8 + stringOut9 + stringOut10 + stringOut11 + stringOut12 + stringOut13 + stringOut14 + stringOut15 + stringOut16 + stringOut17)*0.3;
    
    return out;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SanturTestAudioProcessor();
}
