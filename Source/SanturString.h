/*
  ==============================================================================

    SanturString.h
    Created: 16 Apr 2021 11:43:43am
    Author:  Oddur Kristjansson

  ==============================================================================
*/

#pragma once

#include "DampedString.hpp"

class SanturString {
    
    public:
    SanturString();
    SanturString(double stringLength, double s0, double s1, double tension, double p, double A, double E, double I, double r, double k);
    
    ~SanturString();
    
    void setPluckLoc(double pluckLoc);
    void exciteHann();
    void exciteTri();
    void excite(int exciteSelection);
    void processScheme();
    void updateStates();
    double getOutput(double outPos);
    
    void setDamping(double newDamping);
    void setTension(double newTension, int detuneValue);
    void updateCoefficientsBrass();
    void updateCoefficientsSteel();

    double k;
    
    
    private:
    
    
    std::unique_ptr<DampedString> string1;
    std::unique_ptr<DampedString> string2;
    std::unique_ptr<DampedString> string3;
//    std::unique_ptr<DampedString> string4;
    
};
