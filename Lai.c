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

float LeaveGrowth(float LAIExp, float NewLeaves)
{
    float GLAI;
    float EffectiveTemp;
    /* Growth during maturation stage */
    GLAI = SLA * GLV;

    /* Calculate the effective temperature i.e. the value above the baseline */
    EffectiveTemp = max(0., Temp - Crop->prm.TempBaseLeaves);
    
    /* Growth during juvenile stage */
    if ((Crop->DevelopmentStage < 0.2) && (Crop->st.LAI < 0.75))
    {
        GLAI =(Crop->st.LAI * (exp(Crop->prm.RelIncreaseLAI * EffectiveTemp * Step) - 1.)/ Step ) * 
                WatBal->WaterStress *  exp(-Crop->prm.NLAI* (1.0 - Crop->N_st.Indx));
    }
       

*---- Growth at day of seedling emergence:
        IF (Crop->st.LAI.EQ.0.)
     $   GLAI = LAII / DELT
      ENDIF  

*---- Growth before seedling emergence:
      IF (.NOT. EMERG) GLAI = 0.
    return GLAI;
}
