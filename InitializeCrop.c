#include "extern.h"
#include <math.h>
#include <stdlib.h>
#include "lintul4.h"

/*---------------------------------------------------*/
/* function EmergenceCrop                            */
/* Purpose: determine if crop emergence has occurred */
/*---------------------------------------------------*/

int EmergenceCrop(int Emergence)
{
    Crop->DeltaTempSum = limit(0, Crop->prm.TempEffMax - Crop->prm.TempBaseEmergence, 
        Temp - Crop->prm.TempBaseEmergence); 
    
    //  Emergence has not taken place yet
    if (!Emergence) {

	    Crop->TSumEmergence += Crop->DeltaTempSum;
	    if (Crop->TSumEmergence >= Crop->prm.TSumEmergence) {
                Crop->GrowthDay = 1;
                Crop->Emergence = 1;
                Emergence = 1;
            }
    } 
    
    return Emergence;
}
    

/* ----------------------------------------------------------*/
/*  function InitializeCrop                                  */
/*  Purpose: Set the initial crop state and leave variables  */
/*  ---------------------------------------------------------*/ 

void InitializeCrop()
{ 
    float FractionRoots;
    float FractionShoots; 
    float InitialShootWeight;
   
    // Initialize the crop states 
    Crop->st.Development = Crop->prm.InitialDVS;

    FractionRoots      = Afgen(Crop->prm.Roots, &(Crop->st.Development));
    FractionShoots     = 1 - FractionRoots;
    InitialShootWeight = Crop->prm.InitialDryWeight * FractionShoots;

    Crop->st.roots     = Crop->prm.InitialDryWeight * FractionRoots;
    Crop->st.RootDepth = Crop->prm.InitRootingDepth;
    Crop->st.stems     = InitialShootWeight * Afgen(Crop->prm.Stems, &(Crop->st.Development));                   
    Crop->st.leaves    = InitialShootWeight * Afgen(Crop->prm.Leaves, &(Crop->st.Development));
    Crop->st.storage   = InitialShootWeight * Afgen(Crop->prm.Storage, &(Crop->st.Development));
    
    Crop->st.vernalization = 0.;
    Crop->st.RootDepth_prev = 0.;
    
    Crop->dst.leaves = 0.; 
    Crop->dst.stems = 0.;
    Crop->dst.roots = 0.;
    
    
    Crop->rt.ParIntercepted = 0.;
    Crop->st.ParIntercepted = 0.;
    
    Crop->st.Development = 0.;
    Crop->rt.Development = 0.;
    
    Crop->rt.roots     = 0.0;
    Crop->rt.RootDepth = 0.0; 
    Crop->rt.stems     = 0.0;  
    Crop->rt.leaves    = 0.0;  
    Crop->rt.storage   = 0.0;  

    // Adapt the maximum rooting depth 
    Crop->prm.MaxRootingDepth = fmaxf(Crop->prm.InitRootingDepth, fminf(Crop->prm.MaxRootingDepth,
         WatBal->ct.SoilMaxRootDepth));

    Crop->st.LAI = Crop->st.leaves * Afgen(Crop->prm.SpecificLeaveArea, &(Crop->st.Development)); 

    Crop->rt.LAI = 0.0;
            
    Crop->st.LAI = Crop->st.LAI + Crop->st.stems * 
           Afgen(Crop->prm.SpecificStemArea, &(Crop->st.Development)) +
           Crop->st.storage*Crop->prm.SpecificPodArea;
    
    Crop->TSumEmergence = 0;
    Crop->Emergence = 0;
    Crop->NutrientStress = 0.;
    
    // Initialize the heat stress 
    Crop->Heat = 0.;
    Crop->Anthesis = 0;
    Crop->HeatDays = 0;
    Crop->HeatReduction = 1.;
    Crop->HeatFlag = FALSE;
    Crop->SeedFlag = FALSE;
    Crop->GrainNr  = 0.;
    Crop->GrowthDay = 0;
    
      
    // Crop death rates set to zero
    Crop->drt.leaves = 0.;
    Crop->drt.roots  = 0.;
    Crop->drt.stems  = 0.;
    Crop->drt.LAI    = 0.;
    Crop->DeltaTempSum = 0.;
      
    // Statistics
    Crop->CroN_an = 0.;
    Crop->CroN_ma = 0.;
    Crop->Biom_an = 0.;
    Crop->Biom_ma = 0.;
    Crop->MaxLAI = 0.;
           
}  
