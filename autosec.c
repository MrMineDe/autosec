#include <stdbool.h>

#include "lib/libical/include/libical/ical.h"

typedef unsigned int uint;
typedef unsigned int ushort;
typedef unsigned int ulong;

typedef struct datelist datelist;
typedef struct needs needs;

// This defines a structure for a few other structures (needs),
// where we want to define a certain criterium/argument/attribute to a few different datecombinations as listed
struct datelist{
	bool minute[60];
	bool hour[24];
	bool wday[7];
	bool mday[31];
	bool month[12];
	int year[100]; //TODO CONSIDER you can define at max 100 different years here. Not perfect.
};

// All times in here are minutes, if not defined otherwise
struct needs{
	int length; //complete length of all sessions
	uint priority; // 0 is the top priority
	int session_length_min;
	int session_length_max;
	int session_length_pref;
	icaltimetype earliest; //Frühestens anfangen mit sessions. This can be a date, but can also specify a time
	icaltimetype latest; //The point, where everything should be done. This can be a date, but can also specify a time
	//alle im datelist definierten Elemente, sind für Termine tabu.
	//So kann man z.B. auch eine früheste/späteste Zeit (z.B. 8-15h täglich verboten) einführen.
	//Wir müssen dies allerdings als Array definieren, um z.B. verschiedene tägliche Zeitverbote zu ermöglichen
	datelist *disallowed; 
	datelist preffered;
	//defines the max and min minutes spend per day/week/month/year
	int max_per_day;
	int max_per_week;
	int max_per_month;
	int max_per_year;
	int min_per_day;
	int min_per_week;
	int min_per_month;
	int min_per_year;
	int pref_per_day;
	int pref_per_week;
	int pref_per_month;
	int pref_per_year;
	// TOOD This is advanded stuff, not for the beginning
	//icalcomponent execute_after; //the needs tasks should be executed before execute_after
	//icalcomponent execute_before; //the needs tasks should be executed after execute_before
	
};

void
icaltime_copy(icaltimetype *dest, icaltimetype src)
{
	dest->year = src.year;
	dest->month = src.month;
	dest->day = src.day;
	dest->hour = src.hour;
	dest->minute = src.minute;
	dest->second = src.second;
	dest->is_date = src.is_date;
	dest->is_daylight = src.is_daylight;
	dest->zone = src.zone; //TODO HACK I think this is not allowed, as I copy a structure-pointer only
}

// Here we want to analyze everything about a new event and make it into a event
// TODO This needs to be refactored eventually. We do not respect pref because we linearly go through from the beginning to end until we find SOMETHING that fits.
void
event_new(needs n)
{
	bool time_found=false;
	icaltimetype start_t, end_t;
	icaltime_copy(&start_t, n.earliest);
	start_t.is_date=0;
	start_t.second=0;
	start_t.minute=0;
	start_t.hour=0;
	icaltime_copy(end_t, icaltime_from_timet_with_zone(icaltime_as_timet(start_t)+length*60, 0, start_t.zone));
	while(!time_found){
		if(icaltime_compare(end_t, n.latest) != -1){
			printf("Couldnt meet the needs! Exiting...");
			return 1;
		}
		if( !time_is_ok(start_t, end_t)){
			// TODO STARTHERE add the checks about the disallowed tag
			icaltime_copy(start_t, icaltime_from_timet_with_zone(icaltime_as_timet(start_t)+1, 0, n.earliest.zone));
			icaltime_copy(end_t, icaltime_from_timet_with_zone(icaltime_as_timet(end_t)+1, 0, n.earliest.zone));
		} else {
			time_found = true;
		}
	}
}

bool
time_is_ok(icaltimetype start_t, icaltimetype end_t){
	// TODO STARTHERE to do this, we probably need to add all the logic about saving the whole calendar inside the program ( and maybe loading it etc. )
}

int
main(void){
	printf("hallo welt\n");

	return 0;
}
