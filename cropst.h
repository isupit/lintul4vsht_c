#include <time.h>

#ifndef CROPST_H
#define CROPST_H

typedef struct TABLE {
	float x;
	float y;
	struct TABLE *next;
	} AFGEN;
        
typedef struct PARAMETERS {
          /** Tables for the Crop simulations **/
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
        AFGEN *CO2TRATB;
        AFGEN *Roots;
        AFGEN *Leaves;
        AFGEN *Stems;
        AFGEN *Storage;
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
        float Fixation;
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
        float Fixation;
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
        float ParIntercepted;
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
        float ParIntercepted;
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
        int EmergenceFlag;
        int Sowing;
        int Anthesis;
        int GrowthDay;  
        int HeatFlag;
        int SeedFlag;
        int Seasons;
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
        float GrainNr;
        float CroN_an;
        float CroN_ma;
        float Biom_an;
        float Biom_ma;
        float MaxLAI;
        float HeatReduction;
        float DeltaTempSum;
        
        Parameters prm;
        
        growth_rates  rt;
        growth_states st;
        dying_rates   drt;
        dying_states  dst;
        
        nutrient_states N_st;      
        nutrient_rates N_rt;
        
	} Plant;    
	
extern Plant *Crop; /* Place holder for the current crop simulations */

#endif	// 

