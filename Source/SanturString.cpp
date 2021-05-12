/*
  ==============================================================================

    SanturString.cpp
    Created: 16 Apr 2021 11:43:43am
    Author:  Oddur Kristjansson

  ==============================================================================
*/

#include "SanturString.h"

SanturString::SanturString(){}

SanturString::SanturString(double stringLength, double s0, double s1, double tension, double p, double A, double E, double I, double r, double sampleRate){
    
    NamedValueSet parameters, parameters2, parameters3, parameters4;
    
    parameters.set("stringLength", stringLength);
    parameters.set("tension", tension);
    parameters.set("p", p);
    parameters.set("A", double_Pi * (r*r));
    parameters.set("E", E);
    parameters.set("I", double_Pi * r * r * r * r * 0.25);
    parameters.set("s0", s0);                               // Frequency-independent damping
    parameters.set("s1",  s1);
    
    parameters2.set("stringLength", stringLength);
    parameters2.set("tension", tension - 116);
    parameters2.set("p", p);
    parameters2.set("A", double_Pi * (r*r));
    parameters2.set("E", E);
    parameters2.set("I", double_Pi * r * r * r * r * 0.25);
    parameters2.set("s0", s0);                               // Frequency-independent damping
    parameters2.set("s1",  s1);
    
    parameters3.set("stringLength", stringLength);
    parameters3.set("tension", tension + 115);
    parameters3.set("p", p);
    parameters3.set("A", double_Pi * (r*r));
    parameters3.set("E", E);
    parameters3.set("I", double_Pi * r * r * r * r * 0.25);
    parameters3.set("s0", s0);                               // Frequency-independent damping
    parameters3.set("s1",  s1);
   
    
    k = stringLength / sampleRate;              // Time-step
    string1 = std::make_unique<DampedString>(parameters, k);
    string2 = std::make_unique<DampedString>(parameters2, k);
    string3 = std::make_unique<DampedString>(parameters3, k);
    
    string1.get();
    string2.get();
    string3.get();
    
}

SanturString::~SanturString(){
    
}


void SanturString::setPluckLoc(double pluckLoc) {
    string1->setPluckLoc(pluckLoc);
    string2->setPluckLoc(pluckLoc);
    string3->setPluckLoc(pluckLoc);
}


void SanturString::excite(int exciteSelection, double velocity) {
    string1->excite(exciteSelection, velocity);
    string2->excite(exciteSelection, velocity);
    string3->excite(exciteSelection, velocity);
}
void SanturString::processScheme() {
    string1->processScheme();
    string2->processScheme();
    string3->processScheme();
    
}
void SanturString::updateStates() {
    string1->updateStates();
    string2->updateStates();
    string3->updateStates();
}

double SanturString::getOutput(double outPos) {
    double out;
    double out1, out2, out3;
    
    out1 = string1->getOutput(outPos);
    out2 = string2->getOutput(outPos);
    out3 = string3->getOutput(outPos);
    
    return out = (out1 + out2 + out3) * 0.33;
}

void SanturString::setDamping(double s1) {
    string1->setDamping(s1);
    string2->setDamping(s1);
    string3->setDamping(s1);
}


void SanturString::setTension(double newTension, int detuneValue) {
    string1->setTension(newTension, 0);
    string2->setTension(newTension, -(350 * detuneValue));
    string3->setTension(newTension, (346 * detuneValue));
}

void SanturString::setTension(double newTension) {
    string1->setTension(newTension);
    string2->setTension(newTension - 350.f);
    string3->setTension(newTension + 346.f);
}

void SanturString::updateCoefficients() {
    string1->updateCoefficients();
    string2->updateCoefficients();
    string3->updateCoefficients();
}

