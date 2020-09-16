/* HASH CRC-32:0xba7adca6 */
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
#include <kos/except/codes.h>        /* E_OK, ... */
#include <kos/bits/fastexcept.h>

#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8
#endif /* !EXCEPTION_DATA_POINTERS */


#ifdef __USE_KOS_KERNEL
#include <hybrid/byteorder.h>

#ifndef EXCEPT_BACKTRACE_SIZE
#ifdef NDEBUG
#define EXCEPT_BACKTRACE_SIZE 0
#else /* NDEBUG */
#define EXCEPT_BACKTRACE_SIZE 16
#endif /* !NDEBUG */
#endif /* !EXCEPT_BACKTRACE_SIZE */
#define EXCEPT_FNORMAL    0x0000 /* Normal exception handler flags. */
#define EXCEPT_FRETHROW   0x0001 /* FLAG: The exception should be rethrown.
                                  * Unless set when `__cxa_end_catch()' is called, `ei_code'
                                  * will be changed to `E_OK', indicating no exception. */
#ifndef __KERNEL__
#define EXCEPT_FINEXCEPT  0x0002 /* FLAG: Currently within `libc_except_handler(3|4)()' (used to prevent
                                  *       an infinite loop when the exception handler itself is faulting) */
#define EXCEPT_FINEXCEPT2 0x0004 /* FLAG: Same as `EXCEPT_FINEXCEPT', but set when that flag was already set.
                                  *       When both flags are already set, a coredump is triggered.
                                  *       Using this double-indirection mechanism, it becomes possible to handle
                                  *       things such as segmentation faults when accessing memory during unwinding,
                                  *       and ensuring that the correct unwind error codes (in this case `UNWIND_SEGFAULT')
                                  *       get produced instead of always causing `UNWIND_USER_RECURSION' (which should only
                                  *       be produced if the unwind machinery itself has become faulty) */
#define EXCEPT_FMAYSIGNAL 0x0008 /* FLAG: The exception may be converted into a signal when `error_unwind(3)' cannot find
                                  *       a handler apart of some except-aware module (s.a. set_exception_handler:#4).
                                  *       If the exception cannot be translated, a coredump is performed. */
#endif /* !__KERNEL__ */
#define OFFSET_EXCEPTION_INFO_STATE    0
#define OFFSET_EXCEPTION_INFO_TRACE    __SIZEOF_ERROR_REGISTER_STATE
#define OFFSET_EXCEPTION_INFO_FLAGS    (__SIZEOF_ERROR_REGISTER_STATE + (__SIZEOF_POINTER__ * EXCEPT_BACKTRACE_SIZE))
#define OFFSET_EXCEPTION_INFO_CODE     (__SIZEOF_ERROR_REGISTER_STATE + (__SIZEOF_POINTER__ * (EXCEPT_BACKTRACE_SIZE + 1)))
#define OFFSET_EXCEPTION_INFO_DATA     (__SIZEOF_ERROR_REGISTER_STATE + (__SIZEOF_POINTER__ * (EXCEPT_BACKTRACE_SIZE + 1)))
#define OFFSET_EXCEPTION_INFO_POINTERS (__SIZEOF_ERROR_REGISTER_STATE + (__SIZEOF_POINTER__ * (EXCEPT_BACKTRACE_SIZE + 2)))
#endif /* __USE_KOS_KERNEL */

#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/mcontext.h>
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


#ifndef __error_register_state_t_defined
#define __error_register_state_t_defined 1
typedef __ERROR_REGISTER_STATE_TYPE error_register_state_t;
#endif /* !__error_register_state_t_defined */

typedef __error_code_t error_code_t;
typedef __error_class_t error_class_t;
typedef __error_subclass_t error_subclass_t;

#ifdef __USE_KOS_KERNEL
#undef ei_data
#undef ei_code
#undef ei_class
#undef ei_subclass
struct exception_info {
	/* The CPU state at the time the exception was originally thrown.
	 * NOTE: The PC register of this state represents the program
	 *       location _AFTER_ the instruction that caused the exception.
	 *       In the case of the exception being caused by a `THROW()',
	 *       this is the return address of the call to the throw-function.
	 *       In the case of cpu-specific exceptions, it points after the
	 *       instruction responsible for the exception.
	 *    -> With that in mind, when querying for special properties of PC,
	 *       you must always subtract `1' from the address, such as when
	 *       calling `unwind_at()', which requires you to provide `PC - 1'
	 *       for its `abs_pc' argument. */
	error_register_state_t    ei_state;
#if EXCEPT_BACKTRACE_SIZE != 0
	/* Exception backtrace (from least-recent[0] to most-recent[EXCEPT_BACKTRACE_SIZE - 1])
	 * This vector is populated as the stack is unwound, until it is either full, or until
	 * a new exception is thrown.
	 * The vector's ends either when `EXCEPT_BACKTRACE_SIZE' were found, or upon the first
	 * entry that evaluates to `NULL'. If a `NULL' entry was found, and the caller is currently
	 * in the process of unwinding the stack, the traceback continues where their CPU context
	 * meets with the next unwind location.
	 * NOTE: In order to prevent redundancy, this trace only starts with the first unwind
	 *       location of the exception, with the exception's original throw-location found
	 *       stored within the PC register of `ei_state'
	 * NOTE: The pointers in this traceback have not been adjusted, meaning that they probably
	 *       point to the first instruction after some `call' instruction (i.e. they're the
	 *       return addresses loaded during unwinding) */
	void                     *ei_trace[EXCEPT_BACKTRACE_SIZE];
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	__uintptr_t               ei_flags;    /* Flags describing the current exception state (Set of `EXCEPT_F*'). */
	union {
		error_code_t          ei_code;     /* Current exception code. */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			error_class_t     ei_class;    /* Current exception class. */
			error_subclass_t  ei_subclass; /* Current exception sub-class. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			error_subclass_t  ei_subclass; /* Current exception sub-class. */
			error_class_t     ei_class;    /* Current exception class. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		_ei_class_subclass
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
		struct exception_data ei_data;     /* Exception data. */
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ei_code_data
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};
#if !defined(__COMPILER_HAVE_TRANSPARENT_UNION) && !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define ei_data      _ei_code_data.ei_data
#define ei_code      _ei_code_data.ei_code
#define ei_class     _ei_code_data._ei_class_subclass.ei_class
#define ei_subclass  _ei_code_data._ei_class_subclass.ei_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#define ei_data      _ei_code_data.ei_data
#define ei_code      _ei_code_data.ei_code
#define ei_class     _ei_code_data.ei_class
#define ei_subclass  _ei_code_data.ei_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define ei_class     _ei_class_subclass.ei_class
#define ei_subclass  _ei_class_subclass.ei_subclass
#endif

#else /* __USE_KOS_KERNEL */
struct exception_info;
#endif /* !__USE_KOS_KERNEL */


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
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL error_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) __CASMNAME_SAME("error_as_signal");
#else /* __CRT_HAVE_error_as_signal */
#include <libc/local/kos.except/error_as_signal.h>
/* Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_as_signal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(__LIBKCALL error_as_signal)(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_as_signal))(__self, __result); })
#endif /* !__CRT_HAVE_error_as_signal */
#ifdef __CRT_HAVE_error_name
/* Return the name of the given error, or `NULL` if unknown.
 * This name is the same as the `E_*` identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))` -> "E_BADALLOC" */
__LIBC __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL error_name)(error_code_t __code) __CASMNAME_SAME("error_name");
#else /* __CRT_HAVE_error_name */
#include <libc/local/kos.except/error_name.h>
/* Return the name of the given error, or `NULL` if unknown.
 * This name is the same as the `E_*` identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))` -> "E_BADALLOC" */
__NAMESPACE_LOCAL_USING_OR_IMPL(error_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBKCALL error_name)(error_code_t __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_name))(__code); })
#endif /* !__CRT_HAVE_error_name */
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
 * Following this, the returned register state should then be loaded. */
__LIBC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) error_register_state_t *__NOTHROW_NCX(__ERROR_UNWIND_CC error_unwind)(error_register_state_t *__restrict __state) __CASMNAME_SAME("error_unwind");
#endif /* __CRT_HAVE_error_unwind */
#endif /* __USE_KOS_KERNEL */
#ifdef __CRT_HAVE_error_throw_current
/* Throw the currently set (in `error_data()') exception. */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL error_throw_current)(void) __THROWS(...) __CASMNAME_SAME("error_throw_current");
#endif /* __CRT_HAVE_error_throw_current */
#ifndef __error_rethrow_defined
#define __error_rethrow_defined 1
#ifdef __CRT_HAVE_error_rethrow
/* Rethrow the current exception (same as a c++ `throw;' expression) */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__LIBKCALL error_rethrow)(void) __THROWS(...) __CASMNAME_SAME("error_rethrow");
#else /* __CRT_HAVE_error_rethrow */
#undef __error_rethrow_defined
#endif /* !__CRT_HAVE_error_rethrow */
#endif /* !__error_rethrow_defined */
/* Rethrow the last exception */
#ifdef __error_rethrow_defined
#define RETHROW() error_rethrow()
#elif defined(__cplusplus)
#define RETHROW() throw
#endif /* ... */
#ifdef __INTELLISENSE__
/* Throw a new exception `code', which is either an exception class,
 * an exception code, or an exception-class+sub-class pair, written
 * as `(class,subclass)', going in hand with the macros defining the
 * various exceptions there are.
 * Following this, up to `EXCEPTION_DATA_POINTERS' optional exception
 * arguments may be provided, which are stored in `e_pointers', with
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
#ifndef __error_throw_defined
#define __error_throw_defined 1
#ifdef __CRT_HAVE_error_throw
/* Throw an exception and fill exception pointers with all zeroes */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__ERROR_THROW_CC error_throw)(error_code_t __code) __THROWS(...) __CASMNAME_SAME("error_throw");
#else /* __CRT_HAVE_error_throw */
#undef __error_throw_defined
#endif /* !__CRT_HAVE_error_throw */
#endif /* !__error_throw_defined */
#ifndef __error_thrown_defined
#define __error_thrown_defined 1
#ifdef __CRT_HAVE_error_thrown
/* Throw an exception and load `argc' pointers from varargs */
__LIBC __ATTR_COLD __ATTR_NORETURN void (__ERROR_THROWN_CC error_thrown)(error_code_t __code, unsigned int ___argc, ...) __THROWS(...) __CASMNAME_SAME("error_thrown");
#else /* __CRT_HAVE_error_thrown */
#undef __error_thrown_defined
#endif /* !__CRT_HAVE_error_thrown */
#endif /* !__error_thrown_defined */
#define __PRIVATE_THROW_PACKAGE_CODE1(code) code
#define __PRIVATE_THROW_PACKAGE_CODE2       ERROR_CODE
#define __PRIVATE_THROW_PACKAGE_CODEN2(n)   __PRIVATE_THROW_PACKAGE_CODE##n
#define __PRIVATE_THROW_PACKAGE_CODEN(n)    __PRIVATE_THROW_PACKAGE_CODEN2(n)
#define __PRIVATE_THROW_PACKAGE_CODE(...)   __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

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
#define THROW(...)            __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
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
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)              __PRIVATE_WAS_THROWN_PACKAGE_CODE##n
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN(n)               __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE(...)              __PRIVATE_WAS_THROWN_PACKAGE_CODEX(__PRIVATE_WAS_THROWN_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEX(x)               x
#define was_thrown(code)                                    __PRIVATE_WAS_THROWN_PACKAGE_CODE code
#endif /* !was_thrown */
#endif /* !__INTELLISENSE__ */
#ifdef __cplusplus
/* TODO: In user-space, using TRY and EXCEPT should leave some sort of marker in the
 *       binary that allows for libc to consider these handlers as `dlexceptaware(3)'
 *       when operating in except-mode #4. However, I am unsure as to how this could
 *       be implemented without making some additional tweaks to gcc under KOS, though
 *       that wouldn't even be the first time I had to tweak binutils/gcc for this
 *       project... */
#ifndef __TRY
#define __TRY    try
#endif /* !__TRY */
#ifndef __EXCEPT
#define __EXCEPT catch(...)
#endif /* !__EXCEPT */
#ifndef TRY
#define TRY      __TRY
#endif /* !TRY */
#ifndef EXCEPT
#define EXCEPT   __EXCEPT
#endif /* !EXCEPT */
#endif /* __cplusplus */


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
