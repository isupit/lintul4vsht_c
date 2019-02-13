#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extern.h"
#include "penman.h"
#include "lintul4.h"


/*-----------------------------------------------------------------------------------------------*/
/* function InitializeWatBal                                                                     */
/* Purpose: Initialization of soil moisture content (SMACT, cm3/cm3), available amounts of water */
/*           (above wilting point) in maximum effective rooted zone, both actual (WAVT)          */
/*           and total amount of water in maximum rooted zone (WTOT),                            */
/*           all in cm.                                                                          */
/*-----------------------------------------------------------------------------------------------*/

void InitializeWatBal()
{ 
    float ActualSM;
    float ActualSMLow;
    float MaxRootingDepth;
    
    ActualSM    = max(Soil.ct.MoistureWP, min(Soil.ct.MoistureInit,Soil.ct.MoistureFC));
    ActualSMLow = max(Soil.ct.MoistureWP, min(Soil.ct.MoistureInitLow,Soil.ct.MoistureFC));
    MaxRootingDepth = min(Soil.ct.SoilMaxRootDepth, Crop.prm.MaxRootingDepth);
    Crop->RootDepth = Crop.prm.InitRootingDepth;
    
    /* Total available water in rooted zone */
    WatBal->st.RootZoneMoisture = Crop->RootDepth * (ActualSM - Soil.ct.MoistureWP);
    
    /* Total available water in lower zone*/
    WatBal->st.MoistureLOW = (MaxRootingDepth-Crop->RootDepth) * (ActualSMLow - Soil.ct.MoistureWP);
    
    /* Total water in rooted zone */
    WatBal->st.TotalWaterRootZone = Crop->RootDepth * ActualSM;
    
    /* Total water in lower zone*/
    WatBal->st.TotalWaterLowerZone = (MaxRootingDepth-Crop->RootDepth) * ActualSMLow; 
 
}


/*-----------------------------------------------------*/
/* function IntegrationWatBal                          */
/* Purpose: integrate the waterbalance rates over time */
/* and calculate the water content in the rooted zone  */
/*-----------------------------------------------------*/

void IntegrationWatBal() 
{
    float PreSurfaceStorage;
    float WaterRootExt;
    
    WatBal->st.Transpiration += WatBal->rt.Transpiration;
    WatBal->st.EvapWater     += WatBal->rt.EvapWater;
    WatBal->st.EvapSoil      += WatBal->rt.EvapSoil;
    
    WatBal->st.Rain += Rain[Day];
    WatBal->st.Infiltration += WatBal->rt.Infiltration;
    WatBal->st.Irrigation   += WatBal->rt.Irrigation;
    
    /* Surface storage and runoff */
    PreSurfaceStorage = WatBal->st.SurfaceStorage + (Rain[Day] + 
            WatBal->rt.Irrigation - WatBal->rt.EvapWater - 
            WatBal->rt.Infiltration) * Step;
    WatBal->st.SurfaceStorage = min(PreSurfaceStorage, 
            Site->MaxSurfaceStorage);
    WatBal->st.Runoff += PreSurfaceStorage - WatBal->st.SurfaceStorage;
    
    /* Water amount in the rooted zone */
    WatBal->st.RootZoneMoisture += WatBal->rt.RootZoneMoisture * Step;
    if (WatBal->st.RootZoneMoisture < 0.) 
    {
       WatBal->st.EvapSoil += WatBal->st.RootZoneMoisture;
       WatBal->st.RootZoneMoisture = 0.;
    }
    
    /* Total percolation and loss of water by deep leaching */
    WatBal->st.Percolation += WatBal->rt.Percolation * Step;
    WatBal->st.Loss        += WatBal->rt.Loss * Step;     
    
    WatBal->st.MoistureLOW += WatBal->rt.MoistureLOW;
   
    /* Change of root zone subsystem boundary                  */
    /* Calculation of amount of soil moisture in new root zone */
    if (Crop->RootDepth - Crop->RootDepth_prev > 0.001) 
    {
        
        /* water added to root zone by root growth, in cm   */
        WaterRootExt = WatBal->st.MoistureLOW *
                (Crop->RootDepth - Crop->RootDepth_prev) / 
                (Crop->prm.MaxRootingDepth - Crop->RootDepth_prev);
        WatBal->st.MoistureLOW -= WaterRootExt;

        /* Total water addition to root zone by root growth  */
        WatBal->st.WaterRootExt += WaterRootExt;

        /* Amount of soil moisture in extended root zone */
        WatBal->st.RootZoneMoisture += WaterRootExt;
    }

    /* Mean soil moisture content in rooted zone */
    WatBal->st.Moisture = WatBal->st.RootZoneMoisture/Crop->RootDepth;
  
}