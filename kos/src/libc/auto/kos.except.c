/* HASH CRC-32:0x562c50c7 */
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
#ifndef GUARD_LIBC_AUTO_KOS_EXCEPT_C
#define GUARD_LIBC_AUTO_KOS_EXCEPT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.except.h"
#include "../user/string.h"

DECL_BEGIN

#include <errno.h>
#include <signal.h>
#include <asm/os/errno.h>
#include <hybrid/host.h>
#include <kos/bits/exception_data.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/except/reason/net.h>
#include <kos/except/reason/noexec.h>
#include <kos/except/codes.h>
#include <kos/kernel/handle.h>
/* Transform the given exception into a posix errno value */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_PURE WUNUSED NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc_error_as_errno)(struct exception_data const *__restrict self) {
#ifdef EPERM
	errno_t result = EPERM;
#else /* EPERM */
	errno_t result = 1;
#endif /* !EPERM */
	switch (self->e_class) {
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
	case E_BADALLOC:
#ifdef ENOMEM
		result = ENOMEM;
#endif /* ENOMEM */
		switch(self->e_subclass) {
#ifdef EMFILE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS)):
			result = EMFILE;
			break;
#endif /* EMFILE */
#ifdef ENFILE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)):
			result = ENFILE;
			break;
#endif /* ENFILE */
#ifdef EADDRNOTAVAIL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_PORT_NUMBERS)):
			result = EADDRNOTAVAIL;
			break;
#endif /* EADDRNOTAVAIL */
		default: break;
		}
		break;

#ifdef EINVAL
	case E_BREAKPOINT:
		result = EINVAL;
		break;
#endif /* EINVAL */

#ifdef ERANGE
	case E_BUFFER_TOO_SMALL:
		result = ERANGE;
		break;
#endif /* ERANGE */

#ifdef EINVAL
	case E_DIVIDE_BY_ZERO:
		result = EINVAL;
		break;
#endif /* EINVAL */

	case E_FSERROR:
		switch(self->e_subclass) {
#ifdef ENOENT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DELETED)):
			result = ENOENT;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND)):
			result = ENOENT;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_PATH_NOT_FOUND)):
			result = ENOENT;
			break;
#endif /* ENOENT */
#ifdef ENAMETOOLONG
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_ILLEGAL_PATH)):
			result = ENAMETOOLONG;
			break;
#endif /* ENAMETOOLONG */
#ifdef ENOTDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_DIRECTORY)):
			result = ENOTDIR;
			break;
#endif /* ENOTDIR */
#ifdef ELOOP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS)):
			result = ELOOP;
			break;
#endif /* ELOOP */
#ifdef EACCES
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_ACCESS_DENIED)):
			result = EACCES;
			break;
#endif /* EACCES */
#ifdef ENOSPC
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DISK_FULL)):
			result = ENOSPC;
			break;
#endif /* ENOSPC */
#ifdef EROFS
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_READONLY)):
			result = EROFS;
			break;
#endif /* EROFS */
#ifdef EMLINK
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_TOO_MANY_HARD_LINKS)):
			result = EMLINK;
			break;
#endif /* EMLINK */
#ifdef EISDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_DIRECTORY)):
			result = EISDIR;
			break;
#endif /* EISDIR */
#ifdef ENOENT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_SYMBOLIC_LINK)):
			result = ENOENT;
			break;
#endif /* ENOENT */
#ifdef ELOOP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_SYMBOLIC_LINK)):
			result = ELOOP;
			break;
#endif /* ELOOP */
#ifdef EEXIST
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_FILE_ALREADY_EXISTS)):
			result = EEXIST;
			break;
#endif /* EEXIST */
#ifdef ENOTEMPTY
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DIRECTORY_NOT_EMPTY)):
			result = ENOTEMPTY;
			break;
#endif /* ENOTEMPTY */
#ifdef EXDEV
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_CROSS_DEVICE_LINK)):
			result = EXDEV;
			break;
#endif /* EXDEV */
#ifdef EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DIRECTORY_MOVE_TO_CHILD)):
			result = EINVAL;
			break;
#endif /* EINVAL */
#ifdef ENOTBLK
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_BLOCK_DEVICE)):
			result = ENOTBLK;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NO_BLOCK_DEVICE)):
			result = ENOTBLK;
			break;
#endif /* ENOTBLK */
#ifdef ENODEV
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_WRONG_FILE_SYSTEM)):
			result = ENODEV;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_UNKNOWN_FILE_SYSTEM)):
			result = ENODEV;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_CORRUPTED_FILE_SYSTEM)):
			result = ENODEV;
			break;
#endif /* ENODEV */
#ifdef EBUSY
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DEVICE_ALREADY_MOUNTED)):
			result = EBUSY;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_PATH_ALREADY_MOUNTED)):
			result = EBUSY;
			break;
#endif /* EBUSY */
#ifdef EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_MOUNTING_POINT)):
			result = EINVAL;
			break;
#endif /* EINVAL */
#ifdef ENOTDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_MOUNTING_POINT)):
			result = ENOTDIR;
			break;
#endif /* ENOTDIR */
#if defined(ESPIPE) && defined(EINVAL) && defined(EPERM)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION)):
			result = self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_SEEK ? ESPIPE :
			        (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READ || self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_WRITE ||
			         self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_TRUNC || self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READDIR)
			         ? EINVAL : EPERM;
			break;
#endif /* ESPIPE && EINVAL && EPERM */
		default: break;
		}
		break;

#if defined(EPERM) && !defined(__i386__) && !defined(__x86_64__)
	case E_ILLEGAL_INSTRUCTION:
		result = EPERM;
		break;
#endif /* EPERM && !__i386__ && !__x86_64__ */

#if defined(EPERM) && (defined(__i386__) || defined(__x86_64__))
	case E_ILLEGAL_INSTRUCTION:
		result = EPERM;
		break;
#endif /* EPERM && (__i386__ || __x86_64__) */

#ifdef ERANGE
	case E_INDEX_ERROR:
		result = ERANGE;
		break;
#endif /* ERANGE */

#ifdef EACCES
	case E_INSUFFICIENT_RIGHTS:
		result = EACCES;
		break;
#endif /* EACCES */

#ifdef EINTR
	case E_INTERRUPT:
		result = EINTR;
		break;
#endif /* EINTR */

	case E_INVALID_ARGUMENT:
#ifdef EINVAL
		result = EINVAL;
#endif /* EINVAL */
		switch(self->e_subclass) {
#if defined(EAFNOSUPPORT) && defined(ESOCKTNOSUPPORT) && defined(EPROTONOSUPPORT) && defined(EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_UNKNOWN_COMMAND)):
			result = self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY ? EAFNOSUPPORT :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE ? ESOCKTNOSUPPORT :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL ? EPROTONOSUPPORT :
			        EINVAL;
			break;
#endif /* EAFNOSUPPORT && ESOCKTNOSUPPORT && EPROTONOSUPPORT && EINVAL */
#if defined(ENOTCONN) && defined(EDESTADDRREQ) && defined(EISCONN) && defined(ENXIO) && defined(EPIPE) && defined(EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_BAD_STATE)):
			result = self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED ||
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED ||
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED ? ENOTCONN :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED ? EDESTADDRREQ :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED ? EISCONN :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS ? ENXIO :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS ? EPIPE :
			        EINVAL;
			break;
#endif /* ENOTCONN && EDESTADDRREQ && EISCONN && ENXIO && EPIPE && EINVAL */
#ifdef ENOPROTOOPT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_SOCKET_OPT)):
			result = ENOPROTOOPT;
			break;
#endif /* ENOPROTOOPT */
#if defined(EAFNOSUPPORT) && defined(EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND)):
			result = self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY ? EAFNOSUPPORT : EINVAL;
			break;
#endif /* EAFNOSUPPORT && EINVAL */
		default: break;
		}
		break;

#ifdef EPERM
	case E_INVALID_CONTEXT:
		result = EPERM;
		break;
#endif /* EPERM */

	case E_INVALID_HANDLE:
#ifdef EBADF
		result = EBADF;
#endif /* EBADF */
		switch(self->e_subclass) {
#if defined(ENOTSOCK) && defined(EBADFD)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_FILETYPE)):
			result = self->e_args.e_invalid_handle.ih_filetype.f_needed_handle_type == HANDLE_TYPE_SOCKET ? ENOTSOCK : EBADFD;
			break;
#endif /* ENOTSOCK && EBADFD */
#ifdef EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_OPERATION)):
			result = EINVAL;
			break;
#endif /* EINVAL */
#ifdef EOPNOTSUPP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_NET_OPERATION)):
			result = EOPNOTSUPP;
			break;
#endif /* EOPNOTSUPP */
		default: break;
		}
		break;

#ifdef EIO
	case E_IOERROR:
		result = EIO;
		break;
#endif /* EIO */

	case E_NET_ERROR:
		switch(self->e_subclass) {
#ifdef EHOSTUNREACH
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_HOST_UNREACHABLE)):
			result = EHOSTUNREACH;
			break;
#endif /* EHOSTUNREACH */
#ifdef EADDRINUSE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_ADDRESS_IN_USE)):
			result = EADDRINUSE;
			break;
#endif /* EADDRINUSE */
#ifdef EMSGSIZE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_MESSAGE_TOO_LONG)):
			result = EMSGSIZE;
			break;
#endif /* EMSGSIZE */
#ifdef ECONNABORTED
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_ABORT)):
			result = ECONNABORTED;
			break;
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_REFUSED)):
			result = ECONNREFUSED;
			break;
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_RESET)):
			result = ECONNRESET;
			break;
#endif /* ECONNRESET */
#ifdef ETIMEDOUT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_TIMEOUT)):
			result = ETIMEDOUT;
			break;
#endif /* ETIMEDOUT */
#ifdef ENETUNREACH
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_UNREACHABLE)):
			result = ENETUNREACH;
			break;
#endif /* ENETUNREACH */
#ifdef EADDRNOTAVAIL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_ADDRESS_NOT_AVAILABLE)):
			result = EADDRNOTAVAIL;
			break;
#endif /* EADDRNOTAVAIL */
#ifdef EPIPE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_SHUTDOWN)):
			result = EPIPE;
			break;
#endif /* EPIPE */
		default: break;
		}
		break;

#ifdef ENOEXEC
	case E_NOT_EXECUTABLE:
		result = ENOEXEC;
		break;
#endif /* ENOEXEC */

#ifdef EPERM
	case E_NOT_IMPLEMENTED:
		result = EPERM;
		break;
#endif /* EPERM */

#ifdef ENODEV
	case E_NO_DEVICE:
		result = ENODEV;
		break;
#endif /* ENODEV */

#ifdef ENODATA
	case E_NO_SUCH_OBJECT:
		result = ENODATA;
		break;
#endif /* ENODATA */

#ifdef EOK
	case E_OK:
		result = EOK;
		break;
#endif /* EOK */

#ifdef EOVERFLOW
	case E_OVERFLOW:
		result = EOVERFLOW;
		break;
#endif /* EOVERFLOW */

#ifdef ESRCH
	case E_PROCESS_EXITED:
		result = ESRCH;
		break;
#endif /* ESRCH */

#ifdef EFAULT
	case E_SEGFAULT:
		result = EFAULT;
		break;
#endif /* EFAULT */

#ifdef EFAULT
	case E_STACK_OVERFLOW:
		result = EFAULT;
		break;
#endif /* EFAULT */

#ifdef EFAULT
	case E_UNHANDLED_INTERRUPT:
		result = EFAULT;
		break;
#endif /* EFAULT */

#ifdef EILSEQ
	case E_UNICODE_ERROR:
		result = EILSEQ;
		break;
#endif /* EILSEQ */

#ifdef ENOSYS
	case E_UNKNOWN_SYSTEMCALL:
		result = ENOSYS;
		break;
#endif /* ENOSYS */

#ifdef EAGAIN
	case E_WOULDBLOCK:
		result = EAGAIN;
		break;
#endif /* EAGAIN */
/*[[[end]]]*/
	default:
		break;
	}
	return result;
}
#include <asm/siginfo.h>
#include <asm/os/signal.h>
#include <bits/siginfo-struct.h>
/* Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
INTERN ATTR_SECTION(".text.crt.except.io.utility") WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(LIBKCALL libc_error_as_signal)(struct exception_data const *__restrict self,
                                           struct __siginfo_struct *__restrict result) {
	error_code_t code = self->e_code;
	libc_bzero(result, sizeof(*result));
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
	switch (ERROR_CLASS(code)) {

#ifdef SIGQUIT
	case E_EXIT_THREAD:
	case E_EXIT_PROCESS:
		result->si_signo = SIGQUIT;
		break;
#endif /* SIGQUIT */

#if defined(SIGBUS) && defined(BUS_OBJERR)
	case E_IOERROR:
		result->si_signo = SIGBUS;
		result->si_code  = BUS_OBJERR;
		break;
#endif /* SIGBUS && BUS_OBJERR */

#ifdef SIGSYS
	case E_UNKNOWN_SYSTEMCALL:
		result->si_signo   = SIGSYS;
		result->si_syscall = self->e_args.e_unknown_systemcall.us_sysno;
		/* TODO: `si_arch' could be determined by
		 *       `self->e_args.e_unknown_systemcall.us_flags & RPC_SYSCALL_INFO_FMETHOD'! */
		break;
#endif /* SIGSYS */

#if defined(SIGFPE) && defined(FPE_INTDIV)
	case E_DIVIDE_BY_ZERO:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_INTDIV;
		break;
#endif /* SIGFPE && FPE_INTDIV */

#if defined(SIGFPE) && defined(FPE_INTOVF)
	case E_OVERFLOW:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_INTOVF;
		break;
#endif /* SIGFPE && FPE_INTOVF */

#if defined(SIGTRAP) && defined(TRAP_BRKPT)
	case E_BREAKPOINT:
		result->si_signo = SIGTRAP;
		result->si_code  = TRAP_BRKPT;
		break;
#endif /* SIGTRAP && TRAP_BRKPT */

#ifdef SIGINT
	case E_INTERRUPT:
		result->si_signo = SIGINT;
		break;
#endif /* SIGINT */

#if defined(SIGFPE) && defined(FPE_FLTSUB)
	case E_INDEX_ERROR:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_FLTSUB;
		break;
#endif /* SIGFPE && FPE_FLTSUB */

#if defined(SIGSEGV) && defined(SEGV_MAPERR)
	case E_SEGFAULT:
	case E_STACK_OVERFLOW:
		result->si_signo = SIGSEGV;
		result->si_code  = SEGV_MAPERR;
		switch (code) {

#ifdef SEGV_ACCERR
		case ERROR_CODEOF(E_SEGFAULT_READONLY):
		case ERROR_CODEOF(E_SEGFAULT_NOTREADABLE):
		case ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE):
			result->si_code = SEGV_ACCERR;
			break;
#endif /* SEGV_ACCERR */

#if defined(SIGBUS) && defined(BUS_OBJERR)
		case ERROR_CODEOF(E_SEGFAULT_NOTATOMIC):
			result->si_signo = SIGBUS;
			result->si_code  = BUS_OBJERR;
			break;
#endif /* SIGBUS && BUS_OBJERR */

#if defined(SIGBUS) && defined(BUS_ADRALN)
		case ERROR_CODEOF(E_SEGFAULT_UNALIGNED):
			result->si_signo = SIGBUS;
			result->si_code  = BUS_ADRALN;
			break;
#endif /* SIGBUS && BUS_ADRALN */

		default: break;
		}
		result->si_addr  = (void *)self->e_args.e_segfault.s_addr;
		result->si_lower = result->si_addr;
		result->si_upper = result->si_addr;
		break;
#endif /* SIGSEGV && SEGV_MAPERR */

#ifdef SIGILL
	case E_ILLEGAL_INSTRUCTION:
		result->si_signo = SIGILL;
		switch (code) {

#ifdef ILL_ILLOPN
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND):
			result->si_code = ILL_ILLOPN;
#ifdef ILL_ILLADR
			if (self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY ||
			    self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER)
				result->si_code = ILL_ILLADR;
#endif /* ILL_ILLADR */
			break;
#endif /* ILL_ILLOPN */

#ifdef ILL_PRVOPC
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE):
			result->si_code = ILL_PRVOPC;
			break;
#endif /* ILL_PRVOPC */

#ifdef ILL_ILLOPN
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER):
			result->si_code = ILL_ILLOPN;
#ifdef ILL_PRVREG
			if (self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV ||
			    self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV)
				result->si_code = ILL_PRVREG;
#endif /* ILL_PRVREG */
			break;
#endif /* ILL_ILLOPN */

#if defined(ILL_ILLADR) && defined(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT)
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT):
			result->si_code = ILL_ILLADR;
			break;
#endif /* ILL_ILLADR && E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

#ifdef ILL_ILLOPC
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE):
#ifdef E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX):
#endif /* E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX */
#ifdef E_ILLEGAL_INSTRUCTION_X86_TOO_LONG
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_TOO_LONG):
#endif /* E_ILLEGAL_INSTRUCTION_X86_TOO_LONG */
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE):
			result->si_code = ILL_ILLOPC;
			break;
#endif /* ILL_ILLOPC */

		default:
			break;
		}
		break;
#endif /* SIGILL */

	default:
		return false;
	}
	result->si_errno = libc_error_as_errno(self);
	return true;
}
/* Return the name of the given error, or `NULL` if unknown.
 * This name is the same as the `E_*` identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))` -> "E_BADALLOC" */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_CONST WUNUSED char const *
NOTHROW(LIBKCALL libc_error_name)(error_code_t code) {
	error_class_t err_class       = ERROR_CLASS(code);
	error_subclass_t err_subclass = ERROR_SUBCLASS(code);
/*[[[deemon
(printExceptNameFunctionBody from ....misc.libgen.exceptinfo)(
	classVariableName:    "err_class",
	subClassVariableName: "err_subclass");
]]]*/
#if !defined(__i386__) && !defined(__x86_64__)
	static char const e_linear_0000h_000ah[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_INSUFFICIENT_PHYSICAL_MEM"
	"ORY\0E_BADALLOC_INSUFFICIENT_SWAP_SPACE\0E_BADALLOC_INSUFFICIENT_H"
	"ANDLE_NUMBERS\0E_BADALLOC_INSUFFICIENT_HANDLE_RANGE\0E_BADALLOC_IN"
	"SUFFICIENT_DEVICE_NUMBERS\0E_BADALLOC_INSUFFICIENT_INTERRUPT_VECT"
	"ORS\0E_BADALLOC_INSUFFICIENT_PORT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_I"
	"NVALID_ARGUMENT_UNKNOWN_FLAG\0E_INVALID_ARGUMENT_RESERVED_FLAG\0E_"
	"INVALID_ARGUMENT_BAD_FLAG_COMBINATION\0E_INVALID_ARGUMENT_BAD_FLA"
	"G_MASK\0E_INVALID_ARGUMENT_BAD_ALIGNMENT\0E_INVALID_ARGUMENT_BAD_V"
	"ALUE\0E_INVALID_ARGUMENT_RESERVED_ARGUMENT\0E_INVALID_ARGUMENT_UNK"
	"NOWN_COMMAND\0E_INVALID_ARGUMENT_BAD_STATE\0E_INVALID_ARGUMENT_SOC"
	"KET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEMENTED"
	"\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0\1E_INVALID"
	"_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HANDLE_FILETYPE\0E_INVALI"
	"D_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OPERATION\0\1E_WOULDBLOCK\0"
	"E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFORSIGNAL\0\1E_PROCESS_EXI"
	"TED\0\1E_NO_DEVICE\0\1E_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_SU"
	"CH_BLOCKDEVICE\0E_NO_SUCH_PROCESS\0E_NO_SUCH_PIDNS\0E_NO_CTTY\0\1E_IL"
	"LEGAL_OPERATION\0E_ILLEGAL_PROCESS_OPERATION\0\1";
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
		result = (char *)libc_rawmemchr(result, '\1') + 1;
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
		result = libc_strend(result) + 1;
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
		result = libc_strend(result) + 1;
	}
	if (!*result)
		result = NULL;
	return result;
#else /* ... */
	static char const e_linear_0000h_000ah[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_INSUFFICIENT_PHYSICAL_MEM"
	"ORY\0E_BADALLOC_INSUFFICIENT_SWAP_SPACE\0E_BADALLOC_INSUFFICIENT_H"
	"ANDLE_NUMBERS\0E_BADALLOC_INSUFFICIENT_HANDLE_RANGE\0E_BADALLOC_IN"
	"SUFFICIENT_DEVICE_NUMBERS\0E_BADALLOC_INSUFFICIENT_INTERRUPT_VECT"
	"ORS\0E_BADALLOC_INSUFFICIENT_PORT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_I"
	"NVALID_ARGUMENT_UNKNOWN_FLAG\0E_INVALID_ARGUMENT_RESERVED_FLAG\0E_"
	"INVALID_ARGUMENT_BAD_FLAG_COMBINATION\0E_INVALID_ARGUMENT_BAD_FLA"
	"G_MASK\0E_INVALID_ARGUMENT_BAD_ALIGNMENT\0E_INVALID_ARGUMENT_BAD_V"
	"ALUE\0E_INVALID_ARGUMENT_RESERVED_ARGUMENT\0E_INVALID_ARGUMENT_UNK"
	"NOWN_COMMAND\0E_INVALID_ARGUMENT_BAD_STATE\0E_INVALID_ARGUMENT_SOC"
	"KET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEMENTED"
	"\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0\1E_INVALID"
	"_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HANDLE_FILETYPE\0E_INVALI"
	"D_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OPERATION\0\1E_WOULDBLOCK\0"
	"E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFORSIGNAL\0\1E_PROCESS_EXI"
	"TED\0\1E_NO_DEVICE\0\1E_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_SU"
	"CH_BLOCKDEVICE\0E_NO_SUCH_PROCESS\0E_NO_SUCH_PIDNS\0E_NO_CTTY\0\1E_IL"
	"LEGAL_OPERATION\0E_ILLEGAL_PROCESS_OPERATION\0\1";
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
		result = (char *)libc_rawmemchr(result, '\1') + 1;
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
		result = libc_strend(result) + 1;
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
		result = libc_strend(result) + 1;
	}
	if (!*result)
		result = NULL;
	return result;
#endif /* !... */
/*[[[end]]]*/
}

DECL_END

DEFINE_PUBLIC_ALIAS(error_as_errno, libc_error_as_errno);
DEFINE_PUBLIC_ALIAS(error_as_signal, libc_error_as_signal);
DEFINE_PUBLIC_ALIAS(error_name, libc_error_name);

#endif /* !GUARD_LIBC_AUTO_KOS_EXCEPT_C */
