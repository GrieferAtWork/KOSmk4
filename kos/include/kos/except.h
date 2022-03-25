/* HASH CRC-32:0x640c51dc */
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
#include <hybrid/host.h>
#include <kos/bits/except.h>         /* __EXCEPT_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h> /* struct exception_data */
#include <kos/bits/exception_nest.h> /* struct _exception_nesting_data */
#include <kos/except/codes.h>        /* E_OK, ... */
#include <kos/bits/fastexcept.h>
#include <bits/crt/format-printer.h>

#ifdef __USE_KOS_KERNEL
#include <kos/bits/exception_info.h>
#endif /* __USE_KOS_KERNEL */

#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8
#endif /* !EXCEPTION_DATA_POINTERS */

#ifndef __EXCEPT_REGISTER_STATE_TYPE
#include <bits/os/mcontext.h>
#define __EXCEPT_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_EXCEPT_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__EXCEPT_REGISTER_STATE_TYPE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __EXCEPT_THROW_CC
#define __EXCEPT_THROW_CC __LIBKCALL
#endif /* !__EXCEPT_THROW_CC */
#ifndef __EXCEPT_THROWN_CC
#define __EXCEPT_THROWN_CC __LIBKCALL
#endif /* !__EXCEPT_THROWN_CC */
#ifndef __EXCEPT_UNWIND_CC
#define __EXCEPT_UNWIND_CC __LIBKCALL
#endif /* !__EXCEPT_UNWIND_CC */
#ifndef __EXCEPT_NESTING_BEGIN_CC
#define __EXCEPT_NESTING_BEGIN_CC __LIBKCALL
#endif /* !__EXCEPT_NESTING_BEGIN_CC */
#ifndef __EXCEPT_NESTING_END_CC
#define __EXCEPT_NESTING_END_CC __LIBKCALL
#endif /* !__EXCEPT_NESTING_END_CC */


#ifndef __except_register_state_t_defined
#define __except_register_state_t_defined
typedef __EXCEPT_REGISTER_STATE_TYPE except_register_state_t;
#endif /* !__except_register_state_t_defined */

typedef __except_code_t except_code_t;
typedef __except_class_t except_class_t;
typedef __except_subclass_t except_subclass_t;

#if defined(__arch_except_data) && defined(__CRT_HAVE_except_data)
/* >> except_data(3)
 * Return a pointer to the thread-local descriptor of the current exception */
__COMPILER_CEIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_data *,__NOTHROW,__LIBKCALL,except_data,(void),{ return __arch_except_data(); })
#elif defined(__CRT_HAVE_except_data)
/* >> except_data(3)
 * Return a pointer to the thread-local descriptor of the current exception */
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_data *__NOTHROW(__LIBKCALL except_data)(void) __CASMNAME_SAME("except_data");
#elif defined(__arch_except_data)
#include <libc/local/kos.except/except_data.h>
/* >> except_data(3)
 * Return a pointer to the thread-local descriptor of the current exception */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_data, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_data *__NOTHROW(__LIBKCALL except_data)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_data))(); })
#endif /* ... */
#if defined(__arch_except_code) && defined(__CRT_HAVE_except_code)
/* >> except_code(3)
 * Return the current exception code, or `EXCEPT_CODEOF(E_OK)' when none is active */
__COMPILER_CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,except_code_t,__NOTHROW,__LIBKCALL,except_code,(void),{ return __arch_except_code(); })
#elif defined(__CRT_HAVE_except_code)
/* >> except_code(3)
 * Return the current exception code, or `EXCEPT_CODEOF(E_OK)' when none is active */
__LIBC __ATTR_PURE __ATTR_WUNUSED except_code_t __NOTHROW(__LIBKCALL except_code)(void) __CASMNAME_SAME("except_code");
#elif defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#include <libc/local/kos.except/except_code.h>
/* >> except_code(3)
 * Return the current exception code, or `EXCEPT_CODEOF(E_OK)' when none is active */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_code, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED except_code_t __NOTHROW(__LIBKCALL except_code)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_code))(); })
#endif /* ... */
#if defined(__arch_except_active) && defined(__CRT_HAVE_except_active)
/* >> except_active(3)
 * Check if an exception is active; same as `except_code() != EXCEPT_CODEOF(E_OK)' */
__COMPILER_CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__BOOL,__NOTHROW,__LIBKCALL,except_active,(void),{ return __arch_except_active(); })
#elif defined(__CRT_HAVE_except_active)
/* >> except_active(3)
 * Check if an exception is active; same as `except_code() != EXCEPT_CODEOF(E_OK)' */
__LIBC __ATTR_PURE __ATTR_WUNUSED __BOOL __NOTHROW(__LIBKCALL except_active)(void) __CASMNAME_SAME("except_active");
#elif defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#include <libc/local/kos.except/except_active.h>
/* >> except_active(3)
 * Check if an exception is active; same as `except_code() != EXCEPT_CODEOF(E_OK)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_active, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __BOOL __NOTHROW(__LIBKCALL except_active)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_active))(); })
#endif /* ... */
#if defined(__arch_except_class) && defined(__CRT_HAVE_except_class)
/* >> except_class(3)
 * Return the current exception class; same as `EXCEPT_CLASS(except_code())' */
__COMPILER_CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,except_class_t,__NOTHROW,__LIBKCALL,except_class,(void),{ return __arch_except_class(); })
#elif defined(__CRT_HAVE_except_class)
/* >> except_class(3)
 * Return the current exception class; same as `EXCEPT_CLASS(except_code())' */
__LIBC __ATTR_PURE __ATTR_WUNUSED except_class_t __NOTHROW(__LIBKCALL except_class)(void) __CASMNAME_SAME("except_class");
#elif defined(__arch_except_class) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#include <libc/local/kos.except/except_class.h>
/* >> except_class(3)
 * Return the current exception class; same as `EXCEPT_CLASS(except_code())' */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_class, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED except_class_t __NOTHROW(__LIBKCALL except_class)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_class))(); })
#endif /* ... */
#if defined(__arch_except_subclass) && defined(__CRT_HAVE_except_subclass)
/* >> except_subclass(3)
 * Return the current exception sub-class; same as `EXCEPT_SUBCLASS(except_code())' */
__COMPILER_CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,except_subclass_t,__NOTHROW,__LIBKCALL,except_subclass,(void),{ return __arch_except_subclass(); })
#elif defined(__CRT_HAVE_except_subclass)
/* >> except_subclass(3)
 * Return the current exception sub-class; same as `EXCEPT_SUBCLASS(except_code())' */
__LIBC __ATTR_PURE __ATTR_WUNUSED except_subclass_t __NOTHROW(__LIBKCALL except_subclass)(void) __CASMNAME_SAME("except_subclass");
#elif defined(__arch_except_subclass) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#include <libc/local/kos.except/except_subclass.h>
/* >> except_subclass(3)
 * Return the current exception sub-class; same as `EXCEPT_SUBCLASS(except_code())' */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_subclass, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED except_subclass_t __NOTHROW(__LIBKCALL except_subclass)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_subclass))(); })
#endif /* ... */
#if defined(__arch_except_register_state) && defined(__CRT_HAVE_except_register_state)
/* >> except_register_state(3)
 * Return  the register state  at the time the  current exception was thrown.
 * The returned block of memory is only valid when `except_active() == true'. */
__COMPILER_CEIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,except_register_state_t *,__NOTHROW,__LIBKCALL,except_register_state,(void),{ return __arch_except_register_state(); })
#elif defined(__CRT_HAVE_except_register_state)
/* >> except_register_state(3)
 * Return  the register state  at the time the  current exception was thrown.
 * The returned block of memory is only valid when `except_active() == true'. */
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED except_register_state_t *__NOTHROW(__LIBKCALL except_register_state)(void) __CASMNAME_SAME("except_register_state");
#elif defined(__arch_except_register_state)
#include <libc/local/kos.except/except_register_state.h>
/* >> except_register_state(3)
 * Return  the register state  at the time the  current exception was thrown.
 * The returned block of memory is only valid when `except_active() == true'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_register_state, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED except_register_state_t *__NOTHROW(__LIBKCALL except_register_state)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_register_state))(); })
#endif /* ... */
#ifdef __CRT_HAVE_except_as_errno
/* >> except_as_errno(3)
 * Transform the  given exception  into  a posix  errno  value.
 * When no special errno is defined for `data', return `EPERM'. */
__LIBC __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBKCALL except_as_errno)(struct exception_data const *__restrict __self) __CASMNAME_SAME("except_as_errno");
#else /* __CRT_HAVE_except_as_errno */
#include <libc/local/kos.except/except_as_errno.h>
/* >> except_as_errno(3)
 * Transform the  given exception  into  a posix  errno  value.
 * When no special errno is defined for `data', return `EPERM'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_as_errno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBKCALL except_as_errno)(struct exception_data const *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_as_errno))(__self); })
#endif /* !__CRT_HAVE_except_as_errno */
struct __siginfo_struct;
#ifdef __CRT_HAVE_except_as_signal
/* >> except_as_signal(3)
 * Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false'
 * is returned. */
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL except_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) __CASMNAME_SAME("except_as_signal");
#else /* __CRT_HAVE_except_as_signal */
#include <libc/local/kos.except/except_as_signal.h>
/* >> except_as_signal(3)
 * Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false'
 * is returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_as_signal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL except_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_as_signal))(__self, __result); })
#endif /* !__CRT_HAVE_except_as_signal */
#ifdef __CRT_HAVE_except_name
/* >> except_name(3)
 * Return the name of the  given error, or `NULL'  if
 * unknown. This name is one of the `E_*' identifier.
 * E.g.: `except_name(EXCEPT_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
__LIBC __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL except_name)(except_code_t __code) __CASMNAME_SAME("except_name");
#else /* __CRT_HAVE_except_name */
#include <libc/local/kos.except/except_name.h>
/* >> except_name(3)
 * Return the name of the  given error, or `NULL'  if
 * unknown. This name is one of the `E_*' identifier.
 * E.g.: `except_name(EXCEPT_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL except_name)(except_code_t __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_name))(__code); })
#endif /* !__CRT_HAVE_except_name */
#ifdef __CRT_HAVE_except_priority
/* >> except_priority(3)
 * Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
__LIBC __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBKCALL except_priority)(except_code_t __code) __CASMNAME_SAME("except_priority");
#else /* __CRT_HAVE_except_priority */
#include <libc/local/kos.except/except_priority.h>
/* >> except_priority(3)
 * Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_priority, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBKCALL except_priority)(except_code_t __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_priority))(__code); })
#endif /* !__CRT_HAVE_except_priority */
/* Flags for `except_print_short_description()' */
#define EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_NORMAL 0x0000 /* Normal flags */
#define EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY    0x0001 /* Print TTY escape sequences for color highlighting */
#ifdef __CRT_HAVE_except_print_short_description
/* >> except_print_short_description(3)
 * Print a short, single-line (without trailing linefeed) description  of
 * the given error `data', including the error code, name and for certain
 * errors, prominent error arguments.
 * @param: flags: Set of `EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_*'
 * @return: * : The usual pformatprinter-compatible return value */
__LIBC __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL except_print_short_description)(__pformatprinter __printer, void *__arg, struct exception_data const *__data, __UINTPTR_TYPE__ __flags) __CASMNAME_SAME("except_print_short_description");
#else /* __CRT_HAVE_except_print_short_description */
#include <libc/local/kos.except/except_print_short_description.h>
/* >> except_print_short_description(3)
 * Print a short, single-line (without trailing linefeed) description  of
 * the given error `data', including the error code, name and for certain
 * errors, prominent error arguments.
 * @param: flags: Set of `EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_*'
 * @return: * : The usual pformatprinter-compatible return value */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_print_short_description, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL except_print_short_description)(__pformatprinter __printer, void *__arg, struct exception_data const *__data, __UINTPTR_TYPE__ __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_print_short_description))(__printer, __arg, __data, __flags); })
#endif /* !__CRT_HAVE_except_print_short_description */
#ifdef __USE_KOS_KERNEL
#if defined(__arch_except_info) && defined(__CRT_HAVE_except_info)
/* >> except_info(3)
 * Return a pointer to the thread-local exception info structure.
 * Note  that the exact  layout of this  structure depends on how
 * libc/the kernel was configured. For the sake of compatibility,
 * try to  use `except_data()'  and `except_register_state()'  in
 * favor of this function. */
__COMPILER_CEIDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_info *,__NOTHROW,__LIBKCALL,except_info,(void),{ return __arch_except_info(); })
#elif defined(__CRT_HAVE_except_info)
/* >> except_info(3)
 * Return a pointer to the thread-local exception info structure.
 * Note  that the exact  layout of this  structure depends on how
 * libc/the kernel was configured. For the sake of compatibility,
 * try to  use `except_data()'  and `except_register_state()'  in
 * favor of this function. */
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_info *__NOTHROW(__LIBKCALL except_info)(void) __CASMNAME_SAME("except_info");
#elif defined(__arch_except_info)
#include <libc/local/kos.except/except_info.h>
/* >> except_info(3)
 * Return a pointer to the thread-local exception info structure.
 * Note  that the exact  layout of this  structure depends on how
 * libc/the kernel was configured. For the sake of compatibility,
 * try to  use `except_data()'  and `except_register_state()'  in
 * favor of this function. */
__NAMESPACE_LOCAL_USING_OR_IMPL(except_info, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_info *__NOTHROW(__LIBKCALL except_info)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(except_info))(); })
#endif /* ... */
#ifdef __CRT_HAVE_except_unwind
/* >> except_unwind(3)
 * Unwind the given register state to propagate the currently set error.
 * Following this, the  returned register state  should then be  loaded. */
__LIBC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) except_register_state_t *__NOTHROW_NCX(__EXCEPT_UNWIND_CC except_unwind)(except_register_state_t *__restrict __state) __CASMNAME_SAME("except_unwind");
#endif /* __CRT_HAVE_except_unwind */
#endif /* __USE_KOS_KERNEL */
#ifdef __CRT_HAVE_except_throw_current
/* >> except_throw_current(3)
 * Throw the currently set (in `except_data()') exception. */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL except_throw_current)(void) __THROWS(...) __CASMNAME_SAME("except_throw_current");
#endif /* __CRT_HAVE_except_throw_current */
#if !defined(__except_rethrow_defined) && defined(__CRT_HAVE_except_rethrow)
#define __except_rethrow_defined
/* >> except_rethrow(3)
 * Rethrow the current exception (same as a c++ `throw;' expression) */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL except_rethrow)(void) __THROWS(...) __CASMNAME_SAME("except_rethrow");
#endif /* !__except_rethrow_defined && __CRT_HAVE_except_rethrow */
#if !defined(__except_throw_defined) && defined(__CRT_HAVE_except_throw)
#define __except_throw_defined
/* >> except_throw(3)
 * Throw an exception and fill exception pointers with all zeroes */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__EXCEPT_THROW_CC except_throw)(except_code_t __code) __THROWS(...) __CASMNAME_SAME("except_throw");
#endif /* !__except_throw_defined && __CRT_HAVE_except_throw */
#if !defined(__except_thrown_defined) && defined(__CRT_HAVE_except_thrown)
#define __except_thrown_defined
/* >> except_thrown(3)
 * Throw an exception and load `argc' pointers from varargs */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__EXCEPT_THROWN_CC except_thrown)(except_code_t __code, unsigned int ___argc, ...) __THROWS(...) __CASMNAME_SAME("except_thrown");
#endif /* !__except_thrown_defined && __CRT_HAVE_except_thrown */
/* Rethrow the last exception */
#ifdef __except_rethrow_defined
#define RETHROW() except_rethrow()
#elif defined(__cplusplus)
#define RETHROW() throw
#endif /* ... */
#ifdef __INTELLISENSE__
/* >> THROW(3)
 * Throw a new exception `code', which is either an exception class,
 * an  exception code, or an exception-class+sub-class pair, written
 * as `(class,subclass)', going in hand with the macros defining the
 * various exceptions there are.
 * Following this, up to `EXCEPTION_DATA_POINTERS' optional exception
 * arguments may be provided, which are stored in `e_pointers',  with
 * any argument not provided simply substituted in with `NULL' / 0. */
#define THROW THROW
__ATTR_NORETURN __ATTR_COLD void (THROW)(except_code_t __code, ...);

/* >> was_thrown(3)
 * Check if the current exception matches the given error code, class, or sub-class
 * >> TRY {
 * >>     ...
 * >> } EXCEPT {
 * >>     if (!was_thrown(E_SEGFAULT))
 * >>         RETHROW();
 * >>     // Handle `E_SEGFAULT'
 * >>     ...
 * >> } */
__ATTR_WUNUSED __BOOL __NOTHROW(was_thrown)(except_code_t __code);
#else /* __INTELLISENSE__ */

#ifndef THROW
#ifdef __HYBRID_PP_VA_NARGS
#define __PRIVATE_THROW_PACKAGE_CODE1(code) code
#define __PRIVATE_THROW_PACKAGE_CODE2       EXCEPT_CODE
#define __PRIVATE_THROW_PACKAGE_CODEN2(n)   __PRIVATE_THROW_PACKAGE_CODE##n
#define __PRIVATE_THROW_PACKAGE_CODEN(n)    __PRIVATE_THROW_PACKAGE_CODEN2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_THROW_PACKAGE_CODE(...)   __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_THROW_PACKAGE_CODE(args...) __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */

#ifdef __except_throw_defined
#define __PRIVATE_THROW1(code) except_throw(__PRIVATE_THROW_PACKAGE_CODE code)
#elif defined(__except_thrown_defined)
#define __PRIVATE_THROW1(code) except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 0)
#endif /* ... */
#ifdef __except_thrown_defined
#define __PRIVATE_THROW2(code, a)                      except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 1, (__UINTPTR_TYPE__)(a))
#define __PRIVATE_THROW3(code, a, b)                   except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 2, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b))
#define __PRIVATE_THROW4(code, a, b, c)                except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 3, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c))
#define __PRIVATE_THROW5(code, a, b, c, d)             except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 4, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d))
#define __PRIVATE_THROW6(code, a, b, c, d, e)          except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 5, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e))
#define __PRIVATE_THROW7(code, a, b, c, d, e, f)       except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 6, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f))
#define __PRIVATE_THROW8(code, a, b, c, d, e, f, g)    except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 7, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g))
#define __PRIVATE_THROW9(code, a, b, c, d, e, f, g, h) except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 8, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g), (__UINTPTR_TYPE__)(h))
#endif /* __except_thrown_defined */
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
#ifndef __arch_except_code_eq
#define __arch_except_code_eq(x) (except_code() == (x))
#endif /* !__arch_except_code_eq */
#ifndef __arch_except_class_eq
#define __arch_except_class_eq(x) (except_class() == (x))
#endif /* !__arch_except_class_eq */
#ifndef __PRIVATE_WAS_THROWN_PACKAGE_CODE1
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE1(code) \
	((__builtin_constant_p(code) && (code) <= 0xffff) ? __arch_except_class_eq(code) : __arch_except_code_eq(code))
#endif /* !__PRIVATE_WAS_THROWN_PACKAGE_CODE1 */
#ifndef __PRIVATE_WAS_THROWN_PACKAGE_CODE2
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE2(class, subclass) __arch_except_code_eq(EXCEPT_CODE(class, subclass))
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
#if !defined(__except_nesting_begin_defined) && defined(__CRT_HAVE_except_nesting_begin)
#define __except_nesting_begin_defined
/* >> except_nesting_begin(3)
 * Begin a nested  TRY-block. (i.e. inside  of another EXCEPT  block)
 * Don't call this function directly; use `NESTED_EXCEPTION' instead. */
__LIBC __ATTR_NONNULL((1)) void __NOTHROW(__EXCEPT_NESTING_BEGIN_CC except_nesting_begin)(struct _exception_nesting_data *__restrict __saved) __CASMNAME_SAME("except_nesting_begin");
#endif /* !__except_nesting_begin_defined && __CRT_HAVE_except_nesting_begin */
#if !defined(__except_nesting_end_defined) && defined(__CRT_HAVE_except_nesting_end)
#define __except_nesting_end_defined
/* >> except_nesting_end(3)
 * End a nested TRY-block. (i.e. inside of another EXCEPT block) */
__LIBC __ATTR_NONNULL((1)) void __NOTHROW(__EXCEPT_NESTING_END_CC except_nesting_end)(struct _exception_nesting_data *__restrict __saved) __CASMNAME_SAME("except_nesting_end");
#endif /* !__except_nesting_end_defined && __CRT_HAVE_except_nesting_end */
#ifdef __cplusplus
extern "C++" {
__NAMESPACE_INT_BEGIN
template<class __F> struct __FinallyAction {
	__F __c;
	__CXX_CLASSMEMBER __FinallyAction(__F __f) __CXX_NOEXCEPT: __c(__f) {}
	__CXX_CLASSMEMBER ~__FinallyAction() __CXX_NOEXCEPT { __c(); }
};
struct __FinallyBase {
	template<class __F> __CXX_CLASSMEMBER __FinallyAction<__F>
	operator ->* (__F __f) __CXX_NOEXCEPT { return __FinallyAction<__F>(__f); }
};
__NAMESPACE_INT_END
} /* extern "C++" */
#ifndef __COMPILER_UNIQUE
#define __COMPILER_UNIQUE_IMPL2(x, y) x##y
#define __COMPILER_UNIQUE_IMPL(x, y) __COMPILER_UNIQUE_IMPL2(x, y)
#ifdef __COUNTER__
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __COUNTER__)
#else /* __COUNTER__ */
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __LINE__)
#endif /* !__COUNTER__ */
#endif /* !__COMPILER_UNIQUE */
#define __RAII_FINALLY       auto __COMPILER_UNIQUE(__raii_finally) = __NAMESPACE_INT_SYM __FinallyBase()->*[&]

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
#if !defined(NDEBUG) && !defined(NDEBUG_EXCEPT) && !defined(NDEBUG_NOTHROW)
#define __NOTHROW_BEGIN do try
#define __NOTHROW_END   catch(...) { __builtin_unreachable(); } __WHILE0
#else /* !NDEBUG && !NDEBUG_EXCEPT && !NDEBUG_NOTHROW */
/* Sadly, GCC doesn't see the optimization potential when  encountering
 * a catch-block that consists of nothing but `__builtin_unreachable()'
 *
 * It should be obvious that such a construct could be optimized into
 * a section of code that can be considered as NOTHROW, similar to an
 * inline function declared as NOTHROW. */
#define __NOTHROW_BEGIN do
#define __NOTHROW_END   __WHILE0
#endif /* NDEBUG || NDEBUG_EXCEPT || NDEBUG_NOTHROW */
#endif /* !__NOTHROW_BEGIN */

/* Nested exception support */
#if defined(__except_nesting_begin_defined) && defined(__except_nesting_end_defined)
class __cxx_exception_nesting: public _exception_nesting_data {
public:
	__ATTR_FORCEINLINE operator bool() const __CXX_NOEXCEPT { return false; }
	__ATTR_FORCEINLINE __cxx_exception_nesting() __CXX_NOEXCEPT {
		en_size = _EXCEPTION_NESTING_DATA_SIZE;
		except_nesting_begin(this);
	}
	__ATTR_FORCEINLINE ~__cxx_exception_nesting() __CXX_NOEXCEPT {
		except_nesting_end(this);
	}
};
#ifdef __COUNTER__
#define __PRIVATE_CXX_EXCEPT_NESTING_NAME __PP_CAT2(__local_cxx_exception_nesting, __COUNTER__)
#else /* __COUNTER__ */
#define __PRIVATE_CXX_EXCEPT_NESTING_NAME __PP_CAT2(__local_cxx_exception_nesting, __LINE__)
#endif /* !__COUNTER__ */
#define __NESTED_TRY       if(__cxx_exception_nesting __PRIVATE_CXX_EXCEPT_NESTING_NAME {});else try
#define __NESTED_EXCEPTION __cxx_exception_nesting __PRIVATE_CXX_EXCEPT_NESTING_NAME
#endif /* __except_nesting_begin_defined && __except_nesting_end_defined */
#endif /* __cplusplus */

/* Validation for correct usage of TRY-blocks. Because KOS exceptions  can't
 * be nested natively, the user must do this for us by use of NESTED_TRY and
 * and NESTED_EXCEPTION. To ensure that `TRY' doesn't appear as-in inside of
 * EXCEPT-handlers (without proper nesting), we inject an assertion check to
 * every use of `TRY' in source code.
 *
 * Sadly, this means that O(0) TRY-setup becomes O(1), but these checks are
 * entirely optional and can be disabled with `-DNDEBUG_EXCEPT_NESTING'  on
 * a per-file basis.
 *
 * >> TRY {
 * >>     foo();
 * >> } EXCEPT {
 * >>     TRY {            // << WRONG! This needs to be `NESTED_TRY'
 * >>         bar();
 * >>     } EXCEPT {
 * >>         baz();
 * >>         RETHROW();
 * >>     }
 * >>     RETHROW();
 * >> }
 */
#if !defined(NDEBUG) && !defined(NDEBUG_EXCEPT) && !defined(NDEBUG_EXCEPT_NESTING)
#ifdef __CRT_HAVE__except_badusage_no_nesting
/* >> _except_badusage_no_nesting(3)
 * Assertion check handler for missing `TRY' nesting */
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,__NOTHROW,_except_badusage_no_nesting,(void),())
#else /* __CRT_HAVE__except_badusage_no_nesting */
#include <libc/local/kos.except/_except_badusage_no_nesting.h>
/* >> _except_badusage_no_nesting(3)
 * Assertion check handler for missing `TRY' nesting */
__NAMESPACE_LOCAL_USING_OR_IMPL(_except_badusage_no_nesting, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_NORETURN void __NOTHROW(__LIBCCALL _except_badusage_no_nesting)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_except_badusage_no_nesting))(); })
#endif /* !__CRT_HAVE__except_badusage_no_nesting */
#ifdef __CRT_HAVE__except_check_no_nesting
/* >> _except_check_no_nesting(3)
 * Assert that a TRY-block is currently allowed (iow: that no error is active) */
__CDECLARE_VOID(,__NOTHROW,_except_check_no_nesting,(void),())
#elif defined(__CRT_HAVE_except_active) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#include <libc/local/kos.except/_except_check_no_nesting.h>
/* >> _except_check_no_nesting(3)
 * Assert that a TRY-block is currently allowed (iow: that no error is active) */
__NAMESPACE_LOCAL_USING_OR_IMPL(_except_check_no_nesting, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW(__LIBCCALL _except_check_no_nesting)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_except_check_no_nesting))(); })
#endif /* ... */
#if defined(__CRT_HAVE__except_check_no_nesting) || defined(__CRT_HAVE_except_active) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
#if !defined(__OPTIMIZE_SIZE__) && defined(__arch_except_active)
#define _except_check_no_nesting() (void)(__likely(!__arch_except_active()) || (_except_badusage_no_nesting(), 0))
#endif /* !__OPTIMIZE_SIZE__ && __arch_except_active */
#if !defined(TRY) && defined(__TRY)
#if !defined(__OPTIMIZE_SIZE__) && defined(__arch_except_active)
#define TRY if __unlikely(__arch_except_active()) _except_badusage_no_nesting(); else __TRY
#else /* !__OPTIMIZE_SIZE__ && __arch_except_active */
#define TRY if ((_except_check_no_nesting(), 0)); else __TRY
#endif /* __OPTIMIZE_SIZE__ || !__arch_except_active */
#endif /* !TRY && __TRY */
#endif /* __CRT_HAVE__except_check_no_nesting || __CRT_HAVE_except_active || __CRT_HAVE_except_code || __arch_except_code || __CRT_HAVE_except_data || __arch_except_data */
#else /* !NDEBUG && !NDEBUG_EXCEPT && !NDEBUG_EXCEPT_NESTING */
#define _except_badusage_no_nesting() __builtin_unreachable()
#define _except_check_no_nesting()    (void)0
#endif /* NDEBUG || NDEBUG_EXCEPT || NDEBUG_EXCEPT_NESTING */

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
#if !defined(RAII_FINALLY) && defined(__RAII_FINALLY)
#define RAII_FINALLY __RAII_FINALLY
#endif /* !RAII_FINALLY && __RAII_FINALLY */

/* Same as `TRY', but never do a check for proper nesting. Instead, assume
 * that the guarded code must be NOEXCEPT when an error is already active. */
#if !defined(UNNESTED_TRY) && defined(__TRY)
#define UNNESTED_TRY __TRY
#endif /* !UNNESTED_TRY && __TRY */


#ifndef __INTELLISENSE__
/* Use macros to directly invoke __arch_* variants (if they've been defined) */
#ifdef __arch_except_data
#define except_data() __arch_except_data()
#endif /* __arch_except_data */
#ifdef __arch_except_code
#define except_code() __arch_except_code()
#endif /* __arch_except_code */
#ifdef __arch_except_active
#define except_active() __arch_except_active()
#endif /* __arch_except_active */
#ifdef __arch_except_class
#define except_class() __arch_except_class()
#endif /* __arch_except_class */
#ifdef __arch_except_subclass
#define except_subclass() __arch_except_subclass()
#endif /* __arch_except_subclass */
#ifdef __arch_except_register_state
#define except_register_state() __arch_except_register_state()
#endif /* __arch_except_register_state */
#ifdef __USE_KOS_KERNEL
#ifdef __arch_except_info
#define except_info() __arch_except_info()
#endif /* __arch_except_info */
#endif /* __USE_KOS_KERNEL */
#endif /* !__INTELLISENSE__ */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_EXCEPT_H */
