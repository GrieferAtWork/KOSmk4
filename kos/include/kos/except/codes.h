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
#ifndef _KOS_EXCEPT_CODES_H
#define _KOS_EXCEPT_CODES_H 1

/* NOTE: After making modifications to this file, you must re-run the following commands:
 * $ deemon -F kos/include/kos/bits/exception_data.h
 * $ deemon -F kos/include/i386-kos/kos/bits/exception_data32.h
 * $ deemon -F kos/include/i386-kos/kos/bits/exception_data64.h
 * $ deemon -F kos/src/libc/magic/kos.except.c
 * $ deemon -F kos/src/libc/hybrid/except.c
 * Or the one-liner
 * $ deemon -F kos/include/kos/bits/exception_data.h kos/include/i386-kos/kos/bits/exception_data32.h kos/include/i386-kos/kos/bits/exception_data64.h kos/src/libc/magic/kos.except.c
 */

#include <__stdinc.h>

#include <hybrid/pp/__va_nargs.h>

#include <kos/except/asm/codes.h> /* Pull in arch-specific code overrides */


/* Macros for addressing bounds of error class ranges */
#ifndef EXCEPTCLASS_STDERROR_MIN
#define EXCEPTCLASS_STDERROR_MIN   (0x0001)
#endif /* !EXCEPTCLASS_STDERROR_MIN */
#ifndef EXCEPTCLASS_STDERROR_MAX
#define EXCEPTCLASS_STDERROR_MAX   (0x00ff)
#endif /* !EXCEPTCLASS_STDERROR_MAX */
#ifndef EXCEPTCLASS_LIBERROR_MIN
#define EXCEPTCLASS_LIBERROR_MIN   (0x0100)
#endif /* !EXCEPTCLASS_LIBERROR_MIN */
#ifndef EXCEPTCLASS_LIBERROR_MAX
#define EXCEPTCLASS_LIBERROR_MAX   (0x01ff)
#endif /* !EXCEPTCLASS_LIBERROR_MAX */
#ifndef EXCEPTCLASS_USERERROR_MIN
#define EXCEPTCLASS_USERERROR_MIN  (0x0200)
#endif /* !EXCEPTCLASS_USERERROR_MIN */
#ifndef EXCEPTCLASS_USERERROR_MAX
#define EXCEPTCLASS_USERERROR_MAX  (0x7fff)
#endif /* !EXCEPTCLASS_USERERROR_MAX */
#ifndef EXCEPTCLASS_RESERVED1_MIN
#define EXCEPTCLASS_RESERVED1_MIN  (0x8000)
#endif /* !EXCEPTCLASS_RESERVED1_MIN */
#ifndef EXCEPTCLASS_RESERVED1_MAX
#define EXCEPTCLASS_RESERVED1_MAX  (0xefff)
#endif /* !EXCEPTCLASS_RESERVED1_MAX */
#ifndef EXCEPTCLASS_STDSIGNAL_MIN
#define EXCEPTCLASS_STDSIGNAL_MIN  (0xf000)
#endif /* !EXCEPTCLASS_STDSIGNAL_MIN */
#ifndef EXCEPTCLASS_STDSIGNAL_MAX
#define EXCEPTCLASS_STDSIGNAL_MAX  (0xf0ff)
#endif /* !EXCEPTCLASS_STDSIGNAL_MAX */
#ifndef EXCEPTCLASS_USERSIGNAL_MIN
#define EXCEPTCLASS_USERSIGNAL_MIN (0xf100)
#endif /* !EXCEPTCLASS_USERSIGNAL_MIN */
#ifndef EXCEPTCLASS_USERSIGNAL_MAX
#define EXCEPTCLASS_USERSIGNAL_MAX (0xfaff)
#endif /* !EXCEPTCLASS_USERSIGNAL_MAX */
#ifndef EXCEPTCLASS_RESERVED2_MIN
#define EXCEPTCLASS_RESERVED2_MIN  (0xfb00)
#endif /* !EXCEPTCLASS_RESERVED2_MIN */
#ifndef EXCEPTCLASS_RESERVED2_MAX
#define EXCEPTCLASS_RESERVED2_MAX  (0xfdff)
#endif /* !EXCEPTCLASS_RESERVED2_MAX */
#ifndef EXCEPTCLASS_RTL_MIN
#define EXCEPTCLASS_RTL_MIN        (0xfe00)
#endif /* !EXCEPTCLASS_RTL_MIN */
#ifndef EXCEPTCLASS_RTL_MAX
#define EXCEPTCLASS_RTL_MAX        (0xfe7f)
#endif /* !EXCEPTCLASS_RTL_MAX */
#ifndef EXCEPTCLASS_UNHANDLED_MIN
#define EXCEPTCLASS_UNHANDLED_MIN  (0xfe80)
#endif /* !EXCEPTCLASS_UNHANDLED_MIN */
#ifndef EXCEPTCLASS_UNHANDLED_MAX
#define EXCEPTCLASS_UNHANDLED_MAX  (0xfebf)
#endif /* !EXCEPTCLASS_UNHANDLED_MAX */
#ifndef EXCEPTCLASS_CPU_MIN
#define EXCEPTCLASS_CPU_MIN        (0xfec0)
#endif /* !EXCEPTCLASS_CPU_MIN */
#ifndef EXCEPTCLASS_CPU_MAX
#define EXCEPTCLASS_CPU_MAX        (0xfeff)
#endif /* !EXCEPTCLASS_CPU_MAX */
#ifndef EXCEPTCLASS_HARDWARE_MIN
#define EXCEPTCLASS_HARDWARE_MIN   (0xff00)
#endif /* !EXCEPTCLASS_HARDWARE_MIN */
#ifndef EXCEPTCLASS_HARDWARE_MAX
#define EXCEPTCLASS_HARDWARE_MAX   (0xffff)
#endif /* !EXCEPTCLASS_HARDWARE_MAX */


/* Check if the given error is low- (may get overwritten by !LOW || HIGH ||
 * RTL), or high- (overwritten by RTL) priority. This mechanism is used for
 * dealing with multiple exceptions thrown at the same time (aka. exception
 * nesting; s.a. `NESTED_TRY' and `except_priority(3)'). */
#ifndef EXCEPTCLASS_ISLOWPRIORITY
#define EXCEPTCLASS_ISLOWPRIORITY(x)  ((x) >= EXCEPTCLASS_STDSIGNAL_MIN && (x) <= EXCEPTCLASS_USERSIGNAL_MAX)
#endif /* !EXCEPTCLASS_ISLOWPRIORITY */
#ifndef EXCEPTCLASS_ISHIGHPRIORITY
#define EXCEPTCLASS_ISHIGHPRIORITY(x) ((x) >= EXCEPTCLASS_RTL_MIN && (x) <= EXCEPTCLASS_UNHANDLED_MAX)
#endif /* !EXCEPTCLASS_ISHIGHPRIORITY */

/* Check for  RTL-priority exceptions.  Exceptions matching  this
 * check are always propagated between the kernel and user-space,
 * irregardless  of whether or not a system call was invoked with
 * or without exceptions enabled.
 * This is only meant for exceptions like `E_EXIT_THREAD', who's
 * sole  purpose is to  unwind the stack  and safely terminate a
 * thread. */
#ifndef EXCEPTCLASS_ISRTLPRIORITY
#define EXCEPTCLASS_ISRTLPRIORITY(x) ((x) >= EXCEPTCLASS_RTL_MIN && (x) <= EXCEPTCLASS_RTL_MAX)
#endif /* !EXCEPTCLASS_ISRTLPRIORITY */






/*[[[begin]]]*/

/************************************************************************/
/* Exception classes.                                                   */
/************************************************************************/
#ifndef E_OK
#define E_OK (0x0000) /* [errno(EOK), msg("No error")]
                       * Never thrown; may be used to indicate error-less state */
#endif /* !E_OK */

/************************************************************************/
/* E_BADALLOC                                                           */
/************************************************************************/
#ifndef E_BADALLOC
#define E_BADALLOC                                (0x0001)             /* [errno(ENOMEM), prefix("ba_"), msg("Failed to allocate sufficient resources")] */
#endif /* !E_BADALLOC */
#ifndef E_BADALLOC_INSUFFICIENT_HEAP_MEMORY
#define E_BADALLOC_INSUFFICIENT_HEAP_MEMORY       (E_BADALLOC, 0x0001) /* [msg("Insufficient heap memory")]
                                                                        * [fld(num_bytes: size_t, "The number of bytes that could not be allocated")] */
#endif /* !E_BADALLOC_INSUFFICIENT_HEAP_MEMORY */
#ifndef E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY
#define E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY    (E_BADALLOC, 0x0002) /* [msg("Insufficient virtual address space")]
                                                                        * [fld(num_bytes: size_t, "The number of bytes that could not be mapped")] */
#endif /* !E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY */
#ifndef E_BADALLOC_ADDRESS_ALREADY_EXISTS
#define E_BADALLOC_ADDRESS_ALREADY_EXISTS         (E_BADALLOC, 0x0003) /* [errno(EEXIST), msg("Virtual address already in use")]
                                                                        * [fld(minaddr:       void *, "Lowest address that was requested")]
                                                                        * [fld(maxaddr:       void *, "Greatest address that was requested")]
                                                                        * [fld(inuse_minaddr: void *, "Lowest address already in use")]
                                                                        * [fld(inuse_maxaddr: void *, "Greatest address already in use")] */
#endif /* !E_BADALLOC_ADDRESS_ALREADY_EXISTS */
#ifndef E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY
#define E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY   (E_BADALLOC, 0x0004) /* [msg("Insufficient physical memory")]
                                                                        * [fld(num_pages: size_t, "The number of bytes that could not be allocated")] */
#endif /* !E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY */
#ifndef E_BADALLOC_INSUFFICIENT_SWAP_SPACE
#define E_BADALLOC_INSUFFICIENT_SWAP_SPACE        (E_BADALLOC, 0x0005) /* [msg("Insufficient swap space")]
                                                                        * [fld(num_pages: size_t, "The number of bytes that could not be allocated")] */
#endif /* !E_BADALLOC_INSUFFICIENT_SWAP_SPACE */
#ifndef E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS
#define E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS    (E_BADALLOC, 0x0006) /* [errno(EMFILE), msg("Too many open file handles")]
                                                                        * [fld(num_handles: unsigned int, "The number of handles that were attempted to be allocated (usually 1)")]
                                                                        * [fld(cur_handles: unsigned int, "The number of handles currently allocated")]
                                                                        * [fld(max_handles: unsigned int, "The max number of handles that may be allocated by the caller")] */
#endif /* !E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS */
/* TODO: Get rid of `E_BADALLOC_INSUFFICIENT_HANDLE_RANGE' */
#ifndef E_BADALLOC_INSUFFICIENT_HANDLE_RANGE
#define E_BADALLOC_INSUFFICIENT_HANDLE_RANGE      (E_BADALLOC, 0x0007) /* [errno(ENFILE), msg("File handle too great")]
                                                                        * [fld(req_handle: unsigned int, "The requested handle number, past which no more unused handles exist.")]
                                                                        * [fld(cur_max:    unsigned int, "The max handle id that is currently in use")]
                                                                        * [fld(cur_limit:  unsigned int, "The set handle id which may not be exceeded")] */
#endif /* !E_BADALLOC_INSUFFICIENT_HANDLE_RANGE */
#ifndef E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS
#define E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS    (E_BADALLOC, 0x0008) /* [msg("No suitable, free device numbers are available")]
                                                                        * [fld(dev_kind: unsigned int, "The kind of device number lacking (One of `E_NO_DEVICE_KIND_*')")] */
#endif /* !E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS */
#ifndef E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS
#define E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS (E_BADALLOC, 0x0009) /* [msg("The given, or all interrupt vectors are already in use")]
                                                                        * [fld(vector: uintptr_t, "The given vector (if that specific vector is already in use),\n"
                                                                        *                         "or (uintptr_t)-1 when all vectors are already in use.")] */
#endif /* !E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS */
#ifndef E_BADALLOC_INSUFFICIENT_PORT_NUMBERS
#define E_BADALLOC_INSUFFICIENT_PORT_NUMBERS      (E_BADALLOC, 0x000a) /* [errno(EADDRNOTAVAIL), msg("Failed to dynamically allocate a socket port number")]
                                                                        * [fld(address_family: syscall_ulong_t, "The socket's address family (one of `AF_*')")]
                                                                        * [fld(socket_type:    syscall_ulong_t, "The socket's type (one of `SOCK_*')")]
                                                                        * [fld(protocol:       syscall_ulong_t, "The socket's protocol (dependent on `address_family' and `socket_type')")] */
#endif /* !E_BADALLOC_INSUFFICIENT_PORT_NUMBERS */



/************************************************************************/
/* E_INVALID_ARGUMENT                                                   */
/************************************************************************/
#ifndef E_INVALID_ARGUMENT
#define E_INVALID_ARGUMENT                        (0x0002)                     /* [errno(EINVAL), msg("Invalid argument")]
                                                                                * [fld(context: syscall_ulong_t, "Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')")] */
#endif /* !E_INVALID_ARGUMENT */
#ifndef E_INVALID_ARGUMENT_UNKNOWN_FLAG
#define E_INVALID_ARGUMENT_UNKNOWN_FLAG           (E_INVALID_ARGUMENT, 0x0001) /* [msg("An invalid set of flags was given")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")]
                                                                                * [fld(mask:    uintptr_t, "The mask of illegal & fixed bits")]
                                                                                * [fld(result:  uintptr_t, "The mask of fixed bits")]
                                                                                * An invalid set of flags was given, such that `(value & mask) != result' was the case */
#endif /* !E_INVALID_ARGUMENT_UNKNOWN_FLAG */
#ifndef E_INVALID_ARGUMENT_RESERVED_FLAG
#define E_INVALID_ARGUMENT_RESERVED_FLAG          (E_INVALID_ARGUMENT, 0x0002) /* [msg("A reserved bit was set incorrectly")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")]
                                                                                * [fld(mask:    uintptr_t, "The mask of illegal & fixed bits")]
                                                                                * [fld(result:  uintptr_t, "The mask of fixed bits")]
                                                                                * A reserved bit was set incorrectly, such that `(value & mask) != result' was the case */
#endif /* !E_INVALID_ARGUMENT_RESERVED_FLAG */
#ifndef E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION
#define E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION   (E_INVALID_ARGUMENT, 0x0003) /* [msg("An invalid combination of flags was set")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")]
                                                                                * [fld(mask:    uintptr_t, "The mask of relevant bits")]
                                                                                * [fld(result:  uintptr_t, "The invalid resulting value")]
                                                                                * An invalid combination of flags was set, such that `(value & mask) == result' was the case */
#endif /* !E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION */
#ifndef E_INVALID_ARGUMENT_BAD_FLAG_MASK
#define E_INVALID_ARGUMENT_BAD_FLAG_MASK          (E_INVALID_ARGUMENT, 0x0004) /* [msg("A masked type field contains an invalid value")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")]
                                                                                * [fld(mask:    uintptr_t, "The mask of relevant bits")]
                                                                                * A masked type field `(value & mask)' contains an invalid value */
#endif /* !E_INVALID_ARGUMENT_BAD_FLAG_MASK */
#ifndef E_INVALID_ARGUMENT_BAD_ALIGNMENT
#define E_INVALID_ARGUMENT_BAD_ALIGNMENT          (E_INVALID_ARGUMENT, 0x0005) /* [msg("A given value has an invalid alignment")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")]
                                                                                * [fld(mask:    uintptr_t, "The mask in which the bits of `value' must match `required_masked_value'")]
                                                                                * [fld(required_masked_value: uintptr_t, "The required result of masking `value'")]
                                                                                * A given `value' has an invalid alignment when masked by `mask', such that
                                                                                * the  expression  `(mask & value) != required_masked_value' was  the case. */
#endif /* !E_INVALID_ARGUMENT_BAD_ALIGNMENT */
#ifndef E_INVALID_ARGUMENT_BAD_VALUE
#define E_INVALID_ARGUMENT_BAD_VALUE              (E_INVALID_ARGUMENT, 0x0006) /* [errno(($context == E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID ||
                                                                                *         $context == E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID) ? EPERM : EINVAL)]
                                                                                * [msg("A given value is invalid for the associated argument")]
                                                                                * [fld(value:   uintptr_t, "The value that was given")] */
#endif /* !E_INVALID_ARGUMENT_BAD_VALUE */
#ifndef E_INVALID_ARGUMENT_RESERVED_ARGUMENT
#define E_INVALID_ARGUMENT_RESERVED_ARGUMENT      (E_INVALID_ARGUMENT, 0x0007) /* [msg("A reserved argument had an unexpected value")] */
#endif /* !E_INVALID_ARGUMENT_RESERVED_ARGUMENT */
#ifndef E_INVALID_ARGUMENT_UNKNOWN_COMMAND
#define E_INVALID_ARGUMENT_UNKNOWN_COMMAND        (E_INVALID_ARGUMENT, 0x0008) /* [errno($context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY ? EAFNOSUPPORT :
                                                                                *        $context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE ? ESOCKTNOSUPPORT :
                                                                                *        $context == E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL ? EPROTONOSUPPORT :
                                                                                *        EINVAL)]
                                                                                * [msg("An unknown command was given")]
                                                                                * [fld(command: uintptr_t, "The command that was given")] */
#endif /* !E_INVALID_ARGUMENT_UNKNOWN_COMMAND */
#ifndef E_INVALID_ARGUMENT_SOCKET_OPT
#define E_INVALID_ARGUMENT_SOCKET_OPT             (E_INVALID_ARGUMENT, 0x0009) /* [errno(ENOPROTOOPT), msg("Unrecognized combination of level/optname")]
                                                                                * [fld(level:          uintptr_t, "The level that was given to `getoptname()' or `setoptname()'")]
                                                                                * [fld(optname:        uintptr_t, "The optname that was given to `getoptname()' or `setoptname()'")]
                                                                                * [fld(address_family: uintptr_t, "The socket's address family (one of `AF_*')")]
                                                                                * [fld(socket_type:    uintptr_t, "The socket's type (one of `SOCK_*')")]
                                                                                * [fld(protocol:       uintptr_t, "The socket's protocol (dependent on `address_family' and `socket_type')")] */
#endif /* !E_INVALID_ARGUMENT_SOCKET_OPT */
#ifndef E_INVALID_ARGUMENT_UNEXPECTED_COMMAND
#define E_INVALID_ARGUMENT_UNEXPECTED_COMMAND     (E_INVALID_ARGUMENT, 0x000a) /* [errno($context == E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY ? EAFNOSUPPORT : EINVAL)]
                                                                                * [msg("One command was given when a different one was expected")]
                                                                                * [fld(command:          uintptr_t, "The command that was given")]
                                                                                * [fld(expected_command: uintptr_t, "The command that had been expected")] */
#endif /* !E_INVALID_ARGUMENT_UNEXPECTED_COMMAND */





/************************************************************************/
/* E_NOT_IMPLEMENTED                                                    */
/************************************************************************/
#ifndef E_NOT_IMPLEMENTED
#define E_NOT_IMPLEMENTED                         (0x0003)                    /* [errno(ENOSYS), msg("Unimplemented function")] */
#endif /* !E_NOT_IMPLEMENTED */
#ifndef E_NOT_IMPLEMENTED_UNSUPPORTED
#define E_NOT_IMPLEMENTED_UNSUPPORTED             (E_NOT_IMPLEMENTED, 0x0001) /* [msg("Unsupported function")] */
#endif /* !E_NOT_IMPLEMENTED_UNSUPPORTED */
#ifndef E_NOT_IMPLEMENTED_TODO
#define E_NOT_IMPLEMENTED_TODO                    (E_NOT_IMPLEMENTED, 0x0002) /* [msg("Function not yet implemented")] */
#endif /* !E_NOT_IMPLEMENTED_TODO */
#ifndef E_SERVICE_EXITED
#define E_SERVICE_EXITED                          (E_NOT_IMPLEMENTED, 0x0003) /* [msg("Service was shut down")] */
#endif /* !E_SERVICE_EXITED */





/************************************************************************/
/* E_INVALID_HANDLE                                                     */
/************************************************************************/
#ifndef E_INVALID_HANDLE
#define E_INVALID_HANDLE                          (0x0004)                   /* [errno(EBADF), msg("Bad file descriptor")]
                                                                              * [fld(fd:       fd_t,            "The FD number that was accessed")] */
#endif /* !E_INVALID_HANDLE */
#ifndef E_INVALID_HANDLE_FILE
#define E_INVALID_HANDLE_FILE                     (E_INVALID_HANDLE, 0x0001) /* [msg("The given file descriptor is invalid")]
                                                                              * [errno($reason == E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD ? EINVAL : EBADF)]
                                                                              * [fld(reason:   syscall_ulong_t, "One of `E_INVALID_HANDLE_FILE_*'")]
                                                                              * [fld(fd_max:   unsigned int,    "1+ the max FD number that is currently in use")]
                                                                              * [fld(fd_limit: unsigned int,    "The max allowed FD number that may be assigned")] */
#endif /* !E_INVALID_HANDLE_FILE */
#ifndef E_INVALID_HANDLE_FILETYPE
#define E_INVALID_HANDLE_FILETYPE                 (E_INVALID_HANDLE, 0x0002) /* [errno($needed_handle_type == HANDLE_TYPE_SOCKET ? ENOTSOCK : EBADFD)]
                                                                              * [msg("Invalid file handle type")]
                                                                              * [fld(needed_handle_type: syscall_ulong_t, "The type of handle that was needed (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)")]
                                                                              * [fld(actual_handle_type: syscall_ulong_t, "The type of handle that was found (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)")]
                                                                              * [fld(needed_handle_kind: syscall_ulong_t, "The type-kind of handle that was needed (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)")]
                                                                              * [fld(actual_handle_kind: syscall_ulong_t, "The type-kind of handle that was found (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)")] */
#endif /* !E_INVALID_HANDLE_FILETYPE */
#ifndef E_INVALID_HANDLE_OPERATION
#define E_INVALID_HANDLE_OPERATION                (E_INVALID_HANDLE, 0x0003) /* [errno($op == E_INVALID_HANDLE_OPERATION_MMAP ? EACCES : EINVAL), msg("Invalid handle operation")]
                                                                              * [fld(op: unsigned int, "One of `E_INVALID_HANDLE_OPERATION_*'")]
                                                                              * [fld(handle_mode: iomode_t, "The access permissions of the handle")] */
#endif /* !E_INVALID_HANDLE_OPERATION */
#ifndef E_INVALID_HANDLE_NET_OPERATION
#define E_INVALID_HANDLE_NET_OPERATION            (E_INVALID_HANDLE, 0x0004) /* [errno(EOPNOTSUPP), msg("Network operation not supported by address family, socket type, and protocol")]
                                                                              * [fld(operation_id:   syscall_ulong_t, "The attempted network operation (One of `E_NET_OPERATION_*')")]
                                                                              * [fld(address_family: syscall_ulong_t, "The socket's address family (one of `AF_*')")]
                                                                              * [fld(socket_type:    syscall_ulong_t, "The socket's type (one of `SOCK_*')")]
                                                                              * [fld(protocol:       syscall_ulong_t, "The socket's protocol (dependent on `address_family' and `socket_type')")] */
#endif /* !E_INVALID_HANDLE_NET_OPERATION */
/*[[[end]]]*/

#ifndef E_INVALID_HANDLE_FILE_UNBOUND
#define E_INVALID_HANDLE_FILE_UNBOUND          0x0001 /* The FD slot associated with the given number has no bound value */
#endif /* !E_INVALID_HANDLE_FILE_UNBOUND */
#ifndef E_INVALID_HANDLE_FILE_NEGATIVE
#define E_INVALID_HANDLE_FILE_NEGATIVE         0x0002 /* The given `fd < 0', and symbolic handles are either not accepted, or `fd' isn't a symbolic handle */
#endif /* !E_INVALID_HANDLE_FILE_NEGATIVE */
#ifndef E_INVALID_HANDLE_FILE_ILLEGAL
#define E_INVALID_HANDLE_FILE_ILLEGAL          0x0003 /* The FD slot associated with the given number may not be used (`fd > fd_limit') */
#endif /* !E_INVALID_HANDLE_FILE_ILLEGAL */
#ifndef E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD
#define E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD  0x0004 /* Same as `E_INVALID_HANDLE_FILE_ILLEGAL', but context is `fcntl(F_DUPFD)'.
                                                       * -> Translated to EINVAL instead of EBADF for compatibility with linux. */
#endif /* !E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD */
#ifndef E_INVALID_HANDLE_OPERATION_READ
#define E_INVALID_HANDLE_OPERATION_READ        0x0001 /* Attempted to read() on a handle opened as IO_WRONLY */
#endif /* !E_INVALID_HANDLE_OPERATION_READ */
#ifndef E_INVALID_HANDLE_OPERATION_WRITE
#define E_INVALID_HANDLE_OPERATION_WRITE       0x0002 /* Attempted to write() on a handle opened as IO_RDONLY */
#endif /* !E_INVALID_HANDLE_OPERATION_WRITE */
#ifndef E_INVALID_HANDLE_OPERATION_TRUNC
#define E_INVALID_HANDLE_OPERATION_TRUNC       0x0003 /* Attempted to truncate() on a handle opened as IO_RDONLY */
#endif /* !E_INVALID_HANDLE_OPERATION_TRUNC */
#ifndef E_INVALID_HANDLE_OPERATION_MMAP
#define E_INVALID_HANDLE_OPERATION_MMAP        0x0004 /* Attempted to:
                                                       * - mmap() a handle opened as IO_WRONLY
                                                       * - mmap(PROT_WRITE) a handle opened with IO_APPEND
                                                       * - mmap(PROT_WRITE, MAP_SHARED) a handle not opened as IO_RDWR
                                                       * - mprotect(PROT_WRITE) a MAP_SHARED mapping  created by a non-IO_RDWR  handle. */
#endif /* !E_INVALID_HANDLE_OPERATION_MMAP */
#ifndef E_INVALID_HANDLE_OPERATION_GETPROPERTY
#define E_INVALID_HANDLE_OPERATION_GETPROPERTY 0x0011 /* Attempted to get some abstract property of a handle opened
                                                       * as IO_WRONLY. Note however that this depends on what  type
                                                       * of handle and property was  accessed. - If, and when  this
                                                       * context has meaning, that fact is explicitly documented. */
#endif /* !E_INVALID_HANDLE_OPERATION_GETPROPERTY */
#ifndef E_INVALID_HANDLE_OPERATION_SETPROPERTY
#define E_INVALID_HANDLE_OPERATION_SETPROPERTY 0x0012 /* Same as `E_INVALID_HANDLE_OPERATION_GETPROPERTY', but for setting properties */
#endif /* !E_INVALID_HANDLE_OPERATION_SETPROPERTY */
/*[[[begin]]]*/





/************************************************************************/
/* E_WOULDBLOCK                                                         */
/************************************************************************/
#ifndef E_WOULDBLOCK
#define E_WOULDBLOCK                              (0x0005)               /* [errno(EAGAIN), prefix("wb_"), msg("Operation would have blocked")] */
#endif /* !E_WOULDBLOCK */
#ifndef E_WOULDBLOCK_PREEMPTED
#define E_WOULDBLOCK_PREEMPTED                    (E_WOULDBLOCK, 0x0001) /* [msg("Operation cannot be preempted")] */
#endif /* !E_WOULDBLOCK_PREEMPTED */
#ifndef E_WOULDBLOCK_WAITFORSIGNAL
#define E_WOULDBLOCK_WAITFORSIGNAL                (E_WOULDBLOCK, 0x0002) /* [msg("Cannot wait for signal")] */
#endif /* !E_WOULDBLOCK_WAITFORSIGNAL */





/************************************************************************/
/* E_PROCESS_EXITED                                                     */
/************************************************************************/
#ifndef E_PROCESS_EXITED
#define E_PROCESS_EXITED                          (0x0006)                   /* [errno(ESRCH), msg("Process does not exist")]
                                                                              * [fld(pid: pid_t, "The pid of the exited process")]
                                                                              * The task controller for the specified process has already been deallocated.
                                                                              * This  implies that the  process has exited. However,  it doesn't imply that
                                                                              * the task controller is immediately deallocated when a process exists. */
#endif /* !E_PROCESS_EXITED */
#ifndef E_PROCESS_GROUP_EXITED
#define E_PROCESS_GROUP_EXITED                    (E_PROCESS_EXITED, 0x0001) /* [msg("Process group does not exists")]
                                                                              * The named process grup doesn't exist. */
#endif /* !E_PROCESS_GROUP_EXITED */





/************************************************************************/
/* E_NO_DEVICE                                                          */
/************************************************************************/
#ifndef E_NO_DEVICE
#define E_NO_DEVICE                               (0x0007) /* [errno(ENODEV), msg("No such device")]
                                                            * [fld(kind: uintptr_t, "The kind of device (One of `E_NO_DEVICE_KIND_*')")]
                                                            * [fld(devno: dev_t, "The number for the named device")] */
#endif /* !E_NO_DEVICE */
/*[[[end]]]*/
#ifndef E_NO_DEVICE_KIND_BLKDEV
#define E_NO_DEVICE_KIND_BLKDEV 0x6000 /* A block device was missing (== S_IFBLK) */
#endif /* !E_NO_DEVICE_KIND_BLKDEV */
#ifndef E_NO_DEVICE_KIND_CHRDEV
#define E_NO_DEVICE_KIND_CHRDEV 0x2000 /* A character device was missing (== S_IFCHR) */
#endif /* !E_NO_DEVICE_KIND_CHRDEV */
/*[[[begin]]]*/





/************************************************************************/
/* E_UNKNOWN_SYSTEMCALL                                                 */
/************************************************************************/
#ifndef E_UNKNOWN_SYSTEMCALL
#define E_UNKNOWN_SYSTEMCALL                      (0x0008) /* [errno(ENOSYS), msg("Unknown system call")]
                                                            * [fld(flags: syscall_ulong_t, "System call invocation flags (Set of `RPC_SYSCALL_INFO_*')")]
                                                            * [fld(sysno: syscall_ulong_t)]
                                                            * [fld(arg0: syscall_ulong_t), fld(arg1: syscall_ulong_t)]
                                                            * [fld(arg2: syscall_ulong_t), fld(arg3: syscall_ulong_t)]
                                                            * [fld(arg4: syscall_ulong_t), fld(arg5: syscall_ulong_t)] */
#endif /* !E_UNKNOWN_SYSTEMCALL */





/************************************************************************/
/* E_NO_SUCH_OBJECT                                                     */
/************************************************************************/
#ifndef E_NO_SUCH_OBJECT
#define E_NO_SUCH_OBJECT                          (0x0009)                   /* [errno(ENODATA), msg("The specified object doesn't exist")] */
#endif /* !E_NO_SUCH_OBJECT */
#ifndef E_NO_CTTY
#define E_NO_CTTY                                 (E_NO_SUCH_OBJECT, 0x0001) /* [errno(ENODEV), msg("No controlling terminal has been assigned to the calling session")] */
#endif /* !E_NO_CTTY */





/************************************************************************/
/* E_ILLEGAL_OPERATION                                                  */
/************************************************************************/
#ifndef E_ILLEGAL_OPERATION
#define E_ILLEGAL_OPERATION                       (0x000a)                      /* [errno($reason == E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK ? ENXIO : EPERM)]
                                                                                 * [msg("Illegal operation")]
                                                                                 * [fld(reason: syscall_ulong_t, "One of `E_ILLEGAL_OPERATION_CONTEXT_*'")] */
#endif /* !E_ILLEGAL_OPERATION */
#ifndef E_ILLEGAL_REFERENCE_LOOP
#define E_ILLEGAL_REFERENCE_LOOP                  (E_ILLEGAL_OPERATION, 0x0001) /* [errno($reason == E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP ? EINVAL : ELOOP)]
                                                                                 * [msg("Reference loop detected")] */
#endif /* !E_ILLEGAL_REFERENCE_LOOP */
#ifndef E_ILLEGAL_BECAUSE_NOT_READY
#define E_ILLEGAL_BECAUSE_NOT_READY               (E_ILLEGAL_OPERATION, 0x0002) /* [errno(($reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED) ? ENOTCONN :
                                                                                 *        ($reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED) ? EDESTADDRREQ :
                                                                                 *        ($reason == E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED) ? EISCONN :
                                                                                 *         EINVAL)]
                                                                                 * [msg("Object isn't ready for the requested operation")] */
#endif /* !E_ILLEGAL_BECAUSE_NOT_READY */
#ifndef E_ILLEGAL_BECAUSE_GROUPING
#define E_ILLEGAL_BECAUSE_GROUPING                (E_ILLEGAL_OPERATION, 0x0003) /* [errno(($reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION ||
                                                                                 *         $reason == E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION) ? ENOTTY :
                                                                                 *         EPERM)]
                                                                                 * [msg("Operation not permitted due to process/process-group/session association")] */
#endif /* !E_ILLEGAL_BECAUSE_GROUPING */
#ifndef E_ILLEGAL_IO_OPERATION
#define E_ILLEGAL_IO_OPERATION                    (E_ILLEGAL_OPERATION, 0x0004) /* [errno(ENXIO)]
                                                                                 * [msg("Illegal I/O operation")] */
#endif /* !E_ILLEGAL_IO_OPERATION */
#ifndef E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED
#define E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED         (E_ILLEGAL_OPERATION, 0x0005) /* [errno(ENOMEM), msg("Resource limit exceeded")] */
#endif /* !E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED */
#ifndef E_INVALID_OPERATION
#define E_INVALID_OPERATION                       (E_ILLEGAL_OPERATION, 0x0006) /* [errno(EINVAL), msg("Operation is invalid in this context")] */
#endif /* !E_INVALID_OPERATION */





/************************************************************************/
/* E_BROKEN_PIPE                                                        */
/************************************************************************/
#ifndef E_BROKEN_PIPE
#define E_BROKEN_PIPE                             (0x000b) /* [errno(EPIPE), msg("Tried to write to a pipe without any readers")] */
#endif /* !E_BROKEN_PIPE */





/************************************************************************/
/* E_UNSUPPORTED_DEVICE                                                 */
/************************************************************************/
#ifndef E_UNSUPPORTED_DEVICE
#define E_UNSUPPORTED_DEVICE                      (0x000c) /* [errno(ENODEV), msg("Unsupported device or feature")] */
#endif /* !E_UNSUPPORTED_DEVICE */





/************************************************************************/
/* E_FSERROR                                                            */
/************************************************************************/
#ifndef E_FSERROR
#define E_FSERROR                                 (0x0080)            /* [msg("Filesystem error")] */
#endif /* !E_FSERROR */
#ifndef E_FSERROR_DELETED
#define E_FSERROR_DELETED                         (E_FSERROR, 0x0001) /* [errno(ENOENT), msg("Attempted to access a file that has been deleted")]
                                                                       * [fld(reason: unsigned int, "The reason/context in which the file was deleted (One of `E_FILESYSTEM_DELETED_*')")] */
#endif /* !E_FSERROR_DELETED */
#ifndef E_FSERROR_FILE_NOT_FOUND
#define E_FSERROR_FILE_NOT_FOUND                  (E_FSERROR, 0x0002) /* [errno(ENOENT), msg("File not found")] */
#endif /* !E_FSERROR_FILE_NOT_FOUND */
#ifndef E_FSERROR_PATH_NOT_FOUND
#define E_FSERROR_PATH_NOT_FOUND                  (E_FSERROR, 0x0003) /* [errno(ENOENT), msg("Path not found")]
                                                                       * [fld(reason: unsigned int, "The reason/context why the path wasn't found (One of `E_FILESYSTEM_PATH_NOT_FOUND_*')")] */
#endif /* !E_FSERROR_PATH_NOT_FOUND */
#ifndef E_FSERROR_ILLEGAL_PATH
#define E_FSERROR_ILLEGAL_PATH                    (E_FSERROR, 0x0004) /* [errno(ENAMETOOLONG), msg("Illegal or malformed path")] */
#endif /* !E_FSERROR_ILLEGAL_PATH */
#ifndef E_FSERROR_NOT_A_DIRECTORY
#define E_FSERROR_NOT_A_DIRECTORY                 (E_FSERROR, 0x0005) /* [errno(ENOTDIR), msg("Expected a directory")]
                                                                       * [fld(action_context: uintptr_t, "The context in which a filesystem component was required to be\n"
                                                                       *                                 "a directory, but wasn't (One of `E_FILESYSTEM_NOT_A_DIRECTORY_*')")]
                                                                       * A directory was expected, but something else was found */
#endif /* !E_FSERROR_NOT_A_DIRECTORY */
/*[[[end]]]*/
/* TODO: Refactor the below from `E_FILESYSTEM_NOT_A_DIRECTORY_*' to `E_FSERROR_NOT_A_DIRECTORY_*'
 *       The same should go for all of the other `E_FILESYSTEM_*' macros. */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_WALK
#define E_FILESYSTEM_NOT_A_DIRECTORY_WALK    1 /* Thrown as the  result of attempting  to traverse a  non-directory
                                                * item as though it was one (e.g. `open("/opt/readme.txt/foobar")') */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_WALK */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_OPEN
#define E_FILESYSTEM_NOT_A_DIRECTORY_OPEN    2 /* Thrown as the result of `open(path, O_DIRECTORY)', where `path' isn't a directory */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_OPEN */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR
#define E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR   3 /* Thrown as the result of `rmdir(path)', where `path' isn't a directory */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_READDIR
#define E_FILESYSTEM_NOT_A_DIRECTORY_READDIR 4 /* Thrown as the result of `readdir(path)', where `path' isn't a directory */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_READDIR */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_RENAME
#define E_FILESYSTEM_NOT_A_DIRECTORY_RENAME  5 /* `rename(2)' tried to override a directory with a non-directory */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_RENAME */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_MOUNT_BIND
#define E_FILESYSTEM_NOT_A_DIRECTORY_MOUNT_BIND 6 /* `mount(2)' with MS_BIND was given a non-directory. */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_MOUNT_BIND */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_IOCTL
#define E_FILESYSTEM_NOT_A_DIRECTORY_IOCTL   7 /* The specific `ioctl(2)' command cannot be used on a non-directory. */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_IOCTL */
#ifndef E_FILESYSTEM_NOT_A_DIRECTORY_WATCH
#define E_FILESYSTEM_NOT_A_DIRECTORY_WATCH   8 /* `IN_ONLYDIR' was given `inotify_add_watch(2)', but specified file wasn't a directory. */
#endif /* !E_FILESYSTEM_NOT_A_DIRECTORY_WATCH */

/* SPLIT: All error codes above should be interpreted as  FILE-NOT-FOUND
 *        in situations where a list of paths is searched for a specific
 *        file. */
#ifndef E_FSERROR_IS_FILE_NOT_FOUND
#define E_FSERROR_IS_FILE_NOT_FOUND(x) (EXCEPT_SUBCLASS(x) <= 0x0005)
#endif /* !E_FSERROR_IS_FILE_NOT_FOUND */
/*[[[begin]]]*/


#ifndef E_FSERROR_TOO_MANY_SYMBOLIC_LINKS
#define E_FSERROR_TOO_MANY_SYMBOLIC_LINKS         (E_FSERROR, 0x0006) /* [errno(ELOOP), msg("Too many symbolic links")]
                                                                       * Attempted to follow too many symbolic links (probably as the result of a loop) */
#endif /* !E_FSERROR_TOO_MANY_SYMBOLIC_LINKS */
#ifndef E_FSERROR_ACCESS_DENIED
#define E_FSERROR_ACCESS_DENIED                   (E_FSERROR, 0x0007) /* [errno(EACCES), msg("File access was denied")] */
#endif /* !E_FSERROR_ACCESS_DENIED */
#ifndef E_FSERROR_DISK_FULL
#define E_FSERROR_DISK_FULL                       (E_FSERROR, 0x0008) /* [errno(ENOSPC), msg("Attempted to write when the disk was already full")] */
#endif /* !E_FSERROR_DISK_FULL */
#ifndef E_FSERROR_READONLY
#define E_FSERROR_READONLY                        (E_FSERROR, 0x0009) /* [errno(EROFS), msg("Read-only filesystem")] */
#endif /* !E_FSERROR_READONLY */
#ifndef E_FSERROR_TOO_MANY_HARD_LINKS
#define E_FSERROR_TOO_MANY_HARD_LINKS             (E_FSERROR, 0x000a) /* [errno(EMLINK), msg("Too many hard links already exist for a given file")] */
#endif /* !E_FSERROR_TOO_MANY_HARD_LINKS */
#ifndef E_FSERROR_IS_A_DIRECTORY
#define E_FSERROR_IS_A_DIRECTORY                  (E_FSERROR, 0x000b) /* [errno($action_context == E_FILESYSTEM_IS_A_DIRECTORY_LINK ? EPERM : EISDIR), msg("Did not expect a directory")]
                                                                       * [fld(action_context: uintptr_t, "The context in which a filesystem component was required to not be\n"
                                                                       *                                 "a directory, but was one (One of `E_FILESYSTEM_IS_A_DIRECTORY_*')")]
                                                                       * A directory was found, but something else was expected */
#endif /* !E_FSERROR_IS_A_DIRECTORY */
#ifndef E_FSERROR_NOT_A_SYMBOLIC_LINK
#define E_FSERROR_NOT_A_SYMBOLIC_LINK             (E_FSERROR, 0x000c) /* [errno(ENOENT), msg("Expected a symbolic link")]
                                                                       * A symbolic link was expected when something else was found */
#endif /* !E_FSERROR_NOT_A_SYMBOLIC_LINK */
#ifndef E_FSERROR_IS_A_SYMBOLIC_LINK
#define E_FSERROR_IS_A_SYMBOLIC_LINK              (E_FSERROR, 0x000d) /* [errno(ELOOP), msg("Did not expect a symbolic link")]
                                                                       * [fld(action_context: uintptr_t, "The context in which a filesystem component was required to not be\n"
                                                                       *                                 "a symlink, but was one (One of `E_FILESYSTEM_IS_A_SYMBOLIC_LINK_*')")]
                                                                       * A symbolic link was encountered when none was expected */
#endif /* !E_FSERROR_IS_A_SYMBOLIC_LINK */
/*[[[end]]]*/
#ifndef E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN
#define E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN 1 /* Thrown as the result of `open(path, O_NOFOLLOW)', where `path' refers to a symbolic link */
#endif /* !E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN */
#ifndef E_FILESYSTEM_IS_A_SYMBOLIC_LINK_EXEC
#define E_FILESYSTEM_IS_A_SYMBOLIC_LINK_EXEC 2 /* Thrown as the result of `exec(path, AT_SYMLINK_NOFOLLOW)', where `path' refers to a symbolic link */
#endif /* !E_FILESYSTEM_IS_A_SYMBOLIC_LINK_EXEC */
/*[[[begin]]]*/
#ifndef E_FSERROR_FILE_ALREADY_EXISTS
#define E_FSERROR_FILE_ALREADY_EXISTS             (E_FSERROR, 0x000e) /* [errno(EEXIST), msg("File already exists")]
                                                                       * Thrown as the result of `open(path,O_CREAT|O_EXCL)', where `path' already exists */
#endif /* !E_FSERROR_FILE_ALREADY_EXISTS */
#ifndef E_FSERROR_DIRECTORY_NOT_EMPTY
#define E_FSERROR_DIRECTORY_NOT_EMPTY             (E_FSERROR, 0x000f) /* [errno(ENOTEMPTY), msg("Directory is not empty")]
                                                                       * Attempted to remove a non-empty directory */
#endif /* !E_FSERROR_DIRECTORY_NOT_EMPTY */
#ifndef E_FSERROR_CROSS_DEVICE_LINK
#define E_FSERROR_CROSS_DEVICE_LINK               (E_FSERROR, 0x0010) /* [errno(EXDEV), msg("Cross-device link")]
                                                                       * Attempted to rename() or link() a file from one device to another */
#endif /* !E_FSERROR_CROSS_DEVICE_LINK */
#ifndef E_FSERROR_DIRECTORY_MOVE_TO_CHILD
#define E_FSERROR_DIRECTORY_MOVE_TO_CHILD         (E_FSERROR, 0x0011) /* [errno(EINVAL), msg("Move to child directory")]
                                                                       * Attempted to move a directory such that it would become a child of itself */
#endif /* !E_FSERROR_DIRECTORY_MOVE_TO_CHILD */
#ifndef E_FSERROR_MOUNT_UNSUPPORTED_DEVICE
#define E_FSERROR_MOUNT_UNSUPPORTED_DEVICE        (E_FSERROR, 0x0012) /* [errno(ENOTBLK), msg("The given device cannot be used for mount()")]
                                                                       * Attempted to mount() something that doesn't fulfil the requirements documentd under:
                                                                       * `/kos/src/kernel/include/kernel/fs/filesys.h:ffilesys::ffs_open::<Device requirements>'
                                                                       * Note that contrary to this exception translating to `ENOTBLK', these requirements don't
                                                                       * include  the device needing to be a block-device (or even a device for that matter). As
                                                                       * a matter of fact, pretty much any "normal" file will do, so-long as the file allows for
                                                                       * direct mmap(2) into  user-space (without  overwriting the mmap  operator), and  doesn't
                                                                       * include special overrides for pread(2) or pwrite(2).
                                                                       * Iow: KOS doesn't need loop devices, because you can just directly mount(2) regular files. */
#endif /* !E_FSERROR_MOUNT_UNSUPPORTED_DEVICE */
#ifndef E_FSERROR_MOUNT_NEEDS_DEVICE
#define E_FSERROR_MOUNT_NEEDS_DEVICE              (E_FSERROR, 0x0013) /* [errno(ENOTBLK), msg("This filesystem type requires a device")]
                                                                       * Attempted to mount() a filesystem without a device, when that filesystem requires one */
#endif /* !E_FSERROR_MOUNT_NEEDS_DEVICE */
#ifndef E_FSERROR_WRONG_FILE_SYSTEM
#define E_FSERROR_WRONG_FILE_SYSTEM               (E_FSERROR, 0x0014) /* [errno(ENODEV), msg("Invalid file-system type for mount()")]
                                                                       * Attempted to mount a device  with the wrong file system.  Also
                                                                       * thrown if the device is already mounted, but using a different
                                                                       * filesystem type. */
#endif /* !E_FSERROR_WRONG_FILE_SYSTEM */
#ifndef E_FSERROR_UNKNOWN_FILE_SYSTEM
#define E_FSERROR_UNKNOWN_FILE_SYSTEM             (E_FSERROR, 0x0015) /* [errno(ENODEV), msg("Unknown filesystem type")]
                                                                       * Attempted to mount an unknown file system type */
#endif /* !E_FSERROR_UNKNOWN_FILE_SYSTEM */
#ifndef E_FSERROR_CORRUPTED_FILE_SYSTEM
#define E_FSERROR_CORRUPTED_FILE_SYSTEM           (E_FSERROR, 0x0016) /* [errno(ENODEV), msg("Corrupted filesystem data")]
                                                                       * The filesystem data found within a given device has been corrupted and cannot be mounted */
#endif /* !E_FSERROR_CORRUPTED_FILE_SYSTEM */
#ifndef E_FSERROR_PATH_ALREADY_MOUNTED
#define E_FSERROR_PATH_ALREADY_MOUNTED            (E_FSERROR, 0x0017) /* [errno(EBUSY), msg("Path has already been mounted")]
                                                                       * Attempted to create a new mounting point for a path that has already been mounted */
#endif /* !E_FSERROR_PATH_ALREADY_MOUNTED */
#ifndef E_FSERROR_NOT_A_MOUNTING_POINT
#define E_FSERROR_NOT_A_MOUNTING_POINT            (E_FSERROR, 0x0018) /* [errno(EINVAL), msg("Path hasn't been mounted")]
                                                                       * Attempted to umount() a path that isn't a mounting point */
#endif /* !E_FSERROR_NOT_A_MOUNTING_POINT */
#ifndef E_FSERROR_IS_A_MOUNTING_POINT
#define E_FSERROR_IS_A_MOUNTING_POINT             (E_FSERROR, 0x0019) /* [errno(EBUSY), msg("Path is a mounting point")]
                                                                       * Attempted to rmdir() or rename() a mounting point */
#endif /* !E_FSERROR_IS_A_MOUNTING_POINT */
#ifndef E_FSERROR_FILE_TOO_BIG
#define E_FSERROR_FILE_TOO_BIG                    (E_FSERROR, 0x001a) /* [errno(EFBIG), msg("File would become too large")]
                                                                       * Attempted to write() or truncate() a file beyond its fs-imposed limit. */
#endif /* !E_FSERROR_FILE_TOO_BIG */
#ifndef E_FSERROR_UNSUPPORTED_OPERATION
#define E_FSERROR_UNSUPPORTED_OPERATION           (E_FSERROR, 0x0100) /* [msg("Unsupported filesystem operation")]
                                                                       * [errno(($operation_id == E_FILESYSTEM_OPERATION_SEEK || $operation_id == E_FILESYSTEM_OPERATION_PREAD ||
                                                                       *         $operation_id == E_FILESYSTEM_OPERATION_PWRITE) ? ESPIPE :
                                                                       *        ($operation_id == E_FILESYSTEM_OPERATION_READ || $operation_id == E_FILESYSTEM_OPERATION_WRITE ||
                                                                       *         $operation_id == E_FILESYSTEM_OPERATION_SYNC) ? EINVAL :
                                                                       *        ($operation_id == E_FILESYSTEM_OPERATION_READDIR) ? ENOTDIR :
                                                                       *        ($operation_id == E_FILESYSTEM_OPERATION_MMAP || $operation_id == E_FILESYSTEM_OPERATION_ALLOCATE) ? ENODEV :
                                                                       *        ($operation_id == E_FILESYSTEM_OPERATION_CREAT) ? EROFS :
                                                                       *        EPERM)]
                                                                       * [fld(operation_id: uintptr_t, "The unsupported operation (One of `E_FILESYSTEM_OPERATION_*')")]
                                                                       * The object does not support the operation */
#endif /* !E_FSERROR_UNSUPPORTED_OPERATION */
/*[[[end]]]*/
/* Notes on errno translation for `E_FSERROR_UNSUPPORTED_OPERATION':
 *  - E_FILESYSTEM_OPERATION_SEEK, E_FILESYSTEM_OPERATION_PREAD, E_FILESYSTEM_OPERATION_PWRITE -> ESPIPE:
 *    - `man 2 lseek' documents: ESPIPE <=> fd is associated with a pipe, socket, or FIFO.
 *    - `man 2 pread' documents: ESPIPE <=> The file is incapable of seeking. (same for `pwrite(2)')
 *  - E_FILESYSTEM_OPERATION_READ, E_FILESYSTEM_OPERATION_WRITE -> EINVAL:
 *    - `man 2 read' documents: EINVAL <=> fd is attached to an object which is unsuitable for reading. (same for `write(2)')
 *                              FIXME (also documented): EISDIR <=> fd refers to a directory
 *  - E_FILESYSTEM_OPERATION_TRUNC -> EPERM:
 *    - `man 2 ftruncate' documents: EPERM <=> The underlying filesystem does not support extending a file beyond its current size.
 *  - E_FILESYSTEM_OPERATION_READDIR -> ENOTDIR:
 *    - `man 2 readdir' documents: ENOTDIR <=> File descriptor does not refer to a directory.
 *  - E_FILESYSTEM_OPERATION_CREAT -> EROFS:
 *    - `man 2 open' documents: EINVAL     <=> The filesystem does not support the O_DIRECT flag
 *                              EOPNOTSUPP <=> The filesystem containing pathname does not support O_TMPFILE.
 *                              EROFS      <=> pathname refers to a file on a read-only filesystem and write access was requested.
 *  - E_FILESYSTEM_OPERATION_MKDIR -> EPERM:
 *    - `man 2 mkdir' documents: EPERM <=> The filesystem containing pathname does not support the creation of directories.
 *  - E_FILESYSTEM_OPERATION_SYMLINK -> EPERM:
 *    - `man 2 symlink' documents: EPERM <=> The filesystem containing `linkpath' does not support the creation of symbolic links.
 *  - E_FILESYSTEM_OPERATION_MKNOD -> EPERM:
 *    - `man 2 symlink' documents: EPERM <=> [...] the filesystem containing pathname does not support the type of node requested.
 *  - E_FILESYSTEM_OPERATION_LINK -> EPERM:
 *    - `man 2 link' documents: EPERM <=> The filesystem containing `oldpath' and `newpath' does not support the creation of hard links.
 *  - E_FILESYSTEM_OPERATION_RENAME -> EPERM:
 *    - `man 2 rename' documents: EPERM <=> [...] the filesystem containing `oldpath' does not support renaming of the type requested.
 *  - E_FILESYSTEM_OPERATION_UNLINK -> EPERM:
 *    - `man 2 unlink' documents: EPERM <=> The system does not allow unlinking of directories. [...] (Linux only) The filesystem does not allow unlinking of files.
 *  - E_FILESYSTEM_OPERATION_RMDIR -> EPERM:
 *    - `man 2 rmdir' documents: EPERM <=> The filesystem containing pathname does not support the removal of directories.
 *  - E_FILESYSTEM_OPERATION_ATTRIB/E_FILESYSTEM_OPERATION_WRATTR -> EPERM:
 *    - `man 2 chmod' documents: EPERM <=> The file is marked immutable [...]
 *    - `man 2 chown' documents: EPERM <=> The file is marked immutable [...]
 *  - E_FILESYSTEM_OPERATION_MMAP -> ENODEV:
 *    - `man 2 mmap' documents: ENODEV <=> The underlying filesystem of the specified file does not support memory mapping.
 *  - E_FILESYSTEM_OPERATION_SYNC, E_FILESYSTEM_OPERATION_DATASYNC -> EINVAL:
 *    - `man 2 fsync' documents: EINVAL <=> fd is bound to a special file [...] which does not support synchronization. (same for `fdatasync(2)')
 *  - E_FILESYSTEM_OPERATION_STAT -> EPERM:
 *    - Non-conforming; on linux, anything can be stat'd
 *  - E_FILESYSTEM_OPERATION_ALLOCATE -> ENODEV:
 *    - `man 2 fallocate' documents: ENODEV <=> fd does  not refer to a  regular file or a  directory
 *                                   FIXME (also documented): ESPIPE <=> fd refers to a pipe or FIFO.
 *                                   FIXME (also documented): EOPNOTSUPP <=> The filesystem containing the file referred to by fd does
 *                                                                           not support this operation; or the mode is not  supported
 *                                                                           by the filesystem containing the file referred to by fd.
 */
/*[[[begin]]]*/





/************************************************************************/
/* E_NET_ERROR                                                          */
/************************************************************************/
#ifndef E_NET_ERROR
#define E_NET_ERROR                               (0x0081)              /* [msg("Network error")] */
#endif /* !E_NET_ERROR */
#ifndef E_NET_HOST_UNREACHABLE
#define E_NET_HOST_UNREACHABLE                    (E_NET_ERROR, 0x0001) /* [errno(EHOSTUNREACH), msg("The given host cannot be reached")]
                                                                         * XXX: Exception pointers, such as the IP (maybe?) */
#endif /* !E_NET_HOST_UNREACHABLE */
#ifndef E_NET_ADDRESS_IN_USE
#define E_NET_ADDRESS_IN_USE                      (E_NET_ERROR, 0x0002) /* [errno(EADDRINUSE), msg("The specified address is already in use")]
                                                                         * [fld(context: unsigned int, "The context under which the address is already in use (one of `E_NET_ADDRESS_IN_USE_CONTEXT_*')")] */
#endif /* !E_NET_ADDRESS_IN_USE */
#ifndef E_NET_MESSAGE_TOO_LONG
#define E_NET_MESSAGE_TOO_LONG                    (E_NET_ERROR, 0x0003) /* [errno(EMSGSIZE), msg("The given message is too long")]
                                                                         * [fld(req_length: size_t, "The requested message length")]
                                                                         * [fld(max_length: size_t, "The max possible message length")] */
#endif /* !E_NET_MESSAGE_TOO_LONG */
#ifndef E_NET_CONNECTION_ABORT
#define E_NET_CONNECTION_ABORT                    (E_NET_ERROR, 0x0004) /* [errno(ECONNABORTED), msg("accept() failed to fully establish a connection")] */
#endif /* !E_NET_CONNECTION_ABORT */
#ifndef E_NET_CONNECTION_REFUSED
#define E_NET_CONNECTION_REFUSED                  (E_NET_ERROR, 0x0005) /* [errno(ECONNREFUSED), msg("connect() or recv() found no one to be listening on the remote address")] */
#endif /* !E_NET_CONNECTION_REFUSED */
#ifndef E_NET_CONNECTION_RESET
#define E_NET_CONNECTION_RESET                    (E_NET_ERROR, 0x0006) /* [errno(ECONNRESET), msg("The connection was reset by the remote during send()")] */
#endif /* !E_NET_CONNECTION_RESET */
#ifndef E_NET_TIMEOUT
#define E_NET_TIMEOUT                             (E_NET_ERROR, 0x0007) /* [errno(ETIMEDOUT), msg("Establishing a connection has failed due to a timeout")] */
#endif /* !E_NET_TIMEOUT */
#ifndef E_NET_UNREACHABLE
#define E_NET_UNREACHABLE                         (E_NET_ERROR, 0x0008) /* [errno(ENETUNREACH), msg("The requested network cannot be reached")] */
#endif /* !E_NET_UNREACHABLE */
#ifndef E_NET_ADDRESS_NOT_AVAILABLE
#define E_NET_ADDRESS_NOT_AVAILABLE               (E_NET_ERROR, 0x0009) /* [errno(EADDRNOTAVAIL), msg("Attempted to bind() to a non-local address")] */
#endif /* !E_NET_ADDRESS_NOT_AVAILABLE */
#ifndef E_NET_SHUTDOWN
#define E_NET_SHUTDOWN                            (E_NET_ERROR, 0x000a) /* [errno(EPIPE), msg("Attempted to write() after the local end had been shutdown()")] */
#endif /* !E_NET_SHUTDOWN */





/************************************************************************/
/* E_IOERROR                                                            */
/************************************************************************/
#ifndef E_IOERROR
#define E_IOERROR                                 (0x0082)            /* [errno(EIO), msg("Hardware error, or miss-behaving/miss-configured device")]
                                                                       * [fld(subsystem: uintptr_t, "The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*')")]
                                                                       * [fld(reason:    uintptr_t, "A more precise description of the error (One of `E_IOERROR_REASON_*')")] */
#endif /* !E_IOERROR */
#ifndef E_IOERROR_ERRORBIT
#define E_IOERROR_ERRORBIT                        (E_IOERROR, 0x0001) /* [msg("A hardware error bit has been set")] */
#endif /* !E_IOERROR_ERRORBIT */
#ifndef E_IOERROR_TIMEOUT
#define E_IOERROR_TIMEOUT                         (E_IOERROR, 0x0002) /* [msg("Hardware component timed out")] */
#endif /* !E_IOERROR_TIMEOUT */
#ifndef E_IOERROR_READONLY
#define E_IOERROR_READONLY                        (E_IOERROR, 0x0003) /* [msg("Attempted to write to read-only disk component")] */
#endif /* !E_IOERROR_READONLY */
#ifndef E_IOERROR_BADBOUNDS
#define E_IOERROR_BADBOUNDS                       (E_IOERROR, 0x0004) /* [msg("Attempted to write beyond the end of a disk")] */
#endif /* !E_IOERROR_BADBOUNDS */
#ifndef E_IOERROR_NODATA
#define E_IOERROR_NODATA                          (E_IOERROR, 0x0005) /* [msg("No data could be read/written")] */
#endif /* !E_IOERROR_NODATA */





/************************************************************************/
/* E_NOT_EXECUTABLE                                                     */
/************************************************************************/
#ifndef E_NOT_EXECUTABLE
#define E_NOT_EXECUTABLE                          (0x0083)                   /* [errno(ENOEXEC), msg("The named file was not recognized as a valid executable")] */
#endif /* !E_NOT_EXECUTABLE */
#ifndef E_NOT_EXECUTABLE_NOEXEC
#define E_NOT_EXECUTABLE_NOEXEC                   (E_NOT_EXECUTABLE, 0x0001) /* [msg("File does not have execute permissions")]
                                                                              * Cannot execute a file without execute permission (s.a. `chmod(2)') */
#endif /* !E_NOT_EXECUTABLE_NOEXEC */
#ifndef E_NOT_EXECUTABLE_NOT_REGULAR
#define E_NOT_EXECUTABLE_NOT_REGULAR              (E_NOT_EXECUTABLE, 0x0002) /* [msg("Can only execute regular files")]
                                                                              * Cannot execute anything other than a regular (S_IFREG) file */
#endif /* !E_NOT_EXECUTABLE_NOT_REGULAR */
#ifndef E_NOT_EXECUTABLE_NOT_A_BINARY
#define E_NOT_EXECUTABLE_NOT_A_BINARY             (E_NOT_EXECUTABLE, 0x0003) /* [msg("Can only execute binary files, or unknown/unsupported binary format")]
                                                                              * The given file's contents weren't recognized as a known/valid binary format */
#endif /* !E_NOT_EXECUTABLE_NOT_A_BINARY */
#ifndef E_NOT_EXECUTABLE_FAULTY
#define E_NOT_EXECUTABLE_FAULTY                   (E_NOT_EXECUTABLE, 0x0004) /* [msg("The executable's binary file is faulty")]
                                                                              * [fld(format: uintptr_t, "The binary format (One of `E_NOT_EXECUTABLE_FAULTY_FORMAT_*')")]
                                                                              * [fld(reason: uintptr_t, "The format-specific reason why the load failed (One of `E_NOT_EXECUTABLE_FAULTY_REASON_*_*')")] */
#endif /* !E_NOT_EXECUTABLE_FAULTY */
#ifndef E_NOT_EXECUTABLE_TOOLARGE
#define E_NOT_EXECUTABLE_TOOLARGE                 (E_NOT_EXECUTABLE, 0x0005) /* [msg("Executable file is too large")]
                                                                              * Only when loading drivers: Executable file is too large */
#endif /* !E_NOT_EXECUTABLE_TOOLARGE */
#ifndef E_NOT_EXECUTABLE_TOOSMALL
#define E_NOT_EXECUTABLE_TOOSMALL                 (E_NOT_EXECUTABLE, 0x0006) /* [msg("Executable file is too small")]
                                                                              * Only when loading drivers: Executable file is too small */
#endif /* !E_NOT_EXECUTABLE_TOOSMALL */





/************************************************************************/
/* E_INSUFFICIENT_RIGHTS                                                */
/************************************************************************/
#ifndef E_INSUFFICIENT_RIGHTS
#define E_INSUFFICIENT_RIGHTS                     (0x0084) /* [errno(EACCES), msg("Insufficient Rights")]
                                                            * [fld(capability: intptr_t, "The missing capability (one of `CAP_*' from `<kos/capability.h>')")] */
#endif /* !E_INSUFFICIENT_RIGHTS */





/************************************************************************/
/* E_BUFFER_TOO_SMALL                                                   */
/************************************************************************/
#ifndef E_BUFFER_TOO_SMALL
#define E_BUFFER_TOO_SMALL                        (0x0090) /* [errno(ERANGE), msg("The provided buffer is too small")]
                                                            * [fld(req_size:   size_t, "The required buffer size")]
                                                            * [fld(given_size: size_t, "The given buffer size")] */
#endif /* !E_BUFFER_TOO_SMALL */
#ifndef _E_BUFFER_TOO_SMALL_EINVAL
#define _E_BUFFER_TOO_SMALL_EINVAL                (E_BUFFER_TOO_SMALL, 0x0001) /* [errno(EINVAL)] Needed for linux compat. */
#endif /* !_E_BUFFER_TOO_SMALL_EINVAL */





/************************************************************************/
/* E_UNICODE_ERROR                                                      */
/************************************************************************/
#ifndef E_UNICODE_ERROR
#define E_UNICODE_ERROR                           (0x0091) /* [errno(EILSEQ), msg("Unicode error")]
                                                            * An illegal sequence was encountered in a unicode string */
#endif /* !E_UNICODE_ERROR */





/************************************************************************/
/* E_INTERRUPT                                                          */
/************************************************************************/
#ifndef E_INTERRUPT
#define E_INTERRUPT                               (0xf000)              /* [errno(EINTR), msg("Interrupt")]
                                                                         * The thread has  been interrupted by  a RPC function  or
                                                                         * posix signal, causing a premature return to user-space.
                                                                         * NOTE: If the  system communication  facility that  was used  for the  interrupt
                                                                         *       supports restarting (e.g. load memory following a #PF on X86), or if  the
                                                                         *       interrupt happened during a restartable system call (e.g. `sys_close()'),
                                                                         *       and SA_RESTART or RPC_SYSRESTART_RESTART  are used, this exception  isn't
                                                                         *       propagated into user-space, but rather causes the underlying interrupt or
                                                                         *       system call to be restarted.
                                                                         * KOS Implements 3 distinct system call interrupt-restart behaviors:
                                                                         *  #1: The system call is always restarted (this behavior is also used when  some
                                                                         *      other type of interrupt handler is interrupted, such as load memory during
                                                                         *      a  lazy initialization page-fault  operation, or when  loading a file into
                                                                         *      memory). This mainly includes system calls where interrupts are undesired,
                                                                         *      or would otherwise be unexpected, most notably ~cleanup~ system calls such
                                                                         *      as `sys_close(2)' or `sys_munmap(2)' (or most importantly: `sys_exit(2)').
                                                                         *  #2: The system call  is never  restarted (required for  some system  calls
                                                                         *      that are meant to wait for events internally delivered by an interrupt
                                                                         *      mechanism, such as `sigtimedwait()'; the behavior here mirrors what is
                                                                         *      also done by linux, as described on this page:
                                                                         *      `http://man7.org/linux/man-pages/man7/signal.7.html')
                                                                         *  #3: The default behavior applicable to all remaining system call, that is to
                                                                         *      restart the system call  based on SA_RESTART or  RPC_SYSRESTART_RESTART. */
#endif /* !E_INTERRUPT */
#ifndef E_INTERRUPT_USER_RPC
#define E_INTERRUPT_USER_RPC                      (E_INTERRUPT, 0x0001) /* [msg("Interrupt from user RPC")] Unwind in order to execute
                                                                         * an RPC callback before  returning to user-space. Thrown  by
                                                                         * `task_serve()' and caught in `userexcpt_handler()' */
#endif /* !E_INTERRUPT_USER_RPC */





/************************************************************************/
/* RTL Thread/Process exit (E_EXIT_THREAD, E_EXIT_PROCESS)              */
/************************************************************************/
/*[[[end]]]*/

/* The following are not ~real~ exception codes, but are used by internal kernel logic.
 * Throwing them in userspace doesn't have any affects (they behave just like  throwing
 * any  other exception). Throwing them in kernel-space  works as intended, in that the
 * `_E_STOP_PROCESS' will cause the process to stop execution until receiving SIG_CONT,
 * and  the `SIG_CORE' exception to trigger a coredump. Handling of this is done at the
 * same time as the E_EXIT_* exceptions, that is just before returning to user-space.
 *
 * Used in: `/kos/src/kernel/core/misc/except-handler-userexcept.c.inl' */
#define _E_STOP_PROCESS (0xfe7f) /* [fld(procstat: uintptr_t, "Process status")] Marker for: `SIG_STOP' */
#define _E_CORE_PROCESS (0xfe82) /* [fld(procstat: uintptr_t)][fld(si_errno: int)][fld(si_code: int)] Marker for: `SIG_CORE' */

/*[[[begin]]]*/
#ifndef E_EXIT_THREAD
#define E_EXIT_THREAD                             (0xfe40) /* [fld(exit_code: uintptr_t, "The thread exit status")]
                                                            * The thread is supposed to terminate */
#endif /* !E_EXIT_THREAD */
#ifndef E_EXIT_PROCESS
#define E_EXIT_PROCESS                            (0xfe81) /* [fld(exit_code: uintptr_t, "The process exit status")]
                                                            * The entire process is supposed to terminate */
#endif /* !E_EXIT_PROCESS */





/************************************************************************/
/* E_UNHANDLED_INTERRUPT                                                */
/************************************************************************/
#ifndef E_UNHANDLED_INTERRUPT
#define E_UNHANDLED_INTERRUPT                     (0xfeff) /* [errno(EFAULT), msg("Unhandled system interrupt")]
                                                            * [fld(opcode: uintptr_t)]
                                                            * [fld(intno: uintptr_t)]
                                                            * [fld(ecode: uintptr_t)] */
#endif /* !E_UNHANDLED_INTERRUPT */





/************************************************************************/
/* E_SEGFAULT                                                           */
/************************************************************************/
#ifndef E_SEGFAULT
#define E_SEGFAULT                                (0xff01)             /* [errno(EFAULT), msg("Segmentation fault")]
                                                                        * [fld(addr:    void *,    "The virtual memory address where the fault happened")]
                                                                        * [fld(context: uintptr_t, "Fault context (Set of `E_SEGFAULT_CONTEXT_*')")]
                                                                        * Segmentation fault (invalid memory access) */
#endif /* !E_SEGFAULT */
#ifndef E_SEGFAULT_UNMAPPED
#define E_SEGFAULT_UNMAPPED                       (E_SEGFAULT, 0x0001) /* [msg("Attempted to access a faulty memory location")] */
#endif /* !E_SEGFAULT_UNMAPPED */
#ifndef E_SEGFAULT_READONLY
#define E_SEGFAULT_READONLY                       (E_SEGFAULT, 0x0002) /* [msg("Attempted to write to a read-only memory location")] */
#endif /* !E_SEGFAULT_READONLY */
#ifndef E_SEGFAULT_NOTREADABLE
#define E_SEGFAULT_NOTREADABLE                    (E_SEGFAULT, 0x0003) /* [msg("Attempted to read from a memory location that is not readable")] */
#endif /* !E_SEGFAULT_NOTREADABLE */
#ifndef E_SEGFAULT_NOTEXECUTABLE
#define E_SEGFAULT_NOTEXECUTABLE                  (E_SEGFAULT, 0x0004) /* [msg("Attempted to execute a non-executable memory location")] */
#endif /* !E_SEGFAULT_NOTEXECUTABLE */
#ifndef E_SEGFAULT_NOTATOMIC
#define E_SEGFAULT_NOTATOMIC                      (E_SEGFAULT, 0x0005) /* [msg("Attempted to perform an impossible atomic operation")]
                                                                        * [fld(size:      size_t,    "The number of consecutive bytes accessed")]
                                                                        * [fld(oldval_lo: uintptr_t, "Low data word of the expected old value")]
                                                                        * [fld(oldval_hi: uintptr_t, "High data word of the expected old value")]
                                                                        * [fld(newval_lo: uintptr_t, "Low data word of the intended new value")]
                                                                        * [fld(newval_hi: uintptr_t, "High data word of the intended new value")] */
#endif /* !E_SEGFAULT_NOTATOMIC */
#ifndef E_SEGFAULT_UNALIGNED
#define E_SEGFAULT_UNALIGNED                      (E_SEGFAULT, 0x0006) /* [msg("Attempted to access an unaligned pointer")]
                                                                        * [fld(required_alignemnt: size_t, "The required alignment of `addr' (power-of-2)")] */
#endif /* !E_SEGFAULT_UNALIGNED */
#ifndef E_SEGFAULT_NONCONTINUOUS
#define E_SEGFAULT_NONCONTINUOUS                  (E_SEGFAULT, 0x0007) /* [msg("File mapping isn't continuous")] */
#endif /* !E_SEGFAULT_NONCONTINUOUS */
/*[[[end]]]*/
#ifndef E_SEGFAULT_CONTEXT_FAULT
#define E_SEGFAULT_CONTEXT_FAULT    0x0001 /* Faulty address */
#endif /* !E_SEGFAULT_CONTEXT_FAULT */
#ifndef E_SEGFAULT_CONTEXT_WRITING
#define E_SEGFAULT_CONTEXT_WRITING  0x0002 /* FLAG: The fault happened during a write operation */
#endif /* !E_SEGFAULT_CONTEXT_WRITING */
#ifndef E_SEGFAULT_CONTEXT_USERCODE
#define E_SEGFAULT_CONTEXT_USERCODE 0x0004 /* FLAG: The access was performed for user-space */
#endif /* !E_SEGFAULT_CONTEXT_USERCODE */
#ifndef E_SEGFAULT_CONTEXT_NONCANON
#define E_SEGFAULT_CONTEXT_NONCANON 0x0008 /* Non-canonical address */
#endif /* !E_SEGFAULT_CONTEXT_NONCANON */
#ifndef E_SEGFAULT_CONTEXT_EXEC
#define E_SEGFAULT_CONTEXT_EXEC     0x0010 /* The instruction pointer's location caused the fault */
#endif /* !E_SEGFAULT_CONTEXT_EXEC */
#ifndef E_SEGFAULT_CONTEXT_FUTEX
#define E_SEGFAULT_CONTEXT_FUTEX    0x2000 /* Attempted to create a futex at an unmapped address */
#endif /* !E_SEGFAULT_CONTEXT_FUTEX */
#ifndef E_SEGFAULT_CONTEXT_UNMAP
#define E_SEGFAULT_CONTEXT_UNMAP    0x4000 /* Attempted to unmap an undefined memory address */
#endif /* !E_SEGFAULT_CONTEXT_UNMAP */
#ifndef E_SEGFAULT_CONTEXT_VIO
#define E_SEGFAULT_CONTEXT_VIO      0x8000 /* FLAG: The access was perform by VIO */
#endif /* !E_SEGFAULT_CONTEXT_VIO */
/*[[[begin]]]*/





/************************************************************************/
/* E_BREAKPOINT                                                         */
/************************************************************************/
#ifndef E_BREAKPOINT
#define E_BREAKPOINT                              (0xff02) /* [errno(EINVAL), msg("Breakpoint")] */
#endif /* !E_BREAKPOINT */





/************************************************************************/
/* E_DIVIDE_BY_ZERO                                                     */
/************************************************************************/
#ifndef E_DIVIDE_BY_ZERO
#define E_DIVIDE_BY_ZERO                          (0xff03) /* [errno(EINVAL), msg("Divide by zero")] */
#endif /* !E_DIVIDE_BY_ZERO */





/************************************************************************/
/* E_OVERFLOW                                                           */
/************************************************************************/
#ifndef E_OVERFLOW
#define E_OVERFLOW                                (0xff04) /* [errno(EOVERFLOW), msg("Overflow")] */
#endif /* !E_OVERFLOW */





/************************************************************************/
/* E_ILLEGAL_INSTRUCTION                                                */
/************************************************************************/
#if defined(__i386__) || defined(__x86_64__)
#ifndef E_ILLEGAL_INSTRUCTION
#define E_ILLEGAL_INSTRUCTION                     (0xff05)                        /* [errno(EPERM), msg("Illegal instruction")]
                                                                                   * [fld(opcode:   uintptr_t, "The opcode that caused the exception\n"
                                                                                   *                           "NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'")]
                                                                                   * [fld(op_flags: uintptr_t, "Opcode flags (set of `EMU86_F_*')")]
                                                                                   * Illegal/privileged/restricted instruction/register/operand/addressing mode or trap encountered */
#endif /* !E_ILLEGAL_INSTRUCTION */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPCODE
#define E_ILLEGAL_INSTRUCTION_BAD_OPCODE          (E_ILLEGAL_INSTRUCTION, 0x0001) /* [msg("Unknown instruction")]
                                                                                   * The instruction opcode was not recognized */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE
#define E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE  (E_ILLEGAL_INSTRUCTION, 0x0002) /* [msg("Unsupported instruction")]
                                                                                   * The instruction's opcode is not supported by the host (not thrown if the instruction was emulated) */
#endif /* !E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE
#define E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE   (E_ILLEGAL_INSTRUCTION, 0x0003) /* [msg("Privileged instruction")]
                                                                                   * The calling code does not have the necessary privilege to invoke the instruction `opcode' */
#endif /* !E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPERAND
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND         (E_ILLEGAL_INSTRUCTION, 0x0004) /* [msg("Invalid instruction operand")]
                                                                                   * [fld(what:     uintptr_t, "For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*')")]
                                                                                   * [fld(regno:    uintptr_t, "The accessed register index (from `<asm/register.h>')\n"
                                                                                   *                           "NOTE: When set to `X86_REGISTER_MSR', then the next 3\n"
                                                                                   *                           "      pointers are index(%ecx), loval(%eax), hival(%edx)")]
                                                                                   * [fld(offset:   uintptr_t, "An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)\n"
                                                                                   *                           "In case an MSR register was accessed, this is the MSR index")]
                                                                                   * [fld(regval:   uintptr_t, "The associated register value")]
                                                                                   * [fld(regval2:  uintptr_t, "The associated register value (high 32 bits in case of an MSR write)")]
                                                                                   * An operand of the instruction is invalid */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPERAND */
#ifndef E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX
#define E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX      (E_ILLEGAL_INSTRUCTION, 0x8601) /* [msg("Unsupported instruction prefix")]
                                                                                   * An unsupported prefix byte was encountered */
#endif /* !E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX */
#ifndef E_ILLEGAL_INSTRUCTION_X86_TOO_LONG
#define E_ILLEGAL_INSTRUCTION_X86_TOO_LONG        (E_ILLEGAL_INSTRUCTION, 0x8602) /* [msg("Instruction too long")]
                                                                                   * Including all prefixes, the instruction is too long */
#endif /* !E_ILLEGAL_INSTRUCTION_X86_TOO_LONG */
#ifndef E_ILLEGAL_INSTRUCTION_X86_INTERRUPT
#define E_ILLEGAL_INSTRUCTION_X86_INTERRUPT       (E_ILLEGAL_INSTRUCTION, 0x8603) /* [fld(intno:  uintptr_t, "The system interrupt that occurred")]
                                                                                   * [fld(ecode:  uintptr_t, "The error code associated with that interrupt")]
                                                                                   * [fld(segval: uintptr_t, "The segment value of the segment in question")]
                                                                                   * A kernel-space instruction has caused an unhandled #GP or #SS */
#endif /* !E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */
#else /* __i386__ || __x86_64__ */
#ifndef E_ILLEGAL_INSTRUCTION
#define E_ILLEGAL_INSTRUCTION                     (0xff05)                        /* [errno(EPERM), msg("Illegal instruction")]
                                                                                   * [fld(opcode:   uintptr_t, "The opcode that caused the exception")]
                                                                                   * Illegal/privileged/restricted instruction/register/operand/addressing mode or trap encountered */
#endif /* !E_ILLEGAL_INSTRUCTION */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPCODE
#define E_ILLEGAL_INSTRUCTION_BAD_OPCODE          (E_ILLEGAL_INSTRUCTION, 0x0001) /* [msg("Unknown instruction")]
                                                                                   * The instruction opcode was not recognized */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE
#define E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE  (E_ILLEGAL_INSTRUCTION, 0x0002) /* [msg("Unsupported instruction")]
                                                                                   * The instruction's opcode is not supported by the host (not thrown if the instruction was emulated) */
#endif /* !E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE
#define E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE   (E_ILLEGAL_INSTRUCTION, 0x0003) /* [msg("Privileged instruction")]
                                                                                   * The calling code does not have the necessary privilege to invoke the instruction `opcode' */
#endif /* !E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPERAND
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND         (E_ILLEGAL_INSTRUCTION, 0x0004) /* [msg("Invalid instruction operand")]
                                                                                   * [fld(what:     uintptr_t, "For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*')")]
                                                                                   * [fld(regno:    uintptr_t, "The accessed register index (from `<asm/register.h>')")]
                                                                                   * [fld(regval:   uintptr_t, "The associated register value")]
                                                                                   * An operand of the instruction is invalid */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPERAND */
#endif /* !__i386__ && !__x86_64__ */
/*[[[end]]]*/
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY   0x0001 /* Unexpectedly, the instruction has a memory operand (the memory operand's address is stored in `offset') */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER 0x0002 /* Unexpectedly, the instruction has a register operand (register and its value is stored in `regno' and `regval') */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER */
#ifndef E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE               0x0003 /* A register operand has a bad value */
#endif /* !E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE */
/*[[[begin]]]*/

#ifndef E_ILLEGAL_INSTRUCTION_REGISTER
#if defined(__i386__) || defined(__x86_64__)
#define E_ILLEGAL_INSTRUCTION_REGISTER            (E_ILLEGAL_INSTRUCTION, 0x0011) /* [msg("Invalid register access")]
                                                                                   * [fld(how:      uintptr_t, "How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*')")]
                                                                                   * [fld(regno:    uintptr_t, "The accessed register index (from `<asm/register.h>')\n"
                                                                                   *                           "NOTE: When set to `X86_REGISTER_MSR', then the next 3\n"
                                                                                   *                           "      pointers are index(%ecx), loval(%eax), hival(%edx)")]
                                                                                   * [fld(offset:   uintptr_t, "An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)\n"
                                                                                   *                           "In case an MSR register was accessed, this is the MSR index")]
                                                                                   * [fld(regval:   uintptr_t, "The associated register value (or 0 for read operations)")]
                                                                                   * [fld(regval2:  uintptr_t, "The associated register value (or 0 for read operations) (high 32 bits in case of an MSR write)")]
                                                                                   * Attempted to access an invalid register `regno' (one of `<ARCH>_REGISTER_*') */
#else /* __i386__ || __x86_64__ */
#define E_ILLEGAL_INSTRUCTION_REGISTER            (E_ILLEGAL_INSTRUCTION, 0x0011) /* [msg("Invalid register access")]
                                                                                   * [fld(how:      uintptr_t, "How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*')")]
                                                                                   * [fld(regno:    uintptr_t, "The accessed register index (from `<asm/register.h>')\n")]
                                                                                   * [fld(regval:   uintptr_t, "The associated register value (or 0 for read operations)")]
                                                                                   * Attempted to access an invalid register `regno' (one of `<ARCH>_REGISTER_*') */
#endif /* !__i386__ && !__x86_64__ */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER */
/*[[[end]]]*/
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_RDINV
#define E_ILLEGAL_INSTRUCTION_REGISTER_RDINV   0x0001 /* Read from invalid register */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_RDINV */
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
#define E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV   0x0002 /* Read from privileged register */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV */
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_WRINV
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRINV   0x0011 /* Write to invalid register */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_WRINV */
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV   0x0012 /* Write to privileged register */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV */
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD   0x0013 /* Bad value written to register */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD */
#if defined(__i386__) || defined(__x86_64__)
#ifndef E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG 0x0014 /* Attempted to assign a non-present segment */
#endif /* !E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG */
#endif /* __i386__ || __x86_64__ */
/*[[[begin]]]*/





/************************************************************************/
/* E_STACK_OVERFLOW                                                     */
/************************************************************************/
#ifndef E_STACK_OVERFLOW
#define E_STACK_OVERFLOW                          (0xff06) /* [errno(EFAULT), msg("Stack overflow")]
                                                            * Thrown in kernel space when: #PF->#DF with ESP/RSP below stack_base
                                                            * Thrown in user space when:   #PF ontop of a guard page with no remaining funds */
#endif /* !E_STACK_OVERFLOW */





/************************************************************************/
/* E_INDEX_ERROR                                                        */
/************************************************************************/
#ifndef E_INDEX_ERROR
#define E_INDEX_ERROR                             (0xff07)                /* [errno(ERANGE)]
                                                                           * The BOUND instruction was executed with an out-of-bounds index */
#endif /* !E_INDEX_ERROR */
#ifndef E_INDEX_ERROR_OUT_OF_BOUNDS
#define E_INDEX_ERROR_OUT_OF_BOUNDS               (E_INDEX_ERROR, 0x0001) /* [fld(index: intptr_t, "The addressed index")]
                                                                           * [fld(min:   intptr_t, "The low bound of valid indices")]
                                                                           * [fld(max:   intptr_t, "The high bound of valid indices")]
                                                                           * An index was outside of the min/max bounds */
#endif /* !E_INDEX_ERROR_OUT_OF_BOUNDS */

/*[[[end]]]*/



#if __SIZEOF_POINTER__ == 4
#define EXCEPT_CODE(class, subclass) (__CCAST(__UINT32_TYPE__)(class) | __CCAST(__UINT32_TYPE__)(subclass) << 16)
#define EXCEPT_CLASS(code)           ((code) & __UINT16_C(0xffff))
#define EXCEPT_SUBCLASS(code)        ((code) >> 16)
#elif __SIZEOF_POINTER__ == 8
#define EXCEPT_CODE(class, subclass) (__CCAST(__UINT64_TYPE__)(class) | __CCAST(__UINT64_TYPE__)(subclass) << 32)
#define EXCEPT_CLASS(code)           ((code) & __UINT32_C(0xffffffff))
#define EXCEPT_SUBCLASS(code)        ((code) >> 32)
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */

/* Return the code for a given error code, class or sub-class */
#ifndef EXCEPT_CODEOF
#ifdef __HYBRID_PP_VA_NARGS
#define EXCEPT_CODEOF(code)                         __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE code
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE1(code) __CCAST(__UINTPTR_TYPE__)code
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE2       EXCEPT_CODE
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEN2(n)   __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE##n
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEN(n)    __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEN2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE(...)   __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEX(__PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODE(args...) __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEX(__PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(args))(args))
#endif /* ... */
#define __PRIVATE_EXCEPT_CODEOF_PACKAGE_CODEX(x)    x
#endif /* __HYBRID_PP_VA_NARGS */
#endif /* !EXCEPT_CODEOF */


#endif /* !_KOS_EXCEPT_CODES_H */
