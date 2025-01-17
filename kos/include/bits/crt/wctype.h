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
#ifndef _BITS_CRT_WCTYPE_H
#define _BITS_CRT_WCTYPE_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

#ifdef __CRT_DOS_PRIMARY
#define __SIZEOF_WCTYPE_T__  2
#define __SIZEOF_WCTRANS_T__ 2
#else /* __CRT_DOS_PRIMARY */
#define __SIZEOF_WCTYPE_T__  __SIZEOF_POINTER__
#define __SIZEOF_WCTRANS_T__ __SIZEOF_POINTER__
#endif /* !__CRT_DOS_PRIMARY */

#ifdef __CC__
__DECL_BEGIN
#ifdef __CRT_DOS_PRIMARY
typedef __UINT16_TYPE__ __wctype_t;
typedef __WCHAR16_TYPE__ __wctrans_t;
#else /* __CRT_DOS_PRIMARY */
typedef __ULONGPTR_TYPE__ __wctype_t;
typedef __INT32_TYPE__ const *__wctrans_t;
#endif /* !__CRT_DOS_PRIMARY */
__DECL_END


#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)

/************************************************************************/
/* KOS                                                                  */
#include <bits/crt/unicode.h>
#include <libc/core/unicode.h>

/* Implement <wctype.h> functions in terms of `__unicode_descriptor' */
#ifdef ____libc_core___unicode_descriptor_defined
#define __crt_iswcntrl(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISCNTRL) != 0)
#define __crt_iswspace(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSPACE) != 0)
#define __crt_iswlower(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLOWER) != 0)
#define __crt_iswupper(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISUPPER) != 0)
#define __crt_iswalpha(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALPHA) != 0)
#define __crt_iswdigit(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISDIGIT) != 0)
#define __crt_iswxdigit(ch) ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISXDIGIT) != 0)
#define __crt_iswalnum(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALNUM) != 0)
#define __crt_iswpunct(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPUNCT) != 0)
#define __crt_iswgraph(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISGRAPH) != 0)
#define __crt_iswprint(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPRINT) != 0)
#define __crt_iswblank(ch)  ((__libc_core___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISBLANK) != 0)
#ifdef __NO_XBLOCK
#define __crt_towlower(ch) ((__WINT_TYPE__)(ch) + __libc_core___unicode_descriptor(ch)->__ut_lower)
#define __crt_towupper(ch) ((__WINT_TYPE__)(ch) + __libc_core___unicode_descriptor(ch)->__ut_upper)
#else /* __NO_XBLOCK */
#define __crt_towlower(ch) __XBLOCK({ __WINT_TYPE__ __ctl_ch = (ch); __XRETURN __ctl_ch + __libc_core___unicode_descriptor(__ctl_ch)->__ut_lower; })
#define __crt_towupper(ch) __XBLOCK({ __WINT_TYPE__ __ctu_ch = (ch); __XRETURN __ctu_ch + __libc_core___unicode_descriptor(__ctu_ch)->__ut_upper; })
#endif /* !__NO_XBLOCK */
#endif /* ____libc_core___unicode_descriptor_defined */
/************************************************************************/

#else /* ... */

/* Generic CRT or CRT doesn't provide wctype lookup matrix */

#endif /* !... */

#endif /* __CC__ */

#endif /* !_BITS_CRT_WCTYPE_H */
