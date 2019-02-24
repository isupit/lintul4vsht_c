#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"
#include "penman.h"

/* -------------------------------------------------------------------------*/
/*  function NutrientPartioning()                                           */
/*  Purpose: To compute the partitioning of the total N uptake rate     */
/*           (N UPTR) over leaves, stem, and roots kg  ha-1 d-1         */
/* -------------------------------------------------------------------------*/
void NutrientPartioning()
{     
    float Total_N_demand;
    float NutrientLimit;
    float N_Fix_rt;
    
    float tiny = 0.001;
    
    Crop->N_rt.Uptake_lv = 0.;
    Crop->N_rt.Uptake_st = 0.;
    Crop->N_rt.Uptake_ro = 0.;  
    
    Total_N_demand = Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro;
    
    NutrientLimit = insw(Crop->st.Development - Crop->prm.DevelopmentStageNLimit , 
            insw(WatBal->rt.Transpiration/Evtra.MaxTranspiration -0.01,0.,1.) , 0.0);
    
    /* Nutrient uptake cannot be larger than the availability and is larger or equal to zero */
    Crop->N_rt.Uptake = min((1.-Crop->prm.N_fixation)*Total_N_demand, Site->st_N_tot)* NutrientLimit/Step;
 
    N_Fix_rt= max(0.,Crop->N_rt.Uptake * Crop->prm.N_fixation / max(0.02, 1.-Crop->prm.N_fixation));
   
    /* N uptake per crop organ kg ha-1 d-1*/
    if (Total_N_demand > tiny)
    {
        Crop->N_rt.Uptake_lv = (Crop->N_rt.Demand_lv / Total_N_demand) * (Crop->N_rt.Uptake + N_Fix_rt);
        Crop->N_rt.Uptake_st = (Crop->N_rt.Demand_st / Total_N_demand) * (Crop->N_rt.Uptake + N_Fix_rt);
        Crop->N_rt.Uptake_ro = (Crop->N_rt.Demand_ro / Total_N_demand) * (Crop->N_rt.Uptake + N_Fix_rt);
    }
}    