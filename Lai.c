#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extern.h"
#include "lintul4.h"

/* ---------------------------------------------------------------------------*/
/*  function LeaveGrowth(float LAIExp, float NewLeaves)                       */
/*  Purpose: Calculation of the daily leaves growth rate, the results are     */
/*           stored in the Crop->properties linked list                       */
/* ---------------------------------------------------------------------------*/

float LeaveGrowth(float *shoots)
{
    float EffectiveTemp;
    float SpecLeafArea;
    
    SpecLeafArea = Afgen(Crop->prm.SpecificLeaveArea,&Crop->st.Development) * 
            exp(-Crop->prm.NitrogenStessSLA * (1.-Crop->N_st.Indx));
    
    /* Calculate the effective temperature i.e. the value above the baseline */
    EffectiveTemp = max(0., Temp - Crop->prm.TempBaseLeaves);
    
    /* Growth during juvenile stage */
    if ((Crop->st.Development < 0.2) && (Crop->st.LAI < 0.75))
    {
        Crop->rt.LAI =(Crop->st.LAI * (exp(Crop->prm.RelIncreaseLAI * EffectiveTemp) - 1.)) * 
                WatBal->WaterStress *  exp(-Crop->prm.NitrogenStressLAI * (1.0 - Crop->N_st.Indx));
    }
    else
    {
        Crop->rt.LAI = (*shoots * Crop->fac_lv) * SpecLeafArea;
    }   

    return Crop->rt.LAI;
}
