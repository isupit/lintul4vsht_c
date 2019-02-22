#include <stdio.h>
#include <stdlib.h>
#include "extern.h"
#include "lintul4.h"
#include "penman.h"

/* ------------------------------------------------------------------------*/
/*  function DyingLeaves()                                                 */
/*  Purpose: To compute the amount of dying leaves as a result of shading, */
/*  (i.e. high LAI), water and/or nutrient stress or age                   */
/* ------------------------------------------------------------------------*/

float DyingOrgans()
{
    float DeathRateTemp = 0.;
    float DeathRateShading;
    float DeathRateWaterStress;
    float DeathRate;
    float DeathRateStress;
    float DeathRateLAIStress;
    float DeathRateNStress;
    float SpecLeafArea; 
    
    /* Specific Leaf area(m2/g), as dependent on N stress */
    SpecLeafArea = Afgen(Crop->prm.SpecificLeaveArea, &(Crop->DevelopmentStage)) * 
        exp(-Crop->prm.NutrientStessSLA * (1.-Crop->N_st.Indx));
    
    /* Death rate due to temperature after a certain development stage */
    if (Crop->DevelopmentStage > Crop->prm.DeathLeavesDVS)
    {
        DeathRateTemp = Afgen(Crop->prm.DeathRateLeaves, &Temp);
    }
    
    /* Death rate due to shading */
    DeathRateShading = max(0., Crop->prm.DeathRateLeavesShading * (Crop->st.LAI - Crop->prm.LAICr)/Crop->prm.LAICr);
    
    /* Death rate due to water stress */
    DeathRateWaterStress = (1. - WatBal->WaterStress) * Crop->prm.DeathRateLeavesWaterStr;
    
    
    DeathRate = max(DeathRateTemp, max(DeathRateShading, DeathRateWaterStress));
    
    /* Death rate due to N stress */
    DeathRateNStress = 0.;
    if (Crop->N_st.Indx < 1.)
    {
        DeathRateNStress = Crop->prm.DeathRateLeavesNStr * DeathRate * (1 -Crop->N_st.Indx);
    }
    
    DeathRateStress = Crop->st.leaves * DeathRate;
    DeathRateLAIStress    = Crop->st.LAI * DeathRate;
    
    Crop->drt.leaves = DeathRateStress + DeathRateNStress;
    Crop->drt.LAI    = DeathRateLAIStress + DeathRateNStress * SpecLeafArea;
    
    /* Death rate roots */
    Crop->drt.roots = Crop->st.roots * Afgen(Crop->prm.DeathRateRoots, &(Crop->DevelopmentStage));
    
    /* Death rate stems */
    Crop->drt.stems = Crop->st.stems * Afgen(Crop->prm.DeathRateStems, &(Crop->DevelopmentStage));
    
}
