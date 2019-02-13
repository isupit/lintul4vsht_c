#ifndef MANAGE_H
#define MANAGE_H

char *ManageParam[]={ "NMINS",
                      "RTNMINS",
                      "NULL"
		   };

char *ManageParam2[]={
                    "FERNTAB",
                    "NRFTAB",
                    "IRRTAB",
                    "NULL"
		    };

extern void FillManageVariables();
extern int FillAfgenTables();

#endif //MANAGE_H