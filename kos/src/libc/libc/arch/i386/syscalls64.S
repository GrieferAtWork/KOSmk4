/* HASH CRC-32:0x32396109 */
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

#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <asm/unistd.h>
#include <sys/syscall.h>




#ifndef CONFIG_SYSCALL_EXCLUDE_WITHOUTEXCEPT
.section .text.crt.syscall.read
/* ssize_t read(fd_t fd,
 *              void *buf,
 *              size_t bufsize) */
INTERN_FUNCTION(libc_sys_read)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_read, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_read)

.section .text.crt.syscall.write
/* ssize_t write(fd_t fd,
 *               void const *buf,
 *               size_t bufsize) */
INTERN_FUNCTION(libc_sys_write)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_write, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_write)

.section .text.crt.syscall.open
/* fd_t open(char const *filename,
 *           oflag_t oflags,
 *           mode_t mode) */
INTERN_FUNCTION(libc_sys_open)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_open, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_open)

/* Close a given file descriptor/handle `FD' */
.section .text.crt.syscall.close
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_close)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_close, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_close)

.section .text.crt.syscall.linux_stat64
/* errno_t linux_stat64(char const *filename,
 *                      struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_linux_stat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_stat64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_linux_stat64)

.section .text.crt.syscall.linux_fstat64
/* errno_t linux_fstat64(fd_t fd,
 *                       struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_linux_fstat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_fstat64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_linux_fstat64)

.section .text.crt.syscall.linux_lstat64
/* errno_t linux_lstat64(char const *filename,
 *                       struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_linux_lstat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_lstat64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_linux_lstat64)

.section .text.crt.syscall.poll
/* ssize_t poll(struct pollfd *fds,
 *              size_t nfds,
 *              syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_poll)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_poll, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_poll)

.section .text.crt.syscall.lseek64
/* int64_t lseek64(fd_t fd,
 *                 int64_t offset,
 *                 syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_lseek64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_lseek64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lseek64)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
.section .text.crt.syscall.mmap
/* void *mmap(void *addr,
 *            size_t len,
 *            syscall_ulong_t prot,
 *            syscall_ulong_t flags,
 *            fd_t fd,
 *            syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_mmap)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_mmap, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
.section .text.crt.syscall.mprotect
/* errno_t mprotect(void *addr,
 *                  size_t len,
 *                  syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_mprotect)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mprotect, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mprotect)

.section .text.crt.syscall.munmap
/* errno_t munmap(void *addr,
 *                size_t len) */
INTERN_FUNCTION(libc_sys_munmap)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_munmap, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munmap)

.section .text.crt.syscall.brk
/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_brk)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_brk, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_brk)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.rt_sigaction
/* errno_t rt_sigaction(syscall_ulong_t signo,
 *                      struct sigaction const *act,
 *                      struct sigaction *oact,
 *                      size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigaction)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigaction, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.crt.syscall.rt_sigprocmask
/* errno_t rt_sigprocmask(syscall_ulong_t how,
 *                        struct __sigset_struct const *set,
 *                        struct __sigset_struct *oset,
 *                        size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigprocmask)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigprocmask, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigprocmask)

.section .text.crt.syscall.rt_sigreturn
/* void rt_sigreturn(void); */
INTERN_FUNCTION(libc_sys_rt_sigreturn)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_rt_sigreturn, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigreturn)

.section .text.crt.syscall.ioctl
/* syscall_slong_t ioctl(fd_t fd,
 *                       syscall_ulong_t request,
 *                       void *arg) */
INTERN_FUNCTION(libc_sys_ioctl)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioctl, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioctl)

.section .text.crt.syscall.pread64
/* ssize_t pread64(fd_t fd,
 *                 void *buf,
 *                 size_t bufsize,
 *                 uint64_t offset) */
INTERN_FUNCTION(libc_sys_pread64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pread64, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pread64)

.section .text.crt.syscall.pwrite64
/* ssize_t pwrite64(fd_t fd,
 *                  void const *buf,
 *                  size_t bufsize,
 *                  uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwrite64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pwrite64, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwrite64)

.section .text.crt.syscall.readv
/* ssize_t readv(fd_t fd,
 *               struct iovec const *iovec,
 *               size_t count) */
INTERN_FUNCTION(libc_sys_readv)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readv, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readv)

.section .text.crt.syscall.writev
/* ssize_t writev(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count) */
INTERN_FUNCTION(libc_sys_writev)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_writev, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
.section .text.crt.syscall.access
/* errno_t access(char const *filename,
 *                syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_access)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_access, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_access)

.section .text.crt.syscall.pipe
/* errno_t pipe([2]fd_t *pipedes) */
INTERN_FUNCTION(libc_sys_pipe)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_pipe, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pipe)

.section .text.crt.syscall.select
/* ssize_t select(size_t nfds,
 *                struct __fd_set_struct *readfds,
 *                struct __fd_set_struct *writefds,
 *                struct __fd_set_struct *exceptfds,
 *                struct __timeval32 *timeout) */
INTERN_FUNCTION(libc_sys_select)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_select, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_select)

.section .text.crt.syscall.sched_yield
/* errno_t sched_yield(void); */
INTERN_FUNCTION(libc_sys_sched_yield)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_sched_yield, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
.section .text.crt.syscall.mremap
/* void *mremap(void *addr,
 *              size_t old_len,
 *              size_t new_len,
 *              syscall_ulong_t flags,
 *              void *new_address) */
INTERN_FUNCTION(libc_sys_mremap)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_mremap, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mremap)

.section .text.crt.syscall.msync
/* errno_t msync(void *addr,
 *               size_t len,
 *               syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_msync)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_msync, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msync)

.section .text.crt.syscall.mincore
/* errno_t mincore(void *start,
 *                 size_t len,
 *                 uint8_t *vec) */
INTERN_FUNCTION(libc_sys_mincore)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mincore, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mincore)

.section .text.crt.syscall.madvise
/* errno_t madvise(void *addr,
 *                 size_t len,
 *                 syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_madvise)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_madvise, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_madvise)

.section .text.crt.syscall.dup
/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_dup)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_dup, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup)

.section .text.crt.syscall.dup2
/* fd_t dup2(fd_t oldfd,
 *           fd_t newfd) */
INTERN_FUNCTION(libc_sys_dup2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_dup2, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup2)

.section .text.crt.syscall.pause
/* errno_t pause(void); */
INTERN_FUNCTION(libc_sys_pause)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_pause, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pause)

.section .text.crt.syscall.nanosleep
/* errno_t nanosleep(struct __timespec32 const *req,
 *                   struct __timespec32 *rem) */
INTERN_FUNCTION(libc_sys_nanosleep)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_nanosleep, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_nanosleep)

.section .text.crt.syscall.getitimer
/* errno_t getitimer(syscall_ulong_t which,
 *                   struct __itimerval32 *curr_value) */
INTERN_FUNCTION(libc_sys_getitimer)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getitimer, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getitimer)

.section .text.crt.syscall.alarm
/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_alarm)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_alarm, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_alarm)

.section .text.crt.syscall.setitimer
/* errno_t setitimer(syscall_ulong_t which,
 *                   struct __itimerval32 const *newval,
 *                   struct __itimerval32 *oldval) */
INTERN_FUNCTION(libc_sys_setitimer)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setitimer, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setitimer)

.section .text.crt.syscall.getpid
/* pid_t getpid(void); */
INTERN_FUNCTION(libc_sys_getpid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getpid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpid)

.section .text.crt.syscall.sendfile
/* ssize_t sendfile(fd_t out_fd,
 *                  fd_t in_fd,
 *                  syscall_ulong_t *offset,
 *                  size_t count) */
INTERN_FUNCTION(libc_sys_sendfile)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sendfile, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendfile)

.section .text.crt.syscall.socket
/* fd_t socket(syscall_ulong_t domain,
 *             syscall_ulong_t type,
 *             syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_socket)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_socket, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_socket)

.section .text.crt.syscall.connect
/* errno_t connect(fd_t sockfd,
 *                 struct sockaddr const *addr,
 *                 socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_connect)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_connect, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_connect)

/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
.section .text.crt.syscall.sendto
/* ssize_t sendto(fd_t sockfd,
 *                void const *buf,
 *                size_t bufsize,
 *                syscall_ulong_t flags,
 *                struct sockaddr const *addr,
 *                socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_sendto)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_sendto, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendto)

.section .text.crt.syscall.recvfrom
/* ssize_t recvfrom(fd_t sockfd,
 *                  void *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t flags,
 *                  struct sockaddr *addr,
 *                  socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_recvfrom)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_recvfrom, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvfrom)

.section .text.crt.syscall.sendmsg
/* ssize_t sendmsg(fd_t sockfd,
 *                 struct msghdr const *message,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_sendmsg)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sendmsg, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendmsg)

.section .text.crt.syscall.recvmsg
/* ssize_t recvmsg(fd_t sockfd,
 *                 struct msghdr *message,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_recvmsg)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_recvmsg, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
.section .text.crt.syscall.shutdown
/* errno_t shutdown(fd_t sockfd,
 *                  syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_shutdown)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_shutdown, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shutdown)

.section .text.crt.syscall.bind
/* errno_t bind(fd_t sockfd,
 *              struct sockaddr const *addr,
 *              socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_bind)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_bind, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_bind)

.section .text.crt.syscall.listen
/* errno_t listen(fd_t sockfd,
 *                syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_listen)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_listen, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_listen)

.section .text.crt.syscall.getsockname
/* errno_t getsockname(fd_t sockfd,
 *                     struct sockaddr *addr,
 *                     socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getsockname)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getsockname, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsockname)

.section .text.crt.syscall.getpeername
/* errno_t getpeername(fd_t sockfd,
 *                     struct sockaddr *addr,
 *                     socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getpeername)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getpeername, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpeername)

.section .text.crt.syscall.socketpair
/* errno_t socketpair(syscall_ulong_t domain,
 *                    syscall_ulong_t type,
 *                    syscall_ulong_t protocol,
 *                    [2]fd_t *fds) */
INTERN_FUNCTION(libc_sys_socketpair)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_socketpair, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_socketpair)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.crt.syscall.setsockopt
/* errno_t setsockopt(fd_t sockfd,
 *                    syscall_ulong_t level,
 *                    syscall_ulong_t optname,
 *                    void const *optval,
 *                    socklen_t optlen) */
INTERN_FUNCTION(libc_sys_setsockopt)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_setsockopt, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.crt.syscall.getsockopt
/* errno_t getsockopt(fd_t sockfd,
 *                    syscall_ulong_t level,
 *                    syscall_ulong_t optname,
 *                    void *optval,
 *                    socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_getsockopt)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_getsockopt, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsockopt)

.section .text.crt.syscall.clone
/* pid_t clone(syscall_ulong_t flags,
 *             void *child_stack,
 *             pid_t *ptid,
 *             pid_t *ctid,
 *             uintptr_t newtls) */
INTERN_FUNCTION(libc_sys_clone)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_clone, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clone)

.section .text.crt.syscall.fork
/* pid_t fork(void); */
INTERN_FUNCTION(libc_sys_fork)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_fork, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fork)

.section .text.crt.syscall.vfork
/* pid_t vfork(void); */
INTERN_FUNCTION(libc_sys_vfork)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_vfork, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vfork)

.section .text.crt.syscall.execve
/* errno_t execve(char const *path,
 *                char const *const *argv,
 *                char const *const *envp) */
INTERN_FUNCTION(libc_sys_execve)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_execve, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_execve)

.section .text.crt.syscall.exit
/* void exit(syscall_ulong_t status) */
INTERN_FUNCTION(libc_sys_exit)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_exit, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_exit)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.crt.syscall.wait4
/* pid_t wait4(pid_t pid,
 *             int32_t *stat_loc,
 *             syscall_ulong_t options,
 *             struct rusage *usage) */
INTERN_FUNCTION(libc_sys_wait4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_wait4, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_wait4)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.kill
/* errno_t kill(pid_t pid,
 *              syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_kill)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kill, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kill)

.section .text.crt.syscall.uname
/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_uname)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_uname, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_uname)

.section .text.crt.syscall.fcntl
/* syscall_slong_t fcntl(fd_t fd,
 *                       syscall_ulong_t cmd,
 *                       void *arg) */
INTERN_FUNCTION(libc_sys_fcntl)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fcntl, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fcntl)

.section .text.crt.syscall.flock
/* errno_t flock(fd_t fd,
 *               syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_flock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_flock, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_flock)

.section .text.crt.syscall.fsync
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fsync)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fsync, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsync)

.section .text.crt.syscall.fdatasync
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fdatasync)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fdatasync, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fdatasync)

.section .text.crt.syscall.truncate
/* errno_t truncate(char const *filename,
 *                  syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_truncate)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_truncate, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_truncate)

.section .text.crt.syscall.ftruncate
/* errno_t ftruncate(fd_t fd,
 *                   syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_ftruncate)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ftruncate, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ftruncate)

.section .text.crt.syscall.getdents
/* ssize_t getdents(fd_t fd,
 *                  struct linux_dirent *dirp,
 *                  size_t count) */
INTERN_FUNCTION(libc_sys_getdents)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getdents, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdents)

.section .text.crt.syscall.getcwd
/* ssize_t getcwd(char *buf,
 *                size_t size) */
INTERN_FUNCTION(libc_sys_getcwd)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getcwd, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getcwd)

.section .text.crt.syscall.chdir
/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_chdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_chdir, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chdir)

.section .text.crt.syscall.fchdir
/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_fchdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fchdir, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchdir)

.section .text.crt.syscall.rename
/* errno_t rename(char const *oldname,
 *                char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_rename)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rename, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rename)

.section .text.crt.syscall.mkdir
/* errno_t mkdir(char const *pathname,
 *               mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdir)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_mkdir, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mkdir)

.section .text.crt.syscall.rmdir
/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_rmdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_rmdir, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rmdir)

.section .text.crt.syscall.creat
/* fd_t creat(char const *filename,
 *            mode_t mode) */
INTERN_FUNCTION(libc_sys_creat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_creat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_creat)

.section .text.crt.syscall.link
/* errno_t link(char const *existing_file,
 *              char const *link_file) */
INTERN_FUNCTION(libc_sys_link)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_link, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_link)

.section .text.crt.syscall.unlink
/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_unlink)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_unlink, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unlink)

.section .text.crt.syscall.symlink
/* errno_t symlink(char const *link_text,
 *                 char const *target_path) */
INTERN_FUNCTION(libc_sys_symlink)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_symlink, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_symlink)

.section .text.crt.syscall.readlink
/* ssize_t readlink(char const *path,
 *                  char *buf,
 *                  size_t buflen) */
INTERN_FUNCTION(libc_sys_readlink)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readlink, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readlink)

.section .text.crt.syscall.chmod
/* errno_t chmod(char const *filename,
 *               mode_t mode) */
INTERN_FUNCTION(libc_sys_chmod)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_chmod, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chmod)

.section .text.crt.syscall.fchmod
/* errno_t fchmod(fd_t fd,
 *                mode_t mode) */
INTERN_FUNCTION(libc_sys_fchmod)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fchmod, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchmod)

.section .text.crt.syscall.chown
/* errno_t chown(char const *filename,
 *               uint32_t owner,
 *               uint32_t group) */
INTERN_FUNCTION(libc_sys_chown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_chown, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chown)

.section .text.crt.syscall.fchown
/* errno_t fchown(fd_t fd,
 *                uint32_t owner,
 *                uint32_t group) */
INTERN_FUNCTION(libc_sys_fchown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fchown, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchown)

.section .text.crt.syscall.lchown
/* errno_t lchown(char const *filename,
 *                uint32_t owner,
 *                uint32_t group) */
INTERN_FUNCTION(libc_sys_lchown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_lchown, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lchown)

.section .text.crt.syscall.umask
/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_umask)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_umask, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_umask)

.section .text.crt.syscall.gettimeofday
/* errno_t gettimeofday(struct __timeval32 *tv,
 *                      struct timezone *tz) */
INTERN_FUNCTION(libc_sys_gettimeofday)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_gettimeofday, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_gettimeofday)

.section .text.crt.syscall.getrlimit
/* errno_t getrlimit(syscall_ulong_t resource,
 *                   struct rlimit *rlimits) */
INTERN_FUNCTION(libc_sys_getrlimit)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getrlimit, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getrlimit)

.section .text.crt.syscall.getrusage
/* errno_t getrusage(syscall_slong_t who,
 *                   struct rusage *usage) */
INTERN_FUNCTION(libc_sys_getrusage)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getrusage, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getrusage)

.section .text.crt.syscall.sysinfo
/* errno_t sysinfo(struct sysinfo *info) */
INTERN_FUNCTION(libc_sys_sysinfo)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sysinfo, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sysinfo)

.section .text.crt.syscall.times
/* clock_t times(struct tms *buf) */
INTERN_FUNCTION(libc_sys_times)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_times, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_times)

.section .text.crt.syscall.ptrace
/* syscall_slong_t ptrace(syscall_ulong_t request,
 *                        pid_t pid,
 *                        void *addr,
 *                        void *data) */
INTERN_FUNCTION(libc_sys_ptrace)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_ptrace, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ptrace)

.section .text.crt.syscall.getuid32
/* uint32_t getuid32(void); */
INTERN_FUNCTION(libc_sys_getuid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getuid32)

.section .text.crt.syscall.syslog
/* ssize_t syslog(syscall_ulong_t level,
 *                char const *str,
 *                size_t len) */
INTERN_FUNCTION(libc_sys_syslog)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_syslog, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_syslog)

.section .text.crt.syscall.getgid32
/* uint32_t getgid32(void); */
INTERN_FUNCTION(libc_sys_getgid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getgid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getgid32)

.section .text.crt.syscall.setuid32
/* errno_t setuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_setuid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setuid32)

.section .text.crt.syscall.setgid32
/* errno_t setgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_setgid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setgid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setgid32)

.section .text.crt.syscall.geteuid32
/* uint32_t geteuid32(void); */
INTERN_FUNCTION(libc_sys_geteuid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_geteuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_geteuid32)

.section .text.crt.syscall.getegid32
/* uint32_t getegid32(void); */
INTERN_FUNCTION(libc_sys_getegid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getegid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getegid32)

.section .text.crt.syscall.setpgid
/* errno_t setpgid(pid_t pid,
 *                 pid_t pgid) */
INTERN_FUNCTION(libc_sys_setpgid)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setpgid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setpgid)

.section .text.crt.syscall.getppid
/* pid_t getppid(void); */
INTERN_FUNCTION(libc_sys_getppid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getppid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getppid)

.section .text.crt.syscall.getpgrp
/* pid_t getpgrp(void); */
INTERN_FUNCTION(libc_sys_getpgrp)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getpgrp, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpgrp)

.section .text.crt.syscall.setsid
/* pid_t setsid(void); */
INTERN_FUNCTION(libc_sys_setsid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_setsid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setsid)

.section .text.crt.syscall.setreuid32
/* errno_t setreuid32(uint32_t ruid,
 *                    uint32_t euid) */
INTERN_FUNCTION(libc_sys_setreuid32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setreuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setreuid32)

.section .text.crt.syscall.setregid32
/* errno_t setregid32(uint32_t rgid,
 *                    uint32_t egid) */
INTERN_FUNCTION(libc_sys_setregid32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setregid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setregid32)

.section .text.crt.syscall.getgroups32
/* errno_t getgroups32(size_t size,
 *                     []uint32_t *list) */
INTERN_FUNCTION(libc_sys_getgroups32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getgroups32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getgroups32)

.section .text.crt.syscall.setgroups32
/* errno_t setgroups32(size_t count,
 *                     uint32_t const *groups) */
INTERN_FUNCTION(libc_sys_setgroups32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setgroups32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setgroups32)

.section .text.crt.syscall.setresuid32
/* errno_t setresuid32(uint32_t ruid,
 *                     uint32_t euid,
 *                     uint32_t suid) */
INTERN_FUNCTION(libc_sys_setresuid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setresuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setresuid32)

.section .text.crt.syscall.getresuid32
/* errno_t getresuid32(uint32_t *ruid,
 *                     uint32_t *euid,
 *                     uint32_t *suid) */
INTERN_FUNCTION(libc_sys_getresuid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getresuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getresuid32)

.section .text.crt.syscall.setresgid32
/* errno_t setresgid32(uint32_t rgid,
 *                     uint32_t egid,
 *                     uint32_t sgid) */
INTERN_FUNCTION(libc_sys_setresgid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setresgid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setresgid32)

.section .text.crt.syscall.getresgid32
/* errno_t getresgid32(uint32_t *rgid,
 *                     uint32_t *egid,
 *                     uint32_t *sgid) */
INTERN_FUNCTION(libc_sys_getresgid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getresgid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getresgid32)

.section .text.crt.syscall.getpgid
/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getpgid)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_getpgid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpgid)

.section .text.crt.syscall.setfsuid32
/* errno_t setfsuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_setfsuid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setfsuid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setfsuid32)

.section .text.crt.syscall.setfsgid32
/* errno_t setfsgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_setfsgid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setfsgid32, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setfsgid32)

.section .text.crt.syscall.getsid
/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getsid)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_getsid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsid)

.section .text.crt.syscall.rt_sigpending
/* errno_t rt_sigpending(struct __sigset_struct *set,
 *                       size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigpending)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rt_sigpending, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigpending)

.section .text.crt.syscall.rt_sigtimedwait
/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set,
 *                                 struct __siginfo_struct *info,
 *                                 struct __timespec32 const *timeout,
 *                                 size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigtimedwait)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigtimedwait, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.rt_sigqueueinfo
/* errno_t rt_sigqueueinfo(pid_t tgid,
 *                         syscall_ulong_t signo,
 *                         struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_sigqueueinfo)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_rt_sigqueueinfo, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigqueueinfo)

.section .text.crt.syscall.rt_sigsuspend
/* errno_t rt_sigsuspend(struct __sigset_struct const *set,
 *                       size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigsuspend)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rt_sigsuspend, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigsuspend)

.section .text.crt.syscall.sigaltstack
/* errno_t sigaltstack(struct sigaltstack const *ss,
 *                     struct sigaltstack *oss) */
INTERN_FUNCTION(libc_sys_sigaltstack)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sigaltstack, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sigaltstack)

.section .text.crt.syscall.utime
/* errno_t utime(char const *filename,
 *               struct __utimbuf32 const *times) */
INTERN_FUNCTION(libc_sys_utime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utime, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utime)

.section .text.crt.syscall.mknod
/* errno_t mknod(char const *nodename,
 *               mode_t mode,
 *               dev_t dev) */
INTERN_FUNCTION(libc_sys_mknod)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mknod, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mknod)

.section .text.crt.syscall.ustat
/* errno_t ustat(dev_t dev,
 *               struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_ustat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ustat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ustat)

.section .text.crt.syscall.statfs
/* errno_t statfs(char const *file,
 *                struct __statfs32 *buf) */
INTERN_FUNCTION(libc_sys_statfs)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_statfs, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_statfs)

.section .text.crt.syscall.fstatfs
/* errno_t fstatfs(fd_t file,
 *                 struct __statfs32 *buf) */
INTERN_FUNCTION(libc_sys_fstatfs)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fstatfs, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fstatfs)

.section .text.crt.syscall.getpriority
/* syscall_slong_t getpriority(syscall_ulong_t which,
 *                             id_t who) */
INTERN_FUNCTION(libc_sys_getpriority)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getpriority, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpriority)

.section .text.crt.syscall.setpriority
/* errno_t setpriority(syscall_ulong_t which,
 *                     id_t who,
 *                     syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_setpriority)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setpriority, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setpriority)

.section .text.crt.syscall.sched_setparam
/* errno_t sched_setparam(pid_t pid,
 *                        struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setparam)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_setparam, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setparam)

.section .text.crt.syscall.sched_getparam
/* errno_t sched_getparam(pid_t pid,
 *                        struct sched_param *param) */
INTERN_FUNCTION(libc_sys_sched_getparam)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_getparam, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getparam)

.section .text.crt.syscall.sched_setscheduler
/* errno_t sched_setscheduler(pid_t pid,
 *                            syscall_ulong_t policy,
 *                            struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setscheduler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_setscheduler, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setscheduler)

.section .text.crt.syscall.sched_getscheduler
/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_sched_getscheduler)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_getscheduler, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getscheduler)

.section .text.crt.syscall.sched_get_priority_max
/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_max)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_get_priority_max, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_get_priority_max)

.section .text.crt.syscall.sched_get_priority_min
/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_min)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_get_priority_min, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_get_priority_min)

.section .text.crt.syscall.sched_rr_get_interval
/* errno_t sched_rr_get_interval(pid_t pid,
 *                               struct __timespec32 *tms) */
INTERN_FUNCTION(libc_sys_sched_rr_get_interval)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_rr_get_interval, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_rr_get_interval)

.section .text.crt.syscall.mlock
/* errno_t mlock(void const *addr,
 *               size_t len) */
INTERN_FUNCTION(libc_sys_mlock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_mlock, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mlock)

.section .text.crt.syscall.munlock
/* errno_t munlock(void const *addr,
 *                 size_t len) */
INTERN_FUNCTION(libc_sys_munlock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_munlock, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munlock)

.section .text.crt.syscall.mlockall
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_mlockall)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_mlockall, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mlockall)

.section .text.crt.syscall.munlockall
/* errno_t munlockall(void); */
INTERN_FUNCTION(libc_sys_munlockall)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_munlockall, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munlockall)

.section .text.crt.syscall.vhangup
/* errno_t vhangup(void); */
INTERN_FUNCTION(libc_sys_vhangup)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_vhangup, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vhangup)

.section .text.crt.syscall.modify_ldt
/* syscall_slong_t modify_ldt(syscall_ulong_t func,
 *                            void *ptr,
 *                            syscall_ulong_t bytecount) */
INTERN_FUNCTION(libc_sys_modify_ldt)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_modify_ldt, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_modify_ldt)

.section .text.crt.syscall.setrlimit
/* errno_t setrlimit(syscall_ulong_t resource,
 *                   struct rlimit const *rlimits) */
INTERN_FUNCTION(libc_sys_setrlimit)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setrlimit, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setrlimit)

.section .text.crt.syscall.chroot
/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_chroot)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_chroot, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chroot)

.section .text.crt.syscall.sync
/* errno_t sync(void); */
INTERN_FUNCTION(libc_sys_sync)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_sync, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sync)

.section .text.crt.syscall.acct
/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_acct)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_acct, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_acct)

.section .text.crt.syscall.settimeofday
/* errno_t settimeofday(struct __timeval32 const *tv,
 *                      struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_settimeofday)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_settimeofday, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_settimeofday)

.section .text.crt.syscall.mount
/* errno_t mount(char const *special_file,
 *               char const *dir,
 *               char const *fstype,
 *               syscall_ulong_t rwflag,
 *               void const *data) */
INTERN_FUNCTION(libc_sys_mount)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_mount, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mount)

.section .text.crt.syscall.umount2
/* errno_t umount2(char const *special_file,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_umount2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_umount2, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_umount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
.section .text.crt.syscall.swapon
/* errno_t swapon(char const *pathname,
 *                syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_swapon)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_swapon, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_swapon)

.section .text.crt.syscall.swapoff
/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_swapoff)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_swapoff, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_swapoff)

/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
.section .text.crt.syscall.reboot
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_reboot)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_reboot, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_reboot)

.section .text.crt.syscall.sethostname
/* errno_t sethostname(char const *name,
 *                     size_t len) */
INTERN_FUNCTION(libc_sys_sethostname)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sethostname, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sethostname)

.section .text.crt.syscall.setdomainname
/* errno_t setdomainname(char const *name,
 *                       size_t len) */
INTERN_FUNCTION(libc_sys_setdomainname)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setdomainname, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setdomainname)

.section .text.crt.syscall.iopl
/* errno_t iopl(syscall_ulong_t level) */
INTERN_FUNCTION(libc_sys_iopl)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_iopl, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_iopl)

.section .text.crt.syscall.ioperm
/* errno_t ioperm(syscall_ulong_t from,
 *                syscall_ulong_t num,
 *                syscall_ulong_t turn_on) */
INTERN_FUNCTION(libc_sys_ioperm)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioperm, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioperm)

.section .text.crt.syscall.gettid
/* pid_t gettid(void); */
INTERN_FUNCTION(libc_sys_gettid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_gettid, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_gettid)

.section .text.crt.syscall.readahead
/* ssize_t readahead(fd_t fd,
 *                   uint64_t offset,
 *                   size_t count) */
INTERN_FUNCTION(libc_sys_readahead)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readahead, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readahead)

.section .text.crt.syscall.setxattr
/* errno_t setxattr(char const *path,
 *                  char const *name,
 *                  void const *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_setxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_setxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setxattr)

.section .text.crt.syscall.lsetxattr
/* errno_t lsetxattr(char const *path,
 *                   char const *name,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_lsetxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lsetxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lsetxattr)

.section .text.crt.syscall.fsetxattr
/* errno_t fsetxattr(fd_t fd,
 *                   char const *name,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_fsetxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fsetxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsetxattr)

.section .text.crt.syscall.getxattr
/* ssize_t getxattr(char const *path,
 *                  char const *name,
 *                  void *buf,
 *                  size_t bufsize) */
INTERN_FUNCTION(libc_sys_getxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_getxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getxattr)

.section .text.crt.syscall.lgetxattr
/* ssize_t lgetxattr(char const *path,
 *                   char const *name,
 *                   void *buf,
 *                   size_t bufsize) */
INTERN_FUNCTION(libc_sys_lgetxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_lgetxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lgetxattr)

.section .text.crt.syscall.fgetxattr
/* ssize_t fgetxattr(fd_t fd,
 *                   char const *name,
 *                   void *buf,
 *                   size_t bufsize) */
INTERN_FUNCTION(libc_sys_fgetxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fgetxattr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fgetxattr)

.section .text.crt.syscall.listxattr
/* ssize_t listxattr(char const *path,
 *                   char *listbuf,
 *                   size_t listbufsize) */
INTERN_FUNCTION(libc_sys_listxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_listxattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_listxattr)

.section .text.crt.syscall.llistxattr
/* ssize_t llistxattr(char const *path,
 *                    char *listbuf,
 *                    size_t listbufsize) */
INTERN_FUNCTION(libc_sys_llistxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_llistxattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_llistxattr)

.section .text.crt.syscall.flistxattr
/* ssize_t flistxattr(fd_t fd,
 *                    char *listbuf,
 *                    size_t listbufsize) */
INTERN_FUNCTION(libc_sys_flistxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_flistxattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_flistxattr)

.section .text.crt.syscall.removexattr
/* errno_t removexattr(char const *path,
 *                     char const *name) */
INTERN_FUNCTION(libc_sys_removexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_removexattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_removexattr)

.section .text.crt.syscall.lremovexattr
/* errno_t lremovexattr(char const *path,
 *                      char const *name) */
INTERN_FUNCTION(libc_sys_lremovexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_lremovexattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lremovexattr)

.section .text.crt.syscall.fremovexattr
/* errno_t fremovexattr(int fd,
 *                      char const *name) */
INTERN_FUNCTION(libc_sys_fremovexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fremovexattr, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fremovexattr)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.tkill
/* errno_t tkill(pid_t tid,
 *               syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_tkill)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_tkill, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tkill)

.section .text.crt.syscall.time
/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_time)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_time, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_time)

.section .text.crt.syscall.futex
/* syscall_slong_t futex(uint32_t *uaddr,
 *                       syscall_ulong_t futex_op,
 *                       uint32_t val,
 *                       struct __timespec32 const *timeout_or_val2,
 *                       uint32_t *uaddr2,
 *                       uint32_t val3) */
INTERN_FUNCTION(libc_sys_futex)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_futex, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_futex)

.section .text.crt.syscall.sched_setaffinity
/* errno_t sched_setaffinity(pid_t pid,
 *                           size_t cpusetsize,
 *                           struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_sched_setaffinity)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_setaffinity, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setaffinity)

.section .text.crt.syscall.sched_getaffinity
/* errno_t sched_getaffinity(pid_t pid,
 *                           size_t cpusetsize,
 *                           struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_sched_getaffinity)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_getaffinity, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getaffinity)

.section .text.crt.syscall.epoll_create
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_epoll_create)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_epoll_create, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_create)

.section .text.crt.syscall.epoll_ctl_old
/* errno_t epoll_ctl_old(fd_t epfd,
 *                       syscall_ulong_t op,
 *                       fd_t fd,
 *                       struct epoll_event *event) */
INTERN_FUNCTION(libc_sys_epoll_ctl_old)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_ctl_old, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_ctl_old)

.section .text.crt.syscall.epoll_wait_old
/* errno_t epoll_wait_old(fd_t epfd,
 *                        struct epoll_event *events,
 *                        syscall_ulong_t maxevents,
 *                        syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_epoll_wait_old)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_wait_old, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_wait_old)

.section .text.crt.syscall.remap_file_pages
/* errno_t remap_file_pages(void *start,
 *                          size_t size,
 *                          syscall_ulong_t prot,
 *                          size_t pgoff,
 *                          syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_remap_file_pages)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_remap_file_pages, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_remap_file_pages)

.section .text.crt.syscall.getdents64
/* ssize_t getdents64(fd_t fd,
 *                    struct linux_dirent64 *dirp,
 *                    size_t count) */
INTERN_FUNCTION(libc_sys_getdents64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getdents64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdents64)

.section .text.crt.syscall.set_tid_address
/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_set_tid_address)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_set_tid_address, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_tid_address)

.section .text.crt.syscall.timer_create
/* errno_t timer_create(clockid_t clock_id,
 *                      struct sigevent *evp,
 *                      timer_t *timerid) */
INTERN_FUNCTION(libc_sys_timer_create)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_timer_create, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_create)

.section .text.crt.syscall.timer_settime
/* errno_t timer_settime(timer_t timerid,
 *                       syscall_ulong_t flags,
 *                       struct __itimerspec32 const *value,
 *                       struct __itimerspec32 *ovalue) */
INTERN_FUNCTION(libc_sys_timer_settime)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_timer_settime, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_settime)

.section .text.crt.syscall.timer_gettime
/* errno_t timer_gettime(timer_t timerid,
 *                       struct __itimerspec32 *value) */
INTERN_FUNCTION(libc_sys_timer_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timer_gettime, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_gettime)

.section .text.crt.syscall.timer_getoverrun
/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_getoverrun)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_timer_getoverrun, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_getoverrun)

.section .text.crt.syscall.timer_delete
/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_delete)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_timer_delete, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_delete)

.section .text.crt.syscall.clock_settime
/* errno_t clock_settime(clockid_t clock_id,
 *                       struct __timespec32 const *tp) */
INTERN_FUNCTION(libc_sys_clock_settime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_settime, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_settime)

.section .text.crt.syscall.clock_gettime
/* errno_t clock_gettime(clockid_t clock_id,
 *                       struct __timespec32 *tp) */
INTERN_FUNCTION(libc_sys_clock_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_gettime, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_gettime)

.section .text.crt.syscall.clock_getres
/* errno_t clock_getres(clockid_t clock_id,
 *                      struct __timespec32 *res) */
INTERN_FUNCTION(libc_sys_clock_getres)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_getres, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_getres)

.section .text.crt.syscall.clock_nanosleep
/* errno_t clock_nanosleep(clockid_t clock_id,
 *                         syscall_ulong_t flags,
 *                         struct __timespec32 const *requested_time,
 *                         struct __timespec32 *remaining) */
INTERN_FUNCTION(libc_sys_clock_nanosleep)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_clock_nanosleep, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_nanosleep)

.section .text.crt.syscall.exit_group
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_exit_group)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_exit_group, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_exit_group)

.section .text.crt.syscall.epoll_wait
/* errno_t epoll_wait(fd_t epfd,
 *                    struct epoll_event *events,
 *                    syscall_ulong_t maxevents,
 *                    syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_epoll_wait)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_wait, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_wait)

.section .text.crt.syscall.epoll_ctl
/* errno_t epoll_ctl(fd_t epfd,
 *                   syscall_ulong_t op,
 *                   fd_t fd,
 *                   struct epoll_event *event) */
INTERN_FUNCTION(libc_sys_epoll_ctl)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_ctl, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_ctl)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.tgkill
/* errno_t tgkill(pid_t tgid,
 *                pid_t tid,
 *                syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_tgkill)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_tgkill, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tgkill)

.section .text.crt.syscall.utimes
/* errno_t utimes(char const *filename,
 *                [2]struct __timeval32 const *times) */
INTERN_FUNCTION(libc_sys_utimes)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utimes, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utimes)

/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
.section .text.crt.syscall.waitid
/* errno_t waitid(idtype_t idtype,
 *                id_t id,
 *                struct __siginfo_struct *infop,
 *                syscall_ulong_t options,
 *                struct rusage *ru) */
INTERN_FUNCTION(libc_sys_waitid)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_waitid, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_waitid)

.section .text.crt.syscall.ioprio_set
/* errno_t ioprio_set(syscall_ulong_t which,
 *                    syscall_ulong_t who,
 *                    syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_ioprio_set)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioprio_set, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioprio_set)

.section .text.crt.syscall.ioprio_get
/* errno_t ioprio_get(syscall_ulong_t which,
 *                    syscall_ulong_t who) */
INTERN_FUNCTION(libc_sys_ioprio_get)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ioprio_get, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioprio_get)

.section .text.crt.syscall.openat
/* fd_t openat(fd_t dirfd,
 *             char const *filename,
 *             oflag_t oflags,
 *             mode_t mode) */
INTERN_FUNCTION(libc_sys_openat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_openat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_openat)

.section .text.crt.syscall.mkdirat
/* errno_t mkdirat(fd_t dirfd,
 *                 char const *pathname,
 *                 mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdirat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mkdirat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mkdirat)

.section .text.crt.syscall.mknodat
/* errno_t mknodat(fd_t dirfd,
 *                 char const *nodename,
 *                 mode_t mode,
 *                 dev_t dev) */
INTERN_FUNCTION(libc_sys_mknodat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_mknodat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.fchownat
/* errno_t fchownat(fd_t dirfd,
 *                  char const *filename,
 *                  uint32_t owner,
 *                  uint32_t group,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchownat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fchownat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchownat)

.section .text.crt.syscall.futimesat
/* errno_t futimesat(fd_t dirfd,
 *                   const char *filename,
 *                   [2]struct __timeval32 const *times) */
INTERN_FUNCTION(libc_sys_futimesat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_futimesat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_futimesat)

.section .text.crt.syscall.fstatat
/* errno_t fstatat(fd_t dirfd,
 *                 char const *filename,
 *                 struct linux64_stat32 *statbuf,
 *                 atflag_t flags) */
INTERN_FUNCTION(libc_sys_fstatat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fstatat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fstatat)

/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
.section .text.crt.syscall.unlinkat
/* errno_t unlinkat(fd_t dirfd,
 *                  char const *name,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_unlinkat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_unlinkat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unlinkat)

.section .text.crt.syscall.renameat
/* errno_t renameat(fd_t oldfd,
 *                  char const *oldname,
 *                  fd_t newfd,
 *                  char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_renameat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_renameat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_renameat)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.linkat
/* errno_t linkat(fd_t fromfd,
 *                char const *existing_file,
 *                fd_t tofd,
 *                char const *target_path,
 *                atflag_t flags) */
INTERN_FUNCTION(libc_sys_linkat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_linkat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_linkat)

.section .text.crt.syscall.symlinkat
/* errno_t symlinkat(char const *link_text,
 *                   fd_t tofd,
 *                   char const *target_path) */
INTERN_FUNCTION(libc_sys_symlinkat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_symlinkat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_symlinkat)

.section .text.crt.syscall.readlinkat
/* ssize_t readlinkat(fd_t dirfd,
 *                    char const *path,
 *                    char *buf,
 *                    size_t buflen) */
INTERN_FUNCTION(libc_sys_readlinkat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readlinkat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readlinkat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.fchmodat
/* errno_t fchmodat(fd_t dirfd,
 *                  char const *filename,
 *                  mode_t mode,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchmodat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fchmodat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
.section .text.crt.syscall.faccessat
/* errno_t faccessat(fd_t dirfd,
 *                   char const *filename,
 *                   syscall_ulong_t type,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_faccessat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_faccessat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_faccessat)

.section .text.crt.syscall.pselect6
/* ssize_t pselect6(size_t nfds,
 *                  struct __fd_set_struct *readfds,
 *                  struct __fd_set_struct *writefds,
 *                  struct __fd_set_struct *exceptfds,
 *                  struct __timespec32 const *timeout,
 *                  void const *sigmask_sigset_and_len) */
INTERN_FUNCTION(libc_sys_pselect6)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_pselect6, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pselect6)

.section .text.crt.syscall.ppoll
/* ssize_t ppoll(struct pollfd *fds,
 *               size_t nfds,
 *               struct __timespec32 const *timeout_ts,
 *               struct __sigset_struct const *sigmask,
 *               size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_ppoll)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_ppoll, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ppoll)

/* param flags: Set of `CLONE_*' */
.section .text.crt.syscall.unshare
/* errno_t unshare(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_unshare)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_unshare, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unshare)

.section .text.crt.syscall.splice
/* ssize_t splice(fd_t fdin,
 *                uint64_t *offin,
 *                fd_t fdout,
 *                uint64_t *offout,
 *                size_t length,
 *                syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_splice)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_splice, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_splice)

.section .text.crt.syscall.tee
/* ssize_t tee(fd_t fdin,
 *             fd_t fdout,
 *             size_t length,
 *             syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_tee)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_tee, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tee)

.section .text.crt.syscall.sync_file_range
/* errno_t sync_file_range(fd_t fd,
 *                         uint64_t offset,
 *                         uint64_t count,
 *                         syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_sync_file_range)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sync_file_range, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sync_file_range)

.section .text.crt.syscall.vmsplice
/* ssize_t vmsplice(fd_t fdout,
 *                  struct iovec const *iov,
 *                  size_t count,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_vmsplice)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_vmsplice, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vmsplice)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.crt.syscall.utimensat
/* errno_t utimensat(fd_t dirfd,
 *                   char const *filename,
 *                   [2-3]struct __timespec32 const *times,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_utimensat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_utimensat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utimensat)

.section .text.crt.syscall.epoll_pwait
/* errno_t epoll_pwait(fd_t epfd,
 *                     struct epoll_event *events,
 *                     syscall_ulong_t maxevents,
 *                     syscall_slong_t timeout,
 *                     struct __sigset_struct const *ss) */
INTERN_FUNCTION(libc_sys_epoll_pwait)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_epoll_pwait, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_pwait)

.section .text.crt.syscall.signalfd
/* errno_t signalfd(fd_t fd,
 *                  struct __sigset_struct const *sigmask,
 *                  size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_signalfd)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_signalfd, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_signalfd)

/* Return file descriptor for new interval timer source */
.section .text.crt.syscall.timerfd_create
/* fd_t timerfd_create(clockid_t clock_id,
 *                     syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_timerfd_create)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timerfd_create, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_create)

.section .text.crt.syscall.eventfd
/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_eventfd)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_eventfd, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_eventfd)

.section .text.crt.syscall.fallocate
/* errno_t fallocate(fd_t fd,
 *                   syscall_ulong_t mode,
 *                   uint32_t offset,
 *                   uint32_t length) */
INTERN_FUNCTION(libc_sys_fallocate)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fallocate, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.crt.syscall.timerfd_settime
/* errno_t timerfd_settime(fd_t ufd,
 *                         syscall_ulong_t flags,
 *                         struct __itimerspec32 const *utmr,
 *                         struct __itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_settime)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_timerfd_settime, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_settime)

/* Return the next expiration time of UFD */
.section .text.crt.syscall.timerfd_gettime
/* errno_t timerfd_gettime(fd_t ufd,
 *                         struct __itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timerfd_gettime, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_gettime)

.section .text.crt.syscall.accept4
/* fd_t accept4(fd_t sockfd,
 *              struct sockaddr *addr,
 *              socklen_t *addr_len,
 *              syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_accept4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_accept4, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_accept4)

.section .text.crt.syscall.signalfd4
/* errno_t signalfd4(fd_t fd,
 *                   struct __sigset_struct const *sigmask,
 *                   size_t sigsetsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_signalfd4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_signalfd4, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_signalfd4)

.section .text.crt.syscall.eventfd2
/* fd_t eventfd2(syscall_ulong_t initval,
 *               syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_eventfd2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_eventfd2, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_eventfd2)

.section .text.crt.syscall.epoll_create1
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_epoll_create1)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_epoll_create1, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
.section .text.crt.syscall.dup3
/* fd_t dup3(fd_t oldfd,
 *           fd_t newfd,
 *           oflag_t flags) */
INTERN_FUNCTION(libc_sys_dup3)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_dup3, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup3)

.section .text.crt.syscall.pipe2
/* errno_t pipe2([2]fd_t *pipedes,
 *               oflag_t flags) */
INTERN_FUNCTION(libc_sys_pipe2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_pipe2, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pipe2)

.section .text.crt.syscall.preadv
/* ssize_t preadv(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count,
 *                uint64_t offset) */
INTERN_FUNCTION(libc_sys_preadv)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_preadv, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_preadv)

.section .text.crt.syscall.pwritev
/* ssize_t pwritev(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwritev)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pwritev, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwritev)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.rt_tgsigqueueinfo
/* errno_t rt_tgsigqueueinfo(pid_t tgid,
 *                           pid_t tid,
 *                           syscall_ulong_t signo,
 *                           struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_tgsigqueueinfo)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_tgsigqueueinfo, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_tgsigqueueinfo)

.section .text.crt.syscall.recvmmsg
/* ssize_t recvmmsg(fd_t sockfd,
 *                  struct mmsghdr *vmessages,
 *                  size_t vlen,
 *                  syscall_ulong_t flags,
 *                  struct __timespec32 *tmo) */
INTERN_FUNCTION(libc_sys_recvmmsg)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_recvmmsg, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvmmsg)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
.section .text.crt.syscall.prlimit64
/* errno_t prlimit64(pid_t pid,
 *                   syscall_ulong_t resource,
 *                   struct rlimit64 const *new_limit,
 *                   struct rlimit64 *old_limit) */
INTERN_FUNCTION(libc_sys_prlimit64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_prlimit64, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_prlimit64)

.section .text.crt.syscall.name_to_handle_at
/* errno_t name_to_handle_at(fd_t dirfd,
 *                           char const *name,
 *                           struct file_handle *handle,
 *                           int32_t *mnt_id,
 *                           syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_name_to_handle_at)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_name_to_handle_at, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_name_to_handle_at)

.section .text.crt.syscall.open_by_handle_at
/* fd_t open_by_handle_at(fd_t mountdirfd,
 *                        struct file_handle *handle,
 *                        syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_open_by_handle_at)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_open_by_handle_at, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_open_by_handle_at)

.section .text.crt.syscall.syncfs
/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_syncfs)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_syncfs, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_syncfs)

.section .text.crt.syscall.sendmmsg
/* ssize_t sendmmsg(fd_t sockfd,
 *                  struct mmsghdr *vmessages,
 *                  size_t vlen,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_sendmmsg)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sendmmsg, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendmmsg)

.section .text.crt.syscall.setns
/* errno_t setns(fd_t fd,
 *               syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_setns)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setns, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setns)

.section .text.crt.syscall.getcpu
/* errno_t getcpu(uint32_t *cpu,
 *                uint32_t *node,
 *                struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_getcpu)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getcpu, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getcpu)

.section .text.crt.syscall.process_vm_readv
/* ssize_t process_vm_readv(pid_t pid,
 *                          struct iovec const *lvec,
 *                          size_t liovcnt,
 *                          struct iovec const *rvec,
 *                          size_t riovcnt,
 *                          syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_readv)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_process_vm_readv, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_process_vm_readv)

.section .text.crt.syscall.process_vm_writev
/* ssize_t process_vm_writev(pid_t pid,
 *                           struct iovec const *lvec,
 *                           size_t liovcnt,
 *                           struct iovec const *rvec,
 *                           size_t riovcnt,
 *                           syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_writev)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_process_vm_writev, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_process_vm_writev)

.section .text.crt.syscall.kcmp
/* syscall_slong_t kcmp(pid_t pid1,
 *                      pid_t pid2,
 *                      syscall_ulong_t type,
 *                      syscall_ulong_t idx1,
 *                      syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_kcmp)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_kcmp, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kcmp)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
.section .text.crt.syscall.renameat2
/* errno_t renameat2(fd_t olddirfd,
 *                   char const *oldpath,
 *                   fd_t newdirfd,
 *                   char const *newpath,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_renameat2)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_renameat2, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_renameat2)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.execveat
/* errno_t execveat(fd_t dirfd,
 *                  char const *pathname,
 *                  char const *const *argv,
 *                  char const *const *envp,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_execveat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_execveat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_execveat)

.section .text.crt.syscall.readf
/* ssize_t readf(fd_t fd,
 *               void *buf,
 *               size_t bufsize,
 *               iomode_t mode) */
INTERN_FUNCTION(libc_sys_readf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readf)

.section .text.crt.syscall.writef
/* ssize_t writef(fd_t fd,
 *                void const *buf,
 *                size_t bufsize,
 *                iomode_t mode) */
INTERN_FUNCTION(libc_sys_writef)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_writef, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writef)

.section .text.crt.syscall.hop
/* syscall_slong_t hop(fd_t fd,
 *                     syscall_ulong_t command,
 *                     void *arg) */
INTERN_FUNCTION(libc_sys_hop)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_hop, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_hop)

.section .text.crt.syscall.hopf
/* syscall_slong_t hopf(fd_t fd,
 *                      syscall_ulong_t command,
 *                      iomode_t mode,
 *                      void *arg) */
INTERN_FUNCTION(libc_sys_hopf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_hopf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_hopf)

.section .text.crt.syscall.kstat
/* errno_t kstat(char const *filename,
 *               struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_kstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kstat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kstat)

.section .text.crt.syscall.kfstat
/* errno_t kfstat(fd_t fd,
 *                struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_kfstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kfstat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kfstat)

.section .text.crt.syscall.klstat
/* errno_t klstat(char const *filename,
 *                struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_klstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_klstat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_klstat)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
.section .text.crt.syscall.detach
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_detach)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_detach, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
.section .text.crt.syscall.getdrives
/* syscall_slong_t getdrives(void); */
INTERN_FUNCTION(libc_sys_getdrives)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getdrives, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.frealpath4
/* ssize_t frealpath4(fd_t fd,
 *                    char *buf,
 *                    size_t buflen,
 *                    atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpath4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_frealpath4, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.frealpathat
/* ssize_t frealpathat(fd_t dirfd,
 *                     char const *filename,
 *                     char *buf,
 *                     size_t buflen,
 *                     atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpathat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_frealpathat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text.crt.syscall.rpc_schedule
/* syscall_slong_t rpc_schedule(pid_t target,
 *                              syscall_ulong_t flags,
 *                              uint8_t const *program,
 *                              void **arguments) */
INTERN_FUNCTION(libc_sys_rpc_schedule)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rpc_schedule, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rpc_schedule)

.section .text.crt.syscall.sysctl
/* syscall_slong_t sysctl(syscall_ulong_t command,
 *                        void *arg) */
INTERN_FUNCTION(libc_sys_sysctl)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sysctl, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
.section .text.crt.syscall.openpty
/* errno_t openpty(fd_t *amaster,
 *                 fd_t *aslave,
 *                 char *name,
 *                 struct termios const *termp,
 *                 struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_openpty)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_openpty, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_openpty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
.section .text.crt.syscall.set_exception_handler
/* errno_t set_exception_handler(syscall_ulong_t mode,
 *                               except_handler_t handler,
 *                               void *handler_sp) */
INTERN_FUNCTION(libc_sys_set_exception_handler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_set_exception_handler, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
.section .text.crt.syscall.get_exception_handler
/* errno_t get_exception_handler(syscall_ulong_t *pmode,
 *                               except_handler_t *phandler,
 *                               void **phandler_sp) */
INTERN_FUNCTION(libc_sys_get_exception_handler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_get_exception_handler, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_exception_handler)

.section .text.crt.syscall.ioctlf
/* syscall_slong_t ioctlf(fd_t fd,
 *                        syscall_ulong_t command,
 *                        iomode_t mode,
 *                        void *arg) */
INTERN_FUNCTION(libc_sys_ioctlf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_ioctlf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioctlf)

.section .text.crt.syscall.pread64f
/* ssize_t pread64f(fd_t fd,
 *                  void *buf,
 *                  size_t bufsize,
 *                  uint64_t offset,
 *                  iomode_t mode) */
INTERN_FUNCTION(libc_sys_pread64f)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pread64f, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pread64f)

.section .text.crt.syscall.pwrite64f
/* ssize_t pwrite64f(fd_t fd,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   uint64_t offset,
 *                   iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwrite64f)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pwrite64f, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwrite64f)

.section .text.crt.syscall.readvf
/* ssize_t readvf(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count,
 *                iomode_t mode) */
INTERN_FUNCTION(libc_sys_readvf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readvf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readvf)

.section .text.crt.syscall.writevf
/* ssize_t writevf(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 iomode_t mode) */
INTERN_FUNCTION(libc_sys_writevf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_writevf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writevf)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
.section .text.crt.syscall.set_library_listdef
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
INTERN_FUNCTION(libc_sys_set_library_listdef)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_set_library_listdef, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
.section .text.crt.syscall.debugtrap
/* errno_t debugtrap(struct ucpustate const *state,
 *                   struct debugtrap_reason const *reason) */
INTERN_FUNCTION(libc_sys_debugtrap)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_debugtrap, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_debugtrap)

.section .text.crt.syscall.select64
/* ssize_t select64(size_t nfds,
 *                  struct __fd_set_struct *readfds,
 *                  struct __fd_set_struct *writefds,
 *                  struct __fd_set_struct *exceptfds,
 *                  struct __timeval64 *timeout) */
INTERN_FUNCTION(libc_sys_select64)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_select64, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_select64)

.section .text.crt.syscall.rpc_service
/* syscall_slong_t rpc_service(void); */
INTERN_FUNCTION(libc_sys_rpc_service)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_rpc_service, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rpc_service)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
.section .text.crt.syscall.lfutex
/* syscall_slong_t lfutex(uintptr_t *uaddr,
 *                        syscall_ulong_t futex_op,
 *                        uintptr_t val,
 *                        struct __timespec64 const *timeout,
 *                        uintptr_t val2) */
INTERN_FUNCTION(libc_sys_lfutex)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lfutex, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.crt.syscall.lfutexexpr
/* errno_t lfutexexpr(void *base,
 *                    size_t exprc,
 *                    struct lfutexexpr const *exprv,
 *                    struct __timespec64 const *timeout,
 *                    syscall_ulong_t timeout_flags) */
INTERN_FUNCTION(libc_sys_lfutexexpr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lfutexexpr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.crt.syscall.lfutexlockexpr
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr,
 *                        void *base,
 *                        size_t exprc,
 *                        struct lfutexexpr const *exprv,
 *                        struct __timespec64 const *timeout,
 *                        syscall_ulong_t timeout_flags) */
INTERN_FUNCTION(libc_sys_lfutexlockexpr)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_lfutexlockexpr, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
.section .text.crt.syscall.mktty
/* fd_t mktty(fd_t keyboard,
 *            fd_t display,
 *            char const *name,
 *            syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_mktty)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_mktty, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
.section .text.crt.syscall.raiseat
/* errno_t raiseat(struct ucpustate const *state,
 *                 struct __siginfo_struct const *si) */
INTERN_FUNCTION(libc_sys_raiseat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_raiseat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == UCPUSTATE_PC(*curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
.section .text.crt.syscall.coredump
/* errno_t coredump(struct ucpustate const *curr_state,
 *                  struct ucpustate const *orig_state,
 *                  void const *const *traceback_vector,
 *                  size_t traceback_length,
 *                  struct exception_data const *exception,
 *                  syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_coredump)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_coredump, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_coredump)

.section .text.crt.syscall.getitimer64
/* errno_t getitimer64(syscall_ulong_t which,
 *                     struct __itimerval64 *curr_value) */
INTERN_FUNCTION(libc_sys_getitimer64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getitimer64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getitimer64)

.section .text.crt.syscall.setitimer64
/* errno_t setitimer64(syscall_ulong_t which,
 *                     struct __itimerval64 const *newval,
 *                     struct __itimerval64 *oldval) */
INTERN_FUNCTION(libc_sys_setitimer64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setitimer64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setitimer64)

.section .text.crt.syscall.kreaddir
/* ssize_t kreaddir(fd_t fd,
 *                  struct dirent *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_kreaddir)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_kreaddir, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kreaddir)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.fchdirat
/* errno_t fchdirat(fd_t dirfd,
 *                  char const *path,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchdirat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fchdirat, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchdirat)

.section .text.crt.syscall.fsmode
/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_fsmode)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fsmode, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsmode)

.section .text.crt.syscall.gettimeofday64
/* errno_t gettimeofday64(struct __timeval64 *tv,
 *                        struct timezone *tz) */
INTERN_FUNCTION(libc_sys_gettimeofday64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_gettimeofday64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_gettimeofday64)

.section .text.crt.syscall.utime64
/* errno_t utime64(char const *filename,
 *                 struct utimbuf64 const *times) */
INTERN_FUNCTION(libc_sys_utime64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utime64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utime64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
.section .text.crt.syscall.maplibrary
/* void *maplibrary(void *addr,
 *                  syscall_ulong_t flags,
 *                  fd_t fd,
 *                  void *hdrv,
 *                  size_t hdrc) */
INTERN_FUNCTION(libc_sys_maplibrary)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_maplibrary, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_maplibrary)

.section .text.crt.syscall.settimeofday64
/* errno_t settimeofday64(struct __timeval64 const *tv,
 *                        struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_settimeofday64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_settimeofday64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_settimeofday64)

.section .text.crt.syscall.time64
/* time64_t time64(time64_t *timer) */
INTERN_FUNCTION(libc_sys_time64)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_time64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_time64)

.section .text.crt.syscall.kreaddirf
/* ssize_t kreaddirf(fd_t fd,
 *                   struct dirent *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t mode,
 *                   iomode_t iomode) */
INTERN_FUNCTION(libc_sys_kreaddirf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_kreaddirf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kreaddirf)

.section .text.crt.syscall.utimes64
/* errno_t utimes64(char const *filename,
 *                  [2]struct __timeval64 const *times) */
INTERN_FUNCTION(libc_sys_utimes64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utimes64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utimes64)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.fmkdirat
/* errno_t fmkdirat(fd_t dirfd,
 *                  char const *pathname,
 *                  mode_t mode,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmkdirat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fmkdirat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fmkdirat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.fmknodat
/* errno_t fmknodat(fd_t dirfd,
 *                  char const *nodename,
 *                  mode_t mode,
 *                  dev_t dev,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmknodat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fmknodat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.crt.syscall.futimesat64
/* errno_t futimesat64(fd_t dirfd,
 *                     const char *filename,
 *                     [2-3]struct __timeval64 const *times) */
INTERN_FUNCTION(libc_sys_futimesat64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_futimesat64, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_futimesat64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.kfstatat
/* errno_t kfstatat(fd_t dirfd,
 *                  char const *filename,
 *                  struct stat *statbuf,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_kfstatat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_kfstatat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kfstatat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.frenameat
/* errno_t frenameat(fd_t oldfd,
 *                   char const *oldname,
 *                   fd_t newfd,
 *                   char const *newname_or_path,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_frenameat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_frenameat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frenameat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.fsymlinkat
/* errno_t fsymlinkat(char const *link_text,
 *                    fd_t tofd,
 *                    char const *target_path,
 *                    atflag_t flags) */
INTERN_FUNCTION(libc_sys_fsymlinkat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fsymlinkat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsymlinkat)

/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.freadlinkat
/* ssize_t freadlinkat(fd_t dirfd,
 *                     char const *path,
 *                     char *buf,
 *                     size_t buflen,
 *                     atflag_t flags) */
INTERN_FUNCTION(libc_sys_freadlinkat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_freadlinkat, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_freadlinkat)

.section .text.crt.syscall.fallocate64
/* errno_t fallocate64(fd_t fd,
 *                     syscall_ulong_t mode,
 *                     uint64_t offset,
 *                     uint64_t length) */
INTERN_FUNCTION(libc_sys_fallocate64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fallocate64, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fallocate64)

.section .text.crt.syscall.preadvf
/* ssize_t preadvf(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 uint64_t offset,
 *                 iomode_t mode) */
INTERN_FUNCTION(libc_sys_preadvf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_preadvf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_preadvf)

.section .text.crt.syscall.pwritevf
/* ssize_t pwritevf(fd_t fd,
 *                  struct iovec const *iovec,
 *                  size_t count,
 *                  uint64_t offset,
 *                  iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwritevf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pwritevf, %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwritevf)

#endif /* !CONFIG_SYSCALL_EXCLUDE_WITHOUTEXCEPT */






#ifndef CONFIG_SYSCALL_EXCLUDE_WITHEXCEPT
.section .text.crt.syscall.Xread
/* ssize_t read(fd_t fd,
 *              void *buf,
 *              size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xread)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_read, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xread)

.section .text.crt.syscall.Xwrite
/* ssize_t write(fd_t fd,
 *               void const *buf,
 *               size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xwrite)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_write, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwrite)

.section .text.crt.syscall.Xopen
/* fd_t open(char const *filename,
 *           oflag_t oflags,
 *           mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopen)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_open, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopen)

/* Close a given file descriptor/handle `FD' */
.section .text.crt.syscall.Xclose
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xclose)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_close, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclose)

.section .text.crt.syscall.Xlinux_stat64
/* errno_t linux_stat64(char const *filename,
 *                      struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xlinux_stat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_stat64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlinux_stat64)

.section .text.crt.syscall.Xlinux_fstat64
/* errno_t linux_fstat64(fd_t fd,
 *                       struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xlinux_fstat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_fstat64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlinux_fstat64)

.section .text.crt.syscall.Xlinux_lstat64
/* errno_t linux_lstat64(char const *filename,
 *                       struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xlinux_lstat64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_linux_lstat64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlinux_lstat64)

.section .text.crt.syscall.Xpoll
/* ssize_t poll(struct pollfd *fds,
 *              size_t nfds,
 *              syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xpoll)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_poll, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpoll)

.section .text.crt.syscall.Xlseek64
/* int64_t lseek64(fd_t fd,
 *                 int64_t offset,
 *                 syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_Xlseek64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_lseek64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlseek64)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
.section .text.crt.syscall.Xmmap
/* void *mmap(void *addr,
 *            size_t len,
 *            syscall_ulong_t prot,
 *            syscall_ulong_t flags,
 *            fd_t fd,
 *            syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_Xmmap)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_mmap, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
.section .text.crt.syscall.Xmprotect
/* errno_t mprotect(void *addr,
 *                  size_t len,
 *                  syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_Xmprotect)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mprotect, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmprotect)

.section .text.crt.syscall.Xmunmap
/* errno_t munmap(void *addr,
 *                size_t len) */
INTERN_FUNCTION(libc_sys_Xmunmap)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_munmap, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunmap)

.section .text.crt.syscall.Xbrk
/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_Xbrk)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_brk, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xbrk)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xrt_sigaction
/* errno_t rt_sigaction(syscall_ulong_t signo,
 *                      struct sigaction const *act,
 *                      struct sigaction *oact,
 *                      size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigaction)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigaction, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.crt.syscall.Xrt_sigprocmask
/* errno_t rt_sigprocmask(syscall_ulong_t how,
 *                        struct __sigset_struct const *set,
 *                        struct __sigset_struct *oset,
 *                        size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigprocmask)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigprocmask, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigprocmask)

.section .text.crt.syscall.Xrt_sigreturn
/* void rt_sigreturn(void); */
INTERN_FUNCTION(libc_sys_Xrt_sigreturn)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_rt_sigreturn, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigreturn)

.section .text.crt.syscall.Xioctl
/* syscall_slong_t ioctl(fd_t fd,
 *                       syscall_ulong_t request,
 *                       void *arg) */
INTERN_FUNCTION(libc_sys_Xioctl)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioctl, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioctl)

.section .text.crt.syscall.Xpread64
/* ssize_t pread64(fd_t fd,
 *                 void *buf,
 *                 size_t bufsize,
 *                 uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpread64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pread64, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpread64)

.section .text.crt.syscall.Xpwrite64
/* ssize_t pwrite64(fd_t fd,
 *                  void const *buf,
 *                  size_t bufsize,
 *                  uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwrite64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pwrite64, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwrite64)

.section .text.crt.syscall.Xreadv
/* ssize_t readv(fd_t fd,
 *               struct iovec const *iovec,
 *               size_t count) */
INTERN_FUNCTION(libc_sys_Xreadv)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readv, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadv)

.section .text.crt.syscall.Xwritev
/* ssize_t writev(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count) */
INTERN_FUNCTION(libc_sys_Xwritev)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_writev, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
.section .text.crt.syscall.Xaccess
/* errno_t access(char const *filename,
 *                syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_Xaccess)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_access, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xaccess)

.section .text.crt.syscall.Xpipe
/* errno_t pipe([2]fd_t *pipedes) */
INTERN_FUNCTION(libc_sys_Xpipe)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_pipe, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpipe)

.section .text.crt.syscall.Xselect
/* ssize_t select(size_t nfds,
 *                struct __fd_set_struct *readfds,
 *                struct __fd_set_struct *writefds,
 *                struct __fd_set_struct *exceptfds,
 *                struct __timeval32 *timeout) */
INTERN_FUNCTION(libc_sys_Xselect)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_select, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xselect)

.section .text.crt.syscall.Xsched_yield
/* errno_t sched_yield(void); */
INTERN_FUNCTION(libc_sys_Xsched_yield)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_sched_yield, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
.section .text.crt.syscall.Xmremap
/* void *mremap(void *addr,
 *              size_t old_len,
 *              size_t new_len,
 *              syscall_ulong_t flags,
 *              void *new_address) */
INTERN_FUNCTION(libc_sys_Xmremap)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_mremap, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmremap)

.section .text.crt.syscall.Xmsync
/* errno_t msync(void *addr,
 *               size_t len,
 *               syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmsync)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_msync, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsync)

.section .text.crt.syscall.Xmincore
/* errno_t mincore(void *start,
 *                 size_t len,
 *                 uint8_t *vec) */
INTERN_FUNCTION(libc_sys_Xmincore)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mincore, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmincore)

.section .text.crt.syscall.Xmadvise
/* errno_t madvise(void *addr,
 *                 size_t len,
 *                 syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_Xmadvise)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_madvise, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmadvise)

.section .text.crt.syscall.Xdup
/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xdup)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_dup, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup)

.section .text.crt.syscall.Xdup2
/* fd_t dup2(fd_t oldfd,
 *           fd_t newfd) */
INTERN_FUNCTION(libc_sys_Xdup2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_dup2, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup2)

.section .text.crt.syscall.Xpause
/* errno_t pause(void); */
INTERN_FUNCTION(libc_sys_Xpause)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_pause, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpause)

.section .text.crt.syscall.Xnanosleep
/* errno_t nanosleep(struct __timespec32 const *req,
 *                   struct __timespec32 *rem) */
INTERN_FUNCTION(libc_sys_Xnanosleep)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_nanosleep, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xnanosleep)

.section .text.crt.syscall.Xgetitimer
/* errno_t getitimer(syscall_ulong_t which,
 *                   struct __itimerval32 *curr_value) */
INTERN_FUNCTION(libc_sys_Xgetitimer)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getitimer, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetitimer)

.section .text.crt.syscall.Xalarm
/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_Xalarm)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_alarm, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xalarm)

.section .text.crt.syscall.Xsetitimer
/* errno_t setitimer(syscall_ulong_t which,
 *                   struct __itimerval32 const *newval,
 *                   struct __itimerval32 *oldval) */
INTERN_FUNCTION(libc_sys_Xsetitimer)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setitimer, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetitimer)

.section .text.crt.syscall.Xgetpid
/* pid_t getpid(void); */
INTERN_FUNCTION(libc_sys_Xgetpid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getpid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpid)

.section .text.crt.syscall.Xsendfile
/* ssize_t sendfile(fd_t out_fd,
 *                  fd_t in_fd,
 *                  syscall_ulong_t *offset,
 *                  size_t count) */
INTERN_FUNCTION(libc_sys_Xsendfile)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sendfile, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendfile)

.section .text.crt.syscall.Xsocket
/* fd_t socket(syscall_ulong_t domain,
 *             syscall_ulong_t type,
 *             syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_Xsocket)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_socket, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsocket)

.section .text.crt.syscall.Xconnect
/* errno_t connect(fd_t sockfd,
 *                 struct sockaddr const *addr,
 *                 socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xconnect)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_connect, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xconnect)

/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
.section .text.crt.syscall.Xsendto
/* ssize_t sendto(fd_t sockfd,
 *                void const *buf,
 *                size_t bufsize,
 *                syscall_ulong_t flags,
 *                struct sockaddr const *addr,
 *                socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xsendto)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_sendto, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendto)

.section .text.crt.syscall.Xrecvfrom
/* ssize_t recvfrom(fd_t sockfd,
 *                  void *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t flags,
 *                  struct sockaddr *addr,
 *                  socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xrecvfrom)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_recvfrom, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvfrom)

.section .text.crt.syscall.Xsendmsg
/* ssize_t sendmsg(fd_t sockfd,
 *                 struct msghdr const *message,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsendmsg)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sendmsg, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendmsg)

.section .text.crt.syscall.Xrecvmsg
/* ssize_t recvmsg(fd_t sockfd,
 *                 struct msghdr *message,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xrecvmsg)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_recvmsg, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
.section .text.crt.syscall.Xshutdown
/* errno_t shutdown(fd_t sockfd,
 *                  syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xshutdown)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_shutdown, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshutdown)

.section .text.crt.syscall.Xbind
/* errno_t bind(fd_t sockfd,
 *              struct sockaddr const *addr,
 *              socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xbind)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_bind, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xbind)

.section .text.crt.syscall.Xlisten
/* errno_t listen(fd_t sockfd,
 *                syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_Xlisten)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_listen, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlisten)

.section .text.crt.syscall.Xgetsockname
/* errno_t getsockname(fd_t sockfd,
 *                     struct sockaddr *addr,
 *                     socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetsockname)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getsockname, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsockname)

.section .text.crt.syscall.Xgetpeername
/* errno_t getpeername(fd_t sockfd,
 *                     struct sockaddr *addr,
 *                     socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetpeername)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getpeername, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpeername)

.section .text.crt.syscall.Xsocketpair
/* errno_t socketpair(syscall_ulong_t domain,
 *                    syscall_ulong_t type,
 *                    syscall_ulong_t protocol,
 *                    [2]fd_t *fds) */
INTERN_FUNCTION(libc_sys_Xsocketpair)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_socketpair, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsocketpair)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.crt.syscall.Xsetsockopt
/* errno_t setsockopt(fd_t sockfd,
 *                    syscall_ulong_t level,
 *                    syscall_ulong_t optname,
 *                    void const *optval,
 *                    socklen_t optlen) */
INTERN_FUNCTION(libc_sys_Xsetsockopt)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_setsockopt, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.crt.syscall.Xgetsockopt
/* errno_t getsockopt(fd_t sockfd,
 *                    syscall_ulong_t level,
 *                    syscall_ulong_t optname,
 *                    void *optval,
 *                    socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_Xgetsockopt)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_getsockopt, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsockopt)

.section .text.crt.syscall.Xclone
/* pid_t clone(syscall_ulong_t flags,
 *             void *child_stack,
 *             pid_t *ptid,
 *             pid_t *ctid,
 *             uintptr_t newtls) */
INTERN_FUNCTION(libc_sys_Xclone)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_clone, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclone)

.section .text.crt.syscall.Xfork
/* pid_t fork(void); */
INTERN_FUNCTION(libc_sys_Xfork)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_fork, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfork)

.section .text.crt.syscall.Xvfork
/* pid_t vfork(void); */
INTERN_FUNCTION(libc_sys_Xvfork)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_vfork, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvfork)

.section .text.crt.syscall.Xexecve
/* errno_t execve(char const *path,
 *                char const *const *argv,
 *                char const *const *envp) */
INTERN_FUNCTION(libc_sys_Xexecve)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_execve, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexecve)

.section .text.crt.syscall.Xexit
/* void exit(syscall_ulong_t status) */
INTERN_FUNCTION(libc_sys_Xexit)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_exit, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexit)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.crt.syscall.Xwait4
/* pid_t wait4(pid_t pid,
 *             int32_t *stat_loc,
 *             syscall_ulong_t options,
 *             struct rusage *usage) */
INTERN_FUNCTION(libc_sys_Xwait4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_wait4, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwait4)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xkill
/* errno_t kill(pid_t pid,
 *              syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_Xkill)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kill, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkill)

.section .text.crt.syscall.Xuname
/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_Xuname)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_uname, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xuname)

.section .text.crt.syscall.Xfcntl
/* syscall_slong_t fcntl(fd_t fd,
 *                       syscall_ulong_t cmd,
 *                       void *arg) */
INTERN_FUNCTION(libc_sys_Xfcntl)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fcntl, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfcntl)

.section .text.crt.syscall.Xflock
/* errno_t flock(fd_t fd,
 *               syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_Xflock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_flock, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xflock)

.section .text.crt.syscall.Xfsync
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfsync)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fsync, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsync)

.section .text.crt.syscall.Xfdatasync
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfdatasync)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fdatasync, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfdatasync)

.section .text.crt.syscall.Xtruncate
/* errno_t truncate(char const *filename,
 *                  syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xtruncate)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_truncate, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtruncate)

.section .text.crt.syscall.Xftruncate
/* errno_t ftruncate(fd_t fd,
 *                   syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xftruncate)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ftruncate, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xftruncate)

.section .text.crt.syscall.Xgetdents
/* ssize_t getdents(fd_t fd,
 *                  struct linux_dirent *dirp,
 *                  size_t count) */
INTERN_FUNCTION(libc_sys_Xgetdents)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getdents, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdents)

.section .text.crt.syscall.Xgetcwd
/* ssize_t getcwd(char *buf,
 *                size_t size) */
INTERN_FUNCTION(libc_sys_Xgetcwd)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getcwd, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetcwd)

.section .text.crt.syscall.Xchdir
/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xchdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_chdir, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchdir)

.section .text.crt.syscall.Xfchdir
/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfchdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fchdir, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchdir)

.section .text.crt.syscall.Xrename
/* errno_t rename(char const *oldname,
 *                char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrename)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rename, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrename)

.section .text.crt.syscall.Xmkdir
/* errno_t mkdir(char const *pathname,
 *               mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdir)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_mkdir, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmkdir)

.section .text.crt.syscall.Xrmdir
/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xrmdir)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_rmdir, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrmdir)

.section .text.crt.syscall.Xcreat
/* fd_t creat(char const *filename,
 *            mode_t mode) */
INTERN_FUNCTION(libc_sys_Xcreat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_creat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcreat)

.section .text.crt.syscall.Xlink
/* errno_t link(char const *existing_file,
 *              char const *link_file) */
INTERN_FUNCTION(libc_sys_Xlink)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_link, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlink)

.section .text.crt.syscall.Xunlink
/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_Xunlink)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_unlink, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunlink)

.section .text.crt.syscall.Xsymlink
/* errno_t symlink(char const *link_text,
 *                 char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlink)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_symlink, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsymlink)

.section .text.crt.syscall.Xreadlink
/* ssize_t readlink(char const *path,
 *                  char *buf,
 *                  size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlink)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readlink, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadlink)

.section .text.crt.syscall.Xchmod
/* errno_t chmod(char const *filename,
 *               mode_t mode) */
INTERN_FUNCTION(libc_sys_Xchmod)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_chmod, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchmod)

.section .text.crt.syscall.Xfchmod
/* errno_t fchmod(fd_t fd,
 *                mode_t mode) */
INTERN_FUNCTION(libc_sys_Xfchmod)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fchmod, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchmod)

.section .text.crt.syscall.Xchown
/* errno_t chown(char const *filename,
 *               uint32_t owner,
 *               uint32_t group) */
INTERN_FUNCTION(libc_sys_Xchown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_chown, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchown)

.section .text.crt.syscall.Xfchown
/* errno_t fchown(fd_t fd,
 *                uint32_t owner,
 *                uint32_t group) */
INTERN_FUNCTION(libc_sys_Xfchown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fchown, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchown)

.section .text.crt.syscall.Xlchown
/* errno_t lchown(char const *filename,
 *                uint32_t owner,
 *                uint32_t group) */
INTERN_FUNCTION(libc_sys_Xlchown)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_lchown, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlchown)

.section .text.crt.syscall.Xumask
/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_Xumask)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_umask, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xumask)

.section .text.crt.syscall.Xgettimeofday
/* errno_t gettimeofday(struct __timeval32 *tv,
 *                      struct timezone *tz) */
INTERN_FUNCTION(libc_sys_Xgettimeofday)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_gettimeofday, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgettimeofday)

.section .text.crt.syscall.Xgetrlimit
/* errno_t getrlimit(syscall_ulong_t resource,
 *                   struct rlimit *rlimits) */
INTERN_FUNCTION(libc_sys_Xgetrlimit)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getrlimit, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetrlimit)

.section .text.crt.syscall.Xgetrusage
/* errno_t getrusage(syscall_slong_t who,
 *                   struct rusage *usage) */
INTERN_FUNCTION(libc_sys_Xgetrusage)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getrusage, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetrusage)

.section .text.crt.syscall.Xsysinfo
/* errno_t sysinfo(struct sysinfo *info) */
INTERN_FUNCTION(libc_sys_Xsysinfo)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sysinfo, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsysinfo)

.section .text.crt.syscall.Xtimes
/* clock_t times(struct tms *buf) */
INTERN_FUNCTION(libc_sys_Xtimes)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_times, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimes)

.section .text.crt.syscall.Xptrace
/* syscall_slong_t ptrace(syscall_ulong_t request,
 *                        pid_t pid,
 *                        void *addr,
 *                        void *data) */
INTERN_FUNCTION(libc_sys_Xptrace)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_ptrace, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xptrace)

.section .text.crt.syscall.Xgetuid32
/* uint32_t getuid32(void); */
INTERN_FUNCTION(libc_sys_Xgetuid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetuid32)

.section .text.crt.syscall.Xsyslog
/* ssize_t syslog(syscall_ulong_t level,
 *                char const *str,
 *                size_t len) */
INTERN_FUNCTION(libc_sys_Xsyslog)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_syslog, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsyslog)

.section .text.crt.syscall.Xgetgid32
/* uint32_t getgid32(void); */
INTERN_FUNCTION(libc_sys_Xgetgid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getgid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetgid32)

.section .text.crt.syscall.Xsetuid32
/* errno_t setuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_Xsetuid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetuid32)

.section .text.crt.syscall.Xsetgid32
/* errno_t setgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_Xsetgid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setgid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetgid32)

.section .text.crt.syscall.Xgeteuid32
/* uint32_t geteuid32(void); */
INTERN_FUNCTION(libc_sys_Xgeteuid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_geteuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgeteuid32)

.section .text.crt.syscall.Xgetegid32
/* uint32_t getegid32(void); */
INTERN_FUNCTION(libc_sys_Xgetegid32)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getegid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetegid32)

.section .text.crt.syscall.Xsetpgid
/* errno_t setpgid(pid_t pid,
 *                 pid_t pgid) */
INTERN_FUNCTION(libc_sys_Xsetpgid)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setpgid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetpgid)

.section .text.crt.syscall.Xgetppid
/* pid_t getppid(void); */
INTERN_FUNCTION(libc_sys_Xgetppid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getppid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetppid)

.section .text.crt.syscall.Xgetpgrp
/* pid_t getpgrp(void); */
INTERN_FUNCTION(libc_sys_Xgetpgrp)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getpgrp, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpgrp)

.section .text.crt.syscall.Xsetsid
/* pid_t setsid(void); */
INTERN_FUNCTION(libc_sys_Xsetsid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_setsid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetsid)

.section .text.crt.syscall.Xsetreuid32
/* errno_t setreuid32(uint32_t ruid,
 *                    uint32_t euid) */
INTERN_FUNCTION(libc_sys_Xsetreuid32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setreuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetreuid32)

.section .text.crt.syscall.Xsetregid32
/* errno_t setregid32(uint32_t rgid,
 *                    uint32_t egid) */
INTERN_FUNCTION(libc_sys_Xsetregid32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setregid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetregid32)

.section .text.crt.syscall.Xgetgroups32
/* errno_t getgroups32(size_t size,
 *                     []uint32_t *list) */
INTERN_FUNCTION(libc_sys_Xgetgroups32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getgroups32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetgroups32)

.section .text.crt.syscall.Xsetgroups32
/* errno_t setgroups32(size_t count,
 *                     uint32_t const *groups) */
INTERN_FUNCTION(libc_sys_Xsetgroups32)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setgroups32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetgroups32)

.section .text.crt.syscall.Xsetresuid32
/* errno_t setresuid32(uint32_t ruid,
 *                     uint32_t euid,
 *                     uint32_t suid) */
INTERN_FUNCTION(libc_sys_Xsetresuid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setresuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetresuid32)

.section .text.crt.syscall.Xgetresuid32
/* errno_t getresuid32(uint32_t *ruid,
 *                     uint32_t *euid,
 *                     uint32_t *suid) */
INTERN_FUNCTION(libc_sys_Xgetresuid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getresuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetresuid32)

.section .text.crt.syscall.Xsetresgid32
/* errno_t setresgid32(uint32_t rgid,
 *                     uint32_t egid,
 *                     uint32_t sgid) */
INTERN_FUNCTION(libc_sys_Xsetresgid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setresgid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetresgid32)

.section .text.crt.syscall.Xgetresgid32
/* errno_t getresgid32(uint32_t *rgid,
 *                     uint32_t *egid,
 *                     uint32_t *sgid) */
INTERN_FUNCTION(libc_sys_Xgetresgid32)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getresgid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetresgid32)

.section .text.crt.syscall.Xgetpgid
/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetpgid)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_getpgid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpgid)

.section .text.crt.syscall.Xsetfsuid32
/* errno_t setfsuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_Xsetfsuid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setfsuid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetfsuid32)

.section .text.crt.syscall.Xsetfsgid32
/* errno_t setfsgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_Xsetfsgid32)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_setfsgid32, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetfsgid32)

.section .text.crt.syscall.Xgetsid
/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetsid)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_getsid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsid)

.section .text.crt.syscall.Xrt_sigpending
/* errno_t rt_sigpending(struct __sigset_struct *set,
 *                       size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigpending)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rt_sigpending, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigpending)

.section .text.crt.syscall.Xrt_sigtimedwait
/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set,
 *                                 struct __siginfo_struct *info,
 *                                 struct __timespec32 const *timeout,
 *                                 size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_sigtimedwait, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigtimedwait)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xrt_sigqueueinfo
/* errno_t rt_sigqueueinfo(pid_t tgid,
 *                         syscall_ulong_t signo,
 *                         struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_sigqueueinfo)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_rt_sigqueueinfo, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigqueueinfo)

.section .text.crt.syscall.Xrt_sigsuspend
/* errno_t rt_sigsuspend(struct __sigset_struct const *set,
 *                       size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigsuspend)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_rt_sigsuspend, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigsuspend)

.section .text.crt.syscall.Xsigaltstack
/* errno_t sigaltstack(struct sigaltstack const *ss,
 *                     struct sigaltstack *oss) */
INTERN_FUNCTION(libc_sys_Xsigaltstack)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sigaltstack, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsigaltstack)

.section .text.crt.syscall.Xutime
/* errno_t utime(char const *filename,
 *               struct __utimbuf32 const *times) */
INTERN_FUNCTION(libc_sys_Xutime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utime, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutime)

.section .text.crt.syscall.Xmknod
/* errno_t mknod(char const *nodename,
 *               mode_t mode,
 *               dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknod)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mknod, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmknod)

.section .text.crt.syscall.Xustat
/* errno_t ustat(dev_t dev,
 *               struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_Xustat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ustat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xustat)

.section .text.crt.syscall.Xstatfs
/* errno_t statfs(char const *file,
 *                struct __statfs32 *buf) */
INTERN_FUNCTION(libc_sys_Xstatfs)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_statfs, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xstatfs)

.section .text.crt.syscall.Xfstatfs
/* errno_t fstatfs(fd_t file,
 *                 struct __statfs32 *buf) */
INTERN_FUNCTION(libc_sys_Xfstatfs)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fstatfs, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfstatfs)

.section .text.crt.syscall.Xgetpriority
/* syscall_slong_t getpriority(syscall_ulong_t which,
 *                             id_t who) */
INTERN_FUNCTION(libc_sys_Xgetpriority)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getpriority, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpriority)

.section .text.crt.syscall.Xsetpriority
/* errno_t setpriority(syscall_ulong_t which,
 *                     id_t who,
 *                     syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_Xsetpriority)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setpriority, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetpriority)

.section .text.crt.syscall.Xsched_setparam
/* errno_t sched_setparam(pid_t pid,
 *                        struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setparam)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_setparam, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setparam)

.section .text.crt.syscall.Xsched_getparam
/* errno_t sched_getparam(pid_t pid,
 *                        struct sched_param *param) */
INTERN_FUNCTION(libc_sys_Xsched_getparam)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_getparam, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getparam)

.section .text.crt.syscall.Xsched_setscheduler
/* errno_t sched_setscheduler(pid_t pid,
 *                            syscall_ulong_t policy,
 *                            struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setscheduler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_setscheduler, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setscheduler)

.section .text.crt.syscall.Xsched_getscheduler
/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xsched_getscheduler)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_getscheduler, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getscheduler)

.section .text.crt.syscall.Xsched_get_priority_max
/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_max)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_get_priority_max, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_get_priority_max)

.section .text.crt.syscall.Xsched_get_priority_min
/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_min)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_sched_get_priority_min, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_get_priority_min)

.section .text.crt.syscall.Xsched_rr_get_interval
/* errno_t sched_rr_get_interval(pid_t pid,
 *                               struct __timespec32 *tms) */
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sched_rr_get_interval, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_rr_get_interval)

.section .text.crt.syscall.Xmlock
/* errno_t mlock(void const *addr,
 *               size_t len) */
INTERN_FUNCTION(libc_sys_Xmlock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_mlock, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmlock)

.section .text.crt.syscall.Xmunlock
/* errno_t munlock(void const *addr,
 *                 size_t len) */
INTERN_FUNCTION(libc_sys_Xmunlock)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_munlock, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunlock)

.section .text.crt.syscall.Xmlockall
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmlockall)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_mlockall, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmlockall)

.section .text.crt.syscall.Xmunlockall
/* errno_t munlockall(void); */
INTERN_FUNCTION(libc_sys_Xmunlockall)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_munlockall, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunlockall)

.section .text.crt.syscall.Xvhangup
/* errno_t vhangup(void); */
INTERN_FUNCTION(libc_sys_Xvhangup)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_vhangup, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvhangup)

.section .text.crt.syscall.Xmodify_ldt
/* syscall_slong_t modify_ldt(syscall_ulong_t func,
 *                            void *ptr,
 *                            syscall_ulong_t bytecount) */
INTERN_FUNCTION(libc_sys_Xmodify_ldt)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_modify_ldt, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmodify_ldt)

.section .text.crt.syscall.Xsetrlimit
/* errno_t setrlimit(syscall_ulong_t resource,
 *                   struct rlimit const *rlimits) */
INTERN_FUNCTION(libc_sys_Xsetrlimit)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setrlimit, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetrlimit)

.section .text.crt.syscall.Xchroot
/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_Xchroot)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_chroot, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchroot)

.section .text.crt.syscall.Xsync
/* errno_t sync(void); */
INTERN_FUNCTION(libc_sys_Xsync)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_sync, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsync)

.section .text.crt.syscall.Xacct
/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_Xacct)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_acct, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xacct)

.section .text.crt.syscall.Xsettimeofday
/* errno_t settimeofday(struct __timeval32 const *tv,
 *                      struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_Xsettimeofday)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_settimeofday, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsettimeofday)

.section .text.crt.syscall.Xmount
/* errno_t mount(char const *special_file,
 *               char const *dir,
 *               char const *fstype,
 *               syscall_ulong_t rwflag,
 *               void const *data) */
INTERN_FUNCTION(libc_sys_Xmount)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_mount, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmount)

.section .text.crt.syscall.Xumount2
/* errno_t umount2(char const *special_file,
 *                 syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xumount2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_umount2, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xumount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
.section .text.crt.syscall.Xswapon
/* errno_t swapon(char const *pathname,
 *                syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_Xswapon)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_swapon, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xswapon)

.section .text.crt.syscall.Xswapoff
/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_Xswapoff)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_swapoff, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xswapoff)

/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
.section .text.crt.syscall.Xreboot
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xreboot)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_reboot, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreboot)

.section .text.crt.syscall.Xsethostname
/* errno_t sethostname(char const *name,
 *                     size_t len) */
INTERN_FUNCTION(libc_sys_Xsethostname)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sethostname, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsethostname)

.section .text.crt.syscall.Xsetdomainname
/* errno_t setdomainname(char const *name,
 *                       size_t len) */
INTERN_FUNCTION(libc_sys_Xsetdomainname)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setdomainname, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetdomainname)

.section .text.crt.syscall.Xiopl
/* errno_t iopl(syscall_ulong_t level) */
INTERN_FUNCTION(libc_sys_Xiopl)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_iopl, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xiopl)

.section .text.crt.syscall.Xioperm
/* errno_t ioperm(syscall_ulong_t from,
 *                syscall_ulong_t num,
 *                syscall_ulong_t turn_on) */
INTERN_FUNCTION(libc_sys_Xioperm)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioperm, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioperm)

.section .text.crt.syscall.Xgettid
/* pid_t gettid(void); */
INTERN_FUNCTION(libc_sys_Xgettid)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_gettid, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgettid)

.section .text.crt.syscall.Xreadahead
/* ssize_t readahead(fd_t fd,
 *                   uint64_t offset,
 *                   size_t count) */
INTERN_FUNCTION(libc_sys_Xreadahead)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_readahead, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadahead)

.section .text.crt.syscall.Xsetxattr
/* errno_t setxattr(char const *path,
 *                  char const *name,
 *                  void const *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsetxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_setxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetxattr)

.section .text.crt.syscall.Xlsetxattr
/* errno_t lsetxattr(char const *path,
 *                   char const *name,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xlsetxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lsetxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlsetxattr)

.section .text.crt.syscall.Xfsetxattr
/* errno_t fsetxattr(fd_t fd,
 *                   char const *name,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xfsetxattr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fsetxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsetxattr)

.section .text.crt.syscall.Xgetxattr
/* ssize_t getxattr(char const *path,
 *                  char const *name,
 *                  void *buf,
 *                  size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xgetxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_getxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetxattr)

.section .text.crt.syscall.Xlgetxattr
/* ssize_t lgetxattr(char const *path,
 *                   char const *name,
 *                   void *buf,
 *                   size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xlgetxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_lgetxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlgetxattr)

.section .text.crt.syscall.Xfgetxattr
/* ssize_t fgetxattr(fd_t fd,
 *                   char const *name,
 *                   void *buf,
 *                   size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xfgetxattr)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fgetxattr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfgetxattr)

.section .text.crt.syscall.Xlistxattr
/* ssize_t listxattr(char const *path,
 *                   char *listbuf,
 *                   size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xlistxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_listxattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlistxattr)

.section .text.crt.syscall.Xllistxattr
/* ssize_t llistxattr(char const *path,
 *                    char *listbuf,
 *                    size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xllistxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_llistxattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xllistxattr)

.section .text.crt.syscall.Xflistxattr
/* ssize_t flistxattr(fd_t fd,
 *                    char *listbuf,
 *                    size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xflistxattr)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_flistxattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xflistxattr)

.section .text.crt.syscall.Xremovexattr
/* errno_t removexattr(char const *path,
 *                     char const *name) */
INTERN_FUNCTION(libc_sys_Xremovexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_removexattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xremovexattr)

.section .text.crt.syscall.Xlremovexattr
/* errno_t lremovexattr(char const *path,
 *                      char const *name) */
INTERN_FUNCTION(libc_sys_Xlremovexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_lremovexattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlremovexattr)

.section .text.crt.syscall.Xfremovexattr
/* errno_t fremovexattr(int fd,
 *                      char const *name) */
INTERN_FUNCTION(libc_sys_Xfremovexattr)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_fremovexattr, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfremovexattr)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xtkill
/* errno_t tkill(pid_t tid,
 *               syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_Xtkill)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_tkill, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtkill)

.section .text.crt.syscall.Xtime
/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_Xtime)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_time, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtime)

.section .text.crt.syscall.Xfutex
/* syscall_slong_t futex(uint32_t *uaddr,
 *                       syscall_ulong_t futex_op,
 *                       uint32_t val,
 *                       struct __timespec32 const *timeout_or_val2,
 *                       uint32_t *uaddr2,
 *                       uint32_t val3) */
INTERN_FUNCTION(libc_sys_Xfutex)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_futex, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfutex)

.section .text.crt.syscall.Xsched_setaffinity
/* errno_t sched_setaffinity(pid_t pid,
 *                           size_t cpusetsize,
 *                           struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_setaffinity)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_setaffinity, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setaffinity)

.section .text.crt.syscall.Xsched_getaffinity
/* errno_t sched_getaffinity(pid_t pid,
 *                           size_t cpusetsize,
 *                           struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_getaffinity)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_sched_getaffinity, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getaffinity)

.section .text.crt.syscall.Xepoll_create
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_Xepoll_create)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_epoll_create, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_create)

.section .text.crt.syscall.Xepoll_ctl_old
/* errno_t epoll_ctl_old(fd_t epfd,
 *                       syscall_ulong_t op,
 *                       fd_t fd,
 *                       struct epoll_event *event) */
INTERN_FUNCTION(libc_sys_Xepoll_ctl_old)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_ctl_old, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_ctl_old)

.section .text.crt.syscall.Xepoll_wait_old
/* errno_t epoll_wait_old(fd_t epfd,
 *                        struct epoll_event *events,
 *                        syscall_ulong_t maxevents,
 *                        syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xepoll_wait_old)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_wait_old, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_wait_old)

.section .text.crt.syscall.Xremap_file_pages
/* errno_t remap_file_pages(void *start,
 *                          size_t size,
 *                          syscall_ulong_t prot,
 *                          size_t pgoff,
 *                          syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xremap_file_pages)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_remap_file_pages, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xremap_file_pages)

.section .text.crt.syscall.Xgetdents64
/* ssize_t getdents64(fd_t fd,
 *                    struct linux_dirent64 *dirp,
 *                    size_t count) */
INTERN_FUNCTION(libc_sys_Xgetdents64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getdents64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdents64)

.section .text.crt.syscall.Xset_tid_address
/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_Xset_tid_address)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_set_tid_address, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_tid_address)

.section .text.crt.syscall.Xtimer_create
/* errno_t timer_create(clockid_t clock_id,
 *                      struct sigevent *evp,
 *                      timer_t *timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_create)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_timer_create, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_create)

.section .text.crt.syscall.Xtimer_settime
/* errno_t timer_settime(timer_t timerid,
 *                       syscall_ulong_t flags,
 *                       struct __itimerspec32 const *value,
 *                       struct __itimerspec32 *ovalue) */
INTERN_FUNCTION(libc_sys_Xtimer_settime)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_timer_settime, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_settime)

.section .text.crt.syscall.Xtimer_gettime
/* errno_t timer_gettime(timer_t timerid,
 *                       struct __itimerspec32 *value) */
INTERN_FUNCTION(libc_sys_Xtimer_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timer_gettime, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_gettime)

.section .text.crt.syscall.Xtimer_getoverrun
/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_getoverrun)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_timer_getoverrun, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_getoverrun)

.section .text.crt.syscall.Xtimer_delete
/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_delete)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_timer_delete, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_delete)

.section .text.crt.syscall.Xclock_settime
/* errno_t clock_settime(clockid_t clock_id,
 *                       struct __timespec32 const *tp) */
INTERN_FUNCTION(libc_sys_Xclock_settime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_settime, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_settime)

.section .text.crt.syscall.Xclock_gettime
/* errno_t clock_gettime(clockid_t clock_id,
 *                       struct __timespec32 *tp) */
INTERN_FUNCTION(libc_sys_Xclock_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_gettime, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_gettime)

.section .text.crt.syscall.Xclock_getres
/* errno_t clock_getres(clockid_t clock_id,
 *                      struct __timespec32 *res) */
INTERN_FUNCTION(libc_sys_Xclock_getres)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_clock_getres, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_getres)

.section .text.crt.syscall.Xclock_nanosleep
/* errno_t clock_nanosleep(clockid_t clock_id,
 *                         syscall_ulong_t flags,
 *                         struct __timespec32 const *requested_time,
 *                         struct __timespec32 *remaining) */
INTERN_FUNCTION(libc_sys_Xclock_nanosleep)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_clock_nanosleep, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_nanosleep)

.section .text.crt.syscall.Xexit_group
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_Xexit_group)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_exit_group, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexit_group)

.section .text.crt.syscall.Xepoll_wait
/* errno_t epoll_wait(fd_t epfd,
 *                    struct epoll_event *events,
 *                    syscall_ulong_t maxevents,
 *                    syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xepoll_wait)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_wait, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_wait)

.section .text.crt.syscall.Xepoll_ctl
/* errno_t epoll_ctl(fd_t epfd,
 *                   syscall_ulong_t op,
 *                   fd_t fd,
 *                   struct epoll_event *event) */
INTERN_FUNCTION(libc_sys_Xepoll_ctl)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_epoll_ctl, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_ctl)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xtgkill
/* errno_t tgkill(pid_t tgid,
 *                pid_t tid,
 *                syscall_ulong_t signo) */
INTERN_FUNCTION(libc_sys_Xtgkill)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_tgkill, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtgkill)

.section .text.crt.syscall.Xutimes
/* errno_t utimes(char const *filename,
 *                [2]struct __timeval32 const *times) */
INTERN_FUNCTION(libc_sys_Xutimes)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utimes, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutimes)

/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
.section .text.crt.syscall.Xwaitid
/* errno_t waitid(idtype_t idtype,
 *                id_t id,
 *                struct __siginfo_struct *infop,
 *                syscall_ulong_t options,
 *                struct rusage *ru) */
INTERN_FUNCTION(libc_sys_Xwaitid)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_waitid, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwaitid)

.section .text.crt.syscall.Xioprio_set
/* errno_t ioprio_set(syscall_ulong_t which,
 *                    syscall_ulong_t who,
 *                    syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_Xioprio_set)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_ioprio_set, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioprio_set)

.section .text.crt.syscall.Xioprio_get
/* errno_t ioprio_get(syscall_ulong_t which,
 *                    syscall_ulong_t who) */
INTERN_FUNCTION(libc_sys_Xioprio_get)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_ioprio_get, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioprio_get)

.section .text.crt.syscall.Xopenat
/* fd_t openat(fd_t dirfd,
 *             char const *filename,
 *             oflag_t oflags,
 *             mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopenat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_openat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopenat)

.section .text.crt.syscall.Xmkdirat
/* errno_t mkdirat(fd_t dirfd,
 *                 char const *pathname,
 *                 mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdirat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_mkdirat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmkdirat)

.section .text.crt.syscall.Xmknodat
/* errno_t mknodat(fd_t dirfd,
 *                 char const *nodename,
 *                 mode_t mode,
 *                 dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknodat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_mknodat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.Xfchownat
/* errno_t fchownat(fd_t dirfd,
 *                  char const *filename,
 *                  uint32_t owner,
 *                  uint32_t group,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchownat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fchownat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchownat)

.section .text.crt.syscall.Xfutimesat
/* errno_t futimesat(fd_t dirfd,
 *                   const char *filename,
 *                   [2]struct __timeval32 const *times) */
INTERN_FUNCTION(libc_sys_Xfutimesat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_futimesat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfutimesat)

.section .text.crt.syscall.Xfstatat
/* errno_t fstatat(fd_t dirfd,
 *                 char const *filename,
 *                 struct linux64_stat32 *statbuf,
 *                 atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfstatat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fstatat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfstatat)

/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
.section .text.crt.syscall.Xunlinkat
/* errno_t unlinkat(fd_t dirfd,
 *                  char const *name,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xunlinkat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_unlinkat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunlinkat)

.section .text.crt.syscall.Xrenameat
/* errno_t renameat(fd_t oldfd,
 *                  char const *oldname,
 *                  fd_t newfd,
 *                  char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrenameat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_renameat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrenameat)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.Xlinkat
/* errno_t linkat(fd_t fromfd,
 *                char const *existing_file,
 *                fd_t tofd,
 *                char const *target_path,
 *                atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xlinkat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_linkat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlinkat)

.section .text.crt.syscall.Xsymlinkat
/* errno_t symlinkat(char const *link_text,
 *                   fd_t tofd,
 *                   char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlinkat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_symlinkat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsymlinkat)

.section .text.crt.syscall.Xreadlinkat
/* ssize_t readlinkat(fd_t dirfd,
 *                    char const *path,
 *                    char *buf,
 *                    size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlinkat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readlinkat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadlinkat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.Xfchmodat
/* errno_t fchmodat(fd_t dirfd,
 *                  char const *filename,
 *                  mode_t mode,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchmodat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fchmodat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
.section .text.crt.syscall.Xfaccessat
/* errno_t faccessat(fd_t dirfd,
 *                   char const *filename,
 *                   syscall_ulong_t type,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfaccessat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_faccessat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfaccessat)

.section .text.crt.syscall.Xpselect6
/* ssize_t pselect6(size_t nfds,
 *                  struct __fd_set_struct *readfds,
 *                  struct __fd_set_struct *writefds,
 *                  struct __fd_set_struct *exceptfds,
 *                  struct __timespec32 const *timeout,
 *                  void const *sigmask_sigset_and_len) */
INTERN_FUNCTION(libc_sys_Xpselect6)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_pselect6, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpselect6)

.section .text.crt.syscall.Xppoll
/* ssize_t ppoll(struct pollfd *fds,
 *               size_t nfds,
 *               struct __timespec32 const *timeout_ts,
 *               struct __sigset_struct const *sigmask,
 *               size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xppoll)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_ppoll, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xppoll)

/* param flags: Set of `CLONE_*' */
.section .text.crt.syscall.Xunshare
/* errno_t unshare(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xunshare)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_unshare, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunshare)

.section .text.crt.syscall.Xsplice
/* ssize_t splice(fd_t fdin,
 *                uint64_t *offin,
 *                fd_t fdout,
 *                uint64_t *offout,
 *                size_t length,
 *                syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsplice)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_splice, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsplice)

.section .text.crt.syscall.Xtee
/* ssize_t tee(fd_t fdin,
 *             fd_t fdout,
 *             size_t length,
 *             syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtee)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_tee, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtee)

.section .text.crt.syscall.Xsync_file_range
/* errno_t sync_file_range(fd_t fd,
 *                         uint64_t offset,
 *                         uint64_t count,
 *                         syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsync_file_range)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sync_file_range, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsync_file_range)

.section .text.crt.syscall.Xvmsplice
/* ssize_t vmsplice(fd_t fdout,
 *                  struct iovec const *iov,
 *                  size_t count,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xvmsplice)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_vmsplice, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvmsplice)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.crt.syscall.Xutimensat
/* errno_t utimensat(fd_t dirfd,
 *                   char const *filename,
 *                   [2-3]struct __timespec32 const *times,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xutimensat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_utimensat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutimensat)

.section .text.crt.syscall.Xepoll_pwait
/* errno_t epoll_pwait(fd_t epfd,
 *                     struct epoll_event *events,
 *                     syscall_ulong_t maxevents,
 *                     syscall_slong_t timeout,
 *                     struct __sigset_struct const *ss) */
INTERN_FUNCTION(libc_sys_Xepoll_pwait)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_epoll_pwait, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_pwait)

.section .text.crt.syscall.Xsignalfd
/* errno_t signalfd(fd_t fd,
 *                  struct __sigset_struct const *sigmask,
 *                  size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xsignalfd)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_signalfd, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsignalfd)

/* Return file descriptor for new interval timer source */
.section .text.crt.syscall.Xtimerfd_create
/* fd_t timerfd_create(clockid_t clock_id,
 *                     syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtimerfd_create)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timerfd_create, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_create)

.section .text.crt.syscall.Xeventfd
/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_Xeventfd)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_eventfd, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xeventfd)

.section .text.crt.syscall.Xfallocate
/* errno_t fallocate(fd_t fd,
 *                   syscall_ulong_t mode,
 *                   uint32_t offset,
 *                   uint32_t length) */
INTERN_FUNCTION(libc_sys_Xfallocate)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fallocate, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.crt.syscall.Xtimerfd_settime
/* errno_t timerfd_settime(fd_t ufd,
 *                         syscall_ulong_t flags,
 *                         struct __itimerspec32 const *utmr,
 *                         struct __itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_settime)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_timerfd_settime, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_settime)

/* Return the next expiration time of UFD */
.section .text.crt.syscall.Xtimerfd_gettime
/* errno_t timerfd_gettime(fd_t ufd,
 *                         struct __itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_timerfd_gettime, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_gettime)

.section .text.crt.syscall.Xaccept4
/* fd_t accept4(fd_t sockfd,
 *              struct sockaddr *addr,
 *              socklen_t *addr_len,
 *              syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xaccept4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_accept4, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xaccept4)

.section .text.crt.syscall.Xsignalfd4
/* errno_t signalfd4(fd_t fd,
 *                   struct __sigset_struct const *sigmask,
 *                   size_t sigsetsize,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsignalfd4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_signalfd4, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsignalfd4)

.section .text.crt.syscall.Xeventfd2
/* fd_t eventfd2(syscall_ulong_t initval,
 *               syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xeventfd2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_eventfd2, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xeventfd2)

.section .text.crt.syscall.Xepoll_create1
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xepoll_create1)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_epoll_create1, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
.section .text.crt.syscall.Xdup3
/* fd_t dup3(fd_t oldfd,
 *           fd_t newfd,
 *           oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xdup3)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_dup3, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup3)

.section .text.crt.syscall.Xpipe2
/* errno_t pipe2([2]fd_t *pipedes,
 *               oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xpipe2)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_pipe2, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpipe2)

.section .text.crt.syscall.Xpreadv
/* ssize_t preadv(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count,
 *                uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpreadv)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_preadv, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpreadv)

.section .text.crt.syscall.Xpwritev
/* ssize_t pwritev(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwritev)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_pwritev, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwritev)

/* @param: signo: One of `SIG*' */
.section .text.crt.syscall.Xrt_tgsigqueueinfo
/* errno_t rt_tgsigqueueinfo(pid_t tgid,
 *                           pid_t tid,
 *                           syscall_ulong_t signo,
 *                           struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_tgsigqueueinfo)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rt_tgsigqueueinfo, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_tgsigqueueinfo)

.section .text.crt.syscall.Xrecvmmsg
/* ssize_t recvmmsg(fd_t sockfd,
 *                  struct mmsghdr *vmessages,
 *                  size_t vlen,
 *                  syscall_ulong_t flags,
 *                  struct __timespec32 *tmo) */
INTERN_FUNCTION(libc_sys_Xrecvmmsg)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_recvmmsg, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvmmsg)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
.section .text.crt.syscall.Xprlimit64
/* errno_t prlimit64(pid_t pid,
 *                   syscall_ulong_t resource,
 *                   struct rlimit64 const *new_limit,
 *                   struct rlimit64 *old_limit) */
INTERN_FUNCTION(libc_sys_Xprlimit64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_prlimit64, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprlimit64)

.section .text.crt.syscall.Xname_to_handle_at
/* errno_t name_to_handle_at(fd_t dirfd,
 *                           char const *name,
 *                           struct file_handle *handle,
 *                           int32_t *mnt_id,
 *                           syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xname_to_handle_at)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_name_to_handle_at, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xname_to_handle_at)

.section .text.crt.syscall.Xopen_by_handle_at
/* fd_t open_by_handle_at(fd_t mountdirfd,
 *                        struct file_handle *handle,
 *                        syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xopen_by_handle_at)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_open_by_handle_at, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopen_by_handle_at)

.section .text.crt.syscall.Xsyncfs
/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xsyncfs)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_syncfs, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsyncfs)

.section .text.crt.syscall.Xsendmmsg
/* ssize_t sendmmsg(fd_t sockfd,
 *                  struct mmsghdr *vmessages,
 *                  size_t vlen,
 *                  syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsendmmsg)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_sendmmsg, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendmmsg)

.section .text.crt.syscall.Xsetns
/* errno_t setns(fd_t fd,
 *               syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_Xsetns)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_setns, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetns)

.section .text.crt.syscall.Xgetcpu
/* errno_t getcpu(uint32_t *cpu,
 *                uint32_t *node,
 *                struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_Xgetcpu)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_getcpu, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetcpu)

.section .text.crt.syscall.Xprocess_vm_readv
/* ssize_t process_vm_readv(pid_t pid,
 *                          struct iovec const *lvec,
 *                          size_t liovcnt,
 *                          struct iovec const *rvec,
 *                          size_t riovcnt,
 *                          syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_readv)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_process_vm_readv, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprocess_vm_readv)

.section .text.crt.syscall.Xprocess_vm_writev
/* ssize_t process_vm_writev(pid_t pid,
 *                           struct iovec const *lvec,
 *                           size_t liovcnt,
 *                           struct iovec const *rvec,
 *                           size_t riovcnt,
 *                           syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_writev)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_process_vm_writev, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprocess_vm_writev)

.section .text.crt.syscall.Xkcmp
/* syscall_slong_t kcmp(pid_t pid1,
 *                      pid_t pid2,
 *                      syscall_ulong_t type,
 *                      syscall_ulong_t idx1,
 *                      syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_Xkcmp)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_kcmp, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkcmp)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
.section .text.crt.syscall.Xrenameat2
/* errno_t renameat2(fd_t olddirfd,
 *                   char const *oldpath,
 *                   fd_t newdirfd,
 *                   char const *newpath,
 *                   syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xrenameat2)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_renameat2, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrenameat2)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.Xexecveat
/* errno_t execveat(fd_t dirfd,
 *                  char const *pathname,
 *                  char const *const *argv,
 *                  char const *const *envp,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xexecveat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_execveat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexecveat)

.section .text.crt.syscall.Xreadf
/* ssize_t readf(fd_t fd,
 *               void *buf,
 *               size_t bufsize,
 *               iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadf)

.section .text.crt.syscall.Xwritef
/* ssize_t writef(fd_t fd,
 *                void const *buf,
 *                size_t bufsize,
 *                iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritef)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_writef, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritef)

.section .text.crt.syscall.Xhop
/* syscall_slong_t hop(fd_t fd,
 *                     syscall_ulong_t command,
 *                     void *arg) */
INTERN_FUNCTION(libc_sys_Xhop)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_hop, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xhop)

.section .text.crt.syscall.Xhopf
/* syscall_slong_t hopf(fd_t fd,
 *                      syscall_ulong_t command,
 *                      iomode_t mode,
 *                      void *arg) */
INTERN_FUNCTION(libc_sys_Xhopf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_hopf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xhopf)

.section .text.crt.syscall.Xkstat
/* errno_t kstat(char const *filename,
 *               struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kstat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkstat)

.section .text.crt.syscall.Xkfstat
/* errno_t kfstat(fd_t fd,
 *                struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkfstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_kfstat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkfstat)

.section .text.crt.syscall.Xklstat
/* errno_t klstat(char const *filename,
 *                struct stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xklstat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_klstat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xklstat)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
.section .text.crt.syscall.Xdetach
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xdetach)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_detach, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdetach)

/* Returns a bitset of all of the currently mounted dos-drives */
.section .text.crt.syscall.Xgetdrives
/* syscall_slong_t getdrives(void); */
INTERN_FUNCTION(libc_sys_Xgetdrives)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_getdrives, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.Xfrealpath4
/* ssize_t frealpath4(fd_t fd,
 *                    char *buf,
 *                    size_t buflen,
 *                    atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpath4)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_frealpath4, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.Xfrealpathat
/* ssize_t frealpathat(fd_t dirfd,
 *                     char const *filename,
 *                     char *buf,
 *                     size_t buflen,
 *                     atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpathat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_frealpathat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text.crt.syscall.Xrpc_schedule
/* syscall_slong_t rpc_schedule(pid_t target,
 *                              syscall_ulong_t flags,
 *                              uint8_t const *program,
 *                              void **arguments) */
INTERN_FUNCTION(libc_sys_Xrpc_schedule)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_rpc_schedule, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrpc_schedule)

.section .text.crt.syscall.Xsysctl
/* syscall_slong_t sysctl(syscall_ulong_t command,
 *                        void *arg) */
INTERN_FUNCTION(libc_sys_Xsysctl)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_sysctl, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
.section .text.crt.syscall.Xopenpty
/* errno_t openpty(fd_t *amaster,
 *                 fd_t *aslave,
 *                 char *name,
 *                 struct termios const *termp,
 *                 struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_Xopenpty)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_openpty, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopenpty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
.section .text.crt.syscall.Xset_exception_handler
/* errno_t set_exception_handler(syscall_ulong_t mode,
 *                               except_handler_t handler,
 *                               void *handler_sp) */
INTERN_FUNCTION(libc_sys_Xset_exception_handler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_set_exception_handler, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
.section .text.crt.syscall.Xget_exception_handler
/* errno_t get_exception_handler(syscall_ulong_t *pmode,
 *                               except_handler_t *phandler,
 *                               void **phandler_sp) */
INTERN_FUNCTION(libc_sys_Xget_exception_handler)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_get_exception_handler, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_exception_handler)

.section .text.crt.syscall.Xioctlf
/* syscall_slong_t ioctlf(fd_t fd,
 *                        syscall_ulong_t command,
 *                        iomode_t mode,
 *                        void *arg) */
INTERN_FUNCTION(libc_sys_Xioctlf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_ioctlf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioctlf)

.section .text.crt.syscall.Xpread64f
/* ssize_t pread64f(fd_t fd,
 *                  void *buf,
 *                  size_t bufsize,
 *                  uint64_t offset,
 *                  iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpread64f)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pread64f, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpread64f)

.section .text.crt.syscall.Xpwrite64f
/* ssize_t pwrite64f(fd_t fd,
 *                   void const *buf,
 *                   size_t bufsize,
 *                   uint64_t offset,
 *                   iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwrite64f)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pwrite64f, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwrite64f)

.section .text.crt.syscall.Xreadvf
/* ssize_t readvf(fd_t fd,
 *                struct iovec const *iovec,
 *                size_t count,
 *                iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadvf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_readvf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadvf)

.section .text.crt.syscall.Xwritevf
/* ssize_t writevf(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritevf)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_writevf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritevf)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
.section .text.crt.syscall.Xset_library_listdef
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
INTERN_FUNCTION(libc_sys_Xset_library_listdef)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_set_library_listdef, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
.section .text.crt.syscall.Xdebugtrap
/* errno_t debugtrap(struct ucpustate const *state,
 *                   struct debugtrap_reason const *reason) */
INTERN_FUNCTION(libc_sys_Xdebugtrap)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_debugtrap, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdebugtrap)

.section .text.crt.syscall.Xselect64
/* ssize_t select64(size_t nfds,
 *                  struct __fd_set_struct *readfds,
 *                  struct __fd_set_struct *writefds,
 *                  struct __fd_set_struct *exceptfds,
 *                  struct __timeval64 *timeout) */
INTERN_FUNCTION(libc_sys_Xselect64)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_select64, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xselect64)

.section .text.crt.syscall.Xrpc_service
/* syscall_slong_t rpc_service(void); */
INTERN_FUNCTION(libc_sys_Xrpc_service)
	/* Argument count: 0 */
	.cfi_startproc
	movq   $SYS_rpc_service, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrpc_service)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
.section .text.crt.syscall.Xlfutex
/* syscall_slong_t lfutex(uintptr_t *uaddr,
 *                        syscall_ulong_t futex_op,
 *                        uintptr_t val,
 *                        struct __timespec64 const *timeout,
 *                        uintptr_t val2) */
INTERN_FUNCTION(libc_sys_Xlfutex)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lfutex, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.crt.syscall.Xlfutexexpr
/* errno_t lfutexexpr(void *base,
 *                    size_t exprc,
 *                    struct lfutexexpr const *exprv,
 *                    struct __timespec64 const *timeout,
 *                    syscall_ulong_t timeout_flags) */
INTERN_FUNCTION(libc_sys_Xlfutexexpr)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_lfutexexpr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.crt.syscall.Xlfutexlockexpr
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr,
 *                        void *base,
 *                        size_t exprc,
 *                        struct lfutexexpr const *exprv,
 *                        struct __timespec64 const *timeout,
 *                        syscall_ulong_t timeout_flags) */
INTERN_FUNCTION(libc_sys_Xlfutexlockexpr)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_lfutexlockexpr, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
.section .text.crt.syscall.Xmktty
/* fd_t mktty(fd_t keyboard,
 *            fd_t display,
 *            char const *name,
 *            syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_Xmktty)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_mktty, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
.section .text.crt.syscall.Xraiseat
/* errno_t raiseat(struct ucpustate const *state,
 *                 struct __siginfo_struct const *si) */
INTERN_FUNCTION(libc_sys_Xraiseat)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_raiseat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xraiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == UCPUSTATE_PC(*curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
.section .text.crt.syscall.Xcoredump
/* errno_t coredump(struct ucpustate const *curr_state,
 *                  struct ucpustate const *orig_state,
 *                  void const *const *traceback_vector,
 *                  size_t traceback_length,
 *                  struct exception_data const *exception,
 *                  syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_Xcoredump)
	/* Argument count: 6 */
	.cfi_startproc
	movq   $SYS_coredump, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcoredump)

.section .text.crt.syscall.Xgetitimer64
/* errno_t getitimer64(syscall_ulong_t which,
 *                     struct __itimerval64 *curr_value) */
INTERN_FUNCTION(libc_sys_Xgetitimer64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_getitimer64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetitimer64)

.section .text.crt.syscall.Xsetitimer64
/* errno_t setitimer64(syscall_ulong_t which,
 *                     struct __itimerval64 const *newval,
 *                     struct __itimerval64 *oldval) */
INTERN_FUNCTION(libc_sys_Xsetitimer64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_setitimer64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetitimer64)

.section .text.crt.syscall.Xkreaddir
/* ssize_t kreaddir(fd_t fd,
 *                  struct dirent *buf,
 *                  size_t bufsize,
 *                  syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_Xkreaddir)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_kreaddir, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkreaddir)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.Xfchdirat
/* errno_t fchdirat(fd_t dirfd,
 *                  char const *path,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchdirat)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_fchdirat, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchdirat)

.section .text.crt.syscall.Xfsmode
/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_Xfsmode)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_fsmode, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsmode)

.section .text.crt.syscall.Xgettimeofday64
/* errno_t gettimeofday64(struct __timeval64 *tv,
 *                        struct timezone *tz) */
INTERN_FUNCTION(libc_sys_Xgettimeofday64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_gettimeofday64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgettimeofday64)

.section .text.crt.syscall.Xutime64
/* errno_t utime64(char const *filename,
 *                 struct utimbuf64 const *times) */
INTERN_FUNCTION(libc_sys_Xutime64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utime64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutime64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
.section .text.crt.syscall.Xmaplibrary
/* void *maplibrary(void *addr,
 *                  syscall_ulong_t flags,
 *                  fd_t fd,
 *                  void *hdrv,
 *                  size_t hdrc) */
INTERN_FUNCTION(libc_sys_Xmaplibrary)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_maplibrary, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmaplibrary)

.section .text.crt.syscall.Xsettimeofday64
/* errno_t settimeofday64(struct __timeval64 const *tv,
 *                        struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_Xsettimeofday64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_settimeofday64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsettimeofday64)

.section .text.crt.syscall.Xtime64
/* time64_t time64(time64_t *timer) */
INTERN_FUNCTION(libc_sys_Xtime64)
	/* Argument count: 1 */
	.cfi_startproc
	movq   $SYS_time64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtime64)

.section .text.crt.syscall.Xkreaddirf
/* ssize_t kreaddirf(fd_t fd,
 *                   struct dirent *buf,
 *                   size_t bufsize,
 *                   syscall_ulong_t mode,
 *                   iomode_t iomode) */
INTERN_FUNCTION(libc_sys_Xkreaddirf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_kreaddirf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkreaddirf)

.section .text.crt.syscall.Xutimes64
/* errno_t utimes64(char const *filename,
 *                  [2]struct __timeval64 const *times) */
INTERN_FUNCTION(libc_sys_Xutimes64)
	/* Argument count: 2 */
	.cfi_startproc
	movq   $SYS_utimes64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutimes64)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.Xfmkdirat
/* errno_t fmkdirat(fd_t dirfd,
 *                  char const *pathname,
 *                  mode_t mode,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmkdirat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fmkdirat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfmkdirat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.Xfmknodat
/* errno_t fmknodat(fd_t dirfd,
 *                  char const *nodename,
 *                  mode_t mode,
 *                  dev_t dev,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmknodat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_fmknodat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.crt.syscall.Xfutimesat64
/* errno_t futimesat64(fd_t dirfd,
 *                     const char *filename,
 *                     [2-3]struct __timeval64 const *times) */
INTERN_FUNCTION(libc_sys_Xfutimesat64)
	/* Argument count: 3 */
	.cfi_startproc
	movq   $SYS_futimesat64, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfutimesat64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.crt.syscall.Xkfstatat
/* errno_t kfstatat(fd_t dirfd,
 *                  char const *filename,
 *                  struct stat *statbuf,
 *                  atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xkfstatat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_kfstatat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkfstatat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.Xfrenameat
/* errno_t frenameat(fd_t oldfd,
 *                   char const *oldname,
 *                   fd_t newfd,
 *                   char const *newname_or_path,
 *                   atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrenameat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_frenameat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrenameat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.crt.syscall.Xfsymlinkat
/* errno_t fsymlinkat(char const *link_text,
 *                    fd_t tofd,
 *                    char const *target_path,
 *                    atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfsymlinkat)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fsymlinkat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsymlinkat)

/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.crt.syscall.Xfreadlinkat
/* ssize_t freadlinkat(fd_t dirfd,
 *                     char const *path,
 *                     char *buf,
 *                     size_t buflen,
 *                     atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfreadlinkat)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_freadlinkat, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfreadlinkat)

.section .text.crt.syscall.Xfallocate64
/* errno_t fallocate64(fd_t fd,
 *                     syscall_ulong_t mode,
 *                     uint64_t offset,
 *                     uint64_t length) */
INTERN_FUNCTION(libc_sys_Xfallocate64)
	/* Argument count: 4 */
	.cfi_startproc
	movq   $SYS_fallocate64, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfallocate64)

.section .text.crt.syscall.Xpreadvf
/* ssize_t preadvf(fd_t fd,
 *                 struct iovec const *iovec,
 *                 size_t count,
 *                 uint64_t offset,
 *                 iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpreadvf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_preadvf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpreadvf)

.section .text.crt.syscall.Xpwritevf
/* ssize_t pwritevf(fd_t fd,
 *                  struct iovec const *iovec,
 *                  size_t count,
 *                  uint64_t offset,
 *                  iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwritevf)
	/* Argument count: 5 */
	.cfi_startproc
	movq   $SYS_pwritevf, %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwritevf)

#endif /* !CONFIG_SYSCALL_EXCLUDE_WITHEXCEPT */






#ifndef CONFIG_SYSCALL_NO_EXPORTS
#ifndef CONFIG_SYSCALL_EXCLUDE_WITHOUTEXCEPT
DEFINE_PUBLIC_WEAK_ALIAS(sys_read, libc_sys_read)
DEFINE_PUBLIC_WEAK_ALIAS(sys_write, libc_sys_write)
DEFINE_PUBLIC_WEAK_ALIAS(sys_open, libc_sys_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_close, libc_sys_close)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_stat64, libc_sys_linux_stat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_fstat64, libc_sys_linux_fstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_lstat64, libc_sys_linux_lstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_poll, libc_sys_poll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lseek64, libc_sys_lseek64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mmap, libc_sys_mmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mprotect, libc_sys_mprotect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munmap, libc_sys_munmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_brk, libc_sys_brk)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigaction, libc_sys_rt_sigaction)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigprocmask, libc_sys_rt_sigprocmask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigreturn, libc_sys_rt_sigreturn)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioctl, libc_sys_ioctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pread64, libc_sys_pread64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwrite64, libc_sys_pwrite64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readv, libc_sys_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writev, libc_sys_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_access, libc_sys_access)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pipe, libc_sys_pipe)
DEFINE_PUBLIC_WEAK_ALIAS(sys_select, libc_sys_select)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_yield, libc_sys_sched_yield)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mremap, libc_sys_mremap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msync, libc_sys_msync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mincore, libc_sys_mincore)
DEFINE_PUBLIC_WEAK_ALIAS(sys_madvise, libc_sys_madvise)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup, libc_sys_dup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup2, libc_sys_dup2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pause, libc_sys_pause)
DEFINE_PUBLIC_WEAK_ALIAS(sys_nanosleep, libc_sys_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getitimer, libc_sys_getitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_alarm, libc_sys_alarm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setitimer, libc_sys_setitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpid, libc_sys_getpid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendfile, libc_sys_sendfile)
DEFINE_PUBLIC_WEAK_ALIAS(sys_socket, libc_sys_socket)
DEFINE_PUBLIC_WEAK_ALIAS(sys_connect, libc_sys_connect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendto, libc_sys_sendto)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvfrom, libc_sys_recvfrom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendmsg, libc_sys_sendmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvmsg, libc_sys_recvmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shutdown, libc_sys_shutdown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_bind, libc_sys_bind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_listen, libc_sys_listen)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsockname, libc_sys_getsockname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpeername, libc_sys_getpeername)
DEFINE_PUBLIC_WEAK_ALIAS(sys_socketpair, libc_sys_socketpair)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setsockopt, libc_sys_setsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsockopt, libc_sys_getsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clone, libc_sys_clone)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fork, libc_sys_fork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vfork, libc_sys_vfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_execve, libc_sys_execve)
DEFINE_PUBLIC_WEAK_ALIAS(sys_exit, libc_sys_exit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_wait4, libc_sys_wait4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kill, libc_sys_kill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_uname, libc_sys_uname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fcntl, libc_sys_fcntl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_flock, libc_sys_flock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsync, libc_sys_fsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fdatasync, libc_sys_fdatasync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_truncate, libc_sys_truncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ftruncate, libc_sys_ftruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdents, libc_sys_getdents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getcwd, libc_sys_getcwd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chdir, libc_sys_chdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchdir, libc_sys_fchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rename, libc_sys_rename)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mkdir, libc_sys_mkdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rmdir, libc_sys_rmdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_creat, libc_sys_creat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_link, libc_sys_link)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unlink, libc_sys_unlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_symlink, libc_sys_symlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readlink, libc_sys_readlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chmod, libc_sys_chmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchmod, libc_sys_fchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chown, libc_sys_chown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchown, libc_sys_fchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lchown, libc_sys_lchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_umask, libc_sys_umask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_gettimeofday, libc_sys_gettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getrlimit, libc_sys_getrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getrusage, libc_sys_getrusage)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sysinfo, libc_sys_sysinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_times, libc_sys_times)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ptrace, libc_sys_ptrace)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getuid32, libc_sys_getuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_syslog, libc_sys_syslog)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getgid32, libc_sys_getgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setuid32, libc_sys_setuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setgid32, libc_sys_setgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_geteuid32, libc_sys_geteuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getegid32, libc_sys_getegid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setpgid, libc_sys_setpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getppid, libc_sys_getppid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpgrp, libc_sys_getpgrp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setsid, libc_sys_setsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setreuid32, libc_sys_setreuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setregid32, libc_sys_setregid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getgroups32, libc_sys_getgroups32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setgroups32, libc_sys_setgroups32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setresuid32, libc_sys_setresuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getresuid32, libc_sys_getresuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setresgid32, libc_sys_setresgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getresgid32, libc_sys_getresgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpgid, libc_sys_getpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setfsuid32, libc_sys_setfsuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setfsgid32, libc_sys_setfsgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsid, libc_sys_getsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigpending, libc_sys_rt_sigpending)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigtimedwait, libc_sys_rt_sigtimedwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigqueueinfo, libc_sys_rt_sigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigsuspend, libc_sys_rt_sigsuspend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sigaltstack, libc_sys_sigaltstack)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utime, libc_sys_utime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mknod, libc_sys_mknod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ustat, libc_sys_ustat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_statfs, libc_sys_statfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fstatfs, libc_sys_fstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpriority, libc_sys_getpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setpriority, libc_sys_setpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setparam, libc_sys_sched_setparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getparam, libc_sys_sched_getparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setscheduler, libc_sys_sched_setscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getscheduler, libc_sys_sched_getscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_get_priority_max, libc_sys_sched_get_priority_max)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_get_priority_min, libc_sys_sched_get_priority_min)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_rr_get_interval, libc_sys_sched_rr_get_interval)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mlock, libc_sys_mlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munlock, libc_sys_munlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mlockall, libc_sys_mlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munlockall, libc_sys_munlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vhangup, libc_sys_vhangup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_modify_ldt, libc_sys_modify_ldt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setrlimit, libc_sys_setrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chroot, libc_sys_chroot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sync, libc_sys_sync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_acct, libc_sys_acct)
DEFINE_PUBLIC_WEAK_ALIAS(sys_settimeofday, libc_sys_settimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mount, libc_sys_mount)
DEFINE_PUBLIC_WEAK_ALIAS(sys_umount2, libc_sys_umount2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_swapon, libc_sys_swapon)
DEFINE_PUBLIC_WEAK_ALIAS(sys_swapoff, libc_sys_swapoff)
DEFINE_PUBLIC_WEAK_ALIAS(sys_reboot, libc_sys_reboot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sethostname, libc_sys_sethostname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setdomainname, libc_sys_setdomainname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_iopl, libc_sys_iopl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioperm, libc_sys_ioperm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_gettid, libc_sys_gettid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readahead, libc_sys_readahead)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setxattr, libc_sys_setxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lsetxattr, libc_sys_lsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsetxattr, libc_sys_fsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getxattr, libc_sys_getxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lgetxattr, libc_sys_lgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fgetxattr, libc_sys_fgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_listxattr, libc_sys_listxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_llistxattr, libc_sys_llistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_flistxattr, libc_sys_flistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_removexattr, libc_sys_removexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lremovexattr, libc_sys_lremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fremovexattr, libc_sys_fremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tkill, libc_sys_tkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_time, libc_sys_time)
DEFINE_PUBLIC_WEAK_ALIAS(sys_futex, libc_sys_futex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setaffinity, libc_sys_sched_setaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getaffinity, libc_sys_sched_getaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_create, libc_sys_epoll_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_ctl_old, libc_sys_epoll_ctl_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_wait_old, libc_sys_epoll_wait_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_remap_file_pages, libc_sys_remap_file_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdents64, libc_sys_getdents64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_tid_address, libc_sys_set_tid_address)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_create, libc_sys_timer_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_settime, libc_sys_timer_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_gettime, libc_sys_timer_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_getoverrun, libc_sys_timer_getoverrun)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_delete, libc_sys_timer_delete)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_settime, libc_sys_clock_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_gettime, libc_sys_clock_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_getres, libc_sys_clock_getres)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_nanosleep, libc_sys_clock_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_exit_group, libc_sys_exit_group)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_wait, libc_sys_epoll_wait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_ctl, libc_sys_epoll_ctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tgkill, libc_sys_tgkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utimes, libc_sys_utimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_waitid, libc_sys_waitid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioprio_set, libc_sys_ioprio_set)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioprio_get, libc_sys_ioprio_get)
DEFINE_PUBLIC_WEAK_ALIAS(sys_openat, libc_sys_openat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mkdirat, libc_sys_mkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mknodat, libc_sys_mknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchownat, libc_sys_fchownat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_futimesat, libc_sys_futimesat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fstatat, libc_sys_fstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unlinkat, libc_sys_unlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_renameat, libc_sys_renameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linkat, libc_sys_linkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_symlinkat, libc_sys_symlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readlinkat, libc_sys_readlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchmodat, libc_sys_fchmodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_faccessat, libc_sys_faccessat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pselect6, libc_sys_pselect6)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ppoll, libc_sys_ppoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unshare, libc_sys_unshare)
DEFINE_PUBLIC_WEAK_ALIAS(sys_splice, libc_sys_splice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tee, libc_sys_tee)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sync_file_range, libc_sys_sync_file_range)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vmsplice, libc_sys_vmsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utimensat, libc_sys_utimensat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_pwait, libc_sys_epoll_pwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_signalfd, libc_sys_signalfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_create, libc_sys_timerfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_eventfd, libc_sys_eventfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fallocate, libc_sys_fallocate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_settime, libc_sys_timerfd_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_gettime, libc_sys_timerfd_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_accept4, libc_sys_accept4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_signalfd4, libc_sys_signalfd4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_eventfd2, libc_sys_eventfd2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_create1, libc_sys_epoll_create1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup3, libc_sys_dup3)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pipe2, libc_sys_pipe2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_preadv, libc_sys_preadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwritev, libc_sys_pwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_tgsigqueueinfo, libc_sys_rt_tgsigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvmmsg, libc_sys_recvmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_prlimit64, libc_sys_prlimit64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_name_to_handle_at, libc_sys_name_to_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_open_by_handle_at, libc_sys_open_by_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_syncfs, libc_sys_syncfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendmmsg, libc_sys_sendmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setns, libc_sys_setns)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getcpu, libc_sys_getcpu)
DEFINE_PUBLIC_WEAK_ALIAS(sys_process_vm_readv, libc_sys_process_vm_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_process_vm_writev, libc_sys_process_vm_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kcmp, libc_sys_kcmp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_renameat2, libc_sys_renameat2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_execveat, libc_sys_execveat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readf, libc_sys_readf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writef, libc_sys_writef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_hop, libc_sys_hop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_hopf, libc_sys_hopf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kstat, libc_sys_kstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kfstat, libc_sys_kfstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_klstat, libc_sys_klstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_detach, libc_sys_detach)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdrives, libc_sys_getdrives)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frealpath4, libc_sys_frealpath4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frealpathat, libc_sys_frealpathat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rpc_schedule, libc_sys_rpc_schedule)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sysctl, libc_sys_sysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_openpty, libc_sys_openpty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_exception_handler, libc_sys_set_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_exception_handler, libc_sys_get_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioctlf, libc_sys_ioctlf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pread64f, libc_sys_pread64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwrite64f, libc_sys_pwrite64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readvf, libc_sys_readvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writevf, libc_sys_writevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_library_listdef, libc_sys_set_library_listdef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_debugtrap, libc_sys_debugtrap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_select64, libc_sys_select64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rpc_service, libc_sys_rpc_service)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutex, libc_sys_lfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutexexpr, libc_sys_lfutexexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutexlockexpr, libc_sys_lfutexlockexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mktty, libc_sys_mktty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_raiseat, libc_sys_raiseat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_coredump, libc_sys_coredump)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getitimer64, libc_sys_getitimer64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setitimer64, libc_sys_setitimer64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kreaddir, libc_sys_kreaddir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchdirat, libc_sys_fchdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsmode, libc_sys_fsmode)
DEFINE_PUBLIC_WEAK_ALIAS(sys_gettimeofday64, libc_sys_gettimeofday64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utime64, libc_sys_utime64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_maplibrary, libc_sys_maplibrary)
DEFINE_PUBLIC_WEAK_ALIAS(sys_settimeofday64, libc_sys_settimeofday64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_time64, libc_sys_time64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kreaddirf, libc_sys_kreaddirf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utimes64, libc_sys_utimes64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fmkdirat, libc_sys_fmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fmknodat, libc_sys_fmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_futimesat64, libc_sys_futimesat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kfstatat, libc_sys_kfstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frenameat, libc_sys_frenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsymlinkat, libc_sys_fsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_freadlinkat, libc_sys_freadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fallocate64, libc_sys_fallocate64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_preadvf, libc_sys_preadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwritevf, libc_sys_pwritevf)
#endif /* !CONFIG_SYSCALL_EXCLUDE_WITHOUTEXCEPT */
#ifndef CONFIG_SYSCALL_EXCLUDE_WITHEXCEPT
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xread, libc_sys_Xread)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwrite, libc_sys_Xwrite)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopen, libc_sys_Xopen)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclose, libc_sys_Xclose)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_stat64, libc_sys_Xlinux_stat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_fstat64, libc_sys_Xlinux_fstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_lstat64, libc_sys_Xlinux_lstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpoll, libc_sys_Xpoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlseek64, libc_sys_Xlseek64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmmap, libc_sys_Xmmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmprotect, libc_sys_Xmprotect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunmap, libc_sys_Xmunmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xbrk, libc_sys_Xbrk)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigaction, libc_sys_Xrt_sigaction)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigprocmask, libc_sys_Xrt_sigprocmask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigreturn, libc_sys_Xrt_sigreturn)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioctl, libc_sys_Xioctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpread64, libc_sys_Xpread64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwrite64, libc_sys_Xpwrite64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadv, libc_sys_Xreadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritev, libc_sys_Xwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xaccess, libc_sys_Xaccess)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpipe, libc_sys_Xpipe)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xselect, libc_sys_Xselect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_yield, libc_sys_Xsched_yield)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmremap, libc_sys_Xmremap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsync, libc_sys_Xmsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmincore, libc_sys_Xmincore)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmadvise, libc_sys_Xmadvise)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup, libc_sys_Xdup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup2, libc_sys_Xdup2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpause, libc_sys_Xpause)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xnanosleep, libc_sys_Xnanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetitimer, libc_sys_Xgetitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xalarm, libc_sys_Xalarm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetitimer, libc_sys_Xsetitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpid, libc_sys_Xgetpid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendfile, libc_sys_Xsendfile)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsocket, libc_sys_Xsocket)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xconnect, libc_sys_Xconnect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendto, libc_sys_Xsendto)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvfrom, libc_sys_Xrecvfrom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendmsg, libc_sys_Xsendmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvmsg, libc_sys_Xrecvmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshutdown, libc_sys_Xshutdown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xbind, libc_sys_Xbind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlisten, libc_sys_Xlisten)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsockname, libc_sys_Xgetsockname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpeername, libc_sys_Xgetpeername)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsocketpair, libc_sys_Xsocketpair)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetsockopt, libc_sys_Xsetsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsockopt, libc_sys_Xgetsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclone, libc_sys_Xclone)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfork, libc_sys_Xfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvfork, libc_sys_Xvfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexecve, libc_sys_Xexecve)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexit, libc_sys_Xexit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwait4, libc_sys_Xwait4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkill, libc_sys_Xkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xuname, libc_sys_Xuname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfcntl, libc_sys_Xfcntl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xflock, libc_sys_Xflock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsync, libc_sys_Xfsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfdatasync, libc_sys_Xfdatasync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtruncate, libc_sys_Xtruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xftruncate, libc_sys_Xftruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdents, libc_sys_Xgetdents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetcwd, libc_sys_Xgetcwd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchdir, libc_sys_Xchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchdir, libc_sys_Xfchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrename, libc_sys_Xrename)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmkdir, libc_sys_Xmkdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrmdir, libc_sys_Xrmdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcreat, libc_sys_Xcreat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlink, libc_sys_Xlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunlink, libc_sys_Xunlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsymlink, libc_sys_Xsymlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadlink, libc_sys_Xreadlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchmod, libc_sys_Xchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchmod, libc_sys_Xfchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchown, libc_sys_Xchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchown, libc_sys_Xfchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlchown, libc_sys_Xlchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xumask, libc_sys_Xumask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgettimeofday, libc_sys_Xgettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetrlimit, libc_sys_Xgetrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetrusage, libc_sys_Xgetrusage)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsysinfo, libc_sys_Xsysinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimes, libc_sys_Xtimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xptrace, libc_sys_Xptrace)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetuid32, libc_sys_Xgetuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsyslog, libc_sys_Xsyslog)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetgid32, libc_sys_Xgetgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetuid32, libc_sys_Xsetuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetgid32, libc_sys_Xsetgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgeteuid32, libc_sys_Xgeteuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetegid32, libc_sys_Xgetegid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetpgid, libc_sys_Xsetpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetppid, libc_sys_Xgetppid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpgrp, libc_sys_Xgetpgrp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetsid, libc_sys_Xsetsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetreuid32, libc_sys_Xsetreuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetregid32, libc_sys_Xsetregid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetgroups32, libc_sys_Xgetgroups32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetgroups32, libc_sys_Xsetgroups32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetresuid32, libc_sys_Xsetresuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetresuid32, libc_sys_Xgetresuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetresgid32, libc_sys_Xsetresgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetresgid32, libc_sys_Xgetresgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpgid, libc_sys_Xgetpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetfsuid32, libc_sys_Xsetfsuid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetfsgid32, libc_sys_Xsetfsgid32)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsid, libc_sys_Xgetsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigpending, libc_sys_Xrt_sigpending)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigtimedwait, libc_sys_Xrt_sigtimedwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigqueueinfo, libc_sys_Xrt_sigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigsuspend, libc_sys_Xrt_sigsuspend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsigaltstack, libc_sys_Xsigaltstack)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutime, libc_sys_Xutime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmknod, libc_sys_Xmknod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xustat, libc_sys_Xustat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xstatfs, libc_sys_Xstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfstatfs, libc_sys_Xfstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpriority, libc_sys_Xgetpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetpriority, libc_sys_Xsetpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setparam, libc_sys_Xsched_setparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getparam, libc_sys_Xsched_getparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setscheduler, libc_sys_Xsched_setscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getscheduler, libc_sys_Xsched_getscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_get_priority_max, libc_sys_Xsched_get_priority_max)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_get_priority_min, libc_sys_Xsched_get_priority_min)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_rr_get_interval, libc_sys_Xsched_rr_get_interval)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmlock, libc_sys_Xmlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunlock, libc_sys_Xmunlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmlockall, libc_sys_Xmlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunlockall, libc_sys_Xmunlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvhangup, libc_sys_Xvhangup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmodify_ldt, libc_sys_Xmodify_ldt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetrlimit, libc_sys_Xsetrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchroot, libc_sys_Xchroot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsync, libc_sys_Xsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xacct, libc_sys_Xacct)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsettimeofday, libc_sys_Xsettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmount, libc_sys_Xmount)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xumount2, libc_sys_Xumount2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xswapon, libc_sys_Xswapon)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xswapoff, libc_sys_Xswapoff)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreboot, libc_sys_Xreboot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsethostname, libc_sys_Xsethostname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetdomainname, libc_sys_Xsetdomainname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xiopl, libc_sys_Xiopl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioperm, libc_sys_Xioperm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgettid, libc_sys_Xgettid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadahead, libc_sys_Xreadahead)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetxattr, libc_sys_Xsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlsetxattr, libc_sys_Xlsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsetxattr, libc_sys_Xfsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetxattr, libc_sys_Xgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlgetxattr, libc_sys_Xlgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfgetxattr, libc_sys_Xfgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlistxattr, libc_sys_Xlistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xllistxattr, libc_sys_Xllistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xflistxattr, libc_sys_Xflistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xremovexattr, libc_sys_Xremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlremovexattr, libc_sys_Xlremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfremovexattr, libc_sys_Xfremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtkill, libc_sys_Xtkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtime, libc_sys_Xtime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfutex, libc_sys_Xfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setaffinity, libc_sys_Xsched_setaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getaffinity, libc_sys_Xsched_getaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_create, libc_sys_Xepoll_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_ctl_old, libc_sys_Xepoll_ctl_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_wait_old, libc_sys_Xepoll_wait_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xremap_file_pages, libc_sys_Xremap_file_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdents64, libc_sys_Xgetdents64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_tid_address, libc_sys_Xset_tid_address)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_create, libc_sys_Xtimer_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_settime, libc_sys_Xtimer_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_gettime, libc_sys_Xtimer_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_getoverrun, libc_sys_Xtimer_getoverrun)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_delete, libc_sys_Xtimer_delete)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_settime, libc_sys_Xclock_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_gettime, libc_sys_Xclock_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_getres, libc_sys_Xclock_getres)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_nanosleep, libc_sys_Xclock_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexit_group, libc_sys_Xexit_group)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_wait, libc_sys_Xepoll_wait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_ctl, libc_sys_Xepoll_ctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtgkill, libc_sys_Xtgkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutimes, libc_sys_Xutimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwaitid, libc_sys_Xwaitid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioprio_set, libc_sys_Xioprio_set)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioprio_get, libc_sys_Xioprio_get)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopenat, libc_sys_Xopenat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmkdirat, libc_sys_Xmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmknodat, libc_sys_Xmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchownat, libc_sys_Xfchownat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfutimesat, libc_sys_Xfutimesat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfstatat, libc_sys_Xfstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunlinkat, libc_sys_Xunlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrenameat, libc_sys_Xrenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinkat, libc_sys_Xlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsymlinkat, libc_sys_Xsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadlinkat, libc_sys_Xreadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchmodat, libc_sys_Xfchmodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfaccessat, libc_sys_Xfaccessat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpselect6, libc_sys_Xpselect6)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xppoll, libc_sys_Xppoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunshare, libc_sys_Xunshare)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsplice, libc_sys_Xsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtee, libc_sys_Xtee)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsync_file_range, libc_sys_Xsync_file_range)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvmsplice, libc_sys_Xvmsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutimensat, libc_sys_Xutimensat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_pwait, libc_sys_Xepoll_pwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsignalfd, libc_sys_Xsignalfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_create, libc_sys_Xtimerfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xeventfd, libc_sys_Xeventfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfallocate, libc_sys_Xfallocate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_settime, libc_sys_Xtimerfd_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_gettime, libc_sys_Xtimerfd_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xaccept4, libc_sys_Xaccept4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsignalfd4, libc_sys_Xsignalfd4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xeventfd2, libc_sys_Xeventfd2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_create1, libc_sys_Xepoll_create1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup3, libc_sys_Xdup3)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpipe2, libc_sys_Xpipe2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpreadv, libc_sys_Xpreadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwritev, libc_sys_Xpwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_tgsigqueueinfo, libc_sys_Xrt_tgsigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvmmsg, libc_sys_Xrecvmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprlimit64, libc_sys_Xprlimit64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xname_to_handle_at, libc_sys_Xname_to_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopen_by_handle_at, libc_sys_Xopen_by_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsyncfs, libc_sys_Xsyncfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendmmsg, libc_sys_Xsendmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetns, libc_sys_Xsetns)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetcpu, libc_sys_Xgetcpu)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprocess_vm_readv, libc_sys_Xprocess_vm_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprocess_vm_writev, libc_sys_Xprocess_vm_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkcmp, libc_sys_Xkcmp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrenameat2, libc_sys_Xrenameat2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexecveat, libc_sys_Xexecveat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadf, libc_sys_Xreadf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritef, libc_sys_Xwritef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xhop, libc_sys_Xhop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xhopf, libc_sys_Xhopf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkstat, libc_sys_Xkstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkfstat, libc_sys_Xkfstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xklstat, libc_sys_Xklstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdetach, libc_sys_Xdetach)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdrives, libc_sys_Xgetdrives)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrealpath4, libc_sys_Xfrealpath4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrealpathat, libc_sys_Xfrealpathat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrpc_schedule, libc_sys_Xrpc_schedule)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsysctl, libc_sys_Xsysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopenpty, libc_sys_Xopenpty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_exception_handler, libc_sys_Xset_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_exception_handler, libc_sys_Xget_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioctlf, libc_sys_Xioctlf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpread64f, libc_sys_Xpread64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwrite64f, libc_sys_Xpwrite64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadvf, libc_sys_Xreadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritevf, libc_sys_Xwritevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_library_listdef, libc_sys_Xset_library_listdef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdebugtrap, libc_sys_Xdebugtrap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xselect64, libc_sys_Xselect64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrpc_service, libc_sys_Xrpc_service)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutex, libc_sys_Xlfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutexexpr, libc_sys_Xlfutexexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutexlockexpr, libc_sys_Xlfutexlockexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmktty, libc_sys_Xmktty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xraiseat, libc_sys_Xraiseat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcoredump, libc_sys_Xcoredump)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetitimer64, libc_sys_Xgetitimer64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetitimer64, libc_sys_Xsetitimer64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkreaddir, libc_sys_Xkreaddir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchdirat, libc_sys_Xfchdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsmode, libc_sys_Xfsmode)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgettimeofday64, libc_sys_Xgettimeofday64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutime64, libc_sys_Xutime64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmaplibrary, libc_sys_Xmaplibrary)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsettimeofday64, libc_sys_Xsettimeofday64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtime64, libc_sys_Xtime64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkreaddirf, libc_sys_Xkreaddirf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutimes64, libc_sys_Xutimes64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfmkdirat, libc_sys_Xfmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfmknodat, libc_sys_Xfmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfutimesat64, libc_sys_Xfutimesat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkfstatat, libc_sys_Xkfstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrenameat, libc_sys_Xfrenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsymlinkat, libc_sys_Xfsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfreadlinkat, libc_sys_Xfreadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfallocate64, libc_sys_Xfallocate64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpreadvf, libc_sys_Xpreadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwritevf, libc_sys_Xpwritevf)
#endif /* !CONFIG_SYSCALL_EXCLUDE_WITHEXCEPT */
#endif /* !CONFIG_SYSCALL_NO_EXPORTS */

#include "syscalls-ammend.S.inl"

