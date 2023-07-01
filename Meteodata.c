#include <string.h>#include <stdlib.h>#include <math.h>#include "lintul4.h"#include "extern.h"int GetMeteoData(char* inputfile){    int c, i, Station;    float A, B, Rad, Rainfall, VapourPressure;    FILE *fq;    /* Open file */    if ((fq = fopen(inputfile, "rt")) == NULL)    {        fprintf(stderr, "Cannot open meteo input file. %s\n", inputfile);         exit(0);    }    /* Skip lines in the header */     while ((c=fgetc(fq)) == '*')         while ((c=fgetc(fq)) != '\n');         fscanf(fq,"%f %f %f %f %f", &Longitude, &Latitude, &Altitude,  &A, &B);    AngstA = fabs(A);    AngstB = fabs(B);    i = 1;    while(fscanf(fq,"%d %d %d %f %f %f %f %f %f", &Station,                                           &MeteoYear[i],                                           &MeteoDay[i],                                           &Rad,                                          &Tmin[i],                                           &Tmax[i],                                           &VapourPressure,                                          &Windspeed[i],                                           &Rainfall) != EOF)    {                // Transform Radiation from KJ m-2 d-1 to J m-2 d-1         Radiation[i] = 1000.*Rad;                // Transform Rain from mm d-1 to cm d-1        Rain[i] = 0.1 * Rainfall;                // Transform Vapour from kPa to hPa        Vapour[i] = 10. * VapourPressure;        i++;    }    fclose(fq);     return 1;}