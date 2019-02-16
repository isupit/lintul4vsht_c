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
    float MaxRootingDepth;
    
    WatBal->st.Moisture    = max(Soil.ct.MoistureWP, min(Soil.ct.MoistureInit,Soil.ct.MoistureFC));
    WatBal->st.MoistureLOW = max(Soil.ct.MoistureWP, min(Soil.ct.MoistureInitLow,Soil.ct.MoistureFC));
    MaxRootingDepth = min(Soil.ct.SoilMaxRootDepth, Crop.prm.MaxRootingDepth);
    Crop->st.RootDepth = Crop.prm.InitRootingDepth;
    
    /* Total available water in rooted zone */
    WatBal->st.RootZoneMoisture = Crop->st.RootDepth * (WatBal->st.Moisture - Soil.ct.MoistureWP);
    
    /* Total available water in lower zone*/
    WatBal->st.MoistureLOW = (MaxRootingDepth-Crop->st.RootDepth) * (WatBal->st.MoistureLOW - Soil.ct.MoistureWP);
    
    /* Total water in rooted zone */
    WatBal->st.TotalWaterRootZone = Crop->st.RootDepth * WatBal->st.Moisture;
    
    /* Total water in lower zone*/
    WatBal->st.TotalWaterLowerZone = (MaxRootingDepth-Crop->st.RootDepth) * WatBal->st.MoistureLOW; 
 
}

/*---------------------------------------------------*/
/* function RateCalulationWatBal                     */
/* Purpose: Calculate the rate of the WatBal struct  */
/*---------------------------------------------------*/

void RateCalulationWatBal() 
{
    float Infiltration;
    float PrelimRunOff;
    float MaxTranspiration;
    float KDiffuse;
    float SoilWatDepletion;
    float CriticalSoilMoisture;
    float MoistureStress;
    float SoilMoistureAeration;
    float MaxReductionOxygenStress;
    float OxygenStress;
    
    /* Infiltration of precipitation (RAIN) and irrigation (RIRR) (cm) */
    Infiltration = (1.0 - Soil.ct.RunOffFrac ) * Rain[Day] + Irrigation[Day];
    
    /* Water loss by surface runoff, preliminary */
    PrelimRunOff = Soil.ct.RunOffFrac * Rain[Day];
    
    /* Water added to root zone by root growth (cm/d), resp. total and available water */
    WatBal->rt.TotalWaterRootZone = Crop->rt.RootDepth * WatBal->st.MoistureLOW;
    WatBal->rt.RootZoneMoisture   = Crop->rt.RootDepth * (WatBal->st.MoistureLOW - Soil.ct.MoistureWP);

    /* Maximum transpiration rate (cm/d) as function of light interception and */
    /* crop-specific correction factor of potential transpiration              */
    KDiffuse = Afgen(Crop->prm.KDiffuseTb, &(Crop->DevelopmentStage));
    MaxTranspiration = max(0.0001,  
                             Penman.ET0 * Crop->prm.CorrectionTransp *
                             (1.-exp(-0.75 * KDiffuse * Crop->st.LAI)));
    
    SoilWatDepletion = sweaf();
    CriticalSoilMoisture = (1. - SoilWatDepletion)*
            (WatBal->ct.MoistureFC - WatBal->ct.MoistureWP) + WatBal->ct.MoistureWP;
    
       /* Transpiration reduction in case of water shortage */
    MoistureStress = limit(0.,1.,(WatBal->st.Moisture - WatBal->ct.MoistureWP)/
            (CriticalSoilMoisture - WatBal->ct.MoistureWP));
    
    
    /* Reduction in transpiration in case of oxygen shortage for non-rice crops */
    if (!Crop->prm.Airducts) 
    {
        /* Critical soil moisture content for aeration */
        SoilMoistureAeration = WatBal->ct.MoistureSAT - WatBal->ct.CriticalSoilAirC;
        
        /* Count days since start oxygen shortage (up to 4 days) */
        if (WatBal->st.Moisture >= SoilMoistureAeration) 
        {
            Crop->DaysOxygenStress = min(Crop->DaysOxygenStress++, 4.);
        }
        else 
        {
            Crop->DaysOxygenStress = 0.;
        }
        
        /* Maximum reduction reached after 4 days */
        MaxReductionOxygenStress = limit (0.,1.,(WatBal->ct.MoistureSAT - WatBal->st.Moisture)/
                (WatBal->ct.MoistureSAT - SoilMoistureAeration));
        
        OxygenStress   = MaxReductionOxygenStress + 
                (1.-Crop->DaysOxygenStress/4.)*(1.-MaxReductionOxygenStress);        
    }
    else 
    {
        OxygenStress = 1.;
    }
    
    WatBal->WaterStress = MoistureStress * OxygenStress;
    
    WatBal->rt.Transpiration = max(0.0, min(WatBal->rt.RootZoneMoisture, WatBal->WaterStress * Evtra.MaxTranspiration));
    
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
    WatBal->st.SurfaceStorage = PreSurfaceStorage, 
           
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
    if (Crop->rt.RootDepth > 0.001) 
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