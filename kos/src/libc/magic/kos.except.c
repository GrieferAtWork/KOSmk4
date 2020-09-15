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
%[default:section(".text.crt{|.dos}.except.io.utility")]

%{
#include <features.h>

#include <hybrid/pp/__va_nargs.h>

#include <bits/types.h>
#include <kos/asm/except.h>          /* __ERROR_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h> /* struct exception_data */
#include <kos/except/codes.h>        /* E_OK, ... */

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


}

%[declare_kernel_export(
	"error_rethrow", "__cxa_rethrow", "_Unwind_Resume",
	"error_thrown", "error_throw", "error_throw_current",
	"error_info", "error_data", "error_register_state",
	"error_code", "error_active", "error_class", "error_subclass",
	"error_unwind", "__cxa_begin_catch", "__cxa_end_catch",
	"__gxx_personality_v0", "__gcc_personality_v0",
	"error_as_errno", "error_as_signal",
)]



/* TODO: Add [[preferred_fastbind]] variants that become available
 *       when compiling for kernel-space, and that are implemented
 *       to directly access the TLS exception storage. */



%[define_replacement(error_register_state_t = __ERROR_REGISTER_STATE_TYPE)]
%[define_replacement(error_code_t = __error_code_t)]
%[define_replacement(error_class_t = __error_class_t)]
%[define_replacement(error_subclass_t = __error_subclass_t)]
%[define_replacement(bool = __BOOL)]


/* Returns non-zero if there is an active exception. */
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, const, nonnull, decl_prefix(struct exception_data;)]]
struct exception_data *error_data(void);

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
error_code_t error_code(void);

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, pure, userimpl, requires_function(error_code)]]
[[impl_include("<kos/except/codes.h>")]]
$bool error_active(void) {
	return error_code() != @E_OK@;
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
[[userimpl, requires_function(error_code)]]
error_class_t error_class(void) {
	return @ERROR_CLASS@(error_code());
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
[[userimpl, requires_function(error_code)]]
error_subclass_t error_subclass(void) {
	return @ERROR_SUBCLASS@(error_code());
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, const, nonnull, decl_include("<kos/asm/except.h>")]]
[[decl_prefix(
#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */
)]]
error_register_state_t *error_register_state(void);

@@Transform the given exception into a posix errno value
[[wunused, pure]]
$errno_t error_as_errno([[nonnull]] struct exception_data const *__restrict data);


%struct __siginfo_struct;
@@Transform the given exception into a posix signal.
@@If doing this is possible, fill in `*result' and return `true'.
@@Otherwise, `*result' is left in an undefined state, and `false' is returned.
[[wunused, decl_prefix(struct __siginfo_struct;)]]
$bool error_as_signal([[nonnull]] struct exception_data const *__restrict data,
                      [[nonnull]] struct __siginfo_struct *__restrict result);




%#ifdef __USE_KOS_KERNEL
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, const, nonnull]]
[[decl_prefix(struct exception_info;)]]
struct exception_info *error_info(void);

%{
#ifndef __ERROR_UNWIND_CC
#define __ERROR_UNWIND_CC __LIBKCALL
#endif /* !__ERROR_UNWIND_CC */
}

@@Unwind the given register state to propagate the currently set error.
@@Following this, the returned register state should then be loaded.
[[kernel, no_crt_dos_wrapper, cc(__ERROR_UNWIND_CC)]]
[[wunused, nonnull, decl_include("<kos/asm/except.h>")]]
[[decl_prefix(
#ifndef __ERROR_UNWIND_CC
#define __ERROR_UNWIND_CC __LIBKCALL
#endif /* !__ERROR_UNWIND_CC */
)]]
[[decl_prefix(
#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */
)]]
error_register_state_t *error_unwind([[nonnull]] error_register_state_t *__restrict state);

%#endif /* __USE_KOS_KERNEL */


@@Throw the currently set (in `error_data()') exception.
[[noreturn, cold]]
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
void error_throw_current(void);

@@Rethrow the current exception (same as a c++ `throw;' expression)
[[guard, noreturn, cold]]
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
void error_rethrow(void);


%{
/* Rethrow the last exception */
#ifdef __error_rethrow_defined
#define RETHROW() error_rethrow()
#elif defined(__cplusplus)
#define RETHROW() throw
#endif /* ... */
}


%#ifdef __INTELLISENSE__
%{
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
}
%#else /* __INTELLISENSE__ */
%{

#ifndef THROW
#ifndef __ERROR_THROW_CC
#define __ERROR_THROW_CC __LIBKCALL
#endif /* !__ERROR_THROW_CC */

#ifndef __ERROR_THROWN_CC
#define __ERROR_THROWN_CC __LIBKCALL
#endif /* !__ERROR_THROWN_CC */
}


@@Throw an exception and fill exception pointers with all zeroes
[[guard, decl_prefix(
#ifndef __ERROR_THROW_CC
#define __ERROR_THROW_CC __LIBKCALL
#endif /* !__ERROR_THROW_CC */
)]]
[[noreturn, cold, cc(__ERROR_THROW_CC)]]
[[kernel, no_crt_dos_wrapper, cc(__ERROR_THROW_CC)]]
void error_throw(error_code_t code);

@@Throw an exception and load `argc' pointers from varargs
[[guard, decl_prefix(
#ifndef __ERROR_THROWN_CC
#define __ERROR_THROWN_CC __LIBKCALL
#endif /* !__ERROR_THROWN_CC */
)]]
[[noreturn, cold, cc(__ERROR_THROWN_CC)]]
[[kernel, no_crt_dos_wrapper, cc(__ERROR_THROWN_CC)]]
void error_thrown(error_code_t code, unsigned int _argc, ...);


%{
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
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE1(code) \
	((__builtin_constant_p(code) && (code) <= 0xffff) ? error_class() == (code) : error_code() == (code))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE2(class, subclass) (error_code() == ERROR_CODE(class, subclass))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)              __PRIVATE_WAS_THROWN_PACKAGE_CODE##n
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN(n)               __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE(...)              __PRIVATE_WAS_THROWN_PACKAGE_CODEX(__PRIVATE_WAS_THROWN_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEX(x)               x
#define was_thrown(code)                                    __PRIVATE_WAS_THROWN_PACKAGE_CODE code
#endif /* !was_thrown */
}

%#endif /* !__INTELLISENSE__ */

%{
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
}


%{

__SYSDECL_END
#endif /* __CC__ */

}