/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_MIME_H
#define I_CAL_MIME_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS

/**
 * ICalMimeParseFunc:
 * @bytes: (array length=size) (element-type gchar): the bytes to process
 * @size: the length of the bytes array
 * @user_data: the user data
 *
 * Returns: A #ICalComponent as a string
 */
typedef gchar *(*ICalMimeParseFunc)(gchar *bytes, size_t size, gpointer user_data);

LIBICAL_ICAL_EXPORT
ICalComponent *	i_cal_mime_parse		(ICalMimeParseFunc func,
						 gpointer user_data);

G_END_DECLS

#endif /* I_CAL_MIME_H */
