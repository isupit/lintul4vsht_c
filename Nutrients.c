#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lintul4.h"
#include "extern.h"
#include "penman.h"

/* ---------------------------------------------------------------------------*/
/*  function NutrientMax()                                                    */
/*  Purpose: To calculate the max nutrient concentration in the stems, leaves */
/*           and roots organs (kg N,P,K ha-1)                                 */
/* ---------------------------------------------------------------------------*/
void NutrientMax()
{           
    /* Maximum N,P,K concentration in the leaves, from which the */
    /* N,P,K concentration in the stems and roots is derived     */
    /* as a function of development stage (kg N kg-1 DM)         */
    Crop->N_st.Max_lv = Afgen(Crop->prm.N_MaxLeaves, &(Crop->st.Development));
      
    /* Maximum N concentrations in stems and roots (kg N kg-1) */
    Crop->N_st.Max_st = Crop->prm.N_MaxRoots * Crop->N_st.Max_lv;
    Crop->N_st.Max_ro = Crop->prm.N_MaxStems * Crop->N_st.Max_lv;
}


/* ---------------------------------------------------------------------------*/
/*  function NutrientOptimum()                                                */
/*  Purpose: To compute the optimal nutrient concentration in the crop        */
 /*  organs (kg N,P,K ha-1 )                                                  */
/* ---------------------------------------------------------------------------*/
void NutrientOptimum()
{  
    /* Optimum N,P,K amount in vegetative above-ground living biomass */
    /* and its N concentration                                        */
    Crop->N_st.Optimum_lv = Crop->prm.Opt_N_Frac * Crop->N_st.Max_lv * Crop->st.leaves;
    Crop->N_st.Optimum_st = Crop->prm.Opt_N_Frac * Crop->N_st.Max_st * Crop->st.stems;
}
 
/* ----------------------------------------------------------------------------*/
/*  function NutrientDemand()                                                  */
/*  Purpose: To compute the nutrient demand of crop organs (kg N,P,K ha-1 d-1) */
/* ----------------------------------------------------------------------------*/
void NutrientDemand()
{
    Crop->N_rt.Demand_lv =  max (Crop->N_st.Max_lv *Crop->st.leaves - Crop->N_st.leaves, 0.);
    Crop->N_rt.Demand_st =  max (Crop->N_st.Max_st *Crop->st.stems  - Crop->N_st.stems, 0.);
    Crop->N_rt.Demand_ro =  max (Crop->N_st.Max_ro *Crop->st.roots  - Crop->N_st.roots, 0.);
    Crop->N_rt.Demand_so =  max (Crop->N_st.Max_so *Crop->st.storage- Crop->N_st.storage, 0.)/Crop->prm.TCNT;
}

/* ---------------------------------------------------------------*/
/*  function SoilNutrientRates()                                  */
/*  Purpose: Calculation of the soil nutrient rates kg ha-1 d-1   */
/* ---------------------------------------------------------------*/     

void SoilNutrientRates()
{
    float N_fert;
    
    Mng->rt.N_mins = 0.;

    
    if (Crop->st.Development > 0. && Crop->st.Development <= Crop->prm.DevelopmentStageNLimit)
    {   // N rates that come available through mineralization, cannot exceed 
        // the available NPK in the soil                                       
        Mng->rt.N_mins = min(Mng->N_Mins * Mng->NRecoveryFrac, Mng->st.N_mins); 
    }
    
    // N amount that comes available for the crop at day_fl through fertilizer applications 
    N_fert = List(Mng->N_Fert_table) * List(Mng->N_Uptake_frac);
    
    // Change in total inorganic NPK in soil as function of fertilizer input, */
    // soil N mineralization and crop uptake                                */
    Mng->rt.N_tot = min(0.,N_fert - Crop->N_rt.Uptake  + Mng->rt.N_mins);
}


               
void RateCalcultionNutrients()
{
    NutrientMax();
    
    NutrientDemand();
    
    NutrientLoss();
    
    NutrientPartioning();
    
    CropNutrientRates();
    
    NutrientTranslocation();
    
    SoilNutrientRates();
    
    /* Establish the optimum nutrient concentrations in the crop organs */
    NutrientOptimum();
    
    /* Calculate the nutrition index */
    NutritionINDX();    
}
