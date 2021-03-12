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
#ifndef __PP_STR
#include "pp-generic.h"
#endif /* !__PP_STR */

#ifndef __option
#define __option(x) 0
#endif /* !__option */

#ifndef __has_builtin
#define __NO_has_builtin
#define __has_builtin(x) 0
#endif /* !__has_builtin */

#ifndef __has_feature
#define __NO_has_feature
#define __has_feature(x) 0
#endif /* !__has_feature */

#ifndef __has_extension
#ifndef __NO_has_feature
#define __NO_has_extension
#endif /* !__NO_has_feature */
#define __has_extension __has_feature
#endif /* !__has_extension */

#ifndef __has_attribute
#define __NO_has_attribute
#define __has_attribute(x) 0
#endif /* !__has_attribute */

#ifndef __has_declspec_attribute
#define __NO_has_declspec_attribute
#define __has_declspec_attribute(x) 0
#endif /* !__has_declspec_attribute */

#ifndef __has_cpp_attribute
#define __NO_has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif /* !__has_cpp_attribute */

#ifndef __has_include
#define __NO_has_include
#define __has_include(x) 0
#endif /* !__has_include */

#ifndef __has_include_next
#define __NO_has_include_next
#define __has_include_next(x) 0
#endif /* !__has_include */


#if (__has_builtin(__builtin_expect) || \
     (defined(__INTEL_VERSION__) && __INTEL_VERSION__ >= 800))
#define __likely(x)   (__builtin_expect(!!(x), 1))
#define __unlikely(x) (__builtin_expect(!!(x), 0))
#else /* ... */
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#endif /* !... */

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ + 0) >= 201112L || \
     __has_feature(c_generic_selections) ||                            \
     __has_extension(c_generic_selections))
#define __COMPILER_HAVE_C11_GENERIC
#endif /* __STDC_VERSION__ >= 201112L */

#if __has_builtin(__builtin_choose_expr)
/* Already a builtin. */
#elif defined(__COMPILER_HAVE_C11_GENERIC)
/* Use C11's _Generic keyword. */
#define __builtin_choose_expr(c, tt, ff) \
	_Generic((char(*)[1+!!(c)])0, char(*)[1]:(ff), default:(tt))
#else /* ... */
#define __NO_builtin_choose_expr
#define __builtin_choose_expr(c, tt, ff) ((c) ? (tt) : (ff))
#endif /* !... */

#if !__has_builtin(__builtin_types_compatible_p)
#define __NO_builtin_types_compatible_p
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __builtin_types_compatible_p(...) 1
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __builtin_types_compatible_p(types...) 1
#else /* ... */
#define __builtin_types_compatible_p(T1, T2) 1
#endif /* !... */
#endif /* !__has_builtin(__builtin_types_compatible_p) */

#ifdef __STDC__
#define __P(x) x
#else /* __STDC__ */
#define __NO_PROTOTYPES
#define __P(x) ()
#endif /* !__STDC__ */

#if (!defined(__NO_LONG_LONG) && !defined(__DARWIN_NO_LONG_LONG) &&               \
     ((defined(__BORLANDC__) && __BORLANDC__ >= 0x561) || defined(__SUNPRO_CC) || \
      defined(__TINYC__) || defined(__DCC_VERSION__) ||                           \
      defined(__CODEGEARC__) || defined(__DMC__) ||                               \
      (defined(__HP_aCC) && __HP_aCC + 0 >= 33900) ||                             \
      (defined(__PGIC__) && __PGIC__ + 0 >= 10)))
#define __COMPILER_HAVE_LONGLONG
#endif /* long long... */
#define __COMPILER_HAVE_LONGDOUBLE
#ifndef __LONGDOUBLE
#define __LONGDOUBLE long double
#endif /* !__LONGDOUBLE */
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#define __COMPILER_HAVE_TRANSPARENT_UNION

#if defined(__DCC_VERSION__) || defined(__TINYC__)
#define __COMPILER_HAVE_GCC_ASM
#define __COMPILER_HAVE_PRAGMA_PACK /* XXX: So many more compilers support this... */
#elif defined(_PUSHPOP_SUPPORTED)
#define __COMPILER_HAVE_PRAGMA_PACK
#endif /* ... */

#if __has_feature(__tpp_pragma_push_macro__) || \
    (defined(__TPP_VERSION__) && __TPP_VERSION__ == 103)
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
#endif /* #pragma push_macro(...) */

#if __has_feature(__tpp_pragma_deprecated__)
#define __COMPILER_HAVE_PRAGMA_DEPRECATED
#endif /* #pragma deprecated(...) */

#if defined(__DCC_VERSION__)
#define __COMPILER_HAVE_AUTOTYPE
#elif __has_feature(cxx_auto_type)
#define __auto_type auto
#define __COMPILER_HAVE_AUTOTYPE
#endif /* ... */

#if defined(__DCC_VERSION__) || defined(__TINYC__)
#define __COMPILER_HAVE_TYPEOF
#endif /* __DCC_VERSION__ || __TINYC__ */

#if defined(__BORLANDC__) && __BORLANDC__ >= 0x599
#pragma defineonoption __CODEGEAR_0X_SUPPORT__ -Ax
#endif /* __BORLANDC__ >= 0x599 */

#if (__has_feature(cxx_static_assert) ||                                                           \
     (defined(__cpp_static_assert) && __cpp_static_assert + 0 != 0) ||                             \
     (defined(__IBMCPP_STATIC_ASSERT) && __IBMCPP_STATIC_ASSERT + 0) ||                            \
     (defined(__cplusplus) &&                                                                      \
      ((defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ + 0 >= 0x610) || \
       (defined(__CODEGEARC__) && __CODEGEARC__ + 0 > 0x620))))
#define __STATIC_ASSERT_IS_STATIC_ASSERT
#if defined(__cpp_static_assert) && __cpp_static_assert + 0 >= 201411
#define __STATIC_ASSERT static_assert
#else /* __cpp_static_assert >= 201411 */
#define __STATIC_ASSERT(expr) static_assert(expr, #expr)
#endif /* __cpp_static_assert < 201411 */
#define __STATIC_ASSERT_MSG static_assert
#elif (defined(_Static_assert) || __has_feature(c_static_assert) || \
       (!defined(__cplusplus) && ((defined(__STDC_VERSION__) && __STDC_VERSION__ + 0 >= 201112L))))
#define __STATIC_ASSERT_IS__STATIC_ASSERT
#define __STATIC_ASSERT(expr) _Static_assert(expr, #expr)
#define __STATIC_ASSERT_MSG   _Static_assert
#elif defined(__TPP_COUNTER)
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#elif defined(__COUNTER__)
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#else /* ... */
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#endif /* !... */

#if defined(__DCC_VERSION__) || defined(__TINYC__)
#define __ASMNAME(x) __asm__(x)
#else /* __DCC_VERSION__ || __TINYC__ */
#define __NO_ASMNAME
#define __ASMNAME(x) /* Nothing */
#endif /* !__DCC_VERSION__ && !__TINYC__ */

#ifndef __DCC_VERSION__
#define __extension__
#endif /* !__DCC_VERSION__ */

#if !__has_builtin(__builtin_LINE)
#define __builtin_LINE() __LINE__
#endif /* !__has_builtin(__builtin_LINE) */

#if !__has_builtin(__builtin_FILE)
#define __builtin_FILE() __FILE__
#endif /* !__has_builtin(__builtin_FILE) */

#if !__has_builtin(__builtin_FUNCTION)
#if defined(__DCC_VERSION__) || defined(__FUNCTION__)
#define __builtin_FUNCTION() __FUNCTION__
#elif defined(__TINYC__) || 1
#define __FUNCTION__ __func__
#define __builtin_FUNCTION() __func__
#define __builtin_FUNCTION_IS_func__
#else /* ... */
#define __NO_builtin_FUNCTION
#define __builtin_FUNCTION() (char *)0
#define __FUNCTION__ ""
#endif /* !... */
#endif /* !__has_builtin(__builtin_FUNCTION) */

#if __has_attribute(__noinline__)
#define __ATTR_NOINLINE __attribute__((__noinline__))
#elif __has_declspec_attribute(noinline)
#define __ATTR_NOINLINE __declspec(noinline)
#else /* ... */
#define __NO_ATTR_NOINLINE
#define __ATTR_NOINLINE /* Nothing */
#endif /* !... */

#if __has_attribute(__noreturn__) || defined(__TINYC__)
#define __ATTR_NORETURN __attribute__((__noreturn__))
#elif __has_declspec_attribute(noreturn)
#define __ATTR_NORETURN __declspec(noreturn)
#elif (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#define __ATTR_NORETURN __attribute__((noreturn))
#elif defined(_Noreturn) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112)
#define __ATTR_NORETURN_IS__NORETURN
#define __ATTR_NORETURN _Noreturn
#elif __has_cpp_attribute(noreturn)
#undef noreturn
#define __ATTR_NORETURN [[noreturn]]
#elif defined(noreturn)
#define __ATTR_NORETURN_IS_NORETURN
#define __ATTR_NORETURN noreturn
#elif !defined(__KOS_SYSTEM_HEADERS__)
#ifdef __NO_has_include
#include <stdnoreturn.h>
#define __ATTR_NORETURN_IS_NORETURN
#define __ATTR_NORETURN noreturn
#else /* __NO_has_include */
#if __has_include(<stdnoreturn.h>)
#include <stdnoreturn.h>
#define __ATTR_NORETURN_IS_NORETURN
#define __ATTR_NORETURN noreturn
#endif /* __has_include(<stdnoreturn.h>) */
#endif /* !__NO_has_include */
#ifndef __ATTR_NORETURN
#define __NO_ATTR_NORETURN
#define __ATTR_NORETURN /* Nothing */
#endif /* !__ATTR_NORETURN */
#else /* ... */
#define __NO_ATTR_NORETURN
#define __ATTR_NORETURN /* Nothing */
#endif /* !... */

#if defined(__cplusplus) && __has_cpp_attribute(fallthrough)
#define __ATTR_FALLTHROUGH [[fallthrough]];
#elif __has_attribute(fallthrough)
#define __ATTR_FALLTHROUGH __attribute__((__fallthrough__));
#else /* ... */
#define __NO_ATTR_FALLTHROUGH
#define __ATTR_FALLTHROUGH /* Nothing */
#endif /* !... */

#define __NO_ATTR_W64
#define __ATTR_W64 /* Nothing */

#if __has_attribute(__fastcall__) || defined(__TINYC__)
#define __ATTR_FASTCALL __attribute__((__fastcall__))
#elif defined(__fastcall)
#define __ATTR_FASTCALL_IS___FASTCALL
#define __ATTR_FASTCALL __fastcall
#else /* ... */
#define __NO_ATTR_FASTCALL
#define __ATTR_FASTCALL /* Nothing */
#endif /* !... */

#if __has_attribute(__stdcall__) || defined(__TINYC__)
#define __ATTR_STDCALL __attribute__((__stdcall__))
#elif defined(__stdcall)
#define __ATTR_STDCALL_IS___STDCALL
#define __ATTR_STDCALL __stdcall
#else /* ... */
#define __NO_ATTR_STDCALL
#define __ATTR_STDCALL /* Nothing */
#endif /* !... */

#if __has_attribute(__cdecl__) || defined(__TINYC__)
#define __ATTR_CDECL __attribute__((__cdecl__))
#elif defined(__cdecl)
#define __ATTR_CDECL_IS___CDECL
#define __ATTR_CDECL __cdecl
#else /* ... */
#define __NO_ATTR_CDECL
#define __ATTR_CDECL /* Nothing */
#endif /* !... */

#if __has_attribute(__clrcall__)
#define __ATTR_CLRCALL __attribute__((__clrcall__))
#elif defined(__clrcall)
#define __ATTR_CLRCALL_IS___CLRCALL
#define __ATTR_CLRCALL __clrcall
#else /* ... */
#define __NO_ATTR_CLRCALL
#define __ATTR_CLRCALL /* Nothing */
#endif /* !... */

#if __has_attribute(__thiscall__)
#define __ATTR_THISCALL __attribute__((__thiscall__))
#elif defined(__thiscall)
#define __ATTR_THISCALL_IS___THISCALL
#define __ATTR_THISCALL __thiscall
#else /* ... */
#define __NO_ATTR_THISCALL
#define __ATTR_THISCALL /* Nothing */
#endif /* !... */

#if __has_attribute(__ms_abi__) || defined(__TINYC__)
#define __ATTR_MSABI __attribute__((__ms_abi__))
#elif defined(__ms_abi)
#define __ATTR_MSABI_IS___MS_ABI
#define __ATTR_MSABI __ms_abi
#else /* ... */
#define __NO_ATTR_MSABI
#define __ATTR_MSABI /* Nothing */
#endif /* !... */

#if __has_attribute(__sysv_abi__) || defined(__TINYC__)
#define __ATTR_SYSVABI __attribute__((__sysv_abi__))
#elif defined(__sysv_abi)
#define __ATTR_SYSVABI_IS___SYSV_ABI
#define __ATTR_SYSVABI __sysv_abi
#else /* ... */
#define __NO_ATTR_SYSVABI
#define __ATTR_SYSVABI /* Nothing */
#endif /* !... */

#if __has_attribute(__leaf__)
#define __ATTR_LEAF __attribute__((__leaf__))
#else /* ... */
#define __NO_ATTR_LEAF
#define __ATTR_LEAF /* Nothing */
#endif /* !... */

#if __has_attribute(__pure__)
#define __ATTR_PURE __attribute__((__pure__))
#elif __has_declspec_attribute(noalias)
#define __ATTR_PURE __declspec(noalias)
#elif !defined(__NO_ATTR_LEAF)
#define __ATTR_PURE __ATTR_LEAF
#else /* ... */
#define __NO_ATTR_PURE
#define __ATTR_PURE /* Nothing */
#endif /* !... */

#if __has_attribute(__const__)
#define __ATTR_CONST __attribute__((__const__))
#elif !defined(__NO_ATTR_PURE)
#define __ATTR_CONST __ATTR_PURE
#elif !defined(__NO_ATTR_LEAF)
#define __ATTR_CONST __ATTR_LEAF
#else /* ... */
#define __NO_ATTR_CONST
#define __ATTR_CONST /* Nothing */
#endif /* !... */

#if __has_attribute(__flatten__)
#define __ATTR_FLATTEN __attribute__((__flatten__))
#else /* ... */
#define __NO_ATTR_FLATTEN
#define __ATTR_FLATTEN /* Nothing */
#endif /* !... */

#if __has_attribute(__malloc__)
#define __ATTR_MALLOC __attribute__((__malloc__))
#else /* ... */
#define __NO_ATTR_MALLOC
#define __ATTR_MALLOC /* Nothing */
#endif /* !... */

#if __has_attribute(__hot__)
#define __ATTR_HOT __attribute__((__hot__))
#else /* ... */
#define __NO_ATTR_HOT
#define __ATTR_HOT /* Nothing */
#endif /* !... */

#if __has_attribute(__cold__) || (defined(__ICC) && (__ICC+0) > 1110)
#define __ATTR_COLD __attribute__((__cold__))
#else /* ... */
#define __NO_ATTR_COLD
#define __ATTR_COLD /* Nothing */
#endif /* !... */

#if __has_attribute(__alloc_size__)
#define __ATTR_ALLOC_SIZE(ppars) __attribute__((__alloc_size__ ppars))
#else /* ... */
#define __NO_ATTR_ALLOC_SIZE
#define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#endif /* !... */

#if __has_attribute(__alloc_align__)
#define __ATTR_ALLOC_ALIGN(pari) __attribute__((__alloc_align__(pari)))
#else /* ... */
#define __NO_ATTR_ALLOC_ALIGN
#define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
#endif /* !... */

#if __has_attribute(__assume_aligned__)
#define __ATTR_ASSUME_ALIGNED(n) __attribute__((__assume_aligned__(n)))
#else /* ... */
#define __NO_ATTR_ASSUME_ALIGNED
#define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#endif /* !... */

#if __has_attribute(__noclone__)
#define __ATTR_NOCLONE __attribute__((__noclone__))
#else /* ... */
#define __NO_ATTR_NOCLONE
#define __ATTR_NOCLONE /* Nothing */
#endif /* !... */

#if __has_attribute(__used__)
#define __ATTR_USED __attribute__((__used__))
#else /* ... */
#define __NO_ATTR_USED
#define __ATTR_USED /* Nothing */
#endif /* !... */

#if __has_attribute(__unused__)
#define __ATTR_UNUSED __attribute__((__unused__))
#else /* ... */
#define __NO_ATTR_UNUSED
#define __ATTR_UNUSED /* Nothing */
#endif /* !... */

#if __has_attribute(__sentinel__)
#define __ATTR_SENTINEL __attribute__((__sentinel__))
#ifdef __INTELLISENSE__
#define __ATTR_SENTINEL_O(x) __attribute__((__sentinel__))
#else /* __INTELLISENSE__ */
#define __ATTR_SENTINEL_O(x) __attribute__((__sentinel__(x)))
#endif /* __INTELLISENSE__ */
#else /* ... */
#define __NO_ATTR_SENTINEL
#define __NO_ATTR_SENTINEL_O
#define __ATTR_SENTINEL      /* Nothing */
#define __ATTR_SENTINEL_O(x) /* Nothing */
#endif /* !... */

#if (__has_feature(cxx_thread_local) ||                                     \
     (defined(__cplusplus) && (defined(__SUNPRO_CC) || defined(__IBMC__) || \
                               defined(__IBMCPP__))))
#define __ATTR_THREAD_IS_THREAD_LOCAL
#define __ATTR_THREAD thread_local
#elif (__has_feature(c_thread_local) || \
       (!defined(__cplusplus) && defined(__STDC_VERSION__) && (__STDC_VERSION__+0) > 201000L))
#define __ATTR_THREAD_IS__THREAD_LOCAL
#define __ATTR_THREAD _Thread_local
#elif __has_declspec_attribute(thread) || defined(__BORLANDC__) || defined(__DMC__)
#define __ATTR_THREAD __declspec(thread)
#elif (defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ICL) || defined(__ECC))
#if defined(_WIN32) || defined(WIN32)
#define __ATTR_THREAD_IS___THREAD
#define __ATTR_THREAD __thread
#else /* _WIN32 || WIN32 */
#define __ATTR_THREAD __declspec(thread)
#endif /* !_WIN32 && !WIN32 */
#else /* ... */
#define __NO_ATTR_THREAD
#define __ATTR_THREAD /* Nothing */
#endif /* !... */

#if __has_attribute(__deprecated__)
#define __ATTR_DEPRECATED_      __attribute__((__deprecated__))
#define __ATTR_DEPRECATED(text) __attribute__((__deprecated__(text)))
#elif __has_declspec_attribute(deprecated)
#define __ATTR_DEPRECATED_      __declspec(deprecated)
#define __ATTR_DEPRECATED(text) __declspec(deprecated(text))
#elif __has_cpp_attribute(deprecated) >= 201309
#define __ATTR_DEPRECATED_      [[deprecated]]
#define __ATTR_DEPRECATED(text) [[deprecated(text)]]
#elif defined(__SUNPRO_C) && __SUNPRO_C >= 0x5130
#define __ATTR_DEPRECATED_      __attribute__((deprecated))
#define __ATTR_DEPRECATED(text) __attribute__((deprecated))
#else /* ... */
#define __NO_ATTR_DEPRECATED
#define __ATTR_DEPRECATED_      /* Nothing */
#define __ATTR_DEPRECATED(text) /* Nothing */
#endif /* !... */

#if __has_attribute(__warning__)
#define __ATTR_WARNING(text) __attribute__((__warning__(text)))
#else /* ... */
#define __NO_ATTR_WARNING
#define __ATTR_WARNING(text) /* Nothing */
#endif /* !... */

#if __has_attribute(__error__)
#define __ATTR_ERROR(text) __attribute__((__error__(text)))
#else /* ... */
#define __NO_ATTR_ERROR
#define __ATTR_ERROR(text) /* Nothing */
#endif /* !... */

#if __has_attribute(__section__) || defined(__TINYC__)
#define __ATTR_SECTION(name) __attribute__((__section__(name)))
#else /* ... */
#define __NO_ATTR_SECTION
#define __ATTR_SECTION(name) /* Nothing */
#endif /* !... */

#if __has_attribute(__nothrow__)
#define __ATTR_NOTHROW __attribute__((__nothrow__))
#else /* ... */
#define __NO_ATTR_NOTHROW
#define __ATTR_NOTHROW /* Nothing */
#endif /* !... */

#if __has_attribute(__optimize__)
#define __ATTR_OPTIMIZE(opt) __attribute__((__optimize__(opt)))
#else /* ... */
#define __NO_ATTR_OPTIMIZE
#define __ATTR_OPTIMIZE(opt) /* Nothing */
#endif /* !... */

#if __has_attribute(__returns_nonnull__)
#define __ATTR_RETNONNULL __attribute__((__returns_nonnull__))
#else /* ... */
#define __NO_ATTR_RETNONNULL
#define __ATTR_RETNONNULL /* Nothing */
#endif /* !... */

#if __has_attribute(__packed__) || defined(__TINYC__)
#define __ATTR_PACKED __attribute__((__packed__))
#else /* ... */
#define __NO_ATTR_PACKED
#define __ATTR_PACKED /* Nothing */
#endif /* !... */

#if __has_attribute(__alias__) || defined(__TINYC__)
#define __ATTR_ALIAS(name) __attribute__((__alias__(name)))
#else /* ... */
#define __NO_ATTR_ALIAS
#define __ATTR_ALIAS(name) /* Nothing */
#endif /* !... */

#if __has_attribute(__aligned__) || defined(__TINYC__)
#define __ATTR_ALIGNED(n) __attribute__((__aligned__(n)))
#elif __has_declspec_attribute(align)
#define __ATTR_ALIGNED(n) __declspec(align(n))
#elif __has_feature(cxx_alignas) || __has_extension(cxx_alignas)
#define __ATTR_ALIGNED_IS_ALIGNAS
#define __ATTR_ALIGNED(n) alignas(n)
#elif 0
#define __ATTR_ALIGNED_IS__ALIGNAS
#define __ATTR_ALIGNED(n) _Alignas(n)
#else /* ... */
#define __NO_ATTR_ALIGNED
#define __ATTR_ALIGNED(n) /* Nothing */
#endif /* !... */

#if __has_attribute(__selectany__)
#define __ATTR_SELECTANY __attribute__((__selectany__))
#elif __has_declspec_attribute(selectany)
#define __ATTR_SELECTANY __declspec(selectany)
#else /* ... */
#define __NO_ATTR_SELECTANY
#define __ATTR_SELECTANY /* Nothing */
#endif /* !... */

#if (__has_attribute(__weak__) || \
     (defined(__ELF__) || defined(__TINYC__)))
#define __ATTR_WEAK __attribute__((__weak__))
#elif !defined(__NO_ATTR_SELECTANY)
#define __ATTR_WEAK_IS_SELECTANY
#define __ATTR_WEAK __ATTR_SELECTANY
#else /* ... */
#define __NO_ATTR_WEAK
#define __ATTR_WEAK /* Nothing */
#endif /* !... */

#if __has_attribute(__returns_twice__)
#define __ATTR_RETURNS_TWICE __attribute__((__returns_twice__))
#else /* ... */
#define __NO_ATTR_RETURNS_TWICE
#define __ATTR_RETURNS_TWICE /* Nothing */
#endif /* !... */

#if __has_attribute(__externally_visible__)
#define __ATTR_EXTERNALLY_VISIBLE __attribute__((__externally_visible__))
#else /* ... */
#define __NO_ATTR_EXTERNALLY_VISIBLE
#define __ATTR_EXTERNALLY_VISIBLE /* Nothing */
#endif /* !... */

#if __has_attribute(__visibility__) || (defined(__ELF__) || defined(__TINYC__))
#define __ATTR_VISIBILITY(vis) __attribute__((__visibility__(vis)))
#else /* ... */
#define __NO_ATTR_VISIBILITY
#define __ATTR_VISIBILITY(vis) /* Nothing */
#endif /* !... */

#if __has_attribute(__format__)
#define __ATTR_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))
#if 0 /* TODO: Only `printf' is supported by everything implementing `__has_attribute(__format__)' */
#define __ATTR_FORMAT_SCANF(fmt, args)    __attribute__((__format__(__scanf__, fmt, args)))
#define __ATTR_FORMAT_STRFMON(fmt, args)  __attribute__((__format__(__strfmon__, fmt, args)))
#define __ATTR_FORMAT_STRFTIME(fmt, args) __attribute__((__format__(__strftime__, fmt, args)))
#endif
#else /* ... */
#define __NO_ATTR_FORMAT_PRINTF
#define __ATTR_FORMAT_PRINTF(fmt, args) /* Nothing */
#endif /* !... */

#ifndef __ATTR_FORMAT_SCANF
#define __NO_ATTR_FORMAT_SCANF
#define __ATTR_FORMAT_SCANF(fmt, args) /* Nothing */
#endif /* !__ATTR_FORMAT_SCANF */

#ifndef __ATTR_FORMAT_STRFMON
#define __NO_ATTR_FORMAT_STRFMON
#define __ATTR_FORMAT_STRFMON(fmt, args) /* Nothing */
#endif /* !__ATTR_FORMAT_STRFMON */

#ifndef __ATTR_FORMAT_STRFTIME
#define __NO_ATTR_FORMAT_STRFTIME
#define __ATTR_FORMAT_STRFTIME(fmt, args) /* Nothing */
#endif /* !__ATTR_FORMAT_STRFTIME */

#if __has_attribute(__dllimport__)
#define __ATTR_DLLIMPORT __attribute__((__dllimport__))
#define __ATTR_DLLEXPORT __attribute__((__dllexport__))
#elif defined(__TINYC__)
#define __ATTR_DLLIMPORT __attribute__((dllimport))
#define __ATTR_DLLEXPORT __attribute__((dllexport))
#elif __has_declspec_attribute(dllimport) || defined(__PE__) || defined(_WIN32)
#define __ATTR_DLLIMPORT __declspec(dllimport)
#define __ATTR_DLLEXPORT __declspec(dllexport)
#else /* ... */
#define __NO_ATTR_DLLIMPORT
#define __ATTR_DLLIMPORT /* Nothing */
#define __NO_ATTR_DLLEXPORT
#define __ATTR_DLLEXPORT /* Nothing */
#endif /* !... */

#if __has_attribute(__noplt__)
#define __ATTR_NOPLT __attribute__((__noplt__))
#else /* ... */
#define __ATTR_NOPLT /* nothing */
#define __NO_ATTR_NOPLT
#endif /* !... */

#if __has_attribute(__nonnull__)
#define __ATTR_NONNULL(ppars)     __attribute__((__nonnull__ ppars))
#define __ATTR_NONNULL_CXX(ppars) __attribute__((__nonnull__ ppars))
#else /* ... */
#define __NO_ATTR_NONNULL
#define __ATTR_NONNULL(ppars)     /* Nothing */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
#endif /* !... */

#if __has_attribute(__warn_unused_result__)
#define __ATTR_WUNUSED __attribute__((__warn_unused_result__))
#else /* ... */
#define __NO_ATTR_WUNUSED
#define __ATTR_WUNUSED /* Nothing */
#endif /* !... */

#if __has_attribute(__transparent_union__)
#define __ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#else /* ... */
#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#endif /* !... */

#if defined(__DCC_VERSION__) || defined(__TINYC__)
#define __XBLOCK  __extension__
#define __XRETURN /* Nothing */
#else /* ... */
#define __NO_XBLOCK
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __XBLOCK(...) do __VA_ARGS__ while(0)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __XBLOCK(expr...) do expr while(0)
#else /* ... */
#define __XBLOCK(expr) do expr while(0)
#endif /* !... */
#define __XRETURN /* Nothing */
#endif /* !... */

#define __DEFINE_PRIVATE_ALIAS(new, old)      /* Nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* Nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* Nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* Nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* Nothing */
#define __NO_DEFINE_ALIAS

#if defined(__INTELLISENSE__)
#elif defined(__TPP_VERSION__) || defined(__STDC__)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __pragma(...) _Pragma(#__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __pragma(command...) _Pragma(#command)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __pragma(command) _Pragma(#command)
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#else /* ... */
#define __NO_pragma
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __pragma(...) /* Nothing */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __pragma(command...) /* Nothing */
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __pragma(command) /* Nothing */
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* !... */

#if !__has_builtin(__builtin_assume)
#if 0
#define __builtin_assume_has_sideeffects
#define __builtin_assume(x) (!(x) ? __builtin_unreachable() : (void)0)
#else
#undef __builtin_assume_has_sideeffects
#define __NO_builtin_assume
#define __builtin_assume(x) (void)0
#endif
#endif /* ... */

#if !__has_builtin(__builtin_unreachable) && !defined(__TINYC__)
#define __NO_builtin_unreachable
#define __builtin_unreachable() do;while(1)
#endif /* ... */

#if !__has_builtin(__builtin_constant_p) && !defined(__TINYC__)
#define __NO_builtin_constant_p
#define __builtin_constant_p(x) 0
#endif /* ... */

#if (__has_feature(cxx_alignof) || \
     (defined(__cplusplus) &&      \
      (defined(__CODEGEARC__) ||   \
       (defined(__BORLANDC__) &&   \
        defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ >= 0x610))))
#define __COMPILER_ALIGNOF_IS_ALIGNOF
#define __COMPILER_ALIGNOF alignof
#elif ((defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)) || \
       (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5130) ||     \
       defined(__DCC_VERSION__) || defined(__TINYC__))
#define __COMPILER_ALIGNOF_IS___ALIGNOF__
#define __COMPILER_ALIGNOF __alignof__
#elif 0
#define __COMPILER_ALIGNOF_IS__ALIGNOF
#define __COMPILER_ALIGNOF _Alignof
#elif defined(__cplusplus)
namespace __intern { template<class T> struct __compiler_alignof { char __x; T __y; }; }
#define __COMPILER_ALIGNOF(T) (sizeof(::__intern::__compiler_alignof< T >) - sizeof(T))
#else /* ... */
#define __COMPILER_ALIGNOF(T) ((__SIZE_TYPE__)&((struct{ char __x; T __y; } *)0)->__y)
#endif /* !... */

#if !__has_builtin(__builtin_offsetof)
#define __builtin_offsetof(s,m) ((__SIZE_TYPE__)&((s *)0)->m)
#endif /* ... */

#if (defined(inline) || defined(__cplusplus) ||        \
     (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)) || \
     (defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0 >= 199901L)))
#define __ATTR_INLINE_IS_INLINE
#define __ATTR_INLINE inline
#elif (defined(__BORLANDC__) || defined(__DMC__) || \
       defined(__SC__) || defined(__WATCOMC__) ||   \
       defined(__LCC__) || defined(__DECC))
#define __ATTR_INLINE_IS___INLINE__
#define __ATTR_INLINE __inline
#elif (__has_attribute(__always_inline__) || \
       defined(__DCC_VERSION__) || defined(__TINYC__))
#define __ATTR_INLINE_IS___INLINE__
#define __ATTR_INLINE __inline__
#else /* ... */
#define __NO_ATTR_INLINE
#define __ATTR_INLINE /* Nothing */
#endif /* !... */

#if __has_attribute(__always_inline__)
#define __ATTR_FORCEINLINE __ATTR_INLINE __attribute__((__always_inline__))
#else /* __always_inline__ */
#define __NO_ATTR_FORCEINLINE
#define __ATTR_FORCEINLINE __ATTR_INLINE /* Nothing */
#endif /* !__always_inline__ */

#if __has_attribute(__artificial__)
#define __ATTR_ARTIFICIAL __attribute__((__artificial__))
#else /* __has_attribute(__artificial__) */
#define __NO_ATTR_ARTIFICIAL
#define __ATTR_ARTIFICIAL /* nothing */
#endif /* !__has_attribute(__artificial__) */

#if __has_attribute(__format_arg__)
#define __ATTR_FORMAT_ARG(x) __attribute__((__format_arg__(x)))
#else /* __has_attribute(__format_arg__) */
#define __NO_ATTR_FORMAT_ARG
#define __ATTR_FORMAT_ARG(x) /* nothing */
#endif /* !__has_attribute(__format_arg__) */

#define __ATTR_LEAF_P  __ATTR_LEAF
#define __ATTR_PURE_P  __ATTR_PURE
#define __ATTR_CONST_P __ATTR_CONST

#define __LOCAL      static __ATTR_INLINE
#define __FORCELOCAL static __ATTR_FORCEINLINE

#if __has_attribute(__gnu_inline__)
#define __EXTERN_INLINE      extern __ATTR_INLINE __attribute__((__gnu_inline__))
#define __EXTERN_FORCEINLINE extern __ATTR_FORCEINLINE __attribute__((__gnu_inline__))
#elif defined(__GNUC_GNU_INLINE__)
#define __EXTERN_INLINE      extern __ATTR_INLINE
#define __EXTERN_FORCEINLINE extern __ATTR_FORCEINLINE
#elif defined(__GNUC_STDC_INLINE__) || __has_attribute(__gnu_inline__)
#define __EXTERN_INLINE      extern __ATTR_INLINE __attribute__((__gnu_inline__))
#define __EXTERN_FORCEINLINE extern __ATTR_FORCEINLINE __attribute__((__gnu_inline__))
#else /* ... */
#define __NO_EXTERN_INLINE
#define __EXTERN_INLINE      __LOCAL
#define __EXTERN_FORCEINLINE __FORCELOCAL
#endif /* !... */

#ifdef __COMPILER_HAVE_LONGLONG
#define __LONGLONG  signed long long
#define __ULONGLONG unsigned long long
#else /* __COMPILER_HAVE_LONGLONG */
/* XXX: What if the compiler doesn't support __int64 either? */
#define __LONGLONG  signed __int64
#define __ULONGLONG unsigned __int64
#endif /* !__COMPILER_HAVE_LONGLONG */

#if !__has_builtin(__builtin_prefetch)
#define __NO_builtin_prefetch   1
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __builtin_prefetch(...) (void)0
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __builtin_prefetch(addr...) (void)0
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __builtin_prefetch(addr) (void)0
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* !__builtin_prefetch */

#ifndef __INTELLISENSE__
#ifndef __restrict
#if (defined(restrict) || \
     (defined(__STDC_VERSION__) && (__STDC_VERSION__ + 0) >= 199901L))
#define __RESTRICT_IS_RESTRICT
#define __restrict  restrict
#else /* ... */
#define __restrict  /* Nothing */
#endif /* !... */
#endif /* !__restrict */
#endif /* !__INTELLISENSE__ */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__+0) >= 199901L
#define __restrict_arr restrict
#else /* __STDC_VERSION__ >= 199901L */
#define __restrict_arr /* Not supported.  */
#endif /* __STDC_VERSION__ < 199901L */

#if 0 /* TODO: Depend on __STDC_VERSION__ for this! */
#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS 1
#endif
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[1024]

#ifdef __cplusplus
#if __cplusplus >= 201703L /* C++17 */
#define __STATIC_IF(x)   if constexpr(x)
#define __STATIC_ELSE(x) if constexpr(!(x))
#else /* __cplusplus >= 201703L */
#define __STATIC_IF(x)   if(x)
#define __STATIC_ELSE(x) if(!(x))
#endif /* __cplusplus < 201703L */
#define __IF0     if(false)
#define __IF1     if(true)
#define __WHILE0  while(false)
#define __WHILE1  while(true)
#else /* __cplusplus */
#define __STATIC_IF(x)   if(x)
#define __STATIC_ELSE(x) if(!(x))
#define __IF0     if(0)
#define __IF1     if(1)
#define __WHILE0  while(0)
#define __WHILE1  while(1)
#endif /* !__cplusplus */
#define __COMPILER_BARRIERS_ALL_IDENTICAL 1
#define __COMPILER_BARRIER()       (void)0 /* ??? */
#define __COMPILER_READ_BARRIER()  (void)0 /* ??? */
#define __COMPILER_WRITE_BARRIER() (void)0 /* ??? */
#define __COMPILER_IMPURE()        (void)0

#ifdef __cplusplus
#ifdef __INTELLISENSE__
#define __NULLPTR nullptr
#else /* __INTELLISENSE__ */
#define __NULLPTR 0
#endif /* !__INTELLISENSE__ */
#else /* __cplusplus */
#define __NULLPTR ((void *)0)
#endif /* !__cplusplus */

/* Mark the wchar_t type as already being defined when pre-defined by the compiler */
#ifdef __cplusplus
#if !defined(__MWERKS__) || __option(wchar_type)
#define __native_wchar_t_defined 1
#define __wchar_t_defined 1
#endif /* !__MWERKS__ || __option(wchar_type) */
#endif /* __cplusplus */

#if defined(c_plusplus) && !defined(__cplusplus)
#if (c_plusplus+0) != 0
#define __cplusplus (c_plusplus + 0)
#else /* (c_plusplus+0) != 0 */
#define __cplusplus 0
#endif /* (c_plusplus+0) == 0 */
#endif /* c_plusplus && !__cplusplus */


#ifndef __COMPILER_IGNORE_UNINITIALIZED
#define __COMPILER_IGNORE_UNINITIALIZED(var) var
#endif /* !__COMPILER_IGNORE_UNINITIALIZED */

/* Define varargs macros expected by system headers. */
#if __has_builtin(__builtin_va_list) || __has_builtin(__builtin_va_start)
#ifndef __builtin_va_list
#define __builtin_va_list __builtin_va_list
#endif /* !__builtin_va_list */
#elif defined(__TINYC__)
#ifdef __x86_64__
#ifndef _WIN64
#define __builtin_va_list            void *
#define __builtin_va_start(ap, last) (void)((ap) = __va_start(__builtin_frame_address(0)))
#define __builtin_va_arg(ap, type)   (*(type *)__va_arg(ap, __builtin_va_arg_types(type), sizeof(type)))
#define __builtin_va_copy(dest, src) (void)((dest) = __va_copy(src))
#define __builtin_va_end(ap)         __va_end(ap)
extern __builtin_va_list (__va_start)(void *fp);
extern __builtin_va_list (__va_copy)(__builtin_va_list src);
extern void *(__va_arg)(__builtin_va_list ap, int arg_type, int size);
extern void (__va_end)(__builtin_va_list ap);
#else /* _WIN64 */
#define __builtin_va_list            char *
#define __builtin_va_start(ap, last) (void)((ap) = ((char *)&(last)) + ((sizeof(last) + 7) & ~7))
#define __builtin_va_arg(ap, type)   ((ap) += (sizeof(type) + 7) & ~7, *(type *)((ap) - ((sizeof(type) + 7) & ~7)))
#define __builtin_va_copy(dest, src) (void)((dest) = (src))
#define __builtin_va_end(ap)         (void)0
#endif /* !_WIN64 */
#else
#define __builtin_va_list            char *
#define __builtin_va_start(ap, last) (void)((ap) = ((char *)&(last)) + ((sizeof(last) + 3) & ~3))
#define __builtin_va_arg(ap, type)   ((ap) += (sizeof(type) + 3) & ~3, *(type *)((ap) - ((sizeof(type) + 3) & ~3)))
#define __builtin_va_copy(dest, src) (void)((dest) = (src))
#define __builtin_va_end(ap)         (void)0
#endif
#elif (defined(__NO_KOS_SYSTEM_HEADERS__) && \
       (defined(__NO_has_include) || __has_include(<stdarg.h>)))
/* Without KOS's system headers around, we can
 * try to make use  of someone else's work  :) */
#include <stdarg.h>
#define __builtin_va_list         va_list
#define __builtin_va_start(ap, v) va_start(ap, v)
#define __builtin_va_arg(ap, T)   va_arg(ap, T)
#define __builtin_va_end(ap)      va_end(ap)
#else /* ... */
/* Just guess some generic implementation... */
#define __builtin_va_list         char *
#define __VA_ADDROF(v)            &(v)
#define __VA_SIZEOF(n)            ((sizeof(n) + (sizeof(int) - 1)) & ~(sizeof(int) - 1))
#define __builtin_va_start(ap, v) (ap = (__builtin_va_list)__VA_ADDROF(v) + __VA_SIZEOF(v))
#define __builtin_va_arg(ap, T)   (*(T *)((ap += __VA_SIZEOF(T)) - __VA_SIZEOF(T)))
#define __builtin_va_end(ap)      (void)0
#endif /* !... */
