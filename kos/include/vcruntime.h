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
/* (#) Portability: MSVC (/include/vcruntime.h) */
#ifndef _VCRUNTIME_H
#define _VCRUNTIME_H 1

#include "__crt.h"
#include "__stdinc.h"
/**/

#include <hybrid/host.h>

#include <crtdefs.h>
#include <sal.h>
#include <vadefs.h>

#ifndef _UCRT
#define _UCRT
#endif /* !_UCRT */

#define _CRT_BEGIN_C_HEADER __pragma(pack(push, _CRT_PACKING)) __DECL_BEGIN
#define _CRT_END_C_HEADER   __DECL_END __pragma(pack(pop))

#ifndef _HAS_EXCEPTIONS
#ifdef _KERNEL_MODE
#define _HAS_EXCEPTIONS 0
#else /* _KERNEL_MODE */
#define _HAS_EXCEPTIONS 1
#endif /* !_KERNEL_MODE */
#endif /* !_HAS_EXCEPTIONS */

#ifndef _CRT_CONCATENATE
#define _CRT_CONCATENATE_ __PP_PRIVATE_CAT2
#define _CRT_CONCATENATE  __PP_CAT2
#endif /* !_CRT_CONCATENATE */

#ifndef _CRT_UNPARENTHESIZE
#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__
#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__
#endif /* !_CRT_UNPARENTHESIZE */

#ifndef _VCRTIMP
#define _VCRTIMP _CRTIMP
#endif /* !_VCRTIMP */

#ifndef __CLRCALL_PURE_OR_CDECL
#ifdef _M_CEE_PURE
#define __CLRCALL_PURE_OR_CDECL __ATTR_CLRCALL
#else /* _M_CEE_PURE */
#define __CLRCALL_PURE_OR_CDECL __ATTR_CDECL
#endif /* !_M_CEE_PURE */
#endif /* !__CLRCALL_PURE_OR_CDECL */

#ifndef _VCRT_NOALIAS
#if (defined(_MSC_VER) || __has_declspec_attribute(noalias))
#define _VCRT_NOALIAS __declspec(noalias)
#else /* ... */
#define _VCRT_NOALIAS /* nothing */
#endif /* !... */
#endif /* !_VCRT_NOALIAS */

#ifndef _VCRT_RESTRICT
#if (defined(_MSC_VER) || __has_declspec_attribute(restrict))
#define _VCRT_RESTRICT __declspec(restrict)
#else /* ... */
#define _VCRT_RESTRICT /* nothing */
#endif /* !... */
#endif /* !_VCRT_RESTRICT */

#ifndef _VCRT_ALLOCATOR
#if ((defined(_MSC_VER) && _MSC_VER >= 1900) || __has_declspec_attribute(allocator))
#define _VCRT_ALLOCATOR __declspec(allocator)
#else /* ... */
#define _VCRT_ALLOCATOR /* nothing */
#endif /* !... */
#endif /* !_VCRT_ALLOCATOR */

#ifndef _VCRT_JIT_INTRINSIC
#define _VCRT_JIT_INTRINSIC _CRT_JIT_INTRINSIC
#endif /* !_VCRT_JIT_INTRINSIC */

#ifndef _VCRT_ALIGN
#define _VCRT_ALIGN(x) __ATTR_ALIGNED(x)
#endif /* !_VCRT_ALIGN */

#ifndef _WConst_return
#define _WConst_return _CONST_RETURN
#endif /* !_WConst_return */

#ifdef __CC__
__DECL_BEGIN

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#endif /* !_SIZE_T_DEFINED */
#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
#endif /* !_PTRDIFF_T_DEFINED */
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__ptrdiff_t_defined */

#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED
#endif /* !_INTPTR_T_DEFINED */
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __INTPTR_TYPE__ intptr_t;
#endif /* !__intptr_t_defined */

typedef __BOOL __vcrt_bool;

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED 1
#endif  /* _WCHAR_T_DEFINED */
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif  /* __wchar_t_defined */

/* Static functions */
#ifdef _MSC_VER
#ifndef _M_CEE
extern void __ATTR_CDECL __security_init_cookie(void);
#if defined(__i386__) || defined(__x86_64__)
extern void __ATTR_FASTCALL __security_check_cookie(uintptr_t __stackcookie);
extern __ATTR_NORETURN void __ATTR_CDECL __report_gsfailure(void);
#else /* _M_IX86 */
extern void __ATTR_CDECL __security_check_cookie(uintptr_t __stackcookie);
extern __ATTR_NORETURN void __ATTR_CDECL __report_gsfailure(uintptr_t __stackcookie);
#endif
#endif /* !_M_CEE */

extern uintptr_t __security_cookie;
#endif /* _MSC_VER */

__DECL_END
#endif /* __CC__ */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#ifndef __crt_countof
#define __crt_countof __COMPILER_LENOF
#endif /* !__crt_countof */

#ifndef _VCRT_BUILD
#define __vcrt_malloc_normal(num_bytes)             malloc(num_bytes)
#define __vcrt_calloc_normal(elem_count, elem_size) calloc(elem_count, elem_size)
#define __vcrt_free_normal(ptr)                     free(ptr)
#endif /* !_VCRT_BUILD */

#endif /* !_VCRUNTIME_H */
