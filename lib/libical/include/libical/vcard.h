#ifndef LIBICAL_VCARD_H
#define LIBICAL_VCARD_H
#ifndef S_SPLINT_S
#ifdef __cplusplus
extern "C" {
#endif
/*======================================================================
 FILE: vcardenumarray.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDENUMARRAY_H
#define VCARDENUMARRAY_H

#include "libical_vcard_export.h"
#include "icalarray.h"

#include <stdlib.h>

typedef icalarray vcardenumarray;

typedef struct {
    int val;
    const char *xvalue;
} vcardenumarray_element;

#define vcardenumarray_new(increment_size) \
    icalarray_new(sizeof(vcardenumarray_element), increment_size)

#define vcardenumarray_element_at(array, position) \
    ((const vcardenumarray_element *)icalarray_element_at(array, position))

#define vcardenumarray_size(array) ((array)->num_elements)

LIBICAL_VCARD_EXPORT ssize_t vcardenumarray_find(vcardenumarray *array,
                                                 vcardenumarray_element *needle);

LIBICAL_VCARD_EXPORT void vcardenumarray_append(vcardenumarray *array,
                                                vcardenumarray_element *elem);

LIBICAL_VCARD_EXPORT void vcardenumarray_add(vcardenumarray *array,
                                             vcardenumarray_element *add);

LIBICAL_VCARD_EXPORT void vcardenumarray_remove_element_at(vcardenumarray *array,
                                                           ssize_t position);
LIBICAL_VCARD_EXPORT void vcardenumarray_remove(vcardenumarray *array,
                                                vcardenumarray_element *del);

LIBICAL_VCARD_EXPORT void vcardenumarray_free(vcardenumarray *array);

LIBICAL_VCARD_EXPORT void vcardenumarray_sort(vcardenumarray *array);

#endif /* VCARDENUMARRAY_H */

/*======================================================================
 FILE: vcardstrarray.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDSTRARRAY_H
#define VCARDSTRARRAY_H

#include "libical_vcard_export.h"
#include "icalarray.h"

#include <stdlib.h>

typedef icalarray vcardstrarray;

#define vcardstrarray_new(increment_size) \
    icalarray_new(sizeof(char *), increment_size)

#define vcardstrarray_element_at(array, position) \
    *((const char **)icalarray_element_at(array, position))

#define vcardstrarray_size(array) ((array)->num_elements)

LIBICAL_VCARD_EXPORT ssize_t vcardstrarray_find(vcardstrarray *array,
                                                const char *needle);

LIBICAL_VCARD_EXPORT void vcardstrarray_append(vcardstrarray *array,
                                               const char *elem);

LIBICAL_VCARD_EXPORT void vcardstrarray_add(vcardstrarray *array,
                                            const char *add);

LIBICAL_VCARD_EXPORT void vcardstrarray_remove_element_at(vcardstrarray *array,
                                                          ssize_t position);

LIBICAL_VCARD_EXPORT void vcardstrarray_remove(vcardstrarray *array,
                                               const char *del);

LIBICAL_VCARD_EXPORT void vcardstrarray_free(vcardstrarray *array);

LIBICAL_VCARD_EXPORT void vcardstrarray_sort(vcardstrarray *array);

LIBICAL_VCARD_EXPORT char *vcardstrarray_as_vcard_string_r(const vcardstrarray *array,
                                                           const char sep);

#endif /* VCARDSTRARRAY_H */

/*======================================================================
 FILE: vcardstructured.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDSTRUCTURED_H
#define VCARDSTRUCTURED_H

#include "libical_vcard_export.h"


#define VCARD_MAX_STRUCTURED_FIELDS 20 // Extended ADR currently uses 18

typedef struct vcardstructuredtype {
    unsigned num_fields;
    vcardstrarray *field[VCARD_MAX_STRUCTURED_FIELDS];
} vcardstructuredtype;

LIBICAL_VCARD_EXPORT vcardstructuredtype *vcardstructured_new(void);

LIBICAL_VCARD_EXPORT char *vcardstructured_as_vcard_string_r(const vcardstructuredtype *s,
                                                             int is_param);

LIBICAL_VCARD_EXPORT vcardstructuredtype *vcardstructured_from_string(const char *s);

LIBICAL_VCARD_EXPORT void vcardstructured_free(vcardstructuredtype *s);

#endif /* VCARDSTRUCTURED_H */

/*======================================================================
 FILE: vcardtime.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDTIME_H
#define VCARDTIME_H

#include "libical_vcard_export.h"

typedef struct vcardtimetype {
    int year;   /* 0000-9999 */
    int month;  /* 01 (Jan) to 12 (Dec). */
    int day;    /* 01-28/29/30/31 depending on month and leap year */
    int hour;   /* 00-23 */
    int minute; /* 00-59 */
    int second; /* 00-58/59/60 depending on leap second */
    /* vCard v3 allows fractional sec, but v4 does not.  We parse and ignore */
    int utcoffset; /* -720 to +840 minutes (-12:00 to +14:00) */
} vcardtimetype;

#define vcardtime_null_date() vcardtime_null_datetime()
#define vcardtime_null_time() vcardtime_null_datetime()
#define vcardtime_null_timestamp() vcardtime_null_datetime()

LIBICAL_VCARD_EXPORT vcardtimetype vcardtime_null_datetime(void);
LIBICAL_VCARD_EXPORT vcardtimetype vcardtime_current_utc_time(void);

LIBICAL_VCARD_EXPORT int vcardtime_is_null_datetime(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_time(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_date(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_datetime(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_timestamp(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_utc(const vcardtimetype t);
LIBICAL_VCARD_EXPORT int vcardtime_is_leap_year(const int year);
LIBICAL_VCARD_EXPORT int vcardtime_is_valid_time(const struct vcardtimetype t);

#define VCARDTIME_BARE_TIME (0x1) /* 'T' not needed for TIME */
#define VCARDTIME_AS_V4 (0x2)     /* allow partial date and/or time */

LIBICAL_VCARD_EXPORT const char *vcardtime_as_vcard_string(const vcardtimetype t,
                                                           unsigned flags);
LIBICAL_VCARD_EXPORT char *vcardtime_as_vcard_string_r(const vcardtimetype t,
                                                       unsigned flags);

LIBICAL_VCARD_EXPORT vcardtimetype vcardtime_from_string(const char *str,
                                                         int is_bare_time);

#endif /* VCARDTIME_H */

/*======================================================================
 FILE: vcardtypes.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDTYPES_H
#define VCARDTYPES_H

#include "libical_vcard_export.h"

typedef struct vcardgeotype {
    const char *uri;
    struct {
        const char *lat;
        const char *lon;
    } coords;
} vcardgeotype;

typedef struct vcardtztype {
    const char *tzid;
    const char *uri;
    int utcoffset;
} vcardtztype;

#endif /* VCARDTYPES_H */

/*======================================================================
 FILE: vcardderivedvalue.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDVALUE_H
#define VCARDDERIVEDVALUE_H

#include "libical_vcard_export.h"


typedef enum vcard_n_field {
    VCARD_N_FAMILY = 0,
    VCARD_N_GIVEN,
    VCARD_N_ADDITIONAL,
    VCARD_N_PREFIX,
    VCARD_N_SUFFIX,
    /* draft-ietf-calext-jscontact-vcard */
    VCARD_N_SECONDARY,
    VCARD_N_GENERATION,
    VCARD_NUM_N_FIELDS
} vcard_n_field;

typedef enum vcard_gender_field {
    VCARD_GENDER_SEX = 0,
    VCARD_GENDER_TEXT,
    VCARD_NUM_GENDER_FIELDS
} vcard_gender_field;

typedef enum vcard_adr_field {
    VCARD_ADR_PO_BOX = 0,
    VCARD_ADR_EXTENDED,
    VCARD_ADR_STREET,
    VCARD_ADR_LOCALITY,
    VCARD_ADR_REGION,
    VCARD_ADR_POSTAL_CODE,
    VCARD_ADR_COUNTRY,
    /* draft-ietf-calext-jscontact-vcard */
    VCARD_ADR_ROOM,
    VCARD_ADR_APARTMENT,
    VCARD_ADR_FLOOR,
    VCARD_ADR_STREET_NUMBER,
    VCARD_ADR_STREET_NAME,
    VCARD_ADR_BUILDING,
    VCARD_ADR_BLOCK,
    VCARD_ADR_SUBDISTRICT,
    VCARD_ADR_DISTRICT,
    VCARD_ADR_LANDMARK,
    VCARD_ADR_DIRECTION,
    VCARD_NUM_ADR_FIELDS
} vcard_adr_field;

typedef enum vcard_clientpidmap_field {
    VCARD_CLIENTPIDMAP_ID = 0,
    VCARD_CLIENTPIDMAP_URI,
    VCARD_NUM_CLIENTPIDMAP_FIELDS
} vcard_clientidmap_field;

typedef struct vcardvalue_impl vcardvalue;

LIBICAL_VCARD_EXPORT void vcardvalue_set_x(vcardvalue *value, const char *v);
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_x(const char *v);
LIBICAL_VCARD_EXPORT const char *vcardvalue_get_x(const vcardvalue *value);

LIBICAL_VCARD_EXPORT void vcardvalue_reset_kind(vcardvalue *value);

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_structured(vcardstructuredtype *v);
LIBICAL_VCARD_EXPORT void vcardvalue_set_structured(vcardvalue *value,
                                                    vcardstructuredtype *v);
LIBICAL_VCARD_EXPORT vcardstructuredtype *vcardvalue_get_structured(const vcardvalue *value);

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_geo(vcardgeotype v);
LIBICAL_VCARD_EXPORT void vcardvalue_set_geo(vcardvalue *value, vcardgeotype v);
LIBICAL_VCARD_EXPORT vcardgeotype vcardvalue_get_geo(const vcardvalue *value);

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_tz(vcardtztype v);
LIBICAL_VCARD_EXPORT void vcardvalue_set_tz(vcardvalue *value, vcardtztype v);
LIBICAL_VCARD_EXPORT vcardtztype vcardvalue_get_tz(const vcardvalue *value);

typedef enum vcardvalue_kind {
   VCARD_ANY_VALUE=5000,
    VCARD_BOOLEAN_VALUE=5008,
    VCARD_DATE_VALUE=5003,
    VCARD_DATEANDORTIME_VALUE=5006,
    VCARD_DATETIME_VALUE=5005,
    VCARD_FLOAT_VALUE=5010,
    VCARD_GEO_VALUE=5021,
    VCARD_GRAMGENDER_VALUE=5018,
    VCARD_INTEGER_VALUE=5009,
    VCARD_KIND_VALUE=5014,
    VCARD_LANGUAGETAG_VALUE=5012,
    VCARD_STRUCTURED_VALUE=5017,
    VCARD_TEXT_VALUE=5001,
    VCARD_TEXTLIST_VALUE=5016,
    VCARD_TIME_VALUE=5004,
    VCARD_TIMESTAMP_VALUE=5007,
    VCARD_TZ_VALUE=5020,
    VCARD_URI_VALUE=5002,
    VCARD_UTCOFFSET_VALUE=5011,
    VCARD_VERSION_VALUE=5015,
    VCARD_X_VALUE=5013,
   VCARD_NO_VALUE=5099
} vcardvalue_kind;

#define VCARDPROPERTY_FIRST_ENUM 10000

typedef enum vcardproperty_gramgender {
    VCARD_GRAMGENDER_X = 10200,
    VCARD_GRAMGENDER_ANIMATE = 10201,
    VCARD_GRAMGENDER_COMMON = 10202,
    VCARD_GRAMGENDER_FEMININE = 10203,
    VCARD_GRAMGENDER_INANIMATE = 10204,
    VCARD_GRAMGENDER_MASCULINE = 10205,
    VCARD_GRAMGENDER_NEUTER = 10206,
    VCARD_GRAMGENDER_NONE = 10299
} vcardproperty_gramgender;

typedef enum vcardproperty_kindenum {
    VCARD_KIND_X = 10000,
    VCARD_KIND_INDIVIDUAL = 10001,
    VCARD_KIND_GROUP = 10002,
    VCARD_KIND_ORG = 10003,
    VCARD_KIND_LOCATION = 10004,
    VCARD_KIND_APPLICATION = 10005,
    VCARD_KIND_DEVICE = 10006,
    VCARD_KIND_NONE = 10099
} vcardproperty_kindenum;

typedef enum vcardproperty_version {
    VCARD_VERSION_X = 10100,
    VCARD_VERSION_21 = 10101,
    VCARD_VERSION_30 = 10102,
    VCARD_VERSION_40 = 10103,
    VCARD_VERSION_NONE = 10199
} vcardproperty_version;

#define VCARDPROPERTY_LAST_ENUM 10300

/* BOOLEAN */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_boolean(int v);
LIBICAL_VCARD_EXPORT int vcardvalue_get_boolean(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_boolean(vcardvalue *value, int v);

/* DATE */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_date(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardvalue_get_date(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_date(vcardvalue *value, vcardtimetype v);

/* DATE-AND-OR-TIME */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_dateandortime(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardvalue_get_dateandortime(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_dateandortime(vcardvalue *value, vcardtimetype v);

/* DATE-TIME */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_datetime(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardvalue_get_datetime(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_datetime(vcardvalue *value, vcardtimetype v);

/* FLOAT */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_float(float v);
LIBICAL_VCARD_EXPORT float vcardvalue_get_float(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_float(vcardvalue *value, float v);

/* GRAMGENDER */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_gramgender(enum vcardproperty_gramgender v);
LIBICAL_VCARD_EXPORT enum vcardproperty_gramgender vcardvalue_get_gramgender(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_gramgender(vcardvalue *value, enum vcardproperty_gramgender v);

/* INTEGER */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_integer(int v);
LIBICAL_VCARD_EXPORT int vcardvalue_get_integer(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_integer(vcardvalue *value, int v);

/* KIND */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_kind(enum vcardproperty_kindenum v);
LIBICAL_VCARD_EXPORT enum vcardproperty_kindenum vcardvalue_get_kind(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_kind(vcardvalue *value, enum vcardproperty_kindenum v);

/* LANGUAGE-TAG */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_languagetag(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardvalue_get_languagetag(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_languagetag(vcardvalue *value, const char * v);

/* TEXT */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_text(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardvalue_get_text(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_text(vcardvalue *value, const char * v);

/* TEXTLIST */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_textlist(vcardstrarray * v);
LIBICAL_VCARD_EXPORT vcardstrarray * vcardvalue_get_textlist(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_textlist(vcardvalue *value, vcardstrarray * v);

/* TIME */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_time(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardvalue_get_time(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_time(vcardvalue *value, vcardtimetype v);

/* TIMESTAMP */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_timestamp(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardvalue_get_timestamp(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_timestamp(vcardvalue *value, vcardtimetype v);

/* URI */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_uri(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardvalue_get_uri(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_uri(vcardvalue *value, const char * v);

/* UTC-OFFSET */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_utcoffset(int v);
LIBICAL_VCARD_EXPORT int vcardvalue_get_utcoffset(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_utcoffset(vcardvalue *value, int v);

/* VERSION */
LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_version(enum vcardproperty_version v);
LIBICAL_VCARD_EXPORT enum vcardproperty_version vcardvalue_get_version(const vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardvalue_set_version(vcardvalue *value, enum vcardproperty_version v);
#endif /*VCARDVALUE_H*/

/*======================================================================
 FILE: vcardderivedparameter.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDPARAMETER_H
#define VCARDDERIVEDPARAMETER_H

#include "libical_vcard_export.h"


typedef struct vcardparameter_impl vcardparameter;

LIBICAL_VCARD_EXPORT const char *vcardparameter_enum_to_string(int e);
LIBICAL_VCARD_EXPORT int vcardparameter_string_to_enum(const char *str);

/* START of section of machine generated code (mkderivedparameters.pl). Do not edit. */

typedef enum vcardparameter_kind {
    VCARD_ANY_PARAMETER = 0,
    VCARD_ALTID_PARAMETER = 4,
    VCARD_AUTHOR_PARAMETER = 23,
    VCARD_AUTHORNAME_PARAMETER = 24,
    VCARD_CALSCALE_PARAMETER = 8,
    VCARD_CC_PARAMETER = 20,
    VCARD_CONTEXT_PARAMETER = 17,
    VCARD_CREATED_PARAMETER = 25,
    VCARD_DERIVED_PARAMETER = 26,
    VCARD_ENCODING_PARAMETER = 16,
    VCARD_GEO_PARAMETER = 10,
    VCARD_IANA_PARAMETER = 13,
    VCARD_INDEX_PARAMETER = 18,
    VCARD_JSCOMPS_PARAMETER = 27,
    VCARD_JSPTR_PARAMETER = 21,
    VCARD_LABEL_PARAMETER = 22,
    VCARD_LANGUAGE_PARAMETER = 1,
    VCARD_LEVEL_PARAMETER = 19,
    VCARD_MEDIATYPE_PARAMETER = 7,
    VCARD_PHONETIC_PARAMETER = 31,
    VCARD_PID_PARAMETER = 5,
    VCARD_PREF_PARAMETER = 3,
    VCARD_PROPID_PARAMETER = 28,
    VCARD_SCRIPT_PARAMETER = 32,
    VCARD_SERVICETYPE_PARAMETER = 29,
    VCARD_SORTAS_PARAMETER = 9,
    VCARD_TYPE_PARAMETER = 6,
    VCARD_TZ_PARAMETER = 11,
    VCARD_USERNAME_PARAMETER = 30,
    VCARD_VALUE_PARAMETER = 2,
    VCARD_X_PARAMETER = 12,
    VCARD_XLICCOMPARETYPE_PARAMETER = 15,
    VCARD_XLICERRORTYPE_PARAMETER = 14,
    VCARD_NO_PARAMETER = 99
} vcardparameter_kind;

#define VCARDPARAMETER_FIRST_ENUM 20000

typedef enum vcardparameter_calscale {
    VCARD_CALSCALE_X = 20200,
    VCARD_CALSCALE_GREGORIAN = 20201,
    VCARD_CALSCALE_NONE = 20299
} vcardparameter_calscale;

typedef enum vcardparameter_derived {
    VCARD_DERIVED_X = 20700,
    VCARD_DERIVED_TRUE = 20701,
    VCARD_DERIVED_FALSE = 20702,
    VCARD_DERIVED_NONE = 20799
} vcardparameter_derived;

typedef enum vcardparameter_encoding {
    VCARD_ENCODING_X = 20500,
    VCARD_ENCODING_B = 20501,
    VCARD_ENCODING_NONE = 20599
} vcardparameter_encoding;

typedef enum vcardparameter_level {
    VCARD_LEVEL_X = 20600,
    VCARD_LEVEL_BEGINNER = 20601,
    VCARD_LEVEL_AVERAGE = 20602,
    VCARD_LEVEL_EXPERT = 20603,
    VCARD_LEVEL_HIGH = 20604,
    VCARD_LEVEL_MEDIUM = 20605,
    VCARD_LEVEL_LOW = 20606,
    VCARD_LEVEL_NONE = 20699
} vcardparameter_level;

typedef enum vcardparameter_phonetic {
    VCARD_PHONETIC_X = 20800,
    VCARD_PHONETIC_IPA = 20801,
    VCARD_PHONETIC_PINY = 20802,
    VCARD_PHONETIC_JYUT = 20803,
    VCARD_PHONETIC_SCRIPT = 20804,
    VCARD_PHONETIC_NONE = 20899
} vcardparameter_phonetic;

typedef enum vcardparameter_type {
    VCARD_TYPE_X = 20100,
    VCARD_TYPE_WORK = 20101,
    VCARD_TYPE_HOME = 20102,
    VCARD_TYPE_TEXT = 20103,
    VCARD_TYPE_VOICE = 20104,
    VCARD_TYPE_FAX = 20105,
    VCARD_TYPE_CELL = 20106,
    VCARD_TYPE_VIDEO = 20107,
    VCARD_TYPE_PAGER = 20108,
    VCARD_TYPE_TEXTPHONE = 20109,
    VCARD_TYPE_CONTACT = 20110,
    VCARD_TYPE_ACQUAINTANCE = 20111,
    VCARD_TYPE_FRIEND = 20112,
    VCARD_TYPE_MET = 20113,
    VCARD_TYPE_COWORKER = 20114,
    VCARD_TYPE_COLLEAGUE = 20115,
    VCARD_TYPE_CORESIDENT = 20116,
    VCARD_TYPE_NEIGHBOR = 20117,
    VCARD_TYPE_CHILD = 20118,
    VCARD_TYPE_PARENT = 20119,
    VCARD_TYPE_SIBLING = 20120,
    VCARD_TYPE_SPOUSE = 20121,
    VCARD_TYPE_KIN = 20122,
    VCARD_TYPE_MUSE = 20123,
    VCARD_TYPE_CRUSH = 20124,
    VCARD_TYPE_DATE = 20125,
    VCARD_TYPE_SWEETHEART = 20126,
    VCARD_TYPE_ME = 20127,
    VCARD_TYPE_AGENT = 20128,
    VCARD_TYPE_EMERGENCY = 20129,
    VCARD_TYPE_PREF = 20130,
    VCARD_TYPE_MAINNUMBER = 20131,
    VCARD_TYPE_BILLING = 20132,
    VCARD_TYPE_DELIVERY = 20133,
    VCARD_TYPE_NONE = 20199
} vcardparameter_type;

typedef enum vcardparameter_value {
    VCARD_VALUE_X = 20000,
    VCARD_VALUE_TEXT = 20001,
    VCARD_VALUE_URI = 20002,
    VCARD_VALUE_DATE = 20003,
    VCARD_VALUE_TIME = 20004,
    VCARD_VALUE_DATETIME = 20005,
    VCARD_VALUE_DATEANDORTIME = 20006,
    VCARD_VALUE_TIMESTAMP = 20007,
    VCARD_VALUE_BOOLEAN = 20008,
    VCARD_VALUE_INTEGER = 20009,
    VCARD_VALUE_FLOAT = 20010,
    VCARD_VALUE_UTCOFFSET = 20011,
    VCARD_VALUE_LANGUAGETAG = 20012,
    VCARD_VALUE_NONE = 20099
} vcardparameter_value;

typedef enum vcardparameter_xliccomparetype {
    VCARD_XLICCOMPARETYPE_X = 20400,
    VCARD_XLICCOMPARETYPE_EQUAL = 20401,
    VCARD_XLICCOMPARETYPE_NOTEQUAL = 20402,
    VCARD_XLICCOMPARETYPE_LESS = 20403,
    VCARD_XLICCOMPARETYPE_GREATER = 20404,
    VCARD_XLICCOMPARETYPE_LESSEQUAL = 20405,
    VCARD_XLICCOMPARETYPE_GREATEREQUAL = 20406,
    VCARD_XLICCOMPARETYPE_REGEX = 20407,
    VCARD_XLICCOMPARETYPE_ISNULL = 20408,
    VCARD_XLICCOMPARETYPE_ISNOTNULL = 20409,
    VCARD_XLICCOMPARETYPE_NONE = 20499
} vcardparameter_xliccomparetype;

typedef enum vcardparameter_xlicerrortype {
    VCARD_XLICERRORTYPE_X = 20300,
    VCARD_XLICERRORTYPE_COMPONENTPARSEERROR = 20301,
    VCARD_XLICERRORTYPE_PROPERTYPARSEERROR = 20302,
    VCARD_XLICERRORTYPE_PARAMETERNAMEPARSEERROR = 20303,
    VCARD_XLICERRORTYPE_PARAMETERVALUEPARSEERROR = 20304,
    VCARD_XLICERRORTYPE_VALUEPARSEERROR = 20305,
    VCARD_XLICERRORTYPE_RESTRICTIONCHECK = 20306,
    VCARD_XLICERRORTYPE_NONE = 20399
} vcardparameter_xlicerrortype;

#define VCARDPARAMETER_LAST_ENUM 20900


/* ALTID */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_altid(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_altid(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_altid(vcardparameter *value, const char * v);

/* AUTHOR */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_author(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_author(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_author(vcardparameter *value, const char * v);

/* AUTHOR-NAME */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_authorname(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_authorname(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_authorname(vcardparameter *value, const char * v);

/* CALSCALE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_calscale(vcardparameter_calscale v);
LIBICAL_VCARD_EXPORT vcardparameter_calscale vcardparameter_get_calscale(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_calscale(vcardparameter *value, vcardparameter_calscale v);

/* CC */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_cc(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_cc(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_cc(vcardparameter *value, const char * v);

/* CONTEXT */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_context(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_context(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_context(vcardparameter *value, const char * v);

/* CREATED */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_created(vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardparameter_get_created(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_created(vcardparameter *value, vcardtimetype v);

/* DERIVED */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_derived(vcardparameter_derived v);
LIBICAL_VCARD_EXPORT vcardparameter_derived vcardparameter_get_derived(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_derived(vcardparameter *value, vcardparameter_derived v);

/* ENCODING */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_encoding(vcardparameter_encoding v);
LIBICAL_VCARD_EXPORT vcardparameter_encoding vcardparameter_get_encoding(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_encoding(vcardparameter *value, vcardparameter_encoding v);

/* GEO */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_geo(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_geo(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_geo(vcardparameter *value, const char * v);

/* IANA */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_iana(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_iana(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_iana(vcardparameter *value, const char * v);

/* INDEX */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_index(int v);
LIBICAL_VCARD_EXPORT int vcardparameter_get_index(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_index(vcardparameter *value, int v);

/* JSCOMPS */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_jscomps(vcardstructuredtype * v);
LIBICAL_VCARD_EXPORT vcardstructuredtype * vcardparameter_get_jscomps(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_jscomps(vcardparameter *value, vcardstructuredtype * v);

/* JSPTR */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_jsptr(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_jsptr(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_jsptr(vcardparameter *value, const char * v);

/* LABEL */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_label(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_label(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_label(vcardparameter *value, const char * v);

/* LANGUAGE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_language(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_language(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_language(vcardparameter *value, const char * v);

/* LEVEL */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_level(vcardparameter_level v);
LIBICAL_VCARD_EXPORT vcardparameter_level vcardparameter_get_level(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_level(vcardparameter *value, vcardparameter_level v);

/* MEDIATYPE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_mediatype(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_mediatype(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_mediatype(vcardparameter *value, const char * v);

/* PHONETIC */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_phonetic(vcardparameter_phonetic v);
LIBICAL_VCARD_EXPORT vcardparameter_phonetic vcardparameter_get_phonetic(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_phonetic(vcardparameter *value, vcardparameter_phonetic v);

/* PID */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_pid(vcardstrarray * v);
LIBICAL_VCARD_EXPORT vcardstrarray * vcardparameter_get_pid(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_pid(vcardparameter *value, vcardstrarray * v);
LIBICAL_VCARD_EXPORT void vcardparameter_add_pid(vcardparameter *value, const char * v);
LIBICAL_VCARD_EXPORT void vcardparameter_remove_pid(vcardparameter *value, const char * v);

/* PREF */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_pref(int v);
LIBICAL_VCARD_EXPORT int vcardparameter_get_pref(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_pref(vcardparameter *value, int v);

/* PROP-ID */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_propid(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_propid(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_propid(vcardparameter *value, const char * v);

/* SCRIPT */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_script(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_script(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_script(vcardparameter *value, const char * v);

/* SERVICE-TYPE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_servicetype(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_servicetype(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_servicetype(vcardparameter *value, const char * v);

/* SORT-AS */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_sortas(vcardstrarray * v);
LIBICAL_VCARD_EXPORT vcardstrarray * vcardparameter_get_sortas(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_sortas(vcardparameter *value, vcardstrarray * v);
LIBICAL_VCARD_EXPORT void vcardparameter_add_sortas(vcardparameter *value, const char * v);
LIBICAL_VCARD_EXPORT void vcardparameter_remove_sortas(vcardparameter *value, const char * v);

/* TYPE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_type(vcardenumarray * v);
LIBICAL_VCARD_EXPORT vcardenumarray * vcardparameter_get_type(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_type(vcardparameter *value, vcardenumarray * v);
LIBICAL_VCARD_EXPORT void vcardparameter_add_type(vcardparameter *value, vcardenumarray_element * v);
LIBICAL_VCARD_EXPORT void vcardparameter_remove_type(vcardparameter *value, vcardenumarray_element * v);

/* TZ */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_tz(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_tz(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_tz(vcardparameter *value, const char * v);

/* USERNAME */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_username(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_username(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_username(vcardparameter *value, const char * v);

/* VALUE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_value(vcardparameter_value v);
LIBICAL_VCARD_EXPORT vcardparameter_value vcardparameter_get_value(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_value(vcardparameter *value, vcardparameter_value v);

/* X */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_x(const char * v);
LIBICAL_VCARD_EXPORT const char * vcardparameter_get_x(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_x(vcardparameter *value, const char * v);

/* X-LIC-COMPARETYPE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_xliccomparetype(vcardparameter_xliccomparetype v);
LIBICAL_VCARD_EXPORT vcardparameter_xliccomparetype vcardparameter_get_xliccomparetype(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_xliccomparetype(vcardparameter *value, vcardparameter_xliccomparetype v);

/* X-LIC-ERRORTYPE */
LIBICAL_VCARD_EXPORT vcardparameter * vcardparameter_new_xlicerrortype(vcardparameter_xlicerrortype v);
LIBICAL_VCARD_EXPORT vcardparameter_xlicerrortype vcardparameter_get_xlicerrortype(const vcardparameter *value);
LIBICAL_VCARD_EXPORT void vcardparameter_set_xlicerrortype(vcardparameter *value, vcardparameter_xlicerrortype v);
#endif /*VCARDPARAMETER_H*/

/* END   of section of machine generated code (mkderivedparameters.pl). Do not edit. */


/*======================================================================
 FILE: vcardvalue.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDVALUE_H
#define VCARDVALUE_H

#include "libical_vcard_export.h"


#define VCARD_BOOLEAN_TRUE 1
#define VCARD_BOOLEAN_FALSE 0

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new(vcardvalue_kind kind);

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_clone(const vcardvalue *value);

LIBICAL_VCARD_EXPORT vcardvalue *vcardvalue_new_from_string(vcardvalue_kind kind,
                                                            const char *str);

LIBICAL_VCARD_EXPORT void vcardvalue_free(vcardvalue *value);

LIBICAL_VCARD_EXPORT int vcardvalue_is_valid(const vcardvalue *value);

LIBICAL_VCARD_EXPORT const char *vcardvalue_as_vcard_string(const vcardvalue *value);

LIBICAL_VCARD_EXPORT char *vcardvalue_as_vcard_string_r(const vcardvalue *value);

LIBICAL_VCARD_EXPORT vcardvalue_kind vcardvalue_isa(const vcardvalue *value);

LIBICAL_VCARD_EXPORT int vcardvalue_isa_value(void *);

/* Convert enumerations */

LIBICAL_VCARD_EXPORT vcardvalue_kind vcardvalue_string_to_kind(const char *str);

LIBICAL_VCARD_EXPORT const char *vcardvalue_kind_to_string(const vcardvalue_kind kind);

/** Check validity of a specific vcardvalue_kind **/
LIBICAL_VCARD_EXPORT int vcardvalue_kind_is_valid(const vcardvalue_kind kind);

/** Encode a character string in ical format, escape certain characters, etc. */
LIBICAL_VCARD_EXPORT int vcardvalue_encode_ical_string(const char *szText,
                                                       char *szEncText,
                                                       int MaxBufferLen);

/** Extract the original character string encoded by the above function **/
LIBICAL_VCARD_EXPORT int vcardvalue_decode_ical_string(const char *szText,
                                                       char *szDecText,
                                                       int nMaxBufferLen);

/* Duplicate and dequote a TEXT value */
LIBICAL_VCARD_EXPORT char *vcardvalue_strdup_and_dequote_text(const char **str,
                                                              const char *sep);

#endif /* VCARDVALUE_H */

/*======================================================================
 FILE: vcardparameter.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDPARAMETER_H
#define VCARDPARAMETER_H

#include "libical_vcard_export.h"


/* Declared in vcardderivedparameter.h */
/*typedef struct vcardparameter_impl vcardparameter;*/

/**
 * @brief Creates new vcardparameter object.
 * @param kind The kind of vcardparameter to create.
 * @return An vcardparameter with the given kind.
 *
 * @par Error handling
 * If there was an internal error regarding
 * memory allocation, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the vcardparameter_free() method.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * vcardparameter *parameter = vcardparameter_new();
 *
 * if(parameter) {
 *     // use parameter ...
 * }
 *
 * // release parameter
 * vcardparameter_free(parameter);
 * ```
 */
LIBICAL_VCARD_EXPORT vcardparameter *vcardparameter_new(vcardparameter_kind kind);

/**
 * @brief Creates new vcardparameter as a clone of the given one.
 * @param p The existing, non-`NULL` parameter to clone.
 * @return An vcardparameter that is a clone of the given one.
 *
 * @par Error handling
 * If @a p is `NULL`, it returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If there was an internal error cloning the data, it returns `NULL`
 * without reporting any error in ::icalerrno.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the vcardparameter_free() method.
 *
 * @par Usage
 * ```x
 * // create an vcardparameter
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * // clone the parameter
 * vcardparameter *clone = vcardparameter_clone(param);
 *
 * if(clone) {
 *     // use clone ...
 * }
 *
 * // release parameters
 * vcardparameter_free(param);
 * vcardparameter_free(clone);
 * ```
 * @since 3.1.0
 */
LIBICAL_VCARD_EXPORT vcardparameter *vcardparameter_clone(const vcardparameter *p);

/**
 * @brief Creates new vcardparameter object from string
 * @param value The string from which to create the vcardparameter, in the form `"PARAMNAME=VALUE"`
 * @return An vcardparameter that corresponds to the given string.
 *
 * @par Error handling
 * If there was an internal error copying data, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR. If @a value was `NULL`, it returns
 * `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR. If @a value was malformed,
 * it returns `NULL` and sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the vcardparameter_free() method.
 *
 * @par Usage
 * ```c
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     // use param ...
 * }
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT vcardparameter *vcardparameter_new_from_string(const char *value);

/**
 * @brief Creates new vcardparameter of a given @a kind with a given @a value
 * @param kind The kind of vcardparameter to create
 * @param value The value of the parameter
 * @return An vcardparameter with the given kind and value.
 *
 * @par Error handling
 * If value is `NULL`, it returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the vcardparameter_free() method.
 *
 * @par Example
 * ```c
 * // create new parameter
 * vcardparameter *param;
 * param = vcardparameter_new_from_value_string(ICAL_ROLE_PARAMETER, "CHAIR");
 *
 * // check parameter
 * assert(0 == strcmp(vcardparameter_get_iana_name(param), "ROLE"));
 * assert(0 == strcmp(vcardparameter_get_iana_value(param), "CHAIR"));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT vcardparameter *vcardparameter_new_from_value_string(vcardparameter_kind kind,
                                                                          const char *value);

LIBICAL_VCARD_EXPORT void vcardparameter_set_value_from_string(vcardparameter *param,
                                                               const char *val);
LIBICAL_VCARD_EXPORT void vcardparameter_add_value_from_string(vcardparameter *param,
                                                               const char *val);

/**
 * @brief Frees an vcardparameter object.
 * @param parameter The vcardparameter to free
 *
 * This method needs to be used on all parameter objects returned
 * from any of the `_new()` methods including vcardparameter_new(),
 * vcardparameter_new_from_string() and vcardparameter_new_from_value_string()
 * and on cloned parameter objects returned by vcardparameter_clone()
 * when these object are not needed anymore and to be released.
 *
 * @par Usage
 * ```c
 * vcardparameter *param = vcardparameter_new();
 *
 * if(param) {
 *     // use param...
 * }
 *
 * // after use, release it
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT void vcardparameter_free(vcardparameter *parameter);

/**
 * @brief Converts vcardparameter into a string representation
 * @param parameter The vcardparameter to convert
 * @return A string representing the parameter according to RFC5445/RFC6868.
 * @sa vcardparameter_as_ical_string_r()
 *
 * @par Error handling
 * If there is any error, the method returns `NULL`. Furthermore,
 * if @a parameter is `NULL`, it also sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If it doesn't recognize the kind of the parameter, it sets ::icalerrno
 * it ::ICAL_BADARG_ERROR. If the parameter is otherwise malformed, it
 * sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Strings returned by this method are owned by libical, they must
 * not be freed and they may be reclaimed with the next call into
 * the library. A version of this function, which returns strings
 * that are not owned by libical, is vcardparameter_as_ical_string_r().
 *
 * @par Usage
 * ```c
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     printf("%s\n", vcardparameter_as_ical_string(param));
 * }
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT char *vcardparameter_as_vcard_string(vcardparameter *parameter);

/**
 * @brief Converts vcardparameter into an string representation according to RFC5445/RFC6868.
 * @param parameter The vcardparameter to convert
 * @return A string representing the parameter
 * @sa vcardparameter_as_ical_string()
 *
 * @par Error handling
 * If there is any error, the method returns `NULL`. Furthermore,
 * if parameter is `NULL`, it also sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If it doesn't recognize the kind of the parameter, it sets ::icalerrno
 * to ::ICAL_BADARG_ERROR. If the parameter is otherwise malformed, it
 * sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Strings returned by this method are owned by the caller, thus they need
 * to be manually `icalmemory_free_buffer()`d after use.
 * A version of this function which returns strings that do not
 * need to be freed manually is vcardparameter_as_ical_string().
 *
 * @par Usage
 * ```c
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     char *str = vcardparameter_as_ical_string(param);
 *     printf("%s\n", str);
 *     icalmemory_free_buffer(str);
 * }
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT char *vcardparameter_as_vcard_string_r(vcardparameter *parameter);

/**
 * Returns the vcardparameter_kind of parameter.
 *
 * @param parameter The vcardparameter whose kind to determine
 * @return The vcardparameter_kind of the parameter
 *
 * @b Error handling
 * Returns ICAL_NO_PARAMETER when passed NULL.
 *
 * @b Usage
 * @code
 * // create parameter
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * // check what type of parameter this is
 * assert(vcardparameter_isa(param) == ICAL_ROLE_PARAMETER);
 *
 * // release memory
 * vcardparameter_free(param);
 * @endcode
 */
LIBICAL_VCARD_EXPORT vcardparameter_kind vcardparameter_isa(vcardparameter *parameter);

/**
 * Determines if the given param is an vcardparameter
 * @param param The libical-originated object to check
 * @return 1 if the object is an vcardparameter, 0 otherwise.
 * @note This function expects to be given an object originating from
 *  libical - if this function is passed anything that is not from
 *  libical, its behavior is undefined.
 *
 * @b Error handling
 * When given a `NULL` object, it returns 0.
 *
 * @b Usage
 * ```c
 * // create parameter
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=CHAIR");
 *
 * // check if it's a parameter
 * assert(vcardparameter_isa_parameter(param));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT int vcardparameter_isa_parameter(void *param);

/* Access the name of an X parameter */

/**
 * @brief Sets the X-name of @a param to @a v
 * @param param The vcardparameter to change
 * @param v The X-name to set @a param to
 * @sa vcardparameter_get_xname()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * vcardparameter *param = vcardparameter_new();
 *
 * // sets xname
 * vcardparameter_set_xname(param, "X-TEST");
 *
 * // compare xname
 * assert(0 == strcmp(vcardparameter_get_xname(param), "X-TEST"));
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT void vcardparameter_set_xname(vcardparameter *param, const char *v);

/**
 * @brief Returns the X-name of @a param
 * @param param The vcardparameter whose X-name is to be returned
 * @return A string representing the X-name of @a param
 * @sa vcardparameter_set_xname()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an vcardparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * vcardparameter *param = vcardparameter_new();
 *
 * // sets xname
 * vcardparameter_set_xname(param, "X-TEST");
 *
 * // compare xname
 * assert(0 == strcmp(vcardparameter_get_xname(param), "X-TEST"));
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT const char *vcardparameter_get_xname(vcardparameter *param);

/**
 * @brief Sets the X-value of @a param to @a v
 * @param param The vcardparameter to change
 * @param v The X-value to set @a param to
 * @sa vcardparameter_get_xvalue()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * vcardparameter *param = vcardparameter_new_from_string("X-TEST=FAIL");
 *
 * // set test to success
 * vcardparameter_set_xvalue(param, "SUCCESS");
 *
 * // check that it worked
 * assert(0 == strcmp(vcardparameter_get_xvalue(param), "SUCCESS"));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT void vcardparameter_set_xvalue(vcardparameter *param, const char *v);

/**
 * @brief Returns the X-value of @a param
 * @param param The vcardparameter whose X-value is to be returned
 * @return A string representing the X-value of @a param
 * @sa vcardparameter_set_xvalue()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an vcardparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * vcardparameter *param = vcardparameter_new_from_string("X-TEST=FAIL");
 *
 * // set test to success
 * vcardparameter_set_xvalue(param, "SUCCESS");
 *
 * // check that it worked
 * assert(0 == strcmp(vcardparameter_get_xvalue(param), "SUCCESS"));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT const char *vcardparameter_get_xvalue(vcardparameter *param);

/* Access the name of an IANA parameter */

/**
 * @brief Sets the IANA name of @a param to @a v
 * @param param The vcardparameter to change
 * @param v The IANA name to set @a param to
 * @sa vcardparameter_get_iana_name()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets :calerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * vcardparameter *param = vcardparameter_new();
 *
 * // sets iana name
 * vcardparameter_set_iana_name(param, "ROLE");
 *
 * // compare iana name
 * assert(0 == strcmp(vcardparameter_get_iana_name(param), "X-TEST"));
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT void vcardparameter_set_iana_name(vcardparameter *param, const char *v);

/**
 * @brief Returns the IANA name of @a param
 * @param param The vcardparameter whose IANA name is to be returned
 * @return A string representing the IANA name of @a param
 * @sa vcardparameter_set_iana_name()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an vcardparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * vcardparameter *param = vcardparameter_new();
 *
 * // sets iana name
 * vcardparameter_set_iana_name(param, "X-TEST");
 *
 * // compare iana name
 * assert(0 == strcmp(vcardparameter_get_iana_name(param), "X-TEST"));
 *
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT const char *vcardparameter_get_iana_name(vcardparameter *param);

/**
 * @brief Sets the IANA value of @a param to @a v
 * @param param The vcardparameter to change
 * @param v The IANA value to set @a param to
 * @sa vcardparameter_get_iana_value()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=ATTENDEE");
 *
 * // set role to chair
 * vcardparameter_set_iana_value(param, "CHAIR");
 *
 * // check that it worked
 * assert(0 == strcmp(vcardparameter_get_iana_value(param), "SUCCESS"));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT void vcardparameter_set_iana_value(vcardparameter *param, const char *v);

/**
 * @brief Returns the IANA value of @a param
 * @param param The vcardparameter whose value is to be returned
 * @return A string representing the value of @a param
 * @sa vcardparameter_set_iana_value()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an vcardparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * vcardparameter *param = vcardparameter_new_from_string("ROLE=ATTENDEE");
 *
 * // set role to chair
 * vcardparameter_set_iana_value(param, "CHAIR");
 *
 * // check that it worked
 * assert(0 == strcmp(vcardparameter_get_iana_value(param), "SUCCESS"));
 *
 * // release memory
 * vcardparameter_free(param);
 * ```
 */
LIBICAL_VCARD_EXPORT const char *vcardparameter_get_iana_value(vcardparameter *param);

/**
 * @brief Determines if two parameters have the same name
 * @param param1 First parameter to compare
 * @param param2 Second parameter to compare
 * @return 1 if they have the same name, 0 otherwise.
 *
 * @par Error handling
 * If either of @a param1 or @a param2 are `NULL`, it returns 0 and sets
 * ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * Does not take ownership of either vcardparameter.
 *
 * @par Example
 * ```c
 * // create two parameters
 * vcardparameter *param1 = vcardparameter_new_from_string("ROLE=CHAIR");
 * vcardparameter *param2 = vcardparameter_new_from_string("EMAIL=mailto@example.com");
 *
 * // compare parameter names for equality
 * assert(vcardparameter_has_same_name(param1, param2) == 0);
 *
 * // release memory
 * vcardparameter_free(param1);
 * vcardparameter_free(param2);
 * ```
 */
LIBICAL_VCARD_EXPORT int vcardparameter_has_same_name(vcardparameter *param1, vcardparameter *param2);

/* Convert enumerations */

/**
 * @brief Returns a string representing the given vcardparameter_kind
 * @param kind The vcardparameter_kind
 * @return A string representing @a kind
 *
 * @par Error handling
 * When passed a non-existing vcardparameter_kind, it returns `NULL`.
 *
 * @par Ownership
 * The string that is returned by this function is owned by libical and
 * must not be freed by the caller.
 *
 * @par Usage
 * ```c
 * assert(0 == strcmp(vcardparameter_kind_to_string(ICAL_ROLE_PARAMETER), "ROLE"));
 * assert(0 == strcmp(vcardparameter_kind_to_string(ICAL_EMAIL_PARAMETER), "EMAIL));
 * assert(0 == strcmp(vcardparameter_kind_to_string(ICAL_ID_PARAMETER), "ID"));
 * ```
 */
LIBICAL_VCARD_EXPORT const char *vcardparameter_kind_to_string(vcardparameter_kind kind);

/**
 * @brief Returns the vcardparameter_kind for a given string
 * @param string A string describing an vcardparameter_kind
 * @return An vcardparameter_kind
 *
 * @par Error handling
 * Returns ICAL_NO_PARAMETER if @a string is `NULL`.
 * If it can't find the parameter, depending on
 * the ical_get_unknown_token_handling_setting(), it returns either
 * ICAL_NO_PARAMETER or ICAL_IANA_PARAMETER.
 *
 * @par Ownership
 * Does not take ownership of @a string.
 *
 * @par Usage
 * ```c
 * assert(vcardparameter_string_to_kind("ROLE")  == ICAL_ROLE_PARAMETER);
 * assert(vcardparameter_string_to_kind("EMAIL") == ICAL_EMAIL_PARAMETER);
 * assert(vcardparameter_string_to_kind("ID")    == ICAL_ID_PARAMETER);
 * ```
 */
LIBICAL_VCARD_EXPORT vcardparameter_kind vcardparameter_string_to_kind(const char *string);

/**
 * @brief Checks the validity of a vcardparameter_kind
 * @param kind The vcardparameter_kind
 * @return 1 if @a kind is valid, 0 otherwise
 *
 * @par Usage
 * ```c
 * assert(vcardparameter_kind_is_valid(ICAL_ROLE_PARAMETER));
 * ```
 * @since 3.0.4
 */
LIBICAL_VCARD_EXPORT int vcardparameter_kind_is_valid(const vcardparameter_kind kind);

LIBICAL_VCARD_EXPORT vcardvalue_kind vcardparameter_kind_value_kind(const vcardparameter_kind kind,
                                                                    int *is_multivalued);

LIBICAL_VCARD_EXPORT int vcardparameter_is_multivalued(vcardparameter *param);

LIBICAL_VCARD_EXPORT int vcardparameter_is_structured(vcardparameter *param);

#endif

/*======================================================================
 FILE: vcardderivedproperty.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDPROPERTY_H
#define VCARDDERIVEDPROPERTY_H

#include "libical_sentinel.h"


typedef struct vcardproperty_impl vcardproperty;

typedef enum vcardproperty_kind {
    VCARD_ANY_PROPERTY = 0,
    VCARD_ADR_PROPERTY = 11,
    VCARD_AGENT_PROPERTY = 41,
    VCARD_ANNIVERSARY_PROPERTY = 9,
    VCARD_BDAY_PROPERTY = 8,
    VCARD_BEGIN_PROPERTY = 497,
    VCARD_BIRTHPLACE_PROPERTY = 44,
    VCARD_CALADRURI_PROPERTY = 35,
    VCARD_CALURI_PROPERTY = 36,
    VCARD_CATEGORIES_PROPERTY = 24,
    VCARD_CLASS_PROPERTY = 43,
    VCARD_CLIENTPIDMAP_PROPERTY = 30,
    VCARD_CONTACTURI_PROPERTY = 52,
    VCARD_CREATED_PROPERTY = 54,
    VCARD_DEATHDATE_PROPERTY = 46,
    VCARD_DEATHPLACE_PROPERTY = 45,
    VCARD_EMAIL_PROPERTY = 13,
    VCARD_END_PROPERTY = 498,
    VCARD_EXPERTISE_PROPERTY = 48,
    VCARD_FBURL_PROPERTY = 34,
    VCARD_FN_PROPERTY = 4,
    VCARD_GENDER_PROPERTY = 10,
    VCARD_GEO_PROPERTY = 17,
    VCARD_GRAMGENDER_PROPERTY = 56,
    VCARD_HOBBY_PROPERTY = 49,
    VCARD_IMPP_PROPERTY = 14,
    VCARD_INTEREST_PROPERTY = 50,
    VCARD_JSPROP_PROPERTY = 53,
    VCARD_KEY_PROPERTY = 33,
    VCARD_KIND_PROPERTY = 2,
    VCARD_LABEL_PROPERTY = 39,
    VCARD_LANG_PROPERTY = 15,
    VCARD_LANGUAGE_PROPERTY = 55,
    VCARD_LOGO_PROPERTY = 20,
    VCARD_MAILER_PROPERTY = 40,
    VCARD_MEMBER_PROPERTY = 22,
    VCARD_N_PROPERTY = 5,
    VCARD_NAME_PROPERTY = 38,
    VCARD_NICKNAME_PROPERTY = 6,
    VCARD_NOTE_PROPERTY = 25,
    VCARD_ORG_PROPERTY = 21,
    VCARD_ORGDIRECTORY_PROPERTY = 51,
    VCARD_PHOTO_PROPERTY = 7,
    VCARD_PRODID_PROPERTY = 26,
    VCARD_PRONOUNS_PROPERTY = 57,
    VCARD_RELATED_PROPERTY = 23,
    VCARD_REV_PROPERTY = 27,
    VCARD_ROLE_PROPERTY = 19,
    VCARD_SOCIALPROFILE_PROPERTY = 58,
    VCARD_SORTSTRING_PROPERTY = 42,
    VCARD_SOUND_PROPERTY = 28,
    VCARD_SOURCE_PROPERTY = 1,
    VCARD_TEL_PROPERTY = 12,
    VCARD_TITLE_PROPERTY = 18,
    VCARD_TZ_PROPERTY = 16,
    VCARD_UID_PROPERTY = 29,
    VCARD_URL_PROPERTY = 31,
    VCARD_VERSION_PROPERTY = 32,
    VCARD_X_PROPERTY = 37,
    VCARD_XLICERROR_PROPERTY = 496,
    VCARD_XML_PROPERTY = 3,
    VCARD_NO_PROPERTY = 499
} vcardproperty_kind;

/* ADR */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_adr(vcardstructuredtype* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_adr(vcardproperty *prop, vcardstructuredtype* v);
LIBICAL_VCARD_EXPORT vcardstructuredtype* vcardproperty_get_adr(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_adr(vcardstructuredtype* v, ...);

/* AGENT */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_agent(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_agent(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_agent(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_agent(const char * v, ...);

/* ANNIVERSARY */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_anniversary(vcardtimetype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_anniversary(vcardproperty *prop, vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardproperty_get_anniversary(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_anniversary(vcardtimetype v, ...);

/* BDAY */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_bday(vcardtimetype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_bday(vcardproperty *prop, vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardproperty_get_bday(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_bday(vcardtimetype v, ...);

/* BIRTHPLACE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_birthplace(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_birthplace(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_birthplace(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_birthplace(const char * v, ...);

/* CALADRURI */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_caladruri(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_caladruri(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_caladruri(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_caladruri(const char * v, ...);

/* CALURI */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_caluri(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_caluri(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_caluri(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_caluri(const char * v, ...);

/* CATEGORIES */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_categories(vcardstrarray* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_categories(vcardproperty *prop, vcardstrarray* v);
LIBICAL_VCARD_EXPORT vcardstrarray* vcardproperty_get_categories(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_categories(vcardstrarray* v, ...);

/* CLASS */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_class(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_class(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_class(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_class(const char * v, ...);

/* CLIENTPIDMAP */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_clientpidmap(vcardstrarray* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_clientpidmap(vcardproperty *prop, vcardstrarray* v);
LIBICAL_VCARD_EXPORT vcardstrarray* vcardproperty_get_clientpidmap(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_clientpidmap(vcardstrarray* v, ...);

/* CONTACT-URI */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_contacturi(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_contacturi(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_contacturi(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_contacturi(const char * v, ...);

/* CREATED */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_created(vcardtimetype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_created(vcardproperty *prop, vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardproperty_get_created(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_created(vcardtimetype v, ...);

/* DEATHDATE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_deathdate(vcardtimetype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_deathdate(vcardproperty *prop, vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardproperty_get_deathdate(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_deathdate(vcardtimetype v, ...);

/* DEATHPLACE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_deathplace(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_deathplace(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_deathplace(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_deathplace(const char * v, ...);

/* EMAIL */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_email(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_email(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_email(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_email(const char * v, ...);

/* EXPERTISE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_expertise(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_expertise(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_expertise(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_expertise(const char * v, ...);

/* FBURL */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_fburl(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_fburl(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_fburl(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_fburl(const char * v, ...);

/* FN */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_fn(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_fn(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_fn(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_fn(const char * v, ...);

/* GENDER */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_gender(vcardstrarray* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_gender(vcardproperty *prop, vcardstrarray* v);
LIBICAL_VCARD_EXPORT vcardstrarray* vcardproperty_get_gender(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_gender(vcardstrarray* v, ...);

/* GEO */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_geo(vcardgeotype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_geo(vcardproperty *prop, vcardgeotype v);
LIBICAL_VCARD_EXPORT vcardgeotype vcardproperty_get_geo(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_geo(vcardgeotype v, ...);

/* GRAMGENDER */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_gramgender(enum vcardproperty_gramgender v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_gramgender(vcardproperty *prop, enum vcardproperty_gramgender v);
LIBICAL_VCARD_EXPORT enum vcardproperty_gramgender vcardproperty_get_gramgender(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_gramgender(enum vcardproperty_gramgender v, ...);

/* HOBBY */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_hobby(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_hobby(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_hobby(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_hobby(const char * v, ...);

/* IMPP */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_impp(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_impp(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_impp(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_impp(const char * v, ...);

/* INTEREST */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_interest(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_interest(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_interest(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_interest(const char * v, ...);

/* JSPROP */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_jsprop(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_jsprop(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_jsprop(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_jsprop(const char * v, ...);

/* KEY */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_key(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_key(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_key(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_key(const char * v, ...);

/* KIND */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_kind(enum vcardproperty_kindenum v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_kind(vcardproperty *prop, enum vcardproperty_kindenum v);
LIBICAL_VCARD_EXPORT enum vcardproperty_kindenum vcardproperty_get_kind(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_kind(enum vcardproperty_kindenum v, ...);

/* LABEL */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_label(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_label(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_label(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_label(const char * v, ...);

/* LANG */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_lang(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_lang(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_lang(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_lang(const char * v, ...);

/* LANGUAGE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_language(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_language(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_language(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_language(const char * v, ...);

/* LOGO */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_logo(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_logo(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_logo(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_logo(const char * v, ...);

/* MAILER */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_mailer(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_mailer(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_mailer(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_mailer(const char * v, ...);

/* MEMBER */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_member(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_member(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_member(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_member(const char * v, ...);

/* N */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_n(vcardstructuredtype* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_n(vcardproperty *prop, vcardstructuredtype* v);
LIBICAL_VCARD_EXPORT vcardstructuredtype* vcardproperty_get_n(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_n(vcardstructuredtype* v, ...);

/* NAME */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_name(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_name(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_name(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_name(const char * v, ...);

/* NICKNAME */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_nickname(vcardstrarray* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_nickname(vcardproperty *prop, vcardstrarray* v);
LIBICAL_VCARD_EXPORT vcardstrarray* vcardproperty_get_nickname(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_nickname(vcardstrarray* v, ...);

/* NOTE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_note(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_note(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_note(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_note(const char * v, ...);

/* ORG */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_org(vcardstrarray* v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_org(vcardproperty *prop, vcardstrarray* v);
LIBICAL_VCARD_EXPORT vcardstrarray* vcardproperty_get_org(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_org(vcardstrarray* v, ...);

/* ORG-DIRECTORY */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_orgdirectory(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_orgdirectory(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_orgdirectory(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_orgdirectory(const char * v, ...);

/* PHOTO */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_photo(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_photo(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_photo(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_photo(const char * v, ...);

/* PRODID */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_prodid(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_prodid(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_prodid(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_prodid(const char * v, ...);

/* PRONOUNS */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_pronouns(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_pronouns(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_pronouns(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_pronouns(const char * v, ...);

/* RELATED */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_related(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_related(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_related(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_related(const char * v, ...);

/* REV */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_rev(vcardtimetype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_rev(vcardproperty *prop, vcardtimetype v);
LIBICAL_VCARD_EXPORT vcardtimetype vcardproperty_get_rev(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_rev(vcardtimetype v, ...);

/* ROLE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_role(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_role(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_role(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_role(const char * v, ...);

/* SOCIALPROFILE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_socialprofile(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_socialprofile(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_socialprofile(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_socialprofile(const char * v, ...);

/* SORT-STRING */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_sortstring(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_sortstring(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_sortstring(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_sortstring(const char * v, ...);

/* SOUND */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_sound(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_sound(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_sound(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_sound(const char * v, ...);

/* SOURCE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_source(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_source(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_source(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_source(const char * v, ...);

/* TEL */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_tel(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_tel(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_tel(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_tel(const char * v, ...);

/* TITLE */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_title(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_title(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_title(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_title(const char * v, ...);

/* TZ */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_tz(vcardtztype v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_tz(vcardproperty *prop, vcardtztype v);
LIBICAL_VCARD_EXPORT vcardtztype vcardproperty_get_tz(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_tz(vcardtztype v, ...);

/* UID */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_uid(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_uid(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_uid(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_uid(const char * v, ...);

/* URL */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_url(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_url(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_url(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_url(const char * v, ...);

/* VERSION */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_version(enum vcardproperty_version v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_version(vcardproperty *prop, enum vcardproperty_version v);
LIBICAL_VCARD_EXPORT enum vcardproperty_version vcardproperty_get_version(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_version(enum vcardproperty_version v, ...);

/* X */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_x(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_x(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_x(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_x(const char * v, ...);

/* X-LIC-ERROR */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_xlicerror(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_xlicerror(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_xlicerror(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_xlicerror(const char * v, ...);

/* XML */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_xml(const char * v);
LIBICAL_VCARD_EXPORT void vcardproperty_set_xml(vcardproperty *prop, const char * v);
LIBICAL_VCARD_EXPORT const char * vcardproperty_get_xml(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardproperty *vcardproperty_vanew_xml(const char * v, ...);

#endif /*VCARDPROPERTY_H*/

/*======================================================================
 FILE: vcardproperty.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDPROPERTY_H
#define VCARDPROPERTY_H

#include "libical_vcard_export.h"
 /* To get vcardproperty_kind enumerations */

#include <stdarg.h> /* for va_... */

/** @file vcardproperty.h */

LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new(vcardproperty_kind kind);

LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_impl(vcardproperty_kind kind);

/** @brief Deeply clones an vcardproperty.
 *
 * Returns a pointer to the memory for the newly cloned vcardproperty.
 * @since 3.1.0
 */
LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_clone(const vcardproperty *prop);

LIBICAL_VCARD_EXPORT vcardproperty *vcardproperty_new_from_string(const char *str);

LIBICAL_VCARD_EXPORT const char *vcardproperty_as_vcard_string(vcardproperty *prop);

LIBICAL_VCARD_EXPORT char *vcardproperty_as_vcard_string_r(vcardproperty *prop);

LIBICAL_VCARD_EXPORT void vcardproperty_free(vcardproperty *prop);

LIBICAL_VCARD_EXPORT vcardproperty_kind vcardproperty_isa(vcardproperty *property);

LIBICAL_VCARD_EXPORT int vcardproperty_isa_property(void *property);

LIBICAL_VCARD_EXPORT void vcardproperty_add_parameters(struct vcardproperty_impl *prop, va_list args);

LIBICAL_VCARD_EXPORT void vcardproperty_add_parameter(vcardproperty *prop, vcardparameter *parameter);

LIBICAL_VCARD_EXPORT void vcardproperty_set_parameter(vcardproperty *prop, vcardparameter *parameter);

LIBICAL_VCARD_EXPORT void vcardproperty_set_parameter_from_string(vcardproperty *prop,
                                                                  const char *name,
                                                                  const char *value);
LIBICAL_VCARD_EXPORT const char *vcardproperty_get_parameter_as_string(vcardproperty *prop,
                                                                       const char *name);

LIBICAL_VCARD_EXPORT char *vcardproperty_get_parameter_as_string_r(vcardproperty *prop,
                                                                   const char *name);

/** @brief Removes all parameters with the specified kind.
 *
 *  @param prop   A valid vcardproperty.
 *  @param kind   The kind to remove (ex. VCARD_TZ_PARAMETER)
 *
 *  See vcardproperty_remove_parameter_by_name() and
 *  vcardproperty_remove_parameter_by_ref() for alternate ways of
 *  removing parameters
 */
LIBICAL_VCARD_EXPORT void vcardproperty_remove_parameter_by_kind(vcardproperty *prop,
                                                                 vcardparameter_kind kind);

/** @brief Removes all parameters with the specified name.
 *
 *  @param prop   A valid vcardproperty.
 *  @param name   The name of the parameter to remove
 *
 *  This function removes parameters with the given name.  The name
 *  corresponds to either a built-in name (TZID, etc.) or the name of
 *  an extended parameter (X-FOO)
 *
 *  See vcardproperty_remove_parameter_by_kind() and
 *  vcardproperty_remove_parameter_by_ref() for alternate ways of removing
 *  parameters
 */
LIBICAL_VCARD_EXPORT void vcardproperty_remove_parameter_by_name(vcardproperty *prop,
                                                                 const char *name);

/** @brief Removes the specified parameter reference from the property.
 *
 *  @param prop   A valid vcardproperty.
 *  @param param  A reference to a specific vcardparameter.
 *
 *  This function removes the specified parameter reference from the
 *  property.
 */
LIBICAL_VCARD_EXPORT void vcardproperty_remove_parameter_by_ref(vcardproperty *prop,
                                                                vcardparameter *param);

LIBICAL_VCARD_EXPORT int vcardproperty_count_parameters(const vcardproperty *prop);

/* Iterate through the parameters */
LIBICAL_VCARD_EXPORT vcardparameter *vcardproperty_get_first_parameter(vcardproperty *prop,
                                                                       vcardparameter_kind kind);
LIBICAL_VCARD_EXPORT vcardparameter *vcardproperty_get_next_parameter(vcardproperty *prop,
                                                                      vcardparameter_kind kind);
/* Access the value of the property */
LIBICAL_VCARD_EXPORT void vcardproperty_set_value(vcardproperty *prop, vcardvalue *value);
LIBICAL_VCARD_EXPORT void vcardproperty_set_value_from_string(vcardproperty *prop, const char *value,
                                                              const char *kind);

LIBICAL_VCARD_EXPORT vcardvalue *vcardproperty_get_value(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT const char *vcardproperty_get_value_as_string(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT char *vcardproperty_get_value_as_string_r(const vcardproperty *prop);

/**
 * Sets the parent @p vcardproperty for the specified @p vcardvalue.
 */
LIBICAL_VCARD_EXPORT void vcardvalue_set_parent(vcardvalue *value, vcardproperty *property);

/**
 * Returns the parent @p vcardproperty for the specified @p vcardvalue.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT vcardproperty *vcardvalue_get_parent(vcardvalue *value);

/* Deal with X properties */

LIBICAL_VCARD_EXPORT void vcardproperty_set_x_name(vcardproperty *prop, const char *name);
LIBICAL_VCARD_EXPORT const char *vcardproperty_get_x_name(vcardproperty *prop);

/* Deal with grouped properties */

LIBICAL_VCARD_EXPORT void vcardproperty_set_group(vcardproperty *prop, const char *group);
LIBICAL_VCARD_EXPORT const char *vcardproperty_get_group(vcardproperty *prop);

/** Returns the name of the property -- the type name converted to a
 *  string, or the value of _get_x_name if the type is and X
 *  property
 */
LIBICAL_VCARD_EXPORT const char *vcardproperty_get_property_name(const vcardproperty *prop);
LIBICAL_VCARD_EXPORT char *vcardproperty_get_property_name_r(const vcardproperty *prop);

LIBICAL_VCARD_EXPORT vcardvalue_kind vcardparameter_value_to_value_kind(vcardparameter_value value);

/**
 * Sets the parent @p vcardproperty for the specified @p vcardparameter.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT void vcardparameter_set_parent(vcardparameter *param, vcardproperty *property);

/**
 * Returns the parent @p vcardproperty for the specified @p vcardparameter.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT vcardproperty *vcardparameter_get_parent(vcardparameter *param);

/* Convert kinds to string and get default value type */
LIBICAL_VCARD_EXPORT vcardvalue_kind vcardproperty_kind_to_value_kind(vcardproperty_kind kind);
LIBICAL_VCARD_EXPORT vcardproperty_kind vcardproperty_value_kind_to_kind(vcardvalue_kind kind);
LIBICAL_VCARD_EXPORT const char *vcardproperty_kind_to_string(vcardproperty_kind kind);
LIBICAL_VCARD_EXPORT vcardproperty_kind vcardproperty_string_to_kind(const char *string);

/** Check validity of a specific vcardproperty_kind **/
LIBICAL_VCARD_EXPORT int vcardproperty_kind_is_valid(const vcardproperty_kind kind);

LIBICAL_VCARD_EXPORT const char *vcardproperty_enum_to_string(int e);
LIBICAL_VCARD_EXPORT char *vcardproperty_enum_to_string_r(int e);
LIBICAL_VCARD_EXPORT int vcardproperty_kind_and_string_to_enum(const int kind, const char *str);

LIBICAL_VCARD_EXPORT int vcardproperty_enum_belongs_to_property(vcardproperty_kind kind, int e);

/**
 * Normalizes (reorders and sorts the parameters) the specified @p vcardproperty.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT void vcardproperty_normalize(vcardproperty *prop);

LIBICAL_VCARD_EXPORT int vcardproperty_is_structured(vcardproperty_kind pkind);
LIBICAL_VCARD_EXPORT int vcardproperty_is_multivalued(vcardproperty_kind pkind);

LIBICAL_VCARD_EXPORT void vcardproperty_add_type_parameter(vcardproperty *prop,
                                                           vcardenumarray_element *type);

#endif /*VCARDPROPERTY_H */

/*======================================================================
 FILE: vcardcomponent.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDCOMPONENT_H
#define VCARDCOMPONENT_H

#include "libical_sentinel.h"
#include "libical_vcard_export.h"


typedef enum vcardcomponent_kind
{
    VCARD_NO_COMPONENT,
    VCARD_ANY_COMPONENT,   /* Used to select all components */
    VCARD_XROOT_COMPONENT, /* Used as container for multiple vCards */
    VCARD_VCARD_COMPONENT,
    VCARD_X_COMPONENT,
    VCARD_NUM_COMPONENT_TYPES /* MUST be last (unless we can put NO_COMP last) */
} vcardcomponent_kind;

typedef struct vcardcomponent_impl vcardcomponent;

/** @brief Constructor
 */
LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_new(vcardcomponent_kind kind);

/**
 * @brief Deeply clones an vcard.
 * Returns a pointer to the memory for the newly cloned vcard.
 * @since 3.1.0
 */
LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_clone(const vcardcomponent *card);

/** @brief Constructor
 */
LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_new_from_string(const char *str);

/** @brief Constructor
 */
LIBICAL_VCARD_EXPORT LIBICAL_SENTINEL vcardcomponent *vcardcomponent_vanew(vcardcomponent_kind kind, ...);

/*** @brief Destructor
 */
LIBICAL_VCARD_EXPORT void vcardcomponent_free(vcardcomponent *card);

LIBICAL_VCARD_EXPORT char *vcardcomponent_as_vcard_string(vcardcomponent *card);

LIBICAL_VCARD_EXPORT char *vcardcomponent_as_vcard_string_r(vcardcomponent *card);

LIBICAL_VCARD_EXPORT int vcardcomponent_is_valid(vcardcomponent *card);

LIBICAL_VCARD_EXPORT vcardcomponent_kind vcardcomponent_isa(const vcardcomponent *component);

LIBICAL_VCARD_EXPORT int vcardcomponent_isa_component(void *component);

/***** Working with Properties *****/

LIBICAL_VCARD_EXPORT void vcardcomponent_add_property(vcardcomponent *card,
                                                      vcardproperty *property);

LIBICAL_VCARD_EXPORT void vcardcomponent_remove_property(vcardcomponent *card,
                                                         vcardproperty *property);

LIBICAL_VCARD_EXPORT int vcardcomponent_count_properties(vcardcomponent *card,
                                                         vcardproperty_kind kind,
                                                         int ignore_alts);

/***** Working with Components *****/

LIBICAL_VCARD_EXPORT void vcardcomponent_add_component(vcardcomponent *parent, vcardcomponent *child);

LIBICAL_VCARD_EXPORT void vcardcomponent_remove_component(vcardcomponent *parent,
                                                          vcardcomponent *child);

LIBICAL_VCARD_EXPORT int vcardcomponent_count_components(vcardcomponent *component,
                                                         vcardcomponent_kind kind);

/* Kind conversion routines */

LIBICAL_VCARD_EXPORT int vcardcomponent_kind_is_valid(const vcardcomponent_kind kind);

LIBICAL_VCARD_EXPORT vcardcomponent_kind vcardcomponent_string_to_kind(const char *string);

LIBICAL_VCARD_EXPORT const char *vcardcomponent_kind_to_string(vcardcomponent_kind kind);

/**
 *  This takes 2 VCARD components and merges the second one into the first.
 *  comp_to_merge will no longer exist after calling this function.
 */
LIBICAL_VCARD_EXPORT void vcardcomponent_merge_component(vcardcomponent *comp,
                                                         vcardcomponent *comp_to_merge);

/* Iteration Routines. There are two forms of iterators, internal and
external. The internal ones came first, and are almost completely
sufficient, but they fail badly when you want to construct a loop that
removes components from the container.*/

/* Iterate through components */
LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_get_current_component(vcardcomponent *component);

LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_get_first_component(vcardcomponent *component,
                                                                        vcardcomponent_kind kind);
LIBICAL_VCARD_EXPORT vcardcomponent *vcardcomponent_get_next_component(vcardcomponent *component,
                                                                       vcardcomponent_kind kind);

/**
 * @brief Sets the parent vcard for the specified vcardproperty @p property.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT void vcardproperty_set_parent(vcardproperty *property,
                                                   vcardcomponent *card);

/**
 * @brief Returns the parent vcard for the specified @p property.
 */
LIBICAL_VCARD_EXPORT vcardcomponent *vcardproperty_get_parent(const vcardproperty *property);

/* Iterate through the properties */
LIBICAL_VCARD_EXPORT vcardproperty *vcardcomponent_get_current_property(vcardcomponent *card);

LIBICAL_VCARD_EXPORT vcardproperty *vcardcomponent_get_first_property(vcardcomponent *card,
                                                                      vcardproperty_kind kind);
LIBICAL_VCARD_EXPORT vcardproperty *vcardcomponent_get_next_property(vcardcomponent *component,
                                                                     vcardproperty_kind kind);

/**
 *  This takes 2 VCARD components and merges the second one into the first.
 *  comp_to_merge will no longer exist after calling this function.
 */
LIBICAL_VCARD_EXPORT void vcardcomponent_merge_card(vcardcomponent *card,
                                                    vcardcomponent *card_to_merge);

/***** Working with embedded error properties *****/

/* Check the component against itip rules and insert error properties*/
/* Working with embedded error properties */
LIBICAL_VCARD_EXPORT int vcardcomponent_check_restrictions(vcardcomponent *card);

/** @brief Returns the number of errors encountered parsing the data.
 *
 * This function counts the number times the X-LIC-ERROR occurs
 * in the data structure.
 */
LIBICAL_VCARD_EXPORT int vcardcomponent_count_errors(vcardcomponent *card);

/** @brief Removes all X-LIC-ERROR properties*/
LIBICAL_VCARD_EXPORT void vcardcomponent_strip_errors(vcardcomponent *card);

/** @brief Converts some X-LIC-ERROR properties into RETURN-STATUS properties*/
LIBICAL_VCARD_EXPORT void vcardcomponent_convert_errors(vcardcomponent *card);

/**
 * @brief Normalizes (reorders and sorts the properties) the specified vcard @p comp.
 * @since 3.0
 */
LIBICAL_VCARD_EXPORT void vcardcomponent_normalize(vcardcomponent *card);

LIBICAL_VCARD_EXPORT void vcardcomponent_transform(vcardcomponent *impl,
                                                   vcardproperty_version version);

/******************** Convenience routines **********************/

LIBICAL_VCARD_EXPORT enum vcardproperty_version vcardcomponent_get_version(vcardcomponent *card);
LIBICAL_VCARD_EXPORT const char *vcardcomponent_get_uid(vcardcomponent *card);
LIBICAL_VCARD_EXPORT const char *vcardcomponent_get_fn(vcardcomponent *card);

#endif /* !VCARDCOMPONENT_H */

/*======================================================================
 FILE: vcardproperty.c

 CREATOR: Ken Murchison 24 Aug 2022

 CONTRIBUTOR: Bron Gondwana

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDPARSER_H
#define VCARDPARSER_H

#include "libical_vcard_export.h"


LIBICAL_VCARD_EXPORT vcardcomponent *vcardparser_parse_string(const char *str);
LIBICAL_VCARD_EXPORT const char *vcardparser_errstr(int err);

#endif /* VCARDPARSER_H */

/*======================================================================
 FILE: vcardrestruction.h

 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDRESTRICTION_H
#define VCARDRESTRICTION_H

#include "libical_vcard_export.h"


/**
 * @brief The kinds of vcardrestrictions there are
 *
 * These must stay in this order for vcardrestriction_compare to work
 */
typedef enum vcardrestriction_kind
{
    /** No restriction. */
    VCARD_RESTRICTION_NONE = 0, /* 0 */

    /** Zero. */
    VCARD_RESTRICTION_ZERO, /* 1 */

    /** One. */
    VCARD_RESTRICTION_ONE, /* 2 */

    /** Zero or more. */
    VCARD_RESTRICTION_ZEROPLUS, /* 3 */

    /** One or more. */
    VCARD_RESTRICTION_ONEPLUS, /* 4 */

    /** Zero or one. */
    VCARD_RESTRICTION_ZEROORONE, /* 5 */

    /** Zero or one, exclusive with another property. */
    VCARD_RESTRICTION_ONEEXCLUSIVE, /* 6 */

    /** Zero or one, mutual with another property. */
    VCARD_RESTRICTION_ONEMUTUAL, /* 7 */

    /** Unknown. */
    VCARD_RESTRICTION_UNKNOWN /* 8 */
} vcardrestriction_kind;

/**
 * @brief Checks if the given @a count is in accordance with the given
 *  restriction, @a restr.
 * @param restr The restriction to apply to the @a count
 * @param count The amount present that is to be checked against the restriction
 * @return 1 if the restriction is met, 0 if not
 *
 * @par Example
 * ```c
 * assert(vcardrestriction_compare(VCARDRESTRICTION_ONEPLUS, 5) == true);
 * assert(vcardrestriction_compare(VCARDRESTRICTION_NONE,    3) == false);
 * ```
 */
LIBICAL_VCARD_EXPORT int vcardrestriction_compare(vcardrestriction_kind restr,
                                                  int count);

/**
 * @brief Checks if a given `VCARD` meets all the restrictions imposed by
 *  the standard.
 * @param comp The `VCARD/XROOT` component to check
 * @return 1 if the restrictions are met, 0 if not
 *
 * @par Error handling
 * Returns 0 and sets ::vcarderrno if `NULL` is passed as @a comp, or if the
 * component is not a `VCARD`.
 *
 * @par Example
 * ```c
 * vcardcomponent *component = // ...
 *
 * // check component
 * assert(vcardrestriction_check(component) == true);
 * ```
 */
LIBICAL_VCARD_EXPORT int vcardrestriction_check(vcardcomponent *comp);

#endif /* VCARDRESTRICTION_H */


#ifdef __cplusplus
}
#endif
#endif
#endif
