#ifndef MANAGE_H
#define MANAGE_H

char *ManageParam[]={ "NRFTAB",
                      "NMINS",
                      "RTNMINS",
                      "NULL"
		   };

char *ManageParam2[]={
                    "FERNTAB",
                    "IRRTAB",
                    "NULL"
		    };

extern void FillManageVariables();
extern int FillAfgenTables();

#endif //MANAGE_H