#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------------------*/
/*  function Translocation()                                                  */ 
/*  Purpose: To compute the amount of nutrients in the organs that can        */
/*  be translocated kg ha-1                                                   */
/* ---------------------------------------------------------------------------*/
void NutrientTranslocation()                                                                                                       
{
     float Avail_N_lv;
     float Avail_N_st;   
     float Avail_N_rt;
     float Supply_so;
                                                                                                                 
    /* N amount available for translocation */                                                                                                              
    Avail_N_lv = max(0.,Crop->N_st.leaves - Crop->st.leaves * Crop->prm.N_ResidualFrac_lv);
    Avail_N_st = max(0.,Crop->N_st.stems  - Crop->st.stems  * Crop->prm.N_ResidualFrac_st);
    Avail_N_rt = max(0.,min((Avail_N_lv + Avail_N_st) * Crop->prm.FracTranslocRoots, 
            Crop->N_st.roots - Crop->st.roots * Crop->prm.N_ResidualFrac_ro));
   
    /* Total available nutrient amount for translocation */
    Crop->N_rt.Transloc = Avail_N_lv + Avail_N_st + Avail_N_rt;
    
    Supply_so = insw(Crop->st.Development - Crop->prm.DevelopmentStageNT,0., Crop->N_rt.Transloc/Crop->prm.TCNT);
    Crop->N_rt.storage  =min(Supply_so,Crop->N_rt.Demand_so);
    
    /* Actual N translocation rate */ 
    if (Crop->N_rt.Transloc > 0.001)
    {
        Crop->N_rt.Transloc_lv = Crop->N_rt.storage * Avail_N_lv / Crop->N_rt.Transloc;
        Crop->N_rt.Transloc_st = Crop->N_rt.storage * Avail_N_st / Crop->N_rt.Transloc;
        Crop->N_rt.Transloc_ro = Crop->N_rt.storage * Avail_N_rt / Crop->N_rt.Transloc;  
    }
    else
    {
        Crop->N_rt.Transloc_lv = 0.;       
        Crop->N_rt.Transloc_st = 0.;
        Crop->N_rt.Transloc_ro = 0.;
    }
}   