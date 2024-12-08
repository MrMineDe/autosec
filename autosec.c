#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lib/libical/include/libical/ical.h"
#include "lib/libical/include/libical/icalcomponent.h"

#include "autosec.h"

//This is ugly, but waaay easier then other solutions I find right now
#define DISALLOWED_DATELIST_AMOUNT_MAX 10000
#define PREFERRED_DATELIST_AMOUNT_MAX 10000

#define DATELIST_STRING_LEN 194
#define WANTED_MAX_PREF_AVG 0.2f

icalcomponent **events, **revents; // A sorted(by time) array of all events, loaded into the program. It is dynamically reallocated, when adding new events to cache or removing from cache
uint events_count = 0, events_max = 0, events_longest = 0, revents_count = 0, revents_max = 0;

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
	//int year[100]; //TODO CONSIDER you can define at max 100 different years here. Not perfect.
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
	uint session_len_min;
	uint session_len_max;
	uint session_len_pref;
	time_t earliest; //Frühestens anfangen mit sessions.
	time_t latest; //The point, where everything should be done. This can be a date, but can also specify a time
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
	//alle im datelist definierten Elemente, sind für Termine tabu.
	//So kann man z.B. auch eine früheste/späteste Zeit (z.B. 8-15h täglich verboten) einführen.
	//Wir müssen dies allerdings als Array definieren, um z.B. verschiedene tägliche Zeitverbote zu ermöglichen
	uint disallowed_len;
	datelist *disallowed; 
	uint preferred_len;
	datelist *preferred;
	// TOOD This is advanded stuff, not for the beginning
	//uint min_dist;
	//uint max_dist;
	//uint pref_dist;
	//icalcomponent execute_after; //the needs tasks should be executed before execute_after
	//icalcomponent execute_before; //the needs tasks should be executed after execute_before
};

//Cut after i characters
void
splitString(char *str, int i, char *left, char *right)
{
  strncpy(left, str, i);
  left[i] = '\0'; // Null-terminate the left part
  strcpy(right, str + i);
}


void
init_datelist(datelist *d)
{
	for(int i=0; i < 100; i++){
		//d->year[i] = 0;
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

//@ret write the uid in the input and return nothing
void
create_uid(char* uid)
{
	//17 for autosec..mminl.de, 15 for random number and 1 for \0
	uid[0] = '\0';
	strcpy(uid, "autosec.");
  for(int i = 8; i < 8+15; i++) {
      uid[i] = (rand() % 10) + '0';
  }
	uid[8+15] = '\0';
	strcat(uid, ".mminl.de");
}

void
init_needs(needs *n, uint length, uint priority, uint session_len_min, uint session_len_max,
					 uint session_len_pref, time_t earliest, time_t latest,
					 uint max_per_day, uint max_per_week, uint max_per_month, uint max_per_year,
					 uint min_per_day, uint min_per_week, uint min_per_month, uint min_per_year,
					 uint pref_per_day, uint pref_per_week, uint pref_per_month, uint pref_per_year)
{
	n->length = length;
	n->priority = priority;
	n->length = length;
	n->priority = priority;
	n->session_len_min = session_len_min;
	n->session_len_max = session_len_max;
	n->session_len_pref = session_len_pref;
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
// We return NULL if we couldnt find any possible time TODO This needs to be refactored eventually.
// the icalcomponent **c array of pointers is returned with a "library malloc", so it has to be freed, by the calling function!
icalcomponent **
event_new(needs n, int *best_indeces_len)
{
	time_t *poss_starts, *poss_ends;
	float *prefs;
	int *best_indeces;
	//poss_len/max is also the len/max of end_t and pref
	uint poss_len=0;
	uint poss_max_i=0;

	// We start with 30 min search mode. See comment at the end of the while for more context.
	int search_mode = 30;

	time_t start_t, end_t;
	//We want to start at the corresponding search_mode start (e.g. 30: 0,30,60)
	struct tm *t = gmtime(&n.earliest);
	//We need to bump to the next minute, to get rid of the seconds
	t->tm_sec = 0;
	t->tm_min++;
	t->tm_min += search_mode - (t->tm_min % search_mode);
	//If we are over an hour in minutes we bump to a new hour.
	//minute 0 of an hour is always legal, as search_mode has to be devidible by 60(so we can repeat every hour) CONSIDER making this even more flexible
	//We can easily add an hour by converting to time_t and adding 3600sec
	//Also initilise start_t with the final value
	if(t->tm_min > 60){
		t->tm_min = 0;
		start_t = mktime(t);
		start_t -= 3600;
	} else {
		start_t = mktime(t);
	}
	//TODO LATER This is not dynamic, we can only create events with a "pref" length
	end_t = start_t+n.session_len_pref*60;
	int alloc_base = (n.latest-end_t)/600;
	int realloc_counter = 0;
	while(end_t < n.latest){
		if(timespan_is_ok(n, start_t, end_t)){
			// If poss_starts etc. is not malloced enough, we needs to alloc more
			if(poss_len==poss_max_i){
				if(poss_max_i==0){
					poss_starts = malloc(sizeof(time_t)*alloc_base);
					poss_ends = malloc(sizeof(time_t)*alloc_base);
					prefs = malloc(sizeof(float)*alloc_base);
					poss_max_i=alloc_base;
				} else {
					realloc_counter++;
					poss_starts = realloc(poss_starts, sizeof(time_t)*(alloc_base*realloc_counter+poss_max_i));
					poss_ends = realloc(poss_ends, sizeof(time_t)*(alloc_base*realloc_counter+poss_max_i));
					prefs = realloc(prefs, sizeof(float)*(alloc_base*realloc_counter+poss_max_i));
					poss_max_i+=alloc_base;
					printf("Realloced to: %d, Time to Go: %ld\n", poss_max_i, n.latest-end_t);
				}
			}
			//We want to store every possible time for the event to later get the most preferred
			prefs[poss_len] = timespan_pref(n, start_t, end_t);
			poss_starts[poss_len] = start_t;
			poss_ends[poss_len] = end_t;
			poss_len++;
		}
		// We want to first search only every 30min, then every 15, then every 10, then every 5
		// We hope, that most of the time we get enough "perfect" times in the first rounds
		// That way we can make all of this between 30 to 10 times faster
		start_t += search_mode * 60;
		end_t += search_mode * 60;
		if(end_t >= n.latest){
			//We dont need to continue, if we have enough
			best_indeces = malloc(sizeof(int)*poss_len);
			if(find_best_time(n, poss_starts, poss_ends, prefs, poss_len, best_indeces, best_indeces_len)){
				//we found that a time is possible, but we only want to quit if the avg of pref is below our tolerance
				int pref_avg = 0;
				for(int i=0; i < *best_indeces_len; i++){
					//TODO STARTHERE debug further
					//for some reason prefs[14] is -89234 or whatever, so not initialised.
					//But there are over 400 elements according to poss_max_i...
					pref_avg += prefs[best_indeces[i]];
				}
				pref_avg /= *best_indeces_len;
				if(pref_avg < WANTED_MAX_PREF_AVG)
					break;
			}
			free(best_indeces);

			//Count down the search modes, when mode=1 is done quit
			if(search_mode == 30)
				search_mode = 15;
			else if(search_mode == 15)
				search_mode = 10;
			else if(search_mode == 10)
				search_mode = 5;
			else if(search_mode == 5)
				search_mode = 1;
			else
				break;

			//reset the time, but skip the first date, as we did it already in the first round
			start_t = n.earliest;
			end_t = start_t+n.session_len_pref*60;
			start_t += search_mode * 60;
			end_t += search_mode * 60;
		}
	}
	printf("Successfull search mode: %d\n", search_mode);

	//Now we create the resulting events in c.
	//We need to add start, end and uid for each event.
	icalproperty *prop;
	icalcomponent **c = malloc(sizeof(icalproperty *)*(*best_indeces_len));
	for(int j=0; j < *best_indeces_len; j++){
		c[j] = icalcomponent_new(ICAL_VEVENT_COMPONENT);
		prop = icalproperty_new_dtstart(icaltime_from_timet_with_zone(poss_starts[best_indeces[j]], 0, zone));
		icalcomponent_add_property(c[j], prop);
		icalproperty_free(prop);
		prop = icalproperty_new_dtend(icaltime_from_timet_with_zone(poss_ends[best_indeces[j]], 0, zone));
		icalcomponent_add_property(c[j], prop);
		//Every event needs a custom UID that does not start with numbers
		//17 for autosec..mminl.de, 15 for random number and 1 for \0
		char *uid = malloc(sizeof(char)*33);
		create_uid(uid);

		prop = icalproperty_new_uid(uid);
		icalcomponent_add_property(c[j], prop);
		free(uid);
	}
	free(best_indeces);
	free(poss_starts);
	free(poss_ends);
	free(prefs);
	return c;
}

//@ret false if there is no combination of times, that fit.
//best_indeces is an array, which should be initialised with amount_possibles elements
//best_indeces_len is a pointer to a int

//TODO LATER This is not only not efficient, but also does not deliver good quality.
//There may often be times where better overall times were available, but we were not able to find them.
bool
find_best_time(needs n, time_t *starts, time_t *ends, float *prefs, int amount_possibles, int *best_indeces, int *best_indeces_len)
{
	//We want to first take the first best time.
	//Then, based on that, we search for the next best time, that also is compatible with the first time.
	//This is repeated until we meet the time requirements.
	if(amount_possibles == 0)
		return NULL;
	uint events_sum_len = 0;
	int i;
	for(i=0; events_sum_len < n.length*60; i++){
		best_indeces[i] = -1;
		for(int j=0; j < amount_possibles; j++){
			//We want to skip one instance of the for loop
			//if we find an overlap or have the same index as an event beforehand.
			//This is checked in the for loop with k
			for(int k=0; k < i; k++){
				if(timespans_ovlp(starts[best_indeces[k]],
								  ends[best_indeces[k]],
								  starts[j],
								  ends[j])){
					goto end_j_for;
				}
				if(j == best_indeces[k]){
					goto end_j_for;
		 		}
			}
			// init best_indeces[i] with the first valid time
			if(best_indeces[i] == -1)
				best_indeces[i] = j;
			else if(prefs[j] < prefs[best_indeces[i]])
				best_indeces[i] = j;
			end_j_for:
		}
		//TODO Understand this and write a better comment
		//Check if no valid time was found. If yes we dont have enough events_sum_len so we throw an error
		if(best_indeces[i] == -1)
			return false;

		events_sum_len += ends[best_indeces[i]] - starts[best_indeces[i]];
	}
	*best_indeces_len = i;
	//If events_sum_len > n.length*60 müssen wir gucken wie wir am besten kürzen.
	//Am besten zuerst plain bei einem alles, falls möglich und gucken ob das noch ok wäre.
	//Sonst irgendwie versuchen zwischen allen zu balancen.
	//TODO
	if(events_sum_len > n.length*60)
		printf("WARNING: time is longer than wanted! Still accepting");
	return true;
}


//Gibt eine Zahl zurück, die als Preferenz gesehen werden kann, je kleiner die Zahl, desto besser
float
timespan_pref(needs n, time_t start, time_t end)
{
	//Every option is evaluated beteen 0 and 1. Afterwards weighed and added
	time_t session_len = end-start;
	//session length
	float length_val;
	if(n.session_len_pref < session_len/60)
		length_val = (session_len/60-n.session_len_pref)/
			           (float)(n.session_len_max-n.session_len_pref);
	else if (n.session_len_pref > session_len/60)
		length_val = (n.session_len_pref-session_len/60)/
			           (float)(n.session_len_pref-n.session_len_min);
	else
		length_val = 0;

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
	float near_start_val;
	near_start_val = (float)(n.latest-end)/(n.latest-session_len);
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
timespan_is_ok(needs n, time_t start, time_t end)
{
	// Checks:
	// - disallowed
	// - in calendar
	if(timespan_is_in_calendar(start, end))
		return false;
	time_t time_temp;
	for(time_temp = start; time_temp < end; time_temp += 60)
	{
		if(time_is_in_datelist_array(n.disallowed, n.disallowed_len, icaltime_from_timet_with_zone(time_temp, 0, zone)))
			return false;
	}
	// Check:
	// - time requirements are met
	time_t len = end - start;
	if(len < n.session_len_min*60 || len > n.session_len_max*60)
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
	// If the datelist is all false, then begin never got activated and the time cant be in the datelist
	if(!begin)
		return false;
	//if all if's dont return false, then everything matches (the time is in the datelist!)
	return true;
}

bool
timespans_ovlp(time_t start1, time_t end1, time_t start2, time_t end2)
{
	if(start1 > end1 || start2 > end2){
		perror("timespans_ovlp(): illegal timespan inputs! Aborting!\n");
		exit(1);
	}
	if(end1 < start2 || end2 < start1)
		return false;
	return true;
}

// This checks if a time t is not applicable because at that time the calendar already contains an event
bool
timespan_is_in_calendar(time_t start_t, time_t end_t)
{
	//search for the nearest event
	int near_ind = search_nearest_event(events_count/2, events_count/2+1, start_t);
	//Search in both directions
	icalproperty *cstart = icalcomponent_get_first_property(events[near_ind], ICAL_DTSTART_PROPERTY);
	icalproperty *cend = icalcomponent_get_first_property(events[near_ind], ICAL_DTEND_PROPERTY);
	time_t near_startt = icaltime_as_timet(icalproperty_get_dtstart(cstart));
	time_t near_endt = icaltime_as_timet(icalproperty_get_dtend(cend));
	//first search <- back
	//We want to check until we are sure, that further back no event can reach start_t.
	//This unfortunately means, that we have to store events_longest the whole time, just for this check...
	for(int i=near_ind; i > 0 && start_t-near_endt < events_longest; i--){
		//fill near_startt/near_endt for new element
		cstart = icalcomponent_get_first_property(events[i], ICAL_DTSTART_PROPERTY);
		cend = icalcomponent_get_first_property(events[i], ICAL_DTEND_PROPERTY);
		near_startt = icaltime_as_timet(icalproperty_get_dtstart(cstart));
		near_endt = icaltime_as_timet(icalproperty_get_dtend(cend));
		if(timespans_ovlp(start_t, end_t, near_startt, near_endt))
			return true;
	}
	for(int i=near_ind; i < events_count && near_startt < end_t; i++){
		//fill near_startt/near_endt for new element
		cstart = icalcomponent_get_first_property(events[i], ICAL_DTSTART_PROPERTY);
		cend = icalcomponent_get_first_property(events[i], ICAL_DTEND_PROPERTY);
		near_startt = icaltime_as_timet(icalproperty_get_dtstart(cstart));
		near_endt = icaltime_as_timet(icalproperty_get_dtend(cend));
		if(timespans_ovlp(start_t, end_t, near_startt, near_endt))
			return true;
	}

	return false;
}

//TODO LATER rewrite this at some point
int
search_nearest_event(int start_index, int index_change, time_t t_start)
{
	//Best search algo i've every written \s
	
	//In the recursion we dont check, if start_index is out of bounce. We do it here
	if(start_index > events_count-1 || start_index < 0)
		return start_index - index_change;

	icalproperty *c = icalcomponent_get_first_property(events[start_index], ICAL_DTSTART_PROPERTY);
	icaltimetype t = icalproperty_get_dtstart(c);
	time_t event_start = icaltime_as_timet(t);

	
	if(event_start > t_start){
		if(index_change == 1){
			if(start_index == 0)
				return start_index;
			return start_index-1;
		}
		return search_nearest_event(start_index-index_change/2, index_change/2, t_start);
	}
	if(event_start < t_start){
		if(index_change == 1)
			return start_index;
		return search_nearest_event(start_index+index_change/2, index_change/2, t_start);
	}
	return start_index;
}

//Helper, that compares the date of 2 components. Needed for qsort(), in calendar_load_from_disk() and potentially other occurrences
int
events_compare_helper(const void *c1, const void *c2)
{
	icaltimetype t1 = icalproperty_get_dtstart(icalcomponent_get_first_property(*((icalcomponent**)c1), ICAL_DTSTART_PROPERTY));
	icaltimetype t2 = icalproperty_get_dtstart(icalcomponent_get_first_property(*((icalcomponent**)c2), ICAL_DTSTART_PROPERTY));
	return icaltime_compare(t1, t2);
}

//Helper, that compares the date of 2 components. Needed for qsort(), in calendar_load_from_disk() and potentially other occurrences
int
revents_compare_helper(const void *c1, const void *c2)
{
	icaltimetype t1 = icalproperty_get_dtend(icalcomponent_get_first_property(*((icalcomponent**)c1), ICAL_DTEND_PROPERTY));
	icaltimetype t2 = icalproperty_get_dtend(icalcomponent_get_first_property(*((icalcomponent**)c2), ICAL_DTEND_PROPERTY));
	return icaltime_compare(t1, t2);
}

bool
calendar_write_to_disk(icalcomponent **cal, int cal_len, char *path){
	icalcomponent *rootc = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

	//Add a few calendar properties ig?
	icalcomponent_add_property(rootc, icalproperty_new_version("2.0"));
	icalcomponent_add_property(rootc, icalproperty_new_version("-//autosec//alpha"));

	//Add all events and revents
	for(int i=0; i < cal_len; i++)
		icalcomponent_add_component(rootc, icalcomponent_new_clone(cal[i]));

	char *ical_string = icalcomponent_as_ical_string(rootc);

	FILE *f = fopen(path, "w");
	if(!f){
		perror("Wanted to write events to disk. Failed to open file");
		icalcomponent_free(rootc);
		return false;
	}

	fprintf(f, "%s", ical_string);
	fclose(f);

	icalcomponent_free(rootc);
	return true;
}

bool
calendar_load_from_disk(char *path)
{
	FILE* f = fopen(path, "r");
	if(!f)
		return false;
	icalparser *p = icalparser_new();
	if(!p){
		fclose(f);
		return false;
	}
	icalparser_set_gen_data(p, f);
	icalcomponent *rootc = icalparser_parse(p, *custom_fgets);
	icalparser_free(p);
	fclose(f);
	if(!rootc)
		return false;
	int new_events_count = icalcomponent_count_components(rootc, ICAL_VEVENT_COMPONENT);
	//We want to avoid reallocs, so we add enough space for all of the new events in both events and revents if needed
	if(events_count+new_events_count >= events_max){
		events = realloc(events, sizeof(icalcomponent*)*(events_max+new_events_count+10));
		events_max = events_max + new_events_count + 10;
	}
	if(revents_count+new_events_count >= revents_max){
		revents = realloc(revents, sizeof(icalcomponent*)*(revents_max+new_events_count+10));
		revents_max = revents_max + new_events_count + 10;
	}
	//Now fill the events read from the file(in component) into events and revents, checking for recurring(rrule) tag each time
	for(icalcomponent *event = icalcomponent_get_first_component(rootc, ICAL_VEVENT_COMPONENT);
	    event != NULL;
	    event=icalcomponent_get_next_component(rootc, ICAL_VEVENT_COMPONENT)){
		if(icalcomponent_get_first_property(event, ICAL_RRULE_PROPERTY) == NULL){
			events[events_count++] = icalcomponent_new_clone(event);
			//This(events_longest) is needed for some checks later on, so we just include it here, because its faster and bla bla
			icalproperty *cstart = icalcomponent_get_first_property(event, ICAL_DTSTART_PROPERTY);
			icalproperty *cend = icalcomponent_get_first_property(event, ICAL_DTEND_PROPERTY);
			time_t near_startt = icaltime_as_timet(icalproperty_get_dtstart(cstart));
			time_t near_endt = icaltime_as_timet(icalproperty_get_dtstart(cend));
			if(events_longest < near_endt - near_startt)
				events_longest = near_endt - near_startt;
		} else
			revents[revents_count++] = icalcomponent_new_clone(event);
	}

	qsort(events, events_count, sizeof(icaltimetype*), events_compare_helper);
	qsort(revents, revents_count, sizeof(icaltimetype*), revents_compare_helper);

	for(int i=0; i < events_count; i++){
		printf("Nr.%d\n%s\n\n", i+1, icalcomponent_as_ical_string(events[i]));
	}

	printf(":::NOW REVENTS:::\n");
	for(int i=0; i < revents_count; i++){
		printf("Nr.%d\n%s\n\n", i+1, icalcomponent_as_ical_string(revents[i]));
	}
	icalcomponent_free(rootc);
	return true;
}

char*
custom_fgets(char *s, size_t size, void *d)
{
	return fgets(s, size, (FILE*)d);
}

bool
needs_to_string(needs n, char* out, int out_len)
{
	// We first store all static information
	int ret = snprintf(out, out_len, "%d;%d;%d;%d;%d;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;",
	           n.length, n.priority, n.session_len_min, n.session_len_max, n.session_len_pref, n.earliest,
	           n.latest, n.max_per_day, n.max_per_week, n.max_per_month,
	           n.max_per_year, n.min_per_day, n.min_per_week, n.min_per_month, n.min_per_year,
	           n.pref_per_day, n.pref_per_week, n.pref_per_month, n.pref_per_year);
	if(ret-out_len > 0)
		return false;

	//Then we store the disallowed and preferred array (+ their size), which size can vary
	char disallowed_len[20];
	sprintf(disallowed_len, "%d;", n.disallowed_len);
	if(strlen(disallowed_len) > out_len-strlen(out))
		return false;
	strcat(out, disallowed_len);

	char disallowed[DATELIST_STRING_LEN];
	for(int i=0; i < n.disallowed_len; i++){
		datelist_to_string(n.disallowed[i], disallowed, DATELIST_STRING_LEN);
		if(strlen(disallowed)+1 > out_len-strlen(out))
			return false;
		strcat(out, disallowed);
	}

	char preferred_len[20];
	sprintf(preferred_len, ";%d;", n.preferred_len);
	if(strlen(preferred_len) > out_len-strlen(out))
		return false;
	strcat(out, disallowed_len);

	char preferred[DATELIST_STRING_LEN];
	for(int i=0; i < n.disallowed_len; i++){
		datelist_to_string(n.preferred[i], preferred, DATELIST_STRING_LEN);
		if(strlen(preferred) > out_len-strlen(out))
			return false;
		strcat(out, preferred);
	}
	return true;
}

bool
datelist_to_string(datelist d, char* out, int out_len)
{
	char min[61], hour[25], wday[8], mday[32], month[13]; 
	bool_arr_to_string(d.minute, 60, min);
	bool_arr_to_string(d.hour, 24, hour);
	bool_arr_to_string(d.wday, 7, wday);
	bool_arr_to_string(d.mday, 31, mday);
	bool_arr_to_string(d.month, 12, month);
	int ret = snprintf(out, out_len, "%s,%s,%s,%s,%s;", min, hour, wday, mday, month);
	if(ret-out_len > 0)
		return false;
	return true;
}

void
bool_arr_to_string(bool *arr, int arr_len, char *out){
	out[0] = '\0';
	for(int i=0; i < arr_len; i++){
		out[i] = arr[i] + '0';
	}
	out[arr_len] = '\0';
}

//@in string to convert and pointers to initialised datelists.
//This function will malloc the datelists, and attach it to the need
//This meens, the calling function still has the responsibility for that memory, in form of the need!
needs
string_to_needs(char *str)
{
	needs n;
	char *disallowed_str = malloc(sizeof(char) * DATELIST_STRING_LEN * DISALLOWED_DATELIST_AMOUNT_MAX);
	char *preferred_str = malloc(sizeof(datelist) * DATELIST_STRING_LEN * PREFERRED_DATELIST_AMOUNT_MAX);

	int ret = sscanf(str, "%d;%d;%d;%d;%d;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%[^;];%d;%[^;];\n",
	  &n.length, &n.priority, &n.session_len_min, &n.session_len_max, &n.session_len_pref, &n.earliest,
	  &n.latest, &n.max_per_day, &n.max_per_week, &n.max_per_month,
	  &n.max_per_year, &n.min_per_day, &n.min_per_week, &n.min_per_month, &n.min_per_year,
	  &n.pref_per_day, &n.pref_per_week, &n.pref_per_month, &n.pref_per_year,
	  &n.disallowed_len, disallowed_str, &n.preferred_len, preferred_str);
	//Check if all 23 %XX arguments were matched successfully
	if(ret != 23){
		printf("\nret:%d\n", ret);
		perror("ERROR converting string to need! Exiting\n");
		exit(1);
	}

	n.disallowed = malloc(sizeof(datelist)*n.disallowed_len);
	n.preferred = malloc(sizeof(datelist)*n.preferred_len);

	//we need a temporary storage for the datelists we extract each for rotation
	char d_temp[DATELIST_STRING_LEN+1];

	for(int i=0; i < n.disallowed_len; i++){
		splitString(disallowed_str, DATELIST_STRING_LEN, d_temp, disallowed_str);
		n.disallowed[i] = string_to_datelist(d_temp);
	}

	for(int i=0; i < n.disallowed_len; i++){
		splitString(preferred_str, DATELIST_STRING_LEN, d_temp, preferred_str);
		n.preferred[i] = string_to_datelist(d_temp);
	}

	return n;
}

datelist
string_to_datelist(char *str)
{
	char min_str[61], hour_str[25], wday_str[8], mday_str[32], month_str[13];
	int ret = sscanf(str, "%[^,],%[^,],%[^,],%[^,],%[^,];", min_str, hour_str, wday_str, mday_str, month_str);
	if(ret != 5){
		perror("Error converting string to datelist! Exiting...\n");
		exit(1);
	}
	datelist d;

	string_to_bool_arr(min_str, d.minute);
	string_to_bool_arr(hour_str, d.hour);
	string_to_bool_arr(wday_str, d.wday);
	string_to_bool_arr(mday_str, d.mday);
	string_to_bool_arr(month_str, d.month);

	return d;
}

void
string_to_bool_arr(char *str, bool *arr)
{
	int len = strlen(str);
	for(int i=0; i < len; i++){
		if(str[i] == '1')
			arr[i] = true;
		else
			arr[i] = false;
	}
	return;
}

int
main(void)
{

	srand(time(NULL));
	//first set the timezone
	zone = icaltimezone_get_builtin_timezone_from_offset(1, "Berlin");

	calendar_load_from_disk("input.ics");

	time_t earliest;
	time(&earliest);
	needs n;
	init_needs(&n, 900, 0, 300, 300, 300, earliest, earliest+60*60*24*3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	n.disallowed = malloc(sizeof(datelist));
	init_datelist(n.disallowed);
	n.disallowed_len = 1;
	for(int i=0; i < 60; i++){
		if(i < 24)
			n.disallowed[0].hour[i] = false;
		if(i < 7)
			n.disallowed[0].wday[i] = false;
		if(i < 12)
			n.disallowed[0].month[i] = false;
		if(i < 31)
			n.disallowed[0].mday[i] = false;
		n.disallowed[0].minute[i] = false;
	}
	n.disallowed[0].wday[2] = false;
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

	char out[9000];
	if(!needs_to_string(n, out, 9000)){
		printf("ferhele1");
		return 1;
	}

	int event_len;
	icalcomponent **event = event_new(n, &event_len);
	if(event == NULL){
		printf("Couldnt find a time for you. Sorry!\n");
		exit(1);
	}

	
	char *needs_name = "EXAMPLE_NAME";
	for(int i=0; i < event_len; i++){
		icalproperty *groupname = icalproperty_new(ICAL_CATEGORIES_PROPERTY);
		icalproperty_set_categories(groupname, needs_name);
    icalcomponent_add_property(event[i], groupname);
    icalproperty_free(groupname);

    icalproperty *xneeds = icalproperty_new_x("X-NEEDS");
		icalproperty_set_x_name(xneeds, "X-NEEDS");
		icalproperty_set_value(xneeds, icalvalue_new_text(out));
    icalcomponent_add_property(event[i], xneeds);
		icalproperty_free(xneeds);
	}
	

	calendar_write_to_disk(events, events_count, "events_o.ics");
	calendar_write_to_disk(revents, revents_count, "revents_o.ics");
	calendar_write_to_disk(event, event_len, "new_o.ics");

	for(int i=0; i < event_len; i++){
		printf("Event Nr. %d:\n", i);
		printf("DTSTART: %s", icaltime_as_ical_string(icalproperty_get_dtstart(icalcomponent_get_first_property(event[i], ICAL_DTSTART_PROPERTY))));
		printf("DTEND  : %s\n", icaltime_as_ical_string(icalproperty_get_dtend(icalcomponent_get_next_property(event[i], ICAL_DTEND_PROPERTY))));
		icalcomponent_free(event[i]);
	}


	free(n.disallowed);
	free(n.preferred);
	for(int i=0; i < events_count; i++)
		icalcomponent_free(events[i]);
	for(int i=0; i < revents_count; i++)
		icalcomponent_free(revents[i]);
	free(events);
	free(revents);
	free(event);
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
