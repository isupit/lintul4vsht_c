#include "extern.h"
#include <math.h>
#include "lintul4.h"


/* ---------------------------------------------------------------------------*/
/*  function RateCalculationCrop()                                            */
/*  Purpose: Calculate the net amount of assimilates that is available for    */
/*  crop growth and subsequently establish the crop growth rates for the      */
/*  plant organs (kg ha-1 d-1).                                               */
/* ---------------------------------------------------------------------------*/


void RateCalculationCrop()
{
    float TotalAssimilation;
    float GrossAssimilation;
    float Stress;

    // Assimilation 
    GrossAssimilation = DailyTotalAssimilation();
   
    // Stress: either nutrient shortage or water shortage 
    Stress = fminf(Crop->NutrientStress, WatBal->WaterStress);
 
    // Correction for low minimum temperatures and stress factors
    TotalAssimilation = Stress * GrossAssimilation;       
   
    DevelopmentRate();

    // Growth of roots, stems, leaves and storage organs
    Growth(TotalAssimilation);

    NutrientLoss();
    
    CropNutrientRates();
    
}
