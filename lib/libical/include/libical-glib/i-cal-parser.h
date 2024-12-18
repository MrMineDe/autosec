/* Generated file (by generator) */

/*
 * SPDX-FileCopyrightText: 2015 William Yu <williamyu@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif

#ifndef I_CAL_PARSER_H
#define I_CAL_PARSER_H

#include <libical-glib/i-cal-forward-declarations.h>
#include <libical-glib/i-cal-object.h>

G_BEGIN_DECLS


#define I_CAL_TYPE_PARSER \
    (i_cal_parser_get_type ())
LIBICAL_ICAL_EXPORT
G_DECLARE_DERIVABLE_TYPE(ICalParser, i_cal_parser, I_CAL, PARSER, ICalObject)

/**
 * ICalParser:
 *
 * This is the ICalParser instance.
 */

/**
 * ICalParserClass:
 *
 * This is the ICalParser class.
 */
struct _ICalParserClass {
    /*< private >*/
    ICalObjectClass parent;
};
/**
 * ICalParserLineGenFunc:
 * @bytes: (array length=size) (element-type gchar): the bytes to process
 * @size: the length of the bytes array
 * @user_data: the user data
 *
 * Returns: One content line per invocation
 */
typedef gchar *(*ICalParserLineGenFunc)(gchar *bytes, size_t size, gpointer user_data);
typedef enum {
	I_CAL_PARSER_ERROR = ICALPARSER_ERROR,
	I_CAL_PARSER_SUCCESS = ICALPARSER_SUCCESS,
	I_CAL_PARSER_BEGIN_COMP = ICALPARSER_BEGIN_COMP,
	I_CAL_PARSER_END_COMP = ICALPARSER_END_COMP,
	I_CAL_PARSER_IN_PROGRESS = ICALPARSER_IN_PROGRESS
} ICalParserState;


LIBICAL_ICAL_EXPORT
ICalParser *	i_cal_parser_new		(void);

LIBICAL_ICAL_EXPORT
ICalComponent *	i_cal_parser_add_line		(ICalParser *parser,
						 gchar *str);

LIBICAL_ICAL_EXPORT
ICalComponent *	i_cal_parser_clean		(ICalParser *parser);

LIBICAL_ICAL_EXPORT
ICalParserState 	i_cal_parser_get_state		(ICalParser *parser);

LIBICAL_ICAL_EXPORT
void		i_cal_parser_free		(ICalParser *parser);

LIBICAL_ICAL_EXPORT
ICalComponent *	i_cal_parser_parse		(ICalParser *parser,
						 ICalParserLineGenFunc func,
						 gpointer user_data);

LIBICAL_ICAL_EXPORT
ICalComponent *	i_cal_parser_parse_string	(const gchar *str);

LIBICAL_ICAL_EXPORT
gchar *		i_cal_parser_get_line		(ICalParser *parser,
						 ICalParserLineGenFunc func,
						 gpointer user_data);

G_END_DECLS

#endif /* I_CAL_PARSER_H */
