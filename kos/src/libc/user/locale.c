/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_LOCALE_C
#define GUARD_LIBC_USER_LOCALE_C 1

#include "../api.h"
/**/

#include <nt/winnls.h>

#include "locale.h"

DECL_BEGIN

/* TODO: On  startup,  `current_locale'   should  be   "C"
 *       Once  `setlocale(LC_ALL, "");'   is  called,   it
 *       should become some string that contains ".UTF-8".
 *       The later is checked for by libncursesw and  must
 *       be present for full unicode support. */
PRIVATE ATTR_SECTION(".data.crt.i18n")
char current_locale[] = "C.UTF-8";

PRIVATE ATTR_SECTION(".data.crt.i18n")
struct lconv current_lconv = {
	.decimal_point      = NULL,
	.thousands_sep      = NULL,
	.grouping           = NULL,
	.int_curr_symbol    = NULL,
	.currency_symbol    = NULL,
	.mon_decimal_point  = NULL,
	.mon_thousands_sep  = NULL,
	.mon_grouping       = NULL,
	.positive_sign      = NULL,
	.negative_sign      = NULL,
	.int_frac_digits    = CHAR_MAX,
	.frac_digits        = CHAR_MAX,
	.p_cs_precedes      = CHAR_MAX,
	.p_sep_by_space     = CHAR_MAX,
	.n_cs_precedes      = CHAR_MAX,
	.n_sep_by_space     = CHAR_MAX,
	.p_sign_posn        = CHAR_MAX,
	.n_sign_posn        = CHAR_MAX,
	.int_p_cs_precedes  = CHAR_MAX,
	.int_p_sep_by_space = CHAR_MAX,
	.int_n_cs_precedes  = CHAR_MAX,
	.int_n_sep_by_space = CHAR_MAX,
	.int_p_sign_posn    = CHAR_MAX,
	.int_n_sign_posn    = CHAR_MAX
};




/*[[[head:libc_setlocale,hash:CRC-32=0x5b88cabd]]]*/
/* >> setlocale(3)
 * Get or set the current locale
 * @param: category: One of `LC_*'
 * @param: locale:   Name of the locale (e.g. "C")
 *                   When `NULL', don't change the locale.
 * @return: * :      The current locale set for `category'
 * @return: NULL:    Error */
INTERN ATTR_SECTION(".text.crt.i18n") char *
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

/*[[[head:libc_localeconv,hash:CRC-32=0x17fd1cbf]]]*/
/* >> localeconv(3)
 * Return numeric and monetary information for the current locale */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_RETNONNULL WUNUSED struct lconv *
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

/*[[[head:libc_newlocale,hash:CRC-32=0xdcd02f3f]]]*/
/* >> newlocale(3)
 * @param: category_mask: Set of `LC_*_MASK' */
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
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

/*[[[head:libc_duplocale,hash:CRC-32=0xf10f92ad]]]*/
/* >> duplocale(3)
 * Duplicate the given locale `dataset' */
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset)
/*[[[body:libc_duplocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("duplocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_duplocale]]]*/

/*[[[head:libc_freelocale,hash:CRC-32=0x953c4dc3]]]*/
/* >> freelocale(3) */
INTERN ATTR_SECTION(".text.crt.i18n") void
NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset)
/*[[[body:libc_freelocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("freelocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_freelocale]]]*/

/*[[[head:libc_uselocale,hash:CRC-32=0x441070a]]]*/
/* >> uselocale(3)
 * Set the calling thread's current default locale to `dataset'
 * @param: dataset: NULL:             Don't change the calling thread's locale
 * @param: dataset: LC_GLOBAL_LOCALE: Use the global locale (s.a. `setlocale(3)')
 * @param: dataset: * :               The new locale to set
 * @return: NULL:             Error
 * @return: LC_GLOBAL_LOCALE: The calling thread uses the global locale (default)
 * @return: * :               The currently used locale */
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset)
/*[[[body:libc_uselocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("uselocale(%p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_uselocale]]]*/

/*[[[head:libc__lock_locales,hash:CRC-32=0x85869cb8]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") void
NOTHROW_NCX(LIBCCALL libc__lock_locales)(void)
/*[[[body:libc__lock_locales]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_lock_locales"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__lock_locales]]]*/

/*[[[head:libc__unlock_locales,hash:CRC-32=0x2085ad0f]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") void
NOTHROW_NCX(LIBCCALL libc__unlock_locales)(void)
/*[[[body:libc__unlock_locales]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_unlock_locales"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__unlock_locales]]]*/

/*[[[head:libc__configthreadlocale,hash:CRC-32=0x754bc758]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") int
NOTHROW_NCX(LIBCCALL libc__configthreadlocale)(int flag)
/*[[[body:libc__configthreadlocale]]]*/
/*AUTO*/{
	(void)flag;
	CRT_UNIMPLEMENTEDF("_configthreadlocale(%x)", flag); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__configthreadlocale]]]*/

/*[[[head:libc__get_current_locale,hash:CRC-32=0xbdf8ddd2]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc__get_current_locale)(void)
/*[[[body:libc__get_current_locale]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_current_locale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__get_current_locale]]]*/

/*[[[head:libc__create_locale,hash:CRC-32=0x7410c28a]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc__create_locale)(int category,
                                          char const *locale)
/*[[[body:libc__create_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_create_locale(%x, %q)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__create_locale]]]*/

/*[[[head:libc__free_locale,hash:CRC-32=0xc5492888]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") void
NOTHROW_NCX(LIBCCALL libc__free_locale)(locale_t locale)
/*[[[body:libc__free_locale]]]*/
/*AUTO*/{
	(void)locale;
	CRT_UNIMPLEMENTEDF("_free_locale(%p)", locale); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__free_locale]]]*/

/*[[[head:libd__wsetlocale,hash:CRC-32=0x242a1d03]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") char16_t *
NOTHROW_NCX(LIBDCALL libd__wsetlocale)(int category,
                                       char16_t const *locale)
/*[[[body:libd__wsetlocale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("DOS$_wsetlocale(%x, %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wsetlocale]]]*/

/*[[[head:libc__wsetlocale,hash:CRC-32=0x8a15ef92]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") char32_t *
NOTHROW_NCX(LIBKCALL libc__wsetlocale)(int category,
                                       char32_t const *locale)
/*[[[body:libc__wsetlocale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_wsetlocale(%x, %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wsetlocale]]]*/

/*[[[head:libd__wcreate_locale,hash:CRC-32=0xa3f72498]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") locale_t
NOTHROW_NCX(LIBDCALL libd__wcreate_locale)(int category,
                                           char16_t const *locale)
/*[[[body:libd__wcreate_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("DOS$_wcreate_locale(%x, %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wcreate_locale]]]*/

/*[[[head:libc__wcreate_locale,hash:CRC-32=0x38ddf7e1]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") locale_t
NOTHROW_NCX(LIBKCALL libc__wcreate_locale)(int category,
                                           char32_t const *locale)
/*[[[body:libc__wcreate_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_wcreate_locale(%x, %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wcreate_locale]]]*/

/*[[[head:libd____lc_locale_name_func,hash:CRC-32=0x9c7fd183]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd____lc_locale_name_func)(void)
/*[[[body:libd____lc_locale_name_func]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$___lc_locale_name_func"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd____lc_locale_name_func]]]*/

/*[[[head:libc____lc_locale_name_func,hash:CRC-32=0x5c1f74fe]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED char32_t **
NOTHROW_NCX(LIBKCALL libc____lc_locale_name_func)(void)
/*[[[body:libc____lc_locale_name_func]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("___lc_locale_name_func"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc____lc_locale_name_func]]]*/

/*[[[head:libc____lc_codepage_func,hash:CRC-32=0x8efeeef0]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc____lc_codepage_func)(void)
/*[[[body:libc____lc_codepage_func]]]*/
{
	COMPILER_IMPURE();
	return CP_UTF8;
}
/*[[[end:libc____lc_codepage_func]]]*/

DEFINE_INTERN_ALIAS(libc____lc_collate_cp_func, libc____lc_codepage_func);
/*[[[skip:libc____lc_collate_cp_func]]]*/

/*[[[head:libc__Getdays,hash:CRC-32=0x95013a8b]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc__Getdays)(void)
/*[[[body:libc__Getdays]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_Getdays"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__Getdays]]]*/

/*[[[head:libc__Getmonths,hash:CRC-32=0x2ee2add9]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc__Getmonths)(void)
/*[[[body:libc__Getmonths]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_Getmonths"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__Getmonths]]]*/

/*[[[head:libc__Gettnames,hash:CRC-32=0x4358ee98]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc__Gettnames)(void)
/*[[[body:libc__Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__Gettnames]]]*/

/*[[[head:libd__W_Getdays,hash:CRC-32=0xbfe75543]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd__W_Getdays)(void)
/*[[[body:libd__W_Getdays]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$_W_Getdays"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__W_Getdays]]]*/

/*[[[head:libc__W_Getdays,hash:CRC-32=0x2e980c35]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc__W_Getdays)(void)
/*[[[body:libc__W_Getdays]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_W_Getdays"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__W_Getdays]]]*/

/*[[[head:libd__W_Getmonths,hash:CRC-32=0xf0cca6b0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd__W_Getmonths)(void)
/*[[[body:libd__W_Getmonths]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$_W_Getmonths"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__W_Getmonths]]]*/

/*[[[head:libc__W_Getmonths,hash:CRC-32=0x9b1e00ef]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc__W_Getmonths)(void)
/*[[[body:libc__W_Getmonths]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_W_Getmonths"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__W_Getmonths]]]*/

/*[[[head:libd__W_Gettnames,hash:CRC-32=0x5626e8b7]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED void *
NOTHROW_NCX(LIBDCALL libd__W_Gettnames)(void)
/*[[[body:libd__W_Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$_W_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__W_Gettnames]]]*/

/*[[[head:libc__W_Gettnames,hash:CRC-32=0x9a4c4e62]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") WUNUSED void *
NOTHROW_NCX(LIBKCALL libc__W_Gettnames)(void)
/*[[[body:libc__W_Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_W_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__W_Gettnames]]]*/

/*[[[head:libc__Strftime,hash:CRC-32=0x8c143096]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") NONNULL((3, 4)) size_t
NOTHROW_NCX(LIBCCALL libc__Strftime)(char *buf,
                                     size_t bufsize,
                                     char const *format,
                                     struct tm const *tms,
                                     void *lc_time_arg)
/*[[[body:libc__Strftime]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tms;
	(void)lc_time_arg;
	CRT_UNIMPLEMENTEDF("_Strftime(%q, %Ix, %q, %p, %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__Strftime]]]*/

/*[[[head:libd__Wcsftime,hash:CRC-32=0xa40b9987]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") NONNULL((3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd__Wcsftime)(char16_t *buf,
                                     size_t bufsize,
                                     char16_t const *format,
                                     struct tm const *tms,
                                     void *lc_time_arg)
/*[[[body:libd__Wcsftime]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tms;
	(void)lc_time_arg;
	CRT_UNIMPLEMENTEDF("DOS$_Wcsftime(%p, %Ix, %p, %p, %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__Wcsftime]]]*/

/*[[[head:libc__Wcsftime,hash:CRC-32=0x89dee8d4]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") NONNULL((3, 4)) size_t
NOTHROW_NCX(LIBKCALL libc__Wcsftime)(char32_t *buf,
                                     size_t bufsize,
                                     char32_t const *format,
                                     struct tm const *tms,
                                     void *lc_time_arg)
/*[[[body:libc__Wcsftime]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tms;
	(void)lc_time_arg;
	CRT_UNIMPLEMENTEDF("_Wcsftime(%p, %Ix, %p, %p, %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__Wcsftime]]]*/





/*[[[start:exports,hash:CRC-32=0xa42cf58c]]]*/
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
DEFINE_PUBLIC_ALIAS(_lock_locales, libc__lock_locales);
DEFINE_PUBLIC_ALIAS(_unlock_locales, libc__unlock_locales);
DEFINE_PUBLIC_ALIAS(_configthreadlocale, libc__configthreadlocale);
DEFINE_PUBLIC_ALIAS(__get_current_locale, libc__get_current_locale);
DEFINE_PUBLIC_ALIAS(_get_current_locale, libc__get_current_locale);
DEFINE_PUBLIC_ALIAS(__create_locale, libc__create_locale);
DEFINE_PUBLIC_ALIAS(_create_locale, libc__create_locale);
DEFINE_PUBLIC_ALIAS(__free_locale, libc__free_locale);
DEFINE_PUBLIC_ALIAS(_free_locale, libc__free_locale);
DEFINE_PUBLIC_ALIAS(DOS$_wsetlocale, libd__wsetlocale);
DEFINE_PUBLIC_ALIAS(_wsetlocale, libc__wsetlocale);
DEFINE_PUBLIC_ALIAS(DOS$_wcreate_locale, libd__wcreate_locale);
DEFINE_PUBLIC_ALIAS(_wcreate_locale, libc__wcreate_locale);
DEFINE_PUBLIC_ALIAS(DOS$___lc_locale_name_func, libd____lc_locale_name_func);
DEFINE_PUBLIC_ALIAS(___lc_locale_name_func, libc____lc_locale_name_func);
DEFINE_PUBLIC_ALIAS(___lc_codepage_func, libc____lc_codepage_func);
DEFINE_PUBLIC_ALIAS(___lc_collate_cp_func, libc____lc_collate_cp_func);
DEFINE_PUBLIC_ALIAS(_Getdays, libc__Getdays);
DEFINE_PUBLIC_ALIAS(_Getmonths, libc__Getmonths);
DEFINE_PUBLIC_ALIAS(_Gettnames, libc__Gettnames);
DEFINE_PUBLIC_ALIAS(DOS$_W_Getdays, libd__W_Getdays);
DEFINE_PUBLIC_ALIAS(_W_Getdays, libc__W_Getdays);
DEFINE_PUBLIC_ALIAS(DOS$_W_Getmonths, libd__W_Getmonths);
DEFINE_PUBLIC_ALIAS(_W_Getmonths, libc__W_Getmonths);
DEFINE_PUBLIC_ALIAS(DOS$_W_Gettnames, libd__W_Gettnames);
DEFINE_PUBLIC_ALIAS(_W_Gettnames, libc__W_Gettnames);
DEFINE_PUBLIC_ALIAS(_Strftime, libc__Strftime);
DEFINE_PUBLIC_ALIAS(DOS$_Wcsftime, libd__Wcsftime);
DEFINE_PUBLIC_ALIAS(_Wcsftime, libc__Wcsftime);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_C */
