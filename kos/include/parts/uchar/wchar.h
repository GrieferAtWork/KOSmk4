/* HASH CRC-32:0x1ed40e6c */
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

#ifndef WEOF16
#define WEOF16 __WEOF16
#define WEOF32 __WEOF32
#endif /* !WEOF16 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

#if defined(__CRT_HAVE_btowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,btoc16,(int __ch),btowc,(__ch))
#elif defined(__CRT_HAVE_DOS$btowc)
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,btoc16,(int __ch),btowc,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/btowc.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW_NCX(__LIBDCALL btoc16)(int __ch) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/btoc16.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(btoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW_NCX(__LIBDCALL btoc16)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btoc16))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_btowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,btoc32,(int __ch),btowc,(__ch))
#elif defined(__CRT_HAVE_KOS$btowc)
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,btoc32,(int __ch),btowc,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/btowc.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW_NCX(__LIBKCALL btoc32)(int __ch) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/btoc32.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(btoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW_NCX(__LIBKCALL btoc32)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btoc32))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wctob) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16tob,(wint16_t __ch),wctob,(__ch))
#elif defined(__CRT_HAVE_DOS$wctob)
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16tob,(wint16_t __ch),wctob,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wctob.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16tob)(wint16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctob))((__WINT_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16tob.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16tob)(wint16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tob))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wctob) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32tob,(wint32_t __ch),wctob,(__ch))
#elif defined(__CRT_HAVE_KOS$wctob)
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32tob,(wint32_t __ch),wctob,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wctob.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32tob)(wint32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctob))((__WINT_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32tob.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32tob)(wint32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tob))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_mbrlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrlen)
/* >> mbrlen(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$__mbrlen)
/* >> mbrlen(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/mbrlen.h>
/* >> mbrlen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16rlen.h>
/* >> mbrlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbrlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrlen)
/* >> mbrlen(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$__mbrlen)
/* >> mbrlen(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32rlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/mbrlen.h>
/* >> mbrlen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32rlen.h>
/* >> mbrlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32rlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbsrtowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> mbsrtowcs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbsrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsrtowcs)
/* >> mbsrtowcs(3) */
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbsrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/mbsrtowcs.h>
/* >> mbsrtowcs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBDCALL mbsrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsrtoc16.h>
/* >> mbsrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBDCALL mbsrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtoc16))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbsrtowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> mbsrtowcs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbsrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsrtowcs)
/* >> mbsrtowcs(3) */
__CREDIRECT_KOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbsrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/mbsrtowcs.h>
/* >> mbsrtowcs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBKCALL mbsrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsrtoc32.h>
/* >> mbsrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBKCALL mbsrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtoc32))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrtombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsrtombs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,c16rtombs,(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$wcsrtombs)
/* >> wcsrtombs(3) */
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,c16rtombs,(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrtombs.h>
/* >> wcsrtombs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBDCALL c16rtombs)(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16rtombs.h>
/* >> wcsrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBDCALL c16rtombs)(char *__dst, char16_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrtombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsrtombs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,c32rtombs,(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$wcsrtombs)
/* >> wcsrtombs(3) */
__CREDIRECT_KOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,c32rtombs,(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrtombs.h>
/* >> wcsrtombs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBKCALL c32rtombs)(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32rtombs.h>
/* >> wcsrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBKCALL c32rtombs)(char *__dst, char32_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol)
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG__ == 4
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstol(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstol.h>
/* >> wcstol(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBDCALL c16stol)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stol.h>
/* >> wcstol(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBDCALL c16stol)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol)
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG__ == 4
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstol(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstol.h>
/* >> wcstol(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBKCALL c32stol)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stol.h>
/* >> wcstol(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBKCALL c32stol)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul)
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG__ == 4
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoul(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoul.h>
/* >> wcstoul(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoul.h>
/* >> wcstoul(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul)
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG__ == 4
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoul(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoul.h>
/* >> wcstoul(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoul.h>
/* >> wcstoul(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll)
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq)
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll.h>
/* >> wcstoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll)
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq)
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll.h>
/* >> wcstoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull)
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq)
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull.h>
/* >> wcstoull(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull)
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq)
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull.h>
/* >> wcstoull(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull))(__nptr, __endptr, __base); })
#endif /* !... */
#ifndef __NO_FPU
#if defined(__CRT_HAVE_wcstod) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstod(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstod)
/* >> wcstod(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstod,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstod.h>
/* >> wcstod(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBDCALL c16stod)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stod.h>
/* >> wcstod(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBDCALL c16stod)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stod))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstod(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstod)
/* >> wcstod(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstod,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstod.h>
/* >> wcstod(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBKCALL c32stod)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stod.h>
/* >> wcstod(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBKCALL c32stod)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stod))(__nptr, __endptr); })
#endif /* !... */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_wcstof) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstof(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstof)
/* >> wcstof(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstof.h>
/* >> wcstof(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBDCALL c16stof)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stof.h>
/* >> wcstof(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBDCALL c16stof)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stof))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstof) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstof(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstof)
/* >> wcstof(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstof.h>
/* >> wcstof(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBKCALL c32stof)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stof.h>
/* >> wcstof(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBKCALL c32stof)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stof))(__nptr, __endptr); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_wcstold) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstold(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstold)
/* >> wcstold(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold,(char16_t const *__restrict __nptr, char16_t **__endptr),wcstold,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstold.h>
/* >> wcstold(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stold.h>
/* >> wcstold(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold)(char16_t const *__restrict __nptr, char16_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stold))(__nptr, __endptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstold) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstold(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstold)
/* >> wcstold(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold,(char32_t const *__restrict __nptr, char32_t **__endptr),wcstold,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstold.h>
/* >> wcstold(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stold.h>
/* >> wcstold(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold)(char32_t const *__restrict __nptr, char32_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stold))(__nptr, __endptr); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__USE_ISOC99 */
#endif /* !__NO_FPU */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll)
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq)
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll)
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq)
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull)
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq)
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stouq,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stouq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stouq)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull)
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq)
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stouq,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stouq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stouq)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c16stol_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstol_l.h>
/* >> wcstol_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBDCALL c16stol_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stol_l.h>
/* >> wcstol_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBDCALL c16stol_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,c32stol_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstol_l.h>
/* >> wcstol_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBKCALL c32stol_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stol_l.h>
/* >> wcstol_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBKCALL c32stol_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c16stoul_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoul_l.h>
/* >> wcstoul_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoul_l.h>
/* >> wcstoul_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,c32stoul_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoul_l.h>
/* >> wcstoul_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoul_l.h>
/* >> wcstoul_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c16stoll_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll_l.h>
/* >> wcstoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoll_l.h>
/* >> wcstoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,c32stoll_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll_l.h>
/* >> wcstoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoll_l.h>
/* >> wcstoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c16stoull_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull_l.h>
/* >> wcstoull_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stoull_l.h>
/* >> wcstoull_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,c32stoull_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull_l.h>
/* >> wcstoull_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stoull_l.h>
/* >> wcstoull_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifndef __NO_FPU
#if defined(__CRT_HAVE_wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c16stof_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstof_l.h>
/* >> wcstof_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBDCALL c16stof_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stof_l.h>
/* >> wcstof_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBDCALL c16stof_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,c32stof_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstof_l.h>
/* >> wcstof_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBKCALL c32stof_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stof_l.h>
/* >> wcstof_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBKCALL c32stof_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c16stod_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstod_l.h>
/* >> wcstod_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBDCALL c16stod_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stod_l.h>
/* >> wcstod_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBDCALL c16stod_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,c32stod_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstod_l.h>
/* >> wcstod_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBKCALL c32stod_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stod_l.h>
/* >> wcstod_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBKCALL c32stod_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c16stold_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstold_l.h>
/* >> wcstold_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16stold_l.h>
/* >> wcstold_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBDCALL c16stold_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT_KOS(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,c32stold_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstold_l.h>
/* >> wcstold_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32stold_l.h>
/* >> wcstold_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBKCALL c32stold_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN
#if defined(__CRT_HAVE_wcwidth) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16width,(char16_t __ch),wcwidth,(__ch))
#elif defined(__CRT_HAVE_DOS$wcwidth)
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c16width,(char16_t __ch),wcwidth,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcwidth.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16width)(char16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))((__WCHAR_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16width.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL c16width)(char16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16width))(__ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcwidth) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32width,(char32_t __ch),wcwidth,(__ch))
#elif defined(__CRT_HAVE_KOS$wcwidth)
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,c32width,(char32_t __ch),wcwidth,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcwidth.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32width)(char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))((__WCHAR_TYPE__)__ch); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32width.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL c32width)(char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32width))(__ch); })
#endif /* !... */
#endif /* __USE_XOPEN */

#ifdef __USE_BSD
#if defined(__CRT_HAVE_fgetwln) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetwln(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_NCX,fgetc16ln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),fgetwln,(__fp,__lenp))
#elif defined(__CRT_HAVE_DOS$fgetwln)
/* >> fgetwln(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_NCX,fgetc16ln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),fgetwln,(__fp,__lenp))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwln) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetwln(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_NCX,fgetc32ln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),fgetwln,(__fp,__lenp))
#elif defined(__CRT_HAVE_KOS$fgetwln)
/* >> fgetwln(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_NCX,fgetc32ln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),fgetwln,(__fp,__lenp))
#endif /* ... */
#if defined(__CRT_HAVE_wcslcat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslcat(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16lcat,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcat,(__dst,__src,__bufsize))
#elif defined(__CRT_HAVE_DOS$wcslcat)
/* >> wcslcat(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16lcat,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcat,(__dst,__src,__bufsize))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslcat.h>
/* >> wcslcat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16lcat)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcat))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __bufsize); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16lcat.h>
/* >> wcslcat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16lcat)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lcat))(__dst, __src, __bufsize); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslcat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslcat(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32lcat,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcat,(__dst,__src,__bufsize))
#elif defined(__CRT_HAVE_KOS$wcslcat)
/* >> wcslcat(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32lcat,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcat,(__dst,__src,__bufsize))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslcat.h>
/* >> wcslcat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32lcat)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcat))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __bufsize); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32lcat.h>
/* >> wcslcat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32lcat)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lcat))(__dst, __src, __bufsize); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslcpy(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16lcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcpy,(__dst,__src,__bufsize))
#elif defined(__CRT_HAVE_DOS$wcslcpy)
/* >> wcslcpy(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16lcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcpy,(__dst,__src,__bufsize))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslcpy.h>
/* >> wcslcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16lcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __bufsize); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16lcpy.h>
/* >> wcslcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16lcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lcpy))(__dst, __src, __bufsize); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslcpy(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32lcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcpy,(__dst,__src,__bufsize))
#elif defined(__CRT_HAVE_KOS$wcslcpy)
/* >> wcslcpy(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32lcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize),wcslcpy,(__dst,__src,__bufsize))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslcpy.h>
/* >> wcslcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32lcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __bufsize); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32lcpy.h>
/* >> wcslcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32lcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lcpy))(__dst, __src, __bufsize); })
#endif /* !... */
#endif /* __USE_BSD */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_mbsnrtowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> mbsnrtowcs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsnrtowcs)
/* >> mbsnrtowcs(3) */
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtoc16,(char16_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/mbsnrtowcs.h>
/* >> mbsnrtowcs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL mbsnrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsnrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __nmc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsnrtoc16.h>
/* >> mbsnrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsnrtoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL mbsnrtoc16)(char16_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsnrtoc16))(__dst, __psrc, __nmc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_mbsnrtowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> mbsnrtowcs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsnrtowcs)
/* >> mbsnrtowcs(3) */
__CREDIRECT_KOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtoc32,(char32_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/mbsnrtowcs.h>
/* >> mbsnrtowcs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL mbsnrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsnrtowcs))((__WCHAR_TYPE__ *)__dst, __psrc, __nmc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/mbsnrtoc32.h>
/* >> mbsnrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsnrtoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL mbsnrtoc32)(char32_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsnrtoc32))(__dst, __psrc, __nmc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrtombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnrtombs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16nrtombs,(char *__dst, char16_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$wcsnrtombs)
/* >> wcsnrtombs(3) */
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c16nrtombs,(char *__dst, char16_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrtombs.h>
/* >> wcsnrtombs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nrtombs)(char *__dst, char16_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __nwc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c16nrtombs.h>
/* >> wcsnrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nrtombs)(char *__dst, char16_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrtombs))(__dst, __psrc, __nwc, __dstlen, __mbs); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrtombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnrtombs(3) */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32nrtombs,(char *__dst, char32_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$wcsnrtombs)
/* >> wcsnrtombs(3) */
__CREDIRECT_KOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,c32nrtombs,(char *__dst, char32_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrtombs.h>
/* >> wcsnrtombs(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nrtombs)(char *__dst, char32_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrtombs))(__dst, (__WCHAR_TYPE__ const **)__psrc, __nwc, __dstlen, __mbs); }
#else /* ... */
#include <libc/local/parts.uchar.wchar/c32nrtombs.h>
/* >> wcsnrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nrtombs)(char *__dst, char32_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrtombs))(__dst, __psrc, __nwc, __dstlen, __mbs); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_WCHAR_H */
