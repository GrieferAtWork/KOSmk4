/* HASH CRC-32:0x2e8256b1 */
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

/* TODO: x86_64_printLibcSyscallWrapperCommon() */

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.crt.syscall.read
INTERN_FUNCTION(libc_sys_read)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_read)
DEFINE_PUBLIC_WEAK_ALIAS(sys_read, libc_sys_read)

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xread
INTERN_FUNCTION(libc_sys_Xread)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xread)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xread, libc_sys_Xread)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.crt.syscall.write
INTERN_FUNCTION(libc_sys_write)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_write)
DEFINE_PUBLIC_WEAK_ALIAS(sys_write, libc_sys_write)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.crt.syscall.Xwrite
INTERN_FUNCTION(libc_sys_Xwrite)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwrite)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwrite, libc_sys_Xwrite)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.open
INTERN_FUNCTION(libc_sys_open)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_open, libc_sys_open)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.Xopen
INTERN_FUNCTION(libc_sys_Xopen)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xopen)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopen, libc_sys_Xopen)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.crt.syscall.close
INTERN_FUNCTION(libc_sys_close)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_close)
DEFINE_PUBLIC_WEAK_ALIAS(sys_close, libc_sys_close)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.crt.syscall.Xclose
INTERN_FUNCTION(libc_sys_Xclose)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclose)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclose, libc_sys_Xclose)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.linux_stat64
INTERN_FUNCTION(libc_sys_linux_stat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_linux_stat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_stat64, libc_sys_linux_stat64)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.Xlinux_stat64
INTERN_FUNCTION(libc_sys_Xlinux_stat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlinux_stat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_stat64, libc_sys_Xlinux_stat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.linux_fstat64
INTERN_FUNCTION(libc_sys_linux_fstat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_linux_fstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_fstat64, libc_sys_linux_fstat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.Xlinux_fstat64
INTERN_FUNCTION(libc_sys_Xlinux_fstat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlinux_fstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_fstat64, libc_sys_Xlinux_fstat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.linux_lstat64
INTERN_FUNCTION(libc_sys_linux_lstat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_linux_lstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_lstat64, libc_sys_linux_lstat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.crt.syscall.Xlinux_lstat64
INTERN_FUNCTION(libc_sys_Xlinux_lstat64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlinux_lstat64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_lstat64, libc_sys_Xlinux_lstat64)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.crt.syscall.poll
INTERN_FUNCTION(libc_sys_poll)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_poll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_poll, libc_sys_poll)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.crt.syscall.Xpoll
INTERN_FUNCTION(libc_sys_Xpoll)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpoll, libc_sys_Xpoll)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.crt.syscall.lseek64
INTERN_FUNCTION(libc_sys_lseek64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lseek64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lseek64, libc_sys_lseek64)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.crt.syscall.Xlseek64
INTERN_FUNCTION(libc_sys_Xlseek64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlseek64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlseek64, libc_sys_Xlseek64)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.crt.syscall.mmap
INTERN_FUNCTION(libc_sys_mmap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mmap, libc_sys_mmap)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.crt.syscall.Xmmap
INTERN_FUNCTION(libc_sys_Xmmap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmmap, libc_sys_Xmmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.crt.syscall.mprotect
INTERN_FUNCTION(libc_sys_mprotect)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mprotect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mprotect, libc_sys_mprotect)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.crt.syscall.Xmprotect
INTERN_FUNCTION(libc_sys_Xmprotect)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmprotect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmprotect, libc_sys_Xmprotect)

/* errno_t munmap(void *addr, size_t len) */
.section .text.crt.syscall.munmap
INTERN_FUNCTION(libc_sys_munmap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_munmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munmap, libc_sys_munmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.crt.syscall.Xmunmap
INTERN_FUNCTION(libc_sys_Xmunmap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmunmap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunmap, libc_sys_Xmunmap)

/* errno_t brk(void *addr) */
.section .text.crt.syscall.brk
INTERN_FUNCTION(libc_sys_brk)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_brk)
DEFINE_PUBLIC_WEAK_ALIAS(sys_brk, libc_sys_brk)

/* errno_t brk(void *addr) */
.section .text.crt.syscall.Xbrk
INTERN_FUNCTION(libc_sys_Xbrk)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xbrk)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xbrk, libc_sys_Xbrk)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigaction
INTERN_FUNCTION(libc_sys_rt_sigaction)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigaction)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigaction, libc_sys_rt_sigaction)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigaction
INTERN_FUNCTION(libc_sys_Xrt_sigaction)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigaction)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigaction, libc_sys_Xrt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigprocmask
INTERN_FUNCTION(libc_sys_rt_sigprocmask)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigprocmask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigprocmask, libc_sys_rt_sigprocmask)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigprocmask
INTERN_FUNCTION(libc_sys_Xrt_sigprocmask)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigprocmask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigprocmask, libc_sys_Xrt_sigprocmask)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.crt.syscall.rt_sigreturn
INTERN_FUNCTION(libc_sys_rt_sigreturn)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigreturn)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigreturn, libc_sys_rt_sigreturn)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.crt.syscall.ioctl
INTERN_FUNCTION(libc_sys_ioctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ioctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioctl, libc_sys_ioctl)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.crt.syscall.Xioctl
INTERN_FUNCTION(libc_sys_Xioctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xioctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioctl, libc_sys_Xioctl)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.pread64
INTERN_FUNCTION(libc_sys_pread64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pread64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pread64, libc_sys_pread64)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.Xpread64
INTERN_FUNCTION(libc_sys_Xpread64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpread64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpread64, libc_sys_Xpread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.pwrite64
INTERN_FUNCTION(libc_sys_pwrite64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pwrite64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwrite64, libc_sys_pwrite64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.Xpwrite64
INTERN_FUNCTION(libc_sys_Xpwrite64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpwrite64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwrite64, libc_sys_Xpwrite64)

/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.crt.syscall.readv
INTERN_FUNCTION(libc_sys_readv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readv, libc_sys_readv)

/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.crt.syscall.Xreadv
INTERN_FUNCTION(libc_sys_Xreadv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadv, libc_sys_Xreadv)

/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.crt.syscall.writev
INTERN_FUNCTION(libc_sys_writev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writev, libc_sys_writev)

/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.crt.syscall.Xwritev
INTERN_FUNCTION(libc_sys_Xwritev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritev, libc_sys_Xwritev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.crt.syscall.access
INTERN_FUNCTION(libc_sys_access)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_access)
DEFINE_PUBLIC_WEAK_ALIAS(sys_access, libc_sys_access)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.crt.syscall.Xaccess
INTERN_FUNCTION(libc_sys_Xaccess)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xaccess)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xaccess, libc_sys_Xaccess)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.crt.syscall.pipe
INTERN_FUNCTION(libc_sys_pipe)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pipe)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pipe, libc_sys_pipe)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.crt.syscall.Xpipe
INTERN_FUNCTION(libc_sys_Xpipe)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpipe)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpipe, libc_sys_Xpipe)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
.section .text.crt.syscall.select
INTERN_FUNCTION(libc_sys_select)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_select)
DEFINE_PUBLIC_WEAK_ALIAS(sys_select, libc_sys_select)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
.section .text.crt.syscall.Xselect
INTERN_FUNCTION(libc_sys_Xselect)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xselect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xselect, libc_sys_Xselect)

/* errno_t sched_yield(void) */
.section .text.crt.syscall.sched_yield
INTERN_FUNCTION(libc_sys_sched_yield)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_yield)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_yield, libc_sys_sched_yield)

/* errno_t sched_yield(void) */
.section .text.crt.syscall.Xsched_yield
INTERN_FUNCTION(libc_sys_Xsched_yield)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_yield)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_yield, libc_sys_Xsched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.crt.syscall.mremap
INTERN_FUNCTION(libc_sys_mremap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mremap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mremap, libc_sys_mremap)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.crt.syscall.Xmremap
INTERN_FUNCTION(libc_sys_Xmremap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmremap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmremap, libc_sys_Xmremap)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.crt.syscall.msync
INTERN_FUNCTION(libc_sys_msync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_msync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msync, libc_sys_msync)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.crt.syscall.Xmsync
INTERN_FUNCTION(libc_sys_Xmsync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsync, libc_sys_Xmsync)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.crt.syscall.mincore
INTERN_FUNCTION(libc_sys_mincore)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mincore)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mincore, libc_sys_mincore)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.crt.syscall.Xmincore
INTERN_FUNCTION(libc_sys_Xmincore)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmincore)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmincore, libc_sys_Xmincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.crt.syscall.madvise
INTERN_FUNCTION(libc_sys_madvise)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_madvise)
DEFINE_PUBLIC_WEAK_ALIAS(sys_madvise, libc_sys_madvise)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.crt.syscall.Xmadvise
INTERN_FUNCTION(libc_sys_Xmadvise)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmadvise)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmadvise, libc_sys_Xmadvise)

/* errno_t shmget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.shmget
INTERN_FUNCTION(libc_sys_shmget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_shmget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shmget, libc_sys_shmget)

/* errno_t shmget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xshmget
INTERN_FUNCTION(libc_sys_Xshmget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xshmget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshmget, libc_sys_Xshmget)

/* errno_t shmat(int TODO_PROTOTYPE) */
.section .text.crt.syscall.shmat
INTERN_FUNCTION(libc_sys_shmat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_shmat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shmat, libc_sys_shmat)

/* errno_t shmat(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xshmat
INTERN_FUNCTION(libc_sys_Xshmat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xshmat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshmat, libc_sys_Xshmat)

/* errno_t shmctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.shmctl
INTERN_FUNCTION(libc_sys_shmctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_shmctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shmctl, libc_sys_shmctl)

/* errno_t shmctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xshmctl
INTERN_FUNCTION(libc_sys_Xshmctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xshmctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshmctl, libc_sys_Xshmctl)

/* fd_t dup(fd_t fd) */
.section .text.crt.syscall.dup
INTERN_FUNCTION(libc_sys_dup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_dup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup, libc_sys_dup)

/* fd_t dup(fd_t fd) */
.section .text.crt.syscall.Xdup
INTERN_FUNCTION(libc_sys_Xdup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup, libc_sys_Xdup)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.crt.syscall.dup2
INTERN_FUNCTION(libc_sys_dup2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_dup2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup2, libc_sys_dup2)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.crt.syscall.Xdup2
INTERN_FUNCTION(libc_sys_Xdup2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdup2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup2, libc_sys_Xdup2)

/* errno_t pause(void) */
.section .text.crt.syscall.pause
INTERN_FUNCTION(libc_sys_pause)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pause)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pause, libc_sys_pause)

/* errno_t pause(void) */
.section .text.crt.syscall.Xpause
INTERN_FUNCTION(libc_sys_Xpause)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpause)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpause, libc_sys_Xpause)

/* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
.section .text.crt.syscall.nanosleep
INTERN_FUNCTION(libc_sys_nanosleep)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_nanosleep, libc_sys_nanosleep)

/* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
.section .text.crt.syscall.Xnanosleep
INTERN_FUNCTION(libc_sys_Xnanosleep)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xnanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xnanosleep, libc_sys_Xnanosleep)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.crt.syscall.getitimer
INTERN_FUNCTION(libc_sys_getitimer)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getitimer, libc_sys_getitimer)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.crt.syscall.Xgetitimer
INTERN_FUNCTION(libc_sys_Xgetitimer)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetitimer, libc_sys_Xgetitimer)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.crt.syscall.alarm
INTERN_FUNCTION(libc_sys_alarm)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_alarm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_alarm, libc_sys_alarm)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.crt.syscall.Xalarm
INTERN_FUNCTION(libc_sys_Xalarm)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xalarm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xalarm, libc_sys_Xalarm)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.crt.syscall.setitimer
INTERN_FUNCTION(libc_sys_setitimer)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setitimer, libc_sys_setitimer)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.crt.syscall.Xsetitimer
INTERN_FUNCTION(libc_sys_Xsetitimer)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetitimer)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetitimer, libc_sys_Xsetitimer)

/* pid_t getpid(void) */
.section .text.crt.syscall.getpid
INTERN_FUNCTION(libc_sys_getpid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpid, libc_sys_getpid)

/* pid_t getpid(void) */
.section .text.crt.syscall.Xgetpid
INTERN_FUNCTION(libc_sys_Xgetpid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpid, libc_sys_Xgetpid)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.crt.syscall.sendfile
INTERN_FUNCTION(libc_sys_sendfile)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sendfile)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendfile, libc_sys_sendfile)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.crt.syscall.Xsendfile
INTERN_FUNCTION(libc_sys_Xsendfile)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsendfile)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendfile, libc_sys_Xsendfile)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.crt.syscall.socket
INTERN_FUNCTION(libc_sys_socket)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_socket)
DEFINE_PUBLIC_WEAK_ALIAS(sys_socket, libc_sys_socket)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.crt.syscall.Xsocket
INTERN_FUNCTION(libc_sys_Xsocket)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsocket)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsocket, libc_sys_Xsocket)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.connect
INTERN_FUNCTION(libc_sys_connect)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_connect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_connect, libc_sys_connect)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xconnect
INTERN_FUNCTION(libc_sys_Xconnect)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xconnect)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xconnect, libc_sys_Xconnect)

/* errno_t accept(int TODO_PROTOTYPE) */
.section .text.crt.syscall.accept
INTERN_FUNCTION(libc_sys_accept)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_accept)
DEFINE_PUBLIC_WEAK_ALIAS(sys_accept, libc_sys_accept)

/* errno_t accept(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xaccept
INTERN_FUNCTION(libc_sys_Xaccept)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xaccept)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xaccept, libc_sys_Xaccept)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.sendto
INTERN_FUNCTION(libc_sys_sendto)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sendto)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendto, libc_sys_sendto)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xsendto
INTERN_FUNCTION(libc_sys_Xsendto)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsendto)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendto, libc_sys_Xsendto)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.recvfrom
INTERN_FUNCTION(libc_sys_recvfrom)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_recvfrom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvfrom, libc_sys_recvfrom)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xrecvfrom
INTERN_FUNCTION(libc_sys_Xrecvfrom)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrecvfrom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvfrom, libc_sys_Xrecvfrom)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.crt.syscall.sendmsg
INTERN_FUNCTION(libc_sys_sendmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sendmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendmsg, libc_sys_sendmsg)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsendmsg
INTERN_FUNCTION(libc_sys_Xsendmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsendmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendmsg, libc_sys_Xsendmsg)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.crt.syscall.recvmsg
INTERN_FUNCTION(libc_sys_recvmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_recvmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvmsg, libc_sys_recvmsg)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.crt.syscall.Xrecvmsg
INTERN_FUNCTION(libc_sys_Xrecvmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrecvmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvmsg, libc_sys_Xrecvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.crt.syscall.shutdown
INTERN_FUNCTION(libc_sys_shutdown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_shutdown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shutdown, libc_sys_shutdown)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.crt.syscall.Xshutdown
INTERN_FUNCTION(libc_sys_Xshutdown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xshutdown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshutdown, libc_sys_Xshutdown)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.bind
INTERN_FUNCTION(libc_sys_bind)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_bind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_bind, libc_sys_bind)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xbind
INTERN_FUNCTION(libc_sys_Xbind)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xbind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xbind, libc_sys_Xbind)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.crt.syscall.listen
INTERN_FUNCTION(libc_sys_listen)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_listen)
DEFINE_PUBLIC_WEAK_ALIAS(sys_listen, libc_sys_listen)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.crt.syscall.Xlisten
INTERN_FUNCTION(libc_sys_Xlisten)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlisten)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlisten, libc_sys_Xlisten)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.getsockname
INTERN_FUNCTION(libc_sys_getsockname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getsockname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsockname, libc_sys_getsockname)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xgetsockname
INTERN_FUNCTION(libc_sys_Xgetsockname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetsockname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsockname, libc_sys_Xgetsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.getpeername
INTERN_FUNCTION(libc_sys_getpeername)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpeername)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpeername, libc_sys_getpeername)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xgetpeername
INTERN_FUNCTION(libc_sys_Xgetpeername)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpeername)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpeername, libc_sys_Xgetpeername)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.crt.syscall.socketpair
INTERN_FUNCTION(libc_sys_socketpair)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_socketpair)
DEFINE_PUBLIC_WEAK_ALIAS(sys_socketpair, libc_sys_socketpair)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.crt.syscall.Xsocketpair
INTERN_FUNCTION(libc_sys_Xsocketpair)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsocketpair)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsocketpair, libc_sys_Xsocketpair)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.crt.syscall.setsockopt
INTERN_FUNCTION(libc_sys_setsockopt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setsockopt, libc_sys_setsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.crt.syscall.Xsetsockopt
INTERN_FUNCTION(libc_sys_Xsetsockopt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetsockopt, libc_sys_Xsetsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.crt.syscall.getsockopt
INTERN_FUNCTION(libc_sys_getsockopt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsockopt, libc_sys_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.crt.syscall.Xgetsockopt
INTERN_FUNCTION(libc_sys_Xgetsockopt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetsockopt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsockopt, libc_sys_Xgetsockopt)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
.section .text.crt.syscall.clone
INTERN_FUNCTION(libc_sys_clone)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clone)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clone, libc_sys_clone)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
.section .text.crt.syscall.Xclone
INTERN_FUNCTION(libc_sys_Xclone)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclone)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclone, libc_sys_Xclone)

/* pid_t fork(void) */
.section .text.crt.syscall.fork
INTERN_FUNCTION(libc_sys_fork)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fork, libc_sys_fork)

/* pid_t fork(void) */
.section .text.crt.syscall.Xfork
INTERN_FUNCTION(libc_sys_Xfork)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfork, libc_sys_Xfork)

/* pid_t vfork(void) */
.section .text.crt.syscall.vfork
INTERN_FUNCTION(libc_sys_vfork)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_vfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vfork, libc_sys_vfork)

/* pid_t vfork(void) */
.section .text.crt.syscall.Xvfork
INTERN_FUNCTION(libc_sys_Xvfork)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xvfork)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvfork, libc_sys_Xvfork)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.crt.syscall.execve
INTERN_FUNCTION(libc_sys_execve)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_execve)
DEFINE_PUBLIC_WEAK_ALIAS(sys_execve, libc_sys_execve)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.crt.syscall.Xexecve
INTERN_FUNCTION(libc_sys_Xexecve)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xexecve)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexecve, libc_sys_Xexecve)

/* void exit(syscall_ulong_t status) */
.section .text.crt.syscall.exit
INTERN_FUNCTION(libc_sys_exit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_exit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_exit, libc_sys_exit)

/* void exit(syscall_ulong_t status) */
.section .text.crt.syscall.Xexit
INTERN_FUNCTION(libc_sys_Xexit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xexit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexit, libc_sys_Xexit)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
.section .text.crt.syscall.wait4
INTERN_FUNCTION(libc_sys_wait4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_wait4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_wait4, libc_sys_wait4)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
.section .text.crt.syscall.Xwait4
INTERN_FUNCTION(libc_sys_Xwait4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwait4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwait4, libc_sys_Xwait4)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.crt.syscall.kill
INTERN_FUNCTION(libc_sys_kill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kill, libc_sys_kill)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.crt.syscall.Xkill
INTERN_FUNCTION(libc_sys_Xkill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkill, libc_sys_Xkill)

/* errno_t uname(struct utsname *name) */
.section .text.crt.syscall.uname
INTERN_FUNCTION(libc_sys_uname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_uname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_uname, libc_sys_uname)

/* errno_t uname(struct utsname *name) */
.section .text.crt.syscall.Xuname
INTERN_FUNCTION(libc_sys_Xuname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xuname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xuname, libc_sys_Xuname)

/* errno_t semget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semget
INTERN_FUNCTION(libc_sys_semget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_semget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_semget, libc_sys_semget)

/* errno_t semget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemget
INTERN_FUNCTION(libc_sys_Xsemget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsemget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsemget, libc_sys_Xsemget)

/* errno_t semop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semop
INTERN_FUNCTION(libc_sys_semop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_semop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_semop, libc_sys_semop)

/* errno_t semop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemop
INTERN_FUNCTION(libc_sys_Xsemop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsemop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsemop, libc_sys_Xsemop)

/* errno_t semctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semctl
INTERN_FUNCTION(libc_sys_semctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_semctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_semctl, libc_sys_semctl)

/* errno_t semctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemctl
INTERN_FUNCTION(libc_sys_Xsemctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsemctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsemctl, libc_sys_Xsemctl)

/* errno_t shmdt(int TODO_PROTOTYPE) */
.section .text.crt.syscall.shmdt
INTERN_FUNCTION(libc_sys_shmdt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_shmdt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_shmdt, libc_sys_shmdt)

/* errno_t shmdt(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xshmdt
INTERN_FUNCTION(libc_sys_Xshmdt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xshmdt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xshmdt, libc_sys_Xshmdt)

/* errno_t msgget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgget
INTERN_FUNCTION(libc_sys_msgget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_msgget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msgget, libc_sys_msgget)

/* errno_t msgget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgget
INTERN_FUNCTION(libc_sys_Xmsgget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmsgget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsgget, libc_sys_Xmsgget)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgsnd
INTERN_FUNCTION(libc_sys_msgsnd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_msgsnd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msgsnd, libc_sys_msgsnd)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgsnd
INTERN_FUNCTION(libc_sys_Xmsgsnd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmsgsnd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsgsnd, libc_sys_Xmsgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgrcv
INTERN_FUNCTION(libc_sys_msgrcv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_msgrcv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msgrcv, libc_sys_msgrcv)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgrcv
INTERN_FUNCTION(libc_sys_Xmsgrcv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmsgrcv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsgrcv, libc_sys_Xmsgrcv)

/* errno_t msgctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgctl
INTERN_FUNCTION(libc_sys_msgctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_msgctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_msgctl, libc_sys_msgctl)

/* errno_t msgctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgctl
INTERN_FUNCTION(libc_sys_Xmsgctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmsgctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmsgctl, libc_sys_Xmsgctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.crt.syscall.fcntl
INTERN_FUNCTION(libc_sys_fcntl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fcntl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fcntl, libc_sys_fcntl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.crt.syscall.Xfcntl
INTERN_FUNCTION(libc_sys_Xfcntl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfcntl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfcntl, libc_sys_Xfcntl)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.crt.syscall.flock
INTERN_FUNCTION(libc_sys_flock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_flock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_flock, libc_sys_flock)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.crt.syscall.Xflock
INTERN_FUNCTION(libc_sys_Xflock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xflock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xflock, libc_sys_Xflock)

/* errno_t fsync(fd_t fd) */
.section .text.crt.syscall.fsync
INTERN_FUNCTION(libc_sys_fsync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsync, libc_sys_fsync)

/* errno_t fsync(fd_t fd) */
.section .text.crt.syscall.Xfsync
INTERN_FUNCTION(libc_sys_Xfsync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsync, libc_sys_Xfsync)

/* errno_t fdatasync(fd_t fd) */
.section .text.crt.syscall.fdatasync
INTERN_FUNCTION(libc_sys_fdatasync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fdatasync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fdatasync, libc_sys_fdatasync)

/* errno_t fdatasync(fd_t fd) */
.section .text.crt.syscall.Xfdatasync
INTERN_FUNCTION(libc_sys_Xfdatasync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfdatasync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfdatasync, libc_sys_Xfdatasync)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.crt.syscall.truncate
INTERN_FUNCTION(libc_sys_truncate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_truncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_truncate, libc_sys_truncate)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.crt.syscall.Xtruncate
INTERN_FUNCTION(libc_sys_Xtruncate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtruncate, libc_sys_Xtruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.crt.syscall.ftruncate
INTERN_FUNCTION(libc_sys_ftruncate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ftruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ftruncate, libc_sys_ftruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.crt.syscall.Xftruncate
INTERN_FUNCTION(libc_sys_Xftruncate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xftruncate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xftruncate, libc_sys_Xftruncate)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.crt.syscall.getdents
INTERN_FUNCTION(libc_sys_getdents)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getdents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdents, libc_sys_getdents)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.crt.syscall.Xgetdents
INTERN_FUNCTION(libc_sys_Xgetdents)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetdents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdents, libc_sys_Xgetdents)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.crt.syscall.getcwd
INTERN_FUNCTION(libc_sys_getcwd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getcwd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getcwd, libc_sys_getcwd)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.crt.syscall.Xgetcwd
INTERN_FUNCTION(libc_sys_Xgetcwd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetcwd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetcwd, libc_sys_Xgetcwd)

/* errno_t chdir(char const *path) */
.section .text.crt.syscall.chdir
INTERN_FUNCTION(libc_sys_chdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_chdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chdir, libc_sys_chdir)

/* errno_t chdir(char const *path) */
.section .text.crt.syscall.Xchdir
INTERN_FUNCTION(libc_sys_Xchdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchdir, libc_sys_Xchdir)

/* errno_t fchdir(fd_t fd) */
.section .text.crt.syscall.fchdir
INTERN_FUNCTION(libc_sys_fchdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchdir, libc_sys_fchdir)

/* errno_t fchdir(fd_t fd) */
.section .text.crt.syscall.Xfchdir
INTERN_FUNCTION(libc_sys_Xfchdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchdir, libc_sys_Xfchdir)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.crt.syscall.rename
INTERN_FUNCTION(libc_sys_rename)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rename)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rename, libc_sys_rename)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.crt.syscall.Xrename
INTERN_FUNCTION(libc_sys_Xrename)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrename)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrename, libc_sys_Xrename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.crt.syscall.mkdir
INTERN_FUNCTION(libc_sys_mkdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mkdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mkdir, libc_sys_mkdir)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.crt.syscall.Xmkdir
INTERN_FUNCTION(libc_sys_Xmkdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmkdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmkdir, libc_sys_Xmkdir)

/* errno_t rmdir(char const *path) */
.section .text.crt.syscall.rmdir
INTERN_FUNCTION(libc_sys_rmdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rmdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rmdir, libc_sys_rmdir)

/* errno_t rmdir(char const *path) */
.section .text.crt.syscall.Xrmdir
INTERN_FUNCTION(libc_sys_Xrmdir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrmdir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrmdir, libc_sys_Xrmdir)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.crt.syscall.creat
INTERN_FUNCTION(libc_sys_creat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_creat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_creat, libc_sys_creat)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.crt.syscall.Xcreat
INTERN_FUNCTION(libc_sys_Xcreat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xcreat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcreat, libc_sys_Xcreat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.crt.syscall.link
INTERN_FUNCTION(libc_sys_link)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_link)
DEFINE_PUBLIC_WEAK_ALIAS(sys_link, libc_sys_link)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.crt.syscall.Xlink
INTERN_FUNCTION(libc_sys_Xlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlink, libc_sys_Xlink)

/* errno_t unlink(char const *filename) */
.section .text.crt.syscall.unlink
INTERN_FUNCTION(libc_sys_unlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_unlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unlink, libc_sys_unlink)

/* errno_t unlink(char const *filename) */
.section .text.crt.syscall.Xunlink
INTERN_FUNCTION(libc_sys_Xunlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xunlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunlink, libc_sys_Xunlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.crt.syscall.symlink
INTERN_FUNCTION(libc_sys_symlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_symlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_symlink, libc_sys_symlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.crt.syscall.Xsymlink
INTERN_FUNCTION(libc_sys_Xsymlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsymlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsymlink, libc_sys_Xsymlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.readlink
INTERN_FUNCTION(libc_sys_readlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readlink, libc_sys_readlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.Xreadlink
INTERN_FUNCTION(libc_sys_Xreadlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadlink, libc_sys_Xreadlink)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.crt.syscall.chmod
INTERN_FUNCTION(libc_sys_chmod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_chmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chmod, libc_sys_chmod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.crt.syscall.Xchmod
INTERN_FUNCTION(libc_sys_Xchmod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchmod, libc_sys_Xchmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.crt.syscall.fchmod
INTERN_FUNCTION(libc_sys_fchmod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchmod, libc_sys_fchmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.crt.syscall.Xfchmod
INTERN_FUNCTION(libc_sys_Xfchmod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchmod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchmod, libc_sys_Xfchmod)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.chown
INTERN_FUNCTION(libc_sys_chown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_chown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chown, libc_sys_chown)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xchown
INTERN_FUNCTION(libc_sys_Xchown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchown, libc_sys_Xchown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
.section .text.crt.syscall.fchown
INTERN_FUNCTION(libc_sys_fchown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchown, libc_sys_fchown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xfchown
INTERN_FUNCTION(libc_sys_Xfchown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchown, libc_sys_Xfchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.lchown
INTERN_FUNCTION(libc_sys_lchown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lchown, libc_sys_lchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xlchown
INTERN_FUNCTION(libc_sys_Xlchown)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlchown)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlchown, libc_sys_Xlchown)

/* mode_t umask(mode_t mode) */
.section .text.crt.syscall.umask
INTERN_FUNCTION(libc_sys_umask)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_umask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_umask, libc_sys_umask)

/* mode_t umask(mode_t mode) */
.section .text.crt.syscall.Xumask
INTERN_FUNCTION(libc_sys_Xumask)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xumask)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xumask, libc_sys_Xumask)

/* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
.section .text.crt.syscall.gettimeofday
INTERN_FUNCTION(libc_sys_gettimeofday)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_gettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_gettimeofday, libc_sys_gettimeofday)

/* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
.section .text.crt.syscall.Xgettimeofday
INTERN_FUNCTION(libc_sys_Xgettimeofday)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgettimeofday, libc_sys_Xgettimeofday)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.crt.syscall.getrlimit
INTERN_FUNCTION(libc_sys_getrlimit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getrlimit, libc_sys_getrlimit)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.crt.syscall.Xgetrlimit
INTERN_FUNCTION(libc_sys_Xgetrlimit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetrlimit, libc_sys_Xgetrlimit)

/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
.section .text.crt.syscall.getrusage
INTERN_FUNCTION(libc_sys_getrusage)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getrusage)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getrusage, libc_sys_getrusage)

/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
.section .text.crt.syscall.Xgetrusage
INTERN_FUNCTION(libc_sys_Xgetrusage)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetrusage)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetrusage, libc_sys_Xgetrusage)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.crt.syscall.sysinfo
INTERN_FUNCTION(libc_sys_sysinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sysinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sysinfo, libc_sys_sysinfo)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.crt.syscall.Xsysinfo
INTERN_FUNCTION(libc_sys_Xsysinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsysinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsysinfo, libc_sys_Xsysinfo)

/* clock_t times(struct tms *buf) */
.section .text.crt.syscall.times
INTERN_FUNCTION(libc_sys_times)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_times)
DEFINE_PUBLIC_WEAK_ALIAS(sys_times, libc_sys_times)

/* clock_t times(struct tms *buf) */
.section .text.crt.syscall.Xtimes
INTERN_FUNCTION(libc_sys_Xtimes)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimes, libc_sys_Xtimes)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.crt.syscall.ptrace
INTERN_FUNCTION(libc_sys_ptrace)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ptrace)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ptrace, libc_sys_ptrace)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.crt.syscall.Xptrace
INTERN_FUNCTION(libc_sys_Xptrace)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xptrace)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xptrace, libc_sys_Xptrace)

/* uid_t getuid(void) */
.section .text.crt.syscall.getuid
INTERN_FUNCTION(libc_sys_getuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getuid, libc_sys_getuid)

/* uid_t getuid(void) */
.section .text.crt.syscall.Xgetuid
INTERN_FUNCTION(libc_sys_Xgetuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetuid, libc_sys_Xgetuid)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.crt.syscall.syslog
INTERN_FUNCTION(libc_sys_syslog)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_syslog)
DEFINE_PUBLIC_WEAK_ALIAS(sys_syslog, libc_sys_syslog)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.crt.syscall.Xsyslog
INTERN_FUNCTION(libc_sys_Xsyslog)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsyslog)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsyslog, libc_sys_Xsyslog)

/* gid_t getgid(void) */
.section .text.crt.syscall.getgid
INTERN_FUNCTION(libc_sys_getgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getgid, libc_sys_getgid)

/* gid_t getgid(void) */
.section .text.crt.syscall.Xgetgid
INTERN_FUNCTION(libc_sys_Xgetgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetgid, libc_sys_Xgetgid)

/* errno_t setuid(uid_t uid) */
.section .text.crt.syscall.setuid
INTERN_FUNCTION(libc_sys_setuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setuid, libc_sys_setuid)

/* errno_t setuid(uid_t uid) */
.section .text.crt.syscall.Xsetuid
INTERN_FUNCTION(libc_sys_Xsetuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetuid, libc_sys_Xsetuid)

/* errno_t setgid(gid_t gid) */
.section .text.crt.syscall.setgid
INTERN_FUNCTION(libc_sys_setgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setgid, libc_sys_setgid)

/* errno_t setgid(gid_t gid) */
.section .text.crt.syscall.Xsetgid
INTERN_FUNCTION(libc_sys_Xsetgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetgid, libc_sys_Xsetgid)

/* uid_t geteuid(void) */
.section .text.crt.syscall.geteuid
INTERN_FUNCTION(libc_sys_geteuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_geteuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_geteuid, libc_sys_geteuid)

/* uid_t geteuid(void) */
.section .text.crt.syscall.Xgeteuid
INTERN_FUNCTION(libc_sys_Xgeteuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgeteuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgeteuid, libc_sys_Xgeteuid)

/* gid_t getegid(void) */
.section .text.crt.syscall.getegid
INTERN_FUNCTION(libc_sys_getegid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getegid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getegid, libc_sys_getegid)

/* gid_t getegid(void) */
.section .text.crt.syscall.Xgetegid
INTERN_FUNCTION(libc_sys_Xgetegid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetegid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetegid, libc_sys_Xgetegid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.crt.syscall.setpgid
INTERN_FUNCTION(libc_sys_setpgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setpgid, libc_sys_setpgid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.crt.syscall.Xsetpgid
INTERN_FUNCTION(libc_sys_Xsetpgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetpgid, libc_sys_Xsetpgid)

/* pid_t getppid(void) */
.section .text.crt.syscall.getppid
INTERN_FUNCTION(libc_sys_getppid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getppid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getppid, libc_sys_getppid)

/* pid_t getppid(void) */
.section .text.crt.syscall.Xgetppid
INTERN_FUNCTION(libc_sys_Xgetppid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetppid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetppid, libc_sys_Xgetppid)

/* pid_t getpgrp(void) */
.section .text.crt.syscall.getpgrp
INTERN_FUNCTION(libc_sys_getpgrp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpgrp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpgrp, libc_sys_getpgrp)

/* pid_t getpgrp(void) */
.section .text.crt.syscall.Xgetpgrp
INTERN_FUNCTION(libc_sys_Xgetpgrp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpgrp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpgrp, libc_sys_Xgetpgrp)

/* pid_t setsid(void) */
.section .text.crt.syscall.setsid
INTERN_FUNCTION(libc_sys_setsid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setsid, libc_sys_setsid)

/* pid_t setsid(void) */
.section .text.crt.syscall.Xsetsid
INTERN_FUNCTION(libc_sys_Xsetsid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetsid, libc_sys_Xsetsid)

/* errno_t setreuid(uid_t ruid, uid_t euid) */
.section .text.crt.syscall.setreuid
INTERN_FUNCTION(libc_sys_setreuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setreuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setreuid, libc_sys_setreuid)

/* errno_t setreuid(uid_t ruid, uid_t euid) */
.section .text.crt.syscall.Xsetreuid
INTERN_FUNCTION(libc_sys_Xsetreuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetreuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetreuid, libc_sys_Xsetreuid)

/* errno_t setregid(gid_t rgid, gid_t egid) */
.section .text.crt.syscall.setregid
INTERN_FUNCTION(libc_sys_setregid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setregid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setregid, libc_sys_setregid)

/* errno_t setregid(gid_t rgid, gid_t egid) */
.section .text.crt.syscall.Xsetregid
INTERN_FUNCTION(libc_sys_Xsetregid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetregid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetregid, libc_sys_Xsetregid)

/* errno_t getgroups(size_t size, gid_t[] list) */
.section .text.crt.syscall.getgroups
INTERN_FUNCTION(libc_sys_getgroups)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getgroups)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getgroups, libc_sys_getgroups)

/* errno_t getgroups(size_t size, gid_t[] list) */
.section .text.crt.syscall.Xgetgroups
INTERN_FUNCTION(libc_sys_Xgetgroups)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetgroups)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetgroups, libc_sys_Xgetgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
.section .text.crt.syscall.setgroups
INTERN_FUNCTION(libc_sys_setgroups)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setgroups)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setgroups, libc_sys_setgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
.section .text.crt.syscall.Xsetgroups
INTERN_FUNCTION(libc_sys_Xsetgroups)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetgroups)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetgroups, libc_sys_Xsetgroups)

/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
.section .text.crt.syscall.setresuid
INTERN_FUNCTION(libc_sys_setresuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setresuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setresuid, libc_sys_setresuid)

/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
.section .text.crt.syscall.Xsetresuid
INTERN_FUNCTION(libc_sys_Xsetresuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetresuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetresuid, libc_sys_Xsetresuid)

/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
.section .text.crt.syscall.getresuid
INTERN_FUNCTION(libc_sys_getresuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getresuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getresuid, libc_sys_getresuid)

/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
.section .text.crt.syscall.Xgetresuid
INTERN_FUNCTION(libc_sys_Xgetresuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetresuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetresuid, libc_sys_Xgetresuid)

/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
.section .text.crt.syscall.setresgid
INTERN_FUNCTION(libc_sys_setresgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setresgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setresgid, libc_sys_setresgid)

/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
.section .text.crt.syscall.Xsetresgid
INTERN_FUNCTION(libc_sys_Xsetresgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetresgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetresgid, libc_sys_Xsetresgid)

/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
.section .text.crt.syscall.getresgid
INTERN_FUNCTION(libc_sys_getresgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getresgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getresgid, libc_sys_getresgid)

/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
.section .text.crt.syscall.Xgetresgid
INTERN_FUNCTION(libc_sys_Xgetresgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetresgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetresgid, libc_sys_Xgetresgid)

/* pid_t getpgid(pid_t pid) */
.section .text.crt.syscall.getpgid
INTERN_FUNCTION(libc_sys_getpgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpgid, libc_sys_getpgid)

/* pid_t getpgid(pid_t pid) */
.section .text.crt.syscall.Xgetpgid
INTERN_FUNCTION(libc_sys_Xgetpgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpgid, libc_sys_Xgetpgid)

/* errno_t setfsuid(uid_t uid) */
.section .text.crt.syscall.setfsuid
INTERN_FUNCTION(libc_sys_setfsuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setfsuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setfsuid, libc_sys_setfsuid)

/* errno_t setfsuid(uid_t uid) */
.section .text.crt.syscall.Xsetfsuid
INTERN_FUNCTION(libc_sys_Xsetfsuid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetfsuid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetfsuid, libc_sys_Xsetfsuid)

/* errno_t setfsgid(gid_t gid) */
.section .text.crt.syscall.setfsgid
INTERN_FUNCTION(libc_sys_setfsgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setfsgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setfsgid, libc_sys_setfsgid)

/* errno_t setfsgid(gid_t gid) */
.section .text.crt.syscall.Xsetfsgid
INTERN_FUNCTION(libc_sys_Xsetfsgid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetfsgid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetfsgid, libc_sys_Xsetfsgid)

/* pid_t getsid(pid_t pid) */
.section .text.crt.syscall.getsid
INTERN_FUNCTION(libc_sys_getsid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getsid, libc_sys_getsid)

/* pid_t getsid(pid_t pid) */
.section .text.crt.syscall.Xgetsid
INTERN_FUNCTION(libc_sys_Xgetsid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetsid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetsid, libc_sys_Xgetsid)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.capget
INTERN_FUNCTION(libc_sys_capget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_capget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_capget, libc_sys_capget)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcapget
INTERN_FUNCTION(libc_sys_Xcapget)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xcapget)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcapget, libc_sys_Xcapget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.crt.syscall.capset
INTERN_FUNCTION(libc_sys_capset)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_capset)
DEFINE_PUBLIC_WEAK_ALIAS(sys_capset, libc_sys_capset)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcapset
INTERN_FUNCTION(libc_sys_Xcapset)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xcapset)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcapset, libc_sys_Xcapset)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigpending
INTERN_FUNCTION(libc_sys_rt_sigpending)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigpending)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigpending, libc_sys_rt_sigpending)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigpending
INTERN_FUNCTION(libc_sys_Xrt_sigpending)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigpending)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigpending, libc_sys_Xrt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigtimedwait
INTERN_FUNCTION(libc_sys_rt_sigtimedwait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigtimedwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigtimedwait, libc_sys_rt_sigtimedwait)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigtimedwait
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigtimedwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigtimedwait, libc_sys_Xrt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.crt.syscall.rt_sigqueueinfo
INTERN_FUNCTION(libc_sys_rt_sigqueueinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigqueueinfo, libc_sys_rt_sigqueueinfo)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.crt.syscall.Xrt_sigqueueinfo
INTERN_FUNCTION(libc_sys_Xrt_sigqueueinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigqueueinfo, libc_sys_Xrt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigsuspend
INTERN_FUNCTION(libc_sys_rt_sigsuspend)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_sigsuspend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_sigsuspend, libc_sys_rt_sigsuspend)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigsuspend
INTERN_FUNCTION(libc_sys_Xrt_sigsuspend)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_sigsuspend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_sigsuspend, libc_sys_Xrt_sigsuspend)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.crt.syscall.sigaltstack
INTERN_FUNCTION(libc_sys_sigaltstack)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sigaltstack)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sigaltstack, libc_sys_sigaltstack)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.crt.syscall.Xsigaltstack
INTERN_FUNCTION(libc_sys_Xsigaltstack)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsigaltstack)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsigaltstack, libc_sys_Xsigaltstack)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.crt.syscall.utime
INTERN_FUNCTION(libc_sys_utime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_utime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utime, libc_sys_utime)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.crt.syscall.Xutime
INTERN_FUNCTION(libc_sys_Xutime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xutime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutime, libc_sys_Xutime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.mknod
INTERN_FUNCTION(libc_sys_mknod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mknod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mknod, libc_sys_mknod)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.Xmknod
INTERN_FUNCTION(libc_sys_Xmknod)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmknod)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmknod, libc_sys_Xmknod)

/* errno_t uselib(char const *library) */
.section .text.crt.syscall.uselib
INTERN_FUNCTION(libc_sys_uselib)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_uselib)
DEFINE_PUBLIC_WEAK_ALIAS(sys_uselib, libc_sys_uselib)

/* errno_t uselib(char const *library) */
.section .text.crt.syscall.Xuselib
INTERN_FUNCTION(libc_sys_Xuselib)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xuselib)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xuselib, libc_sys_Xuselib)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.crt.syscall.personality
INTERN_FUNCTION(libc_sys_personality)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_personality)
DEFINE_PUBLIC_WEAK_ALIAS(sys_personality, libc_sys_personality)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpersonality
INTERN_FUNCTION(libc_sys_Xpersonality)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpersonality)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpersonality, libc_sys_Xpersonality)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.crt.syscall.ustat
INTERN_FUNCTION(libc_sys_ustat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ustat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ustat, libc_sys_ustat)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.crt.syscall.Xustat
INTERN_FUNCTION(libc_sys_Xustat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xustat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xustat, libc_sys_Xustat)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.crt.syscall.statfs
INTERN_FUNCTION(libc_sys_statfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_statfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_statfs, libc_sys_statfs)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.crt.syscall.Xstatfs
INTERN_FUNCTION(libc_sys_Xstatfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xstatfs, libc_sys_Xstatfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.crt.syscall.fstatfs
INTERN_FUNCTION(libc_sys_fstatfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fstatfs, libc_sys_fstatfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.crt.syscall.Xfstatfs
INTERN_FUNCTION(libc_sys_Xfstatfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfstatfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfstatfs, libc_sys_Xfstatfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sysfs
INTERN_FUNCTION(libc_sys_sysfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sysfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sysfs, libc_sys_sysfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsysfs
INTERN_FUNCTION(libc_sys_Xsysfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsysfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsysfs, libc_sys_Xsysfs)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.crt.syscall.getpriority
INTERN_FUNCTION(libc_sys_getpriority)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpriority, libc_sys_getpriority)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.crt.syscall.Xgetpriority
INTERN_FUNCTION(libc_sys_Xgetpriority)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpriority, libc_sys_Xgetpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.crt.syscall.setpriority
INTERN_FUNCTION(libc_sys_setpriority)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setpriority, libc_sys_setpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.crt.syscall.Xsetpriority
INTERN_FUNCTION(libc_sys_Xsetpriority)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetpriority)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetpriority, libc_sys_Xsetpriority)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.crt.syscall.sched_setparam
INTERN_FUNCTION(libc_sys_sched_setparam)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_setparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setparam, libc_sys_sched_setparam)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.crt.syscall.Xsched_setparam
INTERN_FUNCTION(libc_sys_Xsched_setparam)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_setparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setparam, libc_sys_Xsched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.crt.syscall.sched_getparam
INTERN_FUNCTION(libc_sys_sched_getparam)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_getparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getparam, libc_sys_sched_getparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.crt.syscall.Xsched_getparam
INTERN_FUNCTION(libc_sys_Xsched_getparam)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_getparam)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getparam, libc_sys_Xsched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.crt.syscall.sched_setscheduler
INTERN_FUNCTION(libc_sys_sched_setscheduler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_setscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setscheduler, libc_sys_sched_setscheduler)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.crt.syscall.Xsched_setscheduler
INTERN_FUNCTION(libc_sys_Xsched_setscheduler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_setscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setscheduler, libc_sys_Xsched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.crt.syscall.sched_getscheduler
INTERN_FUNCTION(libc_sys_sched_getscheduler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_getscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getscheduler, libc_sys_sched_getscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.crt.syscall.Xsched_getscheduler
INTERN_FUNCTION(libc_sys_Xsched_getscheduler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_getscheduler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getscheduler, libc_sys_Xsched_getscheduler)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.crt.syscall.sched_get_priority_max
INTERN_FUNCTION(libc_sys_sched_get_priority_max)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_get_priority_max)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_get_priority_max, libc_sys_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.crt.syscall.Xsched_get_priority_max
INTERN_FUNCTION(libc_sys_Xsched_get_priority_max)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_get_priority_max)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_get_priority_max, libc_sys_Xsched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.crt.syscall.sched_get_priority_min
INTERN_FUNCTION(libc_sys_sched_get_priority_min)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_get_priority_min)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_get_priority_min, libc_sys_sched_get_priority_min)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.crt.syscall.Xsched_get_priority_min
INTERN_FUNCTION(libc_sys_Xsched_get_priority_min)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_get_priority_min)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_get_priority_min, libc_sys_Xsched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
.section .text.crt.syscall.sched_rr_get_interval
INTERN_FUNCTION(libc_sys_sched_rr_get_interval)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_rr_get_interval)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_rr_get_interval, libc_sys_sched_rr_get_interval)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
.section .text.crt.syscall.Xsched_rr_get_interval
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_rr_get_interval)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_rr_get_interval, libc_sys_Xsched_rr_get_interval)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.crt.syscall.mlock
INTERN_FUNCTION(libc_sys_mlock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mlock, libc_sys_mlock)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.crt.syscall.Xmlock
INTERN_FUNCTION(libc_sys_Xmlock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmlock, libc_sys_Xmlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.crt.syscall.munlock
INTERN_FUNCTION(libc_sys_munlock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_munlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munlock, libc_sys_munlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.crt.syscall.Xmunlock
INTERN_FUNCTION(libc_sys_Xmunlock)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmunlock)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunlock, libc_sys_Xmunlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.crt.syscall.mlockall
INTERN_FUNCTION(libc_sys_mlockall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mlockall, libc_sys_mlockall)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.crt.syscall.Xmlockall
INTERN_FUNCTION(libc_sys_Xmlockall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmlockall, libc_sys_Xmlockall)

/* errno_t munlockall(void) */
.section .text.crt.syscall.munlockall
INTERN_FUNCTION(libc_sys_munlockall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_munlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_munlockall, libc_sys_munlockall)

/* errno_t munlockall(void) */
.section .text.crt.syscall.Xmunlockall
INTERN_FUNCTION(libc_sys_Xmunlockall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmunlockall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmunlockall, libc_sys_Xmunlockall)

/* errno_t vhangup(void) */
.section .text.crt.syscall.vhangup
INTERN_FUNCTION(libc_sys_vhangup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_vhangup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vhangup, libc_sys_vhangup)

/* errno_t vhangup(void) */
.section .text.crt.syscall.Xvhangup
INTERN_FUNCTION(libc_sys_Xvhangup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xvhangup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvhangup, libc_sys_Xvhangup)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.crt.syscall.modify_ldt
INTERN_FUNCTION(libc_sys_modify_ldt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_modify_ldt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_modify_ldt, libc_sys_modify_ldt)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.crt.syscall.Xmodify_ldt
INTERN_FUNCTION(libc_sys_Xmodify_ldt)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmodify_ldt)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmodify_ldt, libc_sys_Xmodify_ldt)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.crt.syscall.pivot_root
INTERN_FUNCTION(libc_sys_pivot_root)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pivot_root)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pivot_root, libc_sys_pivot_root)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpivot_root
INTERN_FUNCTION(libc_sys_Xpivot_root)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpivot_root)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpivot_root, libc_sys_Xpivot_root)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall._sysctl
INTERN_FUNCTION(libc_sys__sysctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys__sysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys__sysctl, libc_sys__sysctl)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.X_sysctl
INTERN_FUNCTION(libc_sys_X_sysctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_X_sysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_X_sysctl, libc_sys_X_sysctl)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.prctl
INTERN_FUNCTION(libc_sys_prctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_prctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_prctl, libc_sys_prctl)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xprctl
INTERN_FUNCTION(libc_sys_Xprctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xprctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprctl, libc_sys_Xprctl)

/* errno_t arch_prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.arch_prctl
INTERN_FUNCTION(libc_sys_arch_prctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_arch_prctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_arch_prctl, libc_sys_arch_prctl)

/* errno_t arch_prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xarch_prctl
INTERN_FUNCTION(libc_sys_Xarch_prctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xarch_prctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xarch_prctl, libc_sys_Xarch_prctl)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.crt.syscall.adjtimex
INTERN_FUNCTION(libc_sys_adjtimex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_adjtimex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_adjtimex, libc_sys_adjtimex)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xadjtimex
INTERN_FUNCTION(libc_sys_Xadjtimex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xadjtimex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xadjtimex, libc_sys_Xadjtimex)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.crt.syscall.setrlimit
INTERN_FUNCTION(libc_sys_setrlimit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setrlimit, libc_sys_setrlimit)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.crt.syscall.Xsetrlimit
INTERN_FUNCTION(libc_sys_Xsetrlimit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetrlimit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetrlimit, libc_sys_Xsetrlimit)

/* errno_t chroot(char const *path) */
.section .text.crt.syscall.chroot
INTERN_FUNCTION(libc_sys_chroot)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_chroot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_chroot, libc_sys_chroot)

/* errno_t chroot(char const *path) */
.section .text.crt.syscall.Xchroot
INTERN_FUNCTION(libc_sys_Xchroot)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xchroot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xchroot, libc_sys_Xchroot)

/* errno_t sync(void) */
.section .text.crt.syscall.sync
INTERN_FUNCTION(libc_sys_sync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sync, libc_sys_sync)

/* errno_t sync(void) */
.section .text.crt.syscall.Xsync
INTERN_FUNCTION(libc_sys_Xsync)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsync)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsync, libc_sys_Xsync)

/* errno_t acct(char const *filename) */
.section .text.crt.syscall.acct
INTERN_FUNCTION(libc_sys_acct)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_acct)
DEFINE_PUBLIC_WEAK_ALIAS(sys_acct, libc_sys_acct)

/* errno_t acct(char const *filename) */
.section .text.crt.syscall.Xacct
INTERN_FUNCTION(libc_sys_Xacct)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xacct)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xacct, libc_sys_Xacct)

/* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
.section .text.crt.syscall.settimeofday
INTERN_FUNCTION(libc_sys_settimeofday)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_settimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_settimeofday, libc_sys_settimeofday)

/* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
.section .text.crt.syscall.Xsettimeofday
INTERN_FUNCTION(libc_sys_Xsettimeofday)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsettimeofday)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsettimeofday, libc_sys_Xsettimeofday)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.crt.syscall.mount
INTERN_FUNCTION(libc_sys_mount)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mount)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mount, libc_sys_mount)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.crt.syscall.Xmount
INTERN_FUNCTION(libc_sys_Xmount)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmount)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmount, libc_sys_Xmount)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.crt.syscall.umount2
INTERN_FUNCTION(libc_sys_umount2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_umount2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_umount2, libc_sys_umount2)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.crt.syscall.Xumount2
INTERN_FUNCTION(libc_sys_Xumount2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xumount2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xumount2, libc_sys_Xumount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.crt.syscall.swapon
INTERN_FUNCTION(libc_sys_swapon)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_swapon)
DEFINE_PUBLIC_WEAK_ALIAS(sys_swapon, libc_sys_swapon)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.crt.syscall.Xswapon
INTERN_FUNCTION(libc_sys_Xswapon)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xswapon)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xswapon, libc_sys_Xswapon)

/* errno_t swapoff(char const *pathname) */
.section .text.crt.syscall.swapoff
INTERN_FUNCTION(libc_sys_swapoff)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_swapoff)
DEFINE_PUBLIC_WEAK_ALIAS(sys_swapoff, libc_sys_swapoff)

/* errno_t swapoff(char const *pathname) */
.section .text.crt.syscall.Xswapoff
INTERN_FUNCTION(libc_sys_Xswapoff)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xswapoff)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xswapoff, libc_sys_Xswapoff)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.crt.syscall.reboot
INTERN_FUNCTION(libc_sys_reboot)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_reboot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_reboot, libc_sys_reboot)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.crt.syscall.Xreboot
INTERN_FUNCTION(libc_sys_Xreboot)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreboot)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreboot, libc_sys_Xreboot)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.crt.syscall.sethostname
INTERN_FUNCTION(libc_sys_sethostname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sethostname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sethostname, libc_sys_sethostname)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.crt.syscall.Xsethostname
INTERN_FUNCTION(libc_sys_Xsethostname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsethostname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsethostname, libc_sys_Xsethostname)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.crt.syscall.setdomainname
INTERN_FUNCTION(libc_sys_setdomainname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setdomainname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setdomainname, libc_sys_setdomainname)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.crt.syscall.Xsetdomainname
INTERN_FUNCTION(libc_sys_Xsetdomainname)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetdomainname)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetdomainname, libc_sys_Xsetdomainname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.crt.syscall.iopl
INTERN_FUNCTION(libc_sys_iopl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_iopl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_iopl, libc_sys_iopl)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.crt.syscall.Xiopl
INTERN_FUNCTION(libc_sys_Xiopl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xiopl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xiopl, libc_sys_Xiopl)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.crt.syscall.ioperm
INTERN_FUNCTION(libc_sys_ioperm)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ioperm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioperm, libc_sys_ioperm)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.crt.syscall.Xioperm
INTERN_FUNCTION(libc_sys_Xioperm)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xioperm)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioperm, libc_sys_Xioperm)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.create_module
INTERN_FUNCTION(libc_sys_create_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_create_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_create_module, libc_sys_create_module)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcreate_module
INTERN_FUNCTION(libc_sys_Xcreate_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xcreate_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcreate_module, libc_sys_Xcreate_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.init_module
INTERN_FUNCTION(libc_sys_init_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_init_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_init_module, libc_sys_init_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinit_module
INTERN_FUNCTION(libc_sys_Xinit_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xinit_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xinit_module, libc_sys_Xinit_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.delete_module
INTERN_FUNCTION(libc_sys_delete_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_delete_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_delete_module, libc_sys_delete_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xdelete_module
INTERN_FUNCTION(libc_sys_Xdelete_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdelete_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdelete_module, libc_sys_Xdelete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_kernel_syms
INTERN_FUNCTION(libc_sys_get_kernel_syms)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_get_kernel_syms)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_kernel_syms, libc_sys_get_kernel_syms)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_kernel_syms
INTERN_FUNCTION(libc_sys_Xget_kernel_syms)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xget_kernel_syms)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_kernel_syms, libc_sys_Xget_kernel_syms)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.query_module
INTERN_FUNCTION(libc_sys_query_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_query_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_query_module, libc_sys_query_module)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xquery_module
INTERN_FUNCTION(libc_sys_Xquery_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xquery_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xquery_module, libc_sys_Xquery_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.quotactl
INTERN_FUNCTION(libc_sys_quotactl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_quotactl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_quotactl, libc_sys_quotactl)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xquotactl
INTERN_FUNCTION(libc_sys_Xquotactl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xquotactl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xquotactl, libc_sys_Xquotactl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.nfsservctl
INTERN_FUNCTION(libc_sys_nfsservctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_nfsservctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_nfsservctl, libc_sys_nfsservctl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xnfsservctl
INTERN_FUNCTION(libc_sys_Xnfsservctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xnfsservctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xnfsservctl, libc_sys_Xnfsservctl)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.getpmsg
INTERN_FUNCTION(libc_sys_getpmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getpmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getpmsg, libc_sys_getpmsg)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xgetpmsg
INTERN_FUNCTION(libc_sys_Xgetpmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetpmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetpmsg, libc_sys_Xgetpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.putpmsg
INTERN_FUNCTION(libc_sys_putpmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_putpmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_putpmsg, libc_sys_putpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xputpmsg
INTERN_FUNCTION(libc_sys_Xputpmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xputpmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xputpmsg, libc_sys_Xputpmsg)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.afs_syscall
INTERN_FUNCTION(libc_sys_afs_syscall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_afs_syscall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_afs_syscall, libc_sys_afs_syscall)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xafs_syscall
INTERN_FUNCTION(libc_sys_Xafs_syscall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xafs_syscall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xafs_syscall, libc_sys_Xafs_syscall)

/* errno_t tuxcall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.tuxcall
INTERN_FUNCTION(libc_sys_tuxcall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_tuxcall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tuxcall, libc_sys_tuxcall)

/* errno_t tuxcall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xtuxcall
INTERN_FUNCTION(libc_sys_Xtuxcall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtuxcall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtuxcall, libc_sys_Xtuxcall)

/* errno_t security(int TODO_PROTOTYPE) */
.section .text.crt.syscall.security
INTERN_FUNCTION(libc_sys_security)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_security)
DEFINE_PUBLIC_WEAK_ALIAS(sys_security, libc_sys_security)

/* errno_t security(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsecurity
INTERN_FUNCTION(libc_sys_Xsecurity)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsecurity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsecurity, libc_sys_Xsecurity)

/* pid_t gettid(void) */
.section .text.crt.syscall.gettid
INTERN_FUNCTION(libc_sys_gettid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_gettid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_gettid, libc_sys_gettid)

/* pid_t gettid(void) */
.section .text.crt.syscall.Xgettid
INTERN_FUNCTION(libc_sys_Xgettid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgettid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgettid, libc_sys_Xgettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.crt.syscall.readahead
INTERN_FUNCTION(libc_sys_readahead)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readahead)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readahead, libc_sys_readahead)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.crt.syscall.Xreadahead
INTERN_FUNCTION(libc_sys_Xreadahead)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadahead)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadahead, libc_sys_Xreadahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.setxattr
INTERN_FUNCTION(libc_sys_setxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setxattr, libc_sys_setxattr)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsetxattr
INTERN_FUNCTION(libc_sys_Xsetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetxattr, libc_sys_Xsetxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.lsetxattr
INTERN_FUNCTION(libc_sys_lsetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lsetxattr, libc_sys_lsetxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xlsetxattr
INTERN_FUNCTION(libc_sys_Xlsetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlsetxattr, libc_sys_Xlsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.fsetxattr
INTERN_FUNCTION(libc_sys_fsetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsetxattr, libc_sys_fsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xfsetxattr
INTERN_FUNCTION(libc_sys_Xfsetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfsetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsetxattr, libc_sys_Xfsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.getxattr
INTERN_FUNCTION(libc_sys_getxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getxattr, libc_sys_getxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xgetxattr
INTERN_FUNCTION(libc_sys_Xgetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetxattr, libc_sys_Xgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.lgetxattr
INTERN_FUNCTION(libc_sys_lgetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lgetxattr, libc_sys_lgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xlgetxattr
INTERN_FUNCTION(libc_sys_Xlgetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlgetxattr, libc_sys_Xlgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.fgetxattr
INTERN_FUNCTION(libc_sys_fgetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fgetxattr, libc_sys_fgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xfgetxattr
INTERN_FUNCTION(libc_sys_Xfgetxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfgetxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfgetxattr, libc_sys_Xfgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.listxattr
INTERN_FUNCTION(libc_sys_listxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_listxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_listxattr, libc_sys_listxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xlistxattr
INTERN_FUNCTION(libc_sys_Xlistxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlistxattr, libc_sys_Xlistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.llistxattr
INTERN_FUNCTION(libc_sys_llistxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_llistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_llistxattr, libc_sys_llistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xllistxattr
INTERN_FUNCTION(libc_sys_Xllistxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xllistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xllistxattr, libc_sys_Xllistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.flistxattr
INTERN_FUNCTION(libc_sys_flistxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_flistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_flistxattr, libc_sys_flistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xflistxattr
INTERN_FUNCTION(libc_sys_Xflistxattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xflistxattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xflistxattr, libc_sys_Xflistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.crt.syscall.removexattr
INTERN_FUNCTION(libc_sys_removexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_removexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_removexattr, libc_sys_removexattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.crt.syscall.Xremovexattr
INTERN_FUNCTION(libc_sys_Xremovexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xremovexattr, libc_sys_Xremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.crt.syscall.lremovexattr
INTERN_FUNCTION(libc_sys_lremovexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lremovexattr, libc_sys_lremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.crt.syscall.Xlremovexattr
INTERN_FUNCTION(libc_sys_Xlremovexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlremovexattr, libc_sys_Xlremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.crt.syscall.fremovexattr
INTERN_FUNCTION(libc_sys_fremovexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fremovexattr, libc_sys_fremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.crt.syscall.Xfremovexattr
INTERN_FUNCTION(libc_sys_Xfremovexattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfremovexattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfremovexattr, libc_sys_Xfremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.crt.syscall.tkill
INTERN_FUNCTION(libc_sys_tkill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_tkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tkill, libc_sys_tkill)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.crt.syscall.Xtkill
INTERN_FUNCTION(libc_sys_Xtkill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtkill, libc_sys_Xtkill)

/* time32_t time(time32_t *timer) */
.section .text.crt.syscall.time
INTERN_FUNCTION(libc_sys_time)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_time)
DEFINE_PUBLIC_WEAK_ALIAS(sys_time, libc_sys_time)

/* time32_t time(time32_t *timer) */
.section .text.crt.syscall.Xtime
INTERN_FUNCTION(libc_sys_Xtime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtime, libc_sys_Xtime)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.crt.syscall.futex
INTERN_FUNCTION(libc_sys_futex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_futex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_futex, libc_sys_futex)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.crt.syscall.Xfutex
INTERN_FUNCTION(libc_sys_Xfutex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfutex, libc_sys_Xfutex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.crt.syscall.sched_setaffinity
INTERN_FUNCTION(libc_sys_sched_setaffinity)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_setaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setaffinity, libc_sys_sched_setaffinity)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.crt.syscall.Xsched_setaffinity
INTERN_FUNCTION(libc_sys_Xsched_setaffinity)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_setaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setaffinity, libc_sys_Xsched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.crt.syscall.sched_getaffinity
INTERN_FUNCTION(libc_sys_sched_getaffinity)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_getaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getaffinity, libc_sys_sched_getaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.crt.syscall.Xsched_getaffinity
INTERN_FUNCTION(libc_sys_Xsched_getaffinity)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_getaffinity)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getaffinity, libc_sys_Xsched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_thread_area
INTERN_FUNCTION(libc_sys_set_thread_area)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_thread_area)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_thread_area, libc_sys_set_thread_area)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_thread_area
INTERN_FUNCTION(libc_sys_Xset_thread_area)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_thread_area)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_thread_area, libc_sys_Xset_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_setup
INTERN_FUNCTION(libc_sys_io_setup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_io_setup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_io_setup, libc_sys_io_setup)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_setup
INTERN_FUNCTION(libc_sys_Xio_setup)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xio_setup)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xio_setup, libc_sys_Xio_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_destroy
INTERN_FUNCTION(libc_sys_io_destroy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_io_destroy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_io_destroy, libc_sys_io_destroy)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_destroy
INTERN_FUNCTION(libc_sys_Xio_destroy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xio_destroy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xio_destroy, libc_sys_Xio_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_getevents
INTERN_FUNCTION(libc_sys_io_getevents)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_io_getevents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_io_getevents, libc_sys_io_getevents)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_getevents
INTERN_FUNCTION(libc_sys_Xio_getevents)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xio_getevents)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xio_getevents, libc_sys_Xio_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_submit
INTERN_FUNCTION(libc_sys_io_submit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_io_submit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_io_submit, libc_sys_io_submit)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_submit
INTERN_FUNCTION(libc_sys_Xio_submit)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xio_submit)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xio_submit, libc_sys_Xio_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_cancel
INTERN_FUNCTION(libc_sys_io_cancel)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_io_cancel)
DEFINE_PUBLIC_WEAK_ALIAS(sys_io_cancel, libc_sys_io_cancel)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_cancel
INTERN_FUNCTION(libc_sys_Xio_cancel)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xio_cancel)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xio_cancel, libc_sys_Xio_cancel)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_thread_area
INTERN_FUNCTION(libc_sys_get_thread_area)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_get_thread_area)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_thread_area, libc_sys_get_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_thread_area
INTERN_FUNCTION(libc_sys_Xget_thread_area)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xget_thread_area)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_thread_area, libc_sys_Xget_thread_area)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.crt.syscall.lookup_dcookie
INTERN_FUNCTION(libc_sys_lookup_dcookie)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lookup_dcookie)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lookup_dcookie, libc_sys_lookup_dcookie)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xlookup_dcookie
INTERN_FUNCTION(libc_sys_Xlookup_dcookie)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlookup_dcookie)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlookup_dcookie, libc_sys_Xlookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.crt.syscall.epoll_create
INTERN_FUNCTION(libc_sys_epoll_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_create, libc_sys_epoll_create)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.crt.syscall.Xepoll_create
INTERN_FUNCTION(libc_sys_Xepoll_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_create, libc_sys_Xepoll_create)

/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.epoll_ctl_old
INTERN_FUNCTION(libc_sys_epoll_ctl_old)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_ctl_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_ctl_old, libc_sys_epoll_ctl_old)

/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.Xepoll_ctl_old
INTERN_FUNCTION(libc_sys_Xepoll_ctl_old)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_ctl_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_ctl_old, libc_sys_Xepoll_ctl_old)

/* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.epoll_wait_old
INTERN_FUNCTION(libc_sys_epoll_wait_old)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_wait_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_wait_old, libc_sys_epoll_wait_old)

/* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.Xepoll_wait_old
INTERN_FUNCTION(libc_sys_Xepoll_wait_old)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_wait_old)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_wait_old, libc_sys_Xepoll_wait_old)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.crt.syscall.remap_file_pages
INTERN_FUNCTION(libc_sys_remap_file_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_remap_file_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_remap_file_pages, libc_sys_remap_file_pages)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.crt.syscall.Xremap_file_pages
INTERN_FUNCTION(libc_sys_Xremap_file_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xremap_file_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xremap_file_pages, libc_sys_Xremap_file_pages)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.crt.syscall.getdents64
INTERN_FUNCTION(libc_sys_getdents64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getdents64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdents64, libc_sys_getdents64)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.crt.syscall.Xgetdents64
INTERN_FUNCTION(libc_sys_Xgetdents64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetdents64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdents64, libc_sys_Xgetdents64)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.crt.syscall.set_tid_address
INTERN_FUNCTION(libc_sys_set_tid_address)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_tid_address)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_tid_address, libc_sys_set_tid_address)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.crt.syscall.Xset_tid_address
INTERN_FUNCTION(libc_sys_Xset_tid_address)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_tid_address)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_tid_address, libc_sys_Xset_tid_address)

/* errno_t restart_syscall(void) */
.section .text.crt.syscall.restart_syscall
INTERN_FUNCTION(libc_sys_restart_syscall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_restart_syscall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_restart_syscall, libc_sys_restart_syscall)

/* errno_t restart_syscall(void) */
.section .text.crt.syscall.Xrestart_syscall
INTERN_FUNCTION(libc_sys_Xrestart_syscall)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrestart_syscall)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrestart_syscall, libc_sys_Xrestart_syscall)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semtimedop
INTERN_FUNCTION(libc_sys_semtimedop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_semtimedop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_semtimedop, libc_sys_semtimedop)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemtimedop
INTERN_FUNCTION(libc_sys_Xsemtimedop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsemtimedop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsemtimedop, libc_sys_Xsemtimedop)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fadvise64
INTERN_FUNCTION(libc_sys_fadvise64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fadvise64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fadvise64, libc_sys_fadvise64)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfadvise64
INTERN_FUNCTION(libc_sys_Xfadvise64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfadvise64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfadvise64, libc_sys_Xfadvise64)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.crt.syscall.timer_create
INTERN_FUNCTION(libc_sys_timer_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timer_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_create, libc_sys_timer_create)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.crt.syscall.Xtimer_create
INTERN_FUNCTION(libc_sys_Xtimer_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimer_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_create, libc_sys_Xtimer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
.section .text.crt.syscall.timer_settime
INTERN_FUNCTION(libc_sys_timer_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timer_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_settime, libc_sys_timer_settime)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
.section .text.crt.syscall.Xtimer_settime
INTERN_FUNCTION(libc_sys_Xtimer_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimer_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_settime, libc_sys_Xtimer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
.section .text.crt.syscall.timer_gettime
INTERN_FUNCTION(libc_sys_timer_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timer_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_gettime, libc_sys_timer_gettime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
.section .text.crt.syscall.Xtimer_gettime
INTERN_FUNCTION(libc_sys_Xtimer_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimer_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_gettime, libc_sys_Xtimer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.crt.syscall.timer_getoverrun
INTERN_FUNCTION(libc_sys_timer_getoverrun)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timer_getoverrun)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_getoverrun, libc_sys_timer_getoverrun)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.crt.syscall.Xtimer_getoverrun
INTERN_FUNCTION(libc_sys_Xtimer_getoverrun)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimer_getoverrun)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_getoverrun, libc_sys_Xtimer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.crt.syscall.timer_delete
INTERN_FUNCTION(libc_sys_timer_delete)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timer_delete)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timer_delete, libc_sys_timer_delete)

/* errno_t timer_delete(timer_t timerid) */
.section .text.crt.syscall.Xtimer_delete
INTERN_FUNCTION(libc_sys_Xtimer_delete)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimer_delete)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimer_delete, libc_sys_Xtimer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
.section .text.crt.syscall.clock_settime
INTERN_FUNCTION(libc_sys_clock_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clock_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_settime, libc_sys_clock_settime)

/* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
.section .text.crt.syscall.Xclock_settime
INTERN_FUNCTION(libc_sys_Xclock_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclock_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_settime, libc_sys_Xclock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
.section .text.crt.syscall.clock_gettime
INTERN_FUNCTION(libc_sys_clock_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clock_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_gettime, libc_sys_clock_gettime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
.section .text.crt.syscall.Xclock_gettime
INTERN_FUNCTION(libc_sys_Xclock_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclock_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_gettime, libc_sys_Xclock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
.section .text.crt.syscall.clock_getres
INTERN_FUNCTION(libc_sys_clock_getres)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clock_getres)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_getres, libc_sys_clock_getres)

/* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
.section .text.crt.syscall.Xclock_getres
INTERN_FUNCTION(libc_sys_Xclock_getres)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclock_getres)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_getres, libc_sys_Xclock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
.section .text.crt.syscall.clock_nanosleep
INTERN_FUNCTION(libc_sys_clock_nanosleep)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clock_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_nanosleep, libc_sys_clock_nanosleep)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
.section .text.crt.syscall.Xclock_nanosleep
INTERN_FUNCTION(libc_sys_Xclock_nanosleep)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclock_nanosleep)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_nanosleep, libc_sys_Xclock_nanosleep)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.crt.syscall.exit_group
INTERN_FUNCTION(libc_sys_exit_group)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_exit_group)
DEFINE_PUBLIC_WEAK_ALIAS(sys_exit_group, libc_sys_exit_group)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.crt.syscall.Xexit_group
INTERN_FUNCTION(libc_sys_Xexit_group)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xexit_group)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexit_group, libc_sys_Xexit_group)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.epoll_wait
INTERN_FUNCTION(libc_sys_epoll_wait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_wait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_wait, libc_sys_epoll_wait)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.Xepoll_wait
INTERN_FUNCTION(libc_sys_Xepoll_wait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_wait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_wait, libc_sys_Xepoll_wait)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.epoll_ctl
INTERN_FUNCTION(libc_sys_epoll_ctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_ctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_ctl, libc_sys_epoll_ctl)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.Xepoll_ctl
INTERN_FUNCTION(libc_sys_Xepoll_ctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_ctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_ctl, libc_sys_Xepoll_ctl)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.crt.syscall.tgkill
INTERN_FUNCTION(libc_sys_tgkill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_tgkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tgkill, libc_sys_tgkill)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.crt.syscall.Xtgkill
INTERN_FUNCTION(libc_sys_Xtgkill)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtgkill)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtgkill, libc_sys_Xtgkill)

/* errno_t utimes(char const *filename, struct __timeval32 const[2] times) */
.section .text.crt.syscall.utimes
INTERN_FUNCTION(libc_sys_utimes)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_utimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utimes, libc_sys_utimes)

/* errno_t utimes(char const *filename, struct __timeval32 const[2] times) */
.section .text.crt.syscall.Xutimes
INTERN_FUNCTION(libc_sys_Xutimes)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xutimes)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutimes, libc_sys_Xutimes)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.crt.syscall.vserver
INTERN_FUNCTION(libc_sys_vserver)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_vserver)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vserver, libc_sys_vserver)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xvserver
INTERN_FUNCTION(libc_sys_Xvserver)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xvserver)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvserver, libc_sys_Xvserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mbind
INTERN_FUNCTION(libc_sys_mbind)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mbind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mbind, libc_sys_mbind)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmbind
INTERN_FUNCTION(libc_sys_Xmbind)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmbind)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmbind, libc_sys_Xmbind)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_mempolicy
INTERN_FUNCTION(libc_sys_set_mempolicy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_mempolicy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_mempolicy, libc_sys_set_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_mempolicy
INTERN_FUNCTION(libc_sys_Xset_mempolicy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_mempolicy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_mempolicy, libc_sys_Xset_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_mempolicy
INTERN_FUNCTION(libc_sys_get_mempolicy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_get_mempolicy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_mempolicy, libc_sys_get_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_mempolicy
INTERN_FUNCTION(libc_sys_Xget_mempolicy)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xget_mempolicy)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_mempolicy, libc_sys_Xget_mempolicy)

/* errno_t mq_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_open
INTERN_FUNCTION(libc_sys_mq_open)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_open, libc_sys_mq_open)

/* errno_t mq_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_open
INTERN_FUNCTION(libc_sys_Xmq_open)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_open, libc_sys_Xmq_open)

/* errno_t mq_unlink(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_unlink
INTERN_FUNCTION(libc_sys_mq_unlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_unlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_unlink, libc_sys_mq_unlink)

/* errno_t mq_unlink(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_unlink
INTERN_FUNCTION(libc_sys_Xmq_unlink)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_unlink)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_unlink, libc_sys_Xmq_unlink)

/* errno_t mq_timedsend(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_timedsend
INTERN_FUNCTION(libc_sys_mq_timedsend)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_timedsend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_timedsend, libc_sys_mq_timedsend)

/* errno_t mq_timedsend(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_timedsend
INTERN_FUNCTION(libc_sys_Xmq_timedsend)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_timedsend)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_timedsend, libc_sys_Xmq_timedsend)

/* errno_t mq_timedreceive(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_timedreceive
INTERN_FUNCTION(libc_sys_mq_timedreceive)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_timedreceive)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_timedreceive, libc_sys_mq_timedreceive)

/* errno_t mq_timedreceive(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_timedreceive
INTERN_FUNCTION(libc_sys_Xmq_timedreceive)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_timedreceive)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_timedreceive, libc_sys_Xmq_timedreceive)

/* errno_t mq_notify(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_notify
INTERN_FUNCTION(libc_sys_mq_notify)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_notify)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_notify, libc_sys_mq_notify)

/* errno_t mq_notify(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_notify
INTERN_FUNCTION(libc_sys_Xmq_notify)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_notify)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_notify, libc_sys_Xmq_notify)

/* errno_t mq_getsetattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mq_getsetattr
INTERN_FUNCTION(libc_sys_mq_getsetattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mq_getsetattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mq_getsetattr, libc_sys_mq_getsetattr)

/* errno_t mq_getsetattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmq_getsetattr
INTERN_FUNCTION(libc_sys_Xmq_getsetattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmq_getsetattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmq_getsetattr, libc_sys_Xmq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.kexec_load
INTERN_FUNCTION(libc_sys_kexec_load)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kexec_load)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kexec_load, libc_sys_kexec_load)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkexec_load
INTERN_FUNCTION(libc_sys_Xkexec_load)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkexec_load)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkexec_load, libc_sys_Xkexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
.section .text.crt.syscall.waitid
INTERN_FUNCTION(libc_sys_waitid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_waitid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_waitid, libc_sys_waitid)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
.section .text.crt.syscall.Xwaitid
INTERN_FUNCTION(libc_sys_Xwaitid)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwaitid)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwaitid, libc_sys_Xwaitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.add_key
INTERN_FUNCTION(libc_sys_add_key)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_add_key)
DEFINE_PUBLIC_WEAK_ALIAS(sys_add_key, libc_sys_add_key)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xadd_key
INTERN_FUNCTION(libc_sys_Xadd_key)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xadd_key)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xadd_key, libc_sys_Xadd_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.request_key
INTERN_FUNCTION(libc_sys_request_key)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_request_key)
DEFINE_PUBLIC_WEAK_ALIAS(sys_request_key, libc_sys_request_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xrequest_key
INTERN_FUNCTION(libc_sys_Xrequest_key)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrequest_key)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrequest_key, libc_sys_Xrequest_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.keyctl
INTERN_FUNCTION(libc_sys_keyctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_keyctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_keyctl, libc_sys_keyctl)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkeyctl
INTERN_FUNCTION(libc_sys_Xkeyctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkeyctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkeyctl, libc_sys_Xkeyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.crt.syscall.ioprio_set
INTERN_FUNCTION(libc_sys_ioprio_set)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ioprio_set)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioprio_set, libc_sys_ioprio_set)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.crt.syscall.Xioprio_set
INTERN_FUNCTION(libc_sys_Xioprio_set)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xioprio_set)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioprio_set, libc_sys_Xioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.crt.syscall.ioprio_get
INTERN_FUNCTION(libc_sys_ioprio_get)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ioprio_get)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioprio_get, libc_sys_ioprio_get)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.crt.syscall.Xioprio_get
INTERN_FUNCTION(libc_sys_Xioprio_get)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xioprio_get)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioprio_get, libc_sys_Xioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_init
INTERN_FUNCTION(libc_sys_inotify_init)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_inotify_init)
DEFINE_PUBLIC_WEAK_ALIAS(sys_inotify_init, libc_sys_inotify_init)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_init
INTERN_FUNCTION(libc_sys_Xinotify_init)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xinotify_init)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xinotify_init, libc_sys_Xinotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_add_watch
INTERN_FUNCTION(libc_sys_inotify_add_watch)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_inotify_add_watch)
DEFINE_PUBLIC_WEAK_ALIAS(sys_inotify_add_watch, libc_sys_inotify_add_watch)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_add_watch
INTERN_FUNCTION(libc_sys_Xinotify_add_watch)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xinotify_add_watch)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xinotify_add_watch, libc_sys_Xinotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_rm_watch
INTERN_FUNCTION(libc_sys_inotify_rm_watch)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_inotify_rm_watch)
DEFINE_PUBLIC_WEAK_ALIAS(sys_inotify_rm_watch, libc_sys_inotify_rm_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_rm_watch
INTERN_FUNCTION(libc_sys_Xinotify_rm_watch)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xinotify_rm_watch)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xinotify_rm_watch, libc_sys_Xinotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.migrate_pages
INTERN_FUNCTION(libc_sys_migrate_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_migrate_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_migrate_pages, libc_sys_migrate_pages)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmigrate_pages
INTERN_FUNCTION(libc_sys_Xmigrate_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmigrate_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmigrate_pages, libc_sys_Xmigrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.openat
INTERN_FUNCTION(libc_sys_openat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_openat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_openat, libc_sys_openat)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.Xopenat
INTERN_FUNCTION(libc_sys_Xopenat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xopenat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopenat, libc_sys_Xopenat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.crt.syscall.mkdirat
INTERN_FUNCTION(libc_sys_mkdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mkdirat, libc_sys_mkdirat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.crt.syscall.Xmkdirat
INTERN_FUNCTION(libc_sys_Xmkdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmkdirat, libc_sys_Xmkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.mknodat
INTERN_FUNCTION(libc_sys_mknodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mknodat, libc_sys_mknodat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.Xmknodat
INTERN_FUNCTION(libc_sys_Xmknodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmknodat, libc_sys_Xmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.crt.syscall.fchownat
INTERN_FUNCTION(libc_sys_fchownat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchownat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchownat, libc_sys_fchownat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.crt.syscall.Xfchownat
INTERN_FUNCTION(libc_sys_Xfchownat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchownat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchownat, libc_sys_Xfchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timeval32 const[2] times) */
.section .text.crt.syscall.futimesat
INTERN_FUNCTION(libc_sys_futimesat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_futimesat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_futimesat, libc_sys_futimesat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timeval32 const[2] times) */
.section .text.crt.syscall.Xfutimesat
INTERN_FUNCTION(libc_sys_Xfutimesat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfutimesat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfutimesat, libc_sys_Xfutimesat)

/* errno_t linux_fstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
.section .text.crt.syscall.linux_fstatat
INTERN_FUNCTION(libc_sys_linux_fstatat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_linux_fstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linux_fstatat, libc_sys_linux_fstatat)

/* errno_t linux_fstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
.section .text.crt.syscall.Xlinux_fstatat
INTERN_FUNCTION(libc_sys_Xlinux_fstatat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlinux_fstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinux_fstatat, libc_sys_Xlinux_fstatat)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.crt.syscall.unlinkat
INTERN_FUNCTION(libc_sys_unlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_unlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unlinkat, libc_sys_unlinkat)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.crt.syscall.Xunlinkat
INTERN_FUNCTION(libc_sys_Xunlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xunlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunlinkat, libc_sys_Xunlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.crt.syscall.renameat
INTERN_FUNCTION(libc_sys_renameat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_renameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_renameat, libc_sys_renameat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.crt.syscall.Xrenameat
INTERN_FUNCTION(libc_sys_Xrenameat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrenameat, libc_sys_Xrenameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.linkat
INTERN_FUNCTION(libc_sys_linkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_linkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_linkat, libc_sys_linkat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.Xlinkat
INTERN_FUNCTION(libc_sys_Xlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlinkat, libc_sys_Xlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.crt.syscall.symlinkat
INTERN_FUNCTION(libc_sys_symlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_symlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_symlinkat, libc_sys_symlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.crt.syscall.Xsymlinkat
INTERN_FUNCTION(libc_sys_Xsymlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsymlinkat, libc_sys_Xsymlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.readlinkat
INTERN_FUNCTION(libc_sys_readlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readlinkat, libc_sys_readlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.Xreadlinkat
INTERN_FUNCTION(libc_sys_Xreadlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadlinkat, libc_sys_Xreadlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.fchmodat
INTERN_FUNCTION(libc_sys_fchmodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchmodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchmodat, libc_sys_fchmodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.Xfchmodat
INTERN_FUNCTION(libc_sys_Xfchmodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchmodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchmodat, libc_sys_Xfchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.crt.syscall.faccessat
INTERN_FUNCTION(libc_sys_faccessat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_faccessat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_faccessat, libc_sys_faccessat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.crt.syscall.Xfaccessat
INTERN_FUNCTION(libc_sys_Xfaccessat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfaccessat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfaccessat, libc_sys_Xfaccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.crt.syscall.pselect6
INTERN_FUNCTION(libc_sys_pselect6)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pselect6)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pselect6, libc_sys_pselect6)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.crt.syscall.Xpselect6
INTERN_FUNCTION(libc_sys_Xpselect6)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpselect6)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpselect6, libc_sys_Xpselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.ppoll
INTERN_FUNCTION(libc_sys_ppoll)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ppoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ppoll, libc_sys_ppoll)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.Xppoll
INTERN_FUNCTION(libc_sys_Xppoll)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xppoll)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xppoll, libc_sys_Xppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.crt.syscall.unshare
INTERN_FUNCTION(libc_sys_unshare)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_unshare)
DEFINE_PUBLIC_WEAK_ALIAS(sys_unshare, libc_sys_unshare)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.crt.syscall.Xunshare
INTERN_FUNCTION(libc_sys_Xunshare)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xunshare)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xunshare, libc_sys_Xunshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_robust_list
INTERN_FUNCTION(libc_sys_set_robust_list)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_robust_list)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_robust_list, libc_sys_set_robust_list)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_robust_list
INTERN_FUNCTION(libc_sys_Xset_robust_list)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_robust_list)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_robust_list, libc_sys_Xset_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_robust_list
INTERN_FUNCTION(libc_sys_get_robust_list)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_get_robust_list)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_robust_list, libc_sys_get_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_robust_list
INTERN_FUNCTION(libc_sys_Xget_robust_list)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xget_robust_list)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_robust_list, libc_sys_Xget_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.splice
INTERN_FUNCTION(libc_sys_splice)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_splice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_splice, libc_sys_splice)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsplice
INTERN_FUNCTION(libc_sys_Xsplice)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsplice, libc_sys_Xsplice)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.tee
INTERN_FUNCTION(libc_sys_tee)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_tee)
DEFINE_PUBLIC_WEAK_ALIAS(sys_tee, libc_sys_tee)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.Xtee
INTERN_FUNCTION(libc_sys_Xtee)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtee)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtee, libc_sys_Xtee)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.sync_file_range
INTERN_FUNCTION(libc_sys_sync_file_range)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sync_file_range)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sync_file_range, libc_sys_sync_file_range)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsync_file_range
INTERN_FUNCTION(libc_sys_Xsync_file_range)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsync_file_range)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsync_file_range, libc_sys_Xsync_file_range)

/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.vmsplice
INTERN_FUNCTION(libc_sys_vmsplice)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_vmsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_vmsplice, libc_sys_vmsplice)

/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.Xvmsplice
INTERN_FUNCTION(libc_sys_Xvmsplice)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xvmsplice)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xvmsplice, libc_sys_Xvmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.move_pages
INTERN_FUNCTION(libc_sys_move_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_move_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_move_pages, libc_sys_move_pages)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmove_pages
INTERN_FUNCTION(libc_sys_Xmove_pages)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmove_pages)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmove_pages, libc_sys_Xmove_pages)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespec32 const[2] times, atflag_t flags) */
.section .text.crt.syscall.utimensat
INTERN_FUNCTION(libc_sys_utimensat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_utimensat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_utimensat, libc_sys_utimensat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespec32 const[2] times, atflag_t flags) */
.section .text.crt.syscall.Xutimensat
INTERN_FUNCTION(libc_sys_Xutimensat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xutimensat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xutimensat, libc_sys_Xutimensat)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.crt.syscall.epoll_pwait
INTERN_FUNCTION(libc_sys_epoll_pwait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_pwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_pwait, libc_sys_epoll_pwait)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.crt.syscall.Xepoll_pwait
INTERN_FUNCTION(libc_sys_Xepoll_pwait)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_pwait)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_pwait, libc_sys_Xepoll_pwait)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.signalfd
INTERN_FUNCTION(libc_sys_signalfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_signalfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_signalfd, libc_sys_signalfd)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.Xsignalfd
INTERN_FUNCTION(libc_sys_Xsignalfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsignalfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsignalfd, libc_sys_Xsignalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.crt.syscall.timerfd_create
INTERN_FUNCTION(libc_sys_timerfd_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timerfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_create, libc_sys_timerfd_create)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.crt.syscall.Xtimerfd_create
INTERN_FUNCTION(libc_sys_Xtimerfd_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimerfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_create, libc_sys_Xtimerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.crt.syscall.eventfd
INTERN_FUNCTION(libc_sys_eventfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_eventfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_eventfd, libc_sys_eventfd)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.crt.syscall.Xeventfd
INTERN_FUNCTION(libc_sys_Xeventfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xeventfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xeventfd, libc_sys_Xeventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.crt.syscall.fallocate
INTERN_FUNCTION(libc_sys_fallocate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fallocate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fallocate, libc_sys_fallocate)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.crt.syscall.Xfallocate
INTERN_FUNCTION(libc_sys_Xfallocate)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfallocate)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfallocate, libc_sys_Xfallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
.section .text.crt.syscall.timerfd_settime
INTERN_FUNCTION(libc_sys_timerfd_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timerfd_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_settime, libc_sys_timerfd_settime)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
.section .text.crt.syscall.Xtimerfd_settime
INTERN_FUNCTION(libc_sys_Xtimerfd_settime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimerfd_settime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_settime, libc_sys_Xtimerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
.section .text.crt.syscall.timerfd_gettime
INTERN_FUNCTION(libc_sys_timerfd_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_timerfd_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_timerfd_gettime, libc_sys_timerfd_gettime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
.section .text.crt.syscall.Xtimerfd_gettime
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xtimerfd_gettime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xtimerfd_gettime, libc_sys_Xtimerfd_gettime)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.crt.syscall.accept4
INTERN_FUNCTION(libc_sys_accept4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_accept4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_accept4, libc_sys_accept4)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.crt.syscall.Xaccept4
INTERN_FUNCTION(libc_sys_Xaccept4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xaccept4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xaccept4, libc_sys_Xaccept4)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.crt.syscall.signalfd4
INTERN_FUNCTION(libc_sys_signalfd4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_signalfd4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_signalfd4, libc_sys_signalfd4)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsignalfd4
INTERN_FUNCTION(libc_sys_Xsignalfd4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsignalfd4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsignalfd4, libc_sys_Xsignalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.crt.syscall.eventfd2
INTERN_FUNCTION(libc_sys_eventfd2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_eventfd2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_eventfd2, libc_sys_eventfd2)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.crt.syscall.Xeventfd2
INTERN_FUNCTION(libc_sys_Xeventfd2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xeventfd2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xeventfd2, libc_sys_Xeventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.crt.syscall.epoll_create1
INTERN_FUNCTION(libc_sys_epoll_create1)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_epoll_create1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_epoll_create1, libc_sys_epoll_create1)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.crt.syscall.Xepoll_create1
INTERN_FUNCTION(libc_sys_Xepoll_create1)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xepoll_create1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xepoll_create1, libc_sys_Xepoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.crt.syscall.dup3
INTERN_FUNCTION(libc_sys_dup3)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_dup3)
DEFINE_PUBLIC_WEAK_ALIAS(sys_dup3, libc_sys_dup3)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.crt.syscall.Xdup3
INTERN_FUNCTION(libc_sys_Xdup3)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdup3)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdup3, libc_sys_Xdup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.crt.syscall.pipe2
INTERN_FUNCTION(libc_sys_pipe2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pipe2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pipe2, libc_sys_pipe2)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.crt.syscall.Xpipe2
INTERN_FUNCTION(libc_sys_Xpipe2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpipe2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpipe2, libc_sys_Xpipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_init1
INTERN_FUNCTION(libc_sys_inotify_init1)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_inotify_init1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_inotify_init1, libc_sys_inotify_init1)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_init1
INTERN_FUNCTION(libc_sys_Xinotify_init1)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xinotify_init1)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xinotify_init1, libc_sys_Xinotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.preadv
INTERN_FUNCTION(libc_sys_preadv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_preadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_preadv, libc_sys_preadv)

/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.Xpreadv
INTERN_FUNCTION(libc_sys_Xpreadv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpreadv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpreadv, libc_sys_Xpreadv)

/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.pwritev
INTERN_FUNCTION(libc_sys_pwritev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwritev, libc_sys_pwritev)

/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.Xpwritev
INTERN_FUNCTION(libc_sys_Xpwritev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpwritev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwritev, libc_sys_Xpwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.crt.syscall.rt_tgsigqueueinfo
INTERN_FUNCTION(libc_sys_rt_tgsigqueueinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rt_tgsigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rt_tgsigqueueinfo, libc_sys_rt_tgsigqueueinfo)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.crt.syscall.Xrt_tgsigqueueinfo
INTERN_FUNCTION(libc_sys_Xrt_tgsigqueueinfo)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrt_tgsigqueueinfo)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrt_tgsigqueueinfo, libc_sys_Xrt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.perf_event_open
INTERN_FUNCTION(libc_sys_perf_event_open)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_perf_event_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_perf_event_open, libc_sys_perf_event_open)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xperf_event_open
INTERN_FUNCTION(libc_sys_Xperf_event_open)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xperf_event_open)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xperf_event_open, libc_sys_Xperf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
.section .text.crt.syscall.recvmmsg
INTERN_FUNCTION(libc_sys_recvmmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_recvmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_recvmmsg, libc_sys_recvmmsg)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
.section .text.crt.syscall.Xrecvmmsg
INTERN_FUNCTION(libc_sys_Xrecvmmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrecvmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrecvmmsg, libc_sys_Xrecvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fanotify_init
INTERN_FUNCTION(libc_sys_fanotify_init)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fanotify_init)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fanotify_init, libc_sys_fanotify_init)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfanotify_init
INTERN_FUNCTION(libc_sys_Xfanotify_init)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfanotify_init)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfanotify_init, libc_sys_Xfanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fanotify_mark
INTERN_FUNCTION(libc_sys_fanotify_mark)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fanotify_mark)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fanotify_mark, libc_sys_fanotify_mark)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfanotify_mark
INTERN_FUNCTION(libc_sys_Xfanotify_mark)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfanotify_mark)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfanotify_mark, libc_sys_Xfanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.crt.syscall.prlimit64
INTERN_FUNCTION(libc_sys_prlimit64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_prlimit64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_prlimit64, libc_sys_prlimit64)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.crt.syscall.Xprlimit64
INTERN_FUNCTION(libc_sys_Xprlimit64)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xprlimit64)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprlimit64, libc_sys_Xprlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.crt.syscall.name_to_handle_at
INTERN_FUNCTION(libc_sys_name_to_handle_at)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_name_to_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_name_to_handle_at, libc_sys_name_to_handle_at)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.crt.syscall.Xname_to_handle_at
INTERN_FUNCTION(libc_sys_Xname_to_handle_at)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xname_to_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xname_to_handle_at, libc_sys_Xname_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.crt.syscall.open_by_handle_at
INTERN_FUNCTION(libc_sys_open_by_handle_at)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_open_by_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_open_by_handle_at, libc_sys_open_by_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.crt.syscall.Xopen_by_handle_at
INTERN_FUNCTION(libc_sys_Xopen_by_handle_at)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xopen_by_handle_at)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopen_by_handle_at, libc_sys_Xopen_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.crt.syscall.clock_adjtime
INTERN_FUNCTION(libc_sys_clock_adjtime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_clock_adjtime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_clock_adjtime, libc_sys_clock_adjtime)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xclock_adjtime
INTERN_FUNCTION(libc_sys_Xclock_adjtime)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xclock_adjtime)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xclock_adjtime, libc_sys_Xclock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.crt.syscall.syncfs
INTERN_FUNCTION(libc_sys_syncfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_syncfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_syncfs, libc_sys_syncfs)

/* errno_t syncfs(fd_t fd) */
.section .text.crt.syscall.Xsyncfs
INTERN_FUNCTION(libc_sys_Xsyncfs)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsyncfs)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsyncfs, libc_sys_Xsyncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.crt.syscall.sendmmsg
INTERN_FUNCTION(libc_sys_sendmmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sendmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sendmmsg, libc_sys_sendmmsg)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsendmmsg
INTERN_FUNCTION(libc_sys_Xsendmmsg)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsendmmsg)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsendmmsg, libc_sys_Xsendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.crt.syscall.setns
INTERN_FUNCTION(libc_sys_setns)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_setns)
DEFINE_PUBLIC_WEAK_ALIAS(sys_setns, libc_sys_setns)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.crt.syscall.Xsetns
INTERN_FUNCTION(libc_sys_Xsetns)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsetns)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsetns, libc_sys_Xsetns)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.crt.syscall.getcpu
INTERN_FUNCTION(libc_sys_getcpu)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getcpu)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getcpu, libc_sys_getcpu)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.crt.syscall.Xgetcpu
INTERN_FUNCTION(libc_sys_Xgetcpu)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetcpu)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetcpu, libc_sys_Xgetcpu)

/* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.process_vm_readv
INTERN_FUNCTION(libc_sys_process_vm_readv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_process_vm_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_process_vm_readv, libc_sys_process_vm_readv)

/* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.Xprocess_vm_readv
INTERN_FUNCTION(libc_sys_Xprocess_vm_readv)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xprocess_vm_readv)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprocess_vm_readv, libc_sys_Xprocess_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.process_vm_writev
INTERN_FUNCTION(libc_sys_process_vm_writev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_process_vm_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_process_vm_writev, libc_sys_process_vm_writev)

/* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.Xprocess_vm_writev
INTERN_FUNCTION(libc_sys_Xprocess_vm_writev)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xprocess_vm_writev)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xprocess_vm_writev, libc_sys_Xprocess_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.crt.syscall.kcmp
INTERN_FUNCTION(libc_sys_kcmp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kcmp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kcmp, libc_sys_kcmp)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.crt.syscall.Xkcmp
INTERN_FUNCTION(libc_sys_Xkcmp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkcmp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkcmp, libc_sys_Xkcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.finit_module
INTERN_FUNCTION(libc_sys_finit_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_finit_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_finit_module, libc_sys_finit_module)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfinit_module
INTERN_FUNCTION(libc_sys_Xfinit_module)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfinit_module)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfinit_module, libc_sys_Xfinit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sched_setattr
INTERN_FUNCTION(libc_sys_sched_setattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_setattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_setattr, libc_sys_sched_setattr)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsched_setattr
INTERN_FUNCTION(libc_sys_Xsched_setattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_setattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_setattr, libc_sys_Xsched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sched_getattr
INTERN_FUNCTION(libc_sys_sched_getattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sched_getattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sched_getattr, libc_sys_sched_getattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsched_getattr
INTERN_FUNCTION(libc_sys_Xsched_getattr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsched_getattr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsched_getattr, libc_sys_Xsched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.crt.syscall.renameat2
INTERN_FUNCTION(libc_sys_renameat2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_renameat2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_renameat2, libc_sys_renameat2)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.crt.syscall.Xrenameat2
INTERN_FUNCTION(libc_sys_Xrenameat2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrenameat2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrenameat2, libc_sys_Xrenameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.crt.syscall.seccomp
INTERN_FUNCTION(libc_sys_seccomp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_seccomp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_seccomp, libc_sys_seccomp)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xseccomp
INTERN_FUNCTION(libc_sys_Xseccomp)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xseccomp)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xseccomp, libc_sys_Xseccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.crt.syscall.getrandom
INTERN_FUNCTION(libc_sys_getrandom)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getrandom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getrandom, libc_sys_getrandom)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xgetrandom
INTERN_FUNCTION(libc_sys_Xgetrandom)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetrandom)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetrandom, libc_sys_Xgetrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.crt.syscall.memfd_create
INTERN_FUNCTION(libc_sys_memfd_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_memfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_memfd_create, libc_sys_memfd_create)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmemfd_create
INTERN_FUNCTION(libc_sys_Xmemfd_create)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmemfd_create)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmemfd_create, libc_sys_Xmemfd_create)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.kexec_file_load
INTERN_FUNCTION(libc_sys_kexec_file_load)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kexec_file_load)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kexec_file_load, libc_sys_kexec_file_load)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkexec_file_load
INTERN_FUNCTION(libc_sys_Xkexec_file_load)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkexec_file_load)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkexec_file_load, libc_sys_Xkexec_file_load)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.crt.syscall.bpf
INTERN_FUNCTION(libc_sys_bpf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_bpf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_bpf, libc_sys_bpf)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xbpf
INTERN_FUNCTION(libc_sys_Xbpf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xbpf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xbpf, libc_sys_Xbpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.crt.syscall.execveat
INTERN_FUNCTION(libc_sys_execveat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_execveat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_execveat, libc_sys_execveat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.crt.syscall.Xexecveat
INTERN_FUNCTION(libc_sys_Xexecveat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xexecveat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xexecveat, libc_sys_Xexecveat)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.userfaultfd
INTERN_FUNCTION(libc_sys_userfaultfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_userfaultfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_userfaultfd, libc_sys_userfaultfd)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xuserfaultfd
INTERN_FUNCTION(libc_sys_Xuserfaultfd)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xuserfaultfd)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xuserfaultfd, libc_sys_Xuserfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.crt.syscall.membarrier
INTERN_FUNCTION(libc_sys_membarrier)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_membarrier)
DEFINE_PUBLIC_WEAK_ALIAS(sys_membarrier, libc_sys_membarrier)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmembarrier
INTERN_FUNCTION(libc_sys_Xmembarrier)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmembarrier)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmembarrier, libc_sys_Xmembarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mlock2
INTERN_FUNCTION(libc_sys_mlock2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mlock2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mlock2, libc_sys_mlock2)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmlock2
INTERN_FUNCTION(libc_sys_Xmlock2)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmlock2)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmlock2, libc_sys_Xmlock2)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.readf
INTERN_FUNCTION(libc_sys_readf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readf, libc_sys_readf)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.Xreadf
INTERN_FUNCTION(libc_sys_Xreadf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadf, libc_sys_Xreadf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.writef
INTERN_FUNCTION(libc_sys_writef)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_writef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writef, libc_sys_writef)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.Xwritef
INTERN_FUNCTION(libc_sys_Xwritef)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwritef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritef, libc_sys_Xwritef)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.hop
INTERN_FUNCTION(libc_sys_hop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_hop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_hop, libc_sys_hop)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xhop
INTERN_FUNCTION(libc_sys_Xhop)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xhop)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xhop, libc_sys_Xhop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.hopf
INTERN_FUNCTION(libc_sys_hopf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_hopf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_hopf, libc_sys_hopf)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.Xhopf
INTERN_FUNCTION(libc_sys_Xhopf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xhopf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xhopf, libc_sys_Xhopf)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.crt.syscall.kstat
INTERN_FUNCTION(libc_sys_kstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kstat, libc_sys_kstat)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.crt.syscall.Xkstat
INTERN_FUNCTION(libc_sys_Xkstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkstat, libc_sys_Xkstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.crt.syscall.kfstat
INTERN_FUNCTION(libc_sys_kfstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kfstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kfstat, libc_sys_kfstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.crt.syscall.Xkfstat
INTERN_FUNCTION(libc_sys_Xkfstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkfstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkfstat, libc_sys_Xkfstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.crt.syscall.klstat
INTERN_FUNCTION(libc_sys_klstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_klstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_klstat, libc_sys_klstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.crt.syscall.Xklstat
INTERN_FUNCTION(libc_sys_Xklstat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xklstat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xklstat, libc_sys_Xklstat)

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
/* errno_t detach(pid_t pid) */
.section .text.crt.syscall.detach
INTERN_FUNCTION(libc_sys_detach)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_detach)
DEFINE_PUBLIC_WEAK_ALIAS(sys_detach, libc_sys_detach)

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
/* errno_t detach(pid_t pid) */
.section .text.crt.syscall.Xdetach
INTERN_FUNCTION(libc_sys_Xdetach)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdetach)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdetach, libc_sys_Xdetach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.crt.syscall.getdrives
INTERN_FUNCTION(libc_sys_getdrives)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_getdrives)
DEFINE_PUBLIC_WEAK_ALIAS(sys_getdrives, libc_sys_getdrives)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.crt.syscall.Xgetdrives
INTERN_FUNCTION(libc_sys_Xgetdrives)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xgetdrives)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xgetdrives, libc_sys_Xgetdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.frealpath4
INTERN_FUNCTION(libc_sys_frealpath4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_frealpath4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frealpath4, libc_sys_frealpath4)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.Xfrealpath4
INTERN_FUNCTION(libc_sys_Xfrealpath4)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfrealpath4)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrealpath4, libc_sys_Xfrealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.frealpathat
INTERN_FUNCTION(libc_sys_frealpathat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_frealpathat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frealpathat, libc_sys_frealpathat)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.Xfrealpathat
INTERN_FUNCTION(libc_sys_Xfrealpathat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfrealpathat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrealpathat, libc_sys_Xfrealpathat)

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
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
.section .text.crt.syscall.rpc_schedule
INTERN_FUNCTION(libc_sys_rpc_schedule)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rpc_schedule)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rpc_schedule, libc_sys_rpc_schedule)

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
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
.section .text.crt.syscall.Xrpc_schedule
INTERN_FUNCTION(libc_sys_Xrpc_schedule)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrpc_schedule)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrpc_schedule, libc_sys_Xrpc_schedule)

/* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.sysctl
INTERN_FUNCTION(libc_sys_sysctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_sysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_sysctl, libc_sys_sysctl)

/* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xsysctl
INTERN_FUNCTION(libc_sys_Xsysctl)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xsysctl)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xsysctl, libc_sys_Xsysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.crt.syscall.openpty
INTERN_FUNCTION(libc_sys_openpty)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_openpty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_openpty, libc_sys_openpty)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.crt.syscall.Xopenpty
INTERN_FUNCTION(libc_sys_Xopenpty)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xopenpty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xopenpty, libc_sys_Xopenpty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.crt.syscall.set_exception_handler
INTERN_FUNCTION(libc_sys_set_exception_handler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_exception_handler, libc_sys_set_exception_handler)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.crt.syscall.Xset_exception_handler
INTERN_FUNCTION(libc_sys_Xset_exception_handler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_exception_handler, libc_sys_Xset_exception_handler)

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
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
.section .text.crt.syscall.get_exception_handler
INTERN_FUNCTION(libc_sys_get_exception_handler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_get_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_get_exception_handler, libc_sys_get_exception_handler)

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
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
.section .text.crt.syscall.Xget_exception_handler
INTERN_FUNCTION(libc_sys_Xget_exception_handler)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xget_exception_handler)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xget_exception_handler, libc_sys_Xget_exception_handler)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.ioctlf
INTERN_FUNCTION(libc_sys_ioctlf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_ioctlf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_ioctlf, libc_sys_ioctlf)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.Xioctlf
INTERN_FUNCTION(libc_sys_Xioctlf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xioctlf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xioctlf, libc_sys_Xioctlf)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pread64f
INTERN_FUNCTION(libc_sys_pread64f)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pread64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pread64f, libc_sys_pread64f)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpread64f
INTERN_FUNCTION(libc_sys_Xpread64f)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpread64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpread64f, libc_sys_Xpread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pwrite64f
INTERN_FUNCTION(libc_sys_pwrite64f)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pwrite64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwrite64f, libc_sys_pwrite64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpwrite64f
INTERN_FUNCTION(libc_sys_Xpwrite64f)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpwrite64f)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwrite64f, libc_sys_Xpwrite64f)

/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.readvf
INTERN_FUNCTION(libc_sys_readvf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_readvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_readvf, libc_sys_readvf)

/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.Xreadvf
INTERN_FUNCTION(libc_sys_Xreadvf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xreadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xreadvf, libc_sys_Xreadvf)

/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.writevf
INTERN_FUNCTION(libc_sys_writevf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_writevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_writevf, libc_sys_writevf)

/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.Xwritevf
INTERN_FUNCTION(libc_sys_Xwritevf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xwritevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xwritevf, libc_sys_Xwritevf)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
.section .text.crt.syscall.set_library_listdef
INTERN_FUNCTION(libc_sys_set_library_listdef)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_set_library_listdef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_set_library_listdef, libc_sys_set_library_listdef)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
.section .text.crt.syscall.Xset_library_listdef
INTERN_FUNCTION(libc_sys_Xset_library_listdef)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xset_library_listdef)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xset_library_listdef, libc_sys_Xset_library_listdef)

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
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
.section .text.crt.syscall.debugtrap
INTERN_FUNCTION(libc_sys_debugtrap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_debugtrap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_debugtrap, libc_sys_debugtrap)

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
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
.section .text.crt.syscall.Xdebugtrap
INTERN_FUNCTION(libc_sys_Xdebugtrap)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xdebugtrap)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xdebugtrap, libc_sys_Xdebugtrap)

/* syscall_slong_t rpc_service(void) */
.section .text.crt.syscall.rpc_service
INTERN_FUNCTION(libc_sys_rpc_service)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_rpc_service)
DEFINE_PUBLIC_WEAK_ALIAS(sys_rpc_service, libc_sys_rpc_service)

/* syscall_slong_t rpc_service(void) */
.section .text.crt.syscall.Xrpc_service
INTERN_FUNCTION(libc_sys_Xrpc_service)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xrpc_service)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xrpc_service, libc_sys_Xrpc_service)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
.section .text.crt.syscall.lfutex
INTERN_FUNCTION(libc_sys_lfutex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutex, libc_sys_lfutex)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
.section .text.crt.syscall.Xlfutex
INTERN_FUNCTION(libc_sys_Xlfutex)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlfutex)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutex, libc_sys_Xlfutex)

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
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.lfutexexpr
INTERN_FUNCTION(libc_sys_lfutexexpr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lfutexexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutexexpr, libc_sys_lfutexexpr)

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
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.Xlfutexexpr
INTERN_FUNCTION(libc_sys_Xlfutexexpr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlfutexexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutexexpr, libc_sys_Xlfutexexpr)

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
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.lfutexlockexpr
INTERN_FUNCTION(libc_sys_lfutexlockexpr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_lfutexlockexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_lfutexlockexpr, libc_sys_lfutexlockexpr)

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
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.Xlfutexlockexpr
INTERN_FUNCTION(libc_sys_Xlfutexlockexpr)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xlfutexlockexpr)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xlfutexlockexpr, libc_sys_Xlfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.crt.syscall.mktty
INTERN_FUNCTION(libc_sys_mktty)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_mktty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_mktty, libc_sys_mktty)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.crt.syscall.Xmktty
INTERN_FUNCTION(libc_sys_Xmktty)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmktty)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmktty, libc_sys_Xmktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
.section .text.crt.syscall.raiseat
INTERN_FUNCTION(libc_sys_raiseat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_raiseat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_raiseat, libc_sys_raiseat)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
.section .text.crt.syscall.Xraiseat
INTERN_FUNCTION(libc_sys_Xraiseat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xraiseat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xraiseat, libc_sys_Xraiseat)

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
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
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
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
.section .text.crt.syscall.coredump
INTERN_FUNCTION(libc_sys_coredump)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_coredump)
DEFINE_PUBLIC_WEAK_ALIAS(sys_coredump, libc_sys_coredump)

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
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
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
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
.section .text.crt.syscall.Xcoredump
INTERN_FUNCTION(libc_sys_Xcoredump)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xcoredump)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xcoredump, libc_sys_Xcoredump)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.crt.syscall.kreaddir
INTERN_FUNCTION(libc_sys_kreaddir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kreaddir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kreaddir, libc_sys_kreaddir)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.crt.syscall.Xkreaddir
INTERN_FUNCTION(libc_sys_Xkreaddir)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkreaddir)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkreaddir, libc_sys_Xkreaddir)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.crt.syscall.fchdirat
INTERN_FUNCTION(libc_sys_fchdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fchdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fchdirat, libc_sys_fchdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.crt.syscall.Xfchdirat
INTERN_FUNCTION(libc_sys_Xfchdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfchdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfchdirat, libc_sys_Xfchdirat)

/* uint64_t fsmode(uint64_t mode) */
.section .text.crt.syscall.fsmode
INTERN_FUNCTION(libc_sys_fsmode)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fsmode)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsmode, libc_sys_fsmode)

/* uint64_t fsmode(uint64_t mode) */
.section .text.crt.syscall.Xfsmode
INTERN_FUNCTION(libc_sys_Xfsmode)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfsmode)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsmode, libc_sys_Xfsmode)

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
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.crt.syscall.maplibrary
INTERN_FUNCTION(libc_sys_maplibrary)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_maplibrary)
DEFINE_PUBLIC_WEAK_ALIAS(sys_maplibrary, libc_sys_maplibrary)

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
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.crt.syscall.Xmaplibrary
INTERN_FUNCTION(libc_sys_Xmaplibrary)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xmaplibrary)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xmaplibrary, libc_sys_Xmaplibrary)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.crt.syscall.kreaddirf
INTERN_FUNCTION(libc_sys_kreaddirf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kreaddirf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kreaddirf, libc_sys_kreaddirf)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.crt.syscall.Xkreaddirf
INTERN_FUNCTION(libc_sys_Xkreaddirf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkreaddirf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkreaddirf, libc_sys_Xkreaddirf)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.fmkdirat
INTERN_FUNCTION(libc_sys_fmkdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fmkdirat, libc_sys_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.Xfmkdirat
INTERN_FUNCTION(libc_sys_Xfmkdirat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfmkdirat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfmkdirat, libc_sys_Xfmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.crt.syscall.fmknodat
INTERN_FUNCTION(libc_sys_fmknodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fmknodat, libc_sys_fmknodat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.crt.syscall.Xfmknodat
INTERN_FUNCTION(libc_sys_Xfmknodat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfmknodat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfmknodat, libc_sys_Xfmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.crt.syscall.kfstatat
INTERN_FUNCTION(libc_sys_kfstatat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_kfstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_kfstatat, libc_sys_kfstatat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.crt.syscall.Xkfstatat
INTERN_FUNCTION(libc_sys_Xkfstatat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xkfstatat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xkfstatat, libc_sys_Xkfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.crt.syscall.frenameat
INTERN_FUNCTION(libc_sys_frenameat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_frenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_frenameat, libc_sys_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.crt.syscall.Xfrenameat
INTERN_FUNCTION(libc_sys_Xfrenameat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfrenameat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfrenameat, libc_sys_Xfrenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.fsymlinkat
INTERN_FUNCTION(libc_sys_fsymlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_fsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_fsymlinkat, libc_sys_fsymlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.Xfsymlinkat
INTERN_FUNCTION(libc_sys_Xfsymlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfsymlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfsymlinkat, libc_sys_Xfsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE|AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.freadlinkat
INTERN_FUNCTION(libc_sys_freadlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_freadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_freadlinkat, libc_sys_freadlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE|AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.Xfreadlinkat
INTERN_FUNCTION(libc_sys_Xfreadlinkat)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xfreadlinkat)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xfreadlinkat, libc_sys_Xfreadlinkat)

/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.preadvf
INTERN_FUNCTION(libc_sys_preadvf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_preadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_preadvf, libc_sys_preadvf)

/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpreadvf
INTERN_FUNCTION(libc_sys_Xpreadvf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpreadvf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpreadvf, libc_sys_Xpreadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pwritevf
INTERN_FUNCTION(libc_sys_pwritevf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_pwritevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_pwritevf, libc_sys_pwritevf)

/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpwritevf
INTERN_FUNCTION(libc_sys_Xpwritevf)
/* TODO: x86_64_printLibcSyscallWrapper() */
END(libc_sys_Xpwritevf)
DEFINE_PUBLIC_WEAK_ALIAS(sys_Xpwritevf, libc_sys_Xpwritevf)



/* Include the system call ammendment in order to alias
 * some exception-enabled functions onto system calls. */
#include "../../syscalls-ammend.S.inl"

