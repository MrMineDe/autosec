/*======================================================================
 FILE: vcardderivedvalue.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDVALUE_H
#define VCARDDERIVEDVALUE_H

#include "libical_vcard_export.h"
#include "vcardstrarray.h"
#include "vcardstructured.h"
#include "vcardtime.h"
#include "vcardtypes.h"

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
