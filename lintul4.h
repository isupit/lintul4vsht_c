#include <time.h>

#ifndef LINTUL4_H
#define LINTUL4_H

#define NR_VARIABLES_CRP	49
#define NR_TABLES_CRP   	20
#define NR_VARIABLES_SITE       12
#define NR_TABLES_SITE          1
#define NR_VARIABLES_SOIL       12
#define NR_VARIABLES_SOIL_USED  6
#define NR_TABLES_SOIL          2
#define NR_VARIABLES_MANAGEMENT 2
#define NR_TABLES_MANAGEMENT    3
#define NUMBER_OF_TABLES        32
#define NR_SIMUNITS             4

typedef struct TABLE {
	float x;
	float y;
	struct TABLE *next;
	} AFGEN;

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
        float SoilMaxRootDepth;
        float RunOffFrac;
        float CorrFactor;
        float KSUB;
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
        float DevelopStageHarvest;

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
        float DyingLeaves_NPK_Stress; 
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
        float NutrientStessSLA;   
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
        float Infiltration;
        float Irrigation;
        float Loss;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float Rain;
        float RootZoneMoisture;
        float Runoff;
        float SurfaceStorage;
        float Transpiration;
        float WaterRootExt;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
        } States;
        

typedef struct RATES {
        float EvapWater;
        float EvapSoil;
        float Infiltration;
        float Irrigation;
        float Loss;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float RootZoneMoisture;
        float Runoff;
        float SurfaceStorage;
        float Transpiration;
        float WaterRootExt;
        float TotalWaterRootZone;
        float TotalWaterLowerZone;
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
        float LAI;
        float LAIExp;
        float storage;
        float vernalization;
} growth_rates;

typedef struct GROWTH_STATES {
        float roots;
        float stems;
        float leaves;
        float LAI;
        float LAIExp;
        float storage;
        float vernalization;
        } growth_states;

        
typedef struct DYING_RATES {
        float roots;
        float stems;
        float leaves;
        float LAI;
        } dying_rates; 


typedef struct GREEN {
	float weight;
	float age;
	float area;
	struct GREEN *next;
	} Green;
        

typedef struct PLANT {
        int Emergence;
        int GrowthDay;
        float DevelopmentStage;
        float RootDepth;
        float RootDepth_prev;
        float NPK_Indx;
        float NutrientStress;
        float DaysOxygenStress;
        float TSumEmergence;
        
        Parameters prm;
        
        growth_rates  rt;
        growth_states st;
        dying_rates   drt;
        
        nutrient_states N_st;        
        nutrient_rates N_rt;
	
        Green *LeaveProperties;
	} Plant;    
Plant *Crop; /* Place holder for the current crop simulations */


typedef struct SOIL {
        float DaysSinceLastRain;
        float SoilMaxRootingDepth;
        float WaterStress;
        
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
        float MaxSurfaceStorage;     
        float InitSoilMoisture;
        float GroundwaterDepth;
        float DD;
        float SoilLimRootDepth;
        float NotInfiltrating;
        float SurfaceStorage;
        float MaxInitSoilM;
        
        /* Mineral states and rates */
        float st_N_tot;
        float st_N_mins;
        float rt_N_tot;
        float rt_N_mins;
 
        
        /** Table for the fraction of precipitation that does not infiltrate **/
        AFGEN *NotInfTB;
        } Field;
Field *Site; /* Place holder for the current site simulations */


/* Simulation time */
struct tm simTime;


/* Place holder for a simulation unit */
typedef struct SIMUNIT {
        Plant *crp;
        Field *ste;
        Management *mng;
        Soil  *soil;
        int start;
        int emergence;
        int file;
        char name[100]; 
        struct SIMUNIT *next;
        } SimUnit;
        
float CO2;

/** Meteorological Variables  **/
int Station, Year;
float AngstA;
float AngstB;
float Longitude, Latitude, Altitude;
float Tmin[732], Tmax[732], Radiation[732], Rain[732];
float Windspeed[732], Vapour[732];

/* Time step */
float Step;

             
#endif	// 

