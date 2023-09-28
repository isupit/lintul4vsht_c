#include "extern.h"
#include <math.h>
#include "lintul4.h"



/*-------------------------------------------------------------------------------------*/
/* function InitializeWatBal                                                           */
/* Purpose: Initialization of soil moisture content in rooted and the lower zone [cm]  */
/*---------------------------------------------------------------------------*---------*/

void InitializeWatBal()
{   
    WatBal->rt.EvapWater = 0.;
    WatBal->rt.EvapSoil = 0.;
    WatBal->rt.Drainage = 0.;
    WatBal->rt.Infiltration = 0;
    WatBal->rt.RunOff  = 0.;
    WatBal->rt.Transpiration = 0.;
    WatBal->rt.TotalWaterRootZone = 0.;
    WatBal->rt.TotalWaterLowerZone = 0.;        
    WatBal->rt.AvailableRootZone = 0.;
    WatBal->rt.AvailableLowerZone = 0.;
    WatBal->rt.TotalETc = 0.;
    WatBal->st.TotalETc = 0.;
 
    WatBal->st.EvapWater = 0.;
    WatBal->st.EvapSoil = 0.;
    WatBal->st.Drainage = 0.;
    WatBal->st.Rain = 0.;
    WatBal->st.RunOff  = 0.;
    WatBal->st.Moisture = 0.;
    WatBal->st.MoistureLow = 0.;
    WatBal->st.Transpiration = 0.;
    WatBal->st.AvailableRootZone = 0.;
    WatBal->st.AvailableLowerZone = 0.;
    WatBal->st.TotalWaterRootZone = 0.;
    WatBal->st.TotalWaterLowerZone = 0.;        
    WatBal->st.AvailableRootZone = 0.;
    WatBal->st.AvailableLowerZone = 0.;
    WatBal->st.TotalETc = 0.;
    
    // Set max and initial rooting depth 
    Crop->prm.MaxRootingDepth = fminf(WatBal->ct.SoilMaxRootDepth, Crop->prm.MaxRootingDepth);
    Crop->st.RootDepth = Crop->prm.InitRootingDepth;
    Crop->rt.RootDepth = Crop->prm.MaxIncreaseRoot;
        
    // Assume no water stress at initialization
    WatBal->WaterStress = 1.;
    
    // Set the infiltration of the previous day to zero
    WatBal->InfPreviousDay = 0.;
    
    WatBal->st.Moisture    = fmaxf(WatBal->ct.MoistureWP, fminf(WatBal->ct.MoistureInit,WatBal->ct.MoistureFC));
    WatBal->st.MoistureLow = fmaxf(WatBal->ct.MoistureWP, fminf(WatBal->ct.MoistureInitLow,WatBal->ct.MoistureFC));
   
    // Initial soil moisture for a rice crop 
    if (Crop->prm.Airducts) {
        WatBal->st.Moisture = WatBal->ct.MoistureSAT; 
        WatBal->st.MoistureLow = WatBal->ct.MoistureSAT;
    }
       
    // Initial available moisture amount in rootable zone [cm]
    WatBal->st.AvailableRootZone = (WatBal->st.Moisture - WatBal->ct.MoistureWP) * Crop->st.RootDepth;
    
   // Initial available moisture amount between rooted zone and max.rooting depth [cm]
    WatBal->st.AvailableLowerZone  = (WatBal->st.MoistureLow - WatBal->ct.MoistureWP) * 
            (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    // Initial  total moisture amount in rootable zone [cm] 
    WatBal->st.TotalWaterRootZone = WatBal->st.Moisture * Crop->st.RootDepth;
    
   // Initial total moisture amount between rooted zone and max.rooting depth [cm] 
    WatBal->st.TotalWaterLowerZone = WatBal->st.MoistureLow * 
            (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    
    //  Soil evaporation, days since last rain
    WatBal->DaysSinceLastRain = 3.;
    if (WatBal->st.Moisture <= (WatBal->ct.MoistureWP + 
            0.5 * (WatBal->ct.MoistureFC - WatBal->ct.MoistureWP))) 
            WatBal->DaysSinceLastRain = 5.;   
}

/*---------------------------------------------------*/
/* function RateCalulationWatBal                     */
/* Purpose: Calculate the rate of the WatBal struct  */
/*---------------------------------------------------*/

void RateCalulationWatBal() {
    
    float CMaxSoilEvap;
    float Perc, Perc2, PercP;
    float CAP, CAPL, CAP0, CAPL0;
    float NotInf, RUNOFP;
    float AddedTotal, AddedAvailable;
    //Management *Mng;
    
    // Get the irrigation rate
    WatBal->rt.Irrigation = List(Mng->Irrigation);
         
    // Preliminary runoff rate
    NotInf = Afgen(WatBal->NotInfTB, &Rain[Day]);
    RUNOFP = NotInf * Rain[Day];
    
    // Water added to root zone by root growth (cm/d), resp. total and available water
    if (Crop->GrowthDay > 0) {
        AddedTotal =  Crop->rt.RootDepth * WatBal->st.MoistureLow;
        AddedAvailable = Crop->rt.RootDepth * (WatBal->st.MoistureLow - WatBal->ct.MoistureWP);
    }
    else {
        AddedTotal = 0.;
        AddedAvailable = 0.;
    }
        
    
    Perc = (1. - NotInf) * Rain[Day] + WatBal->rt.Irrigation;
    
    if (Perc >= 0.5) 
    {
        WatBal->rt.EvapSoil = Evtra.MaxEvapSoil;
        WatBal->DaysSinceLastRain = 1.;
    }
    else 
    {
        WatBal->DaysSinceLastRain++;
        CMaxSoilEvap = Evtra.MaxEvapSoil*limit(0.,1.,(sqrt(WatBal->DaysSinceLastRain) - 
                    sqrt(WatBal->DaysSinceLastRain - 1)))* WatBal->ct.CorrFactor;
        WatBal->rt.EvapSoil = fminf(Evtra.MaxEvapSoil, 
                    fminf(CMaxSoilEvap + Perc,10*(WatBal->st.Moisture - WatBal->ct.MoistureAirDry)));
    }
    
    // Water holding capacity of rooted and lower zone, at field capacity and at soil saturation (cm)
    CAP   = (WatBal->ct.MoistureFC - WatBal->st.Moisture) * Crop->st.RootDepth;
    CAP0  = (WatBal->ct.MoistureSAT - WatBal->st.Moisture) * Crop->st.RootDepth;
    if (Crop->prm.MaxRootingDepth - Crop->st.RootDepth > 0.) {
        CAPL  = (WatBal->ct.MoistureFC - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
        CAPL0 = (WatBal->ct.MoistureSAT - WatBal->st.MoistureLow) * (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    }
    else {
        CAPL  = 0.;
        CAPL0 = 0.;       
    }
    
    // Effective percolation incl. ET losses, potential and next dependent on soil water holding capacity (cm/d)
    PercP = Perc - WatBal->rt.EvapSoil - WatBal->rt.Transpiration;
    WatBal->rt.Infiltration=  fminf(WatBal->ct.KSUB + CAP0, PercP);    
    
    // Water loss by surface runoff, final
    WatBal->rt.RunOff = RUNOFP + fmaxf(0., PercP - WatBal->rt.Infiltration);
         
    // Rooted zone is filled up to field capacity and 
    // the excess amount is lost by percolation to lower zone
    if (CAP < WatBal->rt.Infiltration) {
        Perc2 = fminf(WatBal->ct.KSUB + CAPL0, WatBal->rt.Infiltration - CAP);
    }
    else {
        Perc2 = 0.;
    }
    
    // Lower zone is filled up to field capacity and 
    // the excess amount is lost by drainage to subsoil
    if (CAPL < Perc2) {
        WatBal->rt.Drainage = fminf(WatBal->ct.KSUB, Perc2 - CAPL);
    }
    else {
        WatBal->rt.Drainage= 0.;
    }
       
    // Change in total water and available water (DWAT) in rooted and lower zones
    WatBal->rt.TotalWaterRootZone  = WatBal->rt.Infiltration - Perc2 + AddedTotal;
    WatBal->rt.TotalWaterLowerZone = Perc2 - WatBal->rt.Drainage - AddedTotal;
    WatBal->rt.AvailableRootZone   = WatBal->rt.Infiltration - Perc2 + AddedAvailable;
    WatBal->rt.AvailableLowerZone  = Perc2 - WatBal->rt.Drainage - AddedAvailable;
    /*if (WatBal->rt.AvailableRootZone < 0.)
        printf("%7.4f %7.4f %7.4f\n",Perc,WatBal->rt.Infiltration,AddedAvailable);*/
}
    
    

/*-----------------------------------------------------*/
/* function IntegrationWatBal                          */
/* Purpose: integrate the waterbalance rates over time */
/* and calculate the water content in the rooted zone  */
/*-----------------------------------------------------*/

void IntegrationWatBal() 
{   
    WatBal->st.Transpiration += WatBal->rt.Transpiration;
    WatBal->st.EvapWater     += WatBal->rt.EvapWater;
    WatBal->st.EvapSoil      += WatBal->rt.EvapSoil;
    WatBal->st.Drainage      += WatBal->rt.Drainage;
    
    WatBal->st.TotalETc      += Penman.ETC;
    
    WatBal->st.Rain += Rain[Day];
    WatBal->st.Irrigation   += WatBal->rt.Irrigation;
    
    // Change in total water and available water (DWAT) in rooted and lower zones
    WatBal->st.TotalWaterRootZone   += WatBal->rt.TotalWaterRootZone;
    WatBal->st.TotalWaterLowerZone  += WatBal->rt.TotalWaterLowerZone;
    WatBal->st.AvailableRootZone    += WatBal->rt.AvailableRootZone;
    WatBal->st.AvailableLowerZone   += WatBal->rt.AvailableLowerZone;   
    
    WatBal->st.Moisture    = WatBal->st.TotalWaterRootZone / Crop->st.RootDepth; 
    if (Crop->prm.MaxRootingDepth - Crop->st.RootDepth > 0.) {
        WatBal->st.MoistureLow = WatBal->st.TotalWaterLowerZone / (Crop->prm.MaxRootingDepth - Crop->st.RootDepth);
    }
    else {
         WatBal->st.MoistureLow = 0.;
    }
}
