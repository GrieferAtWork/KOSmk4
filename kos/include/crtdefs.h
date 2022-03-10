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
/* (#) Portability: MSVC  (/include/crtdefs.h) */
/* (#) Portability: MinGW (/mingw-w64-headers/crt/crtdefs.h) */
#ifndef _INC_CRTDEFS
#define _INC_CRTDEFS 1

#include "__crt.h"
#include "__stdinc.h"
/**/

#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <bits/crt/wctype.h> /* __wctype_t */

#include <sal.h>
#include <vadefs.h>

__SYSDECL_BEGIN

#undef _CRT_PACKING
#define _CRT_PACKING 8

#ifndef _MSC_VER
/* Auto-configure _DEBUG from NDEBUG on compilers that follow the C-standard */
#ifdef NDEBUG
#undef _DEBUG
#else /* NDEBUG */
#define _DEBUG 1
#endif /* !NDEBUG */
#endif /* !_MSC_VER */


#ifndef _CRTIMP
#ifdef _DLL
#define _CRTIMP __ATTR_DLLIMPORT
#else /* _DLL */
#define _CRTIMP /* nothing */
#endif /* !_DLL */
#endif /* !_CRTIMP */

#ifndef _CRT_STRINGIZE
#define __CRT_STRINGIZE __PP_PRIVATE_STR
#define _CRT_STRINGIZE  __PP_STR
#endif /* !_CRT_STRINGIZE */

#ifndef _CRT_WIDE
#define __CRT_WIDE(str) L##str
#define _CRT_WIDE(str)  __CRT_WIDE(str)
#endif /* !_CRT_WIDE */

#ifndef _CRT_APPEND
#define __CRT_APPEND __PP_PRIVATE_CAT2
#define _CRT_APPEND  __PP_CAT2
#endif /* !_CRT_APPEND */

#ifndef _W64
#define _W64 __ATTR_W64
#endif /* !_W64 */

#ifndef _CRTIMP2
#if defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _CRTIMP2 __ATTR_DLLIMPORT
#else /* _DLL && !_STATIC_CPPLIB */
#define _CRTIMP2 /* nothing */
#endif /* !_DLL || _STATIC_CPPLIB */
#endif /* !_CRTIMP2 */

#ifndef _CRTIMP_ALTERNATIVE
#ifdef _DLL
#ifdef _CRT_ALTERNATIVE_INLINES
#define _CRTIMP_ALTERNATIVE        /* nothing */
#else /* _CRT_ALTERNATIVE_INLINES */
#define _CRTIMP_ALTERNATIVE        _CRTIMP
#define _CRT_ALTERNATIVE_IMPORTED
#endif /* !_CRT_ALTERNATIVE_INLINES */
#else /* _DLL */
#define _CRTIMP_ALTERNATIVE        /* nothing */
#endif /* !_DLL */
#endif /* !_CRTIMP_ALTERNATIVE */

#ifndef _MRTIMP
#define _MRTIMP __ATTR_DLLIMPORT
#endif /* !_MRTIMP */

#ifndef _MRTIMP2
#if defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _MRTIMP2 __ATTR_DLLIMPORT
#else /* _DLL && !_STATIC_CPPLIB */
#define _MRTIMP2 /* nothing */
#endif /* !_DLL || _STATIC_CPPLIB */
#endif /* !_MRTIMP2 */

#ifndef __CLR_OR_THIS_CALL
#ifdef _M_CEE_PURE
#define __CLR_OR_THIS_CALL __ATTR_CLRCALL
#else /* _M_CEE_PURE */
#define __CLR_OR_THIS_CALL /* nothing */
#endif /* !_M_CEE_PURE */
#endif /* !__CLR_OR_THIS_CALL */
#ifndef __CLRCALL_OR_CDECL
#ifdef _M_CEE_PURE
#define __CLRCALL_OR_CDECL __ATTR_CLRCALL
#else /* _M_CEE_PURE */
#define __CLRCALL_OR_CDECL __ATTR_CDECL
#endif /* !_M_CEE_PURE */
#endif /* !__CLRCALL_OR_CDECL */

#ifndef _CRTIMP_PURE
#if defined(_M_CEE_PURE) || defined(_STATIC_CPPLIB)
#define _CRTIMP_PURE /* nothing */
#else /* _M_CEE_PURE || _STATIC_CPPLIB */
#define _CRTIMP_PURE _CRTIMP
#endif /* !_M_CEE_PURE && !_STATIC_CPPLIB */
#endif /* !_CRTIMP_PURE */

#ifndef _PGLOBAL
#ifdef _M_CEE
#if (defined(__cplusplus_cli) && \
     (defined(_MSC_VER) || __has_declspec_attribute(process)))
#define _PGLOBAL __declspec(process)
#else /* ... */
#define _PGLOBAL /* nothing */
#endif /* !... */
#else /* _M_CEE */
#define _PGLOBAL /* nothing */
#endif /* _M_CEE */
#endif /* !_PGLOBAL */

#ifndef _AGLOBAL
#if (defined(_M_CEE) && \
     (defined(_MSC_VER) || __has_declspec_attribute(appdomain)))
#define _AGLOBAL __declspec(appdomain)
#else /* ... */
#define _AGLOBAL /* nothing */
#endif /* !... */
#endif /* !_AGLOBAL */

#ifndef _CRT_GUARDOVERFLOW
#if (defined(_GUARDOVERFLOW_CRT_ALLOCATORS) && \
     (defined(_MSC_VER) || __has_declspec_attribute(guard)))
#define _CRT_GUARDOVERFLOW __declspec(guard(overflow))
#else /* ... */
#define _CRT_GUARDOVERFLOW /* nothing */
#endif /* !... */
#endif /* !_CRT_GUARDOVERFLOW */

#ifdef _M_CEE
#ifndef _M_CEE_PURE
#define _M_CEE_MIXED 1
#endif /* !_M_CEE_PURE */
#endif /* _M_CEE */

#ifndef __STDC_SECURE_LIB__
#define __STDC_SECURE_LIB__ 200411L
#endif /* !__STDC_SECURE_LIB__ */
#ifndef __GOT_SECURE_LIB__
#define __GOT_SECURE_LIB__  __STDC_SECURE_LIB__
#endif /* !__GOT_SECURE_LIB__ */
#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__ 1
#endif /* !__STDC_WANT_SECURE_LIB__ */

#ifndef _CRT_DEPRECATE_TEXT
#define _CRT_DEPRECATE_TEXT __ATTR_DEPRECATED
#endif /* !_CRT_DEPRECATE_TEXT */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif /* !_CRT_SECURE_NO_WARNINGS */
#ifndef _CRT_INSECURE_DEPRECATE
#define _CRT_INSECURE_DEPRECATE(x)
#endif /* !_CRT_INSECURE_DEPRECATE */

#ifndef _CRT_SECURE_WARNINGS_MEMORY
#define _CRT_SECURE_WARNINGS_MEMORY 1
#endif /* !_CRT_SECURE_WARNINGS_MEMORY */
#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
#define _CRT_INSECURE_DEPRECATE_MEMORY(x)
#endif /* !_CRT_INSECURE_DEPRECATE_MEMORY */

#ifndef _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 1
#endif /* !_CRT_SECURE_NO_WARNINGS_GLOBALS */
#ifndef _CRT_INSECURE_DEPRECATE_GLOBALS
#define _CRT_INSECURE_DEPRECATE_GLOBALS(x)
#endif /* !_CRT_INSECURE_DEPRECATE_GLOBALS */

#ifndef _CRT_MANAGED_HEAP_NO_WARNINGS
#define _CRT_MANAGED_HEAP_NO_WARNINGS 1
#endif /* !_CRT_MANAGED_HEAP_NO_WARNINGS */
#ifndef _CRT_MANAGED_HEAP_DEPRECATE
#define _CRT_MANAGED_HEAP_DEPRECATE /* nothing */
#endif /* !_CRT_MANAGED_HEAP_DEPRECATE */

#ifndef _SECURECRT_FILL_BUFFER_PATTERN
#define _SECURECRT_FILL_BUFFER_PATTERN 0xFE
#endif /* !_SECURECRT_FILL_BUFFER_PATTERN */

#ifndef _CRT_OBSOLETE_NO_WARNINGS
#define _CRT_OBSOLETE_NO_WARNINGS 1
#endif /* !_CRT_OBSOLETE_NO_WARNINGS */
#ifndef _CRT_OBSOLETE
#define _CRT_OBSOLETE(x)
#endif /* !_CRT_OBSOLETE */

#ifndef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
#define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP 1
#endif /* !_CRT_USE_WINAPI_FAMILY_DESKTOP_APP */

#ifndef _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE
#define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 0
#endif /* !_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE */

#ifndef _CRT_BUILD_DESKTOP_APP
#define _CRT_BUILD_DESKTOP_APP 1
#endif  /* _CRT_BUILD_DESKTOP_APP */

#ifndef _CRT_JIT_INTRINSIC
#if (defined(_M_CEE) && defined(_M_X64) && \
     (defined(_MSC_VER) || __has_declspec_attribute(jitintrinsic)))
#define _CRT_JIT_INTRINSIC __declspec(jitintrinsic)
#else /* ... */
#define _CRT_JIT_INTRINSIC /* nothing */
#endif /* !... */
#endif /* !_CRT_JIT_INTRINSIC */

#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0
#endif /* !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES */
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0
#endif /* !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT */

#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#if __STDC_WANT_SECURE_LIB__
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#else /* __STDC_WANT_SECURE_LIB__ */
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 0
#endif /* !__STDC_WANT_SECURE_LIB__ */
#endif /* !_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES */

#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY 0
#endif /* !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY */
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY 0
#endif /* !_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY */

#ifndef _CRT_SECURE_CPP_NOTHROW
#define _CRT_SECURE_CPP_NOTHROW __CXX_NOEXCEPT
#endif /* !_CRT_SECURE_CPP_NOTHROW */

#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS 1
#endif /* !_CRT_NONSTDC_NO_WARNINGS */
#ifndef _CRT_NONSTDC_DEPRECATE
#define _CRT_NONSTDC_DEPRECATE(x)
#endif /* !_CRT_NONSTDC_DEPRECATE */

#ifndef __USE_DOS_CLEAN
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED 1
#endif /* !_SIZE_T_DEFINED */
#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if __STDC_WANT_SECURE_LIB__
#ifndef _RSIZE_T_DEFINED
#define _RSIZE_T_DEFINED 1
#endif /* !_RSIZE_T_DEFINED */
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */
#endif /* __STDC_WANT_SECURE_LIB__ */

#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED 1
#endif /* !_INTPTR_T_DEFINED */
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __INTPTR_TYPE__ intptr_t;
#endif /* !__intptr_t_defined */
#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED 1
#endif /* !_UINTPTR_T_DEFINED */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __UINTPTR_TYPE__ uintptr_t;
#endif /* !__uintptr_t_defined */
#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED 1
#endif /* !_PTRDIFF_T_DEFINED */
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__ptrdiff_t_defined */

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED 1
#endif  /* _WCHAR_T_DEFINED */
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif  /* __wchar_t_defined */
#ifndef _WCTYPE_T_DEFINED
#define _WCTYPE_T_DEFINED 1
#endif /* !_WCTYPE_T_DEFINED */
#ifndef __wint_t_defined
#define __wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined
typedef __wctype_t wctype_t;
#endif /* !__wctype_t_defined */
#ifndef _VA_LIST_DEFINED
#define _VA_LIST_DEFINED 1
#endif /* !_VA_LIST_DEFINED */
#ifndef __va_list_defined
#define __va_list_defined
typedef __builtin_va_list va_list;
#endif /* !__va_list_defined */

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED 1
#ifndef __errno_t_defined
#define __errno_t_defined
typedef int errno_t;
#endif /* !__errno_t_defined */
#endif /* !_ERRNO_T_DEFINED */
#endif /* !__USE_DOS_CLEAN */

#ifndef _TIME32_T_DEFINED
#define _TIME32_T_DEFINED 1
/* Defined in <bits/types.h> */
#endif /* !_TIME32_T_DEFINED */

#ifndef _TIME64_T_DEFINED
#define _TIME64_T_DEFINED 1
/* Defined in <bits/types.h> */
#endif /* !_TIME64_T_DEFINED */


#ifndef __USE_DOS_CLEAN
#undef _USE_32BIT_TIME_T
#ifndef __USE_TIME_BITS64
#define _USE_32BIT_TIME_T 1
#endif /* !__USE_TIME_BITS64 */

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED 1
#ifndef __time_t_defined
#define __time_t_defined
#ifdef _USE_32BIT_TIME_T
typedef __time32_t time_t;
#else /* _USE_32BIT_TIME_T */
typedef __time64_t time_t;
#endif /* _USE_32BIT_TIME_T */
#endif /* !__time_t_defined */
#endif /* !_TIME_T_DEFINED */
#endif /* !__USE_DOS_CLEAN */

#ifndef _CONST_RETURN
#ifdef __cplusplus
#define _CONST_RETURN const
#define _CRT_CONST_CORRECT_OVERLOADS 1
#else /* __cplusplus */
#define _CONST_RETURN /* nothing */
#endif /* !__cplusplus */
#endif /* !_CONST_RETURN */

#ifndef _UNALIGNED
#if defined(_M_X64) || defined(_M_ARM)
#define _UNALIGNED __unaligned /* XXX: Compiler-independent? */
#else /* _M_X64 || _M_ARM */
#define _UNALIGNED /* nothing */
#endif /* !_M_X64 && !_M_ARM */
#endif /* !_UNALIGNED */

#ifndef _CRT_ALIGN
#define _CRT_ALIGN   __ATTR_ALIGNED
#endif /* !_CRT_ALIGN */
#ifndef _CRTNOALIAS
#define _CRTNOALIAS  __ATTR_PURE
#endif /* !_CRTNOALIAS */
#ifndef _CRTRESTRICT
#define _CRTRESTRICT __ATTR_MALLOC
#endif /* !_CRTRESTRICT */

#ifndef __CRTDECL
#ifdef _M_CEE_PURE
#define __CRTDECL /* nothing */
#elif defined(__NO_ATTR_CDECL)
#define __CRTDECL __ATTR_MSABI
#else /* _M_CEE_PURE */
#define __CRTDECL __ATTR_CDECL
#endif /* !_M_CEE_PURE */
#endif /* !__CRTDECL */

#ifndef _STR2WSTR
#define __STR2WSTR(str) L##str
#define _STR2WSTR(str)  __STR2WSTR(str)
#endif /* !_STR2WSTR */
#ifndef __FILEW__
#define __FILEW__ _STR2WSTR(__FILE__)
#endif /* !__FILEW__ */
#ifndef __FUNCTIONW__
#define __FUNCTIONW__ _STR2WSTR(__FUNCTION__)
#endif /* !__FUNCTIONW__ */

#ifdef __CC__
#ifdef _DEBUG
#ifdef __CRT_HAVE__invalid_parameter
_CRTIMP void (__ATTR_CDECL _invalid_parameter)(__WCHAR16_TYPE__ const *,
                                               __WCHAR16_TYPE__ const *,
                                               __WCHAR16_TYPE__ const *,
                                               unsigned int, __UINTPTR_TYPE__);
#else /* __CRT_HAVE__invalid_parameter */
__LOCAL void (__ATTR_CDECL _invalid_parameter)(__WCHAR16_TYPE__ const *__UNUSED(__a),
                                               __WCHAR16_TYPE__ const *__UNUSED(__b),
                                               __WCHAR16_TYPE__ const *__UNUSED(__c),
                                               unsigned int __UNUSED(__d),
                                               __UINTPTR_TYPE__ __UNUSED(__e)) {}
#endif /* !__CRT_HAVE__invalid_parameter */
#else /* _DEBUG */
#ifdef __CRT_HAVE__invalid_parameter_noinfo
_CRTIMP void (__ATTR_CDECL _invalid_parameter_noinfo)(void);
#else /* __CRT_HAVE__invalid_parameter_noinfo */
__LOCAL void (__ATTR_CDECL _invalid_parameter_noinfo)(void) {}
#endif /* !__CRT_HAVE__invalid_parameter_noinfo */
#ifdef __CRT_HAVE__invalid_parameter_noinfo_noreturn
_CRTIMP __ATTR_NORETURN void (__ATTR_CDECL _invalid_parameter_noinfo_noreturn)(void);
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,_invalid_parameter_noinfo_noreturn,(void),_Exit,())
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,_invalid_parameter_noinfo_noreturn,(void),_exit,())
#else
__LOCAL __ATTR_NORETURN void (__ATTR_CDECL _invalid_parameter_noinfo_noreturn)(void) { for (;;) {} }
#endif
#endif  /* _DEBUG */
#ifdef __CRT_HAVE__invoke_watson
_CRTIMP __ATTR_NORETURN void
(__ATTR_CDECL _invoke_watson)(__WCHAR16_TYPE__ const *,
                              __WCHAR16_TYPE__ const *,
                              __WCHAR16_TYPE__ const *,
                              unsigned int, __UINTPTR_TYPE__);
#else /* __CRT_HAVE__invoke_watson */
__LOCAL __ATTR_NORETURN void
(__ATTR_CDECL _invoke_watson)(__WCHAR16_TYPE__ const *__UNUSED(__a),
                              __WCHAR16_TYPE__ const *__UNUSED(__b),
                              __WCHAR16_TYPE__ const *__UNUSED(__c),
                              unsigned int __UNUSED(__d),
                              __UINTPTR_TYPE__ __UNUSED(__e)) {
	for (;;) {
	}
}
#endif /* !__CRT_HAVE__invoke_watson */

#ifndef _CRT_SECURE_INVALID_PARAMETER
#ifdef _DEBUG
#define _CRT_SECURE_INVALID_PARAMETER(expr) \
	_invalid_parameter(__STR2WSTR(#expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)
#else /* _DEBUG */
#define _CRT_SECURE_INVALID_PARAMETER(expr) \
	_invalid_parameter_noinfo_noreturn()
#endif /* !_DEBUG */
#endif /* !_CRT_SECURE_INVALID_PARAMETER */
#endif /* __CC__ */

#ifndef _ARGMAX
#define _ARGMAX 100
#endif /* !_ARGMAX */

#ifndef _TRUNCATE
#define _TRUNCATE ((__SIZE_TYPE__)-1)
#endif /* !_TRUNCATE */

#define __RETURN_POLICY_SAME(fcall) /* nothing */
#define __RETURN_POLICY_DST(fcall)  /* nothing */
#define __RETURN_POLICY_VOID(fcall) /* nothing */
#define __EMPTY_DECLSPEC            /* nothing */

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(return_type, name, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(return_type, name, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(return_type, name, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(return_type, name, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(return_type, name, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(return_type, name, ht1, ha1, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(return_type, name, ht1, ha1, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(return_type, name, ht1, ha1, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(return_type, name, ht1, ha1, ht2, ha2, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(return_type, name, vname, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(return_type, name, vname, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(return_type, name, dsttype, _Src)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(return_type, return_pol, attr, name, destattr, dsttype, dst) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(return_type, return_pol, attr, name, name##_s, destattr, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(return_type, return_pol, attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(return_type, return_pol, attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(return_type, return_pol, attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(return_type, return_pol, attr, name, name##_s, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(return_type, return_pol, attr, name, ht1, ha1, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(return_type, return_pol, attr, name, name##_s, ht1, ha1, destattr, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(return_type, return_pol, attr, name, ht1, ha1, ht2, ha2, destattr, dsttype, dst) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(return_type, return_pol, attr, name, name##_s, ht1, ha1, ht2, ha2, destattr, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(return_type, return_pol, attr, name, vname, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, name##_s, vname, vname##_s, destattr, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(return_type, return_pol, attr, name, vname, destattr, dsttype, dst, t1, a1, t2, a2) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(return_type, return_pol, attr, name, vname, vname##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE(attr, name, destattr, dsttype, dst, t1, a1, t2, a2) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE(attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0(return_type, return_pol, attr, name, destattr, dsttype, dst) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(return_type, return_pol, attr, name, name##_s, destattr, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(return_type, return_pol, attr, name, name##_s, destattr, dsttype, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(return_type, return_pol, attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(return_type, return_pol, attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4(return_type, return_pol, attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(return_type, return_pol, attr, name, name##_s, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1(return_type, return_pol, attr, name, ht1, ha1, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(return_type, return_pol, attr, name, name##_s, ht1, ha1, destattr, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0(return_type, return_pol, attr, name, ht1, ha1, ht2, ha2, destattr, dsttype, dst) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(return_type, return_pol, attr, name, name##_s, ht1, ha1, ht2, ha2, destattr, dsttype, dst)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST(return_type, return_pol, attr, name, vname, destattr, dsttype, dst, t1, a1) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, name##_s, vname, vname##_s, destattr, dsttype, dst, t1, a1)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(attr, name, destattr, dsttype, dst, t1, a1, t2, a2) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE(attr, name, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(attr, name, name##_s, dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#ifdef __CC__
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst) \
	attr return_type __cdecl name(destattr dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(return_type, attr, name, destattr, dsttype, dst) \
	attr return_type __cdecl name(destattr dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3, t4 a4);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(return_type, return_pol, attr, name, secname, ht1, ha1, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(ht1 ha1, destattr dsttype *dst, t1 a1);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(return_type, return_pol, attr, name, secname, ht1, ha1, ht2, ha2, destattr, dsttype, dst) \
	attr return_type __cdecl name(ht1 ha1, ht2 ha2, destattr dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, secname, vname, _SecureVFuncName, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, ...);                                                                                             \
	attr return_type __cdecl vname(destattr dsttype *dst, t1 a1, va_list __args);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(return_type, return_pol, attr, name, vname, _SecureVFuncName, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, ...);                                                                                                  \
	attr return_type __cdecl vname(destattr dsttype *dst, t1 a1, t2 a2, va_list __args);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr __SIZE_TYPE__ __cdecl name(destattr dsttype *dst, t1 a1, t2 a2);
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	attr __SIZE_TYPE__ __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst) \
	attr return_type __cdecl name(destattr dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(return_type, return_pol, attr, name, dsttype, dst) \
	attr return_type __cdecl name(dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3, t4 a4);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(return_type, return_pol, attr, name, secname, ht1, ha1, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(ht1 ha1, destattr dsttype *dst, t1 a1);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(return_type, return_pol, attr, name, secname, ht1, ha1, ht2, ha2, destattr, dsttype, dst) \
	attr return_type __cdecl name(ht1 ha1, ht2 ha2, destattr dsttype *dst);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, secname, vname, _SecureVFuncName, destattr, dsttype, dst, t1, a1) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, ...);                                                                                              \
	attr return_type __cdecl vname(destattr dsttype *dst, t1 a1, va_list __args);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(return_type, return_pol, attr, name, vname, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, ...);                                                                 \
	attr return_type __cdecl vname(destattr dsttype *dst, t1 a1, t2 a2, va_list __args);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(return_type, return_pol, attr, name, vname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr return_type __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, ...);                                                                                 \
	attr return_type __cdecl vname(destattr dsttype *dst, t1 a1, t2 a2, va_list __args);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) \
	attr __SIZE_TYPE__ __cdecl name(destattr dsttype *dst, t1 a1, t2 a2);
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	attr __SIZE_TYPE__ __cdecl name(destattr dsttype *dst, t1 a1, t2 a2, t3 a3);
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst) \
	__LOCAL return_type __CRTDECL name(dsttype *dst)
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1)
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1, t2 a2)
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1, t2 a2, t3 a3)
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst) \
	__LOCAL return_type __CRTDECL name(dsttype *dst)
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1)
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1, t2 a2)
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2, t3, a3) \
	__LOCAL return_type __CRTDECL name(dsttype *dst, t1 a1, t2 a2, t3 a3)
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)
#else /* __CC__ */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst)                                                      /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(return_type, attr, name, destattr, dsttype, dst)                                                                        /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1)                                 /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                         /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                 /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4)                      /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(return_type, return_pol, attr, name, secname, ht1, ha1, destattr, dsttype, dst, t1, a1)                                    /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(return_type, return_pol, attr, name, secname, ht1, ha1, ht2, ha2, destattr, dsttype, dst)                                  /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, secname, vname, _SecureVFuncName, destattr, dsttype, dst, t1, a1)             /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(return_type, return_pol, attr, name, vname, _SecureVFuncName, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2) /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                                             /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                                     /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst)                                                     /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(return_type, return_pol, attr, name, dsttype, dst)                                                                      /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1)                                /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                        /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(return_type, return_pol, attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(return_type, return_pol, attr, name, secname, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3, t4, a4)                     /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(return_type, return_pol, attr, name, secname, ht1, ha1, destattr, dsttype, dst, t1, a1)                                   /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(return_type, return_pol, attr, name, secname, ht1, ha1, ht2, ha2, destattr, dsttype, dst)                                 /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(return_type, return_pol, attr, name, secname, vname, _SecureVFuncName, destattr, dsttype, dst, t1, a1)            /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(return_type, return_pol, attr, name, vname, destattr, dsttype, dst, t1, a1, t2, a2)                                  /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(return_type, return_pol, attr, name, vname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                  /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                                            /* nothing */
#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(attr, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                                    /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)                                                          /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)                                                           /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)                                                  /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)                                                   /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2)                                          /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                                 /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2, t3, a3)                                  /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                         /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)                                                         /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst)                                                          /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)                                                 /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1)                                                  /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2)                                         /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2)                                /* nothing */
#define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, dsttype, dst, t1, a1, t2, a2, t3, a3)                                 /* nothing */
#define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(return_type, return_pol, name, secname, sec_dsttype, destattr, dsttype, dst, t1, a1, t2, a2, t3, a3)                        /* nothing */
#endif /* !__CC__ */


#if defined(__CRT_DOS) && !defined(__CRT_KOS)
#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(push,_CRT_PACKING)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("threadlocaleinfostruct")
#pragma push_macro("threadmbcinfostruct")
#pragma push_macro("pthreadlocinfo")
#pragma push_macro("pthreadmbcinfo")
#pragma push_macro("localeinfo_struct")
#pragma push_macro("locinfo")
#pragma push_macro("mbcinfo")
#pragma push_macro("_locale_tstruct")
#pragma push_macro("_locale_t")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef threadlocaleinfostruct
#undef threadmbcinfostruct
#undef pthreadlocinfo
#undef pthreadmbcinfo
#undef localeinfo_struct
#undef locinfo
#undef mbcinfo
#undef _locale_tstruct
#undef _locale_t

struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;
typedef struct localeinfo_struct {
	pthreadlocinfo locinfo;
	pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;

#ifndef _THREADLOCALEINFO
#define _THREADLOCALEINFO 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("localerefcount")
#pragma push_macro("locale")
#pragma push_macro("wlocale")
#pragma push_macro("refcount")
#pragma push_macro("wrefcount")
#pragma push_macro("locrefcount")
#pragma push_macro("lc_codepage")
#pragma push_macro("lc_collate_cp")
#pragma push_macro("lc_time_cp")
#pragma push_macro("lc_category")
#pragma push_macro("lc_clike")
#pragma push_macro("mb_cur_max")
#pragma push_macro("lconv_intl_refcount")
#pragma push_macro("lconv_num_refcount")
#pragma push_macro("lconv_mon_refcount")
#pragma push_macro("lconv")
#pragma push_macro("ctype1_refcount")
#pragma push_macro("ctype1")
#pragma push_macro("pctype")
#pragma push_macro("pclmap")
#pragma push_macro("pcumap")
#pragma push_macro("lc_time_curr")
#pragma push_macro("locale_name")
#pragma push_macro("threadlocinfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef localerefcount
#undef locale
#undef wlocale
#undef refcount
#undef wrefcount
#undef locrefcount
#undef lc_codepage
#undef lc_collate_cp
#undef lc_time_cp
#undef lc_category
#undef lc_clike
#undef mb_cur_max
#undef lconv_intl_refcount
#undef lconv_num_refcount
#undef lconv_mon_refcount
#undef lconv
#undef ctype1_refcount
#undef ctype1
#undef pctype
#undef pclmap
#undef pcumap
#undef lc_time_curr
#undef locale_name
#undef threadlocinfo

typedef struct localerefcount {
	char             *locale;
	__WCHAR16_TYPE__ *wlocale;
	int              *refcount;
	int              *wrefcount;
} locrefcount;
typedef struct threadlocaleinfostruct {
	int                    refcount;
	unsigned int           lc_codepage;
	unsigned int           lc_collate_cp;
	unsigned int           lc_time_cp;
	locrefcount            lc_category[6];
	int                    lc_clike;
	int                    mb_cur_max;
	int                   *lconv_intl_refcount;
	int                   *lconv_num_refcount;
	int                   *lconv_mon_refcount;
	struct lconv          *lconv;
	int                   *ctype1_refcount;
	__UINT16_TYPE__       *ctype1;
	__UINT16_TYPE__ const *pctype;
	__UINT8_TYPE__ const  *pclmap;
	__UINT8_TYPE__ const  *pcumap;
	struct __lc_time_data *lc_time_curr;
	__WCHAR16_TYPE__      *locale_name[6];
} threadlocinfo;
#endif /* !_THREADLOCALEINFO */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_locale_t")
#pragma pop_macro("_locale_tstruct")
#pragma pop_macro("mbcinfo")
#pragma pop_macro("locinfo")
#pragma pop_macro("localeinfo_struct")
#pragma pop_macro("pthreadmbcinfo")
#pragma pop_macro("pthreadlocinfo")
#pragma pop_macro("threadmbcinfostruct")
#pragma pop_macro("threadlocaleinfostruct")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(pop)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */
#endif /* __CRT_DOS && !__CRT_KOS */

#ifndef _Check_return_opt_
#if defined(_PREFAST_) && defined(_CA_SHOULD_CHECK_RETURN)
#define _Check_return_opt_ _Check_return_
#else /* _PREFAST_ && _CA_SHOULD_CHECK_RETURN */
#define _Check_return_opt_ /* nothing */
#endif /* !_PREFAST_ || !_CA_SHOULD_CHECK_RETURN */
#endif /* !_Check_return_opt_ */

#ifndef _Check_return_wat_
#if defined(_PREFAST_) && defined(_CA_SHOULD_CHECK_RETURN_WER)
#define _Check_return_wat_ _Check_return_
#else /* _PREFAST_ && _CA_SHOULD_CHECK_RETURN_WER */
#define _Check_return_wat_ /* nothing */
#endif /* !_PREFAST_ || !_CA_SHOULD_CHECK_RETURN_WER */
#endif /* !_Check_return_wat_ */

#ifndef __crt_typefix
#if defined(_MSC_VER) && (!defined(__midl) && !defined(MIDL_PASS) && defined(_PREFAST_))
#define __crt_typefix(ctype) __declspec("SAL_typefix(" __CRT_STRINGIZE(ctype) ")")
#else /* ... */
#define __crt_typefix(ctype)
#endif /* !... */
#endif /* !__crt_typefix */

#ifdef __midl
#ifndef _NO_INLINING
#define _NO_INLINING 1
#endif /* !_NO_INLINING */
#endif /* __midl */

#ifndef _CRT_UNUSED
#define _CRT_UNUSED(x) (void)x
#endif /* !_CRT_UNUSED */

__SYSDECL_END

#endif /* !_INC_CRTDEFS */
