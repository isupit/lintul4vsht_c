#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------------------*/
/*  function IntegrationCrop                                                  */
/*  Purpose: Establish the crop state variables by integration of the crop    */
/*  rate variables and update the crop leave classes                          */
/* ---------------------------------------------------------------------------*/

void IntegrationCrop()	    
{

    /* Living material */
    Crop->st.roots    += Crop->rt.roots;
    Crop->st.stems    += Crop->rt.stems;
    Crop->st.leaves   += Crop->rt.leaves;
    Crop->st.storage  += Crop->rt.storage;
    Crop->st.LAIExp   += Crop->rt.LAIExp;
    
    /* Death material*/
    Crop->dst.roots    += Crop->drt.roots;
    Crop->dst.stems    += Crop->drt.stems;
    Crop->dst.leaves   += Crop->drt.leaves;
   
    /* Development */
    Crop->st.Development += Crop->rt.Development;
    
    /* Calculate vernalization state in case the switch is set */
    if (Crop->prm.IdentifyAnthesis == 2)
    {
        Crop->st.vernalization += Crop->rt.vernalization;       
    }

   
}       	     
