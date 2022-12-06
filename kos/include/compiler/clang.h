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


#if __has_builtin(__builtin_expect)
#define __likely(x)   (__builtin_expect(!!(x), 1))
#define __unlikely(x) (__builtin_expect(!!(x), 0))
#else /* ... */
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#endif /* !... */

#if (__has_feature(c_generic_selections) || __has_extension(c_generic_selections))
#define __COMPILER_HAVE_C11_GENERIC
#endif /* ... */

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

#ifdef __STDC__
#define __P(x) x
#else /* __STDC__ */
#define __NO_PROTOTYPES
#define __P(x) ()
#endif /* !__STDC__ */

#define __COMPILER_HAVE_LONGLONG
#define __COMPILER_HAVE_LONGDOUBLE
#ifndef __LONGDOUBLE
#define __LONGDOUBLE long double
#endif /* !__LONGDOUBLE */
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#define __COMPILER_HAVE_TRANSPARENT_UNION
#define __COMPILER_HAVE_GCC_ASM
#define __COMPILER_HAVE_PRAGMA_PACK /* XXX: So many more compilers support this... */
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
//#define __COMPILER_HAVE_PRAGMA_DEPRECATED
#if __has_feature(cxx_auto_type) || __has_extension(cxx_auto_type)
#define __auto_type auto
#define __COMPILER_HAVE_AUTOTYPE
#endif /* ... */
#define __COMPILER_HAVE_TYPEOF
#if (__has_feature(cxx_static_assert) || __has_extension(cxx_static_assert) || \
     (defined(__cpp_static_assert) && __cpp_static_assert + 0 != 0))
#if defined(__cpp_static_assert) && __cpp_static_assert + 0 >= 201411
#define __STATIC_ASSERT_IS_static_assert
#define __STATIC_ASSERT static_assert
#else /* __cpp_static_assert >= 201411 */
#define __STATIC_ASSERT(expr) static_assert(expr, #expr)
#endif /* __cpp_static_assert < 201411 */
#define __STATIC_ASSERT_MSG_IS_static_assert
#define __STATIC_ASSERT_MSG static_assert
#elif (defined(_Static_assert) || __has_feature(c_static_assert) || __has_extension(c_static_assert) || \
       (!defined(__cplusplus) && ((defined(__STDC_VERSION__) && __STDC_VERSION__ + 0 >= 201112L))))
#define __STATIC_ASSERT_IS__Static_assert
#define __STATIC_ASSERT(expr) _Static_assert(expr, #expr)
#define __STATIC_ASSERT_MSG   _Static_assert
#elif defined(__COUNTER__)
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#else /* ... */
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#endif /* !... */

#define __COMPILER_ASMNAME(x) __asm__(x)

#if __has_attribute(__noinline__)
#define __ATTR_NOINLINE __attribute__((__noinline__))
#elif __has_declspec_attribute(noinline)
#define __ATTR_NOINLINE __declspec(noinline)
#else /* ... */
#define __NO_ATTR_NOINLINE
#define __ATTR_NOINLINE /* Nothing */
#endif /* !... */

#if __has_attribute(__noreturn__)
#define __ATTR_NORETURN __attribute__((__noreturn__))
#elif __has_declspec_attribute(noreturn)
#define __ATTR_NORETURN __declspec(noreturn)
#elif !defined(__cplusplus)
#define __ATTR_NORETURN_IS__NORETURN
#define __ATTR_NORETURN _Noreturn
#elif __has_cpp_attribute(noreturn)
#undef noreturn
#define __ATTR_NORETURN_IS_LB_LB_NORETURN_RB_RB
#define __ATTR_NORETURN [[noreturn]]
#elif defined(noreturn)
#define __ATTR_NORETURN_IS_NORETURN
#define __ATTR_NORETURN noreturn
#elif (!defined(__KOS_SYSTEM_HEADERS__) && \
       (defined(__NO_has_include) || __has_include(<stdnoreturn.h>))
#include <stdnoreturn.h>
#define __ATTR_NORETURN_IS_NORETURN
#define __ATTR_NORETURN noreturn
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

#ifdef __clang_tidy__
#define __ATTR_FASTCALL /* nothing */
#elif __has_attribute(__fastcall__)
#define __ATTR_FASTCALL __attribute__((__fastcall__))
#elif defined(__fastcall)
#define __ATTR_FASTCALL_IS___FASTCALL
#define __ATTR_FASTCALL __fastcall
#else /* ... */
#define __NO_ATTR_FASTCALL
#define __ATTR_FASTCALL /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_STDCALL /* nothing */
#elif __has_attribute(__stdcall__)
#define __ATTR_STDCALL __attribute__((__stdcall__))
#elif defined(__stdcall)
#define __ATTR_STDCALL_IS___STDCALL
#define __ATTR_STDCALL __stdcall
#else /* ... */
#define __NO_ATTR_STDCALL
#define __ATTR_STDCALL /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_CDECL /* nothing */
#elif __has_attribute(__cdecl__)
#define __ATTR_CDECL __attribute__((__cdecl__))
#elif defined(__cdecl)
#define __ATTR_CDECL_IS___CDECL
#define __ATTR_CDECL __cdecl
#else /* ... */
#define __NO_ATTR_CDECL
#define __ATTR_CDECL /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_CLRCALL /* nothing */
#elif __has_attribute(__clrcall__)
#define __ATTR_CLRCALL __attribute__((__clrcall__))
#elif defined(__clrcall)
#define __ATTR_CLRCALL_IS___CLRCALL
#define __ATTR_CLRCALL __clrcall
#else /* ... */
#define __NO_ATTR_CLRCALL
#define __ATTR_CLRCALL /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_THISCALL /* nothing */
#elif __has_attribute(__thiscall__)
#define __ATTR_THISCALL __attribute__((__thiscall__))
#elif defined(__thiscall)
#define __ATTR_THISCALL_IS___THISCALL
#define __ATTR_THISCALL __thiscall
#else /* ... */
#define __NO_ATTR_THISCALL
#define __ATTR_THISCALL /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_MSABI /* nothing */
#elif __has_attribute(__ms_abi__)
#define __ATTR_MSABI __attribute__((__ms_abi__))
#elif defined(__ms_abi)
#define __ATTR_MSABI_IS___MS_ABI
#define __ATTR_MSABI __ms_abi
#else /* ... */
#define __NO_ATTR_MSABI
#define __ATTR_MSABI /* Nothing */
#endif /* !... */

#ifdef __clang_tidy__
#define __ATTR_SYSVABI /* nothing */
#elif __has_attribute(__sysv_abi__)
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

#if __has_attribute(__cold__)
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
#endif /* !__INTELLISENSE__ */
#else /* ... */
#define __NO_ATTR_SENTINEL
#define __NO_ATTR_SENTINEL_O
#define __ATTR_SENTINEL      /* Nothing */
#define __ATTR_SENTINEL_O(x) /* Nothing */
#endif /* !... */

#if __has_feature(cxx_thread_local)
#define __ATTR_THREAD_IS_THREAD_LOCAL
#define __ATTR_THREAD thread_local
#elif __has_feature(c_thread_local)
#define __ATTR_THREAD_IS__THREAD_LOCAL
#define __ATTR_THREAD _Thread_local
#elif __has_declspec_attribute(thread)
#define __ATTR_THREAD __declspec(thread)
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

#if __has_attribute(__section__)
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

#if __has_attribute(__packed__)
#define __ATTR_PACKED __attribute__((__packed__))
#else /* ... */
#define __NO_ATTR_PACKED
#define __ATTR_PACKED /* Nothing */
#endif /* !... */

#if __has_attribute(__alias__)
#define __ATTR_ALIAS(name) __attribute__((__alias__(name)))
#else /* ... */
#define __NO_ATTR_ALIAS
#define __ATTR_ALIAS(name) /* Nothing */
#endif /* !... */

#if __has_attribute(__aligned__)
#define __ATTR_ALIGNED(n) __attribute__((__aligned__(n)))
#elif __has_declspec_attribute(align)
#define __ATTR_ALIGNED(n) __declspec(align(n))
#elif __has_feature(cxx_alignas) || __has_extension(cxx_alignas)
#define __ATTR_ALIGNED_IS_ALIGNAS
#define __ATTR_ALIGNED(n) alignas(n)
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

#if __has_attribute(__weak__) || \
   (defined(__ELF__))
#define __ATTR_WEAK __attribute__((__weak__))
#elif !defined(__NO_ATTR_SELECTANY)
#define __ATTR_WEAK __ATTR_SELECTANY
#define __ATTR_WEAK_IS_SELECTANY
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

#if __has_attribute(__visibility__)
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
#endif /* ... */
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
#elif __has_declspec_attribute(dllimport)
#define __ATTR_DLLIMPORT __declspec(dllimport)
#define __ATTR_DLLEXPORT __declspec(dllexport)
#else /* ... */
#define __NO_ATTR_DLLIMPORT
#define __ATTR_DLLIMPORT /* Nothing */
#define __NO_ATTR_DLLEXPORT
#define __ATTR_DLLEXPORT /* Nothing */
#endif /* !... */

#ifdef __ELF__
#ifdef __PE__
#error "Cannot #define both __ELF__ and __PE__ at once"
#endif /* __PE__ */
#undef __NO_ATTR_DLLIMPORT
#undef __ATTR_DLLIMPORT
#undef __NO_ATTR_DLLEXPORT
#undef __ATTR_DLLEXPORT
#define __NO_ATTR_DLLIMPORT
#define __ATTR_DLLIMPORT /* Nothing */
#define __NO_ATTR_DLLEXPORT
#define __ATTR_DLLEXPORT /* Nothing */
#undef __NO_ATTR_VISIBILITY
#define __ATTR_VISIBILITY(vis) __attribute__((__visibility__(vis)))
#elif defined(__PE__)
#undef __NO_ATTR_VISIBILITY
#define __NO_ATTR_VISIBILITY
#define __ATTR_VISIBILITY(vis) /* Nothing */
#undef __NO_ATTR_DLLIMPORT
#undef __NO_ATTR_DLLEXPORT
#if __has_attribute(__dllimport__)
#define __ATTR_DLLIMPORT __attribute__((__dllimport__))
#define __ATTR_DLLEXPORT __attribute__((__dllexport__))
#else /* __has_attribute(__dllimport__) */
#define __ATTR_DLLIMPORT __declspec(dllimport)
#define __ATTR_DLLEXPORT __declspec(dllexport)
#endif /* !__has_attribute(__dllimport__) */
#else /* ... */
#if !defined(__NO_ATTR_DLLIMPORT)
#define __PE__ 1
#elif !defined(__NO_ATTR_VISIBILITY)
#define __ELF__ 1
#endif /* ... */
#endif /* !... */

#if __has_attribute(__noplt__)
#define __ATTR_NOPLT __attribute__((__noplt__))
#else /* ... */
#define __ATTR_NOPLT /* Nothing */
#define __NO_ATTR_NOPLT
#endif /* !... */

#if __has_attribute(__nonnull__)
#define __ATTR_NONNULL(ppars) __attribute__((__nonnull__ ppars))
/* clang is dumb: "error: '__nonnull__' attribute is invalid for the implicit this argument" */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
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

#if __has_attribute(__transparent_union__) && 0 /* This one doesn't seem to actually work??? */
#define __ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#else /* ... */
#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#endif /* !... */

#define __XBLOCK  __extension__
#define __XRETURN /* Nothing */
#define __pragma(...) _Pragma(#__VA_ARGS__)

#if !__has_builtin(__builtin_LINE)
#define __builtin_LINE() __LINE__
#endif /* !__has_builtin(__builtin_LINE) */

#if !__has_builtin(__builtin_FILE)
#define __builtin_FILE() __FILE__
#endif /* !__has_builtin(__builtin_FILE) */

#if !__has_builtin(__builtin_FUNCTION)
#ifdef __FUNCTION__
#define __builtin_FUNCTION() __FUNCTION__
#else /* __FUNCTION__ */
#define __FUNCTION__ __func__
#define __builtin_FUNCTION() __func__
#define __builtin_FUNCTION_IS___func__
#endif /* !__FUNCTION__ */
#endif /* !__has_builtin(__builtin_FUNCTION) */

#if !__has_builtin(__builtin_assume)
#if 0
#define __builtin_assume_has_sideeffects
#define __builtin_assume(x)  (!(x) ? __builtin_unreachable() : (void)0)
#else /* ... */
#undef __builtin_assume_has_sideeffects
#define __NO_builtin_assume
#define __builtin_assume(x) (void)0
#endif /* !... */
#endif /* ... */

#if !__has_builtin(__builtin_unreachable) && !defined(__TINYC__)
#define __NO_builtin_unreachable
#define __builtin_unreachable() do;while(1)
#endif /* ... */

#if !__has_builtin(__builtin_constant_p) && !defined(__TINYC__)
#define __NO_builtin_constant_p
#define __builtin_constant_p(x) 0
#endif /* ... */

#if __has_feature(cxx_alignof)
#define __COMPILER_ALIGNOF_IS_ALIGNOF
#define __COMPILER_ALIGNOF alignof
#elif defined(__cplusplus)
namespace __intern { template<class T> struct __compiler_alignof { char __x; T __y; }; }
#define __COMPILER_ALIGNOF(T) (sizeof(::__intern::__compiler_alignof< T >) - sizeof(T))
#else /* ... */
#define __COMPILER_ALIGNOF(T) ((__SIZE_TYPE__)&((struct{ char __x; T __y; } *)0)->__y)
#endif /* !... */


#if defined(inline) || defined(__cplusplus)
#define __ATTR_INLINE_IS_INLINE
#define __ATTR_INLINE inline
#elif __has_attribute(__always_inline__)
#define __ATTR_INLINE_IS___INLINE__
#define __ATTR_INLINE __inline__
#else /* ... */
#define __ATTR_INLINE_IS___INLINE
#define __ATTR_INLINE __inline
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

#define __LOCAL      static __ATTR_INLINE
#define __FORCELOCAL static __ATTR_FORCEINLINE

#ifdef __INTELLISENSE__
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

#define __LONGLONG  signed long long
#define __ULONGLONG unsigned long long

#if !__has_builtin(__builtin_prefetch)
#define __NO_builtin_prefetch
#define __builtin_prefetch(...) (void)0
#endif /* !__builtin_prefetch */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__+0) >= 199901L
#define __restrict_arr restrict
#else /* __STDC_VERSION__ >= 199901L */
#define __restrict_arr /* Not supported.  */
#endif /* __STDC_VERSION__ < 199901L */

#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[]

#define _Complex_I (__extension__ 1.0iF)
#if __STDC_VERSION__ < 199901
#define _Complex __complex__
#endif /* __STDC_VERSION__ < 199901 */

#if 1 /* ??? */
#define __COMPILER_HAVE_REGISTER_VARS
#ifdef __INTELLISENSE__
#define __register_var(T, name, regname) T name
#else /* __INTELLISENSE__ */
#define __register_var(T, name, regname) register T name __asm__(regname)
#endif /* !__INTELLISENSE__ */
#endif


#ifdef __clang_tidy__
/* I don't know if the  proper clang really supports  this, but clang-tidy keeps  on
 * being a d1ck, telling me "initialization of flexible array member is not allowed"
 * WHEN  GCC FULLY ALLOWS ME TO DO THIS,  AND IT PROBABLY ALSO HAVING SOME OPTION TO
 * ALLOW THIS TO BE DONE!!!! */
#undef __COMPILER_FLEXIBLE_ARRAY
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[1024]
#undef __UNUSED
#define __UNUSED(x) x __attribute__((__unused__))
/* Disable  this, so clang-tidy doesn't think that function like memcpy() cannot
 * be made to be noexcept. - We only want warnings when calling functions marked
 * as THROWS() are called by those marked as NOTHROW(). */
#undef __NO_NON_CALL_EXCEPTIONS
#define __NO_NON_CALL_EXCEPTIONS
/* clang-tidy causes problems with extern-inline, so just disable it for now... */
#undef __NO_EXTERN_INLINE
#define __NO_EXTERN_INLINE
#define typeof __typeof__
#define __typeof __typeof__
#define __auto_type auto
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifndef __SIZE_TYPE__
#ifdef __x86_64__
#if defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ == 8
#define __SIZE_TYPE__ unsigned long
#else /* __SIZEOF_LONG__ == 8 */
#define __SIZE_TYPE__ unsigned long long
#endif /* __SIZEOF_LONG__ != 8 */
#else /* __x86_64__ */
#define __SIZE_TYPE__ unsigned int
#endif /* !__x86_64__ */
#endif /* !__SIZE_TYPE__ */

/* Builtin heap functions for static analysis (use these for static detection of leaks and bad usage) */
#define __builtin_malloc(num_bytes)                        malloc(num_bytes)
#define __builtin_pvalloc(num_bytes)                       malloc(num_bytes)
#define __builtin_valloc(num_bytes)                        malloc(num_bytes)
#define __builtin_memalign(alignment, num_bytes)           ((void)(alignment), malloc(num_bytes))
#define __builtin_free(ptr)                                free(ptr)
#define __builtin_calloc(item_size, item_count)            calloc(item_size, item_count)
#define __builtin_realloc(ptr, num_bytes)                  realloc(ptr, num_bytes)
#define __builtin_recalloc(ptr, num_bytes)                 realloc(ptr, num_bytes)
#define __builtin_recallocv(ptr, item_size, item_count)    realloc(ptr, (item_size) * (item_count))
#define __builtin_malloc_usable_size(ptr)                  malloc_usable_size(ptr)
#define __builtin_realloc_in_place(ptr, num_bytes)         realloc_in_place(ptr, num_bytes)
#define __builtin_memdup(ptr, num_bytes)                   __builtin_memcpy(malloc(num_bytes), ptr, num_bytes)
#define __builtin_reallocarray(ptr, item_size, item_count) realloc(ptr, (item_size) * (item_count))
#define __malloc_defined
#define __free_defined
#define __calloc_defined
#define __realloc_defined
#define __malloc_usable_size_defined
#define __realloc_in_place_defined
extern void free(void *);
extern void *malloc(__SIZE_TYPE__);
extern void *calloc(__SIZE_TYPE__, __SIZE_TYPE__);
extern void *realloc(void *, __SIZE_TYPE__);
extern __SIZE_TYPE__ malloc_usable_size(void *);
extern void *realloc_in_place(void *, __SIZE_TYPE__);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

/* Make log output a little easier to read */
#undef __builtin_expect
#undef __NO_builtin_expect
#undef __likely
#undef __unlikely
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#endif /* __clang_tidy__ */

#define __STATIC_IF(x)   if(x)
#define __STATIC_ELSE(x) if(!(x))
#define __IF0     if(0)
#define __IF1     if(1)
#define __WHILE0  while(0)
#define __WHILE1  while(1)
#define __COMPILER_BARRIERS_ALL_IDENTICAL
#define __COMPILER_BARRIER()       __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#define __COMPILER_READ_BARRIER()  __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#define __COMPILER_WRITE_BARRIER() __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#define __COMPILER_IMPURE() __asm__("")

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
#define __native_wchar_t_defined
#define __wchar_t_defined
#endif /* __cplusplus */

#ifndef __builtin_va_list
#define __builtin_va_list __builtin_va_list
#endif /* !__builtin_va_list */


/* clang has a broken prototype for `__builtin_bcopy()' */
#if __has_builtin(__builtin_bcopy) && __has_builtin(__builtin_memcpy)
#undef __builtin_bcopy
#define __builtin_bcopy(src, dst, num_bytes) __builtin_memcpy(dst, src, num_bytes)
#endif /* __builtin_bcopy && __builtin_memcpy */


#if (defined(_WIN32) && !defined(__PE__) && \
     defined(__ELF__) && defined(__KOS__))
/* This can happen when using the standard clang-tidy redistributable to scan KOS.
 * Re-configure stuff to prevent false warnings! */
#ifndef __NO_ATTR_MSABI
#undef __ATTR_MSABI
#define __ATTR_MSABI /* nothing */
#endif /* !__NO_ATTR_MSABI */
#ifndef __NO_ATTR_SYSVABI
#undef __ATTR_SYSVABI
#define __ATTR_SYSVABI /* nothing */
#endif /* !__NO_ATTR_SYSVABI */
#undef WIN32
#undef WIN64
#undef _WIN32
#undef _WIN64
#endif /* _WIN32 && !__PE__ && __ELF__ && __KOS__ */


#if 0 /* Always available? (even when __has_builtin() doesn't say so?) */
#undef __builtin_offsetof
#define __builtin_offsetof(s, m) ((__SIZE_TYPE__)&((s *)0)->m)
#endif

#define __COMPILER_IGNORE_UNINITIALIZED(var) var

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

#if !__has_builtin(__builtin_types_compatible_p)
/* Emulate: __builtin_types_compatible_p() */
#ifdef __cplusplus
namespace __intern {
template<class __T> struct __clang_remcv { typedef __T __type; };
template<class __T> struct __clang_remcv<__T const> { typedef __T __type; };
template<class __T> struct __clang_remcv<__T volatile> { typedef __T __type; };
template<class __T> struct __clang_remcv<__T const volatile> { typedef __T __type; };
template<class T1, class T2> struct __clang_sametype_impl { enum { __val = false }; };
template<class T1> struct __clang_sametype_impl<T1, T1> { enum { __val = true }; };
template<class T1, class T2> struct __clang_sametype:
	__clang_sametype_impl<typename __clang_remcv<T1>::__type,
	typename __clang_remcv<T2>::__type> { };
#define __builtin_types_compatible_p(...) (::__intern::__clang_sametype< __VA_ARGS__ >::__val)
}
#else /* __cplusplus */
#define __NO_builtin_types_compatible_p
#define __builtin_types_compatible_p(...) 1
#endif /* !__cplusplus */
#endif /* !__has_builtin(__builtin_types_compatible_p) */
