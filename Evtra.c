/* original: Penman.for from I.G.A.M. Noy and C.A. van Diepen, */
/* van Kraalingen, and Allard de Wit, Sep 2011                 */

#include <stdio.h>
#include <math.h>
#include "penman.h"
#include "lintul4.h"
#include "extern.h"

/* ---------------------------------------------------------------*/
/*  function sweaf()                                              */
/*  Purpose: Calculates the Soil Water Easily Available Fraction  */
/*                                                                */
/* Chapter 20 in documentation WOFOST Version 4.1 (1988)          */
/*                                                                */
/*    The fraction of easily available soil water between         */
/*    field capacity and wilting point is a function of the       */
/*    potential evapotranspiration rate (for a closed canopy)     */
/*    in cm/day, ET0, and the crop group number, CGNR (from       */
/*    1 (=drought-sensitive) to 5 (=drought-resistent)). The      */
/*    function SWEAF describes this relationship given in tabular */
/*    form by Doorenbos & Kassam (1979) and by Van Keulen & Wolf  */
/*    (1986; p.108, table 20).                                    */
/*    Original fortran version: D.M. Jansen and C.A. van Diepen,  */
/*    October 1986.                                               */
/* ---------------------------------------------------------------*/ 
float sweaf(){
    float sweaf; 
    sweaf = 1./(0.76 + 1.5 * Penman.ET0) - (5.-Crop->prm.CropGroupNumber ) * 0.10;
    if  (Crop->prm.CropGroupNumber < 3.) {
        sweaf = sweaf + (Penman.ET0 - 0.6)/(Crop->prm.CropGroupNumber *
                (Crop->prm.CropGroupNumber + 3.));
    }
    return limit(0.10, 0.95, sweaf);

}
    
/* -----------------------------------------------------------------*/
/*  function EvapTra()                                              */
/*  Purpose: Calculates the water stress and the transpiration rate */
/* -----------------------------------------------------------------*/     
void EvapTra() {   
    float KDiffuse;
    
    /* crop specific correction on potential evapotranspiration rate */
    Penman.ET0 = Penman.ET0 * Crop->prm.CorrectionTransp;
    
    KDiffuse = Afgen(Crop->prm.KDiffuseTb, &(Crop->st.Development));      
    Evtra.MaxEvapWater = Penman.E0 * exp(-0.75 * KDiffuse * Crop->st.LAI);
    Evtra.MaxEvapSoil  = max(0., Penman.ES0 * exp(-0.75 * KDiffuse * Crop->st.LAI));
    Evtra.MaxTranspiration = max(0.0001,  
                             Penman.ET0 * Afgen(Crop->prm.CO2CorrectionTRA, &CO2) *
                             (1.-exp(-0.75 * KDiffuse * Crop->st.LAI)));
       
    }
