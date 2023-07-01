#include "extern.h"
#include <string.h>
#include <stdlib.h>
#include "lintul4.h"
#include "astro.h"
#include "timest.h"


int Station, Year;
int MeteoYear[METEO_LENGTH];
int MeteoDay[METEO_LENGTH];

float CO2;
float AngstA;
float AngstB;
float Longitude, Latitude, Altitude;
float Tmin[METEO_LENGTH];
float Tmax[METEO_LENGTH];
float Radiation[METEO_LENGTH];
float Rain[METEO_LENGTH];
float Windspeed[METEO_LENGTH];
float Vapour[METEO_LENGTH];

size_t Day;
float Temp;
float DayTemp;

Management *Mng;
Soil *WatBal;
Weather *Meteo; 
Etp Penman;
EVP Evtra;
SimUnit *Grid;

int main(int argc, char **argv)
{
    FILE **output;
    
    SimUnit *initial  = NULL;
    //Weather *Meteo = NULL;
    Weather *head;
      
    int CycleLength   = 300;
    int NumberOfFiles = 0;
    int Emergence;
    int Option = 0;
    
    int month, start_day;
    
    char list[MAX_STRING];
    char meteolist[MAX_STRING];
    char name[MAX_STRING];
    
    if (argc != 3) exit(0);
    if (strlen(argv[1]) >= MAX_STRING) exit(0);
    if (strlen(argv[2]) >= MAX_STRING) exit(0);
    
    memset(list,'\0',MAX_STRING);
    memset(meteolist,'\0',MAX_STRING);
    
    strncpy(list,argv[1],strlen(argv[1]));
    strncpy(meteolist,argv[2],strlen(argv[2]));
    
    // Fill the crop, soil, site and management place holders
    NumberOfFiles = GetSimInput(list);
    
    // Set the initial Grid address 
    initial = Grid;    
    
    // Get the meteo filenames and put them in the placeholder
    GetMeteoInput(meteolist);
    
    // Allocate memory for the file pointers 
    output = malloc(sizeof(**output) * NumberOfFiles);
   
    // Open the output files
    while (Grid)
    {   // Make valgrind happy 
        memset(name,'\0',MAX_STRING);
        strncpy(name, Grid->output,strlen(Grid->output));
           
        output[Grid->file] = fopen(name, "w");
        header(output[Grid->file]);
        Grid = Grid->next;
    }
    
    // Go back to the beginning of the list
    Grid = initial;
    
    while (Meteo)
    {
        // Get the meteodata 
        GetMeteoData(Meteo->file);
        
        for (Day = 1; Day < METEO_LENGTH; Day++) //assume that the series start January first
        {                   
            // Go back to the beginning of the list 
            Grid = initial;
            
            // Set the date struct 
            memset(&current_date, 0, sizeof(current_date)); 
            current_date.tm_year = MeteoYear[Day] -1900;
            current_date.tm_mday =  MeteoDay[Day];
            date = mktime(&current_date);
            
            //Set the sowing/emergence date struct
            sscanf(Grid->start, "%d-%d", &month, &start_day);
            start_date.tm_year = MeteoYear[Day];
            start_date.tm_mon = month -1; 
            start_date.tm_mday = start_day;
            start = mktime(&start_date);
            
            while (Grid)
            {
                // Get data, states and rates from the Grid structure and 
                // put them in the place holders 
                Crop      = Grid->crp;
                WatBal    = Grid->soil;
                Mng       = Grid->mng;
                Emergence = Grid->emergence;
                Option    = Grid->option;
                 
                Temp = 0.5 * (Tmax[Day] + Tmin[Day]);
                DayTemp = 0.5 * (Tmax[Day] + Temp);
                
                // Only simulate between start and end year 
                if ( MeteoYear[Day] >=  Meteo->StartYear && Meteo->Seasons  >= Crop->Seasons) {   
                    
                    // Determine if the starting date for the simulations already has occurred 
                    if (start_date.tm_yday == current_date.tm_yday) {
                        
                        // Initialize: set state variables 
                        InitializeCrop();
                        InitializeWatBal();
                        InitializeNutrients();
                        
                        Crop->Sowing = 1;
                        
                        if (Emergence) {
                            Crop->Emergence = 1;
                        }
                        else {
                            Crop->Emergence = 0;
                        }
                    }
                    
                    // If sowing has occurred than determine the emergence 
                    // Note that the TSUMEM will be calculated starting from next day
                    if (Crop->Sowing ) {
                        Astro();
                        CalcPenman();
                        EvapTra();
                        RateCalulationWatBal();    
                        // IntegrationWatBal();
                        if (!Crop->Emergence) {
                            EmergenceCrop(Crop->Emergence); 
                        }
                        else  {   
                            if (Crop->st.Development <= (Crop->prm.DevelopStageEnd) 
                                && Crop->GrowthDay < CycleLength) {                           
                                
                                // State calculations 
                                IntegrationCrop();
                                IntegrationNutrients();
                                
                                // Rate calculations
                                RatesToZero();
                                RateCalcultionNutrients();
                                RateCalculationCrop();
                                // Update the number of days that the crop has grown
                                Crop->GrowthDay++;     
                            }
                            else {
                                // Write to the output files 
                                //Output(output[Grid->file]);   
                                //printf("%7d %7d\n", MeteoYear[Day], Crop->GrowthDay);
                                Emergence = 0;
                                Crop->TSumEmergence = 0;
                                Crop->Emergence = 0;
                                Crop->Sowing    = 0;
                                Crop->Seasons++;
                            }
                        }
                        Output();
                    
                        IntegrationWatBal();
                    }    
                }
                // Store the daily calculations in the Grid structure 
                Grid->crp  = Crop;
                Grid->soil = WatBal;
                Grid->mng  = Mng;
                Grid = Grid->next;
            }
        }
        
    head = Meteo;
    Meteo = Meteo->next;
    free(head);
    }
    free(Meteo);
     
    // Return to the beginning of the list 
    Grid = initial;
    
    // Close the output files and free the allocated memory 
    while(Grid)
    {
        fclose(output[Grid->file]);
        Grid = Grid->next;
    }
    free(output);

    // Go back to the beginning of the list 
    Grid = initial;
    Clean(Grid);

    return 1;
}
