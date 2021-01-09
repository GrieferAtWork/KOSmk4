/* HASH CRC-32:0x699d4f9b */
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
#ifndef _PARTS_UCHAR_WCHAR_H
#define _PARTS_UCHAR_WCHAR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_btowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btoc16,(int __ch),btowc,(__ch))
#elif defined(__CRT_HAVE_DOS$btowc)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btoc16,(int __ch),btowc,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/btowc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBDCALL btoc16)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/btoc16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(btoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBDCALL btoc16)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btoc16))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_btowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btoc32,(int __ch),btowc,(__ch))
#elif defined(__CRT_HAVE_KOS$btowc)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btoc32,(int __ch),btowc,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/btowc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBKCALL btoc32)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/btoc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(btoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBKCALL btoc32)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btoc32))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_mbrlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrlen)
__CREDIRECT_DOS(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$__mbrlen)
__CREDIRECT_DOS(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/mbrlen.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16rlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbrlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrlen)
__CREDIRECT_KOS(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$__mbrlen)
__CREDIRECT_KOS(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/mbrlen.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32rlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbsrtowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsrtowcs)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/mbsrtowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL mbsrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsrtoc16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL mbsrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtoc16))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbsrtowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsrtowcs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/mbsrtowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL mbsrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsrtoc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL mbsrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtoc32))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrtombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16rtombs,(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$wcsrtombs)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16rtombs,(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrtombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16rtombs)(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16rtombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16rtombs)(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrtombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32rtombs,(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$wcsrtombs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32rtombs,(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrtombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32rtombs)(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32rtombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32rtombs)(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16stol)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16stol)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32stol)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32stol)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stol))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoul.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoul.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoul.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoul.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoul))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull))(__nptr, __endptr, __base); })
#endif /* !... */
#ifndef __NO_FPU
#if defined(__CRT_HAVE_wcstod) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstod)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstod,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstod.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBDCALL c16stod)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBDCALL c16stod)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stod))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstod)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstod,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstod.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBKCALL c32stod)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBKCALL c32stod)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stod))(__nptr, __endptr); })
#endif /* !... */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_wcstof) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstof)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstof.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBDCALL c16stof)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBDCALL c16stof)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stof))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstof) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstof)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstof.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBKCALL c32stof)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBKCALL c32stof)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stof))(__nptr, __endptr); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_wcstold) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstold)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstold,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstold.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stold.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stold))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstold) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstold)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstold,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstold.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stold.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stold))(__nptr, __endptr); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__USE_ISOC99 */
#endif /* !__NO_FPU */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stouq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stouq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stouq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stouq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstol_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16stol_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16stol_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstol_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32stol_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32stol_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoul_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoul_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifndef __NO_FPU
#if defined(__CRT_HAVE_wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstof_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstof_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstof_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstof_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBDCALL c16stof_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBDCALL c16stof_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstof_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstof_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstof_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstof_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBKCALL c32stof_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBKCALL c32stof_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstod_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstod_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstod_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBDCALL c16stod_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBDCALL c16stod_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstod_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstod_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstod_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBKCALL c32stod_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBKCALL c32stod_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstold_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstold_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstold_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstold_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstold_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstold_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstold_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstold_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN
#if defined(__CRT_HAVE_wcwidth) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16width,(char16_t __ch),wcwidth,(__ch))
#elif defined(__CRT_HAVE_DOS$wcwidth)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16width,(char16_t __ch),wcwidth,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcwidth.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16width)(char16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))((__WCHAR_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16width.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16width)(char16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16width))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcwidth) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32width,(char32_t __ch),wcwidth,(__ch))
#elif defined(__CRT_HAVE_KOS$wcwidth)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32width,(char32_t __ch),wcwidth,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcwidth.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32width)(char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))((__WCHAR_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32width.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32width)(char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32width))(__ch); })
#endif /* !... */
#endif /* __USE_XOPEN */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_wcsto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16sto32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32sto32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stou32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stou32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_wcsto64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16sto64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32sto64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stou64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stou64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou64))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto32_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16sto32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto32_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32sto32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou32_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stou32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou32_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stou32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto64_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoi64_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16sto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoi64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32sto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou64_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoui64_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stou64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stou64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */
#if defined(__CRT_HAVE_wtoi) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16toi)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16toi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16toi)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toi))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtoi) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32toi)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32toi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32toi)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toi))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16tol)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16tol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBDCALL c16tol)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tol))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32tol)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32tol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBKCALL c32tol)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tol))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16toll)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16toll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16toll)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toll))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32toll)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32toll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32toll)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toll))(__nptr); })
#endif /* !... */
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_WCHAR_H */
