/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_PARAMETER_H
#define I_CAL_PARAMETER_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>
#include <libical-glib/i-cal-derived-parameter.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_PARAMETER \
    (i_cal_parameter_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalParameter, i_cal_parameter, I_CAL, PARAMETER, ICalObject)

/**
 * ICalParameter:
 *
 * This is the ICalParameter instance.
 */

/**
 * ICalParameterClass:
 *
 * This is the ICalParameter class.
 */
struct _ICalParameterClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_parameter_new		(ICalParameterKind v);

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_parameter_clone		(const ICalParameter *p);

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_parameter_new_from_string	(const gchar *value);

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_parameter_new_from_value_string
						(ICalParameterKind kind,
						 const gchar *value);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_free		(ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_parameter_as_ical_string	(ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
ICalParameterKind 
		i_cal_parameter_isa		(ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
gint 		i_cal_parameter_isa_parameter	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_set_xname	(ICalParameter *param,
						 const gchar *v);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_parameter_get_xname	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_set_xvalue	(ICalParameter *param,
						 const gchar *v);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_parameter_get_xvalue	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_set_iana_name	(ICalParameter *param,
						 const gchar *v);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_parameter_get_iana_name	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_set_iana_value	(ICalParameter *param,
						 const gchar *v);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_parameter_get_iana_value	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
gint 		i_cal_parameter_has_same_name	(ICalParameter *param1,
						 ICalParameter *param2);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_parameter_kind_to_string	(ICalParameterKind kind);

LIBICAL_ICAL_EXPORT
ICalParameterKind 
		i_cal_parameter_kind_from_string
						(const gchar *string);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_parameter_kind_is_valid	(const ICalParameterKind kind);

G_END_DECLS

#endif /* I_CAL_PARAMETER_H */
