
#ifndef WATBAL_H
#define WATBAL_H
        
typedef struct CONSTANTS {
        float MoistureAirDry;
        float MoistureFC;
        float MoistureWP;
        float MoistureSAT;
        float CriticalSoilAirC;
        float MoistureInit;
        float MoistureInitLow;
        float SoilMaxRootDepth;
        float CorrFactor;
        float KSUB;
        } Constants;

typedef struct STATES {
        float EvapWater;
        float EvapSoil;
        float RunOff;
        float Infiltration;
        float SurfaceStorage;
        float Irrigation;
        float Moisture;
        float MoistureLow;
        float Percolation;
        float Loss;
        float Rain;
        float Transpiration;
        float WaterRootExt;
        float AvailableRootZone;
        float AvailableLowerZone;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
        float Drainage;
        float TotalETc;
        } States;
        

typedef struct RATES {
        float EvapWater;
        float EvapSoil;
        float RunOff;
        float Infiltration;
        float SurfaceStorage;
        float Irrigation;
        float Percolation;
        float Loss;
        float Transpiration;
        float WaterRootExt;
        float AvailableRootZone;
        float AvailableLowerZone;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
        float Drainage;
        float TotalETc;
        } Rates;

typedef struct SOIL {
        float DaysSinceLastRain;
        float SoilMaxRootingDepth;
        float WaterStress;
        float InfPreviousDay;
        
        AFGEN *NotInfTB;
    
        Constants ct;
        States st;
        Rates rt;
        } Soil;
        
extern Soil *WatBal;

#endif	// 

