
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

    void setFs(double Fs);
    
    

    void setPluckLoc(double pluckLoc);
    
    void setOutLoc(double outLoc);
    
    void setF0(double f0);
    
    void setDamping(double s1);
    void setE(double newE);
    void setTension(double newTension);
    
    void setN(double N);
    void setH(double h);
    void setLambdaSq(double newLambdaSq);
    void setMuSq(double newMuSq);
    
    void updateCoefficients();
    void updateCoefficients(double s1, double lambdaSq, double muSq);
    
    void setNodes(int startNode, int endNode);
    
    
    void exciteHann();
    void exciteTri();
    
    double getOutput(double outPos);
    
    std::vector<double> u, uPrev, uNext;
private:
    
    double fs, f0, c, k, s0, s1, h, N, lambdaSq, muSq, pluckLoc, outPos, stringPluckRatio, kappa, width;
    
    double damp, stiffness, tension, stringLength, stringDiameter, stringRadius, p, A, E, I;;
    
    double startNode = 2;
    double endNode;
    
};



#endif /* DampedString_hpp */
