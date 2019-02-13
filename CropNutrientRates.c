#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"


/* ---------------------------------------------------------------------------*/
/*  function NutrientRates()                                                  */
/*  Purpose: To calculate nutrient changes (i.e. rates) in the plant          */
/*           organs (kg N,P,K ha-1 d-1)                                       */
/* ---------------------------------------------------------------------------*/

void CropNutrientRates()
{   
    Crop->N_rt.storage = 0;
    Crop->P_rt.storage = 0;
    Crop->K_rt.storage = 0;     
 
    Crop->N_rt.leaves  = Crop->N_rt.Uptake_lv - Crop->N_rt.Transloc_lv - Crop->N_rt.death_lv;
    Crop->N_rt.stems   = Crop->N_rt.Uptake_st - Crop->N_rt.Transloc_st - Crop->N_rt.death_st;
    Crop->N_rt.roots   = Crop->N_rt.Uptake_ro - Crop->N_rt.Transloc_ro - Crop->N_rt.death_ro;
   
   
    /* Rate of N,P,K uptake in storage organs (kg N,P,K ha-1 d-1) */
    if (Crop->DevelopmentStage <  Crop->prm.DevelopmentStageNT)
    {
        Crop->N_rt.storage = min(Crop->N_rt.Demand_so, Crop->N_rt.Transloc/Crop->prm.TCNT);
    }
}
