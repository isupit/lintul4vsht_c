#include "extern.h"
#include <stdlib.h>
#include <math.h>
#include "lintul4.h"


/* ---------------------------------------------------------------------------*/
/*  function NutrientLoss                                                     */
/*  Purpose: To calculate nutrient loss rate of dying of roots, stems leaves  */
/*           and storage organs (kg N ha-1 d-1)                               */
/* ---------------------------------------------------------------------------*/   

 
void NutrientLoss() 
{         
    Crop->N_rt.death_lv = Crop->prm.N_ResidualFrac_lv * Crop->drt.leaves;
    Crop->N_rt.death_st = Crop->prm.N_ResidualFrac_st * Crop->drt.stems;
    Crop->N_rt.death_ro = Crop->prm.N_ResidualFrac_ro * Crop->drt.roots;
} 

/* ---------------------------------------------------------------------------*/
/*  function NutrientMax()                                                    */
/*  Purpose: To calculate the max nutrient concentration in the stems, leaves */
/*           and roots organs (kg N ha-1)                                     */
/* ---------------------------------------------------------------------------*/
void NutrientMax()
{           
    // Maximum N concentration in the leaves (kg N kg-1)
    Crop->N_st.Max_lv = Afgen(Crop->prm.N_MaxLeaves, &(Crop->st.Development));
      
    // Maximum N concentrations in stems and roots (kg N kg-1) 
    Crop->N_st.Max_st = Crop->prm.N_MaxRoots * Crop->N_st.Max_lv;
    Crop->N_st.Max_ro = Crop->prm.N_MaxStems * Crop->N_st.Max_lv;
}


/* -----------------------------------------------------------------------*/
/*  function NutrientOptimum()                                            */
/*  Purpose: To compute the optimal nutrient concentration in the crop    */
/*  organs (kg N ha-1 )                                                   */
/* -----------------------------------------------------------------------*/
void NutrientOptimum()
{  
    // Optimum N amount in vegetative above-ground living biomass
    //and its N concentration                                       
    Crop->N_st.Optimum_lv = Crop->prm.Opt_N_Frac * Crop->N_st.Max_lv * Crop->st.leaves;
    Crop->N_st.Optimum_st = Crop->prm.Opt_N_Frac * Crop->N_st.Max_st * Crop->st.stems;
}
 
/* ----------------------------------------------------------------------------*/
/*  function NutrientDemand()                                                  */
/*  Purpose: To compute the nutrient demand of crop organs (kg N ha-1 d-1)     */
/* ----------------------------------------------------------------------------*/
void NutrientDemand()
{
    Crop->N_rt.Demand_lv =  fmaxf(Crop->N_st.Max_lv *Crop->st.leaves - Crop->N_st.leaves, 0.);
    Crop->N_rt.Demand_st =  fmaxf(Crop->N_st.Max_st *Crop->st.stems  - Crop->N_st.stems, 0.);
    Crop->N_rt.Demand_ro =  fmaxf(Crop->N_st.Max_ro *Crop->st.roots  - Crop->N_st.roots, 0.);
    Crop->N_rt.Demand_so =  fmaxf(Crop->prm.Max_N_storage *Crop->st.storage- Crop->N_st.storage, 0.)/Crop->prm.TCNT;
}


/* ---------------------------------------------------------------------------*/
/*  function NutrientRates()                                                  */
/*  Purpose: To calculate nutrient changes (i.e. rates) in the plant          */
/*           organs (kg N ha-1 d-1)                                       */
/* ---------------------------------------------------------------------------*/

void CropNutrientRates()
{   
    Crop->N_rt.leaves  = Crop->N_rt.Uptake_lv - Crop->N_rt.Transloc_lv - Crop->N_rt.death_lv;
    Crop->N_rt.stems   = Crop->N_rt.Uptake_st - Crop->N_rt.Transloc_st - Crop->N_rt.death_st;
    Crop->N_rt.roots   = Crop->N_rt.Uptake_ro - Crop->N_rt.Transloc_ro - Crop->N_rt.death_ro;
     
}


/* ---------------------------------------------------------------*/
/*  function SoilNutrientRates()                                  */
/*  Purpose: Calculation of the soil nutrient rates kg ha-1 d-1   */
/* ---------------------------------------------------------------*/     

void SoilNutrientRates(float *NutrientLimit)
{
    float N_fert =0.;
    
    Mng->rt.N_mins = 0.;
   
    if (Crop->Emergence > 0. && Crop->st.Development <= Crop->prm.DevelopmentStageNLimit)
    {   // N rates that come available through mineralization, cannot exceed 
        // the available N in the soil                                       
        Mng->rt.N_mins = fminf(Mng->st.N_mins, Mng->N_Mins * Mng->NRecoveryFrac + 
                Mng->N_Background) * (*NutrientLimit);
    }
    
    // N amount that comes available for the crop at day_fl through fertilizer applications 
    N_fert = List(Mng->N_Fert_table) * Mng->N_Uptake_frac;
    
    // Change in total inorganic N in soil as function of fertilizer input, 
    // soil N mineralization and crop uptake 
    Mng->rt.N_tot = (N_fert - Crop->N_rt.Uptake + Mng->rt.N_mins);
    if (Mng->st.N_tot + Mng->rt.N_tot < 0. ) 
        Mng->rt.N_tot = fmaxf(0, Mng->st.N_tot + Mng->rt.N_tot); 
}


               
void RateCalcultionNutrients()
{
    float NutrientLimit;
    
    NutrientLimit = insw(Crop->st.Development - Crop->prm.DevelopmentStageNLimit, 
        insw(WatBal->WaterStress - 0.01,0.,1.) , 0.0);

    
    NutrientMax();
    
    NutrientDemand();
        
    NutrientLoss();
    
    NutrientPartioning(&NutrientLimit);
    
    NutrientTranslocation();
    
    CropNutrientRates();
        
    SoilNutrientRates(&NutrientLimit);
    
    /* Establish the optimum nutrient concentrations in the crop organs */
    NutrientOptimum();
    
    /* Calculate the nutrition index */
    NutritionINDX();    
}
