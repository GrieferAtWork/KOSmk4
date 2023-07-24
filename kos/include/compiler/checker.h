/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#define __P(x) x

#undef __SIZEOF_INT128__
#undef __INT128_TYPE__
#undef __UINT128_TYPE__
#define __SIZEOF_INT128__ 16
#define __INT128_TYPE__ signed __int128
#define __UINT128_TYPE__ unsigned __int128

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

#include "gcc-warnings.h"

#ifndef __GCC_PRIVATE_IS_DEFINED
#define __GCC_PRIVATE_ARG_PLACEHOLDER_ ,
#define __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __GCC_PRIVATE_TAKE_SECOND_ARG(x) __GCC_PRIVATE_TAKE_SECOND_ARG_IMPL x
#define __GCC_PRIVATE_IS_DEFINED3(x) __GCC_PRIVATE_TAKE_SECOND_ARG((x 1, 0))
#define __GCC_PRIVATE_IS_DEFINED2(x) __GCC_PRIVATE_IS_DEFINED3(__GCC_PRIVATE_ARG_PLACEHOLDER_##x)
#define __GCC_PRIVATE_IS_DEFINED(x) __GCC_PRIVATE_IS_DEFINED2(x)
#endif /* !__GCC_PRIVATE_IS_DEFINED */

#undef __has_attribute
#define __has_attribute(x) __GCC_PRIVATE_IS_DEFINED(__GCC_HAS_ATTRIBUTE_##x)
#define __GCC_HAS_ATTRIBUTE___packed__
#define __GCC_HAS_ATTRIBUTE___noreturn__
#define __GCC_HAS_ATTRIBUTE___deref__
#define __GCC_HAS_ATTRIBUTE___noderef__
#define __GCC_HAS_ATTRIBUTE___nothrow__
#define __GCC_HAS_ATTRIBUTE___tag__
#define __GCC_HAS_ATTRIBUTE___require_caller_tag__
#define __GCC_HAS_ATTRIBUTE___aligned__

#undef __has_builtin
#define __has_builtin(x) __GCC_PRIVATE_IS_DEFINED(__GCC_HAS_BUILTIN_##x)
#define __GCC_HAS_BUILTIN___builtin_alloca
#define __GCC_HAS_BUILTIN___builtin_bswap16
#define __GCC_HAS_BUILTIN___builtin_bswap32
#define __GCC_HAS_BUILTIN___builtin_bswap64
#define __GCC_HAS_BUILTIN___builtin_bswap128
#define __GCC_HAS_BUILTIN___builtin_alignof
#define __GCC_HAS_BUILTIN___builtin_expect
#define __GCC_HAS_BUILTIN___builtin_expect_with_probability
#define __GCC_HAS_BUILTIN___builtin_unreachable
#define __GCC_HAS_BUILTIN___builtin_constant_p
#define __GCC_HAS_BUILTIN___builtin_has_attribute
#define __GCC_HAS_BUILTIN___builtin_speculation_safe_value
#define __GCC_HAS_BUILTIN___builtin_assoc_barrier
#define __GCC_HAS_BUILTIN___builtin_offsetof
#define __GCC_HAS_BUILTIN___builtin_add_overflow
#define __GCC_HAS_BUILTIN___builtin_add_overflow_p
#define __GCC_HAS_BUILTIN___builtin_sadd_overflow
#define __GCC_HAS_BUILTIN___builtin_saddl_overflow
#define __GCC_HAS_BUILTIN___builtin_saddll_overflow
#define __GCC_HAS_BUILTIN___builtin_uadd_overflow
#define __GCC_HAS_BUILTIN___builtin_uaddl_overflow
#define __GCC_HAS_BUILTIN___builtin_uaddll_overflow
#define __GCC_HAS_BUILTIN___builtin_sub_overflow
#define __GCC_HAS_BUILTIN___builtin_sub_overflow_p
#define __GCC_HAS_BUILTIN___builtin_ssub_overflow
#define __GCC_HAS_BUILTIN___builtin_ssubl_overflow
#define __GCC_HAS_BUILTIN___builtin_ssubll_overflow
#define __GCC_HAS_BUILTIN___builtin_usub_overflow
#define __GCC_HAS_BUILTIN___builtin_usubl_overflow
#define __GCC_HAS_BUILTIN___builtin_usubll_overflow
#define __GCC_HAS_BUILTIN___builtin_mul_overflow
#define __GCC_HAS_BUILTIN___builtin_mul_overflow_p
#define __GCC_HAS_BUILTIN___builtin_smul_overflow
#define __GCC_HAS_BUILTIN___builtin_smull_overflow
#define __GCC_HAS_BUILTIN___builtin_smulll_overflow
#define __GCC_HAS_BUILTIN___builtin_umul_overflow
#define __GCC_HAS_BUILTIN___builtin_umull_overflow
#define __GCC_HAS_BUILTIN___builtin_umulll_overflow
/* Builtins that we're emulating */
#define __GCC_HAS_BUILTIN___builtin_va_list
#define __GCC_HAS_BUILTIN___builtin_va_start
#define __GCC_HAS_BUILTIN___builtin_va_arg
#define __GCC_HAS_BUILTIN___builtin_va_end
#define __GCC_HAS_BUILTIN___atomic_load_n
#define __GCC_HAS_BUILTIN___atomic_load
#define __GCC_HAS_BUILTIN___atomic_store_n
#define __GCC_HAS_BUILTIN___atomic_store
#define __GCC_HAS_BUILTIN___atomic_exchange_n
#define __GCC_HAS_BUILTIN___atomic_exchange
#define __GCC_HAS_BUILTIN___atomic_compare_exchange_n
#define __GCC_HAS_BUILTIN___atomic_compare_exchange
#define __GCC_HAS_BUILTIN___atomic_add_fetch
#define __GCC_HAS_BUILTIN___atomic_sub_fetch
#define __GCC_HAS_BUILTIN___atomic_and_fetch
#define __GCC_HAS_BUILTIN___atomic_xor_fetch
#define __GCC_HAS_BUILTIN___atomic_or_fetch
#define __GCC_HAS_BUILTIN___atomic_nand_fetch
#define __GCC_HAS_BUILTIN___atomic_fetch_add
#define __GCC_HAS_BUILTIN___atomic_fetch_sub
#define __GCC_HAS_BUILTIN___atomic_fetch_and
#define __GCC_HAS_BUILTIN___atomic_fetch_xor
#define __GCC_HAS_BUILTIN___atomic_fetch_or
#define __GCC_HAS_BUILTIN___atomic_fetch_nand
#define __GCC_HAS_BUILTIN___builtin_assume
#define __GCC_HAS_BUILTIN___builtin_choose_expr
/* Checker-specific builtins */
#define __GCC_HAS_BUILTIN___builtin_offsetafter  /* size_t __builtin_offsetafter(T, fields...) */
#define __GCC_HAS_BUILTIN___builtin_container_of /* T *__builtin_container_of(typeof(((T *)0)->fields) *p, T, fields...) */
#define __GCC_HAS_BUILTIN___builtin_throw        /* __attribute__((noreturn)) void __builtin_throw(int code, ...); */
#define __GCC_HAS_BUILTIN___builtin_void         /* T __builtin_void(T val);  ## Evaluates to `val', but value becomes unknown */
#define __GCC_HAS_BUILTIN___builtin_rvoid        /* T __builtin_rvoid(T val); ## Like `__builtin_void()', but also do r-value */

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
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#endif /* !__likely */

#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
#define __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#define __COMPILER_HAVE_LONGDOUBLE
#ifndef __LONGDOUBLE
#define __LONGDOUBLE long double
#endif /* !__LONGDOUBLE */
#define __COMPILER_HAVE_GCC_ASM
#define __COMPILER_HAVE_PRAGMA_PACK
#define __COMPILER_HAVE_ADDRESSIBLE_LABELS /* void *p = &&foo; goto *p; foo: */
#define __COMPILER_HAVE_TYPEOF
#define __COMPILER_HAVE_LONGLONG
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#define __COMPILER_HAVE_TRANSPARENT_UNION

#ifdef __cplusplus
#define __STATIC_ASSERT_IS_static_assert
#define __STATIC_ASSERT_MSG_IS_static_assert
#define __STATIC_ASSERT(x)        static_assert(x)
#define __STATIC_ASSERT_MSG(x, m) static_assert(x, m)
#else /* __cplusplus */
#define __STATIC_ASSERT_IS__Static_assert
#define __STATIC_ASSERT_MSG_IS__Static_assert
#define __STATIC_ASSERT(x)        _Static_assert(x)
#define __STATIC_ASSERT_MSG(x, m) _Static_assert(x, m)
#endif /* !__cplusplus */

#define __COMPILER_ASMNAME __asm__

#if defined(__x86_64__) || defined(__x86_64)
#if (defined(__PE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || \
     defined(__WINDOWS__) || defined(_WIN16) || defined(WIN16) || defined(_WIN32) ||            \
     defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) ||               \
     defined(__TOS_WIN__) || defined(_WIN32_WCE) || defined(WIN32_WCE))
#undef __VA_LIST_IS_ARRAY /* No on this platform, it's not... */
#else /* ... */
#define __VA_LIST_IS_ARRAY
#endif /* !... */
#endif /* */
#if (defined(__ELF__) || \
     (!defined(__PE__) && !defined(_WIN32) && !defined(__CYGWIN__)))
#define __NO_ATTR_DLLIMPORT
#define __NO_ATTR_DLLEXPORT
#endif /* ... */

#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */


#undef __NO_NON_CALL_EXCEPTIONS
#undef __NON_CALL_EXCEPTIONS
#define __NON_CALL_EXCEPTIONS
#define __checker_attribute__(...) __attribute__((__VA_ARGS__))

/* >> __attribute__((nothrow(<level>))
 * >> __attribute__((nothrow(*<level>))
 * Set  the nothrow level for the annotated  function. When `*' appears before `<level>',
 * scan the argument list of the function and use the greatest nothrow level of arguments
 * instead. If no argument specifies a nothrow level, use the given `<level>'.
 *
 * A  warning will be  issued if a nothrow  function is called  by another function that
 * also has a  nothrow attribute,  and whose nothrow  attribute specifies  a level  that
 * is smaller than the called function. Additionally, a warning is issued for a function
 * that has no nothrow attribute and calls only functions that have nothrow  attributes.
 * The  same also happens when dereferencing a pointer with a greater nothrow level than
 * one's own function.
 *
 * Levels are defined as follows:
 * 0: NOTHROW:     Always nothrow; if this function *were* to throw an exception, that's a crash
 * 1: CHECKED:     Memory that has been checked, but might still throw an exception upon access
 *                 due to OOM, some other thread unmapping memory, etc.
 * 2: NOTHROW_RPC: This function always can throw exception because it serves RPCs
 *
 * >> __attribute__((noderef))
 * >> __attribute__((deref))
 * Specify if this pointer may be dereferenced or not (`deref' is the
 * default and supersedes `noderef' when both attributes are present)
 *
 * >> __attribute__((tag(<name>)))
 * Tag the annotated function with a name. Each function can have at  most
 * 1 tag, and it is possible to assert that the calling function also have
 * some tag (s.a. `require_caller_tag').
 * A warning is generated when trying to assign multiple tags to the same
 * function.
 *
 * >> __attribute__((require_caller_tag(<name>)))
 * Produce a compiler warning if this function is invoked by one that is
 * not tagged as `__attribute__((tag(<name>)))'.
 */
#define __ATTR_NOTHROW          __checker_attribute__(__nothrow__(0))
#define __NOTHROW               __checker_attribute__(__nothrow__(0))
#define __NOTHROW_NCX           __checker_attribute__(__nothrow__(*0))
#define __CXX_NOEXCEPT_NCX      __checker_attribute__(__nothrow__(*0))
#define __NOTHROW_CB            __checker_attribute__(__nothrow__(0), __throws__(*))
#define __NOTHROW_CB_NCX        __checker_attribute__(__nothrow__(*0), __throws__(*))
#define __NOTHROW_RPC           __checker_attribute__(__nothrow__(2))
#define __NOTHROW_RPC_KOS       __checker_attribute__(__nothrow__(2))
#define __NOTHROW_RPC_NOKOS     __checker_attribute__(__nothrow__(2))
#define __CXX_NOEXCEPT_RPC_PURE __checker_attribute__(__nothrow__(2))

#define __ATTR_USER             __checker_attribute__(__nothrow__(1))
#define __ATTR_UNCHECKED        __checker_attribute__(__noderef__, __nothrow__(1))
#define __ATTR_PHYS             __checker_attribute__(__noderef__) /* Physical pointer, only for arithmetic */
#define __ATTR_VIRT             __checker_attribute__(__noderef__) /* Virtual pointer, only for arithmetic */
#define __ATTR_CHECKED          __checker_attribute__(__deref__, __nothrow__(1))
#define __ATTR_BLOCKING         __checker_attribute__(__throws__(E_INTERRUPT))
#define __ATTR_BLOCKING_IF(...) __checker_attribute__(__throws__(E_INTERRUPT)) /* XXX: Condition */

#define __ATTR_THROWS(...)      __checker_attribute__(__throws__(__VA_ARGS__))
#define __ATTR_THROWING         __checker_attribute__(__throws__(...))

#define __ATTR_NOBLOCK          __checker_attribute__(__tag__("NOBLOCK"))
#define __ATTR_NOBLOCK_IF(...)  __checker_attribute__(__tag__("NOBLOCK")) /* XXX: Condition */
#define __ATTR_NOPREEMPT        __checker_attribute__(__tag__("NOPREEMPT"), __require_caller_tag__("NOPREEMPT"))

/* TODO: __throws__(*) to indicate that a function throws exceptions  that
 *       may be thrown by a function pointer it takes as argument. Example
 *       for this would be `format_printf()'
 *       Such a function would then also be `__nothrow__(*0)', and the `*'
 *       must then also inherit  the __nothrow__-tag of function  pointers
 *       passed to the function in question.
 */


#define __ATTR_NORETURN                      __checker_attribute__(__noreturn__)
#define __ATTR_NOINLINE                      /* Nothing */
#define __ATTR_FALLTHROUGH                   /* Nothing */
#define __ATTR_W64                           /* Nothing */
#define __ATTR_FASTCALL                      /* Nothing */
#define __ATTR_STDCALL                       /* Nothing */
#define __ATTR_CDECL                         /* Nothing */
#define __ATTR_CLRCALL                       /* Nothing */
#define __ATTR_THISCALL                      /* Nothing */
#define __ATTR_MSABI                         /* Nothing */
#define __ATTR_SYSVABI                       /* Nothing */
#define __ATTR_LEAF                          /* Nothing */
#define __ATTR_PURE                          /* Nothing */
#define __ATTR_CONST                         /* Nothing */
#define __ATTR_FLATTEN                       /* Nothing */
#define __ATTR_MALLOC                        /* Nothing */
#define __ATTR_ALLOC_SIZE(ppars)             /* Nothing */
#define __ATTR_UNUSED                        /* Nothing */
#define __ATTR_USED                          /* Nothing */
#define __ATTR_DEPRECATED_                   /* Nothing */
#define __ATTR_DEPRECATED(text)              /* Nothing */
#define __ATTR_SENTINEL                      /* Nothing */
#define __ATTR_SENTINEL_O(x)                 /* Nothing */
#define __ATTR_HOT                           /* Nothing */
#define __ATTR_COLD                          /* Nothing */
#define __ATTR_NOCLONE                       /* Nothing */
#define __ATTR_THREAD                        /* Nothing */
#define __ATTR_ASSUME_ALIGNED(n)             /* Nothing */
#define __ATTR_ALLOC_ALIGN(pari)             /* Nothing */
#define __ATTR_OPTIMIZE(opt)                 /* Nothing */
#define __ATTR_FORMAT_PRINTF(fmt, args)      /* Nothing */
#define __ATTR_FORMAT_SCANF(fmt, args)       /* Nothing */
#define __ATTR_FORMAT_STRFMON(fmt, args)     /* Nothing */
#define __ATTR_FORMAT_STRFTIME(fmt, args)    /* Nothing */
#define __ATTR_DLLIMPORT                     /* Nothing */
#define __ATTR_DLLEXPORT                     /* Nothing */
#define __ATTR_NOPLT                         /* Nothing */
#define __ATTR_NONNULL(ppars)                /* Nothing */
#define __ATTR_WUNUSED                       /* Nothing */
#define __ATTR_SELECTANY                     /* Nothing */
#define __ATTR_ACCESS_NONE(ptr_index)        /* Nothing */
#define __ATTR_INS(ptr_index, size_index)    /* Nothing */
#define __ATTR_OUTS(ptr_index, size_index)   /* Nothing */
#define __ATTR_INOUTS(ptr_index, size_index) /* Nothing */
#define __ATTR_IN_OPT(ptr_index)             /* Nothing */
#define __ATTR_OUT_OPT(ptr_index)            /* Nothing */
#define __ATTR_INOUT_OPT(ptr_index)          /* Nothing */
#define __ATTR_IN(ptr_index)                 /* Nothing */
#define __ATTR_OUT(ptr_index)                /* Nothing */
#define __ATTR_INOUT(ptr_index)              /* Nothing */
#define __ATTR_WARNING(text)                 /* Nothing */
#define __ATTR_ERROR(text)                   /* Nothing */
#define __ATTR_SECTION(name)                 /* Nothing */
#define __ATTR_RETNONNULL                    /* Nothing */
#define __ATTR_PACKED                        /* Nothing */
#define __ATTR_ALIAS(name)                   /* Nothing */
#define __ATTR_ALIGNED(n)                    /* Nothing */
#define __ATTR_WEAK                          /* Nothing */
#define __ATTR_RETURNS_TWICE                 /* Nothing */
#define __ATTR_EXTERNALLY_VISIBLE            /* Nothing */
#define __ATTR_VISIBILITY(vis)               /* Nothing */

/* Suppress warnings about `-Wsuggest-attribute=const' or `-Wsuggest-attribute=pure' */
#define __COMPILER_IMPURE() (void)0

#define __COMPILER_ASM_BUFFER(T, s, p) (*(__checker_attribute__(__force__) T(*)[s])(p))
#define __register_var(T, name, regname) T name

#define __pragma(...) _Pragma(#__VA_ARGS__)
#define __XBLOCK  /* Nothing */
#define __XRETURN /* Nothing */
#define __builtin_assume(x) (void)(int(*)[(x) ? 1 : -1])0

#define __COMPILER_ALIGNOF_IS___alignof__
#define __COMPILER_ALIGNOF __alignof__

#define __seg_gs /* Nothing */
#define __seg_fs /* Nothing */

#define __NO_ATTR_FORCEINLINE
#define __ATTR_INLINE        /* Nothing */
#define __ATTR_FORCEINLINE   /* Nothing */
#define __ATTR_ARTIFICIAL    /* Nothing */
#define __ATTR_FORMAT_ARG(x) /* Nothing */
#define __LOCAL              /* Nothing */
#define __FORCELOCAL         /* Nothing */
#define __NO_EXTERN_INLINE
#define __EXTERN_INLINE      /* Nothing */
#define __EXTERN_FORCEINLINE /* Nothing */
#ifndef __LONGLONG
#define __LONGLONG  long long
#define __ULONGLONG unsigned long long
#endif /* !__LONGLONG */

#define inline
#define __inline
#define __inline__
#define __restrict restrict
#define __restrict__ restrict
#define __restrict_arr restrict

#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[]

#define __builtin_choose_expr(c, tt, ff) __static_if(c){tt}else{ff}

#define __STATIC_IF(x)   __static_if(x)
#define __STATIC_ELSE(x) else
#define __IF0    if(0)
#define __IF1    if(1)
#define __WHILE0 while(0)
#define __WHILE1 while(1)
#define __native_wchar_t_defined
#define __wchar_t_defined
#define __builtin_object_size(ptr, type) ((type) < 2 ? (__SIZE_TYPE__)-1 : 0)

#if 0 /* These are built-in, but function the same as these macros */
#define __builtin_offsetof(s, ...)    ((__SIZE_TYPE__)&((s *)0)->__VA_ARGS__)
#define __builtin_offsetafter(s, ...) ((__SIZE_TYPE__)&((s *)0)->__VA_ARGS__ + 1)
#define __builtin_container_of(ptr, type, member)                                  \
	((type *)(int(*)[__builtin_types_compatible_p(__typeof__(((type *)0)->member), \
	                                              __typeof__(*(ptr))) ? 1 : -1])   \
	 ((__INTELLISENSE_SIZE_TYPE__)(ptr) - __builtin_offsetof(type, member)))
#endif

#define __COMPILER_OFFSETAFTER  __builtin_offsetafter
#define __COMPILER_CONTAINER_OF __builtin_container_of


#define __COMPILER_BARRIERS_ALL_IDENTICAL
#define __COMPILER_BARRIER()       (void)0
#define __COMPILER_READ_BARRIER()  (void)0
#define __COMPILER_WRITE_BARRIER() (void)0
#define __COMPILER_IGNORE_UNINITIALIZED(var) var
#define __COMPILER_DELETE_ASSUMPTIONS(var)   var = __builtin_void(var)

#ifdef __cplusplus
#define __NULLPTR nullptr
#else /* __cplusplus */
#define __NULLPTR ((void *)0)
#endif /* !__cplusplus */

#ifdef __VA_LIST_IS_ARRAY
#define __builtin_va_list __typeof(int[1])
#else /* __VA_LIST_IS_ARRAY */
#define __builtin_va_list char *
#endif /* !__VA_LIST_IS_ARRAY */
#define __builtin_va_start(ap, last_arg) (void)0
#define __builtin_va_arg(ap, T)          __builtin_void(*(T *)0)
#define __builtin_va_end(ap)             (void)0

#define __COMPILER_HAVE_BUG_BLOATY_CXX_USING 0

/* Atomic builtins (only need to emulate semantics ). */
#define __atomic_load_n(ptr, memorder)                 __builtin_rvoid(*(ptr))
#define __atomic_load(ptr, p_ret, memorder)            (void)(__builtin_void(*(p_ret)) = __builtin_rvoid(*(ptr)))
#define __atomic_store_n(ptr, val, memorder)           (void)(__builtin_void(*(ptr)) = (val))
#define __atomic_store(ptr, p_val, memorder)           (void)(__builtin_void(*(ptr)) = *(p_val))
#define __atomic_exchange_n(ptr, val, memorder)        __builtin_rvoid(__builtin_void(*(ptr)) += (val))
#define __atomic_exchange(ptr, p_val, p_ret, memorder) (void)(*(p_ret) = __atomic_exchange_n(ptr, *(p_val), memorder))
#define __atomic_compare_exchange_n(ptr, p_expected, desired, weak, success_memorder, failure_memorder) \
	(!__builtin_rvoid(__builtin_void(*(ptr)) = __builtin_rvoid(*(p_expected) = 0)))
#define __atomic_compare_exchange(ptr, p_expected, p_desired, weak, success_memorder, failure_memorder) \
	__atomic_compare_exchange_n(ptr, p_expected, *(p_desired), weak, success_memorder, failure_memorder)
#define __atomic_add_fetch(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_sub_fetch(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_and_fetch(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_xor_fetch(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_or_fetch(ptr, val, memorder)   __atomic_exchange_n(ptr, val, memorder)
#define __atomic_nand_fetch(ptr, val, memorder) __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_add(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_sub(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_and(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_xor(ptr, val, memorder)  __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_or(ptr, val, memorder)   __atomic_exchange_n(ptr, val, memorder)
#define __atomic_fetch_nand(ptr, val, memorder) __atomic_exchange_n(ptr, val, memorder)

/* NOTE: the following builtins are actually supported by the checker, but they're no-ops.
 *       By  deleting  them  here,  we  can   cut  down  on  some  unnecessary   overhead! */
#define __NO_builtin_expect
#define __builtin_expect(x, v)                     (x)
#define __builtin_expect_with_probability(x, v, p) (x)


/* Prevent including of too many local functions by faking CRT features. */
#ifndef __NO_KOS_SYSTEM_HEADERS__
#include <crt-features/crt-kos.h>
#endif /* !__NO_KOS_SYSTEM_HEADERS__ */
