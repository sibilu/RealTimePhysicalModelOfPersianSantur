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
    parameters2.set("tension", tension - tension/50);
    parameters2.set("p", p);
    parameters2.set("A", double_Pi * (r*r));
    parameters2.set("E", E);
    parameters2.set("I", double_Pi * r * r * r * r * 0.25);
    parameters2.set("s0", s0);                               // Frequency-independent damping
    parameters2.set("s1",  s1);
    
    parameters3.set("stringLength", stringLength);
    parameters3.set("tension", tension + tension/99);
    parameters3.set("p", p);
    parameters3.set("A", double_Pi * (r*r));
    parameters3.set("E", E);
    parameters3.set("I", double_Pi * r * r * r * r * 0.25);
    parameters3.set("s0", s0);                               // Frequency-independent damping
    parameters3.set("s1",  s1);
   
    parameters4.set("stringLength", stringLength);
    parameters4.set("tension", tension - tension/98);
    parameters4.set("p", p);
    parameters4.set("A", double_Pi * (r*r));
    parameters4.set("E", E);
    parameters4.set("I", double_Pi * r * r * r * r * 0.25);
    parameters4.set("s0", s0);                               // Frequency-independent damping
    parameters4.set("s1",  s1);
    
    k = stringLength / sampleRate;              // Time-step
    string1 = std::make_unique<DampedString>(parameters, k);
    string2 = std::make_unique<DampedString>(parameters2, k);
    string3 = std::make_unique<DampedString>(parameters3, k);
    string4 = std::make_unique<DampedString>(parameters4, k);
    
    string1.get();
    string2.get();
    string3.get();
    string4.get();
    
}

SanturString::~SanturString(){
    
}


void SanturString::setPluckLoc(double pluckLoc) {
    string1->setPluckLoc(pluckLoc);
    string2->setPluckLoc(pluckLoc);
    string3->setPluckLoc(pluckLoc);
    string4->setPluckLoc(pluckLoc);
}


void SanturString::excite(int exciteSelection, double velocity) {
    string1->excite(exciteSelection, velocity);
    string2->excite(exciteSelection, velocity);
    string3->excite(exciteSelection, velocity);
    string4->excite(exciteSelection, velocity);
}
void SanturString::processScheme() {
    string1->processScheme();
    string2->processScheme();
    string3->processScheme();
    string4->processScheme();
    
}
void SanturString::updateStates() {
    string1->updateStates();
    string2->updateStates();
    string3->updateStates();
    string4->updateStates();
}

double SanturString::getOutput(double outPos) {
    double out;
    double out1, out2, out3, out4;
    
    out1 = string1->getOutput(outPos);
    out2 = string2->getOutput(outPos);
    out3 = string3->getOutput(outPos);
    out4 = string4->getOutput(outPos);
    
    return out = (out1 + out2 + out3 + out4) * 0.25;
}

