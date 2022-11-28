#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"

/* ---------------------------------------------------------------*/
/*  function Clean()                                              */
/*  Purpose: free all the allocated memory and set nodes to NULL  */
/* ---------------------------------------------------------------*/ 

void Clean(SimUnit *Grid)
{
    SimUnit *initial, *GridHead;
    AFGEN *head;
    
    /* Store pointer of the beginning of the list */
    initial = Grid;
 
    /* For each node the Afgen tables and the Leaves have to be freed before */
    /* the individual nodes will be freed.                                   */
    while (Grid)
    {
        while(Grid->crp->prm.PhotoDayLength)
        {
            head = Grid->crp->prm.PhotoDayLength;
            Grid->crp->prm.PhotoDayLength = Grid->crp->prm.PhotoDayLength->next;
            free(head);
        }
        free(Grid->crp->prm.PhotoDayLength);
        Grid->crp->prm.PhotoDayLength = NULL;
        
        while(Grid->crp->prm.VernalizationRate)
        {
            head = Grid->crp->prm.VernalizationRate;
            Grid->crp->prm.VernalizationRate = Grid->crp->prm.VernalizationRate->next;
            free(head);
        }
        free(Grid->crp->prm.VernalizationRate);
        Grid->crp->prm.VernalizationRate = NULL;
        
        /* Free all the Afgen tables */
        while(Grid->crp->prm.DeltaTempSum)
        {
            head = Grid->crp->prm.DeltaTempSum;
            Grid->crp->prm.DeltaTempSum = Grid->crp->prm.DeltaTempSum->next;
            free(head);
        }
        free(Grid->crp->prm.DeltaTempSum);
        Grid->crp->prm.DeltaTempSum = NULL;


        while(Grid->crp->prm.SpecificLeaveArea)
        {
            head = Grid->crp->prm.SpecificLeaveArea;
            Grid->crp->prm.SpecificLeaveArea = Grid->crp->prm.SpecificLeaveArea->next;
            free(head);
        }
        free(Grid->crp->prm.SpecificLeaveArea);
        Grid->crp->prm.SpecificLeaveArea = NULL;


        while(Grid->crp->prm.SpecificStemArea)
        {
            head = Grid->crp->prm.SpecificStemArea;
            Grid->crp->prm.SpecificStemArea = Grid->crp->prm.SpecificStemArea->next;
            free(head);
        }
        free(Grid->crp->prm.SpecificStemArea);
        Grid->crp->prm.SpecificStemArea = NULL;


        while(Grid->crp->prm.KDiffuseTb)
        {
            head = Grid->crp->prm.KDiffuseTb;
            Grid->crp->prm.KDiffuseTb = Grid->crp->prm.KDiffuseTb->next;
            free(head);
        }
        free(Grid->crp->prm.KDiffuseTb);
        Grid->crp->prm.KDiffuseTb = NULL;



        while(Grid->crp->prm.RadiationUseEff)
        {
            head = Grid->crp->prm.RadiationUseEff;
            Grid->crp->prm.RadiationUseEff = Grid->crp->prm.RadiationUseEff->next;
            free(head);
        }
        free(Grid->crp->prm.RadiationUseEff);
        Grid->crp->prm.RadiationUseEff = NULL;

        while(Grid->crp->prm.ReductionRueDayTemp)
        {
            head = Grid->crp->prm.ReductionRueDayTemp;
            Grid->crp->prm.ReductionRueDayTemp = Grid->crp->prm.ReductionRueDayTemp->next;
            free(head);
        }
        free(Grid->crp->prm.ReductionRueDayTemp);
        Grid->crp->prm.ReductionRueDayTemp = NULL; 

        while(Grid->crp->prm.ReductionRueLowTemp)
        {
            head = Grid->crp->prm.ReductionRueLowTemp;
            Grid->crp->prm.ReductionRueLowTemp = Grid->crp->prm.ReductionRueLowTemp->next;
            free(head);
        }
        free(Grid->crp->prm.ReductionRueLowTemp);
        Grid->crp->prm.ReductionRueLowTemp = NULL;


        while(Grid->crp->prm.CO2CorrectionRUE)
        {
            head = Grid->crp->prm.CO2CorrectionRUE;
            Grid->crp->prm.CO2CorrectionRUE = Grid->crp->prm.CO2CorrectionRUE->next;
            free(head);
        }
        free(Grid->crp->prm.CO2CorrectionRUE);
        Grid->crp->prm.CO2CorrectionRUE = NULL;


        while(Grid->crp->prm.DeathRateLeaves)
        {
            head = Grid->crp->prm.DeathRateLeaves;
            Grid->crp->prm.DeathRateLeaves = Grid->crp->prm.DeathRateLeaves->next;
            free(head);
        }
        free(Grid->crp->prm.DeathRateLeaves);
        Grid->crp->prm.DeathRateLeaves = NULL;


         while(Grid->crp->prm.DeathRateStems)
        {
            head = Grid->crp->prm.DeathRateStems;
            Grid->crp->prm.DeathRateStems = Grid->crp->prm.DeathRateStems->next;
            free(head);
        }
        free(Grid->crp->prm.DeathRateStems);
        Grid->crp->prm.DeathRateStems = NULL;


        while(Grid->crp->prm.DeathRateRoots)
        {
            head = Grid->crp->prm.DeathRateRoots;
            Grid->crp->prm.DeathRateRoots = Grid->crp->prm.DeathRateRoots->next;
            free(head);
        }
        free(Grid->crp->prm.DeathRateRoots);
        Grid->crp->prm.DeathRateRoots = NULL;


        while(Grid->crp->prm.Roots)
        {
            head = Grid->crp->prm.Roots;
            Grid->crp->prm.Roots = Grid->crp->prm.Roots->next;
            free(head);
        }
        free(Grid->crp->prm.Roots);
        Grid->crp->prm.Roots = NULL;


        while(Grid->crp->prm.Leaves)
        {
            head = Grid->crp->prm.Leaves;
            Grid->crp->prm.Leaves = Grid->crp->prm.Leaves->next;
            free(head);
        }
        free(Grid->crp->prm.Leaves);
        Grid->crp->prm.Leaves = NULL;


         while(Grid->crp->prm.Stems)
        {
            head = Grid->crp->prm.Stems;
            Grid->crp->prm.Stems = Grid->crp->prm.Stems->next;
            free(head);
        }
        free(Grid->crp->prm.Stems);
        Grid->crp->prm.Stems = NULL;


        while(Grid->crp->prm.Storage)
        {
            head = Grid->crp->prm.Storage;
            Grid->crp->prm.Storage = Grid->crp->prm.Storage->next;
            free(head);
        }
        free(Grid->crp->prm.Storage);
        Grid->crp->prm.Storage = NULL;

        
        while(Grid->crp->prm.N_MaxLeaves)
        {
            head = Grid->crp->prm.N_MaxLeaves;
            Grid->crp->prm.N_MaxLeaves = Grid->crp->prm.N_MaxLeaves->next;
            free(head);
        }
        free(Grid->crp->prm.N_MaxLeaves);
        Grid->crp->prm.N_MaxLeaves = NULL;

        
        while(Grid->crp->prm.ReductionGrainTemp)
        {
            head = Grid->crp->prm.ReductionGrainTemp;
            Grid->crp->prm.ReductionGrainTemp = Grid->crp->prm.ReductionGrainTemp->next;
            free(head);
        }
        free(Grid->crp->prm.ReductionGrainTemp);
        Grid->crp->prm.ReductionGrainTemp = NULL;        
        

        while(Grid->crp->prm.ReductionGrainHeat)
        {
            head = Grid->crp->prm.ReductionGrainHeat;
            Grid->crp->prm.ReductionGrainHeat = Grid->crp->prm.ReductionGrainHeat->next;
            free(head);
        }
        free(Grid->crp->prm.ReductionGrainHeat);
        Grid->crp->prm.ReductionGrainHeat = NULL;


        while(Grid->mng->N_Fert_table)
        {
            head = Grid->mng->N_Fert_table;
            Grid->mng->N_Fert_table = Grid->mng->N_Fert_table->next;
            free(head);
        }
        free(Grid->mng->N_Fert_table);
        Grid->mng->N_Fert_table = NULL;

        while(Grid->mng->Irrigation)        
        {
            head = Grid->mng->Irrigation;
            Grid->mng->Irrigation = Grid->mng->Irrigation->next;
            free(head);
        }
        free(Grid->mng->Irrigation);
        Grid->mng->Irrigation = NULL;
        
        /* Go to the next node */
        Grid = Grid->next;
    }

    Grid = initial;
    while (Grid)
    {
       GridHead = Grid;
       free( Grid->crp);
       free(Grid->mng);
       free(Grid->soil);
       free(Grid->ste);

       Grid->crp = NULL;
       Grid->mng = NULL;
       Grid->soil = NULL;
       Grid->ste = NULL;

       Grid = Grid->next;
       free(GridHead);
    }

    Grid = initial = NULL;
}

void CleanMeteo(Weather * Meteo)
{
    size_t j, k;
    for (j = 0; j < Meteo->nlon; j++) {
        for (k = 0; k < Meteo->nlat; k++) {
            free(Tmin[j][k]);
            free(Tmax[j][k]);
            free(Radiation[j][k]);
            free(Rain[j][k]);
            free(Windspeed[j][k]);
            free(Vapour[j][k]);
        }
        free(Tmin[j]);
        free(Tmax[j]);
        free(Radiation[j]);
        free(Rain[j]);
        free(Windspeed[j]);
        free(Vapour[j]);
        
        free(AngstA[j]);
        free(AngstB[j]);
        free(Altitude[j]);
        free(Mask[j]);
    }
    free(Tmin);
    free(Tmax);
    free(Radiation);
    free(Rain);
    free(Windspeed);
    free(Vapour);
        
    free(AngstA);
    free(AngstB);
    free(Altitude);
    free(Mask);
}