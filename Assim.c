#include <stdio.h>
#include <math.h>
#include "astro.h"
#include "extern.h"
#include "lintul4.h"

/* ----------------------------------------------------------------------------*/
/*  function DailyTotalAssimilation()                                          */ 
/*  Purpose: Calculation of the daily assimilation rate using the three point  */
/*  Gaussian integration method.                                               */
/*-----------------------------------------------------------------------------*/
float DailyTotalAssimilation()
{
    float RadiationUseEFF;
    float RCO;
    float RTMP;
    float RTMCO;
    
    /* Radiation use efficiency as dependent on development stage (g DM MJ-1) */
    RadiationUseEFF= Afgen(Crop->prm.RUETb, &Crop->DevelopmentStage);
            
    /* Correction of radiation use efficiency for change in atmospheric CO2 concentration (-) */
    RCO = Afgen(Crop->prm.CO2AMAXTB, &CO2);
        
    /* Reduction of radiation use efficiency for non-optimal day-time temperatures and for low minimum temperature */
  
    RTMP= Afgen(Crop->prm.FactorAssimRateTemp, &DayTemp) * Afgen(Crop->prm.FactorGrossAssimTemp, &Tmin[Day]);

    /* Correction of RUE for both non-optimal temperatures and atmospheric CO2 */
    RTMCO= RTMP * RCO;

}
