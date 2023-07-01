#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lintul4.h"
#include "manage.h"

       
void GetManagement(Management *MNG, char *management)
{
 TABLE_D *Table[NR_TABLES_MANAGEMENT], *start;
  
  int i, c, mnth, dy;
  float Variable[100], Value;
  char  word[100], x[2];
  FILE *fq;

 if ((fq = fopen(management, "rt")) == NULL) {
     fprintf(stderr, "Cannot open input file.\n"); 
     exit(0);
 }

 i=0;
  while ((c=fscanf(fq,"%s",word)) != EOF) {
    if (!strcmp(word, ManageParam[i])) {
        while ((c=fgetc(fq)) !='=');
	fscanf(fq,"%f",  &Variable[i]);
	i++; 
       }  
  }

  if (i != NR_VARIABLES_MANAGEMENT) {
    fprintf(stderr, "Something wrong with the Management variables.\n"); 
    exit(0);
  }
 
  rewind(fq);  
  
  FillManageVariables(MNG, Variable);
 

  i=0;
  while ((c=fscanf(fq,"%s",word)) != EOF) 
  {
    if (!strcmp(word, ManageParam2[i])) {
        Table[i] = start = malloc(sizeof(TABLE_D));
	fscanf(fq,"%s %d-%d  %f", x, &Table[i]->month, &Table[i]->day, &Table[i]->amount);
        Table[i]->next = NULL;				     
			       
	while ((c=fgetc(fq)) !='\n');
	while (fscanf(fq," %2d-%2d  %f",  &mnth, &dy, &Value) > 0)  {
	    Table[i]->next = malloc(sizeof(TABLE_D));
            Table[i] = Table[i]->next; 
            Table[i]->next = NULL;
	    Table[i]->month = mnth;
	    Table[i]->day = dy;
	    Table[i]->amount = Value;
            
	    while ((c=fgetc(fq)) !='\n');
	    }
        /* Go back to beginning of the table */
        Table[i] = start;
	i++; 
       }      
  }

  fclose(fq);
  
  if (i!= NR_TABLES_MANAGEMENT){
    fprintf(stderr, "Something wrong with the Management tables.\n"); 
    exit(0);
  }
      
 
  MNG->N_Fert_table   = Table[0];
  MNG->Irrigation     = Table[1];
  
  }
