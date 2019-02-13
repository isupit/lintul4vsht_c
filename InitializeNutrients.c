#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"

/* --------------------------------------------------------------------*/
/*  function NutrientsInitialize()                                     */
/*  Purpose: Initialization of nutrient parameters                     */
/* --------------------------------------------------------------------*/

void InitializeNutrients()
{
    float day_fl;
    
    /* Initial maximum N concentration in plant organs per kg biomass [kg N kg-1 dry biomass]   */
    Crop->N_st.Max_lv = Afgen(Crop->prm.N_MaxLeaves, &(Crop->DevelopmentStage));
    Crop->N_st.Max_st = Crop->prm.N_MaxStems * Crop->N_st.Max_lv;
    Crop->N_st.Max_ro = Crop->prm.N_MaxRoots * Crop->N_st.Max_lv;
    Crop->N_st.Max_so = 0.;
        
    /* Initial maximum N concentration in plant organs [kg N ]           */
    Crop->N_st.leaves = Crop->N_st.Max_lv * Crop->st.leaves;
    Crop->N_st.stems  = Crop->N_st.Max_st * Crop->st.stems;
    Crop->N_st.roots  = Crop->N_st.Max_ro * Crop->st.roots;
    Crop->N_st.storage = 0.;
          
    /* No nutrient losses at initialization */
    Crop->N_st.death_lv = 0.;
    Crop->N_st.death_st = 0.;
    Crop->N_st.death_ro = 0.;
    
    /* No death rats at initialization */
    Crop->N_rt.death_lv = 0.;
    Crop->N_rt.death_st = 0.;
    Crop->N_rt.death_ro = 0.;
       
    /* Set the initial demand rates */
    Crop->N_rt.Demand_lv = 0.;
    Crop->N_rt.Demand_st = 0.;
    Crop->N_rt.Demand_ro = 0.;
    Crop->N_rt.Demand_so = 0.;

    /* Set the initial translocation rates */
    Crop->N_rt.Transloc = 0.;
    
    /* Set the initial uptake to zero*/
    Crop->N_st.Uptake    = 0.;
    Crop->N_st.Uptake_lv = 0.;
    Crop->N_st.Uptake_st = 0.;
    Crop->N_st.Uptake_ro = 0.;
                     
    /* Set the soil nutrient rates to zero */
    Site->rt_N_tot = 0.;
    Site->rt_N_mins = 0.;

    
    day_fl = (float)Day;
    
     /* Set the soil nutrient states */
    Site->st_N_tot = Afgen(Mng->N_Fert_table, &day_fl) * Afgen(Mng->N_Uptake_frac, &day_fl) + Mng->N_Mins;
    Site->st_N_mins = Mng->N_Mins;

    
    /* Set the crop nutrient rates to zero */
    Crop->N_rt.Uptake = 0.;
    Crop->N_rt.Uptake_lv = 0.;
    Crop->N_rt.Uptake_st = 0.;
    Crop->N_rt.Uptake_ro = 0.;

    Crop->N_rt.Transloc_lv = 0.;
    Crop->N_rt.Transloc_st = 0.;
    Crop->N_rt.Transloc_ro = 0.;
     
    Crop->N_rt.death_lv = 0.;
    Crop->N_rt.death_st = 0.;
    Crop->N_rt.death_ro = 0.;
        
    Crop->N_rt.leaves = 0.;
    Crop->N_rt.stems  = 0.;
    Crop->N_rt.roots  = 0.;
    Crop->N_rt.storage= 0.;
       
    /* No nutrient stress at initialization */
    Crop->N_st.Indx = 1.;
    Crop->NPK_Indx  = 1.;
    
    /* No nutrient losses at initialization */
    Crop->N_rt.death_lv = 0.;
    Crop->N_rt.death_st = 0.;
    Crop->N_rt.death_ro = 0.;
       
    /* Set the initial optimal leave concentrations to zero */
    Crop->N_st.Optimum_lv = 0;
    Crop->N_st.Optimum_st = 0;
    
}     
