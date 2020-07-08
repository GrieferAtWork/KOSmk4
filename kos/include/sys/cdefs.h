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
#ifndef __GCC_VERSION_NUM
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
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */
#define __GNUC_PREREQ(a, b) (__GCC_VERSION_NUM >= ((a)*10000 + (b)*100))
#else /* __GNUC__ */
#define __GNUC_PREREQ(a, b) 0
#endif /* !__GNUC__ */

#define __BEGIN_DECLS __DECL_BEGIN
#define __END_DECLS   __DECL_END



#undef __P
#undef __PMT
#ifdef __NO_PROTOTYPES
#define __P(args)   ()
#define __PMT(args) ()
#else /* __NO_PROTOTYPES */
#define __P(args)   args
#define __PMT(args) args
#endif /* !__NO_PROTOTYPES */
#define __LEAF_ATTR __ATTR_LEAF

#if __GNUC_PREREQ(4, 6) || __has_attribute(__leaf__)
#define __LEAF , __leaf__
#else
#define __LEAF /* nothing */
#endif

#ifdef __cplusplus
#define __THROW    __CXX_NOEXCEPT
#define __THROWNL  __CXX_NOEXCEPT
#define __NTH(fct) __LEAF_ATTR fct __CXX_NOEXCEPT
#else /* __cplusplus */
#define __THROW    __ATTR_NOTHROW __ATTR_LEAF
#define __THROWNL  __ATTR_NOTHROW
#define __NTH(fct) __ATTR_NOTHROW __ATTR_LEAF fct
#endif /* !__cplusplus */

#define __CONCAT __PP_PRIVATE_CAT2
#define __STRING __PP_PRIVATE_STR
#define __ptr_t  void *
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __long_double_t __LONGDOUBLE
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__cplusplus) && defined(_GLIBCPP_USE_NAMESPACES)
#define __BEGIN_NAMESPACE_STD       __NAMESPACE_STD_BEGIN
#define __END_NAMESPACE_STD         __NAMESPACE_STD_END
#define __USING_NAMESPACE_STD       __NAMESPACE_STD_USING
#define __BEGIN_NAMESPACE_C99       namespace __c99 {
#define __END_NAMESPACE_C99         }
#define __USING_NAMESPACE_C99(name) using __c99::name;
#else /* __cplusplus && _GLIBCPP_USE_NAMESPACES */
#define __BEGIN_NAMESPACE_STD
#define __END_NAMESPACE_STD
#define __USING_NAMESPACE_STD(name)
#define __BEGIN_NAMESPACE_C99
#define __END_NAMESPACE_C99
#define __USING_NAMESPACE_C99(name)
#endif /* !__cplusplus || !_GLIBCPP_USE_NAMESPACES */

#if __has_builtin(__builtin_object_size)
#define __bos(ptr)  __builtin_object_size(ptr, __USE_FORTIFY_LEVEL > 1)
#define __bos0(ptr) __builtin_object_size(ptr, 0)
#else /* __has_builtin(__builtin_object_size) */
#include <hybrid/typecore.h>
#define __bos(ptr)  (__CCAST(__SIZE_TYPE__) - 1)
#define __bos0(ptr) (__CCAST(__SIZE_TYPE__) - 1)
#endif /* !__has_builtin(__builtin_object_size) */

#define __warndecl(name, msg)  extern __ATTR_WARNING(msg) void(name)(void)
#define __warnattr(msg)        __ATTR_WARNING(msg)
#define __errordecl(name, msg) extern __ATTR_ERROR(msg) void(name)(void)

#ifndef __flexarr
#ifdef __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#define __flexarr []
#elif defined(__GNUC__) /* XXX: Other compilers? */
#define __flexarr [0]
#else /* ... */
#define __flexarr [1]
#endif /* !... */
#endif /* !__flexarr */

#ifndef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX_IS_EMPTY 1
#define __USER_LABEL_PREFIX__        /* nothing */
#endif /* !__USER_LABEL_PREFIX__ */

#ifdef __USER_LABEL_PREFIX_IS_EMPTY
#define __ASMNAMESTR(cname) cname
#else /* __USER_LABEL_PREFIX_IS_EMPTY */
#define __ASMNAMESTR2(prefix, cname) __STRING(prefix) cname
#define __ASMNAMESTR(cname)          __ASMNAMESTR2(__USER_LABEL_PREFIX__, cname)
#endif /* !__USER_LABEL_PREFIX_IS_EMPTY */

#if !defined(__REDIRECT) && !defined(__NO_ASMNAME)
#define __REDIRECT(name, proto, alias) name proto __ASMNAME(__ASMNAMESTR(#alias))
#endif /* !__REDIRECT && !__NO_ASMNAME */

#if !defined(__REDIRECT_NTH) && !defined(__NO_ASMNAME)
#ifdef __cplusplus
#define __REDIRECT_NTH(name, proto, alias) name proto __THROW __ASMNAME(__ASMNAMESTR(#alias))
#else /* __cplusplus */
#define __REDIRECT_NTH(name, proto, alias) name proto __ASMNAME(__ASMNAMESTR(#alias)) __THROW
#endif /* !__cplusplus */
#endif /* !__REDIRECT_NTH && !__NO_ASMNAME */

#if !defined(__REDIRECT_NTHNL) && !defined(__NO_ASMNAME)
#ifdef __cplusplus
#define __REDIRECT_NTHNL(name, proto, alias) name proto __THROWNL __ASMNAME(__ASMNAMESTR(#alias))
#else /* __cplusplus */
#define __REDIRECT_NTHNL(name, proto, alias) name proto __ASMNAME(__ASMNAMESTR(#alias)) __THROWNL
#endif /* !__cplusplus */
#endif /* !__REDIRECT_NTHNL && !__NO_ASMNAME */


#define __attribute_malloc__             __ATTR_MALLOC
#define __attribute_alloc_size__         __ATTR_ALLOC_SIZE
#define __attribute_pure__               __ATTR_PURE
#define __attribute_const__              __ATTR_CONST
#define __attribute_used__               __ATTR_USED
#define __attribute_noinline__           __ATTR_NOINLINE
#define __attribute_deprecated__         __ATTR_DEPRECATED_
#define __nonnull                        __ATTR_NONNULL
#define __attribute_warn_unused_result__ __ATTR_WUNUSED
#define __attribute_format_strfmon__     __ATTR_FORMAT_STRFMON
#define __always_inline                  __ATTR_FORCEINLINE
#define __attribute_artificial__         __ATTR_ARTIFICIAL
#define __glibc_unlikely                 __unlikely
#define __glibc_likely                   __likely

#if defined(__USE_FORTIFY_LEVEL) && (__USE_FORTIFY_LEVEL + 0) > 0
#define __wur __ATTR_WUNUSED
#else /* __USE_FORTIFY_LEVEL > 0 */
#define __wur /* Nothing */
#endif /* __USE_FORTIFY_LEVEL <= 0 */

#if __GNUC_PREREQ(2, 8) || __has_attribute(__format_arg__)
#define __attribute_format_arg__(x) __attribute__((__format_arg__(x)))
#else /* __GNUC_PREREQ(2, 8) || __has_attribute(__format_arg__) */
#define __attribute_format_arg__(x) /* Nothing */
#endif /* !__GNUC_PREREQ(2, 8) && !__has_attribute(__format_arg__) */
#ifndef __NO_EXTERN_INLINE
#define __extern_inline        __EXTERN_INLINE
#define __extern_always_inline __EXTERN_FORCEINLINE
#define __fortify_function     __EXTERN_FORCEINLINE __ATTR_ARTIFICIAL
#endif /* !__NO_EXTERN_INLINE */
#if __GNUC_PREREQ(4, 3) || __has_builtin(__builtin_va_arg_pack)
#define __va_arg_pack() __builtin_va_arg_pack()
#endif /* __GNUC_PREREQ(4, 3) || __has_builtin(__builtin_va_arg_pack) */
#if __GNUC_PREREQ(4, 3) || __has_builtin(__builtin_va_arg_pack_len)
#define __va_arg_pack_len() __builtin_va_arg_pack_len()
#endif /* __GNUC_PREREQ(4, 3) || __has_builtin(__builtin_va_arg_pack_len) */
#if (!defined(_Noreturn) &&                                               \
     (defined(__STDC_VERSION__) ? (__STDC_VERSION__ + 0) : 0) < 201112 && \
     !__GNUC_PREREQ(4, 7))
#define _Noreturn __ATTR_NORETURN
#endif /* ... */
#if (!defined(_Static_assert) && !defined(__cplusplus) &&               \
     (defined(__STDC_VERSION__) ? __STDC_VERSION__ + 0 : 0) < 201112 && \
     (!__GNUC_PREREQ(4, 6) || defined(__STRICT_ANSI__)))
#define _Static_assert(expr, diagnostic) __STATIC_ASSERT(expr)
#endif /* !... */

#include <bits/wordsize.h>
#if (defined(__LONG_DOUBLE_MATH_OPTIONAL) && \
     defined(__NO_LONG_DOUBLE_MATH))
#define __LDBL_COMPAT 1
#ifdef __REDIRECT
#define __LDBL_REDIR1(name, proto, alias)       __REDIRECT(name, proto, alias)
#define __LDBL_REDIR(name, proto)               __LDBL_REDIR1(name, proto, __nldbl_##name)
#define __LDBL_REDIR1_NTH(name, proto, alias)   __REDIRECT_NTH(name, proto, alias)
#define __LDBL_REDIR_NTH(name, proto)           __LDBL_REDIR1_NTH(name, proto, __nldbl_##name)
#define __LDBL_REDIR1_DECL(name, alias)         extern __typeof(name) name __asm(__ASMNAME(#alias));
#define __LDBL_REDIR_DECL(name)                 extern __typeof(name) name __asm(__ASMNAME("__nldbl_" #name));
#define __REDIRECT_LDBL(name, proto, alias)     __LDBL_REDIR1(name, proto, __nldbl_##alias)
#define __REDIRECT_NTH_LDBL(name, proto, alias) __LDBL_REDIR1_NTH(name, proto, __nldbl_##alias)
#endif /* __REDIRECT */
#endif /* __LONG_DOUBLE_MATH_OPTIONAL && __NO_LONG_DOUBLE_MATH */
#if !defined(__LDBL_COMPAT) || !defined(__REDIRECT)
#define __LDBL_REDIR1(name, proto, alias)     name proto
#define __LDBL_REDIR(name, proto)             name proto
#define __LDBL_REDIR1_NTH(name, proto, alias) name proto __THROW
#define __LDBL_REDIR_NTH(name, proto)         name proto __THROW
#define __LDBL_REDIR_DECL(name)
#ifdef __REDIRECT
#define __REDIRECT_LDBL(name, proto, alias)     __REDIRECT(name, proto, alias)
#define __REDIRECT_NTH_LDBL(name, proto, alias) __REDIRECT_NTH(name, proto, alias)
#endif /* __REDIRECT */
#endif /* !__LDBL_COMPAT || !__REDIRECT */

#ifdef __USE_BSD
#include <hybrid/typecore.h>
#ifndef __dead2
#define __dead2 __ATTR_NORETURN
#endif /* !__dead2 */
#ifndef __pure2
#define __pure2 __ATTR_CONST
#endif /* !__pure2 */
#ifndef __packed
#define __packed __ATTR_PACKED
#endif /* !__packed */
#ifndef __aligned
#define __aligned(x) __ATTR_ALIGNED(x)
#endif /* !__aligned */
#ifndef __unused
#define __unused __ATTR_UNUSED
#endif /* !__unused */
#ifndef __printflike
#define __printflike __ATTR_FORMAT_PRINTF
#endif /* !__printflike */
#ifndef __bounded__
#define __bounded__(x, y, z)
#endif /* !__bounded__ */
#ifndef __arraycount
#define __arraycount __COMPILER_LENOF
#endif /* !__arraycount */
#ifndef __offsetof
#define __offsetof __builtin_offsetof
#endif /* !__offsetof */
#ifndef __rangeof
#define __rangeof(type, start, end)  \
	(__builtin_offsetof(type, end) - \
	 __builtin_offsetof(type, start))
#endif /* !__rangeof */
#ifndef __containerof
#define __containerof __COMPILER_CONTAINER_OF
#endif /* !__containerof */
#ifndef __RCSID
#define __RCSID(x) /* nothing */
#endif /* !__RCSID */
#ifndef __FBSDID
#define __FBSDID(x) /* nothing */
#endif /* !__FBSDID */
#ifndef __RCSID_SOURCE
#define __RCSID_SOURCE(x) /* nothing */
#endif /* !__RCSID_SOURCE */
#ifndef __SCCSID
#define __SCCSID(x) /* nothing */
#endif /* !__SCCSID */
#ifndef __COPYRIGHT
#define __COPYRIGHT(x) /* nothing */
#endif /* !__COPYRIGHT */
#ifndef __DECONST
#define __DECONST(type, var) ((type)(__UINTPTR_TYPE__)(void const *)(var))
#endif /* !__DECONST */
#ifndef __DEVOLATILE
#define __DEVOLATILE(type, var) ((type)(__UINTPTR_TYPE__)(void volatile *)(var))
#endif /* !__DEVOLATILE */
#ifndef __DEQUALIFY
#define __DEQUALIFY(type, var) ((type)(__UINTPTR_TYPE__)(void const volatile *)(var))
#endif /* !__DEQUALIFY */
#endif /* __USE_BSD */


#endif /* !_SYS_CDEFS_H */
