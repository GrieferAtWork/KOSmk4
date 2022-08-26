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

#include <langinfo.h>

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




/*[[[head:libc_setlocale,hash:CRC-32=0xa6ff7968]]]*/
/* >> setlocale(3)
 * Get or set the current locale
 * @param: category: One of `LC_*'
 * @param: locale:   Name of the locale (e.g. "C")
 *                   When `NULL', don't change the locale.
 * @return: * :      The current locale set for `category'
 * @return: NULL:    Error */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_IN_OPT(2) char *
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
		current_lconv.decimal_point      = (char *)nl_langinfo(DECIMAL_POINT);
		current_lconv.thousands_sep      = (char *)nl_langinfo(THOUSANDS_SEP);
		current_lconv.grouping           = (char *)nl_langinfo(GROUPING);
		current_lconv.int_curr_symbol    = (char *)nl_langinfo(INT_CURR_SYMBOL);
		current_lconv.currency_symbol    = (char *)nl_langinfo(CURRENCY_SYMBOL);
		current_lconv.mon_decimal_point  = (char *)nl_langinfo(MON_DECIMAL_POINT);
		current_lconv.mon_thousands_sep  = (char *)nl_langinfo(MON_THOUSANDS_SEP);
		current_lconv.mon_grouping       = (char *)nl_langinfo(MON_GROUPING);
		current_lconv.positive_sign      = (char *)nl_langinfo(POSITIVE_SIGN);
		/* XXX: Use nl_langinfo() to initialize the other fields? */
		COMPILER_WRITE_BARRIER();
		current_lconv.negative_sign = (char *)nl_langinfo(NEGATIVE_SIGN);
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
	CRT_UNIMPLEMENTEDF("newlocale(category_mask: %x, locale: %q, base: %p)", category_mask, locale, base); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
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
	CRT_UNIMPLEMENTEDF("duplocale(dataset: %p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_duplocale]]]*/

/*[[[head:libc_freelocale,hash:CRC-32=0x953c4dc3]]]*/
/* >> freelocale(3) */
INTERN ATTR_SECTION(".text.crt.i18n") void
NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset)
/*[[[body:libc_freelocale]]]*/
/*AUTO*/{
	(void)dataset;
	CRT_UNIMPLEMENTEDF("freelocale(dataset: %p)", dataset); /* TODO */
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
	CRT_UNIMPLEMENTEDF("uselocale(dataset: %p)", dataset); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_uselocale]]]*/

/*[[[head:libc__lock_locales,hash:CRC-32=0xddd288bb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") void
NOTHROW_NCX(LIBCCALL libc__lock_locales)(void)
/*[[[body:libc__lock_locales]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_lock_locales"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__lock_locales]]]*/

/*[[[head:libc__unlock_locales,hash:CRC-32=0x117272e5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") void
NOTHROW_NCX(LIBCCALL libc__unlock_locales)(void)
/*[[[body:libc__unlock_locales]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_unlock_locales"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__unlock_locales]]]*/

/*[[[head:libc__configthreadlocale,hash:CRC-32=0x83708372]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") int
NOTHROW_NCX(LIBCCALL libc__configthreadlocale)(int flag)
/*[[[body:libc__configthreadlocale]]]*/
/*AUTO*/{
	(void)flag;
	CRT_UNIMPLEMENTEDF("_configthreadlocale(flag: %x)", flag); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__configthreadlocale]]]*/

/*[[[head:libc__get_current_locale,hash:CRC-32=0x66b52f40]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc__get_current_locale)(void)
/*[[[body:libc__get_current_locale]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_current_locale"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__get_current_locale]]]*/

/*[[[head:libc__create_locale,hash:CRC-32=0xb7dc98df]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") locale_t
NOTHROW_NCX(LIBCCALL libc__create_locale)(int category,
                                          char const *locale)
/*[[[body:libc__create_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_create_locale(category: %x, locale: %q)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__create_locale]]]*/

/*[[[head:libc__free_locale,hash:CRC-32=0x1e04da1a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") void
NOTHROW_NCX(LIBCCALL libc__free_locale)(locale_t locale)
/*[[[body:libc__free_locale]]]*/
/*AUTO*/{
	(void)locale;
	CRT_UNIMPLEMENTEDF("_free_locale(locale: %p)", locale); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__free_locale]]]*/

/*[[[head:libd__wsetlocale,hash:CRC-32=0x391a4b7e]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN_OPT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__wsetlocale)(int category,
                                       char16_t const *locale)
/*[[[body:libd__wsetlocale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("DOS$_wsetlocale(category: %x, locale: %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wsetlocale]]]*/

/*[[[head:libc__wsetlocale,hash:CRC-32=0x8549908c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN_OPT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__wsetlocale)(int category,
                                       char32_t const *locale)
/*[[[body:libc__wsetlocale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_wsetlocale(category: %x, locale: %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wsetlocale]]]*/

/*[[[head:libd__wcreate_locale,hash:CRC-32=0x47cdc86e]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN_OPT(2) locale_t
NOTHROW_NCX(LIBDCALL libd__wcreate_locale)(int category,
                                           char16_t const *locale)
/*[[[body:libd__wcreate_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("DOS$_wcreate_locale(category: %x, locale: %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wcreate_locale]]]*/

/*[[[head:libc__wcreate_locale,hash:CRC-32=0xf0041433]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN_OPT(2) locale_t
NOTHROW_NCX(LIBKCALL libc__wcreate_locale)(int category,
                                           char32_t const *locale)
/*[[[body:libc__wcreate_locale]]]*/
/*AUTO*/{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_wcreate_locale(category: %x, locale: %p)", category, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wcreate_locale]]]*/

/*[[[head:libd____lc_locale_name_func,hash:CRC-32=0xf44da6b6]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd____lc_locale_name_func)(void)
/*[[[body:libd____lc_locale_name_func]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$___lc_locale_name_func"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd____lc_locale_name_func]]]*/

/*[[[head:libc____lc_locale_name_func,hash:CRC-32=0xa0c056e4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char32_t **
NOTHROW_NCX(LIBKCALL libc____lc_locale_name_func)(void)
/*[[[body:libc____lc_locale_name_func]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("___lc_locale_name_func"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc____lc_locale_name_func]]]*/

/*[[[head:libc____lc_codepage_func,hash:CRC-32=0x22a37f2a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc____lc_codepage_func)(void)
/*[[[body:libc____lc_codepage_func]]]*/
{
	COMPILER_IMPURE();
	return CP_UTF8;
}
/*[[[end:libc____lc_codepage_func]]]*/

DEFINE_INTERN_ALIAS(libc____lc_collate_cp_func, libc____lc_codepage_func);
/*[[[impl:libc____lc_collate_cp_func]]]*/



/*[[[head:libc__Gettnames,hash:CRC-32=0x29ddface]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc__Gettnames)(void)
/*[[[body:libc__Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__Gettnames]]]*/





/*[[[head:libd__W_Gettnames,hash:CRC-32=0x134fc105]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") WUNUSED void *
NOTHROW_NCX(LIBDCALL libd__W_Gettnames)(void)
/*[[[body:libd__W_Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$_W_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__W_Gettnames]]]*/

/*[[[head:libc__W_Gettnames,hash:CRC-32=0x6c770a48]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED void *
NOTHROW_NCX(LIBKCALL libc__W_Gettnames)(void)
/*[[[body:libc__W_Gettnames]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_W_Gettnames"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__W_Gettnames]]]*/

/*[[[head:libc__Strftime,hash:CRC-32=0x425b17cf]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN(3) ATTR_IN(4) ATTR_OUTS(1, 2) size_t
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
	CRT_UNIMPLEMENTEDF("_Strftime(buf: %q, bufsize: %Ix, format: %q, tms: %p, lc_time_arg: %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc__Strftime]]]*/

/*[[[head:libd__Wcsftime,hash:CRC-32=0xf37b3f93]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN(3) ATTR_IN(4) ATTR_OUTS(1, 2) size_t
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
	CRT_UNIMPLEMENTEDF("DOS$_Wcsftime(buf: %p, bufsize: %Ix, format: %p, tms: %p, lc_time_arg: %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libd__Wcsftime]]]*/

/*[[[head:libc__Wcsftime,hash:CRC-32=0x6186e928]]]*/
INTERN ATTR_SECTION(".text.crt.dos.i18n") ATTR_IN(3) ATTR_IN(4) ATTR_OUTS(1, 2) size_t
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
	CRT_UNIMPLEMENTEDF("_Wcsftime(buf: %p, bufsize: %Ix, format: %p, tms: %p, lc_time_arg: %p)", buf, bufsize, format, tms, lc_time_arg); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc__Wcsftime]]]*/





/*[[[start:exports,hash:CRC-32=0x8c949b1e]]]*/
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
DEFINE_PUBLIC_ALIAS(_Gettnames, libc__Gettnames);
DEFINE_PUBLIC_ALIAS(DOS$_W_Gettnames, libd__W_Gettnames);
DEFINE_PUBLIC_ALIAS(_W_Gettnames, libc__W_Gettnames);
DEFINE_PUBLIC_ALIAS(_Strftime, libc__Strftime);
DEFINE_PUBLIC_ALIAS(DOS$_Wcsftime, libd__Wcsftime);
DEFINE_PUBLIC_ALIAS(_Wcsftime, libc__Wcsftime);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_C */
