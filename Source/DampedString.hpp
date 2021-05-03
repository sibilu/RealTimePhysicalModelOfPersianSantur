
#ifndef DampedString_hpp
#define DampedString_hpp

#include <JuceHeader.h>

//using namespace std;

class DampedString {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    DampedString();
    DampedString(double stringLength, double stringDiameter, double s0, double s1, double tension, double p, double A, double E, double I, double k);
    DampedString(NamedValueSet& parameters, double k);
    
    // Destructor
    ~DampedString();
    
    float processSample(float l, float outPos);
    void processScheme();
    void updateStates();
    void updateMass();

    void setPluckLoc(double pluckLoc);
    void setOutLoc(double outLoc);
    
    void setDamping(double s1);
    void setTension(double newTension, double detune);

    void updateCoefficientsBrass();
    void updateCoefficientsSteel();

    void exciteHann();
    void exciteTri();
    void exciteHammer();
    void excite(int exciteSelection);
    
    double getOutput(double outPos);
    
    std::vector<std::vector<double>> uStates;
    std::vector<double> u, uPrev, uNext;
    std::vector<double*> uPtr;
private:
    
    double c, k, s0, s1, h, N, lambdaSq, muSq, pluckLoc, outPos, stringPluckRatio, kappa, width;
    
    double damp, stiffness, tension, stringLength, p, A, E, I;;
    
    double startNode = 2;
    double endNode;
    
    double hammerMass;
    double hammerStiffness = 2;
    int hammerNonLinearStiffness = 2;
    double hammerDistance = 0.5;
    
    double A1, A2, A3, A4, A5, B1, B2, D;
    
};



#endif /* DampedString_hpp */
