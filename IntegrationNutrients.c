#include <math.h>
#include "lintul4.h"

/* ----------------------------------------------------------------------*/
/*  function IntegrationNutrients()                                      */
/*  Purpose: Integration of the soil and crop nutrient rates  kg ha-1    */
/* ----------------------------------------------------------------------*/      

void IntegrationNutrients()
{          
    // Crops nutrients 
    Crop->N_st.leaves  += Crop->N_rt.leaves ;
    Crop->N_st.stems   += Crop->N_rt.stems  ;
    Crop->N_st.roots   += Crop->N_rt.roots  ;
    Crop->N_st.storage += Crop->N_rt.storage;
    
    // Nutrient losses due to dying plant parts
    Crop->N_st.death_lv += Crop->N_rt.death_lv;
    Crop->N_st.death_st += Crop->N_rt.death_st;
    Crop->N_st.death_ro += Crop->N_rt.death_ro;
    
    // Total N uptake (kg N ha-1 d-1) from soil and by biological fixation
    Crop->N_st.Uptake   += Crop->N_rt.Uptake;
    Crop->N_st.Fixation += Crop->N_rt.Fixation;
    
    // Total N that is available for mineralisation
    Mng->st.N_mins  = fmaxf(0, Mng->st.N_mins - Mng->rt.N_mins);
    
    //Total of available N in the Soil
    Mng->st.N_tot  += Mng->rt.N_tot;
    
    // Total N that came available through mineralisation
    Mng->st.N_mins_av += Mng->rt.N_mins;

}
