#include "extern.h"
#include <math.h>
#include "lintul4.h"


/* ------------------------------------------------------------------------*/
/*  function DyingLeaves()                                                 */
/*  Purpose: To compute the amount of dying leaves as a result of shading, */
/*  (i.e. high LAI), water and/or nutrient stress or age                   */
/* ------------------------------------------------------------------------*/

void DyingOrgans()
{
    float DeathRateTemp = 0.;
    float DeathRateShading;
    float DeathRateWaterStress;
    float DeathRate;
    float DeathRateNStress;
    float DeathRateLAIStress;
    float SpecLeafArea; 
    float DeathLeaves;
    float DeathLAI;
    
    // Specific Leaf area(m2/g), as dependent on N stress 
    SpecLeafArea = Afgen(Crop->prm.SpecificLeaveArea, &(Crop->st.Development)) * 
        exp(-Crop->prm.NitrogenStessSLA * (1.-Crop->N_st.Indx));
    
    // Death rate due to temperature after a certain development stage 
    if (Crop->st.Development >= Crop->prm.DVSLeavesDie) {
        DeathRateTemp = Afgen(Crop->prm.DeathRateLeaves, &Temp);
    }

    // Death rate due to shading 
    DeathRateShading = fmaxf(0., Crop->prm.DeathRateLeavesShading * (Crop->st.LAI - Crop->prm.LAICr)/Crop->prm.LAICr);

    // Death rate due to water stress 
    DeathRateWaterStress = (1. - WatBal->WaterStress) * Crop->prm.DeathRateLeavesWaterStr;
    
    DeathRate = fmaxf(DeathRateTemp, fmaxf(DeathRateShading, DeathRateWaterStress));
    
    // Death rate due to N stress 
    DeathRateNStress   = 0.;
    DeathRateLAIStress = 0.;
    if (Crop->N_st.Indx < 1.)
    {
        DeathRateNStress   = Crop->prm.DyingLeaves_N_Stress * Crop->st.leaves * (1 -Crop->N_st.Indx);
        DeathRateLAIStress = DeathRateNStress * SpecLeafArea;
    }

    DeathLeaves = Crop->st.leaves * DeathRate;
    DeathLAI    = Crop->st.LAI * DeathRate;
    
    Crop->drt.leaves = fminf(Crop->st.leaves, DeathLeaves + DeathRateNStress);
    Crop->drt.LAI    = fminf(Crop->st.LAI, DeathLAI + DeathRateLAIStress);
    
    // Death rate roots
    Crop->drt.roots = fminf(Crop->st.roots, Crop->st.roots * 
            Afgen(Crop->prm.DeathRateRoots, &(Crop->st.Development)));

    // Death rate stems
    Crop->drt.stems = fminf(Crop->st.stems, Crop->st.stems * 
            Afgen(Crop->prm.DeathRateStems, &(Crop->st.Development)));

}
