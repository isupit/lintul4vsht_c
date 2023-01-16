#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "lintul4.h"
#include "extern.h"


/*---------------------------------------------------*/
/* function EmergenceCrop                            */
/* Purpose: determine if crop emergence has occurred */
/*---------------------------------------------------*/

int EmergenceCrop(int Emergence)
{
    float DeltaTempSum;
     
    /*  Emergence has not taken place yet*/
    if (!Emergence)
	{
            DeltaTempSum = limit(0, Crop->prm.TempEffMax - Crop->prm.TempBaseEmergence, 
                Temp-Crop->prm.TempBaseEmergence);
	    Crop->TSumEmergence += DeltaTempSum;
	    if (Crop->TSumEmergence >= Crop->prm.TSumEmergence)
            {
                Emergence = 1;
                // Emergence true
                Crop->Emergence = 1;
                Crop->GrowthDay = 1;
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
   
    /* Initialize the crop states */
    Crop->st.Development = Crop->prm.InitialDVS;

    FractionRoots      = Afgen(Crop->prm.Roots, &(Crop->st.Development));
    FractionShoots     = 1 - FractionRoots;
    InitialShootWeight = Crop->prm.InitialDryWeight * FractionShoots;

    Crop->st.roots     = Crop->prm.InitialDryWeight * FractionRoots;
    Crop->st.RootDepth = Crop->prm.InitRootingDepth;
    Crop->st.stems     = InitialShootWeight * Afgen(Crop->prm.Stems, &(Crop->st.Development));                   
    Crop->st.leaves    = InitialShootWeight * Afgen(Crop->prm.Leaves, &(Crop->st.Development));
    Crop->st.storage   = InitialShootWeight * Afgen(Crop->prm.Storage, &(Crop->st.Development));

    /* Adapt the maximum rooting depth */
    Crop->prm.MaxRootingDepth = max(Crop->prm.InitRootingDepth, min(Crop->prm.MaxRootingDepth,
         WatBal->SoilMaxRootingDepth));

    Crop->st.LAI = Crop->st.leaves * Afgen(Crop->prm.SpecificLeaveArea, &(Crop->st.Development)); 


    Crop->st.LAI = Crop->st.LAI + Crop->st.stems * 
           Afgen(Crop->prm.SpecificStemArea, &(Crop->st.Development)) +
           Crop->st.storage*Crop->prm.SpecificPodArea;
    
    /* Initialize the heat stress */
    Crop->Heat = 0.;
    Crop->HeatDays = 0;
    Crop->HeatFlag = FALSE;
    Crop->SeedFlag = FALSE;
    
    /* Crop death rates set to zero */
    Crop->drt.leaves = 0.;
    Crop->drt.roots  = 0.;
    Crop->drt.stems  = 0.;
    
    /* Emergence true */
    //Crop->Emergence = 1;
    //Crop->GrowthDay = 1;
            
}  