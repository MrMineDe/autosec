/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_ARRAY_H
#define I_CAL_ARRAY_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_ARRAY \
    (i_cal_array_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalArray, i_cal_array, I_CAL, ARRAY, ICalObject)

/**
 * ICalArray:
 *
 * This is the ICalArray instance.
 */

/**
 * ICalArrayClass:
 *
 * This is the ICalArray class.
 */
struct _ICalArrayClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
gint 		i_cal_array_size		(ICalArray *array);

LIBICAL_ICAL_EXPORT
ICalArray *	i_cal_array_copy		(ICalArray *array);

LIBICAL_ICAL_EXPORT
void		i_cal_array_free		(ICalArray *array);

LIBICAL_ICAL_EXPORT
void		i_cal_array_remove_element_at	(ICalArray *array,
						 gint position);

LIBICAL_ICAL_EXPORT
void		i_cal_array_sort		(ICalArray *array,
						 gint (*compare) (const void *, const void *));

G_END_DECLS

#endif /* I_CAL_ARRAY_H */
