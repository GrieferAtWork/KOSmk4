/* HASH CRC-32:0xcbad460c */
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

#ifndef __SYSCALL_REPR
#define __SYSCALL_REPR(id) /* nothing */
#endif /* !__SYSCALL_REPR */

#ifdef __WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES
#define HAVE_SC_REPR_ACCEPT4_FLAGS
#define HAVE_SC_REPR_ACCESS_TYPE
#define HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH
#define HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH
#define HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH
#define HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH
#define HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH
#define HAVE_SC_REPR_BUFFER
#define HAVE_SC_REPR_CHAR
#define HAVE_SC_REPR_CLOCKID_T
#define HAVE_SC_REPR_CLONE_FLAGS
#define HAVE_SC_REPR_CLONE_FLAGS_SETNS
#define HAVE_SC_REPR_CLONE_FLAGS_UNSHARE
#define HAVE_SC_REPR_CPUSET
#define HAVE_SC_REPR_DEV_BLK
#define HAVE_SC_REPR_DEV_T
#define HAVE_SC_REPR_EPOLL_CREATE1_FLAGS
#define HAVE_SC_REPR_EPOLL_OP
#define HAVE_SC_REPR_EVENTFD2_FLAGS
#define HAVE_SC_REPR_EXIT_STATUS
#define HAVE_SC_REPR_FALLOCATE_MODE
#define HAVE_SC_REPR_FCNTL_ARG
#define HAVE_SC_REPR_FCNTL_COMMAND
#define HAVE_SC_REPR_FD_T
#define HAVE_SC_REPR_FILENAME
#define HAVE_SC_REPR_FUTEX_OP
#define HAVE_SC_REPR_GETRANDOM_FLAGS
#define HAVE_SC_REPR_GETRUSAGE_WHO
#define HAVE_SC_REPR_GID_T
#define HAVE_SC_REPR_GID_VECTOR
#define HAVE_SC_REPR_IDTYPE_T
#define HAVE_SC_REPR_ID_T
#define HAVE_SC_REPR_INOTIFY_INIT_FLAGS
#define HAVE_SC_REPR_INOTIFY_MASK
#define HAVE_SC_REPR_INT
#define HAVE_SC_REPR_IOCTL_ARG
#define HAVE_SC_REPR_IOCTL_COMMAND
#define HAVE_SC_REPR_IOPRIO_ID
#define HAVE_SC_REPR_IOPRIO_VALUE
#define HAVE_SC_REPR_IOPRIO_WHO
#define HAVE_SC_REPR_ITIMER_WHICH
#define HAVE_SC_REPR_KCMP_TYPE
#define HAVE_SC_REPR_MEMFD_CREATE_FLAGS
#define HAVE_SC_REPR_MLOCKALL_FLAGS
#define HAVE_SC_REPR_MMAP_FLAGS
#define HAVE_SC_REPR_MMAP_PROT
#define HAVE_SC_REPR_MODE_T
#define HAVE_SC_REPR_MOUNT_FLAGS
#define HAVE_SC_REPR_MREMAP_FLAGS
#define HAVE_SC_REPR_OFLAG_T
#define HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK
#define HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT
#define HAVE_SC_REPR_PID_T
#define HAVE_SC_REPR_POINTER
#define HAVE_SC_REPR_PRCTL_COMMAND
#define HAVE_SC_REPR_REBOOT_HOW
#define HAVE_SC_REPR_RENAMEAT2_FLAGS
#define HAVE_SC_REPR_RLIMIT_RESOURCE
#define HAVE_SC_REPR_SCHED_POLICY
#define HAVE_SC_REPR_SCHED_PRIORITY_WHICH
#define HAVE_SC_REPR_SEEK_WHENCE
#define HAVE_SC_REPR_SIGNALFD4_FLAGS
#define HAVE_SC_REPR_SIGNO_T
#define HAVE_SC_REPR_SIGPROCMASK_HOW
#define HAVE_SC_REPR_SIZE_T
#define HAVE_SC_REPR_SOCKET_DOMAIN
#define HAVE_SC_REPR_SOCKET_PROTOCOL
#define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS
#define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2
#define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS3
#define HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS
#define HAVE_SC_REPR_SOCKET_SHUTDOWN_HOW
#define HAVE_SC_REPR_SOCKET_TYPE
#define HAVE_SC_REPR_SOCKLEN_T
#define HAVE_SC_REPR_SOCKOPT_LEVEL
#define HAVE_SC_REPR_SOCKOPT_OPTNAME
#define HAVE_SC_REPR_SOCKOPT_OPTVAL
#define HAVE_SC_REPR_SPLICE_FLAGS
#define HAVE_SC_REPR_STRING
#define HAVE_SC_REPR_STRING_VECTOR
#define HAVE_SC_REPR_STRUCT_EPOLL_EVENT
#define HAVE_SC_REPR_STRUCT_FDSET
#define HAVE_SC_REPR_STRUCT_FILE_HANDLE
#define HAVE_SC_REPR_STRUCT_IOVEC
#define HAVE_SC_REPR_STRUCT_IOVEC_C
#define HAVE_SC_REPR_STRUCT_ITIMERSPEC
#define HAVE_SC_REPR_STRUCT_ITIMERVAL
#define HAVE_SC_REPR_STRUCT_KERNEL_SIGACTION
#define HAVE_SC_REPR_STRUCT_MMSGHDR
#define HAVE_SC_REPR_STRUCT_MQ_ATTR
#define HAVE_SC_REPR_STRUCT_MSGHDR
#define HAVE_SC_REPR_STRUCT_POLLFD
#define HAVE_SC_REPR_STRUCT_RLIMIT
#define HAVE_SC_REPR_STRUCT_RLIMIT64
#define HAVE_SC_REPR_STRUCT_SCHED_PARAM
#define HAVE_SC_REPR_STRUCT_SIGALTSTACK
#define HAVE_SC_REPR_STRUCT_SIGEVENT
#define HAVE_SC_REPR_STRUCT_SIGINFO
#define HAVE_SC_REPR_STRUCT_SIGSET
#define HAVE_SC_REPR_STRUCT_SIGSET_WITH_SIZE
#define HAVE_SC_REPR_STRUCT_SOCKADDR
#define HAVE_SC_REPR_STRUCT_TIMESPEC
#define HAVE_SC_REPR_STRUCT_TIMESPEC_OR_UINT32
#define HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3
#define HAVE_SC_REPR_STRUCT_TIMEVAL
#define HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2
#define HAVE_SC_REPR_STRUCT_TIMEZONE
#define HAVE_SC_REPR_STRUCT_UTIMBUF
#define HAVE_SC_REPR_SWAPFLAGS
#define HAVE_SC_REPR_SYNC_FILE_RANGE_FLAGS
#define HAVE_SC_REPR_SYSCALL_SLONG_T
#define HAVE_SC_REPR_SYSCALL_ULONG_T
#define HAVE_SC_REPR_SYSLOG_LEVEL
#define HAVE_SC_REPR_TIMERFD_FLAGS
#define HAVE_SC_REPR_TIMERFD_TIMER_FLAGS
#define HAVE_SC_REPR_TIMER_FLAGS
#define HAVE_SC_REPR_TIMER_T
#define HAVE_SC_REPR_UID_T
#define HAVE_SC_REPR_UINT32_T
#define HAVE_SC_REPR_UINT64_T
#define HAVE_SC_REPR_WAITFLAGS
#define HAVE_SC_REPR_XATTR_FLAGS
#endif /* __WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES */

#ifdef __WANT_HAVE_SYSCALL_RETURN_REPR_TYPES
#define HAVE_SC_REPR_ERRNO_T
#define HAVE_SC_REPR_SSIZE_T
#define HAVE_SC_REPR_TIME_T
#endif /* __WANT_HAVE_SYSCALL_RETURN_REPR_TYPES */

#ifdef __WANT_SYSCALL_ARGUMENT_REPR_TYPES
__SYSCALL_REPR(SC_REPR_ACCEPT4_FLAGS)
__SYSCALL_REPR(SC_REPR_ACCESS_TYPE)
__SYSCALL_REPR(SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH)
__SYSCALL_REPR(SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH)
__SYSCALL_REPR(SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH)
__SYSCALL_REPR(SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH)
__SYSCALL_REPR(SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH)
__SYSCALL_REPR(SC_REPR_BUFFER)
__SYSCALL_REPR(SC_REPR_CHAR)
__SYSCALL_REPR(SC_REPR_CLOCKID_T)
__SYSCALL_REPR(SC_REPR_CLONE_FLAGS)
__SYSCALL_REPR(SC_REPR_CLONE_FLAGS_SETNS)
__SYSCALL_REPR(SC_REPR_CLONE_FLAGS_UNSHARE)
__SYSCALL_REPR(SC_REPR_CPUSET)
__SYSCALL_REPR(SC_REPR_DEV_BLK)
__SYSCALL_REPR(SC_REPR_DEV_T)
__SYSCALL_REPR(SC_REPR_EPOLL_CREATE1_FLAGS)
__SYSCALL_REPR(SC_REPR_EPOLL_OP)
__SYSCALL_REPR(SC_REPR_EVENTFD2_FLAGS)
__SYSCALL_REPR(SC_REPR_EXIT_STATUS)
__SYSCALL_REPR(SC_REPR_FALLOCATE_MODE)
__SYSCALL_REPR(SC_REPR_FCNTL_ARG)
__SYSCALL_REPR(SC_REPR_FCNTL_COMMAND)
__SYSCALL_REPR(SC_REPR_FD_T)
__SYSCALL_REPR(SC_REPR_FILENAME)
__SYSCALL_REPR(SC_REPR_FUTEX_OP)
__SYSCALL_REPR(SC_REPR_GETRANDOM_FLAGS)
__SYSCALL_REPR(SC_REPR_GETRUSAGE_WHO)
__SYSCALL_REPR(SC_REPR_GID_T)
__SYSCALL_REPR(SC_REPR_GID_VECTOR)
__SYSCALL_REPR(SC_REPR_IDTYPE_T)
__SYSCALL_REPR(SC_REPR_ID_T)
__SYSCALL_REPR(SC_REPR_INOTIFY_INIT_FLAGS)
__SYSCALL_REPR(SC_REPR_INOTIFY_MASK)
__SYSCALL_REPR(SC_REPR_INT)
__SYSCALL_REPR(SC_REPR_IOCTL_ARG)
__SYSCALL_REPR(SC_REPR_IOCTL_COMMAND)
__SYSCALL_REPR(SC_REPR_IOPRIO_ID)
__SYSCALL_REPR(SC_REPR_IOPRIO_VALUE)
__SYSCALL_REPR(SC_REPR_IOPRIO_WHO)
__SYSCALL_REPR(SC_REPR_ITIMER_WHICH)
__SYSCALL_REPR(SC_REPR_KCMP_TYPE)
__SYSCALL_REPR(SC_REPR_MEMFD_CREATE_FLAGS)
__SYSCALL_REPR(SC_REPR_MLOCKALL_FLAGS)
__SYSCALL_REPR(SC_REPR_MMAP_FLAGS)
__SYSCALL_REPR(SC_REPR_MMAP_PROT)
__SYSCALL_REPR(SC_REPR_MODE_T)
__SYSCALL_REPR(SC_REPR_MOUNT_FLAGS)
__SYSCALL_REPR(SC_REPR_MREMAP_FLAGS)
__SYSCALL_REPR(SC_REPR_OFLAG_T)
__SYSCALL_REPR(SC_REPR_OFLAG__CLOEXEC__CLOFORK)
__SYSCALL_REPR(SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT)
__SYSCALL_REPR(SC_REPR_PID_T)
__SYSCALL_REPR(SC_REPR_POINTER)
__SYSCALL_REPR(SC_REPR_PRCTL_COMMAND)
__SYSCALL_REPR(SC_REPR_REBOOT_HOW)
__SYSCALL_REPR(SC_REPR_RENAMEAT2_FLAGS)
__SYSCALL_REPR(SC_REPR_RLIMIT_RESOURCE)
__SYSCALL_REPR(SC_REPR_SCHED_POLICY)
__SYSCALL_REPR(SC_REPR_SCHED_PRIORITY_WHICH)
__SYSCALL_REPR(SC_REPR_SEEK_WHENCE)
__SYSCALL_REPR(SC_REPR_SIGNALFD4_FLAGS)
__SYSCALL_REPR(SC_REPR_SIGNO_T)
__SYSCALL_REPR(SC_REPR_SIGPROCMASK_HOW)
__SYSCALL_REPR(SC_REPR_SIZE_T)
__SYSCALL_REPR(SC_REPR_SOCKET_DOMAIN)
__SYSCALL_REPR(SC_REPR_SOCKET_PROTOCOL)
__SYSCALL_REPR(SC_REPR_SOCKET_RECVMSG_FLAGS)
__SYSCALL_REPR(SC_REPR_SOCKET_RECVMSG_FLAGS2)
__SYSCALL_REPR(SC_REPR_SOCKET_RECVMSG_FLAGS3)
__SYSCALL_REPR(SC_REPR_SOCKET_SENDMSG_FLAGS)
__SYSCALL_REPR(SC_REPR_SOCKET_SHUTDOWN_HOW)
__SYSCALL_REPR(SC_REPR_SOCKET_TYPE)
__SYSCALL_REPR(SC_REPR_SOCKLEN_T)
__SYSCALL_REPR(SC_REPR_SOCKOPT_LEVEL)
__SYSCALL_REPR(SC_REPR_SOCKOPT_OPTNAME)
__SYSCALL_REPR(SC_REPR_SOCKOPT_OPTVAL)
__SYSCALL_REPR(SC_REPR_SPLICE_FLAGS)
__SYSCALL_REPR(SC_REPR_STRING)
__SYSCALL_REPR(SC_REPR_STRING_VECTOR)
__SYSCALL_REPR(SC_REPR_STRUCT_EPOLL_EVENT)
__SYSCALL_REPR(SC_REPR_STRUCT_FDSET)
__SYSCALL_REPR(SC_REPR_STRUCT_FILE_HANDLE)
__SYSCALL_REPR(SC_REPR_STRUCT_IOVEC)
__SYSCALL_REPR(SC_REPR_STRUCT_IOVEC_C)
__SYSCALL_REPR(SC_REPR_STRUCT_ITIMERSPEC)
__SYSCALL_REPR(SC_REPR_STRUCT_ITIMERVAL)
__SYSCALL_REPR(SC_REPR_STRUCT_KERNEL_SIGACTION)
__SYSCALL_REPR(SC_REPR_STRUCT_MMSGHDR)
__SYSCALL_REPR(SC_REPR_STRUCT_MQ_ATTR)
__SYSCALL_REPR(SC_REPR_STRUCT_MSGHDR)
__SYSCALL_REPR(SC_REPR_STRUCT_POLLFD)
__SYSCALL_REPR(SC_REPR_STRUCT_RLIMIT)
__SYSCALL_REPR(SC_REPR_STRUCT_RLIMIT64)
__SYSCALL_REPR(SC_REPR_STRUCT_SCHED_PARAM)
__SYSCALL_REPR(SC_REPR_STRUCT_SIGALTSTACK)
__SYSCALL_REPR(SC_REPR_STRUCT_SIGEVENT)
__SYSCALL_REPR(SC_REPR_STRUCT_SIGINFO)
__SYSCALL_REPR(SC_REPR_STRUCT_SIGSET)
__SYSCALL_REPR(SC_REPR_STRUCT_SIGSET_WITH_SIZE)
__SYSCALL_REPR(SC_REPR_STRUCT_SOCKADDR)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMESPEC)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMESPEC_OR_UINT32)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMEVAL)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMEVAL_VEC2)
__SYSCALL_REPR(SC_REPR_STRUCT_TIMEZONE)
__SYSCALL_REPR(SC_REPR_STRUCT_UTIMBUF)
__SYSCALL_REPR(SC_REPR_SWAPFLAGS)
__SYSCALL_REPR(SC_REPR_SYNC_FILE_RANGE_FLAGS)
__SYSCALL_REPR(SC_REPR_SYSCALL_SLONG_T)
__SYSCALL_REPR(SC_REPR_SYSCALL_ULONG_T)
__SYSCALL_REPR(SC_REPR_SYSLOG_LEVEL)
__SYSCALL_REPR(SC_REPR_TIMERFD_FLAGS)
__SYSCALL_REPR(SC_REPR_TIMERFD_TIMER_FLAGS)
__SYSCALL_REPR(SC_REPR_TIMER_FLAGS)
__SYSCALL_REPR(SC_REPR_TIMER_T)
__SYSCALL_REPR(SC_REPR_UID_T)
__SYSCALL_REPR(SC_REPR_UINT32_T)
__SYSCALL_REPR(SC_REPR_UINT64_T)
__SYSCALL_REPR(SC_REPR_WAITFLAGS)
__SYSCALL_REPR(SC_REPR_XATTR_FLAGS)
#endif /* __WANT_SYSCALL_ARGUMENT_REPR_TYPES */

#ifdef __WANT_SYSCALL_RETURN_REPR_TYPES
__SYSCALL_REPR(SC_REPR_ERRNO_T)
__SYSCALL_REPR(SC_REPR_SSIZE_T)
__SYSCALL_REPR(SC_REPR_TIME_T)
#endif /* __WANT_SYSCALL_RETURN_REPR_TYPES */

#undef __SYSCALL_REPR

