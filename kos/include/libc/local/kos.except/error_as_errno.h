/* HASH CRC-32:0x5cdd01a5 */
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
#ifndef __local_error_as_errno_defined
#define __local_error_as_errno_defined 1
#include <__crt.h>
#include <bits/types.h>
struct exception_data;
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
__NAMESPACE_LOCAL_BEGIN
/* Transform the given exception into a posix errno value */
__LOCAL_LIBC(error_as_errno) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(error_as_errno))(struct exception_data const *__restrict __self) {
#ifdef __EPERM
	__errno_t __result = __EPERM;
#else /* __EPERM */
	__errno_t __result = 1;
#endif /* !__EPERM */
	switch (__self->e_class) {
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
#ifdef __ENOMEM
		__result = __ENOMEM;
#endif /* __ENOMEM */
		switch(__self->e_subclass) {
#ifdef __EMFILE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS)):
			__result = __EMFILE;
			break;
#endif /* __EMFILE */
#ifdef __ENFILE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)):
			__result = __ENFILE;
			break;
#endif /* __ENFILE */
#ifdef __EADDRNOTAVAIL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_BADALLOC_INSUFFICIENT_PORT_NUMBERS)):
			__result = __EADDRNOTAVAIL;
			break;
#endif /* __EADDRNOTAVAIL */
		default: break;
		}
		break;

#ifdef __EINVAL
	case E_BREAKPOINT:
		__result = __EINVAL;
		break;
#endif /* __EINVAL */

#ifdef __ERANGE
	case E_BUFFER_TOO_SMALL:
		__result = __ERANGE;
		break;
#endif /* __ERANGE */

#ifdef __EINVAL
	case E_DIVIDE_BY_ZERO:
		__result = __EINVAL;
		break;
#endif /* __EINVAL */

	case E_FSERROR:
		switch(__self->e_subclass) {
#ifdef __ENOENT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DELETED)):
			__result = __ENOENT;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND)):
			__result = __ENOENT;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_PATH_NOT_FOUND)):
			__result = __ENOENT;
			break;
#endif /* __ENOENT */
#ifdef __ENAMETOOLONG
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_ILLEGAL_PATH)):
			__result = __ENAMETOOLONG;
			break;
#endif /* __ENAMETOOLONG */
#ifdef __ENOTDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_DIRECTORY)):
			__result = __ENOTDIR;
			break;
#endif /* __ENOTDIR */
#ifdef __ELOOP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS)):
			__result = __ELOOP;
			break;
#endif /* __ELOOP */
#ifdef __EACCES
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_ACCESS_DENIED)):
			__result = __EACCES;
			break;
#endif /* __EACCES */
#ifdef __ENOSPC
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DISK_FULL)):
			__result = __ENOSPC;
			break;
#endif /* __ENOSPC */
#ifdef __EROFS
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_READONLY)):
			__result = __EROFS;
			break;
#endif /* __EROFS */
#ifdef __EMLINK
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_TOO_MANY_HARD_LINKS)):
			__result = __EMLINK;
			break;
#endif /* __EMLINK */
#ifdef __EISDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_DIRECTORY)):
			__result = __EISDIR;
			break;
#endif /* __EISDIR */
#ifdef __ENOENT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_SYMBOLIC_LINK)):
			__result = __ENOENT;
			break;
#endif /* __ENOENT */
#ifdef __ELOOP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_SYMBOLIC_LINK)):
			__result = __ELOOP;
			break;
#endif /* __ELOOP */
#ifdef __EEXIST
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_FILE_ALREADY_EXISTS)):
			__result = __EEXIST;
			break;
#endif /* __EEXIST */
#ifdef __ENOTEMPTY
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DIRECTORY_NOT_EMPTY)):
			__result = __ENOTEMPTY;
			break;
#endif /* __ENOTEMPTY */
#ifdef __EXDEV
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_CROSS_DEVICE_LINK)):
			__result = __EXDEV;
			break;
#endif /* __EXDEV */
#ifdef __EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DIRECTORY_MOVE_TO_CHILD)):
			__result = __EINVAL;
			break;
#endif /* __EINVAL */
#ifdef __ENOTBLK
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_BLOCK_DEVICE)):
			__result = __ENOTBLK;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NO_BLOCK_DEVICE)):
			__result = __ENOTBLK;
			break;
#endif /* __ENOTBLK */
#ifdef __ENODEV
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_WRONG_FILE_SYSTEM)):
			__result = __ENODEV;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_UNKNOWN_FILE_SYSTEM)):
			__result = __ENODEV;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_CORRUPTED_FILE_SYSTEM)):
			__result = __ENODEV;
			break;
#endif /* __ENODEV */
#ifdef __EBUSY
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_DEVICE_ALREADY_MOUNTED)):
			__result = __EBUSY;
			break;
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_PATH_ALREADY_MOUNTED)):
			__result = __EBUSY;
			break;
#endif /* __EBUSY */
#ifdef __EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_NOT_A_MOUNTING_POINT)):
			__result = __EINVAL;
			break;
#endif /* __EINVAL */
#ifdef __ENOTDIR
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_IS_A_MOUNTING_POINT)):
			__result = __ENOTDIR;
			break;
#endif /* __ENOTDIR */
#if defined(__ESPIPE) && defined(__EINVAL) && defined(__EPERM)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION)):
			__result = __self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_SEEK ? __ESPIPE :
			        (__self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READ || __self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_WRITE ||
			         __self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_TRUNC || __self->e_args.e_fserror.f_unsupported_operation.uo_operation_id == E_FILESYSTEM_OPERATION_READDIR)
			         ? __EINVAL : __EPERM;
			break;
#endif /* __ESPIPE && __EINVAL && __EPERM */
		default: break;
		}
		break;

#if defined(__EPERM) && !defined(__i386__) && !defined(__x86_64__)
	case E_ILLEGAL_INSTRUCTION:
		__result = __EPERM;
		break;
#endif /* __EPERM && !__i386__ && !__x86_64__ */

#if defined(__EPERM) && (defined(__i386__) || defined(__x86_64__))
	case E_ILLEGAL_INSTRUCTION:
		__result = __EPERM;
		break;
#endif /* __EPERM && (__i386__ || __x86_64__) */

	case E_ILLEGAL_OPERATION:
		switch(__self->e_subclass) {
#ifdef __ELOOP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_ILLEGAL_REFERENCE_LOOP)):
			__result = __ELOOP;
			break;
#endif /* __ELOOP */
		default: break;
		}
		break;

#ifdef __ERANGE
	case E_INDEX_ERROR:
		__result = __ERANGE;
		break;
#endif /* __ERANGE */

#ifdef __EACCES
	case E_INSUFFICIENT_RIGHTS:
		__result = __EACCES;
		break;
#endif /* __EACCES */

#ifdef __EINTR
	case E_INTERRUPT:
		__result = __EINTR;
		break;
#endif /* __EINTR */

	case E_INVALID_ARGUMENT:
#ifdef __EINVAL
		__result = __EINVAL;
#endif /* __EINVAL */
		switch(__self->e_subclass) {
#if defined(__EAFNOSUPPORT) && defined(__ESOCKTNOSUPPORT) && defined(__EPROTONOSUPPORT) && defined(__EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_UNKNOWN_COMMAND)):
			__result = __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY ? __EAFNOSUPPORT :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE ? __ESOCKTNOSUPPORT :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL ? __EPROTONOSUPPORT :
			        __EINVAL;
			break;
#endif /* __EAFNOSUPPORT && __ESOCKTNOSUPPORT && __EPROTONOSUPPORT && __EINVAL */
#if defined(__ENOTCONN) && defined(__EDESTADDRREQ) && defined(__EISCONN) && defined(__ENXIO) && defined(__EPIPE) && defined(__EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_BAD_STATE)):
			__result = __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED ||
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED ||
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED ? __ENOTCONN :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED ? __EDESTADDRREQ :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED ? __EISCONN :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS ? __ENXIO :
			        __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS ? __EPIPE :
			        __EINVAL;
			break;
#endif /* __ENOTCONN && __EDESTADDRREQ && __EISCONN && __ENXIO && __EPIPE && __EINVAL */
#ifdef __ENOPROTOOPT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_SOCKET_OPT)):
			__result = __ENOPROTOOPT;
			break;
#endif /* __ENOPROTOOPT */
#if defined(__EAFNOSUPPORT) && defined(__EINVAL)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND)):
			__result = __self->e_args.e_invalid_argument.ia_context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY ? __EAFNOSUPPORT : __EINVAL;
			break;
#endif /* __EAFNOSUPPORT && __EINVAL */
		default: break;
		}
		break;

#ifdef __EPERM
	case E_INVALID_CONTEXT:
		__result = __EPERM;
		break;
#endif /* __EPERM */

	case E_INVALID_HANDLE:
#ifdef __EBADF
		__result = __EBADF;
#endif /* __EBADF */
		switch(__self->e_subclass) {
#if defined(__ENOTSOCK) && defined(__EBADFD)
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_FILETYPE)):
			__result = __self->e_args.e_invalid_handle.ih_filetype.f_needed_handle_type == HANDLE_TYPE_SOCKET ? __ENOTSOCK : __EBADFD;
			break;
#endif /* __ENOTSOCK && __EBADFD */
#ifdef __EINVAL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_OPERATION)):
			__result = __EINVAL;
			break;
#endif /* __EINVAL */
#ifdef __EOPNOTSUPP
		case ERROR_SUBCLASS(ERROR_CODEOF(E_INVALID_HANDLE_NET_OPERATION)):
			__result = __EOPNOTSUPP;
			break;
#endif /* __EOPNOTSUPP */
		default: break;
		}
		break;

#ifdef __EIO
	case E_IOERROR:
		__result = __EIO;
		break;
#endif /* __EIO */

	case E_NET_ERROR:
		switch(__self->e_subclass) {
#ifdef __EHOSTUNREACH
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_HOST_UNREACHABLE)):
			__result = __EHOSTUNREACH;
			break;
#endif /* __EHOSTUNREACH */
#ifdef __EADDRINUSE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_ADDRESS_IN_USE)):
			__result = __EADDRINUSE;
			break;
#endif /* __EADDRINUSE */
#ifdef __EMSGSIZE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_MESSAGE_TOO_LONG)):
			__result = __EMSGSIZE;
			break;
#endif /* __EMSGSIZE */
#ifdef __ECONNABORTED
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_ABORT)):
			__result = __ECONNABORTED;
			break;
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_REFUSED)):
			__result = __ECONNREFUSED;
			break;
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_CONNECTION_RESET)):
			__result = __ECONNRESET;
			break;
#endif /* __ECONNRESET */
#ifdef __ETIMEDOUT
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_TIMEOUT)):
			__result = __ETIMEDOUT;
			break;
#endif /* __ETIMEDOUT */
#ifdef __ENETUNREACH
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_UNREACHABLE)):
			__result = __ENETUNREACH;
			break;
#endif /* __ENETUNREACH */
#ifdef __EADDRNOTAVAIL
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_ADDRESS_NOT_AVAILABLE)):
			__result = __EADDRNOTAVAIL;
			break;
#endif /* __EADDRNOTAVAIL */
#ifdef __EPIPE
		case ERROR_SUBCLASS(ERROR_CODEOF(E_NET_SHUTDOWN)):
			__result = __EPIPE;
			break;
#endif /* __EPIPE */
		default: break;
		}
		break;

#ifdef __ENOEXEC
	case E_NOT_EXECUTABLE:
		__result = __ENOEXEC;
		break;
#endif /* __ENOEXEC */

#ifdef __ENOSYS
	case E_NOT_IMPLEMENTED:
		__result = __ENOSYS;
		break;
#endif /* __ENOSYS */

#ifdef __ENODEV
	case E_NO_DEVICE:
		__result = __ENODEV;
		break;
#endif /* __ENODEV */

#ifdef __ENODATA
	case E_NO_SUCH_OBJECT:
		__result = __ENODATA;
		break;
#endif /* __ENODATA */

#ifdef __EOK
	case E_OK:
		__result = __EOK;
		break;
#endif /* __EOK */

#ifdef __EOVERFLOW
	case E_OVERFLOW:
		__result = __EOVERFLOW;
		break;
#endif /* __EOVERFLOW */

#ifdef __ESRCH
	case E_PROCESS_EXITED:
		__result = __ESRCH;
		break;
#endif /* __ESRCH */

#ifdef __EFAULT
	case E_SEGFAULT:
		__result = __EFAULT;
		break;
#endif /* __EFAULT */

#ifdef __EFAULT
	case E_STACK_OVERFLOW:
		__result = __EFAULT;
		break;
#endif /* __EFAULT */

#ifdef __EFAULT
	case E_UNHANDLED_INTERRUPT:
		__result = __EFAULT;
		break;
#endif /* __EFAULT */

#ifdef __EILSEQ
	case E_UNICODE_ERROR:
		__result = __EILSEQ;
		break;
#endif /* __EILSEQ */

#ifdef __ENOSYS
	case E_UNKNOWN_SYSTEMCALL:
		__result = __ENOSYS;
		break;
#endif /* __ENOSYS */

#ifdef __EAGAIN
	case E_WOULDBLOCK:
		__result = __EAGAIN;
		break;
#endif /* __EAGAIN */
/*[[[end]]]*/
	default:
		break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_as_errno_defined
#define __local___localdep_error_as_errno_defined 1
#define __localdep_error_as_errno __LIBC_LOCAL_NAME(error_as_errno)
#endif /* !__local___localdep_error_as_errno_defined */
#endif /* !__local_error_as_errno_defined */
