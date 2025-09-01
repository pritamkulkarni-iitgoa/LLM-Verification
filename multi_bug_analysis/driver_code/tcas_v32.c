/*  -*- Last-Edit:  Fri Jan 29 11:13:27 1993 by Tarak S. Goradia; -*- */
/* $Log: tcas.c,v $
 * Revision 1.2  1993/03/12  19:29:50  foster
 * Correct logic bug which didn't allow output of 2 - hf
 * */

#include <stdio.h>

#define OLEV       600		/* in feets/minute */
#define MAXALTDIFF 600		/* max altitude difference in feet */
#define MINSEP     300          /* min separation in feet */
#define NOZCROSS   100		/* in feet */
				/* variables */

typedef int bool;

int Cur_Vertical_Sep;
bool High_Confidence;
bool Two_of_Three_Reports_Valid;

int Own_Tracked_Alt;
int Own_Tracked_Alt_Rate;
int Other_Tracked_Alt;

int Alt_Layer_Value;		/* 0, 1, 2, 3 */
int Positive_RA_Alt_Thresh[4];

int Up_Separation;
int Down_Separation;

				/* state variables */
int Other_RAC;			/* NO_INTENT, DO_NOT_CLIMB, DO_NOT_DESCEND */
#define NO_INTENT 0
#define DO_NOT_CLIMB 1
#define DO_NOT_DESCEND 2

int Other_Capability;		/* TCAS_TA, OTHER */
#define TCAS_TA 1
#define OTHER 2

int Climb_Inhibit;		/* true/false */

#define UNRESOLVED 0
#define UPWARD_RA 1
#define DOWNWARD_RA 2

#define OLEV_2       600		/* in feets/minute */
#define MAXALTDIFF_2 600		/* max altitude difference in feet */
#define MINSEP_2     300          /* min separation in feet */
#define NOZCROSS_2   100		/* in feet */
				/* variables */

int Cur_Vertical_Sep_2;
bool High_Confidence_2;
bool Two_of_Three_Reports_Valid_2;

int Own_Tracked_Alt_2;
int Own_Tracked_Alt_Rate_2;
int Other_Tracked_Alt_2;

int Alt_Layer_Value_2;		/* 0, 1, 2, 3 */
int Positive_RA_Alt_Thresh_2[4];

int Up_Separation_2;
int Down_Separation_2;

				/* state variables */
int Other_RAC_2;			/* NO_INTENT, DO_NOT_CLIMB, DO_NOT_DESCEND */
#define NO_INTENT_2 0
#define DO_NOT_CLIMB_2 1
#define DO_NOT_DESCEND_2 2

int Other_Capability_2;		/* TCAS_TA, OTHER */
#define TCAS_TA_2 1
#define OTHER_2 2

int Climb_Inhibit_2;		/* true/false */

#define UNRESOLVED_2 0
#define UPWARD_RA_2 1
#define DOWNWARD_RA_2 2

void initialize()
{
    Positive_RA_Alt_Thresh[0] = 400;
    Positive_RA_Alt_Thresh[1] = 500;
    Positive_RA_Alt_Thresh[2] = 640;
    Positive_RA_Alt_Thresh[3] = 740;
}

int ALIM ()
{
 return Positive_RA_Alt_Thresh[Alt_Layer_Value];
}

int Inhibit_Biased_Climb ()
{
    return (Climb_Inhibit ? Up_Separation + NOZCROSS : Up_Separation);
}

bool Non_Crossing_Biased_Climb()
{
    int upward_preferred;
    int upward_crossing_situation;
    bool result;

    upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
    if (upward_preferred)
    {
	result = !(Own_Below_Threat()) || ((Own_Below_Threat()) && (!(Down_Separation >= ALIM())));
    }
    else
    {	
	result = Own_Above_Threat() && (Cur_Vertical_Sep >= MINSEP) && (Up_Separation >= ALIM());
    }
    return result;
}

bool Non_Crossing_Biased_Descend()
{
    int upward_preferred;
    int upward_crossing_situation;
    bool result;

    upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
    if (upward_preferred)
    {
	result = Own_Below_Threat() && (Cur_Vertical_Sep >= MINSEP) && (Down_Separation >= ALIM());
    }
    else
    {
	result = !(Own_Above_Threat()) || ((Own_Above_Threat()) && (Up_Separation >= ALIM()));
    }
    return result;
}

bool Own_Below_Threat()
{
    return (Own_Tracked_Alt < Other_Tracked_Alt);
}

bool Own_Above_Threat()
{
    return (Other_Tracked_Alt < Own_Tracked_Alt);
}

int alt_sep_test()
{
    bool enabled, tcas_equipped, intent_not_known;
    bool need_upward_RA, need_downward_RA;
    int alt_sep;

    enabled = High_Confidence && (Own_Tracked_Alt_Rate <= OLEV) && (Cur_Vertical_Sep > MAXALTDIFF);
    tcas_equipped = Other_Capability == TCAS_TA;
    intent_not_known = Two_of_Three_Reports_Valid && Other_RAC == NO_INTENT;
    
    alt_sep = UNRESOLVED;
    
    if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped))
    {
	need_upward_RA = Non_Crossing_Biased_Climb() && Own_Below_Threat();
	need_downward_RA = Non_Crossing_Biased_Descend() && Own_Above_Threat();
	if (need_upward_RA && need_downward_RA)
        /* unreachable: requires Own_Below_Threat and Own_Above_Threat
           to both be true - that requires Own_Tracked_Alt < Other_Tracked_Alt
           and Other_Tracked_Alt < Own_Tracked_Alt, which isn't possible */
	    alt_sep = UNRESOLVED;
	else if (need_upward_RA)
	    alt_sep = UPWARD_RA;
	else if (need_downward_RA)
	    alt_sep = DOWNWARD_RA;
	else
	    alt_sep = UNRESOLVED;
    }
    
    return alt_sep;
}

void initialize_2()
{
    Positive_RA_Alt_Thresh_2[0] = 400;
    Positive_RA_Alt_Thresh_2[1] = 500;
    Positive_RA_Alt_Thresh_2[2] = 640;
    Positive_RA_Alt_Thresh_2[3] = 740;
}

int ALIM_2 ()
{
 return Positive_RA_Alt_Thresh_2[Alt_Layer_Value_2];
}

int Inhibit_Biased_Climb_2 ()
{
    return (Climb_Inhibit_2 ? Up_Separation_2 + NOZCROSS_2 : Up_Separation_2);
}

bool Non_Crossing_Biased_Climb_2()
{
    int upward_preferred_2;
    int upward_crossing_situation_2;
    bool result_2;

    upward_preferred_2 = Inhibit_Biased_Climb_2() > Down_Separation_2;
    if (upward_preferred_2)
    {
	result_2 = !(Own_Below_Threat_2()) || ((Own_Below_Threat_2()) && (!(Down_Separation_2 >= ALIM_2())));
    //result_2 = result_2 && (Own_Tracked_Alt_2 <= Other_Tracked_Alt_2);
    }
    else
    {	
	result_2 = Own_Above_Threat_2() && (Cur_Vertical_Sep_2 >= MINSEP_2) && (Up_Separation_2 >= ALIM_2());
    //result_2 = result_2 && (Own_Tracked_Alt_2 < Other_Tracked_Alt_2);
    }
    return result_2;
}

bool Non_Crossing_Biased_Descend_2()
{
    int upward_preferred_2;
    int upward_crossing_situation_2;
    bool result_2;

    upward_preferred_2 = Inhibit_Biased_Climb_2() > Down_Separation_2;
    if (upward_preferred_2)
    {
	result_2 = Own_Below_Threat_2() && (Cur_Vertical_Sep_2 >= MINSEP_2) && (Down_Separation_2 >= ALIM_2());
    result_2 = result_2 && (Other_Tracked_Alt_2 < Own_Tracked_Alt_2);
    }
    else
    {
	result_2 = !(Own_Above_Threat_2()) || ((Own_Above_Threat_2()) && (Up_Separation_2 >= ALIM_2()));
    result_2 = result_2 && (Other_Tracked_Alt_2 <= Own_Tracked_Alt_2);
    }
    return result_2;
}

bool Own_Below_Threat_2()
{
    /* NOTE JMW replaced LESS-THAN with LESS-THAN-EQUAL. */
    return (Own_Tracked_Alt_2 < Other_Tracked_Alt_2);
}

bool Own_Above_Threat_2()
{
    /* NOTE JMW replaced LESS-THAN with LESS-THAN-EQUAL. */
    return (Other_Tracked_Alt_2 < Own_Tracked_Alt_2);
}

int alt_sep_test_2()
{
    bool enabled_2, tcas_equipped_2, intent_not_known_2;
    bool need_upward_RA_2, need_downward_RA_2;
    int alt_sep_2;
    
    enabled_2 = High_Confidence_2 && (Own_Tracked_Alt_Rate_2 <= OLEV_2) && (Cur_Vertical_Sep_2 > MAXALTDIFF_2); 
    tcas_equipped_2 = Other_Capability_2 == TCAS_TA_2;
    intent_not_known_2 = Two_of_Three_Reports_Valid_2 && Other_RAC_2 == NO_INTENT_2;
    
    alt_sep_2 = UNRESOLVED_2;
    
    if (enabled_2 && ((tcas_equipped_2 && intent_not_known_2) || !tcas_equipped_2))
    {
	need_upward_RA_2 = Non_Crossing_Biased_Climb_2() && Own_Below_Threat_2();;
	need_downward_RA_2 = Non_Crossing_Biased_Descend_2();
	if (need_upward_RA_2 && need_downward_RA_2)
        /* unreachable: requires Own_Below_Threat and Own_Above_Threat
           to both be true - that requires Own_Tracked_Alt < Other_Tracked_Alt
           and Other_Tracked_Alt < Own_Tracked_Alt, which isn't possible */
	    alt_sep_2 = UNRESOLVED_2;
	else if (need_upward_RA_2)
	    alt_sep_2 = UPWARD_RA_2;
	else if (need_downward_RA_2)
	    alt_sep_2 = DOWNWARD_RA_2;
	else
	    alt_sep_2 = UNRESOLVED_2;
    }
    
    return alt_sep_2;
}


int main()
{
    /*if(argc < 13)
    {
	fprintf(stdout, "Error: Command line arguments are\n");
	fprintf(stdout, "Cur_Vertical_Sep, High_Confidence, Two_of_Three_Reports_Valid\n");
	fprintf(stdout, "Own_Tracked_Alt, Own_Tracked_Alt_Rate, Other_Tracked_Alt\n");
	fprintf(stdout, "Alt_Layer_Value, Up_Separation, Down_Separation\n");
	fprintf(stdout, "Other_RAC, Other_Capability, Climb_Inhibit\n");
	exit(1);
    }*/
    initialize();
    Cur_Vertical_Sep = nondet_int();
    High_Confidence = nondet_int();
    Two_of_Three_Reports_Valid = nondet_int();
    Own_Tracked_Alt = nondet_int();
    Own_Tracked_Alt_Rate = nondet_int();
    Other_Tracked_Alt = nondet_int();
    Alt_Layer_Value = nondet_int();
    Up_Separation = nondet_int();
    Down_Separation = nondet_int();
    Other_RAC = nondet_int();
    Other_Capability = nondet_int();
    Climb_Inhibit = nondet_int();

    initialize_2();
    Cur_Vertical_Sep_2 = nondet_int();
    High_Confidence_2 = nondet_int();
    Two_of_Three_Reports_Valid_2 = nondet_int();
    Own_Tracked_Alt_2 = nondet_int();
    Own_Tracked_Alt_Rate_2 = nondet_int();
    Other_Tracked_Alt_2 = nondet_int();
    Alt_Layer_Value_2 = nondet_int();
    Up_Separation_2 = nondet_int();
    Down_Separation_2 = nondet_int();
    Other_RAC_2 = nondet_int();
    Other_Capability_2 = nondet_int();
    Climb_Inhibit_2 = nondet_int();

    __CPROVER_assume(Cur_Vertical_Sep == Cur_Vertical_Sep_2);
    __CPROVER_assume(High_Confidence == High_Confidence_2);
    __CPROVER_assume(Two_of_Three_Reports_Valid == Two_of_Three_Reports_Valid_2);
    __CPROVER_assume(Own_Tracked_Alt == Own_Tracked_Alt_2);
    __CPROVER_assume(Own_Tracked_Alt_Rate == Own_Tracked_Alt_Rate_2);
    __CPROVER_assume(Other_Tracked_Alt == Other_Tracked_Alt_2);
    __CPROVER_assume(Alt_Layer_Value == Alt_Layer_Value_2);
    __CPROVER_assume(Up_Separation == Up_Separation_2);
    __CPROVER_assume(Down_Separation == Down_Separation_2);
    __CPROVER_assume(Other_RAC == Other_RAC_2);
    __CPROVER_assume(Other_Capability == Other_Capability_2);
    __CPROVER_assume(Climb_Inhibit == Climb_Inhibit_2);

    fprintf(stdout, "%d\n", alt_sep_test());
    assert(alt_sep_test() == alt_sep_test_2());
    exit(0);
}

