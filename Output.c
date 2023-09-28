#include "extern.h"
#include "timest.h"
#include "lintul4.h"


void header(FILE *fp)
{
//    fprintf(fp,"               Date   Date   DVS       WLV        WST          WSO         WRT         LAI     WSTRESS  SOILM    INF      Rain   NNI        PNI        KNI        NPKI  \n");
    fprintf(fp,"AgMIP_Wheat_4_CI\nModel: lintul4-vsht\nModeler_name: Iwan Supit & Joost Wolf\nSimulation:\nSite: %s\n",Grid->location);
    fprintf(fp,"Model\tYear\tDate\t      Treatment\tYield\tBiom\tLAI\tWDrain\tCumET\tSoilAvW\tRunoff\tTransp\tCroN\tNleac\tGrainN\tNmin\tNvol\tNimmo\tSoilN\t  Nden\t  cumPARi\n");
    fprintf(fp,"\t(YYYY)\t(YYYY-MM-DD)\t(-)\t(t/ha)\t(t/ha)\t(-)\t(mm)\t(mm)\t(mm)\t(mm)\t(mm)   (kgN/ha)(kgN/ha)\t(-)   (kgN/ha) (kgN/ha) (kgN/ha) (kgN/ha) (kgN/ha) (MJ/m²/d)\n");
}

void header_sum(FILE *fps)
{
    fprintf(fps,"AgMIP_Wheat_4_CI\nModel: lintul4-vsht\nModeler_name: Iwan Supit & Joost Wolf\nSimulation:\nSite: %s\n",Grid->location);
    fprintf(fps,"Model Planting.date\tTreatment Yield\tEmergence\tAnt\t\tMat\t\tFLN\tGNumber\t\t");
    fprintf(fps,"Biom-an\tBiom-ma\tMaxLAI\tWDrain\tCumET\tSoilAvW\tRunoff\tTransp\tCroN-an\t");
    fprintf(fps,"CroN-ma\tNleac\tGrainN\tNmin\tNvol\tNimmo\tSoilN\tNden\tcumPARi\n");
    fprintf(fps,"\t(YYYY-MM-DD)\t(-)\t(t/ha)\t(YYYY-MM-DD) (YYYY-MM-DD) (YYYY-MM-DD) ");
    fprintf(fps,"(leaf/mainstem)\t(grain/m2)\t(t/ha)\t(t/ha)\t(-)\t(mm)\t(mm)\t(mm)\t(mm)\t(mm)\t");
    fprintf(fps,"(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(kgN/ha)(MJ/m²)\n");
            
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

/*void Output()
{
     
   printf("%5d%5d%5.2f\t%6.2f\t%6.2f\t%8.2f\t%6.2f\t%6.2f\t%7.2f\t%4.2f\t%5.2f\t%5.4f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
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
   WatBal->rt.Irrigation,
   WatBal->rt.Infiltration,
   WatBal->rt.RunOff,
   WatBal->rt.Loss,
   Crop->N_st.Indx,
   Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro,
   Mng->rt.N_mins,
   Mng->st.N_mins,
   Mng->rt.N_tot,
   Mng->st.N_tot,
   Crop->N_st.Uptake,
   (Crop->N_st.leaves + Crop->N_st.stems + Crop->N_st.roots + Crop->N_st.storage),
   (Crop->N_st.death_lv + Crop->N_st.death_st + Crop->N_st.death_ro));
}*/

void Output(FILE *fp)
{   
   float AbTotBiomasse; //In-seaons total above ground biomass t/dm/ha
   float Cron;  //In-season total above ground nitrogen
   
   
   AbTotBiomasse = 0.001 * (Crop->st.leaves + Crop->dst.leaves + 
           Crop->st.stems + Crop->dst.stems + Crop->st.storage);  
   
   Cron = Crop->N_st.leaves + Crop->N_st.death_lv + 
          Crop->N_st.stems + Crop->N_st.death_st + 
          Crop->N_st.storage;
   
    if (Crop->st.Development > 0.99 && Crop->Anthesis == 0) {    
       anthesis_date.tm_year = MeteoYear[Day];
       anthesis_date.tm_mon  = current_date.tm_mon; 
       anthesis_date.tm_mday = current_date.tm_mday;
       anthesis = mktime(&emergence_date);
       
       Crop->CroN_an = Crop->N_st.leaves + Crop->N_st.death_lv + 
               Crop->N_st.stems + Crop->N_st.death_st + 
               Crop->N_st.storage;

       Crop->Biom_an = AbTotBiomasse;
       Crop->Anthesis = 1;
    } 
   
   if (Crop->st.LAI > Crop->MaxLAI)
       Crop->MaxLAI = Crop->st.LAI; 
   
   fprintf(fp,"LI\t%4d\t%4d-%02d-%02d\t%4s\t%5.2f\t%5.2f\t%4.2f\t%4.1f\t%4.1f\t%4.1f\t%4.1f\t%4.1f\t%4.1f\t na \t%4.1f\t %4.1f \t na \t  na \t %4.1f\t   na \t  %5.1f\n",
   MeteoYear[Day],
   MeteoYear[Day],
           current_date.tm_mon + 1,
           current_date.tm_mday,
   Grid->treatment,
   0.001 * Crop->st.storage,
   AbTotBiomasse,
   Crop->st.LAI,
   10*WatBal->st.Drainage,
   10*WatBal->st.TotalETc,
   10*WatBal->st.AvailableRootZone,
   10*WatBal->st.RunOff,
   10*WatBal->st.Transpiration,
   Cron,
   Crop->N_st.storage,
   Mng->st.N_mins_av,
   Mng->st.N_tot,  //Total of available N in the Soil
   Crop->st.ParIntercepted);
}
 
void Summary(FILE *fps){
       
    Crop->CroN_ma = Crop->N_st.leaves + Crop->N_st.death_lv + 
        Crop->N_st.stems + Crop->N_st.death_st + 
        Crop->N_st.storage;
    
    Crop->Biom_ma = 0.001 * (Crop->st.leaves + Crop->dst.leaves + 
           Crop->st.stems + Crop->dst.stems + Crop->st.storage);
    
    fprintf(fps,"LI\t%4d-%02d-%02d\t%4s\t%5.2f\t%4d-%02d-%02d\t%4d-%02d-%02d\t%4d-%02d-%02d\t",
    start_date.tm_year,
    start_date.tm_mon + 1,
    start_date.tm_mday,
    Grid->treatment,
    0.001 * Crop->st.storage,
    MeteoYear[Day],
    emergence_date.tm_mon + 1,
    emergence_date.tm_mday,
    anthesis_date.tm_year,
    anthesis_date.tm_mon + 1,
    anthesis_date.tm_mday,
    MeteoYear[Day],
    current_date.tm_mon + 1,
    current_date.tm_mday
    );
     
    fprintf(fps,"na\t%5.0f\t\t%4.1f\t%4.1f\t%4.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\tna\t",
    0.0001 * Crop->GrainNr, 
    Crop->Biom_an,
    Crop->Biom_ma,
    Crop->MaxLAI,
    10*WatBal->st.Drainage,
    10*WatBal->st.TotalETc,
    10*WatBal->st.AvailableRootZone,
    10*WatBal->st.RunOff,
    10*WatBal->st.Transpiration,
    Crop->CroN_an,
    Crop->CroN_ma
    );
    
    fprintf(fps,"%4.1f\t%4.1f\tna\tna\t%4.1f\tna\t%4.1f\n",
    Crop->N_st.storage,
    Mng->st.N_mins_av,
    Mng->st.N_tot,  //Total of available N in the Soil
    Crop->st.ParIntercepted        
    );
}
