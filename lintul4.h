#include "cropst.h"
#include "watbal.h"
#include "managest.h"
#include "penman.h"
#include "simunit.h"


#ifndef LINTUL4_H
#define LINTUL4_H

#define FALSE 0
#define TRUE 1  

#define NR_VARIABLES_CRP	51
#define NR_TABLES_CRP   	21
#define NR_VARIABLES_SOIL       10
#define NR_TABLES_SOIL          1
#define NR_VARIABLES_MANAGEMENT 4
#define NR_TABLES_MANAGEMENT    2
#define NUMBER_OF_TABLES        32
#define NR_SIMUNITS             4
#define MAX_STRING             2048
#define METEO_LENGTH           36600 //max 100 years 
      


typedef struct WEATHER {
        char file[MAX_STRING];
        int StartYear;
        int Seasons;
        float lat;
        float lon;
        struct WEATHER *next;
        } Weather;


#endif	// 

