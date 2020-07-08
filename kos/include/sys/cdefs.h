/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1

#include <__stdinc.h>
#ifndef _FEATURES_H
#include <features.h>
#endif /* !_FEATURES_H */

/* NOTE: KOS doesn't actually make use of this header!
 *    >> It is only provided to define all the stuff glibc does,
 *       allowing the KOS toolchain the potential of compiling
 *       applications that may rely on this non-standard header
 *       and its contents. */

#ifdef __GNUC__
#define __GNUC_PREREQ(a, b) (__GCC_VERSION_NUM >= ((a)*10000 + (b)*100))
#else /* __GNUC__ */
#define __GNUC_PREREQ(a, b) 0
#endif /* !__GNUC__ */

#undef __P
#undef __PMT
#if __GNUC_PREREQ(4,6)
#   define __LEAF                    ,__leaf__
#   define __LEAF_ATTR __attribute__((__leaf__))
#else
#   define __LEAF
#   define __LEAF_ATTR
#endif
#if !defined(__cplusplus) && __GNUC_PREREQ(3,3)
#   define __THROW     __attribute__((__nothrow__ __LEAF))
#   define __THROWNL   __attribute__((__nothrow__))
#   define __NTH(fct)  __attribute__((__nothrow__ __LEAF)) fct
#elif defined __cplusplus && __GNUC_PREREQ(2,8)
#   define __THROW     throw()
#   define __THROWNL   throw()
#   define __NTH(fct)  __LEAF_ATTR fct throw()
#else
#   define __THROW
#   define __THROWNL
#   define __NTH(fct)  fct
#endif
#   define __P(args)       args
#   define __PMT(args)     args
#   define __CONCAT(x,y)   x##y
#   define __STRING(x)     #x
#   define __ptr_t         void *
#   define __long_double_t __LONGDOUBLE
#ifdef __cplusplus
#   define __BEGIN_DECLS extern "C" {
#   define __END_DECLS   }
#else
#   define __BEGIN_DECLS
#   define __END_DECLS
#endif
#if defined(__cplusplus) && defined(_GLIBCPP_USE_NAMESPACES)
#   define __BEGIN_NAMESPACE_STD       namespace std {
#   define __END_NAMESPACE_STD         }
#   define __USING_NAMESPACE_STD(name) using std::name;
#   define __BEGIN_NAMESPACE_C99       namespace __c99 {
#   define __END_NAMESPACE_C99         }
#   define __USING_NAMESPACE_C99(name) using __c99::name;
#else
#   define __BEGIN_NAMESPACE_STD
#   define __END_NAMESPACE_STD
#   define __USING_NAMESPACE_STD(name)
#   define __BEGIN_NAMESPACE_C99
#   define __END_NAMESPACE_C99
#   define __USING_NAMESPACE_C99(name)
#endif
#   define __bos(ptr)  __builtin_object_size(ptr,__USE_FORTIFY_LEVEL > 1)
#   define __bos0(ptr) __builtin_object_size(ptr,0)
#if __GNUC_PREREQ(4,3)
#   define __warndecl(name,msg)  extern void (name)(void) __attribute__((__warning__(msg)))
#   define __warnattr(msg)                                __attribute__((__warning__(msg)))
#   define __errordecl(name,msg) extern void (name)(void) __attribute__((__error__(msg)))
#else
#   define __warndecl(name,msg) extern void (name)(void)
#   define __warnattr(msg)
#   define __errordecl(name,msg) extern void (name)(void)
#endif
#if __GNUC_PREREQ(2,97)
#   define __flexarr    []
#elif defined(__GNUC__)
#   define __flexarr    [0]
#elif defined(__STDC_VERSION__) && __STDC_VERSION__+0 >= 199901L
#   define __flexarr    []
#else
#   define __flexarr    [1]
#endif
#if defined(__GNUC__) && __GNUC__ >= 2
#   define __REDIRECT(name,proto,alias) name proto __asm__(__ASMNAMESTR(#alias))
#ifdef __cplusplus
#   define __REDIRECT_NTH(name,proto,alias)   name proto __THROW __asm__(__ASMNAMESTR(#alias))
#   define __REDIRECT_NTHNL(name,proto,alias) name proto __THROWNL __asm__(__ASMNAMESTR(#alias))
#else
#   define __REDIRECT_NTH(name,proto,alias)   name proto __asm__(__ASMNAMESTR(#alias)) __THROW
#   define __REDIRECT_NTHNL(name,proto,alias) name proto __asm__(__ASMNAMESTR(#alias)) __THROWNL
#endif
#   define __ASMNAMESTR(cname)         __ASMNAMESTR2(__USER_LABEL_PREFIX__,cname)
#   define __ASMNAMESTR2(prefix,cname) __STRING(prefix) cname
#endif
#   define __attribute_malloc__             __ATTR_MALLOC
#   define __attribute_alloc_size__(params) __ATTR_ALLOC_SIZE(params)
#   define __attribute_pure__               __ATTR_PURE
#   define __attribute_const__              __ATTR_CONST
#   define __attribute_used__               __ATTR_USED
#   define __attribute_noinline__           __ATTR_NOINLINE
#   define __attribute_deprecated__         __ATTR_DEPRECATED_
#   define __nonnull(params)                __ATTR_NONNULL(params)
#   define __attribute_warn_unused_result__ __ATTR_WUNUSED
#if __USE_FORTIFY_LEVEL > 0
#   define __wur                         __ATTR_WUNUSED
#else
#   define __wur                         /* Nothing */
#endif
#if __GNUC_PREREQ(2,8)
#   define __attribute_format_arg__(x)   __attribute__((__format_arg__(x)))
#else
#   define __attribute_format_arg__(x)   /* Nothing */
#endif
#if __GNUC_PREREQ(2,97)
#   define __attribute_format_strfmon__(a,b) __attribute__((__format__(__strfmon__,a,b)))
#else
#   define __attribute_format_strfmon__(a,b) /* Nothing */
#endif
#if __GNUC_PREREQ(3,2)
#   define __always_inline __inline      __attribute__((__always_inline__))
#else
#   define __always_inline __inline
#endif
#if __GNUC_PREREQ(4,3)
#   define __attribute_artificial__      __attribute__((__artificial__))
#else
#   define __attribute_artificial__      /* Nothing */
#endif
#if (!defined(__cplusplus) || __GNUC_PREREQ(4,3) || \
    (defined(__clang__) && (defined(__GNUC_STDC_INLINE__) || defined(__GNUC_GNU_INLINE__))))
#if defined(__GNUC_STDC_INLINE__) || defined(__cplusplus)
#   define __extern_inline        extern __inline __attribute__ ((__gnu_inline__))
#   define __extern_always_inline extern __always_inline __attribute__ ((__gnu_inline__))
#else
#   define __extern_inline        extern __inline
#   define __extern_always_inline extern __always_inline
#endif
#endif
#ifdef __extern_always_inline
#   define __fortify_function     __extern_always_inline __attribute_artificial__
#endif
#if __GNUC_PREREQ(4,3)
#   define __va_arg_pack()        __builtin_va_arg_pack()
#   define __va_arg_pack_len()    __builtin_va_arg_pack_len()
#endif
#if !__GNUC_PREREQ(2,8)
#   define __extension__          /* Nothing */
#endif
#if !__GNUC_PREREQ(2,92)
#   define __restrict             /* Nothing */
#endif
#   define __glibc_unlikely(cond)    __unlikely(cond)
#   define __glibc_likely(cond)      __likely(cond)
#if (!defined(_Noreturn) && \
     (defined(__STDC_VERSION__) ? __STDC_VERSION__+0 : 0) < 201112 && !__GNUC_PREREQ(4, 7))
#define _Noreturn __ATTR_NORETURN
#endif
#if (!defined(_Static_assert) && !defined(__cplusplus) \
     && (defined(__STDC_VERSION__) ? __STDC_VERSION__+0 : 0) < 201112 \
     && (!__GNUC_PREREQ(4,6) || defined(__STRICT_ANSI__)))
#define _Static_assert(expr, diagnostic) __STATIC_ASSERT(expr)
#endif

#include <bits/wordsize.h>
#if defined(__LONG_DOUBLE_MATH_OPTIONAL) && \
    defined(__NO_LONG_DOUBLE_MATH)
#   define __LDBL_COMPAT 1
#ifdef __REDIRECT
#   define __LDBL_REDIR1(name,proto,alias)       __REDIRECT(name,proto,alias)
#   define __LDBL_REDIR(name,proto)              __LDBL_REDIR1(name,proto,__nldbl_##name)
#   define __LDBL_REDIR1_NTH(name,proto,alias)   __REDIRECT_NTH(name,proto,alias)
#   define __LDBL_REDIR_NTH(name,proto)          __LDBL_REDIR1_NTH(name,proto,__nldbl_##name)
#   define __LDBL_REDIR1_DECL(name,alias)        extern __typeof(name) name __asm(__ASMNAME(#alias));
#   define __LDBL_REDIR_DECL(name)               extern __typeof(name) name __asm(__ASMNAME("__nldbl_" #name));
#   define __REDIRECT_LDBL(name,proto,alias)     __LDBL_REDIR1(name,proto,__nldbl_##alias)
#   define __REDIRECT_NTH_LDBL(name,proto,alias) __LDBL_REDIR1_NTH (name,proto,__nldbl_##alias)
#endif
#endif
#if !defined(__LDBL_COMPAT) || !defined(__REDIRECT)
#   define __LDBL_REDIR1(name,proto,alias)     name proto
#   define __LDBL_REDIR(name,proto)            name proto
#   define __LDBL_REDIR1_NTH(name,proto,alias) name proto __THROW
#   define __LDBL_REDIR_NTH(name,proto)        name proto __THROW
#   define __LDBL_REDIR_DECL(name)
#ifdef __REDIRECT
#   define __REDIRECT_LDBL(name,proto,alias)     __REDIRECT(name,proto,alias)
#   define __REDIRECT_NTH_LDBL(name,proto,alias) __REDIRECT_NTH(name,proto,alias)
#endif
#endif

#endif /* !_SYS_CDEFS_H */
