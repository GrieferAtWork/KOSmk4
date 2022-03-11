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
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdint.h) */
/* (#) Portability: DJGPP         (/include/stdint.h) */
/* (#) Portability: GNU C Library (/stdlib/stdint.h) */
/* (#) Portability: MSVC          (/include/stdint.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdint.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdint.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdint.h) */
/* (#) Portability: diet libc     (/include/stdint.h) */
/* (#) Portability: libc6         (/include/stdint.h) */
/* (#) Portability: musl libc     (/include/stdint.h) */
/* (#) Portability: uClibc        (/include/stdint.h) */
#ifndef _STDINT_H
#define _STDINT_H 1

#ifdef _CXX_STDONLY_CSTDINT
#ifdef __CXX_SYSTEM_HEADER
#undef _STDINT_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdint.h" after "cstdint" */
#ifndef __intmax_t_defined
#define __intmax_t_defined
__NAMESPACE_STD_USING(intmax_t)
__NAMESPACE_STD_USING(uintmax_t)
#endif /* !__intmax_t_defined */

#ifndef __int8_t_defined
#define __int8_t_defined
#ifdef __INT8_TYPE__
__NAMESPACE_STD_USING(int8_t)
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
__NAMESPACE_STD_USING(int16_t)
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
__NAMESPACE_STD_USING(int32_t)
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
__NAMESPACE_STD_USING(int64_t)
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __UINT8_TYPE__
__NAMESPACE_STD_USING(uint8_t)
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
__NAMESPACE_STD_USING(uint16_t)
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
__NAMESPACE_STD_USING(uint32_t)
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
__NAMESPACE_STD_USING(uint64_t)
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __int_least8_t_defined
#define __int_least8_t_defined
__NAMESPACE_STD_USING(int_least8_t)
__NAMESPACE_STD_USING(int_least16_t)
__NAMESPACE_STD_USING(int_least32_t)
__NAMESPACE_STD_USING(uint_least8_t)
__NAMESPACE_STD_USING(uint_least16_t)
__NAMESPACE_STD_USING(uint_least32_t)
#ifdef __UINT_LEAST64_TYPE__
__NAMESPACE_STD_USING(int_least64_t)
__NAMESPACE_STD_USING(uint_least64_t)
#endif /* __UINT_LEAST64_TYPE__ */
#endif /* !__int_least8_t_defined */

#ifndef __int_fast8_t_defined
#define __int_fast8_t_defined
__NAMESPACE_STD_USING(int_fast8_t)
__NAMESPACE_STD_USING(int_fast16_t)
__NAMESPACE_STD_USING(int_fast32_t)
__NAMESPACE_STD_USING(uint_fast8_t)
__NAMESPACE_STD_USING(uint_fast16_t)
__NAMESPACE_STD_USING(uint_fast32_t)
#ifdef __UINT_FAST64_TYPE__
__NAMESPACE_STD_USING(int_fast64_t)
__NAMESPACE_STD_USING(uint_fast64_t)
#endif /* __UINT_FAST64_TYPE__ */
#endif /* !__int_fast8_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
__NAMESPACE_STD_USING(intptr_t)
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
__NAMESPACE_STD_USING(uintptr_t)
#endif /* !__uintptr_t_defined */
#undef _CXX_STDONLY_CSTDINT
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDINT */

#include "__stdinc.h"
/**/

#include <features.h> /* __USE_KOS */

#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN
__NAMESPACE_STD_BEGIN

#ifndef __std_intmax_t_defined
#define __std_intmax_t_defined
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#endif /* !__std_intmax_t_defined */

#ifndef __std_int8_t_defined
#define __std_int8_t_defined
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#endif /* __INT64_TYPE__ */
#endif /* !__std_int8_t_defined */

#ifndef __std_uint8_t_defined
#define __std_uint8_t_defined
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__std_uint8_t_defined */

#ifndef __std_int_least8_t_defined
#define __std_int_least8_t_defined
typedef __INT_LEAST8_TYPE__   int_least8_t;
typedef __INT_LEAST16_TYPE__  int_least16_t;
typedef __INT_LEAST32_TYPE__  int_least32_t;
typedef __UINT_LEAST8_TYPE__  uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
#ifdef __UINT_LEAST64_TYPE__
typedef __INT_LEAST64_TYPE__  int_least64_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;
#endif /* __UINT_LEAST64_TYPE__ */
#endif /* !__std_int_least8_t_defined */

#ifndef __std_int_fast8_t_defined
#define __std_int_fast8_t_defined
typedef __INT_FAST8_TYPE__   int_fast8_t;
typedef __INT_FAST16_TYPE__  int_fast16_t;
typedef __UINT_FAST8_TYPE__  uint_fast8_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __INT_FAST32_TYPE__  int_fast32_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
#ifdef __UINT_FAST64_TYPE__
typedef __INT_FAST64_TYPE__  int_fast64_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;
#endif /* __UINT_FAST64_TYPE__ */
#endif /* !__std_int_fast8_t_defined */

#ifndef __std_intptr_t_defined
#define __std_intptr_t_defined
typedef __INTPTR_TYPE__  intptr_t;
#endif /* !__std_intptr_t_defined */

#ifndef __std_uintptr_t_defined
#define __std_uintptr_t_defined
typedef __UINTPTR_TYPE__ uintptr_t;
#endif /* !__std_uintptr_t_defined */

__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __intmax_t_defined
#define __intmax_t_defined
__NAMESPACE_STD_USING(intmax_t)
__NAMESPACE_STD_USING(uintmax_t)
#endif /* !__intmax_t_defined */

#ifndef __int8_t_defined
#define __int8_t_defined
#ifdef __INT8_TYPE__
__NAMESPACE_STD_USING(int8_t)
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
__NAMESPACE_STD_USING(int16_t)
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
__NAMESPACE_STD_USING(int32_t)
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
__NAMESPACE_STD_USING(int64_t)
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __UINT8_TYPE__
__NAMESPACE_STD_USING(uint8_t)
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
__NAMESPACE_STD_USING(uint16_t)
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
__NAMESPACE_STD_USING(uint32_t)
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
__NAMESPACE_STD_USING(uint64_t)
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __int_least8_t_defined
#define __int_least8_t_defined
__NAMESPACE_STD_USING(int_least8_t)
__NAMESPACE_STD_USING(int_least16_t)
__NAMESPACE_STD_USING(int_least32_t)
__NAMESPACE_STD_USING(uint_least8_t)
__NAMESPACE_STD_USING(uint_least16_t)
__NAMESPACE_STD_USING(uint_least32_t)
#ifdef __UINT_LEAST64_TYPE__
__NAMESPACE_STD_USING(int_least64_t)
__NAMESPACE_STD_USING(uint_least64_t)
#endif /* __UINT_LEAST64_TYPE__ */
#endif /* !__int_least8_t_defined */

#ifndef __int_fast8_t_defined
#define __int_fast8_t_defined
__NAMESPACE_STD_USING(int_fast8_t)
__NAMESPACE_STD_USING(int_fast16_t)
__NAMESPACE_STD_USING(int_fast32_t)
__NAMESPACE_STD_USING(uint_fast8_t)
__NAMESPACE_STD_USING(uint_fast16_t)
__NAMESPACE_STD_USING(uint_fast32_t)
#ifdef __UINT_FAST64_TYPE__
__NAMESPACE_STD_USING(int_fast64_t)
__NAMESPACE_STD_USING(uint_fast64_t)
#endif /* __UINT_FAST64_TYPE__ */
#endif /* !__int_fast8_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
__NAMESPACE_STD_USING(intptr_t)
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
__NAMESPACE_STD_USING(uintptr_t)
#endif /* !__uintptr_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__DECL_END
#endif /* __CC__ */


#ifndef INTMAX_MIN
#define INTMAX_MIN __INTMAX_MIN__
#endif /* !INTMAX_MIN */
#ifndef INTMAX_MAX
#define INTMAX_MAX __INTMAX_MAX__
#endif /* !INTMAX_MAX */
#ifndef UINTMAX_MAX
#define UINTMAX_MAX __UINTMAX_MAX__
#endif /* !UINTMAX_MAX */
#ifndef INT8_MIN
#define INT8_MIN __INT8_MIN__
#endif /* !INT8_MIN */
#ifndef INT16_MIN
#define INT16_MIN __INT16_MIN__
#endif /* !INT16_MIN */
#ifndef INT32_MIN
#define INT32_MIN __INT32_MIN__
#endif /* !INT32_MIN */
#ifndef INT8_MAX
#define INT8_MAX __INT8_MAX__
#endif /* !INT8_MAX */
#ifndef INT16_MAX
#define INT16_MAX __INT16_MAX__
#endif /* !INT16_MAX */
#ifndef INT32_MAX
#define INT32_MAX __INT32_MAX__
#endif /* !INT32_MAX */
#ifndef UINT8_MAX
#define UINT8_MAX __UINT8_MAX__
#endif /* !UINT8_MAX */
#ifndef UINT16_MAX
#define UINT16_MAX __UINT16_MAX__
#endif /* !UINT16_MAX */
#ifndef UINT32_MAX
#define UINT32_MAX __UINT32_MAX__
#endif /* !UINT32_MAX */
#ifdef __UINT64_MAX__
#ifndef INT64_MIN
#define INT64_MIN __INT64_MIN__
#endif /* !INT64_MIN */
#ifndef INT64_MAX
#define INT64_MAX __INT64_MAX__
#endif /* !INT64_MAX */
#ifndef UINT64_MAX
#define UINT64_MAX __UINT64_MAX__
#endif /* !UINT64_MAX */
#endif /* __UINT64_MAX__ */
#ifndef INT_LEAST8_MIN
#define INT_LEAST8_MIN __INT_LEAST8_MIN__
#endif /* !INT_LEAST8_MIN */
#ifndef INT_LEAST16_MIN
#define INT_LEAST16_MIN __INT_LEAST16_MIN__
#endif /* !INT_LEAST16_MIN */
#ifndef INT_LEAST32_MIN
#define INT_LEAST32_MIN __INT_LEAST32_MIN__
#endif /* !INT_LEAST32_MIN */
#ifndef INT_LEAST8_MAX
#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#endif /* !INT_LEAST8_MAX */
#ifndef INT_LEAST16_MAX
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#endif /* !INT_LEAST16_MAX */
#ifndef INT_LEAST32_MAX
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#endif /* !INT_LEAST32_MAX */
#ifndef UINT_LEAST8_MAX
#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__
#endif /* !UINT_LEAST8_MAX */
#ifndef UINT_LEAST16_MAX
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#endif /* !UINT_LEAST16_MAX */
#ifndef UINT_LEAST32_MAX
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#endif /* !UINT_LEAST32_MAX */
#ifdef __UINT_LEAST64_MAX__
#ifndef INT_LEAST64_MIN
#define INT_LEAST64_MIN __INT_LEAST64_MIN__
#endif /* !INT_LEAST64_MIN */
#ifndef INT_LEAST64_MAX
#define INT_LEAST64_MAX __INT_LEAST64_MAX__
#endif /* !INT_LEAST64_MAX */
#ifndef UINT_LEAST64_MAX
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__
#endif /* !UINT_LEAST64_MAX */
#endif /* __UINT_LEAST64_MAX__ */
#ifndef INT_FAST8_MIN
#define INT_FAST8_MIN __INT_FAST8_MIN__
#endif /* !INT_FAST8_MIN */
#ifndef INT_FAST16_MIN
#define INT_FAST16_MIN __INT_FAST16_MIN__
#endif /* !INT_FAST16_MIN */
#ifndef INT_FAST32_MIN
#define INT_FAST32_MIN __INT_FAST32_MIN__
#endif /* !INT_FAST32_MIN */
#ifndef INT_FAST8_MAX
#define INT_FAST8_MAX __INT_FAST8_MAX__
#endif /* !INT_FAST8_MAX */
#ifndef INT_FAST16_MAX
#define INT_FAST16_MAX __INT_FAST16_MAX__
#endif /* !INT_FAST16_MAX */
#ifndef INT_FAST32_MAX
#define INT_FAST32_MAX __INT_FAST32_MAX__
#endif /* !INT_FAST32_MAX */
#ifndef UINT_FAST8_MAX
#define UINT_FAST8_MAX __UINT_FAST8_MAX__
#endif /* !UINT_FAST8_MAX */
#ifndef UINT_FAST16_MAX
#define UINT_FAST16_MAX __UINT_FAST16_MAX__
#endif /* !UINT_FAST16_MAX */
#ifndef UINT_FAST32_MAX
#define UINT_FAST32_MAX __UINT_FAST32_MAX__
#endif /* !UINT_FAST32_MAX */
#ifdef __UINT_FAST64_MAX__
#ifndef INT_FAST64_MIN
#define INT_FAST64_MIN __INT_FAST64_MIN__
#endif /* !INT_FAST64_MIN */
#ifndef INT_FAST64_MAX
#define INT_FAST64_MAX __INT_FAST64_MAX__
#endif /* !INT_FAST64_MAX */
#ifndef UINT_FAST64_MAX
#define UINT_FAST64_MAX __UINT_FAST64_MAX__
#endif /* !UINT_FAST64_MAX */
#endif /* __UINT_FAST64_MAX__ */
#ifndef INTPTR_MIN
#define INTPTR_MIN __INTPTR_MIN__
#endif /* !INTPTR_MIN */
#ifndef INTPTR_MAX
#define INTPTR_MAX __INTPTR_MAX__
#endif /* !INTPTR_MAX */
#ifndef UINTPTR_MAX
#define UINTPTR_MAX __UINTPTR_MAX__
#endif /* !UINTPTR_MAX */

#ifndef SIZE_MAX
#define SIZE_MAX __SIZE_MAX__
#endif /* !SIZE_MAX */
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN __PTRDIFF_MIN__
#endif /* !PTRDIFF_MIN */
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX __PTRDIFF_MAX__
#endif /* !PTRDIFF_MAX */
#ifndef SIG_ATOMIC_MIN
#define SIG_ATOMIC_MIN __SIG_ATOMIC_MIN__
#endif /* !SIG_ATOMIC_MIN */
#ifndef SIG_ATOMIC_MAX
#define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
#endif /* !SIG_ATOMIC_MAX */
#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#endif /* !WCHAR_MIN */
#ifndef WCHAR_MAX
#define WCHAR_MAX __WCHAR_MAX__
#endif /* !WCHAR_MAX */
#ifndef WINT_MIN
#define WINT_MIN __WINT_MIN__
#endif /* !WINT_MIN */
#ifndef WINT_MAX
#define WINT_MAX __WINT_MAX__
#endif /* !WINT_MAX */

#ifndef INTMAX_C
#define INTMAX_C __INTMAX_C
#endif /* !INTMAX_C */
#ifndef UINTMAX_C
#define UINTMAX_C __UINTMAX_C
#endif /* !UINTMAX_C */
#ifndef INT8_C
#define INT8_C __INT8_C
#endif /* !INT8_C */
#ifndef INT16_C
#define INT16_C __INT16_C
#endif /* !INT16_C */
#ifndef INT32_C
#define INT32_C __INT32_C
#endif /* !INT32_C */
#ifndef INT64_C
#define INT64_C __INT64_C
#endif /* !INT64_C */
#ifndef UINT8_C
#define UINT8_C __UINT8_C
#endif /* !UINT8_C */
#ifndef UINT16_C
#define UINT16_C __UINT16_C
#endif /* !UINT16_C */
#ifndef UINT32_C
#define UINT32_C __UINT32_C
#endif /* !UINT32_C */
#ifndef UINT64_C
#define UINT64_C __UINT64_C
#endif /* !UINT64_C */
#ifdef __USE_KOS
#ifndef SIZE_C
#define SIZE_C __SIZE_C
#endif /* !SIZE_C */
#ifndef SSIZE_C
#define SSIZE_C __SSIZE_C
#endif /* !SSIZE_C */
#ifndef INTPTR_C
#define INTPTR_C __INTPTR_C
#endif /* !INTPTR_C */
#ifndef UINTPTR_C
#define UINTPTR_C __UINTPTR_C
#endif /* !UINTPTR_C */
#endif /* __USE_KOS */


#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__) || 1
#ifndef INT8_WIDTH
#define INT8_WIDTH 8
#endif /* !INT8_WIDTH */
#ifndef UINT8_WIDTH
#define UINT8_WIDTH 8
#endif /* !UINT8_WIDTH */
#ifndef INT16_WIDTH
#define INT16_WIDTH 16
#endif /* !INT16_WIDTH */
#ifndef UINT16_WIDTH
#define UINT16_WIDTH 16
#endif /* !UINT16_WIDTH */
#ifndef INT32_WIDTH
#define INT32_WIDTH 32
#endif /* !INT32_WIDTH */
#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif /* !UINT32_WIDTH */
#ifdef __INT64_TYPE__
#ifndef INT64_WIDTH
#define INT64_WIDTH 64
#endif /* !INT64_WIDTH */
#ifndef UINT64_WIDTH
#define UINT64_WIDTH 64
#endif /* !UINT64_WIDTH */
#endif /* __INT64_TYPE__ */

#ifndef INT_LEAST8_WIDTH
#define INT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#endif /* !INT_LEAST8_WIDTH */
#ifndef UINT_LEAST8_WIDTH
#define UINT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#endif /* !UINT_LEAST8_WIDTH */
#ifndef INT_LEAST16_WIDTH
#define INT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#endif /* !INT_LEAST16_WIDTH */
#ifndef UINT_LEAST16_WIDTH
#define UINT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#endif /* !UINT_LEAST16_WIDTH */
#ifndef INT_LEAST32_WIDTH
#define INT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#endif /* !INT_LEAST32_WIDTH */
#ifndef UINT_LEAST32_WIDTH
#define UINT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#endif /* !UINT_LEAST32_WIDTH */
#ifdef __INT_LEAST64_WIDTH__
#ifndef INT_LEAST64_WIDTH
#define INT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#endif /* !INT_LEAST64_WIDTH */
#ifndef UINT_LEAST64_WIDTH
#define UINT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#endif /* !UINT_LEAST64_WIDTH */
#endif /* __INT_LEAST64_WIDTH__ */

#ifndef INT_FAST8_WIDTH
#define INT_FAST8_WIDTH __INT_FAST8_WIDTH__
#endif /* !INT_FAST8_WIDTH */
#ifndef UINT_FAST8_WIDTH
#define UINT_FAST8_WIDTH __INT_FAST8_WIDTH__
#endif /* !UINT_FAST8_WIDTH */
#ifndef INT_FAST16_WIDTH
#define INT_FAST16_WIDTH __INT_FAST16_WIDTH__
#endif /* !INT_FAST16_WIDTH */
#ifndef UINT_FAST16_WIDTH
#define UINT_FAST16_WIDTH __INT_FAST16_WIDTH__
#endif /* !UINT_FAST16_WIDTH */
#ifndef INT_FAST32_WIDTH
#define INT_FAST32_WIDTH __INT_FAST32_WIDTH__
#endif /* !INT_FAST32_WIDTH */
#ifndef UINT_FAST32_WIDTH
#define UINT_FAST32_WIDTH __INT_FAST32_WIDTH__
#endif /* !UINT_FAST32_WIDTH */
#ifdef __INT_FAST64_WIDTH__
#ifndef INT_FAST64_WIDTH
#define INT_FAST64_WIDTH __INT_FAST64_WIDTH__
#endif /* !INT_FAST64_WIDTH */
#ifndef UINT_FAST64_WIDTH
#define UINT_FAST64_WIDTH __INT_FAST64_WIDTH__
#endif /* !UINT_FAST64_WIDTH */
#endif /* __INT_FAST64_WIDTH__ */

#ifndef INTPTR_WIDTH
#define INTPTR_WIDTH __INTPTR_WIDTH__
#endif /* !INTPTR_WIDTH */
#ifndef UINTPTR_WIDTH
#define UINTPTR_WIDTH __INTPTR_WIDTH__
#endif /* !UINTPTR_WIDTH */

#ifndef INTMAX_WIDTH
#define INTMAX_WIDTH __INTMAX_WIDTH__
#endif /* !INTMAX_WIDTH */
#ifndef UINTMAX_WIDTH
#define UINTMAX_WIDTH __INTMAX_WIDTH__
#endif /* !UINTMAX_WIDTH */

#ifndef PTRDIFF_WIDTH
#define PTRDIFF_WIDTH __PTRDIFF_WIDTH__
#endif /* !PTRDIFF_WIDTH */
#ifndef SIG_ATOMIC_WIDTH
#define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__
#endif /* !SIG_ATOMIC_WIDTH */
#ifndef SIZE_WIDTH
#define SIZE_WIDTH __SIZE_WIDTH__
#endif /* !SIZE_WIDTH */
#ifndef WCHAR_WIDTH
#define WCHAR_WIDTH __WCHAR_WIDTH__
#endif /* !WCHAR_WIDTH */
#ifndef WINT_WIDTH
#define WINT_WIDTH __WINT_WIDTH__
#endif /* !WINT_WIDTH */
#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDINT
#undef _STDINT_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDINT */
#endif /* !_STDINT_H */
