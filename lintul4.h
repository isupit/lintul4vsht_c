#include <time.h>

#ifndef LINTUL4_H
#define LINTUL4_H

#define FALSE 0
#define TRUE 1  

#define NR_VARIABLES_CRP	51
#define NR_TABLES_CRP   	20
#define NR_VARIABLES_SITE       12
#define NR_TABLES_SITE          1
#define NR_VARIABLES_SOIL       13
#define NR_VARIABLES_MANAGEMENT 2
#define NR_TABLES_MANAGEMENT    3
#define NUMBER_OF_TABLES        32
#define NR_SIMUNITS             4
#define MAX_STRING             2048
#define METEO_LENGTH           36600 //max 100 years 
#define DOMAIN_LENGTH          720   //max 0.5 degree

typedef struct TABLE {
	float x;
	float y;
	struct TABLE *next;
	} AFGEN;

        
typedef struct TBLD {
	int month;
	int day;
        float amount;
	struct TBLD *next;
	} TABLE_D;
        
        
typedef struct MANAGEMENT {
        /** Tables for fertilizer application and recovery fraction **/
        AFGEN *N_Fert_table;
        AFGEN *N_Uptake_frac;
        AFGEN *Irrigation;
        
        float N_Mins;
        float NRecoveryFrac;
        } Management;
Management *Mng;

typedef struct CONSTANTS {
        float MoistureAirDry;
        float MoistureFC;
        float MoistureWP;
        float MoistureSAT;
        float CriticalSoilAirC;
        float MoistureInit;
        float MoistureInitLow;
        float MaxPercolSubS;
        float MaxPercolRTZ;
        float SoilMaxRootDepth;
        float RunOffFrac;
        float CorrFactor;
        float K0;
        } Constants;

typedef struct PARAMETERS {
          /** Tables for the Crop simulations **/
        AFGEN *Roots;
        AFGEN *Stems;
        AFGEN *Leaves;
        AFGEN *Storage;

        AFGEN *PhotoDayLength;
        AFGEN *VernalizationRate;
        AFGEN *DeltaTempSum;
        AFGEN *SpecificLeaveArea;
        AFGEN *SpecificStemArea;
        AFGEN *KDiffuseTb;
        AFGEN *RadiationUseEff;
        AFGEN *ReductionRueDayTemp;
        AFGEN *ReductionRueLowTemp;
        AFGEN *CO2CorrectionRUE;
        AFGEN *CO2CorrectionTRA;
        AFGEN *DeathRateLeaves;
        AFGEN *DeathRateStems;
        AFGEN *DeathRateRoots; 
        
        /** Table for the maximum nutrient content in leaves as a function of DVS **/
        AFGEN *N_MaxLeaves;
        
        /** Table for the reduction of the grain formation as a function of **/
        /** the day time temperature **/
         AFGEN *ReductionGrainTemp;
         
        
        /** Table for the heat stress reduction factor for grain around anthesis **/
        /** as a function of temperature **/
        AFGEN *ReductionGrainHeat;
        
        /** Static Variables  **/
        /**  Emergence  **/
        float TempBaseEmergence;
        float TempEffMax;
        float TSumEmergence;                      	     

        /**  Phenology  **/
        int   IdentifyAnthesis; 
        float OptimumDaylength;	            
        float CriticalDaylength;
        float SatVernRequirement;
        float BaseVernRequirement;
        float TempSum1;       
        float TempSum2; 
        float InitialDVS;
        float DevelopStageEnd;  //Ripe or Harvest

        /** Initial Values  **/
        float InitialDryWeight;
        float LAIEmergence;
        float RelIncreaseLAI;

        /**  Green Area  **/
        float SpecificPodArea;
        float TempBaseLeaves;

        /** Stress due to shading **/
        float LAICr;

        /** Death Rates  **/
        float DeathLeavesDVS;
        float DeathRateLeavesShading;
        float DeathRateLeavesWaterStr;
        float DeathRateLeavesNStr;

        /** Water Use  **/
        float CorrectionTransp;
        float CropGroupNumber;
        float Airducts;

        /** Rooting **/
        float InitRootingDepth;
        float MaxIncreaseRoot;
        float MaxRootingDepth;
        
        /* DVS above roots stems and leaves die */
        float DVSRootsStemsDie;
        float DVSLeavesDie;

        /** Nutrients **/
        float DyingLeaves_N_Stress; 
        float DevelopmentStageNLimit; 
        float DevelopmentStageNT;
        float FracTranslocRoots;  
        float Opt_N_Frac;     
        float N_MaxRoots;   
        float N_MaxStems;   
        float NitrogenStressLAI;   
        float NLUE;   
        float Max_N_storage; 
        float N_lv_partitioning;  
        float NitrogenStessSLA;   
        float N_ResidualFrac_lv;  
        float N_ResidualFrac_st;  
        float N_ResidualFrac_ro;   
        float TCNT;     
        float N_fixation; 
        
        float IdentifySink;
        float IdentifyHeatStress;
        
        float FracStemsToStorage;
        
        /* Grain formation */
        float PotGrainformation;
        float MaxGrainMass;
        float VarA;
        float VarB;
        
        /* Heat stress */
        float DVSBeginHeatStr;
        float DVSFinalHeatStr;
        
        } Parameters;


typedef struct STATES {
        float EvapWater;
        float EvapSoil;
        float RunOff;
        float Infiltration;
        float SurfaceStorage;
        float Irrigation;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float Loss;
        float Rain;
        float RootZoneMoisture;
        float Runoff;
        float Transpiration;
        float WaterRootExt;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
        float Drainage;
        } States;
        

typedef struct RATES {
        float EvapWater;
        float EvapSoil;
        float RunOff;
        float Infiltration;
        float SurfaceStorage;
        float Irrigation;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float Loss;
        float RootZoneMoisture;
        float Runoff;
        float Transpiration;
        float WaterRootExt;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
        float Drainage;
        } Rates;
        
 
typedef struct NUTRIENT_RATES {
        float roots;
        float stems;
        float leaves;
        float storage;
        float Demand_lv;
        float Demand_st;
        float Demand_ro;
        float Demand_so;
        float Transloc;
        float Transloc_lv;
        float Transloc_st;
        float Transloc_ro;
        float Uptake;
        float Uptake_lv;
        float Uptake_st;
        float Uptake_ro;
        float death_lv;
        float death_st;
        float death_ro;
        } nutrient_rates;
        

typedef struct NUTRIENT_STATES {
        float roots;
        float stems;
        float leaves;
        float storage;
        float Max_lv;
        float Max_st;
        float Max_ro;
        float Max_so;
        float Optimum_lv;
        float Optimum_st;
        float Indx;
        float Uptake;
        float Uptake_lv;
        float Uptake_st;
        float Uptake_ro;
        float death_lv;
        float death_st;
        float death_ro;
        } nutrient_states;
        

typedef struct GROWTH_RATES {
        float roots;
        float stems;
        float leaves;
        float Development;
        float LAI;
        float LAIExp;
        float RootDepth;
        float storage;
        float vernalization;
} growth_rates;

typedef struct GROWTH_STATES {
        float roots;
        float stems;
        float leaves;
        float Development;
        float LAI;
        float LAIExp;
        float RootDepth;
        float RootDepth_prev;
        float storage;
        float vernalization;
        } growth_states;

        
typedef struct DYING_RATES {
        float roots;
        float stems;
        float leaves;
        float LAI;
        } dying_rates; 
        
typedef struct DYING_STATES {
        float roots;
        float stems;
        float leaves;
        float LAI;
        } dying_states; 


typedef struct PLANT {
        int Emergence;
        int Sowing;
        int GrowthDay;  
        int HeatFlag;
        int SeedFlag;
        float NPK_Indx;
        float NutrientStress;
        float DaysOxygenStress;
        float TSumEmergence;
        float fac_ro;
        float fac_lv;
        float fac_st;
        float fac_so;
        float Heat;
        float HeatDays;
        
        Parameters prm;
        
        growth_rates  rt;
        growth_states st;
        dying_rates   drt;
        dying_states  dst;
        
        nutrient_states N_st;
	nutrient_states P_st;
        nutrient_states K_st;
        
        nutrient_rates N_rt;
	nutrient_rates P_rt;
        nutrient_rates K_rt;            
        
	} Plant;    
Plant *Crop; /* Place holder for the current crop simulations */


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
Soil *WatBal; /* Place holder for the current water balance simulations */



typedef struct FIELD {
        /* Water related parameters */
        float FlagGroundWater;
        float InfRainDependent;
        float FlagDrains;  
        float InitSoilMoisture;
        float GroundwaterDepth;
        float DD;
        float MaxSurfaceStorage;  
        float SoilLimRootDepth;
        float NotInfiltrating;
        float SurfaceStorage;
        float MaxInitSoilM;
        
        /* Mineral states and rates */
        float st_N_tot;
        float st_N_mins;
        float rt_N_tot;
        float rt_N_mins;
 

        } Field;
Field *Site; /* Place holder for the current site simulations */




/* Simulation time */
struct tm simTime;
struct tm current_date;
       
float CO2;

/* Place holder for a simulation unit */
typedef struct SIMUNIT {
        Plant *crp;
        Field *ste;
        Management *mng;
        Soil  *soil;
        int emergence;
        int file;
        char start[MAX_STRING];
        char output[MAX_STRING];
        
        /* Statistics */
        float twso[31];
        
        struct SIMUNIT *next;
        } SimUnit; 
SimUnit *Grid;

enum{
    WEATHER_TMIN,
    WEATHER_TMAX,
    WEATHER_RADIATION,
    WEATHER_RAIN,
    WEATHER_WINDSPEED,
    WEATHER_VAPOUR,
    WEATHER_NTYPES
};

typedef struct WEATHER {
        char mask[MAX_STRING];
        char file[WEATHER_NTYPES][MAX_STRING];
        char type[WEATHER_NTYPES][MAX_STRING];
        char var[WEATHER_NTYPES][MAX_STRING];
        int StartYear;
        int EndYear;
        size_t nlat;
        size_t nlon;
        size_t ntime;
        struct WEATHER *next;
        } Weather;
Weather *Meteo; /* Place holder for the meteo filenames and lat/lon */

/** Meteorological Variables  **/
int Station, Year;
int MeteoYear[METEO_LENGTH];
int MeteoDay[METEO_LENGTH];
float CO2;
double Longitude[DOMAIN_LENGTH], Latitude[DOMAIN_LENGTH];
int **Mask;
int **Tsum1;
int **Tsum2;
float **Altitude;
float **AngstA;
float **AngstB;
float ***Tmin;
float ***Tmax;
float ***Radiation;
float ***Rain;
float ***Windspeed;
float ***Vapour;

/* Time step */
float Step;

             
#endif	// 

