/* HASH CRC-32:0x36268496 */
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
#ifndef _PARTS_UCHAR_STDLIB_H
#define _PARTS_UCHAR_STDLIB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_mbtowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_NCX,mbtoc16,(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$mbtowc)
__CREDIRECT_DOS(,int,__NOTHROW_NCX,mbtoc16,(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/stdlib/mbtowc.h>
__FORCELOCAL int __NOTHROW_NCX(__LIBDCALL mbtoc16)(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))((__WCHAR_TYPE__ *)__pwc, __str, __maxlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/mbtoc16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtoc16, __FORCELOCAL int __NOTHROW_NCX(__LIBDCALL mbtoc16)(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtoc16))(__pwc, __str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_mbtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_NCX,mbtoc32,(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$mbtowc)
__CREDIRECT_KOS(,int,__NOTHROW_NCX,mbtoc32,(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/stdlib/mbtowc.h>
__FORCELOCAL int __NOTHROW_NCX(__LIBKCALL mbtoc32)(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))((__WCHAR_TYPE__ *)__pwc, __str, __maxlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/mbtoc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtoc32, __FORCELOCAL int __NOTHROW_NCX(__LIBKCALL mbtoc32)(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtoc32))(__pwc, __str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wctomb) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_NCX,c16tomb,(char *__str, char16_t __wc),wctomb,(__str,__wc))
#elif defined(__CRT_HAVE_DOS$wctomb)
__CREDIRECT_DOS(,int,__NOTHROW_NCX,c16tomb,(char *__str, char16_t __wc),wctomb,(__str,__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/stdlib/wctomb.h>
__FORCELOCAL int __NOTHROW_NCX(__LIBDCALL c16tomb)(char *__str, char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, (__WCHAR_TYPE__)__wc); }
#else /* ... */
#include <local/parts.uchar.stdlib/c16tomb.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tomb, __FORCELOCAL int __NOTHROW_NCX(__LIBDCALL c16tomb)(char *__str, char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tomb))(__str, __wc); })
#endif /* !... */
#if defined(__CRT_HAVE_wctomb) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_NCX,c32tomb,(char *__str, char32_t __wc),wctomb,(__str,__wc))
#elif defined(__CRT_HAVE_KOS$wctomb)
__CREDIRECT_KOS(,int,__NOTHROW_NCX,c32tomb,(char *__str, char32_t __wc),wctomb,(__str,__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/stdlib/wctomb.h>
__FORCELOCAL int __NOTHROW_NCX(__LIBKCALL c32tomb)(char *__str, char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, (__WCHAR_TYPE__)__wc); }
#else /* ... */
#include <local/parts.uchar.stdlib/c32tomb.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tomb, __FORCELOCAL int __NOTHROW_NCX(__LIBKCALL c32tomb)(char *__str, char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tomb))(__str, __wc); })
#endif /* !... */
#if defined(__CRT_HAVE_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstoc16s,(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$mbstowcs)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstoc16s,(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/stdlib/mbstowcs.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL mbstoc16s)(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))((__WCHAR_TYPE__ *)__dst, __src, __dstlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/mbstoc16s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstoc16s, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL mbstoc16s)(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstoc16s))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstoc32s,(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_KOS$mbstowcs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstoc32s,(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/stdlib/mbstowcs.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL mbstoc32s)(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))((__WCHAR_TYPE__ *)__dst, __src, __dstlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/mbstoc32s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstoc32s, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL mbstoc32s)(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstoc32s))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16stombs,(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$wcstombs)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16stombs,(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/stdlib/wcstombs.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16stombs)(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, (__WCHAR_TYPE__ const *)__src, __dstlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/c16stombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stombs, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16stombs)(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stombs))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32stombs,(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_KOS$wcstombs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32stombs,(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/stdlib/wcstombs.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32stombs)(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, (__WCHAR_TYPE__ const *)__src, __dstlen); }
#else /* ... */
#include <local/parts.uchar.stdlib/c32stombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stombs, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32stombs)(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stombs))(__dst, __src, __dstlen); })
#endif /* !... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_STDLIB_H */
