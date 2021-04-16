/*
  ==============================================================================

    SanturString.cpp
    Created: 16 Apr 2021 11:43:43am
    Author:  Oddur Kristjansson

  ==============================================================================
*/

#include "SanturString.h"

SanturString::SanturString(){}

SanturString::SanturString(double stringLength, double s0, double s1, double tension, double p, double A, double E, double I, double r, double k){
    
    NamedValueSet parameters;
    
    parameters.set("stringLength", stringLength);
    parameters.set("tension", tension);
    parameters.set("p", p);
    parameters.set("A", double_Pi * (r*r));
    parameters.set("E", E);
    parameters.set("I", double_Pi * r * r * r * r * 0.25);
    parameters.set("s0", s0);                               // Frequency-independent damping
    parameters.set("s1",  s1);
    
    string1 = std::make_unique<DampedString>(parameters, k);
    string2 = std::make_unique<DampedString>(parameters, k);
    string3 = std::make_unique<DampedString>(parameters, k);
    string4 = std::make_unique<DampedString>(parameters, k);
    
    string1.get();
    string2.get();
    string3.get();
    string4.get();
    
}

void SanturString::getString() {
//        string1.get();
//        string2.get();
//        string3.get();
//        string4.get();
}

void SanturString::setPluckLoc(double pluckLoc) {
    string1->setPluckLoc(pluckLoc);
    string2->setPluckLoc(pluckLoc);
    string3->setPluckLoc(pluckLoc);
    string4->setPluckLoc(pluckLoc);
}
void SanturString::exciteHann() {
    string1->exciteHann();
    string2->exciteHann();
    string3->exciteHann();
    string4->exciteHann();
    
}
void SanturString::exciteTri() {
    string1->exciteTri();
    string2->exciteTri();
    string3->exciteTri();
    string4->exciteTri();
    
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
