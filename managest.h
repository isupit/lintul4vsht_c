#ifndef MANAGEST_H
#define MANAGEST_H

typedef struct TBLD {
	int month;
	int day;
        float amount;
	struct TBLD *next;
	} TABLE_D;
        
     
typedef struct SITE_STATES {
    float N_tot;
    float N_mins;
} site_states;

typedef struct SITE_RATES {
    float N_tot;
    float N_mins;
} site_rates;   


typedef struct MANAGEMENT {
        /** Tables for fertilizer application and recovery fraction **/
        TABLE_D *N_Fert_table;
        TABLE_D *Irrigation;
        
        float N_Uptake_frac;
        float N_Mins;
        float NRecoveryFrac;
        float N_Background;
        
        site_rates rt;
        site_states st;
} Management;

extern Management *Mng;

#endif	
