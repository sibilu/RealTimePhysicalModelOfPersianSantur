
#include "DampedString.hpp"


DampedString::DampedString(){}

DampedString::DampedString(NamedValueSet& parameters, double k) :
stringLength (*parameters.getVarPointer ("stringLength")),
s0 (*parameters.getVarPointer ("s0")),
s1 (*parameters.getVarPointer ("s1")),
tension (*parameters.getVarPointer ("tension")),
p (*parameters.getVarPointer ("p")),
A (*parameters.getVarPointer ("A")),
E (*parameters.getVarPointer ("E")),
I (*parameters.getVarPointer ("I")),
k (k)
{
    c = sqrt(tension/(p*A));
    kappa = sqrt((E*I)/p*A);
    h = sqrt((c * c * k * k + 4.0 * s1 * k
                    + sqrt (pow (c * c * k * k + 4.0 * s1 * k, 2.0)
                            + 16.0 * kappa * kappa * k * k)) * 0.5);
        
    
    N = truncatePositiveToUnsignedInt(stringLength / h);                    // Number of gridpoints
    h = stringLength / N;                            // Recalculate gridspacing

    lambdaSq = (c*c*k*k)/(h*h);
    muSq = (kappa*kappa*k*k)/pow(h,4);
    
    u.resize(N+1);
    uPrev.resize(N+1);
    uNext.resize(N+1);
    
    stringPluckRatio = 0.5;                   // 0 - 1
    
    pluckLoc = truncatePositiveToUnsignedInt(stringPluckRatio*N);
    endNode = N-1;
}

// Destructor
DampedString::~DampedString(){
}

void DampedString::processScheme() {
    for (int l = startNode; l < N-1; ++l) {
        damp = (s0 * k * uPrev[l]) + (((2.0 * s1 * k)/(h*h) * (u[l+1] - 2.0 * u[l] + u[l-1] - uPrev[l+1] + 2.0 * uPrev[l] - uPrev[l-1])));
        stiffness = muSq * (u[l+2] - 4.0 * u[l+1] + 6.0 * u[l] - 4.0 * u[l-1] + u[l-2]);
            
        uNext[l] = 1.0/(1.0 + s0 * k) * (2.0 * u[l] - uPrev[l] + lambdaSq * (u[l-1] - 2.0 * u[l] + u[l+1])) - stiffness + damp;
            
        uNext[startNode - 2] = 0;
        uNext[startNode - 1] = 0;
        uNext[endNode + 1] = 0;
        uNext[endNode + 2] = 0;
        
    }
}

void DampedString::updateStates() {
    uPrev = u;
    u = uNext;
}

void DampedString::updateMass() {
    for(int l = startNode; l < N-1; ++l) {
        hammerMass;
    }
    
}

double DampedString::getOutput(double outPos) {
    return uNext[(round(N+1) * outPos)];
}

void DampedString::setPluckLoc(double pluckLoc) {
    this->pluckLoc = (round(N+1) * pluckLoc);
}

void DampedString::setOutLoc(double outLoc) {
    this->outPos = outLoc;
}

void DampedString::setDamping(double s1) {
    this->s1 = s1;
}

void DampedString::setTension(double newTension) {
    this->tension = newTension;
}


void DampedString::updateCoefficientsBrass() {
    c = sqrt(tension/(p*A));
    kappa = sqrt((E*I)/p*A);
    h = sqrt((c * c * k * k + 4.0 * s1 * k
             + sqrt (pow (c * c * k * k + 4.0 * s1 * k, 2.0)
                    + 16.0 * kappa * kappa * k * k)) * 0.5);
    N = truncatePositiveToUnsignedInt(stringLength / h);
    h = stringLength / N;
    lambdaSq = (c*c*k*k)/(h*h);
    muSq = (kappa*kappa*k*k)/pow(h,4);
}

void DampedString::updateCoefficientsSteel() {
    c = sqrt(tension/(p*A));
    kappa = sqrt((E*I)/p*A);
    h = sqrt((c * c * k * k + 4.0 * s1 * k
             + sqrt (pow (c * c * k * k + 4.0 * s1 * k, 2.0)
                    + 16.0 * kappa * kappa * k * k)) * 0.5);
    N = truncatePositiveToUnsignedInt(stringLength / h);
    h = stringLength / N;
    lambdaSq = (c*c*k*k)/(h*h);
    muSq = (kappa*kappa*k*k)/pow(h,4);
}

void DampedString::exciteHann() {
    width = 10;
    for (int j = 0; j < width; ++j) {
        double hann = 0.5 * (1 - cos(2*double_Pi*j/(width-1)));
        u[j+pluckLoc] = hann;
        uPrev[j+pluckLoc] = hann;
      }
}

void DampedString::exciteTri() {
    width = 10;
    for (int j = 0; j < width; ++j) {
        if(j <= width && j >= ((width+1)/2)) {
            u[j+pluckLoc] = 2 - ((2*j)/(width + 1));
            uPrev[j+pluckLoc] = 2 - ((2*j)/(width + 1));
            } else {
                u[j+pluckLoc] = (2*j)/(width+1);
                uPrev[j+pluckLoc] = (2*j)/(width+1);
            }
    }
}

void DampedString::exciteHammer() {
    width = 10;
    for (int j = 0; j < width; ++j) {
        u[j+pluckLoc];
        uPrev[j+pluckLoc];
    }
}



