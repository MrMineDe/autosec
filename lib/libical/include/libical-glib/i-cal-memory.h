/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_MEMORY_H
#define I_CAL_MEMORY_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


LIBICAL_ICAL_EXPORT
void *		i_cal_memory_tmp_buffer		(size_t size);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_memory_tmp_copy		(const gchar *str);

LIBICAL_ICAL_EXPORT
void		i_cal_memory_add_tmp_buffer	(void *buf);

LIBICAL_ICAL_EXPORT
void		i_cal_memory_free_ring		(void);

LIBICAL_ICAL_EXPORT
void *		i_cal_memory_new_buffer		(size_t size);

LIBICAL_ICAL_EXPORT
void *		i_cal_memory_resize_buffer	(void *buf,
						 size_t size);

LIBICAL_ICAL_EXPORT
void		i_cal_memory_free_buffer	(void *buf);

LIBICAL_ICAL_EXPORT
void		i_cal_memory_append_string	(gchar **buf,
						 gchar **pos,
						 size_t *buf_size,
						 const gchar *str);

LIBICAL_ICAL_EXPORT
void		i_cal_memory_append_char	(gchar **buf,
						 gchar **pos,
						 size_t *buf_size,
						 gchar ch);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_memory_strdup		(const gchar *s);

G_END_DECLS

#endif /* I_CAL_MEMORY_H */
