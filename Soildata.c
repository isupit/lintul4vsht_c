#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lintul4.h"
#include "soil.h"


void GetSoilData(Soil *SOIL, char *soilfile)
{
  int i, c;
  float Variable[100], XValue, YValue;
  char x[2], xx[2],  word[100];
  FILE *fq;

 if ((fq = fopen(soilfile, "rt")) == NULL)
 {
     fprintf(stderr, "Cannot open input file.\n"); 
     exit(0);
 }

 i=0;
  while ((c=fscanf(fq,"%s",word)) != EOF && i < 12 ) 
  {
    if (!strcmp(word, SoilParam[i])) {
        while ((c=fgetc(fq)) !='=');
	fscanf(fq,"%f",  &Variable[i]);

	i++; 
       }  
  }

 if (i != NR_VARIABLES_SOIL) 
 {
    fprintf(stderr, "Something wrong with the Soil variables.\n"); 
    exit(0);
 }
 
  rewind(fq);  
  
  FillSoilVariables(SOIL, Variable);
 
  fclose(fq);

 if (i!= NR_TABLES_SOIL) 
 {
    fprintf(stderr, "Something wrong with the Soil tables.\n"); 
    exit(0);
 }
  
    /* Set state variables of the water balance are set to zero. */   
    SOIL->st.EvapWater         = 0.;
    SOIL->st.EvapSoil          = 0.;
    SOIL->st.Infiltration      = 0.;
    SOIL->st.Irrigation        = 0.;
    SOIL->st.Loss              = 0.;
    SOIL->st.Moisture          = 0.;
    SOIL->st.MoistureLOW       = 0.;
    SOIL->st.Percolation       = 0.;
    SOIL->st.Rain              = 0.;
    SOIL->st.RootZoneMoisture  = 0.;
    SOIL->st.Runoff            = 0.;
    SOIL->st.Transpiration     = 0.;
    SOIL->st.WaterRootExt      = 0.;
    
    SOIL->rt.EvapWater         = 0.;
    SOIL->rt.EvapSoil          = 0.;   
    SOIL->rt.Infiltration      = 0.;
    SOIL->rt.Irrigation        = 0.;
    SOIL->rt.Loss              = 0.;
    SOIL->rt.Moisture          = 0.;
    SOIL->rt.MoistureLOW       = 0.;
    SOIL->rt.Percolation       = 0.;
    SOIL->rt.RootZoneMoisture  = 0.;
    SOIL->rt.Runoff            = 0.;
    SOIL->rt.WaterRootExt      = 0.;
    SOIL->rt.RootZoneMoisture  = 0.;
  
}

