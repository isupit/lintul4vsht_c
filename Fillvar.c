#include <stdio.h>
#include "lintul4.h"

/* ---------------------------------------------------------------------------*/
/*  function FillCropVariables(float *Variable)                               */
/*  Purpose: Fill the crop parameters that are read by GetCropData()          */
/* ---------------------------------------------------------------------------*/

void FillCropVariables(Plant *CROP, float *Variable)
{
    int i;
    CROP->prm.TempBaseEmergence        = Variable[0];
    CROP->prm.TempEffMax               = Variable[1];
    CROP->prm.TSumEmergence            = Variable[2];                      	     

    /**  Phenology  **/
    CROP->prm.IdentifyAnthesis         = (int) Variable[3]; 
     
    /** Switch if vernalization is accounted for **/
    if (CROP->prm.IdentifyAnthesis < 2)
    {
        CROP->prm.SatVernRequirement   = -99.;
        CROP->prm.BaseVernRequirement  = -99.;
    }
    else
    {
        CROP->prm.SatVernRequirement   = Variable[4];
        CROP->prm.BaseVernRequirement  = Variable[5];
    }        

    CROP->prm.TempSum1                 = Variable[6];       
    CROP->prm.TempSum2                 = Variable[7]; 
    CROP->prm.InitialDVS               = Variable[8];
    CROP->prm.DevelopStageEnd          = Variable[9];
    
    /** Initial Values  **/
    CROP->prm.InitialDryWeight         = Variable[10];
    CROP->prm.RelIncreaseLAI           = Variable[11];

    /**  Green Area  **/
    CROP->prm.SpecificPodArea          = Variable[12];
    CROP->prm.LAICr                    = Variable[13];
    CROP->prm.TempBaseLeaves           = Variable[14];

    /** Death Rates  **/
    CROP->prm.DeathRateLeavesWaterStr  = Variable[15];
    CROP->prm.DeathRateLeavesShading   = Variable[16];

    /** Water Use  **/
    CROP->prm.CorrectionTransp         = Variable[17];
    CROP->prm.CropGroupNumber          = Variable[18];
    CROP->prm.Airducts                 = Variable[19];
    
    /** Rooting **/
    /** Convert cm to mm */
    CROP->prm.InitRootingDepth         = Variable[20];
    CROP->prm.MaxIncreaseRoot          = Variable[21];
    CROP->prm.MaxRootingDepth          = Variable[22];
    
    CROP->prm.DVSRootsStemsDie         = Variable[23];
    CROP->prm.DVSLeavesDie             = Variable[24];

    /** Nutrients  **/
    CROP->prm.DyingLeaves_N_Stress     = Variable[25];
    CROP->prm.DevelopmentStageNLimit   = Variable[26];
    CROP->prm.DevelopmentStageNT       = Variable[27];
    CROP->prm.FracTranslocRoots        = Variable[28];
    CROP->prm.Opt_N_Frac               = Variable[29];
    CROP->prm.N_MaxRoots               = Variable[30];
    CROP->prm.N_MaxStems               = Variable[31];
    CROP->prm.NitrogenStressLAI        = Variable[32];                	     
    CROP->prm.NLUE                     = Variable[33];
    CROP->prm.Max_N_storage            = Variable[34];
    CROP->prm.N_lv_partitioning        = Variable[35];
    CROP->prm.NitrogenStessSLA         = Variable[36];
    CROP->prm.N_ResidualFrac_lv        = Variable[37];
    CROP->prm.N_ResidualFrac_st        = Variable[38];
    CROP->prm.N_ResidualFrac_ro        = Variable[39];
    CROP->prm.TCNT                     = Variable[40];
    CROP->prm.N_fixation               = Variable[41];
    
    /** Stem reserves **/
    CROP->prm.FracStemsToStorage       = Variable[42];
    
    CROP->prm.IdentifySink             = (int) Variable[43]; 
    
    /** Switch if sinks are accounted for **/
    if (CROP->prm.IdentifySink < 1)
    {
        CROP->prm.PotGrainformation   = -99.;
        CROP->prm.MaxGrainMass        = -99.;
        CROP->prm.VarA                = -99.;
        CROP->prm.VarB                = -99.;
    }
    else
    {
        CROP->prm.PotGrainformation   = Variable[44];
        CROP->prm.MaxGrainMass        = Variable[45];
        CROP->prm.VarA                = Variable[46];
        CROP->prm.VarB                = Variable[47];
    }   
    
    /* Heat Stress */
    CROP->prm.IdentifyHeatStress      = (int) Variable[48]; 
    
    if (CROP->prm.IdentifyHeatStress)
    {
        CROP->prm.DVSBeginHeatStr     = -99.9;
        CROP->prm.DVSFinalHeatStr     = -99.9;
    }
    else
    {
        CROP->prm.DVSBeginHeatStr     = Variable[49];
        CROP->prm.DVSFinalHeatStr     = Variable[50];
    }

    for (i=0;i<=NR_VARIABLES_CRP;i++) 
    {
        Variable[i] = 0.;
    }
}

/* ---------------------------------------------------------------------------*/
/*  function FillSoilVariables(float *Variable)                               */
/*  Purpose: Fill the soil parameters that are read by GetSoilData()          */
/* ---------------------------------------------------------------------------*/

void FillSoilVariables(Soil *SOIL, float *Variable) {
    int i;
    
    SOIL->ct.MoistureAirDry   = Variable[0];
    SOIL->ct.MoistureWP       = Variable[1];
    SOIL->ct.MoistureFC       = Variable[2];
    SOIL->ct.MoistureSAT      = Variable[3];
    SOIL->ct.CriticalSoilAirC = Variable[4];
    SOIL->ct.MoistureInit     = Variable[5];
    SOIL->ct.MoistureInitLow  = Variable[6];        
    SOIL->ct.SoilMaxRootDepth = Variable[7];
    SOIL->ct.RunOffFrac       = Variable[8];
    SOIL->ct.CorrFactor       = Variable[9];
    SOIL->ct.K0               = Variable[10];
    SOIL->ct.MaxPercolRTZ     = Variable[11];
    SOIL->ct.MaxPercolSubS    = Variable[12];
    
    /* No workability parameters will be used in this version */
    
    for (i=0;i<=NR_VARIABLES_SOIL;i++) 
    {
        Variable[i]= 0.;
    }
}


/* ---------------------------------------------------------------------------*/
/*  function FillSiteVariables(float *Variable)                               */
/*  Purpose: Fill the site parameters that are read by GetSiteData()          */
/* ---------------------------------------------------------------------------*/

void FillSiteVariables(Field *SITE, float *Variable) {
    int i;
   
    SITE->FlagGroundWater                 = Variable[0];
    SITE->InfRainDependent                = Variable[1];
    SITE->FlagDrains                      = Variable[2];
    SITE->MaxSurfaceStorage               = Variable[3];
    SITE->InitSoilMoisture                = Variable[4];
    SITE->GroundwaterDepth                = Variable[5];
    SITE->DD                              = Variable[6];
    SITE->SoilLimRootDepth                = Variable[7];
    SITE->NotInfiltrating                 = Variable[8];
    SITE->SurfaceStorage                  = Variable[9];
    SITE->MaxInitSoilM                    = Variable[10];
    
    CO2 = Variable[11];
       
    for (i=0;i<=NR_VARIABLES_SITE;i++) 
    {
        Variable[i]= 0.;
    }
}


/* ---------------------------------------------------------------------------*/
/*  function FillManageVariables(float *Variable)                             */
/*  Purpose: Fill the management parameters that are read by GetManagement()  */
/* ---------------------------------------------------------------------------*/

void FillManageVariables(Management *MNG, float *Variable) {
    int i;
    
    MNG->N_Mins                          = Variable[0];
    MNG->NRecoveryFrac                   = Variable[1];
    
    for (i=0;i<=NR_VARIABLES_MANAGEMENT;i++) 
    {
        Variable[i]= 0.;
    }
}
