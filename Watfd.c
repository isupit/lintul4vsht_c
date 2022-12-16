#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extern.h"
#include "penman.h"
#include "lintul4.h"


/*-------------------------------------------------------------------------------------*/
/* function InitializeWatBal                                                           */
/* Purpose: Initialization of soil moisture content in rooted and the lower zone [cm]  */
/*---------------------------------------------------------------------------*---------*/

void InitializeWatBal()
{ 
    float KDiffuse;
    
    /* Set max and initial rooting depth */
    Crop->prm.MaxRootingDepth = min(WatBal->ct.SoilMaxRootDepth, Crop->prm.MaxRootingDepth);
    Crop->st.RootDepth = Crop->prm.InitRootingDepth;
    
    /* Assume no water stress at initialization */
    WatBal->WaterStress = 1.;
    
    /* Set the infiltration of the previous day to zero */
    WatBal->InfPreviousDay = 0.;
    
    WatBal->st.Moisture    = max(WatBal->ct.MoistureWP, min(WatBal->ct.MoistureInit,WatBal->ct.MoistureFC));
    WatBal->st.MoistureLow = max(WatBal->ct.MoistureWP, min(WatBal->ct.MoistureInitLow,WatBal->ct.MoistureFC));

    /* Set initial surface storage */
    WatBal->st.SurfaceStorage = Site->SurfaceStorage;
    
    /* Initial soil moisture for a rice crop */
    if (Crop->prm.Airducts) 
    {
        WatBal->st.Moisture = WatBal->ct.MoistureSAT; 
        WatBal->st.MoistureLow = WatBal->ct.MoistureSAT;
    }
       
    /* Initial  available moisture amount in rootable zone [cm] */
    WatBal->st.RootZoneMoisture = (WatBal->st.Moisture - WatBal->ct.MoistureWP) * Crop->st.RootDepth;
    
   /* Initial available moisture amount between rooted zone and max.rooting depth [cm] */
    WatBal->st.MoistureLow  = (WatBal->st.MoistureLow - WatBal->ct.MoistureWP) * 
            (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    /* Initial  total moisture amount in rootable zone [cm] */
    WatBal->st.TotalWaterRootZone = WatBal->st.Moisture * Crop->st.RootDepth;
    
   /* Initial total moisture amount between rooted zone and max.rooting depth [cm] */
    WatBal->st.TotalWaterLowerZone = WatBal->st.MoistureLow * 
            (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    /*  Soil evaporation, days since last rain */
    WatBal->DaysSinceLastRain = 1.;
    if (WatBal->st.Moisture <= (WatBal->ct.MoistureWP + 
            0.5 * (WatBal->ct.MoistureFC - WatBal->ct.MoistureWP))) 
            WatBal->DaysSinceLastRain = 5.;
    

    
    KDiffuse = Afgen(Crop->prm.KDiffuseTb, &(Crop->st.Development));
    WatBal->rt.EvapSoil = max(0., Penman.ES0 * exp(-0.75 * KDiffuse * Crop->st.LAI));
   
}

/*---------------------------------------------------*/
/* function RateCalulationWatBal                     */
/* Purpose: Calculate the rate of the WatBal struct  */
/*---------------------------------------------------*/

void RateCalulationWatBal() {
   
    float Available;
    float CMaxSoilEvap;
    float Perc1, Perc2;
    float WaterEq;
    float WELOW;
    float PERC, PERC1, PERC2; 
    float CAP,CAPL,CAP0,CAPL0;
    float PERCP,PERC1,PERC2,PERC3;
    float NotInf, RUNOFF, RUNOFP;
    
    // Get the irrigation rate */
    WatBal->rt.Irrigation = List(Mng->Irrigation);
    
    // Preliminary runoff rate
    NotInf = Afgen(Soil->NotInfTB, &Rain[Day]);
    RUNOFP = NotInf * Rain[Day];
    
    // Preliminary infiltration and rate 
    if (WatBal->st.SurfaceStorage <= 0.1) 
    {
        PERC = (1. - NotInf) * Rain[Day] + 
                WatBal->rt.Irrigation + WatBal->st.SurfaceStorage;
    }
    else 
    {
        /* Surface storage, infiltration limited by maximum percolation */
        /* rate root zone */
        Available = WatBal->st.SurfaceStorage + (Rain[Day] * 
                (1. - WatBal->ct.RunOffFrac) + WatBal->rt.Irrigation 
                 - WatBal->rt.EvapSoil);
        PERC = min(WatBal->ct.MaxPercolRTZ, Available);
    }
        
    /* If surface storage > 1 cm */
    if (WatBal->st.SurfaceStorage > 1.) 
    {
        WatBal->rt.EvapWater = Evtra.MaxEvapWater;
    }
    else 
    {
        if (WatBal->InfPreviousDay >= 1.) 
        {
            //If infiltration >= 1cm on previous day assume maximum soil evaporation
            WatBal->rt.EvapSoil = Evtra.MaxEvapSoil;
            WatBal->DaysSinceLastRain = 1.;
        }
        else 
        {
            WatBal->DaysSinceLastRain++;
            CMaxSoilEvap = Evtra.MaxEvapSoil*limit(0.,1.,(sqrt(WatBal->DaysSinceLastRain) - 
                    sqrt(WatBal->DaysSinceLastRain - 1)))* WatBal->ct.CorrFactor;
            WatBal->rt.EvapSoil = min(Evtra.MaxEvapSoil, 
                    min(CMaxSoilEvap + PERC,10*(WatBal->st.Moisture - WatBal->ct.MoistureAirDry)));
        }
    }
    
    // Water holding capacity of rooted and lower zone, at field capacity and at soil saturation (cm)
    CAP   = (WatBal->ct.MoistureFC - WatBal->st.Moisture) * Crop->st.RootDepth;
    CAPL  = (WatBal->ct.MoistureFC - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    CAP0  = (WatBal->ct.MoistureSAT - WatBal->st.Moisture) * Crop->st.RootDepth;
    CAPL0 = (WatBal->ct.MoistureSAT - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    // Effective percolation incl. ET losses, potential and next dependent on soil water holding capacity (cm/d)
    PERCP = PERC - WatBal->rt.EvapWater - WatBal->rt.Transpiration;
    PERC1=  min(WatBal->ct.KSUB + CAP0, PERCP);    
    
    // Water loss by surface runoff, final
    RUNOFF = RUNOFP + max(0.,PERCP - PERC1);
         
    // Rooted zone is filled up to field capacity and 
    // the excess amount is lost by percolation to lower zone
    if (CAP < PERC1) {
        PERC2= min(WatBal->ct.KSUB + CAPL0, PERC1 - CAP);
    }
    else {
        PERC2;
    }
    
    // Lower zone is filled up to field capacity and 
    // the excess amount is lost by drainage to subsoil
    if (CAPL < PERC2) 
    {
        PERC3= min(WatBal->ct.KSUB, PERC2 - CAPL);
    }
    else
    {
        PERC3= 0.;
    }
    
    
    
    
    
    
    
    
    /* Equilibrium amount of soil moisture in rooted zone*/
    WaterEq = WatBal->ct.MoistureFC * Crop->st.RootDepth;
    
    /* Percolation from rooted zone to subsoil equals amount of   */
    /* Excess moisture in rooted zone (not to exceed conductivity)*/
    Perc1 = limit(0., WatBal->ct.MaxPercolRTZ, 
            (WatBal->st.RootZoneMoisture - WaterEq) - 
            WatBal->rt.Transpiration - WatBal->rt.EvapSoil);
    
    /* Loss of water at the lower end of the maximum root zone */
    /* Equilibrium amount of soil moisture below rooted zone   */
    WELOW = WatBal->ct.MoistureFC * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    WatBal->rt.Loss  = limit (0., WatBal->ct.MaxPercolSubS, 
            (WatBal->st.MoistureLow - WELOW) + Perc1);
    
    /* For rice water losses are limited to K0/20 */
    if (Crop->prm.Airducts) 
        WatBal->rt.Loss = min(WatBal->rt.Loss, 0.05*WatBal->ct.KSUB);
    
    /* Percolation not to exceed uptake capacity of subsoil */
    Perc2 = ((Crop->prm.MaxRootingDepth - Crop->st.RootDepth) * WatBal->ct.MoistureSAT - 
            WatBal->st.Moisture) + WatBal->rt.Loss;
    
    WatBal->rt.Percolation = min(Perc1, Perc2);
   
    
    /* Adjustment of the infiltration rate */
    WatBal->rt.Infiltration = max(0, min(PERC,
          (WatBal->ct.MoistureSAT - WatBal->st.Moisture) * Crop->st.RootDepth + 
          WatBal->rt.Transpiration + WatBal->rt.EvapSoil + WatBal->rt.Percolation));
            
    /* Rates of change in amounts of moisture W and WLOW */
    WatBal->rt.RootZoneMoisture = -WatBal->rt.Transpiration - WatBal->rt.EvapSoil -  
            WatBal->rt.Percolation + WatBal->rt.Infiltration;
    WatBal->rt.MoistureLow = WatBal->rt.Percolation - WatBal->rt.Loss;             
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
            WatBal->rt.Infiltration);
    WatBal->st.SurfaceStorage = min(PreSurfaceStorage, 
            Site->MaxSurfaceStorage);
    WatBal->st.Runoff += PreSurfaceStorage - WatBal->st.SurfaceStorage;
    
    /* Water amount in the rooted zone */
    WatBal->st.RootZoneMoisture += WatBal->rt.RootZoneMoisture;
    if (WatBal->st.RootZoneMoisture < 0.) 
    {
       WatBal->st.EvapSoil += WatBal->st.RootZoneMoisture;
       WatBal->st.RootZoneMoisture = 0.;
    }
    
    /* Total percolation and loss of water by deep leaching */
    WatBal->st.Percolation += WatBal->rt.Percolation ;
    WatBal->st.Loss        += WatBal->rt.Loss;     
    
    WatBal->st.MoistureLow += WatBal->rt.MoistureLow;
   
    /* Change of root zone subsystem boundary                  */
    /* Calculation of amount of soil moisture in new root zone */
    if (Crop->st.RootDepth - Crop->st.RootDepth_prev > 0.001) 
    {
        
        /* water added to root zone by root growth, in cm   */
        WaterRootExt = WatBal->st.MoistureLow *
                (Crop->st.RootDepth - Crop->st.RootDepth_prev) / 
                (Crop->prm.MaxRootingDepth - Crop->st.RootDepth_prev);
        
        WaterRootExt = min( WaterRootExt,WatBal->st.MoistureLow);
                
        WatBal->st.MoistureLow -= WaterRootExt;

        /* Total water addition to root zone by root growth  */
        WatBal->st.WaterRootExt += WaterRootExt;

        /* Amount of soil moisture in extended root zone */
        WatBal->st.RootZoneMoisture += WaterRootExt;
    }

    /* Mean soil moisture content in rooted zone */
    WatBal->st.Moisture = WatBal->st.RootZoneMoisture/Crop->st.RootDepth;
    
    /* Store the infiltration rate of the previous day */
     WatBal->InfPreviousDay = WatBal->rt.Infiltration;
     
}