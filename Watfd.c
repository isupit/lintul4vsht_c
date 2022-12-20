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
    Crop->rt.RootDepth = Crop->prm.MaxIncreaseRoot;
            
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
       
    /* Initial available moisture amount in rootable zone [cm] */
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
    float Perc, Perc2, Perc3, PercP;
    float CAP, CAPL, CAP0, CAPL0;
    float NotInf, RUNOFP;
    float AddedTotal, AddedAvailable;
   
    
    // Get the irrigation rate
    WatBal->rt.Irrigation = List(Mng->Irrigation);
         
    // Preliminary runoff rate
    NotInf = Afgen(WatBal->NotInfTB, &Rain[Day]);
    RUNOFP = NotInf * Rain[Day];
    
    // Water added to root zone by root growth (cm/d), resp. total and available water
    AddedTotal =  Crop->st.RootDepth * WatBal->st.MoistureLow;
    AddedAvailable = Crop->st.RootDepth * (WatBal->st.MoistureLow - WatBal->ct.MoistureWP);
    
    // Preliminary infiltration and rate 
    if (WatBal->st.SurfaceStorage <= 0.1) 
    {
        Perc = (1. - NotInf) * Rain[Day] + 
                WatBal->rt.Irrigation + WatBal->st.SurfaceStorage;
    }
    else 
    {
        // Surface storage, infiltration limited by maximum percolation
        // rate root zone 
        Available = WatBal->st.SurfaceStorage + (Rain[Day] * 
                (1. - WatBal->ct.RunOffFrac) + WatBal->rt.Irrigation 
                 - WatBal->rt.EvapSoil);
        Perc = min(WatBal->ct.MaxPercolRTZ, Available);
    }
        
    // If surface storage > 1 cm 
    if (WatBal->st.SurfaceStorage > 1.) 
    {
        WatBal->rt.EvapWater = Evtra.MaxEvapWater;
    }
    else 
    {
        if (WatBal->InfPreviousDay >= 1.) 
        {
            // If infiltration >= 1cm on previous day assume maximum soil evaporation
            WatBal->rt.EvapSoil = Evtra.MaxEvapSoil;
            WatBal->DaysSinceLastRain = 1.;
        }
        else 
        {
            WatBal->DaysSinceLastRain++;
            CMaxSoilEvap = Evtra.MaxEvapSoil*limit(0.,1.,(sqrt(WatBal->DaysSinceLastRain) - 
                    sqrt(WatBal->DaysSinceLastRain - 1)))* WatBal->ct.CorrFactor;
            WatBal->rt.EvapSoil = min(Evtra.MaxEvapSoil, 
                    min(CMaxSoilEvap + Perc,10*(WatBal->st.Moisture - WatBal->ct.MoistureAirDry)));
        }
    }
    
    // Water holding capacity of rooted and lower zone, at field capacity and at soil saturation (cm)
    CAP   = (WatBal->ct.MoistureFC - WatBal->st.Moisture) * Crop->st.RootDepth;
    CAPL  = (WatBal->ct.MoistureFC - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    CAP0  = (WatBal->ct.MoistureSAT - WatBal->st.Moisture) * Crop->st.RootDepth;
    CAPL0 = (WatBal->ct.MoistureSAT - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    // Effective percolation incl. ET losses, potential and next dependent on soil water holding capacity (cm/d)
    PercP = Perc - WatBal->rt.EvapWater - WatBal->rt.Transpiration;
    WatBal->rt.Infiltration=  min(WatBal->ct.KSUB + CAP0, PercP);    
    
    // Water loss by surface runoff, final
    WatBal->rt.RunOff = RUNOFP + max(0., PercP - WatBal->rt.Infiltration);
         
    // Rooted zone is filled up to field capacity and 
    // the excess amount is lost by percolation to lower zone
    if (CAP < WatBal->rt.Infiltration) {
        Perc2 = min(WatBal->ct.KSUB + CAPL0, WatBal->rt.Infiltration - CAP);
    }
    else {
        Perc2 = 0.;
    }
    
    // Lower zone is filled up to field capacity and 
    // the excess amount is lost by drainage to subsoil
    if (CAPL < Perc2) 
    {
        Perc3= min(WatBal->ct.KSUB, Perc2 - CAPL);
    }
    else
    {
        Perc3= 0.;
    }
    
    // Change in total water and available water (DWAT) in rooted and lower zones
    WatBal->rt.TotalWaterRootZone  = WatBal->rt.Infiltration - Perc2 + AddedTotal;
    WatBal->rt.TotalWaterLowerZone = Perc2 - Perc3 - AddedTotal;
    WatBal->rt.RootZoneMoisture    = WatBal->rt.Infiltration - Perc2 + AddedAvailable;
    WatBal->rt.MoistureLow         = Perc2 - Perc3 - AddedAvailable;
    
}
    
    

/*-----------------------------------------------------*/
/* function IntegrationWatBal                          */
/* Purpose: integrate the waterbalance rates over time */
/* and calculate the water content in the rooted zone  */
/*-----------------------------------------------------*/

void IntegrationWatBal() 
{
    float PreSurfaceStorage;
    
    WatBal->st.Transpiration += WatBal->rt.Transpiration;
    WatBal->st.EvapWater     += WatBal->rt.EvapWater;
    WatBal->st.EvapSoil      += WatBal->rt.EvapSoil;
    
    WatBal->st.Rain += Rain[Day];
    WatBal->st.Irrigation   += WatBal->rt.Irrigation;
    
    // Surface storage and runoff 
    PreSurfaceStorage = WatBal->st.SurfaceStorage + (Rain[Day] + 
            WatBal->rt.Irrigation - WatBal->rt.EvapWater - 
            WatBal->rt.Infiltration);
    WatBal->st.SurfaceStorage = min(PreSurfaceStorage, 
            Site->MaxSurfaceStorage);
    WatBal->st.RunOff += PreSurfaceStorage - WatBal->st.SurfaceStorage;
    
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
   
    /* Mean soil moisture content in rooted zone */
    WatBal->st.Moisture = WatBal->st.RootZoneMoisture/Crop->st.RootDepth;
    
    /* Store the infiltration rate of the previous day */
     WatBal->InfPreviousDay = WatBal->rt.Infiltration;
     
     
    Crop->rt.RootDepth = min(Crop->prm.MaxIncreaseRoot * insw(WatBal->WaterStress - 0.01, 0., 1.0), 
            Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    Crop->rt.RootDepth += Crop->rt.RootDepth;
     
}