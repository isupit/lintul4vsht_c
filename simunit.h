#ifndef SIMUNIT_H
#define SIMUNIT_H

#define MAX_STRING             2048

#include "cropst.h"
#include "managest.h"
#include "watbal.h"

// Place holder for a simulation unit 
typedef struct SIMUNIT {
        Plant *crp;
        Management *mng;
        Soil  *soil;
        int emergence;
        int option;
        int file;
        int file_sum;
        char start[MAX_STRING];
        char output[MAX_STRING];
        char output_sum[MAX_STRING];
        char treatment[MAX_STRING];
        char location[MAX_STRING]; 
        
        struct SIMUNIT *next;
        } SimUnit; 

#endif	
