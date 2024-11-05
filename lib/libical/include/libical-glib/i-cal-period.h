/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_PERIOD_H
#define I_CAL_PERIOD_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_PERIOD \
    (i_cal_period_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalPeriod, i_cal_period, I_CAL, PERIOD, ICalObject)

/**
 * ICalPeriod:
 *
 * This is the ICalPeriod instance.
 */

/**
 * ICalPeriodClass:
 *
 * This is the ICalPeriod class.
 */
struct _ICalPeriodClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalTime *	i_cal_period_get_start		(ICalPeriod *period);

LIBICAL_ICAL_EXPORT
void		i_cal_period_set_start		(ICalPeriod *period,
						 ICalTime *start);

LIBICAL_ICAL_EXPORT
ICalTime *	i_cal_period_get_end		(ICalPeriod *period);

LIBICAL_ICAL_EXPORT
void		i_cal_period_set_end		(ICalPeriod *period,
						 ICalTime *end);

LIBICAL_ICAL_EXPORT
ICalDuration *	i_cal_period_get_duration	(ICalPeriod *period);

LIBICAL_ICAL_EXPORT
void		i_cal_period_set_duration	(ICalPeriod *period,
						 ICalDuration *duration);

LIBICAL_ICAL_EXPORT
ICalPeriod *	i_cal_period_new_from_string	(const gchar *str);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_period_as_ical_string	(ICalPeriod *p);

LIBICAL_ICAL_EXPORT
ICalPeriod *	i_cal_period_new_null_period	(void);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_period_is_null_period	(ICalPeriod *p);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_period_is_valid_period	(ICalPeriod *p);

G_END_DECLS

#endif /* I_CAL_PERIOD_H */
