/*======================================================================
 FILE: vcardderivedparameter.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDPARAMETER_H
#define VCARDDERIVEDPARAMETER_H

#include "libical_vcard_export.h"
#include "vcardenumarray.h"
#include "vcardstrarray.h"
#include "vcardstructured.h"
#include "vcardtime.h"

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

