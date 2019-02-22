#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lintul4.h"
#include "extern.h"

void Partioning(float *Fraction_ro, float *Fraction_lv, float *Fraction_st, float *Fraction_so)
{
    float factor;
    float flv;
    
    /* Water stress is more severe as compared to Nitrogen stress and */
    /* partitioning will follow the original assumptions of LINTUL2   */  
    
    if (WatBal->WaterStress < Crop->N_st.Indx)
    {
        factor = max(1., 1./(WatBal->WaterStress + 0.5));
        *Fraction_ro = min(0.6, Afgen(Crop->prm.Roots, &(Crop->DevelopmentStage)) * factor);
        *Fraction_lv = Afgen(Crop->prm.Leaves, &(Crop->DevelopmentStage));
        *Fraction_st = Afgen(Crop->prm.Stems, &(Crop->DevelopmentStage));
        *Fraction_so = Afgen(Crop->prm.Storage, &(Crop->DevelopmentStage));
    }
    else
    {
        flv = Afgen(Crop->prm.Leaves, &(Crop->DevelopmentStage));
        factor = exp(-Crop->prm.N_lv_partitioning * ( 1. - Crop->N_st.Indx));
        
        *Fraction_lv = flv * factor;
        *Fraction_ro = Afgen(Crop->prm.Roots, &(Crop->DevelopmentStage));
        *Fraction_st = Afgen(Crop->prm.Stems, &(Crop->DevelopmentStage)) + flv - Fraction_lv;
        *Fraction_so = Afgen(Crop->prm.Storage, &(Crop->DevelopmentStage));
    }
}

/* ---------------------------------------------------------------------------*/
/*  function Growth(float NewPlantMaterial)                                   */
/*  Purpose: Establish growth rates of the plant organs (kg ha-1 d-1) and     */
/*  rooting depth (cm)                                                        */
/* ---------------------------------------------------------------------------*/

void Growth(float NewPlantMaterial)
{
    float shoots;
    float Fraction_ro;
    float Fraction_lv;
    float Fraction_st;
    float Fraction_so;
    
    float RootGrowth;
        
    
    Partioning(&Fraction_ro, &Fraction_lv, &Fraction_st, &Fraction_so);
    DyingOrgans();
    
    Crop->rt.roots  = NewPlantMaterial * Fraction_ro - Crop->drt.roots;
	
    shoots         = NewPlantMaterial * (1-Fraction_ro);
    Crop->rt.stems  = shoots * Fraction_st - Crop->drt.stems;
    Crop->rt.storage = shoots * Fraction_so;
	
     
    Crop->rt.leaves  = shoots * Fraction_lv;
    Crop->rt.LAIExp  = LeaveGrowth(Crop->st.LAIExp, Crop->rt.leaves);	
    Crop->rt.leaves  = Crop->rt.leaves -  Crop->drt.leaves;
	
    Crop->st.RootDepth_prev = Crop->st.RootDepth;
    
    /* No Root growth if no assimilates are partitioned to the roots or if */
    /* the crop has no airducts and the roots are close to the groundwater */
    if (Fraction_ro <= 0.0 || (!Crop->prm.Airducts && Site->GroundwaterDepth - Crop->st.RootDepth < 10.))
        RootGrowth = 0.;
    else
        RootGrowth = min(Crop->prm.MaxRootingDepth - Crop->st.RootDepth,
                Crop->prm.MaxIncreaseRoot*Step);
    
     Crop->st.RootDepth += RootGrowth;
}	
