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
#ifndef _KOS_EXCEPT_REASON_INVAL_H
#define _KOS_EXCEPT_REASON_INVAL_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Context codes for E_INVALID_ARGUMENT exceptions */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_INVALID_ARGUMENT_CONTEXT_GENERIC,                            /* Generic context */
	E_INVALID_ARGUMENT_CONTEXT_SETFD_FD_FLAG,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `FD_*' flag passed to `F_SETFD' */
	E_INVALID_ARGUMENT_CONTEXT_SETFL_OFLAG,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `F_SETFL' */
	E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG,                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `dup3' */
	E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT,                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `PROT_*' flag */
	E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG,                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `MAP_*' flag
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_MASK: (flags & MAP_TYPE) !in [MAP_AUTOMATIC,MAP_SHARED,MAP_PRIVATE]
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Both `MAP_GROWSDOWN' and `MAP_GROWSUP' were specified in `flags' */
	E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR,                          /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: `MAP_FIXED' was specified when `MAP_ANONYMOUS' wasn't, but the `(file_offset & (getpagesize() - 1)) != ((uintptr_t)addr & (getpagesize() - 1))' */
	E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,                        /* E_INVALID_ARGUMENT_BAD_VALUE: The specified `length' is either `0' or is larger than the entirety of the designated address space. */
	E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE,                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mknod()' cannot be masked by `07777 | S_IFMT'.
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed to `mknod()' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
	E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE,                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mkdir()' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `unlinkat()' (accepted are `AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH'). */
	E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS,                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `linkat()' (accepted are `AT_SYMLINK_FOLLOW|AT_DOSPATH|AT_EMPTY_PATH|AT_NO_AUTOMOUNT'). */
	E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `UMOUNT_*' flag passed to `umount2()' (accepted are `MNT_FORCE|MNT_DETACH|MNT_EXPIRE|UMOUNT_NOFOLLOW'). */
	E_INVALID_ARGUMENT_CONTEXT_MOUNT_FLAGS,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `MS_*' flag passed to `mount()' (accepted are those defined in <sys/mount.h>). */
	E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE,                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `chmod()' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,                         /* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: [mask == O_ACCMODE]: The given `oflags' used `__O_ACCMODE_INVALID' as access mode
	                                                                * E_INVALID_ARGUMENT_UNKNOWN_FLAG:         Unknown `O_*' flag passed to `open()' */
	E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE,                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `open()' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND,                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown fcntl() command */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown ioctl() command */
	E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFS_FLAGS,                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `of_flags' field of a `hop_openfd'-compatible HOP command contained flags other than `IO_CLOEXEC|IO_CLOFORK'. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFD_MODE,                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `of_mode' field of a `hop_openfd'-compatible HOP command wasn't one of `HOP_OPENFD_MODE_*'. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,                        /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `hop()' wasn't recognized by the associated handle. */
	E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE,                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `hopf()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `ioctlf()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_READF_MODE,                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `readf()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `writef()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `preadf()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE,                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `pwritef()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS,       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_OPENNODE_FLAG_*' flag passed in `hop_directory_opennode::don_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS,     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed in `hop_directory_creatfile::dcf_oflags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE,       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_creatfile::dcf_mode' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS,         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_REMOVE_FLAG_*' flag passed in `hop_directory_remove::drm_flags'
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Neither `HOP_DIRECTORY_REMOVE_FLAG_REGULAR', nor `HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY' was given in `hop_directory_remove::dr_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS,         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_RENAME_FLAG_*' flag passed in `hop_directory_rename::drn_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS,           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_LINK_FLAG_*' flag passed in `hop_directory_link::dli_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS,        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_SYMLINK_FLAG_*' flag passed in `hop_directory_symlink::dsl_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE,         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_symlink::dsl_mode' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS,          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKNOD_FLAG_*' flag passed in `hop_directory_mknod::dmn_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE,           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mknod::dmn_mode' cannot be masked by `07777 | S_IFMT'.
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed in `hop_directory_mknod::dmn_mode' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS,          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKDIR_FLAG_*' flag passed in `hop_directory_mkdir::dmd_flags' */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE,           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mkdir::dmd_mode' cannot be masked by `07777'. */
	E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL,                       /* E_INVALID_ARGUMENT_BAD_VALUE: The `level' argument passed to `syslog()' wasn't recognized. */
	E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS,                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frealpath4' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value for `whence' in `lseek()' */
	E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' contains invalid/unknown flags
	                                                                * E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & READDIR_MODEMASK' isn't recognized */
	E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS,                  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Invalid set of `MAP_*' flags passed to `loadlibrary()' */
	E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN,           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: Segments have inconsistent page alignments */
	E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN,           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid byte-alignment */
	E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN,           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid file-alignment */
	E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `kfstatat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS,                  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `freadlinkat' isn't a set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchmodat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchownat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `execveat' isn't a set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `waitid()' isn't a set of `WNOHANG|WNOREAP|WEXITED|WSTOPPED|WCONTINUED'
	                                                                * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: The `options' argument passed to `waitid()' contains none of `WEXITED|WSTOPPED|WCONTINUED' */
	E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH,                       /* E_INVALID_ARGUMENT_BAD_VALUE: The `which' value passed to `waitid()' isn't one of `P_ALL,P_PID,P_PGID' */
	E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `wait4()' isn't a set of `WNOHANG|WUNTRACED|WCONTINUED|WNOWAIT' */
	E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE,                      /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to set a user-space address as the base of the `struct userkern' segment */
	E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID,                      /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write a value other than `0' to `struct userkern::ut_ppid' */
	E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID,                       /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write an invalid value to `struct userkern::ut_sid' */
	E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `prot' argument passed to `mprotect()' isn't a set of `PROT_EXEC|PROT_WRITE|PROT_READ' */
	E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchdirat()' isn't a set of `0|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS,                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `rpc_schedule()' is malformed */
	E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE,                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `iomode' passed to `kreaddirf()' could not be masked by `IO_USERF_MASK'. */
	E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS,                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `pipe2()' cannot be masked by `O_CLOEXEC|O_CLOFORK|O_NONBLOCK|O_DIRECT' */
	E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND,                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `ksysctl()' wasn't recognized */
	E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT,                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `sysctl_driver_insmod::im_format', `sysctl_driver_delmod::dm_format' or `sysctl_driver_getmod::gm_format' wasn't one of `SYSCTL_DRIVER_FORMAT_*', or wasn't recognized as valid in the specific context */
	E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS,                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_insmod::im_flags' cannot be masked by `KSYSCTL_DRIVER_INSMOD_F*' */
	E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS,                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_delmod::dm_flags' cannot be masked by `KSYSCTL_DRIVER_DELMOD_F*' */
	E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS,                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frenameat()' isn't a set of `0|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS,                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fsymlinkat()' isn't a set of `0|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmknodat()' isn't a set of `0|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmkdirat()' isn't a set of `0|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND,                     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCXONC)' isn't one of `TC(I|O)(ON|OFF)' */
	E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND,                     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCFLSH)' isn't one of `TC(I|O|IO)FLUSH' */
	E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE,         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & EXCEPT_HANDLER_MODE_MASK' isn't one of `EXCEPT_HANDLER_MODE_*'
	                                                                * E_INVALID_ARGUMENT_UNKNOWN_FLAG:    The given `mode & ~EXCEPT_HANDLER_MODE_MASK' isn't a set of `EXCEPT_HANDLER_FLAG_*' */
	E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,                 /* E_INVALID_ARGUMENT_BAD_VALUE: One of the register values passed to sigreturn is invalid (`value' is the arch-specific register ID; e.g. `X86_REGISTER_SEGMENT_SS') */
	E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,                        /* E_INVALID_ARGUMENT_BAD_VALUE: Bad signal number passed to `raise()', `kill()', `tgkill()', etc. */
	E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO,                       /* E_INVALID_ARGUMENT_BAD_VALUE: Bad trap number passed to `debugtrap()' */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETRDKEY_BADMODE,       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, KBDIO_SETRDKEY, ...)' */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE,    /* E_INVALID_ARGUMENT_BAD_VALUE: The specified keymap data block is too large */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT,  /* E_INVALID_ARGUMENT_BAD_VALUE: The text contained within the keymap is corrupted/invalid */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING, /* E_INVALID_ARGUMENT_BAD_VALUE: The specified default encoding is invalid */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSMODE_BADMODE,   /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, MOUSEIO_SETABSMODE, ...)' */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSRECT_BADBOUNDS, /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t minx, miny, maxx, maxy] The bounds specified are invalid and cannot be used */
	E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE,     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid (or unsupported) value passed as argument to `ioctl(fd, KBDIO_SETDBGF12, ...)' */
	E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,                 /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t given_sigset_size] The sigset size passed to one of the RT signal system calls is incorrect */
	E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS,                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to sigaction() or rt_sigaction() isn't a set of `SA_*' */
	E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW,                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid `how' passed to `sigprocmask()' (must be one of { SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK }) */
	E_INVALID_ARGUMENT_CONTEXT_RAISE_PID,                          /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_pid] Bad pid value to one of the signal functions */
	E_INVALID_ARGUMENT_CONTEXT_RAISE_TID,                          /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_tid] Bad tid value to one of the signal functions */
	E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,              /* E_INVALID_ARGUMENT_BAD_VALUE: [int given_code] Attempted to raise a signal using `rt_sigqueueinfo()' or `rt_tgsigqueueinfo()' with a bad `si_code' */
	E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS,                        /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [syscall_ulong_t reserved] The `reserved' argument passed to `mktty()' is non-zero */
	E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME,                         /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t namelen, max_namelen] The `name' argument passed to `mktty()' is too long */
	E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `type' argument passed to `faccessat()' isn't a set of `F_OK|R_OK|W_OK|X_OK' */
	E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS,                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `faccessat()' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE,                    /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to read()/write() to/from an eventfd object using a buffer size less that 8 */
	E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh,    /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t value] Attempted to write 0xffffffffffffffff to an eventfd object */
	E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS,                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_eventfd2()' is not masked by `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
	E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_signalfd4()' is not masked by `SFD_NONBLOCK | SFD_CLOEXEC' */
	E_INVALID_ARGUMENT_CONTEXT_BAD_PIPE_BUFFER_SIZE,               /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to pass a too low value to `F_SETPIPE_SZ' */
	E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,                        /* E_INVALID_ARGUMENT_BAD_VALUE: [int intval] Attempted to write an invalid integer to a system configuration file */
	E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON,                       /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t reason] Bad reason code passed to `debugtrap()' */
	E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY,                    /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t perso] Bad personality code passed to `SYSCTL_SYSCALL_(GET|SET)_PERSONALITY'
	                                                                * E_INVALID_ARGUMENT_UNKNOWN_FLAG: The least significant argument-bit of `SYSCTL_SYSCALL_GET_PERSONALITY' was set (arg should be `kp << 1') */
	E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,                          /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `lfutex()', `lfutexlock()', `lfutexexpr()' or `lfutexlockexpr()' is invalid.
	                                                                * E_INVALID_ARGUMENT_UNKNOWN_FLAG: When masked with `LFUTEX_FLAGMASK', `futex_op' contains bits not defined by `LFUTEX_WAIT_FLAG_*'
	                                                                * E_INVALID_ARGUMENT_RESERVED_FLAG: The `timeout' argument was non-NULL, but `futex_op & LFUTEX_FLAGMASK' contained non-zero `LFUTEX_WAIT_FLAG_TIMEOUT_*' flags. 
	                                                                * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was false, but the `LFUTEX_WAIT_FLAG_TIMEOUT_*' bits were set.
	                                                                * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was true, but unused flag bits were set. */
	E_INVALID_ARGUMENT_CONTEXT_IOPL_LEVEL,                         /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t level] The `level' argument passed to `iopl()' was negative, or greater than `3' */
	E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE,                       /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t first_bad_port] At least one of the ports specified by the given range lies outside the valid port bounds */
	E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON,                      /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t turn_on] The `turn_on' argument is neither `0' nor `1' */
	E_INVALID_ARGUMENT_CONTEXT_FUTEX_OP,                           /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `futex()' is invalid. */
	E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE,                         /* E_INVALID_ARGUMENT_BAD_VALUE: [unsigned int mode = (KD_TEXT, KD_GRAPHICS)] Attempted to set an unsupported video mode. */
	E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC,                        /* E_INVALID_ARGUMENT_BAD_VALUE: [vd_codec_t codec] Attempted to set an unsupported video codec/resolution combination. */
	E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0,              /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [uintptr_t index] The `hop_driver_string::ds_index' field was non-zero for a HOP that only accepts `0' as index. */
	E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT,                         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `getsockopt()'. */
	E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT,                         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `setsockopt()'. */
	E_INVALID_ARGUMENT_CONTEXT_ACCEPT_NOT_LISTENING,               /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND,                   /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED,             /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED,          /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED,                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `send(2)' on a socket without first calling `connect(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED,                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
	E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED,          /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
	E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND,                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
	E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY,          /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `bind()'). */
	E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY,       /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `connect()'). */
	E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY,        /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `sendto()'). */
	E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY,                  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `family' argument passed to `socket(2)' is unknown or unsupported. */
	E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE,                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `socket(2)' is unknown or unsupported by the given `family'. */
	E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL,                /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `protocol' argument passed to `socket(2)' is unknown or unsupported by the given `family' and `type'. */
	E_INVALID_ARGUMENT_CONTEXT_ACCEPT4_SOCK_FLAGS,                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of socket flags passed to `sys_accept()' is not masked by `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
	E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_send()', `sys_sendto()', `sys_sendmsg()' or `sys_sendmmsg()' is not masked by `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
	E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS,                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_recv()', `sys_recvfrom()', `sys_recvmsg()' or `sys_recvmmsg()' is not masked by `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
	E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_HOW,                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `how' passed to `sys_shutdown()' isn't one of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
	E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_OPCODE,                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The kernel doesn't recognize, or doesn't support the given `struct uvio_response::ur_opcode' */
	E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_RESPFLAGS,                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags given in `struct uvio_response::ur_respflags' isn't masked by `UVIO_RESPONSE_FLAG_NORMAL' */
	E_INVALID_ARGUMENT_CONTEXT_USERVIOFD_FLAGS,                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `userviofd(2)' isn't a set of `O_NONBLOCK | O_CLOEXEC | O_CLOFORK' */
	E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS,        /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
	E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS,              /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `write(2)' to a fifo without any connected readers. */
	E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS,                   /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_open(2)' was non-zero. */
	E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS,                  /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_getfd(2)' was non-zero. */
	E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS,      /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_send_signal(2)' was non-zero. */
	E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER,              /* E_INVALID_ARGUMENT_BAD_STATE: The thread specified by `pid' in a call to `pidfd_open(2)' isn't a process leader. */
	E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO,                      /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: In a call to `rt_sigqueueinfo(2)', `rt_tgsigqueueinfo(2)' or `pidfd_send_signal(2)',
	                                                                *                                        `uinfo' was given, but the pointed-to signal number didn't match the given `usigno' */
	E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS,                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' isn't a set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
	E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME,         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' (with `filename' set to `NULL') isn't a set of `0 | AT_CHANGE_CTIME' */
	E_INVALID_ARGUMENT_CONTEXT_UNSHARE_WHAT,                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `what' argument passed to `unshare(2)' isn't a subset of:
	                                                                * `CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_CRED | CLONE_NEWNS | CLONE_SYSVSEM |
	                                                                *  CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET | CLONE_IO' */
	E_INVALID_ARGUMENT_CONTEXT_KCMP_TYPE,                          /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `kcmp(2)' isn't one of `KCMP_*' from `<linux/kcmp.h>' */
	E_INVALID_ARGUMENT_CONTEXT_DELETE_MODULE_FLAGS,                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `delete_module(2)' cannot be masked by `O_TRUNC | O_NONBLOCK' */
	E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS,                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `epoll_create1(2)' cannot be masked by `EPOLL_CLOEXEC | EPOLL_CLOFORK' */
	E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP,                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `op' argument passed to `epoll_ctl(2)' isn't one of `EPOLL_CTL_*' from `<sys/epoll.h>' */
	E_INVALID_ARGUMENT_CONTEXT_EPOLL_WAIT_ZERO_MAXEVENTS,          /* E_INVALID_ARGUMENT_BAD_VALUE: The `maxevents' argument passed to `epoll_wait(2)' is `<= 0' */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_INVALID_ARGUMENT_CONTEXT_GENERIC                            E_INVALID_ARGUMENT_CONTEXT_GENERIC                            /* Generic context */
#define E_INVALID_ARGUMENT_CONTEXT_SETFD_FD_FLAG                      E_INVALID_ARGUMENT_CONTEXT_SETFD_FD_FLAG                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `FD_*' flag passed to `F_SETFD' */
#define E_INVALID_ARGUMENT_CONTEXT_SETFL_OFLAG                        E_INVALID_ARGUMENT_CONTEXT_SETFL_OFLAG                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `F_SETFL' */
#define E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG                         E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `dup3' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT                          E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `PROT_*' flag */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG                          E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `MAP_*' flag
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_MASK: (flags & MAP_TYPE) !in [MAP_AUTOMATIC,MAP_SHARED,MAP_PRIVATE]
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Both `MAP_GROWSDOWN' and `MAP_GROWSUP' were specified in `flags' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR                          E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR                          /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: `MAP_FIXED' was specified when `MAP_ANONYMOUS' wasn't, but the `(file_offset & (getpagesize() - 1)) != ((uintptr_t)addr & (getpagesize() - 1))' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH                        E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH                        /* E_INVALID_ARGUMENT_BAD_VALUE: The specified `length' is either `0' or is larger than the entirety of the designated address space. */
#define E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE                         E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mknod()' cannot be masked by `07777 | S_IFMT'.
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed to `mknod()' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE                         E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mkdir()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `unlinkat()' (accepted are `AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH'). */
#define E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS                       E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `linkat()' (accepted are `AT_SYMLINK_FOLLOW|AT_DOSPATH|AT_EMPTY_PATH|AT_NO_AUTOMOUNT'). */
#define E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS                      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `UMOUNT_*' flag passed to `umount2()' (accepted are `MNT_FORCE|MNT_DETACH|MNT_EXPIRE|UMOUNT_NOFOLLOW'). */
#define E_INVALID_ARGUMENT_CONTEXT_MOUNT_FLAGS                        E_INVALID_ARGUMENT_CONTEXT_MOUNT_FLAGS                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `MS_*' flag passed to `mount()' (accepted are those defined in <sys/mount.h>). */
#define E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE                         E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `chmod()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG                         E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG                         /* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: [mask == O_ACCMODE]: The given `oflags' used `__O_ACCMODE_INVALID' as access mode
                                                                                                                                     * E_INVALID_ARGUMENT_UNKNOWN_FLAG:         Unknown `O_*' flag passed to `open()' */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE                          E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `open()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND                      E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown fcntl() command */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND                      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown ioctl() command */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFS_FLAGS                   E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFS_FLAGS                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `of_flags' field of a `hop_openfd'-compatible HOP command contained flags other than `IO_CLOEXEC|IO_CLOFORK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFD_MODE                    E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFD_MODE                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `of_mode' field of a `hop_openfd'-compatible HOP command wasn't one of `HOP_OPENFD_MODE_*'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND                        E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND                        /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `hop()' wasn't recognized by the associated handle. */
#define E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE                          E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE                          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `hopf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE                        E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `ioctlf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_READF_MODE                         E_INVALID_ARGUMENT_CONTEXT_READF_MODE                         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `readf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE                        E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `writef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE                        E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `preadf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE                       E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `pwritef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS       E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_OPENNODE_FLAG_*' flag passed in `hop_directory_opennode::don_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS     E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed in `hop_directory_creatfile::dcf_oflags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE       E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_creatfile::dcf_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS         E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_REMOVE_FLAG_*' flag passed in `hop_directory_remove::drm_flags'
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Neither `HOP_DIRECTORY_REMOVE_FLAG_REGULAR', nor `HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY' was given in `hop_directory_remove::dr_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS         E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_RENAME_FLAG_*' flag passed in `hop_directory_rename::drn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS           E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_LINK_FLAG_*' flag passed in `hop_directory_link::dli_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS        E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_SYMLINK_FLAG_*' flag passed in `hop_directory_symlink::dsl_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE         E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_symlink::dsl_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS          E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKNOD_FLAG_*' flag passed in `hop_directory_mknod::dmn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE           E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mknod::dmn_mode' cannot be masked by `07777 | S_IFMT'.
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed in `hop_directory_mknod::dmn_mode' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS          E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS          /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKDIR_FLAG_*' flag passed in `hop_directory_mkdir::dmd_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE           E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE           /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mkdir::dmd_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL                       E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL                       /* E_INVALID_ARGUMENT_BAD_VALUE: The `level' argument passed to `syslog()' wasn't recognized. */
#define E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS                   E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frealpath4' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE                       E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value for `whence' in `lseek()' */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE                      E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' contains invalid/unknown flags
                                                                                                                                     * E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & READDIR_MODEMASK' isn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS                  E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS                  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Invalid set of `MAP_*' flags passed to `loadlibrary()' */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN           E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: Segments have inconsistent page alignments */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN           E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid byte-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN           E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN           /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid file-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `kfstatat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS                  E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS                  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `freadlinkat' isn't a set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchmodat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchownat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `execveat' isn't a set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS                     E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `waitid()' isn't a set of `WNOHANG|WNOREAP|WEXITED|WSTOPPED|WCONTINUED'
                                                                                                                                     * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: The `options' argument passed to `waitid()' contains none of `WEXITED|WSTOPPED|WCONTINUED' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH                       E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH                       /* E_INVALID_ARGUMENT_BAD_VALUE: The `which' value passed to `waitid()' isn't one of `P_ALL,P_PID,P_PGID' */
#define E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS                      E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `wait4()' isn't a set of `WNOHANG|WUNTRACED|WCONTINUED|WNOWAIT' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE                      E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE                      /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to set a user-space address as the base of the `struct userkern' segment */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID                      E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID                      /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write a value other than `0' to `struct userkern::ut_ppid' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID                       E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID                       /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write an invalid value to `struct userkern::ut_sid' */
#define E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT                      E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `prot' argument passed to `mprotect()' isn't a set of `PROT_EXEC|PROT_WRITE|PROT_READ' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS                 E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `rpc_schedule()' is malformed */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE                   E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `iomode' passed to `kreaddirf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS                        E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS                        /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `pipe2()' cannot be masked by `O_CLOEXEC|O_CLOFORK|O_NONBLOCK|O_DIRECT' */
#define E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND                    E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `ksysctl()' wasn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT                      E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT                      /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `sysctl_driver_insmod::im_format', `sysctl_driver_delmod::dm_format' or `sysctl_driver_getmod::gm_format' wasn't one of `SYSCTL_DRIVER_FORMAT_*', or wasn't recognized as valid in the specific context */
#define E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS                       E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_insmod::im_flags' cannot be masked by `KSYSCTL_DRIVER_INSMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS                       E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_delmod::dm_flags' cannot be masked by `KSYSCTL_DRIVER_DELMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS                    E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frenameat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS                   E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS                   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fsymlinkat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmknodat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmkdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND                     E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND                     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCXONC)' isn't one of `TC(I|O)(ON|OFF)' */
#define E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND                     E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND                     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCFLSH)' isn't one of `TC(I|O|IO)FLUSH' */
#define E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE         E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & EXCEPT_HANDLER_MODE_MASK' isn't one of `EXCEPT_HANDLER_MODE_*'
                                                                                                                                     * E_INVALID_ARGUMENT_UNKNOWN_FLAG:    The given `mode & ~EXCEPT_HANDLER_MODE_MASK' isn't a set of `EXCEPT_HANDLER_FLAG_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER                 E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER                 /* E_INVALID_ARGUMENT_BAD_VALUE: One of the register values passed to sigreturn is invalid (`value' is the arch-specific register ID; e.g. `X86_REGISTER_SEGMENT_SS') */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO                        E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO                        /* E_INVALID_ARGUMENT_BAD_VALUE: Bad signal number passed to `raise()', `kill()', `tgkill()', etc. */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO                       E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO                       /* E_INVALID_ARGUMENT_BAD_VALUE: Bad trap number passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETRDKEY_BADMODE       E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETRDKEY_BADMODE       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, KBDIO_SETRDKEY, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE    E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE    /* E_INVALID_ARGUMENT_BAD_VALUE: The specified keymap data block is too large */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT  E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT  /* E_INVALID_ARGUMENT_BAD_VALUE: The text contained within the keymap is corrupted/invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING /* E_INVALID_ARGUMENT_BAD_VALUE: The specified default encoding is invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSMODE_BADMODE   E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSMODE_BADMODE   /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, MOUSEIO_SETABSMODE, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSRECT_BADBOUNDS E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSRECT_BADBOUNDS /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t minx, miny, maxx, maxy] The bounds specified are invalid and cannot be used */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE     E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE     /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid (or unsupported) value passed as argument to `ioctl(fd, KBDIO_SETDBGF12, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE                 E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE                 /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t given_sigset_size] The sigset size passed to one of the RT signal system calls is incorrect */
#define E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS                E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to sigaction() or rt_sigaction() isn't a set of `SA_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW                    E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid `how' passed to `sigprocmask()' (must be one of { SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK }) */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_PID                          E_INVALID_ARGUMENT_CONTEXT_RAISE_PID                          /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_pid] Bad pid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_TID                          E_INVALID_ARGUMENT_CONTEXT_RAISE_TID                          /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_tid] Bad tid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE              E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE              /* E_INVALID_ARGUMENT_BAD_VALUE: [int given_code] Attempted to raise a signal using `rt_sigqueueinfo()' or `rt_tgsigqueueinfo()' with a bad `si_code' */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS                        E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS                        /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [syscall_ulong_t reserved] The `reserved' argument passed to `mktty()' is non-zero */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME                         E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME                         /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t namelen, max_namelen] The `name' argument passed to `mktty()' is too long */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE                     E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `type' argument passed to `faccessat()' isn't a set of `F_OK|R_OK|W_OK|X_OK' */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS                    E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `faccessat()' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE                    E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE                    /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to read()/write() to/from an eventfd object using a buffer size less that 8 */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh    E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh    /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t value] Attempted to write 0xffffffffffffffff to an eventfd object */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS                      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS                      /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_eventfd2()' is not masked by `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_signalfd4()' is not masked by `SFD_NONBLOCK | SFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_PIPE_BUFFER_SIZE               E_INVALID_ARGUMENT_CONTEXT_BAD_PIPE_BUFFER_SIZE               /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to pass a too low value to `F_SETPIPE_SZ' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER                        E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER                        /* E_INVALID_ARGUMENT_BAD_VALUE: [int intval] Attempted to write an invalid integer to a system configuration file */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON                       E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON                       /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t reason] Bad reason code passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY                    E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY                    /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t perso] Bad personality code passed to `SYSCTL_SYSCALL_(GET|SET)_PERSONALITY'
                                                                                                                                     * E_INVALID_ARGUMENT_UNKNOWN_FLAG: The least significant argument-bit of `SYSCTL_SYSCALL_GET_PERSONALITY' was set (arg should be `kp << 1') */
#define E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP                          E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP                          /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `lfutex()', `lfutexlock()', `lfutexexpr()' or `lfutexlockexpr()' is invalid.
                                                                                                                                     * E_INVALID_ARGUMENT_UNKNOWN_FLAG: When masked with `LFUTEX_FLAGMASK', `futex_op' contains bits not defined by `LFUTEX_WAIT_FLAG_*'
                                                                                                                                     * E_INVALID_ARGUMENT_RESERVED_FLAG: The `timeout' argument was non-NULL, but `futex_op & LFUTEX_FLAGMASK' contained non-zero `LFUTEX_WAIT_FLAG_TIMEOUT_*' flags.
                                                                                                                                     * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was false, but the `LFUTEX_WAIT_FLAG_TIMEOUT_*' bits were set.
                                                                                                                                     * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was true, but unused flag bits were set. */
#define E_INVALID_ARGUMENT_CONTEXT_IOPL_LEVEL                         E_INVALID_ARGUMENT_CONTEXT_IOPL_LEVEL                         /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t level] The `level' argument passed to `iopl()' was negative, or greater than `3' */
#define E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE                       E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE                       /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t first_bad_port] At least one of the ports specified by the given range lies outside the valid port bounds */
#define E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON                      E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON                      /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t turn_on] The `turn_on' argument is neither `0' nor `1' */
#define E_INVALID_ARGUMENT_CONTEXT_FUTEX_OP                           E_INVALID_ARGUMENT_CONTEXT_FUTEX_OP                           /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `futex()' is invalid. */
#define E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE                         E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE                         /* E_INVALID_ARGUMENT_BAD_VALUE: [unsigned int mode = (KD_TEXT, KD_GRAPHICS)] Attempted to set an unsupported video mode. */
#define E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC                        E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC                        /* E_INVALID_ARGUMENT_BAD_VALUE: [vd_codec_t codec] Attempted to set an unsupported video codec/resolution combination. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0              E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0              /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [uintptr_t index] The `hop_driver_string::ds_index' field was non-zero for a HOP that only accepts `0' as index. */
#define E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT                         E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT                         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `getsockopt()'. */
#define E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT                         E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT                         /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `setsockopt()'. */
#define E_INVALID_ARGUMENT_CONTEXT_ACCEPT_NOT_LISTENING               E_INVALID_ARGUMENT_CONTEXT_ACCEPT_NOT_LISTENING               /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND                   E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND                   /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED             E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED             /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED          E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED          /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED                 E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `send(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED                 E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED          E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED          /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
#define E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND                 E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND                 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
#define E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY          E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY          /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `bind()'). */
#define E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY       E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY       /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `connect()'). */
#define E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY        E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY        /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `sendto()'). */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY                  E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY                  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `family' argument passed to `socket(2)' is unknown or unsupported. */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE                    E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `socket(2)' is unknown or unsupported by the given `family'. */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL                E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL                /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `protocol' argument passed to `socket(2)' is unknown or unsupported by the given `family' and `type'. */
#define E_INVALID_ARGUMENT_CONTEXT_ACCEPT4_SOCK_FLAGS                 E_INVALID_ARGUMENT_CONTEXT_ACCEPT4_SOCK_FLAGS                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of socket flags passed to `sys_accept()' is not masked by `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_send()', `sys_sendto()', `sys_sendmsg()' or `sys_sendmmsg()' is not masked by `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
#define E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS                     E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS                     /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_recv()', `sys_recvfrom()', `sys_recvmsg()' or `sys_recvmmsg()' is not masked by `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
#define E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_HOW                       E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_HOW                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `how' passed to `sys_shutdown()' isn't one of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_OPCODE                    E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_OPCODE                    /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The kernel doesn't recognize, or doesn't support the given `struct uvio_response::ur_opcode' */
#define E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_RESPFLAGS                 E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_RESPFLAGS                 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags given in `struct uvio_response::ur_respflags' isn't masked by `UVIO_RESPONSE_FLAG_NORMAL' */
#define E_INVALID_ARGUMENT_CONTEXT_USERVIOFD_FLAGS                    E_INVALID_ARGUMENT_CONTEXT_USERVIOFD_FLAGS                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `userviofd(2)' isn't a set of `O_NONBLOCK | O_CLOEXEC | O_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS        E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS        /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
#define E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS              E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS              /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `write(2)' to a fifo without any connected readers. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS                   E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS                   /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_open(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS                  E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS                  /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_getfd(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS      E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS      /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_send_signal(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER              E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER              /* E_INVALID_ARGUMENT_BAD_STATE: The thread specified by `pid' in a call to `pidfd_open(2)' isn't a process leader. */
#define E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO                      E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO                      /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: In a call to `rt_sigqueueinfo(2)', `rt_tgsigqueueinfo(2)' or `pidfd_send_signal(2)',
                                                                                                                                     *                                        `uinfo' was given, but the pointed-to signal number didn't match the given `usigno' */
#define E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS                    E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS                    /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' isn't a set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME         E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME         /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' (with `filename' set to `NULL') isn't a set of `0 | AT_CHANGE_CTIME' */
#define E_INVALID_ARGUMENT_CONTEXT_UNSHARE_WHAT                       E_INVALID_ARGUMENT_CONTEXT_UNSHARE_WHAT                       /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `what' argument passed to `unshare(2)' isn't a subset of:
                                                                                                                                     * `CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_CRED | CLONE_NEWNS | CLONE_SYSVSEM |
                                                                                                                                     *  CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET | CLONE_IO' */
#define E_INVALID_ARGUMENT_CONTEXT_KCMP_TYPE                          E_INVALID_ARGUMENT_CONTEXT_KCMP_TYPE                          /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `kcmp(2)' isn't one of `KCMP_*' from `<linux/kcmp.h>' */
#define E_INVALID_ARGUMENT_CONTEXT_DELETE_MODULE_FLAGS                E_INVALID_ARGUMENT_CONTEXT_DELETE_MODULE_FLAGS                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `delete_module(2)' cannot be masked by `O_TRUNC | O_NONBLOCK' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS                E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS                /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `epoll_create1(2)' cannot be masked by `EPOLL_CLOEXEC | EPOLL_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP                       E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP                       /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `op' argument passed to `epoll_ctl(2)' isn't one of `EPOLL_CTL_*' from `<sys/epoll.h>' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_WAIT_ZERO_MAXEVENTS          E_INVALID_ARGUMENT_CONTEXT_EPOLL_WAIT_ZERO_MAXEVENTS          /* E_INVALID_ARGUMENT_BAD_VALUE: The `maxevents' argument passed to `epoll_wait(2)' is `<= 0' */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_INVALID_ARGUMENT_CONTEXT_GENERIC                            0   /* Generic context */
#define E_INVALID_ARGUMENT_CONTEXT_SETFD_FD_FLAG                      1   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `FD_*' flag passed to `F_SETFD' */
#define E_INVALID_ARGUMENT_CONTEXT_SETFL_OFLAG                        2   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `F_SETFL' */
#define E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG                         3   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed to `dup3' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT                          4   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `PROT_*' flag */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG                          5   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `MAP_*' flag
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_MASK: (flags & MAP_TYPE) !in [MAP_AUTOMATIC,MAP_SHARED,MAP_PRIVATE]
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Both `MAP_GROWSDOWN' and `MAP_GROWSUP' were specified in `flags' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR                          6   /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: `MAP_FIXED' was specified when `MAP_ANONYMOUS' wasn't, but the `(file_offset & (getpagesize() - 1)) != ((uintptr_t)addr & (getpagesize() - 1))' */
#define E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH                        7   /* E_INVALID_ARGUMENT_BAD_VALUE: The specified `length' is either `0' or is larger than the entirety of the designated address space. */
#define E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE                         8   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mknod()' cannot be masked by `07777 | S_IFMT'.
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed to `mknod()' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE                         9   /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `mkdir()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS                     10  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `unlinkat()' (accepted are `AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH'). */
#define E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS                       11  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `AT_*' flag passed to `linkat()' (accepted are `AT_SYMLINK_FOLLOW|AT_DOSPATH|AT_EMPTY_PATH|AT_NO_AUTOMOUNT'). */
#define E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS                      12  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `UMOUNT_*' flag passed to `umount2()' (accepted are `MNT_FORCE|MNT_DETACH|MNT_EXPIRE|UMOUNT_NOFOLLOW'). */
#define E_INVALID_ARGUMENT_CONTEXT_MOUNT_FLAGS                        13  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Illegal `MS_*' flag passed to `mount()' (accepted are those defined in <sys/mount.h>). */
#define E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE                         14  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `chmod()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG                         15  /* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: [mask == O_ACCMODE]: The given `oflags' used `__O_ACCMODE_INVALID' as access mode
                                                                           * E_INVALID_ARGUMENT_UNKNOWN_FLAG:         Unknown `O_*' flag passed to `open()' */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE                          16  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed to `open()' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND                      17  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown fcntl() command */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND                      18  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Unknown ioctl() command */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFS_FLAGS                   19  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `of_flags' field of a `hop_openfd'-compatible HOP command contained flags other than `IO_CLOEXEC|IO_CLOFORK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_OPENFD_MODE                    20  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `of_mode' field of a `hop_openfd'-compatible HOP command wasn't one of `HOP_OPENFD_MODE_*'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND                        21  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `hop()' wasn't recognized by the associated handle. */
#define E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE                          22  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `hopf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE                        23  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `ioctlf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_READF_MODE                         24  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `readf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE                        25  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `writef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE                        26  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `preadf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE                       27  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' passed to `pwritef()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS       28  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_OPENNODE_FLAG_*' flag passed in `hop_directory_opennode::don_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS     29  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `O_*' flag passed in `hop_directory_creatfile::dcf_oflags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE       30  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_creatfile::dcf_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS         31  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_REMOVE_FLAG_*' flag passed in `hop_directory_remove::drm_flags'
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: Neither `HOP_DIRECTORY_REMOVE_FLAG_REGULAR', nor `HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY' was given in `hop_directory_remove::dr_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS         32  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_RENAME_FLAG_*' flag passed in `hop_directory_rename::drn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS           33  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_LINK_FLAG_*' flag passed in `hop_directory_link::dli_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS        34  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_SYMLINK_FLAG_*' flag passed in `hop_directory_symlink::dsl_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE         35  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The mode argument passed in `hop_directory_symlink::dsl_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS          36  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKNOD_FLAG_*' flag passed in `hop_directory_mknod::dmn_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE           37  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mknod::dmn_mode' cannot be masked by `07777 | S_IFMT'.
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_MASK: When masked by `S_IFMT', the mode argument passed in `hop_directory_mknod::dmn_mode' doesn't evaluate to one of `S_IFREG', `S_IFCHR' or `S_IFBLK' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS          38  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Unknown `HOP_DIRECTORY_MKDIR_FLAG_*' flag passed in `hop_directory_mkdir::dmd_flags' */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE           39  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG:  The mode argument passed in `hop_directory_mkdir::dmd_mode' cannot be masked by `07777'. */
#define E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL                       40  /* E_INVALID_ARGUMENT_BAD_VALUE: The `level' argument passed to `syslog()' wasn't recognized. */
#define E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS                   41  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frealpath4' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE                       42  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value for `whence' in `lseek()' */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE                      43  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `mode' contains invalid/unknown flags
                                                                           * E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & READDIR_MODEMASK' isn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS                  44  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: Invalid set of `MAP_*' flags passed to `loadlibrary()' */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN           45  /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: Segments have inconsistent page alignments */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN           46  /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid byte-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN           47  /* E_INVALID_ARGUMENT_BAD_ALIGNMENT: A segment has an invalid file-alignment */
#define E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS                     48  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `kfstatat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS                  49  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `freadlinkat' isn't a set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS                     50  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchmodat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS                     51  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchownat' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS                     52  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `execveat' isn't a set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS                     53  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `waitid()' isn't a set of `WNOHANG|WNOREAP|WEXITED|WSTOPPED|WCONTINUED'
                                                                           * E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION: The `options' argument passed to `waitid()' contains none of `WEXITED|WSTOPPED|WCONTINUED' */
#define E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH                       54  /* E_INVALID_ARGUMENT_BAD_VALUE: The `which' value passed to `waitid()' isn't one of `P_ALL,P_PID,P_PGID' */
#define E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS                      55  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `options' argument passed to `wait4()' isn't a set of `WNOHANG|WUNTRACED|WCONTINUED|WNOWAIT' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE                      56  /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to set a user-space address as the base of the `struct userkern' segment */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID                      57  /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write a value other than `0' to `struct userkern::ut_ppid' */
#define E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID                       58  /* E_INVALID_ARGUMENT_BAD_VALUE: Attempted to write an invalid value to `struct userkern::ut_sid' */
#define E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT                      59  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `prot' argument passed to `mprotect()' isn't a set of `PROT_EXEC|PROT_WRITE|PROT_READ' */
#define E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS                     60  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fchdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS                 61  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `rpc_schedule()' is malformed */
#define E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE                   62  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `iomode' passed to `kreaddirf()' could not be masked by `IO_USERF_MASK'. */
#define E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS                        63  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `pipe2()' cannot be masked by `O_CLOEXEC|O_CLOFORK|O_NONBLOCK|O_DIRECT' */
#define E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND                    64  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `cmd' passed to `ksysctl()' wasn't recognized */
#define E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT                      65  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `sysctl_driver_insmod::im_format', `sysctl_driver_delmod::dm_format' or `sysctl_driver_getmod::gm_format' wasn't one of `SYSCTL_DRIVER_FORMAT_*', or wasn't recognized as valid in the specific context */
#define E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS                       66  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_insmod::im_flags' cannot be masked by `KSYSCTL_DRIVER_INSMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS                       67  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `sysctl_driver_delmod::dm_flags' cannot be masked by `KSYSCTL_DRIVER_DELMOD_F*' */
#define E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS                    68  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `frenameat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS                   69  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fsymlinkat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS                     70  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmknodat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS                     71  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `fmkdirat()' isn't a set of `0|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND                     72  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCXONC)' isn't one of `TC(I|O)(ON|OFF)' */
#define E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND                     73  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `arg' passed to `ioctl(fd,TCFLSH)' isn't one of `TC(I|O|IO)FLUSH' */
#define E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE         74  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given `mode & EXCEPT_HANDLER_MODE_MASK' isn't one of `EXCEPT_HANDLER_MODE_*'
                                                                           * E_INVALID_ARGUMENT_UNKNOWN_FLAG:    The given `mode & ~EXCEPT_HANDLER_MODE_MASK' isn't a set of `EXCEPT_HANDLER_FLAG_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER                 75  /* E_INVALID_ARGUMENT_BAD_VALUE: One of the register values passed to sigreturn is invalid (`value' is the arch-specific register ID; e.g. `X86_REGISTER_SEGMENT_SS') */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO                        76  /* E_INVALID_ARGUMENT_BAD_VALUE: Bad signal number passed to `raise()', `kill()', `tgkill()', etc. */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO                       77  /* E_INVALID_ARGUMENT_BAD_VALUE: Bad trap number passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETRDKEY_BADMODE       78  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, KBDIO_SETRDKEY, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE    79  /* E_INVALID_ARGUMENT_BAD_VALUE: The specified keymap data block is too large */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT  80  /* E_INVALID_ARGUMENT_BAD_VALUE: The text contained within the keymap is corrupted/invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING 81  /* E_INVALID_ARGUMENT_BAD_VALUE: The specified default encoding is invalid */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSMODE_BADMODE   82  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid value passed as argument to `ioctl(fd, MOUSEIO_SETABSMODE, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSEIO_SETABSRECT_BADBOUNDS 83  /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t minx, miny, maxx, maxy] The bounds specified are invalid and cannot be used */
#define E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE     84  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid (or unsupported) value passed as argument to `ioctl(fd, KBDIO_SETDBGF12, ...)' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE                 85  /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t given_sigset_size] The sigset size passed to one of the RT signal system calls is incorrect */
#define E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS                86  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to sigaction() or rt_sigaction() isn't a set of `SA_*' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW                    87  /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: Invalid `how' passed to `sigprocmask()' (must be one of { SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK }) */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_PID                          88  /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_pid] Bad pid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_TID                          89  /* E_INVALID_ARGUMENT_BAD_VALUE: [pid_t given_tid] Bad tid value to one of the signal functions */
#define E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE              90  /* E_INVALID_ARGUMENT_BAD_VALUE: [int given_code] Attempted to raise a signal using `rt_sigqueueinfo()' or `rt_tgsigqueueinfo()' with a bad `si_code' */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS                        91  /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [syscall_ulong_t reserved] The `reserved' argument passed to `mktty()' is non-zero */
#define E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME                         92  /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t namelen, max_namelen] The `name' argument passed to `mktty()' is too long */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE                     93  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `type' argument passed to `faccessat()' isn't a set of `F_OK|R_OK|W_OK|X_OK' */
#define E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS                    94  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `faccessat()' isn't a set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE                    95  /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to read()/write() to/from an eventfd object using a buffer size less that 8 */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh    96  /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t value] Attempted to write 0xffffffffffffffff to an eventfd object */
#define E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS                      97  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_eventfd2()' is not masked by `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS                     98  /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags passed to `sys_signalfd4()' is not masked by `SFD_NONBLOCK | SFD_CLOEXEC' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_PIPE_BUFFER_SIZE               99  /* E_INVALID_ARGUMENT_BAD_VALUE: [size_t bufsize] Attempted to pass a too low value to `F_SETPIPE_SZ' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER                        100 /* E_INVALID_ARGUMENT_BAD_VALUE: [int intval] Attempted to write an invalid integer to a system configuration file */
#define E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON                       101 /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t reason] Bad reason code passed to `debugtrap()' */
#define E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY                    102 /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t perso] Bad personality code passed to `SYSCTL_SYSCALL_(GET|SET)_PERSONALITY'
                                                                           * E_INVALID_ARGUMENT_UNKNOWN_FLAG: The least significant argument-bit of `SYSCTL_SYSCALL_GET_PERSONALITY' was set (arg should be `kp << 1') */
#define E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP                          103 /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `lfutex()', `lfutexlock()', `lfutexexpr()' or `lfutexlockexpr()' is invalid.
                                                                           * E_INVALID_ARGUMENT_UNKNOWN_FLAG: When masked with `LFUTEX_FLAGMASK', `futex_op' contains bits not defined by `LFUTEX_WAIT_FLAG_*'
                                                                           * E_INVALID_ARGUMENT_RESERVED_FLAG: The `timeout' argument was non-NULL, but `futex_op & LFUTEX_FLAGMASK' contained non-zero `LFUTEX_WAIT_FLAG_TIMEOUT_*' flags.
                                                                           * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was false, but the `LFUTEX_WAIT_FLAG_TIMEOUT_*' bits were set.
                                                                           * E_INVALID_ARGUMENT_RESERVED_FLAG: `LFUTEX_USES_TIMEOUT(futex_op)' was true, but unused flag bits were set. */
#define E_INVALID_ARGUMENT_CONTEXT_IOPL_LEVEL                         104 /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t level] The `level' argument passed to `iopl()' was negative, or greater than `3' */
#define E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE                       105 /* E_INVALID_ARGUMENT_BAD_VALUE: [uintptr_t first_bad_port] At least one of the ports specified by the given range lies outside the valid port bounds */
#define E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON                      106 /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t turn_on] The `turn_on' argument is neither `0' nor `1' */
#define E_INVALID_ARGUMENT_CONTEXT_FUTEX_OP                           107 /* E_INVALID_ARGUMENT_BAD_VALUE: [syscall_ulong_t futex_op] The `futex_op' given to one of `futex()' is invalid. */
#define E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE                         108 /* E_INVALID_ARGUMENT_BAD_VALUE: [unsigned int mode = (KD_TEXT, KD_GRAPHICS)] Attempted to set an unsupported video mode. */
#define E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC                        109 /* E_INVALID_ARGUMENT_BAD_VALUE: [vd_codec_t codec] Attempted to set an unsupported video codec/resolution combination. */
#define E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0              110 /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: [uintptr_t index] The `hop_driver_string::ds_index' field was non-zero for a HOP that only accepts `0' as index. */
#define E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT                         111 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `getsockopt()'. */
#define E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT                         112 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The given level/optname pair was not recognized or isn't supported by `setsockopt()'. */
#define E_INVALID_ARGUMENT_CONTEXT_ACCEPT_NOT_LISTENING               113 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND                   114 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED             115 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED          116 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED                 117 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `send(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED                 118 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
#define E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED          119 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
#define E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND                 120 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
#define E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY          121 /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `bind()'). */
#define E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY       122 /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `connect()'). */
#define E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY        123 /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: A different address family was expected (in `sendto()'). */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY                  124 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `family' argument passed to `socket(2)' is unknown or unsupported. */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE                    125 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `socket(2)' is unknown or unsupported by the given `family'. */
#define E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL                126 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `protocol' argument passed to `socket(2)' is unknown or unsupported by the given `family' and `type'. */
#define E_INVALID_ARGUMENT_CONTEXT_ACCEPT4_SOCK_FLAGS                 127 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of socket flags passed to `sys_accept()' is not masked by `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS                     128 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_send()', `sys_sendto()', `sys_sendmsg()' or `sys_sendmmsg()' is not masked by `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
#define E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS                     129 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of message flags passed to `sys_recv()', `sys_recvfrom()', `sys_recvmsg()' or `sys_recvmmsg()' is not masked by `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
#define E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_HOW                       130 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `how' passed to `sys_shutdown()' isn't one of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_OPCODE                    131 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The kernel doesn't recognize, or doesn't support the given `struct uvio_response::ur_opcode' */
#define E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_RESPFLAGS                 132 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The set of flags given in `struct uvio_response::ur_respflags' isn't masked by `UVIO_RESPONSE_FLAG_NORMAL' */
#define E_INVALID_ARGUMENT_CONTEXT_USERVIOFD_FLAGS                    133 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `userviofd(2)' isn't a set of `O_NONBLOCK | O_CLOEXEC | O_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS        134 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
#define E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS              135 /* E_INVALID_ARGUMENT_BAD_STATE: Attempted to `write(2)' to a fifo without any connected readers. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS                   136 /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_open(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS                  137 /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_getfd(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS      138 /* E_INVALID_ARGUMENT_RESERVED_ARGUMENT: The `flags' argument passed to `pidfd_send_signal(2)' was non-zero. */
#define E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER              139 /* E_INVALID_ARGUMENT_BAD_STATE: The thread specified by `pid' in a call to `pidfd_open(2)' isn't a process leader. */
#define E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO                      140 /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND: In a call to `rt_sigqueueinfo(2)', `rt_tgsigqueueinfo(2)' or `pidfd_send_signal(2)',
                                                                           *                                        `uinfo' was given, but the pointed-to signal number didn't match the given `usigno' */
#define E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS                    141 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' isn't a set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME         142 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `flags' argument passed to `utimensat(2)' (with `filename' set to `NULL') isn't a set of `0 | AT_CHANGE_CTIME' */
#define E_INVALID_ARGUMENT_CONTEXT_UNSHARE_WHAT                       143 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The `what' argument passed to `unshare(2)' isn't a subset of:
                                                                           * `CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_CRED | CLONE_NEWNS | CLONE_SYSVSEM |
                                                                           *  CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET | CLONE_IO' */
#define E_INVALID_ARGUMENT_CONTEXT_KCMP_TYPE                          144 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `type' argument passed to `kcmp(2)' isn't one of `KCMP_*' from `<linux/kcmp.h>' */
#define E_INVALID_ARGUMENT_CONTEXT_DELETE_MODULE_FLAGS                145 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `delete_module(2)' cannot be masked by `O_TRUNC | O_NONBLOCK' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS                146 /* E_INVALID_ARGUMENT_UNKNOWN_FLAG: The flags passed to `epoll_create1(2)' cannot be masked by `EPOLL_CLOEXEC | EPOLL_CLOFORK' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP                       147 /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND: The `op' argument passed to `epoll_ctl(2)' isn't one of `EPOLL_CTL_*' from `<sys/epoll.h>' */
#define E_INVALID_ARGUMENT_CONTEXT_EPOLL_WAIT_ZERO_MAXEVENTS          148 /* E_INVALID_ARGUMENT_BAD_VALUE: The `maxevents' argument passed to `epoll_wait(2)' is `<= 0' */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_REASON_INVAL_H */
