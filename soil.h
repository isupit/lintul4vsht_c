#ifndef SOIL_H
#define SOIL_H

char *SoilParam[]={"SMDRY",
                   "SMW",
                   "SMFCF",
		   "SM0",
		   "CRAIRC",
		   "SMI",
		   "SMLOWI",
		   "RDMSO",
		   "RUNFR",
                   "CFEV",
		   "KSUB",
		   "NULL"
		   };
		   
char *SoilParam2[]={
                    "NotInfTB",
                    "NULL"
		    };

extern int FillSoilVariables();

#endif //SOIL_H