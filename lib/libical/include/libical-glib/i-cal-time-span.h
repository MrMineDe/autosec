/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_TIME_SPAN_H
#define I_CAL_TIME_SPAN_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-time.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_TIME_SPAN \
    (i_cal_time_span_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalTimeSpan, i_cal_time_span, I_CAL, TIME_SPAN, ICalObject)

/**
 * ICalTimeSpan:
 *
 * This is the ICalTimeSpan instance.
 */

/**
 * ICalTimeSpanClass:
 *
 * This is the ICalTimeSpan class.
 */
struct _ICalTimeSpanClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalTimeSpan *	i_cal_time_span_new_timet	(time_t start,
						 time_t end,
						 gboolean is_busy);

LIBICAL_ICAL_EXPORT
ICalTimeSpan *	i_cal_time_span_clone		(const ICalTimeSpan *src);

LIBICAL_ICAL_EXPORT
time_t 		i_cal_time_span_get_start	(ICalTimeSpan *timespan);

LIBICAL_ICAL_EXPORT
void		i_cal_time_span_set_start	(ICalTimeSpan *timespan,
						 time_t start);

LIBICAL_ICAL_EXPORT
time_t 		i_cal_time_span_get_end		(ICalTimeSpan *timespan);

LIBICAL_ICAL_EXPORT
void		i_cal_time_span_set_end		(ICalTimeSpan *timespan,
						 time_t end);

LIBICAL_ICAL_EXPORT
gboolean 	i_cal_time_span_get_is_busy	(ICalTimeSpan *timespan);

LIBICAL_ICAL_EXPORT
void		i_cal_time_span_set_is_busy	(ICalTimeSpan *timespan,
						 gboolean is_busy);

G_END_DECLS

#endif /* I_CAL_TIME_SPAN_H */
