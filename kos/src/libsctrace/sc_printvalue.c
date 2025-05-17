/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C
#define GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1
#define _DOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _FILE_OFFSET_BITS 32 /* We also need the 32-bit file structures */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__va_size.h>
#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/typecore.h>

#include <arpa/inet.h>
#include <asm/ioctl.h>
#include <bits/os/itimerspec.h>
#include <bits/os/itimerval.h>
#include <bits/os/termios.h>
#include <bits/os/termiox.h>
#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <kos/anno.h>
#include <kos/except-handler.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/io.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <linux/close_range.h>
#include <linux/fd.h>
#include <linux/fs.h>
#include <linux/futex.h>
#include <linux/hdreg.h>
#include <linux/kd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/mkdev.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/termiox.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/wait.h>

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <format-printer.h>
#include <inttypes.h>
#include <sched.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <libsctrace/sctrace.h>

#include "sctrace.h"

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/iovec.h>
#include <compat/bits/os/itimerspec.h>
#include <compat/bits/os/itimerval.h>
#include <compat/bits/os/sigaction.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifdef HAVE_SC_REPR_ARCH_PRCTL_COMMAND
#include <asm/prctl.h>
#endif /* HAVE_SC_REPR_ARCH_PRCTL_COMMAND */

#ifdef __KERNEL__
#include <kernel/fs/blkdev.h>
#include <kernel/fs/chrdev.h>
#include <kernel/user.h>
#elif defined(__CHECKER__)
#define validate_readable(base, num_bytes)                          __builtin_remove_noderef(base)
#define validate_readablem(base, num_items, item_size_in_bytes)     __builtin_remove_noderef(base)
#define validate_readable_opt(base, num_bytes)                      __builtin_remove_noderef(base)
#define validate_readablem_opt(base, num_items, item_size_in_bytes) __builtin_remove_noderef(base)
#else /* ... */
#define validate_readable(base, num_bytes)                          (void)0
#define validate_readablem(base, num_items, item_size_in_bytes)     (void)0
#define validate_readable_opt(base, num_bytes)                      (void)0
#define validate_readablem_opt(base, num_items, item_size_in_bytes) (void)0
#endif /* !... */


/* Representation limits before printed data is truncated */
#define LIMIT_STRLEN       128 /* Max # of bytes to print from user-supplied strings. */
#define LIMIT_POLLFDS      16  /* Max # of `struct pollfd' structures to print from a vector. */
#define LIMIT_IOVEC        16  /* Max # of `struct iovec' structures to print from a vector. */
#define LIMIT_NFDS         16  /* Max # of fds to print from a `fd_set'. */
#define LIMIT_STRINGVECTOR 32  /* Max # of strings to print from a string-vector (such as `argv' and `envp' in `sys_execve()'). */


/* Figure out what we actually need to define. */
#ifdef HAVE_SC_REPR_DEV_T
#define NEED_print_dev
#endif /* HAVE_SC_REPR_DEV_T */

#ifdef HAVE_SC_REPR_DEV_BLK
#define NEED_print_dev
#endif /* HAVE_SC_REPR_DEV_BLK */

#ifdef HAVE_SC_REPR_DEV_CHR
#define NEED_print_dev
#endif /* HAVE_SC_REPR_DEV_CHR */

#ifdef HAVE_SC_REPR_MODE_T
#define NEED_print_mode_t
#endif /* HAVE_SC_REPR_MODE_T */

#ifdef HAVE_SC_REPR_OFLAG_T
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG_T */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT */

#ifdef HAVE_SC_REPR_ATFLAG_T
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG_T */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH */

#ifdef HAVE_SC_REPR_IOMODE_T
#define NEED_print_iomode_t
#endif /* HAVE_SC_REPR_IOMODE_T */

#ifdef HAVE_SC_REPR_FD_T
#define NEED_print_fd_t
#endif /* HAVE_SC_REPR_FD_T */

#ifdef HAVE_SC_REPR_CLOCKID_T
#define NEED_print_clockid_t
#endif /* HAVE_SC_REPR_CLOCKID_T */

#ifdef HAVE_SC_REPR_FILENAME
#define NEED_print_string
#endif /* HAVE_SC_REPR_FILENAME */

#ifdef HAVE_SC_REPR_BUFFER
#define NEED_print_string_or_buffer
#endif /* HAVE_SC_REPR_BUFFER */

#ifdef HAVE_SC_REPR_STRING
#define NEED_print_string
#endif /* HAVE_SC_REPR_STRING */

#ifdef HAVE_SC_REPR_SIGHANDLER_T
#define NEED_print_sighandler_t
#endif /* HAVE_SC_REPR_SIGHANDLER_T */

#ifdef HAVE_SC_REPR_STRUCT_POLLFD
#define NEED_print_pollfds
#endif /* HAVE_SC_REPR_STRUCT_POLLFD */

#ifdef HAVE_SC_REPR_IOCTL_COMMAND
#define NEED_print_ioctl_command
#endif /* HAVE_SC_REPR_IOCTL_COMMAND */

#ifdef HAVE_SC_REPR_IOCTL_ARG
#define NEED_print_ioctl_arg
#endif /* HAVE_SC_REPR_IOCTL_ARG */

#ifdef HAVE_SC_REPR_STRING_VECTOR
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR */

#ifdef HAVE_SC_REPR_STRING_VECTOR32
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR32 */

#ifdef HAVE_SC_REPR_STRING_VECTOR64
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 */

#ifdef HAVE_SC_REPR_SIGNO_T
#define NEED_print_signo_t
#endif /* HAVE_SC_REPR_SIGNO_T */

#ifdef HAVE_SC_REPR_SOCKET_DOMAIN
#define NEED_print_socket_domain
#endif /* HAVE_SC_REPR_SOCKET_DOMAIN */

#ifdef HAVE_SC_REPR_SOCKET_PROTOCOL
#define NEED_print_socket_proto
#endif /* HAVE_SC_REPR_SOCKET_PROTOCOL */

#ifdef HAVE_SC_REPR_ACCEPT4_FLAGS
#define NEED_print_socket_type_flags
#endif /* HAVE_SC_REPR_ACCEPT4_FLAGS */

#ifdef HAVE_SC_REPR_SOCKET_TYPE
#define NEED_print_socket_type
#endif /* HAVE_SC_REPR_SOCKET_TYPE */

#ifdef HAVE_SC_REPR_STRUCT_SOCKADDR
#define NEED_print_sockaddr
#endif /* HAVE_SC_REPR_STRUCT_SOCKADDR */

#if defined(HAVE_SC_REPR_FCNTL64_COMMAND) || defined(HAVE_SC_REPR_FCNTL_COMMAND)
#define NEED_print_fcntl_command
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND || HAVE_SC_REPR_FCNTL_COMMAND */

#if defined(HAVE_SC_REPR_FCNTL64_ARG) || defined(HAVE_SC_REPR_FCNTL_ARG)
#define NEED_print_fcntl_arg
#endif /* HAVE_SC_REPR_FCNTL64_ARG || HAVE_SC_REPR_FCNTL_ARG */

#ifdef HAVE_SC_REPR_SEEK_WHENCE
#define NEED_print_seek_whence
#endif /* HAVE_SC_REPR_SEEK_WHENCE */

#if defined(HAVE_SC_REPR_STRUCT_IOVEC) || defined(HAVE_SC_REPR_STRUCT_IOVEC_C)
#if __SIZEOF_IOVEC == 8
#define iovecx32 iovec
#define NEED_print_iovecx32
#elif __SIZEOF_IOVEC == 16
#define iovecx64 iovec
#define NEED_print_iovecx64
#else /* __SIZEOF_IOVEC == ... */
#error "Unsupported `__SIZEOF_IOVEC'"
#endif /* __SIZEOF_IOVEC != ... */
#endif /* HAVE_SC_REPR_STRUCT_IOVEC || HAVE_SC_REPR_STRUCT_IOVEC_C */

#if defined(HAVE_SC_REPR_STRUCT_IOVECX32) || defined(HAVE_SC_REPR_STRUCT_IOVECX32_C)
#define NEED_print_iovecx32
#endif /* HAVE_SC_REPR_STRUCT_IOVECX32 || HAVE_SC_REPR_STRUCT_IOVECX32_C */

#if defined(HAVE_SC_REPR_STRUCT_IOVECX64) || defined(HAVE_SC_REPR_STRUCT_IOVECX64_C)
#define NEED_print_iovecx64
#endif /* HAVE_SC_REPR_STRUCT_IOVECX64 || HAVE_SC_REPR_STRUCT_IOVECX64_C */

#ifdef HAVE_SC_REPR_STRUCT_FDSET
#define NEED_print_fdset
#endif /* HAVE_SC_REPR_STRUCT_FDSET */

#if (defined(HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS) ||  \
     defined(HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS) ||  \
     defined(HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2) || \
     defined(HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS3))
#define NEED_print_msg_flags
#endif /* ... */

#ifdef HAVE_SC_REPR_SOCKOPT_LEVEL
#define NEED_print_sockopt_level
#endif /* HAVE_SC_REPR_SOCKOPT_LEVEL */

#ifdef HAVE_SC_REPR_SOCKOPT_OPTNAME
#define NEED_print_sockopt_optname
#endif /* HAVE_SC_REPR_SOCKOPT_OPTNAME */

#ifdef HAVE_SC_REPR_STRUCT_SIGSET
#define NEED_print_sigset
#endif /* HAVE_SC_REPR_STRUCT_SIGSET */

#if (defined(HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE) ||     \
     defined(HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32) || \
     defined(HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64))
#define NEED_print_sigmask_sigset_and_len
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE */

#ifdef HAVE_SC_REPR_MMAP_PROT
#define NEED_print_mmap_prot
#endif /* HAVE_SC_REPR_MMAP_PROT */

#ifdef HAVE_SC_REPR_MMAP_FLAGS
#define NEED_print_mmap_flags
#endif /* HAVE_SC_REPR_MMAP_FLAGS */

#ifdef HAVE_SC_REPR_KREADDIR_MODE
#define NEED_print_kreaddir_mode
#endif /* HAVE_SC_REPR_KREADDIR_MODE */

#ifdef HAVE_SC_REPR_STRUCT_SIGACTION
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_SIGACTION */

#ifdef HAVE_SC_REPR_STRUCT_SIGACTIONX32
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX32 */

#ifdef HAVE_SC_REPR_STRUCT_SIGACTIONX64
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX64 */

#ifdef HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION */

#ifdef HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32 */

#ifdef HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64 */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTION
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTION */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX32
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX32 */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX64
#define NEED_print_sigaction
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX64 */

#ifdef HAVE_SC_REPR_EPOLL_CREATE1_FLAGS
#define NEED_print_epoll_create1_flags
#endif /* HAVE_SC_REPR_EPOLL_CREATE1_FLAGS */

#ifdef HAVE_SC_REPR_EPOLL_OP
#define NEED_print_epoll_ctl
#endif /* HAVE_SC_REPR_EPOLL_OP */

#ifdef HAVE_SC_REPR_STRUCT_EPOLL_EVENT
#define NEED_print_epoll_event
#endif /* HAVE_SC_REPR_STRUCT_EPOLL_EVENT */

#ifdef HAVE_SC_REPR_MREMAP_FLAGS
#define NEED_print_mremap_flags
#endif /* HAVE_SC_REPR_MREMAP_FLAGS */

#ifdef HAVE_SC_REPR_ARCH_PRCTL_COMMAND
#define NEED_print_arch_prctl_command
#endif /* HAVE_SC_REPR_ARCH_PRCTL_COMMAND */

#ifdef HAVE_SC_REPR_PRCTL_COMMAND
#define NEED_print_prctl_command
#endif /* HAVE_SC_REPR_PRCTL_COMMAND */

#ifdef HAVE_SC_REPR_STRUCT_CLONE_ARGS
#define NEED_print_clone_args
#endif /* HAVE_SC_REPR_STRUCT_CLONE_ARGS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS
#define NEED_print_clone_flags
#endif /* HAVE_SC_REPR_CLONE_FLAGS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS_SETNS
#define NEED_print_clone_flags
#endif /* HAVE_SC_REPR_CLONE_FLAGS_SETNS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS_UNSHARE
#define NEED_print_clone_flags
#endif /* HAVE_SC_REPR_CLONE_FLAGS_UNSHARE */

#ifdef HAVE_SC_REPR_WAITFLAGS
#define NEED_print_waitflags
#endif /* HAVE_SC_REPR_WAITFLAGS */

#ifdef HAVE_SC_REPR_IDTYPE_T
#define NEED_print_idtype_t
#endif /* HAVE_SC_REPR_IDTYPE_T */

#ifdef HAVE_SC_REPR_SIGNALFD4_FLAGS
#define NEED_print_signalfd_flags
#endif /* HAVE_SC_REPR_SIGNALFD4_FLAGS */

#ifdef HAVE_SC_REPR_EVENTFD2_FLAGS
#define NEED_print_eventfd_flags
#endif /* HAVE_SC_REPR_EVENTFD2_FLAGS */

#ifdef HAVE_SC_REPR_EXIT_STATUS
#define NEED_print_exit_status
#endif /* HAVE_SC_REPR_EXIT_STATUS */

#ifdef HAVE_SC_REPR_EXCEPTION_HANDLER_MODE
#define NEED_print_exception_handler_mode
#endif /* HAVE_SC_REPR_EXCEPTION_HANDLER_MODE */

#ifdef HAVE_SC_REPR_KCMP_TYPE
#define NEED_print_kcmp_type
#endif /* HAVE_SC_REPR_KCMP_TYPE */

#ifdef HAVE_SC_REPR_ACCESS_TYPE
#define NEED_print_access_type
#endif /* HAVE_SC_REPR_ACCESS_TYPE */

#ifdef HAVE_SC_REPR_CLOSE_RANGE_FLAGS
#define NEED_print_close_range_flags
#endif /* HAVE_SC_REPR_CLOSE_RANGE_FLAGS */

#ifdef HAVE_SC_REPR_SIGMASK32
#define NEED_print_sigset
#endif /* HAVE_SC_REPR_SIGMASK32 */






/* Inter-printer dependencies */
#ifdef NEED_print_sigaction
#define NEED_print_sighandler_t
#define NEED_print_sigset
#define NEED_print_sigaction_flags
#endif /* NEED_print_sigaction */

#ifdef NEED_print_epoll_event
#define NEED_print_epoll_what
#endif /* NEED_print_epoll_event */

#ifdef NEED_print_epoll_create1_flags
#define NEED_print_flagset32
#endif /* NEED_print_epoll_create1_flags */

#ifdef NEED_print_socket_type_flags
#define NEED_print_flagset32
#endif /* NEED_print_socket_type_flags */

#ifdef NEED_print_mremap_flags
#define NEED_print_flagset32
#endif /* NEED_print_mremap_flags */

#ifdef NEED_print_pollfds
#define NEED_print_pollfd
#define NEED_print_segfault
#endif /* NEED_print_pollfds */

#ifdef NEED_print_pollfd
#define NEED_print_fd_t
#define NEED_print_poll_what
#endif /* NEED_print_pollfd */

#ifdef NEED_print_poll_what
#define NEED_print_flagset16
#endif /* NEED_print_poll_what */

#ifdef NEED_print_string_vector
#define NEED_print_string
#define NEED_print_segfault
#endif /* NEED_print_string_vector */

#ifdef NEED_print_timespec_vector
#define NEED_print_timespec
#endif /* NEED_print_timespec_vector */

#ifdef NEED_print_timeval_vector
#define NEED_print_timeval
#endif /* NEED_print_timeval_vector */

#ifdef NEED_print_sockaddr
#define NEED_print_bytes
#define NEED_print_socket_domain
#endif /* NEED_print_sockaddr */

#ifdef NEED_print_socket_domain
#define NEED_print_socket_af_pf
#endif /* NEED_print_socket_domain */

#ifdef NEED_print_socket_proto
#define NEED_print_socket_af_pf
#endif /* NEED_print_socket_proto */

#ifdef NEED_print_fcntl_arg
#define NEED_print_oflag_t
#define NEED_print_fd_flags
#define NEED_print_dn_flags
#define NEED_print_signo_t
#define NEED_print_fd_t
#define NEED_print_f_owner_ex
#define NEED_print_f_lock
#define NEED_print_flock64
#endif /* NEED_print_fcntl_arg */

#ifdef NEED_print_f_owner_ex
#define NEED_print_f_owner_type
#endif /* NEED_print_f_owner_ex */

#ifdef NEED_print_flock64
#define NEED_print_f_lock
#define NEED_print_seek_whence
#endif /* NEED_print_flock64 */

#ifdef NEED_print_iovecx32
#define NEED_print_iovec_entry
#endif /* NEED_print_iovecx32 */

#ifdef NEED_print_iovecx64
#define NEED_print_iovec_entry
#endif /* NEED_print_iovecx64 */

#if defined(NEED_print_iovecx32) || defined(NEED_print_iovecx64)
#define NEED_print_segfault
#endif /* NEED_print_iovecx32 || NEED_print_iovecx64 */

#ifdef NEED_print_iovec_entry
#define NEED_print_string_or_buffer
#endif /* NEED_print_iovec_entry */

#ifdef NEED_print_string_or_buffer
#define NEED_print_string
#define NEED_print_bytes
#endif /* NEED_print_string_or_buffer */

#ifdef NEED_print_fdset
#define NEED_print_fd_t
#define NEED_print_segfault
#endif /* NEED_print_fdset */

#ifdef NEED_print_sigmask_sigset_and_len
#define NEED_print_sigset
#endif /* NEED_print_sigmask_sigset_and_len */

#ifdef NEED_print_sigset
#define NEED_print_signo_t
#define NEED_print_segfault
#endif /* NEED_print_sigset */

#ifdef NEED_print_socket_type
#define NEED_print_socket_type_flags
#endif /* NEED_print_socket_type */

#ifdef NEED_print_clone_args
#define NEED_print_clone_flags_ex
#define NEED_print_signo_t
#define NEED_print_fd_t
#endif /* NEED_print_clone_args */

#ifdef NEED_print_clone_flags_ex
#define NEED_print_clone_flags
#endif /* NEED_print_clone_flags_ex */

#ifdef NEED_print_clone_flags
#ifdef NEED_print_clone_args
#define NEED_print_flagset64
#endif /* NEED_print_clone_args */
#define NEED_print_signo_t
#endif /* NEED_print_clone_flags */

#ifdef NEED_print_waitflags
#define NEED_print_flagset32
#endif /* NEED_print_waitflags */

#ifdef NEED_print_access_type
#define NEED_print_flagset8
#endif /* NEED_print_access_type */

#ifdef NEED_print_fd_flags
#define NEED_print_flagset8
#endif /* NEED_print_fd_flags */

#ifdef NEED_print_dn_flags
#define NEED_print_flagset32
#endif /* NEED_print_dn_flags */

#ifdef NEED_print_f_lock
#define NEED_print_flagset8
#endif /* NEED_print_f_lock */

#ifdef NEED_print_sigaction_flags
#define NEED_print_flagset32
#endif /* NEED_print_sigaction_flags */

#ifdef NEED_print_close_range_flags
#define NEED_print_flagset8
#endif /* NEED_print_close_range_flags */

#if defined(NEED_print_flagset8) || defined(NEED_print_flagset16) || defined(NEED_print_flagset32)
#define NEED_print_flagset_remainder
#endif /* NEED_print_flagset8 || NEED_print_flagset16 || NEED_print_flagset32 */

#ifdef NEED_print_ioctl_arg
#define NEED_print_termio
#define NEED_print_termios
#define NEED_print_termios2
#define NEED_print_termiox
#define NEED_print_winsize
#define NEED_print_tty_modem_bits
#define NEED_print_tcflow_arg
#define NEED_print_tcflush_arg
#endif /* NEED_print_ioctl_arg */

#if defined(NEED_print_termio) || defined(NEED_print_termios) || defined(NEED_print_termios2)
#define NEED_print_termio_common
#endif /* NEED_print_termio || NEED_print_termios || NEED_print_termios2 */

#ifdef NEED_print_termio_common
#define NEED_print_termios_iflag
#define NEED_print_termios_oflag
#define NEED_print_termios_lflag
#define NEED_print_termios_cflag
#endif /* NEED_print_termio_common */




/* Configure special printer extensions */
#undef HAVE_STRING_VECTOR_POINTER_SIZE
#if ((defined(HAVE_SC_REPR_STRING_VECTOR32) && defined(HAVE_SC_REPR_STRING_VECTOR64)) ||                            \
     (defined(HAVE_SC_REPR_STRING_VECTOR) && (defined(HAVE_SC_REPR_STRING_VECTOR32) && __SIZEOF_POINTER__ != 4)) || \
     (defined(HAVE_SC_REPR_STRING_VECTOR) && (defined(HAVE_SC_REPR_STRING_VECTOR64) && __SIZEOF_POINTER__ != 8)))
#define HAVE_STRING_VECTOR_POINTER_SIZE 1
#endif /* ... */

DECL_BEGIN

#if !defined(POLLRDNORM) && defined(__POLLRDNORM)
#define POLLRDNORM __POLLRDNORM /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* !POLLRDNORM && __POLLRDNORM */
#if !defined(POLLRDBAND) && defined(__POLLRDBAND)
#define POLLRDBAND __POLLRDBAND /* Priority data may be read. */
#endif /* !POLLRDBAND && __POLLRDBAND */
#if !defined(POLLWRNORM) && defined(__POLLWRNORM)
#define POLLWRNORM __POLLWRNORM /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* !POLLWRNORM && __POLLWRNORM */
#if !defined(POLLWRBAND) && defined(__POLLWRBAND)
#define POLLWRBAND __POLLWRBAND /* Priority data may be written. */
#endif /* !POLLWRBAND && __POLLWRBAND */

#if !defined(EPOLLRDNORM) && defined(__EPOLLRDNORM)
#define EPOLLRDNORM __EPOLLRDNORM /* 100% identical to `EPOLLIN' (Normal data may be read). */
#endif /* !EPOLLRDNORM && __EPOLLRDNORM */
#if !defined(EPOLLRDBAND) && defined(__EPOLLRDBAND)
#define EPOLLRDBAND __EPOLLRDBAND /* Priority data may be read. */
#endif /* !EPOLLRDBAND && __EPOLLRDBAND */
#if !defined(EPOLLWRNORM) && defined(__EPOLLWRNORM)
#define EPOLLWRNORM __EPOLLWRNORM /* 100% identical to `EPOLLOUT' (Writing now will not block). */
#endif /* !EPOLLWRNORM && __EOLLWRNORM */
#if !defined(EPOLLWRBAND) && defined(__EPOLLWRBAND)
#define EPOLLWRBAND __EPOLLWRBAND /* Priority data may be written. */
#endif /* !EPOLLWRBAND && __EPOLLWRBAND */


#ifndef LINUX_FUTEX_USES_TIMEOUT
#define LINUX_FUTEX_USES_TIMEOUT(futex_op)    \
	(((futex_op)&127) == FUTEX_WAIT ||        \
	 ((futex_op)&127) == FUTEX_LOCK_PI ||     \
	 ((futex_op)&127) == FUTEX_WAIT_BITSET || \
	 ((futex_op)&127) == FUTEX_WAIT_REQUEUE_PI)
#endif /* !LINUX_FUTEX_USES_TIMEOUT */



/* Spacing strings inserted in places to prettify representations. */
#if 0
#define SYNSPACE  ""
#define SYNSPACE2 ""
#elif 1
#define SYNSPACE  ""
#define SYNSPACE2 " "
#else
#define SYNSPACE  " "
#define SYNSPACE2 " "
#endif


/* The syntax to use for struct field names. */
#if 1
#define HAVE_SYNFIELD 1
#define SYNFIELD(name) name ":" SYNSPACE
#elif 1
#define HAVE_SYNFIELD 1
#define SYNFIELD(name) "." name SYNSPACE "=" SYNSPACE
#else
#define SYNFIELD(name) ""
#endif


/* The representation of bit-wide OR in flagsets */
#define PIPESTR_S SYNSPACE "|" SYNSPACE
#define PIPESTR   PIPESTR_S

#define NULLSTR_S "NULL"
#define NULLSTR   NULLSTR_S

/* Ensure that `PIPESTR' doesn't get allocated multiple times. */
PRIVATE ATTR_UNUSED char const PIPESTR_[] = PIPESTR;
#undef PIPESTR
#define PIPESTR PIPESTR_

PRIVATE /*ATTR_UNUSED*/ char const NULLSTR_[] = NULLSTR;
#undef NULLSTR
#define NULLSTR NULLSTR_



/* Helper macros. */
#define DO(...) do{ if unlikely((temp = (__VA_ARGS__)) < 0) goto err; result += temp; }__WHILE0
#define DOPRINT(str) (*printer)(arg, str, COMPILER_STRLEN(str))
#define PRINT(str)   DO(DOPRINT(str))
#define PRINTF(...)  DO(format_printf(printer, arg, __VA_ARGS__))


#if __VA_SIZE == 4
typedef uint32_t va_uint_t;
#elif __VA_SIZE == 8
typedef uint64_t va_uint_t;
#elif __VA_SIZE == 2
typedef uint16_t va_uint_t;
#elif __VA_SIZE == 1
typedef uint8_t va_uint_t;
#elif !defined(__DEEMON__)
#error "Unsupported `__VA_SIZE'"
#endif


#ifdef NEED_print_flagset_remainder
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_flagset_remainder)(pformatprinter printer, void *arg,
                                       syscall_ulong_t flags, bool is_first) {
	ssize_t result;
	if (flags) {
		/* Print unknown flags. */
		result = format_printf(printer, arg,
		                       "%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		                       is_first ? "" : PIPESTR, flags);
	} else if (is_first) {
		/* Special case for when no flags are given (in this case, don't print the `0x' prefix) */
		result = (*printer)(arg, "0", 1);
	} else {
		result = 0;
	}
	return result;
}
#endif /* NEED_print_flagset_remainder */

#ifdef NEED_print_flagset8
PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW_CB(CC print_flagset8)(pformatprinter printer, void *arg,
                              void const *flags_db, size_t stride,
                              char const *flag_prefix, syscall_ulong_t flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0;; ++i) {
		uint8_t const *pflag;
		uint8_t flag;
		pflag = (uint8_t const *)((byte_t const *)flags_db + i * stride);
		if ((flag = *pflag) == 0)
			break;
		if (!(flags & flag))
			continue;
		PRINTF("%s%s%s",
		       is_first ? "" : PIPESTR,
		       flag_prefix, (char const *)(pflag + 1));
		flags &= ~flag;
		is_first = false;
	}
	DO(print_flagset_remainder(printer, arg, flags, is_first));
	return result;
err:
	return temp;
}
#endif /* NEED_print_flagset8 */




#ifdef NEED_print_flagset16
PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW_CB(CC print_flagset16)(pformatprinter printer, void *arg,
                               void const *flags_db, size_t stride,
                               char const *flag_prefix, syscall_ulong_t flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0;; ++i) {
		uint16_t const *pflag;
		uint16_t flag;
		pflag = (uint16_t const *)((byte_t const *)flags_db + i * stride);
		if ((flag = *pflag) == 0)
			break;
		if (!(flags & flag))
			continue;
		PRINTF("%s%s%s",
		       is_first ? "" : PIPESTR,
		       flag_prefix, (char const *)(pflag + 1));
		flags &= ~flag;
		is_first = false;
	}
	DO(print_flagset_remainder(printer, arg, flags, is_first));
	return result;
err:
	return temp;
}
#endif /* NEED_print_flagset16 */




#ifdef NEED_print_flagset32
PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW_CB(CC print_flagset32)(pformatprinter printer, void *arg,
                               void const *flags_db, size_t stride,
                               char const *flag_prefix, syscall_ulong_t flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0;; ++i) {
		uint32_t const *pflag;
		uint32_t flag;
		pflag = (uint32_t const *)((byte_t const *)flags_db + i * stride);
		if ((flag = *pflag) == 0)
			break;
		if (!(flags & flag))
			continue;
		PRINTF("%s%s%s",
		       is_first ? "" : PIPESTR,
		       flag_prefix, (char const *)(pflag + 1));
		flags &= ~flag;
		is_first = false;
	}
	DO(print_flagset_remainder(printer, arg, flags, is_first));
	return result;
err:
	return temp;
}
#endif /* NEED_print_flagset32 */




#ifdef NEED_print_flagset64
PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW_CB(CC print_flagset64)(pformatprinter printer, void *arg,
                               void const *flags_db, size_t stride,
                               char const *flag_prefix, uint64_t flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0;; ++i) {
		uint64_t const *pflag;
		uint64_t flag;
		pflag = (uint64_t const *)((byte_t const *)flags_db + i * stride);
		if ((flag = *pflag) == 0)
			break;
		if (!(flags & flag))
			continue;
		PRINTF("%s%s%s",
		       is_first ? "" : PIPESTR,
		       flag_prefix, (char const *)(pflag + 1));
		flags &= ~flag;
		is_first = false;
	}
	if (flags) {
		/* Print unknown flags. */
		PRINTF("%s%#" PRIx64,
		       is_first ? "" : PIPESTR, flags);
	} else if (is_first) {
		/* Special case for when no flags are given (in this case, don't print the `0x' prefix) */
		PRINT("0");
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_flagset64 */




#ifdef NEED_print_dev
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_dev)(pformatprinter printer, void *arg,
                         mode_t mode, dev_t devno) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "%s"
	                       ":%" PRIuN(__SIZEOF_MAJOR_T__)
	                       ":%" PRIuN(__SIZEOF_MINOR_T__),
	                       S_ISBLK(mode) ? "blk" : "chr",
	                       major(devno), minor(devno));
#ifdef __KERNEL__
	if likely(result >= 0) {
		REF struct device *dev;
		dev = device_lookup_bydev_nx(mode, devno);
		if (dev) {
			ssize_t temp;
			REF struct fdirent *name;
			name = device_getfilename(dev);
			decref_unlikely(dev);
			FINALLY_DECREF_UNLIKELY(name);
			temp = format_printf(printer, arg, ":\"/dev/%#$q\"",
			                     (size_t)name->fd_namelen,
			                     name->fd_name);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	}
#endif /* __KERNEL__ */
	return result;
}
#endif /* NEED_print_dev */




#ifdef NEED_print_mode_t
PRIVATE struct {
	mode_t mn_mode;    /* Flag value */
	char   mn_name[8]; /* Flag name */
} const mode_names[] = {
	{ S_ISVTX, "S_ISVTX" },
	{ S_ISGID, "S_ISGID" },
	{ S_ISUID, "S_ISUID" }
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_mode_t)(pformatprinter printer, void *arg, mode_t mode) {
	ssize_t temp, result = 0;
	char const *name;
	bool is_first;
	unsigned int i;
	enum { VALID_MASK = S_IFMT | S_ISVTX | S_ISGID | S_ISUID | 0777 };
	switch (mode & S_IFMT) {
	case S_IFIFO:  name = "IFO"; break;  /* 0010000: FIFO. */
	case S_IFCHR:  name = "CHR"; break;  /* 0020000: Character device. */
	case S_IFDIR:  name = "DIR"; break;  /* 0040000: Directory. */
	case S_IFBLK:  name = "BLK"; break;  /* 0060000: Block device. */
	case S_IFREG:  name = "REG"; break;  /* 0100000: Regular file. */
	case S_IFLNK:  name = "LNK"; break;  /* 0120000: Symbolic link. */
	case S_IFSOCK: name = "SOCK"; break; /* 0140000: Socket. */
	default: name = NULL; break;
	}
	is_first = true;
	if likely(name) {
		result = format_printf(printer, arg, "S_IF%s", name);
		if unlikely(result < 0)
			goto done;
		is_first = false;
	} else if ((mode & S_IFMT) != 0) {
		result = format_printf(printer, arg,
		                       "0%" PRIoN(__SIZEOF_MODE_T__),
		                       (mode_t)(mode & S_IFMT));
		if unlikely(result < 0)
			goto done;
		is_first = false;
	}
	for (i = 0; i < lengthof(mode_names); ++i) {
		char const *name;
		if (!(mode & mode_names[i].mn_mode))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = mode_names[i].mn_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if (mode & 0777) {
		/* Print the permissions suffix as a raw string. */
		PRINTF("%s0%" PRIoN(__SIZEOF_MODE_T__),
		       is_first ? "" : PIPESTR,
		       (mode_t)(mode & 0777));
		is_first = false;
	}
	if unlikely(mode & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("0%" PRIoN(__SIZEOF_MODE_T__),
		       (mode_t)(mode & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_mode_t */



#ifdef NEED_print_oflag_t
PRIVATE struct {
	oflag_t on_flag;     /* Flag value */
	char    on_name[12]; /* Flag name */
} const oflag_names[] = {
	{ O_TRUNC,     "O_TRUNC" },
	{ O_CREAT,     "O_CREAT" },
	{ O_EXCL,      "O_EXCL" },
	{ O_NOCTTY,    "O_NOCTTY" },
	{ O_APPEND,    "O_APPEND" },
	{ O_NONBLOCK,  "O_NONBLOCK" },
	{ O_SYNC,      "O_SYNC" },
	{ O_DSYNC,     "O_DSYNC" },
	{ O_ASYNC,     "O_ASYNC" },
	{ O_DIRECT,    "O_DIRECT" },
	{ O_LARGEFILE, "O_LARGEFILE" },
	{ O_DIRECTORY, "O_DIRECTORY" },
	{ O_NOFOLLOW,  "O_NOFOLLOW" },
	{ O_NOATIME,   "O_NOATIME" },
	{ O_CLOEXEC,   "O_CLOEXEC" },
	{ O_PATH,      "O_PATH" },
	{ O_TMPFILE,   "O_TMPFILE" },
	{ O_CLOFORK,   "O_CLOFORK" },
	{ O_DOSPATH,   "O_DOSPATH" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_oflag_t_impl)(pformatprinter printer, void *arg,
                                  oflag_t oflags, bool force_accmode) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	enum {
		VALID_MASK = (O_ACCMODE | O_TRUNC | O_CREAT | O_EXCL |
		              O_NOCTTY | O_APPEND | O_NONBLOCK | O_SYNC |
		              O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
		              O_DIRECTORY | O_NOFOLLOW | O_NOATIME |
		              O_CLOEXEC | O_PATH | O_TMPFILE |
		              O_CLOFORK | O_DOSPATH)
	};
	if (force_accmode || (oflags & O_ACCMODE) != 0) {
		/* Print the access mode */
		char const *accname;
		switch (oflags & O_ACCMODE) {
		case O_RDONLY: accname = "RDONLY"; break;
		case O_WRONLY: accname = "WRONLY"; break;
		case O_RDWR:   accname = "RDWR"; break;
		default: accname = NULL; break;
		}
		if likely(accname) {
			result = format_printf(printer, arg, "O_%s", accname);
		} else {
			result = format_printf(printer, arg, "%#" PRIoN(__SIZEOF_OFLAG_T__),
			                       (oflag_t)(oflags & O_ACCMODE));
		}
		if unlikely(result < 0)
			goto done;
		is_first = false;
	}
	for (i = 0; i < lengthof(oflag_names); ++i) {
		char const *name;
		if ((oflags & oflag_names[i].on_flag) !=
		    /*     */ oflag_names[i].on_flag)
			continue;
#if (O_TMPFILE & O_DIRECTORY) != 0
		if (oflag_names[i].on_flag == O_DIRECTORY &&
		    (oflags & O_TMPFILE) == O_TMPFILE)
			continue;
#endif /* (O_TMPFILE & O_DIRECTORY) != 0 */
		if (!is_first)
			PRINT(PIPESTR);
		name = oflag_names[i].on_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if unlikely(oflags & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_OFLAG_T__),
		       (oflag_t)(oflags & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_oflag_t)(pformatprinter printer, void *arg,
                             oflag_t oflags, oflag_t allowed_oflags) {
	ssize_t temp, result;
	bool force_accmode;
	force_accmode = (allowed_oflags & O_ACCMODE) != 0;
	result = print_oflag_t_impl(printer, arg, oflags, force_accmode);
	if (likely(result >= 0) && unlikely((oflags & ~allowed_oflags) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_oflag_t_impl(printer, arg,
		                      oflags & ~allowed_oflags,
		                      false));
		PRINT(">");
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_oflag_t */



#ifdef NEED_print_atflag_t
PRIVATE struct {
	atflag_t an_flag;     /* Flag value */
	char     an_name[20]; /* Flag name */
} const atflag_names[] = {
	{ AT_SYMLINK_NOFOLLOW, "AT_SYMLINK_NOFOLLOW" },
	{ AT_SYMLINK_FOLLOW,   "AT_SYMLINK_FOLLOW" },
	{ AT_NO_AUTOMOUNT,     "AT_NO_AUTOMOUNT" },
	{ AT_EMPTY_PATH,       "AT_EMPTY_PATH" },
	{ AT_REMOVEREG,        "AT_REMOVEREG" },
	{ AT_ALTPATH,          "AT_ALTPATH" },
	{ AT_DOSPATH,          "AT_DOSPATH" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_atflag_t_impl)(pformatprinter printer, void *arg,
                                   atflag_t atflags,
                                   char const *nameof_AT_READLINK_REQSIZE) {
	static_assert(AT_READLINK_REQSIZE == AT_CHANGE_BTIME);
	static_assert(AT_READLINK_REQSIZE == AT_EACCESS);
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	atflag_t valid_mask;
	valid_mask = (AT_SYMLINK_NOFOLLOW | AT_SYMLINK_FOLLOW |
	              AT_NO_AUTOMOUNT | AT_EMPTY_PATH | AT_REMOVEREG |
	              AT_ALTPATH | AT_DOSPATH);
	if (nameof_AT_READLINK_REQSIZE)
		valid_mask |= AT_READLINK_REQSIZE;
	for (i = 0; i < lengthof(atflag_names); ++i) {
		char const *name;
		if (!(atflags & atflag_names[i].an_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = atflag_names[i].an_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if ((atflags & AT_READLINK_REQSIZE) && nameof_AT_READLINK_REQSIZE) {
		if (!is_first)
			PRINT(PIPESTR);
		DO((*printer)(arg, nameof_AT_READLINK_REQSIZE,
		              strlen(nameof_AT_READLINK_REQSIZE)));
		is_first = false;
	}
	if unlikely(atflags & ~valid_mask) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_ATFLAG_T__),
		       (atflag_t)(atflags & ~valid_mask));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_atflag_t)(pformatprinter printer, void *arg,
                              atflag_t atflags, atflag_t allowed_atflags,
                              char const *nameof_AT_READLINK_REQSIZE) {
	ssize_t temp, result;
	result = print_atflag_t_impl(printer, arg, atflags,
	                             nameof_AT_READLINK_REQSIZE);
	if (likely(result >= 0) && unlikely((atflags & ~allowed_atflags) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_atflag_t_impl(printer, arg,
		                       atflags & ~allowed_atflags,
		                       nameof_AT_READLINK_REQSIZE));
		PRINT(">");
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_atflag_t */



#ifdef NEED_print_iomode_t
PRIVATE struct {
	iomode_t on_flag;     /* Flag value */
	char    on_name[12]; /* Flag name */
} const iomode_names[] = {
	{ IO_CLOEXEC,    "CLOEXEC" },
	{ IO_CLOFORK,    "CLOFORK" },
	{ IO_APPEND,     "APPEND" },
	{ IO_NONBLOCK,   "NONBLOCK" },
	{ IO_DSYNC,      "DSYNC" },
	{ IO_DIRECT,     "DIRECT" },
	{ IO_NODATAZERO, "NODATAZERO" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_iomode_t_impl)(pformatprinter printer, void *arg,
                                   iomode_t iomodes, bool force_accmode) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	enum {
		VALID_MASK = (IO_ACCMODE | IO_CLOEXEC | IO_CLOFORK |
		              IO_APPEND | IO_NONBLOCK | IO_DSYNC |
		              IO_DIRECT | IO_NODATAZERO)
	};
	if (force_accmode || (iomodes & IO_ACCMODE) != 0) {
		/* Print the access mode */
		char const *accname;
		switch (iomodes & IO_ACCMODE) {
		case IO_RDONLY:   accname = "RDONLY"; break;
		case IO_WRONLY:   accname = "WRONLY"; break;
		case IO_RDWR:     accname = "RDWR"; break;
		default: accname = NULL; break;
		}
		if likely(accname) {
			result = format_printf(printer, arg, "IO_%s", accname);
		} else {
			result = format_printf(printer, arg, "%#" PRIoN(__SIZEOF_IOMODE_T__),
			                       (iomode_t)(iomodes & IO_ACCMODE));
		}
		if unlikely(result < 0)
			goto done;
		is_first = false;
	}
	for (i = 0; i < lengthof(iomode_names); ++i) {
		char const *name;
		if (!(iomodes & iomode_names[i].on_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = iomode_names[i].on_name;
		PRINTF("IO_%s", name);
		is_first = false;
	}
	if unlikely(iomodes & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_IOMODE_T__),
		       (iomode_t)(iomodes & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_iomode_t)(pformatprinter printer, void *arg,
                              iomode_t iomodes, iomode_t allowed_iomodes) {
	ssize_t temp, result;
	bool force_accmode;
	force_accmode = (allowed_iomodes & IO_ACCMODE) != 0;
	result = print_iomode_t_impl(printer, arg, iomodes, force_accmode);
	if (likely(result >= 0) && unlikely((iomodes & ~allowed_iomodes) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_iomode_t_impl(printer, arg,
		                       iomodes & ~allowed_iomodes,
		                       false));
		PRINT(">");
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_iomode_t */



#ifdef NEED_print_fd_t
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_fd_t)(pformatprinter printer, void *arg, fd_t fd) {
	ssize_t result;
	char const *name;
	/* XXX: Don't use a switch() here? */
	switch (fd) {
		/* Deal with symbolic file handles. */
	case AT_FDCWD:     name = "AT_FDCWD"; break;
	case AT_FDROOT:    name = "AT_FDROOT"; break;
	case AT_FDTHRD:    name = "AT_FDTHRD"; break;
	case AT_FDPROC:    name = "AT_FDPROC"; break;
	case AT_FDPARPROC: name = "AT_FDPARPROC"; break;
	case AT_FDCTTY:    name = "AT_FDCTTY"; break;
	case AT_FDSYSRTLD: name = "AT_FDSYSRTLD"; break;

#if 1 /* <unistd.h> names for certain file handles. */
	case STDIN_FILENO:  name = "STDIN_FILENO"; break;
	case STDOUT_FILENO: name = "STDOUT_FILENO"; break;
	case STDERR_FILENO: name = "STDERR_FILENO"; break;
#endif

	default:
		/* Deal with DOS drive file handles. */
		if (fd >= AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN) &&
		    fd <= AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)) {
			result = format_printf(printer, arg, "AT_FDDRIVE_CWD('%c')",
			                       'A' + (fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)));
		} else if (fd >= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) &&
		           fd <= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)) {
			result = format_printf(printer, arg, "AT_FDDRIVE_ROOT('%c')",
			                       'A' + (fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)));
		} else {
			result = format_printf(printer, arg,
			                       "%" PRIdN(__SIZEOF_FD_T__),
			                       fd);
		}
		goto done;
	}
	result = (*printer)(arg, name, strlen(name));
done:
	return result;
}
#endif /* NEED_print_fd_t */



#if defined(NEED_print_clockid_t) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/clock.h", "__CLOCK_");
printStrendNDatabase("CLOCKID", typ);
]]]*/
#define GETBASE_CLOCKID(result, index) \
	(((index) <= 0xb) ? ((result) = repr_CLOCKID_0h, true) : false)
PRIVATE char const repr_CLOCKID_0h[] =
"REALTIME\0MONOTONIC\0PROCESS_CPUTIME_ID\0THREAD_CPUTIME_ID\0MONOTONI"
"C_RAW\0REALTIME_COARSE\0MONOTONIC_COARSE\0BOOTTIME\0REALTIME_ALARM\0B"
"OOTTIME_ALARM\0\0TAI";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_clockid_name)(clockid_t clockid) {
	char const *result = NULL;
	if (!GETBASE_CLOCKID(result, clockid))
		goto done;
	for (; clockid; --clockid)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_clockid_t)(pformatprinter printer, void *arg, clockid_t clockid) {
	char const *name;
	name = get_clockid_name(clockid);
	if (name)
		return format_printf(printer, arg, "CLOCK_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_CLOCKID_T__), clockid);
}
#endif /* NEED_print_clockid_t */



#ifdef NEED_print_string
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_string)(pformatprinter printer, void *arg,
                                NCX UNCHECKED char const *str,
                                struct sc_argument *length_link) {
	ssize_t result;
	if (!str) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else {
		size_t len;
		if (length_link) {
			len = (size_t)length_link->sa_value.sv_u64;
			validate_readable(str, len);
		} else {
			validate_readable(str, 1);
			len = strlen(str);
		}
		if (len > LIMIT_STRLEN) {
			result = format_printf(printer, arg, "%$q...", LIMIT_STRLEN, str);
		} else {
			result = format_printf(printer, arg, "%$q", len, str);
		}
	}
	return result;
}
#endif /* NEED_print_string */



#ifdef NEED_print_bytes
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_bytes)(pformatprinter printer, void *arg,
                               NCX void const *buf, size_t len) {
	ssize_t temp, result = 0;
	size_t i;
	for (i = 0; i < len; ++i) {
		byte_t b;
		b = ((NCX byte_t const *)buf)[i];
		if (i != 0)
			PRINT("," SYNSPACE);
		PRINTF("%#.2" PRIx8, b);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_bytes */



#ifdef NEED_print_string_or_buffer
PRIVATE ATTR_CONST bool
NOTHROW(CC is_printable_character)(char ch) {
	if (isprint(ch))
		return true;
	switch (ch) {

	case 7:  /* \a */
	case 8:  /* \b */
	case 9:  /* \t */
	case 10: /* \n */
	case 11: /* \v */
	case 12: /* \f */
	case 13: /* \r */
	case 27: /* \e */
	case '\\':
	case '\'':
	case '\"':
		return true;

	default:
		break;
	}
	return false;
}

PRIVATE ATTR_PURE WUNUSED bool
NOTHROW_NCX(CC is_printable_string)(NCX char const *str,
                                    size_t length) {
	size_t i;
	size_t num_printable = 0;
	for (i = 0; i < length; ++i) {
		if (is_printable_character(str[i]))
			++num_printable;
	}
	/* Consider as printable when at least 3/4th are printable characters. */
	return (num_printable * 4) >= (length * 3);
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_string_or_buffer)(pformatprinter printer, void *arg,
                                          NCX UNCHECKED void const *buf,
                                          size_t length) {
	ssize_t result, temp;
	if (!buf) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else if (!length) {
		result = format_printf(printer, arg, "%#p", buf);
	} else {
		size_t used_length = length;
		if (used_length > LIMIT_STRLEN)
			used_length = LIMIT_STRLEN;
		validate_readable(buf, used_length);
		/* Check if all characters are  printable.
		 * If all of them are, output as a string. */
		if (is_printable_string((char const *)buf, used_length)) {
			result = format_printf(printer, arg, "%$q", used_length, buf);
			if unlikely(result < 0)
				goto done;
		} else {
			result = DOPRINT("[");
			if unlikely(result < 0)
				goto done;
			DO(print_bytes(printer, arg, buf, used_length));
			PRINT("]");
		}
		if (used_length > LIMIT_STRLEN)
			PRINT("...");
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_string_or_buffer */



#if defined(NEED_print_sighandler_t) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping(
	"../../include/asm/os/kos/signal.h", "__SIG_",
	filter: x -> x !in { "__SIG_BLOCK", "__SIG_UNBLOCK", "__SIG_SETMASK" });
printStrendNDatabase("SIGHANDLER", typ);
]]]*/
#define GETBASE_SIGHANDLER(result, index) \
	(((index) >= -0x1 && (index) <= 0xb) ? ((index) += 0x1, (result) = repr_SIGHANDLER_m1h, true) : false)
PRIVATE char const repr_SIGHANDLER_m1h[] =
"ERR\0DFL\0IGN\0HOLD\0TERM\0EXIT\0\0\0\0CONT\0STOP\0CORE\0GET";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_sighandler_t_name)(intptr_t hand) {
	char const *result = NULL;
	if (!GETBASE_SIGHANDLER(result, hand))
		goto done;
	for (; hand; --hand)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_sighandler_t)(pformatprinter printer, void *arg,
                                  NCX UNCHECKED void *hand) {
	char const *name;
	name = get_sighandler_t_name((intptr_t)(uintptr_t)hand);
	if (name)
		return format_printf(printer, arg, "SIG_%s", name);
	return format_printf(printer, arg, "%#" PRIxPTR, hand);
}
#endif /* NEED_print_sighandler_t */



#ifdef NEED_print_poll_what
PRIVATE struct {
	uint16_t   pn_flag;
	char const pn_name[8];
} const poll_event_flag_names[] = {
#ifdef POLLIN
	{ POLLIN,     "IN" },
#endif /* POLLIN */
#ifdef POLLPRI
	{ POLLPRI,    "PRI" },
#endif /* POLLPRI */
#ifdef POLLOUT
	{ POLLOUT,    "OUT" },
#endif /* POLLOUT */
#ifdef POLLRDNORM
	{ POLLRDNORM, "RDNORM" },
#endif /* POLLRDNORM */
#ifdef POLLRDBAND
	{ POLLRDBAND, "RDBAND" },
#endif /* POLLRDBAND */
#ifdef POLLWRNORM
	{ POLLWRNORM, "WRNORM" },
#endif /* POLLWRNORM */
#ifdef POLLWRBAND
	{ POLLWRBAND, "WRBAND" },
#endif /* POLLWRBAND */
#ifdef POLLMSG
	{ POLLMSG,    "MSG" },
#endif /* POLLMSG */
#ifdef POLLREMOVE
	{ POLLREMOVE, "REMOVE" },
#endif /* POLLREMOVE */
#ifdef POLLRDHUP
	{ POLLRDHUP,  "RDHUP" },
#endif /* POLLRDHUP */
#ifdef POLLERR
	{ POLLERR,    "ERR" },
#endif /* POLLERR */
#ifdef POLLHUP
	{ POLLHUP,    "HUP" },
#endif /* POLLHUP */
#ifdef POLLNVAL
	{ POLLNVAL,   "NVAL" },
#endif /* POLLNVAL */
	{ 0, "" }
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_poll_what)(pformatprinter printer, void *arg, uint16_t events) {
	return print_flagset16(printer, arg,
	                       poll_event_flag_names,
	                       sizeof(*poll_event_flag_names),
	                       "POLL", events);
}
#endif /* NEED_print_poll_what */



#ifdef NEED_print_epoll_what
PRIVATE struct {
	uint16_t   pn_flag;
	char const pn_name[8];
} const epoll_event_flag_names[] = {
#ifdef EPOLLIN
	{ EPOLLIN,     "IN" },
#endif /* EPOLLIN */
#ifdef EPOLLPRI
	{ EPOLLPRI,    "PRI" },
#endif /* EPOLLPRI */
#ifdef EPOLLOUT
	{ EPOLLOUT,    "OUT" },
#endif /* EPOLLOUT */
#ifdef EPOLLRDNORM
	{ EPOLLRDNORM, "RDNORM" },
#endif /* EPOLLRDNORM */
#ifdef EPOLLRDBAND
	{ EPOLLRDBAND, "RDBAND" },
#endif /* EPOLLRDBAND */
#ifdef EPOLLWRNORM
	{ EPOLLWRNORM, "WRNORM" },
#endif /* EPOLLWRNORM */
#ifdef EPOLLWRBAND
	{ EPOLLWRBAND, "WRBAND" },
#endif /* EPOLLWRBAND */
#ifdef EPOLLMSG
	{ EPOLLMSG,    "MSG" },
#endif /* EPOLLMSG */
#ifdef EPOLLRDHUP
	{ EPOLLRDHUP,  "RDHUP" },
#endif /* EPOLLRDHUP */
#ifdef EPOLLERR
	{ EPOLLERR,    "ERR" },
#endif /* EPOLLERR */
#ifdef EPOLLHUP
	{ EPOLLHUP,    "HUP" },
#endif /* EPOLLHUP */
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_epoll_what)(pformatprinter printer, void *arg, uint16_t events) {
	return print_flagset16(printer, arg,
	                       epoll_event_flag_names,
	                       sizeof(*epoll_event_flag_names),
	                       "EPOLL", events);
}
#endif /* NEED_print_epoll_what */



#ifdef NEED_print_pollfd
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_pollfd)(pformatprinter printer, void *arg,
                            struct pollfd const *__restrict pfd) {
	ssize_t temp, result;
	result = DOPRINT("{" SYNSPACE SYNFIELD("fd"));
	if unlikely(result < 0)
		goto done;
	DO(print_fd_t(printer, arg, pfd->fd));
	PRINT("," SYNSPACE SYNFIELD("events"));
	DO(print_poll_what(printer, arg, pfd->events));
	PRINT(SYNSPACE "}");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_pollfd */



#ifdef NEED_print_segfault
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_segfault)(pformatprinter printer, void *arg) {
	struct exception_data *data = except_data();
	return format_printf(printer, arg, "<segfault:%p>",
	                     data->e_args.e_segfault.s_addr);
}
#endif /* NEED_print_segfault */



#ifdef NEED_print_pollfds
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_pollfds)(pformatprinter printer, void *arg,
                                 NCX struct pollfd const *fds, size_t count) {
	ssize_t temp, result = 0;
	size_t i, used_count = count;
	if (used_count > LIMIT_POLLFDS)
		used_count = LIMIT_POLLFDS;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < used_count; ++i) {
		struct pollfd pfd;
		if (i != 0)
			PRINT("," SYNSPACE2);
		TRY {
			memcpy(&pfd, &fds[i], sizeof(struct pollfd));
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			DO(print_segfault(printer, arg));
			goto done_rbracket;
		}
		DO(print_pollfd(printer, arg, &pfd));
	}
	if (used_count < count)
		PRINT("," SYNSPACE2 "...");
done_rbracket:
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_pollfds */



#ifdef NEED_print_timespec
PRIVATE NONNULL((1, 3)) ssize_t
NOTHROW_CB(CC print_timespec)(pformatprinter printer, void *arg,
                              struct timespec const *__restrict ts) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("tv_sec") "%" PRIdN(__SIZEOF_TIME64_T__)
	                       "," SYNSPACE SYNFIELD("tv_nsec") "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__)
	                       SYNSPACE "}",
	                       ts->tv_sec, ts->tv_nsec);
	return result;
}
#endif /* NEED_print_timespec */




#ifdef NEED_print_timespec_vector
PRIVATE ATTR_INS(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(CC print_timespec_vector)(pformatprinter printer, void *arg,
                                     struct timespec const *__restrict tsv,
                                     size_t count) {
	size_t i;
	ssize_t temp, result;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < count; ++i) {
		if (i != 0)
			PRINT("," SYNSPACE2);
		DO(print_timespec(printer, arg, &tsv[i]));
	}
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_timespec_vector */



#ifdef NEED_print_timeval
PRIVATE NONNULL((1, 3)) ssize_t
NOTHROW_CB(CC print_timeval)(pformatprinter printer, void *arg,
                             struct timeval const *__restrict ts) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("tv_sec") "%" PRIdN(__SIZEOF_TIME64_T__)
	                       "," SYNSPACE SYNFIELD("tv_usec") "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__)
	                       SYNSPACE "}",
	                       ts->tv_sec, ts->tv_usec);
	return result;
}
#endif /* NEED_print_timeval */



#ifdef NEED_print_timeval_vector
PRIVATE ATTR_INS(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(CC print_timeval_vector)(pformatprinter printer, void *arg,
                                    struct timeval const *__restrict tsv,
                                    size_t count) {
	size_t i;
	ssize_t temp, result;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < count; ++i) {
		if (i != 0)
			PRINT("," SYNSPACE2);
		DO(print_timeval(printer, arg, &tsv[i]));
	}
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_timeval_vector */



#if defined(NEED_print_ioctl_command) || defined(__DEEMON__)
/* Use the same trick as also used in libdebuginfo/repr.c to encode
 * symbolic constant names (such as those for ioctl() commands)  as
 * efficiently as possible. */

/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
import util;
local ioctls = Dict();

for (local macroName, macroValue: enumerateMacrosFromFiles({
	"../../include/asm/os/kos/block.h",
	"../../include/asm/os/kos/tty.h",
	"../../include/asm/os/kos/stropts.h",
	"../../include/asm/os/kos/socket-ioctls.h",
	"../../include/linux/kd.h",
	"../../include/linux/fd.h",
	"../../include/linux/hdreg.h",
	"../../include/linux/msdos_fs.h",
	"../../include/linux/vt.h",
	"../../include/kos/ioctl/" "*.h",
})) {
	for (local prefix: {
		"_IO(", "_IOR(", "_IOW(", "_IOWR(",
		"_IO_KOS(", "_IOR_KOS(", "_IOW_KOS(", "_IOWR_KOS("
	}) {
		if (!macroValue.startswith(prefix))
			continue;
		local a, b;
		try {
			a, b = macroValue[#prefix:].scanf(" %[^,], %[^,)] ")...;
			a = getMacroIntValue(a);
			b = getMacroIntValue(b);
		} catch (...) {
			continue;
		}
		if (a < 0 || a > 0xff || b < 0 || b > 0xff)
			continue;
		macroValue = a << 8 | b;
		if (prefix.startswith("_IOWR")) {
			macroValue |= 0xc0000000; // _IOC_INOUT
		} else if (prefix.startswith("_IOR")) {
			macroValue |= 0x80000000; // _IOC_OUT
		} else if (prefix.startswith("_IOW")) {
			macroValue |= 0x40000000; // _IOC_IN
		}
		if ("KOS" in prefix)
			macroValue |= 0x20000000; // _IOCKOS_MASK
		break;
	}
	if (macroValue !is int)
		continue;
	if (macroValue !in ioctls)
		ioctls[macroValue] = macroName.lstrip("_");
}

printStrendNDatabase("IOCTLS", ioctls);
]]]*/
#define GETBASE_IOCTLS(result, index) \
	(((index) <= 0x2) ? ((result) = repr_IOCTLS_0h, true) : \
	 ((index) >= 0x241 && (index) <= 0x25a) ? ((index) -= 0x241, (result) = repr_IOCTLS_241h, true) : \
	 ((index) >= 0x301 && (index) <= 0x32f) ? ((index) -= 0x301, (result) = repr_IOCTLS_301h, true) : \
	 ((index) >= 0x125d && (index) <= 0x127f) ? ((index) -= 0x125d, (result) = repr_IOCTLS_125dh, true) : \
	 ((index) >= 0x4b2f && (index) <= 0x4b72) ? ((index) -= 0x4b2f, (result) = repr_IOCTLS_4b2fh, true) : \
	 ((index) >= 0x4bfa && (index) <= 0x4bfb) ? ((index) -= 0x4bfa, (result) = repr_IOCTLS_4bfah, true) : \
	 ((index) >= 0x5301 && (index) <= 0x5322) ? ((index) -= 0x5301, (result) = repr_IOCTLS_5301h, true) : \
	 ((index) >= 0x5401 && (index) <= 0x5460) ? ((index) -= 0x5401, (result) = repr_IOCTLS_5401h, true) : \
	 ((index) >= 0x5600 && (index) <= 0x560f) ? ((index) -= 0x5600, (result) = repr_IOCTLS_5600h, true) : \
	 ((index) >= 0x8901 && (index) <= 0x89b1) ? ((index) -= 0x8901, (result) = repr_IOCTLS_8901h, true) : \
	 ((index) >= 0x89e0 && (index) <= 0x89f0) ? ((index) -= 0x89e0, (result) = repr_IOCTLS_89e0h, true) : \
	 ((index) >= 0x20004b03 && (index) <= 0x20004b04) ? ((index) -= 0x20004b03, (result) = repr_IOCTLS_20004b03h, true) : \
	 ((index) == 0x20004d07) ? ((index) = 0, (result) = repr_IOCTLS_20004d07h, true) : \
	 ((index) == 0x20005600) ? ((index) = 0, (result) = repr_IOCTLS_20005600h, true) : \
	 ((index) == 0x20006600) ? ((index) = 0, (result) = repr_IOCTLS_20006600h, true) : \
	 ((index) == 0x2000664c) ? ((index) = 0, (result) = repr_IOCTLS_2000664ch, true) : \
	 ((index) >= 0x200066c0 && (index) <= 0x200066c1) ? ((index) -= 0x200066c0, (result) = repr_IOCTLS_200066c0h, true) : \
	 ((index) >= 0x20006d12 && (index) <= 0x20006d13) ? ((index) -= 0x20006d12, (result) = repr_IOCTLS_20006d12h, true) : \
	 ((index) >= 0x40000242 && (index) <= 0x4000024c) ? ((index) -= 0x40000242, (result) = repr_IOCTLS_40000242h, true) : \
	 ((index) == 0x40000290) ? ((index) = 0, (result) = repr_IOCTLS_40000290h, true) : \
	 ((index) == 0x40001271) ? ((index) = 0, (result) = repr_IOCTLS_40001271h, true) : \
	 ((index) >= 0x4000542b && (index) <= 0x40005436) ? ((index) -= 0x4000542b, (result) = repr_IOCTLS_4000542bh, true) : \
	 ((index) == 0x40007211) ? ((index) = 0, (result) = repr_IOCTLS_40007211h, true) : \
	 ((index) >= 0x60004b02 && (index) <= 0x60004b08) ? ((index) -= 0x60004b02, (result) = repr_IOCTLS_60004b02h, true) : \
	 ((index) == 0x60004c01) ? ((index) = 0, (result) = repr_IOCTLS_60004c01h, true) : \
	 ((index) >= 0x60004d00 && (index) <= 0x60004d06) ? ((index) -= 0x60004d00, (result) = repr_IOCTLS_60004d00h, true) : \
	 ((index) >= 0x60005301 && (index) <= 0x60005302) ? ((index) -= 0x60005301, (result) = repr_IOCTLS_60005301h, true) : \
	 ((index) >= 0x60005400 && (index) <= 0x60005403) ? ((index) -= 0x60005400, (result) = repr_IOCTLS_60005400h, true) : \
	 ((index) >= 0x60005611 && (index) <= 0x60005612) ? ((index) -= 0x60005611, (result) = repr_IOCTLS_60005611h, true) : \
	 ((index) == 0x6000664c) ? ((index) = 0, (result) = repr_IOCTLS_6000664ch, true) : \
	 ((index) >= 0x80000204 && (index) <= 0x80000217) ? ((index) -= 0x80000204, (result) = repr_IOCTLS_80000204h, true) : \
	 ((index) >= 0x80001270 && (index) <= 0x80001272) ? ((index) -= 0x80001270, (result) = repr_IOCTLS_80001270h, true) : \
	 ((index) >= 0x8000542a && (index) <= 0x80005442) ? ((index) -= 0x8000542a, (result) = repr_IOCTLS_8000542ah, true) : \
	 ((index) == 0x8000667a) ? ((index) = 0, (result) = repr_IOCTLS_8000667ah, true) : \
	 ((index) >= 0x80007201 && (index) <= 0x80007213) ? ((index) -= 0x80007201, (result) = repr_IOCTLS_80007201h, true) : \
	 ((index) >= 0x80008906 && (index) <= 0x80008907) ? ((index) -= 0x80008906, (result) = repr_IOCTLS_80008906h, true) : \
	 ((index) >= 0xa0004600 && (index) <= 0xa0004604) ? ((index) -= 0xa0004600, (result) = repr_IOCTLS_a0004600h, true) : \
	 ((index) >= 0xa0004680 && (index) <= 0xa0004687) ? ((index) -= 0xa0004680, (result) = repr_IOCTLS_a0004680h, true) : \
	 ((index) >= 0xa0004b00 && (index) <= 0xa0004b08) ? ((index) -= 0xa0004b00, (result) = repr_IOCTLS_a0004b00h, true) : \
	 ((index) >= 0xa0004c01 && (index) <= 0xa0004c06) ? ((index) -= 0xa0004c01, (result) = repr_IOCTLS_a0004c01h, true) : \
	 ((index) >= 0xa0004d00 && (index) <= 0xa0004d04) ? ((index) -= 0xa0004d00, (result) = repr_IOCTLS_a0004d00h, true) : \
	 ((index) >= 0xa0005000 && (index) <= 0xa0005001) ? ((index) -= 0xa0005000, (result) = repr_IOCTLS_a0005000h, true) : \
	 ((index) >= 0xa0005300 && (index) <= 0xa0005305) ? ((index) -= 0xa0005300, (result) = repr_IOCTLS_a0005300h, true) : \
	 ((index) >= 0xa0005400 && (index) <= 0xa0005403) ? ((index) -= 0xa0005400, (result) = repr_IOCTLS_a0005400h, true) : \
	 ((index) >= 0xa0005601 && (index) <= 0xa0005612) ? ((index) -= 0xa0005601, (result) = repr_IOCTLS_a0005601h, true) : \
	 ((index) == 0xa000664c) ? ((index) = 0, (result) = repr_IOCTLS_a000664ch, true) : \
	 ((index) >= 0xa0006680 && (index) <= 0xa0006685) ? ((index) -= 0xa0006680, (result) = repr_IOCTLS_a0006680h, true) : \
	 ((index) >= 0xa0006d01 && (index) <= 0xa0006d11) ? ((index) -= 0xa0006d01, (result) = repr_IOCTLS_a0006d01h, true) : \
	 ((index) >= 0xa0007000 && (index) <= 0xa0007010) ? ((index) -= 0xa0007000, (result) = repr_IOCTLS_a0007000h, true) : \
	 ((index) == 0xc0001273) ? ((index) = 0, (result) = repr_IOCTLS_c0001273h, true) : \
	 ((index) == 0xc0005443) ? ((index) = 0, (result) = repr_IOCTLS_c0005443h, true) : \
	 ((index) >= 0xc0005877 && (index) <= 0xc0005879) ? ((index) -= 0xc0005877, (result) = repr_IOCTLS_c0005877h, true) : \
	 ((index) >= 0xe0004610 && (index) <= 0xe0004620) ? ((index) -= 0xe0004610, (result) = repr_IOCTLS_e0004610h, true) : \
	 ((index) >= 0xe0005008 && (index) <= 0xe0005009) ? ((index) -= 0xe0005008, (result) = repr_IOCTLS_e0005008h, true) : \
	 ((index) >= 0xe0006601 && (index) <= 0xe0006612) ? ((index) -= 0xe0006601, (result) = repr_IOCTLS_e0006601h, true) : \
	 ((index) >= 0xe0006d00 && (index) <= 0xe0006d02) ? ((index) -= 0xe0006d00, (result) = repr_IOCTLS_e0006d00h, true) : false)
PRIVATE char const repr_IOCTLS_0h[] =
"\0FIBMAP\0FIGETBSZ";
PRIVATE char const repr_IOCTLS_241h[] =
"FDCLRPRM\0\0\0\0FDMSGON\0FDMSGOFF\0FDFMTBEG\0\0FDFMTEND\0FDSETEMSGTRESH\0F"
"DFLUSH\0\0\0\0\0\0\0\0\0FDRESET\0\0FDWERRORCLR\0\0FDRAWCMD\0FDTWADDLE\0FDEJECT";
PRIVATE char const repr_IOCTLS_301h[] =
"HDIO_GETGEO\0HDIO_GET_UNMASKINTR\0\0HDIO_GET_MULTCOUNT\0HDIO_GET_QDM"
"A\0HDIO_SET_XFER\0HDIO_OBSOLETE_IDENTITY\0HDIO_GET_KEEPSETTINGS\0HDI"
"O_GET_32BIT\0HDIO_GET_NOWERR\0HDIO_GET_DMA\0HDIO_GET_NICE\0HDIO_GET_"
"IDENTITY\0HDIO_GET_WCACHE\0HDIO_GET_ACOUSTIC\0HDIO_GET_ADDRESS\0\0\0\0\0"
"\0\0\0\0\0HDIO_GET_BUSSTATE\0HDIO_TRISTATE_HWIF\0HDIO_DRIVE_RESET\0HDIO_"
"DRIVE_TASKFILE\0HDIO_DRIVE_TASK\0HDIO_DRIVE_CMD\0\0HDIO_SET_MULTCOUN"
"T\0HDIO_SET_UNMASKINTR\0HDIO_SET_KEEPSETTINGS\0HDIO_SET_32BIT\0HDIO_"
"SET_NOWERR\0HDIO_SET_DMA\0HDIO_SET_PIO_MODE\0HDIO_SCAN_HWIF\0HDIO_SE"
"T_NICE\0HDIO_UNREGISTER_HWIF\0HDIO_SET_WCACHE\0HDIO_SET_ACOUSTIC\0HD"
"IO_SET_BUSSTATE\0HDIO_SET_QDMA\0HDIO_SET_ADDRESS";
PRIVATE char const repr_IOCTLS_125dh[] =
"BLKROSET\0BLKROGET\0BLKRRPART\0BLKGETSIZE\0BLKFLSBUF\0BLKRASET\0BLKRAG"
"ET\0BLKFRASET\0BLKFRAGET\0BLKSECTSET\0BLKSECTGET\0BLKSSZGET\0\0\0\0\0\0\0\0\0\0"
"\0\0BLKTRACESTART\0BLKTRACESTOP\0BLKTRACETEARDOWN\0BLKDISCARD\0BLKIOMI"
"N\0BLKIOOPT\0BLKALIGNOFF\0BLKPBSZGET\0BLKDISCARDZEROES\0BLKSECDISCARD"
"\0BLKROTATIONAL\0BLKZEROOUT";
PRIVATE char const repr_IOCTLS_4b2fh[] =
"KIOCSOUND\0KDMKTONE\0KDGETLED\0KDSETLED\0KDGKBTYPE\0KDADDIO\0KDDELIO\0K"
"DENABIO\0KDDISABIO\0\0\0KDSETMODE\0KDGETMODE\0KDMAPDISP\0KDUNMAPDISP\0\0\0"
"GIO_SCRNMAP\0PIO_SCRNMAP\0\0\0KDGKBMODE\0KDSKBMODE\0KDGKBENT\0KDSKBENT\0"
"KDGKBSENT\0KDSKBSENT\0KDGKBDIACR\0KDSKBDIACR\0KDGETKEYCODE\0KDSETKEYC"
"ODE\0KDSIGACCEPT\0\0\0\0KDKBDREP\0\0\0\0\0\0\0\0\0\0\0\0\0\0GIO_FONT\0PIO_FONT\0KDGKB"
"META\0KDSKBMETA\0KDGKBLED\0KDSKBLED\0GIO_UNIMAP\0PIO_UNIMAP\0PIO_UNIMA"
"PCLR\0GIO_UNISCRNMAP\0PIO_UNISCRNMAP\0GIO_FONTX\0PIO_FONTX\0PIO_FONTR"
"ESET\0\0\0GIO_CMAP\0PIO_CMAP\0KDFONTOP";
PRIVATE char const repr_IOCTLS_4bfah[] =
"KDGKBDIACRUC\0KDSKBDIACRUC";
PRIVATE char const repr_IOCTLS_5301h[] =
"I_NREAD\0I_PUSH\0I_POP\0I_LOOK\0I_FLUSH\0I_SRDOPT\0I_GRDOPT\0I_STR\0I_SE"
"TSIG\0I_GETSIG\0I_FIND\0I_LINK\0I_UNLINK\0I_RECVFD\0I_PEEK\0I_FDINSERT\0"
"I_SENDFD\0\0I_SWROPT\0I_GWROPT\0I_LIST\0I_PLINK\0I_PUNLINK\0\0\0\0\0I_FLUSH"
"BAND\0I_CKBAND\0I_GETBAND\0I_ATMARK\0I_SETCLTIME\0I_GETCLTIME\0I_CANPU"
"T";
PRIVATE char const repr_IOCTLS_5401h[] =
"TCGETS\0TCSETS\0TCSETSW\0TCSETSF\0TCGETA\0TCSETA\0TCSETAW\0TCSETAF\0TCSB"
"RK\0TCXONC\0TCFLSH\0TIOCEXCL\0TIOCNXCL\0TIOCSCTTY\0TIOCGPGRP\0TIOCSPGRP"
"\0TIOCOUTQ\0TIOCSTI\0TIOCGWINSZ\0TIOCSWINSZ\0TIOCMGET\0TIOCMBIS\0TIOCMB"
"IC\0TIOCMSET\0TIOCGSOFTCAR\0TIOCSSOFTCAR\0TIOCINQ\0TIOCLINUX\0TIOCCONS"
"\0TIOCGSERIAL\0TIOCSSERIAL\0TIOCPKT\0FIONBIO\0TIOCNOTTY\0TIOCSETD\0TIOC"
"GETD\0TCSBRKP\0\0TIOCSBRK\0TIOCCBRK\0TIOCGSID\0\0\0\0\0TIOCGRS485\0TIOCSRS4"
"85\0\0\0TCGETX\0TCSETX\0TCSETXF\0TCSETXW\0\0TIOCVHANGUP\0\0\0\0\0\0\0\0\0\0TIOCGPT"
"PEER\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0FIONCLEX\0FIOCLEX\0FIOASYNC\0TIOCSERCONFIG\0TIOCS"
"ERGWILD\0TIOCSERSWILD\0TIOCGLCKTRMIOS\0TIOCSLCKTRMIOS\0TIOCSERGSTRUC"
"T\0TIOCSERGETLSR\0TIOCSERGETMULTI\0TIOCSERSETMULTI\0TIOCMIWAIT\0TIOCG"
"ICOUNT\0\0\0FIOQSIZE";
PRIVATE char const repr_IOCTLS_5600h[] =
"VT_OPENQRY\0VT_GETMODE\0VT_SETMODE\0VT_GETSTATE\0VT_SENDSIG\0VT_RELDI"
"SP\0VT_ACTIVATE\0VT_WAITACTIVE\0VT_DISALLOCATE\0VT_RESIZE\0VT_RESIZEX"
"\0VT_LOCKSWITCH\0VT_UNLOCKSWITCH\0VT_GETHIFONTMASK\0VT_WAITEVENT\0VT_"
"SETACTIVATE";
PRIVATE char const repr_IOCTLS_8901h[] =
"FIOSETOWN\0SIOCSPGRP\0FIOGETOWN\0SIOCGPGRP\0SIOCATMARK\0\0\0\0\0\0SIOCADDR"
"T\0SIOCDELRT\0SIOCRTMSG\0\0\0SIOCGIFNAME\0SIOCSIFLINK\0SIOCGIFCONF\0SIOC"
"GIFFLAGS\0SIOCSIFFLAGS\0SIOCGIFADDR\0SIOCSIFADDR\0SIOCGIFDSTADDR\0SIO"
"CSIFDSTADDR\0SIOCGIFBRDADDR\0SIOCSIFBRDADDR\0SIOCGIFNETMASK\0SIOCSIF"
"NETMASK\0SIOCGIFMETRIC\0SIOCSIFMETRIC\0SIOCGIFMEM\0SIOCSIFMEM\0SIOCGI"
"FMTU\0SIOCSIFMTU\0SIOCSIFNAME\0SIOCSIFHWADDR\0SIOCGIFENCAP\0SIOCSIFEN"
"CAP\0SIOCGIFHWADDR\0\0SIOCGIFSLAVE\0\0\0\0\0\0\0SIOCSIFSLAVE\0SIOCADDMULTI\0"
"SIOCDELMULTI\0SIOCGIFINDEX\0SIOCSIFPFLAGS\0SIOCGIFPFLAGS\0SIOCDIFADD"
"R\0SIOCSIFHWBROADCAST\0SIOCGIFCOUNT\0\0\0\0\0\0\0\0SIOCGIFBR\0SIOCSIFBR\0SIO"
"CGIFTXQLEN\0SIOCSIFTXQLEN\0\0\0SIOCETHTOOL\0SIOCGMIIPHY\0SIOCGMIIREG\0S"
"IOCSMIIREG\0SIOCWANDEV\0SIOCOUTQNSD\0\0\0\0\0\0\0\0SIOCDARP\0SIOCGARP\0SIOCS"
"ARP\0\0\0\0\0\0\0\0\0\0\0SIOCDRARP\0SIOCGRARP\0SIOCSRARP\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCGIF"
"MAP\0SIOCSIFMAP\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCADDDLCI\0SIOCDELDLCI\0SIOCGIFVLAN"
"\0SIOCSIFVLAN\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCBONDENSLAVE\0SIOCBONDRELEASE\0SIOCBON"
"DSETHWADDR\0SIOCBONDSLAVEINFOQUERY\0SIOCBONDINFOQUERY\0SIOCBONDCHAN"
"GEACTIVE\0\0\0\0\0\0\0\0\0\0\0SIOCBRADDBR\0SIOCBRDELBR\0SIOCBRADDIF\0SIOCBRDEL"
"IF\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCSHWTSTAMP\0SIOCGHWTSTAMP";
PRIVATE char const repr_IOCTLS_89e0h[] =
"SIOCPROTOPRIVATE\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCDEVPRIVATE";
PRIVATE char const repr_IOCTLS_20004b03h[] =
"KBD_IOC_RESETKEYMAP\0KBD_IOC_FLUSHPENDING";
PRIVATE char const repr_IOCTLS_20004d07h[] =
"MOUSEIO_FLUSHPENDING";
PRIVATE char const repr_IOCTLS_20005600h[] =
"VID_IOC_ACTIVATE";
PRIVATE char const repr_IOCTLS_20006600h[] =
"FD_IOC_NOOP";
PRIVATE char const repr_IOCTLS_2000664ch[] =
"FD_IOC_DIRECTIO";
PRIVATE char const repr_IOCTLS_200066c0h[] =
"FD_IOC_INCREF\0FD_IOC_DECREF";
PRIVATE char const repr_IOCTLS_20006d12h[] =
"MOD_IOC_INIT\0MOD_IOC_FINI";
PRIVATE char const repr_IOCTLS_40000242h[] =
"FDSETMEDIAPRM\0FDDEFPRM\0\0\0\0\0FDFMTTRK\0\0\0\0FDSETMAXERRS";
PRIVATE char const repr_IOCTLS_40000290h[] =
"FDSETDRVPRM";
PRIVATE char const repr_IOCTLS_40001271h[] =
"BLKBSZSET";
PRIVATE char const repr_IOCTLS_4000542bh[] =
"TCSETS2\0TCSETSW2\0TCSETSF2\0\0\0\0TIOCSPTLCK\0\0\0\0\0TIOCSIG";
PRIVATE char const repr_IOCTLS_40007211h[] =
"FAT_IOCTL_SET_ATTRIBUTES";
PRIVATE char const repr_IOCTLS_60004b02h[] =
"KBD_IOC_SETLED\0KBD_IOC_SETKEYMAP\0\0KBD_IOC_PUTSTR\0KBD_IOC_PUTKEY\0"
"KBD_IOC_SETDBGF12\0KBD_IOC_SETMOD";
PRIVATE char const repr_IOCTLS_60004c01h[] =
"LEAKS_IOC_SETONCLOSE";
PRIVATE char const repr_IOCTLS_60004d00h[] =
"MOUSEIO_SETABSMODE\0MOUSEIO_SETABSRECT\0MOUSEIO_PUTMOTION\0MOUSEIO_"
"SETPOS\0MOUSEIO_PUTBUTTON\0MOUSEIO_PUTVWHEEL\0MOUSEIO_PUTHWHEEL";
PRIVATE char const repr_IOCTLS_60005301h[] =
"SVGA_IOC_SETMODE\0SVGA_IOC_SETDEFMODE";
PRIVATE char const repr_IOCTLS_60005400h[] =
"TTYIO_IBUF_SETLIMIT\0TTYIO_CANON_SETLIMIT\0TTYIO_OPEND_SETLIMIT\0TT"
"YIO_IPEND_SETLIMIT";
PRIVATE char const repr_IOCTLS_60005611h[] =
"VID_IOC_SETCELLDATA\0VID_IOC_SETCURSOR";
PRIVATE char const repr_IOCTLS_6000664ch[] =
"FD_IOC_SETDIRECTIO";
PRIVATE char const repr_IOCTLS_80000204h[] =
"FDGETMEDIAPRM\0\0\0\0\0\0\0\0\0\0FDGETMAXERRS\0FDGETDRVTYP\0\0FDGETDRVPRM\0FDG"
"ETDRVSTAT\0FDPOLLDRVSTAT\0\0FDGETFDCSTAT\0\0FDWERRORGET";
PRIVATE char const repr_IOCTLS_80001270h[] =
"BLKBSZGET\0\0BLKGETSIZE64";
PRIVATE char const repr_IOCTLS_8000542ah[] =
"TCGETS2\0\0\0\0\0\0TIOCGPTN\0\0TIOCGDEV\0\0\0\0\0\0TIOCGPKT\0TIOCGPTLCK\0\0\0\0\0\0\0T"
"IOCGEXCL\0\0TIOCGISO7816";
PRIVATE char const repr_IOCTLS_8000667ah[] =
"FIODTYPE";
PRIVATE char const repr_IOCTLS_80007201h[] =
"VFAT_IOCTL_READDIR_BOTH\0VFAT_IOCTL_READDIR_SHORT\0\0\0\0\0\0\0\0\0\0\0\0\0\0FA"
"T_IOCTL_GET_ATTRIBUTES\0\0\0FAT_IOCTL_GET_VOLUME_ID";
PRIVATE char const repr_IOCTLS_80008906h[] =
"SIOCGSTAMP64\0SIOCGSTAMPNS64";
PRIVATE char const repr_IOCTLS_a0004600h[] =
"FILE_IOC_DELETED\0FILE_IOC_HASRAWIO\0FILE_IOC_DCHANGED\0FILE_IOC_CH"
"ANGED\0FILE_IOC_BLKSHIFT";
PRIVATE char const repr_IOCTLS_a0004680h[] =
"FILE_IOC_GETFSLINKMAX\0FILE_IOC_GETFSNAMEMAX\0FILE_IOC_GETFSSIZBIT"
"S\0FILE_IOC_GETFSXFERINC\0FILE_IOC_GETFSXFERMAX\0FILE_IOC_GETFSXFER"
"MIN\0FILE_IOC_GETFSXFERALN\0FILE_IOC_GETFSSYMMAX";
PRIVATE char const repr_IOCTLS_a0004b00h[] =
"KBD_IOC_TRYGETKEY\0KBD_IOC_GETKEY\0KBD_IOC_MASKLED\0KBD_IOC_GETKEYM"
"AP\0\0\0\0KBD_IOC_GETDBGF12\0KBD_IOC_MASKMOD";
PRIVATE char const repr_IOCTLS_a0004c01h[] =
"LEAKS_IOC_GETONCLOSE\0LEAKS_IOC_GETCOUNT\0LEAKS_IOC_LEAKATTR\0LEAKS"
"_IOC_LEAKTB\0LEAKS_IOC_READLEAKMEM\0LEAKS_IOC_READUSERMEM";
PRIVATE char const repr_IOCTLS_a0004d00h[] =
"MOUSEIO_GETABSMODE\0MOUSEIO_GETABSRECT\0\0MOUSEIO_GETPOS\0MOUSEIO_GE"
"TBUTTONS";
PRIVATE char const repr_IOCTLS_a0005000h[] =
"PIPE_IOC_CLOSED\0PIPE_IOC_READABLE";
PRIVATE char const repr_IOCTLS_a0005300h[] =
"SVGA_IOC_MAKETTY\0SVGA_IOC_GETMODE\0SVGA_IOC_GETDEFMODE\0SVGA_IOC_L"
"SMODES\0SVGA_IOC_GETCSNAME\0SVGA_IOC_CSSTRINGS";
PRIVATE char const repr_IOCTLS_a0005400h[] =
"TTYIO_IBUF_GETLIMIT\0TTYIO_CANON_GETLIMIT\0TTYIO_OPEND_GETLIMIT\0TT"
"YIO_IPEND_GETLIMIT";
PRIVATE char const repr_IOCTLS_a0005601h[] =
"VID_IOC_MAKELCK\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0VID_IOC_GETTTYINFO\0VID_IOC_GETCELL"
"DATA\0VID_IOC_GETCURSOR";
PRIVATE char const repr_IOCTLS_a000664ch[] =
"FD_IOC_GETDIRECTIO";
PRIVATE char const repr_IOCTLS_a0006680h[] =
"FD_IOC_GETTYPE\0FD_IOC_GETKIND\0FD_IOC_GETMODE\0FD_IOC_GETADDR\0FD_I"
"OC_GETRADDR\0FD_IOC_GETREFCNT";
PRIVATE char const repr_IOCTLS_a0006d01h[] =
"MOD_IOC_GETCOUNT\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0MOD_IOC_GETSTATE\0MOD_IOC_LOADINFO";
PRIVATE char const repr_IOCTLS_a0007000h[] =
"PIDFD_IOC_GETTID\0PIDFD_IOC_GETPID\0PIDFD_IOC_GETPPID\0PIDFD_IOC_GE"
"TPGID\0PIDFD_IOC_GETSID\0\0\0\0\0PIDFD_IOC_OPENPID\0PIDFD_IOC_OPENPPID\0"
"\0\0\0\0\0PIDFD_IOC_EXITCODE";
PRIVATE char const repr_IOCTLS_c0001273h[] =
"BLKTRACESETUP";
PRIVATE char const repr_IOCTLS_c0005443h[] =
"TIOCSISO7816";
PRIVATE char const repr_IOCTLS_c0005877h[] =
"FIFREEZE\0FITHAW\0FITRIM";
PRIVATE char const repr_IOCTLS_e0004610h[] =
"FILE_IOC_MSALIGN\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0FILE_IOC_TAILREAD";
PRIVATE char const repr_IOCTLS_e0005008h[] =
"PIPE_IOC_PEEK\0PIPE_IOC_DISCARD";
PRIVATE char const repr_IOCTLS_e0006601h[] =
"FD_IOC_POLLTEST\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0FD_IOC_DUPFD\0FD_IOC_CAST\0FD_IOC_DE"
"SC";
PRIVATE char const repr_IOCTLS_e0006d00h[] =
"MOD_IOC_GETOBJECT\0\0MOD_IOC_GETSTRING";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_ioctl_command_name_raw)(syscall_ulong_t command) {
	char const *result = NULL;
	if (!GETBASE_IOCTLS(result, command))
		goto done;
	for (; command; --command)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_ioctl_command_name)(syscall_ulong_t command) {
	char const *result;
	command &= ((_IOC_NRMASK << _IOC_NRSHIFT) |
	            (_IOC_TYPEMASK << _IOC_TYPESHIFT) |
	            (_IOC_KOSMASK << _IOC_KOSSHIFT) |
	            (_IOC_DIRMASK << _IOC_DIRSHIFT));
	result = get_ioctl_command_name_raw(command);
	if (result)
		goto done;

	/* If not found with the original direct, also try different directions. */
	command &= ((_IOC_NRMASK << _IOC_NRSHIFT) |
	            (_IOC_TYPEMASK << _IOC_TYPESHIFT) |
	            (_IOC_KOSMASK << _IOC_KOSSHIFT));
	result = get_ioctl_command_name_raw(command);
	if (result)
		goto done;
	result = get_ioctl_command_name_raw(command | _IOC_IN);
	if (result)
		goto done;
	result = get_ioctl_command_name_raw(command | _IOC_OUT);
	if (result)
		goto done;
	result = get_ioctl_command_name_raw(command | _IOC_INOUT);
	/*if (result)
		goto done;*/
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_ioctl_command_size)(pformatprinter printer,
                                        void *arg, size_t size) {
	ssize_t result;
	char const *name;
	switch (size) {
	case 1:  name = "uint8_t"; break;
	case 2:  name = "uint16_t"; break;
	case 4:  name = "uint32_t"; break;
	case 8:  name = "uint64_t"; break;
	default: name = NULL; break;
	}
	if (name) {
		result = (*printer)(arg, name, strlen(name));
	} else {
		result = format_printf(printer, arg, "byte_t[%" PRIuSIZ "]", size);
	}
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_ioctl_type)(pformatprinter printer, void *arg,
                                syscall_ulong_t type) {
	ssize_t result;
	if (type <= 0x7f && isprint((int)(unsigned int)type)) {
		result = format_printf(printer, arg, "'%c'",
		                       (int)(unsigned int)type);
	} else {
		result = format_printf(printer, arg, "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		                       type);
	}
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_ioctl_command)(pformatprinter printer, void *arg,
                                   syscall_ulong_t command) {
	char const *name;
	ssize_t temp, result;
	name = get_ioctl_command_name(command);
	if (name) {
		result = (*printer)(arg, name, strlen(name));
#if __SIZEOF_SYSCALL_LONG_T__ > 4
	} else if (command > UINT32_MAX) {
		goto do_print_hex_repr;
#endif /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
	} else {
		syscall_ulong_t nr, type, size, kos, dir;
		nr   = _IOC_NR(command);
		type = _IOC_TYPE(command);
		size = _IOC_SIZE(command);
		kos  = _IOC_ISKOS(command);
		dir  = _IOC_DIR(command);
		if (dir || kos || size || type) {
			result = DOPRINT("_IO");
			if unlikely(result < 0)
				goto done;
			if (dir == _IOC_NONE) {
				if (size != 0) {
					PRINT("C");
					if (kos)
						PRINT("_KOS");
					PRINT("(_IOC_NONE," SYNSPACE);
					DO(print_ioctl_type(printer, arg, type));
					DO(format_printf(printer, arg,
					                 "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__)
					                 "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__) ")",
					                 nr, size));
					goto done;
				}
				temp = 0;
			} else if (dir == _IOC_READ) {
				temp = DOPRINT("R");
			} else if (dir == _IOC_WRITE) {
				temp = DOPRINT("W");
			} else /*if (dir == (_IOC_WRITE | _IOC_READ))*/ {
				temp = DOPRINT("WR");
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
			if (kos)
				PRINT("_KOS");
			PRINT("(");
			DO(print_ioctl_type(printer, arg, type));
			DO(format_printf(printer, arg, "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__), nr));
			if (dir != _IOC_NONE) {
				PRINT("," SYNSPACE);
				DO(print_ioctl_command_size(printer, arg, size));
			}
			PRINT(")");
		} else {
#if __SIZEOF_SYSCALL_LONG_T__ > 4
do_print_hex_repr:
#endif /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
			result = format_printf(printer, arg,
			                       "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
			                       command);
		}
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_ioctl_command */


#ifdef NEED_print_termios_iflag
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[8];
} const termios_iflag_names[] = {
	{ __IGNBRK, /* */ "IGNBRK" },
	{ __BRKINT, /* */ "BRKINT" },
	{ __IGNPAR, /* */ "IGNPAR" },
	{ __PARMRK, /* */ "PARMRK" },
	{ __INPCK, /*  */ "INPCK" },
	{ __ISTRIP, /* */ "ISTRIP" },
	{ __INLCR, /*  */ "INLCR" },
	{ __IGNCR, /*  */ "IGNCR" },
	{ __ICRNL, /*  */ "ICRNL" },
	{ __IUCLC, /*  */ "IUCLC" },
	{ __IXON, /*   */ "IXON" },
	{ __IXANY, /*  */ "IXANY" },
	{ __IXOFF, /*  */ "IXOFF" },
	{ __IMAXBEL, /**/ "IMAXBEL" },
	{ __IUTF8, /*  */ "IUTF8" },
	{ __IIOFF, /*  */ "IIOFF" },
	{ __IBAUD0, /* */ "IBAUD0" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_termios_iflag)(pformatprinter printer, void *arg, syscall_ulong_t flags) {
	if (flags == TTYDEF_IFLAG)
		return (*printer)(arg, "TTYDEF_IFLAG", COMPILER_STRLEN("TTYDEF_IFLAG"));
	return print_flagset32(printer, arg, termios_iflag_names,
	                       sizeof(*termios_iflag_names),
	                       "", flags);
}
#endif /* NEED_print_termios_iflag */


#ifdef NEED_print_termios_oflag
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[8];
} const termios_oflag_names[] = {
	{ __OPOST, /* */ "OPOST" },
	{ __OLCUC, /* */ "OLCUC" },
	{ __ONLCR, /* */ "ONLCR" },
	{ __OCRNL, /* */ "OCRNL" },
	{ __ONOCR, /* */ "ONOCR" },
	{ __ONLRET, /**/ "ONLRET" },
	{ __OFILL, /* */ "OFILL" },
	{ __OFDEL, /* */ "OFDEL" },
	{ __NL1, /*   */ "NL1" },
	{ __BS1, /*   */ "BS1" },
	{ __FF1, /*   */ "FF1" },
	{ __VT1, /*   */ "VT1" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_termios_oflag)(pformatprinter printer, void *arg, syscall_ulong_t flags) {
	ssize_t result, temp;
	if (flags == TTYDEF_OFLAG)
		return (*printer)(arg, "TTYDEF_OFLAG", COMPILER_STRLEN("TTYDEF_OFLAG"));
	result = 0;
	if (flags & __CRDLY) {
		syscall_ulong_t mask = flags & __CRDLY;
		PRINTF("CR%d" PIPESTR_S, mask == __CR1 ? 1 : mask == __CR2 ? 2 : 3);
		flags &= ~__CRDLY;
	}
	if (flags & __TABDLY) {
		syscall_ulong_t mask = flags & __TABDLY;
		PRINTF("TAB%d" PIPESTR_S, mask == __TAB1 ? 1 : mask == __TAB2 ? 2 : 3);
		flags &= ~__TABDLY;
	}
	DO(print_flagset32(printer, arg, termios_oflag_names,
	                   sizeof(*termios_oflag_names),
	                   "", flags));
	return result;
err:
	return temp;
}
#endif /* NEED_print_termios_oflag */


#ifdef NEED_print_termios_lflag
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[12];
} const termios_lflag_names[] = {
	{ __ISIG, /*     */ "ISIG" },
	{ __ICANON, /*   */ "ICANON" },
	{ __XCASE, /*    */ "XCASE" },
	{ __ECHO, /*     */ "ECHO" },
	{ __ECHOE, /*    */ "ECHOE" },
	{ __ECHOK, /*    */ "ECHOK" },
	{ __ECHONL, /*   */ "ECHONL" },
	{ __NOFLSH, /*   */ "NOFLSH" },
	{ __TOSTOP, /*   */ "TOSTOP" },
	{ __ECHOCTL, /*  */ "ECHOCTL" },
	{ __ECHOPRT, /*  */ "ECHOPRT" },
	{ __ECHOKE, /*   */ "ECHOKE" },
	{ __FLUSHO, /*   */ "FLUSHO" },
	{ __PENDIN, /*   */ "PENDIN" },
	{ __IEXTEN, /*   */ "IEXTEN" },
	{ __EXTPROC, /*  */ "EXTPROC" },
	{ __IERASING, /* */ "IERASING" },
	{ __IXCASEING, /**/ "IXCASEING" },
	{ __IEOFING, /*  */ "IEOFING" },
	{ __IESCAPING, /**/ "IESCAPING" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_termios_lflag)(pformatprinter printer, void *arg, syscall_ulong_t flags) {
	if (flags == TTYDEF_LFLAG)
		return (*printer)(arg, "TTYDEF_LFLAG", COMPILER_STRLEN("TTYDEF_LFLAG"));
	return print_flagset32(printer, arg, termios_lflag_names,
	                       sizeof(*termios_lflag_names),
	                       "", flags);
}
#endif /* NEED_print_termios_lflag */


#ifdef NEED_print_termios_cflag
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[8];
} const termios_cflag_names[] = {
	{ __CSTOPB, /* */ "CSTOPB" },
	{ __CREAD, /*  */ "CREAD" },
	{ __PARENB, /* */ "PARENB" },
	{ __PARODD, /* */ "PARODD" },
	{ __HUPCL, /*  */ "HUPCL" },
	{ __CLOCAL, /* */ "CLOCAL" },
	{ __CMSPAR, /* */ "CMSPAR" },
	{ __CRTSCTS, /**/ "CRTSCTS" },
	{ 0, "" },
};

PRIVATE unsigned int const termio_speeds[0x20] = {
	/* For: __B0       */ 0,
	/* For: __B50      */ 50,
	/* For: __B75      */ 75,
	/* For: __B110     */ 110,
	/* For: __B134     */ 134,
	/* For: __B150     */ 150,
	/* For: __B200     */ 200,
	/* For: __B300     */ 300,
	/* For: __B600     */ 600,
	/* For: __B1200    */ 1200,
	/* For: __B1800    */ 1800,
	/* For: __B2400    */ 2400,
	/* For: __B4800    */ 4800,
	/* For: __B9600    */ 9600,
	/* For: __B19200   */ 19200,
	/* For: __B38400   */ 38400,
	/* For: __BOTHER   */ 0,
	/* For: __B57600   */ 57600,
	/* For: __B115200  */ 115200,
	/* For: __B230400  */ 230400,
	/* For: __B460800  */ 460800,
	/* For: __B500000  */ 500000,
	/* For: __B576000  */ 576000,
	/* For: __B921600  */ 921600,
	/* For: __B1000000 */ 1000000,
	/* For: __B1152000 */ 1152000,
	/* For: __B1500000 */ 1500000,
	/* For: __B2000000 */ 2000000,
	/* For: __B2500000 */ 2500000,
	/* For: __B3000000 */ 3000000,
	/* For: __B3500000 */ 3500000,
	/* For: __B4000000 */ 4000000,
};

PRIVATE ATTR_CONST WUNUSED unsigned int
NOTHROW(CC get_termios_speed)(syscall_ulong_t flags) {
	if (flags & 0x00001000) {
		flags &= ~0x00001000;
		flags |= 0x10;
	}
	return termio_speeds[flags];
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_termios_cflag)(pformatprinter printer, void *arg, syscall_ulong_t flags) {
	ssize_t result, temp;
	if (flags == TTYDEF_CFLAG)
		return (*printer)(arg, "TTYDEF_CFLAG", COMPILER_STRLEN("TTYDEF_CFLAG"));
	result = 0;
	if (flags & __CSIZE) {
		syscall_ulong_t mask = flags & __CSIZE;
		PRINTF("CS%d" PIPESTR_S, mask == __CS6 ? 6 : mask == __CS7 ? 7 : 8);
		flags &= ~__CSIZE;
	}
	if (flags & __CBAUD) {
		syscall_ulong_t mask = flags & __CBAUD;
		if (mask == __CBAUDEX) {
			PRINT("CBAUDEX");
		} else {
			PRINTF("B%u" PIPESTR_S, get_termios_speed(mask));
		}
		flags &= ~__CBAUD;
	}
	if (flags & __CIBAUD) {
		syscall_ulong_t mask = (flags & __CIBAUD) >> __IBSHIFT;
		if (mask == __CBAUDEX) {
			PRINT("(CBAUDEX" SYNSPACE "<<" SYNSPACE "IBSHIFT)");
		} else {
			PRINTF("(B%u" SYNSPACE "<<" SYNSPACE "IBSHIFT)" PIPESTR_S,
			       get_termios_speed(mask));
		}
		flags &= ~__CIBAUD;
	}
	DO(print_flagset32(printer, arg, termios_cflag_names,
	                   sizeof(*termios_cflag_names),
	                   "", flags));
	return result;
err:
	return temp;
}
#endif /* NEED_print_termios_cflag */


#if defined(NEED_print_termio_common) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping(
	"../../include/asm/os/kos/termios.h", "__V",
	filter: x -> x !in { "__VTDLY", "__VT0", "__VT1" });
printStrendNDatabase("TERMIOS_V_NAME", typ);
]]]*/
#define GETBASE_TERMIOS_V_NAME(result, index) \
	(((index) <= 0x10) ? ((result) = repr_TERMIOS_V_NAME_0h, true) : false)
PRIVATE char const repr_TERMIOS_V_NAME_0h[] =
"INTR\0QUIT\0ERASE\0KILL\0EOF\0TIME\0MIN\0SWTCH\0START\0STOP\0SUSP\0EOL\0REPR"
"INT\0DISCARD\0WERASE\0LNEXT\0EOL2";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_termios_v_name)(size_t slotid) {
	char const *result = NULL;
	if (!GETBASE_TERMIOS_V_NAME(result, slotid))
		goto done;
	for (; slotid; --slotid)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}


PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_termio_common)(pformatprinter printer, void *arg,
                                       NCX struct termios const *ios,
                                       size_t nccs, bool have_speed) {
	bool is_first;
	size_t i;
	ssize_t result, temp;
#define LOCAL_HEAD "{" SYNSPACE SYNFIELD("c_iflag")
	result = (*printer)(arg, LOCAL_HEAD, COMPILER_STRLEN(LOCAL_HEAD));
#undef LOCAL_HEAD
	if unlikely(result < 0)
		goto done;
	DO(print_termios_iflag(printer, arg, ios->c_iflag));
	PRINT("," SYNSPACE SYNFIELD("c_oflag"));
	DO(print_termios_oflag(printer, arg, ios->c_oflag));
	PRINT("," SYNSPACE SYNFIELD("c_cflag"));
	DO(print_termios_cflag(printer, arg, ios->c_cflag));
	PRINT("," SYNSPACE SYNFIELD("c_lflag"));
	DO(print_termios_lflag(printer, arg, ios->c_lflag));
	PRINTF("," SYNSPACE SYNFIELD("c_line") "%" PRIu8
	       "," SYNSPACE SYNFIELD("c_cc") "[",
	       ios->c_line);
	is_first = true;
	for (i = 0; i < nccs; ++i) {
		char const *name;
		cc_t cc = ios->c_cc[i];
		if (cc == _POSIX_VDISABLE)
			continue;
		if (!is_first)
			PRINT("," SYNSPACE2);
		name = get_termios_v_name(i);
		if (name) {
			PRINTF("V%s", name);
		} else {
			PRINTF("%" PRIuSIZ, i);
		}
		PRINT(":" SYNSPACE);
		if (i == __VMIN || i == __VTIME || (cc & ~31)) {
			PRINTF("%" PRIu8, (uint8_t)cc);
		} else {
			PRINTF("^%c", '@' + cc);
		}
		is_first = false;
	}
	if (have_speed && (ios->c_ispeed || ios->c_ospeed)) {
		PRINTF("]"
		       "," SYNSPACE SYNFIELD("c_ispeed") "%" PRIu32
		       "," SYNSPACE SYNFIELD("c_ospeed") "%" PRIu32
		       "}",
		       (uint32_t)ios->c_ispeed,
		       (uint32_t)ios->c_ospeed);
	} else {
		PRINT("]}");
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_termio_common */


#ifdef NEED_print_termio
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_termio)(pformatprinter printer, void *arg,
                                NCX UNCHECKED struct termio const *ios) {
	struct termios common_ios;
	static_assert(sizeof(common_ios.c_cc[0]) == sizeof(ios->c_cc[0]));
	static_assert(COMPILER_LENOF(common_ios.c_cc) >= COMPILER_LENOF(ios->c_cc));
	validate_readable(ios, sizeof(*ios));
	common_ios.c_iflag = ios->c_iflag;
	common_ios.c_oflag = ios->c_oflag;
	common_ios.c_cflag = ios->c_cflag;
	common_ios.c_lflag = ios->c_lflag;
	common_ios.c_line  = ios->c_line;
	memcpy(common_ios.c_cc, ios->c_cc, sizeof(ios->c_cc));
	return print_termio_common(printer, arg, &common_ios, COMPILER_LENOF(ios->c_cc), false);
}
#endif /* NEED_print_termio */


#ifdef NEED_print_termios
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_termios)(pformatprinter printer, void *arg,
                                 NCX UNCHECKED struct termios const *ios) {
	validate_readable(ios, sizeof(*ios));
	return print_termio_common(printer, arg, ios, COMPILER_LENOF(ios->c_cc), true);
}
#endif /* NEED_print_termios */


#ifdef NEED_print_termios2
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_termios2)(pformatprinter printer, void *arg,
                                  NCX UNCHECKED struct termios2 const *ios) {
	struct termios common_ios;
	static_assert(sizeof(common_ios.c_cc[0]) == sizeof(ios->c_cc[0]));
	static_assert(COMPILER_LENOF(common_ios.c_cc) >= COMPILER_LENOF(ios->c_cc));
	validate_readable(ios, sizeof(*ios));
	common_ios.c_iflag = ios->c_iflag;
	common_ios.c_oflag = ios->c_oflag;
	common_ios.c_cflag = ios->c_cflag;
	common_ios.c_lflag = ios->c_lflag;
	common_ios.c_line  = ios->c_line;
	memcpy(common_ios.c_cc, ios->c_cc, sizeof(ios->c_cc));
	common_ios.c_ispeed = ios->c_ispeed;
	common_ios.c_ospeed = ios->c_ospeed;
	return print_termio_common(printer, arg, &common_ios, COMPILER_LENOF(ios->c_cc), true);
}
#endif /* NEED_print_termios2 */


#ifdef NEED_print_termiox
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_termiox)(pformatprinter printer, void *arg,
                                 NCX UNCHECKED struct termiox const *ios) {
	size_t i;
	ssize_t result, temp;
	static_assert(sizeof(ios->x_hflag) == 2);
	static_assert(sizeof(ios->x_cflag) == 2);
	static_assert(sizeof(ios->x_rflag[0]) == 2);
	static_assert(sizeof(ios->x_sflag) == 2);
	validate_readable(ios, sizeof(*ios));
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("x_hflag") "%#" PRIx16
	                       "," SYNSPACE SYNFIELD("x_cflag") "%#" PRIx16
	                       "," SYNSPACE SYNFIELD("x_rflag") "[",
	                       ios->x_hflag,
	                       ios->x_cflag);
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < COMPILER_LENOF(ios->x_rflag); ++i) {
		PRINTF("%s%#" PRIx16, i ? "," SYNSPACE2 : "", ios->x_rflag[i]);
	}
	PRINTF("]," SYNSPACE SYNFIELD("x_sflag") "%#" PRIx16
	       SYNSPACE "}",
	       ios->x_sflag);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_termiox */


#ifdef NEED_print_winsize
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_winsize)(pformatprinter printer, void *arg,
                                 NCX UNCHECKED struct winsize const *ws) {
	ssize_t result;
	static_assert(sizeof(ws->ws_row) == 2);
	static_assert(sizeof(ws->ws_col) == 2);
	static_assert(sizeof(ws->ws_xpixel) == 2);
	static_assert(sizeof(ws->ws_ypixel) == 2);
	validate_readable(ws, sizeof(*ws));
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("ws_row") "%" PRIu16
	                       "," SYNSPACE SYNFIELD("ws_col") "%" PRIu16
	                       "," SYNSPACE SYNFIELD("ws_xpixel") "%" PRIu16
	                       "," SYNSPACE SYNFIELD("ws_ypixel") "%" PRIu16
	                       SYNSPACE "}",
	                       ws->ws_row,
	                       ws->ws_col,
	                       ws->ws_xpixel,
	                       ws->ws_ypixel);
	return result;
}
#endif /* NEED_print_winsize */


#ifdef NEED_print_tty_modem_bits
PRIVATE struct {
	uint16_t   pn_flag;
	char const pn_name[6];
} const tty_modem_bit_flag_names[] = {
#ifdef __TIOCM_LE
	{ __TIOCM_LE, "LE" },
#endif /* __TIOCM_LE */
#ifdef __TIOCM_DTR
	{ __TIOCM_DTR, "DTR" },
#endif /* __TIOCM_DTR */
#ifdef __TIOCM_RTS
	{ __TIOCM_RTS, "RTS" },
#endif /* __TIOCM_RTS */
#ifdef __TIOCM_ST
	{ __TIOCM_ST, "ST" },
#endif /* __TIOCM_ST */
#ifdef __TIOCM_SR
	{ __TIOCM_SR, "SR" },
#endif /* __TIOCM_SR */
#ifdef __TIOCM_CTS
	{ __TIOCM_CTS, "CTS" },
#endif /* __TIOCM_CTS */
#ifdef __TIOCM_CAR
	{ __TIOCM_CAR, "CAR" },
#endif /* __TIOCM_CAR */
#ifdef __TIOCM_RNG
	{ __TIOCM_RNG, "RNG" },
#endif /* __TIOCM_RNG */
#ifdef __TIOCM_DSR
	{ __TIOCM_DSR, "DSR" },
#endif /* __TIOCM_DSR */
#ifdef __TIOCM_OUT1
	{ __TIOCM_OUT1, "OUT1" },
#endif /* __TIOCM_OUT1 */
#ifdef __TIOCM_OUT2
	{ __TIOCM_OUT2, "OUT2" },
#endif /* __TIOCM_OUT2 */
#ifdef __TIOCM_LOOP
	{ __TIOCM_LOOP, "LOOP" },
#endif /* __TIOCM_LOOP */
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_tty_modem_bits)(pformatprinter printer, void *arg, syscall_ulong_t flags) {
	return print_flagset16(printer, arg,
	                       tty_modem_bit_flag_names,
	                       sizeof(*tty_modem_bit_flag_names),
	                       "TIOCM_", flags);
}
#endif /* NEED_print_tty_modem_bits */


#if defined(NEED_print_tcflow_arg) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping(
	"../../include/asm/os/kos/termios.h", "__TC",
	filter: x -> x in { "__TCOOFF", "__TCOON", "__TCIOFF", "__TCION" });
printStrendNDatabase("TCFLOW_ARG", typ);
]]]*/
#define GETBASE_TCFLOW_ARG(result, index) \
	(((index) <= 0x3) ? ((result) = repr_TCFLOW_ARG_0h, true) : false)
PRIVATE char const repr_TCFLOW_ARG_0h[] =
"OOFF\0OON\0IOFF\0ION";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_tcflow_arg_name)(syscall_slong_t mode) {
	char const *result = NULL;
	if (!GETBASE_TCFLOW_ARG(result, mode))
		goto done;
	for (; mode; --mode)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_tcflow_arg)(pformatprinter printer, void *arg,
                                syscall_slong_t mode) {
	char const *name;
	name = get_tcflow_arg_name(mode);
	if (name)
		return format_printf(printer, arg, "TC_%s", name);
	return format_printf(printer, arg, "%#" PRIxPTR, mode);
}
#endif /* NEED_print_tcflow_arg */


#if defined(NEED_print_tcflush_arg) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping(
	"../../include/asm/os/kos/termios.h", "__TC",
	filter: x -> x in { "__TCIFLUSH", "__TCOFLUSH", "__TCIOFLUSH" });
printStrendNDatabase("TCFLUSH_ARG", typ);
]]]*/
#define GETBASE_TCFLUSH_ARG(result, index) \
	(((index) <= 0x2) ? ((result) = repr_TCFLUSH_ARG_0h, true) : false)
PRIVATE char const repr_TCFLUSH_ARG_0h[] =
"IFLUSH\0OFLUSH\0IOFLUSH";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_tcflush_arg_name)(syscall_slong_t mode) {
	char const *result = NULL;
	if (!GETBASE_TCFLUSH_ARG(result, mode))
		goto done;
	for (; mode; --mode)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_tcflush_arg)(pformatprinter printer, void *arg,
                                 syscall_slong_t mode) {
	char const *name;
	name = get_tcflush_arg_name(mode);
	if (name)
		return format_printf(printer, arg, "TC_%s", name);
	return format_printf(printer, arg, "%#" PRIxPTR, mode);
}
#endif /* NEED_print_tcflush_arg */



#ifdef NEED_print_ioctl_arg
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_ioctl_arg_fallback)(pformatprinter printer, void *arg,
                                            syscall_ulong_t command,
                                            NCX UNCHECKED void *io_arg) {
	ssize_t result, temp;
	if (!io_arg) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else {
		syscall_ulong_t size = _IOC_SIZE(command);
		if ((command & _IOC_IN) && (size != 0)) {
			syscall_ulong_t i;
			result = (*printer)(arg, "{" SYNSPACE, COMPILER_STRLEN("{" SYNSPACE));
			if unlikely(result < 0)
				goto done;
			validate_readable(io_arg, size);
			for (i = 0; i < size; ++i) {
				byte_t b = ((byte_t const *)io_arg)[i];
				PRINTF("%s%.2" PRIx8, i ? " " : "", b);
			}
			PRINT(SYNSPACE "}");
		} else {
			result = format_printf(printer, arg, "%#" PRIxPTR, io_arg);
		}
	}
done:
	return result;
err:
	return temp;
}

PRIVATE WUNUSED intmax_t
NOTHROW_NCX(CC print_ioctl_getarg_intptr)(syscall_ulong_t command,
                                          NCX UNCHECKED void *io_arg,
                                          size_t default_size) {
	intmax_t value;
	size_t intsize = _IOC_SIZE(command);
	if (intsize == 0)
		intsize = default_size;
	if (!IS_POWER_OF_TWO(intsize) || !intsize || intsize > sizeof(intmax_t))
		intsize = default_size;
	value = 0;
	validate_readable(io_arg, intsize);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	memcpy(&value, io_arg, intsize);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	memcpy((byte_t *)&value + sizeof(intmax_t) - intsize, io_arg, intsize);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

	/* Force sign-extension. */
	if (intsize < sizeof(intmax_t)) {
		value <<= ((sizeof(intmax_t) - intsize) * NBBY);
		value >>= ((sizeof(intmax_t) - intsize) * NBBY);
	}
	return value;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_ioctl_arg_intptr)(pformatprinter printer, void *arg,
                                          syscall_ulong_t command, NCX UNCHECKED void *io_arg,
                                          size_t default_size) {
	intmax_t value = print_ioctl_getarg_intptr(command, io_arg, default_size);
	return format_printf(printer, arg, "{" SYNSPACE "%" PRIdMAX SYNSPACE "}", value);
}

/* Mask of command-relevant bits of ioctl codes */
#undef IOCTL_CMDMASK
#define IOCTL_CMDMASK ((_IOC_NRMASK << _IOC_NRSHIFT) | (_IOC_TYPEMASK << _IOC_TYPESHIFT))

/* Check if the given `command' (when used with `ioctl(2)') *definitely* ignores its argument. */
INTERN ATTR_CONST WUNUSED bool /* "INTERN" because also used in "./sc_getdesc.c" */
NOTHROW(CC libsc_ioctl_voidarg)(syscall_ulong_t command) {
	switch (command & IOCTL_CMDMASK) {

	case (BLKRRPART & IOCTL_CMDMASK):
	case (BLKFLSBUF & IOCTL_CMDMASK):
	case (TIOCNOTTY & IOCTL_CMDMASK):
	case (TIOCVHANGUP & IOCTL_CMDMASK):
	case (FIONCLEX & IOCTL_CMDMASK):
	case (FIOCLEX & IOCTL_CMDMASK):
		return true;

	default: break;
	}
	return false;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_ioctl_arg)(pformatprinter printer, void *arg,
                                   syscall_ulong_t command, NCX UNCHECKED void *io_arg) {
	ssize_t result;
	switch (command & IOCTL_CMDMASK) {

	case (BLKSECTSET & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(u16));
		break;

	case (BLKROSET & IOCTL_CMDMASK):
	case (TIOCSSOFTCAR & IOCTL_CMDMASK):
	case (FIONBIO & IOCTL_CMDMASK):
	case (TIOCSETD & IOCTL_CMDMASK):
	case (FIOASYNC & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(int));
		break;

	case (TIOCSTI & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(char));
		break;

	case (BLKBSZSET & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(size_t));
		break;

	case (BLKRASET & IOCTL_CMDMASK):
	case (BLKFRASET & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(ulongptr_t));
		break;

	case (TIOCSPGRP & IOCTL_CMDMASK):
		result = print_ioctl_arg_intptr(printer, arg, command, io_arg, sizeof(pid_t));
		break;

	case (TCSETS & IOCTL_CMDMASK):
	case (TCSETSW & IOCTL_CMDMASK):
	case (TCSETSF & IOCTL_CMDMASK):
		result = print_termio(printer, arg, (NCX UNCHECKED struct termio const *)io_arg);
		break;

	case (TCSETA & IOCTL_CMDMASK):
	case (TCSETAW & IOCTL_CMDMASK):
	case (TCSETAF & IOCTL_CMDMASK):
		result = print_termios(printer, arg, (NCX UNCHECKED struct termios const *)io_arg);
		break;

	case (TCSETS2 & IOCTL_CMDMASK):
	case (TCSETSW2 & IOCTL_CMDMASK):
	case (TCSETSF2 & IOCTL_CMDMASK):
		result = print_termios2(printer, arg, (NCX UNCHECKED struct termios2 const *)io_arg);
		break;

	case (TCSETX & IOCTL_CMDMASK):
	case (TCSETXF & IOCTL_CMDMASK):
	case (TCSETXW & IOCTL_CMDMASK):
		result = print_termiox(printer, arg, (NCX UNCHECKED struct termiox const *)io_arg);
		break;

	case (TIOCSWINSZ & IOCTL_CMDMASK):
		result = print_winsize(printer, arg, (NCX UNCHECKED struct winsize const *)io_arg);
		break;

	case (TCSBRK & IOCTL_CMDMASK):
	case (TIOCSCTTY & IOCTL_CMDMASK):
	case (TCSBRKP & IOCTL_CMDMASK):
		result = format_printf(printer, arg, "%" PRIdPTR, (intptr_t)(syscall_slong_t)io_arg);
		break;

	case (TIOCMBIS & IOCTL_CMDMASK):
	case (TIOCMBIC & IOCTL_CMDMASK):
	case (TIOCMSET & IOCTL_CMDMASK): {
		uintmax_t value = (uintmax_t)print_ioctl_getarg_intptr(command, io_arg, sizeof(int));
		result = print_tty_modem_bits(printer, arg, (syscall_ulong_t)value);
	}	break;

	case (TCXONC & IOCTL_CMDMASK):
		result = print_tcflow_arg(printer, arg, (syscall_ulong_t)io_arg);
		break;

	case (TCFLSH & IOCTL_CMDMASK):
		result = print_tcflush_arg(printer, arg, (syscall_ulong_t)io_arg);
		break;

// TODO: ioctls from: "../../include/asm/os/kos/stropts.h",
// TODO: ioctls from: "../../include/asm/os/kos/socket-ioctls.h",
// TODO: ioctls from: "../../include/linux/kd.h",
// TODO: ioctls from: "../../include/linux/fd.h",
// TODO: ioctls from: "../../include/linux/hdreg.h",
// TODO: ioctls from: "../../include/linux/msdos_fs.h",
// TODO: ioctls from: "../../include/linux/vt.h",
// TODO: ioctls from: "../../include/kos/ioctl/" "*.h",

	default:
		if (libsc_ioctl_voidarg(command)) {
			result = (*printer)(arg, "(void)0", 7);
		} else {
			result = print_ioctl_arg_fallback(printer, arg, command, io_arg);
		}
		break;
	}
	return result;
}
#endif /* NEED_print_ioctl_arg */



#ifdef NEED_print_string_vector
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_string_vector)(pformatprinter printer, void *arg,
                                       NCX UNCHECKED char const *NCX UNCHECKED const *vector
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
                                       ,
                                       size_t sizeof_pointer
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
                                       ) {
#ifndef HAVE_STRING_VECTOR_POINTER_SIZE
	enum { sizeof_pointer = sizeof(void *) };
#endif /* !HAVE_STRING_VECTOR_POINTER_SIZE */
	ssize_t temp, result;
	if (!vector) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else {
		size_t i;
		validate_readable(vector, sizeof_pointer);
		result = (*printer)(arg, "[", 1);
		if unlikely(result < 0)
			goto done;
		for (i = 0;; ++i) {
			NCX UNCHECKED char const *string;
			TRY {
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
				if (sizeof_pointer == 4) {
					string = (NCX UNCHECKED char const *)(uintptr_t)((uint32_t *)vector)[i];
				} else {
					string = (NCX UNCHECKED char const *)(uintptr_t)((uint64_t *)vector)[i];
				}
#else /* HAVE_STRING_VECTOR_POINTER_SIZE */
				string = vector[i];
#endif /* !HAVE_STRING_VECTOR_POINTER_SIZE */
			} EXCEPT {
				if (!was_thrown(E_SEGFAULT))
					RETHROW();
				DO(print_segfault(printer, arg));
				break;
			}
			if (!string)
				break;
			if (i != 0)
				PRINT("," SYNSPACE2);
			if (i >= LIMIT_STRINGVECTOR) {
				PRINT("...");
				break;
			}
			TRY {
				DO(print_string(printer, arg, string, NULL));
			} EXCEPT {
				if (!was_thrown(E_SEGFAULT))
					RETHROW();
				DO(print_segfault(printer, arg));
			}
		}
		PRINT("]");
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_string_vector */



#if defined(NEED_print_signo_t) || defined(__DEEMON__)
#if defined(__KERNEL__) || defined(__DEEMON__) || defined(__INTELLISENSE__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;

function getSigno(filename: string, prefix: string): {string...} {
	local result = [];
	for (local macroName, macroValue: enumerateMacrosFromFile(filename)) {
		if (!macroName.startswith(prefix))
			continue;
		macroName = macroName[#prefix:];
		if (macroName in ["RTMIN", "RTMAX"])
			continue;
		if (macroName.startswith("_"))
			continue;
		macroValue = getMacroIntValue(macroValue);
		if (macroValue !is int)
			continue;
		if (macroValue >= #result)
			result.resize(macroValue + 1);
		if (result[macroValue] is none)
			result[macroValue] = macroName;
	}
	return result;
}

printStrendNDatabase("SIGNO", getSigno("../../include/asm/os/kos/signal.h", "__SIG"));

]]]*/
#define GETBASE_SIGNO(result, index) \
	(((index) <= 0x1f) ? ((result) = repr_SIGNO_0h, true) : false)
PRIVATE char const repr_SIGNO_0h[] =
"\0HUP\0INT\0QUIT\0ILL\0TRAP\0ABRT\0BUS\0FPE\0KILL\0USR1\0SEGV\0USR2\0PIPE\0ALR"
"M\0TERM\0STKFLT\0CLD\0CONT\0STOP\0TSTP\0TTIN\0TTOU\0RPC\0XCPU\0XFSZ\0VTALRM\0"
"PROF\0WINCH\0POLL\0PWR\0SYS";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_signo_name)(syscall_ulong_t signo) {
	char const *result = NULL;
	if (!GETBASE_SIGNO(result, signo))
		goto done;
	for (; signo; --signo)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#else /* __KERNEL__ || ... */
#define get_signo_name(signo) sigabbrev_np(signo)
#endif /* !__KERNEL__ && !... */

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_signo_t)(pformatprinter printer, void *arg, signo_t signo) {
	char const *name = get_signo_name(signo);
	if (name)
		return format_printf(printer, arg, "SIG%s", name);
	if (signo >= __SIGRTMIN && signo <= __SIGRTMAX) {
		return format_printf(printer, arg, "SIGRTMIN+%u",
		                     (unsigned int)(signo - __SIGRTMIN));
	} else {
		/* Fallback: Print the integer value */
		return format_printf(printer, arg, "%d", signo);
	}
}
#endif /* NEED_print_signo_t */



#if defined(NEED_print_socket_af_pf) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local sockaf = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/socket.h", "__AF_");
local sockpf = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/socket.h", "__PF_");

printStrendNDatabase("SOCKAF", sockaf);
if (sockaf == sockpf) {
	print("#define GETBASE_SOCKPF_IS_SOCKAF");
	print("#define GETBASE_SOCKPF GETBASE_SOCKAF");
} else {
	printStrendNDatabase("SOCKPF", sockpf);
}
]]]*/
#define GETBASE_SOCKAF(result, index) \
	(((index) <= 0x29) ? ((result) = repr_SOCKAF_0h, true) : false)
PRIVATE char const repr_SOCKAF_0h[] =
"UNSPEC\0LOCAL\0INET\0AX25\0IPX\0APPLETALK\0NETROM\0BRIDGE\0ATMPVC\0X25\0IN"
"ET6\0ROSE\0DECnet\0NETBEUI\0SECURITY\0KEY\0NETLINK\0PACKET\0ASH\0ECONET\0A"
"TMSVC\0RDS\0SNA\0IRDA\0PPPOX\0WANPIPE\0LLC\0IB\0MPLS\0CAN\0TIPC\0BLUETOOTH\0"
"IUCV\0RXRPC\0ISDN\0PHONET\0IEEE802154\0CAIF\0ALG\0NFC\0VSOCK\0MAX";

#define GETBASE_SOCKPF(result, index) \
	(((index) <= 0x29) ? ((result) = repr_SOCKPF_0h, true) : false)
PRIVATE char const repr_SOCKPF_0h[] =
"UNSPEC\0LOCAL\0INET\0AX25\0IPX\0APPLETALK\0NETROM\0BRIDGE\0ATMPVC\0X25\0IN"
"ET6\0ROSE\0DECnet\0NETBEUI\0SECURITY\0KEY\0ROUTE\0PACKET\0ASH\0ECONET\0ATM"
"SVC\0RDS\0SNA\0IRDA\0PPPOX\0WANPIPE\0LLC\0IB\0MPLS\0CAN\0TIPC\0BLUETOOTH\0IU"
"CV\0RXRPC\0ISDN\0PHONET\0IEEE802154\0CAIF\0ALG\0NFC\0VSOCK\0MAX";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_socket_domain_name)(syscall_ulong_t domain) {
	char const *result = NULL;
	if (!GETBASE_SOCKAF(result, domain))
		goto done;
	for (; domain; --domain)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#ifdef GETBASE_SOCKPF_IS_SOCKAF
#define get_socket_proto_name get_socket_domain_name
#else /* GETBASE_SOCKPF_IS_SOCKAF */
PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_socket_proto_name)(syscall_ulong_t proto) {
	char const *result = NULL;
	if (!GETBASE_SOCKPF(result, proto))
		goto done;
	for (; proto; --proto)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#endif /* !GETBASE_SOCKPF_IS_SOCKAF */

#endif /* NEED_print_socket_af_pf */



#ifdef NEED_print_socket_domain
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_socket_domain)(pformatprinter printer, void *arg,
                                   syscall_ulong_t domain) {
	char const *name;
	name = get_socket_domain_name(domain);
	if (name)
		return format_printf(printer, arg, "AF_%s", name);
	/* Fallback: Print the integer value */
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     domain);
}
#endif /* NEED_print_socket_domain */



#ifdef NEED_print_socket_proto
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_socket_proto)(pformatprinter printer, void *arg,
                                  syscall_ulong_t proto) {
	char const *name;
	name = get_socket_proto_name(proto);
	if (name)
		return format_printf(printer, arg, "PF_%s", name);
	/* Fallback: Print the integer value */
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     proto);
}
#endif /* NEED_print_socket_proto */



#ifdef NEED_print_socket_type_flags
struct socket_type_flag {
	uint32_t stf_flag;     /* Type flag */
	char     stf_name[12]; /* Type name */
};
PRIVATE struct socket_type_flag const socket_type_flags[] = {
	{ SOCK_NONBLOCK, "NONBLOCK" },
	{ SOCK_CLOEXEC,  "CLOEXEC" },
	{ SOCK_CLOFORK,  "CLOFORK" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_socket_type_flags)(pformatprinter printer, void *arg,
                                       syscall_ulong_t type_flags) {
	return print_flagset32(printer, arg, socket_type_flags,
	                       sizeof(*socket_type_flags),
	                       "SOCK_", type_flags);
}
#endif /* NEED_print_socket_type */



#if defined(NEED_print_socket_type) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/socket.h", "__SOCK_");
for (;;) {
	local maxkey = typ.keys > ...;
	if (maxkey < 255)
		break;
	del typ[maxkey];
}
printStrendNDatabase("SOCKTYPE", typ);
]]]*/
#define GETBASE_SOCKTYPE(result, index) \
	(((index) <= 0xa) ? ((result) = repr_SOCKTYPE_0h, true) : false)
PRIVATE char const repr_SOCKTYPE_0h[] =
"\0STREAM\0DGRAM\0RAW\0RDM\0SEQPACKET\0DCCP\0\0\0\0PACKET";
/*[[[end]]]*/


PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_socket_type_name)(syscall_ulong_t type) {
	char const *result = NULL;
	if (!GETBASE_SOCKTYPE(result, type))
		goto done;
	for (; type; --type)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_socket_type)(pformatprinter printer, void *arg,
                                 syscall_ulong_t type) {
	char const *type_name;
	ssize_t temp, result;
	type_name = get_socket_type_name(type & SOCK_TYPEMASK);
	if (type_name) {
		result = format_printf(printer, arg, "SOCK_%s", type_name);
	} else {
		result = format_printf(printer, arg, "%#x",
		                       (unsigned int)(type & SOCK_TYPEMASK));
	}
	type &= ~SOCK_TYPEMASK;
	if (type) {
		PRINT(PIPESTR);
		DO(print_socket_type_flags(printer, arg, type));
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_socket_type */



#ifdef NEED_print_sockaddr
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_sockaddr)(pformatprinter printer, void *arg,
                                  NCX struct sockaddr const *sa,
                                  socklen_t len) {
	ssize_t temp, result = 0;
	sa_family_t family = AF_UNSPEC;
	NCX byte_t const *payload_data;
	size_t payload_len = 0;
#ifdef HAVE_SYNFIELD
	char const *family_prefix;
#endif /* HAVE_SYNFIELD */
	payload_data = (NCX byte_t const *)sa + offsetafter(struct sockaddr, sa_family);
	if likely(len >= offsetafter(struct sockaddr, sa_family)) {
		payload_len = len - offsetafter(struct sockaddr, sa_family);
		family      = sa->sa_family;
	}
#ifdef HAVE_SYNFIELD
	family_prefix = "sa";
	switch (family) {
	case AF_UNIX: family_prefix = "sun"; break; /* struct sockaddr_un */
	case AF_INET: family_prefix = "sin"; break; /* struct sockaddr_in */
	default: break;
	}
	PRINTF("{" SYNSPACE SYNFIELD("%s_family"), family_prefix);
#else /* HAVE_SYNFIELD */
	PRINT("{" SYNSPACE SYNFIELD(-));
#endif /* !HAVE_SYNFIELD */
	DO(print_socket_domain(printer, arg, family));
	switch (family) {

	case AF_UNIX:
		/* struct sockaddr_un */
		PRINTF("," SYNSPACE SYNFIELD("sun_path") "%.?q",
		       payload_len, payload_data);
		break;

	case AF_INET: {
		/* struct sockaddr_in */
		char buf[INET_ADDRSTRLEN];
		NCX struct sockaddr_in const *sin;
		if unlikely(len < offsetafter(struct sockaddr_in, sin_addr))
			goto fallback;
		sin = (NCX struct sockaddr_in const *)sa;
		PRINTF("," SYNSPACE SYNFIELD("sin_port") "%" PRIu16
		       "," SYNSPACE SYNFIELD("sin_addr") "%q",
		       sin->sin_port, inet_ntoa_r(sin->sin_addr, buf));
	}	break;

	default:
fallback:
#ifdef HAVE_SYNFIELD
		PRINTF("," SYNSPACE SYNFIELD("%s_data") "{" SYNSPACE, family_prefix);
#else /* HAVE_SYNFIELD */
		PRINT("," SYNSPACE SYNFIELD(-) "{" SYNSPACE);
#endif /* !HAVE_SYNFIELD */
		DO(print_bytes(printer, arg, payload_data, payload_len));
		PRINT(SYNSPACE "}");
		break;
	}
	PRINT(SYNSPACE "}");
	return result;
err:
	return temp;
}
#endif /* NEED_print_sockaddr */



#if defined(NEED_print_seek_whence) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/stdio.h", "__SEEK_");
printStrendNDatabase("SEEK", typ);
]]]*/
#define GETBASE_SEEK(result, index) \
	(((index) <= 0x4) ? ((result) = repr_SEEK_0h, true) : false)
PRIVATE char const repr_SEEK_0h[] =
"SET\0CUR\0END\0DATA\0HOLE";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_seek_whence_name)(syscall_ulong_t whence) {
	char const *result = NULL;
	if (!GETBASE_SEEK(result, whence))
		goto done;
	for (; whence; --whence)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_seek_whence)(pformatprinter printer, void *arg,
                                 syscall_ulong_t whence) {
	char const *name;
	name = get_seek_whence_name(whence);
	if (name)
		return format_printf(printer, arg, "SEEK_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), whence);
}
#endif /* NEED_print_seek_whence */





#if defined(NEED_print_fcntl_command) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/fcntl.h", "__F_",
	filter: x -> x !in {
		"__F_RDLCK", "__F_WRLCK", "__F_UNLCK", "__F_EXLCK", "__F_SHLCK",
		"__F_OWNER_TID", "__F_OWNER_PID", "__F_OWNER_PGRP",
		"__F_LINUX_SPECIFIC_BASE", "__F_SEAL_SEAL", "__F_SEAL_SHRINK",
		"__F_SEAL_GROW", "__F_SEAL_WRITE", "__F_SEAL_FUTURE_WRITE",
	});
printStrendNDatabase("FCNTL", typ);
]]]*/
#define GETBASE_FCNTL(result, index) \
	(((index) <= 0x26) ? ((result) = repr_FCNTL_0h, true) : \
	 ((index) >= 0x400 && (index) <= 0x40e) ? ((index) -= 0x400, (result) = repr_FCNTL_400h, true) : \
	 ((index) >= 0x142b && (index) <= 0x1430) ? ((index) -= 0x142b, (result) = repr_FCNTL_142bh, true) : false)
PRIVATE char const repr_FCNTL_0h[] =
"DUPFD\0GETFD\0SETFD\0GETFL\0SETFL\0GETLK\0SETLK\0SETLKW\0SETOWN\0GETOWN\0S"
"ETSIG\0GETSIG\0GETLK64\0SETLK64\0SETLKW64\0SETOWN_EX\0GETOWN_EX\0GETOWN"
"ER_UIDS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0OFD_GETLK\0OFD_SETLK\0OFD_SETLKW";
PRIVATE char const repr_FCNTL_400h[] =
"SETLEASE\0GETLEASE\0NOTIFY\0\0\0\0DUPFD_CLOEXEC\0SETPIPE_SZ\0GETPIPE_SZ\0"
"ADD_SEALS\0GET_SEALS\0GET_RW_HINT\0SET_RW_HINT\0GET_FILE_RW_HINT\0SET"
"_FILE_RW_HINT";
PRIVATE char const repr_FCNTL_142bh[] =
"SETFL_XCH\0NEXT\0CLOSEM\0MAXFD\0DUP2FD\0DUP2FD_CLOEXEC";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_fcntl_command_name)(syscall_ulong_t cmd) {
	char const *result = NULL;
	if (!GETBASE_FCNTL(result, cmd))
		goto done;
	for (; cmd; --cmd)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_fcntl_command)(pformatprinter printer, void *arg,
                                   syscall_ulong_t cmd) {
	char const *name;
	name = get_fcntl_command_name(cmd);
	if (name)
		return format_printf(printer, arg, "F_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), cmd);
}
#endif /* NEED_print_fcntl_command */





#ifdef NEED_print_fd_flags
struct fdflag_name {
	__uint8_t fd_flag;
	char      fd_name[8];
};
PRIVATE struct fdflag_name const fdflag_names[] = {
	{ FD_CLOEXEC, "CLOEXEC" },
	{ FD_CLOFORK, "CLOFORK" },
	{ 0, "" },
};
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_fd_flags)(pformatprinter printer, void *arg,
                              syscall_ulong_t fd_flags) {
	return print_flagset8(printer, arg, fdflag_names,
	                      sizeof(*fdflag_names),
	                      "FD_", fd_flags);
}
#endif /* NEED_print_fd_flags */





#ifdef NEED_print_dn_flags
struct dn_flag_name {
	__uint32_t dfn_flag;
	char       dfn_name[12];
};
PRIVATE struct dn_flag_name const dn_flag_names[] = {
	{ DN_ACCESS, /*   */ "ACCESS" },
	{ DN_MODIFY, /*   */ "MODIFY" },
	{ DN_CREATE, /*   */ "CREATE" },
	{ DN_DELETE, /*   */ "DELETE" },
	{ DN_RENAME, /*   */ "RENAME" },
	{ DN_ATTRIB, /*   */ "ATTRIB" },
	{ DN_MULTISHOT, /**/ "MULTISHOT" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_dn_flags)(pformatprinter printer, void *arg,
                              syscall_ulong_t dn_flags) {
	return print_flagset32(printer, arg, dn_flag_names,
	                       sizeof(*dn_flag_names),
	                       "DN_", dn_flags);
}
#endif /* NEED_print_dn_flags */





#if defined(NEED_print_f_owner_type) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/fcntl.h", "__F_OWNER_");
printStrendNDatabase("F_OWNER", typ);
]]]*/
#define GETBASE_F_OWNER(result, index) \
	(((index) <= 0x2) ? ((result) = repr_F_OWNER_0h, true) : false)
PRIVATE char const repr_F_OWNER_0h[] =
"TID\0PID\0PGRP";
/*[[[end]]]*/
PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_f_owner_name)(unsigned int type) {
	char const *result = NULL;
	if (!GETBASE_FCNTL(result, type))
		goto done;
	for (; type; --type)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_f_owner_type)(pformatprinter printer, void *arg,
                                  unsigned int type) {
	char const *name;
	name = get_f_owner_name(type);
	if (name)
		return format_printf(printer, arg, "F_OWNER_%s", name);
	return format_printf(printer, arg, "%u", type);
}
#endif /* NEED_print_f_owner_type */





#ifdef NEED_print_f_lock
struct f_lock_name {
	__uint8_t f_lock;
	char      f_name[6];
};
PRIVATE struct f_lock_name const f_lock_names[] = {
	{ F_RDLCK, "RDLCK" },
	{ F_WRLCK, "WRLCK" },
	{ F_UNLCK, "UNLCK" },
	{ F_EXLCK, "EXLCK" },
	{ F_SHLCK, "SHLCK" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_f_lock)(pformatprinter printer, void *arg,
                            syscall_ulong_t lock) {
	return print_flagset8(printer, arg, f_lock_names,
	                      sizeof(*f_lock_names),
	                      "FD_", lock);
}
#endif /* NEED_print_f_lock */





#ifdef NEED_print_flock64
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_flock64)(pformatprinter printer, void *arg,
                                 NCX struct flock64 const *obj) {
	ssize_t result, temp;
	result = DOPRINT("{" SYNSPACE SYNFIELD("l_type"));
	if unlikely(result < 0)
		goto done;
	DO(print_f_lock(printer, arg, (unsigned int)obj->l_type));
	PRINT("," SYNSPACE SYNFIELD("l_whence"));
	DO(print_seek_whence(printer, arg, (unsigned int)obj->l_whence));
	DO(format_printf(printer, arg,
	                 "," SYNSPACE SYNFIELD("l_start") "%" PRIu64
	                 "," SYNSPACE SYNFIELD("l_len") "%" PRIu64
	                 "," SYNSPACE SYNFIELD("l_pid") "%" PRIuN(__SIZEOF_PID_T__)
	                 SYNSPACE "}",
	                 obj->l_start, obj->l_len, obj->l_pid));
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_flock64 */





#ifdef NEED_print_f_owner_ex
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_f_owner_ex)(pformatprinter printer, void *arg,
                                    NCX struct f_owner_ex const *obj) {
	ssize_t result, temp;
	result = DOPRINT("{" SYNSPACE SYNFIELD("type"));
	if unlikely(result < 0)
		goto done;
	DO(print_f_owner_type(printer, arg, (unsigned int)obj->type));
	DO(format_printf(printer, arg,
	                 "," SYNSPACE SYNFIELD("pid") "%" PRIuN(__SIZEOF_PID_T__)
	                 SYNSPACE "}",
	                 obj->pid));
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_f_owner_ex */





#ifdef NEED_print_fcntl_arg
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_fcntl_arg)(pformatprinter printer, void *arg,
                                   syscall_ulong_t cmd,
                                   NCX UNCHECKED void *fcntl_arg) {
	ssize_t result;
	switch (cmd) {

	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GETSIG:
	case F_GETLEASE:
	case F_GETPIPE_SZ:
	case F_NEXT:
	case F_CLOSEM:
	case F_MAXFD:
		result = (*printer)(arg, "(void)0", 7);
		break;

	case F_DUPFD:
	case F_DUPFD_CLOEXEC:
		result = format_printf(printer, arg, "%" PRIdN(__SIZEOF_FD_T__),
		                       (fd_t)(uintptr_t)fcntl_arg);
		break;

	case F_SETFL:
	case F_SETFL_XCH:
		result = print_oflag_t(printer, arg,
		                       (oflag_t)(uintptr_t)fcntl_arg,
		                       IO_SETFL_MASK);
		break;

	case F_SETFD:
		result = print_fd_flags(printer, arg,
		                        (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_SETSIG:
		result = print_signo_t(printer, arg,
		                       (signo_t)(uintptr_t)fcntl_arg);
		break;

	case F_GETLK:
	case F_OFD_GETLK:
		result = format_printf(printer, arg, "(struct flock *)%#" PRIxPTR, fcntl_arg);
		break;

#if F_GETLK != F_GETLK64
	case F_GETLK64:
		result = format_printf(printer, arg,
		                       "(struct flock64 *)%#" PRIxPTR,
		                       fcntl_arg);
		break;
#endif /* F_GETLK != F_GETLK64 */

	case F_SETLK:
	case F_SETLKW:
	case F_OFD_SETLK:
	case F_OFD_SETLKW: {
		struct flock64 lck64;
		NCX struct flock const *ulck;
		validate_readable(fcntl_arg, sizeof(struct flock));
		ulck = (NCX struct flock const *)fcntl_arg;
		lck64.l_type   = ulck->l_type;
		lck64.l_whence = ulck->l_whence;
		lck64.l_start  = ulck->l_start;
		lck64.l_len    = ulck->l_len;
		lck64.l_pid    = ulck->l_pid;
		result = print_flock64(printer, arg, &lck64);
	}	break;

#if F_GETLK != F_GETLK64
	case F_SETLK64:
	case F_SETLKW64:
		validate_readable(fcntl_arg, sizeof(struct flock64));
		result = print_flock64(printer, arg, (NCX struct flock64 const *)fcntl_arg);
		break;
#endif /* F_GETLK != F_GETLK64 */

	case F_SETOWN_EX:
		validate_readable(fcntl_arg, sizeof(struct f_owner_ex));
		result = print_f_owner_ex(printer, arg, (NCX struct f_owner_ex const *)fcntl_arg);
		break;

	case F_SETOWN:
		result = format_printf(printer, arg,
		                       "(pid_t)%" PRIuN(__SIZEOF_PID_T__),
		                       (pid_t)(uintptr_t)fcntl_arg);
		break;

	case F_GETOWN_EX:
		result = format_printf(printer, arg,
		                       "(struct f_owner_ex *)%#" PRIxPTR,
		                       fcntl_arg);
		break;

	case F_SETLEASE:
		result = print_f_lock(printer, arg, (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_NOTIFY:
		result = print_dn_flags(printer, arg, (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_SETPIPE_SZ:
		result = format_printf(printer, arg, "%" PRIuSIZ,
		                       (size_t)(uintptr_t)fcntl_arg);
		break;

	case F_DUP2FD:
	case F_DUP2FD_CLOEXEC:
		result = print_fd_t(printer, arg, (fd_t)(uintptr_t)fcntl_arg);
		break;

	default:
		result = format_printf(printer, arg, "(void *)%#" PRIxPTR, fcntl_arg);
		break;
	}
	return result;
}
#endif /* NEED_print_fcntl_arg */





#ifdef NEED_print_iovec_entry
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_iovec_entry)(pformatprinter printer, void *arg,
                                     bool print_content,
                                     NCX UNCHECKED void *iov_base,
                                     size_t iov_len) {
	ssize_t result, temp;
	result = DOPRINT("{" SYNSPACE SYNFIELD("iov_base"));
	if unlikely(result < 0)
		goto done;
	if (print_content) {
		validate_readable(iov_base, iov_len);
		DO(print_string_or_buffer(printer, arg,
		                          (NCX char const *)iov_base,
		                          iov_len));
	} else {
		PRINTF("%#" PRIxPTR, iov_base);
	}
	PRINTF("," SYNSPACE SYNFIELD("iov_len") "%" PRIuSIZ SYNSPACE "}",
	       iov_len);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_iovec_entry */





#if defined(NEED_print_iovecx32) || defined(NEED_print_iovecx64)
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_iovec_n)(pformatprinter printer, void *arg, bool print_content,
#if defined(NEED_print_iovecx32) && defined(NEED_print_iovecx64)
#define print_iovecx32(printer, arg, print_content, iov, count) \
	print_iovec_n(printer, arg, print_content, iov, count, sizeof(struct iovecx32))
#define print_iovecx64(printer, arg, print_content, iov, count) \
	print_iovec_n(printer, arg, print_content, iov, count, sizeof(struct iovecx64))
                                 NCX void const *iov,
                                 size_t count,
                                 size_t iov_ent_size
#elif defined(NEED_print_iovecx32)
#define print_iovecx32 print_iovec_n
                                 NCX struct iovecx32 const *iov,
                                 size_t count
#else /* ... */
#define print_iovecx64 print_iovec_n
                                 NCX struct iovecx64 const *iov,
                                 size_t count
#endif /* !... */
                                 ) {
	size_t used_count = count;
	ssize_t temp, result;
	if (used_count > LIMIT_IOVEC)
		used_count = LIMIT_IOVEC;
	result = (*printer)(arg, "[", 1);
	if unlikely(result < 0)
		goto done;
	TRY {
		size_t i;
		for (i = 0; i < used_count; ++i) {
			void *iov_base;
			size_t iov_len;
			if (i != 0)
				PRINT("," SYNSPACE2);
#if defined(NEED_print_iovecx32) && defined(NEED_print_iovecx64)
			if (iov_ent_size == sizeof(struct iovecx32)) {
				iov_base = (void *)((struct iovecx32 *)iov)[i].iov_base;
				iov_len  = (size_t)((struct iovecx32 *)iov)[i].iov_len;
			} else {
				iov_base = (void *)((struct iovecx64 *)iov)[i].iov_base;
				iov_len  = (size_t)((struct iovecx64 *)iov)[i].iov_len;
			}
#else /* NEED_print_iovecx32 && NEED_print_iovecx64 */
			iov_base = (void *)iov[i].iov_base;
			iov_len  = (size_t)iov[i].iov_len;
#endif /* !NEED_print_iovecx32 || !NEED_print_iovecx64 */
			DO(print_iovec_entry(printer, arg, print_content, iov_base, iov_len));
		}
	} EXCEPT {
		if (!was_thrown(E_SEGFAULT))
			RETHROW();
		DO(print_segfault(printer, arg));
	}
	if (used_count < count)
		PRINT("," SYNSPACE2 "...");
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_iovecx32 || NEED_print_iovecx64 */





#ifdef NEED_print_fdset
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_fdset)(pformatprinter printer, void *arg,
                               NCX fd_set const *set,
                               size_t nfds) {
	size_t would_print_count = 0;
	ssize_t temp, result;
	result = (*printer)(arg, "[", 1);
	if unlikely(result < 0)
		goto done;
	TRY {
		size_t firstfd;
		for (firstfd = 0; firstfd < nfds;) {
			if (!FD_ISSET((fd_t)firstfd, set)) {
				 ++firstfd;
				continue;
			}
			if (would_print_count < LIMIT_NFDS) {
				size_t lastfd = firstfd;
				while (lastfd < nfds && FD_ISSET((fd_t)(lastfd + 1), set))
					++lastfd;
				if (would_print_count != 0)
					PRINT("," SYNSPACE2);
				if (lastfd >= firstfd + 2) {
					PRINTF("%" PRIuSIZ ".." "%" PRIuSIZ,
					       firstfd, lastfd);
				} else {
					DO(print_fd_t(printer, arg, (fd_t)firstfd));
					lastfd = firstfd;
				}
				firstfd = lastfd + 1;
			}
			++would_print_count;
		}
	} EXCEPT {
		if (!was_thrown(E_SEGFAULT))
			RETHROW();
		DO(print_segfault(printer, arg));
	}
	if (would_print_count > LIMIT_NFDS)
		PRINT("," SYNSPACE2 "...");
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_fdset */





#ifdef NEED_print_msg_flags
struct msg_flag {
	uint32_t mf_flag;
	char     mf_name[12];
};
PRIVATE struct msg_flag const msg_flag_names[] = {
	{ MSG_OOB,          "OOB" },
	{ MSG_PEEK,         "PEEK" },
	{ MSG_DONTROUTE,    "DONTROUTE" },
	{ MSG_CTRUNC,       "CTRUNC" },
	{ MSG_PROXY,        "PROXY" },
	{ MSG_TRUNC,        "TRUNC" },
	{ MSG_DONTWAIT,     "DONTWAIT" },
	{ MSG_EOR,          "EOR" },
	{ MSG_WAITALL,      "WAITALL" },
	{ MSG_FIN,          "FIN" },
	{ MSG_SYN,          "SYN" },
	{ MSG_CONFIRM,      "CONFIRM" },
	{ MSG_RST,          "RST" },
	{ MSG_ERRQUEUE,     "ERRQUEUE" },
	{ MSG_NOSIGNAL,     "NOSIGNAL" },
	{ MSG_MORE,         "MORE" },
	{ MSG_WAITFORONE,   "WAITFORONE" },
	{ MSG_FASTOPEN,     "FASTOPEN" },
	{ MSG_CMSG_CLOEXEC, { 'C', 'M', 'S', 'G', '_', 'C', 'L', 'O', 'E', 'X', 'E', 'C' } },
	{ MSG_CMSG_CLOFORK, { 'C', 'M', 'S', 'G', '_', 'C', 'L', 'O', 'F', 'O', 'R', 'K' } },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_msg_flags)(pformatprinter printer, void *arg,
                               syscall_ulong_t msg_flags,
                               syscall_ulong_t valid_flags) {
	ssize_t temp, result = 0;
	unsigned int i;
	bool is_first = true;
	for (i = 0; i < lengthof(msg_flag_names); ++i) {
		if (!(msg_flags & msg_flag_names[i].mf_flag))
			continue;
		if (!(valid_flags & msg_flag_names[i].mf_flag))
			continue;
		PRINTF("%s%.12s",
		       is_first ? "" : PIPESTR,
		       msg_flag_names[i].mf_name);
		msg_flags &= ~msg_flag_names[i].mf_flag;
		is_first = false;
	}
	if (msg_flags || is_first) {
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, msg_flags);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_msg_flags */





#if defined(NEED_print_sockopt_level) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/socket.h", "__SOL_");
printStrendNDatabase("SOL", typ);
]]]*/
#define GETBASE_SOL(result, index) \
	(((index) <= 0x1) ? ((result) = repr_SOL_0h, true) : \
	 ((index) >= 0xff && (index) <= 0x10a) ? ((index) -= 0xff, (result) = repr_SOL_ffh, true) : false)
PRIVATE char const repr_SOL_0h[] =
"\0SOCKET";
PRIVATE char const repr_SOL_ffh[] =
"RAW\0\0\0\0\0\0DECNET\0X25\0PACKET\0ATM\0AAL\0IRDA";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_sol_name)(syscall_ulong_t level) {
	char const *result = NULL;
	if (!GETBASE_SOL(result, level))
		goto done;
	for (; level; --level)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_sockopt_level)(pformatprinter printer, void *arg,
                                   syscall_ulong_t level) {
	char const *name;
	name = get_sol_name(level);
	if (name)
		return format_printf(printer, arg, "SOL_%s", name);
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     level);
}
#endif /* NEED_print_sockopt_level */





#if defined(NEED_print_sockopt_optname) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/socket.h", "__SO_");
printStrendNDatabase("SOCKET_SO", typ);
]]]*/
#define GETBASE_SOCKET_SO(result, index) \
	(((index) <= 0x48) ? ((result) = repr_SOCKET_SO_0h, true) : \
	 ((index) >= 0x400 && (index) <= 0x401) ? ((index) -= 0x400, (result) = repr_SOCKET_SO_400h, true) : false)
PRIVATE char const repr_SOCKET_SO_0h[] =
"\0DEBUG\0REUSEADDR\0TYPE\0ERROR\0DONTROUTE\0BROADCAST\0SNDBUF\0RCVBUF\0KE"
"EPALIVE\0OOBINLINE\0NO_CHECK\0PRIORITY\0LINGER\0BSDCOMPAT\0REUSEPORT\0P"
"ASSCRED\0PEERCRED\0RCVLOWAT\0SNDLOWAT\0RCVTIMEO_OLD\0SNDTIMEO_OLD\0SEC"
"URITY_AUTHENTICATION\0SECURITY_ENCRYPTION_TRANSPORT\0SECURITY_ENCR"
"YPTION_NETWORK\0BINDTODEVICE\0ATTACH_FILTER\0DETACH_FILTER\0PEERNAME"
"\0TIMESTAMP_OLD\0ACCEPTCONN\0PEERSEC\0SNDBUFFORCE\0RCVBUFFORCE\0PASSSE"
"C\0TIMESTAMPNS_OLD\0MARK\0TIMESTAMPING_OLD\0PROTOCOL\0DOMAIN\0RXQ_OVFL"
"\0WIFI_STATUS\0PEEK_OFF\0NOFCS\0LOCK_FILTER\0SELECT_ERR_QUEUE\0BUSY_PO"
"LL\0MAX_PACING_RATE\0BPF_EXTENSIONS\0INCOMING_CPU\0ATTACH_BPF\0ATTACH"
"_REUSEPORT_CBPF\0ATTACH_REUSEPORT_EBPF\0CNX_ADVICE\0\0MEMINFO\0INCOMI"
"NG_NAPI_ID\0COOKIE\0\0PEERGROUPS\0ZEROCOPY\0TXTIME\0BINDTOIFINDEX\0TIME"
"STAMP\0TIMESTAMPNS_NEW\0TIMESTAMPING_NEW\0RCVTIMEO\0SNDTIMEO_NEW\0DET"
"ACH_REUSEPORT_BPF\0PREFER_BUSY_POLL\0BUSY_POLL_BUDGET\0NETNS_COOKIE"
"\0BUF_LOCK";
PRIVATE char const repr_SOCKET_SO_400h[] =
"NOSIGPIPE\0DONTWAIT";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_socket_so_name)(syscall_ulong_t name) {
	char const *result = NULL;
	if (!GETBASE_SOCKET_SO(result, name))
		goto done;
	for (; name; --name)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_sockopt_optname)(pformatprinter printer, void *arg,
                                     syscall_ulong_t level,
                                     syscall_ulong_t optname) {
	char const *name;
	switch (level) {

	case SOL_SOCKET:
		name = get_socket_so_name(optname);
		break;

	default:
		name = NULL;
		break;
	}
	if (name)
		return format_printf(printer, arg, "SO_%s", name);
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     optname);
}
#endif /* NEED_print_sockopt_optname */





#ifdef NEED_print_sigset
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_sigset)(pformatprinter printer, void *arg,
                                NCX UNCHECKED sigset_t const *sigset,
                                size_t sigsetsize) {
	__CRT_PRIVATE_UINT(__SIZEOF_SIGNO_T__) signo_limit;
	signo_t signo_max = NSIG - 1;
	ssize_t temp, result = 0;
	bool has_prefix = false;
	bool is_first   = true;
	if (!OVERFLOW_UMUL(sigsetsize, NBBY, &signo_limit) &&
	    signo_max > (signo_t)(signo_limit + 1))
		signo_max = (signo_t)(signo_limit + 1);
	TRY {
		bool inverse;
		signo_t signo;
		unsigned int count, inverse_count;
		validate_readable(sigset, sigsetsize);
		/* Check if we should print the inverse of the bitset. */
		for (count = 0, signo = 1; signo <= signo_max; ++signo) {
			if (!sigismember(sigset, signo))
				continue;
			if (signo >= __SIGRTMIN) {
				unsigned int n = 1; /* Special handling for grouping SIGRT* signals. */
				while (((signo_t)(signo + n) <= signo_max) && sigismember(sigset, signo))
					++n;
				signo += (n - 1); /* -1 because of the `++signo' on the for-expression above. */
			}
			++count;
		}
		for (inverse_count = 0, signo = 1; signo <= signo_max; ++signo) {
			if (sigismember(sigset, signo))
				continue;
			if (signo >= __SIGRTMIN) {
				unsigned int n = 1; /* Special handling for grouping SIGRT* signals. */
				while (((signo_t)(signo + n) <= signo_max) && !sigismember(sigset, signo))
					++n;
				signo += (n - 1); /* -1 because of the `++signo' on the for-expression above. */
			}
			++inverse_count;
		}
		inverse = inverse_count < count;
		result = inverse
		         ? DOPRINT("~{" SYNSPACE)
		         : DOPRINT("{" SYNSPACE);
		if unlikely(result < 0)
			goto done;
		has_prefix = true;
		count      = 0;
		for (signo = 1; signo <= signo_max; ++signo) {
			if ((sigismember(sigset, signo) != 0) == inverse)
				continue;
			if (!is_first)
				PRINT("," SYNSPACE2);
			if (count >= 64) {
				PRINT("...");
				break;
			}
			if (signo >= __SIGRTMIN) {
				/* Special handling for grouping SIGRT* signals. */
				unsigned int n = 1;
				while (((signo_t)(signo + n) <= signo_max) &&
				       ((sigismember(sigset, signo) != 0) != inverse))
					++n;
				if (n >= 2) {
					DO(format_printf(printer, arg, "SIGRTMIN+[%u..%u]",
					                 (unsigned int)(signo - __SIGRTMIN),
					                 (unsigned int)(signo + n - 1 - __SIGRTMIN)));
					signo += (n - 1); /* -1 because of the `++signo' on the for-expression above. */
					goto do_continue;
				}
			}
			DO(print_signo_t(printer, arg, signo));
do_continue:
			++count;
			is_first = false;
		}
	} EXCEPT {
		if (!was_thrown(E_SEGFAULT))
			RETHROW();
		if (!is_first)
			PRINT("," SYNSPACE2);
		DO(print_segfault(printer, arg));
	}
	if (has_prefix)
		PRINT(SYNSPACE "}");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_sigset */





#ifdef NEED_print_sigmask_sigset_and_len
#undef NEED_print_sigmask_sigset_and_len_sizearg
#undef NEED_print_sigmask_sigset_and_len_x32
#undef NEED_print_sigmask_sigset_and_len_x64
#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE
#if __SIZEOF_POINTER__ == 4
#define NEED_print_sigmask_sigset_and_len_x32
#elif __SIZEOF_POINTER__ == 8
#define NEED_print_sigmask_sigset_and_len_x64
#else /* __SIZEOF_POINTER__ == ... */
#define NEED_print_sigmask_sigset_and_len_misc
#define NEED_print_sigmask_sigset_and_len_sizearg
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE */
#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32
#define NEED_print_sigmask_sigset_and_len_x32
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32 */
#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64
#define NEED_print_sigmask_sigset_and_len_x64
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64 */
#if (defined(NEED_print_sigmask_sigset_and_len_x32) && \
     defined(NEED_print_sigmask_sigset_and_len_x64))
#define NEED_print_sigmask_sigset_and_len_sizearg
#endif /* NEED_print_sigmask_sigset_and_len_x(32|64) */

#ifdef NEED_print_sigmask_sigset_and_len_misc
#define IF_NEED_print_sigmask_sigset_and_len_misc(...) __VA_ARGS__
#else /* NEED_print_sigmask_sigset_and_len_misc */
#define IF_NEED_print_sigmask_sigset_and_len_misc(...) /* nothing */
#endif /* !NEED_print_sigmask_sigset_and_len_misc */

#ifdef NEED_print_sigmask_sigset_and_len_sizearg
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_sigmask_sigset_and_len)(pformatprinter printer, void *arg,
                                                NCX void *ptr,
                                                size_t sizeof_pointer)
#else /* NEED_print_sigmask_sigset_and_len_sizearg */
#define print_sigmask_sigset_and_len(printer, arg, ptr, sizeof_pointer) \
	print_sigmask_sigset_and_len_impl(printer, arg, ptr)
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_sigmask_sigset_and_len_impl)(pformatprinter printer, void *arg,
                                                     NCX void *ptr)
#endif /* !NEED_print_sigmask_sigset_and_len_sizearg */
{
	ssize_t temp, result;
	NCX UNCHECKED sigset_t const *ss_ptr;
	size_t ss_len;
	/* Extract the sigset pointer and length from the user-provided argument extension. */
#ifdef NEED_print_sigmask_sigset_and_len_sizearg
#ifdef NEED_print_sigmask_sigset_and_len_x32
	if (sizeof_pointer == 4) {
		ss_ptr = (NCX UNCHECKED sigset_t const *)(uintptr_t)(*(uint32_t NCX const *)((byte_t *)ptr + 0));
		ss_len = (size_t)(*(uint32_t NCX const *)((byte_t *)ptr + 4));
	} else
#endif /* NEED_print_sigmask_sigset_and_len_x32 */
#ifdef NEED_print_sigmask_sigset_and_len_x64
	IF_NEED_print_sigmask_sigset_and_len_misc(if (sizeof_pointer == 8)) {
		ss_ptr = (NCX UNCHECKED sigset_t const *)(uintptr_t)(*(uint64_t NCX const *)((byte_t *)ptr + 0));
		ss_len = (size_t)(*(uint64_t NCX const *)((byte_t *)ptr + 8));
	}
	IF_NEED_print_sigmask_sigset_and_len_misc(else)
#endif /* NEED_print_sigmask_sigset_and_len_x64 */
#ifdef NEED_print_sigmask_sigset_and_len_misc
	{
		ss_ptr = *(NCX UNCHECKED sigset_t const *NCX const *)((byte_t *)ptr + 0);
		ss_len = *(size_t NCX const *)((byte_t *)ptr + sizeof(void *));
	}
#endif /* NEED_print_sigmask_sigset_and_len_misc */
#else /* NEED_print_sigmask_sigset_and_len_sizearg */
	ss_ptr = *(NCX UNCHECKED sigset_t const *NCX const *)((byte_t *)ptr + 0);
	ss_len = *(size_t NCX const *)((byte_t *)ptr + sizeof(void *));
#endif /* !NEED_print_sigmask_sigset_and_len_sizearg */
	result = DOPRINT("{" SYNSPACE SYNFIELD("ss_ptr"));
	if unlikely(result < 0)
		goto done;
	/* Print the pointed-to sigset. */
	if (!ss_ptr) {
		temp = DOPRINT("NULL");
	} else {
		temp = print_sigset(printer, arg, ss_ptr, ss_len);
	}
	if unlikely(temp < 0)
		goto err;
	result += temp;
	PRINTF("," SYNSPACE SYNFIELD("ss_len") "%" PRIuSIZ SYNSPACE "}",
	       ss_len);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_sigmask_sigset_and_len */





#ifdef NEED_print_mmap_prot
#if PROT_MASK <= 0xff
typedef uint8_t mmap_prot_t;
#elif PROT_MASK <= 0xffff
typedef uint16_t mmap_prot_t;
#elif PROT_MASK <= 0xffffffff
typedef uint32_t mmap_prot_t;
#else /* PROT_MASK <= ... */
typedef uint64_t mmap_prot_t;
#endif /* PROT_MASK > ... */
struct mmap_prot_flag {
	mmap_prot_t mpf_flag;    /* The mmap prot flag */
	char        mpf_name[7]; /* Flag name. */
};

PRIVATE struct mmap_prot_flag const mmap_prot_flags[] = {
#if defined(PROT_NONE) && PROT_NONE != 0
	{ PROT_NONE,  "NONE" },
#endif /* PROT_NONE && PROT_NONE != 0 */
#if defined(PROT_EXEC) && PROT_EXEC != 0
	{ PROT_EXEC,  "EXEC" },
#endif /* PROT_EXEC && PROT_EXEC != 0 */
#if defined(PROT_WRITE) && PROT_WRITE != 0
	{ PROT_WRITE, "WRITE" },
#endif /* PROT_WRITE && PROT_WRITE != 0 */
#if defined(PROT_READ) && PROT_READ != 0
	{ PROT_READ,  "READ" },
#endif /* PROT_READ && PROT_READ != 0 */
#if defined(PROT_SEM) && PROT_SEM != 0
	{ PROT_SEM,   "SEM" },
#endif /* PROT_SEM && PROT_SEM != 0 */
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_mmap_prot)(pformatprinter printer, void *arg,
                               syscall_ulong_t prot) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0; i < lengthof(mmap_prot_flags); ++i) {
		if (!(prot & mmap_prot_flags[i].mpf_flag))
			continue;
		PRINTF("%sPROT_%s",
		       is_first ? "" : PIPESTR,
		       mmap_prot_flags[i].mpf_name);
		prot &= ~mmap_prot_flags[i].mpf_flag;
		is_first = false;
	}
#if defined(PROT_NONE) && PROT_NONE == 0
	if (is_first) {
		PRINT("PROT_NONE");
		is_first = false;
	}
#endif /* PROT_NONE && PROT_NONE == 0 */
	if unlikely(prot) {
		/* Print unknown flags. */
#if !defined(PROT_NONE) || PROT_NONE != 0
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, prot);
#else /* !PROT_NONE || PROT_NONE != 0 */
		PRINTF(PIPESTR_S "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__), prot);
#endif /* PROT_NONE && PROT_NONE == 0 */
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_mmap_prot */





#ifdef NEED_print_mmap_flags
struct mmap_flag {
	uint32_t mf_flag;     /* The mmap prot flag */
	char     mf_name[16]; /* Flag name. */
};

PRIVATE struct mmap_flag const mmap_flags[] = {
#if defined(MAP_SHARED) && MAP_SHARED != 0
	{ MAP_SHARED,        "SHARED" },
#endif /* MAP_SHARED && MAP_SHARED != 0 */
#if defined(MAP_PRIVATE) && MAP_PRIVATE != 0
	{ MAP_PRIVATE,       "PRIVATE" },
#endif /* MAP_PRIVATE && MAP_PRIVATE != 0 */
#if defined(MAP_FIXED) && MAP_FIXED != 0
	{ MAP_FIXED,         "FIXED" },
#endif /* MAP_FIXED && MAP_FIXED != 0 */
#if defined(MAP_TYPE) && MAP_TYPE != 0
	{ MAP_TYPE,          "TYPE" },
#endif /* MAP_TYPE && MAP_TYPE != 0 */
#if defined(MAP_FILE) && MAP_FILE != 0
	{ MAP_FILE,          "FILE" },
#endif /* MAP_FILE && MAP_FILE != 0 */
#if defined(MAP_ANON) && MAP_ANON != 0
	{ MAP_ANON,          "ANON" },
#endif /* MAP_ANON && MAP_ANON != 0 */
#if defined(MAP_32BIT) && MAP_32BIT != 0
	{ MAP_32BIT,         "32BIT" },
#endif /* MAP_32BIT && MAP_32BIT != 0 */
#if defined(MAP_GROWSDOWN) && MAP_GROWSDOWN != 0
	{ MAP_GROWSDOWN,     "GROWSDOWN" },
#endif /* MAP_GROWSDOWN && MAP_GROWSDOWN != 0 */
#if defined(MAP_GROWSUP) && MAP_GROWSUP != 0
	{ MAP_GROWSUP,       "GROWSUP" },
#endif /* MAP_GROWSUP && MAP_GROWSUP != 0 */
#if defined(MAP_DENYWRITE) && MAP_DENYWRITE != 0
	{ MAP_DENYWRITE,     "DENYWRITE" },
#endif /* MAP_DENYWRITE && MAP_DENYWRITE != 0 */
#if defined(MAP_EXECUTABLE) && MAP_EXECUTABLE != 0
	{ MAP_EXECUTABLE,    "EXECUTABLE" },
#endif /* MAP_EXECUTABLE && MAP_EXECUTABLE != 0 */
#if defined(MAP_LOCKED) && MAP_LOCKED != 0
	{ MAP_LOCKED,        "LOCKED" },
#endif /* MAP_LOCKED && MAP_LOCKED != 0 */
#if defined(MAP_NORESERVE) && MAP_NORESERVE != 0
	{ MAP_NORESERVE,     "NORESERVE" },
#endif /* MAP_NORESERVE && MAP_NORESERVE != 0 */
#if defined(MAP_POPULATE) && MAP_POPULATE != 0
	{ MAP_POPULATE,      "POPULATE" },
#endif /* MAP_POPULATE && MAP_POPULATE != 0 */
#if defined(MAP_NONBLOCK) && MAP_NONBLOCK != 0
	{ MAP_NONBLOCK,      "NONBLOCK" },
#endif /* MAP_NONBLOCK && MAP_NONBLOCK != 0 */
#if defined(MAP_STACK) && MAP_STACK != 0
	{ MAP_STACK,         "STACK" },
#endif /* MAP_STACK && MAP_STACK != 0 */
#if defined(MAP_SYNC) && MAP_SYNC != 0
	{ MAP_SYNC,          "SYNC" },
#endif /* MAP_SYNC && MAP_SYNC != 0 */
#if defined(MAP_HUGETLB) && MAP_HUGETLB != 0
	{ MAP_HUGETLB,       "HUGETLB" },
#endif /* MAP_HUGETLB && MAP_HUGETLB != 0 */
#if defined(MAP_UNINITIALIZED) && MAP_UNINITIALIZED != 0
	{ MAP_UNINITIALIZED, "UNINITIALIZED" },
#endif /* MAP_UNINITIALIZED && MAP_UNINITIALIZED != 0 */
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_mmap_flags)(pformatprinter printer, void *arg,
                                syscall_ulong_t flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0; i < lengthof(mmap_flags); ++i) {
		if (!(flags & mmap_flags[i].mf_flag))
			continue;
		PRINTF("%sMAP_%s",
		       is_first ? "" : PIPESTR,
		       mmap_flags[i].mf_name);
		flags &= ~mmap_flags[i].mf_flag;
		is_first = false;
	}
#ifdef MAP_HUGE_MASK
	if ((flags & ((syscall_ulong_t)MAP_HUGE_MASK << MAP_HUGE_SHIFT)) != 0) {
		syscall_ulong_t hv;
		hv = (flags >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK;
		/* Print unknown flags. */
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__)
		       SYNSPACE "<<" SYNSPACE "MAP_HUGE_SHIFT",
		       is_first ? "" : PIPESTR, hv);
		is_first = false;
		flags &= ~((syscall_ulong_t)MAP_HUGE_MASK << MAP_HUGE_SHIFT);
	}
#endif /* MAP_HUGE_MASK */
	if unlikely(flags) {
		/* Print unknown flags. */
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, flags);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_mmap_flags */





#ifdef NEED_print_kreaddir_mode
static_assert(READDIR_DEFAULT == 0);
static_assert(READDIR_CONTINUE == 1);
static_assert(READDIR_PEEK == 2);
static_assert(READDIR_MULTIPLE == 3);
static_assert(READDIR_MODEMAX == 3);
PRIVATE char const repr_READDIR_0h[] =
"DEFAULT\0CONTINUE\0PEEK\0MULTIPLE";

PRIVATE ATTR_PURE WUNUSED char const *
NOTHROW(CC get_readdir_mode)(unsigned int mode) {
	char const *result;
	if unlikely(mode > READDIR_MODEMAX)
		return NULL;
	result = repr_READDIR_0h;
	while (mode) {
		--mode;
		result = strend(result) + 1;
	}
	return result;
}

struct readdir_flag {
	uint16_t rf_flag;    /* Flag value */
	char     rf_name[8]; /* Flag name */
};

PRIVATE struct readdir_flag const readdir_flags[] = {
	{ READDIR_SKIPREL, "SKIPREL" },
	{ READDIR_WANTEOF, "WANTEOF" }
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_kreaddir_mode)(pformatprinter printer, void *arg,
                                   unsigned int mode) {
	ssize_t temp, result;
	unsigned int mode_id, i;
	char const *mode_name;
	mode_id   = mode & READDIR_MODEMASK;
	mode_name = get_readdir_mode(mode_id);
	mode &= ~READDIR_MODEMASK;
	result = mode_name ? format_printf(printer, arg, "READDIR_%s", mode_name)
	                   : format_printf(printer, arg, "%#x", mode_id);
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < lengthof(readdir_flags); ++i) {
		if (!(mode & readdir_flags[i].rf_flag))
			continue;
		PRINTF(PIPESTR_S "READDIR_%s",
		       readdir_flags[i].rf_name);
		mode &= ~readdir_flags[i].rf_flag;
	}
	if unlikely(mode)
		PRINTF(PIPESTR_S "%#x", mode);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_kreaddir_mode */





#ifdef NEED_print_sigaction_flags
struct sigaction_flag {
	uint32_t sf_flag;     /* The sigaction flag */
	char     sf_name[12]; /* Flag name. */
};

PRIVATE struct sigaction_flag const sigaction_flags[] = {
#ifdef SA_NOCLDSTOP
	{ SA_NOCLDSTOP, "NOCLDSTOP" },
#endif /* SA_NOCLDSTOP */
#ifdef SA_NOCLDWAIT
	{ SA_NOCLDWAIT, "NOCLDWAIT" },
#endif /* SA_NOCLDWAIT */
#ifdef SA_SIGINFO
	{ SA_SIGINFO,   "SIGINFO" },
#endif /* SA_SIGINFO */
#ifdef SA_RESTORER
	{ SA_RESTORER,  "RESTORER" },
#endif /* SA_RESTORER */
#ifdef SA_ONSTACK
	{ SA_ONSTACK,   "ONSTACK" },
#endif /* SA_ONSTACK */
#ifdef SA_RESTART
	{ SA_RESTART,   "RESTART" },
#endif /* SA_RESTART */
#ifdef SA_NODEFER
	{ SA_NODEFER,   "NODEFER" },
#endif /* SA_NODEFER */
#ifdef SA_RESETHAND
	{ SA_RESETHAND, "RESETHAND" },
#endif /* SA_RESETHAND */
#ifdef SA_INTERRUPT
	{ SA_INTERRUPT, "INTERRUPT" },
#endif /* SA_INTERRUPT */
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_sigaction_flags)(pformatprinter printer, void *arg,
                                     syscall_ulong_t flags) {
	return print_flagset32(printer, arg, sigaction_flags,
	                       sizeof(*sigaction_flags),
	                       "SA_", flags);
}
#endif /* NEED_print_sigaction_flags */





#ifdef NEED_print_sigaction
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_sigaction)(pformatprinter printer, void *arg,
                                   NCX UNCHECKED void *sa_handler,
                                   NCX sigset_t *sa_mask, size_t sigsetsize,
                                   syscall_ulong_t sa_flags,
                                   NCX UNCHECKED void *sa_restorer) {
	ssize_t temp, result;
	result = DOPRINT("{" SYNSPACE SYNFIELD("sa_handler"));
	if unlikely(result < 0)
		goto done;
	DO(print_sighandler_t(printer, arg, sa_handler));
	PRINT("," SYNSPACE SYNFIELD("sa_mask"));
	DO(print_sigset(printer, arg, sa_mask, sigsetsize));
	PRINT("," SYNSPACE SYNFIELD("sa_flags"));
	DO(print_sigaction_flags(printer, arg, sa_flags));
	if (sa_flags & SA_RESTORER)
		PRINTF("," SYNSPACE SYNFIELD("sa_restorer") "%#" PRIxPTR, sa_restorer);
	PRINT(SYNSPACE "}");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_sigaction */





#ifdef NEED_print_epoll_create1_flags
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[8];
} const epoll_create1_flags[] = {
	{ EPOLL_CLOEXEC, "CLOEXEC" },
	{ EPOLL_CLOFORK, "CLOFORK" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_epoll_create1_flags)(pformatprinter printer, void *arg,
                                         syscall_ulong_t flags) {
	return print_flagset32(printer, arg, epoll_create1_flags,
	                       sizeof(*epoll_create1_flags),
	                       "EPOLL_", flags);
}
#endif /* NEED_print_epoll_create1_flags */





#ifdef NEED_print_epoll_event
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_epoll_event)(pformatprinter printer, void *arg,
                                     NCX struct epoll_event const *ee) {
	ssize_t temp, result;
	result = DOPRINT("{" SYNSPACE SYNFIELD("events"));
	if unlikely(result < 0)
		goto done;
	DO(print_epoll_what(printer, arg, ee->events));
	PRINTF("," SYNSPACE SYNFIELD("data")
	       "{" SYNSPACE "%#" PRIx64 SYNSPACE "}"
	       SYNSPACE "}",
	       ee->data.u64);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_epoll_event */





#if defined(NEED_print_epoll_ctl) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local epop = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/epoll.h", "__EPOLL_CTL_");
printStrendNDatabase("EPOLL_CTL", epop);
]]]*/
#define GETBASE_EPOLL_CTL(result, index) \
	(((index) <= 0x3) ? ((result) = repr_EPOLL_CTL_0h, true) : \
	 ((index) == 0x20) ? ((index) = 0, (result) = repr_EPOLL_CTL_20h, true) : false)
PRIVATE char const repr_EPOLL_CTL_0h[] =
"\0ADD\0DEL\0MOD";
PRIVATE char const repr_EPOLL_CTL_20h[] =
"RPC_PROG";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_epoll_ctl_name)(syscall_ulong_t op) {
	char const *result = NULL;
	if (!GETBASE_EPOLL_CTL(result, op))
		goto done;
	for (; op; --op)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_epoll_ctl)(pformatprinter printer, void *arg,
                               syscall_ulong_t op) {
	char const *name;
	name = get_epoll_ctl_name(op);
	if (name)
		return format_printf(printer, arg, "EPOLL_CTL_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), op);
}
#endif /* NEED_print_epoll_ctl */



#if defined(NEED_print_mremap_flags) || defined(__DEEMON__)
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[16];
} const mremap_flags[] = {
	{ MREMAP_MAYMOVE,         "MAYMOVE" },
	{ MREMAP_FIXED,           "FIXED" },
#ifdef MREMAP_DONTUNMAP
	{ MREMAP_DONTUNMAP,       "DONTUNMAP" },
#endif /* MREMAP_DONTUNMAP */
	{ MREMAP_32BIT,           "32BIT" },
	{ MREMAP_GROWSDOWN,       "GROWSDOWN" },
	{ MREMAP_GROWSUP,         "GROWSUP" },
	{ MREMAP_POPULATE,        "POPULATE" },
	{ MREMAP_NONBLOCK,        "NONBLOCK" },
	{ MREMAP_STACK,           "STACK" },
	{ MREMAP_FIXED_NOREPLACE, "FIXED_NOREPLACE" },
	{ MREMAP_NOASLR,          "NOASLR" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_mremap_flags)(pformatprinter printer, void *arg,
                                  syscall_ulong_t flags) {
	return print_flagset32(printer, arg, mremap_flags,
	                       sizeof(*mremap_flags),
	                       "MREMAP_", flags);
}
#endif /* NEED_print_mremap_flags */



#if defined(NEED_print_arch_prctl_command) || defined(__DEEMON__)
#if defined(__i386__) || defined(__x86_64__) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local prctl = getPrefixedMacrosFromFileAsMapping("../../include/i386-kos/asm/os/kos/prctl.h", "ARCH_");
printStrendNDatabase("ARCH_", prctl);
]]]*/
#define GETBASE_ARCH(result, index) \
	(((index) >= 0x1001 && (index) <= 0x1012) ? ((index) -= 0x1001, (result) = repr_ARCH_1001h, true) : \
	 ((index) >= 0x2001 && (index) <= 0x2003) ? ((index) -= 0x2001, (result) = repr_ARCH_2001h, true) : false)
PRIVATE char const repr_ARCH_1001h[] =
"SET_GS\0SET_FS\0GET_FS\0GET_GS\0\0\0\0\0\0\0\0\0\0\0\0\0GET_CPUID\0SET_CPUID";
PRIVATE char const repr_ARCH_2001h[] =
"MAP_VDSO_X32\0MAP_VDSO_32\0MAP_VDSO_64";
/*[[[end]]]*/
#else /* __i386__ || __x86_64__ */
#error "Need arch_prctl command reprs, but don't know where to find on this arch"
#endif /* !__i386__ && !__x86_64__ */

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_arch_prctl_name)(syscall_ulong_t op) {
	char const *result = NULL;
	if (!GETBASE_ARCH(result, op))
		goto done;
	for (; op; --op)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_arch_prctl_command)(pformatprinter printer, void *arg,
                                        syscall_ulong_t command) {
	char const *name;
	name = get_arch_prctl_name(command);
	if (name)
		return format_printf(printer, arg, "ARCH_%s", name);
	return format_printf(printer, arg, "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__), command);
}
#endif /* NEED_print_arch_prctl_command */



#if defined(NEED_print_prctl_command) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local prctl = getPrefixedMacrosFromFileAsMapping(
	"../../include/linux/prctl.h", "PR_",
	requireNoSpaceAfterPound: true);
printStrendNDatabase("PR_", prctl);
]]]*/
#define GETBASE_PR(result, index) \
	(((index) <= 0x3a) ? ((result) = repr_PR_0h, true) : \
	 ((index) == 0x59616d61) ? ((index) = 0, (result) = repr_PR_59616d61h, true) : \
	 ((index) == 0x8050fff1) ? ((index) = 0, (result) = repr_PR_8050fff1h, true) : false)
PRIVATE char const repr_PR_0h[] =
"\0SET_PDEATHSIG\0GET_PDEATHSIG\0GET_DUMPABLE\0SET_DUMPABLE\0GET_UNALI"
"GN\0SET_UNALIGN\0GET_KEEPCAPS\0SET_KEEPCAPS\0GET_FPEMU\0SET_FPEMU\0GET"
"_FPEXC\0SET_FPEXC\0GET_TIMING\0SET_TIMING\0SET_NAME\0GET_NAME\0\0\0GET_E"
"NDIAN\0SET_ENDIAN\0GET_SECCOMP\0SET_SECCOMP\0CAPBSET_READ\0CAPBSET_DR"
"OP\0GET_TSC\0SET_TSC\0GET_SECUREBITS\0SET_SECUREBITS\0SET_TIMERSLACK\0"
"GET_TIMERSLACK\0TASK_PERF_EVENTS_DISABLE\0TASK_PERF_EVENTS_ENABLE\0"
"MCE_KILL\0MCE_KILL_GET\0SET_MM\0SET_CHILD_SUBREAPER\0GET_CHILD_SUBRE"
"APER\0SET_NO_NEW_PRIVS\0GET_NO_NEW_PRIVS\0GET_TID_ADDRESS\0SET_THP_D"
"ISABLE\0GET_THP_DISABLE\0MPX_ENABLE_MANAGEMENT\0MPX_DISABLE_MANAGEM"
"ENT\0SET_FP_MODE\0GET_FP_MODE\0CAP_AMBIENT\0\0\0\0\0GET_SPECULATION_CTRL"
"\0SET_SPECULATION_CTRL\0PAC_RESET_KEYS\0SET_TAGGED_ADDR_CTRL\0GET_TA"
"GGED_ADDR_CTRL\0SET_IO_FLUSHER\0GET_IO_FLUSHER";
PRIVATE char const repr_PR_59616d61h[] =
"SET_PTRACER";
PRIVATE char const repr_PR_8050fff1h[] =
"KOS_GET_AT_SECURE";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_prctl_name)(syscall_ulong_t op) {
	char const *result = NULL;
	if (!GETBASE_PR(result, op))
		goto done;
	for (; op; --op)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_prctl_command)(pformatprinter printer, void *arg,
                                   syscall_ulong_t command) {
	char const *name;
	name = get_prctl_name(command);
	if (name)
		return format_printf(printer, arg, "PR_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), command);
}
#endif /* NEED_print_prctl_command */





#if defined(NEED_print_clone_flags) || defined(__DEEMON__)
PRIVATE struct {
#ifdef NEED_print_clone_flags_ex
	uint64_t   pn_flag;
#else /* NEED_print_clone_flags_ex */
	uint32_t   pn_flag;
#endif /* !NEED_print_clone_flags_ex */
	char const pn_name[16];
} const clone_flags[] = {
	{ CLONE_VM,             "VM" },
	{ CLONE_FS,             "FS" },
	{ CLONE_FILES,          "FILES" },
	{ CLONE_SIGHAND,        "SIGHAND" },
	{ CLONE_PIDFD,          "PIDFD" },
	{ CLONE_PTRACE,         "PTRACE" },
	{ CLONE_VFORK,          "VFORK" },
	{ CLONE_PARENT,         "PARENT" },
	{ CLONE_THREAD,         "THREAD" },
	{ CLONE_NEWNS,          "NEWNS" },
	{ CLONE_SYSVSEM,        "SYSVSEM" },
	{ CLONE_SETTLS,         "SETTLS" },
	{ CLONE_PARENT_SETTID,  "PARENT_SETTID" },
	{ CLONE_CHILD_CLEARTID, "CHILD_CLEARTID" },
	{ CLONE_DETACHED,       "DETACHED" },
	{ CLONE_UNTRACED,       "UNTRACED" },
	{ CLONE_CHILD_SETTID,   "CHILD_SETTID" },
	{ CLONE_NEWCGROUP,      "NEWCGROUP" },
	{ CLONE_NEWUTS,         "NEWUTS" },
	{ CLONE_NEWIPC,         "NEWIPC" },
	{ CLONE_NEWUSER,        "NEWUSER" },
	{ CLONE_NEWPID,         "NEWPID" },
	{ CLONE_NEWNET,         "NEWNET" },
	{ CLONE_IO,             "IO" },
	/* 64-bit flags: */
#ifdef NEED_print_clone_flags_ex
	{ CLONE_CLEAR_SIGHAND,  "CLEAR_SIGHAND" },
	{ CLONE_INTO_CGROUP,    "INTO_CGROUP" },
	{ CLONE_NEWTIME,        "NEWTIME" },
	{ CLONE_CRED,           "CRED" },
#endif /* NEED_print_clone_flags_ex */
	{ 0, "" },
};

#ifdef NEED_print_clone_flags_ex
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_clone_flags_ex)(pformatprinter printer, void *arg,
                                    uint64_t flags, uint64_t valid_flags,
                                    bool allow_csignal)
#define print_clone_flags(printer, arg, flags, valid_flags) \
	print_clone_flags_ex(printer, arg, (uint64_t)(flags), (uint64_t)(uint32_t)(valid_flags), true)
#else /* NEED_print_clone_flags_ex */
PRIVATE NONNULL((1)) ssize_t CC
print_clone_flags(pformatprinter printer, void *arg,
                  uint32_t flags, uint32_t valid_flags)
#endif /* !NEED_print_clone_flags_ex */
{
	ssize_t temp, result = 0;
	uint64_t invalid_flags;
	invalid_flags = flags & ~valid_flags;
	flags         = flags & valid_flags;
#ifdef NEED_print_clone_flags_ex
	if ((flags & CSIGNAL) != 0 && allow_csignal)
#else /* NEED_print_clone_flags_ex */
	if ((flags & CSIGNAL) != 0)
#endif /* !NEED_print_clone_flags_ex */
	{
		result = print_signo_t(printer, arg, flags & CSIGNAL);
		if unlikely(result < 0)
			return result;
		flags &= ~CSIGNAL;
	}
#ifdef NEED_print_clone_flags_ex
	temp = print_flagset64(printer, arg, clone_flags,
	                       sizeof(*clone_flags),
	                       "CLONE_", flags);
#else /* NEED_print_clone_flags_ex */
	temp = print_flagset32(printer, arg, clone_flags,
	                       sizeof(*clone_flags),
	                       "CLONE_", flags);
#endif /* !NEED_print_clone_flags_ex */
	if unlikely(temp < 0)
		goto err;
	result += temp;
	if (invalid_flags) {
		temp = format_printf(printer, arg,
		                     PIPESTR_S "%" PRIu64,
		                     invalid_flags);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_clone_flags */





#if defined(NEED_print_clone_args) || defined(__DEEMON__)
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC print_clone_args)(pformatprinter printer, void *arg,
                                    NCX UNCHECKED struct clone_args const *_user_cargs,
                                    size_t sizeof_args) {
	ssize_t temp, result;
	struct clone_args cargs;
	validate_readable(_user_cargs, sizeof_args);
	if (sizeof_args > sizeof(struct clone_args))
		sizeof_args = sizeof(struct clone_args);
	bzero(mempcpy(&cargs, _user_cargs, sizeof_args),
	      sizeof(struct clone_args) - sizeof_args);
	result = DOPRINT("{" SYNSPACE SYNFIELD("flags"));
	if unlikely(result < 0)
		goto done;
	DO(print_clone_flags_ex(printer, arg, cargs.ca_flags, (uint64_t)-1, false));
	if (cargs.ca_flags & CLONE_PIDFD)
		PRINTF("," SYNSPACE SYNFIELD("pidfd") "%#" PRIxPTR, cargs.ca_pidfd);
	if (cargs.ca_flags & (CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID))
		PRINTF("," SYNSPACE SYNFIELD("child_tid") "%#" PRIxPTR, cargs.ca_child_tid);
	if (cargs.ca_flags & CLONE_PARENT_SETTID)
		PRINTF("," SYNSPACE SYNFIELD("parent_tid") "%#" PRIxPTR, cargs.ca_parent_tid);
	PRINT("," SYNSPACE SYNFIELD("exit_signal"));
	DO(print_signo_t(printer, arg, cargs.ca_exit_signal));
	if ((cargs.ca_flags & CLONE_VM) || cargs.ca_stack_size) {
		PRINTF("," SYNSPACE SYNFIELD("stack") "%#" PRIxPTR
		       "," SYNSPACE SYNFIELD("stack_size") "%#" PRIxSIZ,
		       cargs.ca_stack, cargs.ca_stack_size);
	}
	if (cargs.ca_flags & CLONE_SETTLS)
		PRINTF("," SYNSPACE SYNFIELD("tls") "%#" PRIxPTR, cargs.ca_tls);
	if (sizeof_args >= offsetafter(struct clone_args, ca_set_tid_size)) {
		if (cargs.ca_set_tid_size != 0) {
			size_t i, count;
			NCX UNCHECKED pid_t const *pid_array = (NCX UNCHECKED pid_t const *)cargs.ca_set_tid;
			validate_readablem(pid_array, cargs.ca_set_tid_size, sizeof(size_t));
			count = cargs.ca_set_tid_size;
			if (count > LIMIT_STRINGVECTOR)
				count = LIMIT_STRINGVECTOR;
			PRINT("," SYNSPACE SYNFIELD("set_tid") "[");
			for (i = 0; i < count; ++i) {
				if (i != 0)
					PRINT("," SYNSPACE);
				PRINTF("%" PRIdN(__SIZEOF_PID_T__), pid_array[i]);
			}
			if (cargs.ca_set_tid_size > LIMIT_STRINGVECTOR)
				PRINT(",...");
			PRINT("]");
		} else if (cargs.ca_set_tid == NULL) {
			PRINT("," SYNSPACE SYNFIELD("set_tid") NULLSTR_S);
		} else {
			PRINTF("," SYNSPACE SYNFIELD("set_tid") "%#" PRIxPTR, cargs.ca_set_tid);
		}
		PRINTF("," SYNSPACE SYNFIELD("set_tid_size") "%#" PRIxSIZ, cargs.ca_set_tid_size);
	}
	if (sizeof_args >= offsetafter(struct clone_args, ca_cgroup)) {
		if (cargs.ca_flags & CLONE_INTO_CGROUP) {
			PRINT("," SYNSPACE SYNFIELD("cgroup"));
			DO(print_fd_t(printer, arg, cargs.ca_cgroup));
		}
	}
	PRINT(SYNSPACE "}");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_clone_args */



#if defined(NEED_print_waitflags) || defined(__DEEMON__)
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[12];
} const waitflags[] = {
	{ WNOHANG,    "NOHANG" },
	{ WUNTRACED,  "UNTRACED" },
	{ WSTOPPED,   "STOPPED" },
	{ WEXITED,    "EXITED" },
	{ WCONTINUED, "CONTINUED" },
	{ WNOWAIT,    "NOWAIT" },
	{ WNOTHREAD,  "NOTHREAD" },
	{ WALL,       "ALL" },
	{ WCLONE,     "CLONE" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_waitflags)(pformatprinter printer, void *arg,
                               syscall_ulong_t flags) {
	return print_flagset32(printer, arg, waitflags,
	                       sizeof(*waitflags),
	                       "W", flags);
}
#endif /* NEED_print_waitflags */



#if defined(NEED_print_idtype_t) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/kos/wait.h", "__P_");
printStrendNDatabase("IDTYPE_T", typ);
]]]*/
#define GETBASE_IDTYPE_T(result, index) \
	(((index) <= 0x2) ? ((result) = repr_IDTYPE_T_0h, true) : false)
PRIVATE char const repr_IDTYPE_T_0h[] =
"ALL\0PID\0PGID";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_idtype_t_name)(syscall_ulong_t idtype) {
	char const *result = NULL;
	if (!GETBASE_IDTYPE_T(result, idtype))
		goto done;
	for (; idtype; --idtype)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_idtype_t)(pformatprinter printer, void *arg,
                              syscall_ulong_t idtype) {
	char const *name;
	name = get_idtype_t_name(idtype);
	if (name)
		return format_printf(printer, arg, "P_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), idtype);
}
#endif /* NEED_print_idtype_t */



#if defined(NEED_print_eventfd_flags) || defined(__DEEMON__)
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[12];
} const eventfd_flags[] = {
	{ EFD_SEMAPHORE, "SEMAPHORE" },
	{ EFD_NONBLOCK,  "NONBLOCK" },
	{ EFD_CLOEXEC,   "CLOEXEC" },
	{ EFD_CLOFORK,   "CLOFORK" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_eventfd_flags)(pformatprinter printer, void *arg,
                                   syscall_ulong_t flags) {
	return print_flagset32(printer, arg, eventfd_flags,
	                       sizeof(*eventfd_flags),
	                       "EFD_", flags);
}
#endif /* NEED_print_eventfd_flags */



#if defined(NEED_print_signalfd_flags) || defined(__DEEMON__)
#if (defined(NEED_print_eventfd_flags) && \
     __SFD_NONBLOCK == __EFD_NONBLOCK &&  \
     __SFD_CLOEXEC == __EFD_CLOEXEC &&    \
     __SFD_CLOFORK == __EFD_CLOFORK)
#define signalfd_flags (eventfd_flags + 1) /* Skip `EFD_SEMAPHORE' */
#else /* ... */
PRIVATE struct {
	uint32_t   pn_flag;
	char const pn_name[12];
} const signalfd_flags[] = {
	{ SFD_NONBLOCK, "NONBLOCK" },
	{ SFD_CLOEXEC,  "CLOEXEC" },
	{ SFD_CLOFORK,  "CLOFORK" },
	{ 0, "" }
};
#endif /* !... */

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_signalfd_flags)(pformatprinter printer, void *arg,
                                    syscall_ulong_t flags) {
	return print_flagset32(printer, arg, signalfd_flags,
	                       sizeof(*signalfd_flags),
	                       "SFD_", flags);
}
#endif /* NEED_print_signalfd_flags */



#if defined(NEED_print_exit_status) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/asm/os/stdlib.h", "__EXIT_");
printStrendNDatabase("EXIT_STATUS", typ);
]]]*/
#define GETBASE_EXIT_STATUS(result, index) \
	(((index) <= 0x1) ? ((result) = repr_EXIT_STATUS_0h, true) : false)
PRIVATE char const repr_EXIT_STATUS_0h[] =
"SUCCESS\0FAILURE";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_exit_status_name)(syscall_ulong_t idtype) {
	char const *result = NULL;
	if (!GETBASE_EXIT_STATUS(result, idtype))
		goto done;
	for (; idtype; --idtype)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_exit_status)(pformatprinter printer, void *arg,
                                 syscall_ulong_t idtype) {
	char const *name;
	name = get_exit_status_name(idtype);
	if (name)
		return format_printf(printer, arg, "EXIT_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), idtype);
}
#endif /* NEED_print_exit_status */



#if defined(NEED_print_exception_handler_mode) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/kos/except-handler.h", "EXCEPT_HANDLER_MODE_");
for (;;) {
	local key = typ.keys > ...;
	if (key < 0xf)
		break;
	del typ[key];
}
printStrendNDatabase("EXCEPT_HANDLER_MODE", typ);
]]]*/
#define GETBASE_EXCEPT_HANDLER_MODE(result, index) \
	(((index) <= 0x3) ? ((result) = repr_EXCEPT_HANDLER_MODE_0h, true) : false)
PRIVATE char const repr_EXCEPT_HANDLER_MODE_0h[] =
"UNCHANGED\0DISABLED\0ENABLED\0SIGHAND";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_except_handler_mode_name)(syscall_ulong_t mode) {
	char const *result = NULL;
	if (!GETBASE_EXCEPT_HANDLER_MODE(result, mode))
		goto done;
	for (; mode; --mode)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_exception_handler_mode)(pformatprinter printer, void *arg,
                                            syscall_ulong_t mode) {
	ssize_t temp, result;
	char const *basename;
	basename = get_except_handler_mode_name(mode & EXCEPT_HANDLER_MODE_MASK);
	if (basename) {
		result = format_printf(printer, arg, "EXCEPT_HANDLER_%s", basename);
	} else {
		result = format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
		                       mode & EXCEPT_HANDLER_MODE_MASK);
	}
	if unlikely(result < 0)
		goto done;
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT)
		PRINT(PIPESTR_S "EXCEPT_HANDLER_FLAG_ONESHOT");
	if (mode & EXCEPT_HANDLER_FLAG_SETHANDLER)
		PRINT(PIPESTR_S "EXCEPT_HANDLER_FLAG_SETHANDLER");
	if (mode & EXCEPT_HANDLER_FLAG_SETSTACK)
		PRINT(PIPESTR_S "EXCEPT_HANDLER_FLAG_SETSTACK");
	mode &= ~(EXCEPT_HANDLER_MODE_MASK | EXCEPT_HANDLER_FLAG_ONESHOT |
	          EXCEPT_HANDLER_FLAG_SETHANDLER | EXCEPT_HANDLER_FLAG_SETSTACK);
	if (mode)
		PRINTF(PIPESTR_S "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__), mode);
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_exception_handler_mode */



#if defined(NEED_print_kcmp_type) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFileAsMapping("../../include/linux/kcmp.h", "KCMP_");
printStrendNDatabase("KCMP", typ);
]]]*/
#define GETBASE_KCMP(result, index) \
	(((index) <= 0x8) ? ((result) = repr_KCMP_0h, true) : false)
PRIVATE char const repr_KCMP_0h[] =
"FILE\0VM\0FILES\0FS\0SIGHAND\0IO\0SYSVSEM\0EPOLL_TFD\0TYPES";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_kcmp_type_name)(syscall_ulong_t kcmp_type) {
	char const *result = NULL;
	if (!GETBASE_KCMP(result, kcmp_type))
		goto done;
	for (; kcmp_type; --kcmp_type)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_kcmp_type)(pformatprinter printer, void *arg,
                               syscall_ulong_t kcmp_type) {
	char const *name;
	name = get_kcmp_type_name(kcmp_type);
	if (name)
		return format_printf(printer, arg, "KCMP_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), kcmp_type);
}
#endif /* NEED_print_kcmp_type */



#ifdef NEED_print_access_type
PRIVATE struct {
	uint8_t    pn_flag;
	char const pn_name[5];
} const access_type_flags[] = {
	{ X_OK, "X_OK" },
	{ W_OK, "W_OK" },
	{ R_OK, "R_OK" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_access_type)(pformatprinter printer, void *arg,
                                 syscall_ulong_t flags) {
	if (flags == F_OK)
		return DOPRINT("F_OK");
	return print_flagset8(printer, arg, access_type_flags,
	                      sizeof(*access_type_flags),
	                      "", flags);
}
#endif /* NEED_print_access_type */



#ifdef NEED_print_close_range_flags
PRIVATE struct {
	uint8_t    pn_flag;
	char const pn_name[8];
} const close_range_flags[] = {
	{ CLOSE_RANGE_CLOEXEC, "CLOEXEC" },
	{ CLOSE_RANGE_UNSHARE, "UNSHARE" },
	{ 0, "" },
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB(CC print_close_range_flags)(pformatprinter printer, void *arg,
                                       syscall_ulong_t flags) {
	return print_flagset8(printer, arg, close_range_flags,
	                      sizeof(*close_range_flags),
	                      "CLOSE_RANGE_", flags);
}
#endif /* NEED_print_close_range_flags */












/* Print the representation of a given system call argument
 * value, given both its `argtype' (one of `SC_REPR_*'), as
 * well as its `value'.
 * WARNING: Depending on `argtype', an exception may be thrown
 *          if the system call invoker has passed some invalid
 *          argument to a system  call (i.e. a faulty  pointer
 *          when a structure pointer or string was expected) */
INTERN NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC libsc_printvalue)(pformatprinter printer, void *arg,
                                    uintptr_t argtype, union sc_argval value,
                                    struct sc_argument *link) {
	ssize_t result;
	char const *format;
	(void)link;
	switch (argtype) {

/*[[[deemon
//INSIDE:libsc_printvalue
import * from deemon;
local MARKER = "//INSIDE:libsc_printvalue";
local knownCases = HashSet();
local implementedCases = none;
for (local l: File.open(__FILE__, "r")) {
	l = l.strip();
	if (l == MARKER)
		implementedCases = HashSet();
	if (l.startswith("case")) {
		local e = l.find(":");
		if (e >= 0) {
			l = l[4:e].strip();
			implementedCases.insert(l);
		}
	}
}
for (local f: [
	"../../include/asm/syscalls-types.h",
	"../../include/arm-kos/asm/syscalls-types.h",
	"../../include/i386-kos/asm/syscalls-types.h",
	"../../include/i386-kos/asm/syscall3264-types.h",
	"../../include/i386-kos/asm/syscalls-types32.h",
	"../../include/i386-kos/asm/syscalls-types64.h",
]) {
	for (local l: File.open(f, "r")) {
		l = l.strip();
		if (l.startswith("__SYSCALL_REPR(") &&
		    l.endswith(")")) {
			knownCases.insert(l[15:-1].strip());
		}
	}
}
for (local c: knownCases.sorted()) {
	if (c !in implementedCases) {
		print("\t// TO" "DO: #define HAVE_", c);
	}
}
]]]*/
	// TODO: #define HAVE_SC_REPR_CPUSET
	// TODO: #define HAVE_SC_REPR_FALLOCATE_MODE
	// TODO: #define HAVE_SC_REPR_FSMODE
	// TODO: #define HAVE_SC_REPR_FUTEX_OP
	// TODO: #define HAVE_SC_REPR_GETRANDOM_FLAGS
	// TODO: #define HAVE_SC_REPR_GETRUSAGE_WHO
	// TODO: #define HAVE_SC_REPR_GID_VECTOR
	// TODO: #define HAVE_SC_REPR_GID_VECTOR16
	// TODO: #define HAVE_SC_REPR_GID_VECTOR32
	// TODO: #define HAVE_SC_REPR_INOTIFY_INIT_FLAGS
	// TODO: #define HAVE_SC_REPR_INOTIFY_MASK
	// TODO: #define HAVE_SC_REPR_IOPRIO_ID
	// TODO: #define HAVE_SC_REPR_IOPRIO_VALUE
	// TODO: #define HAVE_SC_REPR_IOPRIO_WHO
	// TODO: #define HAVE_SC_REPR_ITIMER_WHICH
	// TODO: #define HAVE_SC_REPR_KSYSCTL_ARG
	// TODO: #define HAVE_SC_REPR_KSYSCTL_COMMAND
	// TODO: #define HAVE_SC_REPR_LFUTEX_OP
	// TODO: #define HAVE_SC_REPR_LFUTEX_TIMEOUT_FLAGS
	// TODO: #define HAVE_SC_REPR_MEMFD_CREATE_FLAGS
	// TODO: #define HAVE_SC_REPR_MLOCKALL_FLAGS
	// TODO: #define HAVE_SC_REPR_MOUNT_FLAGS
	// TODO: #define HAVE_SC_REPR_REBOOT_HOW
	// TODO: #define HAVE_SC_REPR_RENAMEAT2_FLAGS
	// TODO: #define HAVE_SC_REPR_RLIMIT_RESOURCE
	// TODO: #define HAVE_SC_REPR_RPC_SCHEDULE_MODE
	// TODO: #define HAVE_SC_REPR_SCHED_POLICY
	// TODO: #define HAVE_SC_REPR_SCHED_PRIORITY_WHICH
	// TODO: #define HAVE_SC_REPR_SIGPROCMASK_HOW
	// TODO: #define HAVE_SC_REPR_SOCKETCALL_ARGS
	// TODO: #define HAVE_SC_REPR_SOCKETCALL_CALL
	// TODO: #define HAVE_SC_REPR_SOCKET_SHUTDOWN_HOW
	// TODO: #define HAVE_SC_REPR_SOCKOPT_OPTVAL
	// TODO: #define HAVE_SC_REPR_SPLICE_FLAGS
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON32
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON64
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR32_VECTOR
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR64_VECTOR
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA32
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA64
	// TODO: #define HAVE_SC_REPR_STRUCT_FILE_HANDLE
	// TODO: #define HAVE_SC_REPR_STRUCT_FPUSTATE
	// TODO: #define HAVE_SC_REPR_STRUCT_FPUSTATE32
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPEC
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPEC32
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPEC64
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX32
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX32_64
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX64
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVAL
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVAL64
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX32
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX32_64
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX64
	// TODO: #define HAVE_SC_REPR_STRUCT_LFUTEXEXPRX32_VECTOR
	// TODO: #define HAVE_SC_REPR_STRUCT_LFUTEXEXPRX64_VECTOR
	// TODO: #define HAVE_SC_REPR_STRUCT_LFUTEXEXPR_VECTOR
	// TODO: #define HAVE_SC_REPR_STRUCT_MMSGHDR
	// TODO: #define HAVE_SC_REPR_STRUCT_MMSGHDRX32
	// TODO: #define HAVE_SC_REPR_STRUCT_MMSGHDRX64
	// TODO: #define HAVE_SC_REPR_STRUCT_MQ_ATTR
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDR
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX32
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX64
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT32
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT64
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMITX32
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMITX32_64
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMITX64
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO32
	// TODO: #define HAVE_SC_REPR_STRUCT_SCHED_PARAM
	// TODO: #define HAVE_SC_REPR_STRUCT_SEL_ARG
	// TODO: #define HAVE_SC_REPR_STRUCT_SEL_ARGX32
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGALTSTACK
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGALTSTACKX32
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGALTSTACKX64
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGEVENT
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFO
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX32
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX64
	// TODO: #define HAVE_SC_REPR_STRUCT_TERMIOS
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMESPEC_OR_UINT32
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEZONE
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE32
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE64
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUF
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUF32
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUF64
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32_64
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX64
	// TODO: #define HAVE_SC_REPR_STRUCT_WINSIZE
	// TODO: #define HAVE_SC_REPR_SWAPFLAGS
	// TODO: #define HAVE_SC_REPR_SYNC_FILE_RANGE_FLAGS
	// TODO: #define HAVE_SC_REPR_SYSLOG_LEVEL
	// TODO: #define HAVE_SC_REPR_TIME32_T_PTR
	// TODO: #define HAVE_SC_REPR_TIME64_T_PTR
	// TODO: #define HAVE_SC_REPR_TIMERFD_FLAGS
	// TODO: #define HAVE_SC_REPR_TIMERFD_TIMER_FLAGS
	// TODO: #define HAVE_SC_REPR_TIMER_FLAGS
	// TODO: #define HAVE_SC_REPR_UNWIND_ERRNO_T
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR32
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR64
	// TODO: #define HAVE_SC_REPR_XATTR_FLAGS
/*[[[end]]]*/

#ifdef HAVE_SC_REPR_SIGMASK32
	case SC_REPR_SIGMASK32: {
		uint32_t sm = (uint32_t)value.sv_u64;
		result = print_sigset(printer, arg, (sigset_t const *)&sm, sizeof(sm));
	}	break;
#endif /* HAVE_SC_REPR_SIGMASK32 */

#ifdef HAVE_SC_REPR_CLOSE_RANGE_FLAGS
	case SC_REPR_CLOSE_RANGE_FLAGS:
		result = print_close_range_flags(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_CLOSE_RANGE_FLAGS */

#ifdef HAVE_SC_REPR_ACCESS_TYPE
	case SC_REPR_ACCESS_TYPE:
		result = print_access_type(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_ACCESS_TYPE */

#ifdef HAVE_SC_REPR_KCMP_TYPE
	case SC_REPR_KCMP_TYPE:
		result = print_kcmp_type(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_KCMP_TYPE */

#ifdef HAVE_SC_REPR_EXCEPTION_HANDLER_SP
	case SC_REPR_EXCEPTION_HANDLER_SP:
		if (link && !(link->sa_value.sv_u64 & EXCEPT_HANDLER_FLAG_SETSTACK)) {
			/* Only have special treatment for `EXCEPT_HANDLER_SP_CURRENT'
			 * when the stack pointer is being set! */
			goto do_pointer;
		}
		if ((void *)(uintptr_t)value.sv_u64 == EXCEPT_HANDLER_SP_CURRENT) {
			result = DOPRINT("EXCEPT_HANDLER_SP_CURRENT");
			break;
		}
		goto do_pointer;
#endif /* HAVE_SC_REPR_EXCEPTION_HANDLER_SP */

#ifdef HAVE_SC_REPR_EXCEPTION_HANDLER_MODE
	case SC_REPR_EXCEPTION_HANDLER_MODE:
		result = print_exception_handler_mode(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_EXCEPTION_HANDLER_MODE */

#ifdef HAVE_SC_REPR_EXIT_STATUS
	case SC_REPR_EXIT_STATUS:
		result = print_exit_status(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_EXIT_STATUS */

#ifdef HAVE_SC_REPR_EVENTFD2_FLAGS
	case SC_REPR_EVENTFD2_FLAGS:
		result = print_eventfd_flags(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_EVENTFD2_FLAGS */

#ifdef HAVE_SC_REPR_SIGNALFD4_FLAGS
	case SC_REPR_SIGNALFD4_FLAGS:
		result = print_signalfd_flags(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SIGNALFD4_FLAGS */

#ifdef HAVE_SC_REPR_IDTYPE_T
	case SC_REPR_IDTYPE_T:
		result = print_idtype_t(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_IDTYPE_T */

#ifdef HAVE_SC_REPR_WAITFLAGS
	case SC_REPR_WAITFLAGS:
		result = print_waitflags(printer, arg, (uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_WAITFLAGS */

#ifdef HAVE_SC_REPR_STRUCT_CLONE_ARGS
	case SC_REPR_STRUCT_CLONE_ARGS:
		result = print_clone_args(printer, arg,
		                          (NCX UNCHECKED struct clone_args const *)(uintptr_t)value.sv_u64,
		                          link ? (size_t)link->sa_value.sv_u64 : sizeof(struct clone_args));
		break;
#endif /* HAVE_SC_REPR_STRUCT_CLONE_ARGS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS
	case SC_REPR_CLONE_FLAGS:
		result = print_clone_flags(printer, arg, (syscall_ulong_t)value.sv_u64,
		                           UINT32_C(0xffffffff));
		break;
#endif /* HAVE_SC_REPR_CLONE_FLAGS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS_SETNS
	case SC_REPR_CLONE_FLAGS_SETNS:
		result = print_clone_flags(printer, arg, (syscall_ulong_t)value.sv_u64,
		                           CLONE_NEWCGROUP | CLONE_NEWIPC | CLONE_NEWNET |
		                           CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWTIME |
		                           CLONE_NEWUSER | CLONE_NEWUTS);
		break;
#endif /* HAVE_SC_REPR_CLONE_FLAGS_SETNS */

#ifdef HAVE_SC_REPR_CLONE_FLAGS_UNSHARE
	case SC_REPR_CLONE_FLAGS_UNSHARE:
		result = print_clone_flags(printer, arg, (syscall_ulong_t)value.sv_u64,
		                           CLONE_FILES | CLONE_FS | CLONE_NEWCGROUP | CLONE_NEWIPC |
		                           CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWTIME |
		                           CLONE_NEWUSER | CLONE_NEWUTS | CLONE_SYSVSEM | CLONE_THREAD |
		                           CLONE_SIGHAND | CLONE_VM);
		break;
#endif /* HAVE_SC_REPR_CLONE_FLAGS_UNSHARE */

#ifdef HAVE_SC_REPR_PRCTL_COMMAND
	case SC_REPR_PRCTL_COMMAND:
		result = print_prctl_command(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_PRCTL_COMMAND */

#ifdef HAVE_SC_REPR_ARCH_PRCTL_COMMAND
	case SC_REPR_ARCH_PRCTL_COMMAND:
		result = print_arch_prctl_command(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_ARCH_PRCTL_COMMAND */

#ifdef HAVE_SC_REPR_MREMAP_FLAGS
	case SC_REPR_MREMAP_FLAGS:
		result = print_mremap_flags(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_MREMAP_FLAGS */

#ifdef HAVE_SC_REPR_EPOLL_OP
	case SC_REPR_EPOLL_OP:
		result = print_epoll_ctl(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_EPOLL_OP */

#ifdef HAVE_SC_REPR_STRUCT_EPOLL_EVENT
	case SC_REPR_STRUCT_EPOLL_EVENT: {
		NCX UNCHECKED struct epoll_event const *ee;
		ee = (NCX UNCHECKED struct epoll_event const *)(uintptr_t)value.sv_u64;
		if (!ee)
			goto do_pointer;
		validate_readable(ee, sizeof(*ee));
		result = print_epoll_event(printer, arg, ee);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_EPOLL_EVENT */

#ifdef HAVE_SC_REPR_EPOLL_CREATE1_FLAGS
	case SC_REPR_EPOLL_CREATE1_FLAGS:
		result = print_epoll_create1_flags(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_EPOLL_CREATE1_FLAGS */

#if ((defined(HAVE_SC_REPR_STRUCT_SIGACTION)) || \
     (defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION) && defined(__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION)))
#ifdef HAVE_SC_REPR_STRUCT_SIGACTION
	case SC_REPR_STRUCT_SIGACTION:
#endif /* HAVE_SC_REPR_STRUCT_SIGACTION */
#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION) && defined(__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION)
	case SC_REPR_STRUCT_KERNEL_SIGACTION:
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION && __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION */
	{
		NCX UNCHECKED struct sigaction *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct sigaction *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGACTION... */

#if ((defined(HAVE_SC_REPR_STRUCT_SIGACTIONX32)) || \
     (defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32) && defined(__ARCH_HAVE_KERNEL_SIGACTIONX32_IS_LIBC_SIGACTIONX32)))
#ifdef HAVE_SC_REPR_STRUCT_SIGACTIONX32
	case SC_REPR_STRUCT_SIGACTIONX32:
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX32 */
#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32) && defined(__ARCH_HAVE_KERNEL_SIGACTIONX32_IS_LIBC_SIGACTIONX32)
	case SC_REPR_STRUCT_KERNEL_SIGACTIONX32:
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32 && __ARCH_HAVE_KERNEL_SIGACTIONX32_IS_LIBC_SIGACTIONX32 */
	{
		NCX UNCHECKED struct __sigactionx32 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __sigactionx32 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa)
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX32... */

#if ((defined(HAVE_SC_REPR_STRUCT_SIGACTIONX64)) || \
     (defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64) && defined(__ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64)))
#ifdef HAVE_SC_REPR_STRUCT_SIGACTIONX64
	case SC_REPR_STRUCT_SIGACTIONX64:
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX64 */
#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64) && defined(__ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64)
	case SC_REPR_STRUCT_KERNEL_SIGACTIONX64:
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64 && __ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64 */
	{
		NCX UNCHECKED struct __sigactionx64 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __sigactionx64 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGACTIONX64... */

#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION) && !defined(__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION)
	case SC_REPR_STRUCT_KERNEL_SIGACTION: {
		NCX UNCHECKED struct __kernel_sigaction *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigaction *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION && !__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION */

#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32) && !defined(__ARCH_HAVE_KERNEL_SIGACTIONX32_IS_LIBC_SIGACTIONX32)
	case SC_REPR_STRUCT_KERNEL_SIGACTIONX32: {
		NCX UNCHECKED struct __kernel_sigactionx32 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigactionx32 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa)
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX32 && !__ARCH_HAVE_KERNEL_SIGACTIONX32_IS_LIBC_SIGACTIONX32 */

#if defined(HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64) && !defined(__ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64)
	case SC_REPR_STRUCT_KERNEL_SIGACTIONX64: {
		NCX UNCHECKED struct __kernel_sigactionx64 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigactionx64 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_KERNEL_SIGACTIONX64 && !__ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64 */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTION
	case SC_REPR_STRUCT_OLD_KERNEL_SIGACTION: {
		NCX UNCHECKED struct __kernel_sigaction *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigaction *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTION */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX32
	case SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX32: {
		NCX UNCHECKED struct __kernel_sigactionx32 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigactionx32 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa)
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX32 */

#ifdef HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX64
	case SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX64: {
		NCX UNCHECKED struct __kernel_sigactionx64 *sa;
		size_t sigsetsize = sizeof(sa->sa_mask);
		sa = (NCX UNCHECKED struct __kernel_sigactionx64 *)(uintptr_t)value.sv_u64;
		if (link)
			sigsetsize = (size_t)link->sa_value.sv_u64;
		if (!sa || sigsetsize != sizeof(sa->sa_mask))
			goto do_pointer;
		validate_readable(sa, sizeof(*sa));
		result = print_sigaction(printer,
		                         arg,
		                         (void *)sa->sa_handler,
		                         (NCX sigset_t *)&sa->sa_mask,
		                         sigsetsize,
		                         sa->sa_flags,
		                         (void *)sa->sa_restorer);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_OLD_KERNEL_SIGACTIONX64 */

#ifdef HAVE_SC_REPR_KREADDIR_MODE
	case SC_REPR_KREADDIR_MODE:
		result = print_kreaddir_mode(printer, arg,
		                             (unsigned int)(syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_KREADDIR_MODE */

#ifdef HAVE_SC_REPR_ACCEPT4_FLAGS
	case SC_REPR_ACCEPT4_FLAGS:
		result = print_socket_type_flags(printer, arg,
		                                 (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_ACCEPT4_FLAGS */

#ifdef HAVE_SC_REPR_MMAP_PROT
	case SC_REPR_MMAP_PROT:
		result = print_mmap_prot(printer, arg,
		                         (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_MMAP_PROT */

#ifdef HAVE_SC_REPR_MMAP_FLAGS
	case SC_REPR_MMAP_FLAGS:
		result = print_mmap_flags(printer, arg,
		                          (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_MMAP_FLAGS */

#ifdef HAVE_SC_REPR_STRUCT_SIGSET
	case SC_REPR_STRUCT_SIGSET: {
		NCX UNCHECKED sigset_t *sigset;
		size_t sigsetsize;
		if unlikely(!link)
			goto do_pointer;
		sigset = (NCX UNCHECKED sigset_t *)(uintptr_t)value.sv_u64;
		if (!sigset)
			goto do_pointer;
		sigsetsize = (size_t)(syscall_ulong_t)link->sa_value.sv_u64;
		result = print_sigset(printer, arg, sigset, sigsetsize);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGSET */

#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE
	case SC_REPR_STRUCT_SIGSET_WITH_SIZE: {
		NCX UNCHECKED void *valptr;
		valptr = (NCX UNCHECKED void *)(uintptr_t)(syscall_ulong_t)value.sv_u64;
		if (!valptr)
			goto do_pointer;
		validate_readable(valptr, sizeof(void *) + sizeof(size_t));
		result = print_sigmask_sigset_and_len(printer, arg, valptr, sizeof(void *));
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE */

#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32
	case SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32: {
		NCX UNCHECKED void *valptr;
		valptr = (NCX UNCHECKED void *)(uintptr_t)(syscall_ulong_t)value.sv_u64;
		if (!valptr)
			goto do_pointer;
		validate_readable(valptr, 2 * 4);
		result = print_sigmask_sigset_and_len(printer, arg, valptr, 4);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32 */

#ifdef HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64
	case SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64: {
		NCX UNCHECKED void *valptr;
		valptr = (NCX UNCHECKED void *)(uintptr_t)(syscall_ulong_t)value.sv_u64;
		if (!valptr)
			goto do_pointer;
		validate_readable(valptr, 2 * 8);
		result = print_sigmask_sigset_and_len(printer, arg, valptr, 8);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE_X64 */

#ifdef HAVE_SC_REPR_SOCKOPT_LEVEL
	case SC_REPR_SOCKOPT_LEVEL:
		result = print_sockopt_level(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKOPT_LEVEL */

#ifdef HAVE_SC_REPR_SOCKOPT_OPTNAME
	case SC_REPR_SOCKOPT_OPTNAME:
		if unlikely(!link) {
#if __SIZEOF_SYSCALL_LONG_T__ == 4
			goto do_uint32_t;
#define NEED_do_uint32_t
#elif __SIZEOF_SYSCALL_LONG_T__ == 8
			goto do_uint64_t;
#define NEED_do_uint64_t
#else /* __SIZEOF_SYSCALL_LONG_T__ == ... */
#error "Unsupported __SIZEOF_SYSCALL_LONG_T__"
#endif /* __SIZEOF_SYSCALL_LONG_T__ != ... */
		}
		result = print_sockopt_optname(printer, arg,
		                               (syscall_ulong_t)link->sa_value.sv_u64,
		                               (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKOPT_OPTNAME */


#ifdef HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS
	case SC_REPR_SOCKET_SENDMSG_FLAGS:
		result = print_msg_flags(printer, arg,
		                         (syscall_ulong_t)value.sv_u64,
		                         MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
		                         MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB);
		break;
#endif /* HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS */

#ifdef HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS
	case SC_REPR_SOCKET_RECVMSG_FLAGS:
		result = print_msg_flags(printer, arg,
		                         (syscall_ulong_t)value.sv_u64,
		                         MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
		                         MSG_PEEK | MSG_TRUNC | MSG_WAITALL);
		break;
#endif /* HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS */

#ifdef HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2
	case SC_REPR_SOCKET_RECVMSG_FLAGS2:
		result = print_msg_flags(printer, arg,
		                         (syscall_ulong_t)value.sv_u64,
		                         MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
		                         MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
		                         MSG_PEEK | MSG_TRUNC | MSG_WAITALL);
		break;
#endif /* HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2 */

#ifdef HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS3
	case SC_REPR_SOCKET_RECVMSG_FLAGS3:
		result = print_msg_flags(printer, arg,
		                         (syscall_ulong_t)value.sv_u64,
		                         MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
		                         MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
		                         MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
		                         MSG_WAITFORONE);
		break;
#endif /* HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS3 */



#ifdef HAVE_SC_REPR_STRUCT_FDSET
	case SC_REPR_STRUCT_FDSET: {
		NCX UNCHECKED fd_set *fdset;
		size_t nfds;
		if unlikely(!link)
			goto do_pointer;
		fdset = (NCX UNCHECKED fd_set *)(uintptr_t)value.sv_u64;
		if unlikely(!fdset)
			goto do_pointer;
		nfds = (size_t)link->sa_value.sv_u64;
		validate_readable(fdset, CEILDIV(nfds, NBBY));
		result = print_fdset(printer, arg, fdset, nfds);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_FDSET */



#if (defined(HAVE_SC_REPR_STRUCT_IOVECX32) ||   \
     defined(HAVE_SC_REPR_STRUCT_IOVECX32_C) || \
     ((defined(HAVE_SC_REPR_STRUCT_IOVEC) ||    \
       defined(HAVE_SC_REPR_STRUCT_IOVEC_C)) && \
      __SIZEOF_IOVEC == 8))
#ifdef HAVE_SC_REPR_STRUCT_IOVECX32
	case SC_REPR_STRUCT_IOVECX32:
#define _IS_IOVECX32_1() (argtype == SC_REPR_STRUCT_IOVECX32)
#endif /* HAVE_SC_REPR_STRUCT_IOVECX32 */
#ifdef HAVE_SC_REPR_STRUCT_IOVECX32_C
	case SC_REPR_STRUCT_IOVECX32_C:
#define _IS_IOVECX32_C_1() (argtype == SC_REPR_STRUCT_IOVECX32_C)
#endif /* HAVE_SC_REPR_STRUCT_IOVECX32_C */
#if defined(HAVE_SC_REPR_STRUCT_IOVEC) && __SIZEOF_IOVEC == 8
	case SC_REPR_STRUCT_IOVEC:
#define _IS_IOVECX32_2() (argtype == SC_REPR_STRUCT_IOVEC)
#endif /* HAVE_SC_REPR_STRUCT_IOVEC && __SIZEOF_IOVEC == 8 */
#if defined(HAVE_SC_REPR_STRUCT_IOVEC_C) && __SIZEOF_IOVEC == 8
	case SC_REPR_STRUCT_IOVEC_C:
#define _IS_IOVECX32_C_2() (argtype == SC_REPR_STRUCT_IOVEC_C)
#endif /* HAVE_SC_REPR_STRUCT_IOVEC_C && __SIZEOF_IOVEC == 8 */
#if defined(_IS_IOVECX32_1) && defined(_IS_IOVECX32_2)
#define _IS_IOVECX32() (_IS_IOVECX32_1() || _IS_IOVECX32_2())
#elif defined(_IS_IOVECX32_1)
#define _IS_IOVECX32 _IS_IOVECX32_1
#elif defined(_IS_IOVECX32_2)
#define _IS_IOVECX32 _IS_IOVECX32_2
#endif /* ... */
#if defined(_IS_IOVECX32_C_1) && defined(_IS_IOVECX32_C_2)
#define _IS_IOVECX32_C() (_IS_IOVECX32_C_1() || _IS_IOVECX32_C_2())
#elif defined(_IS_IOVECX32_C_1)
#define _IS_IOVECX32_C _IS_IOVECX32_C_1
#elif defined(_IS_IOVECX32_C_2)
#define _IS_IOVECX32_C _IS_IOVECX32_C_2
#endif /* ... */
	{
		NCX UNCHECKED struct iovecx32 *iov;
		size_t count;
		if unlikely(!link)
			goto do_pointer;
		iov = (NCX UNCHECKED struct iovecx32 *)(uintptr_t)value.sv_u64;
		if unlikely(!iov)
			goto do_pointer;
		count = (size_t)link->sa_value.sv_u64;
		validate_readablem(iov, count, sizeof(struct iovecx32));
#if defined(_IS_IOVECX32) && defined(_IS_IOVECX32_C)
		result = print_iovecx32(printer, arg, _IS_IOVECX32_C(), iov, count);
#elif defined(_IS_IOVECX32)
		result = print_iovecx32(printer, arg, false, iov, count);
#elif defined(_IS_IOVECX32_C)
		result = print_iovecx32(printer, arg, true, iov, count);
#else /* ... */
#error "Bad configuration"
#endif /* !... */
#undef _IS_IOVECX32
#undef _IS_IOVECX32_1
#undef _IS_IOVECX32_2
#undef _IS_IOVECX32_C
#undef _IS_IOVECX32_C_1
#undef _IS_IOVECX32_C_2
	}	break;
#endif /* ... */


#if (defined(HAVE_SC_REPR_STRUCT_IOVECX64) ||   \
     defined(HAVE_SC_REPR_STRUCT_IOVECX64_C) || \
     ((defined(HAVE_SC_REPR_STRUCT_IOVEC) ||    \
       defined(HAVE_SC_REPR_STRUCT_IOVEC_C)) && \
      __SIZEOF_IOVEC == 16))
#ifdef HAVE_SC_REPR_STRUCT_IOVECX64
	case SC_REPR_STRUCT_IOVECX64:
#define _IS_IOVECX64_1() (argtype == SC_REPR_STRUCT_IOVECX64)
#endif /* HAVE_SC_REPR_STRUCT_IOVECX64 */
#ifdef HAVE_SC_REPR_STRUCT_IOVECX64_C
	case SC_REPR_STRUCT_IOVECX64_C:
#define _IS_IOVECX64_C_1() (argtype == SC_REPR_STRUCT_IOVECX64_C)
#endif /* HAVE_SC_REPR_STRUCT_IOVECX64_C */
#if defined(HAVE_SC_REPR_STRUCT_IOVEC) && __SIZEOF_IOVEC == 16
	case SC_REPR_STRUCT_IOVEC:
#define _IS_IOVECX64_2() (argtype == SC_REPR_STRUCT_IOVEC)
#endif /* HAVE_SC_REPR_STRUCT_IOVEC && __SIZEOF_IOVEC == 16 */
#if defined(HAVE_SC_REPR_STRUCT_IOVEC_C) && __SIZEOF_IOVEC == 16
	case SC_REPR_STRUCT_IOVEC_C:
#define _IS_IOVECX64_C_2() (argtype == SC_REPR_STRUCT_IOVEC_C)
#endif /* HAVE_SC_REPR_STRUCT_IOVEC_C && __SIZEOF_IOVEC == 16 */
#if defined(_IS_IOVECX64_1) && defined(_IS_IOVECX64_2)
#define _IS_IOVECX64() (_IS_IOVECX64_1() || _IS_IOVECX64_2())
#elif defined(_IS_IOVECX64_1)
#define _IS_IOVECX64 _IS_IOVECX64_1
#elif defined(_IS_IOVECX64_2)
#define _IS_IOVECX64 _IS_IOVECX64_2
#endif /* ... */
#if defined(_IS_IOVECX64_C_1) && defined(_IS_IOVECX64_C_2)
#define _IS_IOVECX64_C() (_IS_IOVECX64_C_1() || _IS_IOVECX64_C_2())
#elif defined(_IS_IOVECX64_C_1)
#define _IS_IOVECX64_C _IS_IOVECX64_C_1
#elif defined(_IS_IOVECX64_C_2)
#define _IS_IOVECX64_C _IS_IOVECX64_C_2
#endif /* ... */
	{
		NCX UNCHECKED struct iovecx64 *iov;
		size_t count;
		if unlikely(!link)
			goto do_pointer;
		iov = (NCX UNCHECKED struct iovecx64 *)(uintptr_t)value.sv_u64;
		if unlikely(!iov)
			goto do_pointer;
		count = (size_t)link->sa_value.sv_u64;
		validate_readablem(iov, count, sizeof(struct iovecx64));
#if defined(_IS_IOVECX64) && defined(_IS_IOVECX64_C)
		result = print_iovecx64(printer, arg, _IS_IOVECX64_C(), iov, count);
#elif defined(_IS_IOVECX64)
		result = print_iovecx64(printer, arg, false, iov, count);
#elif defined(_IS_IOVECX64_C)
		result = print_iovecx64(printer, arg, true, iov, count);
#else /* ... */
#error "Bad configuration"
#endif /* !... */
#undef _IS_IOVECX64
#undef _IS_IOVECX64_1
#undef _IS_IOVECX64_2
#undef _IS_IOVECX64_C
#undef _IS_IOVECX64_C_1
#undef _IS_IOVECX64_C_2
	}	break;
#endif /* ... */


#ifdef HAVE_SC_REPR_SEEK_WHENCE
	case SC_REPR_SEEK_WHENCE:
		result = print_seek_whence(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SEEK_WHENCE */

#ifdef HAVE_SC_REPR_STRUCT_SOCKADDR
	case SC_REPR_STRUCT_SOCKADDR: {
		NCX UNCHECKED struct sockaddr *sa;
		socklen_t len;
		if (!link)
			goto do_pointer;
		sa  = (NCX UNCHECKED struct sockaddr *)(uintptr_t)value.sv_u64;
		len = (socklen_t)link->sa_value.sv_u64;
		validate_readable(sa, len);
		result = print_sockaddr(printer, arg, sa, len);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SOCKADDR */

#ifdef HAVE_SC_REPR_IOCTL_COMMAND
	case SC_REPR_IOCTL_COMMAND:
		result = print_ioctl_command(printer, arg,
		                             (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_IOCTL_COMMAND */

#ifdef HAVE_SC_REPR_IOCTL_ARG
	case SC_REPR_IOCTL_ARG:
		if (!link)
			goto do_pointer;
		result = print_ioctl_arg(printer, arg,
		                         (syscall_ulong_t)link->sa_value.sv_u64,
		                         (void *)(uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_IOCTL_ARG */

#if defined(HAVE_SC_REPR_FCNTL64_COMMAND) || defined(HAVE_SC_REPR_FCNTL_COMMAND)
#ifdef HAVE_SC_REPR_FCNTL64_COMMAND
	case SC_REPR_FCNTL64_COMMAND:
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND */
#ifdef HAVE_SC_REPR_FCNTL_COMMAND
	case SC_REPR_FCNTL_COMMAND:
#endif /* HAVE_SC_REPR_FCNTL_COMMAND */
		result = print_fcntl_command(printer, arg,
		                             (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND || HAVE_SC_REPR_FCNTL_COMMAND */

#if defined(HAVE_SC_REPR_FCNTL64_ARG) || defined(HAVE_SC_REPR_FCNTL_ARG)
#ifdef HAVE_SC_REPR_FCNTL64_ARG
	case SC_REPR_FCNTL64_ARG:
#endif /* HAVE_SC_REPR_FCNTL64_ARG */
#ifdef HAVE_SC_REPR_FCNTL_ARG
	case SC_REPR_FCNTL_ARG:
#endif /* HAVE_SC_REPR_FCNTL_ARG */
		if unlikely(!link)
			goto do_pointer;
		result = print_fcntl_arg(printer, arg,
		                         (syscall_ulong_t)link->sa_value.sv_u64,
		                         (void *)(uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FCNTL64_ARG || HAVE_SC_REPR_FCNTL_ARG */

#ifdef HAVE_SC_REPR_SIGNO_T
	case SC_REPR_SIGNO_T:
		result = print_signo_t(printer, arg, (signo_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SIGNO_T */

#ifdef HAVE_SC_REPR_SOCKET_DOMAIN
	case SC_REPR_SOCKET_DOMAIN:
		result = print_socket_domain(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_DOMAIN */

#ifdef HAVE_SC_REPR_SOCKET_PROTOCOL
	case SC_REPR_SOCKET_PROTOCOL:
		result = print_socket_proto(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_PROTOCOL */

#ifdef HAVE_SC_REPR_SOCKET_TYPE
	case SC_REPR_SOCKET_TYPE:
		result = print_socket_type(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_TYPE */

#ifdef HAVE_SC_REPR_STRING_VECTOR
	case SC_REPR_STRING_VECTOR:
		result = print_string_vector(printer, arg,
		                             (NCX UNCHECKED char const *NCX UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             sizeof(void *)
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR */

#ifdef HAVE_SC_REPR_STRING_VECTOR32
	case SC_REPR_STRING_VECTOR32:
		result = print_string_vector(printer, arg,
		                             (NCX UNCHECKED char const *NCX UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             4
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR32 */

#ifdef HAVE_SC_REPR_STRING_VECTOR64
	case SC_REPR_STRING_VECTOR64:
		result = print_string_vector(printer, arg,
		                             (NCX UNCHECKED char const *NCX UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             8
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR64 */


#define DO_REPR_STRUCT_TIMEVAL_VEC2(struct_timeval_typecode)                      \
	do {                                                                          \
		struct timeval tsv[2];                                                    \
		NCX UNCHECKED struct_timeval_typecode *utms;                             \
		utms = (NCX UNCHECKED struct_timeval_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                        \
			goto do_null_pointer;                                                 \
		validate_readable(utms, 2 * sizeof(struct_timeval_typecode));             \
		COMPILER_READ_BARRIER();                                                  \
		tsv[0].tv_sec  = (time_t)utms[0].tv_sec;                                  \
		tsv[0].tv_usec = (syscall_ulong_t)utms[0].tv_usec;                        \
		tsv[1].tv_sec  = (time_t)utms[1].tv_sec;                                  \
		tsv[1].tv_usec = (syscall_ulong_t)utms[1].tv_usec;                        \
		COMPILER_READ_BARRIER();                                                  \
		result = print_timeval_vector(printer, arg, tsv, 2);                      \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2
	case SC_REPR_STRUCT_TIMEVAL_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2
	case SC_REPR_STRUCT_TIMEVAL32_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2
	case SC_REPR_STRUCT_TIMEVAL64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2
	case SC_REPR_STRUCT_TIMEVALX32_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2
	case SC_REPR_STRUCT_TIMEVALX32_64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2
	case SC_REPR_STRUCT_TIMEVALX64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2 */
#undef DO_REPR_STRUCT_TIMEVAL_VEC2


#define DO_REPR_STRUCT_TIMEVAL(struct_timeval_typecode)                           \
	do {                                                                          \
		struct timeval ts;                                                        \
		NCX UNCHECKED struct_timeval_typecode *utms;                             \
		utms = (NCX UNCHECKED struct_timeval_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                        \
			goto do_null_pointer;                                                 \
		validate_readable(utms, sizeof(struct_timeval_typecode));                 \
		COMPILER_READ_BARRIER();                                                  \
		ts.tv_sec  = (time_t)utms->tv_sec;                                        \
		ts.tv_usec = (syscall_ulong_t)utms->tv_usec;                              \
		COMPILER_READ_BARRIER();                                                  \
		result = print_timeval(printer, arg, &ts);                                \
	}	__WHILE0

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL) || defined(NEED_do_struct_timeval)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL
	case SC_REPR_STRUCT_TIMEVAL:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL */
#ifdef NEED_do_struct_timeval
do_struct_timeval:
#endif /* NEED_do_struct_timeval */
		DO_REPR_STRUCT_TIMEVAL(struct timeval);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL || NEED_do_struct_timeval */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL32) || defined(NEED_do_struct_timeval32)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32
	case SC_REPR_STRUCT_TIMEVAL32:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 */
#ifdef NEED_do_struct_timeval32
do_struct_timeval32:
#endif /* NEED_do_struct_timeval32 */
		DO_REPR_STRUCT_TIMEVAL(struct timeval32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 || NEED_do_struct_timeval32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL64) || defined(NEED_do_struct_timeval64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64
	case SC_REPR_STRUCT_TIMEVAL64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 */
#ifdef NEED_do_struct_timeval64
do_struct_timeval64:
#endif /* NEED_do_struct_timeval64 */
		DO_REPR_STRUCT_TIMEVAL(struct timeval64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 || NEED_do_struct_timeval64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX32) || defined(NEED_do_struct_timevalx32)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32
	case SC_REPR_STRUCT_TIMEVALX32:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 */
#ifdef NEED_do_struct_timevalx32
do_struct_timevalx32:
#endif /* NEED_do_struct_timevalx32 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 || NEED_do_struct_timevalx32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX32_64) || defined(NEED_do_struct_timevalx32_64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64
	case SC_REPR_STRUCT_TIMEVALX32_64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 */
#ifdef NEED_do_struct_timevalx32_64
do_struct_timevalx32_64:
#endif /* NEED_do_struct_timevalx32_64 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 || NEED_do_struct_timevalx32_64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX64) || defined(NEED_do_struct_timevalx64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64
	case SC_REPR_STRUCT_TIMEVALX64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 */
#ifdef NEED_do_struct_timevalx64
do_struct_timevalx64:
#endif /* NEED_do_struct_timevalx64 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 || NEED_do_struct_timevalx64 */
#undef DO_REPR_STRUCT_TIMEVAL



#define DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct_timespec_typecode)                \
	do {                                                                           \
		size_t count = 2;                                                          \
		struct timespec tsv[3];                                                    \
		NCX UNCHECKED struct_timespec_typecode *utms;                             \
		utms = (NCX UNCHECKED struct_timespec_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                         \
			goto do_null_pointer;                                                  \
		if (link && ((syscall_ulong_t)link->sa_value.sv_u64 & AT_CHANGE_BTIME))    \
			count = 3;                                                             \
		validate_readablem(utms, count, sizeof(struct_timespec_typecode));         \
		COMPILER_READ_BARRIER();                                                   \
		tsv[0].tv_sec  = (time_t)utms[0].tv_sec;                                   \
		tsv[0].tv_nsec = (syscall_ulong_t)utms[0].tv_nsec;                         \
		tsv[1].tv_sec  = (time_t)utms[1].tv_sec;                                   \
		tsv[1].tv_nsec = (syscall_ulong_t)utms[1].tv_nsec;                         \
		if (count >= 3) {                                                          \
			tsv[2].tv_sec  = (time_t)utms[2].tv_sec;                               \
			tsv[2].tv_nsec = (syscall_ulong_t)utms[2].tv_nsec;                     \
		}                                                                          \
		COMPILER_READ_BARRIER();                                                   \
		result = print_timespec_vector(printer, arg, tsv, count);                  \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3 */
#undef DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3



#define DO_REPR_STRUCT_TIMESPEC_OR_UINT32()                                            \
	do {                                                                               \
		if (!link || LINUX_FUTEX_USES_TIMEOUT((syscall_ulong_t)link->sa_value.sv_u64)) \
			goto do_uint32_t;                                                          \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32
	case SC_REPR_STRUCT_TIMESPEC32_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespec32;
#define NEED_do_struct_timespec32
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPEC64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespec64;
#define NEED_do_struct_timespec64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX32_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx32;
#define NEED_do_struct_timespecx32
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx32_64;
#define NEED_do_struct_timespecx32_64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx64;
#define NEED_do_struct_timespecx64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32 */
#undef DO_REPR_STRUCT_TIMESPEC_OR_UINT32



#define DO_REPR_STRUCT_TIMESPEC(struct_timespec_typecode)                          \
	do {                                                                           \
		struct timespec ts;                                                        \
		NCX UNCHECKED struct_timespec_typecode *utms;                             \
		utms = (NCX UNCHECKED struct_timespec_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                         \
			goto do_null_pointer;                                                  \
		validate_readable(utms, sizeof(struct_timespec_typecode));                 \
		COMPILER_READ_BARRIER();                                                   \
		ts.tv_sec  = (time_t)utms->tv_sec;                                         \
		ts.tv_nsec = (syscall_ulong_t)utms->tv_nsec;                               \
		COMPILER_READ_BARRIER();                                                   \
		result = print_timespec(printer, arg, &ts);                                \
	}	__WHILE0

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC) || defined(NEED_do_struct_timespec)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC
	case SC_REPR_STRUCT_TIMESPEC:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC */
#ifdef NEED_do_struct_timespec
do_struct_timespec:
#endif /* NEED_do_struct_timespec */
		DO_REPR_STRUCT_TIMESPEC(struct timespec);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC || NEED_do_struct_timespec */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC32) || defined(NEED_do_struct_timespec32)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32
	case SC_REPR_STRUCT_TIMESPEC32:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 */
#ifdef NEED_do_struct_timespec32
do_struct_timespec32:
#endif /* NEED_do_struct_timespec32 */
		DO_REPR_STRUCT_TIMESPEC(struct timespec32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 || NEED_do_struct_timespec32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC64) || defined(NEED_do_struct_timespec64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64
	case SC_REPR_STRUCT_TIMESPEC64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 */
#ifdef NEED_do_struct_timespec64
do_struct_timespec64:
#endif /* NEED_do_struct_timespec64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespec64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 || NEED_do_struct_timespec64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX32) || defined(NEED_do_struct_timespecx32)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32
	case SC_REPR_STRUCT_TIMESPECX32:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 */
#ifdef NEED_do_struct_timespecx32
do_struct_timespecx32:
#endif /* NEED_do_struct_timespecx32 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 || NEED_do_struct_timespecx32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX32_64) || defined(NEED_do_struct_timespecx32_64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64
	case SC_REPR_STRUCT_TIMESPECX32_64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 */
#ifdef NEED_do_struct_timespecx32_64
do_struct_timespecx32_64:
#endif /* NEED_do_struct_timespecx32_64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 || NEED_do_struct_timespecx32_64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX64) || defined(NEED_do_struct_timespecx64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64
	case SC_REPR_STRUCT_TIMESPECX64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 */
#ifdef NEED_do_struct_timespecx64
do_struct_timespecx64:
#endif /* NEED_do_struct_timespecx64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 || NEED_do_struct_timespecx64 */
#undef DO_REPR_STRUCT_TIMESPEC



#ifdef HAVE_SC_REPR_STRUCT_POLLFD
	case SC_REPR_STRUCT_POLLFD: {
		NCX UNCHECKED struct pollfd *fds;
		size_t count = 1;
		if (link)
			count = (size_t)link->sa_value.sv_u64;
		fds = (NCX UNCHECKED struct pollfd *)(uintptr_t)value.sv_u64;
		if unlikely(!fds)
			goto do_null_pointer;
		validate_readablem(fds, count, sizeof(struct pollfd));
		result = print_pollfds(printer, arg, fds, count);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_POLLFD */

#ifdef HAVE_SC_REPR_SIGHANDLER_T
	case SC_REPR_SIGHANDLER_T: {
		result = print_sighandler_t(printer, arg, (void *)(uintptr_t)value.sv_u64);
	}	break;
#endif /* HAVE_SC_REPR_SIGHANDLER_T */

#ifdef HAVE_SC_REPR_EXCEPT_HANDLER_T
	case SC_REPR_EXCEPT_HANDLER_T:
		goto do_pointer;
#endif /* HAVE_SC_REPR_EXCEPT_HANDLER_T */

#ifdef HAVE_SC_REPR_FILENAME
	case SC_REPR_FILENAME:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64, NULL);
		break;
#endif /* HAVE_SC_REPR_FILENAME */

#ifdef HAVE_SC_REPR_BUFFER
	case SC_REPR_BUFFER:
		if unlikely(!link)
			goto do_pointer;
		result = print_string_or_buffer(printer, arg,
		                                (void const *)(uintptr_t)value.sv_u64,
		                                (size_t)link->sa_value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_BUFFER */

#ifdef HAVE_SC_REPR_STRING
	case SC_REPR_STRING:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64, link);
		break;
#endif /* HAVE_SC_REPR_STRING */

#ifdef HAVE_SC_REPR_CLOCKID_T
	case SC_REPR_CLOCKID_T:
		result = print_clockid_t(printer, arg, (clockid_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_CLOCKID_T */

#ifdef HAVE_SC_REPR_FD_T
	case SC_REPR_FD_T:
		result = print_fd_t(printer, arg, (fd_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FD_T */

#ifdef HAVE_SC_REPR_ERRNO_T
	case SC_REPR_ERRNO_T: {
		char const *name;
		ssize_t temp;
		errno_t eno;
		eno = (errno_t)value.sv_u64;
		result = 0;
		if (eno < 0) {
			result = (*printer)(arg, "-", 1);
			if unlikely(result < 0)
				goto done;
			eno = -eno;
		}
		name = strerrorname_np(eno);
		if likely(name) {
			temp = (*printer)(arg, name, strlen(name));
		} else {
			temp = format_printf("%" PRIuN(__SIZEOF_ERRNO_T__), eno);
		}
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}	break;
#endif /* HAVE_SC_REPR_ERRNO_T */

#ifdef HAVE_SC_REPR_IOMODE_T
	case SC_REPR_IOMODE_T:
		result = print_iomode_t(printer, arg, (iomode_t)value.sv_u64, ~0);
		break;
#endif /* HAVE_SC_REPR_IOMODE_T */

#ifdef HAVE_SC_REPR_ATFLAG_T
	case SC_REPR_ATFLAG_T:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64, ~0, NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG_T */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__DOSPATH
	case SC_REPR_ATFLAG__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_DOSPATH, NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH
	case SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH
	case SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH
	case SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH,
		                        "AT_CHANGE_BTIME");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH,
		                        "AT_EACCESS");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH */

#ifdef HAVE_SC_REPR_OFLAG_T
	case SC_REPR_OFLAG_T:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64, ~0);
		break;
#endif /* HAVE_SC_REPR_OFLAG_T */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK | O_NONBLOCK);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT */

#ifdef HAVE_SC_REPR_MODE_T
	case SC_REPR_MODE_T:
		/* Handle the special  case of  the 3rd  argument
		 * to sys_open(), where the mode value is ignored */
		if (link &&
		    (link->sa_value.sv_u64 & O_CREAT) != O_CREAT &&
		    (link->sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
			value.sv_u64 = 0;
		result = print_mode_t(printer, arg, (mode_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_MODE_T */

#ifdef HAVE_SC_REPR_DEV_T
	case SC_REPR_DEV_T: {
		dev_t devno = (dev_t)value.sv_u64;
		if (link) {
			mode_t linked_mode = (mode_t)link->sa_value.sv_u64;
			if (S_ISDEV(linked_mode)) {
				result = print_dev(printer, arg, linked_mode, devno);
				break;
			}
		}
		result = format_printf(printer, arg,
		                       "?"
		                       ":%" PRIuN(__SIZEOF_MAJOR_T__)
		                       ":%" PRIuN(__SIZEOF_MINOR_T__),
		                       major(devno), minor(devno));
	}	break;
#endif /* HAVE_SC_REPR_DEV_T */

#ifdef HAVE_SC_REPR_DEV_BLK
	case SC_REPR_DEV_BLK: {
		dev_t devno = (dev_t)value.sv_u64;
		result = print_dev(printer, arg, S_IFBLK, devno);
	}	break;
#endif /* HAVE_SC_REPR_DEV_BLK */

#ifdef HAVE_SC_REPR_DEV_CHR
	case SC_REPR_DEV_CHR: {
		dev_t devno = (dev_t)value.sv_u64;
		result = print_dev(printer, arg, S_IFCHR, devno);
	}	break;
#endif /* HAVE_SC_REPR_DEV_CHR */

#ifdef HAVE_SC_REPR_TIME_T
	case SC_REPR_TIME_T:
#if __SIZEOF_TIME_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_TIME_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_TIME_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_TIME_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_TIME_T__ == ... */
#error "Unsupported `__SIZEOF_TIME_T__'"
#endif /* __SIZEOF_TIME_T__ != ... */
#endif /* HAVE_SC_REPR_TIME_T */


		/* Escape character constants. */
#ifdef HAVE_SC_REPR_CHAR
	case SC_REPR_CHAR:
		format = "%Q";
#if __SIZEOF_CHAR__ == 1
#define NEED_do_format8
		goto do_format8;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_format64
		goto do_format64;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_CHAR */

#ifdef HAVE_SC_REPR_GID_T
		case SC_REPR_GID_T:
#if __SIZEOF_GID_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_GID_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_GID_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_GID_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_GID_T__ == ... */
#error "Unsupported `__SIZEOF_GID_T__'"
#endif /* __SIZEOF_GID_T__ != ... */
#endif /* HAVE_SC_REPR_GID_T */

#ifdef HAVE_SC_REPR_UID_T
		case SC_REPR_UID_T:
#if __SIZEOF_UID_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_UID_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_UID_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_UID_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_UID_T__ == ... */
#error "Unsupported `__SIZEOF_UID_T__'"
#endif /* __SIZEOF_UID_T__ != ... */
#endif /* HAVE_SC_REPR_UID_T */

#ifdef HAVE_SC_REPR_ID_T
		case SC_REPR_ID_T:
#if __SIZEOF_ID_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_ID_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_ID_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_ID_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_ID_T__ == ... */
#error "Unsupported `__SIZEOF_ID_T__'"
#endif /* __SIZEOF_ID_T__ != ... */
#endif /* HAVE_SC_REPR_ID_T */

#ifdef HAVE_SC_REPR_PID_T
		case SC_REPR_PID_T:
#if __SIZEOF_PID_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_PID_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_PID_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_PID_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_PID_T__ == ... */
#error "Unsupported `__SIZEOF_PID_T__'"
#endif /* __SIZEOF_PID_T__ != ... */
#endif /* HAVE_SC_REPR_PID_T */

#ifdef HAVE_SC_REPR_TIMER_T
	case SC_REPR_TIMER_T:
		goto do_uintptr_t;
#define NEED_do_uintptr_t
#endif /* HAVE_SC_REPR_TIMER_T */

	case SC_REPR_POINTER:
do_pointer: ATTR_UNUSED;
		if (value.sv_u64 == 0) {
do_null_pointer: ATTR_UNUSED;
			result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
			break;
		}
		goto do_uintptr_t;
#define NEED_do_uintptr_t

#if defined(HAVE_SC_REPR_INTPTR_T) || defined(NEED_do_intptr_t)
#ifdef HAVE_SC_REPR_INTPTR_T
	case SC_REPR_INTPTR_T:
#endif /* HAVE_SC_REPR_INTPTR_T */
#ifdef NEED_do_intptr_t
do_intptr_t:
#endif /* NEED_do_intptr_t */
		format = "%#tx"; /* Signed, ptrdiff_t-sized printf */
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_INTPTR_T || NEED_do_intptr_t */

#if defined(HAVE_SC_REPR_UINTPTR_T) || defined(NEED_do_uintptr_t)
#ifdef HAVE_SC_REPR_UINTPTR_T
	case SC_REPR_UINTPTR_T:
#endif /* HAVE_SC_REPR_UINTPTR_T */
#ifdef NEED_do_uintptr_t
do_uintptr_t:
#endif /* NEED_do_uintptr_t */
		format = "%#" PRIxPTR;
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#elif !defined(__DEEMON__)
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* ... */
#endif /* HAVE_SC_REPR_UINTPTR_T || NEED_do_uintptr_t */

#if defined(HAVE_SC_REPR_SYSCALL_SLONG_T) || defined(NEED_do_syscall_slong_t)
#ifdef HAVE_SC_REPR_SYSCALL_SLONG_T
	case SC_REPR_SYSCALL_SLONG_T:
#endif /* HAVE_SC_REPR_SYSCALL_SLONG_T */
#ifdef NEED_do_syscall_slong_t
do_syscall_slong_t:
#endif /* NEED_do_syscall_slong_t */
		format = "%" PRIdPTR;
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_SYSCALL_SLONG_T || NEED_do_syscall_slong_t */

#if defined(HAVE_SC_REPR_SYSCALL_ULONG_T) || defined(NEED_do_syscall_ulong_t)
#ifdef HAVE_SC_REPR_SYSCALL_ULONG_T
	case SC_REPR_SYSCALL_ULONG_T:
#endif /* HAVE_SC_REPR_SYSCALL_ULONG_T */
#ifdef NEED_do_syscall_ulong_t
do_syscall_ulong_t:
#endif /* NEED_do_syscall_ulong_t */
		format = "%" PRIuPTR;
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_SYSCALL_ULONG_T || NEED_do_syscall_ulong_t */

#ifdef HAVE_SC_REPR_SIGNED_CHAR
		case SC_REPR_SIGNED_CHAR:
#if __SIZEOF_CHAR__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_SIGNED_CHAR */

#ifdef HAVE_SC_REPR_UNSIGNED_CHAR
		case SC_REPR_UNSIGNED_CHAR:
#if __SIZEOF_CHAR__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_CHAR */

#ifdef HAVE_SC_REPR_SHORT
		case SC_REPR_SHORT:
#if __SIZEOF_SHORT__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_SHORT__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_SHORT__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_SHORT__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_SHORT__ == ... */
#error "Unsupported `__SIZEOF_SHORT__'"
#endif /* __SIZEOF_SHORT__ != ... */
#endif /* HAVE_SC_REPR_SHORT */

#ifdef HAVE_SC_REPR_UNSIGNED_SHORT
		case SC_REPR_UNSIGNED_SHORT:
#if __SIZEOF_SHORT__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SHORT__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SHORT__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SHORT__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SHORT__ == ... */
#error "Unsupported `__SIZEOF_SHORT__'"
#endif /* __SIZEOF_SHORT__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_SHORT */

#ifdef HAVE_SC_REPR_INT
		case SC_REPR_INT:
#if __SIZEOF_INT__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_INT__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_INT__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_INT__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported `__SIZEOF_INT__'"
#endif /* __SIZEOF_INT__ != ... */
#endif /* HAVE_SC_REPR_INT */

#ifdef HAVE_SC_REPR_UNSIGNED_INT
		case SC_REPR_UNSIGNED_INT:
#if __SIZEOF_INT__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_INT__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_INT__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_INT__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported `__SIZEOF_INT__'"
#endif /* __SIZEOF_INT__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_INT */

#ifdef HAVE_SC_REPR_LONG
		case SC_REPR_LONG:
#if __SIZEOF_LONG__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_LONG__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_LONG__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_LONG__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG__'"
#endif /* __SIZEOF_LONG__ != ... */
#endif /* HAVE_SC_REPR_LONG */

#ifdef HAVE_SC_REPR_UNSIGNED_LONG
		case SC_REPR_UNSIGNED_LONG:
#if __SIZEOF_LONG__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_LONG__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_LONG__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_LONG__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG__'"
#endif /* __SIZEOF_LONG__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_LONG */

#ifdef HAVE_SC_REPR_LONG_LONG
		case SC_REPR_LONG_LONG:
#if __SIZEOF_LONG_LONG__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_LONG_LONG__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_LONG_LONG__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_LONG_LONG__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_LONG_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG_LONG__'"
#endif /* __SIZEOF_LONG_LONG__ != ... */
#endif /* HAVE_SC_REPR_LONG_LONG */

#ifdef HAVE_SC_REPR_UNSIGNED_LONG_LONG
		case SC_REPR_UNSIGNED_LONG_LONG:
#if __SIZEOF_LONG_LONG__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_LONG_LONG__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_LONG_LONG__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_LONG_LONG__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_LONG_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG_LONG__'"
#endif /* __SIZEOF_LONG_LONG__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_LONG_LONG */

#ifdef HAVE_SC_REPR_PTRDIFF_T
		case SC_REPR_PTRDIFF_T:
#if __SIZEOF_PTRDIFF_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_PTRDIFF_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_PTRDIFF_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_PTRDIFF_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_PTRDIFF_T__ == ... */
#error "Unsupported `__SIZEOF_PTRDIFF_T__'"
#endif /* __SIZEOF_PTRDIFF_T__ != ... */
#endif /* HAVE_SC_REPR_PTRDIFF_T */

#ifdef HAVE_SC_REPR_SSIZE_T
		case SC_REPR_SSIZE_T:
#if __SIZEOF_SSIZE_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_SSIZE_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_SSIZE_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_SSIZE_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_SSIZE_T__ == ... */
#error "Unsupported `__SIZEOF_SSIZE_T__'"
#endif /* __SIZEOF_SSIZE_T__ != ... */
#endif /* HAVE_SC_REPR_SSIZE_T */

#ifdef HAVE_SC_REPR_SIZE_T
		case SC_REPR_SIZE_T:
#if __SIZEOF_SIZE_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SIZE_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SIZE_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SIZE_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SIZE_T__ == ... */
#error "Unsupported `__SIZEOF_SIZE_T__'"
#endif /* __SIZEOF_SIZE_T__ != ... */
#endif /* HAVE_SC_REPR_SIZE_T */

#ifdef HAVE_SC_REPR_SOCKLEN_T
		case SC_REPR_SOCKLEN_T:
#if __SIZEOF_SOCKLEN_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SOCKLEN_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SOCKLEN_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SOCKLEN_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SOCKLEN_T__ == ... */
#error "Unsupported `__SIZEOF_SOCKLEN_T__'"
#endif /* __SIZEOF_SOCKLEN_T__ != ... */
#endif /* HAVE_SC_REPR_SOCKLEN_T */


		/* ========== SC_REPR_INT8_T ========== */
#if defined(HAVE_SC_REPR_INT8_T) || defined(NEED_do_int8_t)
#ifdef HAVE_SC_REPR_INT8_T
	case SC_REPR_INT8_T:
#endif /* HAVE_SC_REPR_INT8_T */
#ifdef NEED_do_int8_t
do_int8_t:
#endif /* NEED_do_int8_t */
		format = "%" PRId8;
#define NEED_do_format8
		goto do_format8;
#endif /* HAVE_SC_REPR_INT8_T || NEED_do_int8_t */


		/* ========== SC_REPR_INT16_T ========== */
#if defined(HAVE_SC_REPR_INT16_T) || defined(NEED_do_int16_t)
#ifdef HAVE_SC_REPR_INT16_T
	case SC_REPR_INT16_T:
#endif /* HAVE_SC_REPR_INT16_T */
#ifdef NEED_do_int16_t
do_int16_t:
#endif /* NEED_do_int16_t */
		format = "%" PRId16;
#define NEED_do_format16
		goto do_format16;
#endif /* HAVE_SC_REPR_INT16_T || NEED_do_int16_t */


		/* ========== SC_REPR_INT32_T ========== */
#if defined(HAVE_SC_REPR_INT32_T) || defined(NEED_do_int32_t)
#ifdef HAVE_SC_REPR_INT32_T
	case SC_REPR_INT32_T:
#endif /* HAVE_SC_REPR_INT32_T */
#ifdef NEED_do_int32_t
do_int32_t:
#endif /* NEED_do_int32_t */
		format = "%" PRId32;
#define NEED_do_format32
		goto do_format32;
#endif /* HAVE_SC_REPR_INT32_T || NEED_do_int32_t */


		/* ========== SC_REPR_INT64_T ========== */
#if defined(HAVE_SC_REPR_INT64_T) || defined(NEED_do_int64_t)
#ifdef HAVE_SC_REPR_INT64_T
	case SC_REPR_INT64_T:
#endif /* HAVE_SC_REPR_INT64_T */
#ifdef NEED_do_int64_t
do_int64_t:
#endif /* NEED_do_int64_t */
		format = "%" PRId64;
#define NEED_do_format64
		goto do_format64;
#endif /* HAVE_SC_REPR_INT64_T || NEED_do_int64_t */


		/* ========== SC_REPR_UINT8_T ========== */
#if defined(HAVE_SC_REPR_UINT8_T) || defined(NEED_do_uint8_t)
#ifdef HAVE_SC_REPR_UINT8_T
	case SC_REPR_UINT8_T:
#endif /* HAVE_SC_REPR_UINT8_T */
#ifdef NEED_do_uint8_t
do_uint8_t:
#endif /* NEED_do_uint8_t */
		format = "%" PRIu8;
#define NEED_do_format8
		goto do_format8;
#endif /* HAVE_SC_REPR_UINT8_T || NEED_do_uint8_t */


		/* ========== SC_REPR_UINT16_T ========== */
#if defined(HAVE_SC_REPR_UINT16_T) || defined(NEED_do_uint16_t)
#ifdef HAVE_SC_REPR_UINT16_T
	case SC_REPR_UINT16_T:
#endif /* HAVE_SC_REPR_UINT16_T */
#ifdef NEED_do_uint16_t
do_uint16_t:
#endif /* NEED_do_uint16_t */
		format = "%" PRIu16;
#define NEED_do_format16
		goto do_format16;
#endif /* HAVE_SC_REPR_UINT16_T || NEED_do_uint16_t */


		/* ========== SC_REPR_UINT32_T ========== */
#if defined(HAVE_SC_REPR_UINT32_T) || defined(NEED_do_uint32_t)
#ifdef HAVE_SC_REPR_UINT32_T
	case SC_REPR_UINT32_T:
#endif /* HAVE_SC_REPR_UINT32_T */
#ifdef NEED_do_uint32_t
do_uint32_t:
#endif /* NEED_do_uint32_t */
		format = "%" PRIu32;
#define NEED_do_format32
		goto do_format32;
#endif /* HAVE_SC_REPR_UINT32_T || NEED_do_uint32_t */


		/* ========== SC_REPR_UINT64_T ========== */
#if defined(HAVE_SC_REPR_UINT64_T) || defined(NEED_do_uint64_t)
#ifdef HAVE_SC_REPR_UINT64_T
	case SC_REPR_UINT64_T:
#endif /* HAVE_SC_REPR_UINT64_T */
#ifdef NEED_do_uint64_t
do_uint64_t:
#endif /* NEED_do_uint64_t */
		format = "%" PRIu64;
#define NEED_do_format64
		goto do_format64;
#endif /* HAVE_SC_REPR_UINT64_T || NEED_do_uint64_t */





#ifdef NEED_do_format64
#undef NEED_do_format64
do_format64:
		result = format_printf(printer, arg, format, value.sv_u64);
		break;
#endif /* NEED_do_format64 */

#ifdef NEED_do_format32
#undef NEED_do_format32
do_format32:
		result = format_printf(printer, arg, format, (u32)value.sv_u64);
		break;
#endif /* NEED_do_format32 */

#ifdef NEED_do_format16
#undef NEED_do_format16
do_format16:
		result = format_printf(printer, arg, format, (u16)value.sv_u64);
		break;
#endif /* NEED_do_format16 */

#ifdef NEED_do_format8
#undef NEED_do_format8
do_format8:
		result = format_printf(printer, arg, format, (u8)value.sv_u64);
		break;
#endif /* NEED_do_format8 */

	default:
#if 1
		result = format_printf(printer, arg, "%p",
		                       (uintptr_t)value.sv_u64);
#else
		result = DOPRINT("?");
#endif
		break;
	}
done: ATTR_UNUSED;
	return result;
}

DEFINE_PUBLIC_ALIAS(sc_printvalue, libsc_printvalue);

DECL_END

#endif /* !GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C */
