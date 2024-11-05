/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_VALUE_H
#define I_CAL_VALUE_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <string.h>
#include <libical-glib/i-cal-object.h>
#include <libical-glib/i-cal-derived-parameter.h>
#include <libical-glib/i-cal-derived-value.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_VALUE \
    (i_cal_value_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalValue, i_cal_value, I_CAL, VALUE, ICalObject)

/**
 * ICalValue:
 *
 * This is the ICalValue instance.
 */

/**
 * ICalValueClass:
 *
 * This is the ICalValue class.
 */
struct _ICalValueClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalValue *	i_cal_value_new			(ICalValueKind kind);

LIBICAL_ICAL_EXPORT
ICalValue *	i_cal_value_clone		(const ICalValue *value);

LIBICAL_ICAL_EXPORT
ICalValue *	i_cal_value_new_from_string	(ICalValueKind kind,
						 const gchar *str);

LIBICAL_ICAL_EXPORT
void		i_cal_value_free		(ICalValue *value);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_value_is_valid		(const ICalValue *value);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_value_as_ical_string	(const ICalValue *value);

LIBICAL_ICAL_EXPORT
ICalValueKind 	i_cal_value_isa			(const ICalValue *value);

LIBICAL_ICAL_EXPORT
gint 		i_cal_value_isa_value		(ICalValue *value);

LIBICAL_ICAL_EXPORT
ICalParameterXliccomparetype 
		i_cal_value_compare		(const ICalValue *a,
						 const ICalValue *b);

LIBICAL_ICAL_EXPORT
ICalValueKind 	i_cal_value_kind_from_string	(const gchar *str);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_value_kind_to_string	(const ICalValueKind kind);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_value_kind_is_valid	(const ICalValueKind kind);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_value_encode_ical_string	(const gchar *szText);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_value_decode_ical_string	(const gchar *szText);

G_END_DECLS

#endif /* I_CAL_VALUE_H */
