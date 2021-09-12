/* HASH CRC-32:0xfd5ec919 */
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
#ifndef _LIBC_CORE_PARTS_UCHAR_STRING_H
#define _LIBC_CORE_PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `str+wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16send,(__CHAR16_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_DOS$wcsend)
#include <hybrid/typecore.h>
/* Same as `str+wcslen(str)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16send,(__CHAR16_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsend.h>
/* Same as `str+wcslen(str)' */
#define __libc_core_c16send (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#else /* ... */
#include <libc/local/parts.uchar.string/c16send.h>
/* Same as `str+wcslen(str)' */
#define __libc_core_c16send __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16send)
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `str+wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32send,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_KOS$wcsend)
#include <hybrid/typecore.h>
/* Same as `str+wcslen(str)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32send,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsend.h>
/* Same as `str+wcslen(str)' */
#define __libc_core_c32send (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#else /* ... */
#include <libc/local/parts.uchar.string/c32send.h>
/* Same as `str+wcslen(str)' */
#define __libc_core_c32send __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32send)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16snend,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
#include <hybrid/typecore.h>
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16snend,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnend.h>
/* Same as `str+wcsnlen(str, max_chars)' */
#define __libc_core_c16snend (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
#include <libc/local/parts.uchar.string/c16snend.h>
/* Same as `str+wcsnlen(str, max_chars)' */
#define __libc_core_c16snend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snend)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32snend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnend)
#include <hybrid/typecore.h>
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32snend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnend.h>
/* Same as `str+wcsnlen(str, max_chars)' */
#define __libc_core_c32snend (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
#include <libc/local/parts.uchar.string/c32snend.h>
/* Same as `str+wcsnlen(str, max_chars)' */
#define __libc_core_c32snend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snend)
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16slen,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
#include <hybrid/typecore.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16slen,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_core_c16slen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#else /* ... */
#include <libc/local/parts.uchar.string/c16slen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_core_c16slen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16slen)
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32slen,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_KOS$wcslen)
#include <hybrid/typecore.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32slen,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_core_c32slen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#else /* ... */
#include <libc/local/parts.uchar.string/c32slen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_core_c32slen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32slen)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16snlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16snlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_core_c16snlen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
#include <libc/local/parts.uchar.string/c16snlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_core_c16snlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snlen)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32snlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32snlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_core_c32snlen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
#include <libc/local/parts.uchar.string/c32snlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_core_c32snlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snlen)
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16scmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16scmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_core_c16scmp (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c16scmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_core_c16scmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32scmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32scmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_core_c32scmp (*(int(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c32scmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_core_c32scmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16sncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
#include <hybrid/typecore.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16sncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __libc_core_c16sncmp (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __libc_core_c16sncmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32sncmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncmp)
#include <hybrid/typecore.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32sncmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __libc_core_c32sncmp (*(int(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __libc_core_c32sncmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncmp)
#endif /* !... */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_PARTS_UCHAR_STRING_H */
