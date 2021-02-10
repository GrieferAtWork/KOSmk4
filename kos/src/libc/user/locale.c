/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_LOCALE_C
#define GUARD_LIBC_USER_LOCALE_C 1

#include "../api.h"
#include "locale.h"

DECL_BEGIN



/* TODO: On startup, `current_locale' should be "C"
 *       Once `setlocale(LC_ALL, "");' is called, it
 *       should become some string that contains ".UTF-8".
 *       The later is checked for by libncursesw and must
 *       be present for full unicode support. */
PRIVATE ATTR_SECTION(".data.crt.unsorted.current_locale")
char current_locale[] = "C.UTF-8";

PRIVATE ATTR_SECTION(".data.crt.unsorted.current_lconv")
struct lconv current_lconv = {
	/* .decimal_point      = */ NULL,
	/* .thousands_sep      = */ NULL,
	/* .grouping           = */ NULL,
	/* .int_curr_symbol    = */ NULL,
	/* .currency_symbol    = */ NULL,
	/* .mon_decimal_point  = */ NULL,
	/* .mon_thousands_sep  = */ NULL,
	/* .mon_grouping       = */ NULL,
	/* .positive_sign      = */ NULL,
	/* .negative_sign      = */ NULL,
	/* .int_frac_digits    = */ CHAR_MAX,
	/* .frac_digits        = */ CHAR_MAX,
	/* .p_cs_precedes      = */ CHAR_MAX,
	/* .p_sep_by_space     = */ CHAR_MAX,
	/* .n_cs_precedes      = */ CHAR_MAX,
	/* .n_sep_by_space     = */ CHAR_MAX,
	/* .p_sign_posn        = */ CHAR_MAX,
	/* .n_sign_posn        = */ CHAR_MAX,
	/* .int_p_cs_precedes  = */ CHAR_MAX,
	/* .int_p_sep_by_space = */ CHAR_MAX,
	/* .int_n_cs_precedes  = */ CHAR_MAX,
	/* .int_n_sep_by_space = */ CHAR_MAX,
	/* .int_p_sign_posn    = */ CHAR_MAX,
	/* .int_n_sign_posn    = */ CHAR_MAX
};




/*[[[head:libc_setlocale,hash:CRC-32=0xcd2b53e]]]*/
/* >> setlocale(3)
 * Get or set the current locale
 * @param: category: One of `LC_*'
 * @param: locale:   Name of the locale (e.g. "C")
 *                   When `NULL', don't change the locale.
 * @return: * :      The current locale set for `category'
 * @return: NULL:    Error */
INTERN ATTR_SECTION(".text.crt.unsorted") char *
NOTHROW_NCX(LIBCCALL libc_setlocale)(int category,
                                     char const *locale)
/*[[[body:libc_setlocale]]]*/
{
	COMPILER_IMPURE();
	(void)category;
	(void)locale;
	return current_locale;
}
/*[[[end:libc_setlocale]]]*/

/*[[[head:libc_localeconv,hash:CRC-32=0xad508515]]]*/
/* >> localeconv(3)
 * Return numeric and monetary information for the current locale */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_RETNONNULL WUNUSED struct lconv *
NOTHROW_NCX(LIBCCALL libc_localeconv)(void)
/*[[[body:libc_localeconv]]]*/
{
	if (!current_lconv.negative_sign) {
		/* Initialize as mandated by the standard for the "C" locale. */
		current_lconv.decimal_point      = (char *)".";
		current_lconv.thousands_sep      = (char *)"";
		current_lconv.grouping           = (char *)"";
		current_lconv.int_curr_symbol    = (char *)"";
		current_lconv.currency_symbol    = (char *)"";
		current_lconv.mon_decimal_point  = (char *)"";
		current_lconv.mon_thousands_sep  = (char *)"";
		current_lconv.mon_grouping       = (char *)"";
		current_lconv.positive_sign      = (char *)"";
		COMPILER_WRITE_BARRIER();
		current_lconv.negative_sign = (char *)"";
	}
	return &current_lconv;
}
/*[[[end:libc_localeconv]]]*/

/*[[[head:libc_newlocale,hash:CRC-32=0xc5598fa4]]]*/
/* >> newlocale(3)
 * @param: category_mask: Set of `LC_*_MASK' */
INTERN ATTR_SECTION(".text.crt.unsorted") locale_t
NOTHROW_NCX(LIBCCALL libc_newlocale)(int category_mask,
                                     char const *locale,
                                     locale_t base)
/*[[[body:libc_newlocale]]]*/
/*AUTO*/{
	(void)category_mask;
	(void)locale;
	(void)base;
	CRT_UNIMPLEMENTEDF("newlocale(%x, %q, %p)", category_mask, locale, base); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_newlocale]]]*/

/*[[[head:libc_duplocale,hash:CRC-32=0xa5a82dae]]]*/
/* >> duplocale(3)
 * Duplicate the given locale `dataset' */
INTERN ATTR_SECTION(".text.crt.unsorted") locale_t
NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset)
/*[[[body:libc_duplocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("duplocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_duplocale]]]*/

/*[[[head:libc_freelocale,hash:CRC-32=0xf88daef1]]]*/
/* >> freelocale(3) */
INTERN ATTR_SECTION(".text.crt.unsorted") void
NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset)
/*[[[body:libc_freelocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("freelocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_freelocale]]]*/

/*[[[head:libc_uselocale,hash:CRC-32=0xe15bd1d4]]]*/
/* >> uselocale(3)
 * Set the calling thread's current default locale to `dataset'
 * @param: dataset: NULL:             Don't change the calling thread's locale
 * @param: dataset: LC_GLOBAL_LOCALE: Use the global locale (s.a. `setlocale(3)')
 * @param: dataset: * :               The new locale to set
 * @return: NULL:             Error
 * @return: LC_GLOBAL_LOCALE: The calling thread uses the global locale (default)
 * @return: * :               The currently used locale */
INTERN ATTR_SECTION(".text.crt.unsorted") locale_t
NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset)
/*[[[body:libc_uselocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("uselocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_uselocale]]]*/





/*[[[start:exports,hash:CRC-32=0xe0a21aaa]]]*/
DEFINE_PUBLIC_ALIAS(setlocale, libc_setlocale);
DEFINE_PUBLIC_ALIAS(localeconv, libc_localeconv);
DEFINE_PUBLIC_ALIAS(__newlocale, libc_newlocale);
DEFINE_PUBLIC_ALIAS(newlocale, libc_newlocale);
DEFINE_PUBLIC_ALIAS(__duplocale, libc_duplocale);
DEFINE_PUBLIC_ALIAS(duplocale, libc_duplocale);
DEFINE_PUBLIC_ALIAS(__freelocale, libc_freelocale);
DEFINE_PUBLIC_ALIAS(freelocale, libc_freelocale);
DEFINE_PUBLIC_ALIAS(__uselocale, libc_uselocale);
DEFINE_PUBLIC_ALIAS(uselocale, libc_uselocale);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_C */
