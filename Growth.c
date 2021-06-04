#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lintul4.h"
#include "extern.h"

void Partioning()
{
    float factor;
    float flv;
       
    if (WatBal->WaterStress < Crop->N_st.Indx)
    {
        factor = max(1., 1./(WatBal->WaterStress + 0.5));
        Crop->fac_ro = min(0.6, Afgen(Crop->prm.Roots, &(Crop->st.Development)) * factor);
        Crop->fac_lv = Afgen(Crop->prm.Leaves, &(Crop->st.Development));
        Crop->fac_st = Afgen(Crop->prm.Stems, &(Crop->st.Development));
        Crop->fac_so = Afgen(Crop->prm.Storage, &(Crop->st.Development));
    }
    else
    {
        flv = Afgen(Crop->prm.Leaves, &(Crop->st.Development));
        factor = exp(-Crop->prm.N_lv_partitioning * ( 1. - Crop->N_st.Indx));
        Crop->fac_lv = flv * factor;
        Crop->fac_ro = Afgen(Crop->prm.Roots, &(Crop->st.Development));
        Crop->fac_st = Afgen(Crop->prm.Stems, &(Crop->st.Development)) + flv - Crop->fac_lv;
        Crop->fac_so = Afgen(Crop->prm.Storage, &(Crop->st.Development));
    }
}	

/* -----------------------------------------------------------------------------*/
/*  function HeatStess()                                                        */
/*  Purpose:  Calculation of the mean day-time temperature during the sensitive */
/*  period around anthesis (between DVSBeginHeatStr and DVSFinalHeatStr)        */
/* -----------------------------------------------------------------------------*/
void HeatStress()
{   
    if (Crop->st.Development >= Crop->prm.DVSBeginHeatStr && Crop->st.Development <= Crop->prm.DVSFinalHeatStr) 
    {
        Crop->Heat += DayTemp;
        Crop->HeatDays++;
    }
    
    if (Crop->st.Development >= Crop->prm.DVSFinalHeatStr && !Crop->HeatFlag) 
    {
           Crop->Heat= Crop->Heat/(float)Crop->HeatDays;
           Crop->HeatFlag = TRUE;
    }
}

/* ---------------------------------------------------------------------------*/
/*  function Growth(float NewPlantMaterial)                                   */
/*  Purpose: Establish growth rates of the plant organs (kg ha-1 d-1) and     */
/*  rooting depth (cm)                                                        */
/* ---------------------------------------------------------------------------*/

void Growth(float NewPlantMaterial)
{
    float shoots;
    float Fraction_ro;
    float Fraction_lv;
    float Fraction_st;
    float Fraction_so;
    float Translocatable;
    float GrainNr;
    
    float rt_GrainMass;
    float PotGrainMass;
    float MaxGrainMass;
        
    Partioning(&Fraction_ro, &Fraction_lv, &Fraction_st, &Fraction_so);
    
    DyingOrgans();
    
    shoots  = NewPlantMaterial * (1-Crop->fac_ro);
	    
    
    if (Crop->prm.IdentifyHeatStress) HeatStress();
    
     /* Available stem reserves for translocation (kg/ha/d) */
    if (Crop->st.Development >= 1.0) 
        Translocatable = (Crop->st.stems + Crop->dst.stems) * Crop->rt.Development * Crop->prm.FracStemsToStorage;
    else 
        Translocatable = 0.;
           
    Crop->rt.storage = shoots * Fraction_so + Translocatable;
     
    shoots = NewPlantMaterial * (1. - Fraction_ro);
    if (Crop->prm.IdentifySink)
    {
        Crop->rt.stems   = shoots * Fraction_st - Crop->drt.stems - Translocatable;
        Crop->rt.storage = shoots * Fraction_so + Translocatable;
        
        /* Correct for heat stress around anthesis, number of sinks not yet set */
        if (!Crop->SeedFlag && Crop->HeatFlag) 
        {
            /* Number of grains (per ha) as determined from total leaf and stem */
            /* dry weight at anthesis corrected for heat stress around anthesis */
            GrainNr = Afgen(Crop->prm.ReductionGrainHeat, &Crop->Heat) * 
                    (Crop->prm.VarA + Crop->prm.VarB * (Crop->st.leaves + Crop->st.stems));
            
            /* The number of sinks is established */
            Crop->SeedFlag = TRUE;
            
            /* Grain growth limited by both maximal grain mass (MaxGrainMass) */
            /* and by potential growth of the grains (PotGrainMass)           */
            PotGrainMass = Afgen(Crop->prm.ReductionGrainTemp, &DayTemp) * GrainNr * Crop->prm.PotGrainformation;
            MaxGrainMass = max (0.0, GrainNr * Crop->prm.MaxGrainMass - Crop->st.storage);
            rt_GrainMass = min (MaxGrainMass, PotGrainMass);
            
            /* Source or sink limitation  */
            Crop->rt.storage = min(Crop->rt.storage, rt_GrainMass);
            
            /* Correction in case of sink limitation */
            if (rt_GrainMass < Crop->rt.storage) 
            {
              Crop->rt.stems -= (Crop->rt.storage - rt_GrainMass);   
            }       
        }
    }
      
    Crop->rt.roots   = NewPlantMaterial * Fraction_ro - Crop->drt.roots;
    Crop->rt.storage = shoots * Fraction_so;
	
    Crop->rt.leaves  = shoots * Fraction_lv -  Crop->drt.leaves;
    Crop->rt.LAI     = LeaveGrowth(&Crop->rt.leaves);	
    
    Crop->rt.stems   = shoots * Fraction_st - Crop->drt.stems;
    
    /* No Root growth if no assimilates are partitioned to the roots or if */
    /* the crop has no airducts and the roots are close to the groundwater */
    if (Fraction_ro <= 0.0 || (!Crop->prm.Airducts && (Site->GroundwaterDepth - Crop->st.RootDepth) < 10.))
        Crop->rt.RootDepth = 0.;
    else
        Crop->rt.RootDepth = min(Crop->prm.MaxRootingDepth - Crop->st.RootDepth,
                Crop->prm.MaxIncreaseRoot * Step);
    
}	
