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
%[default:section(".text.crt{|.dos}.except.io.utility")]

%(auto_source){
#include <errno.h>
#include <signal.h>
}

%(auto_header){
/* Make use of inline optimizations when possible! */
#ifndef __INTELLISENSE__
#ifdef __arch_error_data
#define libc_error_data() __arch_error_data()
#endif /* __arch_error_data */
#ifdef __arch_error_code
#define libc_error_code() __arch_error_code()
#endif /* __arch_error_code */
#ifdef __arch_error_active
#define libc_error_active() __arch_error_active()
#endif /* __arch_error_active */
#ifdef __arch_error_class
#define libc_error_class() __arch_error_class()
#endif /* __arch_error_class */
#ifdef __arch_error_subclass
#define libc_error_subclass() __arch_error_subclass()
#endif /* __arch_error_subclass */
#ifdef __arch_error_register_state
#define libc_error_register_state() __arch_error_register_state()
#endif /* __arch_error_register_state */
#ifdef __arch_error_info
#define libc_error_info() __arch_error_info()
#endif /* __arch_error_info */
#endif /* !__INTELLISENSE__ */
}


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/pp/__va_nargs.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <kos/bits/except.h>         /* __ERROR_REGISTER_STATE_TYPE */
)]%[insert:prefix(
#include <kos/bits/exception_data.h> /* struct exception_data */
)]%[insert:prefix(
#include <kos/bits/exception_nest.h> /* struct _exception_nesting_data */
)]%[insert:prefix(
#include <kos/except/codes.h>        /* E_OK, ... */
)]%[insert:prefix(
#include <kos/bits/fastexcept.h>
)]%{

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

}
%#ifdef __CC__
%{
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
#define __error_register_state_t_defined 1
typedef __ERROR_REGISTER_STATE_TYPE error_register_state_t;
#endif /* !__error_register_state_t_defined */

typedef __error_code_t error_code_t;
typedef __error_class_t error_class_t;
typedef __error_subclass_t error_subclass_t;

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
[[wunused, const, nothrow, nonnull, decl_prefix(struct exception_data;)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>"), requires(defined(__arch_error_data))]]
struct exception_data *error_data(void) {
	return __arch_error_data();
}

[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_code)),
  preferred_fast_extern_inline("error_code", { return __arch_error_code(); })]]
[[wunused, pure, nothrow, decl_include("<kos/bits/exception_data.h>")]]
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
[[wunused, pure, nothrow, userimpl, requires_function(error_code)]]
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
[[wunused, pure, nothrow, decl_include("<kos/bits/exception_data.h>")]]
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
[[wunused, pure, nothrow, decl_include("<kos/bits/exception_data.h>")]]
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
[[wunused, const, nothrow, nonnull, decl_include("<kos/bits/except.h>")]]
[[decl_prefix(
#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/os/mcontext.h>
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
[[impl_include("<hybrid/host.h>")]]
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

local classes = parseExceptionClasses();
for (local name: classes.keys.sorted()) {
	local ppCondToCls = classes[name];
	for (local ppCond: ppCondToCls.keys.sorted()) {
		local cls = ppCondToCls[ppCond];
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

@@pp_if defined(EINVAL)@@
	case @E_BREAKPOINT@:
		result = EINVAL;
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

	case @E_ILLEGAL_OPERATION@:
		switch(self->@e_subclass@) {
@@pp_if defined(ELOOP)@@
		case @ERROR_SUBCLASS@(@ERROR_CODEOF@(@E_ILLEGAL_REFERENCE_LOOP@)):
			result = ELOOP;
			break;
@@pp_endif@@
		default: break;
		}
		break;

@@pp_if defined(ERANGE)@@
	case @E_INDEX_ERROR@:
		result = ERANGE;
		break;
@@pp_endif@@

@@pp_if defined(EACCES)@@
	case @E_INSUFFICIENT_RIGHTS@:
		result = EACCES;
		break;
@@pp_endif@@

@@pp_if defined(EINTR)@@
	case @E_INTERRUPT@:
		result = EINTR;
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

@@pp_if defined(EPERM)@@
	case @E_INVALID_CONTEXT@:
		result = EPERM;
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

@@pp_if defined(EIO)@@
	case @E_IOERROR@:
		result = EIO;
		break;
@@pp_endif@@

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

@@pp_if defined(ENOEXEC)@@
	case @E_NOT_EXECUTABLE@:
		result = ENOEXEC;
		break;
@@pp_endif@@

@@pp_if defined(ENOSYS)@@
	case @E_NOT_IMPLEMENTED@:
		result = ENOSYS;
		break;
@@pp_endif@@

@@pp_if defined(ENODEV)@@
	case @E_NO_DEVICE@:
		result = ENODEV;
		break;
@@pp_endif@@

@@pp_if defined(ENODATA)@@
	case @E_NO_SUCH_OBJECT@:
		result = ENODATA;
		break;
@@pp_endif@@

@@pp_if defined(EOK)@@
	case @E_OK@:
		result = EOK;
		break;
@@pp_endif@@

@@pp_if defined(EOVERFLOW)@@
	case @E_OVERFLOW@:
		result = EOVERFLOW;
		break;
@@pp_endif@@

@@pp_if defined(ESRCH)@@
	case @E_PROCESS_EXITED@:
		result = ESRCH;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_SEGFAULT@:
		result = EFAULT;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_STACK_OVERFLOW@:
		result = EFAULT;
		break;
@@pp_endif@@

@@pp_if defined(EFAULT)@@
	case @E_UNHANDLED_INTERRUPT@:
		result = EFAULT;
		break;
@@pp_endif@@

@@pp_if defined(EILSEQ)@@
	case @E_UNICODE_ERROR@:
		result = EILSEQ;
		break;
@@pp_endif@@

@@pp_if defined(ENOSYS)@@
	case @E_UNKNOWN_SYSTEMCALL@:
		result = ENOSYS;
		break;
@@pp_endif@@

@@pp_if defined(EAGAIN)@@
	case @E_WOULDBLOCK@:
		result = EAGAIN;
		break;
@@pp_endif@@
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
[[impl_include("<hybrid/host.h>")]]
[[impl_include("<asm/os/siginfo.h>")]]
[[impl_include("<asm/os/signal.h>")]]
[[impl_include("<bits/os/siginfo.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/kernel/handle.h>")]]
$bool error_as_signal([[nonnull]] struct exception_data const *__restrict self,
                      [[nonnull]] struct __siginfo_struct *__restrict result) {
	error_code_t code = self->@e_code@;
	bzero(result, sizeof(*result));
	/* TODO: Make sure that this matches the sysv abi386 requirements:
	 *       Figure    3-27:    Hardware   Exceptions    and   Signals
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



@@Return the name of the given error, or `NULL` if unknown.
@@This name is the same as the `E_*` identifier.
@@E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))` -> "E_BADALLOC"
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, const, nothrow, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<hybrid/host.h>", "<kos/except/codes.h>")]]
char const *error_name(error_code_t code) {
	error_class_t err_class       = @ERROR_CLASS@(code);
	error_subclass_t err_subclass = @ERROR_SUBCLASS@(code);
/*[[[deemon
(printExceptNameFunctionBody from ....misc.libgen.exceptinfo)(
	classVariableName:    "err_class",
	subClassVariableName: "err_subclass");
]]]*/
#if !defined(__i386__) && !defined(__x86_64__)
	static char const e_linear_0000h_000ah[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_ADDRESS_ALREADY_EXISTS\0E_"
	"BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY\0E_BADALLOC_INSUFFICIENT_SW"
	"AP_SPACE\0E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS\0E_BADALLOC_INSUF"
	"FICIENT_HANDLE_RANGE\0E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS\0E_BA"
	"DALLOC_INSUFFICIENT_INTERRUPT_VECTORS\0E_BADALLOC_INSUFFICIENT_PO"
	"RT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_FLAG\0E"
	"_INVALID_ARGUMENT_RESERVED_FLAG\0E_INVALID_ARGUMENT_BAD_FLAG_COMB"
	"INATION\0E_INVALID_ARGUMENT_BAD_FLAG_MASK\0E_INVALID_ARGUMENT_BAD_"
	"ALIGNMENT\0E_INVALID_ARGUMENT_BAD_VALUE\0E_INVALID_ARGUMENT_RESERV"
	"ED_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_COMMAND\0E_INVALID_ARGUMEN"
	"T_BAD_STATE\0E_INVALID_ARGUMENT_SOCKET_OPT\0E_INVALID_ARGUMENT_UNE"
	"XPECTED_COMMAND\0\1E_NOT_IMPLEMENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED"
	"\0E_NOT_IMPLEMENTED_TODO\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0"
	"E_INVALID_HANDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_H"
	"ANDLE_NET_OPERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULD"
	"BLOCK_WAITFORSIGNAL\0\1E_PROCESS_EXITED\0\1E_NO_DEVICE\0\1E_UNKNOWN_SY"
	"STEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_SUCH_BLOCKDEVICE\0E_NO_SUCH_PROCE"
	"SS\0E_NO_SUCH_PIDNS\0E_NO_CTTY\0\1E_ILLEGAL_OPERATION\0E_ILLEGAL_PROC"
	"ESS_OPERATION\0E_ILLEGAL_REFERENCE_LOOP\0\1";
	static char const e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1E_INVALID_CONTEXT\0E_INVALID_CONTEXT_NOT_SESSIO"
	"N_LEADER\0E_INVALID_CONTEXT_CTTY_ALREADY_ASSIGNED\0E_INVALID_CONTE"
	"XT_CTTY_DIFFERS\0\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0\1E_UNICODE_ERROR\0\1";
	static char const e_linear_f000h_f001h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1__E_RETRY_RWLOCK\0\1";
	static char const e_linear_fe00h_fe01h[] =
	"E_EXIT_THREAD\0\1E_EXIT_PROCESS\0\1";
	static char const e_linear_feffh_ff07h[] =
	"E_UNHANDLED_INTERRUPT\0\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAUL"
	"T_READONLY\0E_SEGFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEG"
	"FAULT_NOTATOMIC\0E_SEGFAULT_UNALIGNED\0\1E_BREAKPOINT\0\1E_DIVIDE_BY_"
	"ZERO\0\1E_OVERFLOW\0\1E_ILLEGAL_INSTRUCTION\0E_ILLEGAL_INSTRUCTION_BA"
	"D_OPCODE\0E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE\0E_ILLEGAL_INST"
	"RUCTION_PRIVILEGED_OPCODE\0E_ILLEGAL_INSTRUCTION_BAD_OPERAND\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0E_ILLEGAL_INSTRUCTION_REGISTER\0\1E_STACK_OVERFLOW\0\1E_INDE"
	"X_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1";
	char const *result;
	error_class_t class_offset;
	error_subclass_t subclass_offset;
	if (err_class <= 0x000a) {
		result = e_linear_0000h_000ah;
		class_offset = err_class;
	} else if (err_class >= 0x0081 && err_class <= 0x0091) {
		result = e_linear_0081h_0091h;
		class_offset = err_class - 0x0081;
	} else if (err_class >= 0xf000 && err_class <= 0xf001) {
		result = e_linear_f000h_f001h;
		class_offset = err_class - 0xf000;
	} else if (err_class >= 0xfe00 && err_class <= 0xfe01) {
		result = e_linear_fe00h_fe01h;
		class_offset = err_class - 0xfe00;
	} else if (err_class >= 0xfeff && err_class <= 0xff07) {
		result = e_linear_feffh_ff07h;
		class_offset = err_class - 0xfeff;
	} else {
		goto non_linear_prefix;
	}
	while (class_offset) {
		--class_offset;
		result = (char *)rawmemchr(result, '\1') + 1;
	}
	subclass_offset = err_subclass;
	for (;;) {
		if (*result == '\1')
			break; /* End-of-class */
		if (!subclass_offset) {
			if (!*result)
				result = NULL;
			return result;
		}
		--subclass_offset;
		result = strend(result) + 1;
	}
non_linear_prefix:
	switch(err_class) {

	case 0x0080: {
		static char const e_0080h_linear_0000h_001ah[] =
		"E_FSERROR\0E_FSERROR_DELETED\0E_FSERROR_FILE_NOT_FOUND\0E_FSERROR_P"
		"ATH_NOT_FOUND\0E_FSERROR_ILLEGAL_PATH\0E_FSERROR_NOT_A_DIRECTORY\0E"
		"_FSERROR_TOO_MANY_SYMBOLIC_LINKS\0E_FSERROR_ACCESS_DENIED\0E_FSERR"
		"OR_DISK_FULL\0E_FSERROR_READONLY\0E_FSERROR_TOO_MANY_HARD_LINKS\0E_"
		"FSERROR_IS_A_DIRECTORY\0E_FSERROR_NOT_A_SYMBOLIC_LINK\0E_FSERROR_I"
		"S_A_SYMBOLIC_LINK\0E_FSERROR_FILE_ALREADY_EXISTS\0E_FSERROR_DIRECT"
		"ORY_NOT_EMPTY\0E_FSERROR_CROSS_DEVICE_LINK\0E_FSERROR_DIRECTORY_MO"
		"VE_TO_CHILD\0E_FSERROR_NOT_A_BLOCK_DEVICE\0E_FSERROR_NO_BLOCK_DEVI"
		"CE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_SYSTEM\0E_F"
		"SERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_DEVICE_ALREADY_MOUNTED\0E_"
		"FSERROR_PATH_ALREADY_MOUNTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FS"
		"ERROR_IS_A_MOUNTING_POINT";
		static char const e_0080h_linear_0100h_0100h[] =
		"E_FSERROR_UNSUPPORTED_OPERATION";
		if (err_subclass <= 0x001a) {
			result = e_0080h_linear_0000h_001ah;
			subclass_offset = err_subclass;
		} else if (err_subclass >= 0x0100 && err_subclass <= 0x0100) {
			result = e_0080h_linear_0100h_0100h;
			subclass_offset = err_subclass - 0x0100;
		} else {
			return NULL;
		}
	}	break;

	default:
		return NULL;
	}
	while (subclass_offset) {
		--subclass_offset;
		result = strend(result) + 1;
	}
	if (!*result)
		result = NULL;
	return result;
#else /* ... */
	static char const e_linear_0000h_000ah[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_ADDRESS_ALREADY_EXISTS\0E_"
	"BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY\0E_BADALLOC_INSUFFICIENT_SW"
	"AP_SPACE\0E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS\0E_BADALLOC_INSUF"
	"FICIENT_HANDLE_RANGE\0E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS\0E_BA"
	"DALLOC_INSUFFICIENT_INTERRUPT_VECTORS\0E_BADALLOC_INSUFFICIENT_PO"
	"RT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_FLAG\0E"
	"_INVALID_ARGUMENT_RESERVED_FLAG\0E_INVALID_ARGUMENT_BAD_FLAG_COMB"
	"INATION\0E_INVALID_ARGUMENT_BAD_FLAG_MASK\0E_INVALID_ARGUMENT_BAD_"
	"ALIGNMENT\0E_INVALID_ARGUMENT_BAD_VALUE\0E_INVALID_ARGUMENT_RESERV"
	"ED_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_COMMAND\0E_INVALID_ARGUMEN"
	"T_BAD_STATE\0E_INVALID_ARGUMENT_SOCKET_OPT\0E_INVALID_ARGUMENT_UNE"
	"XPECTED_COMMAND\0\1E_NOT_IMPLEMENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED"
	"\0E_NOT_IMPLEMENTED_TODO\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0"
	"E_INVALID_HANDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_H"
	"ANDLE_NET_OPERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULD"
	"BLOCK_WAITFORSIGNAL\0\1E_PROCESS_EXITED\0\1E_NO_DEVICE\0\1E_UNKNOWN_SY"
	"STEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_SUCH_BLOCKDEVICE\0E_NO_SUCH_PROCE"
	"SS\0E_NO_SUCH_PIDNS\0E_NO_CTTY\0\1E_ILLEGAL_OPERATION\0E_ILLEGAL_PROC"
	"ESS_OPERATION\0E_ILLEGAL_REFERENCE_LOOP\0\1";
	static char const e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1E_INVALID_CONTEXT\0E_INVALID_CONTEXT_NOT_SESSIO"
	"N_LEADER\0E_INVALID_CONTEXT_CTTY_ALREADY_ASSIGNED\0E_INVALID_CONTE"
	"XT_CTTY_DIFFERS\0\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0\1E_UNICODE_ERROR\0\1";
	static char const e_linear_f000h_f001h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1__E_RETRY_RWLOCK\0\1";
	static char const e_linear_fe00h_fe01h[] =
	"E_EXIT_THREAD\0\1E_EXIT_PROCESS\0\1";
	static char const e_linear_feffh_ff0eh[] =
	"E_UNHANDLED_INTERRUPT\0\1E_DIVIDE_BY_ZERO\0\1\1\1E_BREAKPOINT\0\1E_OVERF"
	"LOW\0\1E_INDEX_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1\1\1E_STACK_OVERFL"
	"OW\0\1\1\1\1\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAULT_READONLY\0E_SE"
	"GFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEGFAULT_NOTATOMIC"
	"\0E_SEGFAULT_UNALIGNED\0\1";
	char const *result;
	error_class_t class_offset;
	error_subclass_t subclass_offset;
	if (err_class <= 0x000a) {
		result = e_linear_0000h_000ah;
		class_offset = err_class;
	} else if (err_class >= 0x0081 && err_class <= 0x0091) {
		result = e_linear_0081h_0091h;
		class_offset = err_class - 0x0081;
	} else if (err_class >= 0xf000 && err_class <= 0xf001) {
		result = e_linear_f000h_f001h;
		class_offset = err_class - 0xf000;
	} else if (err_class >= 0xfe00 && err_class <= 0xfe01) {
		result = e_linear_fe00h_fe01h;
		class_offset = err_class - 0xfe00;
	} else if (err_class >= 0xfeff && err_class <= 0xff0e) {
		result = e_linear_feffh_ff0eh;
		class_offset = err_class - 0xfeff;
	} else {
		goto non_linear_prefix;
	}
	while (class_offset) {
		--class_offset;
		result = (char *)rawmemchr(result, '\1') + 1;
	}
	subclass_offset = err_subclass;
	for (;;) {
		if (*result == '\1')
			break; /* End-of-class */
		if (!subclass_offset) {
			if (!*result)
				result = NULL;
			return result;
		}
		--subclass_offset;
		result = strend(result) + 1;
	}
non_linear_prefix:
	switch(err_class) {

	case 0x0080: {
		static char const e_0080h_linear_0000h_001ah[] =
		"E_FSERROR\0E_FSERROR_DELETED\0E_FSERROR_FILE_NOT_FOUND\0E_FSERROR_P"
		"ATH_NOT_FOUND\0E_FSERROR_ILLEGAL_PATH\0E_FSERROR_NOT_A_DIRECTORY\0E"
		"_FSERROR_TOO_MANY_SYMBOLIC_LINKS\0E_FSERROR_ACCESS_DENIED\0E_FSERR"
		"OR_DISK_FULL\0E_FSERROR_READONLY\0E_FSERROR_TOO_MANY_HARD_LINKS\0E_"
		"FSERROR_IS_A_DIRECTORY\0E_FSERROR_NOT_A_SYMBOLIC_LINK\0E_FSERROR_I"
		"S_A_SYMBOLIC_LINK\0E_FSERROR_FILE_ALREADY_EXISTS\0E_FSERROR_DIRECT"
		"ORY_NOT_EMPTY\0E_FSERROR_CROSS_DEVICE_LINK\0E_FSERROR_DIRECTORY_MO"
		"VE_TO_CHILD\0E_FSERROR_NOT_A_BLOCK_DEVICE\0E_FSERROR_NO_BLOCK_DEVI"
		"CE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_SYSTEM\0E_F"
		"SERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_DEVICE_ALREADY_MOUNTED\0E_"
		"FSERROR_PATH_ALREADY_MOUNTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FS"
		"ERROR_IS_A_MOUNTING_POINT";
		static char const e_0080h_linear_0100h_0100h[] =
		"E_FSERROR_UNSUPPORTED_OPERATION";
		if (err_subclass <= 0x001a) {
			result = e_0080h_linear_0000h_001ah;
			subclass_offset = err_subclass;
		} else if (err_subclass >= 0x0100 && err_subclass <= 0x0100) {
			result = e_0080h_linear_0100h_0100h;
			subclass_offset = err_subclass - 0x0100;
		} else {
			return NULL;
		}
	}	break;

	case 0xff06: {
		static char const e_ff06h_linear_0000h_0011h[] =
		"E_ILLEGAL_INSTRUCTION\0E_ILLEGAL_INSTRUCTION_BAD_OPCODE\0E_ILLEGAL"
		"_INSTRUCTION_UNSUPPORTED_OPCODE\0E_ILLEGAL_INSTRUCTION_PRIVILEGED"
		"_OPCODE\0E_ILLEGAL_INSTRUCTION_BAD_OPERAND\0\0\0\0\0\0\0\0\0\0\0\0\0E_ILLEGAL_"
		"INSTRUCTION_REGISTER";
		static char const e_ff06h_linear_8601h_8603h[] =
		"E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX\0E_ILLEGAL_INSTRUCTION_X86_T"
		"OO_LONG\0E_ILLEGAL_INSTRUCTION_X86_INTERRUPT";
		if (err_subclass <= 0x0011) {
			result = e_ff06h_linear_0000h_0011h;
			subclass_offset = err_subclass;
		} else if (err_subclass >= 0x8601 && err_subclass <= 0x8603) {
			result = e_ff06h_linear_8601h_8603h;
			subclass_offset = err_subclass - 0x8601;
		} else {
			return NULL;
		}
	}	break;

	default:
		return NULL;
	}
	while (subclass_offset) {
		--subclass_offset;
		result = strend(result) + 1;
	}
	if (!*result)
		result = NULL;
	return result;
#endif /* !... */
/*[[[end]]]*/
}



@@Return the priority for a given error code, where exceptions
@@with greater priorities should take the place of ones with
@@lower priorities in situations where multiple simultaneous
@@errors can't be prevented.
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[wunused, const, nothrow]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[decl_include("<kos/bits/exception_data.h>")]]
unsigned int error_priority(error_code_t code) {
	error_class_t code_class = @ERROR_CLASS@(code);
	if (@ERRORCLASS_ISRTLPRIORITY@(code_class))
		return 4 + (code_class - @ERRORCLASS_RTL_MIN@);
	if (@ERRORCLASS_ISHIGHPRIORITY@(code_class))
		return 3;
	if (!@ERRORCLASS_ISLOWPRIORITY@(code_class))
		return 2;
	if (code_class != @ERROR_CLASS@(@ERROR_CODEOF@(@E_OK@)))
		return 1;
	return 0;
}




%#ifdef __USE_KOS_KERNEL
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_error_info)),
  preferred_fast_extern_inline("error_info", { return __arch_error_info(); })]]
[[wunused, const, nothrow, nonnull, decl_prefix(struct exception_info;)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_error_info))]]
struct exception_info *error_info(void) {
	return __arch_error_info();
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
#include <bits/os/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */
)]]
error_register_state_t *error_unwind([[nonnull]] error_register_state_t *__restrict state);

%#endif /* __USE_KOS_KERNEL */


@@Throw the currently set (in `error_data()') exception.
[[noreturn, cold, throws]]
[[kernel, no_crt_dos_wrapper, cc(LIBKCALL)]]
void error_throw_current(void);

@@Rethrow the current exception (same as a c++ `throw;' expression)
[[guard, noreturn, cold, throws]]
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
}
%#else /* __INTELLISENSE__ */
%{

#ifndef THROW
}


@@Throw an exception and fill exception pointers with all zeroes
[[guard, decl_prefix(
#ifndef __ERROR_THROW_CC
#define __ERROR_THROW_CC __LIBKCALL
#endif /* !__ERROR_THROW_CC */
)]]
[[noreturn, cold, throws]]
[[kernel, no_crt_dos_wrapper, cc(__ERROR_THROW_CC)]]
void error_throw(error_code_t code);

@@Throw an exception and load `argc' pointers from varargs
[[guard, decl_prefix(
#ifndef __ERROR_THROWN_CC
#define __ERROR_THROWN_CC __LIBKCALL
#endif /* !__ERROR_THROWN_CC */
)]]
[[noreturn, cold, throws]]
[[kernel, no_crt_dos_wrapper, cc(__ERROR_THROWN_CC)]]
void error_thrown(error_code_t code, unsigned int _argc, ...);


%{
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
}

%#endif /* !__INTELLISENSE__ */

@@Begin a nested TRY-block. (i.e. inside of another EXCEPT block)
[[guard, no_local, decl_prefix(
#ifndef __ERROR_NESTING_BEGIN_CC
#define __ERROR_NESTING_BEGIN_CC __LIBKCALL
#endif /* !__ERROR_NESTING_BEGIN_CC */
), nothrow, kernel, no_crt_dos_wrapper, cc(__ERROR_NESTING_BEGIN_CC)]]
[[decl_include("<kos/bits/exception_info.h>", "<bits/types.h>")]]
void error_nesting_begin([[nonnull]] struct _exception_nesting_data *__restrict saved) {
	struct exception_info *info = error_info();
	if (!(info->@ei_flags@ & @EXCEPT_FINCATCH@)) {
		/* Not inside of a  catch-block (ignore the nesting  request)
		 * This can happen if the caller  is only using the nest  for
		 * safety  (in case a sub-function needs to be able to handle
		 * its own  exceptions, but  may be  called from  an  unaware
		 * exception handler),  or  is  using  more  than  one  nest.
		 * In all of these cases, just ignore the nest, and also make
		 * it so that the associated `error_nesting_end()' is a no-op */
		saved->@en_size@ = 0;
	} else {
		__hybrid_assertf(info->@ei_code@ != @ERROR_CODEOF@(@E_OK@),
		                 "No exception set in `error_nesting_begin()'");
		if unlikely(saved->@en_size@ > @_EXCEPTION_NESTING_DATA_SIZE@)
			saved->@en_size@ = @_EXCEPTION_NESTING_DATA_SIZE@;
		memcpy(&saved->@en_state@, info, saved->@en_size@);
		info->@ei_flags@ &= ~@EXCEPT_FINCATCH@;
		info->@ei_code@   = @ERROR_CODEOF@(@E_OK@);
		++info->@ei_nesting@;
	}
}

@@End a nested TRY-block. (i.e. inside of another EXCEPT block)
[[guard, no_local, decl_prefix(
#ifndef __ERROR_NESTING_END_CC
#define __ERROR_NESTING_END_CC __LIBKCALL
#endif /* !__ERROR_NESTING_END_CC */
), nothrow, kernel, no_crt_dos_wrapper, cc(__ERROR_NESTING_END_CC)]]
[[decl_include("<kos/bits/exception_info.h>")]]
[[impl_include("<hybrid/__assert.h>")]]
void error_nesting_end([[nonnull]] struct _exception_nesting_data *__restrict saved) {
	struct exception_info *info;
	if unlikely(!saved->@en_size@)
		return; /* No-op */
	info = error_info();
	__hybrid_assertf(info->@ei_nesting@ != 0,
	                 "Error-nesting stack is empty");
	--info->@ei_nesting@;
	__hybrid_assertf(!(info->@ei_flags@ & @EXCEPT_FINCATCH@),
	                 "This flag should have been cleared by `error_nesting_begin()'");
	__hybrid_assertf(saved->@en_data@.@e_code@ != @ERROR_CODEOF@(@E_OK@),
	                 "No saved exception in `error_nesting_end()'");
	if (info->@ei_code@ == @ERROR_CODEOF@(@E_OK@)) {
		/* No newly thrown exception. (meaning we're currently not propagating
		 * any exceptions, so we also shouldn't try to set the RETHROW  flag!) */
restore_saved_exception:
		memcpy(info, &saved->@en_state@, saved->@en_size@);
	} else {
		/* An Exception  is currently  being handled,  and we  must prevent  that
		 * exception from being deleted by an outer `__cxa_end_catch()'. Therefor
		 * we  must  set  the RETHROW  flag  to essentially  re-throw  the merged
		 * exception from outside of the inner try-block:
		 * [ 1] TRY {
		 * [ 2]     foo();
		 * [ 3] } EXCEPT {
		 * [ 4]     NESTED_TRY {
		 * [ 5]         bar();
		 * [ 6]     } EXCEPT {
		 * [ 7]         foobar();
		 * [ 8]         RETHROW();
		 * [ 9]     }
		 * [10]     RETHROW();
		 * [11] }
		 *
		 * Equivalent:
		 * [ 1] foo();                                // [ 2]
		 * [ 2] if (EXCEPTION_THROWN) {
		 * [ 3]     __cxa_begin_catch();              // [ 3]
		 * [ 4]     struct _exception_nesting_data nest;
		 * [ 5]     error_nesting_begin(&nest);
		 * [ 6]     bar();                            // [ 5]
		 * [ 7]     if (EXCEPTION_THROWN) {
		 * [ 8]         __cxa_begin_catch();          // [ 6]
		 * [ 9]         foobar();                     // [ 7]
		 * [10]         error_rethrow();              // [ 8]
		 * [11]         __cxa_end_catch();            // [ 9]
		 * [12]         error_nesting_end(&nest);
		 * [13]     } else {
		 * [14]         error_nesting_end(&nest);
		 * [15]         error_rethrow();              // [10]
		 * [16]     }
		 * [17]     __cxa_end_catch();                // [11]
		 * [18] }
		 *
		 * We  get  here  from  EQ[12],  which  is  followed  by  EQ[17], which
		 * would normally  delete the  exception  because it  wasn't  re-thrown
		 * from anywhere. But if you think of all of the possible constellation
		 * where this function  might be  called, in  all cases  where we  know
		 * that there's currently an active  exception (i.e. ei_code !=  E_OK),
		 * it's always  acceptable  to  set  the RETHROW  flag  for  the  outer
		 * call to `__cxa_end_catch()' (on line EQ[17])
		 */
		info->@ei_flags@ |= @EXCEPT_FRETHROW@;
		/* Select the more important exception. */
		if (error_priority(saved->@en_data@.@e_code@) >=
		    error_priority(info->@ei_code@))
			goto restore_saved_exception;
		/* Keep the newly set exception. */
	}
	/* Indicate that exception nesting is once again no longer allowed. */
	info->@ei_flags@ |= @EXCEPT_FINCATCH@;
}


%{
#ifdef __cplusplus
/* TODO: In user-space, using TRY and EXCEPT should  leave some sort of marker in  the
 *       binary  that allows for libc to consider these handlers as `dlexceptaware(3)'
 *       when operating in except-mode #4. However, I  am unsure as to how this  could
 *       be implemented without making some additional tweaks to gcc under KOS, though
 *       that wouldn't even be  the first time  I had to  tweak binutils/gcc for  this
 *       project... */
#ifndef __TRY
#define __TRY    try
#endif /* !__TRY */
#ifndef __EXCEPT
#define __EXCEPT catch(...)
#endif /* !__EXCEPT */

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
