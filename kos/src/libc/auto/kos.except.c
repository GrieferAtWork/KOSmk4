/* HASH CRC-32:0x17367f5f */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#include "format-printer.h"
#include "string.h"

DECL_BEGIN

#include <errno.h>
#include <signal.h>
#include "../libc/dl.h" /* dlopen(), dlclose() */
#include <asm/os/errno.h>
#include <hybrid/host.h>
#include <kos/bits/exception_data.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/except/reason/net.h>
#include <kos/except/reason/noexec.h>
#include <kos/except/codes.h>
#include <kos/kernel/handle.h>
/* >> except_as_errno(3)
 * Transform the  given exception  into  a posix  errno  value.
 * When no special errno is defined for `data', return `EPERM'. */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_PURE WUNUSED ATTR_IN(1) errno_t
NOTHROW_NCX(LIBKCALL libc_except_as_errno)(struct exception_data const *__restrict self) {
#ifdef EPERM
	errno_t result = EPERM;
#else /* EPERM */
	errno_t result = 1;
#endif /* !EPERM */
	switch (self->e_class) {
/*[[[deemon
local final DEFAULT_ERRNO = "EPERM";
import * from deemon;
import * from ....misc.libgen.exceptinfo;
function isCustomErrnoExpr(s) -> s !is none && s != "DEFAULT_ERRNO";

@@Returns (formattedExpr, listOfMacrosThatMustBeDefined)
function formatErrnoExpr(cls: ExceptClass): (string, {string...}) {
	local expr = File.Writer();
	cls.printErrnoExpr(expr, cbField: name ->
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
	case E_BADALLOC:
#ifdef ENOMEM
		result = ENOMEM;
#endif /* ENOMEM */
		switch(self->e_subclass) {
#ifdef EEXIST
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_ADDRESS_ALREADY_EXISTS)):
			result = EEXIST;
			break;
#endif /* EEXIST */
#ifdef EMFILE
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS)):
			result = EMFILE;
			break;
#endif /* EMFILE */
#ifdef ENFILE
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)):
			result = ENFILE;
			break;
#endif /* ENFILE */
#ifdef EADDRNOTAVAIL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_PORT_NUMBERS)):
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

#ifdef EPIPE
	case E_BROKEN_PIPE:
		result = EPIPE;
		break;
#endif /* EPIPE */

	case E_BUFFER_TOO_SMALL:
#ifdef ERANGE
		result = ERANGE;
#endif /* ERANGE */
		switch(self->e_subclass) {
#ifdef EINVAL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(_E_BUFFER_TOO_SMALL_EINVAL)):
			result = EINVAL;
			break;
#endif /* EINVAL */
		default: break;
		}
		break;

#ifdef EINVAL
	case E_DIVIDE_BY_ZERO:
		result = EINVAL;
		break;
#endif /* EINVAL */

	case E_FSERROR:
		switch(self->e_subclass) {
#ifdef ENOENT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_DELETED)):
			result = ENOENT;
			break;
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_FILE_NOT_FOUND)):
			result = ENOENT;
			break;
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_PATH_NOT_FOUND)):
			result = ENOENT;
			break;
#endif /* ENOENT */
#ifdef ENAMETOOLONG
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_ILLEGAL_PATH)):
			result = ENAMETOOLONG;
			break;
#endif /* ENAMETOOLONG */
#ifdef ENOTDIR
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_NOT_A_DIRECTORY)):
			result = ENOTDIR;
			break;
#endif /* ENOTDIR */
#ifdef ELOOP
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS)):
			result = ELOOP;
			break;
#endif /* ELOOP */
#ifdef EACCES
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_ACCESS_DENIED)):
			result = EACCES;
			break;
#endif /* EACCES */
#ifdef ENOSPC
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_DISK_FULL)):
			result = ENOSPC;
			break;
#endif /* ENOSPC */
#ifdef EROFS
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_READONLY)):
			result = EROFS;
			break;
#endif /* EROFS */
#ifdef EMLINK
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_TOO_MANY_HARD_LINKS)):
			result = EMLINK;
			break;
#endif /* EMLINK */
#if defined(EPERM) && defined(EISDIR)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_IS_A_DIRECTORY)):
			result = self->e_args.e_fserror.f_is_a_directory.iad_action_context == E_FILESYSTEM_IS_A_DIRECTORY_LINK ? EPERM : EISDIR;
			break;
#endif /* EPERM && EISDIR */
#ifdef ENOENT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_NOT_A_SYMBOLIC_LINK)):
			result = ENOENT;
			break;
#endif /* ENOENT */
#ifdef ELOOP
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_IS_A_SYMBOLIC_LINK)):
			result = ELOOP;
			break;
#endif /* ELOOP */
#ifdef EEXIST
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_FILE_ALREADY_EXISTS)):
			result = EEXIST;
			break;
#endif /* EEXIST */
#ifdef ENOTEMPTY
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_DIRECTORY_NOT_EMPTY)):
			result = ENOTEMPTY;
			break;
#endif /* ENOTEMPTY */
#ifdef EXDEV
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_CROSS_DEVICE_LINK)):
			result = EXDEV;
			break;
#endif /* EXDEV */
#ifdef EINVAL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_DIRECTORY_MOVE_TO_CHILD)):
			result = EINVAL;
			break;
#endif /* EINVAL */
#ifdef ENOTBLK
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_MOUNT_UNSUPPORTED_DEVICE)):
			result = ENOTBLK;
			break;
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_MOUNT_NEEDS_DEVICE)):
			result = ENOTBLK;
			break;
#endif /* ENOTBLK */
#ifdef ENODEV
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_WRONG_FILE_SYSTEM)):
			result = ENODEV;
			break;
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_UNKNOWN_FILE_SYSTEM)):
			result = ENODEV;
			break;
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_CORRUPTED_FILE_SYSTEM)):
			result = ENODEV;
			break;
#endif /* ENODEV */
#ifdef EBUSY
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_PATH_ALREADY_MOUNTED)):
			result = EBUSY;
			break;
#endif /* EBUSY */
#ifdef EINVAL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_NOT_A_MOUNTING_POINT)):
			result = EINVAL;
			break;
#endif /* EINVAL */
#ifdef EBUSY
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_IS_A_MOUNTING_POINT)):
			result = EBUSY;
			break;
#endif /* EBUSY */
#ifdef EFBIG
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_FILE_TOO_BIG)):
			result = EFBIG;
			break;
#endif /* EFBIG */
#if defined(ESPIPE) && defined(EINVAL) && defined(ENOTDIR) && defined(ENODEV) && defined(EROFS) && defined(EPERM)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION)):
			result = (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_SEEK || self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_PREAD ||
			         self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_PWRITE) ? ESPIPE :
			        (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READ || self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_WRITE ||
			         self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_SYNC) ? EINVAL :
			        (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READDIR) ? ENOTDIR :
			        (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_MMAP || self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_ALLOCATE) ? ENODEV :
			        (self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_CREAT) ? EROFS :
			        EPERM;
			break;
#endif /* ESPIPE && EINVAL && ENOTDIR && ENODEV && EROFS && EPERM */
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

	case E_ILLEGAL_OPERATION:
#if defined(ENXIO) && defined(EPERM)
		result = self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK ? ENXIO : EPERM;
#endif /* ENXIO && EPERM */
		switch(self->e_subclass) {
#if defined(EINVAL) && defined(ELOOP)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_REFERENCE_LOOP)):
			result = self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP ? EINVAL : ELOOP;
			break;
#endif /* EINVAL && ELOOP */
#if defined(ENOTCONN) && defined(EDESTADDRREQ) && defined(EISCONN) && defined(EINVAL)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_BECAUSE_NOT_READY)):
			result = (self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED) ? ENOTCONN :
			        (self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED) ? EDESTADDRREQ :
			        (self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED) ? EISCONN :
			         EINVAL;
			break;
#endif /* ENOTCONN && EDESTADDRREQ && EISCONN && EINVAL */
#if defined(ENOTTY) && defined(EPERM)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_BECAUSE_GROUPING)):
			result = (self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION ||
			         self->e_args.e_illegal_operation.io_reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION) ? ENOTTY :
			         EPERM;
			break;
#endif /* ENOTTY && EPERM */
#ifdef ENXIO
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_IO_OPERATION)):
			result = ENXIO;
			break;
#endif /* ENXIO */
#ifdef ENOMEM
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED)):
			result = ENOMEM;
			break;
#endif /* ENOMEM */
#ifdef EINVAL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_OPERATION)):
			result = EINVAL;
			break;
#endif /* EINVAL */
		default: break;
		}
		break;

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
#if defined(EPERM) && defined(EINVAL)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE)):
			result = (self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID ||
			         self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID) ? EPERM : EINVAL;
			break;
#endif /* EPERM && EINVAL */
#if defined(EAFNOSUPPORT) && defined(ESOCKTNOSUPPORT) && defined(EPROTONOSUPPORT) && defined(EINVAL)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_ARGUMENT_UNKNOWN_COMMAND)):
			result = self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY ? EAFNOSUPPORT :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE ? ESOCKTNOSUPPORT :
			        self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL ? EPROTONOSUPPORT :
			        EINVAL;
			break;
#endif /* EAFNOSUPPORT && ESOCKTNOSUPPORT && EPROTONOSUPPORT && EINVAL */
#ifdef ENOPROTOOPT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_ARGUMENT_SOCKET_OPT)):
			result = ENOPROTOOPT;
			break;
#endif /* ENOPROTOOPT */
#if defined(EAFNOSUPPORT) && defined(EINVAL)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND)):
			result = self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY ? EAFNOSUPPORT : EINVAL;
			break;
#endif /* EAFNOSUPPORT && EINVAL */
		default: break;
		}
		break;

	case E_INVALID_HANDLE:
#ifdef EBADF
		result = EBADF;
#endif /* EBADF */
		switch(self->e_subclass) {
#if defined(EINVAL) && defined(EBADF)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_HANDLE_FILE)):
			result = self->e_args.e_invalid_handle.ih_file.f_reason == E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD ? EINVAL : EBADF;
			break;
#endif /* EINVAL && EBADF */
#if defined(ENOTSOCK) && defined(EBADFD)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_HANDLE_FILETYPE)):
			result = self->e_args.e_invalid_handle.ih_filetype.f_needed_handle_type == HANDLE_TYPE_SOCKET ? ENOTSOCK : EBADFD;
			break;
#endif /* ENOTSOCK && EBADFD */
#if defined(EACCES) && defined(EINVAL)
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_HANDLE_OPERATION)):
			result = self->e_args.e_invalid_handle.ih_operation.o_op == E_INVALID_HANDLE_OPERATION_MMAP ? EACCES : EINVAL;
			break;
#endif /* EACCES && EINVAL */
#ifdef EOPNOTSUPP
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_INVALID_HANDLE_NET_OPERATION)):
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
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_HOST_UNREACHABLE)):
			result = EHOSTUNREACH;
			break;
#endif /* EHOSTUNREACH */
#ifdef EADDRINUSE
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_ADDRESS_IN_USE)):
			result = EADDRINUSE;
			break;
#endif /* EADDRINUSE */
#ifdef EMSGSIZE
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_MESSAGE_TOO_LONG)):
			result = EMSGSIZE;
			break;
#endif /* EMSGSIZE */
#ifdef ECONNABORTED
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_CONNECTION_ABORT)):
			result = ECONNABORTED;
			break;
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_CONNECTION_REFUSED)):
			result = ECONNREFUSED;
			break;
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_CONNECTION_RESET)):
			result = ECONNRESET;
			break;
#endif /* ECONNRESET */
#ifdef ETIMEDOUT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_TIMEOUT)):
			result = ETIMEDOUT;
			break;
#endif /* ETIMEDOUT */
#ifdef ENETUNREACH
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_UNREACHABLE)):
			result = ENETUNREACH;
			break;
#endif /* ENETUNREACH */
#ifdef EADDRNOTAVAIL
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_ADDRESS_NOT_AVAILABLE)):
			result = EADDRNOTAVAIL;
			break;
#endif /* EADDRNOTAVAIL */
#ifdef EPIPE
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NET_SHUTDOWN)):
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

#ifdef ENOSYS
	case E_NOT_IMPLEMENTED:
		result = ENOSYS;
		break;
#endif /* ENOSYS */

#ifdef ENODEV
	case E_NO_DEVICE:
		result = ENODEV;
		break;
#endif /* ENODEV */

	case E_NO_SUCH_OBJECT:
#ifdef ENODATA
		result = ENODATA;
#endif /* ENODATA */
		switch(self->e_subclass) {
#ifdef ENODEV
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_NO_CTTY)):
			result = ENODEV;
			break;
#endif /* ENODEV */
		default: break;
		}
		break;

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

#ifdef ENODEV
	case E_UNSUPPORTED_DEVICE:
		result = ENODEV;
		break;
#endif /* ENODEV */

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
#include <asm/os/siginfo.h>
#include <asm/os/signal.h>
#include <bits/os/siginfo.h>
/* >> except_as_signal(3)
 * Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false'
 * is returned. */
INTERN ATTR_SECTION(".text.crt.except.io.utility") WUNUSED ATTR_IN(1) ATTR_OUT(2) bool
NOTHROW_NCX(LIBKCALL libc_except_as_signal)(struct exception_data const *__restrict self,
                                            struct __siginfo_struct *__restrict result) {
	except_code_t code = self->e_code;
	libc_bzero(result, sizeof(*result));
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
	switch (EXCEPT_CLASS(code)) {

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
		case EXCEPT_CODEOF(E_SEGFAULT_READONLY):
		case EXCEPT_CODEOF(E_SEGFAULT_NOTREADABLE):
		case EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE):
			result->si_code = SEGV_ACCERR;
			break;
#endif /* SEGV_ACCERR */

#if defined(SIGBUS) && defined(BUS_OBJERR)
		case EXCEPT_CODEOF(E_SEGFAULT_NOTATOMIC):
			result->si_signo = SIGBUS;
			result->si_code  = BUS_OBJERR;
			break;
#endif /* SIGBUS && BUS_OBJERR */

#if defined(SIGBUS) && defined(BUS_ADRALN)
		case EXCEPT_CODEOF(E_SEGFAULT_UNALIGNED):
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
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND):
			result->si_code = ILL_ILLOPN;
#ifdef ILL_ILLADR
			if (self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY ||
			    self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER)
				result->si_code = ILL_ILLADR;
#endif /* ILL_ILLADR */
			break;
#endif /* ILL_ILLOPN */

#ifdef ILL_PRVOPC
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE):
			result->si_code = ILL_PRVOPC;
			break;
#endif /* ILL_PRVOPC */

#ifdef ILL_ILLOPN
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER):
			result->si_code = ILL_ILLOPN;
#ifdef ILL_PRVREG
			if (self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV ||
			    self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV)
				result->si_code = ILL_PRVREG;
#endif /* ILL_PRVREG */
			break;
#endif /* ILL_ILLOPN */

#if defined(ILL_ILLADR) && defined(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT)
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT):
			result->si_code = ILL_ILLADR;
			break;
#endif /* ILL_ILLADR && E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

#ifdef ILL_ILLOPC
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE):
#ifdef E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX):
#endif /* E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX */
#ifdef E_ILLEGAL_INSTRUCTION_X86_TOO_LONG
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_TOO_LONG):
#endif /* E_ILLEGAL_INSTRUCTION_X86_TOO_LONG */
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE):
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
	result->si_errno = libc_except_as_errno(self);
	return true;
}
/* >> except_name(3)
 * Return the name of the  given error, or `NULL'  if
 * unknown. This name is one of the `E_*' identifier.
 * E.g.: `except_name(EXCEPT_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_CONST WUNUSED char const *
NOTHROW(LIBKCALL libc_except_name)(except_code_t code) {
	except_class_t err_class       = EXCEPT_CLASS(code);
	except_subclass_t err_subclass = EXCEPT_SUBCLASS(code);
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
		result = libc_strend(result) + 1;
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
		result = libc_strend(result) + 1;
	}
	if (!*result)
		result = NULL;
	return result;
#endif /* !... */
/*[[[end]]]*/
}
/* >> except_priority(3)
 * Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBKCALL libc_except_priority)(except_code_t code) {
	except_class_t code_class = EXCEPT_CLASS(code);
	if (EXCEPTCLASS_ISRTLPRIORITY(code_class))
		return 4 + (code_class - EXCEPTCLASS_RTL_MIN);
	if (EXCEPTCLASS_ISHIGHPRIORITY(code_class))
		return 3;
	if (code_class != EXCEPT_CLASS(EXCEPT_CODEOF(E_OK))) {
		if (!EXCEPTCLASS_ISLOWPRIORITY(code_class))
			return 2;
		return 1;
	}
	return 0;
}
#include <bits/crt/inttypes.h>
#include <libregdump/register.h>
#include <dlfcn.h>
#include <libansitty/ctl.h>
#if defined(__i386__) || defined(__x86_64__)
#include <asm/registers.h>
#endif /* __i386__ || __x86_64__ */
/* >> except_print_short_description(3)
 * Print a short, single-line (without trailing linefeed) description  of
 * the given error `data', including the error code, name and for certain
 * errors, prominent error arguments.
 * @param: flags: Set of `EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_*'
 * @return: * : The usual pformatprinter-compatible return value */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_IN(3) NONNULL((1)) ssize_t
NOTHROW_NCX(LIBKCALL libc_except_print_short_description)(pformatprinter printer,
                                                          void *arg,
                                                          struct exception_data const *data,
                                                          uintptr_t flags) {
#ifndef PRIxPTR
#ifdef __PRIP_PREFIX
#define PRIxPTR __PRIP_PREFIX "x"
#else /* __PRIP_PREFIX */
#define PRIxPTR "zx"
#endif /* !__PRIP_PREFIX */
#endif /* !PRIxPTR */
#define FMT(tty, notty) (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY ? tty : notty)
	ssize_t temp, result = 0;
	result = libc_format_printf(printer, arg,
	                       FMT("exception "
	                           AC_WHITE("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x") ":"
	                           AC_WHITE("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                           "exception "
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x:"
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                       data->e_class, data->e_subclass);
	if unlikely(result < 0)
		goto done;
	{
		char const *name;
		char const *errno_name;
		name = libc_except_name(data->e_code);
		errno_name = libc_strerrorname_np(libc_except_as_errno(data));
		if (name) {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [" AC_WHITE("%s") "%s" AC_WHITE("%s") "]",
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
	switch (data->e_class) {

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_BADALLOC)):
		switch (data->e_subclass) {

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY)):
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY)):
			temp = libc_format_printf(printer, arg,
			                     FMT(" [num_bytes:" AC_WHITE("%#" PRIxPTR) "]",
			                         " [num_bytes:%#" PRIxPTR "]"),
			                     data->e_args.e_badalloc.ba_insufficient_heap_memory);
			break;

		default:
			break;
		}
		break;

	/* TODO: More error classes */

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_SEGFAULT)): {
		temp = libc_format_printf(printer, arg,
#if defined(__i386__) || defined(__x86_64__)
		                     FMT(" [cr2:" AC_WHITE("%p") "," AC_WHITE("%c%c%c%c%c%c") "]",
		                         " [cr2:%p,%c%c%c%c%c%c]")
#else /* __i386__ || __x86_64__ */
		                     FMT(" [addr:" AC_WHITE("%p") "," AC_WHITE("%c%c%c%c%c%c") "]",
		                         " [addr:%p,%c%c%c%c%c%c]")
#endif /* !__i386__ && !__x86_64__ */
		                     ,
		                     data->e_args.e_segfault.s_addr,
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_FAULT ? 'f' : '-',
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_WRITING ? 'w' : '-',
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_USERCODE ? 'u' : '-',
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_NONCANON ? 'c' : '-',
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_EXEC ? 'x' : '-',
		                     data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_VIO ? 'v' : '-');
	}	break;

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION)): {
#if defined(__i386__) || defined(__x86_64__)
		uintptr_t opcode, opno;
		opcode = data->e_args.e_illegal_instruction.ii_opcode;
		opno   = E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(opcode);
		if (opno <= 0xff) {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#.2" PRIxPTR),
			                         " [opcode:%#.2" PRIxPTR),
			                     opno);
		} else if (opno <= 0xffff) {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#.4" PRIxPTR),
			                         " [opcode:%#.4" PRIxPTR),
			                     opno);
		} else {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#" PRIxPTR),
			                         " [opcode:%#" PRIxPTR),
			                     opno);
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(opcode)) {
			temp = libc_format_printf(printer, arg, "/%u", (unsigned int)E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(opcode));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = (*printer)(arg, "]", 1);
#else /* __i386__ || __x86_64__ */
		uintptr_t opcode = data->e_args.e_illegal_instruction.ii_opcode;
		if (opcode <= 0xff) {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#.2" PRIxPTR) "]",
			                         " [opcode:%#.2" PRIxPTR "]"),
			                     opcode);
		} else if (opcode <= 0xffff) {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#.4" PRIxPTR) "]",
			                         " [opcode:%#.4" PRIxPTR "]"),
			                     opcode);
		} else {
			temp = libc_format_printf(printer, arg,
			                     FMT(" [opcode:" AC_WHITE("%#" PRIxPTR) "]",
			                         " [opcode:%#" PRIxPTR "]"),
			                     opcode);
		}
#endif /* !__i386__ && !__x86_64__ */
		if unlikely(temp < 0)
			goto err;
		result += temp;
		switch (data->e_subclass) {

#ifdef E_ILLEGAL_INSTRUCTION_X86_INTERRUPT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT)):
			temp = libc_format_printf(printer, arg,
			                     FMT(" [int:" AC_WHITE("%#.2" PRIxPTR) ","
			                                  AC_WHITE("%#" PRIxPTR) ","
			                                  "seg:" AC_WHITE("%#" PRIxPTR) "]",
			                         " [int:%#.2" PRIxPTR ",%#" PRIxPTR ",seg:%#" PRIxPTR "]"),
			                     data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_intno,
			                     data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_ecode,
			                     data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_segval);
			break;
#endif /* E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND)): {
			char const *what_name;
			switch (data->e_args.e_illegal_instruction.ii_bad_operand.bo_what) {

			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY:
			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER:
				what_name = "addrmode";
				break;

			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE:
				what_name = "value";
				break;

			default:
				what_name = NULL;
				break;
			}
			if (what_name) {
				temp = libc_format_printf(printer, arg,
				                     FMT(" [what=" AC_WHITE("%s") "]",
				                         " [what=%s]"),
				                     what_name);
			} else {
				temp = libc_format_printf(printer, arg,
				                     FMT(" [what=" AC_WHITE("?(%#" PRIxPTR ")") "]",
				                         " [what=?(%#" PRIxPTR ")]"),
				                     data->e_args.e_illegal_instruction.ii_bad_operand.bo_what);
			}
		}	break;

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER)): {
			char const *what;
			uintptr_t regno;
			switch (data->e_args.e_illegal_instruction.ii_register.r_how) {
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDINV: what = "rdinv"; break; /* Read from invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV: what = "rdprv"; break; /* Read from privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRINV: what = "wrinv"; break; /* Write to invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV: what = "wrprv"; break; /* Write to privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD: what = "wrbad"; break; /* Bad value written to register */
			default: what = NULL; break;
			}
			if (what) {
				temp = libc_format_printf(printer, arg, " [%s:", what);
			} else {
				temp = libc_format_printf(printer, arg, " [?(%#" PRIxPTR "):",
				                     data->e_args.e_illegal_instruction.ii_register.r_how);
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
			regno = data->e_args.e_illegal_instruction.ii_register.r_regno;
#if defined(__i386__) || defined(__x86_64__)
			if (regno == X86_REGISTER_XCR || regno == X86_REGISTER_PCR || regno == X86_REGISTER_MSR) {
				char extname[4];
				extname[0] = 'x';
				extname[1] = 'c';
				extname[2] = 'r';
				extname[3] = 0;
				if (regno == X86_REGISTER_PCR) {
					extname[0] = 'p';
				} else if (regno == X86_REGISTER_MSR) {
					extname[0] = 'm';
					extname[1] = 's';
				}
				temp = libc_format_printf(printer, arg,
				                     FMT(AC_WHITE("%s(%#" PRIxPTR ")") "," AC_WHITE("%#" __PRI8_PREFIX "x") "]",
				                         "%s(%#" PRIxPTR "),%#" __PRI8_PREFIX "x]"),
				                     extname, data->e_args.e_illegal_instruction.ii_register.r_offset,
				                     (uint64_t)data->e_args.e_illegal_instruction.ii_register.r_regval |
				                     (uint64_t)data->e_args.e_illegal_instruction.ii_register.r_regval2 << 32);
			} else
#endif /* __i386__ || __x86_64__ */
			{
				if (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY) {
					static char const beginfg[] = AC_FG(ANSITTY_CL_WHITE);
					temp = (*printer)(arg, beginfg, COMPILER_STRLEN(beginfg));
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
#ifdef LIBREGDUMP_WANT_PROTOTYPES
				temp = regdump_register_name(printer, arg, regno);
#else /* LIBREGDUMP_WANT_PROTOTYPES */
#if defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)
				void *libregdump;
#ifdef RTLD_LOCAL
				libregdump = dlopen(LIBREGDUMP_LIBRARY_NAME, RTLD_LOCAL);
#else /* RTLD_LOCAL */
				libregdump = dlopen(LIBREGDUMP_LIBRARY_NAME, 0);
#endif /* !RTLD_LOCAL */
				if (libregdump != NULL) {
					PREGDUMP_REGISTER_NAME pdyn_regdump_register_name;
					*(void **)&pdyn_regdump_register_name = dlsym(libregdump, "regdump_register_name");
					if unlikely(!pdyn_regdump_register_name) {
#ifdef __CRT_HAVE_dlclose
						dlclose(libregdump);
#endif /* __CRT_HAVE_dlclose */
						goto print_generic_register_name;
					}
					temp = (*pdyn_regdump_register_name)(printer, arg, regno);
#ifdef __CRT_HAVE_dlclose
					dlclose(libregdump);
#endif /* __CRT_HAVE_dlclose */
				} else
#endif /* __CRT_HAVE_dlopen && __CRT_HAVE_dlsym */
				{
print_generic_register_name:
					temp = libc_format_printf(printer, arg, "reg.%#" PRIxPTR, regno);
				}
#endif /* !LIBREGDUMP_WANT_PROTOTYPES */
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if (flags & EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY) {
					static char const endfg[] = AC_FGDEF;
					temp = (*printer)(arg, endfg, COMPILER_STRLEN(endfg));
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
				if (data->e_args.e_illegal_instruction.ii_register.r_regval != 0 ||
				    (data->e_args.e_illegal_instruction.ii_register.r_how != E_ILLEGAL_INSTRUCTION_REGISTER_RDINV &&
				     data->e_args.e_illegal_instruction.ii_register.r_how != E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV)) {
					temp = libc_format_printf(printer, arg,
					                     FMT("," AC_WHITE("%#" PRIxPTR) "]",
					                         ",%#" PRIxPTR "]"),
					                     data->e_args.e_illegal_instruction.ii_register.r_regval);
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
#include <kos/bits/exception_info.h>
/* >> except_nesting_begin(3)
 * Begin a nested  TRY-block. (i.e. inside  of another EXCEPT  block)
 * Don't call this function directly; use `NESTED_EXCEPTION' instead. */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_INOUT(1) void
NOTHROW(__EXCEPT_NESTING_BEGIN_CC libc_except_nesting_begin)(struct _exception_nesting_data *__restrict saved) {
	struct exception_info *info = libc_except_info();
	if (info->ei_code == EXCEPT_CODEOF(E_OK)) {
		/* Not inside of  a catch-block (ignore  the nesting  request)
		 * This  can happen if  the caller is only  using the nest for
		 * safety (in case a sub-function  needs to be able to  handle
		 * its  own  exceptions, but  may  be called  from  an unaware
		 * exception  handler),  or  is  using  more  than  one  nest.
		 * In all of these cases, just ignore the nest, and also  make
		 * it so that the associated `except_nesting_end()' is a no-op */
		saved->en_size = 0;
	} else {
		if unlikely(saved->en_size > _EXCEPTION_NESTING_DATA_SIZE)
			saved->en_size = _EXCEPTION_NESTING_DATA_SIZE;
		libc_memcpy(&saved->en_state, info, saved->en_size);
		info->ei_code   = EXCEPT_CODEOF(E_OK);
		++info->ei_nesting;
	}
}
#include <hybrid/__assert.h>
/* >> except_nesting_end(3)
 * End a nested TRY-block. (i.e. inside of another EXCEPT block) */
INTERN ATTR_SECTION(".text.crt.except.io.utility") ATTR_IN(1) void
NOTHROW(__EXCEPT_NESTING_END_CC libc_except_nesting_end)(struct _exception_nesting_data const *__restrict saved) {
	struct exception_info *info;
	if unlikely(!saved->en_size)
		return; /* No-op */
	info = libc_except_info();
	__hybrid_assertf(info->ei_nesting != 0,
	                 "Error-nesting stack is empty");
	--info->ei_nesting;
	__hybrid_assertf(saved->en_data.e_code != EXCEPT_CODEOF(E_OK),
	                 "No saved exception in `except_nesting_end()'");
	if (info->ei_code == EXCEPT_CODEOF(E_OK)) {
		/* No newly thrown exception. (meaning we're currently not propagating
		 * any exceptions, so we also shouldn't try to set the RETHROW  flag!) */
restore_saved_exception:
		libc_memcpy(info, &saved->en_state, saved->en_size);
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
		info->ei_flags |= EXCEPT_FRETHROW;
		/* Select the more important exception. */
		if (libc_except_priority(saved->en_data.e_code) >=
		    libc_except_priority(info->ei_code))
			goto restore_saved_exception;
		/* Keep the newly set exception. */
	}
}

DECL_END

DEFINE_PUBLIC_ALIAS(except_as_errno, libc_except_as_errno);
DEFINE_PUBLIC_ALIAS(except_as_signal, libc_except_as_signal);
DEFINE_PUBLIC_ALIAS(except_name, libc_except_name);
DEFINE_PUBLIC_ALIAS(except_priority, libc_except_priority);
DEFINE_PUBLIC_ALIAS(except_print_short_description, libc_except_print_short_description);
DEFINE_PUBLIC_ALIAS(except_nesting_begin, libc_except_nesting_begin);
DEFINE_PUBLIC_ALIAS(except_nesting_end, libc_except_nesting_end);

#endif /* !GUARD_LIBC_AUTO_KOS_EXCEPT_C */
