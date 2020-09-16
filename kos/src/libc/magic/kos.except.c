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

%(auto_source){
#include <signal.h>
}


%{
#include <features.h>

#include <hybrid/pp/__va_nargs.h>

#include <bits/types.h>
#include <kos/bits/except.h>         /* __ERROR_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h> /* struct exception_data */
#include <kos/except/codes.h>        /* E_OK, ... */
}%[insert:prefix(
#include <kos/bits/fastexcept.h>
)]%{

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




}
%#ifdef __CC__
%{
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
)]



%[define_replacement(error_register_state_t = __ERROR_REGISTER_STATE_TYPE)]
%[define_replacement(error_code_t = __error_code_t)]
%[define_replacement(error_class_t = __error_class_t)]
%[define_replacement(error_subclass_t = __error_subclass_t)]
%[define_replacement(bool = __BOOL)]
%[define_replacement(true = 1)]
%[define_replacement(false = 0)]


/* Returns non-zero if there is an active exception. */
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_data)),
  preferred_fast_extern_inline("error_data", { return __arch_error_data(); })]]
[[wunused, const, nonnull, decl_prefix(struct exception_data;)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>"), requires(defined(__arch_error_data))]]
struct exception_data *error_data(void) {
	return __arch_error_data();
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_code)),
  preferred_fast_extern_inline("error_code", { return __arch_error_code(); })]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_code) || $has_function(error_data))]]
error_code_t error_code(void) {
@@pp_ifdef __arch_error_code@@
	return __arch_error_code();
@@pp_else@@
	return error_data()->@e_code@;
@@pp_endif@@
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_active)),
  preferred_fast_extern_inline("error_active", { return __arch_error_active(); })]]
[[wunused, pure, userimpl, requires_function(error_code)]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_active) || $has_function(error_code))]]
$bool error_active(void) {
@@pp_ifdef __arch_error_active@@
	return __arch_error_active();
@@pp_else@@
	return error_code() != @E_OK@;
@@pp_endif@@
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_class)),
  preferred_fast_extern_inline("error_class", { return __arch_error_class(); })]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_class) || $has_function(error_code))]]
error_class_t error_class(void) {
@@pp_ifdef __arch_error_class@@
	return __arch_error_class();
@@pp_else@@
	return @ERROR_CLASS@(error_code());
@@pp_endif@@
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_subclass)),
  preferred_fast_extern_inline("error_subclass", { return __arch_error_subclass(); })]]
[[wunused, pure, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_subclass) || $has_function(error_code))]]
error_subclass_t error_subclass(void) {
@@pp_ifdef __arch_error_subclass@@
	return __arch_error_subclass();
@@pp_else@@
	return @ERROR_SUBCLASS@(error_code());
@@pp_endif@@
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_register_state)),
  preferred_fast_extern_inline("error_register_state", { return __arch_error_register_state(); })]]
[[wunused, const, nonnull, decl_include("<kos/bits/except.h>")]]
[[decl_prefix(
#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */
)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_register_state))]]
error_register_state_t *error_register_state(void) {
	return __arch_error_register_state();
}

@@Transform the given exception into a posix errno value
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, pure, decl_include("<bits/types.h>")]]
[[decl_prefix(struct exception_data;)]]
[[impl_include("<asm/os/errno.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/reason/fs.h>")]]
[[impl_include("<kos/except/reason/inval.h>")]]
[[impl_include("<kos/except/reason/io.h>")]]
[[impl_include("<kos/except/reason/net.h>")]]
[[impl_include("<kos/except/reason/noexec.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/kernel/handle.h>")]]
$errno_t error_as_errno([[nonnull]] struct exception_data const *__restrict self) {
@@pp_ifdef EPERM@@
	errno_t result = EPERM;
@@pp_else@@
	errno_t result = 1;
@@pp_endif@@
	switch (self->@e_class@) {
/*[[[deemon
final local DEFAULT_ERRNO = "EPERM";
import * from deemon;
import * from ....misc.libgen.exceptinfo;
function isCustomErrnoExpr(s) -> s !is none && s != "DEFAULT_ERRNO";

@@Returns (formattedExpr, listOfMacrosThatMustBeDefined)
function formatErrnoExpr(cls: ExceptClass): (string, {string...}) {
	local expr = File.Writer();
	cls.printErrnoExpr(expr, cbField: [](name) ->
		expr << "self->e_args." << cls.findFieldByName(name)[0]);
	expr = expr.string;
	local reqMacros = [];
	File.Writer resultExpr;
	local flushStart = 0, i = 0, len = #expr;
	while (i < len) {
		if (!expr.issymstrt(i)) {
			++i;
			continue;
		}
		local symStart = i;
		++i;
		while (i < len && expr.issymcont(i))
			++i;
		local symb = expr[symStart:i];
		if (symb !in ["self"]) {
			resultExpr << expr[flushStart:symStart];
			if (symb.startswith("E") && "_" !in symb) {
				resultExpr << symb;
				if (symb !in reqMacros)
					reqMacros.append(symb);
			} else {
				resultExpr << "@" << symb << "@";
			}
			flushStart = i;
		}
	}
	resultExpr << expr[flushStart:];
	return (resultExpr.string, reqMacros);
}

for (local name, ppCondToCls: parseExceptionClasses()) {
	for (local ppCond, cls: ppCondToCls) {
		if (cls.baseClass !is none)
			continue;
		local hasErrnoExpr = isCustomErrnoExpr(cls.errnoExpr);
		local hasSubClassErrnoExpr = false;
		for (local c: cls.subClasses) {
			if (isCustomErrnoExpr(c.errnoExpr)) {
				hasSubClassErrnoExpr = true;
				hasErrnoExpr = true;
				break;
			}
		}
		if (!hasErrnoExpr)
			continue;
		if (!hasSubClassErrnoExpr) {
			local expr, reqMacros = formatErrnoExpr(cls)...;
			reqMacros = " && ".join(for (local x: reqMacros) "defined({})".format({ x }));
			if (!reqMacros)
				reqMacros = cls.ppCond;
			else if (cls.ppCond != "1") {
				reqMacros = "({}) && ({})".format({ reqMacros, cls.ppCond });
			}
			if (reqMacros != "1")
				print("@@pp_if ", reqMacros, "@@");
			print("\tcase @", cls.name, "@:");
			print("\t\tresult = ", expr.replace("\n", "\n\t\t"), ";");
			print("\t\tbreak;");
			if (reqMacros != "1")
				print("@@pp_endif@@");
			print;
			continue;
		}
		if (cls.ppCond != "1")
			print("@@pp_if ", cls.ppCond, "@@");
		print("\tcase @", cls.name, "@:");
		if (isCustomErrnoExpr(cls.errnoExpr)) {
			local expr, reqMacros = formatErrnoExpr(cls)...;
			reqMacros = " && ".join(for (local x: reqMacros) "defined({})".format({ x }));
			if (reqMacros)
				print("@@pp_if ", reqMacros, "@@");
			print("\t\tresult = ", expr.replace("\n", "\n\t\t"), ";");
			if (reqMacros)
				print("@@pp_endif@@");
		}
		// Deal with sub-classes
		print("\t\tswitch(self->@e_subclass@) {");
		for (local c: cls.subClasses) {
			if (!isCustomErrnoExpr(c.errnoExpr))
				continue;
			local expr, reqMacros = formatErrnoExpr(c)...;
			reqMacros = " && ".join(for (local x: reqMacros) "defined({})".format({ x }));
			if (reqMacros)
				print("@@pp_if ", reqMacros, "@@");
			print("\t\tcase @ERROR_SUBCLASS@(@ERROR_CODEOF@(@", c.name, "@)):");
			print("\t\t\tresult = ", expr.replace("\n", "\n\t\t\t"), ";");
			print("\t\t\tbreak;");
			if (reqMacros)
				print("@@pp_endif@@");
		}
		print("\t\tdefault: break;");
		print("\t\t}");
		print("\t\tbreak;");
		if (cls.ppCond != "1")
			print("@@pp_endif@@");
		print;
	}
}
]]]*/
@@pp_if defined(EACCES)@@
	case @E_INSUFFICIENT_RIGHTS@:
		result = EACCES;
		break;
@@pp_endif@@

@@pp_if defined(EIO)@@
	case @E_IOERROR@:
		result = EIO;
		break;
@@pp_endif@@

@@pp_if defined(EOK)@@
	case @E_OK@:
		result = EOK;
		break;
@@pp_endif@@

@@pp_if defined(EINTR)@@
	case @E_INTERRUPT@:
		result = EINTR;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_SEGFAULT@:
		result = EFAULT;
		break;
@@pp_endif@@

	case @E_BADALLOC@:
@@pp_if defined(ENOMEM)@@
		result = ENOMEM;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(EMFILE)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS@)):
			result = EMFILE;
			break;
@@pp_endif@@
@@pp_if defined(ENFILE)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_BADALLOC_INSUFFICIENT_HANDLE_RANGE@)):
			result = ENFILE;
			break;
@@pp_endif@@
@@pp_if defined(EADDRNOTAVAIL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_BADALLOC_INSUFFICIENT_PORT_NUMBERS@)):
			result = EADDRNOTAVAIL;
			break;
@@pp_endif@@
		default: break;
		}
		break;

@@pp_if defined(ENOSYS)@@
	case @E_UNKNOWN_SYSTEMCALL@:
		result = ENOSYS;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_UNHANDLED_INTERRUPT@:
		result = EFAULT;
		break;
@@pp_endif@@

@@pp_if defined(ENODEV)@@
	case @E_NO_DEVICE@:
		result = ENODEV;
		break;
@@pp_endif@@

@@pp_if defined(EAGAIN)@@
	case @E_WOULDBLOCK@:
		result = EAGAIN;
		break;
@@pp_endif@@

@@pp_if defined(ERANGE)@@
	case @E_BUFFER_TOO_SMALL@:
		result = ERANGE;
		break;
@@pp_endif@@

@@pp_if defined(EINVAL)@@
	case @E_DIVIDE_BY_ZERO@:
		result = EINVAL;
		break;
@@pp_endif@@

	case @E_INVALID_HANDLE@:
@@pp_if defined(EBADF)@@
		result = EBADF;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(ENOTSOCK) && defined(EBADFD)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_HANDLE_FILETYPE@)):
			result = self->@e_args@.@e_invalid_handle@.@ih_filetype@.@f_needed_handle_type@ == @HANDLE_TYPE_SOCKET@ ? ENOTSOCK : EBADFD;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_HANDLE_OPERATION@)):
			result = EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(EOPNOTSUPP)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_HANDLE_NET_OPERATION@)):
			result = EOPNOTSUPP;
			break;
@@pp_endif@@
		default: break;
		}
		break;

@@pp_if defined(EOVERFLOW)@@
	case @E_OVERFLOW@:
		result = EOVERFLOW;
		break;
@@pp_endif@@

@@pp_if defined(EILSEQ)@@
	case @E_UNICODE_ERROR@:
		result = EILSEQ;
		break;
@@pp_endif@@

@@pp_if defined(EINVAL)@@
	case @E_BREAKPOINT@:
		result = EINVAL;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_STACK_OVERFLOW@:
		result = EFAULT;
		break;
@@pp_endif@@

@@pp_if defined(ESRCH)@@
	case @E_PROCESS_EXITED@:
		result = ESRCH;
		break;
@@pp_endif@@

@@pp_if (defined(EPERM)) && (!defined(__i386__) && !defined(__x86_64__))@@
	case @E_ILLEGAL_INSTRUCTION@:
		result = EPERM;
		break;
@@pp_endif@@

@@pp_if (defined(EPERM)) && (defined(__i386__) || defined(__x86_64__))@@
	case @E_ILLEGAL_INSTRUCTION@:
		result = EPERM;
		break;
@@pp_endif@@

@@pp_if defined(ERANGE)@@
	case @E_INDEX_ERROR@:
		result = ERANGE;
		break;
@@pp_endif@@

@@pp_if defined(EPERM)@@
	case @E_NOT_IMPLEMENTED@:
		result = EPERM;
		break;
@@pp_endif@@

	case @E_FSERROR@:
		switch(self->@e_subclass@) {
@@pp_if defined(ENOENT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_DELETED@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_FILE_NOT_FOUND@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_PATH_NOT_FOUND@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENAMETOOLONG)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_ILLEGAL_PATH@)):
			result = ENAMETOOLONG;
			break;
@@pp_endif@@
@@pp_if defined(ENOTDIR)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_NOT_A_DIRECTORY@)):
			result = ENOTDIR;
			break;
@@pp_endif@@
@@pp_if defined(ELOOP)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_TOO_MANY_SYMBOLIC_LINKS@)):
			result = ELOOP;
			break;
@@pp_endif@@
@@pp_if defined(EACCES)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_ACCESS_DENIED@)):
			result = EACCES;
			break;
@@pp_endif@@
@@pp_if defined(ENOSPC)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_DISK_FULL@)):
			result = ENOSPC;
			break;
@@pp_endif@@
@@pp_if defined(EROFS)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_READONLY@)):
			result = EROFS;
			break;
@@pp_endif@@
@@pp_if defined(EMLINK)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_TOO_MANY_HARD_LINKS@)):
			result = EMLINK;
			break;
@@pp_endif@@
@@pp_if defined(EISDIR)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_IS_A_DIRECTORY@)):
			result = EISDIR;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_NOT_A_SYMBOLIC_LINK@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ELOOP)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_IS_A_SYMBOLIC_LINK@)):
			result = ELOOP;
			break;
@@pp_endif@@
@@pp_if defined(EEXIST)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_FILE_ALREADY_EXISTS@)):
			result = EEXIST;
			break;
@@pp_endif@@
@@pp_if defined(ENOTEMPTY)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_DIRECTORY_NOT_EMPTY@)):
			result = ENOTEMPTY;
			break;
@@pp_endif@@
@@pp_if defined(EXDEV)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_CROSS_DEVICE_LINK@)):
			result = EXDEV;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_DIRECTORY_MOVE_TO_CHILD@)):
			result = EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOTBLK)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_NOT_A_BLOCK_DEVICE@)):
			result = ENOTBLK;
			break;
@@pp_endif@@
@@pp_if defined(ENOTBLK)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_NO_BLOCK_DEVICE@)):
			result = ENOTBLK;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_WRONG_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_UNKNOWN_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_CORRUPTED_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(EBUSY)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_DEVICE_ALREADY_MOUNTED@)):
			result = EBUSY;
			break;
@@pp_endif@@
@@pp_if defined(EBUSY)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_PATH_ALREADY_MOUNTED@)):
			result = EBUSY;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_NOT_A_MOUNTING_POINT@)):
			result = EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOTDIR)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_IS_A_MOUNTING_POINT@)):
			result = ENOTDIR;
			break;
@@pp_endif@@
@@pp_if defined(ESPIPE) && defined(EINVAL) && defined(EPERM)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_FSERROR_UNSUPPORTED_OPERATION@)):
			result = self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_SEEK@ ? ESPIPE :
			        (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_READ@ || self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_WRITE@ ||
			         self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_TRUNC@ || self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_READDIR@)
			         ? EINVAL : EPERM;
			break;
@@pp_endif@@
		default: break;
		}
		break;

@@pp_if defined(EPERM)@@
	case @E_INVALID_CONTEXT@:
		result = EPERM;
		break;
@@pp_endif@@

@@pp_if defined(ENOEXEC)@@
	case @E_NOT_EXECUTABLE@:
		result = ENOEXEC;
		break;
@@pp_endif@@

	case @E_INVALID_ARGUMENT@:
@@pp_if defined(EINVAL)@@
		result = EINVAL;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(EAFNOSUPPORT) && defined(ESOCKTNOSUPPORT) && defined(EPROTONOSUPPORT) && defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_ARGUMENT_UNKNOWN_COMMAND@)):
			result = self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY@ ? EAFNOSUPPORT :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE@ ? ESOCKTNOSUPPORT :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL@ ? EPROTONOSUPPORT :
			        EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOTCONN) && defined(EDESTADDRREQ) && defined(EISCONN) && defined(ENXIO) && defined(EPIPE) && defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_ARGUMENT_BAD_STATE@)):
			result = self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED@ ||
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED@ ||
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED@ ? ENOTCONN :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED@ ? EDESTADDRREQ :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED@ ? EISCONN :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS@ ? ENXIO :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS@ ? EPIPE :
			        EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOPROTOOPT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_ARGUMENT_SOCKET_OPT@)):
			result = ENOPROTOOPT;
			break;
@@pp_endif@@
@@pp_if defined(EAFNOSUPPORT) && defined(EINVAL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_INVALID_ARGUMENT_UNEXPECTED_COMMAND@)):
			result = self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY@ ? EAFNOSUPPORT : EINVAL;
			break;
@@pp_endif@@
		default: break;
		}
		break;

	case @E_NET_ERROR@:
		switch(self->@e_subclass@) {
@@pp_if defined(EHOSTUNREACH)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_HOST_UNREACHABLE@)):
			result = EHOSTUNREACH;
			break;
@@pp_endif@@
@@pp_if defined(EADDRINUSE)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_ADDRESS_IN_USE@)):
			result = EADDRINUSE;
			break;
@@pp_endif@@
@@pp_if defined(EMSGSIZE)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_MESSAGE_TOO_LONG@)):
			result = EMSGSIZE;
			break;
@@pp_endif@@
@@pp_if defined(ECONNABORTED)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_CONNECTION_ABORT@)):
			result = ECONNABORTED;
			break;
@@pp_endif@@
@@pp_if defined(ECONNREFUSED)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_CONNECTION_REFUSED@)):
			result = ECONNREFUSED;
			break;
@@pp_endif@@
@@pp_if defined(ECONNRESET)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_CONNECTION_RESET@)):
			result = ECONNRESET;
			break;
@@pp_endif@@
@@pp_if defined(ETIMEDOUT)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_TIMEOUT@)):
			result = ETIMEDOUT;
			break;
@@pp_endif@@
@@pp_if defined(ENETUNREACH)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_UNREACHABLE@)):
			result = ENETUNREACH;
			break;
@@pp_endif@@
@@pp_if defined(EADDRNOTAVAIL)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_ADDRESS_NOT_AVAILABLE@)):
			result = EADDRNOTAVAIL;
			break;
@@pp_endif@@
@@pp_if defined(EPIPE)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_NET_SHUTDOWN@)):
			result = EPIPE;
			break;
@@pp_endif@@
		default: break;
		}
		break;
/*[[[end]]]*/
	default:
		break;
	}
	return result;
}


%struct __siginfo_struct;
@@Transform the given exception into a posix signal.
@@If doing this is possible, fill in `*result' and return `true'.
@@Otherwise, `*result' is left in an undefined state, and `false' is returned.
[[wunused, kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[decl_prefix(struct exception_data;)]]
[[decl_prefix(struct __siginfo_struct;)]]
[[impl_include("<asm/siginfo.h>")]]
[[impl_include("<asm/os/signal.h>")]]
[[impl_include("<bits/siginfo-struct.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/kernel/handle.h>")]]
$bool error_as_signal([[nonnull]] struct exception_data const *__restrict self,
                      [[nonnull]] struct __siginfo_struct *__restrict result) {
	error_code_t code = self->@e_code@;
	bzero(result, sizeof(*result));
	/* TODO: Make sure that this matches the sysv abi386 requirements:
	 *       Figure 3-27:  Hardware Exceptions and Signals
	 *       0   divide error fault             SIGFPE
	 *       1   single step trap/fault         SIGTRAP
	 *       2   nonmaskable interrupt          none
	 *       3   breakpoint trap                SIGTRAP
	 *       4   overflow trap                  SIGSEGV
	 *       5   bounds check fault             SIGSEGV
	 *       6   invalid opcode fault           SIGILL
	 *       7   no coprocessor fault           SIGFPE
	 *       8   double fault abort             none
	 *       9   coprocessor overrun abort      SIGSEGV
	 *       10  invalid TSS fault              none
	 *       11  segment not present fault      none
	 *       12  stack exception fault          SIGSEGV
	 *       13  general protection fault/abort SIGSEGV
	 *       14  page fault                     SIGSEGV
	 *       15 (reserved)
	 *       16 coprocessor error fault         SIGFPE
	 *       other (unspecified)                SIGILL */
	switch (@ERROR_CLASS@(code)) {

@@pp_ifdef SIGQUIT@@
	case @E_EXIT_THREAD@:
	case @E_EXIT_PROCESS@:
		result->@si_signo@ = SIGQUIT;
		break;
@@pp_endif@@

@@pp_if defined(SIGBUS) && defined(BUS_OBJERR)@@
	case @E_IOERROR@:
		result->@si_signo@ = SIGBUS;
		result->@si_code@  = BUS_OBJERR;
		break;
@@pp_endif@@

@@pp_ifdef SIGSYS@@
	case @E_UNKNOWN_SYSTEMCALL@:
		result->@si_signo@   = SIGSYS;
		result->@si_syscall@ = self->@e_args@.@e_unknown_systemcall@.@us_sysno@;
		/* TODO: `si_arch' could be determined by
		 *       `self->e_args.e_unknown_systemcall.us_flags & RPC_SYSCALL_INFO_FMETHOD'! */
		break;
@@pp_endif@@

@@pp_if defined(SIGFPE) && defined(FPE_INTDIV)@@
	case @E_DIVIDE_BY_ZERO@:
		result->@si_signo@ = SIGFPE;
		result->@si_code@  = FPE_INTDIV;
		break;
@@pp_endif@@

@@pp_if defined(SIGFPE) && defined(FPE_INTOVF)@@
	case @E_OVERFLOW@:
		result->@si_signo@ = SIGFPE;
		result->@si_code@  = FPE_INTOVF;
		break;
@@pp_endif@@

@@pp_if defined(SIGTRAP) && defined(TRAP_BRKPT)@@
	case @E_BREAKPOINT@:
		result->@si_signo@ = SIGTRAP;
		result->@si_code@  = TRAP_BRKPT;
		break;
@@pp_endif@@

@@pp_if defined(SIGINT)@@
	case @E_INTERRUPT@:
		result->@si_signo@ = SIGINT;
		break;
@@pp_endif@@

@@pp_if defined(SIGFPE) && defined(FPE_FLTSUB)@@
	case @E_INDEX_ERROR@:
		result->@si_signo@ = SIGFPE;
		result->@si_code@  = FPE_FLTSUB;
		break;
@@pp_endif@@

@@pp_if defined(SIGSEGV) && defined(SEGV_MAPERR)@@
	case @E_SEGFAULT@:
	case @E_STACK_OVERFLOW@:
		result->@si_signo@ = SIGSEGV;
		result->@si_code@  = SEGV_MAPERR;
		switch (code) {

@@pp_if defined(SEGV_ACCERR)@@
		case @ERROR_CODEOF@(@E_SEGFAULT_READONLY@):
		case @ERROR_CODEOF@(@E_SEGFAULT_NOTREADABLE@):
		case @ERROR_CODEOF@(@E_SEGFAULT_NOTEXECUTABLE@):
			result->@si_code@ = SEGV_ACCERR;
			break;
@@pp_endif@@

@@pp_if defined(SIGBUS) && defined(BUS_OBJERR)@@
		case @ERROR_CODEOF@(@E_SEGFAULT_NOTATOMIC@):
			result->@si_signo@ = SIGBUS;
			result->@si_code@  = BUS_OBJERR;
			break;
@@pp_endif@@

@@pp_if defined(SIGBUS) && defined(BUS_ADRALN)@@
		case @ERROR_CODEOF@(@E_SEGFAULT_UNALIGNED@):
			result->@si_signo@ = SIGBUS;
			result->@si_code@  = BUS_ADRALN;
			break;
@@pp_endif@@

		default: break;
		}
		result->@si_addr@  = (void *)self->@e_args@.@e_segfault@.@s_addr@;
		result->@si_lower@ = result->@si_addr@;
		result->@si_upper@ = result->@si_addr@;
		break;
@@pp_endif@@

@@pp_if defined(SIGILL)@@
	case @E_ILLEGAL_INSTRUCTION@:
		result->@si_signo@ = SIGILL;
		switch (code) {

@@pp_if defined(ILL_ILLOPN)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_BAD_OPERAND@):
			result->@si_code@ = ILL_ILLOPN;
@@pp_if defined(ILL_ILLADR)@@
			if (self->@e_args@.@e_illegal_instruction@.@ii_bad_operand@.@bo_what@ == @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY@ ||
			    self->@e_args@.@e_illegal_instruction@.@ii_bad_operand@.@bo_what@ == @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER@)
				result->@si_code@ = ILL_ILLADR;
@@pp_endif@@
			break;
@@pp_endif@@

@@pp_if defined(ILL_PRVOPC)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE@):
			result->@si_code@ = ILL_PRVOPC;
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLOPN)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_REGISTER@):
			result->@si_code@ = ILL_ILLOPN;
@@pp_if defined(ILL_PRVREG)@@
			if (self->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ == @E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV@ ||
			    self->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ == @E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV@)
				result->@si_code@ = ILL_PRVREG;
@@pp_endif@@
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLADR) && defined(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@):
			result->@si_code@ = ILL_ILLADR;
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLOPC)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_BAD_OPCODE@):
@@pp_if defined(@E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX@)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX@):
@@pp_endif@@
@@pp_if defined(@E_ILLEGAL_INSTRUCTION_X86_TOO_LONG@)@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_TOO_LONG@):
@@pp_endif@@
		case @ERROR_CODEOF@(@E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE@):
			result->@si_code@ = ILL_ILLOPC;
			break;
@@pp_endif@@

		default:
			break;
		}
		break;
@@pp_endif@@

	default:
		return false;
	}
	result->@si_errno@ = error_as_errno(self);
	return true;
}




%#ifdef __USE_KOS_KERNEL
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_info)),
  preferred_fast_extern_inline("error_info", { return __arch_error_info(); })]]
[[wunused, const, nonnull, decl_prefix(struct exception_info;)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_info))]]
struct exception_info *error_info(void) {
	return __arch_error_info();
}

%{
#ifndef __ERROR_UNWIND_CC
#define __ERROR_UNWIND_CC __LIBKCALL
#endif /* !__ERROR_UNWIND_CC */
}

@@Unwind the given register state to propagate the currently set error.
@@Following this, the returned register state should then be loaded.
[[kernel, no_crt_dos_wrapper, cc(__ERROR_UNWIND_CC)]]
[[wunused, nonnull, decl_include("<kos/bits/except.h>")]]
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
}
%#endif /* __CC__ */
%{

}