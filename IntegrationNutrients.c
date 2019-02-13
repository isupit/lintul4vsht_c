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
    /* Integration of the total of soil N,P,K */
    Site->st_N_tot = max(0., Site->st_N_tot + Site->rt_N_tot);
    
    /* Integration of the total N,P,K soil mineralization */
    Site->st_N_mins += Site->rt_N_mins;
        
    /* Crops nutrients */
    Crop->N_st.leaves  += Crop->N_rt.leaves ;
    Crop->N_st.stems   += Crop->N_rt.stems  ;
    Crop->N_st.roots   += Crop->N_rt.roots  ;
    Crop->N_st.storage += Crop->N_rt.storage;
    
    /* Nutrient losses due to dying plant parts */
    Crop->N_st.death_lv += Crop->N_rt.death_lv;
    Crop->N_st.death_st += Crop->N_rt.death_st;
    Crop->N_st.death_ro += Crop->N_rt.death_ro;
}