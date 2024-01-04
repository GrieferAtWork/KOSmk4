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
#ifndef _KOS_EXCEPT_REASON_ILLOP_H
#define _KOS_EXCEPT_REASON_ILLOP_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Reason codes for `E_ILLEGAL_OPERATION' */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_ILLEGAL_OPERATION_CONTEXT_GENERIC,                               /* Generic context */
	E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK,                         /* E_ILLEGAL_IO_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
	E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS,      /* E_ILLEGAL_IO_OPERATION: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
	E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM,                               /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
	E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED,                    /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
	E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP,                    /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
	E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP,               /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING,           /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_LISTEN_NOT_BOUND,               /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED,         /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED,      /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED,             /* E_ILLEGAL_BECAUSE_NOT_READY: [EDESTADDRREQ] Attempted to `send(2)' on a socket without first calling `connect(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED,             /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED,      /* E_ILLEGAL_BECAUSE_NOT_READY: [EISCONN] Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND,             /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
	E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SO_PEERCRED_NOT_CONNECTED,      /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `getsockopt(SOL_SOCKET, SO_PEERCRED)' on a socket that isn't `connect(2)'-ed and wasn't returned by `accept(2)'. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU,                 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' from a background process group. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION,      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' on a tty that's not your controlling tty. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_DIFFERENT_SESSION,       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSPGRP' to assign a group from a different session. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION,      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGPGRP' on a tty that's not your controlling tty. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION,       /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGSID' on a tty that's not your controlling tty. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_NOT_SESSION_LEADER,      /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller isn't session leader. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_ALREADY_HAVE_CTTY,       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller already has a ctty. */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_CANNOT_STEAL_CTTY,       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but tty is already a ctty, and stealing isn't wanted (arg != 1) or permitted (!capable(CAP_SYS_ADMIN)). */
	E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION,      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCNOTTY' on a tty that's not your controlling tty. */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED,             /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK,           /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED,           /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE, /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED,      /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
	E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED,        /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
	E_ILLEGAL_OPERATION_CONTEXT_SETPGID_DIFFERENT_SESSION,             /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to set the progress group of a process apart of a different session */
	E_ILLEGAL_OPERATION_CONTEXT_SETPGID_IS_SESSION_LEADER,             /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] `pid' refers to a process that is a session leader */
	E_ILLEGAL_OPERATION_CONTEXT_SETSID_ALREADY_GROUP_LEADER,           /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] The process calling `setsid(2)' is already a process group leader */
	E_ILLEGAL_OPERATION_CONTEXT_PROC_COMM_DIFFERENT_PROCESS,           /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `comm' of a thread in a different process. */
	E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS,            /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `/proc/[pid]/kos/peb-addr' or `/proc/[pid]/kos/peb-compat' of a thread in a different mman (CLONE_VM). */
	E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED,           /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_MEMORY_MAX' byte locations. */
	E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_FUTEX_COUNT_EXCEEDED,      /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_FUTEX_MAX' futex objects locations. */
	E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW,            /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] Attempted to push stack value with full stack */
	E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW,           /* E_INVALID_OPERATION: [EINVAL] Attempted to pop stack value with empty stack */
	E_ILLEGAL_OPERATION_CONTEXT_BLKRRPART_NOT_DRIVE_ROOT,              /* E_INVALID_OPERATION: [EINVAL] Attempted to use `BLKRRPART' on a block device partition */
	E_ILLEGAL_OPERATION_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE,           /* E_INVALID_OPERATION: [EINVAL] In `mremap(2)': `old_size' was `0', but the mapping pointed-to by `old_address' isn't `PROT_SHARED'. */
	E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED,                       /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Tried to use `PIDFD_IOC_EXITCODE', but the thread hasn't exited, yet. */
	E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET,                      /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] `SVGA_IOC_GETMODE' used on a video lock when no mode has been set. */
	E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MOD_RPC,                         /* E_INVALID_OPERATION: [EINVAL] Attempted to `EPOLL_CTL_MOD' an RPC monitor, which isn't allowed. */
	E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE,               /* E_INVALID_OPERATION: [EINVAL] Attempted to access a mem-part beyond the end of its associated file. */
	E_ILLEGAL_OPERATION_CONTEXT_SETPGID_NO_SUCH_GROUP,                 /* E_ILLEGAL_OPERATION: [EPERM] `pgid' doesn't indicate creation of a new process group, and no group with the given ID exists in the calling session. */
	E_ILLEGAL_OPERATION_CONTEXT_SENDFILE_NO_FILE_POSITION,             /* E_INVALID_OPERATION: [EINVAL] Tried to use `sendfile(2)' with `pin_offset == NULL', and `infd' doesn't have a writable file position attribute. */
	E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS,                   /* E_ILLEGAL_OPERATION: [EPERM] Attempted to change one of `_MFILE_F_ROFLAGSMASK' of a file marked as `MFILE_F_ROFLAGS' */
	E_ILLEGAL_OPERATION_CONTEXT_MSALIGN_NO_RAW_IO,                     /* E_ILLEGAL_OPERATION: [EPERM] Attempted to use `FILE_IOC_MSALIGN' on a file that doesn't support "Raw I/O" */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_ILLEGAL_OPERATION_CONTEXT_GENERIC                               E_ILLEGAL_OPERATION_CONTEXT_GENERIC                               /* Generic context */
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK                         E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK                         /* E_ILLEGAL_IO_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS      E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS      /* E_ILLEGAL_IO_OPERATION: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
#define E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                               E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                               /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
#define E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED                    E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED                    /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP                    E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP                    /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP               E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP               /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING           E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING           /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_LISTEN_NOT_BOUND               E_ILLEGAL_OPERATION_CONTEXT_SOCKET_LISTEN_NOT_BOUND               /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED         E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED         /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED      /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED             E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED             /* E_ILLEGAL_BECAUSE_NOT_READY: [EDESTADDRREQ] Attempted to `send(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED             E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED             /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED      /* E_ILLEGAL_BECAUSE_NOT_READY: [EISCONN] Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND             E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND             /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SO_PEERCRED_NOT_CONNECTED      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SO_PEERCRED_NOT_CONNECTED      /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `getsockopt(SOL_SOCKET, SO_PEERCRED)' on a socket that isn't `connect(2)'-ed and wasn't returned by `accept(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU                 E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU                 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' from a background process group. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION      E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_DIFFERENT_SESSION       E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_DIFFERENT_SESSION       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSPGRP' to assign a group from a different session. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION      E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGPGRP' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION       E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION       /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGSID' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_NOT_SESSION_LEADER      E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_NOT_SESSION_LEADER      /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller isn't session leader. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_ALREADY_HAVE_CTTY       E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_ALREADY_HAVE_CTTY       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller already has a ctty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_CANNOT_STEAL_CTTY       E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_CANNOT_STEAL_CTTY       /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but tty is already a ctty, and stealing isn't wanted (arg != 1) or permitted (!capable(CAP_SYS_ADMIN)). */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION      E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION      /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCNOTTY' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_DIFFERENT_SESSION             E_ILLEGAL_OPERATION_CONTEXT_SETPGID_DIFFERENT_SESSION             /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to set the progress group of a process apart of a different session */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_IS_SESSION_LEADER             E_ILLEGAL_OPERATION_CONTEXT_SETPGID_IS_SESSION_LEADER             /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] `pid' refers to a process that is a session leader */
#define E_ILLEGAL_OPERATION_CONTEXT_SETSID_ALREADY_GROUP_LEADER           E_ILLEGAL_OPERATION_CONTEXT_SETSID_ALREADY_GROUP_LEADER           /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] The process calling `setsid(2)' is already a process group leader */
#define E_ILLEGAL_OPERATION_CONTEXT_PROC_COMM_DIFFERENT_PROCESS           E_ILLEGAL_OPERATION_CONTEXT_PROC_COMM_DIFFERENT_PROCESS           /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `comm' of a thread in a different process. */
#define E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS            E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS            /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `/proc/[pid]/kos/peb-addr' or `/proc/[pid]/kos/peb-compat' of a thread in a different mman (CLONE_VM). */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED           E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED           /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_MEMORY_MAX' byte locations. */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_FUTEX_COUNT_EXCEEDED      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_FUTEX_COUNT_EXCEEDED      /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_FUTEX_MAX' futex objects locations. */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW            E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW            /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] Attempted to push stack value with full stack */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW           E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW           /* E_INVALID_OPERATION: [EINVAL] Attempted to pop stack value with empty stack */
#define E_ILLEGAL_OPERATION_CONTEXT_BLKRRPART_NOT_DRIVE_ROOT              E_ILLEGAL_OPERATION_CONTEXT_BLKRRPART_NOT_DRIVE_ROOT              /* E_INVALID_OPERATION: [EINVAL] Attempted to use `BLKRRPART' on a block device partition */
#define E_ILLEGAL_OPERATION_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE           E_ILLEGAL_OPERATION_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE           /* E_INVALID_OPERATION: [EINVAL] In `mremap(2)': `old_size' was `0', but the mapping pointed-to by `old_address' isn't `PROT_SHARED'. */
#define E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED                       E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED                       /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Tried to use `PIDFD_IOC_EXITCODE', but the thread hasn't exited, yet. */
#define E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET                      E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET                      /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] `SVGA_IOC_GETMODE' used on a video lock when no mode has been set. */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MOD_RPC                         E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MOD_RPC                         /* E_INVALID_OPERATION: [EINVAL] Attempted to `EPOLL_CTL_MOD' an RPC monitor, which isn't allowed. */
#define E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE               E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE               /* E_INVALID_OPERATION: [EINVAL] Attempted to access a mem-part beyond the end of its associated file. */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_NO_SUCH_GROUP                 E_ILLEGAL_OPERATION_CONTEXT_SETPGID_NO_SUCH_GROUP                 /* E_ILLEGAL_OPERATION: [EPERM] `pgid' doesn't indicate creation of a new process group, and no group with the given ID exists in the calling session. */
#define E_ILLEGAL_OPERATION_CONTEXT_SENDFILE_NO_FILE_POSITION             E_ILLEGAL_OPERATION_CONTEXT_SENDFILE_NO_FILE_POSITION             /* E_INVALID_OPERATION: [EINVAL] Tried to use `sendfile(2)' with `pin_offset == NULL', and `infd' doesn't have a writable file position attribute. */
#define E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS                   E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS                   /* E_ILLEGAL_OPERATION: [EPERM] Attempted to change one of `_MFILE_F_ROFLAGSMASK' of a file marked as `MFILE_F_ROFLAGS' */
#define E_ILLEGAL_OPERATION_CONTEXT_MSALIGN_NO_RAW_IO                     E_ILLEGAL_OPERATION_CONTEXT_MSALIGN_NO_RAW_IO                     /* E_ILLEGAL_OPERATION: [EPERM] Attempted to use `FILE_IOC_MSALIGN' on a file that doesn't support "Raw I/O" */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_ILLEGAL_OPERATION_CONTEXT_GENERIC                               0  /* Generic context */
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK                         1  /* E_ILLEGAL_IO_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS      2  /* E_ILLEGAL_IO_OPERATION: Attempted to `open(O_WRONLY | O_NONBLOCK)' a fifo without any readers already connected. */
#define E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                               3  /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
#define E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED                    4  /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP                    5  /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP               6  /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING           7  /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `accept(2)' on a socket without first calling `listen(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_LISTEN_NOT_BOUND               8  /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `listen(2)' on a socket without first calling `bind(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED         9  /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `shutdown(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED      10 /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `getpeername(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED             11 /* E_ILLEGAL_BECAUSE_NOT_READY: [EDESTADDRREQ] Attempted to `send(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED             12 /* E_ILLEGAL_BECAUSE_NOT_READY: [ENOTCONN] Attempted to `recv(2)' on a socket without first calling `connect(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED      13 /* E_ILLEGAL_BECAUSE_NOT_READY: [EISCONN] Attempted to `connect(2)' or `sendto(2)' on a socket that had already been `connect(2)'ed before. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND             14 /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `bind(2)' or `recvfrom(2)' on a socket that had already been `bind(2)'ed before. */
#define E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SO_PEERCRED_NOT_CONNECTED      15 /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Attempted to `getsockopt(SOL_SOCKET, SO_PEERCRED)' on a socket that isn't `connect(2)'-ed and wasn't returned by `accept(2)'. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_SIGTTOU                 16 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' from a background process group. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_NOT_CALLER_SESSION      17 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCSPGRP' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSPGRP_DIFFERENT_SESSION       18 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSPGRP' to assign a group from a different session. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGPGRP_NOT_CALLER_SESSION      19 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGPGRP' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCGSID_NOT_CALLER_SESSION       20 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCGSID' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_NOT_SESSION_LEADER      21 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller isn't session leader. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_ALREADY_HAVE_CTTY       22 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but caller already has a ctty. */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCSCTTY_CANNOT_STEAL_CTTY       23 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to use `TIOCSCTTY', but tty is already a ctty, and stealing isn't wanted (arg != 1) or permitted (!capable(CAP_SYS_ADMIN)). */
#define E_ILLEGAL_OPERATION_CONTEXT_TTY_TIOCNOTTY_NOT_CALLER_SESSION      24 /* E_ILLEGAL_BECAUSE_GROUPING: [ENOTTY] Tried to use `TIOCNOTTY' on a tty that's not your controlling tty. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             25 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           26 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           27 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE 28 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      29 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
#define E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        30 /* E_ILLEGAL_OPERATION: [EPERM] Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_DIFFERENT_SESSION             31 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to set the progress group of a process apart of a different session */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_IS_SESSION_LEADER             32 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] `pid' refers to a process that is a session leader */
#define E_ILLEGAL_OPERATION_CONTEXT_SETSID_ALREADY_GROUP_LEADER           33 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] The process calling `setsid(2)' is already a process group leader */
#define E_ILLEGAL_OPERATION_CONTEXT_PROC_COMM_DIFFERENT_PROCESS           34 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `comm' of a thread in a different process. */
#define E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS            35 /* E_ILLEGAL_BECAUSE_GROUPING: [EPERM] Tried to change the `/proc/[pid]/kos/peb-addr' or `/proc/[pid]/kos/peb-compat' of a thread in a different mman (CLONE_VM). */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED           36 /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_MEMORY_MAX' byte locations. */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_FUTEX_COUNT_EXCEEDED      37 /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] RPC program tried to access more than `RPC_PROG_FUTEX_MAX' futex objects locations. */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW            38 /* E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED: [ENOMEM] Attempted to push stack value with full stack */
#define E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW           39 /* E_INVALID_OPERATION: [EINVAL] Attempted to pop stack value with empty stack */
#define E_ILLEGAL_OPERATION_CONTEXT_BLKRRPART_NOT_DRIVE_ROOT              40 /* E_INVALID_OPERATION: [EINVAL] Attempted to use `BLKRRPART' on a block device partition */
#define E_ILLEGAL_OPERATION_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE           41 /* E_INVALID_OPERATION: [EINVAL] In `mremap(2)': `old_size' was `0', but the mapping pointed-to by `old_address' isn't `PROT_SHARED'. */
#define E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED                       42 /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] Tried to use `PIDFD_IOC_EXITCODE', but the thread hasn't exited, yet. */
#define E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET                      43 /* E_ILLEGAL_BECAUSE_NOT_READY: [EINVAL] `SVGA_IOC_GETMODE' used on a video lock when no mode has been set. */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MOD_RPC                         44 /* E_INVALID_OPERATION: [EINVAL] Attempted to `EPOLL_CTL_MOD' an RPC monitor, which isn't allowed. */
#define E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE               45 /* E_INVALID_OPERATION: [EINVAL] Attempted to access a mem-part beyond the end of its associated file. */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_NO_SUCH_GROUP                 46 /* E_ILLEGAL_OPERATION: [EPERM] `pgid' doesn't indicate creation of a new process group, and no group with the given ID exists in the calling session. */
#define E_ILLEGAL_OPERATION_CONTEXT_SENDFILE_NO_FILE_POSITION             47 /* E_INVALID_OPERATION: [EINVAL] Tried to use `sendfile(2)' with `pin_offset == NULL', and `infd' doesn't have a writable file position attribute. */
#define E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS                   48 /* E_ILLEGAL_OPERATION: [EPERM] Attempted to change one of `_MFILE_F_ROFLAGSMASK' of a file marked as `MFILE_F_ROFLAGS' */
#define E_ILLEGAL_OPERATION_CONTEXT_MSALIGN_NO_RAW_IO                     49 /* E_ILLEGAL_OPERATION: [EPERM] Attempted to use `FILE_IOC_MSALIGN' on a file that doesn't support "Raw I/O" */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_REASON_ILLOP_H */
