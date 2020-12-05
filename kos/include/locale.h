/* HASH CRC-32:0x2191aa9f */
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
#ifndef _LOCALE_H
#define _LOCALE_H 1

#ifdef _CXX_STDONLY_CLOCALE
#ifdef __CXX_SYSTEM_HEADER
#undef _LOCALE_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "locale.h" after "clocale" */
#ifdef __CRT_HAVE_setlocale
__NAMESPACE_STD_USING(setlocale)
#endif /* __CRT_HAVE_setlocale */
#ifdef __CRT_HAVE_localeconv
__NAMESPACE_STD_USING(localeconv)
#endif /* __CRT_HAVE_localeconv */
#undef _CXX_STDONLY_CLOCALE
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CLOCALE */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

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
/* (#) Portability: OpenSolaris   (/usr/src/head/locale.h) */
/* (#) Portability: diet libc     (/include/locale.h) */
/* (#) Portability: musl libc     (/include/locale.h) */
/* (#) Portability: uClibc        (/include/locale.h) */
#include <features.h>
#include <bits/crt/locale.h>
#include <bits/crt/lconv.h>
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
#ifdef __LC_CTYPE
#define LC_CTYPE __LC_CTYPE
#endif /* __LC_CTYPE */
#ifdef __LC_NUMERIC
#define LC_NUMERIC __LC_NUMERIC
#endif /* __LC_NUMERIC */
#ifdef __LC_TIME
#define LC_TIME __LC_TIME
#endif /* __LC_TIME */
#ifdef __LC_COLLATE
#define LC_COLLATE __LC_COLLATE
#endif /* __LC_COLLATE */
#ifdef __LC_MONETARY
#define LC_MONETARY __LC_MONETARY
#endif /* __LC_MONETARY */
#ifdef __LC_MESSAGES
#define LC_MESSAGES __LC_MESSAGES
#endif /* __LC_MESSAGES */
#ifdef __LC_ALL
#define LC_ALL __LC_ALL
#endif /* __LC_ALL */
#ifdef __LC_PAPER
#define LC_PAPER __LC_PAPER
#endif /* __LC_PAPER */
#ifdef __LC_NAME
#define LC_NAME __LC_NAME
#endif /* __LC_NAME */
#ifdef __LC_ADDRESS
#define LC_ADDRESS __LC_ADDRESS
#endif /* __LC_ADDRESS */
#ifdef __LC_TELEPHONE
#define LC_TELEPHONE __LC_TELEPHONE
#endif /* __LC_TELEPHONE */
#ifdef __LC_MEASUREMENT
#define LC_MEASUREMENT __LC_MEASUREMENT
#endif /* __LC_MEASUREMENT */
#ifdef __LC_IDENTIFICATION
#define LC_IDENTIFICATION __LC_IDENTIFICATION
#endif /* __LC_IDENTIFICATION */

#ifdef __USE_XOPEN2K8
/* These are the bits that can be set in the CATEGORY_MASK argument to
 * `newlocale'. In the GNU implementation, LC_FOO_MASK has the value
 * of (1 << LC_FOO), but this is not a part of the interface that
 * callers can assume will be true. */
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

/* This value can be passed to `uselocale' and may be returned by it.
 * Passing this value to any other function has undefined behavior. */
#define LC_GLOBAL_LOCALE (__CCAST(__locale_t)(-1))
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__

__NAMESPACE_STD_BEGIN
/* Set and/or return the current locale */
__CDECLARE_OPT(,char *,__NOTHROW_NCX,setlocale,(int __category, char const *__locale),(__category,__locale))
/* Return the numeric/monetary information for the current locale */
__CDECLARE_OPT(__ATTR_RETNONNULL,struct lconv *,__NOTHROW_NCX,localeconv,(void),())
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifdef __CRT_HAVE_setlocale
__NAMESPACE_STD_USING(setlocale)
#endif /* __CRT_HAVE_setlocale */
#ifdef __CRT_HAVE_localeconv
__NAMESPACE_STD_USING(localeconv)
#endif /* __CRT_HAVE_localeconv */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
/* The concept of one static locale per category is not very well
 * thought out. Many applications will need to process its data using
 * information from several different locales. Another application is
 * the implementation of the internationalization handling in the
 * upcoming ISO C++ standard library. To support this another set of
 * the functions using locale data exist which have an additional
 * argument.
 *
 * Attention: all these functions are *not* standardized in any form.
 * This is a proof-of-concept implementation. */
#ifdef __CRT_HAVE_newlocale
/* Return a reference to a data structure representing a set of locale
 * datasets. Unlike for the CATEGORY parameter for `setlocale' the
 * CATEGORY_MASK parameter here uses a single bit for each category,
 * made by OR'ing together LC_*_MASK bits above */
__CDECLARE(,__locale_t,__NOTHROW_NCX,newlocale,(int __category_mask, char const *__locale, __locale_t __base),(__category_mask,__locale,__base))
#elif defined(__CRT_HAVE___newlocale)
/* Return a reference to a data structure representing a set of locale
 * datasets. Unlike for the CATEGORY parameter for `setlocale' the
 * CATEGORY_MASK parameter here uses a single bit for each category,
 * made by OR'ing together LC_*_MASK bits above */
__CREDIRECT(,__locale_t,__NOTHROW_NCX,newlocale,(int __category_mask, char const *__locale, __locale_t __base),__newlocale,(__category_mask,__locale,__base))
#endif /* ... */
#ifdef __CRT_HAVE_duplocale
/* Return a duplicate of the set of locale in DATASET.
 * All usage counters are increased if necessary */
__CDECLARE(,__locale_t,__NOTHROW_NCX,duplocale,(__locale_t __dataset),(__dataset))
#elif defined(__CRT_HAVE___duplocale)
/* Return a duplicate of the set of locale in DATASET.
 * All usage counters are increased if necessary */
__CREDIRECT(,__locale_t,__NOTHROW_NCX,duplocale,(__locale_t __dataset),__duplocale,(__dataset))
#endif /* ... */
#ifdef __CRT_HAVE_freelocale
/* Free the data associated with a locale dataset
 * previously returned by a call to `setlocale_r' */
__CDECLARE_VOID(,__NOTHROW_NCX,freelocale,(__locale_t __dataset),(__dataset))
#elif defined(__CRT_HAVE___freelocale)
/* Free the data associated with a locale dataset
 * previously returned by a call to `setlocale_r' */
__CREDIRECT_VOID(,__NOTHROW_NCX,freelocale,(__locale_t __dataset),__freelocale,(__dataset))
#endif /* ... */
#ifdef __CRT_HAVE_uselocale
/* Switch the current thread's locale to DATASET.
 * If DATASET is null, instead just return the current setting.
 * The special value LC_GLOBAL_LOCALE is the initial setting
 * for all threads and can also be installed any time, meaning
 * the thread uses the global settings controlled by `setlocale' */
__CDECLARE(,__locale_t,__NOTHROW_NCX,uselocale,(__locale_t __dataset),(__dataset))
#elif defined(__CRT_HAVE___uselocale)
/* Switch the current thread's locale to DATASET.
 * If DATASET is null, instead just return the current setting.
 * The special value LC_GLOBAL_LOCALE is the initial setting
 * for all threads and can also be installed any time, meaning
 * the thread uses the global settings controlled by `setlocale' */
__CREDIRECT(,__locale_t,__NOTHROW_NCX,uselocale,(__locale_t __dataset),__uselocale,(__dataset))
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CLOCALE 1
#undef _LOCALE_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CLOCALE */
#endif /* !_LOCALE_H */
