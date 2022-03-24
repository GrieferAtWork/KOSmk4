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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/cdefs.h) */
/* (#) Portability: DJGPP         (/include/sys/cdefs.h) */
/* (#) Portability: FreeBSD       (/sys/sys/cdefs.h) */
/* (#) Portability: GNU C Library (/misc/sys/cdefs.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/cdefs.h) */
/* (#) Portability: NetBSD        (/sys/sys/cdefs.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/cdefs.h) */
/* (#) Portability: OpenBSD       (/sys/sys/cdefs.h) */
/* (#) Portability: diet libc     (/include/sys/cdefs.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/cdefs.h) */
/* (#) Portability: libc4/5       (/include/sys/cdefs.h) */
/* (#) Portability: uClibc        (/include/sys/cdefs.h) */
#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/typesizes.h>

#ifndef _FEATURES_H
#include <features.h>
#endif /* !_FEATURES_H */

/* NOTE: KOS doesn't actually make use of this header!
 *    >> It is only provided to define all the stuff glibc does,
 *       allowing  the KOS toolchain  the potential of compiling
 *       applications  that may rely on this non-standard header
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
#define __P(args)     ()
#define __PMT(args)   ()
#ifndef _PARAMS
#define _PARAMS(args) ()
#endif /* !_PARAMS */
#define _AND                        ;
#define _NOARGS                     /* Nothing */
#define _CONST                      /* Nothing */
#define _VOLATILE                   /* Nothing */
#define _SIGNED                     /* Nothing */
#define _DOTS                       /* Nothing */
#define _VOID                       void
#define _EXFUN(name, proto)         name()
#define _DEFUN(name, arglist, args) name arglist args;
#define _DEFUN_VOID(name)           name()
#define _CAST_VOID                  /* Nothing */
#else /* __NO_PROTOTYPES */
#define __P(args)     args
#define __PMT(args)   args
#ifndef _PARAMS
#define _PARAMS(args) args
#endif /* !_PARAMS */
#define __ptr_t                     void *
#define _PTR                        void *
#define _AND                        ,
#define _NOARGS                     void
#define _CONST                      const
#define _VOLATILE                   volatile
#define _SIGNED                     signed
#define _DOTS                       , ...
#define _VOID                       void
#define _EXFUN(name, proto)         (name) proto
#define _DEFUN(name, arglist, args) (name)(args)
#define _DEFUN_VOID(name)           (name)(void)
#define _CAST_VOID                  (void)
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
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __long_double_t __LONGDOUBLE
#define _LONG_DOUBLE    __LONGDOUBLE
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
#ifdef __USE_FORTIFY_LEVEL
#define __bos(ptr)  __builtin_object_size(ptr, __USE_FORTIFY_LEVEL > 1)
#else /* __USE_FORTIFY_LEVEL */
#define __bos(ptr)  __builtin_object_size(ptr, 0)
#endif /* !__USE_FORTIFY_LEVEL */
#define __bos0(ptr) __builtin_object_size(ptr, 0)
#else /* __has_builtin(__builtin_object_size) */
#define __bos(ptr)  (__CCAST(__SIZE_TYPE__)-1)
#define __bos0(ptr) (__CCAST(__SIZE_TYPE__)-1)
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
#define __USER_LABEL_PREFIX_IS_EMPTY
#define __USER_LABEL_PREFIX__ /* nothing */
#endif /* !__USER_LABEL_PREFIX__ */

#ifdef __USER_LABEL_PREFIX_IS_EMPTY
#define __ASMNAMESTR(cname) cname
#else /* __USER_LABEL_PREFIX_IS_EMPTY */
#define __ASMNAMESTR2(prefix, cname) __PP_PRIVATE_STR(prefix) cname
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

#ifndef __BOUNDED_POINTERS__
#define __bounded                        /* nothing */
#define __unbounded                      /* nothing */
#define __ptrvalue                       /* nothing */
#endif /* !__BOUNDED_POINTERS__ */
#define __ptr_t                          void *
#define __long_double_t                  __LONGDOUBLE
#define __expect                         __builtin_expect
#define __pure                           __ATTR_PURE
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
#define __attribute_dontuse__            __ATTR_DEPRECATED_
#define __attribute_used                 __ATTR_USED
#define __needsNULL__                    __ATTR_SENTINEL
#define __attribute_alloc__(x)           __ATTR_ALLOC_SIZE((x))
#define __attribute_alloc2__(x, y)       __ATTR_ALLOC_SIZE((x, y))
#define __attribute_formatarg__          __ATTR_FORMAT_ARG
#undef _ATTRIBUTE
#define _ATTRIBUTE(attrs)                __attribute__((attrs))

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
#define _EXTERN_INLINE         __EXTERN_INLINE
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
#if (!defined(_Noreturn) && !defined(__ATTR_NORETURN_IS__NORETURN) &&     \
     (defined(__STDC_VERSION__) ? (__STDC_VERSION__ + 0) : 0) < 201112 && \
     !__GNUC_PREREQ(4, 7))
#define _Noreturn __ATTR_NORETURN
#endif /* ... */
#if (!defined(_Static_assert) && !defined(__cplusplus) &&               \
     !defined(__STATIC_ASSERT_IS__STATIC_ASSERT) &&                     \
     (defined(__STDC_VERSION__) ? __STDC_VERSION__ + 0 : 0) < 201112 && \
     (!__GNUC_PREREQ(4, 6) || defined(__STRICT_ANSI__)))
#define _Static_assert(expr, diagnostic) __STATIC_ASSERT(expr)
#endif /* !... */
#if !defined(__alignof) && !defined(__COMPILER_ALIGNOF_IS___ALIGNOF)
#define __alignof(x) __COMPILER_ALIGNOF(x)
#endif /* !__alignof && !__COMPILER_ALIGNOF_IS___ALIGNOF */
#if !defined(_Alignof) && !defined(__COMPILER_ALIGNOF_IS__ALIGNOF)
#define _Alignof(x) __COMPILER_ALIGNOF(x)
#endif /* !_Alignof && !__COMPILER_ALIGNOF_IS__ALIGNOF */
#if !defined(_Alignas) && !defined(__ATTR_ALIGNED_IS__ALIGNAS)
#define _Alignas(x) __ATTR_ALIGNED(x)
#endif /* !_Alignas && !__ATTR_ALIGNED_IS__ALIGNAS */
#if !defined(_Thread_local) && !defined(__ATTR_THREAD_IS__THREAD_LOCAL)
#define _Thread_local __ATTR_THREAD
#endif /* !_Thread_local && !__ATTR_THREAD_IS__THREAD_LOCAL */
#if !defined(__restrict__) && !defined(__RESTRICT_IS___RESTRICT__)
#define __restrict__ __restrict
#endif /* !__restrict__ && !__RESTRICT_IS___RESTRICT__ */
#if !defined(restrict) && !defined(__RESTRICT_IS_RESTRICT)
#define restrict __restrict
#endif /* !restrict && !__RESTRICT_IS_RESTRICT */
#if !defined(inline) && !defined(__ATTR_INLINE_IS_INLINE) && !defined(__NO_ATTR_INLINE)
#define inline __ATTR_INLINE
#endif /* !inline && !__ATTR_INLINE_IS_INLINE && !__NO_ATTR_INLINE */
#if !defined(__inline) && !defined(__ATTR_INLINE_IS___INLINE) && !defined(__NO_ATTR_INLINE)
#define __inline __ATTR_INLINE
#endif /* !inline && !__ATTR_INLINE_IS___INLINE && !__NO_ATTR_INLINE */
#if !defined(__inline__) && !defined(__ATTR_INLINE_IS___INLINE__) && !defined(__NO_ATTR_INLINE)
#define __inline__ __ATTR_INLINE
#endif /* !__inline__ && !__ATTR_INLINE_IS___INLINE__ && !__NO_ATTR_INLINE */


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
/* Attributes/Annotations */
#define __compactcall         /* nothing */
#define __aconst              /* nothing */
#define __CTASSERT            __STATIC_ASSERT
#define __BEGIN_EXTERN_C      __DECL_BEGIN
#define __END_EXTERN_C        __DECL_END
#define __malloc_like         __ATTR_MALLOC
#define __dead2               __ATTR_NORETURN
#define __pure2               __ATTR_CONST
#define __noinline            __ATTR_NOINLINE
#define __result_use_check    __ATTR_WUNUSED
#define __returns_twice       __ATTR_RETURNS_TWICE
#define __unreachable         __builtin_unreachable
#define __predict_true        __likely
#define __predict_false       __unlikely
#define __null_sentinel       __ATTR_SENTINEL
#define __exported            __ATTR_VISIBILITY("default")
#define __hidden              __ATTR_VISIBILITY("hidden")
#define __dso_public          __ATTR_VISIBILITY("default")
#define __dso_hidden          __ATTR_VISIBILITY("hidden")
#define __dso_protected       __ATTR_VISIBILITY("protected")
#define __packed              __ATTR_PACKED
#define __aligned(x)          __ATTR_ALIGNED(x)
#define __unused              __ATTR_UNUSED
#define __printflike          __ATTR_FORMAT_PRINTF
#define __scanflike           __ATTR_FORMAT_SCANF
#define __format_arg          __attribute_format_arg__
#define __strfmonlike         __ATTR_FORMAT_STRFMON
#define __strftimelike        __ATTR_FORMAT_STRFTIME
#define __printf0like(x, y)   /* __attribute__((__format__ (__printf0__, x, y))) */
#define __bounded__(x, y, z)  /* nothing */
#define __weak_symbol         __ATTR_WEAK
#define __used                __ATTR_USED
#define __section             __ATTR_SECTION
#define __alloc_size(x)       __ATTR_ALLOC_SIZE((x))
#define __alloc_size2(n, x)   __ATTR_ALLOC_SIZE((n, x))
#define __alloc_align(x)      __ATTR_ALLOC_ALIGN(x)
#ifndef __ATTR_FASTCALL_IS___FASTCALL
#define __fastcall         __ATTR_FASTCALL
#endif /* !__ATTR_FASTCALL_IS___FASTCALL */
#ifndef NDEBUG
#define __diagused         /* nothing */
#else /* !NDEBUG */
#define __diagused         __ATTR_UNUSED
#endif /* NDEBUG */
#ifdef DEBUG
#define __debugused        /* nothing */
#else /* DEBUG */
#define __debugused        __ATTR_UNUSED
#endif /* !DEBUG */
#if __has_attribute(__no_instrument_function__)
#define __noprofile        __attribute__((__no_instrument_function__))
#else /* ... */
#define __noprofile        /* nothing */
#endif /* !... */
#ifdef __INTELLISENSE__
#define __c99inline        static
#elif __has_attribute(__gnu_inline__) && defined(__GNUC_STDC_INLINE__)
#define __c99inline        extern __attribute__((__gnu_inline__)) __ATTR_INLINE
#elif !defined(__NO_ATTR_INLINE)
#define __c99inline        __ATTR_INLINE
#endif /* ... */
#if (!defined(__cplusplus) &&                       \
     (defined(__clang__) || __GNUC_PREREQ(4, 6)) && \
     (!defined(__STDC_VERSION__) || (__STDC_VERSION__ >= 199901)))
#define __min_size(x)      static(x)
#else /* ... */
#define __min_size(x)      (x)
#endif /* !... */
#if (__has_attribute(__argument_with_type_tag__) && \
     __has_attribute(__type_tag_for_datatype__))
#define __arg_type_tag(arg_kind, arg_idx, type_tag_idx) __attribute__((__argument_with_type_tag__(arg_kind, arg_idx, type_tag_idx)))
#define __datatype_type_tag(kind, type)                 __attribute__((__type_tag_for_datatype__(kind, type)))
#else /* __has_attribute(__argument_with_type_tag__) && __has_attribute(__type_tag_for_datatype__) */
#define __arg_type_tag(arg_kind, arg_idx, type_tag_idx)
#define __datatype_type_tag(kind, type)
#endif /* !__has_attribute(__argument_with_type_tag__) || !__has_attribute(__type_tag_for_datatype__) */
#if __has_extension(c_thread_safety_attributes)
#define __lock_annotate(x) __attribute__((x))
#else /* __has_extension(c_thread_safety_attributes) */
#define __lock_annotate(x)
#endif /* !__has_extension(c_thread_safety_attributes) */
#define __lockable                __lock_annotate(lockable)
#define __locks_exclusive(...)    __lock_annotate(exclusive_lock_function(__VA_ARGS__))
#define __locks_shared(...)       __lock_annotate(shared_lock_function(__VA_ARGS__))
#define __trylocks_exclusive(...) __lock_annotate(exclusive_trylock_function(__VA_ARGS__))
#define __trylocks_shared(...)    __lock_annotate(shared_trylock_function(__VA_ARGS__))
#define __unlocks(...)            __lock_annotate(unlock_function(__VA_ARGS__))
#define __asserts_exclusive(...)  __lock_annotate(assert_exclusive_lock(__VA_ARGS__))
#define __asserts_shared(...)     __lock_annotate(assert_shared_lock(__VA_ARGS__))
#define __requires_exclusive(...) __lock_annotate(exclusive_locks_required(__VA_ARGS__))
#define __requires_shared(...)    __lock_annotate(shared_locks_required(__VA_ARGS__))
#define __requires_unlocked(...)  __lock_annotate(locks_excluded(__VA_ARGS__))
#define __no_lock_analysis        __lock_annotate(no_thread_safety_analysis)
#ifndef __guarded_by
#define __guarded_by(x)           __lock_annotate(guarded_by(x))
#endif /* !__guarded_by */
#define __pt_guarded_by(x)        __lock_annotate(pt_guarded_by(x))

/* Scope modifiers */
#ifdef __COMPILER_HAVE_PRAGMA_GCC_VISIBILITY
#define __BEGIN_PUBLIC_DECLS _Pragma("GCC visibility push(default)") __DECL_BEGIN
#define __END_PUBLIC_DECLS   _Pragma("GCC visibility push(hidden)")  __DECL_END
#define __BEGIN_HIDDEN_DECLS __DECL_BEGIN _Pragma("GCC visibility pop")
#define __END_HIDDEN_DECLS   __DECL_END   _Pragma("GCC visibility pop")
#else /* __COMPILER_HAVE_PRAGMA_GCC_VISIBILITY */
#define __BEGIN_PUBLIC_DECLS __DECL_BEGIN
#define __END_PUBLIC_DECLS   __DECL_END
#define __BEGIN_HIDDEN_DECLS __DECL_BEGIN
#define __END_HIDDEN_DECLS   __DECL_END
#endif /* !__COMPILER_HAVE_PRAGMA_GCC_VISIBILITY */

/* Helper functions/macros */
#define __arraycount                __COMPILER_LENOF
#define __offsetof                  __builtin_offsetof
#define __rangeof(type, start, end) (__builtin_offsetof(type, end) - __builtin_offsetof(type, start))
#define __containerof               __COMPILER_CONTAINER_OF
#define __DECONST(type, var)        ((type)(__UINTPTR_TYPE__)(void const *)(var))
#define __DEVOLATILE(type, var)     ((type)(__UINTPTR_TYPE__)(void volatile *)(var))
#define __DEQUALIFY(type, var)      ((type)(__UINTPTR_TYPE__)(void const volatile *)(var))
#define __UNCONST(a)                ((void *)(__ULONGPTR_TYPE__)(void const *)(a))
#define __UNVOLATILE(a)             ((void *)(__ULONGPTR_TYPE__)(void volatile *)(a))
#define __FPTRCAST(t, f)            ((t)(void *)(f))
#define __insn_barrier()            __COMPILER_BARRIER()
#define __compiler_membar()         __COMPILER_BARRIER()
#ifdef __cplusplus
#define __static_cast(T, val)       static_cast<T>(val)
#else /* __cplusplus */
#define __static_cast(T, val)       (T)val
#endif /* !__cplusplus */
#ifdef __COMPILER_HAVE_C11_GENERIC
#define	__generic(expr, t, yes, no) _Generic(expr, t: yes, default: no)
#elif (!defined(__NO_builtin_choose_expr) && !defined(__NO_builtin_types_compatible_p) && defined(__COMPILER_HAVE_TYPEOF))
#define __generic(expr, t, yes, no) __builtin_choose_expr(__builtin_types_compatible_p(__typeof(expr), t), yes, no)
#endif /* ... */
#if !defined(__func__) && !defined(__builtin_FUNCTION_IS___func__)
#define __func__                    __builtin_FUNCTION()
#endif /* !__func__ && !__builtin_FUNCTION_IS___func__ */
#undef __CONCAT
#define __CONCAT1                   __PP_PRIVATE_CAT2
#define __CONCAT                    __PP_CAT2
#define __XSTRING                   __PP_STR

/* Declarations */
#define __RCSID(x)                      /* nothing */
#define __FBSDID(x)                     /* nothing */
#define __RCSID_SOURCE(x)               /* nothing */
#define __SCCSID(x)                     /* nothing */
#define __COPYRIGHT(x)                  /* nothing */
#define __strict_weak_alias(alias, sym) __weak_reference(sym, alias)
#ifdef __COMPILER_HAVE_GCC_ASM
#define __strong_reference(sym, alias)  __asm__(".set " #alias ", " #sym)
#define __weak_reference(sym, alias)    __asm__(".weak " #alias "\n.set " #alias ", " #sym)
#define __warn_references(sym, msg)     __asm__(".section .gnu.warning." #sym "\n.asciz \"" msg "\"\n.previous")
#define __sym_compat(sym, impl, verid)  __asm__(".symver " #impl ", " #sym "@" #verid)
#define __sym_default(sym, impl, verid) __asm__(".symver " #impl ", " #sym "@@@" #verid)
#define __GLOBL1(sym)                   __asm__(".globl " #sym)
#define __GLOBL(sym)                    __GLOBL1(sym)
#else /* __COMPILER_HAVE_GCC_ASM */
#define __strong_reference(sym, alias)  /* nothing */
#define __weak_reference(sym, alias)    /* nothing */
#define __warn_references(sym, msg)     /* nothing */
#define __sym_compat(sym, impl, verid)  /* nothing */
#define __sym_default(sym, impl, verid) /* nothing */
#define __GLOBL1(sym)                   /* nothing */
#define __GLOBL(sym)                    /* nothing */
#endif /* !__COMPILER_HAVE_GCC_ASM */
#define __IDSTRING(name, string)        /* nothing */
#if defined(__clang__) && __has_feature(nullability)
#define __NULLABILITY_PRAGMA_PUSH       _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wnullability-completeness\"")
#define __NULLABILITY_PRAGMA_POP        _Pragma("clang diagnostic pop")
#else /* __clang__ && __has_feature(nullability) */
#define _Nonnull                        /* nothing */
#define _Nullable                       /* nothing */
#define _Null_unspecified               /* nothing */
#define __NULLABILITY_PRAGMA_PUSH       /* nothing */
#define __NULLABILITY_PRAGMA_POP        /* nothing */
#endif /* !__clang__ || !__has_feature(nullability) */


/* Features */
#ifndef __COMPILER_HAVE_LONGLONG
#define __LONG_LONG_SUPPORTED
#endif /* __COMPILER_HAVE_LONGLONG */
#if (defined(__COVERITY__) ||                                             \
     __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__) || \
     __has_feature(leak_sanitizer) || defined(__SANITIZE_LEAK__))
#define __NO_LEAKS
#endif /* ... */
#ifdef __COMPILER_HAVE_GCC_ASM
#define __GNUCLIKE_ASM 3
#endif /* __COMPILER_HAVE_GCC_ASM */
#if (__has_builtin(__builtin_huge_val) && \
     __has_builtin(__builtin_inf) &&      \
     __has_builtin(__builtin_nan))
#define __GNUCLIKE_MATH_BUILTIN_CONSTANTS
#endif /* __has_builtin(...) */
#ifdef __COMPILER_HAVE_TYPEOF
#define __GNUCLIKE___TYPEOF 1
#endif /* __COMPILER_HAVE_TYPEOF */
#define __GNUCLIKE___OFFSETOF 1
#ifndef __NO_ATTR_SECTION
#define __GNUCLIKE___SECTION 1
#endif /* !__NO_ATTR_SECTION */
#ifndef __NO_builtin_constant_p
#define __GNUCLIKE_BUILTIN_CONSTANT_P 1
#endif /* !__NO_builtin_constant_p */
#define __GNUCLIKE_BUILTIN_VARARGS   1
#define __GNUCLIKE_BUILTIN_STDARG    1
#define __GNUCLIKE_BUILTIN_VAALIST   1
#define __GNUC_VA_LIST_COMPATIBILITY 1
#if __has_builtin(__builtin_next_arg)
#define __GNUCLIKE_BUILTIN_NEXT_ARG 1
#endif /* __has_builtin(__builtin_next_arg) */
/*#define __GNUCLIKE_CTOR_SECTION_HANDLING ??? */
#if __has_builtin(__builtin_isunordered)
#define __GNUCLIKE_MATH_BUILTIN_RELOPS
#endif /* __has_builtin(__builtin_isunordered) */
#if __has_builtin(__builtin_memcpy)
#define __GNUCLIKE_BUILTIN_MEMCPY 1
#endif /* __has_builtin(__builtin_memcpy) */
/*#define __CC_SUPPORTS_INLINE             -- TODO*/
/*#define __CC_SUPPORTS___INLINE           -- TODO*/
/*#define __CC_SUPPORTS___INLINE__         -- TODO*/
/*#define __CC_SUPPORTS___FUNC__           -- TODO*/
/*#define __CC_SUPPORTS_WARNING            -- TODO*/
/*#define __CC_SUPPORTS_VARADIC_XXX        -- TODO*/
/*#define __CC_SUPPORTS_DYNAMIC_ARRAY_INIT -- TODO*/
#define __GNUC_PREREQ__ __GNUC_PREREQ
#if !defined(__LONG_LONG_SUPPORTED) && defined(__COMPILER_HAVE_LONGLONG)
#define __LONG_LONG_SUPPORTED
#endif /* !__LONG_LONG_SUPPORTED && __COMPILER_HAVE_LONGLONG */
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#endif /* __USE_BSD */


/* On GLibc, this header unconditionally #includes <bits/wordsize.h>,
 * which  defines  a  bunch of  arch-specific  configuration helpers.
 * Since programs might therefor expect <sys/cdefs.h> to define those
 * same macros on  other platforms, emulate  macros from that  header
 * here, since KOS doesn't have <bits/wordsize.h> (any more) */

/* __WORDSIZE = __SIZEOF_POINTER__ * __CHAR_BIT__ */
#ifndef __WORDSIZE
#if __SIZEOF_POINTER__ == 1
#define __WORDSIZE 8
#elif __SIZEOF_POINTER__ == 2
#define __WORDSIZE 16
#elif __SIZEOF_POINTER__ == 4
#define __WORDSIZE 32
#elif __SIZEOF_POINTER__ == 8
#define __WORDSIZE 64
#else /* __SIZEOF_POINTER__ == ... */
#define __WORDSIZE (__SIZEOF_POINTER__ * 8)
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !__WORDSIZE */

#ifndef __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_SYSCALL_LONG_T__   __SIZEOF_REGISTER__
#endif /* !__SIZEOF_SYSCALL_LONG_T__ */

#ifndef __SIZEOF_TIME32_T__
#define __SIZEOF_TIME32_T__         4
#endif /* !__SIZEOF_TIME32_T__ */
#ifndef __SIZEOF_TIME64_T__
#define __SIZEOF_TIME64_T__         8
#endif /* !__SIZEOF_TIME64_T__ */

/* __SYSCALL_WORDSIZE = __SIZEOF_SYSCALL_LONG_T__ * __CHAR_BIT__ */
#if __SIZEOF_SYSCALL_LONG_T__ == 1
#define __SYSCALL_WORDSIZE 8
#elif __SIZEOF_SYSCALL_LONG_T__ == 2
#define __SYSCALL_WORDSIZE 16
#elif __SIZEOF_SYSCALL_LONG_T__ == 4
#define __SYSCALL_WORDSIZE 32
#elif __SIZEOF_SYSCALL_LONG_T__ == 8
#define __SYSCALL_WORDSIZE 64
#else /* __SIZEOF_SYSCALL_LONG_T__ == ... */
#define __SYSCALL_WORDSIZE (__SIZEOF_SYSCALL_LONG_T__ * 8)
#endif /* __SIZEOF_SYSCALL_LONG_T__ != ... */

/* defined(__WORDSIZE_TIME64_COMPAT32) = __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __WORDSIZE_TIME64_COMPAT32 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#endif /* !_SYS_CDEFS_H */
