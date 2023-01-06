#include <stdio.h>
#include <stdlib.h>
#include "extern.h"
#include "lintul4.h"

void header(FILE *fp)
{
    fprintf(fp,"                Date   Date   DVS       WLV        WST          WSO         WRT         LAI     WSTRESS  SOILM    INF      Rain   NNI        PNI        KNI        NPKI  \n");
}
   
void Output(FILE *fp)
{    
    fprintf(fp,"%7.2f\t%7.2f\t\t%4d\t%3d\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
        Latitude,
        Longitude,
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
}

