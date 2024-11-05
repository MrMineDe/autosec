/*======================================================================
 FILE: vcardderivedproperty.h

 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 ======================================================================*/

#ifndef VCARDDERIVEDPROPERTY_H
#define VCARDDERIVEDPROPERTY_H

#include "libical_sentinel.h"
#include "vcardderivedvalue.h"
#include "vcardparameter.h"

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
