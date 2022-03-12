/* HASH CRC-32:0x630d3123 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wstring.h) */
#ifndef _CORECRT_WSTRING_H
#define _CORECRT_WSTRING_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED 1
/* Standard functions (already defined in <wchar.h>) */
#ifndef __wcscat_defined
#define __wcscat_defined
#ifdef __std_wcscat_defined
/* >> wcscat(3) */
__NAMESPACE_STD_USING(wcscat)
#elif defined(__CRT_HAVE_wcscat)
/* >> wcscat(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
#include <libc/local/wchar/wcscat.h>
/* >> wcscat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* !... */
#endif /* !__wcscat_defined */
#ifndef __wcschr_defined
#define __wcschr_defined
#ifdef __std_wcschr_defined
/* >> wcschr(3) */
__NAMESPACE_STD_USING(wcschr)
#elif defined(__CRT_HAVE_wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcschr_defined */
#ifndef __wcscmp_defined
#define __wcscmp_defined
#ifdef __std_wcscmp_defined
/* >> wcscmp(3) */
__NAMESPACE_STD_USING(wcscmp)
#elif defined(__CRT_HAVE_wcscmp)
/* >> wcscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscmp.h>
/* >> wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__wcscmp_defined */
#ifndef __wcscpy_defined
#define __wcscpy_defined
#ifdef __std_wcscpy_defined
/* >> wcscpy(3) */
__NAMESPACE_STD_USING(wcscpy)
#elif defined(__CRT_HAVE_wcscpy)
/* >> wcscpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
#include <libc/local/wchar/wcscpy.h>
/* >> wcscpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* !... */
#endif /* !__wcscpy_defined */
#ifndef __wcscspn_defined
#define __wcscspn_defined
#ifdef __std_wcscspn_defined
/* >> wcscspn(3) */
__NAMESPACE_STD_USING(wcscspn)
#elif defined(__CRT_HAVE_wcscspn)
/* >> wcscspn(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* ... */
#include <libc/local/wchar/wcscspn.h>
/* >> wcscspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* !... */
#endif /* !__wcscspn_defined */
#ifndef __wcslen_defined
#define __wcslen_defined
#ifdef __std_wcslen_defined
/* >> wcslen(3) */
__NAMESPACE_STD_USING(wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* >> wcslen(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcslen.h>
/* >> wcslen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__str); })
#endif /* !... */
#endif /* !__wcslen_defined */
#ifndef __wcsnlen_defined
#define __wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
/* >> wcsnlen(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__str, __maxlen); })
#endif /* !... */
#endif /* !__wcsnlen_defined */
#ifndef __wcsncat_defined
#define __wcsncat_defined
#ifdef __std_wcsncat_defined
/* >> wcsncat(3) */
__NAMESPACE_STD_USING(wcsncat)
#elif defined(__CRT_HAVE_wcsncat)
/* >> wcsncat(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <libc/local/wchar/wcsncat.h>
/* >> wcsncat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__wcsncat_defined */
#ifndef __wcsncmp_defined
#define __wcsncmp_defined
#ifdef __std_wcsncmp_defined
/* >> wcsncmp(3) */
__NAMESPACE_STD_USING(wcsncmp)
#elif defined(__CRT_HAVE_wcsncmp)
/* >> wcsncmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncmp.h>
/* >> wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__wcsncmp_defined */
#ifndef __wcsncpy_defined
#define __wcsncpy_defined
#ifdef __std_wcsncpy_defined
/* >> wcsncpy(3) */
__NAMESPACE_STD_USING(wcsncpy)
#elif defined(__CRT_HAVE_wcsncpy)
/* >> wcsncpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <libc/local/wchar/wcsncpy.h>
/* >> wcsncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__wcsncpy_defined */
#ifndef __wcspbrk_defined
#define __wcspbrk_defined
#ifdef __std_wcspbrk_defined
/* >> wcspbrk(3) */
__NAMESPACE_STD_USING(wcspbrk)
#elif defined(__CRT_HAVE_wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcspbrk_defined */
#ifndef __wcsrchr_defined
#define __wcsrchr_defined
#ifdef __std_wcsrchr_defined
/* >> wcsrchr(3) */
__NAMESPACE_STD_USING(wcsrchr)
#elif defined(__CRT_HAVE_wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcsrchr_defined */
#ifndef __wcsspn_defined
#define __wcsspn_defined
#ifdef __std_wcsspn_defined
/* >> wcsspn(3) */
__NAMESPACE_STD_USING(wcsspn)
#elif defined(__CRT_HAVE_wcsspn)
/* >> wcsspn(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* ... */
#include <libc/local/wchar/wcsspn.h>
/* >> wcsspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* !... */
#endif /* !__wcsspn_defined */
#ifndef __wcsstr_defined
#define __wcsstr_defined
#ifdef __std_wcsstr_defined
/* >> wcsstr(3) */
__NAMESPACE_STD_USING(wcsstr)
#elif defined(__CRT_HAVE_wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcsstr_defined */
#ifndef __wcstok_defined
#define __wcstok_defined
#ifdef __std_wcstok_defined
/* >> wcstok(3) */
__NAMESPACE_STD_USING(wcstok)
#elif defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/wchar/wcstok.h>
/* >> wcstok(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__wcstok_defined */
#ifndef __wcsxfrm_defined
#define __wcsxfrm_defined
#ifdef __std_wcsxfrm_defined
/* >> wcsxfrm(3) */
__NAMESPACE_STD_USING(wcsxfrm)
#elif defined(__CRT_HAVE_wcsxfrm)
/* >> wcsxfrm(3) */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsxfrm.h>
/* >> wcsxfrm(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#endif /* !__wcsxfrm_defined */
#ifndef __wcscoll_defined
#define __wcscoll_defined
#ifdef __std_wcscoll_defined
/* >> wcscoll(3) */
__NAMESPACE_STD_USING(wcscoll)
#elif defined(__CRT_HAVE_wcscoll)
/* >> wcscoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscoll.h>
/* >> wcscoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* !... */
#endif /* !__wcscoll_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined
#ifdef __CRT_HAVE_wcsdup
/* >> wcsdup(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__wcsdup)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsdup.h>
/* >> wcsdup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* ... */
#undef __wcsdup_defined
#endif /* !... */
#endif /* !__wcsdup_defined */
#ifndef __wcsnset_defined
#define __wcsnset_defined
#ifdef __CRT_HAVE_wcsnset
/* >> wcsnset(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnset.h>
/* >> wcsnset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* !... */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined
#ifdef __CRT_HAVE_wcsrev
/* >> wcsrev(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsrev)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),_wcsrev,(__str))
#else /* ... */
#include <libc/local/wchar/wcsrev.h>
/* >> wcsrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* !... */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined
#ifdef __CRT_HAVE_wcsset
/* >> wcsset(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#else /* ... */
#include <libc/local/wchar/wcsset.h>
/* >> wcsset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* !... */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined
#ifdef __CRT_HAVE_wcslwr
/* >> wcslwr(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcslwr)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),_wcslwr,(__str))
#else /* ... */
#include <libc/local/wchar/wcslwr.h>
/* >> wcslwr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* !... */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined
#ifdef __CRT_HAVE_wcsupr
/* >> wcsupr(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsupr)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),_wcsupr,(__str))
#else /* ... */
#include <libc/local/wchar/wcsupr.h>
/* >> wcsupr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* !... */
#endif /* !__wcsupr_defined */



/* DOS-specific aliases for differently named functions */
#ifndef __wcswcs_defined
#define __wcswcs_defined
#ifdef __CRT_HAVE_wcsstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcswcs_defined */
#ifdef __CRT_HAVE_wcscasecmp
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
/* >> wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
/* >> wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
/* >> wcscasecoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
/* >> wcscasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsdup
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup)
/* >> wcsdup(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsdup.h>
/* >> wcsdup(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); }
#endif /* ... */
#ifdef __CRT_HAVE_wcscasecmp
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
/* >> wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
/* >> wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecmp_l
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
/* >> wcscasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecmp_l.h>
/* >> wcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp_l
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
/* >> wcsncasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsnset
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
/* >> wcsnset(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnset.h>
/* >> wcsnset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsrev
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev)
/* >> wcsrev(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcsrev.h>
/* >> wcsrev(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsset
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
/* >> wcsset(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#else /* ... */
#include <libc/local/wchar/wcsset.h>
/* >> wcsset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); }
#endif /* !... */
#ifdef __CRT_HAVE_wcslwr
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr)
/* >> wcslwr(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcslwr.h>
/* >> wcslwr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsupr
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr)
/* >> wcsupr(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcsupr.h>
/* >> wcsupr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); }
#endif /* !... */
#ifdef __CRT_HAVE_wcslwr_l
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
/* >> wcslwr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcslwr_l.h>
/* >> wcslwr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsupr_l
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
/* >> wcsupr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcsupr_l.h>
/* >> wcsupr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsxfrm_l
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsxfrm_l.h>
/* >> wcsxfrm_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcscoll_l
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
/* >> wcscoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscoll_l.h>
/* >> wcscoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
/* >> wcscasecoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
/* >> wcscasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll_l
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
/* >> wcscasecoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecoll_l.h>
/* >> wcscasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
/* >> wcsncasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncoll_l
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
/* >> wcsncoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncoll_l.h>
/* >> wcsncoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
/* >> wcsncasecoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
/* >> wcsncasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll_l
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
/* >> wcsncasecoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */



/* DOS-specific functions */
__CDECLARE_OPT(,wchar_t *,__NOTHROW_NCX,_wcserror,(__errno_t __errno_value),(__errno_value))
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,_wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __errno_t __errno_value),(__buf,__bufsize,__errno_value))
__CDECLARE_OPT(,wchar_t *,__NOTHROW_NCX,__wcserror,(wchar_t const *__message),(__message))
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,__wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__message),(__buf,__bufsize,__message))
#ifdef __CRT_HAVE__wcsnset_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsnset_s,(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* __CRT_HAVE__wcsnset_s */
#include <libc/local/corecrt_wstring/_wcsnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsnset_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsnset_s)(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* !__CRT_HAVE__wcsnset_s */
#ifdef __CRT_HAVE__wcsset_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wcsset_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch),(__dst,__dstsize,__ch))
#else /* __CRT_HAVE__wcsset_s */
#include <libc/local/corecrt_wstring/_wcsset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsset_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _wcsset_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsset_s))(__dst, __dstsize, __ch); })
#endif /* !__CRT_HAVE__wcsset_s */
#ifdef __CRT_HAVE__wcslwr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcslwr_s */
#include <libc/local/corecrt_wstring/_wcslwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcslwr_s */
#ifdef __CRT_HAVE__wcsupr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcsupr_s */
#include <libc/local/corecrt_wstring/_wcsupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcsupr_s */
#ifdef __CRT_HAVE__wcslwr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcslwr_s_l */
#include <libc/local/corecrt_wstring/_wcslwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcslwr_s_l */
#ifdef __CRT_HAVE__wcsupr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcsupr_s_l */
#include <libc/local/corecrt_wstring/_wcsupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcsupr_s_l */
#ifdef __CRT_HAVE_wmemcpy_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemcpy_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_wmemcpy_s */
#include <libc/local/corecrt_wstring/wmemcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemcpy_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_wmemcpy_s */
#ifdef __CRT_HAVE_wmemmove_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemmove_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_wmemmove_s */
#include <libc/local/corecrt_wstring/wmemmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemmove_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_wmemmove_s */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_wcscat_s
/* >> wcscat_s(3) */
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscat_s */
#include <libc/local/corecrt_wstring/wcscat_s.h>
/* >> wcscat_s(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscat_s */
#ifdef __CRT_HAVE_wcscpy_s
/* >> wcscpy_s(3) */
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscpy_s */
#include <libc/local/corecrt_wstring/wcscpy_s.h>
/* >> wcscpy_s(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscpy_s */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> wcsnlen(3) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !... */
#endif /* !__local___localdep_wcsnlen_defined */
__NAMESPACE_LOCAL_END
/* >> wcsnlen_s(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) { return __str ? (__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__str, __maxlen) : 0; }
#ifdef __CRT_HAVE_wcsncat_s
/* >> wcsncat_s(3) */
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncat_s,(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncat_s */
#include <libc/local/corecrt_wstring/wcsncat_s.h>
/* >> wcsncat_s(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncat_s)(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncat_s */
#ifdef __CRT_HAVE_wcsncpy_s
/* >> wcsncpy_s(3) */
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncpy_s */
#include <libc/local/corecrt_wstring/wcsncpy_s.h>
/* >> wcsncpy_s(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncpy_s */
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/wchar/wcstok.h>
/* >> wcstok(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok_s)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__str, __delim, __save_ptr); }
#endif /* !... */
#endif  /* __USE_DOS_SLIB */
#endif /* !_WSTRING_DEFINED */
#if defined(__CRT_HAVE_wcstok) && defined(__CRT_DOS_PRIMARY)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined
#ifdef __CRT_HAVE_wcstok_s
/* >> wcstok(3) */
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* __CRT_HAVE_wcstok_s */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
/* >> wcstok(3) */
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !__CRT_HAVE_wcstok_s */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
/* >> wcstok(3)
 * Define wcstok() incorrectly, the same way DOS does */
__CEIREDIRECT(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim),wcstok,{ static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); })
#else /* __CRT_HAVE_wcstok && __CRT_DOS_PRIMARY */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
/* >> wcstok(3) */
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !... */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
/* >> wcstok(3)
 * Define wcstok() incorrectly, the same way DOS does */
__LOCAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcstok)(wchar_t *__str, wchar_t const *__restrict __delim) { static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); }
#endif /* !__CRT_HAVE_wcstok || !__CRT_DOS_PRIMARY */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

#endif /* !_CORECRT_WSTRING_H */
