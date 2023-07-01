#include "extern.h"
#include <time.h>
#include "managest.h"

extern struct tm current_date;

/* ---------------------------------------------------------------------------*/
/*  function List()                                                           */
/*  Purpose: Get the value of a user provided input table                     */
/* ---------------------------------------------------------------------------*/
     
float List(TABLE_D *Table)
{
     while (Table) 
    { 
        if (current_date.tm_mon == Table->month -1 &&
            current_date.tm_mday == Table->day)
        {
            return Table->amount;
        }
        Table = Table->next;
    }
    
    return 0.;
}
