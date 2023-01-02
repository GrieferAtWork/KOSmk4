/* HASH CRC-32:0xd98f2a33 */
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
#ifndef _LIBC_CORE_PARTS_UCHAR_STRING_H
#define _LIBC_CORE_PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16end,(__CHAR16_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_DOS$wcsend)
#include <hybrid/typecore.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16end,(__CHAR16_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsend.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_core_c16end (*(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#else /* ... */
#include <libc/local/parts.uchar.string/c16end.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_core_c16end __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end)
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_KOS$wcsend)
#include <hybrid/typecore.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsend.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_core_c32end (*(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#else /* ... */
#include <libc/local/parts.uchar.string/c32end.h>
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_core_c32end __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16nend,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
#include <hybrid/typecore.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_core_c16nend,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnend.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_core_c16nend (*(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
#include <libc/local/parts.uchar.string/c16nend.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_core_c16nend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32nend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnend)
#include <hybrid/typecore.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_core_c32nend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnend.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_core_c32nend (*(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
#include <libc/local/parts.uchar.string/c32nend.h>
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_core_c32nend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend)
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcslen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
#include <hybrid/typecore.h>
/* >> wcslen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslen.h>
/* >> wcslen(3) */
#define __libc_core_c16len (*(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#else /* ... */
#include <libc/local/parts.uchar.string/c16len.h>
/* >> wcslen(3) */
#define __libc_core_c16len __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len)
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcslen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_KOS$wcslen)
#include <hybrid/typecore.h>
/* >> wcslen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslen.h>
/* >> wcslen(3) */
#define __libc_core_c32len (*(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#else /* ... */
#include <libc/local/parts.uchar.string/c32len.h>
/* >> wcslen(3) */
#define __libc_core_c32len __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16nlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16nlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16nlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$__wcsncnt)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c16nlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
#define __libc_core_c16nlen (*(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
#include <libc/local/parts.uchar.string/c16nlen.h>
/* >> wcsnlen(3) */
#define __libc_core_c16nlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen)
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$__wcsncnt)
#include <hybrid/typecore.h>
/* >> wcsnlen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
#define __libc_core_c32nlen (*(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
#include <libc/local/parts.uchar.string/c32nlen.h>
/* >> wcsnlen(3) */
#define __libc_core_c32nlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen)
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* >> wcscmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscmp.h>
/* >> wcscmp(3) */
#define __libc_core_c16cmp (*(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c16cmp.h>
/* >> wcscmp(3) */
#define __libc_core_c16cmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_c32cmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscmp)
/* >> wcscmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_c32cmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscmp.h>
/* >> wcscmp(3) */
#define __libc_core_c32cmp (*(int(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c32cmp.h>
/* >> wcscmp(3) */
#define __libc_core_c32cmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* >> wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
#include <hybrid/typecore.h>
/* >> wcsncmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncmp.h>
/* >> wcsncmp(3) */
#define __libc_core_c16ncmp (*(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncmp.h>
/* >> wcsncmp(3) */
#define __libc_core_c16ncmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp)
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* >> wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32ncmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncmp)
#include <hybrid/typecore.h>
/* >> wcsncmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_c32ncmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncmp.h>
/* >> wcsncmp(3) */
#define __libc_core_c32ncmp (*(int(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *,__SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncmp.h>
/* >> wcsncmp(3) */
#define __libc_core_c32ncmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncmp)
#endif /* !... */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_PARTS_UCHAR_STRING_H */
