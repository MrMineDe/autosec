/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_PROPERTY_H
#define I_CAL_PROPERTY_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>
#include <libical-glib/i-cal-derived-parameter.h>
#include <libical-glib/i-cal-derived-property.h>
#include <libical-glib/i-cal-derived-value.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_PROPERTY \
    (i_cal_property_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalProperty, i_cal_property, I_CAL, PROPERTY, ICalObject)

/**
 * ICalProperty:
 *
 * This is the ICalProperty instance.
 */

/**
 * ICalPropertyClass:
 *
 * This is the ICalProperty class.
 */
struct _ICalPropertyClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalProperty *	i_cal_property_new		(ICalPropertyKind kind);

LIBICAL_ICAL_EXPORT
ICalProperty *	i_cal_property_clone		(const ICalProperty *prop);

LIBICAL_ICAL_EXPORT
ICalProperty *	i_cal_property_new_from_string	(const gchar *str);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_property_as_ical_string	(ICalProperty *prop);

LIBICAL_ICAL_EXPORT
void		i_cal_property_free		(ICalProperty *prop);

LIBICAL_ICAL_EXPORT
ICalPropertyKind 
		i_cal_property_isa		(ICalProperty *property);

LIBICAL_ICAL_EXPORT
gint 		i_cal_property_isa_property	(ICalProperty *property);

LIBICAL_ICAL_EXPORT
void		i_cal_property_add_parameter	(ICalProperty *prop,
						 ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
void		i_cal_property_take_parameter	(ICalProperty *prop,
						 ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
void		i_cal_property_set_parameter	(ICalProperty *prop,
						 ICalParameter *parameter);

LIBICAL_ICAL_EXPORT
void		i_cal_property_set_parameter_from_string
						(ICalProperty *prop,
						 const gchar *name,
						 const gchar *value);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_property_get_parameter_as_string
						(ICalProperty *prop,
						 const gchar *name);

LIBICAL_ICAL_EXPORT
void		i_cal_property_remove_parameter_by_kind
						(ICalProperty *prop,
						 ICalParameterKind kind);

LIBICAL_ICAL_EXPORT
void		i_cal_property_remove_parameter_by_name
						(ICalProperty *prop,
						 const gchar *name);

LIBICAL_ICAL_EXPORT
void		i_cal_property_remove_parameter_by_ref
						(ICalProperty *prop,
						 ICalParameter *param);

LIBICAL_ICAL_EXPORT
gint 		i_cal_property_count_parameters	(const ICalProperty *prop);

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_property_get_first_parameter
						(ICalProperty *prop,
						 ICalParameterKind kind);

LIBICAL_ICAL_EXPORT
ICalParameter *	i_cal_property_get_next_parameter
						(ICalProperty *prop,
						 ICalParameterKind kind);

LIBICAL_ICAL_EXPORT
void		i_cal_property_set_value	(ICalProperty *prop,
						 ICalValue *value);

LIBICAL_ICAL_EXPORT
void		i_cal_property_take_value	(ICalProperty *prop,
						 ICalValue *value);

LIBICAL_ICAL_EXPORT
void		i_cal_property_set_value_from_string
						(ICalProperty *prop,
						 const gchar *value,
						 const gchar *kind);

LIBICAL_ICAL_EXPORT
ICalValue *	i_cal_property_get_value	(const ICalProperty *prop);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_property_get_value_as_string
						(const ICalProperty *prop);

LIBICAL_ICAL_EXPORT
void		i_cal_value_set_parent		(ICalValue *value,
						 ICalProperty *property);

LIBICAL_ICAL_EXPORT
ICalProperty *	i_cal_value_get_parent		(ICalValue *value);

LIBICAL_ICAL_EXPORT
void		i_cal_parameter_set_parent	(ICalParameter *param,
						 ICalProperty *property);

LIBICAL_ICAL_EXPORT
ICalProperty *	i_cal_parameter_get_parent	(ICalParameter *param);

LIBICAL_ICAL_EXPORT
void		i_cal_property_set_x_name	(ICalProperty *prop,
						 const gchar *name);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_property_get_x_name	(ICalProperty *prop);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_property_get_property_name
						(const ICalProperty *prop);

LIBICAL_ICAL_EXPORT
ICalValueKind 	i_cal_parameter_value_to_value_kind
						(ICalParameterValue value);

LIBICAL_ICAL_EXPORT
ICalValueKind 	i_cal_property_kind_to_value_kind
						(ICalPropertyKind kind);

LIBICAL_ICAL_EXPORT
ICalPropertyKind 
		i_cal_value_kind_to_property_kind
						(ICalValueKind kind);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_property_kind_to_string	(ICalPropertyKind kind);

LIBICAL_ICAL_EXPORT
ICalPropertyKind 
		i_cal_property_kind_from_string	(const gchar *string);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_property_kind_is_valid	(const ICalPropertyKind kind);

LIBICAL_ICAL_EXPORT
ICalPropertyMethod 
		i_cal_property_method_from_string
						(const gchar *str);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_property_method_to_string	(ICalPropertyMethod method);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_property_enum_to_string	(gint e);

LIBICAL_ICAL_EXPORT
gint 		i_cal_property_kind_and_string_to_enum
						(const gint kind,
						 const gchar *str);

LIBICAL_ICAL_EXPORT
ICalPropertyStatus 
		i_cal_property_status_from_string
						(const gchar *str);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_property_status_to_string	(ICalPropertyStatus method);

LIBICAL_ICAL_EXPORT
gint 		i_cal_property_kind_has_property
						(ICalPropertyKind kind,
						 gint e);

G_END_DECLS

#endif /* I_CAL_PROPERTY_H */
