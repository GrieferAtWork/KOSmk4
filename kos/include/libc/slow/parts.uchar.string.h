/* HASH CRC-32:0xab5e14f8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_SLOW_PARTS_UCHAR_STRING_H
#define _LIBC_SLOW_PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_slow_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif defined(__CRT_HAVE_DOS$wcsend)
/* Same as `STR+c16len(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_slow_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsend.h>
/* Same as `STR+c16len(STR)' */
#define __libc_slow_c16end(string) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c16end */
#include <local/wchar/c16end.h>
/* Same as `STR+c16len(STR)' */
#define __libc_slow_c16end (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))
#endif /* c16end... */
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `STR+c32len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_slow_c32end,(__CHAR32_TYPE__ const *__restrict __string),wcsend,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsend.h>
/* Same as `STR+c32len(STR)' */
#define __libc_slow_c32end(string) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c32end */
#include <local/wchar/c32end.h>
/* Same as `STR+c32len(STR)' */
#define __libc_slow_c32end (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))
#endif /* c32end... */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_slow_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__libc_slow_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
#define __libc_slow_c16nend(string, maxlen) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c16nend */
#include <local/wchar/c16nend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
#define __libc_slow_c16nend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))
#endif /* c16nend... */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_slow_c32nend,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
#define __libc_slow_c32nend(string, maxlen) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c32nend */
#include <local/wchar/c32nend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
#define __libc_slow_c32nend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))
#endif /* c32nend... */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_slow_c16len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c16len */
#include <local/wchar/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_slow_c16len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))
#endif /* c16len... */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c32len,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_slow_c32len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c32len */
#include <local/wchar/c32len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_slow_c32len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))
#endif /* c32len... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_slow_c16nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c16nlen */
#include <local/wchar/c16nlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_slow_c16nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))
#endif /* c16nlen... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_c32nlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_slow_c32nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c32nlen */
#include <local/wchar/c32nlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_slow_c32nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))
#endif /* c32nlen... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_slow_c16cmp(s1, s2) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2))
#else /* LIBC: c16cmp */
#include <local/wchar/c16cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_slow_c16cmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cmp))
#endif /* c16cmp... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c32cmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_slow_c32cmp(s1, s2) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2))
#else /* LIBC: c32cmp */
#include <local/wchar/c32cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_slow_c32cmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp))
#endif /* c32cmp... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_slow_c16ncmp(s1, s2, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2), maxlen)
#else /* LIBC: c16ncmp */
#include <local/wchar/c16ncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_slow_c16ncmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp))
#endif /* c16ncmp... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_c32ncmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncmp.h>
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_slow_c32ncmp(s1, s2, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2), maxlen)
#else /* LIBC: c32ncmp */
#include <local/wchar/c32ncmp.h>
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_slow_c32ncmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncmp))
#endif /* c32ncmp... */

__SYSDECL_END

#endif /* !_LIBC_SLOW_PARTS_UCHAR_STRING_H */
