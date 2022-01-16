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
#ifndef _NT___WINSTD_H
#define _NT___WINSTD_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <stdarg.h>
#include <stddef.h>

#undef __cdecl
#undef _X86_
#define DUMMYUNIONNAME   /* Nothing */
#define DUMMYUNIONNAME2  /* Nothing */
#define DUMMYSTRUCTNAME  /* Nothing */
#define DUMMYSTRUCTNAME2 /* Nothing */

#if (defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__WINDOWS__) || \
     defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) ||                       \
     defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) ||              \
     defined(_WIN32_WCE) || defined(WIN32_WCE))
#undef WIN32
#undef _WIN32
#define WIN32  1
#define _WIN32 1
#if __SIZEOF_POINTER__ >= 8
#define WIN64  1
#define _WIN64 1
#endif /* __SIZEOF_POINTER__ >= 8 */
#endif /* ... */

#ifdef __x86_64__
#define _AMD64_ 1
#elif defined(__i386__)
#define _X86_ 1
#elif defined(__arm__)
#define _ARM_ 1
#elif defined(__ia64__)
#define _IA64_ 1
#endif /* ... */


#ifndef _MSC_VER
#undef __int8
#undef __int16
#undef __int32
#undef __int64
#undef __stdcall
#undef __cdecl
#undef __declspec
#undef __unaligned
#undef __fastcall
#define __int8        char
#define __int16       short
#define __int32       int
#define __int64       long long
#define __stdcall     __ATTR_STDCALL
#define __cdecl       __ATTR_CDECL
#define __declspec(x) __attribute__((x))
#define __unaligned   __ATTR_PACKED
#define __fastcall    __ATTR_FASTCALL
#define __MSVCRT__ 1
#undef _MSVCRT_
#endif /* !_MSC_VER */

#ifndef __POINTER32
#include <hybrid/__pointer.h>
#define __POINTER32 __HYBRID_PTR32
#define __POINTER64 __HYBRID_PTR64
#endif /* !__POINTER32 */

#undef UNALIGNED /* avoid redefinition warnings vs __winstd.h */
#undef UNALIGNED64
#if (defined(_MSC_VER) &&                        \
     (defined(_M_MRX000) || defined(_M_ALPHA) || \
      defined(_M_PPC) || defined(_M_IA64) ||     \
      defined(_M_AMD64)))
#define ALIGNMENT_MACHINE
#define UNALIGNED   __unaligned
#if __SIZEOF_POINTER__ >= 8
#define UNALIGNED64 __unaligned
#else /* __SIZEOF_POINTER__ >= 8 */
#define UNALIGNED64
#endif /* __SIZEOF_POINTER__ < 8 */
#else /* ... */
#undef ALIGNMENT_MACHINE
#define UNALIGNED
#define UNALIGNED64
#endif /* !... */

#ifndef RESTRICTED_POINTER
#if (defined(_M_MRX000) &&     \
     !(defined(MIDL_PASS) ||   \
       defined(RC_INVOKED)) && \
     defined(ENABLE_RESTRICTED))
#define RESTRICTED_POINTER __restrict
#else /* ... */
#define RESTRICTED_POINTER
#endif /* !... */
#endif /* !RESTRICTED_POINTER */


#ifdef __CC__
__DECL_BEGIN

#ifndef __WCHAR_DEFINED
#define __WCHAR_DEFINED 1
typedef __CHAR16_TYPE__ WCHAR;
#endif /* !__WCHAR_DEFINED */

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED 1
#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */
#endif /* !_SIZE_T_DEFINED */

#ifndef _SSIZE_T_DEFINED
#define _SSIZE_T_DEFINED 1
#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __SSIZE_TYPE__ ssize_t;
#endif /* !__ssize_t_defined */
#endif /* !_SSIZE_T_DEFINED */

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED 1
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
#endif /* !_WCHAR_T_DEFINED */

#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED 1
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__ptrdiff_t_defined */
#endif /* !_PTRDIFF_T_DEFINED */

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED 1
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __UINTPTR_TYPE__ uintptr_t;
#endif /* !__uintptr_t_defined */
#endif /* !_UINTPTR_T_DEFINED */

#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED 1
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __INTPTR_TYPE__ intptr_t;
#endif /* !__intptr_t_defined */
#endif /* !_INTPTR_T_DEFINED */

__DECL_END
#endif /* __CC__ */

#ifndef _INTEGRAL_MAX_BITS
#ifdef __UINT64_TYPE__
#define _INTEGRAL_MAX_BITS 64
#else /* __UINT64_TYPE__ */
#define _INTEGRAL_MAX_BITS 32
#endif /* !__UINT64_TYPE__ */
#endif /* !_INTEGRAL_MAX_BITS */

#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
#define _ANONYMOUS_UNION
#endif /* __COMPILER_HAVE_TRANSPARENT_UNION */
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
#define _ANONYMOUS_STRUCT
#endif /* __COMPILER_HAVE_TRANSPARENT_STRUCT */

#define __MINGW_IMPORT               __IMPDEF
#define __MINGW_ATTRIB_NORETURN      __ATTR_NORETURN
#define __MINGW_ATTRIB_CONST         __ATTR_CONST
#define __MINGW_ATTRIB_DEPRECATED    __ATTR_DEPRECATED_
#define __MINGW_ATTRIB_MALLOC        __ATTR_MALLOC
#define __MINGW_ATTRIB_PURE          __ATTR_PURE
#define __MINGW_ATTRIB_NONNULL(arg)  __NONNULL(arg)
#define __MINGW_NOTHROW              __ATTR_NOTHROW
#define __GNUC_VA_LIST               __builtin_va_list
#define _CRTIMP                      extern
#define __CRT_INLINE                 __FORCELOCAL
#define __CRT__NO_INLINE             1
#define _CRT_ALIGN(x)                __ATTR_ALIGNED(x)
#define DECLSPEC_ALIGN(x)            __ATTR_ALIGNED(x)
#define _CRT_PACKING                 8
#define __CRT_UNALIGNED
#define _CONST_RETURN
#define __CRT_STRINGIZE(_Value)      #_Value
#define _CRT_STRINGIZE(_Value)       __CRT_STRINGIZE(_Value)
#define __CRT_WIDE(_String)          L##_String
#define _CRT_WIDE(_String)           __CRT_WIDE(_String)
#define DECLSPEC_NORETURN            __ATTR_NORETURN
#define DECLARE_STDCALL_P(type)      __stdcall type
#define NOCRYPT                      1
#define NOSERVICE                    1
#define NOMCX                        1
#define NOIME                        1
#define TYPE_ALIGNMENT(t)            __COMPILER_ALIGNOF(t)

#ifndef PROBE_ALIGNMENT
#if __SIZEOF_POINTER__ >= 8
#ifdef _AMD64_
#define PROBE_ALIGNMENT(_s) TYPE_ALIGNMENT(DWORD)
#elif defined(_IA64_)
#define PROBE_ALIGNMENT(_s) (TYPE_ALIGNMENT(_s) > TYPE_ALIGNMENT(DWORD) ? TYPE_ALIGNMENT(_s) : TYPE_ALIGNMENT(DWORD))
#else /* ... */
/*#error No Target Architecture*/
#endif /* !... */
#define PROBE_ALIGNMENT32(_s) TYPE_ALIGNMENT(DWORD)
#else /* __SIZEOF_POINTER__ >= 8 */
#define PROBE_ALIGNMENT(_s) TYPE_ALIGNMENT(DWORD)
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !PROBE_ALIGNMENT */


#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else /* __cplusplus */
#define EXTERN_C extern
#endif /* !__cplusplus */
#endif /* !EXTERN_C */

#ifndef C_ASSERT
#define C_ASSERT(e) __STATIC_ASSERT(e)
#endif /* !C_ASSERT */

#ifndef DECLSPEC_IMPORT
#if defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
#define DECLSPEC_IMPORT __IMPDEF
#else
#define DECLSPEC_IMPORT
#endif
#endif /* !DECLSPEC_IMPORT */

#ifndef SYSTEM_CACHE_ALIGNMENT_SIZE
#if defined(__x86_64__) || defined(__i386__)
#define SYSTEM_CACHE_ALIGNMENT_SIZE 64
#else /* __x86_64__ || __i386__ */
#define SYSTEM_CACHE_ALIGNMENT_SIZE 128
#endif /* !__x86_64__ && !__i386__ */
#endif /* !SYSTEM_CACHE_ALIGNMENT_SIZE */

#ifndef DECLSPEC_CACHEALIGN
#define DECLSPEC_CACHEALIGN DECLSPEC_ALIGN(SYSTEM_CACHE_ALIGNMENT_SIZE)
#endif /* !DECLSPEC_CACHEALIGN */

#ifndef DECLSPEC_UUID
#define DECLSPEC_UUID(x)
#endif /* !DECLSPEC_UUID */

#ifndef DECLSPEC_NOVTABLE
#define DECLSPEC_NOVTABLE
#endif /* !DECLSPEC_NOVTABLE */

#ifndef DECLSPEC_SELECTANY
#define DECLSPEC_SELECTANY __ATTR_SELECTANY
#endif /* !DECLSPEC_SELECTANY */

#ifndef NOP_FUNCTION
#define NOP_FUNCTION (void)0
#endif /* !NOP_FUNCTION */

#ifndef DECLSPEC_NOINLINE
#define DECLSPEC_NOINLINE __ATTR_NOINLINE
#endif /* !DECLSPEC_NOINLINE */

#ifndef FORCEINLINE
#define FORCEINLINE __ATTR_FORCEINLINE
#endif /* !FORCEINLINE */

#ifndef DECLSPEC_DEPRECATED
#define DECLSPEC_DEPRECATED __ATTR_DEPRECATED_
#ifndef __NO_ATTR_DEPRECATED
#define DEPRECATE_SUPPORTED
#endif /* !__NO_ATTR_DEPRECATED */
#endif /* !DECLSPEC_DEPRECATED */

#define DECLSPEC_DEPRECATED_DDK
#define PRAGMA_DEPRECATED_DDK 0


#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1

#ifndef WINVER
#define WINVER 0x0502
#endif /* !WINVER */

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#endif /* !_WIN32_WINNT */

#endif /* !_NT___WINSTD_H */
