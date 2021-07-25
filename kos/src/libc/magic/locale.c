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
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/locale.h) */
/* (#) Portability: DJGPP         (/include/locale.h) */
/* (#) Portability: FreeBSD       (/include/locale.h) */
/* (#) Portability: GNU C Library (/locale/locale.h) */
/* (#) Portability: MSVC          (/include/locale.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/locale.h) */
/* (#) Portability: NetBSD        (/include/locale.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/locale.h) */
/* (#) Portability: OpenBSD       (/include/locale.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/locale.h) */
/* (#) Portability: Windows Kits  (/ucrt/locale.h) */
/* (#) Portability: diet libc     (/include/locale.h) */
/* (#) Portability: musl libc     (/include/locale.h) */
/* (#) Portability: uClibc        (/include/locale.h) */
}

%[define_ccompat_header("clocale")]
%[define_replacement(locale_t = __locale_t)]
%[default:section(".text.crt{|.dos}.i18n")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/locale.h>
)]%[insert:prefix(
#include <bits/crt/lconv.h>
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

__SYSDECL_BEGIN

#ifdef __CC__

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
char *setlocale(int category, char const *locale);

@@>> localeconv(3)
@@Return numeric and monetary information for the current locale
[[std, decl_include("<bits/crt/lconv.h>")]]
[[wunused, nonnull]] struct lconv *localeconv();

%
%#ifdef __USE_XOPEN2K8

@@>> newlocale(3)
@@@param: category_mask: Set of `LC_*_MASK'
[[export_alias("__newlocale")]]
$locale_t newlocale(int category_mask, char const *locale, $locale_t base);

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

%{

__SYSDECL_END
#endif /* __CC__ */

}
