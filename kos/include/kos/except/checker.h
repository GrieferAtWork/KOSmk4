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
#ifndef _KOS_EXCEPT_CHECKER_H
#define _KOS_EXCEPT_CHECKER_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#if !defined(__CHECKER__) && !defined(__DEEMON__)
#error "This file is only meant for the KOS checker compiler"
#endif /* !__CHECKER__ && !__DEEMON__ */

/*[[[deemon (printExceptNameCheckerPragmas from ....misc.libgen.exceptinfo)();]]]*/
#if !defined(__i386__) && !defined(__x86_64__)
#pragma checker throws E_OK = 0x0
#pragma checker throws E_BADALLOC = 0x1
#pragma checker throws E_BADALLOC_INSUFFICIENT_HEAP_MEMORY = 0x10001
#pragma checker throws E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY = 0x20001
#pragma checker throws E_BADALLOC_ADDRESS_ALREADY_EXISTS = 0x30001
#pragma checker throws E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY = 0x40001
#pragma checker throws E_BADALLOC_INSUFFICIENT_SWAP_SPACE = 0x50001
#pragma checker throws E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS = 0x60001
#pragma checker throws E_BADALLOC_INSUFFICIENT_HANDLE_RANGE = 0x70001
#pragma checker throws E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS = 0x80001
#pragma checker throws E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS = 0x90001
#pragma checker throws E_BADALLOC_INSUFFICIENT_PORT_NUMBERS = 0xa0001
#pragma checker throws E_INVALID_ARGUMENT = 0x2
#pragma checker throws E_INVALID_ARGUMENT_UNKNOWN_FLAG = 0x10002
#pragma checker throws E_INVALID_ARGUMENT_RESERVED_FLAG = 0x20002
#pragma checker throws E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION = 0x30002
#pragma checker throws E_INVALID_ARGUMENT_BAD_FLAG_MASK = 0x40002
#pragma checker throws E_INVALID_ARGUMENT_BAD_ALIGNMENT = 0x50002
#pragma checker throws E_INVALID_ARGUMENT_BAD_VALUE = 0x60002
#pragma checker throws E_INVALID_ARGUMENT_RESERVED_ARGUMENT = 0x70002
#pragma checker throws E_INVALID_ARGUMENT_UNKNOWN_COMMAND = 0x80002
#pragma checker throws E_INVALID_ARGUMENT_SOCKET_OPT = 0x90002
#pragma checker throws E_INVALID_ARGUMENT_UNEXPECTED_COMMAND = 0xa0002
#pragma checker throws E_NOT_IMPLEMENTED = 0x3
#pragma checker throws E_NOT_IMPLEMENTED_UNSUPPORTED = 0x10003
#pragma checker throws E_NOT_IMPLEMENTED_TODO = 0x20003
#pragma checker throws E_SERVICE_EXITED = 0x30003
#pragma checker throws E_INVALID_HANDLE = 0x4
#pragma checker throws E_INVALID_HANDLE_FILE = 0x10004
#pragma checker throws E_INVALID_HANDLE_FILETYPE = 0x20004
#pragma checker throws E_INVALID_HANDLE_OPERATION = 0x30004
#pragma checker throws E_INVALID_HANDLE_NET_OPERATION = 0x40004
#pragma checker throws E_WOULDBLOCK = 0x5
#pragma checker throws E_WOULDBLOCK_PREEMPTED = 0x10005
#pragma checker throws E_WOULDBLOCK_WAITFORSIGNAL = 0x20005
#pragma checker throws E_PROCESS_EXITED = 0x6
#pragma checker throws E_PROCESS_GROUP_EXITED = 0x10006
#pragma checker throws E_NO_DEVICE = 0x7
#pragma checker throws E_UNKNOWN_SYSTEMCALL = 0x8
#pragma checker throws E_NO_SUCH_OBJECT = 0x9
#pragma checker throws E_NO_CTTY = 0x10009
#pragma checker throws E_ILLEGAL_OPERATION = 0xa
#pragma checker throws E_ILLEGAL_REFERENCE_LOOP = 0x1000a
#pragma checker throws E_ILLEGAL_BECAUSE_NOT_READY = 0x2000a
#pragma checker throws E_ILLEGAL_BECAUSE_GROUPING = 0x3000a
#pragma checker throws E_ILLEGAL_IO_OPERATION = 0x4000a
#pragma checker throws E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED = 0x5000a
#pragma checker throws E_INVALID_OPERATION = 0x6000a
#pragma checker throws E_BROKEN_PIPE = 0xb
#pragma checker throws E_UNSUPPORTED_DEVICE = 0xc
#pragma checker throws E_FSERROR = 0x80
#pragma checker throws E_FSERROR_DELETED = 0x10080
#pragma checker throws E_FSERROR_FILE_NOT_FOUND = 0x20080
#pragma checker throws E_FSERROR_PATH_NOT_FOUND = 0x30080
#pragma checker throws E_FSERROR_ILLEGAL_PATH = 0x40080
#pragma checker throws E_FSERROR_NOT_A_DIRECTORY = 0x50080
#pragma checker throws E_FSERROR_TOO_MANY_SYMBOLIC_LINKS = 0x60080
#pragma checker throws E_FSERROR_ACCESS_DENIED = 0x70080
#pragma checker throws E_FSERROR_DISK_FULL = 0x80080
#pragma checker throws E_FSERROR_READONLY = 0x90080
#pragma checker throws E_FSERROR_TOO_MANY_HARD_LINKS = 0xa0080
#pragma checker throws E_FSERROR_IS_A_DIRECTORY = 0xb0080
#pragma checker throws E_FSERROR_NOT_A_SYMBOLIC_LINK = 0xc0080
#pragma checker throws E_FSERROR_IS_A_SYMBOLIC_LINK = 0xd0080
#pragma checker throws E_FSERROR_FILE_ALREADY_EXISTS = 0xe0080
#pragma checker throws E_FSERROR_DIRECTORY_NOT_EMPTY = 0xf0080
#pragma checker throws E_FSERROR_CROSS_DEVICE_LINK = 0x100080
#pragma checker throws E_FSERROR_DIRECTORY_MOVE_TO_CHILD = 0x110080
#pragma checker throws E_FSERROR_MOUNT_UNSUPPORTED_DEVICE = 0x120080
#pragma checker throws E_FSERROR_MOUNT_NEEDS_DEVICE = 0x130080
#pragma checker throws E_FSERROR_WRONG_FILE_SYSTEM = 0x140080
#pragma checker throws E_FSERROR_UNKNOWN_FILE_SYSTEM = 0x150080
#pragma checker throws E_FSERROR_CORRUPTED_FILE_SYSTEM = 0x160080
#pragma checker throws E_FSERROR_PATH_ALREADY_MOUNTED = 0x170080
#pragma checker throws E_FSERROR_NOT_A_MOUNTING_POINT = 0x180080
#pragma checker throws E_FSERROR_IS_A_MOUNTING_POINT = 0x190080
#pragma checker throws E_FSERROR_FILE_TOO_BIG = 0x1a0080
#pragma checker throws E_FSERROR_UNSUPPORTED_OPERATION = 0x1000080
#pragma checker throws E_NET_ERROR = 0x81
#pragma checker throws E_NET_HOST_UNREACHABLE = 0x10081
#pragma checker throws E_NET_ADDRESS_IN_USE = 0x20081
#pragma checker throws E_NET_MESSAGE_TOO_LONG = 0x30081
#pragma checker throws E_NET_CONNECTION_ABORT = 0x40081
#pragma checker throws E_NET_CONNECTION_REFUSED = 0x50081
#pragma checker throws E_NET_CONNECTION_RESET = 0x60081
#pragma checker throws E_NET_TIMEOUT = 0x70081
#pragma checker throws E_NET_UNREACHABLE = 0x80081
#pragma checker throws E_NET_ADDRESS_NOT_AVAILABLE = 0x90081
#pragma checker throws E_NET_SHUTDOWN = 0xa0081
#pragma checker throws E_IOERROR = 0x82
#pragma checker throws E_IOERROR_ERRORBIT = 0x10082
#pragma checker throws E_IOERROR_TIMEOUT = 0x20082
#pragma checker throws E_IOERROR_READONLY = 0x30082
#pragma checker throws E_IOERROR_BADBOUNDS = 0x40082
#pragma checker throws E_IOERROR_NODATA = 0x50082
#pragma checker throws E_NOT_EXECUTABLE = 0x83
#pragma checker throws E_NOT_EXECUTABLE_NOEXEC = 0x10083
#pragma checker throws E_NOT_EXECUTABLE_NOT_REGULAR = 0x20083
#pragma checker throws E_NOT_EXECUTABLE_NOT_A_BINARY = 0x30083
#pragma checker throws E_NOT_EXECUTABLE_FAULTY = 0x40083
#pragma checker throws E_NOT_EXECUTABLE_TOOLARGE = 0x50083
#pragma checker throws E_NOT_EXECUTABLE_TOOSMALL = 0x60083
#pragma checker throws E_INSUFFICIENT_RIGHTS = 0x84
#pragma checker throws E_BUFFER_TOO_SMALL = 0x90
#pragma checker throws _E_BUFFER_TOO_SMALL_EINVAL = 0x10090
#pragma checker throws E_UNICODE_ERROR = 0x91
#pragma checker throws E_INTERRUPT = 0xf000
#pragma checker throws E_INTERRUPT_USER_RPC = 0x1f000
#pragma checker throws E_EXIT_THREAD = 0xfe40
#pragma checker throws E_EXIT_PROCESS = 0xfe81
#pragma checker throws E_UNHANDLED_INTERRUPT = 0xfeff
#pragma checker throws E_SEGFAULT = 0xff01
#pragma checker throws E_SEGFAULT_UNMAPPED = 0x1ff01
#pragma checker throws E_SEGFAULT_READONLY = 0x2ff01
#pragma checker throws E_SEGFAULT_NOTREADABLE = 0x3ff01
#pragma checker throws E_SEGFAULT_NOTEXECUTABLE = 0x4ff01
#pragma checker throws E_SEGFAULT_NOTATOMIC = 0x5ff01
#pragma checker throws E_SEGFAULT_UNALIGNED = 0x6ff01
#pragma checker throws E_SEGFAULT_NONCONTINUOUS = 0x7ff01
#pragma checker throws E_BREAKPOINT = 0xff02
#pragma checker throws E_DIVIDE_BY_ZERO = 0xff03
#pragma checker throws E_OVERFLOW = 0xff04
#pragma checker throws E_ILLEGAL_INSTRUCTION = 0xff05
#pragma checker throws E_ILLEGAL_INSTRUCTION_BAD_OPCODE = 0x1ff05
#pragma checker throws E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE = 0x2ff05
#pragma checker throws E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE = 0x3ff05
#pragma checker throws E_ILLEGAL_INSTRUCTION_BAD_OPERAND = 0x4ff05
#pragma checker throws E_ILLEGAL_INSTRUCTION_REGISTER = 0x11ff05
#pragma checker throws E_STACK_OVERFLOW = 0xff06
#pragma checker throws E_INDEX_ERROR = 0xff07
#pragma checker throws E_INDEX_ERROR_OUT_OF_BOUNDS = 0x1ff07
#else /* ... */
#pragma checker throws E_OK = 0x0
#pragma checker throws E_BADALLOC = 0x1
#pragma checker throws E_BADALLOC_INSUFFICIENT_HEAP_MEMORY = 0x10001
#pragma checker throws E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY = 0x20001
#pragma checker throws E_BADALLOC_ADDRESS_ALREADY_EXISTS = 0x30001
#pragma checker throws E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY = 0x40001
#pragma checker throws E_BADALLOC_INSUFFICIENT_SWAP_SPACE = 0x50001
#pragma checker throws E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS = 0x60001
#pragma checker throws E_BADALLOC_INSUFFICIENT_HANDLE_RANGE = 0x70001
#pragma checker throws E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS = 0x80001
#pragma checker throws E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS = 0x90001
#pragma checker throws E_BADALLOC_INSUFFICIENT_PORT_NUMBERS = 0xa0001
#pragma checker throws E_INVALID_ARGUMENT = 0x2
#pragma checker throws E_INVALID_ARGUMENT_UNKNOWN_FLAG = 0x10002
#pragma checker throws E_INVALID_ARGUMENT_RESERVED_FLAG = 0x20002
#pragma checker throws E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION = 0x30002
#pragma checker throws E_INVALID_ARGUMENT_BAD_FLAG_MASK = 0x40002
#pragma checker throws E_INVALID_ARGUMENT_BAD_ALIGNMENT = 0x50002
#pragma checker throws E_INVALID_ARGUMENT_BAD_VALUE = 0x60002
#pragma checker throws E_INVALID_ARGUMENT_RESERVED_ARGUMENT = 0x70002
#pragma checker throws E_INVALID_ARGUMENT_UNKNOWN_COMMAND = 0x80002
#pragma checker throws E_INVALID_ARGUMENT_SOCKET_OPT = 0x90002
#pragma checker throws E_INVALID_ARGUMENT_UNEXPECTED_COMMAND = 0xa0002
#pragma checker throws E_NOT_IMPLEMENTED = 0x3
#pragma checker throws E_NOT_IMPLEMENTED_UNSUPPORTED = 0x10003
#pragma checker throws E_NOT_IMPLEMENTED_TODO = 0x20003
#pragma checker throws E_SERVICE_EXITED = 0x30003
#pragma checker throws E_INVALID_HANDLE = 0x4
#pragma checker throws E_INVALID_HANDLE_FILE = 0x10004
#pragma checker throws E_INVALID_HANDLE_FILETYPE = 0x20004
#pragma checker throws E_INVALID_HANDLE_OPERATION = 0x30004
#pragma checker throws E_INVALID_HANDLE_NET_OPERATION = 0x40004
#pragma checker throws E_WOULDBLOCK = 0x5
#pragma checker throws E_WOULDBLOCK_PREEMPTED = 0x10005
#pragma checker throws E_WOULDBLOCK_WAITFORSIGNAL = 0x20005
#pragma checker throws E_PROCESS_EXITED = 0x6
#pragma checker throws E_PROCESS_GROUP_EXITED = 0x10006
#pragma checker throws E_NO_DEVICE = 0x7
#pragma checker throws E_UNKNOWN_SYSTEMCALL = 0x8
#pragma checker throws E_NO_SUCH_OBJECT = 0x9
#pragma checker throws E_NO_CTTY = 0x10009
#pragma checker throws E_ILLEGAL_OPERATION = 0xa
#pragma checker throws E_ILLEGAL_REFERENCE_LOOP = 0x1000a
#pragma checker throws E_ILLEGAL_BECAUSE_NOT_READY = 0x2000a
#pragma checker throws E_ILLEGAL_BECAUSE_GROUPING = 0x3000a
#pragma checker throws E_ILLEGAL_IO_OPERATION = 0x4000a
#pragma checker throws E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED = 0x5000a
#pragma checker throws E_INVALID_OPERATION = 0x6000a
#pragma checker throws E_BROKEN_PIPE = 0xb
#pragma checker throws E_UNSUPPORTED_DEVICE = 0xc
#pragma checker throws E_FSERROR = 0x80
#pragma checker throws E_FSERROR_DELETED = 0x10080
#pragma checker throws E_FSERROR_FILE_NOT_FOUND = 0x20080
#pragma checker throws E_FSERROR_PATH_NOT_FOUND = 0x30080
#pragma checker throws E_FSERROR_ILLEGAL_PATH = 0x40080
#pragma checker throws E_FSERROR_NOT_A_DIRECTORY = 0x50080
#pragma checker throws E_FSERROR_TOO_MANY_SYMBOLIC_LINKS = 0x60080
#pragma checker throws E_FSERROR_ACCESS_DENIED = 0x70080
#pragma checker throws E_FSERROR_DISK_FULL = 0x80080
#pragma checker throws E_FSERROR_READONLY = 0x90080
#pragma checker throws E_FSERROR_TOO_MANY_HARD_LINKS = 0xa0080
#pragma checker throws E_FSERROR_IS_A_DIRECTORY = 0xb0080
#pragma checker throws E_FSERROR_NOT_A_SYMBOLIC_LINK = 0xc0080
#pragma checker throws E_FSERROR_IS_A_SYMBOLIC_LINK = 0xd0080
#pragma checker throws E_FSERROR_FILE_ALREADY_EXISTS = 0xe0080
#pragma checker throws E_FSERROR_DIRECTORY_NOT_EMPTY = 0xf0080
#pragma checker throws E_FSERROR_CROSS_DEVICE_LINK = 0x100080
#pragma checker throws E_FSERROR_DIRECTORY_MOVE_TO_CHILD = 0x110080
#pragma checker throws E_FSERROR_MOUNT_UNSUPPORTED_DEVICE = 0x120080
#pragma checker throws E_FSERROR_MOUNT_NEEDS_DEVICE = 0x130080
#pragma checker throws E_FSERROR_WRONG_FILE_SYSTEM = 0x140080
#pragma checker throws E_FSERROR_UNKNOWN_FILE_SYSTEM = 0x150080
#pragma checker throws E_FSERROR_CORRUPTED_FILE_SYSTEM = 0x160080
#pragma checker throws E_FSERROR_PATH_ALREADY_MOUNTED = 0x170080
#pragma checker throws E_FSERROR_NOT_A_MOUNTING_POINT = 0x180080
#pragma checker throws E_FSERROR_IS_A_MOUNTING_POINT = 0x190080
#pragma checker throws E_FSERROR_FILE_TOO_BIG = 0x1a0080
#pragma checker throws E_FSERROR_UNSUPPORTED_OPERATION = 0x1000080
#pragma checker throws E_NET_ERROR = 0x81
#pragma checker throws E_NET_HOST_UNREACHABLE = 0x10081
#pragma checker throws E_NET_ADDRESS_IN_USE = 0x20081
#pragma checker throws E_NET_MESSAGE_TOO_LONG = 0x30081
#pragma checker throws E_NET_CONNECTION_ABORT = 0x40081
#pragma checker throws E_NET_CONNECTION_REFUSED = 0x50081
#pragma checker throws E_NET_CONNECTION_RESET = 0x60081
#pragma checker throws E_NET_TIMEOUT = 0x70081
#pragma checker throws E_NET_UNREACHABLE = 0x80081
#pragma checker throws E_NET_ADDRESS_NOT_AVAILABLE = 0x90081
#pragma checker throws E_NET_SHUTDOWN = 0xa0081
#pragma checker throws E_IOERROR = 0x82
#pragma checker throws E_IOERROR_ERRORBIT = 0x10082
#pragma checker throws E_IOERROR_TIMEOUT = 0x20082
#pragma checker throws E_IOERROR_READONLY = 0x30082
#pragma checker throws E_IOERROR_BADBOUNDS = 0x40082
#pragma checker throws E_IOERROR_NODATA = 0x50082
#pragma checker throws E_NOT_EXECUTABLE = 0x83
#pragma checker throws E_NOT_EXECUTABLE_NOEXEC = 0x10083
#pragma checker throws E_NOT_EXECUTABLE_NOT_REGULAR = 0x20083
#pragma checker throws E_NOT_EXECUTABLE_NOT_A_BINARY = 0x30083
#pragma checker throws E_NOT_EXECUTABLE_FAULTY = 0x40083
#pragma checker throws E_NOT_EXECUTABLE_TOOLARGE = 0x50083
#pragma checker throws E_NOT_EXECUTABLE_TOOSMALL = 0x60083
#pragma checker throws E_INSUFFICIENT_RIGHTS = 0x84
#pragma checker throws E_BUFFER_TOO_SMALL = 0x90
#pragma checker throws _E_BUFFER_TOO_SMALL_EINVAL = 0x10090
#pragma checker throws E_UNICODE_ERROR = 0x91
#pragma checker throws E_INTERRUPT = 0xf000
#pragma checker throws E_INTERRUPT_USER_RPC = 0x1f000
#pragma checker throws E_EXIT_THREAD = 0xfe40
#pragma checker throws E_EXIT_PROCESS = 0xfe81
#pragma checker throws E_UNHANDLED_INTERRUPT = 0xfeff
#pragma checker throws E_DIVIDE_BY_ZERO = 0xff00
#pragma checker throws E_BREAKPOINT = 0xff03
#pragma checker throws E_OVERFLOW = 0xff04
#pragma checker throws E_INDEX_ERROR = 0xff05
#pragma checker throws E_INDEX_ERROR_OUT_OF_BOUNDS = 0x1ff05
#pragma checker throws E_ILLEGAL_INSTRUCTION = 0xff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_BAD_OPCODE = 0x1ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE = 0x2ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE = 0x3ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_BAD_OPERAND = 0x4ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_REGISTER = 0x11ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX = 0x8601ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_X86_TOO_LONG = 0x8602ff06
#pragma checker throws E_ILLEGAL_INSTRUCTION_X86_INTERRUPT = 0x8603ff06
#pragma checker throws E_STACK_OVERFLOW = 0xff08
#pragma checker throws E_SEGFAULT = 0xff0e
#pragma checker throws E_SEGFAULT_UNMAPPED = 0x1ff0e
#pragma checker throws E_SEGFAULT_READONLY = 0x2ff0e
#pragma checker throws E_SEGFAULT_NOTREADABLE = 0x3ff0e
#pragma checker throws E_SEGFAULT_NOTEXECUTABLE = 0x4ff0e
#pragma checker throws E_SEGFAULT_NOTATOMIC = 0x5ff0e
#pragma checker throws E_SEGFAULT_UNALIGNED = 0x6ff0e
#pragma checker throws E_SEGFAULT_NONCONTINUOUS = 0x7ff0e
#endif /* !... */
/*[[[end]]]*/

#endif /* !_KOS_EXCEPT_CHECKER_H */
