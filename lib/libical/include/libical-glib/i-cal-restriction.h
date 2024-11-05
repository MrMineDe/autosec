/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_RESTRICTION_H
#define I_CAL_RESTRICTION_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS

typedef enum {
	I_CAL_RESTRICTION_NONE = ICAL_RESTRICTION_NONE,
	I_CAL_RESTRICTION_ZERO = ICAL_RESTRICTION_ZERO,
	I_CAL_RESTRICTION_ONE = ICAL_RESTRICTION_ONE,
	I_CAL_RESTRICTION_ZEROPLUS = ICAL_RESTRICTION_ZEROPLUS,
	I_CAL_RESTRICTION_ONEPLUS = ICAL_RESTRICTION_ONEPLUS,
	I_CAL_RESTRICTION_ZEROORONE = ICAL_RESTRICTION_ZEROORONE,
	I_CAL_RESTRICTION_ONEEXCLUSIVE = ICAL_RESTRICTION_ONEEXCLUSIVE,
	I_CAL_RESTRICTION_ONEMUTUAL = ICAL_RESTRICTION_ONEMUTUAL,
	I_CAL_RESTRICTION_UNKNOWN = ICAL_RESTRICTION_UNKNOWN
} ICalRestrictionKind;


LIBICAL_ICAL_EXPORT
gint 		i_cal_restriction_compare	(ICalRestrictionKind restr,
						 gint count);

LIBICAL_ICAL_EXPORT
gint 		i_cal_restriction_check		(ICalComponent *comp);

G_END_DECLS

#endif /* I_CAL_RESTRICTION_H */
