#include <stdio.h>
#include <stdlib.h>
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------------------*/
/*  function NutrientLoss                                                     */
/*  Purpose: To calculate nutrient loss rate of dying of roots, stems leaves  */
/*           and storage organs (kg N ha-1 d-1)                               */
/* ---------------------------------------------------------------------------*/     

void NutrientLoss() 
{         
    Crop->N_rt.death_lv = Crop->prm.N_ResidualFrac_ro * Crop->drt.leaves;
    Crop->N_rt.death_st = Crop->prm.N_ResidualFrac_st * Crop->drt.stems;
    Crop->N_rt.death_ro = Crop->prm.N_ResidualFrac_lv * Crop->drt.roots;
}  