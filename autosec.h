typedef struct datelist datelist;
typedef struct needs needs;
typedef struct chunk chunk;

void copy_array_int(int *src, int *dest, int len);
void split_string(char *str, int i, char *left, char *right);
void init_datelist(datelist *d);
void create_uid(char* uid);
void init_needs(needs *n, uint length, uint priority, uint session_length_min, uint session_length_max,
					 uint session_length_pref, time_t earliest, time_t latest,
					 uint max_per_day, uint max_per_week, uint max_per_month, uint max_per_year,
					 uint min_per_day, uint min_per_week, uint min_per_month, uint min_per_year,
					 uint pref_per_day, uint pref_per_week, uint pref_per_month, uint pref_per_year);
bool is_array_false(bool *a, int a_len);
void icaltime_copy(icaltimetype *dest, icaltimetype src);
icalcomponent ** event_new(needs n, int *best_indeces_len);

chunk* calculate_sessions_based_on_chunks(needs n, chunk *chunks, int chunks_len, int *events_len);
int smallest_chunk(chunk *arr, int arrlen);
int biggest_chunk(chunk *arr, int arrlen);
int chunk_len(chunk c);
void calculate_chunks(needs n, chunk **chunk_00, int *chunk_00_index, chunk **chunk_02, int *chunk_02_index);
icalcomponent* chunk_to_event(chunk c);

float timespan_pref(needs n, time_t start_t, time_t end_t);
int time_pref(needs n, time_t t);
bool time_is_in_datelist_array(datelist *d, int d_len, time_t t);
bool time_is_in_datelist(datelist d, icaltimetype t);
bool time_is_in_calendar(time_t t);
bool timespans_ovlp(time_t start1, time_t end1, time_t start2, time_t end2);
int search_nearest_event(int start_index, int index_change, time_t t_start);
int events_compare_helper(const void *c1, const void *c2);
int revents_compare_helper(const void *c1, const void *c2);
bool calendar_write_to_disk(icalcomponent **cal, int cal_len, char* path);
bool calendar_load_from_disk(char* path);
char* custom_fgets(char* s, size_t size, void *d);
bool needs_to_string(needs n, char* out, int out_len);
bool datelist_to_string(datelist d, char* out, int out_len);
void bool_arr_to_string(bool *arr, int arr_len, char*out);
needs string_to_needs(char *str);
datelist string_to_datelist(char *str);
void string_to_bool_arr(char *str, bool *arr);
