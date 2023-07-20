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
%[default:section(".text.crt{|.dos}.except.io.utility")]
%[default:nodos]

%[define_decl_include_implication("<bits/os/siginfo.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/siginfo.h>": ["struct __siginfo_struct"])]

%[define_decl_include_implication("<kos/bits/exception_nest.h>" => [
	"<hybrid/typecore.h>",
	"<bits/types.h>",
	"<kos/bits/except.h>",
	"<kos/bits/exception_data.h>",
])]
%[define_decl_include("<kos/bits/exception_nest.h>": [
	"struct _exception_nesting_data"
])]
%[define_decl_include("<kos/bits/exception_data.h>": [
	"struct exception_data"
])]
/*%[define_decl_include("<kos/bits/exception_info.h>": [
	"struct exception_info"
])]*/

%(auto_source){
#include <errno.h>
#include <signal.h>
#include "../libc/dl.h" /* dlopen(), dlclose() */
}

%(auto_header){
/* Make use of inline optimizations when possible! */
#ifndef __INTELLISENSE__
#ifdef __arch_except_data
#define libc_except_data() __arch_except_data()
#endif /* __arch_except_data */
#ifdef __arch_except_code
#define libc_except_code() __arch_except_code()
#endif /* __arch_except_code */
#ifdef __arch_except_active
#define libc_except_active() __arch_except_active()
#endif /* __arch_except_active */
#ifdef __arch_except_class
#define libc_except_class() __arch_except_class()
#endif /* __arch_except_class */
#ifdef __arch_except_subclass
#define libc_except_subclass() __arch_except_subclass()
#endif /* __arch_except_subclass */
#ifdef __arch_except_register_state
#define libc_except_register_state() __arch_except_register_state()
#endif /* __arch_except_register_state */
#ifdef __arch_except_info
#define libc_except_info() __arch_except_info()
#endif /* __arch_except_info */
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
#include <hybrid/host.h>
)]%[insert:prefix(
#include <kos/bits/except.h>          /* __EXCEPT_REGISTER_STATE_TYPE */
)]%[insert:prefix(
#include <kos/bits/except-compiler.h> /* __TRY, __EXCEPT */
)]%[insert:prefix(
#include <kos/bits/exception_data.h>  /* struct exception_data */
)]%[insert:prefix(
#include <kos/bits/exception_nest.h>  /* struct _exception_nesting_data */
)]%[insert:prefix(
#include <kos/except/codes.h>         /* E_OK, ... */
)]%[insert:prefix(
#include <kos/bits/fastexcept.h>
)]%[insert:prefix(
#include <bits/crt/format-printer.h>
)]%{

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

}

%(auto_header){
#include <bits/crt/format-printer.h>
#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
#endif /* !__pformatprinter_defined */
}

%#ifdef __CC__
%{
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

}

%[declare_kernel_export(
	"except_rethrow", "__cxa_rethrow", "_Unwind_Resume",
	"except_thrown", "except_throw", "except_throw_current",
	"except_info", "except_data", "except_register_state",
	"except_code", "except_active", "except_class", "except_subclass",
	"except_unwind", "__cxa_begin_catch", "__cxa_end_catch",
	"__gxx_personality_v0", "__gcc_personality_v0", "_ZSt9terminatev",
)]


%[define_replacement(except_register_state_t = __EXCEPT_REGISTER_STATE_TYPE)]
%[define_replacement(except_code_t = __except_code_t)]
%[define_replacement(except_class_t = __except_class_t)]
%[define_replacement(except_subclass_t = __except_subclass_t)]
%[define_replacement(bool = __BOOL)]
%[define_replacement(true = 1)]
%[define_replacement(false = 0)]


/* Returns non-zero if there is an active exception. */
@@>> except_data(3)
@@Return a pointer to the thread-local descriptor of the current exception
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_data)),
  preferred_fast_extern_inline("except_data", { return __arch_except_data(); })]]
[[const, wunused, nothrow, nonnull, decl_include("<kos/bits/exception_data.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>"), requires(defined(__arch_except_data))]]
struct exception_data *except_data(void) {
	return __arch_except_data();
}

@@>> except_code(3)
@@Return the current exception code, or `EXCEPT_CODEOF(E_OK)' when none is active
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_code)),
  preferred_fast_extern_inline("except_code", { return __arch_except_code(); })]]
[[pure, wunused, nothrow, decl_include("<kos/bits/exception_data.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_code) || $has_function(except_data))]]
except_code_t except_code(void) {
@@pp_ifdef __arch_except_code@@
	return __arch_except_code();
@@pp_else@@
	return except_data()->@e_code@;
@@pp_endif@@
}

@@>> except_active(3)
@@Check if an exception is active; same as `except_code() != EXCEPT_CODEOF(E_OK)'
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_active)),
  preferred_fast_extern_inline("except_active", { return __arch_except_active(); })]]
[[pure, wunused, nothrow, userimpl, requires_function(except_code)]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_active) || $has_function(except_code))]]
$bool except_active(void) {
@@pp_ifdef __arch_except_active@@
	return __arch_except_active();
@@pp_else@@
	return except_code() != @E_OK@;
@@pp_endif@@
}

@@>> except_class(3)
@@Return the current exception class; same as `EXCEPT_CLASS(except_code())'
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_class)),
  preferred_fast_extern_inline("except_class", { return __arch_except_class(); })]]
[[pure, wunused, nothrow, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_class) || $has_function(except_code))]]
except_class_t except_class(void) {
@@pp_ifdef __arch_except_class@@
	return __arch_except_class();
@@pp_else@@
	return @EXCEPT_CLASS@(except_code());
@@pp_endif@@
}

@@>> except_subclass(3)
@@Return the current exception sub-class; same as `EXCEPT_SUBCLASS(except_code())'
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_subclass)),
  preferred_fast_extern_inline("except_subclass", { return __arch_except_subclass(); })]]
[[pure, wunused, nothrow, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_subclass) || $has_function(except_code))]]
except_subclass_t except_subclass(void) {
@@pp_ifdef __arch_except_subclass@@
	return __arch_except_subclass();
@@pp_else@@
	return @EXCEPT_SUBCLASS@(except_code());
@@pp_endif@@
}

@@>> except_register_state(3)
@@Return  the register state  at the time the  current exception was thrown.
@@The returned block of memory is only valid when `except_active() == true'.
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_register_state)),
  preferred_fast_extern_inline("except_register_state", { return __arch_except_register_state(); })]]
[[const, wunused, nothrow, nonnull, decl_include("<kos/bits/except.h>")]]
[[decl_prefix(
#ifndef __EXCEPT_REGISTER_STATE_TYPE
#include <bits/os/mcontext.h>
#define __EXCEPT_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_EXCEPT_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__EXCEPT_REGISTER_STATE_TYPE */
)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_register_state))]]
except_register_state_t *except_register_state(void) {
	return __arch_except_register_state();
}

@@>> except_as_errno(3)
@@Transform the  given exception  into  a posix  errno  value.
@@When no special errno is defined for `data', return `EPERM'.
[[kernel, cc(LIBKCALL)]]
[[pure, wunused, decl_include("<bits/types.h>")]]
[[decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<asm/os/errno.h>")]]
[[impl_include("<hybrid/host.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/reason/fs.h>")]]
[[impl_include("<kos/except/reason/illop.h>")]]
[[impl_include("<kos/except/reason/inval.h>")]]
[[impl_include("<kos/except/reason/io.h>")]]
[[impl_include("<kos/except/reason/net.h>")]]
[[impl_include("<kos/except/reason/noexec.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/kernel/handle.h>")]]
$errno_t except_as_errno([[in]] struct exception_data const *__restrict self) {
@@pp_ifdef EPERM@@
	errno_t result = EPERM;
@@pp_else@@
	errno_t result = 1;
@@pp_endif@@
	switch (self->@e_class@) {
/*[[[deemon
local final DEFAULT_ERRNO = "EPERM";
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
			reqMacros = " && ".join(for (local x: reqMacros) f"defined({x})");
			if (!reqMacros) {
				reqMacros = cls.ppCond;
			} else if (cls.ppCond != "1") {
				reqMacros = f"({reqMacros}) && ({cls.ppCond})";
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
			reqMacros = " && ".join(for (local x: reqMacros) f"defined({x})");
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
			reqMacros = " && ".join(for (local x: reqMacros) f"defined({x})");
			if (reqMacros)
				print("@@pp_if ", reqMacros, "@@");
			print("\t\tcase @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@", c.name, "@)):");
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
@@pp_if defined(EEXIST)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_ADDRESS_ALREADY_EXISTS@)):
			result = EEXIST;
			break;
@@pp_endif@@
@@pp_if defined(EMFILE)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS@)):
			result = EMFILE;
			break;
@@pp_endif@@
@@pp_if defined(ENFILE)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_INSUFFICIENT_HANDLE_RANGE@)):
			result = ENFILE;
			break;
@@pp_endif@@
@@pp_if defined(EADDRNOTAVAIL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_INSUFFICIENT_PORT_NUMBERS@)):
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

@@pp_if defined(EPIPE)@@
	case @E_BROKEN_PIPE@:
		result = EPIPE;
		break;
@@pp_endif@@

	case @E_BUFFER_TOO_SMALL@:
@@pp_if defined(ERANGE)@@
		result = ERANGE;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@_E_BUFFER_TOO_SMALL_EINVAL@)):
			result = EINVAL;
			break;
@@pp_endif@@
		default: break;
		}
		break;

@@pp_if defined(EINVAL)@@
	case @E_DIVIDE_BY_ZERO@:
		result = EINVAL;
		break;
@@pp_endif@@

	case @E_FSERROR@:
		switch(self->@e_subclass@) {
@@pp_if defined(ENOENT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_DELETED@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_FILE_NOT_FOUND@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_PATH_NOT_FOUND@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ENAMETOOLONG)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_ILLEGAL_PATH@)):
			result = ENAMETOOLONG;
			break;
@@pp_endif@@
@@pp_if defined(ENOTDIR)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_NOT_A_DIRECTORY@)):
			result = ENOTDIR;
			break;
@@pp_endif@@
@@pp_if defined(ELOOP)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_TOO_MANY_SYMBOLIC_LINKS@)):
			result = ELOOP;
			break;
@@pp_endif@@
@@pp_if defined(EACCES)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_ACCESS_DENIED@)):
			result = EACCES;
			break;
@@pp_endif@@
@@pp_if defined(ENOSPC)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_DISK_FULL@)):
			result = ENOSPC;
			break;
@@pp_endif@@
@@pp_if defined(EROFS)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_READONLY@)):
			result = EROFS;
			break;
@@pp_endif@@
@@pp_if defined(EMLINK)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_TOO_MANY_HARD_LINKS@)):
			result = EMLINK;
			break;
@@pp_endif@@
@@pp_if defined(EPERM) && defined(EISDIR)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_IS_A_DIRECTORY@)):
			result = self->@e_args@.@e_fserror@.@f_is_a_directory@.@iad_action_context@ == @E_FILESYSTEM_IS_A_DIRECTORY_LINK@ ? EPERM : EISDIR;
			break;
@@pp_endif@@
@@pp_if defined(ENOENT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_NOT_A_SYMBOLIC_LINK@)):
			result = ENOENT;
			break;
@@pp_endif@@
@@pp_if defined(ELOOP)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_IS_A_SYMBOLIC_LINK@)):
			result = ELOOP;
			break;
@@pp_endif@@
@@pp_if defined(EEXIST)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_FILE_ALREADY_EXISTS@)):
			result = EEXIST;
			break;
@@pp_endif@@
@@pp_if defined(ENOTEMPTY)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_DIRECTORY_NOT_EMPTY@)):
			result = ENOTEMPTY;
			break;
@@pp_endif@@
@@pp_if defined(EXDEV)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_CROSS_DEVICE_LINK@)):
			result = EXDEV;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_DIRECTORY_MOVE_TO_CHILD@)):
			result = EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOTBLK)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_MOUNT_UNSUPPORTED_DEVICE@)):
			result = ENOTBLK;
			break;
@@pp_endif@@
@@pp_if defined(ENOTBLK)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_MOUNT_NEEDS_DEVICE@)):
			result = ENOTBLK;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_WRONG_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_UNKNOWN_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(ENODEV)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_CORRUPTED_FILE_SYSTEM@)):
			result = ENODEV;
			break;
@@pp_endif@@
@@pp_if defined(EBUSY)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_PATH_ALREADY_MOUNTED@)):
			result = EBUSY;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_NOT_A_MOUNTING_POINT@)):
			result = EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(EBUSY)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_IS_A_MOUNTING_POINT@)):
			result = EBUSY;
			break;
@@pp_endif@@
@@pp_if defined(EFBIG)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_FILE_TOO_BIG@)):
			result = EFBIG;
			break;
@@pp_endif@@
@@pp_if defined(ESPIPE) && defined(EINVAL) && defined(ENOTDIR) && defined(ENODEV) && defined(EROFS) && defined(EPERM)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_FSERROR_UNSUPPORTED_OPERATION@)):
			result = (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_SEEK@ || self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_PREAD@ ||
			         self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_PWRITE@) ? ESPIPE :
			        (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_READ@ || self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_WRITE@ ||
			         self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_SYNC@) ? EINVAL :
			        (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_READDIR@) ? ENOTDIR :
			        (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_MMAP@ || self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_ALLOCATE@) ? ENODEV :
			        (self->@e_args@.@e_fserror@.@f_unsupported_operation@.@uo_operation_id@ == @E_FILESYSTEM_OPERATION_CREAT@) ? EROFS :
			        EPERM;
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
@@pp_if defined(ENXIO) && defined(EPERM)@@
		result = self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK@ ? ENXIO : EPERM;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(EINVAL) && defined(ELOOP)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_REFERENCE_LOOP@)):
			result = self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP@ ? EINVAL : ELOOP;
			break;
@@pp_endif@@
@@pp_if defined(ENOTCONN) && defined(EDESTADDRREQ) && defined(EISCONN) && defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_BECAUSE_NOT_READY@)):
			result = (self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED@) ? ENOTCONN :
			        (self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED@) ? EDESTADDRREQ :
			        (self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED@) ? EISCONN :
			         EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOTTY) && defined(EPERM)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_BECAUSE_GROUPING@)):
			result = (self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION@ ||
			         self->@e_args@.@e_illegal_operation@.@io_reason@ == @E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION@) ? ENOTTY :
			         EPERM;
			break;
@@pp_endif@@
@@pp_if defined(ENXIO)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_IO_OPERATION@)):
			result = ENXIO;
			break;
@@pp_endif@@
@@pp_if defined(ENOMEM)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED@)):
			result = ENOMEM;
			break;
@@pp_endif@@
@@pp_if defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_OPERATION@)):
			result = EINVAL;
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
@@pp_if defined(EPERM) && defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_BAD_VALUE@)):
			result = (self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID@ ||
			         self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID@) ? EPERM : EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(EAFNOSUPPORT) && defined(ESOCKTNOSUPPORT) && defined(EPROTONOSUPPORT) && defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_UNKNOWN_COMMAND@)):
			result = self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY@ ? EAFNOSUPPORT :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE@ ? ESOCKTNOSUPPORT :
			        self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL@ ? EPROTONOSUPPORT :
			        EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(ENOPROTOOPT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_SOCKET_OPT@)):
			result = ENOPROTOOPT;
			break;
@@pp_endif@@
@@pp_if defined(EAFNOSUPPORT) && defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_UNEXPECTED_COMMAND@)):
			result = self->@e_args@.@e_invalid_argument@.@ia_context@ == @E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY@ ? EAFNOSUPPORT : EINVAL;
			break;
@@pp_endif@@
		default: break;
		}
		break;

	case @E_INVALID_HANDLE@:
@@pp_if defined(EBADF)@@
		result = EBADF;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(EINVAL) && defined(EBADF)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_HANDLE_FILE@)):
			result = self->@e_args@.@e_invalid_handle@.@ih_file@.@f_reason@ == @E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD@ ? EINVAL : EBADF;
			break;
@@pp_endif@@
@@pp_if defined(ENOTSOCK) && defined(EBADFD)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_HANDLE_FILETYPE@)):
			result = self->@e_args@.@e_invalid_handle@.@ih_filetype@.@f_needed_handle_type@ == @HANDLE_TYPE_SOCKET@ ? ENOTSOCK : EBADFD;
			break;
@@pp_endif@@
@@pp_if defined(EACCES) && defined(EINVAL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_HANDLE_OPERATION@)):
			result = self->@e_args@.@e_invalid_handle@.@ih_operation@.@o_op@ == @E_INVALID_HANDLE_OPERATION_MMAP@ ? EACCES : EINVAL;
			break;
@@pp_endif@@
@@pp_if defined(EOPNOTSUPP)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_INVALID_HANDLE_NET_OPERATION@)):
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
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_HOST_UNREACHABLE@)):
			result = EHOSTUNREACH;
			break;
@@pp_endif@@
@@pp_if defined(EADDRINUSE)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_ADDRESS_IN_USE@)):
			result = EADDRINUSE;
			break;
@@pp_endif@@
@@pp_if defined(EMSGSIZE)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_MESSAGE_TOO_LONG@)):
			result = EMSGSIZE;
			break;
@@pp_endif@@
@@pp_if defined(ECONNABORTED)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_CONNECTION_ABORT@)):
			result = ECONNABORTED;
			break;
@@pp_endif@@
@@pp_if defined(ECONNREFUSED)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_CONNECTION_REFUSED@)):
			result = ECONNREFUSED;
			break;
@@pp_endif@@
@@pp_if defined(ECONNRESET)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_CONNECTION_RESET@)):
			result = ECONNRESET;
			break;
@@pp_endif@@
@@pp_if defined(ETIMEDOUT)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_TIMEOUT@)):
			result = ETIMEDOUT;
			break;
@@pp_endif@@
@@pp_if defined(ENETUNREACH)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_UNREACHABLE@)):
			result = ENETUNREACH;
			break;
@@pp_endif@@
@@pp_if defined(EADDRNOTAVAIL)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_ADDRESS_NOT_AVAILABLE@)):
			result = EADDRNOTAVAIL;
			break;
@@pp_endif@@
@@pp_if defined(EPIPE)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NET_SHUTDOWN@)):
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

	case @E_NO_SUCH_OBJECT@:
@@pp_if defined(ENODATA)@@
		result = ENODATA;
@@pp_endif@@
		switch(self->@e_subclass@) {
@@pp_if defined(ENODEV)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_NO_CTTY@)):
			result = ENODEV;
			break;
@@pp_endif@@
		default: break;
		}
		break;

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

@@pp_if defined(ENODEV)@@
	case @E_UNSUPPORTED_DEVICE@:
		result = ENODEV;
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

@@>> except_as_signal(3)
@@Transform the given exception into a posix signal.
@@If doing this is possible, fill in `*result' and return `true'.
@@Otherwise, `*result' is left in an undefined state, and `false'
@@is returned.
[[wunused, kernel, cc(LIBKCALL)]]
[[decl_include("<kos/bits/exception_data.h>")]]
[[decl_include("<bits/os/siginfo.h>")]]
[[impl_include("<hybrid/host.h>")]]
[[impl_include("<asm/os/siginfo.h>")]]
[[impl_include("<asm/os/signal.h>")]]
[[impl_include("<bits/os/siginfo.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/kernel/handle.h>")]]
$bool except_as_signal([[in]] struct exception_data const *__restrict self,
                       [[out]] struct __siginfo_struct *__restrict result) {
	except_code_t code = self->@e_code@;
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
	switch (@EXCEPT_CLASS@(code)) {

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
		case @EXCEPT_CODEOF@(@E_SEGFAULT_READONLY@):
		case @EXCEPT_CODEOF@(@E_SEGFAULT_NOTREADABLE@):
		case @EXCEPT_CODEOF@(@E_SEGFAULT_NOTEXECUTABLE@):
			result->@si_code@ = SEGV_ACCERR;
			break;
@@pp_endif@@

@@pp_if defined(SIGBUS) && defined(BUS_OBJERR)@@
		case @EXCEPT_CODEOF@(@E_SEGFAULT_NOTATOMIC@):
			result->@si_signo@ = SIGBUS;
			result->@si_code@  = BUS_OBJERR;
			break;
@@pp_endif@@

@@pp_if defined(SIGBUS) && defined(BUS_ADRALN)@@
		case @EXCEPT_CODEOF@(@E_SEGFAULT_UNALIGNED@):
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
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_BAD_OPERAND@):
			result->@si_code@ = ILL_ILLOPN;
@@pp_if defined(ILL_ILLADR)@@
			if (self->@e_args@.@e_illegal_instruction@.@ii_bad_operand@.@bo_what@ == @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY@ ||
			    self->@e_args@.@e_illegal_instruction@.@ii_bad_operand@.@bo_what@ == @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER@)
				result->@si_code@ = ILL_ILLADR;
@@pp_endif@@
			break;
@@pp_endif@@

@@pp_if defined(ILL_PRVOPC)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE@):
			result->@si_code@ = ILL_PRVOPC;
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLOPN)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_REGISTER@):
			result->@si_code@ = ILL_ILLOPN;
@@pp_if defined(ILL_PRVREG)@@
			if (self->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ == @E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV@ ||
			    self->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ == @E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV@)
				result->@si_code@ = ILL_PRVREG;
@@pp_endif@@
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLADR) && defined(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@):
			result->@si_code@ = ILL_ILLADR;
			break;
@@pp_endif@@

@@pp_if defined(ILL_ILLOPC)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_BAD_OPCODE@):
@@pp_if defined(@E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX@)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX@):
@@pp_endif@@
@@pp_if defined(@E_ILLEGAL_INSTRUCTION_X86_TOO_LONG@)@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_TOO_LONG@):
@@pp_endif@@
		case @EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE@):
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
	result->@si_errno@ = except_as_errno(self);
	return true;
}



@@>> except_name(3)
@@Return the name of the  given error, or `NULL'  if
@@unknown. This name is one of the `E_*' identifier.
@@E.g.: `except_name(EXCEPT_CODEOF(E_BADALLOC))' -> "E_BADALLOC"
[[kernel, cc(LIBKCALL)]]
[[const, wunused, nothrow, decl_include("<kos/bits/exception_data.h>")]]
[[impl_include("<hybrid/host.h>", "<kos/except/codes.h>")]]
char const *except_name(except_code_t code) {
	except_class_t err_class       = @EXCEPT_CLASS@(code);
	except_subclass_t err_subclass = @EXCEPT_SUBCLASS@(code);
/*[[[deemon
(printExceptNameFunctionBody from ....misc.libgen.exceptinfo)(
	classVariableName:    "err_class",
	subClassVariableName: "err_subclass");
]]]*/
#if !defined(__i386__) && !defined(__x86_64__)
	static char const e_linear_0000h_000ch[] =
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
	"T_SOCKET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEM"
	"ENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0E_SER"
	"VICE_EXITED\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HA"
	"NDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OP"
	"ERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFO"
	"RSIGNAL\0\1E_PROCESS_EXITED\0E_PROCESS_GROUP_EXITED\0\1E_NO_DEVICE\0\1E"
	"_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_CTTY\0\1E_ILLEGAL_OPERA"
	"TION\0E_ILLEGAL_REFERENCE_LOOP\0E_ILLEGAL_BECAUSE_NOT_READY\0E_ILLE"
	"GAL_BECAUSE_GROUPING\0E_ILLEGAL_IO_OPERATION\0E_ILLEGAL_RESOURCE_L"
	"IMIT_EXCEEDED\0E_INVALID_OPERATION\0\1E_BROKEN_PIPE\0\1E_UNSUPPORTED_"
	"DEVICE\0\1";
	static char const e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0_E_BUFFER_TOO_SM"
	"ALL_EINVAL\0\1E_UNICODE_ERROR\0\1";
	static char const e_linear_f000h_f000h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1";
	static char const e_linear_fe40h_fe40h[] =
	"E_EXIT_THREAD\0\1";
	static char const e_linear_fe81h_fe81h[] =
	"E_EXIT_PROCESS\0\1";
	static char const e_linear_feffh_ff07h[] =
	"E_UNHANDLED_INTERRUPT\0\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAUL"
	"T_READONLY\0E_SEGFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEG"
	"FAULT_NOTATOMIC\0E_SEGFAULT_UNALIGNED\0E_SEGFAULT_NONCONTINUOUS\0\1E"
	"_BREAKPOINT\0\1E_DIVIDE_BY_ZERO\0\1E_OVERFLOW\0\1E_ILLEGAL_INSTRUCTION"
	"\0E_ILLEGAL_INSTRUCTION_BAD_OPCODE\0E_ILLEGAL_INSTRUCTION_UNSUPPOR"
	"TED_OPCODE\0E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE\0E_ILLEGAL_INS"
	"TRUCTION_BAD_OPERAND\0\0\0\0\0\0\0\0\0\0\0\0\0E_ILLEGAL_INSTRUCTION_REGISTER\0"
	"\1E_STACK_OVERFLOW\0\1E_INDEX_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1";
	char const *result;
	except_class_t class_offset;
	except_subclass_t subclass_offset;
	if (err_class <= 0x000c) {
		result = e_linear_0000h_000ch;
		class_offset = err_class;
	} else if (err_class >= 0x0081 && err_class <= 0x0091) {
		result = e_linear_0081h_0091h;
		class_offset = err_class - 0x0081;
	} else if (err_class >= 0xf000 && err_class <= 0xf000) {
		result = e_linear_f000h_f000h;
		class_offset = err_class - 0xf000;
	} else if (err_class >= 0xfe40 && err_class <= 0xfe40) {
		result = e_linear_fe40h_fe40h;
		class_offset = err_class - 0xfe40;
	} else if (err_class >= 0xfe81 && err_class <= 0xfe81) {
		result = e_linear_fe81h_fe81h;
		class_offset = err_class - 0xfe81;
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
		"VE_TO_CHILD\0E_FSERROR_MOUNT_UNSUPPORTED_DEVICE\0E_FSERROR_MOUNT_N"
		"EEDS_DEVICE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_S"
		"YSTEM\0E_FSERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_PATH_ALREADY_MOU"
		"NTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FSERROR_IS_A_MOUNTING_POIN"
		"T\0E_FSERROR_FILE_TOO_BIG";
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
	static char const e_linear_0000h_000ch[] =
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
	"T_SOCKET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEM"
	"ENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0E_SER"
	"VICE_EXITED\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HA"
	"NDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OP"
	"ERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFO"
	"RSIGNAL\0\1E_PROCESS_EXITED\0E_PROCESS_GROUP_EXITED\0\1E_NO_DEVICE\0\1E"
	"_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_CTTY\0\1E_ILLEGAL_OPERA"
	"TION\0E_ILLEGAL_REFERENCE_LOOP\0E_ILLEGAL_BECAUSE_NOT_READY\0E_ILLE"
	"GAL_BECAUSE_GROUPING\0E_ILLEGAL_IO_OPERATION\0E_ILLEGAL_RESOURCE_L"
	"IMIT_EXCEEDED\0E_INVALID_OPERATION\0\1E_BROKEN_PIPE\0\1E_UNSUPPORTED_"
	"DEVICE\0\1";
	static char const e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0_E_BUFFER_TOO_SM"
	"ALL_EINVAL\0\1E_UNICODE_ERROR\0\1";
	static char const e_linear_f000h_f000h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1";
	static char const e_linear_fe40h_fe40h[] =
	"E_EXIT_THREAD\0\1";
	static char const e_linear_fe81h_fe81h[] =
	"E_EXIT_PROCESS\0\1";
	static char const e_linear_feffh_ff0eh[] =
	"E_UNHANDLED_INTERRUPT\0\1E_DIVIDE_BY_ZERO\0\1\1\1E_BREAKPOINT\0\1E_OVERF"
	"LOW\0\1E_INDEX_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1\1\1E_STACK_OVERFL"
	"OW\0\1\1\1\1\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAULT_READONLY\0E_SE"
	"GFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEGFAULT_NOTATOMIC"
	"\0E_SEGFAULT_UNALIGNED\0E_SEGFAULT_NONCONTINUOUS\0\1";
	char const *result;
	except_class_t class_offset;
	except_subclass_t subclass_offset;
	if (err_class <= 0x000c) {
		result = e_linear_0000h_000ch;
		class_offset = err_class;
	} else if (err_class >= 0x0081 && err_class <= 0x0091) {
		result = e_linear_0081h_0091h;
		class_offset = err_class - 0x0081;
	} else if (err_class >= 0xf000 && err_class <= 0xf000) {
		result = e_linear_f000h_f000h;
		class_offset = err_class - 0xf000;
	} else if (err_class >= 0xfe40 && err_class <= 0xfe40) {
		result = e_linear_fe40h_fe40h;
		class_offset = err_class - 0xfe40;
	} else if (err_class >= 0xfe81 && err_class <= 0xfe81) {
		result = e_linear_fe81h_fe81h;
		class_offset = err_class - 0xfe81;
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
		"VE_TO_CHILD\0E_FSERROR_MOUNT_UNSUPPORTED_DEVICE\0E_FSERROR_MOUNT_N"
		"EEDS_DEVICE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_S"
		"YSTEM\0E_FSERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_PATH_ALREADY_MOU"
		"NTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FSERROR_IS_A_MOUNTING_POIN"
		"T\0E_FSERROR_FILE_TOO_BIG";
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



@@>> except_priority(3)
@@Return the priority for a given error code, where exceptions
@@with greater priorities should take  the place of ones  with
@@lower priorities in  situations where multiple  simultaneous
@@errors can't be prevented.
[[kernel, cc(LIBKCALL)]]
[[const, wunused, nothrow]]
[[impl_include("<kos/except/codes.h>")]]
[[impl_include("<kos/bits/exception_data.h>")]]
[[decl_include("<kos/bits/exception_data.h>")]]
unsigned int except_priority(except_code_t code) {
	except_class_t code_class = @EXCEPT_CLASS@(code);
	if (@EXCEPTCLASS_ISRTLPRIORITY@(code_class))
		return 4 + (code_class - @EXCEPTCLASS_RTL_MIN@);
	if (@EXCEPTCLASS_ISHIGHPRIORITY@(code_class))
		return 3;
	if (code_class != @EXCEPT_CLASS@(@EXCEPT_CODEOF@(@E_OK@))) {
		if (!@EXCEPTCLASS_ISLOWPRIORITY@(code_class))
			return 2;
		return 1;
	}
	return 0;
}


%{
/* Flags for `except_print_short_description()' */
#define EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_NORMAL 0x0000 /* Normal flags */
#define EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY    0x0001 /* Print TTY escape sequences for color highlighting */
}

%[define_replacement(EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_NORMAL = 0)]
%[define_replacement(EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY = 1)]


@@>> except_print_short_description(3)
@@Print a short, single-line (without trailing linefeed) description  of
@@the given error `data', including the error code, name and for certain
@@errors, prominent error arguments.
@@@param: flags: Set of `EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_*'
@@@return: * : The usual pformatprinter-compatible return value
[[kernel, cc(LIBKCALL)]]
[[decl_include("<kos/bits/exception_data.h>")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<hybrid/host.h>", "<kos/except/codes.h>")]]
[[impl_include("<kos/bits/exception_data.h>", "<bits/crt/inttypes.h>")]]
[[impl_include("<libregdump/register.h>", "<dlfcn.h>")]]
[[impl_include("<libansitty/ctl.h>")]]
[[impl_prefix(
@@pp_if defined(@__i386__@) || defined(@__x86_64__@)@@
#include <asm/registers.h>
@@pp_endif@@
)]]
$ssize_t except_print_short_description([[nonnull]] $pformatprinter printer, void *arg,
                                        [[in]] struct exception_data const *data,
                                        $uintptr_t flags) {
@@pp_ifndef PRIxPTR@@
@@pp_ifdef __PRIP_PREFIX@@
#define PRIxPTR __PRIP_PREFIX "x"
@@pp_else@@
#define PRIxPTR "zx"
@@pp_endif@@
@@pp_endif@@
#define FMT(tty, notty) (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY ? tty : notty)
	ssize_t temp, result = 0;
	result = format_printf(printer, arg,
	                       FMT("exception "
	                           @AC_WHITE@("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x") ":"
	                           @AC_WHITE@("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                           "exception "
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x:"
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                       data->@e_class@, data->@e_subclass@);
	if unlikely(result < 0)
		goto done;
	{
		char const *name;
		char const *errno_name;
		name = except_name(data->@e_code@);
		errno_name = strerrorname_np(except_as_errno(data));
		if (name) {
			temp = format_printf(printer, arg,
			                     FMT(" [" @AC_WHITE@("%s") "%s" @AC_WHITE@("%s") "]",
			                         " [%s%s%s]"),
			                     name,
			                     errno_name ? "," : "",
			                     errno_name ? errno_name : "");
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	temp = 0;
	switch (data->@e_class@) {

	case @EXCEPT_CLASS@(@EXCEPT_CODEOF@(@E_BADALLOC@)):
		switch (data->@e_subclass@) {

		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_INSUFFICIENT_HEAP_MEMORY@)):
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY@)):
			temp = format_printf(printer, arg,
			                     FMT(" [num_bytes:" @AC_WHITE@("%#" PRIxPTR) "]",
			                         " [num_bytes:%#" PRIxPTR "]"),
			                     data->@e_args@.@e_badalloc@.@ba_insufficient_heap_memory@);
			break;

		default:
			break;
		}
		break;

	/* TODO: More error classes */

	case @EXCEPT_CLASS@(@EXCEPT_CODEOF@(@E_SEGFAULT@)): {
		temp = format_printf(printer, arg,
@@pp_if defined(@__i386__@) || defined(@__x86_64__@)@@
		                     FMT(" [cr2:" @AC_WHITE@("%p") "," @AC_WHITE@("%c%c%c%c%c%c") "]",
		                         " [cr2:%p,%c%c%c%c%c%c]")
@@pp_else@@
		                     FMT(" [addr:" @AC_WHITE@("%p") "," @AC_WHITE@("%c%c%c%c%c%c") "]",
		                         " [addr:%p,%c%c%c%c%c%c]")
@@pp_endif@@
		                     ,
		                     data->@e_args@.@e_segfault@.@s_addr@,
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_FAULT@ ? 'f' : '-',
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_WRITING@ ? 'w' : '-',
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_USERCODE@ ? 'u' : '-',
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_NONCANON@ ? 'c' : '-',
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_EXEC@ ? 'x' : '-',
		                     data->@e_args@.@e_segfault@.@s_context@ & @E_SEGFAULT_CONTEXT_VIO@ ? 'v' : '-');
	}	break;

	case @EXCEPT_CLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION@)): {
@@pp_if defined(@__i386__@) || defined(@__x86_64__@)@@
		uintptr_t opcode, opno;
		opcode = data->@e_args@.@e_illegal_instruction@.@ii_opcode@;
		opno   = @E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC@(opcode);
		if (opno <= 0xff) {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#.2" PRIxPTR),
			                         " [opcode:%#.2" PRIxPTR),
			                     opno);
		} else if (opno <= 0xffff) {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#.4" PRIxPTR),
			                         " [opcode:%#.4" PRIxPTR),
			                     opno);
		} else {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#" PRIxPTR),
			                         " [opcode:%#" PRIxPTR),
			                     opno);
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (@E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG@(opcode)) {
			temp = format_printf(printer, arg, "/%u", (unsigned int)@E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG@(opcode));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = (*printer)(arg, "]", 1);
@@pp_else@@
		uintptr_t opcode = data->@e_args@.@e_illegal_instruction@.@ii_opcode@;
		if (opcode <= 0xff) {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#.2" PRIxPTR) "]",
			                         " [opcode:%#.2" PRIxPTR "]"),
			                     opcode);
		} else if (opcode <= 0xffff) {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#.4" PRIxPTR) "]",
			                         " [opcode:%#.4" PRIxPTR "]"),
			                     opcode);
		} else {
			temp = format_printf(printer, arg,
			                     FMT(" [opcode:" @AC_WHITE@("%#" PRIxPTR) "]",
			                         " [opcode:%#" PRIxPTR "]"),
			                     opcode);
		}
@@pp_endif@@
		if unlikely(temp < 0)
			goto err;
		result += temp;
		switch (data->@e_subclass@) {

@@pp_if defined(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@)@@
		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_X86_INTERRUPT@)):
			temp = format_printf(printer, arg,
			                     FMT(" [int:" @AC_WHITE@("%#.2" PRIxPTR) ","
			                                  @AC_WHITE@("%#" PRIxPTR) ","
			                                  "seg:" @AC_WHITE@("%#" PRIxPTR) "]",
			                         " [int:%#.2" PRIxPTR ",%#" PRIxPTR ",seg:%#" PRIxPTR "]"),
			                     data->@e_args@.@e_illegal_instruction@.@ii_x86_interrupt@.@xi_intno@,
			                     data->@e_args@.@e_illegal_instruction@.@ii_x86_interrupt@.@xi_ecode@,
			                     data->@e_args@.@e_illegal_instruction@.@ii_x86_interrupt@.@xi_segval@);
			break;
@@pp_endif@@

		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_BAD_OPERAND@)): {
			char const *what_name;
			switch (data->@e_args@.@e_illegal_instruction@.@ii_bad_operand.bo_what@) {

			case @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY@:
			case @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER@:
				what_name = "addrmode";
				break;

			case @E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE@:
				what_name = "value";
				break;

			default:
				what_name = NULL;
				break;
			}
			if (what_name) {
				temp = format_printf(printer, arg,
				                     FMT(" [what=" @AC_WHITE@("%s") "]",
				                         " [what=%s]"),
				                     what_name);
			} else {
				temp = format_printf(printer, arg,
				                     FMT(" [what=" @AC_WHITE@("?(%#" PRIxPTR ")") "]",
				                         " [what=?(%#" PRIxPTR ")]"),
				                     data->@e_args@.@e_illegal_instruction@.@ii_bad_operand@.@bo_what@);
			}
		}	break;

		case @EXCEPT_SUBCLASS@(@EXCEPT_CODEOF@(@E_ILLEGAL_INSTRUCTION_REGISTER@)): {
			char const *what;
			uintptr_t regno;
			switch (data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@) {
			case @E_ILLEGAL_INSTRUCTION_REGISTER_RDINV@: what = "rdinv"; break; /* Read from invalid register */
			case @E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV@: what = "rdprv"; break; /* Read from privileged register */
			case @E_ILLEGAL_INSTRUCTION_REGISTER_WRINV@: what = "wrinv"; break; /* Write to invalid register */
			case @E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV@: what = "wrprv"; break; /* Write to privileged register */
			case @E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD@: what = "wrbad"; break; /* Bad value written to register */
			default: what = NULL; break;
			}
			if (what) {
				temp = format_printf(printer, arg, " [%s:", what);
			} else {
				temp = format_printf(printer, arg, " [?(%#" PRIxPTR "):",
				                     data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@);
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
			regno = data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_regno@;
@@pp_if defined(@__i386__@) || defined(@__x86_64__@)@@
			if (regno == @X86_REGISTER_XCR@ || regno == @X86_REGISTER_PCR@ || regno == @X86_REGISTER_MSR@) {
				char extname[4];
				extname[0] = 'x';
				extname[1] = 'c';
				extname[2] = 'r';
				extname[3] = 0;
				if (regno == @X86_REGISTER_PCR@) {
					extname[0] = 'p';
				} else if (regno == @X86_REGISTER_MSR@) {
					extname[0] = 'm';
					extname[1] = 's';
				}
				temp = format_printf(printer, arg,
				                     FMT(@AC_WHITE@("%s(%#" PRIxPTR ")") "," @AC_WHITE@("%#" __PRI8_PREFIX "x") "]",
				                         "%s(%#" PRIxPTR "),%#" __PRI8_PREFIX "x]"),
				                     extname, data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_offset@,
				                     (uint64_t)data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_regval@ |
				                     (uint64_t)data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_regval2@ << 32);
			} else
@@pp_endif@@
			{
				if (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY) {
					static char const beginfg[] = @AC_FG@(@ANSITTY_CL_WHITE@);
					temp = (*printer)(arg, beginfg, COMPILER_STRLEN(beginfg));
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
@@pp_ifdef LIBREGDUMP_WANT_PROTOTYPES@@
				temp = regdump_register_name(printer, arg, regno);
@@pp_else@@
@@pp_if defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)@@
				void *libregdump;
@@pp_ifdef RTLD_LOCAL@@
				libregdump = @dlopen@(@LIBREGDUMP_LIBRARY_NAME@, @RTLD_LOCAL@);
@@pp_else@@
				libregdump = @dlopen@(@LIBREGDUMP_LIBRARY_NAME@, 0);
@@pp_endif@@
				if (libregdump != NULL) {
					@PREGDUMP_REGISTER_NAME@ pdyn_regdump_register_name;
					*(void **)&pdyn_regdump_register_name = @dlsym@(libregdump, "regdump_register_name");
					if unlikely(!pdyn_regdump_register_name) {
@@pp_ifdef __CRT_HAVE_dlclose@@
						@dlclose@(libregdump);
@@pp_endif@@
						goto print_generic_register_name;
					}
					temp = (*pdyn_regdump_register_name)(printer, arg, regno);
@@pp_ifdef __CRT_HAVE_dlclose@@
					@dlclose@(libregdump);
@@pp_endif@@
				} else
@@pp_endif@@
				{
print_generic_register_name:
					temp = format_printf(printer, arg, "reg.%#" PRIxPTR, regno);
				}
@@pp_endif@@
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY) {
					static char const endfg[] = @AC_FGDEF@;
					temp = (*printer)(arg, endfg, COMPILER_STRLEN(endfg));
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
				if (data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_regval@ != 0 ||
				    (data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ != @E_ILLEGAL_INSTRUCTION_REGISTER_RDINV@ &&
				     data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_how@ != @E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV@)) {
					temp = format_printf(printer, arg,
					                     FMT("," @AC_WHITE@("%#" PRIxPTR) "]",
					                         ",%#" PRIxPTR "]"),
					                     data->@e_args@.@e_illegal_instruction@.@ii_register@.@r_regval@);
				} else {
					temp = (*printer)(arg, "]", 1);
				}
			}
		}	break;

		default:
			temp = 0;
			break;
		}
	}	break;

	default:
		break;
	}
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
#undef FMT
}




%#ifdef __USE_KOS_KERNEL
@@>> except_info(3)
@@Return a pointer to the thread-local exception info structure.
@@Note  that the exact  layout of this  structure depends on how
@@libc/the kernel was configured. For the sake of compatibility,
@@try to  use `except_data()'  and `except_register_state()'  in
@@favor of this function.
[[kernel, cc(LIBKCALL)]]
[[if($extended_include_prefix("<kos/bits/fastexcept.h>")defined(__arch_except_info)),
  preferred_fast_extern_inline("except_info", { return __arch_except_info(); })]]
[[const, wunused, nothrow, nonnull, decl_prefix(struct exception_info;)]]
[[userimpl, requires_include("<kos/bits/fastexcept.h>")]]
[[requires(defined(__arch_except_info))]]
struct exception_info *except_info(void) {
	return __arch_except_info();
}

@@>> except_unwind(3)
@@Unwind the given register state to propagate the currently set error.
@@Following this, the  returned register state  should then be  loaded.
[[kernel, cc(__EXCEPT_UNWIND_CC)]]
[[wunused, nonnull, decl_include("<kos/bits/except.h>")]]
[[decl_prefix(
#ifndef __EXCEPT_UNWIND_CC
#define __EXCEPT_UNWIND_CC __LIBKCALL
#endif /* !__EXCEPT_UNWIND_CC */
)]]
[[decl_prefix(
#ifndef __EXCEPT_REGISTER_STATE_TYPE
#include <bits/os/mcontext.h>
#define __EXCEPT_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_EXCEPT_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__EXCEPT_REGISTER_STATE_TYPE */
)]]
except_register_state_t *except_unwind([[inout]] except_register_state_t *__restrict state);

%#endif /* __USE_KOS_KERNEL */


@@>> except_throw_current(3)
@@Throw the currently set (in `except_data()') exception.
[[noreturn, cold, throws]]
[[kernel, cc(LIBKCALL)]]
void except_throw_current(void);

@@>> except_rethrow(3)
@@Rethrow the current exception (same as a c++ `throw;' expression)
[[guard, noreturn, cold, throws]]
[[kernel, cc(LIBKCALL)]]
void except_rethrow(void);


@@>> except_throw(3)
@@Throw an exception and fill exception pointers with all zeroes
[[guard, decl_prefix(
#include <kos/bits/exception_data.h>
#ifndef __EXCEPT_THROW_CC
#define __EXCEPT_THROW_CC __LIBKCALL
#endif /* !__EXCEPT_THROW_CC */
)]]
[[noreturn, cold, throws]]
[[kernel, cc(__EXCEPT_THROW_CC)]]
void except_throw(except_code_t code);


@@>> except_thrown(3)
@@Throw an exception and load `argc' pointers from varargs
[[guard, decl_prefix(
#include <kos/bits/exception_data.h>
#ifndef __EXCEPT_THROWN_CC
#define __EXCEPT_THROWN_CC __LIBKCALL
#endif /* !__EXCEPT_THROWN_CC */
)]]
[[noreturn, cold, throws]]
[[kernel, cc(__EXCEPT_THROWN_CC)]]
void except_thrown(except_code_t code, unsigned int _argc, ...);



%{
/* Rethrow the last exception */
#ifdef __except_rethrow_defined
#define RETHROW() except_rethrow()
#elif defined(__cplusplus)
#define RETHROW() throw
#endif /* ... */
}


%#ifdef __INTELLISENSE__
%{
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
}
%#else /* __INTELLISENSE__ */
%{

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

#ifdef __CHECKER__
#define __except_throw_defined
#define __except_thrown_defined
#undef except_throw
#undef except_thrown
#define except_throw(code)          __builtin_throw(code)
#define except_thrown(code, n, ...) __builtin_throw(code, __VA_ARGS__)
#endif /* __CHECKER__ */

#ifdef __except_thrown_defined
#ifdef __except_throw_defined
#define __PRIVATE_THROW1(code) except_throw(__PRIVATE_THROW_PACKAGE_CODE code)
#else /* __except_throw_defined */
#define __PRIVATE_THROW1(code) except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 0)
#endif /* !__except_throw_defined */
#define __PRIVATE_THROW2(code, a)                      except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 1, (__UINTPTR_TYPE__)(a))
#define __PRIVATE_THROW3(code, a, b)                   except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 2, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b))
#define __PRIVATE_THROW4(code, a, b, c)                except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 3, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c))
#define __PRIVATE_THROW5(code, a, b, c, d)             except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 4, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d))
#define __PRIVATE_THROW6(code, a, b, c, d, e)          except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 5, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e))
#define __PRIVATE_THROW7(code, a, b, c, d, e, f)       except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 6, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f))
#define __PRIVATE_THROW8(code, a, b, c, d, e, f, g)    except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 7, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g))
#define __PRIVATE_THROW9(code, a, b, c, d, e, f, g, h) except_thrown(__PRIVATE_THROW_PACKAGE_CODE code, 8, (__UINTPTR_TYPE__)(a), (__UINTPTR_TYPE__)(b), (__UINTPTR_TYPE__)(c), (__UINTPTR_TYPE__)(d), (__UINTPTR_TYPE__)(e), (__UINTPTR_TYPE__)(f), (__UINTPTR_TYPE__)(g), (__UINTPTR_TYPE__)(h))
#define __PRIVATE_THROW_N2(n) __PRIVATE_THROW##n
#define __PRIVATE_THROW_N(n)  __PRIVATE_THROW_N2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define THROW(...)            __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define THROW(args...)        __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */
#endif /* __except_thrown_defined */
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
}

%#endif /* !__INTELLISENSE__ */

@@>> except_nesting_begin(3)
@@Begin a nested  TRY-block. (i.e. inside  of another EXCEPT  block)
@@Don't call this function directly; use `NESTED_EXCEPTION' instead.
[[guard, no_local, decl_prefix(
#ifndef __EXCEPT_NESTING_BEGIN_CC
#define __EXCEPT_NESTING_BEGIN_CC __LIBKCALL
#endif /* !__EXCEPT_NESTING_BEGIN_CC */
), nothrow, kernel, cc(__EXCEPT_NESTING_BEGIN_CC)]]
[[decl_include("<kos/bits/exception_nest.h>", "<bits/types.h>")]]
[[impl_include("<kos/bits/exception_info.h>")]]
void except_nesting_begin([[inout]] struct _exception_nesting_data *__restrict saved) {
	struct exception_info *info = except_info();
	if (info->@ei_code@ == @EXCEPT_CODEOF@(@E_OK@)) {
		/* Not inside of  a catch-block (ignore  the nesting  request)
		 * This  can happen if  the caller is only  using the nest for
		 * safety (in case a sub-function  needs to be able to  handle
		 * its  own  exceptions, but  may  be called  from  an unaware
		 * exception  handler),  or  is  using  more  than  one  nest.
		 * In all of these cases, just ignore the nest, and also  make
		 * it so that the associated `except_nesting_end()' is a no-op */
		saved->@en_size@ = 0;
	} else {
		if unlikely(saved->@en_size@ > @_EXCEPTION_NESTING_DATA_SIZE@)
			saved->@en_size@ = @_EXCEPTION_NESTING_DATA_SIZE@;
		memcpy(&saved->@en_state@, info, saved->@en_size@);
		info->@ei_code@   = @EXCEPT_CODEOF@(@E_OK@);
		++info->@ei_nesting@;
	}
}

@@>> except_nesting_end(3)
@@End a nested TRY-block. (i.e. inside of another EXCEPT block)
[[guard, no_local, decl_prefix(
#ifndef __EXCEPT_NESTING_END_CC
#define __EXCEPT_NESTING_END_CC __LIBKCALL
#endif /* !__EXCEPT_NESTING_END_CC */
), nothrow, kernel, cc(__EXCEPT_NESTING_END_CC)]]
[[decl_include("<kos/bits/exception_nest.h>")]]
[[impl_include("<hybrid/__assert.h>")]]
[[impl_include("<kos/bits/exception_info.h>")]]
void except_nesting_end([[in]] struct _exception_nesting_data const *__restrict saved) {
	struct exception_info *info;
	if unlikely(!saved->@en_size@)
		return; /* No-op */
	info = except_info();
	__hybrid_assertf(info->@ei_nesting@ != 0,
	                 "Error-nesting stack is empty");
	--info->@ei_nesting@;
	__hybrid_assertf(saved->@en_data@.@e_code@ != @EXCEPT_CODEOF@(@E_OK@),
	                 "No saved exception in `except_nesting_end()'");
	if (info->@ei_code@ == @EXCEPT_CODEOF@(@E_OK@)) {
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
		 * Equivalent[EQ]:
		 * [ 1] foo();                                // [ 2]
		 * [ 2] if (EXCEPTION_THROWN) {
		 * [ 3]     __cxa_begin_catch();              // [ 3]
		 * [ 4]     struct _exception_nesting_data nest;
		 * [ 5]     except_nesting_begin(&nest);
		 * [ 6]     bar();                            // [ 5]
		 * [ 7]     if (EXCEPTION_THROWN) {
		 * [ 8]         __cxa_begin_catch();          // [ 6]
		 * [ 9]         foobar();                     // [ 7]
		 * [10]         except_rethrow();             // [ 8]
		 * [11]         __cxa_end_catch();            // [ 9]
		 * [12]         except_nesting_end(&nest);
		 * [13]     } else {
		 * [14]         except_nesting_end(&nest);
		 * [15]         except_rethrow();             // [10]
		 * [16]     }
		 * [17]     __cxa_end_catch();                // [11]
		 * [18] }
		 *
		 * We  get  here  from  EQ[12],  which  is  followed  by  EQ[17], which
		 * would normally  delete the  exception  because it  wasn't  re-thrown
		 * from anywhere. But if you think of all of the possible constellation
		 * where this function  might be  called, in  all cases  where we  know
		 * that there's currently an active exception (i.e. `ei_code != E_OK'),
		 * it's always  acceptable  to  set  the RETHROW  flag  for  the  outer
		 * call to `__cxa_end_catch()' (on line EQ[17])
		 */
		info->@ei_flags@ |= @EXCEPT_FRETHROW@;
		/* Select the more important exception. */
		if (except_priority(saved->@en_data@.@e_code@) >=
		    except_priority(info->@ei_code@))
			goto restore_saved_exception;
		/* Keep the newly set exception. */
	}
}

%{

/* Nested exception support */
#ifdef __cplusplus
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
}


%
%{
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
}
%#if !defined(NDEBUG) && !defined(NDEBUG_EXCEPT) && !defined(NDEBUG_EXCEPT_NESTING)
%[declare_kernel_export(
	"_except_badusage_no_nesting",
	"_except_check_no_nesting",
)]

@@>> _except_badusage_no_nesting(3)
@@Assertion check handler for missing `TRY' nesting
[[cold, userimpl, noreturn, nothrow, impl_include("<hybrid/__assert.h>")]]
void _except_badusage_no_nesting(void) {
	__hybrid_assertion_failed("Recursive `TRY' isn't nested; use `NESTED_TRY' instead");
}

@@>> _except_check_no_nesting(3)
@@Assert that a TRY-block is currently allowed (iow: that no error is active)
[[userimpl, nothrow, impl_include("<kos/bits/fastexcept.h>")]]
[[requires_function(except_active)]]
void _except_check_no_nesting(void) {
@@pp_ifdef __arch_except_active@@
	if (__arch_except_active())
@@pp_else@@
	if (except_active())
@@pp_endif@@
	{
		_except_badusage_no_nesting();
	}
}

%[insert:pp_if($has_function(_except_check_no_nesting))]
%{
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
}
%[insert:pp_endif]
%#else /* !NDEBUG && !NDEBUG_EXCEPT && !NDEBUG_EXCEPT_NESTING */
/* Turn these into no-ops under this configuration. */
%#define _except_badusage_no_nesting() __builtin_unreachable()
%#define _except_check_no_nesting()    (void)0
%#endif /* NDEBUG || NDEBUG_EXCEPT || NDEBUG_EXCEPT_NESTING */


%
%{
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
}
%#endif /* __CC__ */
%{

}
