/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/locale.h) */
/* (#) Portability: DJGPP         (/include/locale.h) */
/* (#) Portability: DragonFly BSD (/include/locale.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/locale.h) */
/* (#) Portability: FreeBSD       (/include/locale.h) */
/* (#) Portability: GNU C Library (/locale/locale.h) */
/* (#) Portability: GNU Hurd      (/usr/include/locale.h) */
/* (#) Portability: MSVC          (/include/locale.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/locale.h) */
/* (#) Portability: NetBSD        (/include/locale.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/locale.h) */
/* (#) Portability: OpenBSD       (/include/locale.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/locale.h) */
/* (#) Portability: PDCLib        (/include/locale.h) */
/* (#) Portability: Windows Kits  (/ucrt/locale.h) */
/* (#) Portability: avr-libc      (/include/locale.h) */
/* (#) Portability: diet libc     (/include/locale.h) */
/* (#) Portability: libc4/5       (/include/locale.h) */
/* (#) Portability: libc6         (/include/locale.h) */
/* (#) Portability: mintlib       (/include/locale.h) */
/* (#) Portability: musl libc     (/include/locale.h) */
/* (#) Portability: uClibc        (/include/locale.h) */
}

%[define_ccompat_header("clocale")]
%[define_replacement(locale_t = __locale_t)]
%[default:section(".text.crt{|.dos}.i18n")]

%[define_decl_include("<bits/crt/tm.h>": ["struct tm"])]

%[assume_defined_in_kos_userspace(LC_CTYPE, __LC_CTYPE)]
%[assume_defined_in_kos_userspace(LC_NUMERIC, __LC_NUMERIC)]
%[assume_defined_in_kos_userspace(LC_TIME, __LC_TIME)]
%[assume_defined_in_kos_userspace(LC_COLLATE, __LC_COLLATE)]
%[assume_defined_in_kos_userspace(LC_MONETARY, __LC_MONETARY)]
%[assume_defined_in_kos_userspace(LC_MESSAGES, __LC_MESSAGES)]
%[assume_defined_in_kos_userspace(LC_ALL, __LC_ALL)]
%[assume_defined_in_kos_userspace(LC_PAPER, __LC_PAPER)]
%[assume_defined_in_kos_userspace(LC_NAME, __LC_NAME)]
%[assume_defined_in_kos_userspace(LC_ADDRESS, __LC_ADDRESS)]
%[assume_defined_in_kos_userspace(LC_TELEPHONE, __LC_TELEPHONE)]
%[assume_defined_in_kos_userspace(LC_MEASUREMENT, __LC_MEASUREMENT)]
%[assume_defined_in_kos_userspace(LC_IDENTIFICATION, __LC_IDENTIFICATION)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/locale.h>
)]%[insert:prefix(
#include <bits/crt/lconv.h>
)]%[insert:prefix(
#include <bits/crt/tm.h>
)]%{
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

/* Values for `setlocale(3)::category' */
#if !defined(LC_CTYPE) && defined(__LC_CTYPE)
#define LC_CTYPE __LC_CTYPE
#endif /* !LC_CTYPE && __LC_CTYPE */
#if !defined(LC_NUMERIC) && defined(__LC_NUMERIC)
#define LC_NUMERIC __LC_NUMERIC
#endif /* !LC_NUMERIC && __LC_NUMERIC */
#if !defined(LC_TIME) && defined(__LC_TIME)
#define LC_TIME __LC_TIME
#endif /* !LC_TIME && __LC_TIME */
#if !defined(LC_COLLATE) && defined(__LC_COLLATE)
#define LC_COLLATE __LC_COLLATE
#endif /* !LC_COLLATE && __LC_COLLATE */
#if !defined(LC_MONETARY) && defined(__LC_MONETARY)
#define LC_MONETARY __LC_MONETARY
#endif /* !LC_MONETARY && __LC_MONETARY */
#if !defined(LC_MESSAGES) && defined(__LC_MESSAGES)
#define LC_MESSAGES __LC_MESSAGES
#endif /* !LC_MESSAGES && __LC_MESSAGES */
#if !defined(LC_ALL) && defined(__LC_ALL)
#define LC_ALL __LC_ALL
#endif /* !LC_ALL && __LC_ALL */
#if !defined(LC_PAPER) && defined(__LC_PAPER)
#define LC_PAPER __LC_PAPER
#endif /* !LC_PAPER && __LC_PAPER */
#if !defined(LC_NAME) && defined(__LC_NAME)
#define LC_NAME __LC_NAME
#endif /* !LC_NAME && __LC_NAME */
#if !defined(LC_ADDRESS) && defined(__LC_ADDRESS)
#define LC_ADDRESS __LC_ADDRESS
#endif /* !LC_ADDRESS && __LC_ADDRESS */
#if !defined(LC_TELEPHONE) && defined(__LC_TELEPHONE)
#define LC_TELEPHONE __LC_TELEPHONE
#endif /* !LC_TELEPHONE && __LC_TELEPHONE */
#if !defined(LC_MEASUREMENT) && defined(__LC_MEASUREMENT)
#define LC_MEASUREMENT __LC_MEASUREMENT
#endif /* !LC_MEASUREMENT && __LC_MEASUREMENT */
#if !defined(LC_IDENTIFICATION) && defined(__LC_IDENTIFICATION)
#define LC_IDENTIFICATION __LC_IDENTIFICATION
#endif /* !LC_IDENTIFICATION && __LC_IDENTIFICATION */

#ifdef __USE_XOPEN2K8
/* Flags for `newlocale(3)::category_mask' */
#ifdef __LC_CTYPE
#define LC_CTYPE_MASK               (1 << __LC_CTYPE)
#define __PRIVATE_OPT_LC_CTYPE_MASK (1 << __LC_CTYPE)
#else /* __LC_CTYPE */
#define __PRIVATE_OPT_LC_CTYPE_MASK 0
#endif /* !__LC_CTYPE */
#ifdef __LC_NUMERIC
#define LC_NUMERIC_MASK               (1 << __LC_NUMERIC)
#define __PRIVATE_OPT_LC_NUMERIC_MASK (1 << __LC_NUMERIC)
#else /* __LC_NUMERIC */
#define __PRIVATE_OPT_LC_NUMERIC_MASK 0
#endif /* !__LC_NUMERIC */
#ifdef __LC_TIME
#define LC_TIME_MASK               (1 << __LC_TIME)
#define __PRIVATE_OPT_LC_TIME_MASK (1 << __LC_TIME)
#else /* __LC_TIME */
#define __PRIVATE_OPT_LC_TIME_MASK 0
#endif /* !__LC_TIME */
#ifdef __LC_COLLATE
#define LC_COLLATE_MASK               (1 << __LC_COLLATE)
#define __PRIVATE_OPT_LC_COLLATE_MASK (1 << __LC_COLLATE)
#else /* __LC_COLLATE */
#define __PRIVATE_OPT_LC_COLLATE_MASK 0
#endif /* !__LC_COLLATE */
#ifdef __LC_MONETARY
#define LC_MONETARY_MASK               (1 << __LC_MONETARY)
#define __PRIVATE_OPT_LC_MONETARY_MASK (1 << __LC_MONETARY)
#else /* __LC_MONETARY */
#define __PRIVATE_OPT_LC_MONETARY_MASK 0
#endif /* !__LC_MONETARY */
#ifdef __LC_MESSAGES
#define LC_MESSAGES_MASK               (1 << __LC_MESSAGES)
#define __PRIVATE_OPT_LC_MESSAGES_MASK (1 << __LC_MESSAGES)
#else /* __LC_MESSAGES */
#define __PRIVATE_OPT_LC_MESSAGES_MASK 0
#endif /* !__LC_MESSAGES */
#ifdef __LC_PAPER
#define LC_PAPER_MASK               (1 << __LC_PAPER)
#define __PRIVATE_OPT_LC_PAPER_MASK (1 << __LC_PAPER)
#else /* __LC_PAPER */
#define __PRIVATE_OPT_LC_PAPER_MASK 0
#endif /* !__LC_PAPER */
#ifdef __LC_NAME
#define LC_NAME_MASK               (1 << __LC_NAME)
#define __PRIVATE_OPT_LC_NAME_MASK (1 << __LC_NAME)
#else /* __LC_NAME */
#define __PRIVATE_OPT_LC_NAME_MASK 0
#endif /* !__LC_NAME */
#ifdef __LC_ADDRESS
#define LC_ADDRESS_MASK               (1 << __LC_ADDRESS)
#define __PRIVATE_OPT_LC_ADDRESS_MASK (1 << __LC_ADDRESS)
#else /* __LC_ADDRESS */
#define __PRIVATE_OPT_LC_ADDRESS_MASK 0
#endif /* !__LC_ADDRESS */
#ifdef __LC_TELEPHONE
#define LC_TELEPHONE_MASK               (1 << __LC_TELEPHONE)
#define __PRIVATE_OPT_LC_TELEPHONE_MASK (1 << __LC_TELEPHONE)
#else /* __LC_TELEPHONE */
#define __PRIVATE_OPT_LC_TELEPHONE_MASK 0
#endif /* !__LC_TELEPHONE */
#ifdef __LC_MEASUREMENT
#define LC_MEASUREMENT_MASK               (1 << __LC_MEASUREMENT)
#define __PRIVATE_OPT_LC_MEASUREMENT_MASK (1 << __LC_MEASUREMENT)
#else /* __LC_MEASUREMENT */
#define __PRIVATE_OPT_LC_MEASUREMENT_MASK 0
#endif /* !__LC_MEASUREMENT */
#ifdef __LC_IDENTIFICATION
#define LC_IDENTIFICATION_MASK               (1 << __LC_IDENTIFICATION)
#define __PRIVATE_OPT_LC_IDENTIFICATION_MASK (1 << __LC_IDENTIFICATION)
#else /* __LC_IDENTIFICATION */
#define __PRIVATE_OPT_LC_IDENTIFICATION_MASK 0
#endif /* !__LC_IDENTIFICATION */

#define LC_ALL_MASK                      \
	(__PRIVATE_OPT_LC_CTYPE_MASK |       \
	 __PRIVATE_OPT_LC_NUMERIC_MASK |     \
	 __PRIVATE_OPT_LC_TIME_MASK |        \
	 __PRIVATE_OPT_LC_COLLATE_MASK |     \
	 __PRIVATE_OPT_LC_MONETARY_MASK |    \
	 __PRIVATE_OPT_LC_MESSAGES_MASK |    \
	 __PRIVATE_OPT_LC_PAPER_MASK |       \
	 __PRIVATE_OPT_LC_NAME_MASK |        \
	 __PRIVATE_OPT_LC_ADDRESS_MASK |     \
	 __PRIVATE_OPT_LC_TELEPHONE_MASK |   \
	 __PRIVATE_OPT_LC_MEASUREMENT_MASK | \
	 __PRIVATE_OPT_LC_IDENTIFICATION_MASK)

/* For use-with/return-from `uselocale()': Use the global locale. */
#define LC_GLOBAL_LOCALE (__CCAST(__locale_t)(-1))
#endif /* __USE_XOPEN2K8 */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[insert:std]


@@>> setlocale(3)
@@Get or set the current locale
@@@param: category: One of `LC_*'
@@@param: locale:   Name of the locale (e.g. "C")
@@                  When `NULL', don't change the locale.
@@@return: * :      The current locale set for `category'
@@@return: NULL:    Error
[[std]]
char *setlocale(int category, [[in_opt]] char const *locale);

@@>> localeconv(3)
@@Return numeric and monetary information for the current locale
[[std, decl_include("<bits/crt/lconv.h>")]]
[[wunused, nonnull]] struct lconv *localeconv();

%
%#ifdef __USE_XOPEN2K8

@@>> newlocale(3)
@@@param: category_mask: Set of `LC_*_MASK'
[[export_alias("__newlocale")]]
$locale_t newlocale(int category_mask, [[in_opt]] char const *locale, $locale_t base);

@@>> duplocale(3)
@@Duplicate the given locale `dataset'
[[export_alias("__duplocale")]]
$locale_t duplocale($locale_t dataset);

@@>> freelocale(3)
[[export_alias("__freelocale")]]
void freelocale($locale_t dataset);

@@>> uselocale(3)
@@Set the calling thread's current default locale to `dataset'
@@@param: dataset: NULL:             Don't change the calling thread's locale
@@@param: dataset: LC_GLOBAL_LOCALE: Use the global locale (s.a. `setlocale(3)')
@@@param: dataset: * :               The new locale to set
@@@return: NULL:             Error
@@@return: LC_GLOBAL_LOCALE: The calling thread uses the global locale (default)
@@@return: * :               The currently used locale
[[export_alias("__uselocale")]]
$locale_t uselocale($locale_t dataset);

%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_DOS
%{
#define _ENABLE_PER_THREAD_LOCALE         0x0001
#define _DISABLE_PER_THREAD_LOCALE        0x0002
#define _ENABLE_PER_THREAD_LOCALE_GLOBAL  0x0010
#define _DISABLE_PER_THREAD_LOCALE_GLOBAL 0x0020
#define _ENABLE_PER_THREAD_LOCALE_NEW     0x0100
#define _DISABLE_PER_THREAD_LOCALE_NEW    0x0200
}

%[default:section(".text.crt.dos.i18n")]

void _lock_locales(void);
void _unlock_locales(void);
int _configthreadlocale(int flag);

[[export_alias("__get_current_locale")]]
$locale_t _get_current_locale(void);

[[export_alias("__create_locale")]]
$locale_t _create_locale(int category, [[in_opt]] char const *locale);

[[export_alias("__free_locale")]]
void _free_locale($locale_t locale);

[[wchar, decl_include("<hybrid/typecore.h>")]] $wchar_t *_wsetlocale(int category, [[in_opt]] $wchar_t const *locale);
[[wchar, decl_include("<hybrid/typecore.h>")]] $locale_t _wcreate_locale(int category, [[in_opt]] $wchar_t const *locale);
[[wchar, decl_include("<hybrid/typecore.h>"), wunused]] $wchar_t **___lc_locale_name_func(void);
[[wunused]] unsigned int ___lc_codepage_func(void);
[[wunused]] unsigned int ___lc_collate_cp_func(void);

[[wunused, requires_function(nl_langinfo, malloc)]]
[[impl_include("<asm/crt/langinfo.h>")]]
char *_Getdays(void) {
	/* Essentially, we do:
	 * >> strdup(":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	size_t len = 0;
	unsigned int i;
	char *result;
	for (i = 0; i < 7; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
			len += strlen(p);
		if ((p = nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
			len += strlen(p);
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	if likely(result) {
		char *dst = result;
		for (i = 0; i < 7; ++i) {
			char const *p;
			*dst++ = ':';
			if ((p = nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
				dst = stpcpy(dst, p);
			*dst++ = ':';
			if ((p = nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
				dst = stpcpy(dst, p);
		}
		*dst++ = '\0';
	}
	return result;
}

[[wunused, requires_function(nl_langinfo, malloc)]]
[[wchar, impl_include("<asm/crt/langinfo.h>"), decl_include("<hybrid/typecore.h>")]]
$wchar_t *_W_Getdays(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	size_t len = 0;
	unsigned int i;
	$wchar_t *result;
	for (i = 0; i < 7; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
			len += strlen(p);
		if ((p = nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
			len += strlen(p);
	}
	result = ($wchar_t *)malloc((len + 1) * sizeof($wchar_t));
	if likely(result) {
		$wchar_t *dst = result;
		for (i = 0; i < 7; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = nl_langinfo(id ? (_NL_TIME_DAY_1 + i)
				                        : (_NL_TIME_ABDAY_1 + i))) != NULL) {
					while (*p)
						*dst++ = ($wchar_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = ($wchar_t)'\0';
	}
	return result;
}

[[wunused, requires_function(nl_langinfo, malloc)]]
[[impl_include("<asm/crt/langinfo.h>")]]
char *_Getmonths(void) {
	/* Essentially, we do:
	 * >> strdup(":Jan:January:Feb:February:Mar:March:Apr:April:May:May:Jun:June:Jul:July:Aug:August:Sep:September:Oct:October:Nov:November:Dec:December") */
	size_t len = 0;
	unsigned int i;
	char *result;
	for (i = 0; i < 12; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
			len += strlen(p);
		if ((p = nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
			len += strlen(p);
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	if likely(result) {
		char *dst = result;
		for (i = 0; i < 12; ++i) {
			char const *p;
			*dst++ = ':';
			if ((p = nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
				dst = stpcpy(dst, p);
			*dst++ = ':';
			if ((p = nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
				dst = stpcpy(dst, p);
		}
		*dst++ = '\0';
	}
	return result;
}

[[wunused, requires_function(nl_langinfo, malloc)]]
[[wchar, impl_include("<asm/crt/langinfo.h>"), decl_include("<hybrid/typecore.h>")]]
$wchar_t *_W_Getmonths(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Jan:January:Feb:February:Mar:March:Apr:April:May:May:Jun:June:Jul:July:Aug:August:Sep:September:Oct:October:Nov:November:Dec:December") */
	size_t len = 0;
	unsigned int i;
	$wchar_t *result;
	for (i = 0; i < 12; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
			len += strlen(p);
		if ((p = nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
			len += strlen(p);
	}
	result = ($wchar_t *)malloc((len + 1) * sizeof($wchar_t));
	if likely(result) {
		$wchar_t *dst = result;
		for (i = 0; i < 12; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = nl_langinfo(id ? (_NL_TIME_MON_1 + i)
				                        : (_NL_TIME_ABMON_1 + i))) != NULL) {
					while (*p)
						*dst++ = ($wchar_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = ($wchar_t)'\0';
	}
	return result;
}


[[wunused]] void *_Gettnames(void);
[[wchar, wunused]] void *_W_Gettnames(void);

[[decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>")]]
$size_t _Strftime([[out(? <= bufsize)]] char *buf, $size_t bufsize,
                  [[in]] char const *format,
                  [[in]] struct $tm const *tms, void *lc_time_arg);
[[wchar, decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>")]]
$size_t _Wcsftime([[out(? <= bufsize)]] $wchar_t *buf, $size_t bufsize,
                  [[in]] $wchar_t const *format,
                  [[in]] struct $tm const *tms, void *lc_time_arg);

%#endif /* __USE_DOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
