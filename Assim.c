#include <math.h>
#include "extern.h"
#include "lintul4.h"


Plant *Crop;

extern float CO2;
extern float DayTemp;
extern float Radiation[METEO_LENGTH];
extern float Tmin[METEO_LENGTH];
extern size_t Day;

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
    float PAR;
    float InterceptedPAR;
    float KDiffuse;
    
    // Daily photosynthetically active radiation (PAR, MJ/m2)
    PAR = 0.50 * (Radiation[Day]/1.0E6);
    
    KDiffuse = Afgen(Crop->prm.KDiffuseTb,&(Crop->st.Development));
    
    InterceptedPAR = PAR * (1. - exp( -1*KDiffuse * Crop->st.LAI));
    
    // Radiation use efficiency as dependent on development stage (g DM MJ-1)
    RadiationUseEFF= Afgen(Crop->prm.RadiationUseEff, &Crop->st.Development);
            
    // Correction of radiation use efficiency for change in atmospheric CO2 concentration (-)
    RCO = Afgen(Crop->prm.CO2CorrectionRUE, &CO2);
     
    // Reduction of radiation use efficiency for non-optimal day-time temperatures and for low minimum temperature 
    RTMP= Afgen(Crop->prm.ReductionRueDayTemp, &DayTemp) * Afgen(Crop->prm.ReductionRueLowTemp, &Tmin[Day]);

    // Correction of RUE for both non-optimal temperatures and atmospheric CO2 
    RTMCO= RTMP * RCO;
   
   return (10. * RTMCO * RadiationUseEFF * InterceptedPAR);

}
