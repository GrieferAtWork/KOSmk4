/* HASH CRC-32:0x10ca321e */
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
#ifndef _KOS_EXCEPT_H
#define _KOS_EXCEPT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/pp/__va_nargs.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/bits/except.h>         /* __ERROR_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h> /* struct exception_data */
#include <kos/bits/exception_nest.h> /* struct _exception_nesting_data */
#include <kos/except/codes.h>        /* E_OK, ... */
#include <kos/bits/fastexcept.h>

#ifdef __USE_KOS_KERNEL
#include <kos/bits/exception_info.h>
#endif /* __USE_KOS_KERNEL */

#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8
#endif /* !EXCEPTION_DATA_POINTERS */

#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/os/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __ERROR_THROW_CC
#define __ERROR_THROW_CC __LIBKCALL
#endif /* !__ERROR_THROW_CC */
#ifndef __ERROR_THROWN_CC
#define __ERROR_THROWN_CC __LIBKCALL
#endif /* !__ERROR_THROWN_CC */
#ifndef __ERROR_UNWIND_CC
#define __ERROR_UNWIND_CC __LIBKCALL
#endif /* !__ERROR_UNWIND_CC */
#ifndef __ERROR_NESTING_BEGIN_CC
#define __ERROR_NESTING_BEGIN_CC __LIBKCALL
#endif /* !__ERROR_NESTING_BEGIN_CC */
#ifndef __ERROR_NESTING_END_CC
#define __ERROR_NESTING_END_CC __LIBKCALL
#endif /* !__ERROR_NESTING_END_CC */


#ifndef __error_register_state_t_defined
#define __error_register_state_t_defined
typedef __ERROR_REGISTER_STATE_TYPE error_register_state_t;
#endif /* !__error_register_state_t_defined */

typedef __error_code_t error_code_t;
typedef __error_class_t error_class_t;
typedef __error_subclass_t error_subclass_t;

#if defined(__arch_error_data) && defined(__CRT_HAVE_error_data)
__COMPILER_EIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_data *,__NOTHROW,__LIBKCALL,error_data,(void),{ return __arch_error_data(); })
#elif defined(__CRT_HAVE_error_data)
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_data *__NOTHROW(__LIBKCALL error_data)(void) __CASMNAME_SAME("error_data");
#elif defined(__arch_error_data)
#include <libc/local/kos.except/error_data.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_data, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_data *__NOTHROW(__LIBKCALL error_data)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_data))(); })
#endif /* ... */
#if defined(__arch_error_code) && defined(__CRT_HAVE_error_code)
__COMPILER_EIDECLARE(__ATTR_PURE __ATTR_WUNUSED,error_code_t,__NOTHROW,__LIBKCALL,error_code,(void),{ return __arch_error_code(); })
#elif defined(__CRT_HAVE_error_code)
__LIBC __ATTR_PURE __ATTR_WUNUSED error_code_t __NOTHROW(__LIBKCALL error_code)(void) __CASMNAME_SAME("error_code");
#elif defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <libc/local/kos.except/error_code.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_code, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED error_code_t __NOTHROW(__LIBKCALL error_code)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_code))(); })
#endif /* ... */
#if defined(__arch_error_active) && defined(__CRT_HAVE_error_active)
__COMPILER_EIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__BOOL,__NOTHROW,__LIBKCALL,error_active,(void),{ return __arch_error_active(); })
#elif defined(__CRT_HAVE_error_active)
__LIBC __ATTR_PURE __ATTR_WUNUSED __BOOL __NOTHROW(__LIBKCALL error_active)(void) __CASMNAME_SAME("error_active");
#elif defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <libc/local/kos.except/error_active.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_active, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __BOOL __NOTHROW(__LIBKCALL error_active)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_active))(); })
#endif /* ... */
#if defined(__arch_error_class) && defined(__CRT_HAVE_error_class)
__COMPILER_EIDECLARE(__ATTR_PURE __ATTR_WUNUSED,error_class_t,__NOTHROW,__LIBKCALL,error_class,(void),{ return __arch_error_class(); })
#elif defined(__CRT_HAVE_error_class)
__LIBC __ATTR_PURE __ATTR_WUNUSED error_class_t __NOTHROW(__LIBKCALL error_class)(void) __CASMNAME_SAME("error_class");
#elif defined(__arch_error_class) || defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <libc/local/kos.except/error_class.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_class, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED error_class_t __NOTHROW(__LIBKCALL error_class)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_class))(); })
#endif /* ... */
#if defined(__arch_error_subclass) && defined(__CRT_HAVE_error_subclass)
__COMPILER_EIDECLARE(__ATTR_PURE __ATTR_WUNUSED,error_subclass_t,__NOTHROW,__LIBKCALL,error_subclass,(void),{ return __arch_error_subclass(); })
#elif defined(__CRT_HAVE_error_subclass)
__LIBC __ATTR_PURE __ATTR_WUNUSED error_subclass_t __NOTHROW(__LIBKCALL error_subclass)(void) __CASMNAME_SAME("error_subclass");
#elif defined(__arch_error_subclass) || defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <libc/local/kos.except/error_subclass.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_subclass, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED error_subclass_t __NOTHROW(__LIBKCALL error_subclass)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_subclass))(); })
#endif /* ... */
#if defined(__arch_error_register_state) && defined(__CRT_HAVE_error_register_state)
__COMPILER_EIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,error_register_state_t *,__NOTHROW,__LIBKCALL,error_register_state,(void),{ return __arch_error_register_state(); })
#elif defined(__CRT_HAVE_error_register_state)
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED error_register_state_t *__NOTHROW(__LIBKCALL error_register_state)(void) __CASMNAME_SAME("error_register_state");
#elif defined(__arch_error_register_state)
#include <libc/local/kos.except/error_register_state.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_register_state, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED error_register_state_t *__NOTHROW(__LIBKCALL error_register_state)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_register_state))(); })
#endif /* ... */
#ifdef __CRT_HAVE_error_as_errno
/* Transform the given exception into a posix errno value */
__LIBC __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBKCALL error_as_errno)(struct exception_data const *__restrict __self) __CASMNAME_SAME("error_as_errno");
#else /* __CRT_HAVE_error_as_errno */
#include <libc/local/kos.except/error_as_errno.h>
/* Transform the given exception into a posix errno value */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_as_errno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBKCALL error_as_errno)(struct exception_data const *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_as_errno))(__self); })
#endif /* !__CRT_HAVE_error_as_errno */
struct __siginfo_struct;
#ifdef __CRT_HAVE_error_as_signal
/* Transform the given exception into a posix signal.
 * If   doing  this  is   possible,  fill  in   `*result'  and  return  `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL error_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) __CASMNAME_SAME("error_as_signal");
#else /* __CRT_HAVE_error_as_signal */
#include <libc/local/kos.except/error_as_signal.h>
/* Transform the given exception into a posix signal.
 * If   doing  this  is   possible,  fill  in   `*result'  and  return  `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_as_signal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL error_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_as_signal))(__self, __result); })
#endif /* !__CRT_HAVE_error_as_signal */
#ifdef __CRT_HAVE_error_name
/* Return the name of the given error, or `NULL' if unknown.
 * This  name  is   the  same  as   the  `E_*'   identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
__LIBC __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL error_name)(error_code_t __code) __CASMNAME_SAME("error_name");
#else /* __CRT_HAVE_error_name */
#include <libc/local/kos.except/error_name.h>
/* Return the name of the given error, or `NULL' if unknown.
 * This  name  is   the  same  as   the  `E_*'   identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL error_name)(error_code_t __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_name))(__code); })
#endif /* !__CRT_HAVE_error_name */
#ifdef __CRT_HAVE_error_priority
/* Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
__LIBC __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBKCALL error_priority)(error_code_t __code) __CASMNAME_SAME("error_priority");
#else /* __CRT_HAVE_error_priority */
#include <libc/local/kos.except/error_priority.h>
/* Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_priority, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBKCALL error_priority)(error_code_t __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_priority))(__code); })
#endif /* !__CRT_HAVE_error_priority */
#ifdef __USE_KOS_KERNEL
#if defined(__arch_error_info) && defined(__CRT_HAVE_error_info)
__COMPILER_EIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_info *,__NOTHROW,__LIBKCALL,error_info,(void),{ return __arch_error_info(); })
#elif defined(__CRT_HAVE_error_info)
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_info *__NOTHROW(__LIBKCALL error_info)(void) __CASMNAME_SAME("error_info");
#elif defined(__arch_error_info)
#include <libc/local/kos.except/error_info.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(error_info, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_info *__NOTHROW(__LIBKCALL error_info)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_info))(); })
#endif /* ... */
#ifdef __CRT_HAVE_error_unwind
/* Unwind the given register state to propagate the currently set error.
 * Following this, the  returned register state  should then be  loaded. */
__LIBC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) error_register_state_t *__NOTHROW_NCX(__ERROR_UNWIND_CC error_unwind)(error_register_state_t *__restrict __state) __CASMNAME_SAME("error_unwind");
#endif /* __CRT_HAVE_error_unwind */
#endif /* __USE_KOS_KERNEL */
#ifdef __CRT_HAVE_error_throw_current
/* Throw the currently set (in `error_data()') exception. */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL error_throw_current)(void) __THROWS(...) __CASMNAME_SAME("error_throw_current");
#endif /* __CRT_HAVE_error_throw_current */
#if !defined(__error_rethrow_defined) && defined(__CRT_HAVE_error_rethrow)
#define __error_rethrow_defined
/* Rethrow the current exception (same as a c++ `throw;' expression) */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL error_rethrow)(void) __THROWS(...) __CASMNAME_SAME("error_rethrow");
#endif /* !__error_rethrow_defined && __CRT_HAVE_error_rethrow */
/* Rethrow the last exception */
#ifdef __error_rethrow_defined
#define RETHROW() error_rethrow()
#elif defined(__cplusplus)
#define RETHROW() throw
#endif /* ... */
#ifdef __INTELLISENSE__
/* Throw a new exception `code', which is either an exception class,
 * an  exception code, or an exception-class+sub-class pair, written
 * as `(class,subclass)', going in hand with the macros defining the
 * various exceptions there are.
 * Following this, up to `EXCEPTION_DATA_POINTERS' optional exception
 * arguments may be provided, which are stored in `e_pointers',  with
 * any argument not provided simply substituted in with `NULL' / 0. */
#define THROW THROW
__ATTR_NORETURN __ATTR_COLD void (__VLIBCCALL THROW)(error_code_t __code, ...);

/* Check if the current exception matches the given error code, class, or sub-class
 * >> TRY {
 * >>     ...
 * >> } EXCEPT {
 * >>     if (!was_thrown(E_SEGFAULT))
 * >>         RETHROW();
 * >>     // Handle `E_SEGFAULT'
 * >>     ...
 * >> }
 */
__ATTR_WUNUSED __BOOL __NOTHROW(was_thrown)(error_code_t __code);
#else /* __INTELLISENSE__ */

#ifndef THROW
#if !defined(__error_throw_defined) && defined(__CRT_HAVE_error_throw)
#define __error_throw_defined
/* Throw an exception and fill exception pointers with all zeroes */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__ERROR_THROW_CC error_throw)(error_code_t __code) __THROWS(...) __CASMNAME_SAME("error_throw");
#endif /* !__error_throw_defined && __CRT_HAVE_error_throw */
#if !defined(__error_thrown_defined) && defined(__CRT_HAVE_error_thrown)
#define __error_thrown_defined
/* Throw an exception and load `argc' pointers from varargs */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__ERROR_THROWN_CC error_thrown)(error_code_t __code, unsigned int ___argc, ...) __THROWS(...) __CASMNAME_SAME("error_thrown");
#endif /* !__error_thrown_defined && __CRT_HAVE_error_thrown */
#ifdef __HYBRID_PP_VA_NARGS
#define __PRIVATE_THROW_PACKAGE_CODE1(code) code
#define __PRIVATE_THROW_PACKAGE_CODE2       ERROR_CODE
#define __PRIVATE_THROW_PACKAGE_CODEN2(n)   __PRIVATE_THROW_PACKAGE_CODE##n
#define __PRIVATE_THROW_PACKAGE_CODEN(n)    __PRIVATE_THROW_PACKAGE_CODEN2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_THROW_PACKAGE_CODE(...)   __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_THROW_PACKAGE_CODE(args...) __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */

#ifdef __error_throw_defined
#define __PRIVATE_THROW1(code) error_throw(__PRIVATE_THROW_PACKAGE_CODE code)
#elif defined(__error_thrown_defined)
#define __PRIVATE_THROW1(code) error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 0)
#endif /* ... */
#ifdef __error_thrown_defined
#define __PRIVATE_THROW2(code, a)                      error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 1, (__UINTPTR_TYPE__)(a))
#define __PRIVATE_THROW3(code, a, b)                   error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 2, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b))
#define __PRIVATE_THROW4(code, a, b, c)                error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 3, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c))
#define __PRIVATE_THROW5(code, a, b, c, d)             error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 4, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d))
#define __PRIVATE_THROW6(code, a, b, c, d, e)          error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 5, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e))
#define __PRIVATE_THROW7(code, a, b, c, d, e, f)       error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 6, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f))
#define __PRIVATE_THROW8(code, a, b, c, d, e, f, g)    error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 7, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g))
#define __PRIVATE_THROW9(code, a, b, c, d, e, f, g, h) error_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 8, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g), (__UINTPTR_TYPE__)(h))
#endif /* __error_thrown_defined */
#define __PRIVATE_THROW_N2(n) __PRIVATE_THROW##n
#define __PRIVATE_THROW_N(n)  __PRIVATE_THROW_N2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define THROW(...)            __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define THROW(args...)        __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */
#endif /* __HYBRID_PP_VA_NARGS */
#endif /* !THROW */

#ifndef was_thrown
#ifndef __arch_error_code_eq
#define __arch_error_code_eq(x) (error_code() == (x))
#endif /* !__arch_error_code_eq */
#ifndef __arch_error_class_eq
#define __arch_error_class_eq(x) (error_class() == (x))
#endif /* !__arch_error_class_eq */
#ifndef __PRIVATE_WAS_THROWN_PACKAGE_CODE1
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE1(code) \
	((__builtin_constant_p(code) && (code) <= 0xffff) ? __arch_error_class_eq(code) : __arch_error_code_eq(code))
#endif /* !__PRIVATE_WAS_THROWN_PACKAGE_CODE1 */
#ifndef __PRIVATE_WAS_THROWN_PACKAGE_CODE2
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE2(class, subclass) __arch_error_code_eq(ERROR_CODE(class, subclass))
#endif /* !__PRIVATE_WAS_THROWN_PACKAGE_CODE2 */
#ifdef __HYBRID_PP_VA_NARGS
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)              __PRIVATE_WAS_THROWN_PACKAGE_CODE##n
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN(n)               __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE(...)              __PRIVATE_WAS_THROWN_PACKAGE_CODEX(__PRIVATE_WAS_THROWN_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE(args...)          __PRIVATE_WAS_THROWN_PACKAGE_CODEX(__PRIVATE_WAS_THROWN_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(args))(args))
#endif /* ... */
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEX(x)               x
#define was_thrown(code)                                    __PRIVATE_WAS_THROWN_PACKAGE_CODE code
#endif /* __HYBRID_PP_VA_NARGS */
#endif /* !was_thrown */
#endif /* !__INTELLISENSE__ */
#if !defined(__error_nesting_begin_defined) && defined(__CRT_HAVE_error_nesting_begin)
#define __error_nesting_begin_defined
/* Begin a nested TRY-block. (i.e. inside of another EXCEPT block) */
__LIBC __ATTR_NONNULL((1)) void __NOTHROW(__ERROR_NESTING_BEGIN_CC error_nesting_begin)(struct _exception_nesting_data *__restrict __saved) __CASMNAME_SAME("error_nesting_begin");
#endif /* !__error_nesting_begin_defined && __CRT_HAVE_error_nesting_begin */
#if !defined(__error_nesting_end_defined) && defined(__CRT_HAVE_error_nesting_end)
#define __error_nesting_end_defined
/* End a nested TRY-block. (i.e. inside of another EXCEPT block) */
__LIBC __ATTR_NONNULL((1)) void __NOTHROW(__ERROR_NESTING_END_CC error_nesting_end)(struct _exception_nesting_data *__restrict __saved) __CASMNAME_SAME("error_nesting_end");
#endif /* !__error_nesting_end_defined && __CRT_HAVE_error_nesting_end */
#ifdef __cplusplus
/* TODO: In user-space, using TRY and EXCEPT should  leave some sort of marker in  the
 *       binary  that allows for libc to consider these handlers as `dlexceptaware(3)'
 *       when operating in except-mode #4. However, I  am unsure as to how this  could
 *       be implemented without making some additional tweaks to gcc under KOS, though
 *       that wouldn't even be  the first time  I had to  tweak binutils/gcc for  this
 *       project... */
#ifndef __TRY
#define __TRY    try
#define __EXCEPT catch(...)
#endif /* !__TRY */

/* Using NOTHROW_BEGIN ... NOTHROW_END, you can construct blocks of code
 * that will trigger undefined behavior  if they cause an exception.  In
 * debug-mode,  this undefined behavior includes panic/coredump, similar
 * to when an exception is propagated through a NOTHROW function. */
#ifndef __NOTHROW_BEGIN
#ifndef NDEBUG
#define __NOTHROW_BEGIN do try
#define __NOTHROW_END   catch(...) { __builtin_unreachable(); } __WHILE0
#else /* !NDEBUG */
/* Sadly, GCC doesn't see the optimization potential when  encountering
 * a catch-block that consists of nothing but `__builtin_unreachable()'
 *
 * It should be obvious that such a construct could be optimized into
 * a section of code that can be considered as NOTHROW, similar to an
 * inline function declared as NOTHROW. */
#define __NOTHROW_BEGIN do
#define __NOTHROW_END   __WHILE0
#endif /* NDEBUG */
#endif /* !__NOTHROW_BEGIN */

/* Nested exception support */
#if defined(__error_nesting_begin_defined) && defined(__error_nesting_end_defined)
class __cxx_exception_nesting: public _exception_nesting_data {
public:
	__ATTR_FORCEINLINE operator bool() const __CXX_NOEXCEPT { return false; }
	__ATTR_FORCEINLINE __cxx_exception_nesting() __CXX_NOEXCEPT {
		en_size = _EXCEPTION_NESTING_DATA_SIZE;
		error_nesting_begin(this);
	}
	__ATTR_FORCEINLINE ~__cxx_exception_nesting() __CXX_NOEXCEPT {
		error_nesting_end(this);
	}
};
#ifdef __COUNTER__
#define __PRIVATE_CXX_EXCEPT_NESTING_NAME __PP_CAT2(__local_cxx_exception_nesting, __COUNTER__)
#else /* __COUNTER__ */
#define __PRIVATE_CXX_EXCEPT_NESTING_NAME __PP_CAT2(__local_cxx_exception_nesting, __LINE__)
#endif /* !__COUNTER__ */
#define __NESTED_TRY       if(__cxx_exception_nesting __PRIVATE_CXX_EXCEPT_NESTING_NAME {});else try
#define __NESTED_EXCEPTION __cxx_exception_nesting __PRIVATE_CXX_EXCEPT_NESTING_NAME
#endif /* __error_nesting_begin_defined && __error_nesting_end_defined */
#endif /* __cplusplus */


#if !defined(TRY) && defined(__TRY)
#define TRY __TRY
#endif /* !TRY && __TRY */
#if !defined(EXCEPT) && defined(__EXCEPT)
#define EXCEPT __EXCEPT
#endif /* !EXCEPT && __EXCEPT */
#if !defined(NESTED_TRY) && defined(__NESTED_TRY)
#define NESTED_TRY __NESTED_TRY
#endif /* !NESTED_TRY && __NESTED_TRY */
#if !defined(NESTED_EXCEPTION) && defined(__NESTED_EXCEPTION)
#define NESTED_EXCEPTION __NESTED_EXCEPTION
#endif /* !NESTED_EXCEPTION && __NESTED_EXCEPTION */
#if !defined(NOTHROW_BEGIN) && defined(__NOTHROW_BEGIN)
#define NOTHROW_BEGIN __NOTHROW_BEGIN
#endif /* !NOTHROW_BEGIN && __NOTHROW_BEGIN */
#if !defined(NOTHROW_END) && defined(__NOTHROW_END)
#define NOTHROW_END __NOTHROW_END
#endif /* !NOTHROW_END && __NOTHROW_END */


#ifndef __INTELLISENSE__
/* Use macros to directly invoke __arch_* variants (if they've been defined) */
#ifdef __arch_error_data
#define error_data() __arch_error_data()
#endif /* __arch_error_data */
#ifdef __arch_error_code
#define error_code() __arch_error_code()
#endif /* __arch_error_code */
#ifdef __arch_error_active
#define error_active() __arch_error_active()
#endif /* __arch_error_active */
#ifdef __arch_error_class
#define error_class() __arch_error_class()
#endif /* __arch_error_class */
#ifdef __arch_error_subclass
#define error_subclass() __arch_error_subclass()
#endif /* __arch_error_subclass */
#ifdef __arch_error_register_state
#define error_register_state() __arch_error_register_state()
#endif /* __arch_error_register_state */
#ifdef __USE_KOS_KERNEL
#ifdef __arch_error_info
#define error_info() __arch_error_info()
#endif /* __arch_error_info */
#endif /* __USE_KOS_KERNEL */
#endif /* !__INTELLISENSE__ */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_EXCEPT_H */
