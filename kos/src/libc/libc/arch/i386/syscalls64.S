/* HASH CRC-32:0xdf1503e */
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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S
#define GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S 1

#include <hybrid/compiler.h>


/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.crt.syscall.read
INTERN_FUNCTION(libc_sys_read)
	.cfi_startproc
	xorq   %rax, %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_read)
DEFINE_PUBLIC_ALIAS(sys_read, libc_sys_read)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xread
INTERN_FUNCTION(libc_sys_Xread)
	.cfi_startproc
	xorq   %rax, %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xread)
DEFINE_PUBLIC_ALIAS(sys_Xread, libc_sys_Xread)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.crt.syscall.write
INTERN_FUNCTION(libc_sys_write)
	.cfi_startproc
	movq   $(0x1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_write)
DEFINE_PUBLIC_ALIAS(sys_write, libc_sys_write)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.crt.syscall.Xwrite
INTERN_FUNCTION(libc_sys_Xwrite)
	.cfi_startproc
	movq   $(0x1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwrite)
DEFINE_PUBLIC_ALIAS(sys_Xwrite, libc_sys_Xwrite)

/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.open
INTERN_FUNCTION(libc_sys_open)
	.cfi_startproc
	movq   $(0x2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_open)
DEFINE_PUBLIC_ALIAS(sys_open, libc_sys_open)

/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.Xopen
INTERN_FUNCTION(libc_sys_Xopen)
	.cfi_startproc
	movq   $(0x2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopen)
DEFINE_PUBLIC_ALIAS(sys_Xopen, libc_sys_Xopen)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.crt.syscall.close
INTERN_FUNCTION(libc_sys_close)
	.cfi_startproc
	movq   $(0x3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_close)
DEFINE_PUBLIC_ALIAS(sys_close, libc_sys_close)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.crt.syscall.Xclose
INTERN_FUNCTION(libc_sys_Xclose)
	.cfi_startproc
	movq   $(0x3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclose)
DEFINE_PUBLIC_ALIAS(sys_Xclose, libc_sys_Xclose)

/* errno_t stat(char const *filename, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.stat
INTERN_FUNCTION(libc_sys_stat)
	.cfi_startproc
	movq   $(0x4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_stat)
DEFINE_PUBLIC_ALIAS(sys_stat, libc_sys_stat)

/* errno_t stat(char const *filename, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.Xstat
INTERN_FUNCTION(libc_sys_Xstat)
	.cfi_startproc
	movq   $(0x4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xstat)
DEFINE_PUBLIC_ALIAS(sys_Xstat, libc_sys_Xstat)

/* errno_t fstat(fd_t fd, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.fstat
INTERN_FUNCTION(libc_sys_fstat)
	.cfi_startproc
	movq   $(0x5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fstat)
DEFINE_PUBLIC_ALIAS(sys_fstat, libc_sys_fstat)

/* errno_t fstat(fd_t fd, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.Xfstat
INTERN_FUNCTION(libc_sys_Xfstat)
	.cfi_startproc
	movq   $(0x5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfstat)
DEFINE_PUBLIC_ALIAS(sys_Xfstat, libc_sys_Xfstat)

/* errno_t lstat(char const *filename, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.lstat
INTERN_FUNCTION(libc_sys_lstat)
	.cfi_startproc
	movq   $(0x6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lstat)
DEFINE_PUBLIC_ALIAS(sys_lstat, libc_sys_lstat)

/* errno_t lstat(char const *filename, struct linux_statx64 *statbuf) */
.section .text.crt.syscall.Xlstat
INTERN_FUNCTION(libc_sys_Xlstat)
	.cfi_startproc
	movq   $(0x6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlstat)
DEFINE_PUBLIC_ALIAS(sys_Xlstat, libc_sys_Xlstat)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.crt.syscall.poll
INTERN_FUNCTION(libc_sys_poll)
	.cfi_startproc
	movq   $(0x7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_poll)
DEFINE_PUBLIC_ALIAS(sys_poll, libc_sys_poll)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.crt.syscall.Xpoll
INTERN_FUNCTION(libc_sys_Xpoll)
	.cfi_startproc
	movq   $(0x7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpoll)
DEFINE_PUBLIC_ALIAS(sys_Xpoll, libc_sys_Xpoll)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.crt.syscall.lseek
INTERN_FUNCTION(libc_sys_lseek)
	.cfi_startproc
	movq   $(0x8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lseek)
DEFINE_PUBLIC_ALIAS(sys_lseek, libc_sys_lseek)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.crt.syscall.Xlseek
INTERN_FUNCTION(libc_sys_Xlseek)
	.cfi_startproc
	movq   $(0x8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlseek)
DEFINE_PUBLIC_ALIAS(sys_Xlseek, libc_sys_Xlseek)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.crt.syscall.mmap
INTERN_FUNCTION(libc_sys_mmap)
	.cfi_startproc
	movq   $(0x9), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mmap)
DEFINE_PUBLIC_ALIAS(sys_mmap, libc_sys_mmap)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.crt.syscall.Xmmap
INTERN_FUNCTION(libc_sys_Xmmap)
	.cfi_startproc
	movq   $(0x9), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmmap)
DEFINE_PUBLIC_ALIAS(sys_Xmmap, libc_sys_Xmmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.crt.syscall.mprotect
INTERN_FUNCTION(libc_sys_mprotect)
	.cfi_startproc
	movq   $(0xa), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mprotect)
DEFINE_PUBLIC_ALIAS(sys_mprotect, libc_sys_mprotect)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.crt.syscall.Xmprotect
INTERN_FUNCTION(libc_sys_Xmprotect)
	.cfi_startproc
	movq   $(0xa), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmprotect)
DEFINE_PUBLIC_ALIAS(sys_Xmprotect, libc_sys_Xmprotect)

/* errno_t munmap(void *addr, size_t len) */
.section .text.crt.syscall.munmap
INTERN_FUNCTION(libc_sys_munmap)
	.cfi_startproc
	movq   $(0xb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munmap)
DEFINE_PUBLIC_ALIAS(sys_munmap, libc_sys_munmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.crt.syscall.Xmunmap
INTERN_FUNCTION(libc_sys_Xmunmap)
	.cfi_startproc
	movq   $(0xb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunmap)
DEFINE_PUBLIC_ALIAS(sys_Xmunmap, libc_sys_Xmunmap)

/* errno_t brk(void *addr) */
.section .text.crt.syscall.brk
INTERN_FUNCTION(libc_sys_brk)
	.cfi_startproc
	movq   $(0xc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_brk)
DEFINE_PUBLIC_ALIAS(sys_brk, libc_sys_brk)

/* errno_t brk(void *addr) */
.section .text.crt.syscall.Xbrk
INTERN_FUNCTION(libc_sys_Xbrk)
	.cfi_startproc
	movq   $(0xc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xbrk)
DEFINE_PUBLIC_ALIAS(sys_Xbrk, libc_sys_Xbrk)

/* errno_t rt_sigaction(signo_t signo, struct sigactionx64 const *act, struct sigactionx64 *oact, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigaction
INTERN_FUNCTION(libc_sys_rt_sigaction)
	.cfi_startproc
	movq   $(0xd), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_rt_sigaction, libc_sys_rt_sigaction)

/* errno_t rt_sigaction(signo_t signo, struct sigactionx64 const *act, struct sigactionx64 *oact, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigaction
INTERN_FUNCTION(libc_sys_Xrt_sigaction)
	.cfi_startproc
	movq   $(0xd), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigaction, libc_sys_Xrt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigprocmask
INTERN_FUNCTION(libc_sys_rt_sigprocmask)
	.cfi_startproc
	movq   $(0xe), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_rt_sigprocmask, libc_sys_rt_sigprocmask)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigprocmask
INTERN_FUNCTION(libc_sys_Xrt_sigprocmask)
	.cfi_startproc
	movq   $(0xe), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigprocmask, libc_sys_Xrt_sigprocmask)

/* Restore the given CPU/FPU context descriptors, as well as signal mask
 * before resuming execution by either invoking another system call `sc_info',
 * which will then return to `restore_cpu', or by directly returning there.
 * Arguments:
 *  - %rbp: [1..1] struct ucpustate64 const *restore_cpu;
 *  - %rbx: [0..1] struct fpustate64 const *restore_fpu;
 *  - %r12: [0..1] sigset_t const *restore_sigmask;
 *  - %r13: [0..1] struct rpc_syscall_info64 const *sc_info;
 * This system call uses a custom calling convention because registers passed
 * must not get clobbered during execution of a normal C function. On i386
 * this doesn't require a custom calling convention since enough registers
 * exist that are preserved by a C function, but are still used by at least
 * one system call invocation method. However on x86_64, no such registers
 * exist, requiring the use of a custom protocol. */
/* void rt_sigreturn(void) */
.section .text.crt.syscall.rt_sigreturn
INTERN_FUNCTION(libc_sys_rt_sigreturn)
	.cfi_startproc
	movq   $(0xf), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigreturn)
DEFINE_PUBLIC_ALIAS(sys_rt_sigreturn, libc_sys_rt_sigreturn)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.ioctl
INTERN_FUNCTION(libc_sys_ioctl)
	.cfi_startproc
	movq   $(0x10), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioctl)
DEFINE_PUBLIC_ALIAS(sys_ioctl, libc_sys_ioctl)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xioctl
INTERN_FUNCTION(libc_sys_Xioctl)
	.cfi_startproc
	movq   $(0x10), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioctl)
DEFINE_PUBLIC_ALIAS(sys_Xioctl, libc_sys_Xioctl)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.pread64
INTERN_FUNCTION(libc_sys_pread64)
	.cfi_startproc
	movq   $(0x11), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pread64)
DEFINE_PUBLIC_ALIAS(sys_pread64, libc_sys_pread64)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.Xpread64
INTERN_FUNCTION(libc_sys_Xpread64)
	.cfi_startproc
	movq   $(0x11), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpread64)
DEFINE_PUBLIC_ALIAS(sys_Xpread64, libc_sys_Xpread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.pwrite64
INTERN_FUNCTION(libc_sys_pwrite64)
	.cfi_startproc
	movq   $(0x12), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwrite64)
DEFINE_PUBLIC_ALIAS(sys_pwrite64, libc_sys_pwrite64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.crt.syscall.Xpwrite64
INTERN_FUNCTION(libc_sys_Xpwrite64)
	.cfi_startproc
	movq   $(0x12), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwrite64)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64, libc_sys_Xpwrite64)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovecx64 const *iovec, size_t count) */
.section .text.crt.syscall.readv
INTERN_FUNCTION(libc_sys_readv)
	.cfi_startproc
	movq   $(0x13), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readv)
DEFINE_PUBLIC_ALIAS(sys_readv, libc_sys_readv)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovecx64 const *iovec, size_t count) */
.section .text.crt.syscall.Xreadv
INTERN_FUNCTION(libc_sys_Xreadv)
	.cfi_startproc
	movq   $(0x13), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadv)
DEFINE_PUBLIC_ALIAS(sys_Xreadv, libc_sys_Xreadv)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovecx64 const *iovec, size_t count) */
.section .text.crt.syscall.writev
INTERN_FUNCTION(libc_sys_writev)
	.cfi_startproc
	movq   $(0x14), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writev)
DEFINE_PUBLIC_ALIAS(sys_writev, libc_sys_writev)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovecx64 const *iovec, size_t count) */
.section .text.crt.syscall.Xwritev
INTERN_FUNCTION(libc_sys_Xwritev)
	.cfi_startproc
	movq   $(0x14), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritev)
DEFINE_PUBLIC_ALIAS(sys_Xwritev, libc_sys_Xwritev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.crt.syscall.access
INTERN_FUNCTION(libc_sys_access)
	.cfi_startproc
	movq   $(0x15), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_access)
DEFINE_PUBLIC_ALIAS(sys_access, libc_sys_access)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.crt.syscall.Xaccess
INTERN_FUNCTION(libc_sys_Xaccess)
	.cfi_startproc
	movq   $(0x15), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xaccess)
DEFINE_PUBLIC_ALIAS(sys_Xaccess, libc_sys_Xaccess)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.crt.syscall.pipe
INTERN_FUNCTION(libc_sys_pipe)
	.cfi_startproc
	movq   $(0x16), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pipe)
DEFINE_PUBLIC_ALIAS(sys_pipe, libc_sys_pipe)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.crt.syscall.Xpipe
INTERN_FUNCTION(libc_sys_Xpipe)
	.cfi_startproc
	movq   $(0x16), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpipe)
DEFINE_PUBLIC_ALIAS(sys_Xpipe, libc_sys_Xpipe)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx64 *timeout) */
.section .text.crt.syscall.select
INTERN_FUNCTION(libc_sys_select)
	.cfi_startproc
	movq   $(0x17), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_select)
DEFINE_PUBLIC_ALIAS(sys_select, libc_sys_select)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx64 *timeout) */
.section .text.crt.syscall.Xselect
INTERN_FUNCTION(libc_sys_Xselect)
	.cfi_startproc
	movq   $(0x17), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xselect)
DEFINE_PUBLIC_ALIAS(sys_Xselect, libc_sys_Xselect)

/* errno_t sched_yield(void) */
.section .text.crt.syscall.sched_yield
INTERN_FUNCTION(libc_sys_sched_yield)
	.cfi_startproc
	movq   $(0x18), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_yield)
DEFINE_PUBLIC_ALIAS(sys_sched_yield, libc_sys_sched_yield)

/* errno_t sched_yield(void) */
.section .text.crt.syscall.Xsched_yield
INTERN_FUNCTION(libc_sys_Xsched_yield)
	.cfi_startproc
	movq   $(0x18), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_yield)
DEFINE_PUBLIC_ALIAS(sys_Xsched_yield, libc_sys_Xsched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.crt.syscall.mremap
INTERN_FUNCTION(libc_sys_mremap)
	.cfi_startproc
	movq   $(0x19), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mremap)
DEFINE_PUBLIC_ALIAS(sys_mremap, libc_sys_mremap)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.crt.syscall.Xmremap
INTERN_FUNCTION(libc_sys_Xmremap)
	.cfi_startproc
	movq   $(0x19), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmremap)
DEFINE_PUBLIC_ALIAS(sys_Xmremap, libc_sys_Xmremap)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.crt.syscall.msync
INTERN_FUNCTION(libc_sys_msync)
	.cfi_startproc
	movq   $(0x1a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msync)
DEFINE_PUBLIC_ALIAS(sys_msync, libc_sys_msync)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.crt.syscall.Xmsync
INTERN_FUNCTION(libc_sys_Xmsync)
	.cfi_startproc
	movq   $(0x1a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsync)
DEFINE_PUBLIC_ALIAS(sys_Xmsync, libc_sys_Xmsync)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.crt.syscall.mincore
INTERN_FUNCTION(libc_sys_mincore)
	.cfi_startproc
	movq   $(0x1b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mincore)
DEFINE_PUBLIC_ALIAS(sys_mincore, libc_sys_mincore)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.crt.syscall.Xmincore
INTERN_FUNCTION(libc_sys_Xmincore)
	.cfi_startproc
	movq   $(0x1b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmincore)
DEFINE_PUBLIC_ALIAS(sys_Xmincore, libc_sys_Xmincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.crt.syscall.madvise
INTERN_FUNCTION(libc_sys_madvise)
	.cfi_startproc
	movq   $(0x1c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_madvise)
DEFINE_PUBLIC_ALIAS(sys_madvise, libc_sys_madvise)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.crt.syscall.Xmadvise
INTERN_FUNCTION(libc_sys_Xmadvise)
	.cfi_startproc
	movq   $(0x1c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmadvise)
DEFINE_PUBLIC_ALIAS(sys_Xmadvise, libc_sys_Xmadvise)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
.section .text.crt.syscall.shmget
INTERN_FUNCTION(libc_sys_shmget)
	.cfi_startproc
	movq   $(0x1d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shmget)
DEFINE_PUBLIC_ALIAS(sys_shmget, libc_sys_shmget)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
.section .text.crt.syscall.Xshmget
INTERN_FUNCTION(libc_sys_Xshmget)
	.cfi_startproc
	movq   $(0x1d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshmget)
DEFINE_PUBLIC_ALIAS(sys_Xshmget, libc_sys_Xshmget)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
.section .text.crt.syscall.shmat
INTERN_FUNCTION(libc_sys_shmat)
	.cfi_startproc
	movq   $(0x1e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shmat)
DEFINE_PUBLIC_ALIAS(sys_shmat, libc_sys_shmat)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
.section .text.crt.syscall.Xshmat
INTERN_FUNCTION(libc_sys_Xshmat)
	.cfi_startproc
	movq   $(0x1e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshmat)
DEFINE_PUBLIC_ALIAS(sys_Xshmat, libc_sys_Xshmat)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
.section .text.crt.syscall.shmctl
INTERN_FUNCTION(libc_sys_shmctl)
	.cfi_startproc
	movq   $(0x1f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shmctl)
DEFINE_PUBLIC_ALIAS(sys_shmctl, libc_sys_shmctl)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
.section .text.crt.syscall.Xshmctl
INTERN_FUNCTION(libc_sys_Xshmctl)
	.cfi_startproc
	movq   $(0x1f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshmctl)
DEFINE_PUBLIC_ALIAS(sys_Xshmctl, libc_sys_Xshmctl)

/* fd_t dup(fd_t fd) */
.section .text.crt.syscall.dup
INTERN_FUNCTION(libc_sys_dup)
	.cfi_startproc
	movq   $(0x20), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup)
DEFINE_PUBLIC_ALIAS(sys_dup, libc_sys_dup)

/* fd_t dup(fd_t fd) */
.section .text.crt.syscall.Xdup
INTERN_FUNCTION(libc_sys_Xdup)
	.cfi_startproc
	movq   $(0x20), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup)
DEFINE_PUBLIC_ALIAS(sys_Xdup, libc_sys_Xdup)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.crt.syscall.dup2
INTERN_FUNCTION(libc_sys_dup2)
	.cfi_startproc
	movq   $(0x21), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup2)
DEFINE_PUBLIC_ALIAS(sys_dup2, libc_sys_dup2)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.crt.syscall.Xdup2
INTERN_FUNCTION(libc_sys_Xdup2)
	.cfi_startproc
	movq   $(0x21), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup2)
DEFINE_PUBLIC_ALIAS(sys_Xdup2, libc_sys_Xdup2)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
.section .text.crt.syscall.pause
INTERN_FUNCTION(libc_sys_pause)
	.cfi_startproc
	movq   $(0x22), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pause)
DEFINE_PUBLIC_ALIAS(sys_pause, libc_sys_pause)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
.section .text.crt.syscall.Xpause
INTERN_FUNCTION(libc_sys_Xpause)
	.cfi_startproc
	movq   $(0x22), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpause)
DEFINE_PUBLIC_ALIAS(sys_Xpause, libc_sys_Xpause)

/* errno_t nanosleep(struct timespecx64 const *req, struct timespecx64 *rem) */
.section .text.crt.syscall.nanosleep
INTERN_FUNCTION(libc_sys_nanosleep)
	.cfi_startproc
	movq   $(0x23), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_nanosleep, libc_sys_nanosleep)

/* errno_t nanosleep(struct timespecx64 const *req, struct timespecx64 *rem) */
.section .text.crt.syscall.Xnanosleep
INTERN_FUNCTION(libc_sys_Xnanosleep)
	.cfi_startproc
	movq   $(0x23), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xnanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xnanosleep, libc_sys_Xnanosleep)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
.section .text.crt.syscall.getitimer
INTERN_FUNCTION(libc_sys_getitimer)
	.cfi_startproc
	movq   $(0x24), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getitimer)
DEFINE_PUBLIC_ALIAS(sys_getitimer, libc_sys_getitimer)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
.section .text.crt.syscall.Xgetitimer
INTERN_FUNCTION(libc_sys_Xgetitimer)
	.cfi_startproc
	movq   $(0x24), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xgetitimer, libc_sys_Xgetitimer)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.crt.syscall.alarm
INTERN_FUNCTION(libc_sys_alarm)
	.cfi_startproc
	movq   $(0x25), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_alarm)
DEFINE_PUBLIC_ALIAS(sys_alarm, libc_sys_alarm)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.crt.syscall.Xalarm
INTERN_FUNCTION(libc_sys_Xalarm)
	.cfi_startproc
	movq   $(0x25), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xalarm)
DEFINE_PUBLIC_ALIAS(sys_Xalarm, libc_sys_Xalarm)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
.section .text.crt.syscall.setitimer
INTERN_FUNCTION(libc_sys_setitimer)
	.cfi_startproc
	movq   $(0x26), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setitimer)
DEFINE_PUBLIC_ALIAS(sys_setitimer, libc_sys_setitimer)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
.section .text.crt.syscall.Xsetitimer
INTERN_FUNCTION(libc_sys_Xsetitimer)
	.cfi_startproc
	movq   $(0x26), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xsetitimer, libc_sys_Xsetitimer)

/* pid_t getpid(void) */
.section .text.crt.syscall.getpid
INTERN_FUNCTION(libc_sys_getpid)
	.cfi_startproc
	movq   $(0x27), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpid)
DEFINE_PUBLIC_ALIAS(sys_getpid, libc_sys_getpid)

/* pid_t getpid(void) */
.section .text.crt.syscall.Xgetpid
INTERN_FUNCTION(libc_sys_Xgetpid)
	.cfi_startproc
	movq   $(0x27), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpid, libc_sys_Xgetpid)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *pin_offset, size_t num_bytes) */
.section .text.crt.syscall.sendfile
INTERN_FUNCTION(libc_sys_sendfile)
	.cfi_startproc
	movq   $(0x28), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendfile)
DEFINE_PUBLIC_ALIAS(sys_sendfile, libc_sys_sendfile)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *pin_offset, size_t num_bytes) */
.section .text.crt.syscall.Xsendfile
INTERN_FUNCTION(libc_sys_Xsendfile)
	.cfi_startproc
	movq   $(0x28), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendfile)
DEFINE_PUBLIC_ALIAS(sys_Xsendfile, libc_sys_Xsendfile)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.crt.syscall.socket
INTERN_FUNCTION(libc_sys_socket)
	.cfi_startproc
	movq   $(0x29), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_socket)
DEFINE_PUBLIC_ALIAS(sys_socket, libc_sys_socket)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.crt.syscall.Xsocket
INTERN_FUNCTION(libc_sys_Xsocket)
	.cfi_startproc
	movq   $(0x29), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsocket)
DEFINE_PUBLIC_ALIAS(sys_Xsocket, libc_sys_Xsocket)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that will implicitly be used as destination by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.connect
INTERN_FUNCTION(libc_sys_connect)
	.cfi_startproc
	movq   $(0x2a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_connect)
DEFINE_PUBLIC_ALIAS(sys_connect, libc_sys_connect)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that will implicitly be used as destination by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xconnect
INTERN_FUNCTION(libc_sys_Xconnect)
	.cfi_startproc
	movq   $(0x2a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xconnect)
DEFINE_PUBLIC_ALIAS(sys_Xconnect, libc_sys_Xconnect)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 *                           If this happens, the caller can still determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.accept
INTERN_FUNCTION(libc_sys_accept)
	.cfi_startproc
	movq   $(0x2b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_accept)
DEFINE_PUBLIC_ALIAS(sys_accept, libc_sys_accept)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 *                           If this happens, the caller can still determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xaccept
INTERN_FUNCTION(libc_sys_Xaccept)
	.cfi_startproc
	movq   $(0x2b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xaccept)
DEFINE_PUBLIC_ALIAS(sys_Xaccept, libc_sys_Xaccept)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.sendto
INTERN_FUNCTION(libc_sys_sendto)
	.cfi_startproc
	movq   $(0x2c), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendto)
DEFINE_PUBLIC_ALIAS(sys_sendto, libc_sys_sendto)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xsendto
INTERN_FUNCTION(libc_sys_Xsendto)
	.cfi_startproc
	movq   $(0x2c), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendto)
DEFINE_PUBLIC_ALIAS(sys_Xsendto, libc_sys_Xsendto)

/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.recvfrom
INTERN_FUNCTION(libc_sys_recvfrom)
	.cfi_startproc
	movq   $(0x2d), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvfrom)
DEFINE_PUBLIC_ALIAS(sys_recvfrom, libc_sys_recvfrom)

/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xrecvfrom
INTERN_FUNCTION(libc_sys_Xrecvfrom)
	.cfi_startproc
	movq   $(0x2d), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvfrom)
DEFINE_PUBLIC_ALIAS(sys_Xrecvfrom, libc_sys_Xrecvfrom)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdrx64 const *message, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.sendmsg
INTERN_FUNCTION(libc_sys_sendmsg)
	.cfi_startproc
	movq   $(0x2e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmsg, libc_sys_sendmsg)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdrx64 const *message, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.Xsendmsg
INTERN_FUNCTION(libc_sys_Xsendmsg)
	.cfi_startproc
	movq   $(0x2e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmsg, libc_sys_Xsendmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdrx64 *message, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.recvmsg
INTERN_FUNCTION(libc_sys_recvmsg)
	.cfi_startproc
	movq   $(0x2f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmsg, libc_sys_recvmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdrx64 *message, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.Xrecvmsg
INTERN_FUNCTION(libc_sys_Xrecvmsg)
	.cfi_startproc
	movq   $(0x2f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmsg, libc_sys_Xrecvmsg)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as all currently queued data has been read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.crt.syscall.shutdown
INTERN_FUNCTION(libc_sys_shutdown)
	.cfi_startproc
	movq   $(0x30), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shutdown)
DEFINE_PUBLIC_ALIAS(sys_shutdown, libc_sys_shutdown)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as all currently queued data has been read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.crt.syscall.Xshutdown
INTERN_FUNCTION(libc_sys_Xshutdown)
	.cfi_startproc
	movq   $(0x30), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshutdown)
DEFINE_PUBLIC_ALIAS(sys_Xshutdown, libc_sys_Xshutdown)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.bind
INTERN_FUNCTION(libc_sys_bind)
	.cfi_startproc
	movq   $(0x31), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_bind)
DEFINE_PUBLIC_ALIAS(sys_bind, libc_sys_bind)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.crt.syscall.Xbind
INTERN_FUNCTION(libc_sys_Xbind)
	.cfi_startproc
	movq   $(0x31), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xbind)
DEFINE_PUBLIC_ALIAS(sys_Xbind, libc_sys_Xbind)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients pending to be accept(2)-ed, before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse any further requests until the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.crt.syscall.listen
INTERN_FUNCTION(libc_sys_listen)
	.cfi_startproc
	movq   $(0x32), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_listen)
DEFINE_PUBLIC_ALIAS(sys_listen, libc_sys_listen)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients pending to be accept(2)-ed, before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse any further requests until the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.crt.syscall.Xlisten
INTERN_FUNCTION(libc_sys_Xlisten)
	.cfi_startproc
	movq   $(0x32), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlisten)
DEFINE_PUBLIC_ALIAS(sys_Xlisten, libc_sys_Xlisten)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This is usually the same address as was previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.getsockname
INTERN_FUNCTION(libc_sys_getsockname)
	.cfi_startproc
	movq   $(0x33), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsockname)
DEFINE_PUBLIC_ALIAS(sys_getsockname, libc_sys_getsockname)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This is usually the same address as was previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xgetsockname
INTERN_FUNCTION(libc_sys_Xgetsockname)
	.cfi_startproc
	movq   $(0x33), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsockname)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockname, libc_sys_Xgetsockname)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.getpeername
INTERN_FUNCTION(libc_sys_getpeername)
	.cfi_startproc
	movq   $(0x34), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpeername)
DEFINE_PUBLIC_ALIAS(sys_getpeername, libc_sys_getpeername)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.crt.syscall.Xgetpeername
INTERN_FUNCTION(libc_sys_Xgetpeername)
	.cfi_startproc
	movq   $(0x34), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpeername)
DEFINE_PUBLIC_ALIAS(sys_Xgetpeername, libc_sys_Xgetpeername)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.crt.syscall.socketpair
INTERN_FUNCTION(libc_sys_socketpair)
	.cfi_startproc
	movq   $(0x35), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_socketpair)
DEFINE_PUBLIC_ALIAS(sys_socketpair, libc_sys_socketpair)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.crt.syscall.Xsocketpair
INTERN_FUNCTION(libc_sys_Xsocketpair)
	.cfi_startproc
	movq   $(0x35), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsocketpair)
DEFINE_PUBLIC_ALIAS(sys_Xsocketpair, libc_sys_Xsocketpair)

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.crt.syscall.setsockopt
INTERN_FUNCTION(libc_sys_setsockopt)
	.cfi_startproc
	movq   $(0x36), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setsockopt)
DEFINE_PUBLIC_ALIAS(sys_setsockopt, libc_sys_setsockopt)

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.crt.syscall.Xsetsockopt
INTERN_FUNCTION(libc_sys_Xsetsockopt)
	.cfi_startproc
	movq   $(0x36), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xsetsockopt, libc_sys_Xsetsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the contents of `optval' are undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.crt.syscall.getsockopt
INTERN_FUNCTION(libc_sys_getsockopt)
	.cfi_startproc
	movq   $(0x37), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsockopt)
DEFINE_PUBLIC_ALIAS(sys_getsockopt, libc_sys_getsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the contents of `optval' are undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.crt.syscall.Xgetsockopt
INTERN_FUNCTION(libc_sys_Xgetsockopt)
	.cfi_startproc
	movq   $(0x37), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockopt, libc_sys_Xgetsockopt)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
.section .text.crt.syscall.clone
INTERN_FUNCTION(libc_sys_clone)
	.cfi_startproc
	movq   $(0x38), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clone)
DEFINE_PUBLIC_ALIAS(sys_clone, libc_sys_clone)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
.section .text.crt.syscall.Xclone
INTERN_FUNCTION(libc_sys_Xclone)
	.cfi_startproc
	movq   $(0x38), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclone)
DEFINE_PUBLIC_ALIAS(sys_Xclone, libc_sys_Xclone)

/* Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
.section .text.crt.syscall.fork
INTERN_FUNCTION(libc_sys_fork)
	.cfi_startproc
	movq   $(0x39), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fork)
DEFINE_PUBLIC_ALIAS(sys_fork, libc_sys_fork)

/* Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
.section .text.crt.syscall.Xfork
INTERN_FUNCTION(libc_sys_Xfork)
	.cfi_startproc
	movq   $(0x39), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfork)
DEFINE_PUBLIC_ALIAS(sys_Xfork, libc_sys_Xfork)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will only be resumed in case the
 *                     new program image could be loaded successfully. Otherwise,
 *                     the call to `execve(2)' returns normally in the child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care must be taken when using this system call, since you have to make sure that
 * the child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in the parent process. The same also goes for heap
 * functions, but generally speaking: you really shouldn't do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3), which
 * is something that KOS intentionally doesn't do, since I feel like doing so only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which case the parent process will not actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
.section .text.crt.syscall.vfork
INTERN_FUNCTION(libc_sys_vfork)
	.cfi_startproc
	movq   $(0x3a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vfork)
DEFINE_PUBLIC_ALIAS(sys_vfork, libc_sys_vfork)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will only be resumed in case the
 *                     new program image could be loaded successfully. Otherwise,
 *                     the call to `execve(2)' returns normally in the child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care must be taken when using this system call, since you have to make sure that
 * the child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in the parent process. The same also goes for heap
 * functions, but generally speaking: you really shouldn't do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3), which
 * is something that KOS intentionally doesn't do, since I feel like doing so only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which case the parent process will not actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
.section .text.crt.syscall.Xvfork
INTERN_FUNCTION(libc_sys_Xvfork)
	.cfi_startproc
	movq   $(0x3a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvfork)
DEFINE_PUBLIC_ALIAS(sys_Xvfork, libc_sys_Xvfork)

/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
/* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
.section .text.crt.syscall.execve
INTERN_FUNCTION(libc_sys_execve)
	.cfi_startproc
	movq   $(0x3b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_execve)
DEFINE_PUBLIC_ALIAS(sys_execve, libc_sys_execve)

/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
/* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
.section .text.crt.syscall.Xexecve
INTERN_FUNCTION(libc_sys_Xexecve)
	.cfi_startproc
	movq   $(0x3b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexecve)
DEFINE_PUBLIC_ALIAS(sys_Xexecve, libc_sys_Xexecve)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
.section .text.crt.syscall.exit
INTERN_FUNCTION(libc_sys_exit)
	.cfi_startproc
	movq   $(0x3c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_exit)
DEFINE_PUBLIC_ALIAS(sys_exit, libc_sys_exit)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
.section .text.crt.syscall.Xexit
INTERN_FUNCTION(libc_sys_Xexit)
	.cfi_startproc
	movq   $(0x3c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexit)
DEFINE_PUBLIC_ALIAS(sys_Xexit, libc_sys_Xexit)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex64 *usage) */
.section .text.crt.syscall.wait4
INTERN_FUNCTION(libc_sys_wait4)
	.cfi_startproc
	movq   $(0x3d), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_wait4)
DEFINE_PUBLIC_ALIAS(sys_wait4, libc_sys_wait4)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex64 *usage) */
.section .text.crt.syscall.Xwait4
INTERN_FUNCTION(libc_sys_Xwait4)
	.cfi_startproc
	movq   $(0x3d), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwait4)
DEFINE_PUBLIC_ALIAS(sys_Xwait4, libc_sys_Xwait4)

/* errno_t kill(pid_t pid, signo_t signo) */
.section .text.crt.syscall.kill
INTERN_FUNCTION(libc_sys_kill)
	.cfi_startproc
	movq   $(0x3e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kill)
DEFINE_PUBLIC_ALIAS(sys_kill, libc_sys_kill)

/* errno_t kill(pid_t pid, signo_t signo) */
.section .text.crt.syscall.Xkill
INTERN_FUNCTION(libc_sys_Xkill)
	.cfi_startproc
	movq   $(0x3e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkill)
DEFINE_PUBLIC_ALIAS(sys_Xkill, libc_sys_Xkill)

/* errno_t uname(struct utsname *name) */
.section .text.crt.syscall.uname
INTERN_FUNCTION(libc_sys_uname)
	.cfi_startproc
	movq   $(0x3f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_uname)
DEFINE_PUBLIC_ALIAS(sys_uname, libc_sys_uname)

/* errno_t uname(struct utsname *name) */
.section .text.crt.syscall.Xuname
INTERN_FUNCTION(libc_sys_Xuname)
	.cfi_startproc
	movq   $(0x3f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xuname)
DEFINE_PUBLIC_ALIAS(sys_Xuname, libc_sys_Xuname)

/* errno_t semget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semget
INTERN_FUNCTION(libc_sys_semget)
	.cfi_startproc
	movq   $(0x40), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_semget)
DEFINE_PUBLIC_ALIAS(sys_semget, libc_sys_semget)

/* errno_t semget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemget
INTERN_FUNCTION(libc_sys_Xsemget)
	.cfi_startproc
	movq   $(0x40), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsemget)
DEFINE_PUBLIC_ALIAS(sys_Xsemget, libc_sys_Xsemget)

/* errno_t semop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semop
INTERN_FUNCTION(libc_sys_semop)
	.cfi_startproc
	movq   $(0x41), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_semop)
DEFINE_PUBLIC_ALIAS(sys_semop, libc_sys_semop)

/* errno_t semop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemop
INTERN_FUNCTION(libc_sys_Xsemop)
	.cfi_startproc
	movq   $(0x41), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsemop)
DEFINE_PUBLIC_ALIAS(sys_Xsemop, libc_sys_Xsemop)

/* errno_t semctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semctl
INTERN_FUNCTION(libc_sys_semctl)
	.cfi_startproc
	movq   $(0x42), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_semctl)
DEFINE_PUBLIC_ALIAS(sys_semctl, libc_sys_semctl)

/* errno_t semctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemctl
INTERN_FUNCTION(libc_sys_Xsemctl)
	.cfi_startproc
	movq   $(0x42), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsemctl)
DEFINE_PUBLIC_ALIAS(sys_Xsemctl, libc_sys_Xsemctl)

/* errno_t shmdt(void const *shmaddr) */
.section .text.crt.syscall.shmdt
INTERN_FUNCTION(libc_sys_shmdt)
	.cfi_startproc
	movq   $(0x43), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_shmdt)
DEFINE_PUBLIC_ALIAS(sys_shmdt, libc_sys_shmdt)

/* errno_t shmdt(void const *shmaddr) */
.section .text.crt.syscall.Xshmdt
INTERN_FUNCTION(libc_sys_Xshmdt)
	.cfi_startproc
	movq   $(0x43), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xshmdt)
DEFINE_PUBLIC_ALIAS(sys_Xshmdt, libc_sys_Xshmdt)

/* errno_t msgget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgget
INTERN_FUNCTION(libc_sys_msgget)
	.cfi_startproc
	movq   $(0x44), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msgget)
DEFINE_PUBLIC_ALIAS(sys_msgget, libc_sys_msgget)

/* errno_t msgget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgget
INTERN_FUNCTION(libc_sys_Xmsgget)
	.cfi_startproc
	movq   $(0x44), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsgget)
DEFINE_PUBLIC_ALIAS(sys_Xmsgget, libc_sys_Xmsgget)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgsnd
INTERN_FUNCTION(libc_sys_msgsnd)
	.cfi_startproc
	movq   $(0x45), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msgsnd)
DEFINE_PUBLIC_ALIAS(sys_msgsnd, libc_sys_msgsnd)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgsnd
INTERN_FUNCTION(libc_sys_Xmsgsnd)
	.cfi_startproc
	movq   $(0x45), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsgsnd)
DEFINE_PUBLIC_ALIAS(sys_Xmsgsnd, libc_sys_Xmsgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgrcv
INTERN_FUNCTION(libc_sys_msgrcv)
	.cfi_startproc
	movq   $(0x46), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msgrcv)
DEFINE_PUBLIC_ALIAS(sys_msgrcv, libc_sys_msgrcv)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgrcv
INTERN_FUNCTION(libc_sys_Xmsgrcv)
	.cfi_startproc
	movq   $(0x46), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsgrcv)
DEFINE_PUBLIC_ALIAS(sys_Xmsgrcv, libc_sys_Xmsgrcv)

/* errno_t msgctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.msgctl
INTERN_FUNCTION(libc_sys_msgctl)
	.cfi_startproc
	movq   $(0x47), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_msgctl)
DEFINE_PUBLIC_ALIAS(sys_msgctl, libc_sys_msgctl)

/* errno_t msgctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmsgctl
INTERN_FUNCTION(libc_sys_Xmsgctl)
	.cfi_startproc
	movq   $(0x47), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmsgctl)
DEFINE_PUBLIC_ALIAS(sys_Xmsgctl, libc_sys_Xmsgctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.fcntl
INTERN_FUNCTION(libc_sys_fcntl)
	.cfi_startproc
	movq   $(0x48), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fcntl)
DEFINE_PUBLIC_ALIAS(sys_fcntl, libc_sys_fcntl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xfcntl
INTERN_FUNCTION(libc_sys_Xfcntl)
	.cfi_startproc
	movq   $(0x48), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfcntl)
DEFINE_PUBLIC_ALIAS(sys_Xfcntl, libc_sys_Xfcntl)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.crt.syscall.flock
INTERN_FUNCTION(libc_sys_flock)
	.cfi_startproc
	movq   $(0x49), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_flock)
DEFINE_PUBLIC_ALIAS(sys_flock, libc_sys_flock)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.crt.syscall.Xflock
INTERN_FUNCTION(libc_sys_Xflock)
	.cfi_startproc
	movq   $(0x49), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xflock)
DEFINE_PUBLIC_ALIAS(sys_Xflock, libc_sys_Xflock)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
/* errno_t fsync(fd_t fd) */
.section .text.crt.syscall.fsync
INTERN_FUNCTION(libc_sys_fsync)
	.cfi_startproc
	movq   $(0x4a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsync)
DEFINE_PUBLIC_ALIAS(sys_fsync, libc_sys_fsync)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
/* errno_t fsync(fd_t fd) */
.section .text.crt.syscall.Xfsync
INTERN_FUNCTION(libc_sys_Xfsync)
	.cfi_startproc
	movq   $(0x4a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsync)
DEFINE_PUBLIC_ALIAS(sys_Xfsync, libc_sys_Xfsync)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
/* errno_t fdatasync(fd_t fd) */
.section .text.crt.syscall.fdatasync
INTERN_FUNCTION(libc_sys_fdatasync)
	.cfi_startproc
	movq   $(0x4b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fdatasync)
DEFINE_PUBLIC_ALIAS(sys_fdatasync, libc_sys_fdatasync)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
/* errno_t fdatasync(fd_t fd) */
.section .text.crt.syscall.Xfdatasync
INTERN_FUNCTION(libc_sys_Xfdatasync)
	.cfi_startproc
	movq   $(0x4b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfdatasync)
DEFINE_PUBLIC_ALIAS(sys_Xfdatasync, libc_sys_Xfdatasync)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.crt.syscall.truncate
INTERN_FUNCTION(libc_sys_truncate)
	.cfi_startproc
	movq   $(0x4c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_truncate)
DEFINE_PUBLIC_ALIAS(sys_truncate, libc_sys_truncate)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.crt.syscall.Xtruncate
INTERN_FUNCTION(libc_sys_Xtruncate)
	.cfi_startproc
	movq   $(0x4c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtruncate)
DEFINE_PUBLIC_ALIAS(sys_Xtruncate, libc_sys_Xtruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.crt.syscall.ftruncate
INTERN_FUNCTION(libc_sys_ftruncate)
	.cfi_startproc
	movq   $(0x4d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ftruncate)
DEFINE_PUBLIC_ALIAS(sys_ftruncate, libc_sys_ftruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.crt.syscall.Xftruncate
INTERN_FUNCTION(libc_sys_Xftruncate)
	.cfi_startproc
	movq   $(0x4d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xftruncate)
DEFINE_PUBLIC_ALIAS(sys_Xftruncate, libc_sys_Xftruncate)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_direntx64 *buf, size_t buflen) */
.section .text.crt.syscall.getdents
INTERN_FUNCTION(libc_sys_getdents)
	.cfi_startproc
	movq   $(0x4e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdents)
DEFINE_PUBLIC_ALIAS(sys_getdents, libc_sys_getdents)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_direntx64 *buf, size_t buflen) */
.section .text.crt.syscall.Xgetdents
INTERN_FUNCTION(libc_sys_Xgetdents)
	.cfi_startproc
	movq   $(0x4e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdents)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents, libc_sys_Xgetdents)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.crt.syscall.getcwd
INTERN_FUNCTION(libc_sys_getcwd)
	.cfi_startproc
	movq   $(0x4f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getcwd)
DEFINE_PUBLIC_ALIAS(sys_getcwd, libc_sys_getcwd)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.crt.syscall.Xgetcwd
INTERN_FUNCTION(libc_sys_Xgetcwd)
	.cfi_startproc
	movq   $(0x4f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetcwd)
DEFINE_PUBLIC_ALIAS(sys_Xgetcwd, libc_sys_Xgetcwd)

/* errno_t chdir(char const *path) */
.section .text.crt.syscall.chdir
INTERN_FUNCTION(libc_sys_chdir)
	.cfi_startproc
	movq   $(0x50), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chdir)
DEFINE_PUBLIC_ALIAS(sys_chdir, libc_sys_chdir)

/* errno_t chdir(char const *path) */
.section .text.crt.syscall.Xchdir
INTERN_FUNCTION(libc_sys_Xchdir)
	.cfi_startproc
	movq   $(0x50), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchdir)
DEFINE_PUBLIC_ALIAS(sys_Xchdir, libc_sys_Xchdir)

/* errno_t fchdir(fd_t fd) */
.section .text.crt.syscall.fchdir
INTERN_FUNCTION(libc_sys_fchdir)
	.cfi_startproc
	movq   $(0x51), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchdir)
DEFINE_PUBLIC_ALIAS(sys_fchdir, libc_sys_fchdir)

/* errno_t fchdir(fd_t fd) */
.section .text.crt.syscall.Xfchdir
INTERN_FUNCTION(libc_sys_Xfchdir)
	.cfi_startproc
	movq   $(0x51), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchdir)
DEFINE_PUBLIC_ALIAS(sys_Xfchdir, libc_sys_Xfchdir)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.crt.syscall.rename
INTERN_FUNCTION(libc_sys_rename)
	.cfi_startproc
	movq   $(0x52), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rename)
DEFINE_PUBLIC_ALIAS(sys_rename, libc_sys_rename)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.crt.syscall.Xrename
INTERN_FUNCTION(libc_sys_Xrename)
	.cfi_startproc
	movq   $(0x52), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrename)
DEFINE_PUBLIC_ALIAS(sys_Xrename, libc_sys_Xrename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.crt.syscall.mkdir
INTERN_FUNCTION(libc_sys_mkdir)
	.cfi_startproc
	movq   $(0x53), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mkdir)
DEFINE_PUBLIC_ALIAS(sys_mkdir, libc_sys_mkdir)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.crt.syscall.Xmkdir
INTERN_FUNCTION(libc_sys_Xmkdir)
	.cfi_startproc
	movq   $(0x53), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmkdir)
DEFINE_PUBLIC_ALIAS(sys_Xmkdir, libc_sys_Xmkdir)

/* errno_t rmdir(char const *path) */
.section .text.crt.syscall.rmdir
INTERN_FUNCTION(libc_sys_rmdir)
	.cfi_startproc
	movq   $(0x54), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rmdir)
DEFINE_PUBLIC_ALIAS(sys_rmdir, libc_sys_rmdir)

/* errno_t rmdir(char const *path) */
.section .text.crt.syscall.Xrmdir
INTERN_FUNCTION(libc_sys_Xrmdir)
	.cfi_startproc
	movq   $(0x54), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrmdir)
DEFINE_PUBLIC_ALIAS(sys_Xrmdir, libc_sys_Xrmdir)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.crt.syscall.creat
INTERN_FUNCTION(libc_sys_creat)
	.cfi_startproc
	movq   $(0x55), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_creat)
DEFINE_PUBLIC_ALIAS(sys_creat, libc_sys_creat)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.crt.syscall.Xcreat
INTERN_FUNCTION(libc_sys_Xcreat)
	.cfi_startproc
	movq   $(0x55), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcreat)
DEFINE_PUBLIC_ALIAS(sys_Xcreat, libc_sys_Xcreat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.crt.syscall.link
INTERN_FUNCTION(libc_sys_link)
	.cfi_startproc
	movq   $(0x56), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_link)
DEFINE_PUBLIC_ALIAS(sys_link, libc_sys_link)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.crt.syscall.Xlink
INTERN_FUNCTION(libc_sys_Xlink)
	.cfi_startproc
	movq   $(0x56), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlink)
DEFINE_PUBLIC_ALIAS(sys_Xlink, libc_sys_Xlink)

/* errno_t unlink(char const *filename) */
.section .text.crt.syscall.unlink
INTERN_FUNCTION(libc_sys_unlink)
	.cfi_startproc
	movq   $(0x57), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unlink)
DEFINE_PUBLIC_ALIAS(sys_unlink, libc_sys_unlink)

/* errno_t unlink(char const *filename) */
.section .text.crt.syscall.Xunlink
INTERN_FUNCTION(libc_sys_Xunlink)
	.cfi_startproc
	movq   $(0x57), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunlink)
DEFINE_PUBLIC_ALIAS(sys_Xunlink, libc_sys_Xunlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.crt.syscall.symlink
INTERN_FUNCTION(libc_sys_symlink)
	.cfi_startproc
	movq   $(0x58), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_symlink)
DEFINE_PUBLIC_ALIAS(sys_symlink, libc_sys_symlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.crt.syscall.Xsymlink
INTERN_FUNCTION(libc_sys_Xsymlink)
	.cfi_startproc
	movq   $(0x58), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsymlink)
DEFINE_PUBLIC_ALIAS(sys_Xsymlink, libc_sys_Xsymlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.readlink
INTERN_FUNCTION(libc_sys_readlink)
	.cfi_startproc
	movq   $(0x59), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readlink)
DEFINE_PUBLIC_ALIAS(sys_readlink, libc_sys_readlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.Xreadlink
INTERN_FUNCTION(libc_sys_Xreadlink)
	.cfi_startproc
	movq   $(0x59), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadlink)
DEFINE_PUBLIC_ALIAS(sys_Xreadlink, libc_sys_Xreadlink)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.crt.syscall.chmod
INTERN_FUNCTION(libc_sys_chmod)
	.cfi_startproc
	movq   $(0x5a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chmod)
DEFINE_PUBLIC_ALIAS(sys_chmod, libc_sys_chmod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.crt.syscall.Xchmod
INTERN_FUNCTION(libc_sys_Xchmod)
	.cfi_startproc
	movq   $(0x5a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchmod)
DEFINE_PUBLIC_ALIAS(sys_Xchmod, libc_sys_Xchmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.crt.syscall.fchmod
INTERN_FUNCTION(libc_sys_fchmod)
	.cfi_startproc
	movq   $(0x5b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchmod)
DEFINE_PUBLIC_ALIAS(sys_fchmod, libc_sys_fchmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.crt.syscall.Xfchmod
INTERN_FUNCTION(libc_sys_Xfchmod)
	.cfi_startproc
	movq   $(0x5b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchmod)
DEFINE_PUBLIC_ALIAS(sys_Xfchmod, libc_sys_Xfchmod)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.chown
INTERN_FUNCTION(libc_sys_chown)
	.cfi_startproc
	movq   $(0x5c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chown)
DEFINE_PUBLIC_ALIAS(sys_chown, libc_sys_chown)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xchown
INTERN_FUNCTION(libc_sys_Xchown)
	.cfi_startproc
	movq   $(0x5c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchown)
DEFINE_PUBLIC_ALIAS(sys_Xchown, libc_sys_Xchown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
.section .text.crt.syscall.fchown
INTERN_FUNCTION(libc_sys_fchown)
	.cfi_startproc
	movq   $(0x5d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchown)
DEFINE_PUBLIC_ALIAS(sys_fchown, libc_sys_fchown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xfchown
INTERN_FUNCTION(libc_sys_Xfchown)
	.cfi_startproc
	movq   $(0x5d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchown)
DEFINE_PUBLIC_ALIAS(sys_Xfchown, libc_sys_Xfchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.lchown
INTERN_FUNCTION(libc_sys_lchown)
	.cfi_startproc
	movq   $(0x5e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lchown)
DEFINE_PUBLIC_ALIAS(sys_lchown, libc_sys_lchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
.section .text.crt.syscall.Xlchown
INTERN_FUNCTION(libc_sys_Xlchown)
	.cfi_startproc
	movq   $(0x5e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlchown)
DEFINE_PUBLIC_ALIAS(sys_Xlchown, libc_sys_Xlchown)

/* mode_t umask(mode_t mode) */
.section .text.crt.syscall.umask
INTERN_FUNCTION(libc_sys_umask)
	.cfi_startproc
	movq   $(0x5f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_umask)
DEFINE_PUBLIC_ALIAS(sys_umask, libc_sys_umask)

/* mode_t umask(mode_t mode) */
.section .text.crt.syscall.Xumask
INTERN_FUNCTION(libc_sys_Xumask)
	.cfi_startproc
	movq   $(0x5f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xumask)
DEFINE_PUBLIC_ALIAS(sys_Xumask, libc_sys_Xumask)

/* errno_t gettimeofday(struct timevalx64 *tv, struct timezone *tz) */
.section .text.crt.syscall.gettimeofday
INTERN_FUNCTION(libc_sys_gettimeofday)
	.cfi_startproc
	movq   $(0x60), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_gettimeofday)
DEFINE_PUBLIC_ALIAS(sys_gettimeofday, libc_sys_gettimeofday)

/* errno_t gettimeofday(struct timevalx64 *tv, struct timezone *tz) */
.section .text.crt.syscall.Xgettimeofday
INTERN_FUNCTION(libc_sys_Xgettimeofday)
	.cfi_startproc
	movq   $(0x60), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xgettimeofday, libc_sys_Xgettimeofday)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.crt.syscall.getrlimit
INTERN_FUNCTION(libc_sys_getrlimit)
	.cfi_startproc
	movq   $(0x61), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getrlimit)
DEFINE_PUBLIC_ALIAS(sys_getrlimit, libc_sys_getrlimit)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.crt.syscall.Xgetrlimit
INTERN_FUNCTION(libc_sys_Xgetrlimit)
	.cfi_startproc
	movq   $(0x61), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xgetrlimit, libc_sys_Xgetrlimit)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusagex64 *tv) */
.section .text.crt.syscall.getrusage
INTERN_FUNCTION(libc_sys_getrusage)
	.cfi_startproc
	movq   $(0x62), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getrusage)
DEFINE_PUBLIC_ALIAS(sys_getrusage, libc_sys_getrusage)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusagex64 *tv) */
.section .text.crt.syscall.Xgetrusage
INTERN_FUNCTION(libc_sys_Xgetrusage)
	.cfi_startproc
	movq   $(0x62), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetrusage)
DEFINE_PUBLIC_ALIAS(sys_Xgetrusage, libc_sys_Xgetrusage)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.crt.syscall.sysinfo
INTERN_FUNCTION(libc_sys_sysinfo)
	.cfi_startproc
	movq   $(0x63), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sysinfo)
DEFINE_PUBLIC_ALIAS(sys_sysinfo, libc_sys_sysinfo)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.crt.syscall.Xsysinfo
INTERN_FUNCTION(libc_sys_Xsysinfo)
	.cfi_startproc
	movq   $(0x63), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsysinfo)
DEFINE_PUBLIC_ALIAS(sys_Xsysinfo, libc_sys_Xsysinfo)

/* clock_t times(struct tms *buf) */
.section .text.crt.syscall.times
INTERN_FUNCTION(libc_sys_times)
	.cfi_startproc
	movq   $(0x64), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_times)
DEFINE_PUBLIC_ALIAS(sys_times, libc_sys_times)

/* clock_t times(struct tms *buf) */
.section .text.crt.syscall.Xtimes
INTERN_FUNCTION(libc_sys_Xtimes)
	.cfi_startproc
	movq   $(0x64), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimes)
DEFINE_PUBLIC_ALIAS(sys_Xtimes, libc_sys_Xtimes)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.crt.syscall.ptrace
INTERN_FUNCTION(libc_sys_ptrace)
	.cfi_startproc
	movq   $(0x65), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ptrace)
DEFINE_PUBLIC_ALIAS(sys_ptrace, libc_sys_ptrace)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.crt.syscall.Xptrace
INTERN_FUNCTION(libc_sys_Xptrace)
	.cfi_startproc
	movq   $(0x65), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xptrace)
DEFINE_PUBLIC_ALIAS(sys_Xptrace, libc_sys_Xptrace)

/* uid_t getuid(void) */
.section .text.crt.syscall.getuid
INTERN_FUNCTION(libc_sys_getuid)
	.cfi_startproc
	movq   $(0x66), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getuid)
DEFINE_PUBLIC_ALIAS(sys_getuid, libc_sys_getuid)

/* uid_t getuid(void) */
.section .text.crt.syscall.Xgetuid
INTERN_FUNCTION(libc_sys_Xgetuid)
	.cfi_startproc
	movq   $(0x66), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetuid, libc_sys_Xgetuid)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.crt.syscall.syslog
INTERN_FUNCTION(libc_sys_syslog)
	.cfi_startproc
	movq   $(0x67), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_syslog)
DEFINE_PUBLIC_ALIAS(sys_syslog, libc_sys_syslog)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.crt.syscall.Xsyslog
INTERN_FUNCTION(libc_sys_Xsyslog)
	.cfi_startproc
	movq   $(0x67), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsyslog)
DEFINE_PUBLIC_ALIAS(sys_Xsyslog, libc_sys_Xsyslog)

/* gid_t getgid(void) */
.section .text.crt.syscall.getgid
INTERN_FUNCTION(libc_sys_getgid)
	.cfi_startproc
	movq   $(0x68), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getgid)
DEFINE_PUBLIC_ALIAS(sys_getgid, libc_sys_getgid)

/* gid_t getgid(void) */
.section .text.crt.syscall.Xgetgid
INTERN_FUNCTION(libc_sys_Xgetgid)
	.cfi_startproc
	movq   $(0x68), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetgid, libc_sys_Xgetgid)

/* errno_t setuid(uid_t uid) */
.section .text.crt.syscall.setuid
INTERN_FUNCTION(libc_sys_setuid)
	.cfi_startproc
	movq   $(0x69), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setuid)
DEFINE_PUBLIC_ALIAS(sys_setuid, libc_sys_setuid)

/* errno_t setuid(uid_t uid) */
.section .text.crt.syscall.Xsetuid
INTERN_FUNCTION(libc_sys_Xsetuid)
	.cfi_startproc
	movq   $(0x69), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetuid, libc_sys_Xsetuid)

/* errno_t setgid(gid_t gid) */
.section .text.crt.syscall.setgid
INTERN_FUNCTION(libc_sys_setgid)
	.cfi_startproc
	movq   $(0x6a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setgid)
DEFINE_PUBLIC_ALIAS(sys_setgid, libc_sys_setgid)

/* errno_t setgid(gid_t gid) */
.section .text.crt.syscall.Xsetgid
INTERN_FUNCTION(libc_sys_Xsetgid)
	.cfi_startproc
	movq   $(0x6a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetgid, libc_sys_Xsetgid)

/* uid_t geteuid(void) */
.section .text.crt.syscall.geteuid
INTERN_FUNCTION(libc_sys_geteuid)
	.cfi_startproc
	movq   $(0x6b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_geteuid)
DEFINE_PUBLIC_ALIAS(sys_geteuid, libc_sys_geteuid)

/* uid_t geteuid(void) */
.section .text.crt.syscall.Xgeteuid
INTERN_FUNCTION(libc_sys_Xgeteuid)
	.cfi_startproc
	movq   $(0x6b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgeteuid)
DEFINE_PUBLIC_ALIAS(sys_Xgeteuid, libc_sys_Xgeteuid)

/* gid_t getegid(void) */
.section .text.crt.syscall.getegid
INTERN_FUNCTION(libc_sys_getegid)
	.cfi_startproc
	movq   $(0x6c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getegid)
DEFINE_PUBLIC_ALIAS(sys_getegid, libc_sys_getegid)

/* gid_t getegid(void) */
.section .text.crt.syscall.Xgetegid
INTERN_FUNCTION(libc_sys_Xgetegid)
	.cfi_startproc
	movq   $(0x6c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetegid)
DEFINE_PUBLIC_ALIAS(sys_Xgetegid, libc_sys_Xgetegid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.crt.syscall.setpgid
INTERN_FUNCTION(libc_sys_setpgid)
	.cfi_startproc
	movq   $(0x6d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setpgid)
DEFINE_PUBLIC_ALIAS(sys_setpgid, libc_sys_setpgid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.crt.syscall.Xsetpgid
INTERN_FUNCTION(libc_sys_Xsetpgid)
	.cfi_startproc
	movq   $(0x6d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetpgid, libc_sys_Xsetpgid)

/* pid_t getppid(void) */
.section .text.crt.syscall.getppid
INTERN_FUNCTION(libc_sys_getppid)
	.cfi_startproc
	movq   $(0x6e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getppid)
DEFINE_PUBLIC_ALIAS(sys_getppid, libc_sys_getppid)

/* pid_t getppid(void) */
.section .text.crt.syscall.Xgetppid
INTERN_FUNCTION(libc_sys_Xgetppid)
	.cfi_startproc
	movq   $(0x6e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetppid)
DEFINE_PUBLIC_ALIAS(sys_Xgetppid, libc_sys_Xgetppid)

/* pid_t getpgrp(void) */
.section .text.crt.syscall.getpgrp
INTERN_FUNCTION(libc_sys_getpgrp)
	.cfi_startproc
	movq   $(0x6f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpgrp)
DEFINE_PUBLIC_ALIAS(sys_getpgrp, libc_sys_getpgrp)

/* pid_t getpgrp(void) */
.section .text.crt.syscall.Xgetpgrp
INTERN_FUNCTION(libc_sys_Xgetpgrp)
	.cfi_startproc
	movq   $(0x6f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpgrp)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgrp, libc_sys_Xgetpgrp)

/* pid_t setsid(void) */
.section .text.crt.syscall.setsid
INTERN_FUNCTION(libc_sys_setsid)
	.cfi_startproc
	movq   $(0x70), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setsid)
DEFINE_PUBLIC_ALIAS(sys_setsid, libc_sys_setsid)

/* pid_t setsid(void) */
.section .text.crt.syscall.Xsetsid
INTERN_FUNCTION(libc_sys_Xsetsid)
	.cfi_startproc
	movq   $(0x70), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetsid)
DEFINE_PUBLIC_ALIAS(sys_Xsetsid, libc_sys_Xsetsid)

/* errno_t setreuid(uid_t ruid, uid_t euid) */
.section .text.crt.syscall.setreuid
INTERN_FUNCTION(libc_sys_setreuid)
	.cfi_startproc
	movq   $(0x71), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setreuid)
DEFINE_PUBLIC_ALIAS(sys_setreuid, libc_sys_setreuid)

/* errno_t setreuid(uid_t ruid, uid_t euid) */
.section .text.crt.syscall.Xsetreuid
INTERN_FUNCTION(libc_sys_Xsetreuid)
	.cfi_startproc
	movq   $(0x71), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetreuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetreuid, libc_sys_Xsetreuid)

/* errno_t setregid(gid_t rgid, gid_t egid) */
.section .text.crt.syscall.setregid
INTERN_FUNCTION(libc_sys_setregid)
	.cfi_startproc
	movq   $(0x72), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setregid)
DEFINE_PUBLIC_ALIAS(sys_setregid, libc_sys_setregid)

/* errno_t setregid(gid_t rgid, gid_t egid) */
.section .text.crt.syscall.Xsetregid
INTERN_FUNCTION(libc_sys_Xsetregid)
	.cfi_startproc
	movq   $(0x72), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetregid)
DEFINE_PUBLIC_ALIAS(sys_Xsetregid, libc_sys_Xsetregid)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, gid_t[] list) */
.section .text.crt.syscall.getgroups
INTERN_FUNCTION(libc_sys_getgroups)
	.cfi_startproc
	movq   $(0x73), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getgroups)
DEFINE_PUBLIC_ALIAS(sys_getgroups, libc_sys_getgroups)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, gid_t[] list) */
.section .text.crt.syscall.Xgetgroups
INTERN_FUNCTION(libc_sys_Xgetgroups)
	.cfi_startproc
	movq   $(0x73), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xgetgroups, libc_sys_Xgetgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
.section .text.crt.syscall.setgroups
INTERN_FUNCTION(libc_sys_setgroups)
	.cfi_startproc
	movq   $(0x74), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setgroups)
DEFINE_PUBLIC_ALIAS(sys_setgroups, libc_sys_setgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
.section .text.crt.syscall.Xsetgroups
INTERN_FUNCTION(libc_sys_Xsetgroups)
	.cfi_startproc
	movq   $(0x74), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xsetgroups, libc_sys_Xsetgroups)

/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
.section .text.crt.syscall.setresuid
INTERN_FUNCTION(libc_sys_setresuid)
	.cfi_startproc
	movq   $(0x75), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setresuid)
DEFINE_PUBLIC_ALIAS(sys_setresuid, libc_sys_setresuid)

/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
.section .text.crt.syscall.Xsetresuid
INTERN_FUNCTION(libc_sys_Xsetresuid)
	.cfi_startproc
	movq   $(0x75), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresuid, libc_sys_Xsetresuid)

/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
.section .text.crt.syscall.getresuid
INTERN_FUNCTION(libc_sys_getresuid)
	.cfi_startproc
	movq   $(0x76), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getresuid)
DEFINE_PUBLIC_ALIAS(sys_getresuid, libc_sys_getresuid)

/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
.section .text.crt.syscall.Xgetresuid
INTERN_FUNCTION(libc_sys_Xgetresuid)
	.cfi_startproc
	movq   $(0x76), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresuid, libc_sys_Xgetresuid)

/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
.section .text.crt.syscall.setresgid
INTERN_FUNCTION(libc_sys_setresgid)
	.cfi_startproc
	movq   $(0x77), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setresgid)
DEFINE_PUBLIC_ALIAS(sys_setresgid, libc_sys_setresgid)

/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
.section .text.crt.syscall.Xsetresgid
INTERN_FUNCTION(libc_sys_Xsetresgid)
	.cfi_startproc
	movq   $(0x77), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresgid, libc_sys_Xsetresgid)

/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
.section .text.crt.syscall.getresgid
INTERN_FUNCTION(libc_sys_getresgid)
	.cfi_startproc
	movq   $(0x78), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getresgid)
DEFINE_PUBLIC_ALIAS(sys_getresgid, libc_sys_getresgid)

/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
.section .text.crt.syscall.Xgetresgid
INTERN_FUNCTION(libc_sys_Xgetresgid)
	.cfi_startproc
	movq   $(0x78), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresgid, libc_sys_Xgetresgid)

/* pid_t getpgid(pid_t pid) */
.section .text.crt.syscall.getpgid
INTERN_FUNCTION(libc_sys_getpgid)
	.cfi_startproc
	movq   $(0x79), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpgid)
DEFINE_PUBLIC_ALIAS(sys_getpgid, libc_sys_getpgid)

/* pid_t getpgid(pid_t pid) */
.section .text.crt.syscall.Xgetpgid
INTERN_FUNCTION(libc_sys_Xgetpgid)
	.cfi_startproc
	movq   $(0x79), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgid, libc_sys_Xgetpgid)

/* errno_t setfsuid(uid_t uid) */
.section .text.crt.syscall.setfsuid
INTERN_FUNCTION(libc_sys_setfsuid)
	.cfi_startproc
	movq   $(0x7a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setfsuid)
DEFINE_PUBLIC_ALIAS(sys_setfsuid, libc_sys_setfsuid)

/* errno_t setfsuid(uid_t uid) */
.section .text.crt.syscall.Xsetfsuid
INTERN_FUNCTION(libc_sys_Xsetfsuid)
	.cfi_startproc
	movq   $(0x7a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetfsuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsuid, libc_sys_Xsetfsuid)

/* errno_t setfsgid(gid_t gid) */
.section .text.crt.syscall.setfsgid
INTERN_FUNCTION(libc_sys_setfsgid)
	.cfi_startproc
	movq   $(0x7b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setfsgid)
DEFINE_PUBLIC_ALIAS(sys_setfsgid, libc_sys_setfsgid)

/* errno_t setfsgid(gid_t gid) */
.section .text.crt.syscall.Xsetfsgid
INTERN_FUNCTION(libc_sys_Xsetfsgid)
	.cfi_startproc
	movq   $(0x7b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetfsgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsgid, libc_sys_Xsetfsgid)

/* pid_t getsid(pid_t pid) */
.section .text.crt.syscall.getsid
INTERN_FUNCTION(libc_sys_getsid)
	.cfi_startproc
	movq   $(0x7c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getsid)
DEFINE_PUBLIC_ALIAS(sys_getsid, libc_sys_getsid)

/* pid_t getsid(pid_t pid) */
.section .text.crt.syscall.Xgetsid
INTERN_FUNCTION(libc_sys_Xgetsid)
	.cfi_startproc
	movq   $(0x7c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetsid)
DEFINE_PUBLIC_ALIAS(sys_Xgetsid, libc_sys_Xgetsid)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.capget
INTERN_FUNCTION(libc_sys_capget)
	.cfi_startproc
	movq   $(0x7d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_capget)
DEFINE_PUBLIC_ALIAS(sys_capget, libc_sys_capget)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcapget
INTERN_FUNCTION(libc_sys_Xcapget)
	.cfi_startproc
	movq   $(0x7d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcapget)
DEFINE_PUBLIC_ALIAS(sys_Xcapget, libc_sys_Xcapget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.crt.syscall.capset
INTERN_FUNCTION(libc_sys_capset)
	.cfi_startproc
	movq   $(0x7e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_capset)
DEFINE_PUBLIC_ALIAS(sys_capset, libc_sys_capset)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcapset
INTERN_FUNCTION(libc_sys_Xcapset)
	.cfi_startproc
	movq   $(0x7e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcapset)
DEFINE_PUBLIC_ALIAS(sys_Xcapset, libc_sys_Xcapset)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigpending
INTERN_FUNCTION(libc_sys_rt_sigpending)
	.cfi_startproc
	movq   $(0x7f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_rt_sigpending, libc_sys_rt_sigpending)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigpending
INTERN_FUNCTION(libc_sys_Xrt_sigpending)
	.cfi_startproc
	movq   $(0x7f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigpending, libc_sys_Xrt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox64_struct *info, struct timespecx64 const *timeout, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigtimedwait
INTERN_FUNCTION(libc_sys_rt_sigtimedwait)
	.cfi_startproc
	movq   $(0x80), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_rt_sigtimedwait, libc_sys_rt_sigtimedwait)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox64_struct *info, struct timespecx64 const *timeout, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigtimedwait
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait)
	.cfi_startproc
	movq   $(0x80), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigtimedwait, libc_sys_Xrt_sigtimedwait)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t tgid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
.section .text.crt.syscall.rt_sigqueueinfo
INTERN_FUNCTION(libc_sys_rt_sigqueueinfo)
	.cfi_startproc
	movq   $(0x81), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_sigqueueinfo, libc_sys_rt_sigqueueinfo)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t tgid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
.section .text.crt.syscall.Xrt_sigqueueinfo
INTERN_FUNCTION(libc_sys_Xrt_sigqueueinfo)
	.cfi_startproc
	movq   $(0x81), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigqueueinfo, libc_sys_Xrt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.crt.syscall.rt_sigsuspend
INTERN_FUNCTION(libc_sys_rt_sigsuspend)
	.cfi_startproc
	movq   $(0x82), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_rt_sigsuspend, libc_sys_rt_sigsuspend)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.crt.syscall.Xrt_sigsuspend
INTERN_FUNCTION(libc_sys_Xrt_sigsuspend)
	.cfi_startproc
	movq   $(0x82), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigsuspend, libc_sys_Xrt_sigsuspend)

/* errno_t sigaltstack(struct __sigaltstackx64 const *ss, struct __sigaltstackx64 *oss) */
.section .text.crt.syscall.sigaltstack
INTERN_FUNCTION(libc_sys_sigaltstack)
	.cfi_startproc
	movq   $(0x83), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sigaltstack)
DEFINE_PUBLIC_ALIAS(sys_sigaltstack, libc_sys_sigaltstack)

/* errno_t sigaltstack(struct __sigaltstackx64 const *ss, struct __sigaltstackx64 *oss) */
.section .text.crt.syscall.Xsigaltstack
INTERN_FUNCTION(libc_sys_Xsigaltstack)
	.cfi_startproc
	movq   $(0x83), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsigaltstack)
DEFINE_PUBLIC_ALIAS(sys_Xsigaltstack, libc_sys_Xsigaltstack)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbufx64 const *times) */
.section .text.crt.syscall.utime
INTERN_FUNCTION(libc_sys_utime)
	.cfi_startproc
	movq   $(0x84), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utime)
DEFINE_PUBLIC_ALIAS(sys_utime, libc_sys_utime)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbufx64 const *times) */
.section .text.crt.syscall.Xutime
INTERN_FUNCTION(libc_sys_Xutime)
	.cfi_startproc
	movq   $(0x84), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutime)
DEFINE_PUBLIC_ALIAS(sys_Xutime, libc_sys_Xutime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.mknod
INTERN_FUNCTION(libc_sys_mknod)
	.cfi_startproc
	movq   $(0x85), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mknod)
DEFINE_PUBLIC_ALIAS(sys_mknod, libc_sys_mknod)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.Xmknod
INTERN_FUNCTION(libc_sys_Xmknod)
	.cfi_startproc
	movq   $(0x85), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmknod)
DEFINE_PUBLIC_ALIAS(sys_Xmknod, libc_sys_Xmknod)

/* errno_t uselib(char const *library) */
.section .text.crt.syscall.uselib
INTERN_FUNCTION(libc_sys_uselib)
	.cfi_startproc
	movq   $(0x86), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_uselib)
DEFINE_PUBLIC_ALIAS(sys_uselib, libc_sys_uselib)

/* errno_t uselib(char const *library) */
.section .text.crt.syscall.Xuselib
INTERN_FUNCTION(libc_sys_Xuselib)
	.cfi_startproc
	movq   $(0x86), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xuselib)
DEFINE_PUBLIC_ALIAS(sys_Xuselib, libc_sys_Xuselib)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.crt.syscall.personality
INTERN_FUNCTION(libc_sys_personality)
	.cfi_startproc
	movq   $(0x87), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_personality)
DEFINE_PUBLIC_ALIAS(sys_personality, libc_sys_personality)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpersonality
INTERN_FUNCTION(libc_sys_Xpersonality)
	.cfi_startproc
	movq   $(0x87), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpersonality)
DEFINE_PUBLIC_ALIAS(sys_Xpersonality, libc_sys_Xpersonality)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.crt.syscall.ustat
INTERN_FUNCTION(libc_sys_ustat)
	.cfi_startproc
	movq   $(0x88), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ustat)
DEFINE_PUBLIC_ALIAS(sys_ustat, libc_sys_ustat)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.crt.syscall.Xustat
INTERN_FUNCTION(libc_sys_Xustat)
	.cfi_startproc
	movq   $(0x88), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xustat)
DEFINE_PUBLIC_ALIAS(sys_Xustat, libc_sys_Xustat)

/* errno_t statfs(char const *file, struct __statfsx64 *buf) */
.section .text.crt.syscall.statfs
INTERN_FUNCTION(libc_sys_statfs)
	.cfi_startproc
	movq   $(0x89), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_statfs)
DEFINE_PUBLIC_ALIAS(sys_statfs, libc_sys_statfs)

/* errno_t statfs(char const *file, struct __statfsx64 *buf) */
.section .text.crt.syscall.Xstatfs
INTERN_FUNCTION(libc_sys_Xstatfs)
	.cfi_startproc
	movq   $(0x89), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xstatfs, libc_sys_Xstatfs)

/* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
.section .text.crt.syscall.fstatfs
INTERN_FUNCTION(libc_sys_fstatfs)
	.cfi_startproc
	movq   $(0x8a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fstatfs)
DEFINE_PUBLIC_ALIAS(sys_fstatfs, libc_sys_fstatfs)

/* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
.section .text.crt.syscall.Xfstatfs
INTERN_FUNCTION(libc_sys_Xfstatfs)
	.cfi_startproc
	movq   $(0x8a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xfstatfs, libc_sys_Xfstatfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sysfs
INTERN_FUNCTION(libc_sys_sysfs)
	.cfi_startproc
	movq   $(0x8b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sysfs)
DEFINE_PUBLIC_ALIAS(sys_sysfs, libc_sys_sysfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsysfs
INTERN_FUNCTION(libc_sys_Xsysfs)
	.cfi_startproc
	movq   $(0x8b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsysfs)
DEFINE_PUBLIC_ALIAS(sys_Xsysfs, libc_sys_Xsysfs)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.crt.syscall.getpriority
INTERN_FUNCTION(libc_sys_getpriority)
	.cfi_startproc
	movq   $(0x8c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpriority)
DEFINE_PUBLIC_ALIAS(sys_getpriority, libc_sys_getpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.crt.syscall.Xgetpriority
INTERN_FUNCTION(libc_sys_Xgetpriority)
	.cfi_startproc
	movq   $(0x8c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xgetpriority, libc_sys_Xgetpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.crt.syscall.setpriority
INTERN_FUNCTION(libc_sys_setpriority)
	.cfi_startproc
	movq   $(0x8d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setpriority)
DEFINE_PUBLIC_ALIAS(sys_setpriority, libc_sys_setpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.crt.syscall.Xsetpriority
INTERN_FUNCTION(libc_sys_Xsetpriority)
	.cfi_startproc
	movq   $(0x8d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xsetpriority, libc_sys_Xsetpriority)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.crt.syscall.sched_setparam
INTERN_FUNCTION(libc_sys_sched_setparam)
	.cfi_startproc
	movq   $(0x8e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setparam)
DEFINE_PUBLIC_ALIAS(sys_sched_setparam, libc_sys_sched_setparam)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.crt.syscall.Xsched_setparam
INTERN_FUNCTION(libc_sys_Xsched_setparam)
	.cfi_startproc
	movq   $(0x8e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setparam, libc_sys_Xsched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.crt.syscall.sched_getparam
INTERN_FUNCTION(libc_sys_sched_getparam)
	.cfi_startproc
	movq   $(0x8f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getparam)
DEFINE_PUBLIC_ALIAS(sys_sched_getparam, libc_sys_sched_getparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.crt.syscall.Xsched_getparam
INTERN_FUNCTION(libc_sys_Xsched_getparam)
	.cfi_startproc
	movq   $(0x8f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getparam, libc_sys_Xsched_getparam)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE', optionally or'd with `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.crt.syscall.sched_setscheduler
INTERN_FUNCTION(libc_sys_sched_setscheduler)
	.cfi_startproc
	movq   $(0x90), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_setscheduler, libc_sys_sched_setscheduler)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE', optionally or'd with `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.crt.syscall.Xsched_setscheduler
INTERN_FUNCTION(libc_sys_Xsched_setscheduler)
	.cfi_startproc
	movq   $(0x90), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setscheduler, libc_sys_Xsched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.crt.syscall.sched_getscheduler
INTERN_FUNCTION(libc_sys_sched_getscheduler)
	.cfi_startproc
	movq   $(0x91), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_getscheduler, libc_sys_sched_getscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.crt.syscall.Xsched_getscheduler
INTERN_FUNCTION(libc_sys_Xsched_getscheduler)
	.cfi_startproc
	movq   $(0x91), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getscheduler, libc_sys_Xsched_getscheduler)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.crt.syscall.sched_get_priority_max
INTERN_FUNCTION(libc_sys_sched_get_priority_max)
	.cfi_startproc
	movq   $(0x92), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_max, libc_sys_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.crt.syscall.Xsched_get_priority_max
INTERN_FUNCTION(libc_sys_Xsched_get_priority_max)
	.cfi_startproc
	movq   $(0x92), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_max, libc_sys_Xsched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.crt.syscall.sched_get_priority_min
INTERN_FUNCTION(libc_sys_sched_get_priority_min)
	.cfi_startproc
	movq   $(0x93), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_min, libc_sys_sched_get_priority_min)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.crt.syscall.Xsched_get_priority_min
INTERN_FUNCTION(libc_sys_Xsched_get_priority_min)
	.cfi_startproc
	movq   $(0x93), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_min, libc_sys_Xsched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespecx64 *tms) */
.section .text.crt.syscall.sched_rr_get_interval
INTERN_FUNCTION(libc_sys_sched_rr_get_interval)
	.cfi_startproc
	movq   $(0x94), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_sched_rr_get_interval, libc_sys_sched_rr_get_interval)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespecx64 *tms) */
.section .text.crt.syscall.Xsched_rr_get_interval
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval)
	.cfi_startproc
	movq   $(0x94), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_Xsched_rr_get_interval, libc_sys_Xsched_rr_get_interval)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.crt.syscall.mlock
INTERN_FUNCTION(libc_sys_mlock)
	.cfi_startproc
	movq   $(0x95), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mlock)
DEFINE_PUBLIC_ALIAS(sys_mlock, libc_sys_mlock)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.crt.syscall.Xmlock
INTERN_FUNCTION(libc_sys_Xmlock)
	.cfi_startproc
	movq   $(0x95), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmlock)
DEFINE_PUBLIC_ALIAS(sys_Xmlock, libc_sys_Xmlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.crt.syscall.munlock
INTERN_FUNCTION(libc_sys_munlock)
	.cfi_startproc
	movq   $(0x96), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munlock)
DEFINE_PUBLIC_ALIAS(sys_munlock, libc_sys_munlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.crt.syscall.Xmunlock
INTERN_FUNCTION(libc_sys_Xmunlock)
	.cfi_startproc
	movq   $(0x96), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunlock)
DEFINE_PUBLIC_ALIAS(sys_Xmunlock, libc_sys_Xmunlock)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.crt.syscall.mlockall
INTERN_FUNCTION(libc_sys_mlockall)
	.cfi_startproc
	movq   $(0x97), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mlockall)
DEFINE_PUBLIC_ALIAS(sys_mlockall, libc_sys_mlockall)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.crt.syscall.Xmlockall
INTERN_FUNCTION(libc_sys_Xmlockall)
	.cfi_startproc
	movq   $(0x97), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmlockall, libc_sys_Xmlockall)

/* errno_t munlockall(void) */
.section .text.crt.syscall.munlockall
INTERN_FUNCTION(libc_sys_munlockall)
	.cfi_startproc
	movq   $(0x98), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_munlockall)
DEFINE_PUBLIC_ALIAS(sys_munlockall, libc_sys_munlockall)

/* errno_t munlockall(void) */
.section .text.crt.syscall.Xmunlockall
INTERN_FUNCTION(libc_sys_Xmunlockall)
	.cfi_startproc
	movq   $(0x98), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmunlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmunlockall, libc_sys_Xmunlockall)

/* errno_t vhangup(void) */
.section .text.crt.syscall.vhangup
INTERN_FUNCTION(libc_sys_vhangup)
	.cfi_startproc
	movq   $(0x99), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vhangup)
DEFINE_PUBLIC_ALIAS(sys_vhangup, libc_sys_vhangup)

/* errno_t vhangup(void) */
.section .text.crt.syscall.Xvhangup
INTERN_FUNCTION(libc_sys_Xvhangup)
	.cfi_startproc
	movq   $(0x99), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvhangup)
DEFINE_PUBLIC_ALIAS(sys_Xvhangup, libc_sys_Xvhangup)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.crt.syscall.modify_ldt
INTERN_FUNCTION(libc_sys_modify_ldt)
	.cfi_startproc
	movq   $(0x9a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_modify_ldt)
DEFINE_PUBLIC_ALIAS(sys_modify_ldt, libc_sys_modify_ldt)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.crt.syscall.Xmodify_ldt
INTERN_FUNCTION(libc_sys_Xmodify_ldt)
	.cfi_startproc
	movq   $(0x9a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmodify_ldt)
DEFINE_PUBLIC_ALIAS(sys_Xmodify_ldt, libc_sys_Xmodify_ldt)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.crt.syscall.pivot_root
INTERN_FUNCTION(libc_sys_pivot_root)
	.cfi_startproc
	movq   $(0x9b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pivot_root)
DEFINE_PUBLIC_ALIAS(sys_pivot_root, libc_sys_pivot_root)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpivot_root
INTERN_FUNCTION(libc_sys_Xpivot_root)
	.cfi_startproc
	movq   $(0x9b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpivot_root)
DEFINE_PUBLIC_ALIAS(sys_Xpivot_root, libc_sys_Xpivot_root)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall._sysctl
INTERN_FUNCTION(libc_sys__sysctl)
	.cfi_startproc
	movq   $(0x9c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys__sysctl)
DEFINE_PUBLIC_ALIAS(sys__sysctl, libc_sys__sysctl)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.X_sysctl
INTERN_FUNCTION(libc_sys_X_sysctl)
	.cfi_startproc
	movq   $(0x9c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_X_sysctl)
DEFINE_PUBLIC_ALIAS(sys_X_sysctl, libc_sys_X_sysctl)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.prctl
INTERN_FUNCTION(libc_sys_prctl)
	.cfi_startproc
	movq   $(0x9d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_prctl)
DEFINE_PUBLIC_ALIAS(sys_prctl, libc_sys_prctl)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xprctl
INTERN_FUNCTION(libc_sys_Xprctl)
	.cfi_startproc
	movq   $(0x9d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprctl)
DEFINE_PUBLIC_ALIAS(sys_Xprctl, libc_sys_Xprctl)

/* errno_t arch_prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.arch_prctl
INTERN_FUNCTION(libc_sys_arch_prctl)
	.cfi_startproc
	movq   $(0x9e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_arch_prctl)
DEFINE_PUBLIC_ALIAS(sys_arch_prctl, libc_sys_arch_prctl)

/* errno_t arch_prctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xarch_prctl
INTERN_FUNCTION(libc_sys_Xarch_prctl)
	.cfi_startproc
	movq   $(0x9e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xarch_prctl)
DEFINE_PUBLIC_ALIAS(sys_Xarch_prctl, libc_sys_Xarch_prctl)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.crt.syscall.adjtimex
INTERN_FUNCTION(libc_sys_adjtimex)
	.cfi_startproc
	movq   $(0x9f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_adjtimex)
DEFINE_PUBLIC_ALIAS(sys_adjtimex, libc_sys_adjtimex)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xadjtimex
INTERN_FUNCTION(libc_sys_Xadjtimex)
	.cfi_startproc
	movq   $(0x9f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xadjtimex)
DEFINE_PUBLIC_ALIAS(sys_Xadjtimex, libc_sys_Xadjtimex)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.crt.syscall.setrlimit
INTERN_FUNCTION(libc_sys_setrlimit)
	.cfi_startproc
	movq   $(0xa0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setrlimit)
DEFINE_PUBLIC_ALIAS(sys_setrlimit, libc_sys_setrlimit)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.crt.syscall.Xsetrlimit
INTERN_FUNCTION(libc_sys_Xsetrlimit)
	.cfi_startproc
	movq   $(0xa0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xsetrlimit, libc_sys_Xsetrlimit)

/* errno_t chroot(char const *path) */
.section .text.crt.syscall.chroot
INTERN_FUNCTION(libc_sys_chroot)
	.cfi_startproc
	movq   $(0xa1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_chroot)
DEFINE_PUBLIC_ALIAS(sys_chroot, libc_sys_chroot)

/* errno_t chroot(char const *path) */
.section .text.crt.syscall.Xchroot
INTERN_FUNCTION(libc_sys_Xchroot)
	.cfi_startproc
	movq   $(0xa1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xchroot)
DEFINE_PUBLIC_ALIAS(sys_Xchroot, libc_sys_Xchroot)

/* errno_t sync(void) */
.section .text.crt.syscall.sync
INTERN_FUNCTION(libc_sys_sync)
	.cfi_startproc
	movq   $(0xa2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sync)
DEFINE_PUBLIC_ALIAS(sys_sync, libc_sys_sync)

/* errno_t sync(void) */
.section .text.crt.syscall.Xsync
INTERN_FUNCTION(libc_sys_Xsync)
	.cfi_startproc
	movq   $(0xa2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsync)
DEFINE_PUBLIC_ALIAS(sys_Xsync, libc_sys_Xsync)

/* errno_t acct(char const *filename) */
.section .text.crt.syscall.acct
INTERN_FUNCTION(libc_sys_acct)
	.cfi_startproc
	movq   $(0xa3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_acct)
DEFINE_PUBLIC_ALIAS(sys_acct, libc_sys_acct)

/* errno_t acct(char const *filename) */
.section .text.crt.syscall.Xacct
INTERN_FUNCTION(libc_sys_Xacct)
	.cfi_startproc
	movq   $(0xa3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xacct)
DEFINE_PUBLIC_ALIAS(sys_Xacct, libc_sys_Xacct)

/* errno_t settimeofday(struct timevalx64 const *tv, struct timezone const *tz) */
.section .text.crt.syscall.settimeofday
INTERN_FUNCTION(libc_sys_settimeofday)
	.cfi_startproc
	movq   $(0xa4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_settimeofday)
DEFINE_PUBLIC_ALIAS(sys_settimeofday, libc_sys_settimeofday)

/* errno_t settimeofday(struct timevalx64 const *tv, struct timezone const *tz) */
.section .text.crt.syscall.Xsettimeofday
INTERN_FUNCTION(libc_sys_Xsettimeofday)
	.cfi_startproc
	movq   $(0xa4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xsettimeofday, libc_sys_Xsettimeofday)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
.section .text.crt.syscall.mount
INTERN_FUNCTION(libc_sys_mount)
	.cfi_startproc
	movq   $(0xa5), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mount)
DEFINE_PUBLIC_ALIAS(sys_mount, libc_sys_mount)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
.section .text.crt.syscall.Xmount
INTERN_FUNCTION(libc_sys_Xmount)
	.cfi_startproc
	movq   $(0xa5), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmount)
DEFINE_PUBLIC_ALIAS(sys_Xmount, libc_sys_Xmount)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.crt.syscall.umount2
INTERN_FUNCTION(libc_sys_umount2)
	.cfi_startproc
	movq   $(0xa6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_umount2)
DEFINE_PUBLIC_ALIAS(sys_umount2, libc_sys_umount2)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.crt.syscall.Xumount2
INTERN_FUNCTION(libc_sys_Xumount2)
	.cfi_startproc
	movq   $(0xa6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xumount2)
DEFINE_PUBLIC_ALIAS(sys_Xumount2, libc_sys_Xumount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.crt.syscall.swapon
INTERN_FUNCTION(libc_sys_swapon)
	.cfi_startproc
	movq   $(0xa7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_swapon)
DEFINE_PUBLIC_ALIAS(sys_swapon, libc_sys_swapon)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.crt.syscall.Xswapon
INTERN_FUNCTION(libc_sys_Xswapon)
	.cfi_startproc
	movq   $(0xa7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xswapon)
DEFINE_PUBLIC_ALIAS(sys_Xswapon, libc_sys_Xswapon)

/* errno_t swapoff(char const *pathname) */
.section .text.crt.syscall.swapoff
INTERN_FUNCTION(libc_sys_swapoff)
	.cfi_startproc
	movq   $(0xa8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_swapoff)
DEFINE_PUBLIC_ALIAS(sys_swapoff, libc_sys_swapoff)

/* errno_t swapoff(char const *pathname) */
.section .text.crt.syscall.Xswapoff
INTERN_FUNCTION(libc_sys_Xswapoff)
	.cfi_startproc
	movq   $(0xa8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xswapoff)
DEFINE_PUBLIC_ALIAS(sys_Xswapoff, libc_sys_Xswapoff)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.crt.syscall.reboot
INTERN_FUNCTION(libc_sys_reboot)
	.cfi_startproc
	movq   $(0xa9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_reboot)
DEFINE_PUBLIC_ALIAS(sys_reboot, libc_sys_reboot)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.crt.syscall.Xreboot
INTERN_FUNCTION(libc_sys_Xreboot)
	.cfi_startproc
	movq   $(0xa9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreboot)
DEFINE_PUBLIC_ALIAS(sys_Xreboot, libc_sys_Xreboot)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.crt.syscall.sethostname
INTERN_FUNCTION(libc_sys_sethostname)
	.cfi_startproc
	movq   $(0xaa), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sethostname)
DEFINE_PUBLIC_ALIAS(sys_sethostname, libc_sys_sethostname)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.crt.syscall.Xsethostname
INTERN_FUNCTION(libc_sys_Xsethostname)
	.cfi_startproc
	movq   $(0xaa), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsethostname)
DEFINE_PUBLIC_ALIAS(sys_Xsethostname, libc_sys_Xsethostname)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.crt.syscall.setdomainname
INTERN_FUNCTION(libc_sys_setdomainname)
	.cfi_startproc
	movq   $(0xab), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setdomainname)
DEFINE_PUBLIC_ALIAS(sys_setdomainname, libc_sys_setdomainname)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.crt.syscall.Xsetdomainname
INTERN_FUNCTION(libc_sys_Xsetdomainname)
	.cfi_startproc
	movq   $(0xab), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetdomainname)
DEFINE_PUBLIC_ALIAS(sys_Xsetdomainname, libc_sys_Xsetdomainname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.crt.syscall.iopl
INTERN_FUNCTION(libc_sys_iopl)
	.cfi_startproc
	movq   $(0xac), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_iopl)
DEFINE_PUBLIC_ALIAS(sys_iopl, libc_sys_iopl)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.crt.syscall.Xiopl
INTERN_FUNCTION(libc_sys_Xiopl)
	.cfi_startproc
	movq   $(0xac), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xiopl)
DEFINE_PUBLIC_ALIAS(sys_Xiopl, libc_sys_Xiopl)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.crt.syscall.ioperm
INTERN_FUNCTION(libc_sys_ioperm)
	.cfi_startproc
	movq   $(0xad), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioperm)
DEFINE_PUBLIC_ALIAS(sys_ioperm, libc_sys_ioperm)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.crt.syscall.Xioperm
INTERN_FUNCTION(libc_sys_Xioperm)
	.cfi_startproc
	movq   $(0xad), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioperm)
DEFINE_PUBLIC_ALIAS(sys_Xioperm, libc_sys_Xioperm)

/* errno_t create_module(void) */
.section .text.crt.syscall.create_module
INTERN_FUNCTION(libc_sys_create_module)
	.cfi_startproc
	movq   $(0xae), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_create_module)
DEFINE_PUBLIC_ALIAS(sys_create_module, libc_sys_create_module)

/* errno_t create_module(void) */
.section .text.crt.syscall.Xcreate_module
INTERN_FUNCTION(libc_sys_Xcreate_module)
	.cfi_startproc
	movq   $(0xae), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcreate_module)
DEFINE_PUBLIC_ALIAS(sys_Xcreate_module, libc_sys_Xcreate_module)

/* Load a kernel driver from an ELF image `module_image...+=len'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatiblity ends. Since the
 * linux kernel does not implement any semblance of a stable ABI, you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
.section .text.crt.syscall.init_module
INTERN_FUNCTION(libc_sys_init_module)
	.cfi_startproc
	movq   $(0xaf), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_init_module)
DEFINE_PUBLIC_ALIAS(sys_init_module, libc_sys_init_module)

/* Load a kernel driver from an ELF image `module_image...+=len'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatiblity ends. Since the
 * linux kernel does not implement any semblance of a stable ABI, you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
.section .text.crt.syscall.Xinit_module
INTERN_FUNCTION(libc_sys_Xinit_module)
	.cfi_startproc
	movq   $(0xaf), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xinit_module, libc_sys_Xinit_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                 - O_NONBLOCK: Don't wait for the driver to be unloaded.
 *                               Currently, KOS simply ignores this flag,
 *                               since drivers on KOS should always be unloaded
 *                               immediatly. - However, driver finalizers may
 *                               do blocking operations before then...
 *                 - O_TRUNC:    Force the driver to be unloaded immediatly
 *                               (may compromise system integrity)
 *                               s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
.section .text.crt.syscall.delete_module
INTERN_FUNCTION(libc_sys_delete_module)
	.cfi_startproc
	movq   $(0xb0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_delete_module)
DEFINE_PUBLIC_ALIAS(sys_delete_module, libc_sys_delete_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                 - O_NONBLOCK: Don't wait for the driver to be unloaded.
 *                               Currently, KOS simply ignores this flag,
 *                               since drivers on KOS should always be unloaded
 *                               immediatly. - However, driver finalizers may
 *                               do blocking operations before then...
 *                 - O_TRUNC:    Force the driver to be unloaded immediatly
 *                               (may compromise system integrity)
 *                               s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
.section .text.crt.syscall.Xdelete_module
INTERN_FUNCTION(libc_sys_Xdelete_module)
	.cfi_startproc
	movq   $(0xb0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdelete_module)
DEFINE_PUBLIC_ALIAS(sys_Xdelete_module, libc_sys_Xdelete_module)

/* errno_t get_kernel_syms(void) */
.section .text.crt.syscall.get_kernel_syms
INTERN_FUNCTION(libc_sys_get_kernel_syms)
	.cfi_startproc
	movq   $(0xb1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_kernel_syms)
DEFINE_PUBLIC_ALIAS(sys_get_kernel_syms, libc_sys_get_kernel_syms)

/* errno_t get_kernel_syms(void) */
.section .text.crt.syscall.Xget_kernel_syms
INTERN_FUNCTION(libc_sys_Xget_kernel_syms)
	.cfi_startproc
	movq   $(0xb1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_kernel_syms)
DEFINE_PUBLIC_ALIAS(sys_Xget_kernel_syms, libc_sys_Xget_kernel_syms)

/* errno_t query_module(void) */
.section .text.crt.syscall.query_module
INTERN_FUNCTION(libc_sys_query_module)
	.cfi_startproc
	movq   $(0xb2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_query_module)
DEFINE_PUBLIC_ALIAS(sys_query_module, libc_sys_query_module)

/* errno_t query_module(void) */
.section .text.crt.syscall.Xquery_module
INTERN_FUNCTION(libc_sys_Xquery_module)
	.cfi_startproc
	movq   $(0xb2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xquery_module)
DEFINE_PUBLIC_ALIAS(sys_Xquery_module, libc_sys_Xquery_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.quotactl
INTERN_FUNCTION(libc_sys_quotactl)
	.cfi_startproc
	movq   $(0xb3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_quotactl)
DEFINE_PUBLIC_ALIAS(sys_quotactl, libc_sys_quotactl)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xquotactl
INTERN_FUNCTION(libc_sys_Xquotactl)
	.cfi_startproc
	movq   $(0xb3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xquotactl)
DEFINE_PUBLIC_ALIAS(sys_Xquotactl, libc_sys_Xquotactl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.nfsservctl
INTERN_FUNCTION(libc_sys_nfsservctl)
	.cfi_startproc
	movq   $(0xb4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_nfsservctl)
DEFINE_PUBLIC_ALIAS(sys_nfsservctl, libc_sys_nfsservctl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xnfsservctl
INTERN_FUNCTION(libc_sys_Xnfsservctl)
	.cfi_startproc
	movq   $(0xb4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xnfsservctl)
DEFINE_PUBLIC_ALIAS(sys_Xnfsservctl, libc_sys_Xnfsservctl)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.getpmsg
INTERN_FUNCTION(libc_sys_getpmsg)
	.cfi_startproc
	movq   $(0xb5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getpmsg)
DEFINE_PUBLIC_ALIAS(sys_getpmsg, libc_sys_getpmsg)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xgetpmsg
INTERN_FUNCTION(libc_sys_Xgetpmsg)
	.cfi_startproc
	movq   $(0xb5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetpmsg)
DEFINE_PUBLIC_ALIAS(sys_Xgetpmsg, libc_sys_Xgetpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.putpmsg
INTERN_FUNCTION(libc_sys_putpmsg)
	.cfi_startproc
	movq   $(0xb6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_putpmsg)
DEFINE_PUBLIC_ALIAS(sys_putpmsg, libc_sys_putpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xputpmsg
INTERN_FUNCTION(libc_sys_Xputpmsg)
	.cfi_startproc
	movq   $(0xb6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xputpmsg)
DEFINE_PUBLIC_ALIAS(sys_Xputpmsg, libc_sys_Xputpmsg)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.afs_syscall
INTERN_FUNCTION(libc_sys_afs_syscall)
	.cfi_startproc
	movq   $(0xb7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_afs_syscall)
DEFINE_PUBLIC_ALIAS(sys_afs_syscall, libc_sys_afs_syscall)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xafs_syscall
INTERN_FUNCTION(libc_sys_Xafs_syscall)
	.cfi_startproc
	movq   $(0xb7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xafs_syscall)
DEFINE_PUBLIC_ALIAS(sys_Xafs_syscall, libc_sys_Xafs_syscall)

/* errno_t tuxcall(void) */
.section .text.crt.syscall.tuxcall
INTERN_FUNCTION(libc_sys_tuxcall)
	.cfi_startproc
	movq   $(0xb8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tuxcall)
DEFINE_PUBLIC_ALIAS(sys_tuxcall, libc_sys_tuxcall)

/* errno_t tuxcall(void) */
.section .text.crt.syscall.Xtuxcall
INTERN_FUNCTION(libc_sys_Xtuxcall)
	.cfi_startproc
	movq   $(0xb8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtuxcall)
DEFINE_PUBLIC_ALIAS(sys_Xtuxcall, libc_sys_Xtuxcall)

/* errno_t security(int TODO_PROTOTYPE) */
.section .text.crt.syscall.security
INTERN_FUNCTION(libc_sys_security)
	.cfi_startproc
	movq   $(0xb9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_security)
DEFINE_PUBLIC_ALIAS(sys_security, libc_sys_security)

/* errno_t security(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsecurity
INTERN_FUNCTION(libc_sys_Xsecurity)
	.cfi_startproc
	movq   $(0xb9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsecurity)
DEFINE_PUBLIC_ALIAS(sys_Xsecurity, libc_sys_Xsecurity)

/* pid_t gettid(void) */
.section .text.crt.syscall.gettid
INTERN_FUNCTION(libc_sys_gettid)
	.cfi_startproc
	movq   $(0xba), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_gettid)
DEFINE_PUBLIC_ALIAS(sys_gettid, libc_sys_gettid)

/* pid_t gettid(void) */
.section .text.crt.syscall.Xgettid
INTERN_FUNCTION(libc_sys_Xgettid)
	.cfi_startproc
	movq   $(0xba), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgettid)
DEFINE_PUBLIC_ALIAS(sys_Xgettid, libc_sys_Xgettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.crt.syscall.readahead
INTERN_FUNCTION(libc_sys_readahead)
	.cfi_startproc
	movq   $(0xbb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readahead)
DEFINE_PUBLIC_ALIAS(sys_readahead, libc_sys_readahead)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.crt.syscall.Xreadahead
INTERN_FUNCTION(libc_sys_Xreadahead)
	.cfi_startproc
	movq   $(0xbb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadahead)
DEFINE_PUBLIC_ALIAS(sys_Xreadahead, libc_sys_Xreadahead)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.setxattr
INTERN_FUNCTION(libc_sys_setxattr)
	.cfi_startproc
	movq   $(0xbc), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setxattr)
DEFINE_PUBLIC_ALIAS(sys_setxattr, libc_sys_setxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsetxattr
INTERN_FUNCTION(libc_sys_Xsetxattr)
	.cfi_startproc
	movq   $(0xbc), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xsetxattr, libc_sys_Xsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.lsetxattr
INTERN_FUNCTION(libc_sys_lsetxattr)
	.cfi_startproc
	movq   $(0xbd), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lsetxattr)
DEFINE_PUBLIC_ALIAS(sys_lsetxattr, libc_sys_lsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xlsetxattr
INTERN_FUNCTION(libc_sys_Xlsetxattr)
	.cfi_startproc
	movq   $(0xbd), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlsetxattr, libc_sys_Xlsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.fsetxattr
INTERN_FUNCTION(libc_sys_fsetxattr)
	.cfi_startproc
	movq   $(0xbe), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsetxattr)
DEFINE_PUBLIC_ALIAS(sys_fsetxattr, libc_sys_fsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xfsetxattr
INTERN_FUNCTION(libc_sys_Xfsetxattr)
	.cfi_startproc
	movq   $(0xbe), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfsetxattr, libc_sys_Xfsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.getxattr
INTERN_FUNCTION(libc_sys_getxattr)
	.cfi_startproc
	movq   $(0xbf), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getxattr)
DEFINE_PUBLIC_ALIAS(sys_getxattr, libc_sys_getxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xgetxattr
INTERN_FUNCTION(libc_sys_Xgetxattr)
	.cfi_startproc
	movq   $(0xbf), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xgetxattr, libc_sys_Xgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.lgetxattr
INTERN_FUNCTION(libc_sys_lgetxattr)
	.cfi_startproc
	movq   $(0xc0), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lgetxattr)
DEFINE_PUBLIC_ALIAS(sys_lgetxattr, libc_sys_lgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xlgetxattr
INTERN_FUNCTION(libc_sys_Xlgetxattr)
	.cfi_startproc
	movq   $(0xc0), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlgetxattr, libc_sys_Xlgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.fgetxattr
INTERN_FUNCTION(libc_sys_fgetxattr)
	.cfi_startproc
	movq   $(0xc1), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fgetxattr)
DEFINE_PUBLIC_ALIAS(sys_fgetxattr, libc_sys_fgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.crt.syscall.Xfgetxattr
INTERN_FUNCTION(libc_sys_Xfgetxattr)
	.cfi_startproc
	movq   $(0xc1), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfgetxattr, libc_sys_Xfgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.listxattr
INTERN_FUNCTION(libc_sys_listxattr)
	.cfi_startproc
	movq   $(0xc2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_listxattr)
DEFINE_PUBLIC_ALIAS(sys_listxattr, libc_sys_listxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xlistxattr
INTERN_FUNCTION(libc_sys_Xlistxattr)
	.cfi_startproc
	movq   $(0xc2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlistxattr, libc_sys_Xlistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.llistxattr
INTERN_FUNCTION(libc_sys_llistxattr)
	.cfi_startproc
	movq   $(0xc3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_llistxattr)
DEFINE_PUBLIC_ALIAS(sys_llistxattr, libc_sys_llistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xllistxattr
INTERN_FUNCTION(libc_sys_Xllistxattr)
	.cfi_startproc
	movq   $(0xc3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xllistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xllistxattr, libc_sys_Xllistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.flistxattr
INTERN_FUNCTION(libc_sys_flistxattr)
	.cfi_startproc
	movq   $(0xc4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_flistxattr)
DEFINE_PUBLIC_ALIAS(sys_flistxattr, libc_sys_flistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.crt.syscall.Xflistxattr
INTERN_FUNCTION(libc_sys_Xflistxattr)
	.cfi_startproc
	movq   $(0xc4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xflistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xflistxattr, libc_sys_Xflistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.crt.syscall.removexattr
INTERN_FUNCTION(libc_sys_removexattr)
	.cfi_startproc
	movq   $(0xc5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_removexattr)
DEFINE_PUBLIC_ALIAS(sys_removexattr, libc_sys_removexattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.crt.syscall.Xremovexattr
INTERN_FUNCTION(libc_sys_Xremovexattr)
	.cfi_startproc
	movq   $(0xc5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xremovexattr, libc_sys_Xremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.crt.syscall.lremovexattr
INTERN_FUNCTION(libc_sys_lremovexattr)
	.cfi_startproc
	movq   $(0xc6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lremovexattr)
DEFINE_PUBLIC_ALIAS(sys_lremovexattr, libc_sys_lremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.crt.syscall.Xlremovexattr
INTERN_FUNCTION(libc_sys_Xlremovexattr)
	.cfi_startproc
	movq   $(0xc6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xlremovexattr, libc_sys_Xlremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
.section .text.crt.syscall.fremovexattr
INTERN_FUNCTION(libc_sys_fremovexattr)
	.cfi_startproc
	movq   $(0xc7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fremovexattr)
DEFINE_PUBLIC_ALIAS(sys_fremovexattr, libc_sys_fremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
.section .text.crt.syscall.Xfremovexattr
INTERN_FUNCTION(libc_sys_Xfremovexattr)
	.cfi_startproc
	movq   $(0xc7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xfremovexattr, libc_sys_Xfremovexattr)

/* errno_t tkill(pid_t tid, signo_t signo) */
.section .text.crt.syscall.tkill
INTERN_FUNCTION(libc_sys_tkill)
	.cfi_startproc
	movq   $(0xc8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tkill)
DEFINE_PUBLIC_ALIAS(sys_tkill, libc_sys_tkill)

/* errno_t tkill(pid_t tid, signo_t signo) */
.section .text.crt.syscall.Xtkill
INTERN_FUNCTION(libc_sys_Xtkill)
	.cfi_startproc
	movq   $(0xc8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtkill)
DEFINE_PUBLIC_ALIAS(sys_Xtkill, libc_sys_Xtkill)

/* time32_t time(time32_t *timer) */
.section .text.crt.syscall.time
INTERN_FUNCTION(libc_sys_time)
	.cfi_startproc
	movq   $(0xc9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_time)
DEFINE_PUBLIC_ALIAS(sys_time, libc_sys_time)

/* time32_t time(time32_t *timer) */
.section .text.crt.syscall.Xtime
INTERN_FUNCTION(libc_sys_Xtime)
	.cfi_startproc
	movq   $(0xc9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtime)
DEFINE_PUBLIC_ALIAS(sys_Xtime, libc_sys_Xtime)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.crt.syscall.futex
INTERN_FUNCTION(libc_sys_futex)
	.cfi_startproc
	movq   $(0xca), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_futex)
DEFINE_PUBLIC_ALIAS(sys_futex, libc_sys_futex)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.crt.syscall.Xfutex
INTERN_FUNCTION(libc_sys_Xfutex)
	.cfi_startproc
	movq   $(0xca), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfutex)
DEFINE_PUBLIC_ALIAS(sys_Xfutex, libc_sys_Xfutex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.crt.syscall.sched_setaffinity
INTERN_FUNCTION(libc_sys_sched_setaffinity)
	.cfi_startproc
	movq   $(0xcb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_setaffinity, libc_sys_sched_setaffinity)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.crt.syscall.Xsched_setaffinity
INTERN_FUNCTION(libc_sys_Xsched_setaffinity)
	.cfi_startproc
	movq   $(0xcb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setaffinity, libc_sys_Xsched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.crt.syscall.sched_getaffinity
INTERN_FUNCTION(libc_sys_sched_getaffinity)
	.cfi_startproc
	movq   $(0xcc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_getaffinity, libc_sys_sched_getaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.crt.syscall.Xsched_getaffinity
INTERN_FUNCTION(libc_sys_Xsched_getaffinity)
	.cfi_startproc
	movq   $(0xcc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getaffinity, libc_sys_Xsched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_thread_area
INTERN_FUNCTION(libc_sys_set_thread_area)
	.cfi_startproc
	movq   $(0xcd), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_thread_area)
DEFINE_PUBLIC_ALIAS(sys_set_thread_area, libc_sys_set_thread_area)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_thread_area
INTERN_FUNCTION(libc_sys_Xset_thread_area)
	.cfi_startproc
	movq   $(0xcd), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_thread_area)
DEFINE_PUBLIC_ALIAS(sys_Xset_thread_area, libc_sys_Xset_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_setup
INTERN_FUNCTION(libc_sys_io_setup)
	.cfi_startproc
	movq   $(0xce), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_setup)
DEFINE_PUBLIC_ALIAS(sys_io_setup, libc_sys_io_setup)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_setup
INTERN_FUNCTION(libc_sys_Xio_setup)
	.cfi_startproc
	movq   $(0xce), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_setup, libc_sys_Xio_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_destroy
INTERN_FUNCTION(libc_sys_io_destroy)
	.cfi_startproc
	movq   $(0xcf), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_destroy)
DEFINE_PUBLIC_ALIAS(sys_io_destroy, libc_sys_io_destroy)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_destroy
INTERN_FUNCTION(libc_sys_Xio_destroy)
	.cfi_startproc
	movq   $(0xcf), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_destroy)
DEFINE_PUBLIC_ALIAS(sys_Xio_destroy, libc_sys_Xio_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_getevents
INTERN_FUNCTION(libc_sys_io_getevents)
	.cfi_startproc
	movq   $(0xd0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_getevents)
DEFINE_PUBLIC_ALIAS(sys_io_getevents, libc_sys_io_getevents)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_getevents
INTERN_FUNCTION(libc_sys_Xio_getevents)
	.cfi_startproc
	movq   $(0xd0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_getevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_getevents, libc_sys_Xio_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_submit
INTERN_FUNCTION(libc_sys_io_submit)
	.cfi_startproc
	movq   $(0xd1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_submit)
DEFINE_PUBLIC_ALIAS(sys_io_submit, libc_sys_io_submit)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_submit
INTERN_FUNCTION(libc_sys_Xio_submit)
	.cfi_startproc
	movq   $(0xd1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_submit)
DEFINE_PUBLIC_ALIAS(sys_Xio_submit, libc_sys_Xio_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_cancel
INTERN_FUNCTION(libc_sys_io_cancel)
	.cfi_startproc
	movq   $(0xd2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_cancel)
DEFINE_PUBLIC_ALIAS(sys_io_cancel, libc_sys_io_cancel)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_cancel
INTERN_FUNCTION(libc_sys_Xio_cancel)
	.cfi_startproc
	movq   $(0xd2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_cancel)
DEFINE_PUBLIC_ALIAS(sys_Xio_cancel, libc_sys_Xio_cancel)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_thread_area
INTERN_FUNCTION(libc_sys_get_thread_area)
	.cfi_startproc
	movq   $(0xd3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_thread_area)
DEFINE_PUBLIC_ALIAS(sys_get_thread_area, libc_sys_get_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_thread_area
INTERN_FUNCTION(libc_sys_Xget_thread_area)
	.cfi_startproc
	movq   $(0xd3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_thread_area)
DEFINE_PUBLIC_ALIAS(sys_Xget_thread_area, libc_sys_Xget_thread_area)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.crt.syscall.lookup_dcookie
INTERN_FUNCTION(libc_sys_lookup_dcookie)
	.cfi_startproc
	movq   $(0xd4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_lookup_dcookie, libc_sys_lookup_dcookie)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xlookup_dcookie
INTERN_FUNCTION(libc_sys_Xlookup_dcookie)
	.cfi_startproc
	movq   $(0xd4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_Xlookup_dcookie, libc_sys_Xlookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.crt.syscall.epoll_create
INTERN_FUNCTION(libc_sys_epoll_create)
	.cfi_startproc
	movq   $(0xd5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_create)
DEFINE_PUBLIC_ALIAS(sys_epoll_create, libc_sys_epoll_create)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.crt.syscall.Xepoll_create
INTERN_FUNCTION(libc_sys_Xepoll_create)
	.cfi_startproc
	movq   $(0xd5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_create)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create, libc_sys_Xepoll_create)

/* @param: op: One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL', `EPOLL_CTL_MOD' */
/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.epoll_ctl_old
INTERN_FUNCTION(libc_sys_epoll_ctl_old)
	.cfi_startproc
	movq   $(0xd6), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_ctl_old)
DEFINE_PUBLIC_ALIAS(sys_epoll_ctl_old, libc_sys_epoll_ctl_old)

/* @param: op: One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL', `EPOLL_CTL_MOD' */
/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.Xepoll_ctl_old
INTERN_FUNCTION(libc_sys_Xepoll_ctl_old)
	.cfi_startproc
	movq   $(0xd6), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_ctl_old)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_ctl_old, libc_sys_Xepoll_ctl_old)

/* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.epoll_wait_old
INTERN_FUNCTION(libc_sys_epoll_wait_old)
	.cfi_startproc
	movq   $(0xd7), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_wait_old)
DEFINE_PUBLIC_ALIAS(sys_epoll_wait_old, libc_sys_epoll_wait_old)

/* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.Xepoll_wait_old
INTERN_FUNCTION(libc_sys_Xepoll_wait_old)
	.cfi_startproc
	movq   $(0xd7), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_wait_old)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_wait_old, libc_sys_Xepoll_wait_old)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.crt.syscall.remap_file_pages
INTERN_FUNCTION(libc_sys_remap_file_pages)
	.cfi_startproc
	movq   $(0xd8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_remap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_remap_file_pages, libc_sys_remap_file_pages)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.crt.syscall.Xremap_file_pages
INTERN_FUNCTION(libc_sys_Xremap_file_pages)
	.cfi_startproc
	movq   $(0xd8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xremap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_Xremap_file_pages, libc_sys_Xremap_file_pages)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
.section .text.crt.syscall.getdents64
INTERN_FUNCTION(libc_sys_getdents64)
	.cfi_startproc
	movq   $(0xd9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdents64)
DEFINE_PUBLIC_ALIAS(sys_getdents64, libc_sys_getdents64)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
.section .text.crt.syscall.Xgetdents64
INTERN_FUNCTION(libc_sys_Xgetdents64)
	.cfi_startproc
	movq   $(0xd9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdents64)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents64, libc_sys_Xgetdents64)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.crt.syscall.set_tid_address
INTERN_FUNCTION(libc_sys_set_tid_address)
	.cfi_startproc
	movq   $(0xda), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_tid_address)
DEFINE_PUBLIC_ALIAS(sys_set_tid_address, libc_sys_set_tid_address)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.crt.syscall.Xset_tid_address
INTERN_FUNCTION(libc_sys_Xset_tid_address)
	.cfi_startproc
	movq   $(0xda), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_tid_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_tid_address, libc_sys_Xset_tid_address)

/* errno_t restart_syscall(void) */
.section .text.crt.syscall.restart_syscall
INTERN_FUNCTION(libc_sys_restart_syscall)
	.cfi_startproc
	movq   $(0xdb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_restart_syscall)
DEFINE_PUBLIC_ALIAS(sys_restart_syscall, libc_sys_restart_syscall)

/* errno_t restart_syscall(void) */
.section .text.crt.syscall.Xrestart_syscall
INTERN_FUNCTION(libc_sys_Xrestart_syscall)
	.cfi_startproc
	movq   $(0xdb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrestart_syscall)
DEFINE_PUBLIC_ALIAS(sys_Xrestart_syscall, libc_sys_Xrestart_syscall)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.semtimedop
INTERN_FUNCTION(libc_sys_semtimedop)
	.cfi_startproc
	movq   $(0xdc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_semtimedop)
DEFINE_PUBLIC_ALIAS(sys_semtimedop, libc_sys_semtimedop)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsemtimedop
INTERN_FUNCTION(libc_sys_Xsemtimedop)
	.cfi_startproc
	movq   $(0xdc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsemtimedop)
DEFINE_PUBLIC_ALIAS(sys_Xsemtimedop, libc_sys_Xsemtimedop)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fadvise64
INTERN_FUNCTION(libc_sys_fadvise64)
	.cfi_startproc
	movq   $(0xdd), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fadvise64)
DEFINE_PUBLIC_ALIAS(sys_fadvise64, libc_sys_fadvise64)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfadvise64
INTERN_FUNCTION(libc_sys_Xfadvise64)
	.cfi_startproc
	movq   $(0xdd), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfadvise64)
DEFINE_PUBLIC_ALIAS(sys_Xfadvise64, libc_sys_Xfadvise64)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.crt.syscall.timer_create
INTERN_FUNCTION(libc_sys_timer_create)
	.cfi_startproc
	movq   $(0xde), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_create)
DEFINE_PUBLIC_ALIAS(sys_timer_create, libc_sys_timer_create)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.crt.syscall.Xtimer_create
INTERN_FUNCTION(libc_sys_Xtimer_create)
	.cfi_startproc
	movq   $(0xde), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_create, libc_sys_Xtimer_create)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx64 const *value, struct itimerspecx64 *ovalue) */
.section .text.crt.syscall.timer_settime
INTERN_FUNCTION(libc_sys_timer_settime)
	.cfi_startproc
	movq   $(0xdf), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_settime)
DEFINE_PUBLIC_ALIAS(sys_timer_settime, libc_sys_timer_settime)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx64 const *value, struct itimerspecx64 *ovalue) */
.section .text.crt.syscall.Xtimer_settime
INTERN_FUNCTION(libc_sys_Xtimer_settime)
	.cfi_startproc
	movq   $(0xdf), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_settime, libc_sys_Xtimer_settime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspecx64 *value) */
.section .text.crt.syscall.timer_gettime
INTERN_FUNCTION(libc_sys_timer_gettime)
	.cfi_startproc
	movq   $(0xe0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_gettime)
DEFINE_PUBLIC_ALIAS(sys_timer_gettime, libc_sys_timer_gettime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspecx64 *value) */
.section .text.crt.syscall.Xtimer_gettime
INTERN_FUNCTION(libc_sys_Xtimer_gettime)
	.cfi_startproc
	movq   $(0xe0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_gettime, libc_sys_Xtimer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.crt.syscall.timer_getoverrun
INTERN_FUNCTION(libc_sys_timer_getoverrun)
	.cfi_startproc
	movq   $(0xe1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_timer_getoverrun, libc_sys_timer_getoverrun)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.crt.syscall.Xtimer_getoverrun
INTERN_FUNCTION(libc_sys_Xtimer_getoverrun)
	.cfi_startproc
	movq   $(0xe1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_getoverrun, libc_sys_Xtimer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.crt.syscall.timer_delete
INTERN_FUNCTION(libc_sys_timer_delete)
	.cfi_startproc
	movq   $(0xe2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timer_delete)
DEFINE_PUBLIC_ALIAS(sys_timer_delete, libc_sys_timer_delete)

/* errno_t timer_delete(timer_t timerid) */
.section .text.crt.syscall.Xtimer_delete
INTERN_FUNCTION(libc_sys_Xtimer_delete)
	.cfi_startproc
	movq   $(0xe2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimer_delete)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_delete, libc_sys_Xtimer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct timespecx64 const *tp) */
.section .text.crt.syscall.clock_settime
INTERN_FUNCTION(libc_sys_clock_settime)
	.cfi_startproc
	movq   $(0xe3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_settime)
DEFINE_PUBLIC_ALIAS(sys_clock_settime, libc_sys_clock_settime)

/* errno_t clock_settime(clockid_t clock_id, struct timespecx64 const *tp) */
.section .text.crt.syscall.Xclock_settime
INTERN_FUNCTION(libc_sys_Xclock_settime)
	.cfi_startproc
	movq   $(0xe3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_settime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_settime, libc_sys_Xclock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespecx64 *tp) */
.section .text.crt.syscall.clock_gettime
INTERN_FUNCTION(libc_sys_clock_gettime)
	.cfi_startproc
	movq   $(0xe4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_gettime)
DEFINE_PUBLIC_ALIAS(sys_clock_gettime, libc_sys_clock_gettime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespecx64 *tp) */
.section .text.crt.syscall.Xclock_gettime
INTERN_FUNCTION(libc_sys_Xclock_gettime)
	.cfi_startproc
	movq   $(0xe4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_gettime, libc_sys_Xclock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct timespecx64 *res) */
.section .text.crt.syscall.clock_getres
INTERN_FUNCTION(libc_sys_clock_getres)
	.cfi_startproc
	movq   $(0xe5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_getres)
DEFINE_PUBLIC_ALIAS(sys_clock_getres, libc_sys_clock_getres)

/* errno_t clock_getres(clockid_t clock_id, struct timespecx64 *res) */
.section .text.crt.syscall.Xclock_getres
INTERN_FUNCTION(libc_sys_Xclock_getres)
	.cfi_startproc
	movq   $(0xe5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_getres)
DEFINE_PUBLIC_ALIAS(sys_Xclock_getres, libc_sys_Xclock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx64 const *requested_time, struct timespecx64 *remaining) */
.section .text.crt.syscall.clock_nanosleep
INTERN_FUNCTION(libc_sys_clock_nanosleep)
	.cfi_startproc
	movq   $(0xe6), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_clock_nanosleep, libc_sys_clock_nanosleep)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx64 const *requested_time, struct timespecx64 *remaining) */
.section .text.crt.syscall.Xclock_nanosleep
INTERN_FUNCTION(libc_sys_Xclock_nanosleep)
	.cfi_startproc
	movq   $(0xe6), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xclock_nanosleep, libc_sys_Xclock_nanosleep)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
.section .text.crt.syscall.exit_group
INTERN_FUNCTION(libc_sys_exit_group)
	.cfi_startproc
	movq   $(0xe7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_exit_group)
DEFINE_PUBLIC_ALIAS(sys_exit_group, libc_sys_exit_group)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
.section .text.crt.syscall.Xexit_group
INTERN_FUNCTION(libc_sys_Xexit_group)
	.cfi_startproc
	movq   $(0xe7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexit_group)
DEFINE_PUBLIC_ALIAS(sys_Xexit_group, libc_sys_Xexit_group)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.epoll_wait
INTERN_FUNCTION(libc_sys_epoll_wait)
	.cfi_startproc
	movq   $(0xe8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_wait)
DEFINE_PUBLIC_ALIAS(sys_epoll_wait, libc_sys_epoll_wait)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.crt.syscall.Xepoll_wait
INTERN_FUNCTION(libc_sys_Xepoll_wait)
	.cfi_startproc
	movq   $(0xe8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_wait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_wait, libc_sys_Xepoll_wait)

/* @param: op: One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL', `EPOLL_CTL_MOD' */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.epoll_ctl
INTERN_FUNCTION(libc_sys_epoll_ctl)
	.cfi_startproc
	movq   $(0xe9), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_epoll_ctl, libc_sys_epoll_ctl)

/* @param: op: One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL', `EPOLL_CTL_MOD' */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.crt.syscall.Xepoll_ctl
INTERN_FUNCTION(libc_sys_Xepoll_ctl)
	.cfi_startproc
	movq   $(0xe9), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_ctl, libc_sys_Xepoll_ctl)

/* errno_t tgkill(pid_t tgid, pid_t tid, signo_t signo) */
.section .text.crt.syscall.tgkill
INTERN_FUNCTION(libc_sys_tgkill)
	.cfi_startproc
	movq   $(0xea), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tgkill)
DEFINE_PUBLIC_ALIAS(sys_tgkill, libc_sys_tgkill)

/* errno_t tgkill(pid_t tgid, pid_t tid, signo_t signo) */
.section .text.crt.syscall.Xtgkill
INTERN_FUNCTION(libc_sys_Xtgkill)
	.cfi_startproc
	movq   $(0xea), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtgkill)
DEFINE_PUBLIC_ALIAS(sys_Xtgkill, libc_sys_Xtgkill)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timevalx64 const[2] times) */
.section .text.crt.syscall.utimes
INTERN_FUNCTION(libc_sys_utimes)
	.cfi_startproc
	movq   $(0xeb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utimes)
DEFINE_PUBLIC_ALIAS(sys_utimes, libc_sys_utimes)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timevalx64 const[2] times) */
.section .text.crt.syscall.Xutimes
INTERN_FUNCTION(libc_sys_Xutimes)
	.cfi_startproc
	movq   $(0xeb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutimes)
DEFINE_PUBLIC_ALIAS(sys_Xutimes, libc_sys_Xutimes)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.crt.syscall.vserver
INTERN_FUNCTION(libc_sys_vserver)
	.cfi_startproc
	movq   $(0xec), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vserver)
DEFINE_PUBLIC_ALIAS(sys_vserver, libc_sys_vserver)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xvserver
INTERN_FUNCTION(libc_sys_Xvserver)
	.cfi_startproc
	movq   $(0xec), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvserver)
DEFINE_PUBLIC_ALIAS(sys_Xvserver, libc_sys_Xvserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.crt.syscall.mbind
INTERN_FUNCTION(libc_sys_mbind)
	.cfi_startproc
	movq   $(0xed), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mbind)
DEFINE_PUBLIC_ALIAS(sys_mbind, libc_sys_mbind)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmbind
INTERN_FUNCTION(libc_sys_Xmbind)
	.cfi_startproc
	movq   $(0xed), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmbind)
DEFINE_PUBLIC_ALIAS(sys_Xmbind, libc_sys_Xmbind)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_mempolicy
INTERN_FUNCTION(libc_sys_set_mempolicy)
	.cfi_startproc
	movq   $(0xee), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_set_mempolicy, libc_sys_set_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_mempolicy
INTERN_FUNCTION(libc_sys_Xset_mempolicy)
	.cfi_startproc
	movq   $(0xee), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xset_mempolicy, libc_sys_Xset_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_mempolicy
INTERN_FUNCTION(libc_sys_get_mempolicy)
	.cfi_startproc
	movq   $(0xef), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_get_mempolicy, libc_sys_get_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_mempolicy
INTERN_FUNCTION(libc_sys_Xget_mempolicy)
	.cfi_startproc
	movq   $(0xef), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xget_mempolicy, libc_sys_Xget_mempolicy)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.mq_open
INTERN_FUNCTION(libc_sys_mq_open)
	.cfi_startproc
	movq   $(0xf0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_open)
DEFINE_PUBLIC_ALIAS(sys_mq_open, libc_sys_mq_open)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.Xmq_open
INTERN_FUNCTION(libc_sys_Xmq_open)
	.cfi_startproc
	movq   $(0xf0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_open)
DEFINE_PUBLIC_ALIAS(sys_Xmq_open, libc_sys_Xmq_open)

/* errno_t mq_unlink(char const *name) */
.section .text.crt.syscall.mq_unlink
INTERN_FUNCTION(libc_sys_mq_unlink)
	.cfi_startproc
	movq   $(0xf1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_unlink)
DEFINE_PUBLIC_ALIAS(sys_mq_unlink, libc_sys_mq_unlink)

/* errno_t mq_unlink(char const *name) */
.section .text.crt.syscall.Xmq_unlink
INTERN_FUNCTION(libc_sys_Xmq_unlink)
	.cfi_startproc
	movq   $(0xf1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_unlink)
DEFINE_PUBLIC_ALIAS(sys_Xmq_unlink, libc_sys_Xmq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx64 const *abs_timeout) */
.section .text.crt.syscall.mq_timedsend
INTERN_FUNCTION(libc_sys_mq_timedsend)
	.cfi_startproc
	movq   $(0xf2), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_mq_timedsend, libc_sys_mq_timedsend)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx64 const *abs_timeout) */
.section .text.crt.syscall.Xmq_timedsend
INTERN_FUNCTION(libc_sys_Xmq_timedsend)
	.cfi_startproc
	movq   $(0xf2), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedsend, libc_sys_Xmq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx64 const *abs_timeout) */
.section .text.crt.syscall.mq_timedreceive
INTERN_FUNCTION(libc_sys_mq_timedreceive)
	.cfi_startproc
	movq   $(0xf3), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_mq_timedreceive, libc_sys_mq_timedreceive)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx64 const *abs_timeout) */
.section .text.crt.syscall.Xmq_timedreceive
INTERN_FUNCTION(libc_sys_Xmq_timedreceive)
	.cfi_startproc
	movq   $(0xf3), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedreceive, libc_sys_Xmq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
.section .text.crt.syscall.mq_notify
INTERN_FUNCTION(libc_sys_mq_notify)
	.cfi_startproc
	movq   $(0xf4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_notify)
DEFINE_PUBLIC_ALIAS(sys_mq_notify, libc_sys_mq_notify)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
.section .text.crt.syscall.Xmq_notify
INTERN_FUNCTION(libc_sys_Xmq_notify)
	.cfi_startproc
	movq   $(0xf4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_notify)
DEFINE_PUBLIC_ALIAS(sys_Xmq_notify, libc_sys_Xmq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
.section .text.crt.syscall.mq_getsetattr
INTERN_FUNCTION(libc_sys_mq_getsetattr)
	.cfi_startproc
	movq   $(0xf5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_mq_getsetattr, libc_sys_mq_getsetattr)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
.section .text.crt.syscall.Xmq_getsetattr
INTERN_FUNCTION(libc_sys_Xmq_getsetattr)
	.cfi_startproc
	movq   $(0xf5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_Xmq_getsetattr, libc_sys_Xmq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.kexec_load
INTERN_FUNCTION(libc_sys_kexec_load)
	.cfi_startproc
	movq   $(0xf6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kexec_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_load, libc_sys_kexec_load)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkexec_load
INTERN_FUNCTION(libc_sys_Xkexec_load)
	.cfi_startproc
	movq   $(0xf6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkexec_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_load, libc_sys_Xkexec_load)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox64_struct *infop, syscall_ulong_t options, struct rusagex64 *ru) */
.section .text.crt.syscall.waitid
INTERN_FUNCTION(libc_sys_waitid)
	.cfi_startproc
	movq   $(0xf7), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_waitid)
DEFINE_PUBLIC_ALIAS(sys_waitid, libc_sys_waitid)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox64_struct *infop, syscall_ulong_t options, struct rusagex64 *ru) */
.section .text.crt.syscall.Xwaitid
INTERN_FUNCTION(libc_sys_Xwaitid)
	.cfi_startproc
	movq   $(0xf7), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwaitid)
DEFINE_PUBLIC_ALIAS(sys_Xwaitid, libc_sys_Xwaitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.add_key
INTERN_FUNCTION(libc_sys_add_key)
	.cfi_startproc
	movq   $(0xf8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_add_key)
DEFINE_PUBLIC_ALIAS(sys_add_key, libc_sys_add_key)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xadd_key
INTERN_FUNCTION(libc_sys_Xadd_key)
	.cfi_startproc
	movq   $(0xf8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xadd_key)
DEFINE_PUBLIC_ALIAS(sys_Xadd_key, libc_sys_Xadd_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.request_key
INTERN_FUNCTION(libc_sys_request_key)
	.cfi_startproc
	movq   $(0xf9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_request_key)
DEFINE_PUBLIC_ALIAS(sys_request_key, libc_sys_request_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xrequest_key
INTERN_FUNCTION(libc_sys_Xrequest_key)
	.cfi_startproc
	movq   $(0xf9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrequest_key)
DEFINE_PUBLIC_ALIAS(sys_Xrequest_key, libc_sys_Xrequest_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.keyctl
INTERN_FUNCTION(libc_sys_keyctl)
	.cfi_startproc
	movq   $(0xfa), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_keyctl)
DEFINE_PUBLIC_ALIAS(sys_keyctl, libc_sys_keyctl)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkeyctl
INTERN_FUNCTION(libc_sys_Xkeyctl)
	.cfi_startproc
	movq   $(0xfa), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkeyctl)
DEFINE_PUBLIC_ALIAS(sys_Xkeyctl, libc_sys_Xkeyctl)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
.section .text.crt.syscall.ioprio_set
INTERN_FUNCTION(libc_sys_ioprio_set)
	.cfi_startproc
	movq   $(0xfb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioprio_set)
DEFINE_PUBLIC_ALIAS(sys_ioprio_set, libc_sys_ioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
.section .text.crt.syscall.Xioprio_set
INTERN_FUNCTION(libc_sys_Xioprio_set)
	.cfi_startproc
	movq   $(0xfb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioprio_set)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_set, libc_sys_Xioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
.section .text.crt.syscall.ioprio_get
INTERN_FUNCTION(libc_sys_ioprio_get)
	.cfi_startproc
	movq   $(0xfc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioprio_get)
DEFINE_PUBLIC_ALIAS(sys_ioprio_get, libc_sys_ioprio_get)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
.section .text.crt.syscall.Xioprio_get
INTERN_FUNCTION(libc_sys_Xioprio_get)
	.cfi_startproc
	movq   $(0xfc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioprio_get)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_get, libc_sys_Xioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_init
INTERN_FUNCTION(libc_sys_inotify_init)
	.cfi_startproc
	movq   $(0xfd), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_inotify_init)
DEFINE_PUBLIC_ALIAS(sys_inotify_init, libc_sys_inotify_init)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_init
INTERN_FUNCTION(libc_sys_Xinotify_init)
	.cfi_startproc
	movq   $(0xfd), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xinotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init, libc_sys_Xinotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_add_watch
INTERN_FUNCTION(libc_sys_inotify_add_watch)
	.cfi_startproc
	movq   $(0xfe), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_inotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_add_watch, libc_sys_inotify_add_watch)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_add_watch
INTERN_FUNCTION(libc_sys_Xinotify_add_watch)
	.cfi_startproc
	movq   $(0xfe), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xinotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_add_watch, libc_sys_Xinotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_rm_watch
INTERN_FUNCTION(libc_sys_inotify_rm_watch)
	.cfi_startproc
	movq   $(0xff), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_inotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_rm_watch, libc_sys_inotify_rm_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_rm_watch
INTERN_FUNCTION(libc_sys_Xinotify_rm_watch)
	.cfi_startproc
	movq   $(0xff), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xinotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_rm_watch, libc_sys_Xinotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.migrate_pages
INTERN_FUNCTION(libc_sys_migrate_pages)
	.cfi_startproc
	movq   $(0x100), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_migrate_pages)
DEFINE_PUBLIC_ALIAS(sys_migrate_pages, libc_sys_migrate_pages)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmigrate_pages
INTERN_FUNCTION(libc_sys_Xmigrate_pages)
	.cfi_startproc
	movq   $(0x100), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmigrate_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmigrate_pages, libc_sys_Xmigrate_pages)

/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.openat
INTERN_FUNCTION(libc_sys_openat)
	.cfi_startproc
	movq   $(0x101), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_openat)
DEFINE_PUBLIC_ALIAS(sys_openat, libc_sys_openat)

/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.crt.syscall.Xopenat
INTERN_FUNCTION(libc_sys_Xopenat)
	.cfi_startproc
	movq   $(0x101), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopenat)
DEFINE_PUBLIC_ALIAS(sys_Xopenat, libc_sys_Xopenat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.crt.syscall.mkdirat
INTERN_FUNCTION(libc_sys_mkdirat)
	.cfi_startproc
	movq   $(0x102), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mkdirat)
DEFINE_PUBLIC_ALIAS(sys_mkdirat, libc_sys_mkdirat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.crt.syscall.Xmkdirat
INTERN_FUNCTION(libc_sys_Xmkdirat)
	.cfi_startproc
	movq   $(0x102), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xmkdirat, libc_sys_Xmkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.mknodat
INTERN_FUNCTION(libc_sys_mknodat)
	.cfi_startproc
	movq   $(0x103), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mknodat)
DEFINE_PUBLIC_ALIAS(sys_mknodat, libc_sys_mknodat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.crt.syscall.Xmknodat
INTERN_FUNCTION(libc_sys_Xmknodat)
	.cfi_startproc
	movq   $(0x103), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xmknodat, libc_sys_Xmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.crt.syscall.fchownat
INTERN_FUNCTION(libc_sys_fchownat)
	.cfi_startproc
	movq   $(0x104), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchownat)
DEFINE_PUBLIC_ALIAS(sys_fchownat, libc_sys_fchownat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.crt.syscall.Xfchownat
INTERN_FUNCTION(libc_sys_Xfchownat)
	.cfi_startproc
	movq   $(0x104), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchownat)
DEFINE_PUBLIC_ALIAS(sys_Xfchownat, libc_sys_Xfchownat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx64 const[2] times) */
.section .text.crt.syscall.futimesat
INTERN_FUNCTION(libc_sys_futimesat)
	.cfi_startproc
	movq   $(0x105), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_futimesat)
DEFINE_PUBLIC_ALIAS(sys_futimesat, libc_sys_futimesat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx64 const[2] times) */
.section .text.crt.syscall.Xfutimesat
INTERN_FUNCTION(libc_sys_Xfutimesat)
	.cfi_startproc
	movq   $(0x105), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfutimesat)
DEFINE_PUBLIC_ALIAS(sys_Xfutimesat, libc_sys_Xfutimesat)

/* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
.section .text.crt.syscall.newfstatat
INTERN_FUNCTION(libc_sys_newfstatat)
	.cfi_startproc
	movq   $(0x106), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_newfstatat)
DEFINE_PUBLIC_ALIAS(sys_newfstatat, libc_sys_newfstatat)

/* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
.section .text.crt.syscall.Xnewfstatat
INTERN_FUNCTION(libc_sys_Xnewfstatat)
	.cfi_startproc
	movq   $(0x106), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xnewfstatat)
DEFINE_PUBLIC_ALIAS(sys_Xnewfstatat, libc_sys_Xnewfstatat)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.crt.syscall.unlinkat
INTERN_FUNCTION(libc_sys_unlinkat)
	.cfi_startproc
	movq   $(0x107), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unlinkat)
DEFINE_PUBLIC_ALIAS(sys_unlinkat, libc_sys_unlinkat)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.crt.syscall.Xunlinkat
INTERN_FUNCTION(libc_sys_Xunlinkat)
	.cfi_startproc
	movq   $(0x107), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xunlinkat, libc_sys_Xunlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.crt.syscall.renameat
INTERN_FUNCTION(libc_sys_renameat)
	.cfi_startproc
	movq   $(0x108), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_renameat)
DEFINE_PUBLIC_ALIAS(sys_renameat, libc_sys_renameat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.crt.syscall.Xrenameat
INTERN_FUNCTION(libc_sys_Xrenameat)
	.cfi_startproc
	movq   $(0x108), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrenameat)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat, libc_sys_Xrenameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.linkat
INTERN_FUNCTION(libc_sys_linkat)
	.cfi_startproc
	movq   $(0x109), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_linkat)
DEFINE_PUBLIC_ALIAS(sys_linkat, libc_sys_linkat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.Xlinkat
INTERN_FUNCTION(libc_sys_Xlinkat)
	.cfi_startproc
	movq   $(0x109), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xlinkat, libc_sys_Xlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.crt.syscall.symlinkat
INTERN_FUNCTION(libc_sys_symlinkat)
	.cfi_startproc
	movq   $(0x10a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_symlinkat)
DEFINE_PUBLIC_ALIAS(sys_symlinkat, libc_sys_symlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.crt.syscall.Xsymlinkat
INTERN_FUNCTION(libc_sys_Xsymlinkat)
	.cfi_startproc
	movq   $(0x10a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xsymlinkat, libc_sys_Xsymlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.readlinkat
INTERN_FUNCTION(libc_sys_readlinkat)
	.cfi_startproc
	movq   $(0x10b), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readlinkat)
DEFINE_PUBLIC_ALIAS(sys_readlinkat, libc_sys_readlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.crt.syscall.Xreadlinkat
INTERN_FUNCTION(libc_sys_Xreadlinkat)
	.cfi_startproc
	movq   $(0x10b), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xreadlinkat, libc_sys_Xreadlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.fchmodat
INTERN_FUNCTION(libc_sys_fchmodat)
	.cfi_startproc
	movq   $(0x10c), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchmodat)
DEFINE_PUBLIC_ALIAS(sys_fchmodat, libc_sys_fchmodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.Xfchmodat
INTERN_FUNCTION(libc_sys_Xfchmodat)
	.cfi_startproc
	movq   $(0x10c), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchmodat)
DEFINE_PUBLIC_ALIAS(sys_Xfchmodat, libc_sys_Xfchmodat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.crt.syscall.faccessat
INTERN_FUNCTION(libc_sys_faccessat)
	.cfi_startproc
	movq   $(0x10d), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_faccessat)
DEFINE_PUBLIC_ALIAS(sys_faccessat, libc_sys_faccessat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.crt.syscall.Xfaccessat
INTERN_FUNCTION(libc_sys_Xfaccessat)
	.cfi_startproc
	movq   $(0x10d), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfaccessat)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat, libc_sys_Xfaccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.crt.syscall.pselect6
INTERN_FUNCTION(libc_sys_pselect6)
	.cfi_startproc
	movq   $(0x10e), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pselect6)
DEFINE_PUBLIC_ALIAS(sys_pselect6, libc_sys_pselect6)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.crt.syscall.Xpselect6
INTERN_FUNCTION(libc_sys_Xpselect6)
	.cfi_startproc
	movq   $(0x10e), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpselect6)
DEFINE_PUBLIC_ALIAS(sys_Xpselect6, libc_sys_Xpselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.ppoll
INTERN_FUNCTION(libc_sys_ppoll)
	.cfi_startproc
	movq   $(0x10f), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ppoll)
DEFINE_PUBLIC_ALIAS(sys_ppoll, libc_sys_ppoll)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.crt.syscall.Xppoll
INTERN_FUNCTION(libc_sys_Xppoll)
	.cfi_startproc
	movq   $(0x10f), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xppoll)
DEFINE_PUBLIC_ALIAS(sys_Xppoll, libc_sys_Xppoll)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
.section .text.crt.syscall.unshare
INTERN_FUNCTION(libc_sys_unshare)
	.cfi_startproc
	movq   $(0x110), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_unshare)
DEFINE_PUBLIC_ALIAS(sys_unshare, libc_sys_unshare)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
.section .text.crt.syscall.Xunshare
INTERN_FUNCTION(libc_sys_Xunshare)
	.cfi_startproc
	movq   $(0x110), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xunshare)
DEFINE_PUBLIC_ALIAS(sys_Xunshare, libc_sys_Xunshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.set_robust_list
INTERN_FUNCTION(libc_sys_set_robust_list)
	.cfi_startproc
	movq   $(0x111), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_robust_list)
DEFINE_PUBLIC_ALIAS(sys_set_robust_list, libc_sys_set_robust_list)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xset_robust_list
INTERN_FUNCTION(libc_sys_Xset_robust_list)
	.cfi_startproc
	movq   $(0x111), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xset_robust_list, libc_sys_Xset_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.get_robust_list
INTERN_FUNCTION(libc_sys_get_robust_list)
	.cfi_startproc
	movq   $(0x112), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_robust_list)
DEFINE_PUBLIC_ALIAS(sys_get_robust_list, libc_sys_get_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xget_robust_list
INTERN_FUNCTION(libc_sys_Xget_robust_list)
	.cfi_startproc
	movq   $(0x112), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xget_robust_list, libc_sys_Xget_robust_list)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.splice
INTERN_FUNCTION(libc_sys_splice)
	.cfi_startproc
	movq   $(0x113), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_splice)
DEFINE_PUBLIC_ALIAS(sys_splice, libc_sys_splice)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsplice
INTERN_FUNCTION(libc_sys_Xsplice)
	.cfi_startproc
	movq   $(0x113), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsplice)
DEFINE_PUBLIC_ALIAS(sys_Xsplice, libc_sys_Xsplice)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.tee
INTERN_FUNCTION(libc_sys_tee)
	.cfi_startproc
	movq   $(0x114), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_tee)
DEFINE_PUBLIC_ALIAS(sys_tee, libc_sys_tee)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.Xtee
INTERN_FUNCTION(libc_sys_Xtee)
	.cfi_startproc
	movq   $(0x114), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtee)
DEFINE_PUBLIC_ALIAS(sys_Xtee, libc_sys_Xtee)

/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.sync_file_range
INTERN_FUNCTION(libc_sys_sync_file_range)
	.cfi_startproc
	movq   $(0x115), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sync_file_range)
DEFINE_PUBLIC_ALIAS(sys_sync_file_range, libc_sys_sync_file_range)

/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsync_file_range
INTERN_FUNCTION(libc_sys_Xsync_file_range)
	.cfi_startproc
	movq   $(0x115), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsync_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xsync_file_range, libc_sys_Xsync_file_range)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovecx64 const *iov, size_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.vmsplice
INTERN_FUNCTION(libc_sys_vmsplice)
	.cfi_startproc
	movq   $(0x116), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_vmsplice)
DEFINE_PUBLIC_ALIAS(sys_vmsplice, libc_sys_vmsplice)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovecx64 const *iov, size_t count, syscall_ulong_t flags) */
.section .text.crt.syscall.Xvmsplice
INTERN_FUNCTION(libc_sys_Xvmsplice)
	.cfi_startproc
	movq   $(0x116), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xvmsplice)
DEFINE_PUBLIC_ALIAS(sys_Xvmsplice, libc_sys_Xvmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.move_pages
INTERN_FUNCTION(libc_sys_move_pages)
	.cfi_startproc
	movq   $(0x117), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_move_pages)
DEFINE_PUBLIC_ALIAS(sys_move_pages, libc_sys_move_pages)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmove_pages
INTERN_FUNCTION(libc_sys_Xmove_pages)
	.cfi_startproc
	movq   $(0x117), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmove_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmove_pages, libc_sys_Xmove_pages)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx64 const[2] times, atflag_t flags) */
.section .text.crt.syscall.utimensat
INTERN_FUNCTION(libc_sys_utimensat)
	.cfi_startproc
	movq   $(0x118), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_utimensat)
DEFINE_PUBLIC_ALIAS(sys_utimensat, libc_sys_utimensat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx64 const[2] times, atflag_t flags) */
.section .text.crt.syscall.Xutimensat
INTERN_FUNCTION(libc_sys_Xutimensat)
	.cfi_startproc
	movq   $(0x118), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xutimensat)
DEFINE_PUBLIC_ALIAS(sys_Xutimensat, libc_sys_Xutimensat)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.crt.syscall.epoll_pwait
INTERN_FUNCTION(libc_sys_epoll_pwait)
	.cfi_startproc
	movq   $(0x119), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_epoll_pwait, libc_sys_epoll_pwait)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.crt.syscall.Xepoll_pwait
INTERN_FUNCTION(libc_sys_Xepoll_pwait)
	.cfi_startproc
	movq   $(0x119), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_pwait, libc_sys_Xepoll_pwait)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
.section .text.crt.syscall.signalfd
INTERN_FUNCTION(libc_sys_signalfd)
	.cfi_startproc
	movq   $(0x11a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_signalfd)
DEFINE_PUBLIC_ALIAS(sys_signalfd, libc_sys_signalfd)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
.section .text.crt.syscall.Xsignalfd
INTERN_FUNCTION(libc_sys_Xsignalfd)
	.cfi_startproc
	movq   $(0x11a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsignalfd)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd, libc_sys_Xsignalfd)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.crt.syscall.timerfd_create
INTERN_FUNCTION(libc_sys_timerfd_create)
	.cfi_startproc
	movq   $(0x11b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_create)
DEFINE_PUBLIC_ALIAS(sys_timerfd_create, libc_sys_timerfd_create)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.crt.syscall.Xtimerfd_create
INTERN_FUNCTION(libc_sys_Xtimerfd_create)
	.cfi_startproc
	movq   $(0x11b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_create, libc_sys_Xtimerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.crt.syscall.eventfd
INTERN_FUNCTION(libc_sys_eventfd)
	.cfi_startproc
	movq   $(0x11c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_eventfd)
DEFINE_PUBLIC_ALIAS(sys_eventfd, libc_sys_eventfd)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.crt.syscall.Xeventfd
INTERN_FUNCTION(libc_sys_Xeventfd)
	.cfi_startproc
	movq   $(0x11c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xeventfd)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd, libc_sys_Xeventfd)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.crt.syscall.fallocate
INTERN_FUNCTION(libc_sys_fallocate)
	.cfi_startproc
	movq   $(0x11d), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fallocate)
DEFINE_PUBLIC_ALIAS(sys_fallocate, libc_sys_fallocate)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.crt.syscall.Xfallocate
INTERN_FUNCTION(libc_sys_Xfallocate)
	.cfi_startproc
	movq   $(0x11d), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfallocate)
DEFINE_PUBLIC_ALIAS(sys_Xfallocate, libc_sys_Xfallocate)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags' has the `TFD_TIMER_ABSTIME' flag set the timeout value
 * is absolute. Optionally return the old expiration time in `otmr''
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx64 const *utmr, struct itimerspecx64 *otmr) */
.section .text.crt.syscall.timerfd_settime
INTERN_FUNCTION(libc_sys_timerfd_settime)
	.cfi_startproc
	movq   $(0x11e), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_settime, libc_sys_timerfd_settime)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags' has the `TFD_TIMER_ABSTIME' flag set the timeout value
 * is absolute. Optionally return the old expiration time in `otmr''
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx64 const *utmr, struct itimerspecx64 *otmr) */
.section .text.crt.syscall.Xtimerfd_settime
INTERN_FUNCTION(libc_sys_Xtimerfd_settime)
	.cfi_startproc
	movq   $(0x11e), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_settime, libc_sys_Xtimerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx64 *otmr) */
.section .text.crt.syscall.timerfd_gettime
INTERN_FUNCTION(libc_sys_timerfd_gettime)
	.cfi_startproc
	movq   $(0x11f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_timerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_gettime, libc_sys_timerfd_gettime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx64 *otmr) */
.section .text.crt.syscall.Xtimerfd_gettime
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime)
	.cfi_startproc
	movq   $(0x11f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xtimerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_gettime, libc_sys_Xtimerfd_gettime)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The amount of required memory for the address.
 *                            This may be more than was given, in which case
 *                            the address was truncated and may be invalid.
 *                            If this happens, the caller can still determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
.section .text.crt.syscall.accept4
INTERN_FUNCTION(libc_sys_accept4)
	.cfi_startproc
	movq   $(0x120), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_accept4)
DEFINE_PUBLIC_ALIAS(sys_accept4, libc_sys_accept4)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The amount of required memory for the address.
 *                            This may be more than was given, in which case
 *                            the address was truncated and may be invalid.
 *                            If this happens, the caller can still determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
.section .text.crt.syscall.Xaccept4
INTERN_FUNCTION(libc_sys_Xaccept4)
	.cfi_startproc
	movq   $(0x120), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xaccept4)
DEFINE_PUBLIC_ALIAS(sys_Xaccept4, libc_sys_Xaccept4)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
.section .text.crt.syscall.signalfd4
INTERN_FUNCTION(libc_sys_signalfd4)
	.cfi_startproc
	movq   $(0x121), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_signalfd4)
DEFINE_PUBLIC_ALIAS(sys_signalfd4, libc_sys_signalfd4)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
.section .text.crt.syscall.Xsignalfd4
INTERN_FUNCTION(libc_sys_Xsignalfd4)
	.cfi_startproc
	movq   $(0x121), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsignalfd4)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd4, libc_sys_Xsignalfd4)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.crt.syscall.eventfd2
INTERN_FUNCTION(libc_sys_eventfd2)
	.cfi_startproc
	movq   $(0x122), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_eventfd2)
DEFINE_PUBLIC_ALIAS(sys_eventfd2, libc_sys_eventfd2)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.crt.syscall.Xeventfd2
INTERN_FUNCTION(libc_sys_Xeventfd2)
	.cfi_startproc
	movq   $(0x122), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xeventfd2)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd2, libc_sys_Xeventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.crt.syscall.epoll_create1
INTERN_FUNCTION(libc_sys_epoll_create1)
	.cfi_startproc
	movq   $(0x123), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_epoll_create1)
DEFINE_PUBLIC_ALIAS(sys_epoll_create1, libc_sys_epoll_create1)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.crt.syscall.Xepoll_create1
INTERN_FUNCTION(libc_sys_Xepoll_create1)
	.cfi_startproc
	movq   $(0x123), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xepoll_create1)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create1, libc_sys_Xepoll_create1)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.crt.syscall.dup3
INTERN_FUNCTION(libc_sys_dup3)
	.cfi_startproc
	movq   $(0x124), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_dup3)
DEFINE_PUBLIC_ALIAS(sys_dup3, libc_sys_dup3)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.crt.syscall.Xdup3
INTERN_FUNCTION(libc_sys_Xdup3)
	.cfi_startproc
	movq   $(0x124), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdup3)
DEFINE_PUBLIC_ALIAS(sys_Xdup3, libc_sys_Xdup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.crt.syscall.pipe2
INTERN_FUNCTION(libc_sys_pipe2)
	.cfi_startproc
	movq   $(0x125), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pipe2)
DEFINE_PUBLIC_ALIAS(sys_pipe2, libc_sys_pipe2)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.crt.syscall.Xpipe2
INTERN_FUNCTION(libc_sys_Xpipe2)
	.cfi_startproc
	movq   $(0x125), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpipe2)
DEFINE_PUBLIC_ALIAS(sys_Xpipe2, libc_sys_Xpipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.crt.syscall.inotify_init1
INTERN_FUNCTION(libc_sys_inotify_init1)
	.cfi_startproc
	movq   $(0x126), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_inotify_init1)
DEFINE_PUBLIC_ALIAS(sys_inotify_init1, libc_sys_inotify_init1)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xinotify_init1
INTERN_FUNCTION(libc_sys_Xinotify_init1)
	.cfi_startproc
	movq   $(0x126), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xinotify_init1)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init1, libc_sys_Xinotify_init1)

/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.preadv
INTERN_FUNCTION(libc_sys_preadv)
	.cfi_startproc
	movq   $(0x127), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_preadv)
DEFINE_PUBLIC_ALIAS(sys_preadv, libc_sys_preadv)

/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.Xpreadv
INTERN_FUNCTION(libc_sys_Xpreadv)
	.cfi_startproc
	movq   $(0x127), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpreadv)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv, libc_sys_Xpreadv)

/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.pwritev
INTERN_FUNCTION(libc_sys_pwritev)
	.cfi_startproc
	movq   $(0x128), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwritev)
DEFINE_PUBLIC_ALIAS(sys_pwritev, libc_sys_pwritev)

/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
.section .text.crt.syscall.Xpwritev
INTERN_FUNCTION(libc_sys_Xpwritev)
	.cfi_startproc
	movq   $(0x128), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwritev)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev, libc_sys_Xpwritev)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
.section .text.crt.syscall.rt_tgsigqueueinfo
INTERN_FUNCTION(libc_sys_rt_tgsigqueueinfo)
	.cfi_startproc
	movq   $(0x129), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_tgsigqueueinfo, libc_sys_rt_tgsigqueueinfo)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
.section .text.crt.syscall.Xrt_tgsigqueueinfo
INTERN_FUNCTION(libc_sys_Xrt_tgsigqueueinfo)
	.cfi_startproc
	movq   $(0x129), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_tgsigqueueinfo, libc_sys_Xrt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.perf_event_open
INTERN_FUNCTION(libc_sys_perf_event_open)
	.cfi_startproc
	movq   $(0x12a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_perf_event_open)
DEFINE_PUBLIC_ALIAS(sys_perf_event_open, libc_sys_perf_event_open)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xperf_event_open
INTERN_FUNCTION(libc_sys_Xperf_event_open)
	.cfi_startproc
	movq   $(0x12a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xperf_event_open)
DEFINE_PUBLIC_ALIAS(sys_Xperf_event_open, libc_sys_Xperf_event_open)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx64 const *tmo) */
.section .text.crt.syscall.recvmmsg
INTERN_FUNCTION(libc_sys_recvmmsg)
	.cfi_startproc
	movq   $(0x12b), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_recvmmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmmsg, libc_sys_recvmmsg)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx64 const *tmo) */
.section .text.crt.syscall.Xrecvmmsg
INTERN_FUNCTION(libc_sys_Xrecvmmsg)
	.cfi_startproc
	movq   $(0x12b), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrecvmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmmsg, libc_sys_Xrecvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fanotify_init
INTERN_FUNCTION(libc_sys_fanotify_init)
	.cfi_startproc
	movq   $(0x12c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fanotify_init)
DEFINE_PUBLIC_ALIAS(sys_fanotify_init, libc_sys_fanotify_init)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfanotify_init
INTERN_FUNCTION(libc_sys_Xfanotify_init)
	.cfi_startproc
	movq   $(0x12c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfanotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_init, libc_sys_Xfanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fanotify_mark
INTERN_FUNCTION(libc_sys_fanotify_mark)
	.cfi_startproc
	movq   $(0x12d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_fanotify_mark, libc_sys_fanotify_mark)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfanotify_mark
INTERN_FUNCTION(libc_sys_Xfanotify_mark)
	.cfi_startproc
	movq   $(0x12d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_mark, libc_sys_Xfanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.crt.syscall.prlimit64
INTERN_FUNCTION(libc_sys_prlimit64)
	.cfi_startproc
	movq   $(0x12e), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_prlimit64)
DEFINE_PUBLIC_ALIAS(sys_prlimit64, libc_sys_prlimit64)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.crt.syscall.Xprlimit64
INTERN_FUNCTION(libc_sys_Xprlimit64)
	.cfi_startproc
	movq   $(0x12e), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprlimit64)
DEFINE_PUBLIC_ALIAS(sys_Xprlimit64, libc_sys_Xprlimit64)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
.section .text.crt.syscall.name_to_handle_at
INTERN_FUNCTION(libc_sys_name_to_handle_at)
	.cfi_startproc
	movq   $(0x12f), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_name_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_name_to_handle_at, libc_sys_name_to_handle_at)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
.section .text.crt.syscall.Xname_to_handle_at
INTERN_FUNCTION(libc_sys_Xname_to_handle_at)
	.cfi_startproc
	movq   $(0x12f), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xname_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xname_to_handle_at, libc_sys_Xname_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
.section .text.crt.syscall.open_by_handle_at
INTERN_FUNCTION(libc_sys_open_by_handle_at)
	.cfi_startproc
	movq   $(0x130), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_open_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_open_by_handle_at, libc_sys_open_by_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
.section .text.crt.syscall.Xopen_by_handle_at
INTERN_FUNCTION(libc_sys_Xopen_by_handle_at)
	.cfi_startproc
	movq   $(0x130), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopen_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xopen_by_handle_at, libc_sys_Xopen_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.crt.syscall.clock_adjtime
INTERN_FUNCTION(libc_sys_clock_adjtime)
	.cfi_startproc
	movq   $(0x131), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_clock_adjtime, libc_sys_clock_adjtime)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xclock_adjtime
INTERN_FUNCTION(libc_sys_Xclock_adjtime)
	.cfi_startproc
	movq   $(0x131), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_adjtime, libc_sys_Xclock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.crt.syscall.syncfs
INTERN_FUNCTION(libc_sys_syncfs)
	.cfi_startproc
	movq   $(0x132), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_syncfs)
DEFINE_PUBLIC_ALIAS(sys_syncfs, libc_sys_syncfs)

/* errno_t syncfs(fd_t fd) */
.section .text.crt.syscall.Xsyncfs
INTERN_FUNCTION(libc_sys_Xsyncfs)
	.cfi_startproc
	movq   $(0x132), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsyncfs)
DEFINE_PUBLIC_ALIAS(sys_Xsyncfs, libc_sys_Xsyncfs)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.sendmmsg
INTERN_FUNCTION(libc_sys_sendmmsg)
	.cfi_startproc
	movq   $(0x133), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sendmmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmmsg, libc_sys_sendmmsg)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
.section .text.crt.syscall.Xsendmmsg
INTERN_FUNCTION(libc_sys_Xsendmmsg)
	.cfi_startproc
	movq   $(0x133), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsendmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmmsg, libc_sys_Xsendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.crt.syscall.setns
INTERN_FUNCTION(libc_sys_setns)
	.cfi_startproc
	movq   $(0x134), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_setns)
DEFINE_PUBLIC_ALIAS(sys_setns, libc_sys_setns)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.crt.syscall.Xsetns
INTERN_FUNCTION(libc_sys_Xsetns)
	.cfi_startproc
	movq   $(0x134), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsetns)
DEFINE_PUBLIC_ALIAS(sys_Xsetns, libc_sys_Xsetns)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.crt.syscall.getcpu
INTERN_FUNCTION(libc_sys_getcpu)
	.cfi_startproc
	movq   $(0x135), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getcpu)
DEFINE_PUBLIC_ALIAS(sys_getcpu, libc_sys_getcpu)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.crt.syscall.Xgetcpu
INTERN_FUNCTION(libc_sys_Xgetcpu)
	.cfi_startproc
	movq   $(0x135), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetcpu)
DEFINE_PUBLIC_ALIAS(sys_Xgetcpu, libc_sys_Xgetcpu)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.process_vm_readv
INTERN_FUNCTION(libc_sys_process_vm_readv)
	.cfi_startproc
	movq   $(0x136), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_process_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_process_vm_readv, libc_sys_process_vm_readv)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.Xprocess_vm_readv
INTERN_FUNCTION(libc_sys_Xprocess_vm_readv)
	.cfi_startproc
	movq   $(0x136), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprocess_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_readv, libc_sys_Xprocess_vm_readv)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.process_vm_writev
INTERN_FUNCTION(libc_sys_process_vm_writev)
	.cfi_startproc
	movq   $(0x137), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_process_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_process_vm_writev, libc_sys_process_vm_writev)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
.section .text.crt.syscall.Xprocess_vm_writev
INTERN_FUNCTION(libc_sys_Xprocess_vm_writev)
	.cfi_startproc
	movq   $(0x137), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xprocess_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_writev, libc_sys_Xprocess_vm_writev)

/* @param: type: One of `KCMP_FILE', `KCMP_FILES', `KCMP_FS', `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.crt.syscall.kcmp
INTERN_FUNCTION(libc_sys_kcmp)
	.cfi_startproc
	movq   $(0x138), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kcmp)
DEFINE_PUBLIC_ALIAS(sys_kcmp, libc_sys_kcmp)

/* @param: type: One of `KCMP_FILE', `KCMP_FILES', `KCMP_FS', `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.crt.syscall.Xkcmp
INTERN_FUNCTION(libc_sys_Xkcmp)
	.cfi_startproc
	movq   $(0x138), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkcmp)
DEFINE_PUBLIC_ALIAS(sys_Xkcmp, libc_sys_Xkcmp)

/* Load a kernel driver from an ELF image `module_image...+=len'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatiblity ends. Since the
 * linux kernel does not implement any semblance of a stable ABI, you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
.section .text.crt.syscall.finit_module
INTERN_FUNCTION(libc_sys_finit_module)
	.cfi_startproc
	movq   $(0x139), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_finit_module)
DEFINE_PUBLIC_ALIAS(sys_finit_module, libc_sys_finit_module)

/* Load a kernel driver from an ELF image `module_image...+=len'
 * This system call exists for linux compatiblity, and is implemented
 * as an alias for `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatiblity ends. Since the
 * linux kernel does not implement any semblance of a stable ABI, you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
.section .text.crt.syscall.Xfinit_module
INTERN_FUNCTION(libc_sys_Xfinit_module)
	.cfi_startproc
	movq   $(0x139), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xfinit_module, libc_sys_Xfinit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sched_setattr
INTERN_FUNCTION(libc_sys_sched_setattr)
	.cfi_startproc
	movq   $(0x13a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_setattr)
DEFINE_PUBLIC_ALIAS(sys_sched_setattr, libc_sys_sched_setattr)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsched_setattr
INTERN_FUNCTION(libc_sys_Xsched_setattr)
	.cfi_startproc
	movq   $(0x13a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_setattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setattr, libc_sys_Xsched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.sched_getattr
INTERN_FUNCTION(libc_sys_sched_getattr)
	.cfi_startproc
	movq   $(0x13b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sched_getattr)
DEFINE_PUBLIC_ALIAS(sys_sched_getattr, libc_sys_sched_getattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xsched_getattr
INTERN_FUNCTION(libc_sys_Xsched_getattr)
	.cfi_startproc
	movq   $(0x13b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsched_getattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getattr, libc_sys_Xsched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE | RENAME_NOREPLACE | RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.crt.syscall.renameat2
INTERN_FUNCTION(libc_sys_renameat2)
	.cfi_startproc
	movq   $(0x13c), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_renameat2)
DEFINE_PUBLIC_ALIAS(sys_renameat2, libc_sys_renameat2)

/* @param: flags: Set of `RENAME_EXCHANGE | RENAME_NOREPLACE | RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.crt.syscall.Xrenameat2
INTERN_FUNCTION(libc_sys_Xrenameat2)
	.cfi_startproc
	movq   $(0x13c), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrenameat2)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat2, libc_sys_Xrenameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.crt.syscall.seccomp
INTERN_FUNCTION(libc_sys_seccomp)
	.cfi_startproc
	movq   $(0x13d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_seccomp)
DEFINE_PUBLIC_ALIAS(sys_seccomp, libc_sys_seccomp)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xseccomp
INTERN_FUNCTION(libc_sys_Xseccomp)
	.cfi_startproc
	movq   $(0x13d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xseccomp)
DEFINE_PUBLIC_ALIAS(sys_Xseccomp, libc_sys_Xseccomp)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
.section .text.crt.syscall.getrandom
INTERN_FUNCTION(libc_sys_getrandom)
	.cfi_startproc
	movq   $(0x13e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getrandom)
DEFINE_PUBLIC_ALIAS(sys_getrandom, libc_sys_getrandom)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
.section .text.crt.syscall.Xgetrandom
INTERN_FUNCTION(libc_sys_Xgetrandom)
	.cfi_startproc
	movq   $(0x13e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetrandom)
DEFINE_PUBLIC_ALIAS(sys_Xgetrandom, libc_sys_Xgetrandom)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_ALLOW_SEALING' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
.section .text.crt.syscall.memfd_create
INTERN_FUNCTION(libc_sys_memfd_create)
	.cfi_startproc
	movq   $(0x13f), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_memfd_create)
DEFINE_PUBLIC_ALIAS(sys_memfd_create, libc_sys_memfd_create)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_ALLOW_SEALING' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
.section .text.crt.syscall.Xmemfd_create
INTERN_FUNCTION(libc_sys_Xmemfd_create)
	.cfi_startproc
	movq   $(0x13f), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmemfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xmemfd_create, libc_sys_Xmemfd_create)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.kexec_file_load
INTERN_FUNCTION(libc_sys_kexec_file_load)
	.cfi_startproc
	movq   $(0x140), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_file_load, libc_sys_kexec_file_load)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xkexec_file_load
INTERN_FUNCTION(libc_sys_Xkexec_file_load)
	.cfi_startproc
	movq   $(0x140), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_file_load, libc_sys_Xkexec_file_load)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.crt.syscall.bpf
INTERN_FUNCTION(libc_sys_bpf)
	.cfi_startproc
	movq   $(0x141), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_bpf)
DEFINE_PUBLIC_ALIAS(sys_bpf, libc_sys_bpf)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xbpf
INTERN_FUNCTION(libc_sys_Xbpf)
	.cfi_startproc
	movq   $(0x141), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xbpf)
DEFINE_PUBLIC_ALIAS(sys_Xbpf, libc_sys_Xbpf)

/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
.section .text.crt.syscall.execveat
INTERN_FUNCTION(libc_sys_execveat)
	.cfi_startproc
	movq   $(0x142), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_execveat)
DEFINE_PUBLIC_ALIAS(sys_execveat, libc_sys_execveat)

/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
.section .text.crt.syscall.Xexecveat
INTERN_FUNCTION(libc_sys_Xexecveat)
	.cfi_startproc
	movq   $(0x142), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xexecveat)
DEFINE_PUBLIC_ALIAS(sys_Xexecveat, libc_sys_Xexecveat)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.userfaultfd
INTERN_FUNCTION(libc_sys_userfaultfd)
	.cfi_startproc
	movq   $(0x143), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_userfaultfd)
DEFINE_PUBLIC_ALIAS(sys_userfaultfd, libc_sys_userfaultfd)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xuserfaultfd
INTERN_FUNCTION(libc_sys_Xuserfaultfd)
	.cfi_startproc
	movq   $(0x143), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xuserfaultfd)
DEFINE_PUBLIC_ALIAS(sys_Xuserfaultfd, libc_sys_Xuserfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.crt.syscall.membarrier
INTERN_FUNCTION(libc_sys_membarrier)
	.cfi_startproc
	movq   $(0x144), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_membarrier)
DEFINE_PUBLIC_ALIAS(sys_membarrier, libc_sys_membarrier)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmembarrier
INTERN_FUNCTION(libc_sys_Xmembarrier)
	.cfi_startproc
	movq   $(0x144), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmembarrier)
DEFINE_PUBLIC_ALIAS(sys_Xmembarrier, libc_sys_Xmembarrier)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.mlock2
INTERN_FUNCTION(libc_sys_mlock2)
	.cfi_startproc
	movq   $(0x145), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mlock2)
DEFINE_PUBLIC_ALIAS(sys_mlock2, libc_sys_mlock2)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
.section .text.crt.syscall.Xmlock2
INTERN_FUNCTION(libc_sys_Xmlock2)
	.cfi_startproc
	movq   $(0x145), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmlock2)
DEFINE_PUBLIC_ALIAS(sys_Xmlock2, libc_sys_Xmlock2)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
.section .text.crt.syscall.copy_file_range
INTERN_FUNCTION(libc_sys_copy_file_range)
	.cfi_startproc
	movq   $(0x146), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_copy_file_range)
DEFINE_PUBLIC_ALIAS(sys_copy_file_range, libc_sys_copy_file_range)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xcopy_file_range
INTERN_FUNCTION(libc_sys_Xcopy_file_range)
	.cfi_startproc
	movq   $(0x146), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcopy_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xcopy_file_range, libc_sys_Xcopy_file_range)

/* errno_t preadv2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.preadv2
INTERN_FUNCTION(libc_sys_preadv2)
	.cfi_startproc
	movq   $(0x147), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_preadv2)
DEFINE_PUBLIC_ALIAS(sys_preadv2, libc_sys_preadv2)

/* errno_t preadv2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpreadv2
INTERN_FUNCTION(libc_sys_Xpreadv2)
	.cfi_startproc
	movq   $(0x147), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpreadv2)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv2, libc_sys_Xpreadv2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.pwritev2
INTERN_FUNCTION(libc_sys_pwritev2)
	.cfi_startproc
	movq   $(0x148), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwritev2)
DEFINE_PUBLIC_ALIAS(sys_pwritev2, libc_sys_pwritev2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xpwritev2
INTERN_FUNCTION(libc_sys_Xpwritev2)
	.cfi_startproc
	movq   $(0x148), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwritev2)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev2, libc_sys_Xpwritev2)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
.section .text.crt.syscall.pkey_mprotect
INTERN_FUNCTION(libc_sys_pkey_mprotect)
	.cfi_startproc
	movq   $(0x149), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_pkey_mprotect, libc_sys_pkey_mprotect)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
.section .text.crt.syscall.Xpkey_mprotect
INTERN_FUNCTION(libc_sys_Xpkey_mprotect)
	.cfi_startproc
	movq   $(0x149), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_mprotect, libc_sys_Xpkey_mprotect)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
.section .text.crt.syscall.pkey_alloc
INTERN_FUNCTION(libc_sys_pkey_alloc)
	.cfi_startproc
	movq   $(0x14a), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_pkey_alloc, libc_sys_pkey_alloc)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
.section .text.crt.syscall.Xpkey_alloc
INTERN_FUNCTION(libc_sys_Xpkey_alloc)
	.cfi_startproc
	movq   $(0x14a), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_alloc, libc_sys_Xpkey_alloc)

/* errno_t pkey_free(syscall_ulong_t key) */
.section .text.crt.syscall.pkey_free
INTERN_FUNCTION(libc_sys_pkey_free)
	.cfi_startproc
	movq   $(0x14b), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pkey_free)
DEFINE_PUBLIC_ALIAS(sys_pkey_free, libc_sys_pkey_free)

/* errno_t pkey_free(syscall_ulong_t key) */
.section .text.crt.syscall.Xpkey_free
INTERN_FUNCTION(libc_sys_Xpkey_free)
	.cfi_startproc
	movq   $(0x14b), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpkey_free)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_free, libc_sys_Xpkey_free)

/* errno_t statx(int TODO_PROTOTYPE) */
.section .text.crt.syscall.statx
INTERN_FUNCTION(libc_sys_statx)
	.cfi_startproc
	movq   $(0x14c), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_statx)
DEFINE_PUBLIC_ALIAS(sys_statx, libc_sys_statx)

/* errno_t statx(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xstatx
INTERN_FUNCTION(libc_sys_Xstatx)
	.cfi_startproc
	movq   $(0x14c), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xstatx)
DEFINE_PUBLIC_ALIAS(sys_Xstatx, libc_sys_Xstatx)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_pgetevents
INTERN_FUNCTION(libc_sys_io_pgetevents)
	.cfi_startproc
	movq   $(0x14d), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_io_pgetevents, libc_sys_io_pgetevents)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_pgetevents
INTERN_FUNCTION(libc_sys_Xio_pgetevents)
	.cfi_startproc
	movq   $(0x14d), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_pgetevents, libc_sys_Xio_pgetevents)

/* errno_t rseq(int TODO_PROTOTYPE) */
.section .text.crt.syscall.rseq
INTERN_FUNCTION(libc_sys_rseq)
	.cfi_startproc
	movq   $(0x14e), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rseq)
DEFINE_PUBLIC_ALIAS(sys_rseq, libc_sys_rseq)

/* errno_t rseq(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xrseq
INTERN_FUNCTION(libc_sys_Xrseq)
	.cfi_startproc
	movq   $(0x14e), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrseq)
DEFINE_PUBLIC_ALIAS(sys_Xrseq, libc_sys_Xrseq)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_TASK'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:               [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox64_struct const *uinfo, syscall_ulong_t flags) */
.section .text.crt.syscall.pidfd_send_signal
INTERN_FUNCTION(libc_sys_pidfd_send_signal)
	.cfi_startproc
	movq   $(0x1a8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_pidfd_send_signal, libc_sys_pidfd_send_signal)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_TASK'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:               [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox64_struct const *uinfo, syscall_ulong_t flags) */
.section .text.crt.syscall.Xpidfd_send_signal
INTERN_FUNCTION(libc_sys_Xpidfd_send_signal)
	.cfi_startproc
	movq   $(0x1a8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_send_signal, libc_sys_Xpidfd_send_signal)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_uring_setup
INTERN_FUNCTION(libc_sys_io_uring_setup)
	.cfi_startproc
	movq   $(0x1a9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_io_uring_setup, libc_sys_io_uring_setup)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_uring_setup
INTERN_FUNCTION(libc_sys_Xio_uring_setup)
	.cfi_startproc
	movq   $(0x1a9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_setup, libc_sys_Xio_uring_setup)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_uring_enter
INTERN_FUNCTION(libc_sys_io_uring_enter)
	.cfi_startproc
	movq   $(0x1aa), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_io_uring_enter, libc_sys_io_uring_enter)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_uring_enter
INTERN_FUNCTION(libc_sys_Xio_uring_enter)
	.cfi_startproc
	movq   $(0x1aa), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_enter, libc_sys_Xio_uring_enter)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
.section .text.crt.syscall.io_uring_register
INTERN_FUNCTION(libc_sys_io_uring_register)
	.cfi_startproc
	movq   $(0x1ab), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_io_uring_register)
DEFINE_PUBLIC_ALIAS(sys_io_uring_register, libc_sys_io_uring_register)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xio_uring_register
INTERN_FUNCTION(libc_sys_Xio_uring_register)
	.cfi_startproc
	movq   $(0x1ab), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xio_uring_register)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_register, libc_sys_Xio_uring_register)

/* errno_t open_tree(int TODO_PROTOTYPE) */
.section .text.crt.syscall.open_tree
INTERN_FUNCTION(libc_sys_open_tree)
	.cfi_startproc
	movq   $(0x1ac), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_open_tree)
DEFINE_PUBLIC_ALIAS(sys_open_tree, libc_sys_open_tree)

/* errno_t open_tree(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xopen_tree
INTERN_FUNCTION(libc_sys_Xopen_tree)
	.cfi_startproc
	movq   $(0x1ac), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopen_tree)
DEFINE_PUBLIC_ALIAS(sys_Xopen_tree, libc_sys_Xopen_tree)

/* errno_t move_mount(int TODO_PROTOTYPE) */
.section .text.crt.syscall.move_mount
INTERN_FUNCTION(libc_sys_move_mount)
	.cfi_startproc
	movq   $(0x1ad), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_move_mount)
DEFINE_PUBLIC_ALIAS(sys_move_mount, libc_sys_move_mount)

/* errno_t move_mount(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xmove_mount
INTERN_FUNCTION(libc_sys_Xmove_mount)
	.cfi_startproc
	movq   $(0x1ad), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmove_mount)
DEFINE_PUBLIC_ALIAS(sys_Xmove_mount, libc_sys_Xmove_mount)

/* errno_t fsopen(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fsopen
INTERN_FUNCTION(libc_sys_fsopen)
	.cfi_startproc
	movq   $(0x1ae), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsopen)
DEFINE_PUBLIC_ALIAS(sys_fsopen, libc_sys_fsopen)

/* errno_t fsopen(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfsopen
INTERN_FUNCTION(libc_sys_Xfsopen)
	.cfi_startproc
	movq   $(0x1ae), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsopen)
DEFINE_PUBLIC_ALIAS(sys_Xfsopen, libc_sys_Xfsopen)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fsconfig
INTERN_FUNCTION(libc_sys_fsconfig)
	.cfi_startproc
	movq   $(0x1af), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsconfig)
DEFINE_PUBLIC_ALIAS(sys_fsconfig, libc_sys_fsconfig)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfsconfig
INTERN_FUNCTION(libc_sys_Xfsconfig)
	.cfi_startproc
	movq   $(0x1af), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsconfig)
DEFINE_PUBLIC_ALIAS(sys_Xfsconfig, libc_sys_Xfsconfig)

/* errno_t fsmount(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fsmount
INTERN_FUNCTION(libc_sys_fsmount)
	.cfi_startproc
	movq   $(0x1b0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsmount)
DEFINE_PUBLIC_ALIAS(sys_fsmount, libc_sys_fsmount)

/* errno_t fsmount(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfsmount
INTERN_FUNCTION(libc_sys_Xfsmount)
	.cfi_startproc
	movq   $(0x1b0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsmount)
DEFINE_PUBLIC_ALIAS(sys_Xfsmount, libc_sys_Xfsmount)

/* errno_t fspick(int TODO_PROTOTYPE) */
.section .text.crt.syscall.fspick
INTERN_FUNCTION(libc_sys_fspick)
	.cfi_startproc
	movq   $(0x1b1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fspick)
DEFINE_PUBLIC_ALIAS(sys_fspick, libc_sys_fspick)

/* errno_t fspick(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfspick
INTERN_FUNCTION(libc_sys_Xfspick)
	.cfi_startproc
	movq   $(0x1b1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfspick)
DEFINE_PUBLIC_ALIAS(sys_Xfspick, libc_sys_Xfspick)

/* Return a `HANDLE_TYPE_TASK' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER:    [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
.section .text.crt.syscall.pidfd_open
INTERN_FUNCTION(libc_sys_pidfd_open)
	.cfi_startproc
	movq   $(0x1b2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pidfd_open)
DEFINE_PUBLIC_ALIAS(sys_pidfd_open, libc_sys_pidfd_open)

/* Return a `HANDLE_TYPE_TASK' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER:    [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
.section .text.crt.syscall.Xpidfd_open
INTERN_FUNCTION(libc_sys_Xpidfd_open)
	.cfi_startproc
	movq   $(0x1b2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpidfd_open)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_open, libc_sys_Xpidfd_open)

/* errno_t clone3(int TODO_PROTOTYPE) */
.section .text.crt.syscall.clone3
INTERN_FUNCTION(libc_sys_clone3)
	.cfi_startproc
	movq   $(0x1b3), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_clone3)
DEFINE_PUBLIC_ALIAS(sys_clone3, libc_sys_clone3)

/* errno_t clone3(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xclone3
INTERN_FUNCTION(libc_sys_Xclone3)
	.cfi_startproc
	movq   $(0x1b3), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclone3)
DEFINE_PUBLIC_ALIAS(sys_Xclone3, libc_sys_Xclone3)

/* errno_t close_range(int TODO_PROTOTYPE) */
.section .text.crt.syscall.close_range
INTERN_FUNCTION(libc_sys_close_range)
	.cfi_startproc
	movq   $(0x1b4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_close_range)
DEFINE_PUBLIC_ALIAS(sys_close_range, libc_sys_close_range)

/* errno_t close_range(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xclose_range
INTERN_FUNCTION(libc_sys_Xclose_range)
	.cfi_startproc
	movq   $(0x1b4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xclose_range)
DEFINE_PUBLIC_ALIAS(sys_Xclose_range, libc_sys_Xclose_range)

/* errno_t openat2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.openat2
INTERN_FUNCTION(libc_sys_openat2)
	.cfi_startproc
	movq   $(0x1b5), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_openat2)
DEFINE_PUBLIC_ALIAS(sys_openat2, libc_sys_openat2)

/* errno_t openat2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xopenat2
INTERN_FUNCTION(libc_sys_Xopenat2)
	.cfi_startproc
	movq   $(0x1b5), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopenat2)
DEFINE_PUBLIC_ALIAS(sys_Xopenat2, libc_sys_Xopenat2)

/* Duplicate the handle of a foreign process into a handle for the caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_TASK'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
.section .text.crt.syscall.pidfd_getfd
INTERN_FUNCTION(libc_sys_pidfd_getfd)
	.cfi_startproc
	movq   $(0x1b6), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_pidfd_getfd, libc_sys_pidfd_getfd)

/* Duplicate the handle of a foreign process into a handle for the caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_TASK'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
.section .text.crt.syscall.Xpidfd_getfd
INTERN_FUNCTION(libc_sys_Xpidfd_getfd)
	.cfi_startproc
	movq   $(0x1b6), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_getfd, libc_sys_Xpidfd_getfd)

/* errno_t faccessat2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.faccessat2
INTERN_FUNCTION(libc_sys_faccessat2)
	.cfi_startproc
	movq   $(0x1b7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_faccessat2)
DEFINE_PUBLIC_ALIAS(sys_faccessat2, libc_sys_faccessat2)

/* errno_t faccessat2(int TODO_PROTOTYPE) */
.section .text.crt.syscall.Xfaccessat2
INTERN_FUNCTION(libc_sys_Xfaccessat2)
	.cfi_startproc
	movq   $(0x1b7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfaccessat2)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat2, libc_sys_Xfaccessat2)

/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pwritevf
INTERN_FUNCTION(libc_sys_pwritevf)
	.cfi_startproc
	movq   $(0xfffffffffffffed8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwritevf)
DEFINE_PUBLIC_ALIAS(sys_pwritevf, libc_sys_pwritevf)

/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpwritevf
INTERN_FUNCTION(libc_sys_Xpwritevf)
	.cfi_startproc
	movq   $(0xfffffffffffffed8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xpwritevf, libc_sys_Xpwritevf)

/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.preadvf
INTERN_FUNCTION(libc_sys_preadvf)
	.cfi_startproc
	movq   $(0xfffffffffffffed9), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_preadvf)
DEFINE_PUBLIC_ALIAS(sys_preadvf, libc_sys_preadvf)

/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpreadvf
INTERN_FUNCTION(libc_sys_Xpreadvf)
	.cfi_startproc
	movq   $(0xfffffffffffffed9), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xpreadvf, libc_sys_Xpreadvf)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.freadlinkat
INTERN_FUNCTION(libc_sys_freadlinkat)
	.cfi_startproc
	movq   $(0xfffffffffffffef5), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_freadlinkat)
DEFINE_PUBLIC_ALIAS(sys_freadlinkat, libc_sys_freadlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.Xfreadlinkat
INTERN_FUNCTION(libc_sys_Xfreadlinkat)
	.cfi_startproc
	movq   $(0xfffffffffffffef5), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfreadlinkat, libc_sys_Xfreadlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.fsymlinkat
INTERN_FUNCTION(libc_sys_fsymlinkat)
	.cfi_startproc
	movq   $(0xfffffffffffffef6), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_fsymlinkat, libc_sys_fsymlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.crt.syscall.Xfsymlinkat
INTERN_FUNCTION(libc_sys_Xfsymlinkat)
	.cfi_startproc
	movq   $(0xfffffffffffffef6), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfsymlinkat, libc_sys_Xfsymlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.crt.syscall.frenameat
INTERN_FUNCTION(libc_sys_frenameat)
	.cfi_startproc
	movq   $(0xfffffffffffffef8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frenameat)
DEFINE_PUBLIC_ALIAS(sys_frenameat, libc_sys_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.crt.syscall.Xfrenameat
INTERN_FUNCTION(libc_sys_Xfrenameat)
	.cfi_startproc
	movq   $(0xfffffffffffffef8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrenameat)
DEFINE_PUBLIC_ALIAS(sys_Xfrenameat, libc_sys_Xfrenameat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_statx64 *statbuf, atflag_t flags) */
.section .text.crt.syscall.kfstatat
INTERN_FUNCTION(libc_sys_kfstatat)
	.cfi_startproc
	movq   $(0xfffffffffffffefa), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kfstatat)
DEFINE_PUBLIC_ALIAS(sys_kfstatat, libc_sys_kfstatat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_statx64 *statbuf, atflag_t flags) */
.section .text.crt.syscall.Xkfstatat
INTERN_FUNCTION(libc_sys_Xkfstatat)
	.cfi_startproc
	movq   $(0xfffffffffffffefa), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkfstatat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstatat, libc_sys_Xkfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.crt.syscall.fmknodat
INTERN_FUNCTION(libc_sys_fmknodat)
	.cfi_startproc
	movq   $(0xfffffffffffffefd), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fmknodat)
DEFINE_PUBLIC_ALIAS(sys_fmknodat, libc_sys_fmknodat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.crt.syscall.Xfmknodat
INTERN_FUNCTION(libc_sys_Xfmknodat)
	.cfi_startproc
	movq   $(0xfffffffffffffefd), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xfmknodat, libc_sys_Xfmknodat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.fmkdirat
INTERN_FUNCTION(libc_sys_fmkdirat)
	.cfi_startproc
	movq   $(0xfffffffffffffefe), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fmkdirat)
DEFINE_PUBLIC_ALIAS(sys_fmkdirat, libc_sys_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.crt.syscall.Xfmkdirat
INTERN_FUNCTION(libc_sys_Xfmkdirat)
	.cfi_startproc
	movq   $(0xfffffffffffffefe), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfmkdirat, libc_sys_Xfmkdirat)

/* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.ksysctl
INTERN_FUNCTION(libc_sys_ksysctl)
	.cfi_startproc
	movq   $(0xffffffffffffff64), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ksysctl)
DEFINE_PUBLIC_ALIAS(sys_ksysctl, libc_sys_ksysctl)

/* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xksysctl
INTERN_FUNCTION(libc_sys_Xksysctl)
	.cfi_startproc
	movq   $(0xffffffffffffff64), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xksysctl)
DEFINE_PUBLIC_ALIAS(sys_Xksysctl, libc_sys_Xksysctl)

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
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr const *hdrv, size_t hdrc) */
.section .text.crt.syscall.maplibrary
INTERN_FUNCTION(libc_sys_maplibrary)
	.cfi_startproc
	movq   $(0xffffffffffffff7a), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_maplibrary)
DEFINE_PUBLIC_ALIAS(sys_maplibrary, libc_sys_maplibrary)

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
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr const *hdrv, size_t hdrc) */
.section .text.crt.syscall.Xmaplibrary
INTERN_FUNCTION(libc_sys_Xmaplibrary)
	.cfi_startproc
	movq   $(0xffffffffffffff7a), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmaplibrary)
DEFINE_PUBLIC_ALIAS(sys_Xmaplibrary, libc_sys_Xmaplibrary)

/* uint64_t fsmode(uint64_t mode) */
.section .text.crt.syscall.fsmode
INTERN_FUNCTION(libc_sys_fsmode)
	.cfi_startproc
	movq   $(0xffffffffffffffa1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fsmode)
DEFINE_PUBLIC_ALIAS(sys_fsmode, libc_sys_fsmode)

/* uint64_t fsmode(uint64_t mode) */
.section .text.crt.syscall.Xfsmode
INTERN_FUNCTION(libc_sys_Xfsmode)
	.cfi_startproc
	movq   $(0xffffffffffffffa1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfsmode)
DEFINE_PUBLIC_ALIAS(sys_Xfsmode, libc_sys_Xfsmode)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.crt.syscall.fchdirat
INTERN_FUNCTION(libc_sys_fchdirat)
	.cfi_startproc
	movq   $(0xffffffffffffffb0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_fchdirat)
DEFINE_PUBLIC_ALIAS(sys_fchdirat, libc_sys_fchdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.crt.syscall.Xfchdirat
INTERN_FUNCTION(libc_sys_Xfchdirat)
	.cfi_startproc
	movq   $(0xffffffffffffffb0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfchdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfchdirat, libc_sys_Xfchdirat)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.crt.syscall.kreaddirf
INTERN_FUNCTION(libc_sys_kreaddirf)
	.cfi_startproc
	movq   $(0xffffffffffffffb1), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kreaddirf)
DEFINE_PUBLIC_ALIAS(sys_kreaddirf, libc_sys_kreaddirf)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.crt.syscall.Xkreaddirf
INTERN_FUNCTION(libc_sys_Xkreaddirf)
	.cfi_startproc
	movq   $(0xffffffffffffffb1), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkreaddirf)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddirf, libc_sys_Xkreaddirf)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.crt.syscall.kreaddir
INTERN_FUNCTION(libc_sys_kreaddir)
	.cfi_startproc
	movq   $(0xffffffffffffffb2), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kreaddir)
DEFINE_PUBLIC_ALIAS(sys_kreaddir, libc_sys_kreaddir)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.crt.syscall.Xkreaddir
INTERN_FUNCTION(libc_sys_Xkreaddir)
	.cfi_startproc
	movq   $(0xffffffffffffffb2), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkreaddir)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddir, libc_sys_Xkreaddir)

/* Check for pending signals, and keep on handling them until none are left
 * The [restart(must)] is necessary in order to ensure that _all_ unmasked
 * signals get handled until none are left, in case more than one signal
 * became available.
 * This system call is only needed when `set_userprocmask_address(2)' was used. */
/* errno_t sigmask_check(void) */
.section .text.crt.syscall.sigmask_check
INTERN_FUNCTION(libc_sys_sigmask_check)
	.cfi_startproc
	movq   $(0xffffffffffffffdb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_sigmask_check)
DEFINE_PUBLIC_ALIAS(sys_sigmask_check, libc_sys_sigmask_check)

/* Check for pending signals, and keep on handling them until none are left
 * The [restart(must)] is necessary in order to ensure that _all_ unmasked
 * signals get handled until none are left, in case more than one signal
 * became available.
 * This system call is only needed when `set_userprocmask_address(2)' was used. */
/* errno_t sigmask_check(void) */
.section .text.crt.syscall.Xsigmask_check
INTERN_FUNCTION(libc_sys_Xsigmask_check)
	.cfi_startproc
	movq   $(0xffffffffffffffdb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xsigmask_check)
DEFINE_PUBLIC_ALIAS(sys_Xsigmask_check, libc_sys_Xsigmask_check)

/* Register the address of the calling thread's userprocmask controller.
 * This also initializes `*ctl->pm_sigmask' and `ctl->pm_pending', such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally, the address of `&ctl->pm_mytid' is stored as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using atomic-or for the later) from this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional, arch-specific fields to all zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the `pm_sigmask'
 *       of the previously set controller into its internal signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though that `pm_sigmask' is ignored for `SIGKILL' and `SIGSTOP'
 * Note also that this function replaces `set_tid_address(2)', such that
 * it negates a prior call to said function, while a future call to said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
.section .text.crt.syscall.set_userprocmask_address
INTERN_FUNCTION(libc_sys_set_userprocmask_address)
	.cfi_startproc
	movq   $(0xffffffffffffffdc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_set_userprocmask_address, libc_sys_set_userprocmask_address)

/* Register the address of the calling thread's userprocmask controller.
 * This also initializes `*ctl->pm_sigmask' and `ctl->pm_pending', such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally, the address of `&ctl->pm_mytid' is stored as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using atomic-or for the later) from this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional, arch-specific fields to all zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the `pm_sigmask'
 *       of the previously set controller into its internal signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though that `pm_sigmask' is ignored for `SIGKILL' and `SIGSTOP'
 * Note also that this function replaces `set_tid_address(2)', such that
 * it negates a prior call to said function, while a future call to said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
.section .text.crt.syscall.Xset_userprocmask_address
INTERN_FUNCTION(libc_sys_Xset_userprocmask_address)
	.cfi_startproc
	movq   $(0xffffffffffffffdc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_userprocmask_address, libc_sys_Xset_userprocmask_address)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
.section .text.crt.syscall.rtm_test
INTERN_FUNCTION(libc_sys_rtm_test)
	.cfi_startproc
	movq   $(0xffffffffffffffdd), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rtm_test)
DEFINE_PUBLIC_ALIAS(sys_rtm_test, libc_sys_rtm_test)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
.section .text.crt.syscall.Xrtm_test
INTERN_FUNCTION(libc_sys_Xrtm_test)
	.cfi_startproc
	movq   $(0xffffffffffffffdd), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrtm_test)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_test, libc_sys_Xrtm_test)

/* Abort the current transaction by having `sys_rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise, this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
.section .text.crt.syscall.rtm_abort
INTERN_FUNCTION(libc_sys_rtm_abort)
	.cfi_startproc
	movq   $(0xffffffffffffffde), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rtm_abort)
DEFINE_PUBLIC_ALIAS(sys_rtm_abort, libc_sys_rtm_abort)

/* Abort the current transaction by having `sys_rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise, this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
.section .text.crt.syscall.Xrtm_abort
INTERN_FUNCTION(libc_sys_Xrtm_abort)
	.cfi_startproc
	movq   $(0xffffffffffffffde), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrtm_abort)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_abort, libc_sys_Xrtm_abort)

/* End a transaction
 * If the transaction was successful, return normally (by returning `-EOK').
 * If the transaction failed, `sys_rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
.section .text.crt.syscall.rtm_end
INTERN_FUNCTION(libc_sys_rtm_end)
	.cfi_startproc
	movq   $(0xffffffffffffffdf), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rtm_end)
DEFINE_PUBLIC_ALIAS(sys_rtm_end, libc_sys_rtm_end)

/* End a transaction
 * If the transaction was successful, return normally (by returning `-EOK').
 * If the transaction failed, `sys_rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
.section .text.crt.syscall.Xrtm_end
INTERN_FUNCTION(libc_sys_Xrtm_end)
	.cfi_startproc
	movq   $(0xffffffffffffffdf), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrtm_end)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_end, libc_sys_Xrtm_end)

/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls will most likely result in an `RTM_ABORT_FAILED' error, and
 * attempting to access too much system memory in general will result in this
 * function returning with `RTM_ABORT_CAPACITY', rather than succeeding.
 * The following is a list of system calls which are whitelisted for use
 * during a transaction:
 *   - sys_rtm_begin:  Nested RTM operation
 *   - sys_rtm_end:    End an RTM operation
 *   - sys_rtm_abort:  Abort an RTM operation
 *   - sys_rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
/* rtm_status_t rtm_begin(void) */
.section .text.crt.syscall.rtm_begin
INTERN_FUNCTION(libc_sys_rtm_begin)
	.cfi_startproc
	movq   $(0xffffffffffffffe0), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rtm_begin)
DEFINE_PUBLIC_ALIAS(sys_rtm_begin, libc_sys_rtm_begin)

/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls will most likely result in an `RTM_ABORT_FAILED' error, and
 * attempting to access too much system memory in general will result in this
 * function returning with `RTM_ABORT_CAPACITY', rather than succeeding.
 * The following is a list of system calls which are whitelisted for use
 * during a transaction:
 *   - sys_rtm_begin:  Nested RTM operation
 *   - sys_rtm_end:    End an RTM operation
 *   - sys_rtm_abort:  Abort an RTM operation
 *   - sys_rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
/* rtm_status_t rtm_begin(void) */
.section .text.crt.syscall.Xrtm_begin
INTERN_FUNCTION(libc_sys_Xrtm_begin)
	.cfi_startproc
	movq   $(0xffffffffffffffe0), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrtm_begin)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_begin, libc_sys_Xrtm_begin)

/* Construct a user-vio-fd object supporting mmap(2), with actual
 * memory accesses being dispatched by adding them as pending requests
 * to an internal queue that should be read(2) from by a worker thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This size may be altered at a later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
.section .text.crt.syscall.userviofd
INTERN_FUNCTION(libc_sys_userviofd)
	.cfi_startproc
	movq   $(0xffffffffffffffe1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_userviofd)
DEFINE_PUBLIC_ALIAS(sys_userviofd, libc_sys_userviofd)

/* Construct a user-vio-fd object supporting mmap(2), with actual
 * memory accesses being dispatched by adding them as pending requests
 * to an internal queue that should be read(2) from by a worker thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This size may be altered at a later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
.section .text.crt.syscall.Xuserviofd
INTERN_FUNCTION(libc_sys_Xuserviofd)
	.cfi_startproc
	movq   $(0xffffffffffffffe1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xuserviofd)
DEFINE_PUBLIC_ALIAS(sys_Xuserviofd, libc_sys_Xuserviofd)

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
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_SUCCESS' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void) const *traceback_vector, size_t traceback_length, struct __exception_data64 const *exception, syscall_ulong_t unwind_error) */
.section .text.crt.syscall.coredump
INTERN_FUNCTION(libc_sys_coredump)
	.cfi_startproc
	movq   $(0xffffffffffffffe3), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_coredump)
DEFINE_PUBLIC_ALIAS(sys_coredump, libc_sys_coredump)

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
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_SUCCESS' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void) const *traceback_vector, size_t traceback_length, struct __exception_data64 const *exception, syscall_ulong_t unwind_error) */
.section .text.crt.syscall.Xcoredump
INTERN_FUNCTION(libc_sys_Xcoredump)
	.cfi_startproc
	movq   $(0xffffffffffffffe3), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xcoredump)
DEFINE_PUBLIC_ALIAS(sys_Xcoredump, libc_sys_Xcoredump)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it. */
/* errno_t raiseat(struct ucpustate64 const *state, struct __siginfox64_struct const *si) */
.section .text.crt.syscall.raiseat
INTERN_FUNCTION(libc_sys_raiseat)
	.cfi_startproc
	movq   $(0xffffffffffffffe4), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_raiseat)
DEFINE_PUBLIC_ALIAS(sys_raiseat, libc_sys_raiseat)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it. */
/* errno_t raiseat(struct ucpustate64 const *state, struct __siginfox64_struct const *si) */
.section .text.crt.syscall.Xraiseat
INTERN_FUNCTION(libc_sys_Xraiseat)
	.cfi_startproc
	movq   $(0xffffffffffffffe4), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xraiseat)
DEFINE_PUBLIC_ALIAS(sys_Xraiseat, libc_sys_Xraiseat)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
.section .text.crt.syscall.mktty
INTERN_FUNCTION(libc_sys_mktty)
	.cfi_startproc
	movq   $(0xffffffffffffffe5), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_mktty)
DEFINE_PUBLIC_ALIAS(sys_mktty, libc_sys_mktty)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
.section .text.crt.syscall.Xmktty
INTERN_FUNCTION(libc_sys_Xmktty)
	.cfi_startproc
	movq   $(0xffffffffffffffe5), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xmktty)
DEFINE_PUBLIC_ALIAS(sys_Xmktty, libc_sys_Xmktty)

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
/* errno_t lfutexlockexpr(uint64_t *ulockaddr, void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.lfutexlockexpr
INTERN_FUNCTION(libc_sys_lfutexlockexpr)
	.cfi_startproc
	movq   $(0xffffffffffffffe6), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutexlockexpr)
DEFINE_PUBLIC_ALIAS(sys_lfutexlockexpr, libc_sys_lfutexlockexpr)

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
/* errno_t lfutexlockexpr(uint64_t *ulockaddr, void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.Xlfutexlockexpr
INTERN_FUNCTION(libc_sys_Xlfutexlockexpr)
	.cfi_startproc
	movq   $(0xffffffffffffffe6), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutexlockexpr)
DEFINE_PUBLIC_ALIAS(sys_Xlfutexlockexpr, libc_sys_Xlfutexlockexpr)

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
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.lfutexexpr
INTERN_FUNCTION(libc_sys_lfutexexpr)
	.cfi_startproc
	movq   $(0xffffffffffffffe7), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_lfutexexpr, libc_sys_lfutexexpr)

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
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.crt.syscall.Xlfutexexpr
INTERN_FUNCTION(libc_sys_Xlfutexexpr)
	.cfi_startproc
	movq   $(0xffffffffffffffe7), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_Xlfutexexpr, libc_sys_Xlfutexexpr)

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
/* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct timespecx64 const *timeout, uint64_t val2) */
.section .text.crt.syscall.lfutex
INTERN_FUNCTION(libc_sys_lfutex)
	.cfi_startproc
	movq   $(0xffffffffffffffe8), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_lfutex)
DEFINE_PUBLIC_ALIAS(sys_lfutex, libc_sys_lfutex)

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
/* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct timespecx64 const *timeout, uint64_t val2) */
.section .text.crt.syscall.Xlfutex
INTERN_FUNCTION(libc_sys_Xlfutex)
	.cfi_startproc
	movq   $(0xffffffffffffffe8), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xlfutex)
DEFINE_PUBLIC_ALIAS(sys_Xlfutex, libc_sys_Xlfutex)

/* syscall_slong_t rpc_service(void) */
.section .text.crt.syscall.rpc_service
INTERN_FUNCTION(libc_sys_rpc_service)
	.cfi_startproc
	movq   $(0xffffffffffffffe9), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rpc_service)
DEFINE_PUBLIC_ALIAS(sys_rpc_service, libc_sys_rpc_service)

/* syscall_slong_t rpc_service(void) */
.section .text.crt.syscall.Xrpc_service
INTERN_FUNCTION(libc_sys_Xrpc_service)
	.cfi_startproc
	movq   $(0xffffffffffffffe9), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrpc_service)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_service, libc_sys_Xrpc_service)

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
/* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
.section .text.crt.syscall.debugtrap
INTERN_FUNCTION(libc_sys_debugtrap)
	.cfi_startproc
	movq   $(0xffffffffffffffea), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_debugtrap)
DEFINE_PUBLIC_ALIAS(sys_debugtrap, libc_sys_debugtrap)

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
/* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
.section .text.crt.syscall.Xdebugtrap
INTERN_FUNCTION(libc_sys_Xdebugtrap)
	.cfi_startproc
	movq   $(0xffffffffffffffea), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdebugtrap)
DEFINE_PUBLIC_ALIAS(sys_Xdebugtrap, libc_sys_Xdebugtrap)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.writevf
INTERN_FUNCTION(libc_sys_writevf)
	.cfi_startproc
	movq   $(0xffffffffffffffec), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writevf)
DEFINE_PUBLIC_ALIAS(sys_writevf, libc_sys_writevf)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.Xwritevf
INTERN_FUNCTION(libc_sys_Xwritevf)
	.cfi_startproc
	movq   $(0xffffffffffffffec), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xwritevf, libc_sys_Xwritevf)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.readvf
INTERN_FUNCTION(libc_sys_readvf)
	.cfi_startproc
	movq   $(0xffffffffffffffed), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readvf)
DEFINE_PUBLIC_ALIAS(sys_readvf, libc_sys_readvf)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
.section .text.crt.syscall.Xreadvf
INTERN_FUNCTION(libc_sys_Xreadvf)
	.cfi_startproc
	movq   $(0xffffffffffffffed), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xreadvf, libc_sys_Xreadvf)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pwrite64f
INTERN_FUNCTION(libc_sys_pwrite64f)
	.cfi_startproc
	movq   $(0xffffffffffffffee), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pwrite64f)
DEFINE_PUBLIC_ALIAS(sys_pwrite64f, libc_sys_pwrite64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpwrite64f
INTERN_FUNCTION(libc_sys_Xpwrite64f)
	.cfi_startproc
	movq   $(0xffffffffffffffee), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpwrite64f)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64f, libc_sys_Xpwrite64f)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.pread64f
INTERN_FUNCTION(libc_sys_pread64f)
	.cfi_startproc
	movq   $(0xffffffffffffffef), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_pread64f)
DEFINE_PUBLIC_ALIAS(sys_pread64f, libc_sys_pread64f)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.crt.syscall.Xpread64f
INTERN_FUNCTION(libc_sys_Xpread64f)
	.cfi_startproc
	movq   $(0xffffffffffffffef), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xpread64f)
DEFINE_PUBLIC_ALIAS(sys_Xpread64f, libc_sys_Xpread64f)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.ioctlf
INTERN_FUNCTION(libc_sys_ioctlf)
	.cfi_startproc
	movq   $(0xfffffffffffffff0), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_ioctlf)
DEFINE_PUBLIC_ALIAS(sys_ioctlf, libc_sys_ioctlf)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.Xioctlf
INTERN_FUNCTION(libc_sys_Xioctlf)
	.cfi_startproc
	movq   $(0xfffffffffffffff0), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xioctlf)
DEFINE_PUBLIC_ALIAS(sys_Xioctlf, libc_sys_Xioctlf)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                         EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                         &except_handler4, NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.crt.syscall.set_exception_handler
INTERN_FUNCTION(libc_sys_set_exception_handler)
	.cfi_startproc
	movq   $(0xfffffffffffffff1), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_set_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_set_exception_handler, libc_sys_set_exception_handler)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                         EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                         &except_handler4, NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.crt.syscall.Xset_exception_handler
INTERN_FUNCTION(libc_sys_Xset_exception_handler)
	.cfi_startproc
	movq   $(0xfffffffffffffff1), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xset_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xset_exception_handler, libc_sys_Xset_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    When non-NULL, store the address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: When non-NULL, store the starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
.section .text.crt.syscall.get_exception_handler
INTERN_FUNCTION(libc_sys_get_exception_handler)
	.cfi_startproc
	movq   $(0xfffffffffffffff2), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_get_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_get_exception_handler, libc_sys_get_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    When non-NULL, store the address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: When non-NULL, store the starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
.section .text.crt.syscall.Xget_exception_handler
INTERN_FUNCTION(libc_sys_Xget_exception_handler)
	.cfi_startproc
	movq   $(0xfffffffffffffff2), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xget_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xget_exception_handler, libc_sys_Xget_exception_handler)

/* Create a new pseudo-terminal driver and store handles to both the
 * master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.crt.syscall.openpty
INTERN_FUNCTION(libc_sys_openpty)
	.cfi_startproc
	movq   $(0xfffffffffffffff3), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_openpty)
DEFINE_PUBLIC_ALIAS(sys_openpty, libc_sys_openpty)

/* Create a new pseudo-terminal driver and store handles to both the
 * master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.crt.syscall.Xopenpty
INTERN_FUNCTION(libc_sys_Xopenpty)
	.cfi_startproc
	movq   $(0xfffffffffffffff3), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xopenpty)
DEFINE_PUBLIC_ALIAS(sys_Xopenpty, libc_sys_Xopenpty)

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
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR64(void) *arguments) */
.section .text.crt.syscall.rpc_schedule
INTERN_FUNCTION(libc_sys_rpc_schedule)
	.cfi_startproc
	movq   $(0xfffffffffffffff4), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_rpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_rpc_schedule, libc_sys_rpc_schedule)

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
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR64(void) *arguments) */
.section .text.crt.syscall.Xrpc_schedule
INTERN_FUNCTION(libc_sys_Xrpc_schedule)
	.cfi_startproc
	movq   $(0xfffffffffffffff4), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xrpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_schedule, libc_sys_Xrpc_schedule)

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
	.cfi_startproc
	movq   $(0xfffffffffffffff5), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frealpathat)
DEFINE_PUBLIC_ALIAS(sys_frealpathat, libc_sys_frealpathat)

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
	.cfi_startproc
	movq   $(0xfffffffffffffff5), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrealpathat)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpathat, libc_sys_Xfrealpathat)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.frealpath4
INTERN_FUNCTION(libc_sys_frealpath4)
	.cfi_startproc
	movq   $(0xfffffffffffffff6), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_frealpath4)
DEFINE_PUBLIC_ALIAS(sys_frealpath4, libc_sys_frealpath4)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
.section .text.crt.syscall.Xfrealpath4
INTERN_FUNCTION(libc_sys_Xfrealpath4)
	.cfi_startproc
	movq   $(0xfffffffffffffff6), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xfrealpath4)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpath4, libc_sys_Xfrealpath4)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.crt.syscall.getdrives
INTERN_FUNCTION(libc_sys_getdrives)
	.cfi_startproc
	movq   $(0xfffffffffffffff7), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_getdrives)
DEFINE_PUBLIC_ALIAS(sys_getdrives, libc_sys_getdrives)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.crt.syscall.Xgetdrives
INTERN_FUNCTION(libc_sys_Xgetdrives)
	.cfi_startproc
	movq   $(0xfffffffffffffff7), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xgetdrives)
DEFINE_PUBLIC_ALIAS(sys_Xgetdrives, libc_sys_Xgetdrives)

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
 *                      or had you assigned as its parent.
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
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
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
	.cfi_startproc
	movq   $(0xfffffffffffffff8), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_detach)
DEFINE_PUBLIC_ALIAS(sys_detach, libc_sys_detach)

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
 *                      or had you assigned as its parent.
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
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
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
	.cfi_startproc
	movq   $(0xfffffffffffffff8), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xdetach)
DEFINE_PUBLIC_ALIAS(sys_Xdetach, libc_sys_Xdetach)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.readf
INTERN_FUNCTION(libc_sys_readf)
	.cfi_startproc
	movq   $(0xfffffffffffffff9), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_readf)
DEFINE_PUBLIC_ALIAS(sys_readf, libc_sys_readf)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.Xreadf
INTERN_FUNCTION(libc_sys_Xreadf)
	.cfi_startproc
	movq   $(0xfffffffffffffff9), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xreadf)
DEFINE_PUBLIC_ALIAS(sys_Xreadf, libc_sys_Xreadf)

/* errno_t klstat(char const *filename, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.klstat
INTERN_FUNCTION(libc_sys_klstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffa), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_klstat)
DEFINE_PUBLIC_ALIAS(sys_klstat, libc_sys_klstat)

/* errno_t klstat(char const *filename, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.Xklstat
INTERN_FUNCTION(libc_sys_Xklstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffa), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xklstat)
DEFINE_PUBLIC_ALIAS(sys_Xklstat, libc_sys_Xklstat)

/* errno_t kfstat(fd_t fd, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.kfstat
INTERN_FUNCTION(libc_sys_kfstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffb), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kfstat)
DEFINE_PUBLIC_ALIAS(sys_kfstat, libc_sys_kfstat)

/* errno_t kfstat(fd_t fd, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.Xkfstat
INTERN_FUNCTION(libc_sys_Xkfstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffb), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkfstat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstat, libc_sys_Xkfstat)

/* errno_t kstat(char const *filename, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.kstat
INTERN_FUNCTION(libc_sys_kstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffc), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_kstat)
DEFINE_PUBLIC_ALIAS(sys_kstat, libc_sys_kstat)

/* errno_t kstat(char const *filename, struct __kos_statx64 *statbuf) */
.section .text.crt.syscall.Xkstat
INTERN_FUNCTION(libc_sys_Xkstat)
	.cfi_startproc
	movq   $(0xfffffffffffffffc), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xkstat)
DEFINE_PUBLIC_ALIAS(sys_Xkstat, libc_sys_Xkstat)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.hopf
INTERN_FUNCTION(libc_sys_hopf)
	.cfi_startproc
	movq   $(0xfffffffffffffffd), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_hopf)
DEFINE_PUBLIC_ALIAS(sys_hopf, libc_sys_hopf)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.crt.syscall.Xhopf
INTERN_FUNCTION(libc_sys_Xhopf)
	.cfi_startproc
	movq   $(0xfffffffffffffffd), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xhopf)
DEFINE_PUBLIC_ALIAS(sys_Xhopf, libc_sys_Xhopf)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.hop
INTERN_FUNCTION(libc_sys_hop)
	.cfi_startproc
	movq   $(0xfffffffffffffffe), %rax
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_hop)
DEFINE_PUBLIC_ALIAS(sys_hop, libc_sys_hop)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.crt.syscall.Xhop
INTERN_FUNCTION(libc_sys_Xhop)
	.cfi_startproc
	movq   $(0xfffffffffffffffe), %rax
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xhop)
DEFINE_PUBLIC_ALIAS(sys_Xhop, libc_sys_Xhop)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.writef
INTERN_FUNCTION(libc_sys_writef)
	.cfi_startproc
	movq   $(0xffffffffffffffff), %rax
	movq   %rcx, %r10
	clc
	syscall
	ret
	.cfi_endproc
END(libc_sys_writef)
DEFINE_PUBLIC_ALIAS(sys_writef, libc_sys_writef)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.crt.syscall.Xwritef
INTERN_FUNCTION(libc_sys_Xwritef)
	.cfi_startproc
	movq   $(0xffffffffffffffff), %rax
	movq   %rcx, %r10
	stc
	syscall
	ret
	.cfi_endproc
END(libc_sys_Xwritef)
DEFINE_PUBLIC_ALIAS(sys_Xwritef, libc_sys_Xwritef)



/* Include the system call amendment in order to alias
 * some exception-enabled functions onto system calls. */
#include "../../syscalls-ammend.S.inl"

#endif /* GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S */
