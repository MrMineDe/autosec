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
	int earliest_date; //Frühestens anfangen mit sessions
	int latest_date;
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
	// TOOD This is advanded stuff, not for the beginning
	//icalcomponent execute_after; //the needs tasks should be executed before execute_after
	//icalcomponent execute_before; //the needs tasks should be executed after execute_before
	
};


// Here we want to analyze everything about a new event and make it into a event
void
event_new()
{

}

int
main(void){
	printf("hallo welt\n");

	return 0;
}
