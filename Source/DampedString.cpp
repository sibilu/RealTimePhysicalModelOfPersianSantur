
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
    
    uStates.reserve(3);
    
    for(int i = 0; i < 3; ++i) {
        uStates.push_back(std::vector<double>(N+1, 0));
    }
    
    uPtr.resize(3);
    
    for(int i = 0; i < 3; ++i) {
        uPtr[i] = &uStates[i][0];
    }

    stringPluckRatio = 0.5;                   // 0 - 1
    
    pluckLoc = truncatePositiveToUnsignedInt(stringPluckRatio*N);
    endNode = N-1;
    
    B1 = s0 * k;
    B2 = (2.0 * s1 * k) / (h * h);
  
    A1 = 2.0 - 2.0 * lambdaSq - 6.0 * muSq - 2.0 * B2; // u_l^n
    A2 = lambdaSq + 4.0 * muSq + B2;                   // u_{l+-1}^n
    A3 = -muSq;                                        // u_{l+-2}^n
    A4 = B1 - 1.0 + 2.0 * B2;                          // u_l^{n-1}
    A5 = -B2;                                          // u_{l+-1}^{n-1}
  
    D = 1.0 / (1.0 + s0 * k);                      // u_l^{n+1}
  
  // Divide by u_l^{n+1} term
    A1 *= D;
    A2 *= D;
    A3 *= D;
    A4 *= D;
    A5 *= D;
}

// Destructor
DampedString::~DampedString(){}

void DampedString::processScheme() {
    for (int l = startNode; l < N-1; ++l) {
        uPtr[0][l] = A1 * uPtr[1][l] + A2 * (uPtr[1][l + 1] + uPtr[1][l - 1]) + A3 * (uPtr[1][l + 2] + uPtr[1][l - 2])
                + A4 * uPtr[2][l] + A5 * (uPtr[2][l + 1] + uPtr[2][l - 1]);
    }
}

void DampedString::updateStates() {
    double* uTmp = uPtr[2];
    uPtr[2] = uPtr[1];
    uPtr[1] = uPtr[0];
    uPtr[0] = uTmp;
}

void DampedString::updateMass() {
    for(int l = startNode; l < N-1; ++l) {
        hammerMass;
    }
}

double DampedString::getOutput(double outPos) {
    return uPtr[0][static_cast<int>(round(N+1) * outPos)];
}

void DampedString::setPluckLoc(double pluckLoc) {
    this->pluckLoc = (round(N+1) * pluckLoc);
}

void DampedString::excite(int exciteSelection, double velocity) {

    width = 10;
    switch (exciteSelection) {
        case 1:
            for(int j = 0; j < width; ++j) {
                if(j <= ((width)/2) && j >= 1) {
                    uPtr[1][static_cast<int>(j+pluckLoc)] = velocity * ((2*j - 1)/(width));
                    uPtr[2][static_cast<int>(j+pluckLoc)] = velocity * ((2*j - 1)/(width));
                } else {
                    uPtr[1][static_cast<int>(j+pluckLoc)] = velocity * (2 - ((2*j - 1)/(width)));
                    uPtr[2][static_cast<int>(j+pluckLoc)] = velocity * (2 - ((2*j - 1)/(width)));
            }
        }; break;
        case 2:
            for (int j = 0; j < width; ++j) {
                uPtr[1][static_cast<int>(j+pluckLoc)];
                uPtr[2][static_cast<int>(j+pluckLoc)];
            }; break;
            
        default:
            break;
    }
}




