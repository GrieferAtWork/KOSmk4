/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_ccompat_header("clocale")]
%[define_replacement(locale_t = __locale_t)]

%{
#include <features.h>
#include <bits/locale.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

/* Partially derived from GNU C /usr/include/locale.h */

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Per Bothner <bothner@cygnus.com>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License. This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */


/* These are the possibilities for the first argument to setlocale.
 * The code assumes that the lowest LC_* symbol has the value zero. */
#define LC_CTYPE          __LC_CTYPE
#define LC_NUMERIC        __LC_NUMERIC
#define LC_TIME           __LC_TIME
#define LC_COLLATE        __LC_COLLATE
#define LC_MONETARY       __LC_MONETARY
#define LC_MESSAGES       __LC_MESSAGES
#define LC_ALL            __LC_ALL
#define LC_PAPER          __LC_PAPER
#define LC_NAME           __LC_NAME
#define LC_ADDRESS        __LC_ADDRESS
#define LC_TELEPHONE      __LC_TELEPHONE
#define LC_MEASUREMENT    __LC_MEASUREMENT
#define LC_IDENTIFICATION __LC_IDENTIFICATION

#ifdef __USE_XOPEN2K8
/* These are the bits that can be set in the CATEGORY_MASK argument to
 * `newlocale'. In the GNU implementation, LC_FOO_MASK has the value
 * of (1 << LC_FOO), but this is not a part of the interface that
 * callers can assume will be true. */
#define LC_CTYPE_MASK          (1 << __LC_CTYPE)
#define LC_NUMERIC_MASK        (1 << __LC_NUMERIC)
#define LC_TIME_MASK           (1 << __LC_TIME)
#define LC_COLLATE_MASK        (1 << __LC_COLLATE)
#define LC_MONETARY_MASK       (1 << __LC_MONETARY)
#define LC_MESSAGES_MASK       (1 << __LC_MESSAGES)
#define LC_PAPER_MASK          (1 << __LC_PAPER)
#define LC_NAME_MASK           (1 << __LC_NAME)
#define LC_ADDRESS_MASK        (1 << __LC_ADDRESS)
#define LC_TELEPHONE_MASK      (1 << __LC_TELEPHONE)
#define LC_MEASUREMENT_MASK    (1 << __LC_MEASUREMENT)
#define LC_IDENTIFICATION_MASK (1 << __LC_IDENTIFICATION)
#define LC_ALL_MASK            (LC_CTYPE_MASK | LC_NUMERIC_MASK | LC_TIME_MASK | \
                                LC_COLLATE_MASK | LC_MONETARY_MASK | LC_MESSAGES_MASK | \
                                LC_PAPER_MASK | LC_NAME_MASK | LC_ADDRESS_MASK | \
                                LC_TELEPHONE_MASK | LC_MEASUREMENT_MASK | LC_IDENTIFICATION_MASK)

/* This value can be passed to `uselocale' and may be returned by it.
 * Passing this value to any other function has undefined behavior. */
#define LC_GLOBAL_LOCALE   (__CCAST(__locale_t)(-1))

#endif /* __USE_XOPEN2K8 */



__SYSDECL_BEGIN

#ifdef __CC__

}%[push_macro @undef {
	decimal_point thousands_sep grouping int_curr_symbol currency_symbol
	mon_decimal_point mon_thousands_sep mon_grouping positive_sign negative_sign
	int_frac_digits frac_digits p_cs_precedes p_sep_by_space n_cs_precedes
	n_sep_by_space p_sign_posn n_sign_posn int_p_cs_precedes int_p_sep_by_space
	int_n_cs_precedes int_n_sep_by_space int_p_sign_posn int_n_sign_posn
}]%{

/* Structure giving information about numeric and monetary notation. */
__NAMESPACE_STD_BEGIN

#ifndef __std_lconv_defined
#define __std_lconv_defined 1
#ifdef __lconv_defined
__NAMESPACE_GLB_USING(lconv)
#else /* __lconv_defined */
struct lconv {
	/* Numeric (non-monetary) information. */
	char *decimal_point; /* Decimal point character. */
	char *thousands_sep; /* Thousands separator. */
	char *grouping;      /* Each element is the number of digits in each group;
	                      * elements with higher indices are farther left.
	                      * An element with value CHAR_MAX means that no further grouping is done.
	                      * An element with value 0 means that the previous element is used for all groups farther left. */

	/* Monetary information. */
	char *int_curr_symbol;   /* First three chars are a currency symbol from ISO 4217.
	                          * Fourth char is the separator. Fifth char is '\0'. */
	char *currency_symbol;   /* Local currency symbol. */
	char *mon_decimal_point; /* Decimal point character. */
	char *mon_thousands_sep; /* Thousands separator. */
	char *mon_grouping;      /* Like `grouping' element (above). */
	char *positive_sign;     /* Sign for positive values. */
	char *negative_sign;     /* Sign for negative values. */
	char int_frac_digits;    /* Int'l fractional digits. */
	char frac_digits;        /* Local fractional digits. */
	char p_cs_precedes;      /* 1 if currency_symbol precedes a positive value, 0 if succeeds. */
	char p_sep_by_space;     /* 1 iff a space separates currency_symbol from a positive value. */
	char n_cs_precedes;      /* 1 if currency_symbol precedes a negative value, 0 if succeeds. */
	char n_sep_by_space;     /* 1 iff a space separates currency_symbol from a negative value. */
	char p_sign_posn; /* Positive and negative sign positions:
	                   * 0 Parentheses surround the quantity and currency_symbol.
	                   * 1 The sign string precedes the quantity and currency_symbol.
	                   * 2 The sign string follows the quantity and currency_symbol.
	                   * 3 The sign string immediately precedes the currency_symbol.
	                   * 4 The sign string immediately follows the currency_symbol. */
	char n_sign_posn; /* s.a. `p_sign_posn' */
#ifdef __USE_ISOC99
	char int_p_cs_precedes;  /* 1 if int_curr_symbol precedes a positive value, 0 if succeeds. */
	char int_p_sep_by_space; /* 1 iff a space separates int_curr_symbol from a positive value. */
	char int_n_cs_precedes;  /* 1 if int_curr_symbol precedes a negative value, 0 if succeeds. */
	char int_n_sep_by_space; /* 1 iff a space separates int_curr_symbol from a negative value. */
	char int_p_sign_posn;    /* Positive and negative sign positions:
	                          * 0 Parentheses surround the quantity and int_curr_symbol.
	                          * 1 The sign string precedes the quantity and int_curr_symbol.
	                          * 2 The sign string follows the quantity and int_curr_symbol.
	                          * 3 The sign string immediately precedes the int_curr_symbol.
	                          * 4 The sign string immediately follows the int_curr_symbol. */
	char int_n_sign_posn;    /* s.a. `int_p_sign_posn' */
#else /* __USE_ISOC99 */
	char __int_p_cs_precedes;
	char __int_p_sep_by_space;
	char __int_n_cs_precedes;
	char __int_n_sep_by_space;
	char __int_p_sign_posn;
	char __int_n_sign_posn;
#endif /* !__USE_ISOC99 */
};
#endif /* !__lconv_defined */
#endif /* !__std_lconv_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __lconv_defined
#define __lconv_defined 1
__NAMESPACE_STD_USING(lconv)
#endif /* !__lconv_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */


}%[pop_macro]%{

}

%[insert:std]


@@Set and/or return the current locale
[[std]]
char *setlocale(int category, char const *locale);

@@Return the numeric/monetary information for the current locale
[[std]]
struct lconv *localeconv();

%
%#ifdef __USE_XOPEN2K8
%/* The concept of one static locale per category is not very well
% * thought out. Many applications will need to process its data using
% * information from several different locales. Another application is
% * the implementation of the internationalization handling in the
% * upcoming ISO C++ standard library. To support this another set of
% * the functions using locale data exist which have an additional
% * argument.
% *
% * Attention: all these functions are *not* standardized in any form.
% * This is a proof-of-concept implementation. */

@@Return a reference to a data structure representing a set of locale
@@datasets. Unlike for the CATEGORY parameter for `setlocale' the
@@CATEGORY_MASK parameter here uses a single bit for each category,
@@made by OR'ing together LC_*_MASK bits above
[[export_alias("__newlocale")]]
$locale_t newlocale(int category_mask, char const *locale, $locale_t base);

@@Return a duplicate of the set of locale in DATASET.
@@All usage counters are increased if necessary
[[export_alias("__duplocale")]]
$locale_t duplocale($locale_t dataset);

@@Free the data associated with a locale dataset
@@previously returned by a call to `setlocale_r'
[[export_alias("__freelocale")]]
void freelocale($locale_t dataset);

@@Switch the current thread's locale to DATASET.
@@If DATASET is null, instead just return the current setting.
@@The special value LC_GLOBAL_LOCALE is the initial setting
@@for all threads and can also be installed any time, meaning
@@the thread uses the global settings controlled by `setlocale'
[[export_alias("__uselocale")]]
$locale_t uselocale($locale_t dataset);

%#endif /* __USE_XOPEN2K8 */

%{

#endif /* __CC__ */

__SYSDECL_END

}