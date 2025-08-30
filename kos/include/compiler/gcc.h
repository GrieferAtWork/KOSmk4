/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!included_by <__stdinc.h>*/
#ifdef __CHECKER__
#include "checker.h"
#else /* __CHECKER__ */

#define __GCC_PRIVATE_ARG_PLACEHOLDER_  ,
#define __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL(x,val,...) val
#define __GCC_PRIVATE_TAKE_SECOND_ARG(x) __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL x
#define __GCC_PRIVATE_IS_DEFINED3(x) __GCC_PRIVATE_TAKE_SECOND_ARG((x 1,0))
#define __GCC_PRIVATE_IS_DEFINED2(x) __GCC_PRIVATE_IS_DEFINED3(__GCC_PRIVATE_ARG_PLACEHOLDER_##x)
#define __GCC_PRIVATE_IS_DEFINED(x) __GCC_PRIVATE_IS_DEFINED2(x)

#ifdef __STDC__
#define __P(x) x
#else /* __STDC__ */
#define __NO_PROTOTYPES
#define __P(x) ()
#endif /* !__STDC__ */

#ifndef __INTEL_VERSION__
#ifdef __INTEL_COMPILER
#if __INTEL_COMPILER == 9999
#define __INTEL_VERSION__ 1200
#else /* __INTEL_COMPILER == 9999 */
#define __INTEL_VERSION__ __INTEL_COMPILER
#endif /* __INTEL_COMPILER != 9999 */
#elif defined(__ICL)
#define __INTEL_VERSION__ __ICL
#elif defined(__ICC)
#define __INTEL_VERSION__ __ICC
#elif defined(__ECC)
#define __INTEL_VERSION__ __ECC
#endif /* ... */
#endif /* !__INTEL_VERSION__ */

#ifndef __GNUC_MINOR__
#define __GNUC_MINOR__ 0
#endif /* !__GNUC_MINOR__ */

#ifndef __GNUC_PATCH__
#ifdef __GNUC_PATCHLEVEL__
#define __GNUC_PATCH__ __GNUC_PATCHLEVEL__
#else /* __GNUC_PATCHLEVEL__ */
#define __GNUC_PATCH__ 0
#endif /* !__GNUC_PATCHLEVEL__ */
#endif /* !__GNUC_PATCH__ */

#ifndef __GCC_VERSION_NUM
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */

#ifndef __has_attribute
#if ((defined(__i386__) || defined(__i386)) && \
     !defined(__x86_64__) && !defined(__x86_64))
#define __GCC_HAS_ATTRIBUTE___fastcall__
#define __GCC_HAS_ATTRIBUTE___stdcall__
#define __GCC_HAS_ATTRIBUTE___cdecl__
#endif
#if defined(__x86_64__) || defined(__x86_64)
#define __GCC_HAS_ATTRIBUTE___ms_abi__
#define __GCC_HAS_ATTRIBUTE___sysv_abi__
#endif
#if !defined(__ELF__) && (defined(__PE__) || defined(_WIN32) || defined(__CYGWIN__))
#define __GCC_HAS_ATTRIBUTE___dllimport__
#define __GCC_HAS_ATTRIBUTE___dllexport__
#endif
#define __GCC_HAS_ATTRIBUTE___warning__
#define __GCC_HAS_ATTRIBUTE___error__
#define __GCC_HAS_ATTRIBUTE___section__
#define __GCC_HAS_ATTRIBUTE___returns_nonnull__
#define __GCC_HAS_ATTRIBUTE___packed__
#define __GCC_HAS_ATTRIBUTE___alias__
#define __GCC_HAS_ATTRIBUTE___aligned__
#define __GCC_HAS_ATTRIBUTE___weak__
#define __GCC_HAS_ATTRIBUTE___returns_twice__
#define __GCC_HAS_ATTRIBUTE___externally_visible__
#define __GCC_HAS_ATTRIBUTE___visibility__
#if __GCC_VERSION_NUM >= 20000 && !defined(__cplusplus)
#define __GCC_HAS_ATTRIBUTE___transparent_union__
#endif
#if __GCC_VERSION_NUM >= 20400
#define __GCC_HAS_ATTRIBUTE___format__ /* 20300 */
#define __GCC_HAS_ATTRIBUTE___format_arg__ /* 20800 */
#define __GCC_HAS_ATTRIBUTE___const__ /* 20500 */
#define __GCC_HAS_ATTRIBUTE___unused__ /* 20700 */
#define __GCC_HAS_ATTRIBUTE___no_instrument_function__ /* 30100 */
#endif
#if __GCC_VERSION_NUM >= 20800
#define __GCC_HAS_ATTRIBUTE___noreturn__ /* 20500 */
#endif
#if __GCC_VERSION_NUM >= 29600
#define __GCC_HAS_ATTRIBUTE___pure__
#define __GCC_HAS_ATTRIBUTE___malloc__ /* 30000 */
#define __GCC_HAS_ATTRIBUTE___noinline__ /* 30100 */
#endif
#if __GCC_VERSION_NUM >= 30100
#define __GCC_HAS_ATTRIBUTE___used__
#define __GCC_HAS_ATTRIBUTE___deprecated__ /* - __GCC_VERSION_NUM >= 30100
                                            * - __GCC_VERSION_NUM >= 30200
                                            * - __GCC_VERSION_NUM >= 30500
                                            * The internet isn't unanimous about this one... */
#endif
#if __GCC_VERSION_NUM >= 30300
#define __GCC_HAS_ATTRIBUTE___nothrow__
#define __GCC_HAS_ATTRIBUTE___nonnull__
#define __GCC_HAS_ATTRIBUTE___warn_unused_result__ /* __GCC_VERSION_NUM >= 30300 / __GCC_VERSION_NUM >= 30400 */
#define __GCC_HAS_ATTRIBUTE_may_alias
#endif
#if __GCC_VERSION_NUM >= 30400
#define __GCC_HAS_ATTRIBUTE_warn_unused_result
#endif
#if __GCC_VERSION_NUM >= 40000
#define __GCC_HAS_ATTRIBUTE___sentinel__ /* 30500 */
#endif
#if __GCC_VERSION_NUM >= 40300
#define __GCC_HAS_ATTRIBUTE___alloc_size__
#define __GCC_HAS_ATTRIBUTE___artificial__
#define __GCC_HAS_ATTRIBUTE___cold__
#define __GCC_HAS_ATTRIBUTE___hot__
#endif
#if __GCC_VERSION_NUM >= 40400
#define __GCC_HAS_ATTRIBUTE___optimize__
#endif
#if __GCC_VERSION_NUM >= 40500
#define __GCC_HAS_ATTRIBUTE___noclone__
#endif
#if __GCC_VERSION_NUM >= 40900
#define __GCC_HAS_ATTRIBUTE___assume_aligned__
#endif
#if __GCC_VERSION_NUM >= 50400
#define __GCC_HAS_ATTRIBUTE___alloc_align__
#endif
#if __GCC_VERSION_NUM >= 60000
#define __GCC_HAS_ATTRIBUTE_fallthrough
#endif
#if __GCC_VERSION_NUM >= 70000
#define __GCC_HAS_ATTRIBUTE___fallthrough__
#endif
#if __GCC_VERSION_NUM >= 130000
#define __GCC_HAS_ATTRIBUTE___assume__
#define __GCC_HAS_ATTRIBUTE___fd_arg__
#define __GCC_HAS_ATTRIBUTE___fd_arg_read__
#define __GCC_HAS_ATTRIBUTE___fd_arg_write__
#endif
#if defined(__GNUC_GNU_INLINE__) || defined(__GNUC_STDC_INLINE__)
#define __GCC_HAS_ATTRIBUTE___gnu_inline__
#endif /* __GNUC_GNU_INLINE__ || __GNUC_STDC_INLINE__ */
#define __has_attribute(x) __GCC_PRIVATE_IS_DEFINED(__GCC_HAS_ATTRIBUTE_##x)
#endif /* !__has_attribute */

#ifndef __has_builtin
#include "gcc-builtins.h"
#endif /* !__has_builtin */

#include "gcc-warnings.h"

#ifndef __has_feature
#define __NO_has_feature
#define __has_feature(x) 0
#endif /* !__has_feature */

#ifndef __has_extension
#ifndef __NO_has_feature
#define __NO_has_extension
#endif /* !__NO_has_feature */
#define __has_extension  __has_feature
#endif /* !__has_extension */

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


#ifndef __likely
#ifdef __INTELLISENSE__
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#elif __has_builtin(__builtin_expect)
#define __likely(x)   (__builtin_expect(!!(x), 1))
#define __unlikely(x) (__builtin_expect(!!(x), 0))
#else /* ... */
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#endif /* !... */
#endif /* !__likely */


#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
#define __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#if __GCC_VERSION_NUM >= 40000
#define __COMPILER_HAVE_PRAGMA_GCC_VISIBILITY
#endif /* __GCC_VERSION_NUM >= 40000 */
#if __has_feature(__tpp_pragma_deprecated__)
#define __COMPILER_HAVE_PRAGMA_DEPRECATED
#endif /* __has_feature(__tpp_pragma_deprecated__) */
#ifdef __CC__
#define __COMPILER_HAVE_LONGDOUBLE
#ifndef __LONGDOUBLE
#define __LONGDOUBLE long double
#endif /* !__LONGDOUBLE */
#define __COMPILER_HAVE_GCC_ASM
#define __COMPILER_HAVE_PRAGMA_PACK
#define __COMPILER_HAVE_ADDRESSIBLE_LABELS /* void *p = &&foo; goto *p; foo: */
#define __COMPILER_HAVE_TYPEOF
#if defined(__clang__) || !defined(__DARWIN_NO_LONG_LONG)
#define __COMPILER_HAVE_LONGLONG
#endif /* __clang__ || !__DARWIN_NO_LONG_LONG */
/* For   whatever  reason,  g++  refuses  to  allow  trivially
 * constructible+copyable+etc. classes within unnamed structs:
 *     https://stackoverflow.com/questions/39069799/rules-for-anonymous-aggregates
 * So be careful when using them, and use `__COMPILER_HAVE_TRANSPARENT_NONCLASS'
 * to test for this special case. */
#define __COMPILER_HAVE_TRANSPARENT_NONCLASS
#if 1
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#define __COMPILER_HAVE_TRANSPARENT_UNION
#endif
#endif /* __CC__ */
#ifdef __cplusplus
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T(*)[s])(p))
#else /* __cplusplus */
#define __COMPILER_ASM_BUFFER(T, s, p) (*(struct { __extension__ T __d[s]; } *)(p))
#endif /* !__cplusplus */

#define __COMPILER_HAVE_REGISTER_VARS
#ifdef __INTELLISENSE__
#define __register_var(T, name, regname) T name
#else /* __INTELLISENSE__ */
#define __register_var(T, name, regname) register T name __asm__(regname)
#endif /* !__INTELLISENSE__ */

#ifndef __cplusplus
/* XXX: When was this added in C? */
#ifndef __INTELLISENSE__
#define __COMPILER_HAVE_AUTOTYPE
#endif /* !__INTELLISENSE__ */
#elif __has_feature(cxx_auto_type) || (defined(__cplusplus) && __GCC_VERSION_NUM >= 40400)
#define __auto_type auto
#define __COMPILER_HAVE_AUTOTYPE
#endif

#if (__has_feature(cxx_static_assert) ||                               \
     (defined(__cpp_static_assert) && __cpp_static_assert + 0 != 0) || \
     (__GCC_VERSION_NUM >= 40300 && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)))
#if defined(__cpp_static_assert) && __cpp_static_assert + 0 >= 201411
#define __STATIC_ASSERT_IS_static_assert
#define __STATIC_ASSERT static_assert
#else /* __cpp_static_assert >= 201411 */
#define __STATIC_ASSERT(expr) static_assert(expr, #expr)
#endif /* __cpp_static_assert < 201411 */
#define __STATIC_ASSERT_MSG_IS_static_assert
#define __STATIC_ASSERT_MSG static_assert
#elif (defined(_Static_assert) || __has_feature(c_static_assert) ||                                   \
       (!defined(__cplusplus) && ((defined(__STDC_VERSION__) && (__STDC_VERSION__ + 0) >= 201112L) || \
                                  (__GCC_VERSION_NUM >= 40600 && !defined(__STRICT_ANSI__) &&         \
                                   !defined(__INTELLISENSE__)))))
#define __STATIC_ASSERT_IS__Static_assert
#define __STATIC_ASSERT(expr) _Static_assert(expr, #expr)
#define __STATIC_ASSERT_MSG   _Static_assert
#elif defined(__TPP_COUNTER)
#define __STATIC_ASSERT(expr)          extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#elif defined(__COUNTER__)
#define __STATIC_ASSERT(expr)          extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#else /* ... */
#define __STATIC_ASSERT(expr)          extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#endif /* !... */

#if defined(__INTELLISENSE__) && !defined(__INTELLISENSE_GCC__)
#define __COMPILER_ASMNAME(x) /* Nothing */
#else /* ... */
#define __COMPILER_ASMNAME(x) __asm__(x)
#endif /* !... */

#if __GCC_VERSION_NUM < 20700
#ifndef __attribute__
#define __attribute__(x) /* Nothing */
#endif /* !__attribute__ */
#endif /* __GCC_VERSION_NUM < 20700 */

#if __GCC_VERSION_NUM < 20800
#ifndef __extension__
#define __extension__
#endif /* !__extension__ */
#endif /* __GCC_VERSION_NUM < 20800 */

#if __has_attribute(__noinline__)
#define __ATTR_NOINLINE __attribute__((__noinline__))
#else /* ... */
#define __NO_ATTR_NOINLINE
#define __ATTR_NOINLINE /* Nothing */
#endif /* !... */

#if __has_attribute(__noreturn__)
#define __ATTR_NORETURN_IS___attribute_____noreturn__
#define __ATTR_NORETURN __attribute__((__noreturn__))
#else /* ... */
#define __NO_ATTR_NORETURN
#define __ATTR_NORETURN /* Nothing */
#endif /* !... */

#if defined(__cplusplus) && __has_cpp_attribute(fallthrough)
#define __ATTR_FALLTHROUGH [[fallthrough]];
#elif __has_attribute(__fallthrough__)
#define __ATTR_FALLTHROUGH __attribute__((__fallthrough__));
#elif __has_attribute(fallthrough)
#define __ATTR_FALLTHROUGH __attribute__((fallthrough));
#else /* ... */
#define __NO_ATTR_FALLTHROUGH
#define __ATTR_FALLTHROUGH /* Nothing */
#endif /* !... */

#define __NO_ATTR_W64
#define __ATTR_W64 /* Nothing */

#if (defined(__i386__) || defined(__i386)) && \
    !defined(__x86_64__) && !defined(__x86_64)
#define __ATTR_FASTCALL __attribute__((__fastcall__))
#define __ATTR_STDCALL  __attribute__((__stdcall__))
#ifndef __INTELLISENSE__
#define __ATTR_CDECL /* [default] */
#else /* !__INTELLISENSE__ */
#define __ATTR_CDECL __attribute__((__cdecl__))
#endif /* __INTELLISENSE__ */
#else /* ... */
#define __NO_ATTR_FASTCALL
#define __ATTR_FASTCALL /* Nothing */
#define __NO_ATTR_STDCALL
#define __ATTR_STDCALL /* Nothing */
#define __NO_ATTR_CDECL
#define __ATTR_CDECL /* Nothing */
#endif /* !... */

#if __has_attribute(__clrcall__)
#define __ATTR_CLRCALL __attribute__((__clrcall__))
#else /* ... */
#define __NO_ATTR_CLRCALL
#define __ATTR_CLRCALL /* Nothing */
#endif /* !... */

#if __has_attribute(__thiscall__)
#define __ATTR_THISCALL __attribute__((__thiscall__))
#else /* ... */
#define __NO_ATTR_THISCALL
#define __ATTR_THISCALL /* Nothing */
#endif /* !... */

#if defined(__x86_64__) || defined(__x86_64)
#if (defined(__PE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || \
     defined(__WINDOWS__) || defined(_WIN16) || defined(WIN16) || defined(_WIN32) ||            \
     defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) ||               \
     defined(__TOS_WIN__) || defined(_WIN32_WCE) || defined(WIN32_WCE))
#undef __VA_LIST_IS_ARRAY /* No on this platform, it's not... */
#else /* ... */
#define __VA_LIST_IS_ARRAY
#endif /* !... */
#define __ATTR_MSABI   __attribute__((__ms_abi__))
#define __ATTR_SYSVABI __attribute__((__sysv_abi__))
#else /* ... */
#define __NO_ATTR_MSABI
#define __ATTR_MSABI /* Nothing */
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

#if __has_attribute(__alloc_size__)
#define __ATTR_ALLOC_SIZE(ppars) __attribute__((__alloc_size__ ppars))
#else /* ... */
#define __NO_ATTR_ALLOC_SIZE
#define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#endif /* !... */

#if __has_attribute(__unused__)
#define __ATTR_UNUSED __attribute__((__unused__))
#else /* ... */
#define __NO_ATTR_UNUSED
#define __ATTR_UNUSED /* Nothing */
#endif /* !... */

#if __has_attribute(__used__)
#define __ATTR_USED __attribute__((__used__))
#else /* ... */
#define __NO_ATTR_USED
#define __ATTR_USED /* Nothing */
#endif /* !... */

#if __has_attribute(__deprecated__)
#define __ATTR_DEPRECATED_ __attribute__((__deprecated__))
#if __GCC_VERSION_NUM >= 40500
#define __ATTR_DEPRECATED(text) __attribute__((__deprecated__(text)))
#else /* __GCC_VERSION_NUM >= 40500 */
#define __ATTR_DEPRECATED(text) __attribute__((__deprecated__))
#endif /* __GCC_VERSION_NUM < 40500 */
#else /* ... */
#define __NO_ATTR_DEPRECATED
#define __ATTR_DEPRECATED_      /* Nothing */
#define __ATTR_DEPRECATED(text) /* Nothing */
#endif /* !... */

#if __has_attribute(__sentinel__)
#define __ATTR_SENTINEL __attribute__((__sentinel__))
#ifdef __INTELLISENSE__
#define __ATTR_SENTINEL_O(x) __attribute__((__sentinel__))
#else /* __INTELLISENSE__ */
#define __ATTR_SENTINEL_O(x) __attribute__((__sentinel__(x)))
#endif /* !__INTELLISENSE__ */
#else /* ... */
#define __NO_ATTR_SENTINEL
#define __NO_ATTR_SENTINEL_O
#define __ATTR_SENTINEL      /* Nothing */
#define __ATTR_SENTINEL_O(x) /* Nothing */
#endif /* !... */

#if __has_attribute(__hot__)
#define __ATTR_HOT __attribute__((__hot__))
#else /* ... */
#define __NO_ATTR_HOT
#define __ATTR_HOT /* Nothing */
#endif /* !... */

#if __has_attribute(__cold__)
#define __ATTR_COLD __attribute__((__cold__))
#else /* ... */
#define __NO_ATTR_COLD
#define __ATTR_COLD /* Nothing */
#endif /* !... */

#if __has_attribute(__noclone__)
#define __ATTR_NOCLONE __attribute__((__noclone__))
#else /* ... */
#define __NO_ATTR_NOCLONE
#define __ATTR_NOCLONE /* Nothing */
#endif /* !... */

#if __GCC_VERSION_NUM >= 40800
#define __ATTR_THREAD_IS___thread
#define __ATTR_THREAD __thread
#else /* __GCC_VERSION_NUM >= 40800 */
#define __NO_ATTR_THREAD
#define __ATTR_THREAD /* Nothing */
#endif /* __GCC_VERSION_NUM < 40800 */

#if __has_attribute(__assume_aligned__)
#define __ATTR_ASSUME_ALIGNED(n) __attribute__((__assume_aligned__(n)))
#else /* ... */
#define __NO_ATTR_ASSUME_ALIGNED
#define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#endif /* !... */

#if __has_attribute(__alloc_align__)
#define __ATTR_ALLOC_ALIGN(pari) __attribute__((__alloc_align__(pari)))
#else /* ... */
#define __NO_ATTR_ALLOC_ALIGN
#define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
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

#if __has_attribute(__transparent_union__) && !defined(__cplusplus)
#define __ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#else /* ... */
#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#endif /* !... */

/* format-printer attributes. */
#if !__has_attribute(__format__)
#define __NO_ATTR_FORMAT_PRINTF
#define __ATTR_FORMAT_PRINTF(fmt, args) /* Nothing */
#elif __GCC_VERSION_NUM < 20700
/* underscore-guarded variants weren't available in this version of gcc... */
#define __ATTR_FORMAT_PRINTF(fmt, args) __attribute__((format(printf, fmt, args)))
#else /* ... */
#define __ATTR_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))
#endif /* !... */

#if !defined(__NO_ATTR_FORMAT_PRINTF) /* TODO: There were added later. - But when exactly? */
#define __ATTR_FORMAT_SCANF(fmt, args)    __attribute__((__format__(__scanf__, fmt, args)))
#define __ATTR_FORMAT_STRFMON(fmt, args)  __attribute__((__format__(__strfmon__, fmt, args)))
#define __ATTR_FORMAT_STRFTIME(fmt, args) __attribute__((__format__(__strftime__, fmt, 0)))
#else /* ... */
#define __NO_ATTR_FORMAT_SCANF
#define __NO_ATTR_FORMAT_STRFMON
#define __NO_ATTR_FORMAT_STRFTIME
#define __ATTR_FORMAT_SCANF(fmt, args)    /* Nothing */
#define __ATTR_FORMAT_STRFMON(fmt, args)  /* Nothing */
#define __ATTR_FORMAT_STRFTIME(fmt, args) /* Nothing */
#endif /* !... */

#if (!defined(__ELF__) && \
     (defined(__PE__) || defined(_WIN32) || defined(__CYGWIN__)))
#define __ATTR_DLLIMPORT __attribute__((__dllimport__))
#define __ATTR_DLLEXPORT __attribute__((__dllexport__))
#else /* ... */
#define __NO_ATTR_DLLIMPORT
#define __ATTR_DLLIMPORT /* Nothing */
#define __NO_ATTR_DLLEXPORT
#define __ATTR_DLLEXPORT /* Nothing */
#endif /* !... */

#if __has_attribute(__noplt__)
#define __ATTR_NOPLT __attribute__((__noplt__))
#else /* ... */
#define __ATTR_NOPLT /* Nothing */
#define __NO_ATTR_NOPLT
#endif /* !... */

#if __has_attribute(__nonnull__)
#define __ATTR_NONNULL(ppars) __attribute__((__nonnull__ ppars))
/* Parameter IDs are offset by 1, which is dumb */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
#else /* ... */
#define __NO_ATTR_NONNULL
#define __ATTR_NONNULL(ppars)     /* Nothing */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
#endif /* !... */

#if __has_attribute(__warn_unused_result__)
#define __ATTR_WUNUSED __attribute__((__warn_unused_result__))
#elif __has_attribute(warn_unused_result)
#define __ATTR_WUNUSED __attribute__((warn_unused_result))
#else /* ... */
#define __NO_ATTR_WUNUSED
#define __ATTR_WUNUSED /* Nothing */
#endif /* !... */

#if __has_attribute(__selectany__)
#define __ATTR_SELECTANY __attribute__((__selectany__))
#else /* ... */
#define __NO_ATTR_SELECTANY
#define __ATTR_SELECTANY /* Nothing */
#endif /* !... */

#if __has_attribute(__access__)
#define __ATTR_ACCESS_NONE(ptr_index)        __attribute__((__access__(__none__, ptr_index)))
#define __ATTR_INS(ptr_index, size_index)    __attribute__((__access__(__read_only__, ptr_index, size_index)))
#define __ATTR_OUTS(ptr_index, size_index)   __attribute__((__access__(__write_only__, ptr_index, size_index)))
#define __ATTR_INOUTS(ptr_index, size_index) __attribute__((__access__(__read_write__, ptr_index, size_index)))
#define __ATTR_IN_OPT(ptr_index)             __attribute__((__access__(__read_only__, ptr_index)))
#define __ATTR_OUT_OPT(ptr_index)            __attribute__((__access__(__write_only__, ptr_index)))
#define __ATTR_INOUT_OPT(ptr_index)          __attribute__((__access__(__read_write__, ptr_index)))
#if __has_attribute(__nonnull__)
#define __ATTR_IN(ptr_index)    __attribute__((__access__(__read_only__, ptr_index), __nonnull__(ptr_index)))
#define __ATTR_OUT(ptr_index)   __attribute__((__access__(__write_only__, ptr_index), __nonnull__(ptr_index)))
#define __ATTR_INOUT(ptr_index) __attribute__((__access__(__read_write__, ptr_index), __nonnull__(ptr_index)))
#else /* __has_attribute(__nonnull__) */
#define __ATTR_IN(ptr_index)    __attribute__((__access__(__read_only__, ptr_index)))
#define __ATTR_OUT(ptr_index)   __attribute__((__access__(__write_only__, ptr_index)))
#define __ATTR_INOUT(ptr_index) __attribute__((__access__(__read_write__, ptr_index)))
#endif /* !__has_attribute(__nonnull__) */
#elif defined(__INTELLISENSE__)
/* Intellisense doesn't understand __access__, but to get error high-lighting  (since
 * the `ptr_index' argument must reference a pointer-argument), we can use some other
 * attributes that it does know! */
#define __ATTR_ACCESS_NONE(ptr_index)        __attribute__((__nonnull__(ptr_index)))
#define __ATTR_INS(ptr_index, size_index)    __attribute__((__nonnull__(ptr_index)))
#define __ATTR_OUTS(ptr_index, size_index)   __attribute__((__nonnull__(ptr_index)))
#define __ATTR_INOUTS(ptr_index, size_index) __attribute__((__nonnull__(ptr_index)))
#define __ATTR_IN_OPT(ptr_index)             __attribute__((__nonnull__(ptr_index)))
#define __ATTR_OUT_OPT(ptr_index)            __attribute__((__nonnull__(ptr_index)))
#define __ATTR_INOUT_OPT(ptr_index)          __attribute__((__nonnull__(ptr_index)))
#define __ATTR_IN(ptr_index)                 __attribute__((__nonnull__(ptr_index)))
#define __ATTR_OUT(ptr_index)                __attribute__((__nonnull__(ptr_index)))
#define __ATTR_INOUT(ptr_index)              __attribute__((__nonnull__(ptr_index)))
#else /* ... */
#define __NO_ATTR_ACCESS
#define __ATTR_ACCESS_NONE(ptr_index)        /* Nothing */
#define __ATTR_INS(ptr_index, size_index)    /* Nothing */
#define __ATTR_OUTS(ptr_index, size_index)   /* Nothing */
#define __ATTR_INOUTS(ptr_index, size_index) /* Nothing */
#define __ATTR_IN_OPT(ptr_index)             /* Nothing */
#define __ATTR_OUT_OPT(ptr_index)            /* Nothing */
#define __ATTR_INOUT_OPT(ptr_index)          /* Nothing */
#if __has_attribute(__nonnull__)
#define __ATTR_IN(ptr_index)    __attribute__((__nonnull__(ptr_index)))
#define __ATTR_OUT(ptr_index)   __attribute__((__nonnull__(ptr_index)))
#define __ATTR_INOUT(ptr_index) __attribute__((__nonnull__(ptr_index)))
#else /* __has_attribute(__nonnull__) */
#define __ATTR_IN(ptr_index)    /* Nothing */
#define __ATTR_OUT(ptr_index)   /* Nothing */
#define __ATTR_INOUT(ptr_index) /* Nothing */
#endif /* !__has_attribute(__nonnull__) */
#endif /* !... */


#if __has_attribute(__fd_arg__)
#define __ATTR_FDARG(fd_index)   __attribute__((__fd_arg__(fd_index)))
#define __ATTR_FDREAD(fd_index)  __attribute__((__fd_arg_read__(fd_index)))
#define __ATTR_FDWRITE(fd_index) __attribute__((__fd_arg_write__(fd_index)))
#else /* __has_attribute(__fd_arg__) */
#define __ATTR_FDARG(fd_index)   /* Nothing */
#define __ATTR_FDREAD(fd_index)  /* Nothing */
#define __ATTR_FDWRITE(fd_index) /* Nothing */
#endif /* !__has_attribute(__fd_arg__) */

#define __ATTR_WARNING(text)      __attribute__((__warning__(text)))
#define __ATTR_ERROR(text)        __attribute__((__error__(text)))
#define __ATTR_SECTION(name)      __attribute__((__section__(name)))
#define __ATTR_RETNONNULL         __attribute__((__returns_nonnull__))
#define __ATTR_PACKED             __attribute__((__packed__))
#define __ATTR_ALIAS(name)        __attribute__((__alias__(name)))
#define __ATTR_ALIGNED(n)         __attribute__((__aligned__(n)))
#define __ATTR_WEAK               __attribute__((__weak__))
#define __ATTR_RETURNS_TWICE      __attribute__((__returns_twice__))
#define __ATTR_EXTERNALLY_VISIBLE __attribute__((__externally_visible__))
#define __ATTR_VISIBILITY(vis)    __attribute__((__visibility__(vis)))

/* Suppress warnings about `-Wsuggest-attribute=const' or `-Wsuggest-attribute=pure'
 * Must  add a single ";" because without it,  GCC seems to have gotten smart enough
 * to understand that `__asm__("")' is not enough indicate something impure. */
#define __COMPILER_IMPURE() __asm__(";")

#ifdef __INTELLISENSE_GCC__
#define __pragma(...) _Pragma(#__VA_ARGS__)
#define __XBLOCK      /* Nothing */
#define __XRETURN     /* Nothing */
#elif defined(__INTELLISENSE__)
#define __XBLOCK(...) (([&] __VA_ARGS__)())
#define __XRETURN     return
#else /* ... */
#if __GCC_VERSION_NUM >= 40400 || defined(__TPP_VERSION__)
#define __pragma(...) _Pragma(#__VA_ARGS__)
#else /* __GCC_VERSION_NUM >= 40400 || __TPP_VERSION__ */
#define __NO_pragma
#define __pragma(...) /* Nothing */
#endif /* __GCC_VERSION_NUM < 40400 && !__TPP_VERSION__ */
#define __XBLOCK  __extension__
#define __XRETURN /* Nothing */
#endif /* !... */

#if __has_builtin(__builtin_assume)
/* Already exists as a *true* builtin */
#elif __has_attribute(__assume__)
#define __builtin_assume(x) __XBLOCK({ __attribute__((__assume__(x))); (void)0; })
#elif 1
#define __builtin_assume_has_sideeffects
#define __builtin_assume(x) (!(x) ? __builtin_unreachable() : (void)0)
#else /* ... */
#undef __builtin_assume_has_sideeffects
#define __NO_builtin_assume
#define __builtin_assume(x) (void)0
#endif /* !... */

#if (__GCC_VERSION_NUM >= 40300 &&             \
     (!defined(__GCCXML__) &&                  \
      !defined(__clang__) && !defined(unix) && \
      !defined(__unix__)) ||                   \
     defined(__LP64__))
#define __COMPILER_ALIGNOF_IS___alignof__
#define __COMPILER_ALIGNOF __alignof__
#elif defined(__clang__)
#define __COMPILER_ALIGNOF_IS___alignof
#define __COMPILER_ALIGNOF __alignof
#elif defined(__cplusplus)
extern "C++" { template<class T> struct __compiler_alignof { char __x; T __y; }; }
#define __COMPILER_ALIGNOF(T)   (sizeof(__compiler_alignof<__typeof__(T)>)-sizeof(T))
#else /* ... */
#define __COMPILER_ALIGNOF(T)   ((__SIZE_TYPE__)&((struct{ char __x; T __y; } *)0)->__y)
#endif /* !... */

#if defined(__NO_INLINE__) && 0
#define __NO_ATTR_INLINE
#define __ATTR_INLINE /* Nothing */
#elif (defined(inline) || defined(__cplusplus) || \
       (defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L))
#define __ATTR_INLINE_IS_inline
#define __ATTR_INLINE inline
#elif __GCC_VERSION_NUM >= 20700
#define __ATTR_INLINE_IS___inline__
#define __ATTR_INLINE __inline__
#else /* ... */
#define __NO_ATTR_INLINE
#define __ATTR_INLINE /* Nothing */
#endif /* !... */

#if __GCC_VERSION_NUM >= 30000
#define __ATTR_FORCEINLINE __ATTR_INLINE __attribute__((__always_inline__))
#else /* ... */
#define __NO_ATTR_FORCEINLINE
#define __ATTR_FORCEINLINE __ATTR_INLINE
#endif /* !... */

#if __GCC_VERSION_NUM >= 40300
#define __ATTR_ARTIFICIAL __attribute__((__artificial__))
#else /* __GCC_VERSION_NUM >= 40300 */
#define __NO_ATTR_ARTIFICIAL
#define __ATTR_ARTIFICIAL /* Nothing */
#endif /* __GCC_VERSION_NUM < 40300 */

#if __has_attribute(__format_arg__)
#define __ATTR_FORMAT_ARG(x) __attribute__((__format_arg__(x)))
#else /* __has_attribute(__format_arg__) */
#define __NO_ATTR_FORMAT_ARG
#define __ATTR_FORMAT_ARG(x) /* Nothing */
#endif /* !__has_attribute(__format_arg__) */

#define __LOCAL       static __ATTR_INLINE
#define __FORCELOCAL  static __ATTR_FORCEINLINE

#ifdef __INTELLISENSE__
#define _Exit __real__Exit /* Because for some reason, intellisence pre-defines this one... */
#define __NO_EXTERN_INLINE /* Intellisense likes to freeze when parsing `__attribute__((__gnu_inline__))'... */
#define __EXTERN_INLINE      static
#define __EXTERN_FORCEINLINE static
#elif __has_attribute(__gnu_inline__)
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

#ifndef __LONGLONG
#ifdef __CC__
/* If long-long is fully supported without the need for __extension__,
 * then simply define __[U]LONGLONG  as macros, rather than  typedefs,
 * since the later seems to unconditionally create a DIE (debug-info),
 * which would cause debug info to be bloated for _every_ source  file
 * unconditionally...
 * Ugh... I should have never looked at what actually ends up inside
 *        of gcc  debug  info.  -  Sooooo  much  unnecessary  bloat! */
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L)
#define __LONGLONG  long long
#define __ULONGLONG unsigned long long
#else /* __cplusplus || __STDC_VERSION__ > 199901L */
__extension__ typedef long long __longlong_t;
__extension__ typedef unsigned long long __ulonglong_t;
#define __LONGLONG  __longlong_t
#define __ULONGLONG __ulonglong_t
#endif /* !__cplusplus && __STDC_VERSION__ <= 199901L */
#endif /* __CC__ */
#endif /* !__LONGLONG */

#if __GCC_VERSION_NUM < 29200 /* __GCC_VERSION_NUM < 29500 */
#ifndef __restrict
#if defined(restrict) || (defined(__STDC_VERSION__) && (__STDC_VERSION__+0) >= 199901L)
#define __restrict_IS_restrict
#define __restrict restrict
#else /* restrict || ... */
#define __restrict /* Nothing */
#endif /* !restrict && !... */
#endif /* !__restrict */
#endif /* __GCC_VERSION_NUM < 29200 */

#if __GCC_VERSION_NUM >= 30100 && !defined(__GNUG__)
#define __restrict_arr __restrict
#else /* __GCC_VERSION_NUM >= 30100 && !__GNUG__ */
#define __restrict_arr /* Nothing */
#endif /* __GCC_VERSION_NUM < 30100 || __GNUG__ */


#if __GCC_VERSION_NUM >= 20970
#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#endif /* __GCC_VERSION_NUM >= 20970 */

#ifdef __INTELLISENSE__
/* Intellisense doesn't get it, so try to work around that... */
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[1024]
#elif defined(__COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS)
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[]
#elif 1
#define __COMPILER_FLEXIBLE_ARRAY(T, x) __extension__ T x[0]
#else /* ... */
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[1024]
#endif /* !... */


#define __STATIC_IF(x) if(x)
#if 1
#define __STATIC_ELSE(x) else
#else /* ... */
#define __STATIC_ELSE(x) if(!(x))
#endif /* !... */

#ifdef __cplusplus
#define __IF0    if(false)
#define __IF1    if(true)
#define __WHILE0 while(false)
#define __WHILE1 while(true)
#else /* __cplusplus */
#define __IF0    if(0)
#define __IF1    if(1)
#define __WHILE0 while(0)
#define __WHILE1 while(1)
#endif /* !__cplusplus */

#ifdef __cplusplus
#if (!defined(__INTEL_VERSION__) || __INTEL_VERSION__ >= 600 || \
     (_WCHAR_T_DEFINED + 0 != 0) || (_WCHAR_T + 0 != 0))
#define __native_wchar_t_defined
#define __wchar_t_defined
#endif /* ... */
#endif /* __cplusplus */

#ifndef __INTELLISENSE__
#define __FUNCTION__ __extension__ __FUNCTION__
#endif /* !__INTELLISENSE__ */

#if !__has_builtin(__builtin_LINE)
#define __builtin_LINE() __LINE__
#endif /* !__has_builtin(__builtin_LINE) */

#if !__has_builtin(__builtin_FILE)
#define __builtin_FILE() __FILE__
#endif /* !__has_builtin(__builtin_FILE) */

#if !__has_builtin(__builtin_FUNCTION)
#define __builtin_FUNCTION() __FUNCTION__
#endif /* __has_builtin(__builtin_FUNCTION) */

#if !__has_builtin(__builtin_unreachable)
#define __builtin_unreachable() __XBLOCK({ for (;;); (void)0; })
#endif /* !__has_builtin(__builtin_unreachable) */

#if !__has_builtin(__builtin_object_size)
#define __builtin_object_size(ptr,type) ((type) < 2 ? (__SIZE_TYPE__)-1 : 0)
#endif /* !__has_builtin(__builtin_object_size) */


#if __GCC_VERSION_NUM >= 40700
#define __COMPILER_BARRIER()       __atomic_signal_fence(__ATOMIC_ACQ_REL)
#define __COMPILER_READ_BARRIER()  __atomic_signal_fence(__ATOMIC_ACQUIRE)
#define __COMPILER_WRITE_BARRIER() __atomic_signal_fence(__ATOMIC_RELEASE)
#elif defined(__COMPILER_HAVE_GCC_ASM)
#define __COMPILER_BARRIERS_ALL_IDENTICAL
#define __COMPILER_BARRIER()       __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#define __COMPILER_READ_BARRIER()  __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#define __COMPILER_WRITE_BARRIER() __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#else /* ... */
#define __COMPILER_BARRIERS_ALL_IDENTICAL
#define __COMPILER_BARRIER()       __sync_synchronize()
#define __COMPILER_READ_BARRIER()  __sync_synchronize()
#define __COMPILER_WRITE_BARRIER() __sync_synchronize()
#endif /* !... */

#define __COMPILER_IGNORE_UNINITIALIZED(var) var = var

/* Delete assumptions the compiler may have made about `var'.
 * This includes:
 *  - __builtin_constant_p(var)
 *  - __builtin_object_size(var)
 *  - Object origin
 * Usage:
 * >> struct obj {
 * >>     int field;
 * >> };
 * >> struct obj *o = get_object();
 * >> int *p = &o->field;
 * >> __COMPILER_DELETE_ASSUMPTIONS(p);  // Prevents out-of-bounds warnings
 * >> memcpy(p, p + 5, 2 * sizeof(o->field)); */
#define __COMPILER_DELETE_ASSUMPTIONS(var) __asm__("" : "+g" (var))

#ifdef __cplusplus
#ifdef __INTELLISENSE__
#define __NULLPTR nullptr
#else /* __INTELLISENSE__ */
#define __NULLPTR 0
#endif /* !__INTELLISENSE__ */
#else /* __cplusplus */
#define __NULLPTR ((void *)0)
#endif /* !__cplusplus */

#if __GCC_VERSION_NUM < 40402
#undef __builtin_va_start
#define __builtin_va_start __builtin_stdarg_start
#endif /* __GCC_VERSION_NUM < 40402 */

/* Support for complex numbers (test for with `#ifdef _Complex_I') */
#ifdef __INTELLISENSE__
#define _Complex_I 1.0F
#elif __GCC_VERSION_NUM >= 29700
#define _Complex_I (__extension__ 1.0iF)
#if __STDC_VERSION__ < 199901
#define _Complex __complex__
#endif /* __STDC_VERSION__ < 199901 */
#elif __GCC_VERSION_NUM >= 20700
#define _Complex __complex__
#define _Complex_I (__extension__ 1.0iF)
#endif


#ifdef __cplusplus

#ifndef __INTELLISENSE__
/* Compiler has the gcc-ncx-builtin bug:
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=96985
 *
 * As  work-around,  libc functions  that  gcc/g++ considers  to  be nothrow/noexcept
 * must be declared with extern "C++" linkage when compiling with non-call-exceptions
 * enabled, else the  compiler will believe  them to be  unable to throw  exceptions,
 * when in actuality they are _very_ _much_ able to do exactly that! */
#define __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
#endif /* !__INTELLISENSE__ */

/* `__builtin_choose_expr()' is only available in C, but not in C++ */
#undef __builtin_choose_expr
#define __NO_builtin_choose_expr
#define __builtin_choose_expr(c, tt, ff) ((c) ? (tt) : (ff))

/* `__builtin_types_compatible_p()' isn't consistently defined by g++.
 * So  to prevent problems  with that, simply  re-implement it using a
 * macro alongside C++ templates. */
extern "C++" {
namespace __intern {
template<class __T> struct __gcc_types_compatible_remcv{typedef __T __type;};
template<class __T> struct __gcc_types_compatible_remcv<__T const>{typedef __T __type;};
template<class __T> struct __gcc_types_compatible_remcv<__T volatile>{typedef __T __type;};
template<class __T> struct __gcc_types_compatible_remcv<__T const volatile>{typedef __T __type;};
template<class __T1, class __T2> struct __gcc_types_compatible_impl{enum{__val=false};};
template<class __T1> struct __gcc_types_compatible_impl<__T1,__T1>{enum{__val=true};};
template<class __T1, class __T2> struct __gcc_types_compatible:
	__gcc_types_compatible_impl<typename __gcc_types_compatible_remcv<__T1>::__type,
	                            typename __gcc_types_compatible_remcv<__T2>::__type>{};
}
}
#undef __builtin_types_compatible_p
#define __builtin_types_compatible_p(...) (::__intern::__gcc_types_compatible< __VA_ARGS__ >::__val)
#endif /* __cplusplus */


/************************************************************************/
/* Workarounds for compiler bugs.                                       */
/************************************************************************/

/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105689 */
#if defined(__OPTIMIZE__) && __has_attribute(__access__)/* && (__GCC_VERSION_NUM <= FIXED_IN_VERSION)*/
#define __COMPILER_HAVE_BUG_GCC_105689
#define __COMPILER_WORKAROUND_GCC_105689(ptr)  __asm__("" : : "X" (ptr))
#ifdef __COMPILER_HAVE_AUTOTYPE
#define __COMPILER_WORKAROUND_GCC_105689_MAC(self, ...) \
	({ __auto_type __cw_105689_self = (self); __COMPILER_WORKAROUND_GCC_105689(__cw_105689_self); __VA_ARGS__; })
#else /* __COMPILER_HAVE_AUTOTYPE */
#define __COMPILER_WORKAROUND_GCC_105689_MAC(self, ...) \
	({ __typeof__(self) __cw_105689_self = (self); __COMPILER_WORKAROUND_GCC_105689(__cw_105689_self); __VA_ARGS__; })
#endif /* !__COMPILER_HAVE_AUTOTYPE */
#endif /* ... */

/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=111080 */
#if 1 /* && (__GCC_VERSION_NUM <= FIXED_IN_VERSION)*/
#define __COMPILER_HAVE_BUG_GCC_111080
#endif /* ... */

/************************************************************************/
#endif /* !__CHECKER__ */
