/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!included_by <locale.h>*/
#ifndef _BITS_CRT_LCONV_H
#define _BITS_CRT_LCONV_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("decimal_point")
#pragma push_macro("thousands_sep")
#pragma push_macro("grouping")
#pragma push_macro("int_curr_symbol")
#pragma push_macro("currency_symbol")
#pragma push_macro("mon_decimal_point")
#pragma push_macro("mon_thousands_sep")
#pragma push_macro("mon_grouping")
#pragma push_macro("positive_sign")
#pragma push_macro("negative_sign")
#pragma push_macro("int_frac_digits")
#pragma push_macro("frac_digits")
#pragma push_macro("p_cs_precedes")
#pragma push_macro("p_sep_by_space")
#pragma push_macro("n_cs_precedes")
#pragma push_macro("n_sep_by_space")
#pragma push_macro("p_sign_posn")
#pragma push_macro("n_sign_posn")
#pragma push_macro("int_p_cs_precedes")
#pragma push_macro("int_p_sep_by_space")
#pragma push_macro("int_n_cs_precedes")
#pragma push_macro("int_n_sep_by_space")
#pragma push_macro("int_p_sign_posn")
#pragma push_macro("int_n_sign_posn")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef decimal_point
#undef thousands_sep
#undef grouping
#undef int_curr_symbol
#undef currency_symbol
#undef mon_decimal_point
#undef mon_thousands_sep
#undef mon_grouping
#undef positive_sign
#undef negative_sign
#undef int_frac_digits
#undef frac_digits
#undef p_cs_precedes
#undef p_sep_by_space
#undef n_cs_precedes
#undef n_sep_by_space
#undef p_sign_posn
#undef n_sign_posn
#undef int_p_cs_precedes
#undef int_p_sep_by_space
#undef int_n_cs_precedes
#undef int_n_sep_by_space
#undef int_p_sign_posn
#undef int_n_sign_posn

/* Structure giving information about numeric and monetary notation. */
__NAMESPACE_STD_BEGIN

struct lconv {
	/* Numeric (non-monetary) information. */
	char *decimal_point;      /* Decimal point character. */
	char *thousands_sep;      /* Thousands separator. */
	char *grouping;           /* Each element is the number of digits in each group;
	                           * elements with  higher  indices  are  farther  left.
	                           * An element with value CHAR_MAX means that no further grouping is done.
	                           * An element with value 0 means that the previous element is used for all groups farther left. */

	/* Monetary information. */
	char *int_curr_symbol;    /* First three chars are a currency symbol from ISO 4217.
	                           * Fourth char  is the  separator.  Fifth char  is  '\0'. */
	char *currency_symbol;    /* Local currency symbol. */
	char *mon_decimal_point;  /* Decimal point character. */
	char *mon_thousands_sep;  /* Thousands separator. */
	char *mon_grouping;       /* Like `grouping' element (above). */
	char *positive_sign;      /* Sign for positive values. */
	char *negative_sign;      /* Sign for negative values. */
	char  int_frac_digits;    /* Int'l fractional digits. */
	char  frac_digits;        /* Local fractional digits. */
	char  p_cs_precedes;      /* 1 if currency_symbol precedes a positive value, 0 if succeeds. */
	char  p_sep_by_space;     /* 1 iff a space separates currency_symbol from a positive value. */
	char  n_cs_precedes;      /* 1 if currency_symbol precedes a negative value, 0 if succeeds. */
	char  n_sep_by_space;     /* 1 iff a space separates currency_symbol from a negative value. */
	char  p_sign_posn;        /* Positive and negative sign positions:
	                           * 0  Parentheses  surround the  quantity  and currency_symbol.
	                           * 1 The sign string precedes the quantity and currency_symbol.
	                           * 2 The sign string follows the quantity and  currency_symbol.
	                           * 3  The sign string immediately precedes the currency_symbol.
	                           * 4  The sign string  immediately follows the currency_symbol. */
	char  n_sign_posn;        /* s.a. `p_sign_posn' */
#ifdef __CRT_DOS_PRIMARY
	__WCHAR16_TYPE__ *_W_decimal_point;
	__WCHAR16_TYPE__ *_W_thousands_sep;
	__WCHAR16_TYPE__ *_W_int_curr_symbol;
	__WCHAR16_TYPE__ *_W_currency_symbol;
	__WCHAR16_TYPE__ *_W_mon_decimal_point;
	__WCHAR16_TYPE__ *_W_mon_thousands_sep;
	__WCHAR16_TYPE__ *_W_positive_sign;
	__WCHAR16_TYPE__ *_W_negative_sign;
#else /* __CRT_DOS_PRIMARY */
#ifdef __USE_ISOC99
	char  int_p_cs_precedes;  /* 1 if int_curr_symbol precedes a positive value, 0 if succeeds. */
	char  int_p_sep_by_space; /* 1 iff a space separates int_curr_symbol from a positive value. */
	char  int_n_cs_precedes;  /* 1 if int_curr_symbol precedes a negative value, 0 if succeeds. */
	char  int_n_sep_by_space; /* 1 iff a space separates int_curr_symbol from a negative value. */
	char  int_p_sign_posn;    /* Positive and negative sign positions:
	                           * 0  Parentheses  surround the  quantity  and int_curr_symbol.
	                           * 1 The sign string precedes the quantity and int_curr_symbol.
	                           * 2 The sign string follows the quantity and  int_curr_symbol.
	                           * 3  The sign string immediately precedes the int_curr_symbol.
	                           * 4  The sign string  immediately follows the int_curr_symbol. */
	char  int_n_sign_posn;    /* s.a. `int_p_sign_posn' */
#else /* __USE_ISOC99 */
	char __int_p_cs_precedes;
	char __int_p_sep_by_space;
	char __int_n_cs_precedes;
	char __int_n_sep_by_space;
	char __int_p_sign_posn;
	char __int_n_sign_posn;
#endif /* !__USE_ISOC99 */
#endif /* !__CRT_DOS_PRIMARY */
};
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(lconv)
#endif /* !__CXX_SYSTEM_HEADER */


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("int_n_sign_posn")
#pragma pop_macro("int_p_sign_posn")
#pragma pop_macro("int_n_sep_by_space")
#pragma pop_macro("int_n_cs_precedes")
#pragma pop_macro("int_p_sep_by_space")
#pragma pop_macro("int_p_cs_precedes")
#pragma pop_macro("n_sign_posn")
#pragma pop_macro("p_sign_posn")
#pragma pop_macro("n_sep_by_space")
#pragma pop_macro("n_cs_precedes")
#pragma pop_macro("p_sep_by_space")
#pragma pop_macro("p_cs_precedes")
#pragma pop_macro("frac_digits")
#pragma pop_macro("int_frac_digits")
#pragma pop_macro("negative_sign")
#pragma pop_macro("positive_sign")
#pragma pop_macro("mon_grouping")
#pragma pop_macro("mon_thousands_sep")
#pragma pop_macro("mon_decimal_point")
#pragma pop_macro("currency_symbol")
#pragma pop_macro("int_curr_symbol")
#pragma pop_macro("grouping")
#pragma pop_macro("thousands_sep")
#pragma pop_macro("decimal_point")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_LCONV_H */
