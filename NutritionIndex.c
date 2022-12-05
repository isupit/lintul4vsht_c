#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lintul4.h"
#include "extern.h"

/* --------------------------------------------------------------------*/
/*  function NutritionINDX()                                           */
/*  Purpose: To compute N Nutrition Index (-)                      */
/* --------------------------------------------------------------------*/
void NutritionINDX()
{    
    float VegetativeMass;
    
    float N_opt_veg;    
    float N_Veg;
    float N_res;
 
    /* Total vegetative living above-ground biomass (kg DM ha-1)     */
    VegetativeMass = Crop->st.leaves + Crop->st.stems;
    
    
    if (VegetativeMass > 0.)
    {
        /* N,P,K concentration in total vegetative living per */
        /* kg above-ground biomass  (kg N,P,K kg-1 DM)        */
        N_Veg  = (Crop->N_st.leaves + Crop->N_st.stems)/VegetativeMass;

        /* Residual N,P,K concentration in total vegetative living */
        /* above-ground biomass  (kg N,P,K kg-1 DM)                */
        N_res = (Crop->st.leaves * Crop->prm.N_ResidualFrac_lv +Crop->st.stems * Crop->prm.N_ResidualFrac_st)/VegetativeMass;
        N_opt_veg = (Crop->N_st.Optimum_lv + Crop->N_st.Optimum_st)/VegetativeMass;
    }
    
    
    float tiny=0.001;
    Crop->N_st.Indx = limit(tiny,1.0, ((N_Veg -N_res)/notnul(N_opt_veg - N_res)));
    
    /* Nutrient reduction factor */
    Crop->NutrientStress = limit(0., 1.0, 1.-Crop->prm.NLUE*pow((1.0001-Crop->N_st.Indx),2));
    //Crop->NutrientStress = 1.0;
}
