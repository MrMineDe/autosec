/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_GEO_H
#define I_CAL_GEO_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_GEO \
    (i_cal_geo_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalGeo, i_cal_geo, I_CAL, GEO, ICalObject)

/**
 * ICalGeo:
 *
 * This is the ICalGeo instance.
 */

/**
 * ICalGeoClass:
 *
 * This is the ICalGeo class.
 */
struct _ICalGeoClass {
    /*< private >*/
    ICalObjectClass parent;
};

LIBICAL_ICAL_EXPORT
ICalGeo *	i_cal_geo_new			(gdouble lat,
						 gdouble lon);

LIBICAL_ICAL_EXPORT
ICalGeo *	i_cal_geo_clone			(const ICalGeo *geo);

LIBICAL_ICAL_EXPORT
gdouble 		i_cal_geo_get_lat		(ICalGeo *geo);

LIBICAL_ICAL_EXPORT
void		i_cal_geo_set_lat		(ICalGeo *geo,
						 gdouble lat);

LIBICAL_ICAL_EXPORT
gdouble 		i_cal_geo_get_lon		(ICalGeo *geo);

LIBICAL_ICAL_EXPORT
void		i_cal_geo_set_lon		(ICalGeo *geo,
						 gdouble lon);

G_END_DECLS

#endif /* I_CAL_GEO_H */
