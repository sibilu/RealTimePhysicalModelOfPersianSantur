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
    addParameter(outPutParam = new juce::AudioParameterFloat ("outputParam",
                                                              "Output",
                                                              0.0f,
                                                              1.0f,
                                                              0.0f));
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
    NamedValueSet parameters, parameters2;

//    double r = 0.000254/2;
    tension = 405.f;
    Ebrass = 113500000000;
    Esteel = 180000000000;
    p = 8600;
    double rBrass = (pow(4,0.25)*pow(B,0.25)*pow(tension,0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Ebrass,0.25));
    
    double rSteel = (pow(4,0.25)*pow(B,0.25)*pow(tension,0.25)*pow(stringLength,0.5))/(pow(double_Pi,0.25)*pow(Esteel,0.25));
    A = double_Pi * (rBrass*rBrass);
    I = double_Pi * rBrass * rBrass * rBrass * rBrass * 0.25;
    s0 = 1.f;
    s1 = 0.01;
    
    
    parameters.set("stringLength", stringLength);
//    parameters.set("stringDiameter", 0.000254);
    parameters.set("tension", tension);
    parameters.set("p", 8600);
    

    DBG("rSteel");
    DBG(rSteel);


                      
    
    parameters.set("A", double_Pi * (rBrass*rBrass));
    parameters.set("E", Ebrass);
    parameters.set("I", double_Pi * rBrass * rBrass * rBrass * rBrass * 0.25);
    
    parameters.set("s0", 1.f);                               // Frequency-independent damping
    parameters.set("s1",  0.01);                             // Frequency-dependent damping
    
    k = stringLength / sampleRate;              // Time-step
    
    santurString1 = SanturString(stringLength, s0, s1, tension, p, A, Ebrass, I, rBrass, k);
    
    parameters2.set("stringLength", stringLength);
    parameters2.set("stringDiameter", 0.000254);
    parameters2.set("tension", 105.f);
    parameters2.set("p", 7850);
    parameters2.set("A", double_Pi * (rSteel*rSteel));
    parameters2.set("E", Esteel);
    parameters2.set("I", double_Pi * rSteel * rSteel * rSteel * rSteel * 0.25);
    
    parameters2.set("s0", 1.f);                               // Frequency-independent damping
    parameters2.set("s1",  0.01);                             // Frequency-dependent damping
    
    k = stringLength / sampleRate;              // Time-step
//    string1 = std::make_unique<DampedString>(parameters, k);
//    string2 = std::make_unique<DampedString>(parameters2, k);

    
//    string1.get();
//    string2.get();
    
//    santurString1.getString();


        
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
        
        if(message.isNoteOn()) {
            mousePressed = true;
            playOnce = true;
        } if(message.isNoteOff()) {
            mousePressed = false;
        }
    }

    
    if (mousePressed == true && playOnce == true){
            if(excitationSelection == 1) {
                santurString1.setPluckLoc(pluckLoc);
//                string1->setPluckLoc(pluckLoc);
                santurString1.exciteHann();
//                string1->exciteHann();
                
//                string2->setPluckLoc(pluckLoc);
//                string2->exciteHann();
            }
            else if(excitationSelection == 2) {
                santurString1.setPluckLoc(pluckLoc);
//                string1->setPluckLoc(pluckLoc);
                santurString1.exciteTri();
//                string1->exciteTri();
                
//                string2->setPluckLoc(pluckLoc);
//                string2->exciteTri();
                }
            playOnce = false;
        }
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


        // ..do something to the data...
        float* const channelData1 = buffer.getWritePointer(0);
        float* const channelData2 = buffer.getWritePointer(1);
            for (int i = 0; i < buffer.getNumSamples(); ++i) {
                santurString1.processScheme();
//                string1->processScheme();
                santurString1.updateStates();
//                string1->updateStates();
                
//                string2->processScheme();
//                string2->updateStates();
                
//                stringOut1 = string1->getOutput(outPos);
//                stringOut2 = string2->getOutput(outPos);
                
//                out = stringOut1 + stringOut2;
                out = santurString1.getOutput(outPos);
//                out = stringOut1;

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

void SanturTestAudioProcessor::updateCoefficients() {
    c = sqrt(tension/(p*A));
    kappa = sqrt((Ebrass*I)/p*A);
    h = sqrt((c * c * k * k + 4.0 * s1 * k
             + sqrt (pow (c * c * k * k + 4.0 * s1 * k, 2.0)
                    + 16.0 * kappa * kappa * k * k)) * 0.5);
    N = truncatePositiveToUnsignedInt(stringLength / h);
    h = stringLength / N;
    lambdaSq = (c*c*k*k)/(h*h);
    muSq = (kappa*kappa*k*k)/pow(h,4);
}

void SanturTestAudioProcessor::updateStringClassCoefficients() {
    string1->setE(Ebrass);
    string2->setE(Esteel);
    
    string1->setDamping(s1);
    string2->setDamping(s1);
    
    string1->setTension(tension);
    string2->setTension(tension);
    
    string1->updateCoefficients();
    string2->updateCoefficients();
}


double SanturTestAudioProcessor::getE(){
    return this-> Ebrass;
}

void SanturTestAudioProcessor::setE(double newE) {
    this-> Ebrass = newE;
}

double SanturTestAudioProcessor::getKappa() {
    return this-> kappa;
}
void SanturTestAudioProcessor::setKappa(double newKappa) {
    this-> kappa = newKappa;
}

void SanturTestAudioProcessor::setS1(double newS1) {
    this-> s1 = newS1;
}

void SanturTestAudioProcessor::setPluckLoc(float pluckLoc) {
    this-> pluckLoc = pluckLoc;
}

void SanturTestAudioProcessor::setOutPosition(double newOutPos) {
    this-> outPos = newOutPos;
}

double SanturTestAudioProcessor::getN() {
    return this-> N;
}

double SanturTestAudioProcessor::getStringLength() {
    return this-> stringLength;
}

void SanturTestAudioProcessor::setTension(double newTension) {
    this-> tension = newTension;
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
