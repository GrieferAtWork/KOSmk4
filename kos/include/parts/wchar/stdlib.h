/* HASH CRC-32:0x794dcc86 */
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
#ifndef _PARTS_WCHAR_STDLIB_H
#define _PARTS_WCHAR_STDLIB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_KOS
#ifdef __CRT_HAVE_wtoi
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtoi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wtoi)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE_wtol
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtol)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wtol)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))(__nptr); })
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_wtoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wtoll)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))(__nptr); })
#endif /* !... */
#endif /* __LONGLONG */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_WCHAR_STDLIB_H */
