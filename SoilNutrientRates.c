#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------*/
/*  function SoilNutrientRates()                                  */
/*  Purpose: Calculation of the soil nutrient rates kg ha-1 d-1   */
/* ---------------------------------------------------------------*/     

void SoilNutrientRates()
{
    float N_fert;
    float day_fl;
    
    Site->rt_N_mins = 0.;

    
    if (Crop->DevelopmentStage > 0. && Crop->DevelopmentStage <= Crop->prm.DevelopmentStageNLimit)
    {   /* NPK rates that come available through mineralization, cannot exceed */
        /* the available NPK in the soil                                       */
        Site->rt_N_mins = min(Mng->N_Mins * Mng->NRecoveryFrac, Site->st_N_tot); 
    }
    
    day_fl = (float)Day;
    
    /* N amount that comes available for the crop at day_fl through fertilizer applications */
    N_fert = Afgen(Mng->N_Fert_table, &day_fl) * Afgen(Mng->N_Uptake_frac, &day_fl);
    
    /* Change in total inorganic NPK in soil as function of fertilizer input, */
    /* soil N mineralization and crop uptake                                */
    Site->rt_N_tot = (N_fert / Step) - Crop->N_rt.Uptake  + Site->rt_N_mins;
}
