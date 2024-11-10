typedef struct datelist datelist;
typedef struct needs needs;

void init_datelist(datelist *d);
void init_needs(needs *n, uint length, uint priority, uint session_length_min, uint session_length_max,
					 uint session_length_pref, icaltimetype earliest, icaltimetype latest,
					 uint max_per_day, uint max_per_week, uint max_per_month, uint max_per_year,
					 uint min_per_day, uint min_per_week, uint min_per_month, uint min_per_year,
					 uint pref_per_day, uint pref_per_week, uint pref_per_month, uint pref_per_year);
bool is_array_false(bool *a, int a_len);
void icaltime_copy(icaltimetype *dest, icaltimetype src);
bool event_new(needs n, icalcomponent *c);
float timespan_pref(needs n, icaltimetype start_t, icaltimetype end_t);
bool timespan_is_ok(needs n, icaltimetype start_t, icaltimetype end_t);
bool time_is_in_datelist_array(datelist *d, int d_len, icaltimetype t);
bool time_is_in_datelist(datelist d, icaltimetype t);
bool time_is_in_calendar(icaltimetype t);
bool load_events_from_disk(char* path);
char* custom_fgets(char* s, size_t size, void *d);
