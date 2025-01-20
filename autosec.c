#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

struct
chunk
{
	time_t start;
	time_t end;
};

//deep copy an int array
void
copy_array_int(int *src, int *dest, int len)
{
	for(int i=0; i < len; i++){
		dest[i] = src[i];
	}
}

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
// We return NULL if we couldnt find any possible time
// the icalcomponent **c array of pointers is returned with a "library malloc", so it has to be freed, by the calling function!
icalcomponent **
event_new(needs n, int *best_indeces_len)
{
	//Finding the right chunks for the event is key. We do this in a 2 step process
	//1. calculate all possible chunks for every pref threshold (e.g. 0.0, 0.2)
	//every chunk under that threshold is in the respective chunk array.
	//2. try to find a combination of best times for every chunk array.
	//First try the 0.0 pref chunks, if that works exit. Otherwise repeat with 0.2, etc.
	//2.1 There are several key things in arranging times that have impact on chunk_pref and overall pref:
	//pref per day/week etc, pref_dist, session_len_pref and maybe more in the future
	//To accord for these we first try with everything enabled, then disable them one by one/combine them.
	//2.2 When we found a functioning compromise with prefs disabled and enabled we try
	//to recover some of the disabled prefs by rearranging times and lengths were possible

	//Step 1
	chunk *chunk_00, *chunk_02;
	int chunk_00_index, chunk_02_index;
	calculate_chunks(n, &chunk_00, &chunk_00_index, &chunk_02, &chunk_02_index);

	icalcomponent **event_00 = malloc(chunk_00_index * sizeof(icalcomponent*));
	icalcomponent **event_02 = malloc(chunk_02_index * sizeof(icalcomponent*));

	for(int i=0; i < chunk_00_index; i++){
		event_00[i] = chunk_to_event(chunk_00[i]);
	}

	for(int i=0; i < chunk_02_index; i++){
		event_02[i] = chunk_to_event(chunk_02[i]);
	}
	calendar_write_to_disk(event_00, chunk_00_index, "chunk_00.ics");
	calendar_write_to_disk(event_02, chunk_02_index, "chunk_02.ics");

	//Step 2
	chunk *sessions;
	int sessions_len = 0;
	sessions = calculate_sessions_based_on_chunks(n, chunk_00, chunk_00_index, &sessions_len);
	//sessions = calculate_sessions_based_on_chunks(n, chunk_02, chunk_00_index, &sessions_len);

	icalcomponent **events = malloc(sessions_len * sizeof(icalcomponent*));
	for(int i=0; i < sessions_len; i++){
		events[i] = chunk_to_event(sessions[i]);
	}
	calendar_write_to_disk(events, sessions_len, "sessions.ics");
	return NULL;
}

chunk *
calculate_sessions_based_on_chunks(needs n, chunk *chunks, int chunks_len, int *sessions_len)
{
	//We try to respect all preferrences. We will disable them one by one later on if needed
	bool PREF_PER_ENABLED = true;
	bool PREF_DIST_ENABLED = true;
	bool PREF_LEN_ENABLED = true;

	//we init sessions for most possible amount of sessions
	int sessions_maxsize = (n.length/n.session_len_min)+1;
	chunk *sessions = malloc(sessions_maxsize * sizeof(chunk));
	*sessions_len = 0;

	//We track the total length of all used chunks for the current sessions scheduling
	while(PREF_PER_ENABLED || PREF_DIST_ENABLED || PREF_LEN_ENABLED){
		int i=0;
		int totallen = 0;
		*sessions_len = 0;
		//We go through every chunk. We only move on if the chunk is too small to contain another event
		for(i=0; i < chunks_len && totallen < n.length; i++){
			//we know that every chunk is at least n.session_len_min long and therefor we write the start here already.
			//If we skip this chunk because of preference next iteration of for will just overwrite
			sessions[*sessions_len].start = chunks[i].start;
			if(!PREF_LEN_ENABLED){
				if(chunk_len(chunks[i]) < n.session_len_pref*60){
					sessions[*sessions_len].end = chunks[i].end;
					totallen += chunk_len(sessions[*sessions_len])/60;
				} else {
					sessions[*sessions_len].end = chunks[i].start + n.session_len_pref*60;
					totallen += n.session_len_pref;
				}
			}
			else if(PREF_LEN_ENABLED && chunk_len(chunks[i])>= n.session_len_pref*60){
					sessions[*sessions_len].end = chunks[i].start + n.session_len_pref*60;
					totallen += n.session_len_pref;
			} else {
				//if we branch here we do not want to add a session in this for iteration. We skip all steps and go to the next one
				continue;
			}
			//We want to increase i only when going go the next chunk.
			//We do not by default go to the next chunk however, because we only cut parts out for a session.
			//Check if the chunk is still big enough for another session
			//cut the extracted event from chunks[i]
			chunks[i].start = sessions[*sessions_len].end;
			if(chunk_len(chunks[i]) >= n.session_len_pref*60)
				i--;

			(*sessions_len)++;

			//TODO Now we disable all further times based on PREF_DIST and PREF_PER if enabled
		}
		//Now we get to the second part of making the times better again, by making it abide the closest to the prefs disabled
		//However we only do that, if we got enough totallen of the sessions
	
		//Here we check if we have unchecked chunks left, which could be better fits than the selected chunks
		while(!PREF_LEN_ENABLED && i < chunks_len && totallen >= n.length){
			//the worst index is always the smallest because we never make sessions longer than n.session_len_pref
			int worst_i = smallest_chunk(sessions, *sessions_len);
			//Check if the not yet checked chunks[i] is better then the worst element selected.
			//If yes, swap them (but max n.session_len_pref)
			if(n.session_len_pref*60 - chunk_len(chunks[i]) <
			   n.session_len_pref*60 - chunk_len(sessions[worst_i])){
				sessions[worst_i].start = chunks[i].start;
				sessions[worst_i].end = chunks[i].end;
				//if chunks[i] is longer than n.session_len_pref make the event only n.session_len_pref long
				if(chunk_len(chunks[i]) > n.session_len_pref*60){
					sessions[worst_i].end = sessions[worst_i].start + n.session_len_pref*60;
				}
				chunks[i].start = sessions[worst_i].end;
			}

			i++;
		}

		//TODO Here we check if we covered good chunks. We look if the covered chunks are better than the covering.
		//We also have to check if the new chunks would cover other chunks, especially chunks used.
		//Then we have to calculate if changing out the chunks is a good idea or not


		//TODO Here we try to have most events inside / partially inside the best possible time_pref zone.
		//This is still a big problem! We dont pass the zones(the function doesnt know..), I dont know how to calculate this

		//if totallen > n.length we have to cut down on the lengths of events
		//and if possible remove events completely until totallen = n.length
		while(totallen > n.length){
			int worst_i = smallest_chunk(sessions, *sessions_len);
			if(totallen-chunk_len(sessions[worst_i])/60 >= n.length){
				totallen -= chunk_len(sessions[worst_i])/60;
				sessions[worst_i].start = sessions[*sessions_len-1].start;
				sessions[worst_i].end = sessions[*sessions_len-1].end;
				sessions_len--;
			} else {
				//TODO DECIDE (maybe config) if we want to split up the overlength on all big events or cut few as short as needed/possible
				//TODO "highly" inefficient, but i dont have a good way of getting the second biggest right now.
				int biggest_i = biggest_chunk(sessions, *sessions_len);
				if(totallen-10 < n.length){
					sessions[biggest_i].end -= n.length - totallen;
					totallen -= n.length - totallen;
				} else {
					sessions[biggest_i].end -= 10;
					totallen -= 10;
				}
			}
		}

		//if we got the perfect length everything worked and we can finish
		if(totallen == n.length)
			break;

		//disable the prefs one by one each iteration by one
		if(PREF_LEN_ENABLED)
			PREF_LEN_ENABLED = false;
		else if(PREF_DIST_ENABLED)
			PREF_DIST_ENABLED = false;
		else if(PREF_PER_ENABLED)
			PREF_PER_ENABLED = false;
	}
	return sessions;
}

//returns the index of the smallest chunk in an chunk array
int
smallest_chunk(chunk *arr, int arrlen)
{
	if(arrlen == 0)
		return -1;
	int smallest = 0;
	for(int i=0; i < arrlen; i++){
		if(chunk_len(arr[i]) < chunk_len(arr[smallest]))
			smallest = i;
	}
	return smallest;
}

//returns the index of the smallest chunk in an chunk array
int
biggest_chunk(chunk *arr, int arrlen)
{
	if(arrlen == 0)
		return -1;
	int biggest = 0;
	for(int i=0; i < arrlen; i++){
		if(chunk_len(arr[i]) > chunk_len(arr[biggest]))
			biggest = i;
	}
	return biggest;
}

//returns the length of a chunk
int
chunk_len(chunk c)
{
	return c.end - c.start;
}

//TODO LATER this needs to rearrange arr completely
/*
void
delete_chunk_from_chunk_array(chunk *arr, chunk arrlen, chunk deletechunk)
{
	for(int i=0; i < arrlen; i++){
		if(timespans_ovlp(arr[i].start, arr[i].end, deletechunk.start, deletechunk.end)){
			
		}
	}
}
*/

//Calculate all the chunks for the different pref gradations
//@ret return the chunks in chunk_00, chunk_02 etc and the size of the chunks
void
calculate_chunks(needs n, chunk **chunk_00, int *chunk_00_index, chunk **chunk_02, int *chunk_02_index)
{
	//Guess how many chunks in the arrays (chunk_00, chunk_02, ...) are
	#define CHUNKARRAY_START_SIZE 100

	//This tracks if we are on a streak with the timechunks (e.g. 0.0 pref, 0.2 pref etc.) aka was the last time in the timechunk
	int chunk_00_active = false;
	int chunk_02_active = false;

	*chunk_00 = malloc(CHUNKARRAY_START_SIZE * sizeof(chunk));
	*chunk_02 = malloc(CHUNKARRAY_START_SIZE * sizeof(chunk));

	int chunk_00_maxsize = CHUNKARRAY_START_SIZE;
	int chunk_02_maxsize = CHUNKARRAY_START_SIZE;

	*chunk_00_index = 0;
	*chunk_02_index = 0;

	//Check the pref value for every minute and categories timespans accordingly in different gradations(abstuffungen)
	for(time_t i=n.earliest; i < n.latest; i++){
		//if the time is not allowed we end all current active chunks
		//We only save those chunks that are >=session_len_min
		if(time_is_in_datelist_array(n.disallowed, n.disallowed_len, i) || time_is_in_calendar(i)){
			if(chunk_00_active == true){
				if(i - (*chunk_00)[*chunk_00_index].start >= n.session_len_min*60)
					(*chunk_00)[(*chunk_00_index)++].end = i;
				chunk_00_active = false;
			}
			if(chunk_02_active == true){
				if(i - (*chunk_02)[*chunk_02_index].start >= n.session_len_min*60)
					(*chunk_02)[(*chunk_02_index)++].end = i;
				chunk_02_active = false;
			}
		} else {
			int pref = time_pref(n, i);
			//if the time is allowed we get the pref value and check if the chunks are not started.
			//if they are not started we start them and fill the start with i.
			//If the are already started we have to do nothing, as we only need to fill the end, and that is done above or at the end
			if(pref <= 0 && chunk_00_active == false){
				if(*chunk_00_index == chunk_00_maxsize){
					*chunk_00 = realloc(*chunk_00, chunk_00_maxsize*2 * sizeof(chunk));
					chunk_00_maxsize *= 2;
				}
				(*chunk_00)[*chunk_00_index].start = i;
				chunk_00_active = true;
			}
			if(pref <= 2 && chunk_02_active == false){
				if(*chunk_02_index == chunk_02_maxsize){
					(*chunk_02) = realloc(*chunk_02, chunk_02_maxsize*2 * sizeof(chunk));
					chunk_02_maxsize *= 2;
				}
				(*chunk_02)[*chunk_02_index].start = i;
				chunk_02_active = true;
			}
		}
	}
	//at the end we have to check if chunks are still active. If yes deactivate them
	if(chunk_00_active == true){
		if(n.latest - (*chunk_00)[*chunk_00_index].start >= n.session_len_min*60)
			(*chunk_00)[(*chunk_00_index)++].end = n.latest;
		chunk_00_active = false;
	}
	if(chunk_02_active == true){
		if(n.latest - (*chunk_02)[*chunk_02_index].start >= n.session_len_min*60)
			(*chunk_02)[(*chunk_02_index)++].end = n.latest;
		chunk_02_active = false;
	}
}

//@ret a new icalcomponent. the caller has to free it!
icalcomponent*
chunk_to_event(chunk c)
{
	icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
	icalproperty *p;
	p = icalproperty_new_dtstart(icaltime_from_timet_with_zone(c.start, false, zone));
	icalcomponent_add_property(event, p);
	p = icalproperty_new_dtend(icaltime_from_timet_with_zone(c.end, false, zone));
	icalcomponent_add_property(event, p);
	return event;
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
		if(!time_is_in_datelist_array(n.preferred, n.preferred_len, start+60*i))
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

//calculate pref value of a specific time
int
time_pref(needs n, time_t t)
{
	//For now everything is worth 2, this should later be changeable by config (and maybe also change defaults later on)
	//We start with 2, as if the time is preferred its better, so we have to subtract 2. we dont want values under 0 i think
	int pref = 2;
	if(time_is_in_datelist_array(n.preferred, n.preferred_len, t))
		pref -= 2;
	//TODO LATER add more pref arguments if needed
	return pref;
}

// This checks if a time t is contained in one of the datelists d
bool
time_is_in_datelist_array(datelist *d, int d_len, time_t t)
{
	icaltimetype time = icaltime_from_timet_with_zone(t, false, zone);
	for(int i=0; i < d_len; i++){
		if(time_is_in_datelist(d[i], time))
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

//calculate if the given time is in one of the loaded events/revents
//TODO inefficient, maybe store all events in a min buffer/chunk buffer that is easier/faster to check (we have to do many checks)
//TODO revents is not included yet, not sure how to implement, add until t is bigger than the start?
bool
time_is_in_calendar(time_t t)
{
	for(int i=0; i < events_count; i++){
		icalproperty *cstart = icalcomponent_get_first_property(events[i], ICAL_DTSTART_PROPERTY);
		icalproperty *cend = icalcomponent_get_first_property(events[i], ICAL_DTEND_PROPERTY);
		icalproperty *cduration = icalcomponent_get_first_property(events[i], ICAL_DURATION_PROPERTY);
		time_t startt, endt;
		startt = icaltime_as_timet(icalproperty_get_dtstart(cstart));
		if(cend == NULL){
			struct icaldurationtype duration = icalproperty_get_duration(cduration);
			endt = startt + (time_t)icaldurationtype_as_int(duration);
		} else {
			endt = icaltime_as_timet(icalproperty_get_dtstart(cend));
		}

		if(startt <= t && endt >= t)
			return true;
	}
	return false;
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
	init_needs(&n, 2000, 0, 100, 300, 300, earliest, earliest+60*60*24*3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
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
	n.disallowed[0].wday[2] = true;
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
