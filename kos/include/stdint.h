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
#ifndef _STDINT_H
#define _STDINT_H 1

#ifdef _CXX_STDONLY_CSTDINT
#ifdef __CXX_SYSTEM_HEADER
#undef _STDINT_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdint.h" after "cstdint" */
#ifndef __intmax_t_defined
#define __intmax_t_defined 1
__NAMESPACE_STD_USING(intmax_t)
__NAMESPACE_STD_USING(uintmax_t)
#endif /* !__intmax_t_defined */

#ifndef __int8_t_defined
#define __int8_t_defined 1
__NAMESPACE_STD_USING(int8_t)
__NAMESPACE_STD_USING(int16_t)
__NAMESPACE_STD_USING(int32_t)
#ifdef __INT64_TYPE__
__NAMESPACE_STD_USING(int64_t)
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined 1
__NAMESPACE_STD_USING(uint8_t)
__NAMESPACE_STD_USING(uint16_t)
__NAMESPACE_STD_USING(uint32_t)
#ifdef __UINT64_TYPE__
__NAMESPACE_STD_USING(uint64_t)
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __int_least8_t_defined
#define __int_least8_t_defined 1
__NAMESPACE_STD_USING(int_least8_t)
__NAMESPACE_STD_USING(int_least16_t)
__NAMESPACE_STD_USING(int_least32_t)
__NAMESPACE_STD_USING(int_least64_t)
__NAMESPACE_STD_USING(uint_least8_t)
__NAMESPACE_STD_USING(uint_least16_t)
__NAMESPACE_STD_USING(uint_least32_t)
__NAMESPACE_STD_USING(uint_least64_t)
#endif /* !__int_least8_t_defined */

#ifndef __int_fast8_t_defined
#define __int_fast8_t_defined 1
__NAMESPACE_STD_USING(int_fast8_t)
__NAMESPACE_STD_USING(int_fast16_t)
__NAMESPACE_STD_USING(int_fast32_t)
__NAMESPACE_STD_USING(int_fast64_t)
__NAMESPACE_STD_USING(uint_fast8_t)
__NAMESPACE_STD_USING(uint_fast16_t)
__NAMESPACE_STD_USING(uint_fast32_t)
__NAMESPACE_STD_USING(uint_fast64_t)
#endif /* !__int_fast8_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
__NAMESPACE_STD_USING(intptr_t)
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined 1
__NAMESPACE_STD_USING(uintptr_t)
#endif /* !__uintptr_t_defined */
#undef _CXX_STDONLY_CSTDINT
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDINT */

#include "__stdinc.h"
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN
__NAMESPACE_STD_BEGIN

#ifndef __std_intmax_t_defined
#define __std_intmax_t_defined 1
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#endif /* !__std_intmax_t_defined */

#ifndef __std_int8_t_defined
#define __std_int8_t_defined 1
typedef __INT8_TYPE__   int8_t;
typedef __INT16_TYPE__  int16_t;
typedef __INT32_TYPE__  int32_t;
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__  int64_t;
#endif /* __INT64_TYPE__ */
#endif /* !__std_int8_t_defined */

#ifndef __std_uint8_t_defined
#define __std_uint8_t_defined 1
typedef __UINT8_TYPE__  uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__std_uint8_t_defined */

#ifndef __std_int_least8_t_defined
#define __std_int_least8_t_defined 1
typedef __INT_LEAST8_TYPE__   int_least8_t;
typedef __INT_LEAST16_TYPE__  int_least16_t;
typedef __INT_LEAST32_TYPE__  int_least32_t;
typedef __INT_LEAST64_TYPE__  int_least64_t;
typedef __UINT_LEAST8_TYPE__  uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;
#endif /* !__std_int_least8_t_defined */

#ifndef __std_int_fast8_t_defined
#define __std_int_fast8_t_defined 1
typedef __INT_FAST8_TYPE__    int_fast8_t;
typedef __INT_FAST16_TYPE__   int_fast16_t;
typedef __INT_FAST32_TYPE__   int_fast32_t;
typedef __INT_FAST64_TYPE__   int_fast64_t;
typedef __UINT_FAST8_TYPE__   uint_fast8_t;
typedef __UINT_FAST16_TYPE__  uint_fast16_t;
typedef __UINT_FAST32_TYPE__  uint_fast32_t;
typedef __UINT_FAST64_TYPE__  uint_fast64_t;
#endif /* !__std_int_fast8_t_defined */

#ifndef __std_intptr_t_defined
#define __std_intptr_t_defined 1
typedef __INTPTR_TYPE__  intptr_t;
#endif /* !__std_intptr_t_defined */

#ifndef __std_uintptr_t_defined
#define __std_uintptr_t_defined 1
typedef __UINTPTR_TYPE__ uintptr_t;
#endif /* !__std_uintptr_t_defined */

__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __intmax_t_defined
#define __intmax_t_defined 1
__NAMESPACE_STD_USING(intmax_t)
__NAMESPACE_STD_USING(uintmax_t)
#endif /* !__intmax_t_defined */

#ifndef __int8_t_defined
#define __int8_t_defined 1
__NAMESPACE_STD_USING(int8_t)
__NAMESPACE_STD_USING(int16_t)
__NAMESPACE_STD_USING(int32_t)
#ifdef __INT64_TYPE__
__NAMESPACE_STD_USING(int64_t)
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined 1
__NAMESPACE_STD_USING(uint8_t)
__NAMESPACE_STD_USING(uint16_t)
__NAMESPACE_STD_USING(uint32_t)
#ifdef __UINT64_TYPE__
__NAMESPACE_STD_USING(uint64_t)
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __int_least8_t_defined
#define __int_least8_t_defined 1
__NAMESPACE_STD_USING(int_least8_t)
__NAMESPACE_STD_USING(int_least16_t)
__NAMESPACE_STD_USING(int_least32_t)
__NAMESPACE_STD_USING(int_least64_t)
__NAMESPACE_STD_USING(uint_least8_t)
__NAMESPACE_STD_USING(uint_least16_t)
__NAMESPACE_STD_USING(uint_least32_t)
__NAMESPACE_STD_USING(uint_least64_t)
#endif /* !__int_least8_t_defined */

#ifndef __int_fast8_t_defined
#define __int_fast8_t_defined 1
__NAMESPACE_STD_USING(int_fast8_t)
__NAMESPACE_STD_USING(int_fast16_t)
__NAMESPACE_STD_USING(int_fast32_t)
__NAMESPACE_STD_USING(int_fast64_t)
__NAMESPACE_STD_USING(uint_fast8_t)
__NAMESPACE_STD_USING(uint_fast16_t)
__NAMESPACE_STD_USING(uint_fast32_t)
__NAMESPACE_STD_USING(uint_fast64_t)
#endif /* !__int_fast8_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
__NAMESPACE_STD_USING(intptr_t)
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined 1
__NAMESPACE_STD_USING(uintptr_t)
#endif /* !__uintptr_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__SYSDECL_END
#endif /* __CC__ */


#define INTMAX_MIN        __INTMAX_MIN__
#define INTMAX_MAX        __INTMAX_MAX__
#define UINTMAX_MAX       __UINTMAX_MAX__
#define INT8_MIN          __INT8_MIN__
#define INT16_MIN         __INT16_MIN__
#define INT32_MIN         __INT32_MIN__
#define INT64_MIN         __INT64_MIN__
#define INT8_MAX          __INT8_MAX__
#define INT16_MAX         __INT16_MAX__
#define INT32_MAX         __INT32_MAX__
#define INT64_MAX         __INT64_MAX__
#define UINT8_MAX         __UINT8_MAX__
#define UINT16_MAX        __UINT16_MAX__
#define UINT32_MAX        __UINT32_MAX__
#define UINT64_MAX        __UINT64_MAX__
#define INT_LEAST8_MIN    __INT_LEAST8_MIN__
#define INT_LEAST16_MIN   __INT_LEAST16_MIN__
#define INT_LEAST32_MIN   __INT_LEAST32_MIN__
#define INT_LEAST64_MIN   __INT_LEAST64_MIN__
#define INT_LEAST8_MAX    __INT_LEAST8_MAX__
#define INT_LEAST16_MAX   __INT_LEAST16_MAX__
#define INT_LEAST32_MAX   __INT_LEAST32_MAX__
#define INT_LEAST64_MAX   __INT_LEAST64_MAX__
#define UINT_LEAST8_MAX   __UINT_LEAST8_MAX__
#define UINT_LEAST16_MAX  __UINT_LEAST16_MAX__
#define UINT_LEAST32_MAX  __UINT_LEAST32_MAX__
#define UINT_LEAST64_MAX  __UINT_LEAST64_MAX__
#define INT_FAST8_MIN     __INT_FAST8_MIN__
#define INT_FAST16_MIN    __INT_FAST16_MIN__
#define INT_FAST32_MIN    __INT_FAST32_MIN__
#define INT_FAST64_MIN    __INT_FAST64_MIN__
#define INT_FAST8_MAX     __INT_FAST8_MAX__
#define INT_FAST16_MAX    __INT_FAST16_MAX__
#define INT_FAST32_MAX    __INT_FAST32_MAX__
#define INT_FAST64_MAX    __INT_FAST64_MAX__
#define UINT_FAST8_MAX    __UINT_FAST8_MAX__
#define UINT_FAST16_MAX   __UINT_FAST16_MAX__
#define UINT_FAST32_MAX   __UINT_FAST32_MAX__
#define UINT_FAST64_MAX   __UINT_FAST64_MAX__
#define INTPTR_MIN        __INTPTR_MIN__
#define INTPTR_MAX        __INTPTR_MAX__
#define UINTPTR_MAX       __UINTPTR_MAX__

#ifndef SIZE_MAX
#define SIZE_MAX          __SIZE_MAX__
#endif /* !SIZE_MAX */
#define PTRDIFF_MIN       __PTRDIFF_MIN__
#define PTRDIFF_MAX       __PTRDIFF_MAX__
#define SIG_ATOMIC_MIN    __SIG_ATOMIC_MIN__
#define SIG_ATOMIC_MAX    __SIG_ATOMIC_MAX__
#define WCHAR_MIN         __WCHAR_MIN__
#define WCHAR_MAX         __WCHAR_MAX__
#define WINT_MIN          __WINT_MIN__
#define WINT_MAX          __WINT_MAX__

#ifdef __CC__
#   define INTMAX_C(x)       __INTMAX_C(x)
#   define UINTMAX_C(x)      __UINTMAX_C(x)
#   define INT8_C(x)         __INT8_C(x)
#   define INT16_C(x)        __INT16_C(x)
#   define INT32_C(x)        __INT32_C(x)
#   define INT64_C(x)        __INT64_C(x)
#   define UINT8_C(x)        __UINT8_C(x)
#   define UINT16_C(x)       __UINT16_C(x)
#   define UINT32_C(x)       __UINT32_C(x)
#   define UINT64_C(x)       __UINT64_C(x)
#else /* __CC__ */
#   define INTMAX_C(x)       x
#   define UINTMAX_C(x)      x
#   define INT8_C(x)         x
#   define INT16_C(x)        x
#   define INT32_C(x)        x
#   define INT64_C(x)        x
#   define UINT8_C(x)        x
#   define UINT16_C(x)       x
#   define UINT32_C(x)       x
#   define UINT64_C(x)       x
#endif /* !__CC__ */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDINT 1
#undef _STDINT_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDINT */
#endif /* !_STDINT_H */
