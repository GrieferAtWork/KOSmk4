/* HASH CRC-32:0x3ea38112 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXCEPT_H
#define _KOS_EXCEPT_H 1

#include <__stdinc.h>
#include <hybrid/byteorder.h>
#include <hybrid/pp/__va_nargs.h>
#include <bits/types.h>
#include <kos/asm/except.h>
#include <kos/bits/exception_data.h>
#include <features.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */


__DECL_BEGIN

/* Macros for addressing bounds of error class ranges documented above */
#define ERRORCODE_STDERROR_MIN       (0x0001)
#define ERRORCODE_STDERROR_MAX       (0x00ff)
#define ERRORCODE_LIBERROR_MIN       (0x0100)
#define ERRORCODE_LIBERROR_MAX       (0x01ff)
#define ERRORCODE_USERERROR_MIN      (0x0200)
#define ERRORCODE_USERERROR_MAX      (0x7fff)
#define ERRORCODE_RESERVED1_MIN      (0x8000)
#define ERRORCODE_RESERVED1_MAX      (0xefff)
#define ERRORCODE_STDSIGNAL_MIN      (0xf000)
#define ERRORCODE_STDSIGNAL_MAX      (0xf0ff)
#define ERRORCODE_USERSIGNAL_MIN     (0xf100)
#define ERRORCODE_USERSIGNAL_MAX     (0xfaff)
#define ERRORCODE_RESERVED2_MIN      (0xfb00)
#define ERRORCODE_RESERVED2_MAX      (0xfdff)
#define ERRORCODE_RTL_MIN            (0xfe00)
#define ERRORCODE_RTL_MAX            (0xfe7f)
#define ERRORCODE_UNHANDLED_MIN      (0xfe80)
#define ERRORCODE_UNHANDLED_MAX      (0xfebf)
#define ERRORCODE_CPU_MIN            (0xfec0)
#define ERRORCODE_CPU_MAX            (0xfeff)
#define ERRORCODE_HARDWARE_MIN       (0xff00)
#define ERRORCODE_HARDWARE_MAX       (0xffff)


/* Check if the given error is low- (may get overwritten
 * by !LOW || HIGH), or high- (doesn't get overwritten) priority.
 * This mechanism is used for dealing with exceptions thrown by
 * RPC function callbacks executed prior to returning to user-space
 * when checking how an exception should be propagated to user-space. */
#define ERRORCODE_ISLOWPRIORITY(x)   ((x) >= ERRORCODE_STDSIGNAL_MIN && (x) <= ERRORCODE_USERSIGNAL_MAX)
#define ERRORCODE_ISHIGHPRIORITY(x)  ((x) >= ERRORCODE_RTL_MIN && (x) <= ERRORCODE_UNHANDLED_MAX)

/* Check for RTL-priority exceptions. Exceptions matching this
 * check are always propagated between the kernel and user-space,
 * irregardless of whether or not a system call was invoked with
 * or without exceptions enabled.
 * This is only meant for exceptions like `E_EXIT_THREAD', who's
 * sole purpose is to unwind the stack and safely terminate a
 * thread. */
#define ERRORCODE_ISRTLPRIORITY(x)   ((x) >= ERRORCODE_RTL_MIN && (x) <= ERRORCODE_RTL_MAX)


/* Exception classes. */
/* Never thrown; may be used to indicate error-less state */
#define E_OK (0x0000)



/* Failed to allocate sufficient resources */
#define E_BADALLOC (0x0001)
/* Insufficient virtual address space
 * 	@@The number of bytes that could not be allocated
 * 	member num_bytes: size_t; */
#define E_BADALLOC_INSUFFICIENT_HEAP_MEMORY (E_BADALLOC,0x0001)
/* Insufficient virtual address space
 * 	@@The number of pages that could not be allocated
 * 	member num_pages: size_t; */
#define E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY (E_BADALLOC,0x0002)
/* Insufficient physical memory
 * 	@@The number of pages that could not be allocated
 * 	member num_pages: size_t; */
#define E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY (E_BADALLOC,0x0003)
/* Insufficient space in swap
 * 	@@The number of pages that could not be allocated
 * 	member num_pages: size_t; */
#define E_BADALLOC_INSUFFICIENT_SWAP_SPACE (E_BADALLOC,0x0004)
/* The caller is not allowed to allocate more handles without first closing some old ones
 * s.a.: /src/kernel/include/kernel/handle.h
 * 	@@The number of handles that were attempted to be allocated (usually 1)
 * 	member num_handles: unsigned int;
 * 	@@The number of handles currently allocated
 * 	member cur_handles: unsigned int;
 * 	@@The max number of handles that may be allocated by the caller
 * 	member max_handles: unsigned int; */
#define E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS (E_BADALLOC,0x0005)
/* Attempted to allocated a handle index greater than the max allowed index
 * s.a.: /src/kernel/include/kernel/handle.h
 * 	@@The requested handle number, past which no more unused handles exist.
 * 	member req_handle: unsigned int;
 * 	@@The max handle id that is currently in use
 * 	member cur_max: unsigned int;
 * 	@@The set handle id which may not be exceeded
 * 	member cur_limit: unsigned int; */
#define E_BADALLOC_INSUFFICIENT_HANDLE_RANGE (E_BADALLOC,0x0006)
/* No suitable, free device numbers are available
 * 	@@The kind of device number lacking (One of `E_NO_DEVICE_KIND_*')
 * 	member dev_kind: unsigned int; */
#define E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS (E_BADALLOC,0x0007)
/* The given interrupt vector is, or all usable vectors are already in use
 * 	@@The given vector (if that specific vector is already in use),
 * 	@@or (uintptr_t)-1 when all vectors are already in use.
 * 	member vector: uintptr_t; */
#define E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS (E_BADALLOC,0x0008)



/* Invalid argument */
#define E_INVALID_ARGUMENT (0x0002)
/* An invalid set of flags was given, such that `(value & mask) != result' was the case
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t;
 * 	@@The mask of illegal & fixed bits
 * 	member mask: uintptr_t;
 * 	@@The mask of fixed bits
 * 	member result: uintptr_t; */
#define E_INVALID_ARGUMENT_UNKNOWN_FLAG (E_INVALID_ARGUMENT,0x0001)
/* A reserved bit was set incorrectly, such that `(value & mask) != result' was the case
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t;
 * 	@@The mask of illegal & fixed bits
 * 	member mask: uintptr_t;
 * 	@@The mask of fixed bits
 * 	member result: uintptr_t; */
#define E_INVALID_ARGUMENT_RESERVED_FLAG (E_INVALID_ARGUMENT,0x0002)
/* An invalid combination of flags was set, such that `(value & mask) == result' was the case
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t;
 * 	@@The mask of relevant bits
 * 	member mask: uintptr_t;
 * 	@@The invalid resulting value
 * 	member result: uintptr_t; */
#define E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION (E_INVALID_ARGUMENT,0x0003)
/* A masked type field `(value & mask)' contains an invalid value
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t;
 * 	@@The mask of relevant bits
 * 	member mask: uintptr_t; */
#define E_INVALID_ARGUMENT_BAD_FLAG_MASK (E_INVALID_ARGUMENT,0x0004)
/* A given `value' has an invalid alignment when masked by `mask', such that
 * the expression `(mask & value) != required_masked_value' was the case.
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t;
 * 	@@The mask in which the bits of `value' must match `required_masked_value'
 * 	member mask: uintptr_t;
 * 	@@The required result of masking `value'
 * 	member required_masked_value: uintptr_t; */
#define E_INVALID_ARGUMENT_BAD_ALIGNMENT (E_INVALID_ARGUMENT,0x0005)
/* A given `value' is invalid for the associated argument
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The value that was given
 * 	member value: uintptr_t; */
#define E_INVALID_ARGUMENT_BAD_VALUE (E_INVALID_ARGUMENT,0x0006)
/* A reserved argument had an unexpected value
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int; */
#define E_INVALID_ARGUMENT_RESERVED_ARGUMENT (E_INVALID_ARGUMENT,0x0007)
/* An unknown command was given
 * 	@@Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')
 * 	member context: unsigned int;
 * 	@@The command that was given
 * 	member command: uintptr_t; */
#define E_INVALID_ARGUMENT_UNKNOWN_COMMAND (E_INVALID_ARGUMENT,0x0008)
/* Generic context */
#define E_INVALID_ARGUMENT_CONTEXT_GENERIC 0x0000
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `F_SETFD' */
#define E_INVALID_ARGUMENT_CONTEXT_SETFD_OFLAG 0x0001
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `F_SETFL' */
#define E_INVALID_ARGUMENT_CONTEXT_SETFL_OFLAG 0x0002
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `dup3' */
#define E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG 0x0003
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `PROT_*' flag */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT 0x0004
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `MAP_*' flag
 * E_INVALID_ARGUMENT_BAD_FLAG_MASK: (flags & MAP_TYPE) !in [MAP_AUTOMATIC,MAP_SHARED,MAP_PRIVATE]
 * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Both `MAP_GROWSDOWN' and `MAP_GROWSUP' were specified in `flags' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG 0x0005
/* E_INVALID_ARGUMENT_BAD_ALIGNMENT: `MAP_FIXED' was specified when `MAP_ANONYMOUS' wasn't, but the `(file_offset & (getpagesize() - 1)) != ((uintptr_t)addr & (getpagesize() - 1))' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR 0x0006
/* E_INVALID_ARGUMENT_BAD_VALUE: The specified `length' is either `0' or is larger than the entirety of the designated address space. */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH 0x0007
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mknod()' cannot be masked by `07777 | S_IFMT'.
 * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed to `mknod()' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE 0x0008
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mkdir()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE 0x0009
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `unlinkat()' (accepted are `AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH'). */
#define E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS 0x000a
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `linkat()' (accepted are `AT_SYMLINK_FOLLOW|AT_DOSPATH|AT_EMPTY_PATH|AT_NO_AUTOMOUNT'). */
#define E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS 0x000b
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `UMOUNT_*' flag passed to `umount2()' (accepted are `MNT_FORCE|MNT_DETACH|MNT_EXPIRE|UMOUNT_NOFOLLOW'). */
#define E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS 0x000c
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `MS_*' flag passed to `mount()' (accepted are those defined in <sys/mount.h>). */
#define E_INVALID_ARGUMENT_CONTEXT_MOUNT_FLAGS 0x000d
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `chmod()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE 0x000e
/* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: [mask == O_ACCMODE]: The given `oflags' used `__O_ACCMODE_INVALID' as access mode
 * E_INVALID_ARGUMENT_UNKNOWN_FLAG:         Unknown `O_*' flag passed to `open()' */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG 0x000f
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `open()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE 0x0010
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown fcntl() command */
#define E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND 0x0011
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown ioctl() command */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND 0x0012
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `of_flags' field of a `hop_openfd'-compatible HOP command contained flags other than `IO_CLOEXEC|IO_CLOFORK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFS_FLAGS 0x0013
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `of_mode' field of a `hop_openfd'-compatible HOP command wasn't one of `HOP_OPENFD_MODE_*'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFD_MODE 0x0014
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `hop()' wasn't recognized by the associated handle. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND 0x0015
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `hopf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE 0x0016
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `ioctlf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE 0x0017
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `readf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_READF_MODE 0x0018
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `writef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE 0x0019
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `preadf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE 0x001a
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `pwritef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE 0x001b
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_OPENNODE_FLAG_*' flag passed in `hop_directory_opennode::don_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS 0x001c
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed in `hop_directory_creatfile::dcf_oflags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS 0x001d
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_creatfile::dcf_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE 0x001e
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_REMOVE_FLAG_*' flag passed in `hop_directory_remove::drm_flags'
 * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Neither `HOP_DIRECTORY_REMOVE_FLAG_REGULAR', nor `HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY' was given in `hop_directory_remove::dr_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS 0x001f
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_RENAME_FLAG_*' flag passed in `hop_directory_rename::drn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS 0x0020
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_LINK_FLAG_*' flag passed in `hop_directory_link::dli_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS 0x0021
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_SYMLINK_FLAG_*' flag passed in `hop_directory_symlink::dsl_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS 0x0022
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_symlink::dsl_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE 0x0023
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKNOD_FLAG_*' flag passed in `hop_directory_mknod::dmn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS 0x0024
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mknod::dmn_mode' cannot be masked by `07777 | S_IFMT'.
 * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed in `hop_directory_mknod::dmn_mode' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE 0x0025
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKDIR_FLAG_*' flag passed in `hop_directory_mkdir::dmd_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS 0x0026
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mkdir::dmd_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE 0x0027
/* E_INVALID_ARGUMENT_BAD_VALUE: The `level' argument passed to `syslog()' wasn't recognized. */
#define E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL 0x0028
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frealpath4' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS 0x0029
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value for `whence' in `lseek()' */
#define E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE 0x002a
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' contains invalid/unknown flags
 * E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & READDIR_MODEMASK' isn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE 0x002b
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Invalid set of `MAP_*' flags passed to `loadlibrary()' */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS 0x002c
/* E_INVALID_ARGUMENT_BAD_ALIGNMENT: Segments have inconsistent page alignments */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN 0x002d
/* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid byte-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN 0x002e
/* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid file-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN 0x002f
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `kfstatat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS 0x0030
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `freadlinkat' isn't a set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS 0x0031
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchmodat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS 0x0032
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchownat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS 0x0033
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `execveat' isn't a set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS 0x0034
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `waitid()' isn't a set of `WNOHANG|WNOREAP|WEXITED|WSTOPPED|WCONTINUED'
 * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: The `options' argument passed to `waitid()' contains none of `WEXITED|WSTOPPED|WCONTINUED' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS 0x0035
/* E_INVALID_ARGUMENT_BAD_VALUE: The `which' value passed to `waitid()' isn't one of `P_ALL,P_PID,P_PGID' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH 0x0036
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `wait4()' isn't a set of `WNOHANG|WUNTRACED|WCONTINUED|WNOWAIT' */
#define E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS 0x0037
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to set a user-space address as the base of the `struct userkern' segment */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE 0x0038
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write a value other than `0' to `struct userkern::ut_ppid' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID 0x0039
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write an invalid value to `struct userkern::ut_sid' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID 0x003a
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `prot' argument passed to `mprotect()' isn't a set of `PROT_EXEC|PROT_WRITE|PROT_READ' */
#define E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT 0x003b
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS 0x003c
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `rpc_schedule()' is malformed */
#define E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS 0x003d
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `iomode' passed to `kreaddirf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE 0x003e
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `pipe2()' cannot be masked by `O_CLOEXEC|O_CLOFORK|O_NONBLOCK|O_DIRECT' */
#define E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS 0x003f
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `sysctl()' wasn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_SYSCTL_COMMAND 0x0040
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `sysctl_driver_insmod::im_format', `sysctl_driver_delmod::dm_format' or `sysctl_driver_getmod::gm_format' wasn't one of `SYSCTL_DRIVER_FORMAT_*', or wasn't recognized as valid in the specific context */
#define E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT 0x0041
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_insmod::im_flags' cannot be masked by `SYSCTL_DRIVER_INSMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS 0x0042
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_delmod::dm_flags' cannot be masked by `SYSCTL_DRIVER_DELMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS 0x0043
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frenameat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS 0x0044
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fsymlinkat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS 0x0045
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmknodat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS 0x0046
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmkdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS 0x0047
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCXONC)' isn't one of `TC(I|O)(ON|OFF)' */
#define E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND 0x0048
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCFLSH)' isn't one of `TC(I|O|IO)FLUSH' */
#define E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND 0x0049
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & EXCEPT_HANDLER_MODE_MASK' isn't one of `EXCEPT_HANDLER_MODE_*'
 * E_INVALID_ARGUMENT_UNKNOWN_FLAG:    The given `mode & ~EXCEPT_HANDLER_MODE_MASK' isn't a set of `EXCEPT_HANDLER_FLAG_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE 0x004a
/* E_INVALID_ARGUMENT_BAD_VALUE: One of the register values passed to sigreturn is invalid (`value' is the arch-specific register ID; e.g. `X86_REGISTER_SEGMENT_SS') */
#define E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER 0x004b
/* E_INVALID_ARGUMENT_BAD_VALUE: Bad signal number passed to `raise()', `kill()', `tgkill()', etc. */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO 0x004c
/* E_INVALID_ARGUMENT_BAD_VALUE: Bad trap number passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO 0x004d
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, KBDIO_SETRDKEY, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETRDKEY_BADMODE 0x004e
/* E_INVALID_ARGUMENT_BAD_VALUE: The specified keymap data block is too large */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE 0x004f
/* E_INVALID_ARGUMENT_BAD_VALUE: The text contained within the keymap is corrupted/invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT 0x0050
/* E_INVALID_ARGUMENT_BAD_VALUE: The specified default encoding is invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING 0x0051
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, MOUSEIO_SETABSMODE, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSMODE_BADMODE 0x0052
/* E_INVALID_ARGUMENT_BAD_VALUE: The bounds specified are invalid and cannot be used */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSRECT_BADBOUNDS 0x0052
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid (or unsupported) value passed as argument to `ioctl(fd, KBDIO_SETDBGF12, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE 0x0053
/* E_INVALID_ARGUMENT_BAD_VALUE: The sigset size passed to one of the RT signal system calls is incorrect */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE 0x0053
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to sigaction() or rt_sigaction() isn't a set of `SA_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS 0x0054
/* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid `how' passed to `sigprocmask()' (must be one of { SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK }) */
#define E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW 0x0055
/* E_INVALID_ARGUMENT_BAD_VALUE: Bad pid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_PID 0x0056
/* E_INVALID_ARGUMENT_BAD_VALUE: Bad tgid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_TGID 0x0057
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to raise a signal using `rt_sigqueueinfo()' or `rt_tgsigqueueinfo()' with a bad `si_code' */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE 0x0058
/* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `reserved' argument passed to `mktty()' is non-zero */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS 0x0059
/* E_INVALID_ARGUMENT_BAD_VALUE: The `name' argument passed to `mktty()' is too long */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME 0x005a
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `type' argument passed to `faccessat()' isn't a set of `F_OK|R_OK|W_OK|X_OK' */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE 0x005b
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `faccessat()' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS 0x005c
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to read()/write() to/from an eventfd object using a buffer size less that 8 */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE 0x005d
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write 0xffffffffffffffff to a eventfd object */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh 0x005e
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_eventfd2()' is not masked by `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS 0x005f
/* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_signalfd4()' is not masked by `SFD_NONBLOCK | SFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS 0x0060
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to pass a too low value to `F_SETPIPE_SZ' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_PIPE_BUFFER_SIZE 0x0061
/* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write an invalid integer to a system configuration file */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER 0x0062
/* E_INVALID_ARGUMENT_BAD_VALUE: Bad reason code passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON 0x0063




/* Unimplemented function */
#define E_NOT_IMPLEMENTED (0x0003)
#define E_NOT_IMPLEMENTED_UNSUPPORTED (E_NOT_IMPLEMENTED,0x0001)
#define E_NOT_IMPLEMENTED_TODO (E_NOT_IMPLEMENTED,0x0002)




/* Bad file descriptor */
#define E_INVALID_HANDLE (0x0004)
/* The given file descriptor is invalid
 * 	@@The FD number that was accessed
 * 	member fd: unsigned int;
 * 	@@One of `E_INVALID_HANDLE_FILE_*'
 * 	member reason: unsigned int;
 * 	@@1+ the max FD number that is currently in use
 * 	member fd_max: unsigned int;
 * 	@@The max allowed FD number that may be assigned
 * 	member fd_limit: unsigned int; */
#define E_INVALID_HANDLE_FILE (E_INVALID_HANDLE,0x0001)
/* The FD slot associated with the given number has no bound value */
#define E_INVALID_HANDLE_FILE_UNBOUND 0x0001
/* The FD slot associated with the given number isn't allocated (`fd >= fd_max') */
#define E_INVALID_HANDLE_FILE_UNALLOCATED 0x0002
/* The FD slot associated with the given number may not be used (`fd > fd_limit') */
#define E_INVALID_HANDLE_FILE_ILLEGAL 0x0003
/* Invalid file handle type
 * 	@@The FD number that was accessed
 * 	member fd: unsigned int;
 * 	@@The type of handle that was needed (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)
 * 	member needed_handle_type: unsigned int;
 * 	@@The type of handle that was found (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)
 * 	member actual_handle_type: unsigned int;
 * 	@@The type-kind of handle that was needed (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)
 * 	member needed_handle_kind: unsigned int;
 * 	@@The type-kind of handle that was found (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)
 * 	member actual_handle_kind: unsigned int; */
#define E_INVALID_HANDLE_FILETYPE (E_INVALID_HANDLE,0x0002)
/* Invalid handle operation
 * 	@@The FD number that was accessed
 * 	member fd: unsigned int;
 * 	@@One of `E_INVALID_HANDLE_OPERATION_*'
 * 	member op: unsigned int;
 * 	@@The access permissions of the handle
 * 	member handle_mode: iomode_t; */
#define E_INVALID_HANDLE_OPERATION (E_INVALID_HANDLE,0x0003)
/* Attempted to read() on a handle opened as IO_WRONLY */
#define E_INVALID_HANDLE_OPERATION_READ 0x0001
/* Attempted to write() on a handle opened as IO_RDONLY */
#define E_INVALID_HANDLE_OPERATION_WRITE 0x0002
/* Attempted to truncate() on a handle opened as IO_RDONLY */
#define E_INVALID_HANDLE_OPERATION_TRUNC 0x0003
/* Attempted to get some abstract property of a handle opened as IO_WRONLY
 * Note however that this dependens on what type of handle and property was
 * accessed. - If, and when this context has meaning, that fact is explicitly
 * documented. */
#define E_INVALID_HANDLE_OPERATION_GETPROPERTY 0x0011
/* Same as `E_INVALID_HANDLE_OPERATION_GETPROPERTY', but for setting properties */
#define E_INVALID_HANDLE_OPERATION_SETPROPERTY 0x0012




/* A blocking call was attempted when non-blocking behavior was requested */
#define E_WOULDBLOCK (0x0005)
/* An attempt to task_yield() / sched_yield() / etc. would have blocked */
#define E_WOULDBLOCK_PREEMPTED (E_WOULDBLOCK,0x0001)
/* An attempt to wait for a signal would have blocked */
#define E_WOULDBLOCK_WAITFORSIGNAL (E_WOULDBLOCK,0x0002)




/* The task controller for the specified process has already been deallocated.
 * This implies that the process has exited. However, it doesn't imply that
 * the task controller is immediately deallocated when a process exists
 * 	@@The pid of the exited process
 * 	member pid: pid_t; */
#define E_PROCESS_EXITED (0x0006)




/* The named device doesn't exist
 * 	@@The kind of device (One of `E_NO_DEVICE_KIND_*')
 * 	member kind: uintptr_t;
 * 	@@The number for the named device
 * 	member devno: dev_t; */
#define E_NO_DEVICE (0x0007)
/* A block device was missing */
#define E_NO_DEVICE_KIND_BLOCK_DEVICE 1
/* A character device was missing */
#define E_NO_DEVICE_KIND_CHARACTER_DEVICE 2




/* Attempted to execute an unknown system call
 * 	member sysno: uintptr_t;
 * 	member arg0: uintptr_t;
 * 	member arg1: uintptr_t;
 * 	member arg2: uintptr_t;
 * 	member arg3: uintptr_t;
 * 	member arg4: uintptr_t;
 * 	member arg5: uintptr_t; */
#define E_UNKNOWN_SYSTEMCALL (0x0008)




/* The specified object doesn't exist */
#define E_NO_SUCH_OBJECT (0x0009)
/* No block device has been bound */
#define E_NO_SUCH_BLOCKDEVICE (E_NO_SUCH_OBJECT,0x0001)
/* No process has been bound */
#define E_NO_SUCH_PROCESS (E_NO_SUCH_OBJECT,0x0002)
/* No pid namespace has been bound */
#define E_NO_SUCH_PIDNS (E_NO_SUCH_OBJECT,0x0003)
/* No controlling terminal has been assigned to the calling session */
#define E_NO_CTTY (E_NO_SUCH_OBJECT,0x0004)




/* Illegal operation */
#define E_ILLEGAL_OPERATION (0x000a)
/* Illegal process operation
 * 	@@The Pid of the process in question
 * 	member pid: pid_t;
 * 	@@The illegal action that was attempted (One of `E_ILLEGAL_PROCESS_OPERATION_*')
 * 	member action: pid_t;
 * 	@@A second pid, or 0 if unused
 * 	member pid2: pid_t; */
#define E_ILLEGAL_PROCESS_OPERATION (E_ILLEGAL_OPERATION,0x0001)
/* Attempted to move the leader of a process group into a different process group (`pid2' is the PID of the target process group) */
#define E_ILLEGAL_PROCESS_OPERATION_SETPGID_LEADER 0x0001




/* Filesystem error */
#define E_FSERROR (0x0080)
/* Attempted to access a file that has been deleted
 * 	@@The reason/context in which the file was deleted (One of `E_FILESYSTEM_DELETED_*')
 * 	member reason: unsigned int; */
#define E_FSERROR_DELETED (E_FSERROR,0x0001)
/* The file being accessed was deleted. (set if the problem was caused by the last component of a path) */
#define E_FILESYSTEM_DELETED_FILE 0x0001
/* The path being accessed was deleted. (set if the problem was caused by some other than the last component of the path) */
#define E_FILESYSTEM_DELETED_PATH 0x0002
/* The hosting file system has been unmounted */
#define E_FILESYSTEM_DELETED_UNMOUNTED 0x0003
/* File not found */
#define E_FSERROR_FILE_NOT_FOUND (E_FSERROR,0x0002)
/* Path not found
 * 	@@The reason/context why the path wasn't found (One of `E_FILESYSTEM_PATH_NOT_FOUND_*')
 * 	member reason: unsigned int; */
#define E_FSERROR_PATH_NOT_FOUND (E_FSERROR,0x0003)
/* Directory does not exist */
#define E_FILESYSTEM_PATH_NOT_FOUND_DIR 0x0001
/* Drive does not exist */
#define E_FILESYSTEM_PATH_NOT_FOUND_DRIVE 0x0002
/* Illegal or malformed path */
#define E_FSERROR_ILLEGAL_PATH (E_FSERROR,0x0004)
/* A directory was expected, but something else was found
 * 	@@The context in which a filesystem component was required to be a directory, but wasn't (One of `E_FILESYSTEM_NOT_A_DIRECTORY_*')
 * 	member action_context: uintptr_t; */
#define E_FSERROR_NOT_A_DIRECTORY (E_FSERROR,0x0005)
/* Thrown as the result of attempting to traverse a non-directory item as though it was one (e.g. `open("/opt/readme.txt/foobar")') */
#define E_FILESYSTEM_NOT_A_DIRECTORY_WALK 0x0001
/* Thrown as the result of `open(path, O_DIRECTORY)', where `path' isn't a directory */
#define E_FILESYSTEM_NOT_A_DIRECTORY_OPEN 0x0002
/* Thrown as the result of `rmdir(path)', where `path' isn't a directory */
#define E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR 0x0003
/* Thrown as the result of `readdir(path)', where `path' isn't a directory */
#define E_FILESYSTEM_NOT_A_DIRECTORY_READDIR 0x0004

/* SPLIT: All error codes above should be interpreted as FILE-NOT-FOUND
 *        in situations where a list of paths is searched for a specific
 *        file. */
#define E_FSERROR_IS_FILE_NOT_FOUND(x) (ERROR_SUBCLASS(x) <= 0x0005)

/* Attempted to follow too many symbolic links (probably as the result of a loop) */
#define E_FSERROR_TOO_MANY_SYMBOLIC_LINKS (E_FSERROR,0x0006)
/* File access was denied */
#define E_FSERROR_ACCESS_DENIED (E_FSERROR,0x0007)
/* Attempted to write when the disk was already full */
#define E_FSERROR_DISK_FULL (E_FSERROR,0x0008)
/* Read-only filesystem */
#define E_FSERROR_READONLY (E_FSERROR,0x0009)
/* Too many hard links already exist for a given file */
#define E_FSERROR_TOO_MANY_HARD_LINKS (E_FSERROR,0x000a)
/* A directory was found, but something else was expected
 * 	@@The context in which a filesystem component was required to not be a directory, but was one (One of `E_FILESYSTEM_IS_A_DIRECTORY_*')
 * 	member action_context: uintptr_t; */
#define E_FSERROR_IS_A_DIRECTORY (E_FSERROR,0x000b)
/* Thrown as the result of `unlink(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_UNLINK 0x0001
/* Thrown as the result of `exec(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_EXEC 0x0002
/* A symbolic link was expected when something else was found
 * 	@@The context in which a filesystem component was required to be a symlink, but was one (One of `E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_*')
 * 	member action_context: uintptr_t; */
#define E_FSERROR_NOT_A_SYMBOLIC_LINK (E_FSERROR,0x000c)
/* Thrown as the result of `open(path, O_SYMLINK | O_EXCL)', where `path' isn't a symbolic link */
#define E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN 0x0001
/* Thrown as the result of using `readlink(path)', where `path' isn't a symbolic link */
#define E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_READLINK 0x0002
/* A symbolic link was encountered when none was expected
 * 	@@The context in which a filesystem component was required to not be a symlink, but was one (One of `E_FILESYSTEM_IS_A_SYMBOLIC_LINK_*')
 * 	member action_context: uintptr_t; */
#define E_FSERROR_IS_A_SYMBOLIC_LINK (E_FSERROR,0x000d)
/* Thrown as the result of `open(path,O_NOFOLLOW)', where `path' refers to a symbolic link */
#define E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN 0x0001
/* Thrown as the result of `exec(path,AT_SYMLINK_NOFOLLOW)', where `path' refers to a symbolic link */
#define E_FILESYSTEM_IS_A_SYMBOLIC_LINK_EXEC 0x0002
/* Thrown as the result of `open(path,O_CREAT|O_EXCL)', where `path' already exists */
#define E_FSERROR_FILE_ALREADY_EXISTS (E_FSERROR,0x000e)
/* Attempted to remove a non-empty directory */
#define E_FSERROR_DIRECTORY_NOT_EMPTY (E_FSERROR,0x000f)
/* Attempted to rename() or link() a file from one device to another */
#define E_FSERROR_CROSS_DEVICE_LINK (E_FSERROR,0x0010)
/* Attempted to move a directory such that it would become a child of itself */
#define E_FSERROR_DIRECTORY_MOVE_TO_CHILD (E_FSERROR,0x0011)
/* Attempted to mount() something that isn't a block-device */
#define E_FSERROR_NOT_A_BLOCK_DEVICE (E_FSERROR,0x0012)
/* Attempted to mount() a filesystem without a block-device, when that filesystem requires one */
#define E_FSERROR_NO_BLOCK_DEVICE (E_FSERROR,0x0013)
/* Attempted to mount a block-device with the wrong file system */
#define E_FSERROR_WRONG_FILE_SYSTEM (E_FSERROR,0x0014)
/* Attempted to mount an unknown file system type */
#define E_FSERROR_UNKNOWN_FILE_SYSTEM (E_FSERROR,0x0015)
/* The filesystem data found within a given block-device has been corrupted and cannot be mounted */
#define E_FSERROR_CORRUPTED_FILE_SYSTEM (E_FSERROR,0x0016)
/* Attempted to mount a block-device with a different file system type than the one it had already been mounted with */
#define E_FSERROR_DEVICE_ALREADY_MOUNTED (E_FSERROR,0x0017)
/* Attempted to create a new mounting point for a path that has already been mounted */
#define E_FSERROR_PATH_ALREADY_MOUNTED (E_FSERROR,0x0018)
/* Attempted to umount() a path that isn't a mounting point */
#define E_FSERROR_NOT_A_MOUNTING_POINT (E_FSERROR,0x0019)
/* Attempted to rmdir() or rename() a mounting point */
#define E_FSERROR_IS_A_MOUNTING_POINT (E_FSERROR,0x001a)
/* The object does not support the operation
 * 	@@The unsupported operation (One of `E_FILESYSTEM_OPERATION_*')
 * 	member operation_id: uintptr_t; */
#define E_FSERROR_UNSUPPORTED_OPERATION (E_FSERROR,0x0100)
/* The object does not support reading */
#define E_FILESYSTEM_OPERATION_READ 0x0001
/* The object does not support writing */
#define E_FILESYSTEM_OPERATION_WRITE 0x0002
/* The object does not support being resized */
#define E_FILESYSTEM_OPERATION_TRUNC 0x0003
/* The object does not support being read from as a directory */
#define E_FILESYSTEM_OPERATION_READDIR 0x0004
/* The object does not support creation of new files */
#define E_FILESYSTEM_OPERATION_CREAT 0x0005
/* The object does not support creation of new directories */
#define E_FILESYSTEM_OPERATION_MKDIR 0x0006
/* The object does not support creation of symbolic links */
#define E_FILESYSTEM_OPERATION_SYMLINK 0x0007
/* The object does not support creation of device nodes */
#define E_FILESYSTEM_OPERATION_MKNOD 0x0008
/* The object does not support creation of hard links */
#define E_FILESYSTEM_OPERATION_LINK 0x0009
/* The object does not support renaming of items */
#define E_FILESYSTEM_OPERATION_RENAME 0x000a
/* The object does not support unlinking files */
#define E_FILESYSTEM_OPERATION_UNLINK 0x000b
/* The object does not support removal of directories */
#define E_FILESYSTEM_OPERATION_RMDIR 0x000c
/* The values specified by chmod() or chown() cannot be applied within the file system */
#define E_FILESYSTEM_OPERATION_ATTRIB 0x000d
/* The object does not support changes to attributes being written to disk */
#define E_FILESYSTEM_OPERATION_WRATTR 0x000e
/* The object does not support seeking in file stream */
#define E_FILESYSTEM_OPERATION_SEEK 0x000f
/* The object does not support mapping data into memory */
#define E_FILESYSTEM_OPERATION_MMAP 0x0010
/* The object does not the fsync() operator */
#define E_FILESYSTEM_OPERATION_SYNC 0x0011
/* The object does not the fdatasync() operator */
#define E_FILESYSTEM_OPERATION_DATASYNC 0x0012
/* The object does not the fstat() operator */
#define E_FILESYSTEM_OPERATION_STAT 0x0013
/* The object does not the poll() operator */
#define E_FILESYSTEM_OPERATION_POLL 0x0014
/* The object does not the fallocate() operator */
#define E_FILESYSTEM_OPERATION_ALLOCATE 0x0015




/* Network error */
#define E_NET_ERROR (0x0081)




/* Hardware error, or miss-behaving/miss-configured device */
#define E_IOERROR (0x0082)
/* A hardware error bit has been set
 * 	@@The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*')
 * 	member subsystem: uintptr_t;
 * 	@@A more precise description of the error (One of `E_IOERROR_REASON_*')
 * 	member reason: uintptr_t; */
#define E_IOERROR_ERRORBIT (E_IOERROR,0x0001)
/* Hardware component timed out
 * 	@@The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*')
 * 	member subsystem: uintptr_t;
 * 	@@A more precise description of the error (One of `E_IOERROR_REASON_*')
 * 	member reason: uintptr_t; */
#define E_IOERROR_TIMEOUT (E_IOERROR,0x0002)
/* Attempted to write to read-only disk component
 * 	@@The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*')
 * 	member subsystem: uintptr_t;
 * 	@@A more precise description of the error (One of `E_IOERROR_REASON_*')
 * 	member reason: uintptr_t; */
#define E_IOERROR_READONLY (E_IOERROR,0x0003)
/* Attempted to write beyond the end of a disk
 * 	@@The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*')
 * 	member subsystem: uintptr_t;
 * 	@@A more precise description of the error (One of `E_IOERROR_REASON_*')
 * 	member reason: uintptr_t; */
#define E_IOERROR_BADBOUNDS (E_IOERROR,0x0004)
/* The error stems from the physical disk faulting */
#define E_IOERROR_SUBSYSTEM_HARDDISK 0x0001
/* The error stems from an I/O-related file error */
#define E_IOERROR_SUBSYSTEM_FILE 0x0002
/* The error stems from a HumanInterfaceDevice-related connection error */
#define E_IOERROR_SUBSYSTEM_HID 0x0003
/* The error stems from the USB sub-system */
#define E_IOERROR_SUBSYSTEM_USB 0x0004




/* The named file was not recognized as a valid executable */
#define E_NOT_EXECUTABLE (0x0083)
/* Cannot execute a file with the X file permission (s.a. `chmod') */
#define E_NOT_EXECUTABLE_NOEXEC (E_NOT_EXECUTABLE,0x0001)
/* Cannot execute anything other than a regular file */
#define E_NOT_EXECUTABLE_NOT_REGULAR (E_NOT_EXECUTABLE,0x0002)
/* The given file's contents weren't recognized as a known/valid binary format */
#define E_NOT_EXECUTABLE_NOT_A_BINARY (E_NOT_EXECUTABLE,0x0003)
/* The executable's binary state is faulty
 * 	@@The binary format (One of `E_NOT_EXECUTABLE_FAULTY_FORMAT_*')
 * 	member format: uintptr_t;
 * 	@@The format-specific reason why the load failed (One of `E_NOT_EXECUTABLE_FAULTY_REASON_*_*')
 * 	member reason: uintptr_t; */
#define E_NOT_EXECUTABLE_FAULTY (E_NOT_EXECUTABLE,0x0004)
/* ELF Binary */
#define E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF 0x0001
/* e_ident[EI_CLASS] != ELFCLASS32/64 (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS 0x0001
/* e_ident[EI_DATA] != ELFDATA2LSB/MSB (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER 0x0002
/* e_ident[EI_VERSION] != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION 0x0003
/* e_version != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2 0x0004
/* e_type != ET_EXEC (or in the case of a driver: e_type != ET_DYN) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE 0x0005
/* e_machine != EM_* (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH 0x0006
/* e_ehsize < offsetafter(Elf_Ehdr,e_phnum) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER 0x0007
/* e_phnum == 0 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS 0x0008
/* e_phentsize != sizeof(Elf_Phdr) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS 0x0009
/* e_phnum > ... (hard limit imposed by the host; i386/x86_64 uses 64 for this) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS 0x000a
/* (p_offset & (getpagesize() - 1)) != (p_vaddr & (getpagesize() - 1)) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT 0x000b
/* Loading of static binary failed due to overlapping segments */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP 0x000c
/* Only when loading drivers: The program headers pointer is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS 0x000d
/* Only when loading drivers: No `PT_DYNAMIC' program header found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC 0x000e
/* Only when loading drivers: The `PT_DYNAMIC' program header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC 0x000f
/* Only when loading drivers: No `DT_SONAME' or `DT_STRTAB' tag found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME 0x0010
/* Only when loading drivers: The `DT_STRTAB' tag isn't mapped, or the `DT_SONAME' tag is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME 0x0011
/* Only when loading drivers: The `e_shentsize' fields doesn't equal `sizeof(Elf_Shdr)' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT 0x0012
/* Only when loading drivers: The `e_shstrndx' field of the header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX 0x0013
/* Only when loading drivers: The `e_shoff' / `e_shnum' fields of the header are out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF 0x0014
/* Only when loading drivers: The `.shstrtab' section header has a type `SHT_NOBITS' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB 0x0015
/* Only when loading drivers: The `.shstrtab' section header points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB 0x0016
/* Only when loading drivers: The virtual address bounds for one of the program headers overflow */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR 0x0017
/* Only when loading drivers: The file offset one of the program headers is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET 0x0018
/* Only when loading drivers: The alignment requirement of a program header isn't a power-of-2 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN 0x0019
/* Only when loading drivers: The `.eh_frame' section doesn't have the `SHF_ALLOC' flag set. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME 0x001a
/* Only when loading drivers: The `.eh_frame' section address points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME 0x001b
/* Only when loading drivers: The `DT_STRTAB' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR 0x001c
/* Only when loading drivers: The `DT_HASH' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH 0x001d
/* Only when loading drivers: The `DT_DYNSYM' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM 0x001e
/* Only when loading drivers: The `DT_SYMENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT 0x001f
/* Only when loading drivers: The `DT_RELAENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT 0x0020
/* Only when loading drivers: The `DT_RELENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT 0x0021
/* Only when loading drivers: A constructor callback is located out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC 0x0022
/* Only when loading drivers: Bad dependency (either an index miss-match, or a bad filename) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED 0x0023
/* Only when loading drivers: Bad symbol index (symbol index is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL 0x0024
/* Only when loading drivers: Bad symbol name (symbol name is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME 0x0025
/* Only when loading drivers: Relocation against unknown symbol (s.a. system log) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL 0x0026
/* Only when loading drivers: Executable file is too large */
#define E_NOT_EXECUTABLE_TOOLARGE (E_NOT_EXECUTABLE,0x0005)
/* Only when loading drivers: Executable file is too small */
#define E_NOT_EXECUTABLE_TOOSMALL (E_NOT_EXECUTABLE,0x0006)




/* Insufficient Rights */
#define E_INSUFFICIENT_RIGHTS (0x0084)
/* Only root can steal already-assigned controlling terminals */
#define E_INSUFFICIENT_RIGHTS_CTTY_STEALING (E_INSUFFICIENT_RIGHTS,0x0001)




/* Insufficient Context */
#define E_INVALID_CONTEXT (0x0085)
/* The calling process isn't the session leader */
#define E_INVALID_CONTEXT_NOT_SESSION_LEADER (E_INVALID_CONTEXT,0x0001)
/* A controlling terminal had already been assigned */
#define E_INVALID_CONTEXT_CTTY_ALREADY_ASSIGNED (E_INVALID_CONTEXT,0x0002)
/* The calling session uses a different CTTY */
#define E_INVALID_CONTEXT_CTTY_DIFFERS (E_INVALID_CONTEXT,0x0003)




/* The provided buffer is too small
 * 	@@The required buffer size
 * 	member req_size: size_t;
 * 	@@The given buffer size
 * 	member given_size: size_t; */
#define E_BUFFER_TOO_SMALL (0x0090)




/* An illegal sequence was encountered in a unicode string */
#define E_UNICODE_ERROR (0x0091)




/* Signal codes. */
#ifndef E_INTERRUPT
/* The thread has been interrupted by a PRC function,
 * causing a premature return to user-space.
 * NOTE: If the system communication facility that was used for the interrupt
 *       supports restarting (e.g. loadcore() following a #PF on X86), or if the
 *       interrupt happened during a restartable system call (e.g. `sys_close()'),
 *       and either wasn't caused by a posix_signal, or that posix_signal had
 *       the `SA_RESTART' flag set, this exception isn't propagated into user-space,
 *       but rather causes the underlying interrupt to be restarted.
 * KOS Implements 3 distinct system call interrupt-restart behaviors:
 *  #1: The system call is always restarted (this behavior is also used when
 *      some other type of interrupt handler is interrupted, such as loadcore()
 *      during an ALOA operation, or when loading a file into memory)
 *      This mainly includes system calls where interrupts are undesired,
 *      or would otherwise be unexpected, most notably ~cleanup~ system calls,
 *      as also mentioned by the documentation of `_EXCEPT_API' in `<features.h>'
 *     (e.g. `close()' or `munmap()')
 *  #2: The system call is never restarted (required for some system calls
 *      that are meant to wait for events internally delivered by an interrupt
 *      mechanism, such as `sigtimedwait()'; the behavior here mirrors what is
 *      also done by linux, as described on this page:
 *     `http://man7.org/linux/man-pages/man7/signal.7.html')
 *  #3: Restart the system call if the interrupt wasn't caused by a posix_signal,
 *      or if it was caused by a posix_signal with the `SA_RESTART' flag set.
 */
#define E_INTERRUPT (0xf000)
/* Unwind in order to execute an RPC callback before returning to user-space */
#define E_INTERRUPT_USER_RPC (E_INTERRUPT,0x0001)
#endif /* !E_INTERRUPT */




/* The thread should re-attempt to acquire an R/W-lock
 * 	member lock: struct rwlock *; */
#define __E_RETRY_RWLOCK (0xf001)




/* RTL / Special exception codes. */
#ifndef E_EXIT_THREAD
/* The thread is supposed to terminate
 * 	@@The thread exit status
 * 	member exit_code: uintptr_t; */
#define E_EXIT_THREAD (0xfe00)
/* The entire process is supposed to terminate
 * 	@@The process exit status
 * 	member exit_code: uintptr_t; */
#define E_EXIT_PROCESS (0xfe01)
#endif /* !E_EXIT_THREAD */
/* Unhandled system interrupt
 * 	member opcode: uintptr_t;
 * 	member intno: uintptr_t;
 * 	member ecode: uintptr_t; */
#define E_UNHANDLED_INTERRUPT (0xfeff)




#if __SIZEOF_POINTER__ == 4
#define ERROR_CODE(class,subclass) (__CCAST(__UINT32_TYPE__)(class) | __CCAST(__UINT32_TYPE__)(subclass) << 16)
#define ERROR_CLASS(code)          ((code) & __UINT16_C(0xffff))
#define ERROR_SUBCLASS(code)       ((code) >> 16)
#elif __SIZEOF_POINTER__ == 8
#define ERROR_CODE(class,subclass) (__CCAST(__UINT64_TYPE__)(class) | __CCAST(__UINT64_TYPE__)(subclass) << 32)
#define ERROR_CLASS(code)          ((code) & __UINT32_C(0xffffffff))
#define ERROR_SUBCLASS(code)       ((code) >> 32)
#else
#error "Unsupported sizeof(void *)"
#endif


/* Return the code for a given error code, class or sub-class */
#define ERROR_CODEOF(code) __PRIVATE_ERROR_CODEOF_PACKAGE_CODE code

#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODE1(code)  code
#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODE2        ERROR_CODE
#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODEN2(n)    __PRIVATE_ERROR_CODEOF_PACKAGE_CODE##n
#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODEN(n)     __PRIVATE_ERROR_CODEOF_PACKAGE_CODEN2(n)
#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODE(...)    __PRIVATE_ERROR_CODEOF_PACKAGE_CODEX(__PRIVATE_ERROR_CODEOF_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#define __PRIVATE_ERROR_CODEOF_PACKAGE_CODEX(x)     x


#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8
#endif /* !EXCEPTION_DATA_POINTERS */


#ifdef __USE_KOS_KERNEL
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
                                  *       get produced instead of always causing `UNWIND_RECURSION' (which should only
                                  *       be produced if the unwind machinery itself has become faulty) */
#define EXCEPT_FMAYSIGNAL 0x0008 /* FLAG: The exception may be converted into a signal when `error_unwind(3)' cannot find
                                  *       a handler apart of some except-aware module (s.a. set_exception_handler:#4).
                                  *       If the exception cannot be translated, a coredump is performed. */
#endif /* !__KERNEL__ */
#define OFFSET_EXCEPTION_INFO_STATE     0
#define OFFSET_EXCEPTION_INFO_TRACE     __SIZEOF_ERROR_REGISTER_STATE
#define OFFSET_EXCEPTION_INFO_FLAGS    (__SIZEOF_ERROR_REGISTER_STATE+(__SIZEOF_POINTER__ * EXCEPT_BACKTRACE_SIZE))
#define OFFSET_EXCEPTION_INFO_CODE     (__SIZEOF_ERROR_REGISTER_STATE+(__SIZEOF_POINTER__ * (EXCEPT_BACKTRACE_SIZE+1)))
#define OFFSET_EXCEPTION_INFO_POINTERS (__SIZEOF_ERROR_REGISTER_STATE+(__SIZEOF_POINTER__ * (EXCEPT_BACKTRACE_SIZE+2)))
#endif /* __USE_KOS_KERNEL */

#ifndef __ERROR_REGISTER_STATE_TYPE
#define __ERROR_REGISTER_STATE_TYPE      struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE  __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */


#ifdef __CC__
#ifndef __error_register_state_t_defined
#define __error_register_state_t_defined 1
typedef __ERROR_REGISTER_STATE_TYPE error_register_state_t;
#endif /* !__error_register_state_t_defined */

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
	union __ATTR_PACKED {
		error_code_t          ei_code;     /* Current exception code. */
		struct __ATTR_PACKED {
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


#ifdef __KOS__

/* Returns non-zero if there is an active exception. */
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,struct exception_data *,__NOTHROW_NCX,error_data,(void),())
#ifdef __USE_KOS_KERNEL
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,struct exception_info *,__NOTHROW_NCX,error_info,(void),())
#endif /* __USE_KOS_KERNEL */
__CDECLARE(__ATTR_WUNUSED,error_code_t,__NOTHROW_NCX,error_code,(void),())
__CDECLARE(__ATTR_WUNUSED,__BOOL,__NOTHROW_NCX,error_active,(void),())
__CDECLARE(__ATTR_WUNUSED,error_class_t,__NOTHROW_NCX,error_class,(void),())
__CDECLARE(__ATTR_WUNUSED,error_subclass_t,__NOTHROW_NCX,error_subclass,(void),())
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,error_register_state_t *,__NOTHROW_NCX,error_register_state,(void),())

#ifdef __USE_KOS_KERNEL
/* Unwind the given register state to propagate the currently set error.
 * Following this, the returned register state should then be loaded. */
#if defined(__i386__) && !defined(__x86_64__)
__LIBC __ATTR_WUNUSED error_register_state_t *
__NOTHROW_NCX(__ATTR_FASTCALL error_unwind)(error_register_state_t *__restrict state) __CASMNAME_SAME("error_unwind");
#else
__LIBC __ATTR_WUNUSED error_register_state_t *
__NOTHROW_NCX(__LIBCCALL error_unwind)(error_register_state_t *__restrict state) __CASMNAME_SAME("error_unwind");
#endif
#endif /* __USE_KOS_KERNEL */

#ifndef __INTELLISENSE__
#define error_active()   (error_code() != E_OK)
#define error_class()     ERROR_CLASS(error_code())
#define error_subclass()  ERROR_SUBCLASS(error_code())
#endif /* !__INTELLISENSE__ */

/* Throw an exception. */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_COLD,,error_throw_current,(void),())
__CDECLARE_VOID(__ATTR_NORETURN,,error_rethrow,(void),())

/* Transform the given exception into a posix errno value. */
#ifdef __KERNEL__
__CDECLARE(__ATTR_WUNUSED,__errno_t,__NOTHROW,error_as_errno,(struct exception_data const *__restrict data),())
#else /* __KERNEL__ */
__CDECLARE(__ATTR_WUNUSED,__errno_t,__NOTHROW_NCX,error_as_errno,(struct exception_data const *__restrict data),())
#endif /* !__KERNEL__ */

struct __siginfo_struct;
/* Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
#ifdef __KERNEL__
__CDECLARE(__ATTR_WUNUSED,__BOOL,__NOTHROW,error_as_signal,(struct exception_data const *__restrict data, struct __siginfo_struct *__restrict result),(data,result))
#else /* __KERNEL__ */
__CDECLARE(__ATTR_WUNUSED,__BOOL,__NOTHROW_NCX,error_as_signal,(struct exception_data const *__restrict data, struct __siginfo_struct *__restrict result),(data,result))
#endif /* !__KERNEL__ */

/* Rethrow the last exception */
#define RETHROW()   error_rethrow()

#ifdef __INTELLISENSE__
/* Throw a new exception `code', which is either an exception class,
 * an exception code, or an exception-class+sub-class pair, written
 * as `(class,subclass)', going in hand with the macros defining the
 * various exceptions there are.
 * Following this, up to `EXCEPTION_DATA_POINTERS' optional exception
 * arguments may be provided, which are stored in `e_pointers', with
 * any argument not provided simply substituted in with `NULL' / 0. */
#define THROW                                        THROW
__LIBC __ATTR_NORETURN __ATTR_COLD void (__VLIBCCALL THROW)(error_code_t code, ...);

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
__CDECLARE(__ATTR_WUNUSED,__BOOL,__NOTHROW_NCX,was_thrown,(error_code_t code),(code))
#else
#define __PRIVATE_THROW_PACKAGE_CODE1(code) code
#define __PRIVATE_THROW_PACKAGE_CODE2       ERROR_CODE
#define __PRIVATE_THROW_PACKAGE_CODEN2(n) __PRIVATE_THROW_PACKAGE_CODE##n
#define __PRIVATE_THROW_PACKAGE_CODEN(n) __PRIVATE_THROW_PACKAGE_CODEN2(n)
#define __PRIVATE_THROW_PACKAGE_CODE(...) __PRIVATE_THROW_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#if defined(__i386__) && !defined(__x86_64__)
__LIBC __ATTR_NORETURN __ATTR_COLD void (__ATTR_FASTCALL error_throw)(error_code_t __code) __CASMNAME_SAME("error_throw");
__LIBC __ATTR_NORETURN __ATTR_COLD void (__ATTR_CDECL error_thrown)(error_code_t __code, unsigned int ___argc, ...) __CASMNAME_SAME("error_thrown");
#else
__LIBC __ATTR_NORETURN __ATTR_COLD void (__LIBCCALL error_throw)(error_code_t __code) __CASMNAME_SAME("error_throw");
__LIBC __ATTR_NORETURN __ATTR_COLD void (__LIBCCALL error_thrown)(error_code_t __code, unsigned int ___argc, ...) __CASMNAME_SAME("error_thrown");
#endif
#define __PRIVATE_THROW1(code)               error_throw(__PRIVATE_THROW_PACKAGE_CODE code)
#if EXCEPTION_DATA_POINTERS == 8
#define __PRIVATE_THROW2(code,a)               error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,1,(__UINTPTR_TYPE__)(a))
#define __PRIVATE_THROW3(code,a,b)             error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,2,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b))
#define __PRIVATE_THROW4(code,a,b,c)           error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,3,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c))
#define __PRIVATE_THROW5(code,a,b,c,d)         error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,4,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c),(__UINTPTR_TYPE__)(d))
#define __PRIVATE_THROW6(code,a,b,c,d,e)       error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,5,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c),(__UINTPTR_TYPE__)(d),(__UINTPTR_TYPE__)(e))
#define __PRIVATE_THROW7(code,a,b,c,d,e,f)     error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,6,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c),(__UINTPTR_TYPE__)(d),(__UINTPTR_TYPE__)(e),(__UINTPTR_TYPE__)(f))
#define __PRIVATE_THROW8(code,a,b,c,d,e,f,g)   error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,7,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c),(__UINTPTR_TYPE__)(d),(__UINTPTR_TYPE__)(e),(__UINTPTR_TYPE__)(f),(__UINTPTR_TYPE__)(g))
#define __PRIVATE_THROW9(code,a,b,c,d,e,f,g,h) error_thrown(__PRIVATE_THROW_PACKAGE_CODE code,8,(__UINTPTR_TYPE__)(a),(__UINTPTR_TYPE__)(b),(__UINTPTR_TYPE__)(c),(__UINTPTR_TYPE__)(d),(__UINTPTR_TYPE__)(e),(__UINTPTR_TYPE__)(f),(__UINTPTR_TYPE__)(g),(__UINTPTR_TYPE__)(h))
#else
#error "Unsupported EXCEPTION_DATA_POINTERS"
#endif
#define __PRIVATE_THROW_N2(n) __PRIVATE_THROW##n
#define __PRIVATE_THROW_N(n)  __PRIVATE_THROW_N2(n)
#define THROW(...)  __PRIVATE_THROW_N(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define __PRIVATE_WAS_THROWN_PACKAGE_CODE1(code)  \
   ((__builtin_constant_p(code) && (code) <= 0xffff) ? error_class() == (code) : error_code() == (code))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE2(class,subclass) (error_code() == ERROR_CODE(class,subclass))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n) __PRIVATE_WAS_THROWN_PACKAGE_CODE##n
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEN(n) __PRIVATE_WAS_THROWN_PACKAGE_CODEN2(n)
#define __PRIVATE_WAS_THROWN_PACKAGE_CODE(...) __PRIVATE_WAS_THROWN_PACKAGE_CODEX(__PRIVATE_WAS_THROWN_PACKAGE_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__))
#define __PRIVATE_WAS_THROWN_PACKAGE_CODEX(x)  x
#define was_thrown(code) __PRIVATE_WAS_THROWN_PACKAGE_CODE code
#endif

#ifdef __cplusplus
#define __PRIVATE_CATCH_UNIQUE3(x,y) x ## y
#define __PRIVATE_CATCH_UNIQUE2(x,y) __PRIVATE_CATCH_UNIQUE3(x,y)
#define __PRIVATE_CATCH_UNIQUE   __PRIVATE_CATCH_UNIQUE2(__catch_do_handle_,__LINE__)
#define TRY         try
#define EXCEPT      catch(...)
#endif /* __cplusplus */

#endif /* __KOS__ */
#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_EXCEPT_H */
