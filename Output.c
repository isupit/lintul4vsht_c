#include <stdio.h>
#include <stdlib.h>
#include "extern.h"
#include "lintul4.h"

void header(FILE *fp)
{
    fprintf(fp,"                Date   Date   DVS       WLV        WST          WSO         WRT         LAI     WSTRESS  SOILM    INF      Rain   NNI        PNI        KNI        NPKI  \n");
}
   
/*void Output(FILE *fp)
{    
    fprintf(fp,"%4d\t%3d\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
        MeteoYear[Day],
        MeteoDay[Day],
        Crop->st.Development,
        Crop->st.leaves,
        Crop->st.stems,
        Crop->st.storage,
        Crop->st.roots,
        Crop->st.LAI,
        WatBal->WaterStress,
        WatBal->st.Moisture,
        Rain[Day],
        WatBal->rt.Infiltration,
        WatBal->rt.RunOff,
        WatBal->rt.Loss,
        Crop->N_st.Indx,
        Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro);
}*/

void Output()
{
   printf("\t%4d\t%3d\t%5.2f\t%6.2f\t%6.2f\t%6.2f\t%6.2f\t%6.2f\t%7.2f\t%4.2f\t%5.2f\t%5.4f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
   MeteoYear[Day],
   MeteoDay[Day],
   Crop->st.Development,
   Crop->st.leaves,
   Crop->dst.leaves,
   Crop->st.stems,
   Crop->rt.stems, 
   Crop->st.storage,
   (Crop->st.leaves + Crop->dst.leaves + Crop->st.stems + Crop->dst.stems + Crop->st.storage),
   Crop->st.LAI,
   WatBal->WaterStress,
   WatBal->st.Moisture,
   Rain[Day],
   WatBal->rt.Infiltration,
   WatBal->rt.RunOff,
   WatBal->rt.Loss,
   Crop->N_st.Indx,
   Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro,
   Mng->rt.N_mins,
   Mng->st.N_mins,
   Mng->rt.N_tot,
   Mng->st.N_tot,
   Crop->N_st.Uptake);
}