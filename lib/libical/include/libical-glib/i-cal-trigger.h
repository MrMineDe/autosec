/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_TRIGGER_H
#define I_CAL_TRIGGER_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_TRIGGER \
    (i_cal_trigger_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalTrigger, i_cal_trigger, I_CAL, TRIGGER, ICalObject)

/**
 * ICalTrigger:
 *
 * This is the ICalTrigger instance.
 */

/**
 * ICalTriggerClass:
 *
 * This is the ICalTrigger class.
 */
struct _ICalTriggerClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalTrigger *	i_cal_trigger_new_from_int	(const gint reltime);

LIBICAL_ICAL_EXPORT
ICalTrigger *	i_cal_trigger_new_from_string	(const gchar *str);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_trigger_is_null_trigger	(ICalTrigger *tr);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_trigger_is_bad_trigger	(ICalTrigger *tr);

LIBICAL_ICAL_EXPORT
ICalTime *	i_cal_trigger_get_time		(ICalTrigger *trigger);

LIBICAL_ICAL_EXPORT
void		i_cal_trigger_set_time		(ICalTrigger *trigger,
						 ICalTime *time);

LIBICAL_ICAL_EXPORT
ICalDuration *	i_cal_trigger_get_duration	(ICalTrigger *trigger);

LIBICAL_ICAL_EXPORT
void		i_cal_trigger_set_duration	(ICalTrigger *trigger,
						 ICalDuration *duration);

G_END_DECLS

#endif /* I_CAL_TRIGGER_H */
