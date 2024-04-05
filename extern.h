/* General global parameters */


#ifndef EXTERN_H
#define EXTERN_H

#include <stdio.h>
#include "lintul4.h"

/* General help functions */
extern float Afgen();
extern float List(TABLE_D *Table);
extern float limit(float a, float b, float c);
extern float notnul(float x);
extern float insw(float x1, float x2, float x3);
extern int leap_year(int year);
extern int GetSimInput(char *list);
extern void GetMeteoInput(char *meteolist);
extern void IfSowing();
extern void RatesToZero();
extern void Clean(SimUnit *Grid);
extern void header(FILE *fps);
extern void header_sum(FILE *fp);
extern void Output();
extern void Summary(FILE *fps);


/* Crop growth */
extern int Astro();
extern void CalcPenman();
extern void CalcPenmanMonteith();

extern void Clean();
extern void RateCalculationCrop();
extern void Growth(float NewPlantMaterial);
extern void IntegrationCrop();
extern void InitializeCrop();
extern void Partioning();
extern int  EmergenceCrop(int Emergence);

extern void DevelopmentRate();
extern float DailyTotalAssimilation();
extern void DyingOrgans();
extern float InstantAssimilation(float KDiffuse, float EFF, float AssimMax, float SinB, float PARDiffuse, float PARDirect);
extern float LeaveGrowth(float *shoots);
extern float LeaveAreaIndex();
extern float RespirationRef(float TotalAssimilation);

/* Nutrients */
extern void CropNutrientRates();
extern void InitializeNutrients();
extern void IntegrationNutrients();
extern void NutritionINDX();
extern void NutrientLoss();
extern void NutrientMax();
extern void NutrientPartioning(float *NutrientLimit);
extern void NutrientRates();
extern void NutrientOptimum();
extern void NutrientDemand();
extern void SoilNutrientRates();
extern void NutrientTranslocation();
extern void RateCalcultionNutrients();


/* Read data */
extern int GetAfgenTables();
extern int GetMeteoData(char *inputfile);
extern int FillAfgenTables();

extern void GetCropData(Plant *CROP, char *cropfile);
extern void FillCropVariables(Plant *CROP, float *Variable);
extern void FillSiteVariables();
extern void GetSoilData(Soil *SOIL, char *soilfile);
extern void FillSoilVariables(Soil *SOIL, float *Variable);
extern void GetManagement(Management *MNG, char *management);
extern void FillManageVariables(Management *MNG, float *Variable);

/* Water balance */
extern void InitializeWatBal();
extern void RateCalulationWatBal();
extern void IntegrationWatBal();
extern void EvapTra();

extern int Station, Year;
extern int MeteoYear[METEO_LENGTH];
extern int MeteoDay[METEO_LENGTH];
extern float CO2;
extern float AngstA;
extern float AngstB;
extern float Longitude, Latitude, Altitude;
extern float Tmin[METEO_LENGTH];
extern float Tmax[METEO_LENGTH];
extern float Radiation[METEO_LENGTH];
extern float Rain[METEO_LENGTH];
extern float Windspeed[METEO_LENGTH];
extern float Vapour[METEO_LENGTH];

extern int MeteoYear[METEO_LENGTH];
extern int MeteoDay[METEO_LENGTH];

extern float Temp;
extern size_t Day;
extern float DayTemp;
extern float AtmosphTransm;
extern float PARDaylength;

extern Weather *Meteo;
extern SimUnit *Grid;

extern struct tm simTime;
extern struct tm current_date;
extern struct tm start_date;
extern struct tm emergence_date;
extern struct tm anthesis_date;
extern struct tm maturity_date;

extern time_t date;
extern time_t start;
extern time_t emergence;
extern time_t anthesis;
extern time_t maturity;

#endif	// EXTERN_H

