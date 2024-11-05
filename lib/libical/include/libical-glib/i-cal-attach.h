/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_ATTACH_H
#define I_CAL_ATTACH_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_ATTACH \
    (i_cal_attach_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalAttach, i_cal_attach, I_CAL, ATTACH, ICalObject)

/**
 * ICalAttach:
 *
 * This is the ICalAttach instance.
 */

/**
 * ICalAttachClass:
 *
 * This is the ICalAttach class.
 */
struct _ICalAttachClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalAttach *	i_cal_attach_new_from_url	(const gchar *url);

LIBICAL_ICAL_EXPORT
ICalAttach *	i_cal_attach_new_from_data	(const gchar *data,
						 GFunc free_fn,
						 void *free_fn_data);

LIBICAL_ICAL_EXPORT
ICalAttach *	i_cal_attach_new_from_bytes	(GBytes *bytes);

LIBICAL_ICAL_EXPORT
void		i_cal_attach_ref		(ICalAttach *attach);

LIBICAL_ICAL_EXPORT
void		i_cal_attach_unref		(ICalAttach *attach);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_attach_get_is_url		(ICalAttach *attach);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_attach_get_url		(ICalAttach *attach);

LIBICAL_ICAL_EXPORT
const gchar *	i_cal_attach_get_data		(ICalAttach *attach);

G_END_DECLS

#endif /* I_CAL_ATTACH_H */
