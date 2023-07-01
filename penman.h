
#ifndef PENMAN_H
#define PENMAN_H

typedef struct ETP {
    float E0;
    float ES0;
    float ET0;
    float ETC;
} Etp;

extern Etp Penman;


typedef struct EVP {
    float MaxEvapWater;
    float MaxEvapSoil;
    float MaxTranspiration;
} EVP;

extern EVP Evtra;

#endif	// PENMAN_H

