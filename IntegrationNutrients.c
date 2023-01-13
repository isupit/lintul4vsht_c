#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"

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
    
    Mng->st.N_mins = max(0, Mng->st.N_mins - Mng->rt.N_mins);
    Mng->st.N_tot  += Mng->rt.N_tot;
//    printf("%7.2f %7.2f %7.4f\n", Mng->st.N_mins, Mng->st.N_tot, Crop->st.Development);
}