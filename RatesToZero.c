#include "cropst.h"
#include "watbal.h"

/* ---------------------------------------------------------------------------*/
/*  function RatesToZero()                                                    */
/*  Purpose: Set all rates to zero in one go                                  */
/* ---------------------------------------------------------------------------*/


void RatesToZero()
{
    // Set the dying rates 
    Crop->drt.roots = 0.;
    Crop->drt.leaves = 0.;
    Crop->drt.stems = 0.;
  
    // Set the development rate
    Crop->rt.Development = 0.;
    Crop->rt.vernalization = 0.;
       
    // Set the crop growth rates 
    Crop->rt.roots   = 0.;
    Crop->rt.leaves  = 0.;
    Crop->rt.stems   = 0.;
    Crop->rt.storage = 0.;
    Crop->rt.LAIExp  = 0.;      
       
    // Set the nutrient loss rates due to dying
    Crop->N_rt.death_lv = 0.;
    Crop->N_rt.death_st = 0.;
    Crop->N_rt.death_ro = 0.;
       
    // Set nutrient rates to various crop organs
    Crop->N_rt.leaves  = 0.;
    Crop->N_rt.stems   = 0.;
    Crop->N_rt.storage = 0.;
    Crop->N_rt.roots   = 0.;
    
    // Set the nutrient demand rates 
    Crop->N_rt.Demand_lv = 0.;
    Crop->N_rt.Demand_st = 0.;
    Crop->N_rt.Demand_ro = 0.;
    Crop->N_rt.Demand_so = 0.;
    
    
    // Set the nutrient translocation rates
    Crop->N_rt.Transloc = 0.;

    // Set the nutrient uptake rates
    Crop->N_rt.Uptake    = 0.;
    Crop->N_rt.Uptake_lv = 0.;
    Crop->N_rt.Uptake_st = 0.;
    Crop->N_rt.Uptake_ro = 0.;
       
    // Set the water balance rates 
    WatBal->rt.EvapWater          = 0.;
    WatBal->rt.EvapSoil           = 0.;   
    WatBal->rt.Infiltration       = 0.;
    WatBal->rt.Loss               = 0.;
    WatBal->rt.Percolation        = 0.;
    WatBal->rt.AvailableRootZone  = 0.;
    WatBal->rt.RunOff             = 0.;
    WatBal->rt.WaterRootExt       = 0.;
    WatBal->rt.AvailableRootZone  = 0.;
    WatBal->rt.AvailableLowerZone = 0.;
}

