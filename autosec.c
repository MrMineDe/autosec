#include <stdbool.h>
#include <stdlib.h>

#include "lib/libical/include/libical/ical.h"

#include "autosec.h"

icalcomponent *events; // A sorted(by time) array of all events, loaded into the program. It is dynamically reallocated, when adding new events to cache or removing from cache

// TODO Does this work? Is this smart? Does not deal with Sommer/Winterzeit
icaltimezone *zone;

// This defines a structure for a few other structures (needs),
// where we want to define a certain criterium/argument/attribute to a few different datecombinations as listed
struct
datelist{
	bool minute[60];
	bool hour[24];
	bool wday[7];
	bool mday[31];
	bool month[12];
	int year[100]; //TODO CONSIDER you can define at max 100 different years here. Not perfect.
	// all elements in min/hour etc. are false
	bool min_all_f;
	bool hour_all_f;
	bool wday_all_f;
	bool mday_all_f;
	bool month_all_f;
};

// All times in here are minutes, if not defined otherwise
struct
needs{
	uint length; //complete length of all sessions
	uint priority; // 0 is the top priority
	uint session_length_min;
	uint session_length_max;
	uint session_length_pref;
	icaltimetype earliest; //Frühestens anfangen mit sessions. This can be a date, but can also specify a time
	icaltimetype latest; //The point, where everything should be done. This can be a date, but can also specify a time
	//alle im datelist definierten Elemente, sind für Termine tabu.
	//So kann man z.B. auch eine früheste/späteste Zeit (z.B. 8-15h täglich verboten) einführen.
	//Wir müssen dies allerdings als Array definieren, um z.B. verschiedene tägliche Zeitverbote zu ermöglichen
	datelist *disallowed; 
	uint disallowed_len;
	datelist *preferred;
	uint preferred_len;
	//defines the max and min minutes spend per day/week/month/year
	uint max_per_day;
	uint max_per_week;
	uint max_per_month;
	uint max_per_year;
	uint min_per_day;
	uint min_per_week;
	uint min_per_month;
	uint min_per_year;
	uint pref_per_day;
	uint pref_per_week;
	uint pref_per_month;
	uint pref_per_year;
	// TOOD This is advanded stuff, not for the beginning
	//icalcomponent execute_after; //the needs tasks should be executed before execute_after
	//icalcomponent execute_before; //the needs tasks should be executed after execute_before
};

void
init_datelist(datelist *d)
{
	for(int i=0; i < 100; i++){
		d->year[i] = 0;
		if(i < 60)
			d->minute[i] = false;
		if(i < 24)
			d->hour[i] = false;
		if(i < 7)
			d->wday[i] = false;
		if(i < 31)
			d->mday[i] = false;
		if(i < 12)
			d->month[i] = false;
	}
}

void
init_needs(needs *n, uint length, uint priority, uint session_length_min, uint session_length_max,
					 uint session_length_pref, icaltimetype earliest, icaltimetype latest,
					 uint max_per_day, uint max_per_week, uint max_per_month, uint max_per_year,
					 uint min_per_day, uint min_per_week, uint min_per_month, uint min_per_year,
					 uint pref_per_day, uint pref_per_week, uint pref_per_month, uint pref_per_year)
{
	n->length = length;
	n->priority = priority;
	n->length = length;
	n->priority = priority;
	n->session_length_min = session_length_min;
	n->session_length_max = session_length_max;
	n->session_length_pref = session_length_pref;
	n->earliest = earliest;
	n->latest = latest;
	n->max_per_day= max_per_day;
	n->max_per_week = max_per_week;
	n->max_per_month = max_per_month;
	n->max_per_year = max_per_year;
	n->min_per_day = min_per_day;
	n->min_per_week = min_per_week;
	n->min_per_month = min_per_month;
	n->min_per_year = min_per_year;
	n->pref_per_day = pref_per_day;
	n->pref_per_week = pref_per_week;
	n->pref_per_month = pref_per_month;
	n->pref_per_year = pref_per_year;
	n->disallowed_len = 0;
	n->preferred_len = 0;
}

// checks if all entries in bool array are false
bool
is_array_false(bool *a, int a_len)
{
	for(int i=0; i < a_len; i++){
		if(a[i])
			return false;
	}
	return true;
}

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
// We return false if we couldnt find any possible time TODO This needs to be refactored eventually. We do not respect pref because we linearly go through from the beginning to end until we find SOMETHING that fits.
bool
event_new(needs n, icalcomponent *c)
{
	icaltimetype *possible_start_t, *possible_end_t;
	int *pref;
	//possible_start_t_len/max is also the len/max of end_t and pref
	uint possible_start_t_len=0;
	uint possible_start_t_max=0;
	icaltimetype start_t, end_t;
	icaltime_copy(&start_t, n.earliest);
	start_t.is_date=0;
	start_t.second=0;
	start_t.minute=0;
	start_t.hour=0;
	icaltime_copy(&end_t, icaltime_from_timet_with_zone(icaltime_as_timet(start_t)+n.length*60, 0, zone));
	time_t latest = icaltime_as_timet(n.latest);
	int alloc_base = (latest-icaltime_as_timet(end_t))/600;
	int realloc_counter = 0;
	while(icaltime_compare(end_t, n.latest) == -1){
		if(timespan_is_ok(n, start_t, end_t)){
			//TODO Test this! 
			//TODO is 10 mallocs a good number? Maybe 100 or smth is more effective
			// If possible_start_t etc. is not malloced enough, we needs to alloc more
			if(possible_start_t_len==possible_start_t_max){
				if(possible_start_t_max==0){
					possible_start_t = malloc(sizeof(icaltimetype)*alloc_base);
					possible_end_t = malloc(sizeof(icaltimetype)*alloc_base);
					pref = malloc(sizeof(int)*alloc_base);
					possible_start_t_max=alloc_base;
				} else {
					realloc_counter++;
					possible_start_t = realloc(possible_start_t, sizeof(icaltimetype)*(alloc_base*realloc_counter+possible_start_t_max));
					possible_end_t = realloc(possible_end_t, sizeof(icaltimetype)*(alloc_base*realloc_counter+possible_start_t_max));
					pref = realloc(pref, sizeof(int)*(alloc_base*realloc_counter+possible_start_t_max));
					possible_start_t_max+=alloc_base;
					printf("Realloced to: %d, Time to Go: %ld\n", possible_start_t_max, icaltime_as_timet(n.latest)-icaltime_as_timet(end_t));
				}
			}
			//We want to store every possible time for the event to later get the most preferred
			pref[possible_start_t_len] = timespan_pref(n, start_t, end_t);
			possible_start_t[possible_start_t_len] = start_t;
			possible_end_t[possible_start_t_len] = end_t;
			possible_start_t_len++;
		}
		icaltime_copy(&start_t, icaltime_from_timet_with_zone(icaltime_as_timet(start_t)+60, 0, zone));
		icaltime_copy(&end_t, icaltime_from_timet_with_zone(icaltime_as_timet(end_t)+60, 0, zone));
	}
	if(possible_start_t_len == 0)
		return false;
	int best_i = 0;
	for(int i=0; i < possible_start_t_len; i++){
		if(pref[i] < pref[best_i])
			best_i = i;
	}
	icalproperty *prop;
	prop = icalproperty_new_dtstart(possible_start_t[best_i]);
	icalcomponent_add_property(c, prop);
	prop = icalproperty_new_dtend(possible_end_t[best_i]);
	icalcomponent_add_property(c, prop);
	return true;
}

//TODO STARTHERE 
//Gibt eine Zahl zurück, die als Preferenz gesehen werden kann, je kleiner die Zahl, desto besser
float
timespan_pref(needs n, icaltimetype start_t, icaltimetype end_t){
	//Every option is evaluated beteen 0 and 1. Afterwards weighed and added
	time_t start = icaltime_as_timet(start_t);
	time_t end = icaltime_as_timet(end_t);
	time_t session_len = end-start;
	//session length
	float length_val;
	if(n.session_length_pref < session_len/60)
		length_val = ((session_len-n.session_length_pref)*-1)/
			           (float)(n.session_length_pref-n.session_length_min);
	//preferred dates/times
	//TODO LATER maybe be more precise and allow "partial" in datelist to also be better.
	float datelist_pref_val = 0;
	for(int i=0; i < session_len/60 && n.preferred_len != 0; i++){
		if(!time_is_in_datelist_array(n.preferred, n.preferred_len, icaltime_from_timet_with_zone(start+60*i, false, zone)))
			datelist_pref_val = 1.0;
	}
	//time is on 10:20:30:40:50, best is 30 or 00
	float position_val;
	//If time has something other than HH:M0, then thats bad!
	if(start%1800 != 0)
		position_val = 0.3;
	//If time is HH:10 or HH:20 or HH:40 or HH:50 its not perfekt, but not the worst
	if(start%1800 != 0 && start%600 == 0)
		position_val = 0.1;
	//If time is HH:30 or HH:00 or HH:15 or HH:45 everything is perfekt
	if(start%1800 == 0 || start%1800 == 900)
		position_val = 0;
	//How far away from the start it is
	time_t latest = icaltime_as_timet(n.latest);
	float near_start_val;
	near_start_val = (float)(latest-end)/(latest-session_len);
	near_start_val /= 100;
	//TODO LATER time preferred after last event. Maybe custom for each event
	//pref_per_X
	return length_val + datelist_pref_val + position_val + near_start_val;
}

// We want to check, if we could add a item at that timespan.
// This includes but is not limited to:
// - disallowed times
// - already existing calendar items
// - minimal time requirements are met (length, time, etc.)
bool
timespan_is_ok(needs n, icaltimetype start_t, icaltimetype end_t)
{
	// Checks:
	// - disallowed
	// - in calendar
	icaltimetype time_temp;
	for(icaltime_copy(&time_temp, start_t);
		icaltime_compare(time_temp, end_t);
		icaltime_copy(&time_temp, icaltime_from_timet_with_zone(icaltime_as_timet(time_temp)+60, 0, zone)))
	{
		if(time_is_in_datelist_array(n.disallowed, n.disallowed_len, time_temp) ||
		   time_is_in_calendar(time_temp))
			return false;
	}
	// Check:
	// - time requirements are met
	time_t len = icaltime_as_timet(end_t) - icaltime_as_timet(start_t);
	if(len < n.length*60 || len < n.session_length_min*60 || len > n.session_length_max*60)
		return false;
	return true;
}


// This checks if a time t is not applicable because it is contained in one of the disallowed timespans
bool
time_is_in_datelist_array(datelist *d, int d_len, icaltimetype t)
{
	for(int i=0; i < d_len; i++){
		if(time_is_in_datelist(d[i], t))
			return true;
	}
	return false;
}

bool
time_is_in_datelist(datelist d, icaltimetype t)
{
	//we need every element after the beginning to be true
	//the beginning is, when not every element is false
	bool begin=false;
	if((!begin && !d.min_all_f) && d.minute[t.minute])
		begin=true;
	else if((begin && d.min_all_f) ||
	        (!d.min_all_f && !d.minute[t.minute]))
	  return false;

	if((!begin && !d.hour_all_f) && d.hour[t.hour])
		begin=true;
	else if((begin && d.hour_all_f) ||
		      (!d.hour_all_f && !d.hour[t.hour]))
	  return false;

	// day of the week is stored wierdly in icaltime...
	int t_day_of_week = icaltime_day_of_week(t)-2;
	if(t_day_of_week == -1) t_day_of_week=6;
	if((!begin && !d.wday_all_f) && d.wday[t_day_of_week])
		begin=true;
	else if((begin && d.wday_all_f) ||
					(!d.wday_all_f && !d.wday[t_day_of_week]))
	  return false;

	if((!begin && !d.mday_all_f) && d.mday[t.day-1])
		begin=true;
	else if((begin && d.mday_all_f) ||
		      (!d.mday_all_f && !d.mday[t.day-1]))
	  return false;

	if((!begin && !d.month_all_f) && d.month[t.month-1])
		begin=true;
	else if((begin && d.month_all_f) ||
		      (!d.month_all_f && !d.month[t.month-1]))
	  return false;

	//TODO implement the year check. YOu cant check like all the others, bc year is stored in ultimate value as well (not bool)
	//if all if's dont return false, then everything matches (the time is in the datelist!)
	return true;
}

// This checks if a time t is not applicable because at that time the calendar already contains an event
bool
time_is_in_calendar(icaltimetype t)
{
	//TODO to implement this, we need to implement the calendar logic first
	return false;
}

int
main(void){
	//first set the timezone
	zone = icaltimezone_get_builtin_timezone_from_offset(1, "Berlin");

	icalcomponent *event;
	//icalproperty *prop;
	//icalparameter *param;
	//struct icaltimetype atime;
	icaltime_t earliest;
	time(&earliest);
	needs n;
	init_needs(&n, 30, 0, 30, 30, 30, icaltime_from_timet_with_zone(earliest, 0, zone), icaltime_from_timet_with_zone(earliest+60*60*24, 0, zone), 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	n.disallowed = malloc(sizeof(datelist));
	init_datelist(n.disallowed);
	n.disallowed_len = 1;
	for(int i=0; i < 60; i++){
		if(i < 24)
			n.disallowed[0].hour[i] = false;
		if(i < 7)
			n.disallowed[0].wday[i] = false;
		if(i < 12)
			n.disallowed[0].month[i] = true;
		if(i < 31)
			n.disallowed[0].mday[i] = true;
		n.disallowed[0].minute[i] = false;
	}
	n.disallowed[0].wday[1] = true;
	n.disallowed[0].min_all_f = is_array_false(n.disallowed[0].minute, 60);
	n.disallowed[0].hour_all_f = is_array_false(n.disallowed[0].hour, 24);
	n.disallowed[0].wday_all_f = is_array_false(n.disallowed[0].wday, 7);
	n.disallowed[0].month_all_f = is_array_false(n.disallowed[0].month, 12);
	n.disallowed[0].mday_all_f = is_array_false(n.disallowed[0].mday, 31);

	n.preferred = malloc(sizeof(datelist));
	init_datelist(n.preferred);
	n.preferred_len = 1;
	for(int i=0; i < 60; i++){
		if(i < 24)
			n.preferred[0].hour[i] = false;
		if(i < 7)
			n.preferred[0].wday[i] = true;
		if(i < 12)
			n.preferred[0].month[i] = true;
		if(i < 31)
			n.preferred[0].mday[i] = true;
		n.preferred[0].minute[i] = false;
	}
	n.preferred[0].hour[6] = true;
	n.preferred[0].hour[7] = true;
	n.preferred[0].hour[8] = true;
	n.preferred[0].hour[9] = true;
	n.preferred[0].hour[10] = true;
	n.preferred[0].hour[11] = true;
	n.preferred[0].min_all_f = is_array_false(n.preferred[0].minute, 60);
	n.preferred[0].hour_all_f = is_array_false(n.preferred[0].hour, 24);
	n.preferred[0].wday_all_f = is_array_false(n.preferred[0].wday, 7);
	n.preferred[0].month_all_f = is_array_false(n.preferred[0].month, 12);
	n.preferred[0].mday_all_f = is_array_false(n.preferred[0].mday, 31);

	event = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
	bool success = event_new(n, event);
	if(!success)
		printf("Couldnt find a time for you. Sorry!\n");

	printf("DTSTART: %s", icaltime_as_ical_string(icalproperty_get_dtstart(icalcomponent_get_first_property(event, ICAL_DTSTART_PROPERTY))));
	printf("DTEND  : %s", icaltime_as_ical_string(icalproperty_get_dtend(icalcomponent_get_next_property(event, ICAL_DTEND_PROPERTY))));

	free(n.disallowed);
	/*
	prop = icalproperty_new_dtstamp(atime);
	icalcomponent_add_property(event, prop);
	
	prop = icalproperty_new_uid("julian@mminl.de");
	icalcomponent_add_property(event, prop);

	prop = icalproperty_new_organizer("julian");
	param = icalparameter_new_role(ICAL_ROLE_CHAIR);
	icalproperty_add_parameter(prop, param);
	icalcomponent_add_property(event, prop);
	*/
	return 0;
}
