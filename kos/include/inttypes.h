/* HASH CRC-32:0xccd6eb58 */
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
#ifndef _INTTYPES_H
#define _INTTYPES_H 1

#ifdef _CXX_STDONLY_CINTTYPES
#ifdef __CXX_SYSTEM_HEADER
#undef _INTTYPES_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "inttypes.h" after "cinttypes" */
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined 1
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
__NAMESPACE_STD_USING(imaxabs)
__NAMESPACE_STD_USING(imaxdiv)
__NAMESPACE_STD_USING(strtoimax)
__NAMESPACE_STD_USING(strtoumax)
__NAMESPACE_STD_USING(wcstoimax)
__NAMESPACE_STD_USING(wcstoumax)
#undef _CXX_STDONLY_CINTTYPES
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CINTTYPES */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <stdint.h>
#include <hybrid/typecore.h>
#ifdef __USE_DOS
#include <xlocale.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

#ifndef ____gwchar_t_defined
#define ____gwchar_t_defined 1
#define __gwchar_t __WCHAR_TYPE__
#endif

#if __SIZEOF_LONG__ == 8
#define __PRI64_PREFIX  "l"
#define __PRIPTR_PREFIX "l"
#else /* __SIZEOF_LONG__ == 8 */
#define __PRI64_PREFIX  "ll"
#define __PRIPTR_PREFIX
#endif /* __SIZEOF_LONG__ != 8 */

#define PRId8          "d"
#define PRId16         "d"
#define PRId32         "d"
#define PRId64         __PRI64_PREFIX "d"
#define PRIdLEAST8     "d"
#define PRIdLEAST16    "d"
#define PRIdLEAST32    "d"
#define PRIdLEAST64    __PRI64_PREFIX "d"
#define PRIdFAST8      "d"
#define PRIdFAST16     __PRIPTR_PREFIX "d"
#define PRIdFAST32     __PRIPTR_PREFIX "d"
#define PRIdFAST64     __PRI64_PREFIX "d"
#define PRIi8          "i"
#define PRIi16         "i"
#define PRIi32         "i"
#define PRIi64         __PRI64_PREFIX "i"
#define PRIiLEAST8     "i"
#define PRIiLEAST16    "i"
#define PRIiLEAST32    "i"
#define PRIiLEAST64    __PRI64_PREFIX "i"
#define PRIiFAST8      "i"
#define PRIiFAST16     __PRIPTR_PREFIX "i"
#define PRIiFAST32     __PRIPTR_PREFIX "i"
#define PRIiFAST64     __PRI64_PREFIX "i"
#define PRIo8          "o"
#define PRIo16         "o"
#define PRIo32         "o"
#define PRIo64         __PRI64_PREFIX "o"
#define PRIoLEAST8     "o"
#define PRIoLEAST16    "o"
#define PRIoLEAST32    "o"
#define PRIoLEAST64    __PRI64_PREFIX "o"
#define PRIoFAST8      "o"
#define PRIoFAST16     __PRIPTR_PREFIX "o"
#define PRIoFAST32     __PRIPTR_PREFIX "o"
#define PRIoFAST64     __PRI64_PREFIX "o"
#define PRIu8          "u"
#define PRIu16         "u"
#define PRIu32         "u"
#define PRIu64         __PRI64_PREFIX "u"
#define PRIuLEAST8     "u"
#define PRIuLEAST16    "u"
#define PRIuLEAST32    "u"
#define PRIuLEAST64    __PRI64_PREFIX "u"
#define PRIuFAST8      "u"
#define PRIuFAST16     __PRIPTR_PREFIX "u"
#define PRIuFAST32     __PRIPTR_PREFIX "u"
#define PRIuFAST64     __PRI64_PREFIX "u"
#define PRIx8          "x"
#define PRIx16         "x"
#define PRIx32         "x"
#define PRIx64         __PRI64_PREFIX "x"
#define PRIxLEAST8     "x"
#define PRIxLEAST16    "x"
#define PRIxLEAST32    "x"
#define PRIxLEAST64    __PRI64_PREFIX "x"
#define PRIxFAST8      "x"
#define PRIxFAST16     __PRIPTR_PREFIX "x"
#define PRIxFAST32     __PRIPTR_PREFIX "x"
#define PRIxFAST64     __PRI64_PREFIX "x"
#define PRIX8          "X"
#define PRIX16         "X"
#define PRIX32         "X"
#define PRIX64         __PRI64_PREFIX "X"
#define PRIXLEAST8     "X"
#define PRIXLEAST16    "X"
#define PRIXLEAST32    "X"
#define PRIXLEAST64    __PRI64_PREFIX "X"
#define PRIXFAST8      "X"
#define PRIXFAST16     __PRIPTR_PREFIX "X"
#define PRIXFAST32     __PRIPTR_PREFIX "X"
#define PRIXFAST64     __PRI64_PREFIX "X"
#define PRIdMAX        __PRI64_PREFIX "d"
#define PRIiMAX        __PRI64_PREFIX "i"
#define PRIoMAX        __PRI64_PREFIX "o"
#define PRIuMAX        __PRI64_PREFIX "u"
#define PRIxMAX        __PRI64_PREFIX "x"
#define PRIXMAX        __PRI64_PREFIX "X"
#define PRIdPTR        __PRIPTR_PREFIX "d"
#define PRIiPTR        __PRIPTR_PREFIX "i"
#define PRIoPTR        __PRIPTR_PREFIX "o"
#define PRIuPTR        __PRIPTR_PREFIX "u"
#define PRIxPTR        __PRIPTR_PREFIX "x"
#define PRIXPTR        __PRIPTR_PREFIX "X"

#define SCNd8          "hhd"
#define SCNd16         "hd"
#define SCNd32         "d"
#define SCNd64         __PRI64_PREFIX "d"
#define SCNdLEAST8     "hhd"
#define SCNdLEAST16    "hd"
#define SCNdLEAST32    "d"
#define SCNdLEAST64    __PRI64_PREFIX "d"
#define SCNdFAST8      "hhd"
#define SCNdFAST16     __PRIPTR_PREFIX "d"
#define SCNdFAST32     __PRIPTR_PREFIX "d"
#define SCNdFAST64     __PRI64_PREFIX "d"
#define SCNi8          "hhi"
#define SCNi16         "hi"
#define SCNi32         "i"
#define SCNi64         __PRI64_PREFIX "i"
#define SCNiLEAST8     "hhi"
#define SCNiLEAST16    "hi"
#define SCNiLEAST32    "i"
#define SCNiLEAST64    __PRI64_PREFIX "i"
#define SCNiFAST8      "hhi"
#define SCNiFAST16     __PRIPTR_PREFIX "i"
#define SCNiFAST32     __PRIPTR_PREFIX "i"
#define SCNiFAST64     __PRI64_PREFIX "i"
#define SCNu8          "hhu"
#define SCNu16         "hu"
#define SCNu32         "u"
#define SCNu64         __PRI64_PREFIX "u"
#define SCNuLEAST8     "hhu"
#define SCNuLEAST16    "hu"
#define SCNuLEAST32    "u"
#define SCNuLEAST64    __PRI64_PREFIX "u"
#define SCNuFAST8      "hhu"
#define SCNuFAST16     __PRIPTR_PREFIX "u"
#define SCNuFAST32     __PRIPTR_PREFIX "u"
#define SCNuFAST64     __PRI64_PREFIX "u"
#define SCNo8          "hho"
#define SCNo16         "ho"
#define SCNo32         "o"
#define SCNo64         __PRI64_PREFIX "o"
#define SCNoLEAST8     "hho"
#define SCNoLEAST16    "ho"
#define SCNoLEAST32    "o"
#define SCNoLEAST64    __PRI64_PREFIX "o"
#define SCNoFAST8      "hho"
#define SCNoFAST16     __PRIPTR_PREFIX "o"
#define SCNoFAST32     __PRIPTR_PREFIX "o"
#define SCNoFAST64     __PRI64_PREFIX "o"
#define SCNx8          "hhx"
#define SCNx16         "hx"
#define SCNx32         "x"
#define SCNx64         __PRI64_PREFIX "x"
#define SCNxLEAST8     "hhx"
#define SCNxLEAST16    "hx"
#define SCNxLEAST32    "x"
#define SCNxLEAST64    __PRI64_PREFIX "x"
#define SCNxFAST8      "hhx"
#define SCNxFAST16     __PRIPTR_PREFIX "x"
#define SCNxFAST32     __PRIPTR_PREFIX "x"
#define SCNxFAST64     __PRI64_PREFIX "x"
#define SCNdMAX        __PRI64_PREFIX "d"
#define SCNiMAX        __PRI64_PREFIX "i"
#define SCNoMAX        __PRI64_PREFIX "o"
#define SCNuMAX        __PRI64_PREFIX "u"
#define SCNxMAX        __PRI64_PREFIX "x"
#define SCNdPTR        __PRIPTR_PREFIX "d"
#define SCNiPTR        __PRIPTR_PREFIX "i"
#define SCNoPTR        __PRIPTR_PREFIX "o"
#define SCNuPTR        __PRIPTR_PREFIX "u"
#define SCNxPTR        __PRIPTR_PREFIX "x"

#ifdef __CC__

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("quot")
#pragma push_macro("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef quot
#undef rem
struct __imaxdiv_struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rem")
#pragma pop_macro("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifndef __std_imaxdiv_t_defined
#define __std_imaxdiv_t_defined 1
__NAMESPACE_STD_BEGIN
typedef struct __imaxdiv_struct imaxdiv_t;
__NAMESPACE_STD_END
#endif /* !__std_imaxdiv_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined 1
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#if __has_builtin(__builtin_imaxabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_imaxabs)
__FORCELOCAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return __builtin_imaxabs(__x); }
#elif defined(__CRT_HAVE_imaxabs)
__CDECLARE(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),(__x))
#elif defined(__CRT_HAVE_abs) && (__SIZEOF_INTMAX_T__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),llabs,(__x))
#else /* LIBC: imaxabs */
__NAMESPACE_STD_END
#include <local/inttypes/imaxabs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(imaxabs, __FORCELOCAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(imaxabs))(__x); })
#endif /* imaxabs... */
#if defined(__CRT_HAVE_imaxdiv)
__CDECLARE(__ATTR_CONST,imaxdiv_t,__NOTHROW,imaxdiv,(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom),(__numer,__denom))
#else /* LIBC: imaxdiv */
__NAMESPACE_STD_END
#include <local/inttypes/imaxdiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(imaxdiv, __FORCELOCAL __ATTR_CONST imaxdiv_t __NOTHROW(__LIBCCALL imaxdiv)(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(imaxdiv))(__numer, __denom); })
#endif /* imaxdiv... */
#if defined(__CRT_HAVE_strtoimax)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, int __base),strto32,(__nptr,__endptr,__base))
#else /* LIBC: strtoimax */
__NAMESPACE_STD_END
#include <local/inttypes/strtoimax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoimax, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax))(__nptr, __endptr, __base); })
#endif /* strtoimax... */
#if defined(__CRT_HAVE_strtoumax)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#else /* LIBC: strtoumax */
__NAMESPACE_STD_END
#include <local/inttypes/strtoumax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoumax, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax))(__nptr, __endptr, __base); })
#endif /* strtoumax... */
#if defined(__CRT_HAVE_wcstoimax)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#else /* LIBC: wcstoimax */
__NAMESPACE_STD_END
#include <local/inttypes/wcstoimax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoimax, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax))(__nptr, __endptr, __base); })
#endif /* wcstoimax... */
#if defined(__CRT_HAVE_wcstoumax)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#else /* LIBC: wcstoumax */
__NAMESPACE_STD_END
#include <local/inttypes/wcstoumax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoumax, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax))(__nptr, __endptr, __base); })
#endif /* wcstoumax... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(imaxabs)
__NAMESPACE_STD_USING(imaxdiv)
__NAMESPACE_STD_USING(strtoimax)
__NAMESPACE_STD_USING(strtoumax)
__NAMESPACE_STD_USING(wcstoimax)
__NAMESPACE_STD_USING(wcstoumax)
#endif /* !__CXX_SYSTEM_HEADER */




#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_strtoimax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoimax_l */
#include <local/inttypes/strtoimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoimax_l, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtoimax_l... */
#if defined(__CRT_HAVE_strtoumax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoumax_l */
#include <local/inttypes/strtoumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoumax_l, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtoumax_l... */
#if defined(__CRT_HAVE_wcstoimax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoimax_l */
#include <local/inttypes/wcstoimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoimax_l, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstoimax_l... */
#if defined(__CRT_HAVE_wcstoumax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoumax_l */
#include <local/inttypes/wcstoumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoumax_l, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstoumax_l... */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */



#ifdef __USE_DOS
#if defined(__CRT_HAVE_strtoimax_l)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l)
__CDECLARE(,__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoimax_l */
#include <local/inttypes/strtoimax_l.h>
__FORCELOCAL __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoimax_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoimax_l... */
#if defined(__CRT_HAVE_strtoumax_l)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l)
__CDECLARE(,__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoumax_l */
#include <local/inttypes/strtoumax_l.h>
__FORCELOCAL __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoumax_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoumax_l... */
#if defined(__CRT_HAVE_wcstoimax_l)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l)
__CDECLARE(,__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoimax_l */
#include <local/inttypes/wcstoimax_l.h>
__FORCELOCAL __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))(__nptr, __endptr, __base, __locale); }
#endif /* _wcstoimax_l... */
#if defined(__CRT_HAVE_wcstoumax_l)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && (__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l)
__CDECLARE(,__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoumax_l */
#include <local/inttypes/wcstoumax_l.h>
__FORCELOCAL __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))(__nptr, __endptr, __base, __locale); }
#endif /* _wcstoumax_l... */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_INTTYPES_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CINTTYPES 1
#undef _INTTYPES_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CINTTYPES */
#endif /* !_INTTYPES_H */
