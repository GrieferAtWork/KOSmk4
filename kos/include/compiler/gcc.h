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
#define __GCC_PRIVATE_ARG_PLACEHOLDER_  ,
#define __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL(x,val,...) val
#define __GCC_PRIVATE_TAKE_SECOND_ARG(x) __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL x
#define __GCC_PRIVATE_IS_DEFINED3(x) __GCC_PRIVATE_TAKE_SECOND_ARG((x 1,0))
#define __GCC_PRIVATE_IS_DEFINED2(x) __GCC_PRIVATE_IS_DEFINED3(__GCC_PRIVATE_ARG_PLACEHOLDER_##x)
#define __GCC_PRIVATE_IS_DEFINED(x) __GCC_PRIVATE_IS_DEFINED2(x)

#ifdef __STDC__
#   define __P(x) x
#else /* __STDC__ */
#   define __NO_PROTOTYPES 1
#   define __P(x) ()
#endif /* !__STDC__ */

#ifndef __INTEL_VERSION__
#ifdef __INTEL_COMPILER
#if __INTEL_COMPILER == 9999
#   define __INTEL_VERSION__ 1200
#else /* __INTEL_COMPILER == 9999 */
#   define __INTEL_VERSION__ __INTEL_COMPILER
#endif /* __INTEL_COMPILER != 9999 */
#elif defined(__ICL)
#   define __INTEL_VERSION__ __ICL
#elif defined(__ICC)
#   define __INTEL_VERSION__ __ICC
#elif defined(__ECC)
#   define __INTEL_VERSION__ __ECC
#endif
#endif /* !__INTEL_VERSION__ */


#ifndef __GNUC_MINOR__
#   define __GNUC_MINOR__ 0
#endif /* !__GNUC_MINOR__ */
#ifndef __GNUC_PATCH__
#ifdef __GNUC_PATCHLEVEL__
#   define __GNUC_PATCH__ __GNUC_PATCHLEVEL__
#else /* __GNUC_PATCHLEVEL__ */
#   define __GNUC_PATCH__ 0
#endif /* !__GNUC_PATCHLEVEL__ */
#endif /* !__GNUC_PATCH__ */
#ifndef __GCC_VERSION_NUM
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */
#ifndef __GCC_VERSION
#define __GCC_VERSION(a, b, c) (__GCC_VERSION_NUM >= ((a)*10000 + (b)*100 + (c)))
#endif /* !__GCC_VERSION */


#ifndef __has_attribute
#if (defined(__i386__) || defined(__i386)) && \
    !defined(__x86_64__) && !defined(__x86_64)
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
#if __GCC_VERSION(2,0,0) && !defined(__cplusplus)
#define __GCC_HAS_ATTRIBUTE___transparent_union__
#endif
#if __GCC_VERSION(2,3,0)
#define __GCC_HAS_ATTRIBUTE___format__
#endif
#if __GCC_VERSION(2,5,0)
#define __GCC_HAS_ATTRIBUTE___noreturn__
#define __GCC_HAS_ATTRIBUTE___const__
#endif
#if __GCC_VERSION(2,7,0)
#define __GCC_HAS_ATTRIBUTE___unused__
#endif
#if __GCC_VERSION(2,96,0)
#define __GCC_HAS_ATTRIBUTE___pure__
#endif
#if __GCC_VERSION(3,0,0) /* __GCC_VERSION(2,96,0) */
#define __GCC_HAS_ATTRIBUTE___malloc__
#endif
#if __GCC_VERSION(3,1,0)
#define __GCC_HAS_ATTRIBUTE___noinline__
#define __GCC_HAS_ATTRIBUTE___used__
#define __GCC_HAS_ATTRIBUTE___deprecated__ /*  - __GCC_VERSION(3,1,0)
                                            *  - __GCC_VERSION(3,2,0)
                                            *  - __GCC_VERSION(3,5,0)
                                            * The internet isn't unanimous about this one... */

#endif
#if __GCC_VERSION(3,3,0)
#define __GCC_HAS_ATTRIBUTE___nothrow__
#define __GCC_HAS_ATTRIBUTE___nonnull__
#define __GCC_HAS_ATTRIBUTE___warn_unused_result__ /* __GCC_VERSION(3,3,0) / __GCC_VERSION(3,4,0) */
#endif
#if __GCC_VERSION(3,5,0)
#define __GCC_HAS_ATTRIBUTE___sentinel__
#endif
#if __GCC_VERSION(4,3,0)
#define __GCC_HAS_ATTRIBUTE___alloc_size__
#define __GCC_HAS_ATTRIBUTE___hot__
#define __GCC_HAS_ATTRIBUTE___cold__
#endif
#if __GCC_VERSION(4,4,0)
#define __GCC_HAS_ATTRIBUTE___optimize__
#endif
#if __GCC_VERSION(4,5,0)
#define __GCC_HAS_ATTRIBUTE___noclone__
#endif
#if __GCC_VERSION(4,9,0)
#define __GCC_HAS_ATTRIBUTE___assume_aligned__
#endif
#if __GCC_VERSION(5,4,0)
#define __GCC_HAS_ATTRIBUTE___alloc_align__
#endif
#if __GCC_VERSION(7,0,0)
#define __GCC_HAS_ATTRIBUTE___fallthrough__
#endif
#define __has_attribute(x) __GCC_PRIVATE_IS_DEFINED(__GCC_HAS_ATTRIBUTE_##x)
#endif /* !__has_attribute */
#ifndef __has_cpp_attribute
#define __NO_has_cpp_attribute 1
#define __has_cpp_attribute(x) 0
#endif /* !__has_cpp_attribute */
#ifndef __has_feature
#define __NO_has_feature 1
#define __has_feature(x) 0
#endif /* !__has_feature */
#ifndef __has_builtin
#include "gcc-builtins.h"
#endif /* !__has_builtin */

#ifndef __likely
#ifdef __INTELLISENSE__
#   define __likely      /* nothing */
#   define __unlikely    /* nothing */
#elif __has_builtin(__builtin_expect)
#   define __likely(x)   (__builtin_expect(!!(x),1))
#   define __unlikely(x) (__builtin_expect(!!(x),0))
#else
#   define __builtin_expect(x,y) (x)
#   define __NO_builtin_expect 1
#   define __likely      /* Nothing */
#   define __unlikely    /* Nothing */
#endif
#endif /* !__likely */

#if defined(__clang__) || !defined(__DARWIN_NO_LONG_LONG)
#define __COMPILER_HAVE_LONGLONG 1
#endif /* __clang__ || !__DARWIN_NO_LONG_LONG */
#define __COMPILER_HAVE_LONGDOUBLE 1
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO 1
#if __has_feature(__tpp_pragma_deprecated__)
#define __COMPILER_HAVE_PRAGMA_DEPRECATED 1
#endif /* __has_feature(__tpp_pragma_deprecated__) */
#define __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER 1
#ifdef __CC__
#define __COMPILER_HAVE_PRAGMA_PACK 1
#endif /* __CC__ */
#define __COMPILER_HAVE_GCC_ASM 1
#define __COMPILER_HAVE_REGISTER_VARS 1
#ifdef __cplusplus
#define __COMPILER_ASM_BUFFER(T,s,p) (*(T(*)[s])(p))
#else /* __cplusplus */
#define __COMPILER_ASM_BUFFER(T,s,p) (*(struct { __extension__ T __d[s]; } *)(p))
#endif /* !__cplusplus */

/* For whatever reason, g++ refuses to allow trivially
 * constructible+copyable+etc. classes within unnamed structs:
 *     https://stackoverflow.com/questions/39069799/rules-for-anonymous-aggregates
 */
#if !defined(__cplusplus) || defined(__INTELLISENSE__)
#define __COMPILER_HAVE_TRANSPARENT_STRUCT 1
#define __COMPILER_HAVE_TRANSPARENT_UNION 1
#endif /* !__cplusplus || __INTELLISENSE__ */

#ifdef __CPROTO__
#include "cproto.h"
#endif /* __CPROTO__ */

#ifndef __cplusplus
/* XXX: When was this added in C? */
#   define __COMPILER_HAVE_AUTOTYPE 1
#elif __has_feature(cxx_auto_type) || \
     (defined(__cplusplus) && __GCC_VERSION(4,4,0))
#     define __auto_type              auto
#     define __COMPILER_HAVE_AUTOTYPE 1
#endif

#if __has_feature(cxx_static_assert) || \
   (__GCC_VERSION(4,3,0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L))
#   define __STATIC_ASSERT(expr)         static_assert(expr,#expr)
#   define __STATIC_ASSERT_MSG(expr,msg) static_assert(expr,msg)
#elif defined(_Static_assert) || __has_feature(c_static_assert) || \
     (!defined(__cplusplus) && ( \
     (defined(__STDC_VERSION__) && __STDC_VERSION__+0 >= 201112L) || \
     (__GCC_VERSION(4,6,0) && !defined(__STRICT_ANSI__))))
#   define __STATIC_ASSERT(expr)         _Static_assert(expr,#expr)
#   define __STATIC_ASSERT_MSG(expr,msg) _Static_assert(expr,msg)
#elif defined(__TPP_COUNTER)
#   define __STATIC_ASSERT(expr)         extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__TPP_COUNTER(__static_assert))[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__TPP_COUNTER(__static_assert))[(expr)?1:-1]
#elif defined(__COUNTER__)
#   define __STATIC_ASSERT(expr)         extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__COUNTER__)[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__COUNTER__)[(expr)?1:-1]
#else
#   define __STATIC_ASSERT(expr)         extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__LINE__)[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) extern __ATTR_UNUSED int __PP_CAT2(__static_assert_,__LINE__)[(expr)?1:-1]
#endif
#if defined(__INTELLISENSE__) && !defined(__INTELLISENSE_GCC__)
#   define __ASMNAME(x)   /* Nothing */
#else
#   define __ASMNAME(x)   __asm__(x)
#endif
//#define __NO_ASMNAME 1 /* TO-DO: Remove me */
#if !__GCC_VERSION(2,7,0)
#ifndef __attribute__
#   define __attribute__(x) /* Nothing */
#endif /* !__attribute__ */
#endif
#if !__GCC_VERSION(2,8,0)
#ifndef __extension__
#   define __extension__
#endif /* !__extension__ */
#endif
#define __COMPILER_HAVE_TYPEOF 1
#if __GCC_VERSION(3,1,0)
#   define __ATTR_NOINLINE         __attribute__((__noinline__))
#else
#   define __NO_ATTR_NOINLINE      1
#   define __ATTR_NOINLINE         /* Nothing */
#endif
#if __GCC_VERSION(2,5,0)
#   define __ATTR_NORETURN         __attribute__((__noreturn__))
#else
#   define __NO_ATTR_NORETURN      1
#   define __ATTR_NORETURN         /* Nothing */
#endif
#if defined(__cplusplus) && __has_cpp_attribute(fallthrough)
#define __ATTR_FALLTHROUGH         [[fallthrough]];
#elif __has_attribute(fallthrough)
#define __ATTR_FALLTHROUGH         __attribute__((__fallthrough__));
#else
#define __NO_ATTR_FALLTHROUGH      1
#define __ATTR_FALLTHROUGH         /* Nothing */
#endif
#define __NO_ATTR_W64              1
#define __ATTR_W64                 /* Nothing */
#if (defined(__i386__) || defined(__i386)) && \
    !defined(__x86_64__) && !defined(__x86_64)
#   define __ATTR_FASTCALL         __attribute__((__fastcall__))
#   define __ATTR_STDCALL          __attribute__((__stdcall__))
#if !defined(__INTELLISENSE__)
#   define __ATTR_CDECL            /* [default] */
#else
#   define __ATTR_CDECL            __attribute__((__cdecl__))
#endif
#else
#   define __NO_ATTR_FASTCALL      1
#   define __ATTR_FASTCALL         /* Nothing */
#   define __NO_ATTR_STDCALL       1
#   define __ATTR_STDCALL          /* Nothing */
#   define __NO_ATTR_CDECL         1
#   define __ATTR_CDECL            /* Nothing */
#endif
#if __has_attribute(__clrcall__)
#   define __ATTR_CLRCALL          __attribute__((__clrcall__))
#else
#   define __NO_ATTR_CLRCALL       1
#   define __ATTR_CLRCALL          /* Nothing */
#endif
#if __has_attribute(__thiscall__)
#   define __ATTR_THISCALL         __attribute__((__thiscall__))
#else
#   define __NO_ATTR_THISCALL      1
#   define __ATTR_THISCALL         /* Nothing */
#endif
#if defined(__x86_64__) || defined(__x86_64)
#   define __VA_LIST_IS_ARRAY      1
#   define __ATTR_MSABI            __attribute__((__ms_abi__))
#   define __ATTR_SYSVABI          __attribute__((__sysv_abi__))
#else
#   define __NO_ATTR_MSABI         1
#   define __ATTR_MSABI            /* Nothing */
#   define __NO_ATTR_SYSVABI       1
#   define __ATTR_SYSVABI          /* Nothing */
#endif
#if __has_attribute(__leaf__)
#   define __ATTR_LEAF             __attribute__((__leaf__))
#else
#   define __NO_ATTR_LEAF          1
#   define __ATTR_LEAF             /* Nothing */
#endif
#if __has_attribute(__pure__)
#   define __ATTR_PURE             __attribute__((__pure__))
#elif !defined(__NO_ATTR_LEAF)
#   define __ATTR_PURE             __ATTR_LEAF
#else
#   define __NO_ATTR_PURE          1
#   define __ATTR_PURE             /* Nothing */
#endif
#if __has_attribute(__const__)
#   define __ATTR_CONST            __attribute__((__const__))
#elif !defined(__NO_ATTR_PURE)
#   define __ATTR_CONST            __ATTR_PURE
#elif !defined(__NO_ATTR_LEAF)
#   define __ATTR_CONST            __ATTR_LEAF
#else
#   define __NO_ATTR_CONST         1
#   define __ATTR_CONST            /* Nothing */
#endif
#if __has_attribute(__flatten__)
#   define __ATTR_FLATTEN          __attribute__((__flatten__))
#else
#   define __NO_ATTR_FLATTEN       1
#   define __ATTR_FLATTEN          /* Nothing */
#endif
#if __has_attribute(__malloc__)
#   define __ATTR_MALLOC           __attribute__((__malloc__))
#else
#   define __NO_ATTR_MALLOC        1
#   define __ATTR_MALLOC           /* Nothing */
#endif
#if __has_attribute(__alloc_size__)
#   define __ATTR_ALLOC_SIZE(ppars) __attribute__((__alloc_size__ ppars))
#else
#   define __NO_ATTR_ALLOC_SIZE    1
#   define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#endif
#if __has_attribute(__unused__)
#   define __ATTR_UNUSED           __attribute__((__unused__))
#else
#   define __NO_ATTR_UNUSED        1
#   define __ATTR_UNUSED           /* Nothing */
#endif
#if __has_attribute(__used__)
#   define __ATTR_USED             __attribute__((__used__))
#else
#   define __NO_ATTR_USED          1
#   define __ATTR_USED             /* Nothing */
#endif
#if __has_attribute(__deprecated__)
#   define __ATTR_DEPRECATED_      __attribute__((__deprecated__))
#if __GCC_VERSION(4,5,0)
#   define __ATTR_DEPRECATED(text) __attribute__((__deprecated__(text)))
#else
#   define __ATTR_DEPRECATED(text) __attribute__((__deprecated__))
#endif
#else
#   define __NO_ATTR_DEPRECATED    1
#   define __ATTR_DEPRECATED_      /* Nothing */
#   define __ATTR_DEPRECATED(text) /* Nothing */
#endif
#if __has_attribute(__sentinel__)
#   define __ATTR_SENTINEL         __attribute__((__sentinel__))
#ifdef __INTELLISENSE__
#   define __ATTR_SENTINEL_O(x)    __attribute__((__sentinel__))
#else
#   define __ATTR_SENTINEL_O(x)    __attribute__((__sentinel__(x)))
#endif
#else
#   define __NO_ATTR_SENTINEL      1
#   define __NO_ATTR_SENTINEL_O    1
#   define __ATTR_SENTINEL         /* Nothing */
#   define __ATTR_SENTINEL_O(x)    /* Nothing */
#endif
#if __has_attribute(__hot__)
#   define __ATTR_HOT              __attribute__((__hot__))
#else
#   define __NO_ATTR_HOT           1
#   define __ATTR_HOT              /* Nothing */
#endif
#if __has_attribute(__cold__)
#   define __ATTR_COLD             /*__attribute__((__cold__))*/
#else
#   define __NO_ATTR_COLD          1
#   define __ATTR_COLD             /* Nothing */
#endif
#if __has_attribute(__noclone__)
#   define __ATTR_NOCLONE          __attribute__((__noclone__))
#else
#   define __NO_ATTR_NOCLONE       1
#   define __ATTR_NOCLONE          /* Nothing */
#endif
#if __GCC_VERSION(4,8,0)
#   define __ATTR_THREAD           __thread
#else
#   define __NO_ATTR_THREAD        1
#   define __ATTR_THREAD           /* Nothing */
#endif
#if __has_attribute(__assume_aligned__)
#   define __ATTR_ASSUME_ALIGNED(n) __attribute__((__assume_aligned__(n)))
#else
#   define __NO_ATTR_ASSUME_ALIGNED 1
#   define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#endif
#if __has_attribute(__alloc_align__)
#   define __ATTR_ALLOC_ALIGN(pari) __attribute__((__alloc_align__(pari)))
#else
#   define __NO_ATTR_ALLOC_ALIGN   1
#   define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
#endif
#if __has_attribute(__nothrow__)
#   define __ATTR_NOTHROW          __attribute__((__nothrow__))
#else
#   define __NO_ATTR_NOTHROW       1
#   define __ATTR_NOTHROW          /* Nothing */
#endif
#if __has_attribute(__optimize__)
#   define __ATTR_OPTIMIZE(opt)    __attribute__((__optimize__(opt)))
#else
#   define __NO_ATTR_OPTIMIZE      1
#   define __ATTR_OPTIMIZE(opt)    /* Nothing */
#endif
#if __has_attribute(__transparent_union__) && !defined(__cplusplus)
#   define __ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#else
#   define __NO_ATTR_TRANSPARENT_UNION 1
#   define __ATTR_TRANSPARENT_UNION    /* Nothing */
#endif
/* format-printer attributes. */
#if __has_attribute(__format__)
#   define __ATTR_FORMAT_PRINTF(fmt,args) __attribute__((__format__(__printf__,fmt,args)))
#else
#   define __NO_ATTR_FORMAT_PRINTF        1
#   define __ATTR_FORMAT_PRINTF(fmt,args) /* Nothing */
#endif
#if !defined(__NO_ATTR_FORMAT_PRINTF) /* TODO: There were added later. - But when exactly? */
#   define __ATTR_FORMAT_SCANF(fmt,args)    __attribute__((__format__(__scanf__,fmt,args)))
#   define __ATTR_FORMAT_STRFMON(fmt,args)  __attribute__((__format__(__strfmon__,fmt,args)))
#   define __ATTR_FORMAT_STRFTIME(fmt,args) __attribute__((__format__(__strftime__,fmt,0)))
#else
#   define __NO_ATTR_FORMAT_SCANF           1
#   define __NO_ATTR_FORMAT_STRFMON         1
#   define __NO_ATTR_FORMAT_STRFTIME        1
#   define __ATTR_FORMAT_SCANF(fmt,args)    /* Nothing */
#   define __ATTR_FORMAT_STRFMON(fmt,args)  /* Nothing */
#   define __ATTR_FORMAT_STRFTIME(fmt,args) /* Nothing */
#endif
#if !defined(__ELF__) && \
    (defined(__PE__) || defined(_WIN32) || defined(__CYGWIN__))
#   define __ATTR_DLLIMPORT        __attribute__((__dllimport__))
#   define __ATTR_DLLEXPORT        __attribute__((__dllexport__))
#else
#   define __NO_ATTR_DLLIMPORT     1
#   define __ATTR_DLLIMPORT        /* Nothing */
#   define __NO_ATTR_DLLEXPORT     1
#   define __ATTR_DLLEXPORT        /* Nothing */
#endif
#if __has_attribute(__nonnull__)
#   define __ATTR_NONNULL(ppars)   __attribute__((__nonnull__ ppars))
#else
#   define __NO_ATTR_NONNULL       1
#   define __ATTR_NONNULL(ppars)   /* Nothing */
#endif
#if __has_attribute(__warn_unused_result__)
#   define __ATTR_WUNUSED          __attribute__((__warn_unused_result__))
#else
#   define __NO_ATTR_WUNUSED       1
#   define __ATTR_WUNUSED          /* Nothing */
#endif

#define __ATTR_WARNING(text)       __attribute__((__warning__(text)))
#define __ATTR_ERROR(text)         __attribute__((__error__(text)))
#define __ATTR_SECTION(name)       __attribute__((__section__(name)))
#define __ATTR_RETNONNULL          __attribute__((__returns_nonnull__))
#define __ATTR_PACKED              __attribute__((__packed__))
#define __ATTR_ALIAS(name)         __attribute__((__alias__(name)))
#define __ATTR_ALIGNED(n)          __attribute__((__aligned__(n)))
#define __ATTR_WEAK                __attribute__((__weak__))
#define __ATTR_RETURNS_TWICE       __attribute__((__returns_twice__))
#define __ATTR_EXTERNALLY_VISIBLE  __attribute__((__externally_visible__))
#define __ATTR_VISIBILITY(vis)     __attribute__((__visibility__(vis)))

/* Same as the *_P-less variants, however these should be used for function
 * typedefs, since some compilers don't allow these kinds of attributes on
 * those. */
#define __ATTR_LEAF_P   __ATTR_LEAF
#define __ATTR_PURE_P   __ATTR_PURE
#define __ATTR_CONST_P  __ATTR_CONST

/* Suppress warnings about `-Wsuggest-attribute=const' or `-Wsuggest-attribute=pure' */
#define __COMPILER_IMPURE() __asm__("")



#if __has_attribute(__selectany__)
#   define __ATTR_SELECTANY        __attribute__((__selectany__))
#else
#   define __NO_ATTR_SELECTANY     1
#   define __ATTR_SELECTANY        /* Nothing */
#endif

#ifdef __INTELLISENSE_GCC__
#   define __PRIVATE_PRAGMA(...)   _Pragma(#__VA_ARGS__)
#   define __pragma(...) __PRIVATE_PRAGMA(__VA_ARGS__)
#   define __XBLOCK                /* nothing */
#   define __XRETURN               /* nothing */
#   define __builtin_assume_has_sideeffects 1
#   define __builtin_assume(x)     (!(x) ? __builtin_unreachable() : (void)0)
#elif defined(__INTELLISENSE__)
#   define __XBLOCK(...)           (([&]__VA_ARGS__)())
#   define __XRETURN               return
#   define __builtin_assume_has_sideeffects 1
#   define __builtin_assume(x)     __assume(x)
#else
#if __GCC_VERSION(4,4,0) || defined(__TPP_VERSION__)
#   define __PRIVATE_PRAGMA(...)   _Pragma(#__VA_ARGS__)
#   define __pragma(...)           __PRIVATE_PRAGMA(__VA_ARGS__)
#else
#   define __NO_pragma             1
#   define __pragma(...)           /* Nothing */
#endif
#   define __XBLOCK                __extension__
#   define __XRETURN               /* Nothing */
#if !__has_builtin(__builtin_assume)
#if 1
#   define __builtin_assume_has_sideeffects 1
#   define __builtin_assume(x)     (!(x) ? __builtin_unreachable() : (void)0)
#else
#   undef __builtin_assume_has_sideeffects
#   define __NO_builtin_assume     1
#   define __builtin_assume(x)     (void)0
#endif
#endif /* !__has_builtin(__builtin_assume) */
#endif
#if __GCC_VERSION(4,3,0) && (!defined(__GCCXML__) && \
   !defined(__clang__) && !defined(unix) && \
   !defined(__unix__)) || defined(__LP64__)
#   define __COMPILER_ALIGNOF      __alignof__
#elif defined(__clang__)
#   define __COMPILER_ALIGNOF      __alignof
#elif defined(__cplusplus)
extern "C++" { template<class T> struct __compiler_alignof { char __x; T __y; }; }
#   define __COMPILER_ALIGNOF(T)   (sizeof(__compiler_alignof<__typeof__(T)>)-sizeof(T))
#else
#   define __COMPILER_ALIGNOF(T)   ((__SIZE_TYPE__)&((struct{ char __x; T __y; } *)0)->__y)
#endif
#if defined(__NO_INLINE__) && 0
#   define __NO_ATTR_INLINE        1
#   define __ATTR_INLINE           /* Nothing */
#elif defined(inline) || defined(__cplusplus) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L)
#   define __ATTR_INLINE           inline
#elif __GCC_VERSION(2,7,0)
#   define __ATTR_INLINE           __inline__
#else
#   define __NO_ATTR_INLINE        1
#   define __ATTR_INLINE           /* Nothing */
#endif
#if __GCC_VERSION(3,0,0)
#   define __ATTR_FORCEINLINE      __ATTR_INLINE __attribute__((__always_inline__))
#elif __GCC_VERSION(2,7,0)
#   define __NO_ATTR_FORCEINLINE   1
#   define __ATTR_FORCEINLINE      __ATTR_INLINE
#else
#   define __NO_ATTR_FORCEINLINE   1
#   define __ATTR_FORCEINLINE      /* Nothing */
#endif
#define __LOCAL       static __ATTR_INLINE
#define __FORCELOCAL  static __ATTR_FORCEINLINE
#ifndef __LONGLONG
#ifdef __CC__
__extension__ typedef long long __longlong_t;
__extension__ typedef unsigned long long __ulonglong_t;
#define __LONGLONG   __longlong_t
#define __ULONGLONG  __ulonglong_t
#endif /* __CC__ */
#endif /* !__LONGLONG */

#if !__GCC_VERSION(2,92,0) /* !__GCC_VERSION(2,95,0) */
#ifndef __restrict
#if defined(restrict) || \
   (defined(__STDC_VERSION__) && __STDC_VERSION__+0 >= 199901L)
#   define __restrict restrict
#else
#   define __restrict /* Nothing */
#endif
#endif /* !__restrict */
#ifndef __restrict__
#define __restrict__   __restrict
#endif /* !__restrict__ */
#endif

#if __GCC_VERSION(3,1,0) && !defined(__GNUG__)
#   define __restrict_arr __restrict
#else
#   define __restrict_arr /* Nothing */
#endif
#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS 1
#if 1
#define __COMPILER_FLEXIBLE_ARRAY(T,x) T x[]
#elif 1
#define __COMPILER_FLEXIBLE_ARRAY(T,x) __extension__ T x[0]
#else
#define __COMPILER_FLEXIBLE_ARRAY(T,x) T x[1024]
#endif

#define __STATIC_IF(x)   if(x)
#if 1
#define __STATIC_ELSE(x) else
#else
#define __STATIC_ELSE(x) if(!(x))
#endif
#ifdef __cplusplus
#define __IF0     if(false)
#define __IF1     if(true)
#define __WHILE0  while(false)
#define __WHILE1  while(true)
#else /* __cplusplus */
#define __IF0     if(0)
#define __IF1     if(1)
#define __WHILE0  while(0)
#define __WHILE1  while(1)
#endif /* !__cplusplus */

#ifdef __cplusplus
#if !defined(__INTEL_VERSION__) || __INTEL_VERSION__ >= 600 || \
    (_WCHAR_T_DEFINED+0 != 0) || (_WCHAR_T+0 != 0)
#define __native_wchar_t_defined 1
#define __wchar_t_defined 1
#endif
#endif /* __cplusplus */

#ifndef __INTELLISENSE__
#define __FUNCTION__   __extension__ __FUNCTION__
#endif /* !__INTELLISENSE__ */

#if !__has_builtin(__builtin_LINE)
#define __builtin_LINE()     __LINE__
#define __builtin_FUNCTION() __FUNCTION__
#define __builtin_FILE()     __FILE__
#endif /* !__has_builtin(__builtin_LINE) */

#if !__has_builtin(__builtin_unreachable)
#define __builtin_unreachable() __XBLOCK({ for (;;); (void)0; })
#endif /* !__has_builtin(__builtin_unreachable) */

#if !__has_builtin(__builtin_object_size)
#define __builtin_object_size(ptr,type) ((type) < 2 ? (__SIZE_TYPE__)-1 : 0)
#endif /* !__has_builtin(__builtin_object_size) */


#if __GCC_VERSION(4,7,0)
#   define __COMPILER_BARRIER()       __atomic_signal_fence(__ATOMIC_ACQ_REL)
#   define __COMPILER_READ_BARRIER()  __atomic_signal_fence(__ATOMIC_ACQUIRE)
#   define __COMPILER_WRITE_BARRIER() __atomic_signal_fence(__ATOMIC_RELEASE)
#elif defined(__COMPILER_HAVE_GCC_ASM)
#   define __COMPILER_BARRIERS_ALL_IDENTICAL 1
#   define __COMPILER_BARRIER()       __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#   define __COMPILER_READ_BARRIER()  __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#   define __COMPILER_WRITE_BARRIER() __XBLOCK({ __asm__ __volatile__("" : : : "memory"); (void)0; })
#else
#   define __COMPILER_BARRIERS_ALL_IDENTICAL 1
#   define __COMPILER_BARRIER()       __sync_synchronize()
#   define __COMPILER_READ_BARRIER()  __sync_synchronize()
#   define __COMPILER_WRITE_BARRIER() __sync_synchronize()
#endif

#define __COMPILER_IGNORE_UNINITIALIZED(var) var=var

#ifdef __cplusplus
#ifdef __INTELLISENSE__
#   define __NULLPTR nullptr
#else /* __INTELLISENSE__ */
#   define __NULLPTR 0
#endif /* !__INTELLISENSE__ */
#else /* __cplusplus */
#   define __NULLPTR ((void *)0)
#endif /* !__cplusplus */

#ifdef __cplusplus
/* `__builtin_choose_expr()' is only available in C, but not in C++ */
#undef __builtin_choose_expr
#define __NO_builtin_choose_expr 1
#define __builtin_choose_expr(c, tt, ff) ((c) ? (tt) : (ff))

/* `__builtin_types_compatible_p()' isn't consistently defined by g++.
 * So to prevent problems with that, simply re-implement it using a
 * macro alongside C++ templates. */
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
#undef __builtin_types_compatible_p
#define __builtin_types_compatible_p(...) (::__intern::__gcc_types_compatible< __VA_ARGS__ >::__val)
#endif /* __cplusplus */


