#include <stdio.h>
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------------------*/
/*  function void IfSowing    ()                                              */
/*  Purpose: Checks whether sowing has occurred. Note that if the emergence   */
/*           flag is set to 1 the crop simulation starts the next day. If it  */
/*           is set to 0 the Emergence date has to be established.            */
/* ---------------------------------------------------------------------------*/

void IfSowing(char* dateString)
{
    int month, start_day;
        
    sscanf(dateString, "%d-%d", &month, &start_day);
    sowing_date.tm_year = MeteoYear[Day];
    sowing_date.tm_mon = month -1; 
    sowing_date.tm_mday = start_day;
    sowing = mktime(&sowing_date);
   // printf("%5d\n",sowing_date.tm_yday);
    sowing_date.tm_yday = sowing_date.tm_yday + 1;
    //printf("%5d\n",sowing_date.tm_yday);
    
    //diff = difftime(date, sowing);
    //printf("%7.2f\n",diff);
    
    if (sowing_date.tm_yday == current_date.tm_yday && 
        MeteoYear[Day] <= Meteo->EndYear)
    {
        Crop->Sowing = 1;
    }
}