/* HASH CRC-32:0x10376d26 */
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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S
#define GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S 1

#include <hybrid/compiler.h>

.section .text.crt.syscalls
.cfi_startproc
.cfi_escape 22,49,7,146,49,0,11,255,251,26 /* Clear EFLAGS.DF on exit */

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_read)
	xorq   %rax, %rax
	syscall
	ret
END(libc_sys_read)
DEFINE_PUBLIC_ALIAS(sys_read, libc_sys_read)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_write)
	movq   $(0x1), %rax
	syscall
	ret
END(libc_sys_write)
DEFINE_PUBLIC_ALIAS(sys_write, libc_sys_write)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_open)
	movq   $(0x2), %rax
	syscall
	ret
END(libc_sys_open)
DEFINE_PUBLIC_ALIAS(sys_open, libc_sys_open)

/* Close a given file descriptor/handle `fd' */
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_close)
	movq   $(0x3), %rax
	syscall
	ret
END(libc_sys_close)
DEFINE_PUBLIC_ALIAS(sys_close, libc_sys_close)

/* errno_t stat(char const *filename, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_stat)
	movq   $(0x4), %rax
	syscall
	ret
END(libc_sys_stat)
DEFINE_PUBLIC_ALIAS(sys_stat, libc_sys_stat)

/* errno_t fstat(fd_t fd, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_fstat)
	movq   $(0x5), %rax
	syscall
	ret
END(libc_sys_fstat)
DEFINE_PUBLIC_ALIAS(sys_fstat, libc_sys_fstat)

/* errno_t lstat(char const *filename, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_lstat)
	movq   $(0x6), %rax
	syscall
	ret
END(libc_sys_lstat)
DEFINE_PUBLIC_ALIAS(sys_lstat, libc_sys_lstat)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_poll)
	movq   $(0x7), %rax
	syscall
	ret
END(libc_sys_poll)
DEFINE_PUBLIC_ALIAS(sys_poll, libc_sys_poll)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_lseek)
	movq   $(0x8), %rax
	syscall
	ret
END(libc_sys_lseek)
DEFINE_PUBLIC_ALIAS(sys_lseek, libc_sys_lseek)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_mmap)
	movq   $(0x9), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mmap)
DEFINE_PUBLIC_ALIAS(sys_mmap, libc_sys_mmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_mprotect)
	movq   $(0xa), %rax
	syscall
	ret
END(libc_sys_mprotect)
DEFINE_PUBLIC_ALIAS(sys_mprotect, libc_sys_mprotect)

/* errno_t munmap(void *addr, size_t len) */
INTERN_FUNCTION(libc_sys_munmap)
	movq   $(0xb), %rax
	syscall
	ret
END(libc_sys_munmap)
DEFINE_PUBLIC_ALIAS(sys_munmap, libc_sys_munmap)

/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_brk)
	movq   $(0xc), %rax
	syscall
	ret
END(libc_sys_brk)
DEFINE_PUBLIC_ALIAS(sys_brk, libc_sys_brk)

/* errno_t rt_sigaction(signo_t signo, struct __kernel_sigactionx64 const *act, struct __kernel_sigactionx64 *oact, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigaction)
	movq   $(0xd), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_rt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_rt_sigaction, libc_sys_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigprocmask)
	movq   $(0xe), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_rt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_rt_sigprocmask, libc_sys_rt_sigprocmask)

/* void rt_sigreturn(void) */
INTERN_FUNCTION(libc_sys_rt_sigreturn)
	movq   $(0xf), %rax
	syscall
	ret
END(libc_sys_rt_sigreturn)
DEFINE_PUBLIC_ALIAS(sys_rt_sigreturn, libc_sys_rt_sigreturn)

/* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_ioctl)
	movq   $(0x10), %rax
	syscall
	ret
END(libc_sys_ioctl)
DEFINE_PUBLIC_ALIAS(sys_ioctl, libc_sys_ioctl)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pread64)
	movq   $(0x11), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pread64)
DEFINE_PUBLIC_ALIAS(sys_pread64, libc_sys_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwrite64)
	movq   $(0x12), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pwrite64)
DEFINE_PUBLIC_ALIAS(sys_pwrite64, libc_sys_pwrite64)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovecx64 const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_readv)
	movq   $(0x13), %rax
	syscall
	ret
END(libc_sys_readv)
DEFINE_PUBLIC_ALIAS(sys_readv, libc_sys_readv)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovecx64 const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_writev)
	movq   $(0x14), %rax
	syscall
	ret
END(libc_sys_writev)
DEFINE_PUBLIC_ALIAS(sys_writev, libc_sys_writev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_access)
	movq   $(0x15), %rax
	syscall
	ret
END(libc_sys_access)
DEFINE_PUBLIC_ALIAS(sys_access, libc_sys_access)

/* errno_t pipe(fd_t[2] pipedes) */
INTERN_FUNCTION(libc_sys_pipe)
	movq   $(0x16), %rax
	syscall
	ret
END(libc_sys_pipe)
DEFINE_PUBLIC_ALIAS(sys_pipe, libc_sys_pipe)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx64 *timeout) */
INTERN_FUNCTION(libc_sys_select)
	movq   $(0x17), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_select)
DEFINE_PUBLIC_ALIAS(sys_select, libc_sys_select)

/* errno_t sched_yield(void) */
INTERN_FUNCTION(libc_sys_sched_yield)
	movq   $(0x18), %rax
	syscall
	ret
END(libc_sys_sched_yield)
DEFINE_PUBLIC_ALIAS(sys_sched_yield, libc_sys_sched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
INTERN_FUNCTION(libc_sys_mremap)
	movq   $(0x19), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mremap)
DEFINE_PUBLIC_ALIAS(sys_mremap, libc_sys_mremap)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_msync)
	movq   $(0x1a), %rax
	syscall
	ret
END(libc_sys_msync)
DEFINE_PUBLIC_ALIAS(sys_msync, libc_sys_msync)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
INTERN_FUNCTION(libc_sys_mincore)
	movq   $(0x1b), %rax
	syscall
	ret
END(libc_sys_mincore)
DEFINE_PUBLIC_ALIAS(sys_mincore, libc_sys_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_madvise)
	movq   $(0x1c), %rax
	syscall
	ret
END(libc_sys_madvise)
DEFINE_PUBLIC_ALIAS(sys_madvise, libc_sys_madvise)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_shmget)
	movq   $(0x1d), %rax
	syscall
	ret
END(libc_sys_shmget)
DEFINE_PUBLIC_ALIAS(sys_shmget, libc_sys_shmget)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_shmat)
	movq   $(0x1e), %rax
	syscall
	ret
END(libc_sys_shmat)
DEFINE_PUBLIC_ALIAS(sys_shmat, libc_sys_shmat)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
INTERN_FUNCTION(libc_sys_shmctl)
	movq   $(0x1f), %rax
	syscall
	ret
END(libc_sys_shmctl)
DEFINE_PUBLIC_ALIAS(sys_shmctl, libc_sys_shmctl)

/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_dup)
	movq   $(0x20), %rax
	syscall
	ret
END(libc_sys_dup)
DEFINE_PUBLIC_ALIAS(sys_dup, libc_sys_dup)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
INTERN_FUNCTION(libc_sys_dup2)
	movq   $(0x21), %rax
	syscall
	ret
END(libc_sys_dup2)
DEFINE_PUBLIC_ALIAS(sys_dup2, libc_sys_dup2)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
INTERN_FUNCTION(libc_sys_pause)
	movq   $(0x22), %rax
	syscall
	ret
END(libc_sys_pause)
DEFINE_PUBLIC_ALIAS(sys_pause, libc_sys_pause)

/* errno_t nanosleep(struct timespecx64 const *req, struct timespecx64 *rem) */
INTERN_FUNCTION(libc_sys_nanosleep)
	movq   $(0x23), %rax
	syscall
	ret
END(libc_sys_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_nanosleep, libc_sys_nanosleep)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
INTERN_FUNCTION(libc_sys_getitimer)
	movq   $(0x24), %rax
	syscall
	ret
END(libc_sys_getitimer)
DEFINE_PUBLIC_ALIAS(sys_getitimer, libc_sys_getitimer)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_alarm)
	movq   $(0x25), %rax
	syscall
	ret
END(libc_sys_alarm)
DEFINE_PUBLIC_ALIAS(sys_alarm, libc_sys_alarm)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
INTERN_FUNCTION(libc_sys_setitimer)
	movq   $(0x26), %rax
	syscall
	ret
END(libc_sys_setitimer)
DEFINE_PUBLIC_ALIAS(sys_setitimer, libc_sys_setitimer)

/* pid_t getpid(void) */
INTERN_FUNCTION(libc_sys_getpid)
	movq   $(0x27), %rax
	syscall
	ret
END(libc_sys_getpid)
DEFINE_PUBLIC_ALIAS(sys_getpid, libc_sys_getpid)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_sendfile)
	movq   $(0x28), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_sendfile)
DEFINE_PUBLIC_ALIAS(sys_sendfile, libc_sys_sendfile)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_socket)
	movq   $(0x29), %rax
	syscall
	ret
END(libc_sys_socket)
DEFINE_PUBLIC_ALIAS(sys_socket, libc_sys_socket)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_connect)
	movq   $(0x2a), %rax
	syscall
	ret
END(libc_sys_connect)
DEFINE_PUBLIC_ALIAS(sys_connect, libc_sys_connect)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_accept)
	movq   $(0x2b), %rax
	syscall
	ret
END(libc_sys_accept)
DEFINE_PUBLIC_ALIAS(sys_accept, libc_sys_accept)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_sendto)
	movq   $(0x2c), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_sendto)
DEFINE_PUBLIC_ALIAS(sys_sendto, libc_sys_sendto)

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
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_recvfrom)
	movq   $(0x2d), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_recvfrom)
DEFINE_PUBLIC_ALIAS(sys_recvfrom, libc_sys_recvfrom)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdrx64 const *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_sendmsg)
	movq   $(0x2e), %rax
	syscall
	ret
END(libc_sys_sendmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmsg, libc_sys_sendmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdrx64 *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_recvmsg)
	movq   $(0x2f), %rax
	syscall
	ret
END(libc_sys_recvmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmsg, libc_sys_recvmsg)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_shutdown)
	movq   $(0x30), %rax
	syscall
	ret
END(libc_sys_shutdown)
DEFINE_PUBLIC_ALIAS(sys_shutdown, libc_sys_shutdown)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_bind)
	movq   $(0x31), %rax
	syscall
	ret
END(libc_sys_bind)
DEFINE_PUBLIC_ALIAS(sys_bind, libc_sys_bind)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_listen)
	movq   $(0x32), %rax
	syscall
	ret
END(libc_sys_listen)
DEFINE_PUBLIC_ALIAS(sys_listen, libc_sys_listen)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getsockname)
	movq   $(0x33), %rax
	syscall
	ret
END(libc_sys_getsockname)
DEFINE_PUBLIC_ALIAS(sys_getsockname, libc_sys_getsockname)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getpeername)
	movq   $(0x34), %rax
	syscall
	ret
END(libc_sys_getpeername)
DEFINE_PUBLIC_ALIAS(sys_getpeername, libc_sys_getpeername)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
INTERN_FUNCTION(libc_sys_socketpair)
	movq   $(0x35), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_socketpair)
DEFINE_PUBLIC_ALIAS(sys_socketpair, libc_sys_socketpair)

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
INTERN_FUNCTION(libc_sys_setsockopt)
	movq   $(0x36), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_setsockopt)
DEFINE_PUBLIC_ALIAS(sys_setsockopt, libc_sys_setsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_getsockopt)
	movq   $(0x37), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_getsockopt)
DEFINE_PUBLIC_ALIAS(sys_getsockopt, libc_sys_getsockopt)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
INTERN_FUNCTION(libc_sys_clone)
	movq   $(0x38), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_clone)
DEFINE_PUBLIC_ALIAS(sys_clone, libc_sys_clone)

/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
INTERN_FUNCTION(libc_sys_fork)
	movq   $(0x39), %rax
	syscall
	ret
END(libc_sys_fork)
DEFINE_PUBLIC_ALIAS(sys_fork, libc_sys_fork)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
INTERN_FUNCTION(libc_sys_vfork)
	movq   $(0x3a), %rax
	syscall
	ret
END(libc_sys_vfork)
DEFINE_PUBLIC_ALIAS(sys_vfork, libc_sys_vfork)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
/* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
INTERN_FUNCTION(libc_sys_execve)
	movq   $(0x3b), %rax
	syscall
	ret
END(libc_sys_execve)
DEFINE_PUBLIC_ALIAS(sys_execve, libc_sys_execve)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_exit)
	movq   $(0x3c), %rax
	syscall
	ret
END(libc_sys_exit)
DEFINE_PUBLIC_ALIAS(sys_exit, libc_sys_exit)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex64 *usage) */
INTERN_FUNCTION(libc_sys_wait4)
	movq   $(0x3d), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_wait4)
DEFINE_PUBLIC_ALIAS(sys_wait4, libc_sys_wait4)

/* errno_t kill(pid_t pid, signo_t signo) */
INTERN_FUNCTION(libc_sys_kill)
	movq   $(0x3e), %rax
	syscall
	ret
END(libc_sys_kill)
DEFINE_PUBLIC_ALIAS(sys_kill, libc_sys_kill)

/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_uname)
	movq   $(0x3f), %rax
	syscall
	ret
END(libc_sys_uname)
DEFINE_PUBLIC_ALIAS(sys_uname, libc_sys_uname)

/* errno_t semget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semget)
	movq   $(0x40), %rax
	syscall
	ret
END(libc_sys_semget)
DEFINE_PUBLIC_ALIAS(sys_semget, libc_sys_semget)

/* errno_t semop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semop)
	movq   $(0x41), %rax
	syscall
	ret
END(libc_sys_semop)
DEFINE_PUBLIC_ALIAS(sys_semop, libc_sys_semop)

/* errno_t semctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semctl)
	movq   $(0x42), %rax
	syscall
	ret
END(libc_sys_semctl)
DEFINE_PUBLIC_ALIAS(sys_semctl, libc_sys_semctl)

/* errno_t shmdt(void const *shmaddr) */
INTERN_FUNCTION(libc_sys_shmdt)
	movq   $(0x43), %rax
	syscall
	ret
END(libc_sys_shmdt)
DEFINE_PUBLIC_ALIAS(sys_shmdt, libc_sys_shmdt)

/* errno_t msgget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgget)
	movq   $(0x44), %rax
	syscall
	ret
END(libc_sys_msgget)
DEFINE_PUBLIC_ALIAS(sys_msgget, libc_sys_msgget)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgsnd)
	movq   $(0x45), %rax
	syscall
	ret
END(libc_sys_msgsnd)
DEFINE_PUBLIC_ALIAS(sys_msgsnd, libc_sys_msgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgrcv)
	movq   $(0x46), %rax
	syscall
	ret
END(libc_sys_msgrcv)
DEFINE_PUBLIC_ALIAS(sys_msgrcv, libc_sys_msgrcv)

/* errno_t msgctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgctl)
	movq   $(0x47), %rax
	syscall
	ret
END(libc_sys_msgctl)
DEFINE_PUBLIC_ALIAS(sys_msgctl, libc_sys_msgctl)

/* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_fcntl)
	movq   $(0x48), %rax
	syscall
	ret
END(libc_sys_fcntl)
DEFINE_PUBLIC_ALIAS(sys_fcntl, libc_sys_fcntl)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_flock)
	movq   $(0x49), %rax
	syscall
	ret
END(libc_sys_flock)
DEFINE_PUBLIC_ALIAS(sys_flock, libc_sys_flock)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fsync)
	movq   $(0x4a), %rax
	syscall
	ret
END(libc_sys_fsync)
DEFINE_PUBLIC_ALIAS(sys_fsync, libc_sys_fsync)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fdatasync)
	movq   $(0x4b), %rax
	syscall
	ret
END(libc_sys_fdatasync)
DEFINE_PUBLIC_ALIAS(sys_fdatasync, libc_sys_fdatasync)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_truncate)
	movq   $(0x4c), %rax
	syscall
	ret
END(libc_sys_truncate)
DEFINE_PUBLIC_ALIAS(sys_truncate, libc_sys_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_ftruncate)
	movq   $(0x4d), %rax
	syscall
	ret
END(libc_sys_ftruncate)
DEFINE_PUBLIC_ALIAS(sys_ftruncate, libc_sys_ftruncate)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_direntx64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_getdents)
	movq   $(0x4e), %rax
	syscall
	ret
END(libc_sys_getdents)
DEFINE_PUBLIC_ALIAS(sys_getdents, libc_sys_getdents)

/* ssize_t getcwd(char *buf, size_t size) */
INTERN_FUNCTION(libc_sys_getcwd)
	movq   $(0x4f), %rax
	syscall
	ret
END(libc_sys_getcwd)
DEFINE_PUBLIC_ALIAS(sys_getcwd, libc_sys_getcwd)

/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_chdir)
	movq   $(0x50), %rax
	syscall
	ret
END(libc_sys_chdir)
DEFINE_PUBLIC_ALIAS(sys_chdir, libc_sys_chdir)

/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_fchdir)
	movq   $(0x51), %rax
	syscall
	ret
END(libc_sys_fchdir)
DEFINE_PUBLIC_ALIAS(sys_fchdir, libc_sys_fchdir)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_rename)
	movq   $(0x52), %rax
	syscall
	ret
END(libc_sys_rename)
DEFINE_PUBLIC_ALIAS(sys_rename, libc_sys_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdir)
	movq   $(0x53), %rax
	syscall
	ret
END(libc_sys_mkdir)
DEFINE_PUBLIC_ALIAS(sys_mkdir, libc_sys_mkdir)

/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_rmdir)
	movq   $(0x54), %rax
	syscall
	ret
END(libc_sys_rmdir)
DEFINE_PUBLIC_ALIAS(sys_rmdir, libc_sys_rmdir)

/* fd_t creat(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_creat)
	movq   $(0x55), %rax
	syscall
	ret
END(libc_sys_creat)
DEFINE_PUBLIC_ALIAS(sys_creat, libc_sys_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
INTERN_FUNCTION(libc_sys_link)
	movq   $(0x56), %rax
	syscall
	ret
END(libc_sys_link)
DEFINE_PUBLIC_ALIAS(sys_link, libc_sys_link)

/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_unlink)
	movq   $(0x57), %rax
	syscall
	ret
END(libc_sys_unlink)
DEFINE_PUBLIC_ALIAS(sys_unlink, libc_sys_unlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
INTERN_FUNCTION(libc_sys_symlink)
	movq   $(0x58), %rax
	syscall
	ret
END(libc_sys_symlink)
DEFINE_PUBLIC_ALIAS(sys_symlink, libc_sys_symlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_readlink)
	movq   $(0x59), %rax
	syscall
	ret
END(libc_sys_readlink)
DEFINE_PUBLIC_ALIAS(sys_readlink, libc_sys_readlink)

/* errno_t chmod(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_chmod)
	movq   $(0x5a), %rax
	syscall
	ret
END(libc_sys_chmod)
DEFINE_PUBLIC_ALIAS(sys_chmod, libc_sys_chmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
INTERN_FUNCTION(libc_sys_fchmod)
	movq   $(0x5b), %rax
	syscall
	ret
END(libc_sys_fchmod)
DEFINE_PUBLIC_ALIAS(sys_fchmod, libc_sys_fchmod)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_chown)
	movq   $(0x5c), %rax
	syscall
	ret
END(libc_sys_chown)
DEFINE_PUBLIC_ALIAS(sys_chown, libc_sys_chown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_fchown)
	movq   $(0x5d), %rax
	syscall
	ret
END(libc_sys_fchown)
DEFINE_PUBLIC_ALIAS(sys_fchown, libc_sys_fchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_lchown)
	movq   $(0x5e), %rax
	syscall
	ret
END(libc_sys_lchown)
DEFINE_PUBLIC_ALIAS(sys_lchown, libc_sys_lchown)

/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_umask)
	movq   $(0x5f), %rax
	syscall
	ret
END(libc_sys_umask)
DEFINE_PUBLIC_ALIAS(sys_umask, libc_sys_umask)

/* errno_t gettimeofday(struct timevalx64 *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_gettimeofday)
	movq   $(0x60), %rax
	syscall
	ret
END(libc_sys_gettimeofday)
DEFINE_PUBLIC_ALIAS(sys_gettimeofday, libc_sys_gettimeofday)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimitx64 *rlimits) */
INTERN_FUNCTION(libc_sys_getrlimit)
	movq   $(0x61), %rax
	syscall
	ret
END(libc_sys_getrlimit)
DEFINE_PUBLIC_ALIAS(sys_getrlimit, libc_sys_getrlimit)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusagex64 *tv) */
INTERN_FUNCTION(libc_sys_getrusage)
	movq   $(0x62), %rax
	syscall
	ret
END(libc_sys_getrusage)
DEFINE_PUBLIC_ALIAS(sys_getrusage, libc_sys_getrusage)

/* errno_t sysinfo(struct __sysinfox64 *info) */
INTERN_FUNCTION(libc_sys_sysinfo)
	movq   $(0x63), %rax
	syscall
	ret
END(libc_sys_sysinfo)
DEFINE_PUBLIC_ALIAS(sys_sysinfo, libc_sys_sysinfo)

/* clock_t times(struct tmsx64 *buf) */
INTERN_FUNCTION(libc_sys_times)
	movq   $(0x64), %rax
	syscall
	ret
END(libc_sys_times)
DEFINE_PUBLIC_ALIAS(sys_times, libc_sys_times)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
INTERN_FUNCTION(libc_sys_ptrace)
	movq   $(0x65), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_ptrace)
DEFINE_PUBLIC_ALIAS(sys_ptrace, libc_sys_ptrace)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uid_t getuid(void) */
INTERN_FUNCTION(libc_sys_getuid)
	movq   $(0x66), %rax
	syscall
	ret
END(libc_sys_getuid)
DEFINE_PUBLIC_ALIAS(sys_getuid, libc_sys_getuid)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
INTERN_FUNCTION(libc_sys_syslog)
	movq   $(0x67), %rax
	syscall
	ret
END(libc_sys_syslog)
DEFINE_PUBLIC_ALIAS(sys_syslog, libc_sys_syslog)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* gid_t getgid(void) */
INTERN_FUNCTION(libc_sys_getgid)
	movq   $(0x68), %rax
	syscall
	ret
END(libc_sys_getgid)
DEFINE_PUBLIC_ALIAS(sys_getgid, libc_sys_getgid)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid(uid_t uid) */
INTERN_FUNCTION(libc_sys_setuid)
	movq   $(0x69), %rax
	syscall
	ret
END(libc_sys_setuid)
DEFINE_PUBLIC_ALIAS(sys_setuid, libc_sys_setuid)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid(gid_t gid) */
INTERN_FUNCTION(libc_sys_setgid)
	movq   $(0x6a), %rax
	syscall
	ret
END(libc_sys_setgid)
DEFINE_PUBLIC_ALIAS(sys_setgid, libc_sys_setgid)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uid_t geteuid(void) */
INTERN_FUNCTION(libc_sys_geteuid)
	movq   $(0x6b), %rax
	syscall
	ret
END(libc_sys_geteuid)
DEFINE_PUBLIC_ALIAS(sys_geteuid, libc_sys_geteuid)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* gid_t getegid(void) */
INTERN_FUNCTION(libc_sys_getegid)
	movq   $(0x6c), %rax
	syscall
	ret
END(libc_sys_getegid)
DEFINE_PUBLIC_ALIAS(sys_getegid, libc_sys_getegid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
INTERN_FUNCTION(libc_sys_setpgid)
	movq   $(0x6d), %rax
	syscall
	ret
END(libc_sys_setpgid)
DEFINE_PUBLIC_ALIAS(sys_setpgid, libc_sys_setpgid)

/* pid_t getppid(void) */
INTERN_FUNCTION(libc_sys_getppid)
	movq   $(0x6e), %rax
	syscall
	ret
END(libc_sys_getppid)
DEFINE_PUBLIC_ALIAS(sys_getppid, libc_sys_getppid)

/* pid_t getpgrp(void) */
INTERN_FUNCTION(libc_sys_getpgrp)
	movq   $(0x6f), %rax
	syscall
	ret
END(libc_sys_getpgrp)
DEFINE_PUBLIC_ALIAS(sys_getpgrp, libc_sys_getpgrp)

/* pid_t setsid(void) */
INTERN_FUNCTION(libc_sys_setsid)
	movq   $(0x70), %rax
	syscall
	ret
END(libc_sys_setsid)
DEFINE_PUBLIC_ALIAS(sys_setsid, libc_sys_setsid)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid(uid_t ruid, uid_t euid) */
INTERN_FUNCTION(libc_sys_setreuid)
	movq   $(0x71), %rax
	syscall
	ret
END(libc_sys_setreuid)
DEFINE_PUBLIC_ALIAS(sys_setreuid, libc_sys_setreuid)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid(gid_t rgid, gid_t egid) */
INTERN_FUNCTION(libc_sys_setregid)
	movq   $(0x72), %rax
	syscall
	ret
END(libc_sys_setregid)
DEFINE_PUBLIC_ALIAS(sys_setregid, libc_sys_setregid)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, gid_t[] list) */
INTERN_FUNCTION(libc_sys_getgroups)
	movq   $(0x73), %rax
	syscall
	ret
END(libc_sys_getgroups)
DEFINE_PUBLIC_ALIAS(sys_getgroups, libc_sys_getgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
INTERN_FUNCTION(libc_sys_setgroups)
	movq   $(0x74), %rax
	syscall
	ret
END(libc_sys_setgroups)
DEFINE_PUBLIC_ALIAS(sys_setgroups, libc_sys_setgroups)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
INTERN_FUNCTION(libc_sys_setresuid)
	movq   $(0x75), %rax
	syscall
	ret
END(libc_sys_setresuid)
DEFINE_PUBLIC_ALIAS(sys_setresuid, libc_sys_setresuid)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
INTERN_FUNCTION(libc_sys_getresuid)
	movq   $(0x76), %rax
	syscall
	ret
END(libc_sys_getresuid)
DEFINE_PUBLIC_ALIAS(sys_getresuid, libc_sys_getresuid)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
INTERN_FUNCTION(libc_sys_setresgid)
	movq   $(0x77), %rax
	syscall
	ret
END(libc_sys_setresgid)
DEFINE_PUBLIC_ALIAS(sys_setresgid, libc_sys_setresgid)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
INTERN_FUNCTION(libc_sys_getresgid)
	movq   $(0x78), %rax
	syscall
	ret
END(libc_sys_getresgid)
DEFINE_PUBLIC_ALIAS(sys_getresgid, libc_sys_getresgid)

/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getpgid)
	movq   $(0x79), %rax
	syscall
	ret
END(libc_sys_getpgid)
DEFINE_PUBLIC_ALIAS(sys_getpgid, libc_sys_getpgid)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid(uid_t uid) */
INTERN_FUNCTION(libc_sys_setfsuid)
	movq   $(0x7a), %rax
	syscall
	ret
END(libc_sys_setfsuid)
DEFINE_PUBLIC_ALIAS(sys_setfsuid, libc_sys_setfsuid)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid(gid_t gid) */
INTERN_FUNCTION(libc_sys_setfsgid)
	movq   $(0x7b), %rax
	syscall
	ret
END(libc_sys_setfsgid)
DEFINE_PUBLIC_ALIAS(sys_setfsgid, libc_sys_setfsgid)

/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getsid)
	movq   $(0x7c), %rax
	syscall
	ret
END(libc_sys_getsid)
DEFINE_PUBLIC_ALIAS(sys_getsid, libc_sys_getsid)

/* errno_t capget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_capget)
	movq   $(0x7d), %rax
	syscall
	ret
END(libc_sys_capget)
DEFINE_PUBLIC_ALIAS(sys_capget, libc_sys_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_capset)
	movq   $(0x7e), %rax
	syscall
	ret
END(libc_sys_capset)
DEFINE_PUBLIC_ALIAS(sys_capset, libc_sys_capset)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigpending)
	movq   $(0x7f), %rax
	syscall
	ret
END(libc_sys_rt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_rt_sigpending, libc_sys_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox64_struct *info, struct timespecx64 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigtimedwait)
	movq   $(0x80), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_rt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_rt_sigtimedwait, libc_sys_rt_sigtimedwait)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_sigqueueinfo)
	movq   $(0x81), %rax
	syscall
	ret
END(libc_sys_rt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_sigqueueinfo, libc_sys_rt_sigqueueinfo)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigsuspend)
	movq   $(0x82), %rax
	syscall
	ret
END(libc_sys_rt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_rt_sigsuspend, libc_sys_rt_sigsuspend)

/* errno_t sigaltstack(struct __sigaltstackx64 const *ss, struct __sigaltstackx64 *oss) */
INTERN_FUNCTION(libc_sys_sigaltstack)
	movq   $(0x83), %rax
	syscall
	ret
END(libc_sys_sigaltstack)
DEFINE_PUBLIC_ALIAS(sys_sigaltstack, libc_sys_sigaltstack)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbufx64 const *times) */
INTERN_FUNCTION(libc_sys_utime)
	movq   $(0x84), %rax
	syscall
	ret
END(libc_sys_utime)
DEFINE_PUBLIC_ALIAS(sys_utime, libc_sys_utime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_mknod)
	movq   $(0x85), %rax
	syscall
	ret
END(libc_sys_mknod)
DEFINE_PUBLIC_ALIAS(sys_mknod, libc_sys_mknod)

/* errno_t uselib(char const *library) */
INTERN_FUNCTION(libc_sys_uselib)
	movq   $(0x86), %rax
	syscall
	ret
END(libc_sys_uselib)
DEFINE_PUBLIC_ALIAS(sys_uselib, libc_sys_uselib)

/* errno_t personality(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_personality)
	movq   $(0x87), %rax
	syscall
	ret
END(libc_sys_personality)
DEFINE_PUBLIC_ALIAS(sys_personality, libc_sys_personality)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_ustat)
	movq   $(0x88), %rax
	syscall
	ret
END(libc_sys_ustat)
DEFINE_PUBLIC_ALIAS(sys_ustat, libc_sys_ustat)

/* errno_t statfs(char const *file, struct __statfsx64 *buf) */
INTERN_FUNCTION(libc_sys_statfs)
	movq   $(0x89), %rax
	syscall
	ret
END(libc_sys_statfs)
DEFINE_PUBLIC_ALIAS(sys_statfs, libc_sys_statfs)

/* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
INTERN_FUNCTION(libc_sys_fstatfs)
	movq   $(0x8a), %rax
	syscall
	ret
END(libc_sys_fstatfs)
DEFINE_PUBLIC_ALIAS(sys_fstatfs, libc_sys_fstatfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sysfs)
	movq   $(0x8b), %rax
	syscall
	ret
END(libc_sys_sysfs)
DEFINE_PUBLIC_ALIAS(sys_sysfs, libc_sys_sysfs)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
INTERN_FUNCTION(libc_sys_getpriority)
	movq   $(0x8c), %rax
	syscall
	ret
END(libc_sys_getpriority)
DEFINE_PUBLIC_ALIAS(sys_getpriority, libc_sys_getpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_setpriority)
	movq   $(0x8d), %rax
	syscall
	ret
END(libc_sys_setpriority)
DEFINE_PUBLIC_ALIAS(sys_setpriority, libc_sys_setpriority)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setparam)
	movq   $(0x8e), %rax
	syscall
	ret
END(libc_sys_sched_setparam)
DEFINE_PUBLIC_ALIAS(sys_sched_setparam, libc_sys_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
INTERN_FUNCTION(libc_sys_sched_getparam)
	movq   $(0x8f), %rax
	syscall
	ret
END(libc_sys_sched_getparam)
DEFINE_PUBLIC_ALIAS(sys_sched_getparam, libc_sys_sched_getparam)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setscheduler)
	movq   $(0x90), %rax
	syscall
	ret
END(libc_sys_sched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_setscheduler, libc_sys_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_sched_getscheduler)
	movq   $(0x91), %rax
	syscall
	ret
END(libc_sys_sched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_getscheduler, libc_sys_sched_getscheduler)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_max)
	movq   $(0x92), %rax
	syscall
	ret
END(libc_sys_sched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_max, libc_sys_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_min)
	movq   $(0x93), %rax
	syscall
	ret
END(libc_sys_sched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_min, libc_sys_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespecx64 *ts) */
INTERN_FUNCTION(libc_sys_sched_rr_get_interval)
	movq   $(0x94), %rax
	syscall
	ret
END(libc_sys_sched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_sched_rr_get_interval, libc_sys_sched_rr_get_interval)

/* errno_t mlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_mlock)
	movq   $(0x95), %rax
	syscall
	ret
END(libc_sys_mlock)
DEFINE_PUBLIC_ALIAS(sys_mlock, libc_sys_mlock)

/* errno_t munlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_munlock)
	movq   $(0x96), %rax
	syscall
	ret
END(libc_sys_munlock)
DEFINE_PUBLIC_ALIAS(sys_munlock, libc_sys_munlock)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_mlockall)
	movq   $(0x97), %rax
	syscall
	ret
END(libc_sys_mlockall)
DEFINE_PUBLIC_ALIAS(sys_mlockall, libc_sys_mlockall)

/* errno_t munlockall(void) */
INTERN_FUNCTION(libc_sys_munlockall)
	movq   $(0x98), %rax
	syscall
	ret
END(libc_sys_munlockall)
DEFINE_PUBLIC_ALIAS(sys_munlockall, libc_sys_munlockall)

/* errno_t vhangup(void) */
INTERN_FUNCTION(libc_sys_vhangup)
	movq   $(0x99), %rax
	syscall
	ret
END(libc_sys_vhangup)
DEFINE_PUBLIC_ALIAS(sys_vhangup, libc_sys_vhangup)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
INTERN_FUNCTION(libc_sys_modify_ldt)
	movq   $(0x9a), %rax
	syscall
	ret
END(libc_sys_modify_ldt)
DEFINE_PUBLIC_ALIAS(sys_modify_ldt, libc_sys_modify_ldt)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pivot_root)
	movq   $(0x9b), %rax
	syscall
	ret
END(libc_sys_pivot_root)
DEFINE_PUBLIC_ALIAS(sys_pivot_root, libc_sys_pivot_root)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys__sysctl)
	movq   $(0x9c), %rax
	syscall
	ret
END(libc_sys__sysctl)
DEFINE_PUBLIC_ALIAS(sys__sysctl, libc_sys__sysctl)

/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
INTERN_FUNCTION(libc_sys_prctl)
	movq   $(0x9d), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_prctl)
DEFINE_PUBLIC_ALIAS(sys_prctl, libc_sys_prctl)

/* >> arch_prctl(2)
 * Arch-dependent system process control interface. (But don't go and
 * think that the  normal `prctl(2)'  doesn't feature  arch-dependent
 * commands  -- honestly, this syscall shouldn't exist if you ask me,
 * but it does on linux, and so it must also on KOS...)
 * @param: command: One of `ARCH_*' (from <asm/prctl.h>)
 * @param: addr: Either a `syscall_ulong_t' or `syscall_ulong_t *', depending on `command'
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t arch_prctl(unsigned int command, uint64_t *addr) */
INTERN_FUNCTION(libc_sys_arch_prctl)
	movq   $(0x9e), %rax
	syscall
	ret
END(libc_sys_arch_prctl)
DEFINE_PUBLIC_ALIAS(sys_arch_prctl, libc_sys_arch_prctl)

/* errno_t adjtimex(struct timex *ntx) */
INTERN_FUNCTION(libc_sys_adjtimex)
	movq   $(0x9f), %rax
	syscall
	ret
END(libc_sys_adjtimex)
DEFINE_PUBLIC_ALIAS(sys_adjtimex, libc_sys_adjtimex)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimitx64 const *rlimits) */
INTERN_FUNCTION(libc_sys_setrlimit)
	movq   $(0xa0), %rax
	syscall
	ret
END(libc_sys_setrlimit)
DEFINE_PUBLIC_ALIAS(sys_setrlimit, libc_sys_setrlimit)

/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_chroot)
	movq   $(0xa1), %rax
	syscall
	ret
END(libc_sys_chroot)
DEFINE_PUBLIC_ALIAS(sys_chroot, libc_sys_chroot)

/* errno_t sync(void) */
INTERN_FUNCTION(libc_sys_sync)
	movq   $(0xa2), %rax
	syscall
	ret
END(libc_sys_sync)
DEFINE_PUBLIC_ALIAS(sys_sync, libc_sys_sync)

/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_acct)
	movq   $(0xa3), %rax
	syscall
	ret
END(libc_sys_acct)
DEFINE_PUBLIC_ALIAS(sys_acct, libc_sys_acct)

/* errno_t settimeofday(struct timevalx64 const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_settimeofday)
	movq   $(0xa4), %rax
	syscall
	ret
END(libc_sys_settimeofday)
DEFINE_PUBLIC_ALIAS(sys_settimeofday, libc_sys_settimeofday)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
INTERN_FUNCTION(libc_sys_mount)
	movq   $(0xa5), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mount)
DEFINE_PUBLIC_ALIAS(sys_mount, libc_sys_mount)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_umount2)
	movq   $(0xa6), %rax
	syscall
	ret
END(libc_sys_umount2)
DEFINE_PUBLIC_ALIAS(sys_umount2, libc_sys_umount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_swapon)
	movq   $(0xa7), %rax
	syscall
	ret
END(libc_sys_swapon)
DEFINE_PUBLIC_ALIAS(sys_swapon, libc_sys_swapon)

/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_swapoff)
	movq   $(0xa8), %rax
	syscall
	ret
END(libc_sys_swapoff)
DEFINE_PUBLIC_ALIAS(sys_swapoff, libc_sys_swapoff)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_reboot)
	movq   $(0xa9), %rax
	syscall
	ret
END(libc_sys_reboot)
DEFINE_PUBLIC_ALIAS(sys_reboot, libc_sys_reboot)

/* errno_t sethostname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_sethostname)
	movq   $(0xaa), %rax
	syscall
	ret
END(libc_sys_sethostname)
DEFINE_PUBLIC_ALIAS(sys_sethostname, libc_sys_sethostname)

/* errno_t setdomainname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_setdomainname)
	movq   $(0xab), %rax
	syscall
	ret
END(libc_sys_setdomainname)
DEFINE_PUBLIC_ALIAS(sys_setdomainname, libc_sys_setdomainname)

/* errno_t iopl(syscall_ulong_t level) */
INTERN_FUNCTION(libc_sys_iopl)
	movq   $(0xac), %rax
	syscall
	ret
END(libc_sys_iopl)
DEFINE_PUBLIC_ALIAS(sys_iopl, libc_sys_iopl)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
INTERN_FUNCTION(libc_sys_ioperm)
	movq   $(0xad), %rax
	syscall
	ret
END(libc_sys_ioperm)
DEFINE_PUBLIC_ALIAS(sys_ioperm, libc_sys_ioperm)

/* errno_t create_module(void) */
INTERN_FUNCTION(libc_sys_create_module)
	movq   $(0xae), %rax
	syscall
	ret
END(libc_sys_create_module)
DEFINE_PUBLIC_ALIAS(sys_create_module, libc_sys_create_module)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
INTERN_FUNCTION(libc_sys_init_module)
	movq   $(0xaf), %rax
	syscall
	ret
END(libc_sys_init_module)
DEFINE_PUBLIC_ALIAS(sys_init_module, libc_sys_init_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
INTERN_FUNCTION(libc_sys_delete_module)
	movq   $(0xb0), %rax
	syscall
	ret
END(libc_sys_delete_module)
DEFINE_PUBLIC_ALIAS(sys_delete_module, libc_sys_delete_module)

/* errno_t get_kernel_syms(void) */
INTERN_FUNCTION(libc_sys_get_kernel_syms)
	movq   $(0xb1), %rax
	syscall
	ret
END(libc_sys_get_kernel_syms)
DEFINE_PUBLIC_ALIAS(sys_get_kernel_syms, libc_sys_get_kernel_syms)

/* errno_t query_module(void) */
INTERN_FUNCTION(libc_sys_query_module)
	movq   $(0xb2), %rax
	syscall
	ret
END(libc_sys_query_module)
DEFINE_PUBLIC_ALIAS(sys_query_module, libc_sys_query_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_quotactl)
	movq   $(0xb3), %rax
	syscall
	ret
END(libc_sys_quotactl)
DEFINE_PUBLIC_ALIAS(sys_quotactl, libc_sys_quotactl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_nfsservctl)
	movq   $(0xb4), %rax
	syscall
	ret
END(libc_sys_nfsservctl)
DEFINE_PUBLIC_ALIAS(sys_nfsservctl, libc_sys_nfsservctl)

/* errno_t getpmsg(void) */
INTERN_FUNCTION(libc_sys_getpmsg)
	movq   $(0xb5), %rax
	syscall
	ret
END(libc_sys_getpmsg)
DEFINE_PUBLIC_ALIAS(sys_getpmsg, libc_sys_getpmsg)

/* errno_t putpmsg(void) */
INTERN_FUNCTION(libc_sys_putpmsg)
	movq   $(0xb6), %rax
	syscall
	ret
END(libc_sys_putpmsg)
DEFINE_PUBLIC_ALIAS(sys_putpmsg, libc_sys_putpmsg)

/* errno_t afs_syscall(void) */
INTERN_FUNCTION(libc_sys_afs_syscall)
	movq   $(0xb7), %rax
	syscall
	ret
END(libc_sys_afs_syscall)
DEFINE_PUBLIC_ALIAS(sys_afs_syscall, libc_sys_afs_syscall)

/* errno_t tuxcall(void) */
INTERN_FUNCTION(libc_sys_tuxcall)
	movq   $(0xb8), %rax
	syscall
	ret
END(libc_sys_tuxcall)
DEFINE_PUBLIC_ALIAS(sys_tuxcall, libc_sys_tuxcall)

/* errno_t security(void) */
INTERN_FUNCTION(libc_sys_security)
	movq   $(0xb9), %rax
	syscall
	ret
END(libc_sys_security)
DEFINE_PUBLIC_ALIAS(sys_security, libc_sys_security)

/* pid_t gettid(void) */
INTERN_FUNCTION(libc_sys_gettid)
	movq   $(0xba), %rax
	syscall
	ret
END(libc_sys_gettid)
DEFINE_PUBLIC_ALIAS(sys_gettid, libc_sys_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
INTERN_FUNCTION(libc_sys_readahead)
	movq   $(0xbb), %rax
	syscall
	ret
END(libc_sys_readahead)
DEFINE_PUBLIC_ALIAS(sys_readahead, libc_sys_readahead)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_setxattr)
	movq   $(0xbc), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_setxattr)
DEFINE_PUBLIC_ALIAS(sys_setxattr, libc_sys_setxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_lsetxattr)
	movq   $(0xbd), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_lsetxattr)
DEFINE_PUBLIC_ALIAS(sys_lsetxattr, libc_sys_lsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_fsetxattr)
	movq   $(0xbe), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fsetxattr)
DEFINE_PUBLIC_ALIAS(sys_fsetxattr, libc_sys_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_getxattr)
	movq   $(0xbf), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_getxattr)
DEFINE_PUBLIC_ALIAS(sys_getxattr, libc_sys_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_lgetxattr)
	movq   $(0xc0), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_lgetxattr)
DEFINE_PUBLIC_ALIAS(sys_lgetxattr, libc_sys_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_fgetxattr)
	movq   $(0xc1), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fgetxattr)
DEFINE_PUBLIC_ALIAS(sys_fgetxattr, libc_sys_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_listxattr)
	movq   $(0xc2), %rax
	syscall
	ret
END(libc_sys_listxattr)
DEFINE_PUBLIC_ALIAS(sys_listxattr, libc_sys_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_llistxattr)
	movq   $(0xc3), %rax
	syscall
	ret
END(libc_sys_llistxattr)
DEFINE_PUBLIC_ALIAS(sys_llistxattr, libc_sys_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_flistxattr)
	movq   $(0xc4), %rax
	syscall
	ret
END(libc_sys_flistxattr)
DEFINE_PUBLIC_ALIAS(sys_flistxattr, libc_sys_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_removexattr)
	movq   $(0xc5), %rax
	syscall
	ret
END(libc_sys_removexattr)
DEFINE_PUBLIC_ALIAS(sys_removexattr, libc_sys_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_lremovexattr)
	movq   $(0xc6), %rax
	syscall
	ret
END(libc_sys_lremovexattr)
DEFINE_PUBLIC_ALIAS(sys_lremovexattr, libc_sys_lremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
INTERN_FUNCTION(libc_sys_fremovexattr)
	movq   $(0xc7), %rax
	syscall
	ret
END(libc_sys_fremovexattr)
DEFINE_PUBLIC_ALIAS(sys_fremovexattr, libc_sys_fremovexattr)

/* errno_t tkill(pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_tkill)
	movq   $(0xc8), %rax
	syscall
	ret
END(libc_sys_tkill)
DEFINE_PUBLIC_ALIAS(sys_tkill, libc_sys_tkill)

/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_time)
	movq   $(0xc9), %rax
	syscall
	ret
END(libc_sys_time)
DEFINE_PUBLIC_ALIAS(sys_time, libc_sys_time)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_futex)
	movq   $(0xca), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_futex)
DEFINE_PUBLIC_ALIAS(sys_futex, libc_sys_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_sched_setaffinity)
	movq   $(0xcb), %rax
	syscall
	ret
END(libc_sys_sched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_setaffinity, libc_sys_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_sched_getaffinity)
	movq   $(0xcc), %rax
	syscall
	ret
END(libc_sys_sched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_getaffinity, libc_sys_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_set_thread_area)
	movq   $(0xcd), %rax
	syscall
	ret
END(libc_sys_set_thread_area)
DEFINE_PUBLIC_ALIAS(sys_set_thread_area, libc_sys_set_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_setup)
	movq   $(0xce), %rax
	syscall
	ret
END(libc_sys_io_setup)
DEFINE_PUBLIC_ALIAS(sys_io_setup, libc_sys_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_destroy)
	movq   $(0xcf), %rax
	syscall
	ret
END(libc_sys_io_destroy)
DEFINE_PUBLIC_ALIAS(sys_io_destroy, libc_sys_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_getevents)
	movq   $(0xd0), %rax
	syscall
	ret
END(libc_sys_io_getevents)
DEFINE_PUBLIC_ALIAS(sys_io_getevents, libc_sys_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_submit)
	movq   $(0xd1), %rax
	syscall
	ret
END(libc_sys_io_submit)
DEFINE_PUBLIC_ALIAS(sys_io_submit, libc_sys_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_cancel)
	movq   $(0xd2), %rax
	syscall
	ret
END(libc_sys_io_cancel)
DEFINE_PUBLIC_ALIAS(sys_io_cancel, libc_sys_io_cancel)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_get_thread_area)
	movq   $(0xd3), %rax
	syscall
	ret
END(libc_sys_get_thread_area)
DEFINE_PUBLIC_ALIAS(sys_get_thread_area, libc_sys_get_thread_area)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_lookup_dcookie)
	movq   $(0xd4), %rax
	syscall
	ret
END(libc_sys_lookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_lookup_dcookie, libc_sys_lookup_dcookie)

/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_epoll_create)
	movq   $(0xd5), %rax
	syscall
	ret
END(libc_sys_epoll_create)
DEFINE_PUBLIC_ALIAS(sys_epoll_create, libc_sys_epoll_create)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_epoll_ctl_old)
	movq   $(0xd6), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_epoll_ctl_old)
DEFINE_PUBLIC_ALIAS(sys_epoll_ctl_old, libc_sys_epoll_ctl_old)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait_old(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_epoll_wait_old)
	movq   $(0xd7), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_epoll_wait_old)
DEFINE_PUBLIC_ALIAS(sys_epoll_wait_old, libc_sys_epoll_wait_old)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_remap_file_pages)
	movq   $(0xd8), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_remap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_remap_file_pages, libc_sys_remap_file_pages)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_getdents64)
	movq   $(0xd9), %rax
	syscall
	ret
END(libc_sys_getdents64)
DEFINE_PUBLIC_ALIAS(sys_getdents64, libc_sys_getdents64)

/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_set_tid_address)
	movq   $(0xda), %rax
	syscall
	ret
END(libc_sys_set_tid_address)
DEFINE_PUBLIC_ALIAS(sys_set_tid_address, libc_sys_set_tid_address)

/* errno_t restart_syscall(void) */
INTERN_FUNCTION(libc_sys_restart_syscall)
	movq   $(0xdb), %rax
	syscall
	ret
END(libc_sys_restart_syscall)
DEFINE_PUBLIC_ALIAS(sys_restart_syscall, libc_sys_restart_syscall)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semtimedop)
	movq   $(0xdc), %rax
	syscall
	ret
END(libc_sys_semtimedop)
DEFINE_PUBLIC_ALIAS(sys_semtimedop, libc_sys_semtimedop)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fadvise64)
	movq   $(0xdd), %rax
	syscall
	ret
END(libc_sys_fadvise64)
DEFINE_PUBLIC_ALIAS(sys_fadvise64, libc_sys_fadvise64)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
INTERN_FUNCTION(libc_sys_timer_create)
	movq   $(0xde), %rax
	syscall
	ret
END(libc_sys_timer_create)
DEFINE_PUBLIC_ALIAS(sys_timer_create, libc_sys_timer_create)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx64 const *value, struct itimerspecx64 *ovalue) */
INTERN_FUNCTION(libc_sys_timer_settime)
	movq   $(0xdf), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_timer_settime)
DEFINE_PUBLIC_ALIAS(sys_timer_settime, libc_sys_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspecx64 *value) */
INTERN_FUNCTION(libc_sys_timer_gettime)
	movq   $(0xe0), %rax
	syscall
	ret
END(libc_sys_timer_gettime)
DEFINE_PUBLIC_ALIAS(sys_timer_gettime, libc_sys_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_getoverrun)
	movq   $(0xe1), %rax
	syscall
	ret
END(libc_sys_timer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_timer_getoverrun, libc_sys_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_delete)
	movq   $(0xe2), %rax
	syscall
	ret
END(libc_sys_timer_delete)
DEFINE_PUBLIC_ALIAS(sys_timer_delete, libc_sys_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct timespecx64 const *tp) */
INTERN_FUNCTION(libc_sys_clock_settime)
	movq   $(0xe3), %rax
	syscall
	ret
END(libc_sys_clock_settime)
DEFINE_PUBLIC_ALIAS(sys_clock_settime, libc_sys_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespecx64 *tp) */
INTERN_FUNCTION(libc_sys_clock_gettime)
	movq   $(0xe4), %rax
	syscall
	ret
END(libc_sys_clock_gettime)
DEFINE_PUBLIC_ALIAS(sys_clock_gettime, libc_sys_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct timespecx64 *res) */
INTERN_FUNCTION(libc_sys_clock_getres)
	movq   $(0xe5), %rax
	syscall
	ret
END(libc_sys_clock_getres)
DEFINE_PUBLIC_ALIAS(sys_clock_getres, libc_sys_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx64 const *requested_time, struct timespecx64 *remaining) */
INTERN_FUNCTION(libc_sys_clock_nanosleep)
	movq   $(0xe6), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_clock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_clock_nanosleep, libc_sys_clock_nanosleep)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_exit_group)
	movq   $(0xe7), %rax
	syscall
	ret
END(libc_sys_exit_group)
DEFINE_PUBLIC_ALIAS(sys_exit_group, libc_sys_exit_group)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_epoll_wait)
	movq   $(0xe8), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_epoll_wait)
DEFINE_PUBLIC_ALIAS(sys_epoll_wait, libc_sys_epoll_wait)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_epoll_ctl)
	movq   $(0xe9), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_epoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_epoll_ctl, libc_sys_epoll_ctl)

/* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_tgkill)
	movq   $(0xea), %rax
	syscall
	ret
END(libc_sys_tgkill)
DEFINE_PUBLIC_ALIAS(sys_tgkill, libc_sys_tgkill)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timevalx64 const[2] times) */
INTERN_FUNCTION(libc_sys_utimes)
	movq   $(0xeb), %rax
	syscall
	ret
END(libc_sys_utimes)
DEFINE_PUBLIC_ALIAS(sys_utimes, libc_sys_utimes)

/* errno_t vserver(void) */
INTERN_FUNCTION(libc_sys_vserver)
	movq   $(0xec), %rax
	syscall
	ret
END(libc_sys_vserver)
DEFINE_PUBLIC_ALIAS(sys_vserver, libc_sys_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_mbind)
	movq   $(0xed), %rax
	syscall
	ret
END(libc_sys_mbind)
DEFINE_PUBLIC_ALIAS(sys_mbind, libc_sys_mbind)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_set_mempolicy)
	movq   $(0xee), %rax
	syscall
	ret
END(libc_sys_set_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_set_mempolicy, libc_sys_set_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_get_mempolicy)
	movq   $(0xef), %rax
	syscall
	ret
END(libc_sys_get_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_get_mempolicy, libc_sys_get_mempolicy)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_mq_open)
	movq   $(0xf0), %rax
	syscall
	ret
END(libc_sys_mq_open)
DEFINE_PUBLIC_ALIAS(sys_mq_open, libc_sys_mq_open)

/* errno_t mq_unlink(char const *name) */
INTERN_FUNCTION(libc_sys_mq_unlink)
	movq   $(0xf1), %rax
	syscall
	ret
END(libc_sys_mq_unlink)
DEFINE_PUBLIC_ALIAS(sys_mq_unlink, libc_sys_mq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedsend)
	movq   $(0xf2), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_mq_timedsend, libc_sys_mq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedreceive)
	movq   $(0xf3), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_mq_timedreceive, libc_sys_mq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
INTERN_FUNCTION(libc_sys_mq_notify)
	movq   $(0xf4), %rax
	syscall
	ret
END(libc_sys_mq_notify)
DEFINE_PUBLIC_ALIAS(sys_mq_notify, libc_sys_mq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
INTERN_FUNCTION(libc_sys_mq_getsetattr)
	movq   $(0xf5), %rax
	syscall
	ret
END(libc_sys_mq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_mq_getsetattr, libc_sys_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_kexec_load)
	movq   $(0xf6), %rax
	syscall
	ret
END(libc_sys_kexec_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_load, libc_sys_kexec_load)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox64_struct *infop, syscall_ulong_t options, struct rusagex64 *ru) */
INTERN_FUNCTION(libc_sys_waitid)
	movq   $(0xf7), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_waitid)
DEFINE_PUBLIC_ALIAS(sys_waitid, libc_sys_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_add_key)
	movq   $(0xf8), %rax
	syscall
	ret
END(libc_sys_add_key)
DEFINE_PUBLIC_ALIAS(sys_add_key, libc_sys_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_request_key)
	movq   $(0xf9), %rax
	syscall
	ret
END(libc_sys_request_key)
DEFINE_PUBLIC_ALIAS(sys_request_key, libc_sys_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_keyctl)
	movq   $(0xfa), %rax
	syscall
	ret
END(libc_sys_keyctl)
DEFINE_PUBLIC_ALIAS(sys_keyctl, libc_sys_keyctl)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_ioprio_set)
	movq   $(0xfb), %rax
	syscall
	ret
END(libc_sys_ioprio_set)
DEFINE_PUBLIC_ALIAS(sys_ioprio_set, libc_sys_ioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
INTERN_FUNCTION(libc_sys_ioprio_get)
	movq   $(0xfc), %rax
	syscall
	ret
END(libc_sys_ioprio_get)
DEFINE_PUBLIC_ALIAS(sys_ioprio_get, libc_sys_ioprio_get)

/* fd_t inotify_init(void) */
INTERN_FUNCTION(libc_sys_inotify_init)
	movq   $(0xfd), %rax
	syscall
	ret
END(libc_sys_inotify_init)
DEFINE_PUBLIC_ALIAS(sys_inotify_init, libc_sys_inotify_init)

/* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
INTERN_FUNCTION(libc_sys_inotify_add_watch)
	movq   $(0xfe), %rax
	syscall
	ret
END(libc_sys_inotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_add_watch, libc_sys_inotify_add_watch)

/* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
INTERN_FUNCTION(libc_sys_inotify_rm_watch)
	movq   $(0xff), %rax
	syscall
	ret
END(libc_sys_inotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_rm_watch, libc_sys_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_migrate_pages)
	movq   $(0x100), %rax
	syscall
	ret
END(libc_sys_migrate_pages)
DEFINE_PUBLIC_ALIAS(sys_migrate_pages, libc_sys_migrate_pages)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_openat)
	movq   $(0x101), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_openat)
DEFINE_PUBLIC_ALIAS(sys_openat, libc_sys_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdirat)
	movq   $(0x102), %rax
	syscall
	ret
END(libc_sys_mkdirat)
DEFINE_PUBLIC_ALIAS(sys_mkdirat, libc_sys_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_mknodat)
	movq   $(0x103), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mknodat)
DEFINE_PUBLIC_ALIAS(sys_mknodat, libc_sys_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchownat)
	movq   $(0x104), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fchownat)
DEFINE_PUBLIC_ALIAS(sys_fchownat, libc_sys_fchownat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx64 const[2] times) */
INTERN_FUNCTION(libc_sys_futimesat)
	movq   $(0x105), %rax
	syscall
	ret
END(libc_sys_futimesat)
DEFINE_PUBLIC_ALIAS(sys_futimesat, libc_sys_futimesat)

/* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_newfstatat)
	movq   $(0x106), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_newfstatat)
DEFINE_PUBLIC_ALIAS(sys_newfstatat, libc_sys_newfstatat)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
INTERN_FUNCTION(libc_sys_unlinkat)
	movq   $(0x107), %rax
	syscall
	ret
END(libc_sys_unlinkat)
DEFINE_PUBLIC_ALIAS(sys_unlinkat, libc_sys_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_renameat)
	movq   $(0x108), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_renameat)
DEFINE_PUBLIC_ALIAS(sys_renameat, libc_sys_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_linkat)
	movq   $(0x109), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_linkat)
DEFINE_PUBLIC_ALIAS(sys_linkat, libc_sys_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
INTERN_FUNCTION(libc_sys_symlinkat)
	movq   $(0x10a), %rax
	syscall
	ret
END(libc_sys_symlinkat)
DEFINE_PUBLIC_ALIAS(sys_symlinkat, libc_sys_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_readlinkat)
	movq   $(0x10b), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_readlinkat)
DEFINE_PUBLIC_ALIAS(sys_readlinkat, libc_sys_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchmodat)
	movq   $(0x10c), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fchmodat)
DEFINE_PUBLIC_ALIAS(sys_fchmodat, libc_sys_fchmodat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_faccessat)
	movq   $(0x10d), %rax
	syscall
	ret
END(libc_sys_faccessat)
DEFINE_PUBLIC_ALIAS(sys_faccessat, libc_sys_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx64 const *timeout, struct __sigset_with_sizex64 const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_pselect6)
	movq   $(0x10e), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pselect6)
DEFINE_PUBLIC_ALIAS(sys_pselect6, libc_sys_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_ppoll)
	movq   $(0x10f), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_ppoll)
DEFINE_PUBLIC_ALIAS(sys_ppoll, libc_sys_ppoll)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
INTERN_FUNCTION(libc_sys_unshare)
	movq   $(0x110), %rax
	syscall
	ret
END(libc_sys_unshare)
DEFINE_PUBLIC_ALIAS(sys_unshare, libc_sys_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_set_robust_list)
	movq   $(0x111), %rax
	syscall
	ret
END(libc_sys_set_robust_list)
DEFINE_PUBLIC_ALIAS(sys_set_robust_list, libc_sys_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_get_robust_list)
	movq   $(0x112), %rax
	syscall
	ret
END(libc_sys_get_robust_list)
DEFINE_PUBLIC_ALIAS(sys_get_robust_list, libc_sys_get_robust_list)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_splice)
	movq   $(0x113), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_splice)
DEFINE_PUBLIC_ALIAS(sys_splice, libc_sys_splice)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_tee)
	movq   $(0x114), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_tee)
DEFINE_PUBLIC_ALIAS(sys_tee, libc_sys_tee)

/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_sync_file_range)
	movq   $(0x115), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_sync_file_range)
DEFINE_PUBLIC_ALIAS(sys_sync_file_range, libc_sys_sync_file_range)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovecx64 const *iov, size_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_vmsplice)
	movq   $(0x116), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_vmsplice)
DEFINE_PUBLIC_ALIAS(sys_vmsplice, libc_sys_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_move_pages)
	movq   $(0x117), %rax
	syscall
	ret
END(libc_sys_move_pages)
DEFINE_PUBLIC_ALIAS(sys_move_pages, libc_sys_move_pages)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx64 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_utimensat)
	movq   $(0x118), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_utimensat)
DEFINE_PUBLIC_ALIAS(sys_utimensat, libc_sys_utimensat)

/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_epoll_pwait)
	movq   $(0x119), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_epoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_epoll_pwait, libc_sys_epoll_pwait)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
INTERN_FUNCTION(libc_sys_signalfd)
	movq   $(0x11a), %rax
	syscall
	ret
END(libc_sys_signalfd)
DEFINE_PUBLIC_ALIAS(sys_signalfd, libc_sys_signalfd)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_timerfd_create)
	movq   $(0x11b), %rax
	syscall
	ret
END(libc_sys_timerfd_create)
DEFINE_PUBLIC_ALIAS(sys_timerfd_create, libc_sys_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_eventfd)
	movq   $(0x11c), %rax
	syscall
	ret
END(libc_sys_eventfd)
DEFINE_PUBLIC_ALIAS(sys_eventfd, libc_sys_eventfd)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_fallocate)
	movq   $(0x11d), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fallocate)
DEFINE_PUBLIC_ALIAS(sys_fallocate, libc_sys_fallocate)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx64 const *utmr, struct itimerspecx64 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_settime)
	movq   $(0x11e), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_timerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_settime, libc_sys_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx64 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_gettime)
	movq   $(0x11f), %rax
	syscall
	ret
END(libc_sys_timerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_gettime, libc_sys_timerfd_gettime)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
INTERN_FUNCTION(libc_sys_accept4)
	movq   $(0x120), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_accept4)
DEFINE_PUBLIC_ALIAS(sys_accept4, libc_sys_accept4)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_signalfd4)
	movq   $(0x121), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_signalfd4)
DEFINE_PUBLIC_ALIAS(sys_signalfd4, libc_sys_signalfd4)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_eventfd2)
	movq   $(0x122), %rax
	syscall
	ret
END(libc_sys_eventfd2)
DEFINE_PUBLIC_ALIAS(sys_eventfd2, libc_sys_eventfd2)

/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_epoll_create1)
	movq   $(0x123), %rax
	syscall
	ret
END(libc_sys_epoll_create1)
DEFINE_PUBLIC_ALIAS(sys_epoll_create1, libc_sys_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
INTERN_FUNCTION(libc_sys_dup3)
	movq   $(0x124), %rax
	syscall
	ret
END(libc_sys_dup3)
DEFINE_PUBLIC_ALIAS(sys_dup3, libc_sys_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
INTERN_FUNCTION(libc_sys_pipe2)
	movq   $(0x125), %rax
	syscall
	ret
END(libc_sys_pipe2)
DEFINE_PUBLIC_ALIAS(sys_pipe2, libc_sys_pipe2)

/* fd_t inotify_init1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_inotify_init1)
	movq   $(0x126), %rax
	syscall
	ret
END(libc_sys_inotify_init1)
DEFINE_PUBLIC_ALIAS(sys_inotify_init1, libc_sys_inotify_init1)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_preadv)
	movq   $(0x127), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_preadv)
DEFINE_PUBLIC_ALIAS(sys_preadv, libc_sys_preadv)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwritev)
	movq   $(0x128), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pwritev)
DEFINE_PUBLIC_ALIAS(sys_pwritev, libc_sys_pwritev)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_tgsigqueueinfo)
	movq   $(0x129), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_rt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_tgsigqueueinfo, libc_sys_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_perf_event_open)
	movq   $(0x12a), %rax
	syscall
	ret
END(libc_sys_perf_event_open)
DEFINE_PUBLIC_ALIAS(sys_perf_event_open, libc_sys_perf_event_open)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx64 const *tmo) */
INTERN_FUNCTION(libc_sys_recvmmsg)
	movq   $(0x12b), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_recvmmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmmsg, libc_sys_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fanotify_init)
	movq   $(0x12c), %rax
	syscall
	ret
END(libc_sys_fanotify_init)
DEFINE_PUBLIC_ALIAS(sys_fanotify_init, libc_sys_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fanotify_mark)
	movq   $(0x12d), %rax
	syscall
	ret
END(libc_sys_fanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_fanotify_mark, libc_sys_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimitx64 const *new_limit, struct rlimitx64 *old_limit) */
INTERN_FUNCTION(libc_sys_prlimit64)
	movq   $(0x12e), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_prlimit64)
DEFINE_PUBLIC_ALIAS(sys_prlimit64, libc_sys_prlimit64)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
INTERN_FUNCTION(libc_sys_name_to_handle_at)
	movq   $(0x12f), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_name_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_name_to_handle_at, libc_sys_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
INTERN_FUNCTION(libc_sys_open_by_handle_at)
	movq   $(0x130), %rax
	syscall
	ret
END(libc_sys_open_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_open_by_handle_at, libc_sys_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_clock_adjtime)
	movq   $(0x131), %rax
	syscall
	ret
END(libc_sys_clock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_clock_adjtime, libc_sys_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_syncfs)
	movq   $(0x132), %rax
	syscall
	ret
END(libc_sys_syncfs)
DEFINE_PUBLIC_ALIAS(sys_syncfs, libc_sys_syncfs)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_sendmmsg)
	movq   $(0x133), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_sendmmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmmsg, libc_sys_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_setns)
	movq   $(0x134), %rax
	syscall
	ret
END(libc_sys_setns)
DEFINE_PUBLIC_ALIAS(sys_setns, libc_sys_setns)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_getcpu)
	movq   $(0x135), %rax
	syscall
	ret
END(libc_sys_getcpu)
DEFINE_PUBLIC_ALIAS(sys_getcpu, libc_sys_getcpu)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_readv)
	movq   $(0x136), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_process_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_process_vm_readv, libc_sys_process_vm_readv)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_writev)
	movq   $(0x137), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_process_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_process_vm_writev, libc_sys_process_vm_writev)

/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_kcmp)
	movq   $(0x138), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_kcmp)
DEFINE_PUBLIC_ALIAS(sys_kcmp, libc_sys_kcmp)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_finit_module)
	movq   $(0x139), %rax
	syscall
	ret
END(libc_sys_finit_module)
DEFINE_PUBLIC_ALIAS(sys_finit_module, libc_sys_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sched_setattr)
	movq   $(0x13a), %rax
	syscall
	ret
END(libc_sys_sched_setattr)
DEFINE_PUBLIC_ALIAS(sys_sched_setattr, libc_sys_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sched_getattr)
	movq   $(0x13b), %rax
	syscall
	ret
END(libc_sys_sched_getattr)
DEFINE_PUBLIC_ALIAS(sys_sched_getattr, libc_sys_sched_getattr)

/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
INTERN_FUNCTION(libc_sys_renameat2)
	movq   $(0x13c), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_renameat2)
DEFINE_PUBLIC_ALIAS(sys_renameat2, libc_sys_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_seccomp)
	movq   $(0x13d), %rax
	syscall
	ret
END(libc_sys_seccomp)
DEFINE_PUBLIC_ALIAS(sys_seccomp, libc_sys_seccomp)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_getrandom)
	movq   $(0x13e), %rax
	syscall
	ret
END(libc_sys_getrandom)
DEFINE_PUBLIC_ALIAS(sys_getrandom, libc_sys_getrandom)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_memfd_create)
	movq   $(0x13f), %rax
	syscall
	ret
END(libc_sys_memfd_create)
DEFINE_PUBLIC_ALIAS(sys_memfd_create, libc_sys_memfd_create)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_kexec_file_load)
	movq   $(0x140), %rax
	syscall
	ret
END(libc_sys_kexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_file_load, libc_sys_kexec_file_load)

/* errno_t bpf(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_bpf)
	movq   $(0x141), %rax
	syscall
	ret
END(libc_sys_bpf)
DEFINE_PUBLIC_ALIAS(sys_bpf, libc_sys_bpf)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
INTERN_FUNCTION(libc_sys_execveat)
	movq   $(0x142), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_execveat)
DEFINE_PUBLIC_ALIAS(sys_execveat, libc_sys_execveat)

/* fd_t userfaultfd(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_userfaultfd)
	movq   $(0x143), %rax
	syscall
	ret
END(libc_sys_userfaultfd)
DEFINE_PUBLIC_ALIAS(sys_userfaultfd, libc_sys_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_membarrier)
	movq   $(0x144), %rax
	syscall
	ret
END(libc_sys_membarrier)
DEFINE_PUBLIC_ALIAS(sys_membarrier, libc_sys_membarrier)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_mlock2)
	movq   $(0x145), %rax
	syscall
	ret
END(libc_sys_mlock2)
DEFINE_PUBLIC_ALIAS(sys_mlock2, libc_sys_mlock2)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_copy_file_range)
	movq   $(0x146), %rax
	syscall
	ret
END(libc_sys_copy_file_range)
DEFINE_PUBLIC_ALIAS(sys_copy_file_range, libc_sys_copy_file_range)

/* errno_t preadv2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_preadv2)
	movq   $(0x147), %rax
	syscall
	ret
END(libc_sys_preadv2)
DEFINE_PUBLIC_ALIAS(sys_preadv2, libc_sys_preadv2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pwritev2)
	movq   $(0x148), %rax
	syscall
	ret
END(libc_sys_pwritev2)
DEFINE_PUBLIC_ALIAS(sys_pwritev2, libc_sys_pwritev2)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
INTERN_FUNCTION(libc_sys_pkey_mprotect)
	movq   $(0x149), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_pkey_mprotect, libc_sys_pkey_mprotect)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
INTERN_FUNCTION(libc_sys_pkey_alloc)
	movq   $(0x14a), %rax
	syscall
	ret
END(libc_sys_pkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_pkey_alloc, libc_sys_pkey_alloc)

/* errno_t pkey_free(syscall_ulong_t key) */
INTERN_FUNCTION(libc_sys_pkey_free)
	movq   $(0x14b), %rax
	syscall
	ret
END(libc_sys_pkey_free)
DEFINE_PUBLIC_ALIAS(sys_pkey_free, libc_sys_pkey_free)

/* errno_t statx(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_statx)
	movq   $(0x14c), %rax
	syscall
	ret
END(libc_sys_statx)
DEFINE_PUBLIC_ALIAS(sys_statx, libc_sys_statx)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_pgetevents)
	movq   $(0x14d), %rax
	syscall
	ret
END(libc_sys_io_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_io_pgetevents, libc_sys_io_pgetevents)

/* errno_t rseq(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_rseq)
	movq   $(0x14e), %rax
	syscall
	ret
END(libc_sys_rseq)
DEFINE_PUBLIC_ALIAS(sys_rseq, libc_sys_rseq)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_PIDFD'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:                 [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox64_struct const *uinfo, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_send_signal)
	movq   $(0x1a8), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_pidfd_send_signal, libc_sys_pidfd_send_signal)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_setup)
	movq   $(0x1a9), %rax
	syscall
	ret
END(libc_sys_io_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_io_uring_setup, libc_sys_io_uring_setup)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_enter)
	movq   $(0x1aa), %rax
	syscall
	ret
END(libc_sys_io_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_io_uring_enter, libc_sys_io_uring_enter)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_register)
	movq   $(0x1ab), %rax
	syscall
	ret
END(libc_sys_io_uring_register)
DEFINE_PUBLIC_ALIAS(sys_io_uring_register, libc_sys_io_uring_register)

/* errno_t open_tree(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_open_tree)
	movq   $(0x1ac), %rax
	syscall
	ret
END(libc_sys_open_tree)
DEFINE_PUBLIC_ALIAS(sys_open_tree, libc_sys_open_tree)

/* errno_t move_mount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_move_mount)
	movq   $(0x1ad), %rax
	syscall
	ret
END(libc_sys_move_mount)
DEFINE_PUBLIC_ALIAS(sys_move_mount, libc_sys_move_mount)

/* errno_t fsopen(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsopen)
	movq   $(0x1ae), %rax
	syscall
	ret
END(libc_sys_fsopen)
DEFINE_PUBLIC_ALIAS(sys_fsopen, libc_sys_fsopen)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsconfig)
	movq   $(0x1af), %rax
	syscall
	ret
END(libc_sys_fsconfig)
DEFINE_PUBLIC_ALIAS(sys_fsconfig, libc_sys_fsconfig)

/* errno_t fsmount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsmount)
	movq   $(0x1b0), %rax
	syscall
	ret
END(libc_sys_fsmount)
DEFINE_PUBLIC_ALIAS(sys_fsmount, libc_sys_fsmount)

/* errno_t fspick(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fspick)
	movq   $(0x1b1), %rax
	syscall
	ret
END(libc_sys_fspick)
DEFINE_PUBLIC_ALIAS(sys_fspick, libc_sys_fspick)

/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_open)
	movq   $(0x1b2), %rax
	syscall
	ret
END(libc_sys_pidfd_open)
DEFINE_PUBLIC_ALIAS(sys_pidfd_open, libc_sys_pidfd_open)

/* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
INTERN_FUNCTION(libc_sys_clone3)
	movq   $(0x1b3), %rax
	syscall
	ret
END(libc_sys_clone3)
DEFINE_PUBLIC_ALIAS(sys_clone3, libc_sys_clone3)

/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
/* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
INTERN_FUNCTION(libc_sys_close_range)
	movq   $(0x1b4), %rax
	syscall
	ret
END(libc_sys_close_range)
DEFINE_PUBLIC_ALIAS(sys_close_range, libc_sys_close_range)

/* errno_t openat2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_openat2)
	movq   $(0x1b5), %rax
	syscall
	ret
END(libc_sys_openat2)
DEFINE_PUBLIC_ALIAS(sys_openat2, libc_sys_openat2)

/* Duplicate the  handle  of  a  foreign  process into  a  handle  for  the  caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_PIDFD'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_getfd)
	movq   $(0x1b6), %rax
	syscall
	ret
END(libc_sys_pidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_pidfd_getfd, libc_sys_pidfd_getfd)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
INTERN_FUNCTION(libc_sys_faccessat2)
	movq   $(0x1b7), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_faccessat2)
DEFINE_PUBLIC_ALIAS(sys_faccessat2, libc_sys_faccessat2)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwritevf)
	movq   $(0xfffffffffffffed8), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pwritevf)
DEFINE_PUBLIC_ALIAS(sys_pwritevf, libc_sys_pwritevf)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_preadvf)
	movq   $(0xfffffffffffffed9), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_preadvf)
DEFINE_PUBLIC_ALIAS(sys_preadvf, libc_sys_preadvf)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_freadlinkat)
	movq   $(0xfffffffffffffef5), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_freadlinkat)
DEFINE_PUBLIC_ALIAS(sys_freadlinkat, libc_sys_freadlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fsymlinkat)
	movq   $(0xfffffffffffffef6), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_fsymlinkat, libc_sys_fsymlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_kfstatat)
	movq   $(0xfffffffffffffefa), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_kfstatat)
DEFINE_PUBLIC_ALIAS(sys_kfstatat, libc_sys_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmknodat)
	movq   $(0xfffffffffffffefd), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fmknodat)
DEFINE_PUBLIC_ALIAS(sys_fmknodat, libc_sys_fmknodat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmkdirat)
	movq   $(0xfffffffffffffefe), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_fmkdirat)
DEFINE_PUBLIC_ALIAS(sys_fmkdirat, libc_sys_fmkdirat)

/* int inotify_add_watch_at(fd_t notify_fd, fd_t dfd, char const *pathname, atflag_t atflags, uint32_t mask) */
INTERN_FUNCTION(libc_sys_inotify_add_watch_at)
	movq   $(0xffffffffffffff02), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_inotify_add_watch_at)
DEFINE_PUBLIC_ALIAS(sys_inotify_add_watch_at, libc_sys_inotify_add_watch_at)

/* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_ksysctl)
	movq   $(0xffffffffffffff64), %rax
	syscall
	ret
END(libc_sys_ksysctl)
DEFINE_PUBLIC_ALIAS(sys_ksysctl, libc_sys_ksysctl)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN |
 *                MAP_GROWSUP  |  MAP_LOCKED  |  MAP_NORESERVE  |
 *                MAP_POPULATE  |  MAP_NONBLOCK   |  MAP_SYNC   |
 *                MAP_FIXED_NOREPLACE | MAP_NOASLR'
 * @param: fd:    A handle for the library file being mapped (must be mmap(2)-able)
 * @param: hdrv:  Pointer  to  a vector  of `Elf32_Phdr'  or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr const *hdrv, size_t hdrc) */
INTERN_FUNCTION(libc_sys_maplibrary)
	movq   $(0xffffffffffffff7a), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_maplibrary)
DEFINE_PUBLIC_ALIAS(sys_maplibrary, libc_sys_maplibrary)

/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_fsmode)
	movq   $(0xffffffffffffffa1), %rax
	syscall
	ret
END(libc_sys_fsmode)
DEFINE_PUBLIC_ALIAS(sys_fsmode, libc_sys_fsmode)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchdirat)
	movq   $(0xffffffffffffffb0), %rax
	syscall
	ret
END(libc_sys_fchdirat)
DEFINE_PUBLIC_ALIAS(sys_fchdirat, libc_sys_fchdirat)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
INTERN_FUNCTION(libc_sys_kreaddirf)
	movq   $(0xffffffffffffffb1), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_kreaddirf)
DEFINE_PUBLIC_ALIAS(sys_kreaddirf, libc_sys_kreaddirf)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_kreaddir)
	movq   $(0xffffffffffffffb2), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_kreaddir)
DEFINE_PUBLIC_ALIAS(sys_kreaddir, libc_sys_kreaddir)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   - Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   - Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                           EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                           &except_handler4, NULL)'
 * @param: mode:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: handler:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: handler_sp: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given `mode' is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
INTERN_FUNCTION(libc_sys_set_exception_handler)
	movq   $(0xffffffffffffffd9), %rax
	syscall
	ret
END(libc_sys_set_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_set_exception_handler, libc_sys_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: pmode:       When non-`NULL', store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: phandler:    When   non-`NULL',   store  the   address   of  the   user-space   exception  handler.
 *                      Note that when no handler has been set (`!(*pmode & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: phandler_sp: When non-`NULL', store the starting address of the user-space exception handler stack.
 *                      Note that  when no  stack has  been set  (`!(*pmode & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-`NULL' and faulty */
/* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
INTERN_FUNCTION(libc_sys_get_exception_handler)
	movq   $(0xffffffffffffffda), %rax
	syscall
	ret
END(libc_sys_get_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_get_exception_handler, libc_sys_get_exception_handler)

/* >> rpc_serve_sysret(2)
 * Very similar to `rpc_serve(2)', but with the addition that this one
 * will only serve RPCs that can be handled in `RPC_REASONCTX_SYSRET',
 * aka. `RPC_REASONCTX_ASYNC' contexts. Additionally, this system call
 * ignores the state of the  internal `TASK_FRPC' flag, and should  be
 * invoked  when  the calling  thread  makes use  of  the userprocmask
 * mechanism, and the  signal mask became  less restrictive while  the
 * `USERPROCMASK_FLAG_HASPENDING' flag was set.
 * 
 * When userprocmask is disabled, this system call is pretty much just
 * a no-op (semnatically speaking, it does nothing). But when enabled,
 * it is really only usable  in conjuction with the userprocmask.  The
 * exact usage can be seen in `chkuserprocmask(3)'.
 * 
 * @return: 0 : Always, unconditionally returned. */
/* errno_t rpc_serve_sysret(void) */
INTERN_FUNCTION(libc_sys_rpc_serve_sysret)
	movq   $(0xffffffffffffffdb), %rax
	syscall
	ret
END(libc_sys_rpc_serve_sysret)
DEFINE_PUBLIC_ALIAS(sys_rpc_serve_sysret, libc_sys_rpc_serve_sysret)

/* Register the address of  the calling thread's userprocmask  controller.
 * This also  initializes `*ctl->pm_sigmask'  and `ctl->pm_pending',  such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level  signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally,  the address  of `&ctl->pm_mytid'  is stored  as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using  atomic-or for the later) from  this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional,   arch-specific   fields    to   all    zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the  `pm_sigmask'
 *       of the previously set  controller into its internal  signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though  that  `pm_sigmask'  is ignored  for  `SIGKILL'  and  `SIGSTOP'
 * Note also  that  this  function replaces  `set_tid_address(2)',  such  that
 * it negates a  prior call  to said  function, while  a future  call to  said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
INTERN_FUNCTION(libc_sys_set_userprocmask_address)
	movq   $(0xffffffffffffffdc), %rax
	syscall
	ret
END(libc_sys_set_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_set_userprocmask_address, libc_sys_set_userprocmask_address)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
INTERN_FUNCTION(libc_sys_rtm_test)
	movq   $(0xffffffffffffffdd), %rax
	syscall
	ret
END(libc_sys_rtm_test)
DEFINE_PUBLIC_ALIAS(sys_rtm_test, libc_sys_rtm_test)

/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
INTERN_FUNCTION(libc_sys_rtm_abort)
	movq   $(0xffffffffffffffde), %rax
	syscall
	ret
END(libc_sys_rtm_abort)
DEFINE_PUBLIC_ALIAS(sys_rtm_abort, libc_sys_rtm_abort)

/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
INTERN_FUNCTION(libc_sys_rtm_end)
	movq   $(0xffffffffffffffdf), %rax
	syscall
	ret
END(libc_sys_rtm_end)
DEFINE_PUBLIC_ALIAS(sys_rtm_end, libc_sys_rtm_end)

/* Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM  operation is in progress,  only a very small  hand
 * full  of system calls are allowed to  be used. Attempting to use arbitrary
 * system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
 * attempting to access too much system memory in general will result in this
 * function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
 * The following is  a list  of system calls  which are  whitelisted for  use
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
INTERN_FUNCTION(libc_sys_rtm_begin)
	movq   $(0xffffffffffffffe0), %rax
	syscall
	ret
END(libc_sys_rtm_begin)
DEFINE_PUBLIC_ALIAS(sys_rtm_begin, libc_sys_rtm_begin)

/* Construct   a   user-vio-fd  object   supporting  mmap(2),   with  actual
 * memory  accesses  being dispatched  by  adding them  as  pending requests
 * to an internal  queue that  should be read(2)  from by  a worker  thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This  size may be  altered at a  later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_userviofd)
	movq   $(0xffffffffffffffe1), %rax
	syscall
	ret
END(libc_sys_userviofd)
DEFINE_PUBLIC_ALIAS(sys_userviofd, libc_sys_userviofd)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The  state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `reason' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When   `curr_state'   is   also   `NULL',   then   the   current   CPU   state   is   used   instead.
 * @param: traceback_vector: (potentially  incomplete)   vector  of   additional  program   pointers  that   were
 *                           traversed   when   the  stack   was   walked  from   `orig_state'   to  `curr_state'
 *                           Note that earlier  entries within this  vector are further  up the call-stack,  with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it  can  be  assumed  that  the  traceback is  complete  and  contains  all  traversed  instruction locations.
 *                           In   this   case,  a   traceback  displayed   to   a  human   should  not   include   the  text   location  at
 *                           `traceback_vector[traceback_length-1]',    since    that    location    would    also    be    printed    when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: reason:           The reason that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           For certain `unwind_error' values, this can also  point to other things, but is  always
 *                           allowed to be `NULL' to indicate default/stub values.
 * @param: unwind_error:     The  unwind  error that  caused the  coredump,  or `UNWIND_SUCCESS'  if unwinding
 *                           was  never  actually  performed,  and   `reason'  is  actually  a   `siginfo_t *'
 *                           Ignored when `reason == NULL', in which case `UNWIND_SUCCESS' is assumed instead. */
/* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void const) const *traceback_vector, size_t traceback_length, union coredump_info64 const *reason, syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_coredump)
	movq   $(0xffffffffffffffe3), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_coredump)
DEFINE_PUBLIC_ALIAS(sys_coredump, libc_sys_coredump)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_mktty)
	movq   $(0xffffffffffffffe5), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_mktty)
DEFINE_PUBLIC_ALIAS(sys_mktty, libc_sys_mktty)

/* >> lfutexexpr(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: futexaddr: The futex on which to wait
 * @param: base:      Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:      Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:   Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 *                    When `LFUTEX_FDBIT'  is  set,  this argument  must  be  `NULL'.
 * @param: flags:     Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*' or `LFUTEX_FDBIT'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 *              When `LFUTEX_FDBIT' is set, the return value is an `fd_t' for a futex fd that
 *              can be used to poll for the specified `exprv'. Note that in this case `exprv'
 *              is limited to `LFUTEXFD_DEFAULT_MAXEXPR' (`/proc/kos/futexfd-maxexpr')
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(uint64_t *futexaddr, void *base, struct lfutexexprx64 const *expr, struct timespecx64 const *timeout, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_lfutexexpr)
	movq   $(0xffffffffffffffe6), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_lfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_lfutexexpr, libc_sys_lfutexexpr)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct timespecx64 const *timeout, uint64_t val2) */
INTERN_FUNCTION(libc_sys_lfutex)
	movq   $(0xffffffffffffffe8), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_lfutex)
DEFINE_PUBLIC_ALIAS(sys_lfutex, libc_sys_lfutex)

/* >> rpc_serve(2)
 * Check for pending signals and RPCs. This is a wrapper around the
 * kernel `task_serve()' function, which is always invoked before a
 * thread begins waiting for a blocking operation. All system calls
 * marked as cancellation  points probably  call `task_serve()'  at
 * some point.
 * Note that unlike (say) `pause(2)', this function doesn't  block,
 * and may be used to implement `pthread_testcancel(3)' (should KOS
 * RPCs be used to facility pthread cancellation points, as done by
 * KOS's builtin libc)
 * @return: 0:      Nothing was handled.
 * @return: -EINTR: RPCs (or posix signals) were handled. */
/* errno_t rpc_serve(void) */
INTERN_FUNCTION(libc_sys_rpc_serve)
	movq   $(0xffffffffffffffe9), %rax
	syscall
	ret
END(libc_sys_rpc_serve)
DEFINE_PUBLIC_ALIAS(sys_rpc_serve, libc_sys_rpc_serve)

/* Trigger a debugger trap `trapno', optionally extended with  `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to  the
 * given  `state', though given the purpose of this system call being
 * to inform a connected debugger  of some breakable event,  allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
INTERN_FUNCTION(libc_sys_debugtrap)
	movq   $(0xffffffffffffffea), %rax
	syscall
	ret
END(libc_sys_debugtrap)
DEFINE_PUBLIC_ALIAS(sys_debugtrap, libc_sys_debugtrap)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_writevf)
	movq   $(0xffffffffffffffec), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_writevf)
DEFINE_PUBLIC_ALIAS(sys_writevf, libc_sys_writevf)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_readvf)
	movq   $(0xffffffffffffffed), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_readvf)
DEFINE_PUBLIC_ALIAS(sys_readvf, libc_sys_readvf)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwrite64f)
	movq   $(0xffffffffffffffee), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pwrite64f)
DEFINE_PUBLIC_ALIAS(sys_pwrite64f, libc_sys_pwrite64f)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pread64f)
	movq   $(0xffffffffffffffef), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_pread64f)
DEFINE_PUBLIC_ALIAS(sys_pread64f, libc_sys_pread64f)

/* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
INTERN_FUNCTION(libc_sys_ioctlf)
	movq   $(0xfffffffffffffff0), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_ioctlf)
DEFINE_PUBLIC_ALIAS(sys_ioctlf, libc_sys_ioctlf)

/* Restore  the  given CPU/FPU  context descriptors,  as  well as  signal mask
 * before resuming execution by either invoking another system call `sc_info',
 * which  will then return  to `restore_cpu', or  by directly returning there.
 * Arguments:
 *  - %rbp: [1..1] struct ucpustate64 const *restore_cpu;
 *  - %rbx: [0..1] struct fpustate64 const *restore_fpu;
 *  - %r12: [0..1] struct __sigset_with_sizex64 const *restore_sigmask;
 *  - %r13: [0..1] struct rpc_syscall_info64 const *sc_info;
 * This system call uses a custom calling convention because registers passed
 * must not get clobbered  during execution of a  normal C function. On  i386
 * this doesn't require  a custom calling  convention since enough  registers
 * exist  that are preserved by a C function,  but are still used by at least
 * one  system call invocation  method. However on  x86_64, no such registers
 * exist, requiring the use of a custom protocol. */
/* void ksigreturn(void) */
INTERN_FUNCTION(libc_sys_ksigreturn)
	movq   $(0xfffffffffffffff1), %rax
	syscall
	ret
END(libc_sys_ksigreturn)
DEFINE_PUBLIC_ALIAS(sys_ksigreturn, libc_sys_ksigreturn)

/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_openpty)
	movq   $(0xfffffffffffffff3), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_openpty)
DEFINE_PUBLIC_ALIAS(sys_openpty, libc_sys_openpty)

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 * 
 * NOTE: Only a cancellation point when `RPC_JOIN_WAITFOR' is used!
 * 
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 * 
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
/* errno_t rpc_schedule(pid_t target_tid, syscall_ulong_t mode, void const *program, __HYBRID_PTR64(void const) const *params, size_t max_param_count) */
INTERN_FUNCTION(libc_sys_rpc_schedule)
	movq   $(0xfffffffffffffff4), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_rpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_rpc_schedule, libc_sys_rpc_schedule)

/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpathat)
	movq   $(0xfffffffffffffff5), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_frealpathat)
DEFINE_PUBLIC_ALIAS(sys_frealpathat, libc_sys_frealpathat)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpath4)
	movq   $(0xfffffffffffffff6), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_frealpath4)
DEFINE_PUBLIC_ALIAS(sys_frealpath4, libc_sys_frealpath4)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
INTERN_FUNCTION(libc_sys_getdrives)
	movq   $(0xfffffffffffffff7), %rax
	syscall
	ret
END(libc_sys_getdrives)
DEFINE_PUBLIC_ALIAS(sys_getdrives, libc_sys_getdrives)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the  thread from turning into  a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling  thread from  the set of  running children  within
 *     its own process.  Note however  that when this  is done  by the  main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the  calling   process   the   same  way   a   double-fork   would:
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
 *     Detach all child processes/threads  of the calling process,  essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * The given `pid' must be:
 *   - A thread without the caller's process
 *   - A child process of the caller's process
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had  already
 *       be called.
 * @return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
 *                           a thread in your process, or a child process of your process. */
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_detach)
	movq   $(0xfffffffffffffff8), %rax
	syscall
	ret
END(libc_sys_detach)
DEFINE_PUBLIC_ALIAS(sys_detach, libc_sys_detach)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_readf)
	movq   $(0xfffffffffffffff9), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_readf)
DEFINE_PUBLIC_ALIAS(sys_readf, libc_sys_readf)

/* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_klstat)
	movq   $(0xfffffffffffffffa), %rax
	syscall
	ret
END(libc_sys_klstat)
DEFINE_PUBLIC_ALIAS(sys_klstat, libc_sys_klstat)

/* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_kfstat)
	movq   $(0xfffffffffffffffb), %rax
	syscall
	ret
END(libc_sys_kfstat)
DEFINE_PUBLIC_ALIAS(sys_kfstat, libc_sys_kfstat)

/* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_kstat)
	movq   $(0xfffffffffffffffc), %rax
	syscall
	ret
END(libc_sys_kstat)
DEFINE_PUBLIC_ALIAS(sys_kstat, libc_sys_kstat)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_writef)
	movq   $(0xffffffffffffffff), %rax
	movq   %rcx, %r10
	syscall
	ret
END(libc_sys_writef)
DEFINE_PUBLIC_ALIAS(sys_writef, libc_sys_writef)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xread)
	xorq   %rax, %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xread)
DEFINE_PUBLIC_ALIAS(sys_Xread, libc_sys_Xread)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xwrite)
	movq   $(0x1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwrite)
DEFINE_PUBLIC_ALIAS(sys_Xwrite, libc_sys_Xwrite)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopen)
	movq   $(0x2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopen)
DEFINE_PUBLIC_ALIAS(sys_Xopen, libc_sys_Xopen)

/* Close a given file descriptor/handle `fd' */
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xclose)
	movq   $(0x3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclose)
DEFINE_PUBLIC_ALIAS(sys_Xclose, libc_sys_Xclose)

/* errno_t stat(char const *filename, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xstat)
	movq   $(0x4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xstat)
DEFINE_PUBLIC_ALIAS(sys_Xstat, libc_sys_Xstat)

/* errno_t fstat(fd_t fd, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xfstat)
	movq   $(0x5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfstat)
DEFINE_PUBLIC_ALIAS(sys_Xfstat, libc_sys_Xfstat)

/* errno_t lstat(char const *filename, struct linux_statx64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xlstat)
	movq   $(0x6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlstat)
DEFINE_PUBLIC_ALIAS(sys_Xlstat, libc_sys_Xlstat)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xpoll)
	movq   $(0x7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpoll)
DEFINE_PUBLIC_ALIAS(sys_Xpoll, libc_sys_Xpoll)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_Xlseek)
	movq   $(0x8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlseek)
DEFINE_PUBLIC_ALIAS(sys_Xlseek, libc_sys_Xlseek)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_Xmmap)
	movq   $(0x9), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmmap)
DEFINE_PUBLIC_ALIAS(sys_Xmmap, libc_sys_Xmmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_Xmprotect)
	movq   $(0xa), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmprotect)
DEFINE_PUBLIC_ALIAS(sys_Xmprotect, libc_sys_Xmprotect)

/* errno_t munmap(void *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmunmap)
	movq   $(0xb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmunmap)
DEFINE_PUBLIC_ALIAS(sys_Xmunmap, libc_sys_Xmunmap)

/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_Xbrk)
	movq   $(0xc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xbrk)
DEFINE_PUBLIC_ALIAS(sys_Xbrk, libc_sys_Xbrk)

/* errno_t rt_sigaction(signo_t signo, struct __kernel_sigactionx64 const *act, struct __kernel_sigactionx64 *oact, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigaction)
	movq   $(0xd), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigaction, libc_sys_Xrt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigprocmask)
	movq   $(0xe), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigprocmask, libc_sys_Xrt_sigprocmask)

/* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xioctl)
	movq   $(0x10), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xioctl)
DEFINE_PUBLIC_ALIAS(sys_Xioctl, libc_sys_Xioctl)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpread64)
	movq   $(0x11), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpread64)
DEFINE_PUBLIC_ALIAS(sys_Xpread64, libc_sys_Xpread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwrite64)
	movq   $(0x12), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpwrite64)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64, libc_sys_Xpwrite64)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovecx64 const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_Xreadv)
	movq   $(0x13), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadv)
DEFINE_PUBLIC_ALIAS(sys_Xreadv, libc_sys_Xreadv)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovecx64 const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_Xwritev)
	movq   $(0x14), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwritev)
DEFINE_PUBLIC_ALIAS(sys_Xwritev, libc_sys_Xwritev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_Xaccess)
	movq   $(0x15), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xaccess)
DEFINE_PUBLIC_ALIAS(sys_Xaccess, libc_sys_Xaccess)

/* errno_t pipe(fd_t[2] pipedes) */
INTERN_FUNCTION(libc_sys_Xpipe)
	movq   $(0x16), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpipe)
DEFINE_PUBLIC_ALIAS(sys_Xpipe, libc_sys_Xpipe)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx64 *timeout) */
INTERN_FUNCTION(libc_sys_Xselect)
	movq   $(0x17), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xselect)
DEFINE_PUBLIC_ALIAS(sys_Xselect, libc_sys_Xselect)

/* errno_t sched_yield(void) */
INTERN_FUNCTION(libc_sys_Xsched_yield)
	movq   $(0x18), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_yield)
DEFINE_PUBLIC_ALIAS(sys_Xsched_yield, libc_sys_Xsched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
INTERN_FUNCTION(libc_sys_Xmremap)
	movq   $(0x19), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmremap)
DEFINE_PUBLIC_ALIAS(sys_Xmremap, libc_sys_Xmremap)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmsync)
	movq   $(0x1a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmsync)
DEFINE_PUBLIC_ALIAS(sys_Xmsync, libc_sys_Xmsync)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
INTERN_FUNCTION(libc_sys_Xmincore)
	movq   $(0x1b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmincore)
DEFINE_PUBLIC_ALIAS(sys_Xmincore, libc_sys_Xmincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_Xmadvise)
	movq   $(0x1c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmadvise)
DEFINE_PUBLIC_ALIAS(sys_Xmadvise, libc_sys_Xmadvise)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_Xshmget)
	movq   $(0x1d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xshmget)
DEFINE_PUBLIC_ALIAS(sys_Xshmget, libc_sys_Xshmget)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_Xshmat)
	movq   $(0x1e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xshmat)
DEFINE_PUBLIC_ALIAS(sys_Xshmat, libc_sys_Xshmat)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
INTERN_FUNCTION(libc_sys_Xshmctl)
	movq   $(0x1f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xshmctl)
DEFINE_PUBLIC_ALIAS(sys_Xshmctl, libc_sys_Xshmctl)

/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xdup)
	movq   $(0x20), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdup)
DEFINE_PUBLIC_ALIAS(sys_Xdup, libc_sys_Xdup)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
INTERN_FUNCTION(libc_sys_Xdup2)
	movq   $(0x21), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdup2)
DEFINE_PUBLIC_ALIAS(sys_Xdup2, libc_sys_Xdup2)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
INTERN_FUNCTION(libc_sys_Xpause)
	movq   $(0x22), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpause)
DEFINE_PUBLIC_ALIAS(sys_Xpause, libc_sys_Xpause)

/* errno_t nanosleep(struct timespecx64 const *req, struct timespecx64 *rem) */
INTERN_FUNCTION(libc_sys_Xnanosleep)
	movq   $(0x23), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xnanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xnanosleep, libc_sys_Xnanosleep)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
INTERN_FUNCTION(libc_sys_Xgetitimer)
	movq   $(0x24), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xgetitimer, libc_sys_Xgetitimer)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_Xalarm)
	movq   $(0x25), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xalarm)
DEFINE_PUBLIC_ALIAS(sys_Xalarm, libc_sys_Xalarm)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
INTERN_FUNCTION(libc_sys_Xsetitimer)
	movq   $(0x26), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xsetitimer, libc_sys_Xsetitimer)

/* pid_t getpid(void) */
INTERN_FUNCTION(libc_sys_Xgetpid)
	movq   $(0x27), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpid, libc_sys_Xgetpid)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_Xsendfile)
	movq   $(0x28), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsendfile)
DEFINE_PUBLIC_ALIAS(sys_Xsendfile, libc_sys_Xsendfile)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_Xsocket)
	movq   $(0x29), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsocket)
DEFINE_PUBLIC_ALIAS(sys_Xsocket, libc_sys_Xsocket)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xconnect)
	movq   $(0x2a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xconnect)
DEFINE_PUBLIC_ALIAS(sys_Xconnect, libc_sys_Xconnect)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xaccept)
	movq   $(0x2b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xaccept)
DEFINE_PUBLIC_ALIAS(sys_Xaccept, libc_sys_Xaccept)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xsendto)
	movq   $(0x2c), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
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
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xrecvfrom)
	movq   $(0x2d), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrecvfrom)
DEFINE_PUBLIC_ALIAS(sys_Xrecvfrom, libc_sys_Xrecvfrom)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdrx64 const *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xsendmsg)
	movq   $(0x2e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsendmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmsg, libc_sys_Xsendmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdrx64 *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xrecvmsg)
	movq   $(0x2f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrecvmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmsg, libc_sys_Xrecvmsg)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xshutdown)
	movq   $(0x30), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xshutdown)
DEFINE_PUBLIC_ALIAS(sys_Xshutdown, libc_sys_Xshutdown)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xbind)
	movq   $(0x31), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xbind)
DEFINE_PUBLIC_ALIAS(sys_Xbind, libc_sys_Xbind)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_Xlisten)
	movq   $(0x32), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlisten)
DEFINE_PUBLIC_ALIAS(sys_Xlisten, libc_sys_Xlisten)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetsockname)
	movq   $(0x33), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetsockname)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockname, libc_sys_Xgetsockname)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetpeername)
	movq   $(0x34), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpeername)
DEFINE_PUBLIC_ALIAS(sys_Xgetpeername, libc_sys_Xgetpeername)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
INTERN_FUNCTION(libc_sys_Xsocketpair)
	movq   $(0x35), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
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
INTERN_FUNCTION(libc_sys_Xsetsockopt)
	movq   $(0x36), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xsetsockopt, libc_sys_Xsetsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_Xgetsockopt)
	movq   $(0x37), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockopt, libc_sys_Xgetsockopt)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
INTERN_FUNCTION(libc_sys_Xclone)
	movq   $(0x38), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclone)
DEFINE_PUBLIC_ALIAS(sys_Xclone, libc_sys_Xclone)

/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
INTERN_FUNCTION(libc_sys_Xfork)
	movq   $(0x39), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfork)
DEFINE_PUBLIC_ALIAS(sys_Xfork, libc_sys_Xfork)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
INTERN_FUNCTION(libc_sys_Xvfork)
	movq   $(0x3a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xvfork)
DEFINE_PUBLIC_ALIAS(sys_Xvfork, libc_sys_Xvfork)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
/* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
INTERN_FUNCTION(libc_sys_Xexecve)
	movq   $(0x3b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xexecve)
DEFINE_PUBLIC_ALIAS(sys_Xexecve, libc_sys_Xexecve)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_Xexit)
	movq   $(0x3c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xexit)
DEFINE_PUBLIC_ALIAS(sys_Xexit, libc_sys_Xexit)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex64 *usage) */
INTERN_FUNCTION(libc_sys_Xwait4)
	movq   $(0x3d), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwait4)
DEFINE_PUBLIC_ALIAS(sys_Xwait4, libc_sys_Xwait4)

/* errno_t kill(pid_t pid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xkill)
	movq   $(0x3e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkill)
DEFINE_PUBLIC_ALIAS(sys_Xkill, libc_sys_Xkill)

/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_Xuname)
	movq   $(0x3f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xuname)
DEFINE_PUBLIC_ALIAS(sys_Xuname, libc_sys_Xuname)

/* errno_t semget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemget)
	movq   $(0x40), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsemget)
DEFINE_PUBLIC_ALIAS(sys_Xsemget, libc_sys_Xsemget)

/* errno_t semop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemop)
	movq   $(0x41), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsemop)
DEFINE_PUBLIC_ALIAS(sys_Xsemop, libc_sys_Xsemop)

/* errno_t semctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemctl)
	movq   $(0x42), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsemctl)
DEFINE_PUBLIC_ALIAS(sys_Xsemctl, libc_sys_Xsemctl)

/* errno_t shmdt(void const *shmaddr) */
INTERN_FUNCTION(libc_sys_Xshmdt)
	movq   $(0x43), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xshmdt)
DEFINE_PUBLIC_ALIAS(sys_Xshmdt, libc_sys_Xshmdt)

/* errno_t msgget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgget)
	movq   $(0x44), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmsgget)
DEFINE_PUBLIC_ALIAS(sys_Xmsgget, libc_sys_Xmsgget)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgsnd)
	movq   $(0x45), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmsgsnd)
DEFINE_PUBLIC_ALIAS(sys_Xmsgsnd, libc_sys_Xmsgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgrcv)
	movq   $(0x46), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmsgrcv)
DEFINE_PUBLIC_ALIAS(sys_Xmsgrcv, libc_sys_Xmsgrcv)

/* errno_t msgctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgctl)
	movq   $(0x47), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmsgctl)
DEFINE_PUBLIC_ALIAS(sys_Xmsgctl, libc_sys_Xmsgctl)

/* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xfcntl)
	movq   $(0x48), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfcntl)
DEFINE_PUBLIC_ALIAS(sys_Xfcntl, libc_sys_Xfcntl)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_Xflock)
	movq   $(0x49), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xflock)
DEFINE_PUBLIC_ALIAS(sys_Xflock, libc_sys_Xflock)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfsync)
	movq   $(0x4a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsync)
DEFINE_PUBLIC_ALIAS(sys_Xfsync, libc_sys_Xfsync)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfdatasync)
	movq   $(0x4b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfdatasync)
DEFINE_PUBLIC_ALIAS(sys_Xfdatasync, libc_sys_Xfdatasync)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xtruncate)
	movq   $(0x4c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtruncate)
DEFINE_PUBLIC_ALIAS(sys_Xtruncate, libc_sys_Xtruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xftruncate)
	movq   $(0x4d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xftruncate)
DEFINE_PUBLIC_ALIAS(sys_Xftruncate, libc_sys_Xftruncate)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_direntx64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xgetdents)
	movq   $(0x4e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetdents)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents, libc_sys_Xgetdents)

/* ssize_t getcwd(char *buf, size_t size) */
INTERN_FUNCTION(libc_sys_Xgetcwd)
	movq   $(0x4f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetcwd)
DEFINE_PUBLIC_ALIAS(sys_Xgetcwd, libc_sys_Xgetcwd)

/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xchdir)
	movq   $(0x50), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xchdir)
DEFINE_PUBLIC_ALIAS(sys_Xchdir, libc_sys_Xchdir)

/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfchdir)
	movq   $(0x51), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchdir)
DEFINE_PUBLIC_ALIAS(sys_Xfchdir, libc_sys_Xfchdir)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrename)
	movq   $(0x52), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrename)
DEFINE_PUBLIC_ALIAS(sys_Xrename, libc_sys_Xrename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdir)
	movq   $(0x53), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmkdir)
DEFINE_PUBLIC_ALIAS(sys_Xmkdir, libc_sys_Xmkdir)

/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xrmdir)
	movq   $(0x54), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrmdir)
DEFINE_PUBLIC_ALIAS(sys_Xrmdir, libc_sys_Xrmdir)

/* fd_t creat(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xcreat)
	movq   $(0x55), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcreat)
DEFINE_PUBLIC_ALIAS(sys_Xcreat, libc_sys_Xcreat)

/* errno_t link(char const *existing_file, char const *link_file) */
INTERN_FUNCTION(libc_sys_Xlink)
	movq   $(0x56), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlink)
DEFINE_PUBLIC_ALIAS(sys_Xlink, libc_sys_Xlink)

/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_Xunlink)
	movq   $(0x57), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xunlink)
DEFINE_PUBLIC_ALIAS(sys_Xunlink, libc_sys_Xunlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlink)
	movq   $(0x58), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsymlink)
DEFINE_PUBLIC_ALIAS(sys_Xsymlink, libc_sys_Xsymlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlink)
	movq   $(0x59), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadlink)
DEFINE_PUBLIC_ALIAS(sys_Xreadlink, libc_sys_Xreadlink)

/* errno_t chmod(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xchmod)
	movq   $(0x5a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xchmod)
DEFINE_PUBLIC_ALIAS(sys_Xchmod, libc_sys_Xchmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xfchmod)
	movq   $(0x5b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchmod)
DEFINE_PUBLIC_ALIAS(sys_Xfchmod, libc_sys_Xfchmod)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_Xchown)
	movq   $(0x5c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xchown)
DEFINE_PUBLIC_ALIAS(sys_Xchown, libc_sys_Xchown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_Xfchown)
	movq   $(0x5d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchown)
DEFINE_PUBLIC_ALIAS(sys_Xfchown, libc_sys_Xfchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
INTERN_FUNCTION(libc_sys_Xlchown)
	movq   $(0x5e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlchown)
DEFINE_PUBLIC_ALIAS(sys_Xlchown, libc_sys_Xlchown)

/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_Xumask)
	movq   $(0x5f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xumask)
DEFINE_PUBLIC_ALIAS(sys_Xumask, libc_sys_Xumask)

/* errno_t gettimeofday(struct timevalx64 *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_Xgettimeofday)
	movq   $(0x60), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xgettimeofday, libc_sys_Xgettimeofday)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimitx64 *rlimits) */
INTERN_FUNCTION(libc_sys_Xgetrlimit)
	movq   $(0x61), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xgetrlimit, libc_sys_Xgetrlimit)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusagex64 *tv) */
INTERN_FUNCTION(libc_sys_Xgetrusage)
	movq   $(0x62), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetrusage)
DEFINE_PUBLIC_ALIAS(sys_Xgetrusage, libc_sys_Xgetrusage)

/* errno_t sysinfo(struct __sysinfox64 *info) */
INTERN_FUNCTION(libc_sys_Xsysinfo)
	movq   $(0x63), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsysinfo)
DEFINE_PUBLIC_ALIAS(sys_Xsysinfo, libc_sys_Xsysinfo)

/* clock_t times(struct tmsx64 *buf) */
INTERN_FUNCTION(libc_sys_Xtimes)
	movq   $(0x64), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimes)
DEFINE_PUBLIC_ALIAS(sys_Xtimes, libc_sys_Xtimes)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
INTERN_FUNCTION(libc_sys_Xptrace)
	movq   $(0x65), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xptrace)
DEFINE_PUBLIC_ALIAS(sys_Xptrace, libc_sys_Xptrace)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uid_t getuid(void) */
INTERN_FUNCTION(libc_sys_Xgetuid)
	movq   $(0x66), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetuid, libc_sys_Xgetuid)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
INTERN_FUNCTION(libc_sys_Xsyslog)
	movq   $(0x67), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsyslog)
DEFINE_PUBLIC_ALIAS(sys_Xsyslog, libc_sys_Xsyslog)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* gid_t getgid(void) */
INTERN_FUNCTION(libc_sys_Xgetgid)
	movq   $(0x68), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetgid, libc_sys_Xgetgid)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid(uid_t uid) */
INTERN_FUNCTION(libc_sys_Xsetuid)
	movq   $(0x69), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetuid, libc_sys_Xsetuid)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid(gid_t gid) */
INTERN_FUNCTION(libc_sys_Xsetgid)
	movq   $(0x6a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetgid, libc_sys_Xsetgid)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uid_t geteuid(void) */
INTERN_FUNCTION(libc_sys_Xgeteuid)
	movq   $(0x6b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgeteuid)
DEFINE_PUBLIC_ALIAS(sys_Xgeteuid, libc_sys_Xgeteuid)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* gid_t getegid(void) */
INTERN_FUNCTION(libc_sys_Xgetegid)
	movq   $(0x6c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetegid)
DEFINE_PUBLIC_ALIAS(sys_Xgetegid, libc_sys_Xgetegid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
INTERN_FUNCTION(libc_sys_Xsetpgid)
	movq   $(0x6d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetpgid, libc_sys_Xsetpgid)

/* pid_t getppid(void) */
INTERN_FUNCTION(libc_sys_Xgetppid)
	movq   $(0x6e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetppid)
DEFINE_PUBLIC_ALIAS(sys_Xgetppid, libc_sys_Xgetppid)

/* pid_t getpgrp(void) */
INTERN_FUNCTION(libc_sys_Xgetpgrp)
	movq   $(0x6f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpgrp)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgrp, libc_sys_Xgetpgrp)

/* pid_t setsid(void) */
INTERN_FUNCTION(libc_sys_Xsetsid)
	movq   $(0x70), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetsid)
DEFINE_PUBLIC_ALIAS(sys_Xsetsid, libc_sys_Xsetsid)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid(uid_t ruid, uid_t euid) */
INTERN_FUNCTION(libc_sys_Xsetreuid)
	movq   $(0x71), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetreuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetreuid, libc_sys_Xsetreuid)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid(gid_t rgid, gid_t egid) */
INTERN_FUNCTION(libc_sys_Xsetregid)
	movq   $(0x72), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetregid)
DEFINE_PUBLIC_ALIAS(sys_Xsetregid, libc_sys_Xsetregid)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, gid_t[] list) */
INTERN_FUNCTION(libc_sys_Xgetgroups)
	movq   $(0x73), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xgetgroups, libc_sys_Xgetgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
INTERN_FUNCTION(libc_sys_Xsetgroups)
	movq   $(0x74), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xsetgroups, libc_sys_Xsetgroups)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
INTERN_FUNCTION(libc_sys_Xsetresuid)
	movq   $(0x75), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresuid, libc_sys_Xsetresuid)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
INTERN_FUNCTION(libc_sys_Xgetresuid)
	movq   $(0x76), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresuid, libc_sys_Xgetresuid)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
INTERN_FUNCTION(libc_sys_Xsetresgid)
	movq   $(0x77), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresgid, libc_sys_Xsetresgid)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
INTERN_FUNCTION(libc_sys_Xgetresgid)
	movq   $(0x78), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresgid, libc_sys_Xgetresgid)

/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetpgid)
	movq   $(0x79), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgid, libc_sys_Xgetpgid)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid(uid_t uid) */
INTERN_FUNCTION(libc_sys_Xsetfsuid)
	movq   $(0x7a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetfsuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsuid, libc_sys_Xsetfsuid)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid(gid_t gid) */
INTERN_FUNCTION(libc_sys_Xsetfsgid)
	movq   $(0x7b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetfsgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsgid, libc_sys_Xsetfsgid)

/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetsid)
	movq   $(0x7c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetsid)
DEFINE_PUBLIC_ALIAS(sys_Xgetsid, libc_sys_Xgetsid)

/* errno_t capget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcapget)
	movq   $(0x7d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcapget)
DEFINE_PUBLIC_ALIAS(sys_Xcapget, libc_sys_Xcapget)

/* errno_t capset(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcapset)
	movq   $(0x7e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcapset)
DEFINE_PUBLIC_ALIAS(sys_Xcapset, libc_sys_Xcapset)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigpending)
	movq   $(0x7f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigpending, libc_sys_Xrt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox64_struct *info, struct timespecx64 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait)
	movq   $(0x80), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigtimedwait, libc_sys_Xrt_sigtimedwait)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_sigqueueinfo)
	movq   $(0x81), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigqueueinfo, libc_sys_Xrt_sigqueueinfo)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigsuspend)
	movq   $(0x82), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigsuspend, libc_sys_Xrt_sigsuspend)

/* errno_t sigaltstack(struct __sigaltstackx64 const *ss, struct __sigaltstackx64 *oss) */
INTERN_FUNCTION(libc_sys_Xsigaltstack)
	movq   $(0x83), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsigaltstack)
DEFINE_PUBLIC_ALIAS(sys_Xsigaltstack, libc_sys_Xsigaltstack)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbufx64 const *times) */
INTERN_FUNCTION(libc_sys_Xutime)
	movq   $(0x84), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xutime)
DEFINE_PUBLIC_ALIAS(sys_Xutime, libc_sys_Xutime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknod)
	movq   $(0x85), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmknod)
DEFINE_PUBLIC_ALIAS(sys_Xmknod, libc_sys_Xmknod)

/* errno_t uselib(char const *library) */
INTERN_FUNCTION(libc_sys_Xuselib)
	movq   $(0x86), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xuselib)
DEFINE_PUBLIC_ALIAS(sys_Xuselib, libc_sys_Xuselib)

/* errno_t personality(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpersonality)
	movq   $(0x87), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpersonality)
DEFINE_PUBLIC_ALIAS(sys_Xpersonality, libc_sys_Xpersonality)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_Xustat)
	movq   $(0x88), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xustat)
DEFINE_PUBLIC_ALIAS(sys_Xustat, libc_sys_Xustat)

/* errno_t statfs(char const *file, struct __statfsx64 *buf) */
INTERN_FUNCTION(libc_sys_Xstatfs)
	movq   $(0x89), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xstatfs, libc_sys_Xstatfs)

/* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
INTERN_FUNCTION(libc_sys_Xfstatfs)
	movq   $(0x8a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xfstatfs, libc_sys_Xfstatfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsysfs)
	movq   $(0x8b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsysfs)
DEFINE_PUBLIC_ALIAS(sys_Xsysfs, libc_sys_Xsysfs)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
INTERN_FUNCTION(libc_sys_Xgetpriority)
	movq   $(0x8c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xgetpriority, libc_sys_Xgetpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_Xsetpriority)
	movq   $(0x8d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xsetpriority, libc_sys_Xsetpriority)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setparam)
	movq   $(0x8e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_setparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setparam, libc_sys_Xsched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
INTERN_FUNCTION(libc_sys_Xsched_getparam)
	movq   $(0x8f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_getparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getparam, libc_sys_Xsched_getparam)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setscheduler)
	movq   $(0x90), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setscheduler, libc_sys_Xsched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xsched_getscheduler)
	movq   $(0x91), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getscheduler, libc_sys_Xsched_getscheduler)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_max)
	movq   $(0x92), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_max, libc_sys_Xsched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_min)
	movq   $(0x93), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_min, libc_sys_Xsched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespecx64 *ts) */
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval)
	movq   $(0x94), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_Xsched_rr_get_interval, libc_sys_Xsched_rr_get_interval)

/* errno_t mlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmlock)
	movq   $(0x95), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmlock)
DEFINE_PUBLIC_ALIAS(sys_Xmlock, libc_sys_Xmlock)

/* errno_t munlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmunlock)
	movq   $(0x96), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmunlock)
DEFINE_PUBLIC_ALIAS(sys_Xmunlock, libc_sys_Xmunlock)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmlockall)
	movq   $(0x97), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmlockall, libc_sys_Xmlockall)

/* errno_t munlockall(void) */
INTERN_FUNCTION(libc_sys_Xmunlockall)
	movq   $(0x98), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmunlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmunlockall, libc_sys_Xmunlockall)

/* errno_t vhangup(void) */
INTERN_FUNCTION(libc_sys_Xvhangup)
	movq   $(0x99), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xvhangup)
DEFINE_PUBLIC_ALIAS(sys_Xvhangup, libc_sys_Xvhangup)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
INTERN_FUNCTION(libc_sys_Xmodify_ldt)
	movq   $(0x9a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmodify_ldt)
DEFINE_PUBLIC_ALIAS(sys_Xmodify_ldt, libc_sys_Xmodify_ldt)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpivot_root)
	movq   $(0x9b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpivot_root)
DEFINE_PUBLIC_ALIAS(sys_Xpivot_root, libc_sys_Xpivot_root)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_X_sysctl)
	movq   $(0x9c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_X_sysctl)
DEFINE_PUBLIC_ALIAS(sys_X_sysctl, libc_sys_X_sysctl)

/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
INTERN_FUNCTION(libc_sys_Xprctl)
	movq   $(0x9d), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xprctl)
DEFINE_PUBLIC_ALIAS(sys_Xprctl, libc_sys_Xprctl)

/* >> arch_prctl(2)
 * Arch-dependent system process control interface. (But don't go and
 * think that the  normal `prctl(2)'  doesn't feature  arch-dependent
 * commands  -- honestly, this syscall shouldn't exist if you ask me,
 * but it does on linux, and so it must also on KOS...)
 * @param: command: One of `ARCH_*' (from <asm/prctl.h>)
 * @param: addr: Either a `syscall_ulong_t' or `syscall_ulong_t *', depending on `command'
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t arch_prctl(unsigned int command, uint64_t *addr) */
INTERN_FUNCTION(libc_sys_Xarch_prctl)
	movq   $(0x9e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xarch_prctl)
DEFINE_PUBLIC_ALIAS(sys_Xarch_prctl, libc_sys_Xarch_prctl)

/* errno_t adjtimex(struct timex *ntx) */
INTERN_FUNCTION(libc_sys_Xadjtimex)
	movq   $(0x9f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xadjtimex)
DEFINE_PUBLIC_ALIAS(sys_Xadjtimex, libc_sys_Xadjtimex)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimitx64 const *rlimits) */
INTERN_FUNCTION(libc_sys_Xsetrlimit)
	movq   $(0xa0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xsetrlimit, libc_sys_Xsetrlimit)

/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_Xchroot)
	movq   $(0xa1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xchroot)
DEFINE_PUBLIC_ALIAS(sys_Xchroot, libc_sys_Xchroot)

/* errno_t sync(void) */
INTERN_FUNCTION(libc_sys_Xsync)
	movq   $(0xa2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsync)
DEFINE_PUBLIC_ALIAS(sys_Xsync, libc_sys_Xsync)

/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_Xacct)
	movq   $(0xa3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xacct)
DEFINE_PUBLIC_ALIAS(sys_Xacct, libc_sys_Xacct)

/* errno_t settimeofday(struct timevalx64 const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_Xsettimeofday)
	movq   $(0xa4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xsettimeofday, libc_sys_Xsettimeofday)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
INTERN_FUNCTION(libc_sys_Xmount)
	movq   $(0xa5), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmount)
DEFINE_PUBLIC_ALIAS(sys_Xmount, libc_sys_Xmount)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xumount2)
	movq   $(0xa6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xumount2)
DEFINE_PUBLIC_ALIAS(sys_Xumount2, libc_sys_Xumount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_Xswapon)
	movq   $(0xa7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xswapon)
DEFINE_PUBLIC_ALIAS(sys_Xswapon, libc_sys_Xswapon)

/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_Xswapoff)
	movq   $(0xa8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xswapoff)
DEFINE_PUBLIC_ALIAS(sys_Xswapoff, libc_sys_Xswapoff)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xreboot)
	movq   $(0xa9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreboot)
DEFINE_PUBLIC_ALIAS(sys_Xreboot, libc_sys_Xreboot)

/* errno_t sethostname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_Xsethostname)
	movq   $(0xaa), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsethostname)
DEFINE_PUBLIC_ALIAS(sys_Xsethostname, libc_sys_Xsethostname)

/* errno_t setdomainname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_Xsetdomainname)
	movq   $(0xab), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetdomainname)
DEFINE_PUBLIC_ALIAS(sys_Xsetdomainname, libc_sys_Xsetdomainname)

/* errno_t iopl(syscall_ulong_t level) */
INTERN_FUNCTION(libc_sys_Xiopl)
	movq   $(0xac), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xiopl)
DEFINE_PUBLIC_ALIAS(sys_Xiopl, libc_sys_Xiopl)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
INTERN_FUNCTION(libc_sys_Xioperm)
	movq   $(0xad), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xioperm)
DEFINE_PUBLIC_ALIAS(sys_Xioperm, libc_sys_Xioperm)

/* errno_t create_module(void) */
INTERN_FUNCTION(libc_sys_Xcreate_module)
	movq   $(0xae), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcreate_module)
DEFINE_PUBLIC_ALIAS(sys_Xcreate_module, libc_sys_Xcreate_module)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
INTERN_FUNCTION(libc_sys_Xinit_module)
	movq   $(0xaf), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xinit_module, libc_sys_Xinit_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xdelete_module)
	movq   $(0xb0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdelete_module)
DEFINE_PUBLIC_ALIAS(sys_Xdelete_module, libc_sys_Xdelete_module)

/* errno_t get_kernel_syms(void) */
INTERN_FUNCTION(libc_sys_Xget_kernel_syms)
	movq   $(0xb1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xget_kernel_syms)
DEFINE_PUBLIC_ALIAS(sys_Xget_kernel_syms, libc_sys_Xget_kernel_syms)

/* errno_t query_module(void) */
INTERN_FUNCTION(libc_sys_Xquery_module)
	movq   $(0xb2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xquery_module)
DEFINE_PUBLIC_ALIAS(sys_Xquery_module, libc_sys_Xquery_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xquotactl)
	movq   $(0xb3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xquotactl)
DEFINE_PUBLIC_ALIAS(sys_Xquotactl, libc_sys_Xquotactl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xnfsservctl)
	movq   $(0xb4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xnfsservctl)
DEFINE_PUBLIC_ALIAS(sys_Xnfsservctl, libc_sys_Xnfsservctl)

/* errno_t getpmsg(void) */
INTERN_FUNCTION(libc_sys_Xgetpmsg)
	movq   $(0xb5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetpmsg)
DEFINE_PUBLIC_ALIAS(sys_Xgetpmsg, libc_sys_Xgetpmsg)

/* errno_t putpmsg(void) */
INTERN_FUNCTION(libc_sys_Xputpmsg)
	movq   $(0xb6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xputpmsg)
DEFINE_PUBLIC_ALIAS(sys_Xputpmsg, libc_sys_Xputpmsg)

/* errno_t afs_syscall(void) */
INTERN_FUNCTION(libc_sys_Xafs_syscall)
	movq   $(0xb7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xafs_syscall)
DEFINE_PUBLIC_ALIAS(sys_Xafs_syscall, libc_sys_Xafs_syscall)

/* errno_t tuxcall(void) */
INTERN_FUNCTION(libc_sys_Xtuxcall)
	movq   $(0xb8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtuxcall)
DEFINE_PUBLIC_ALIAS(sys_Xtuxcall, libc_sys_Xtuxcall)

/* errno_t security(void) */
INTERN_FUNCTION(libc_sys_Xsecurity)
	movq   $(0xb9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsecurity)
DEFINE_PUBLIC_ALIAS(sys_Xsecurity, libc_sys_Xsecurity)

/* pid_t gettid(void) */
INTERN_FUNCTION(libc_sys_Xgettid)
	movq   $(0xba), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgettid)
DEFINE_PUBLIC_ALIAS(sys_Xgettid, libc_sys_Xgettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
INTERN_FUNCTION(libc_sys_Xreadahead)
	movq   $(0xbb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadahead)
DEFINE_PUBLIC_ALIAS(sys_Xreadahead, libc_sys_Xreadahead)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsetxattr)
	movq   $(0xbc), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xsetxattr, libc_sys_Xsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xlsetxattr)
	movq   $(0xbd), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlsetxattr, libc_sys_Xlsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xfsetxattr)
	movq   $(0xbe), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfsetxattr, libc_sys_Xfsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xgetxattr)
	movq   $(0xbf), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xgetxattr, libc_sys_Xgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xlgetxattr)
	movq   $(0xc0), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlgetxattr, libc_sys_Xlgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xfgetxattr)
	movq   $(0xc1), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfgetxattr, libc_sys_Xfgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xlistxattr)
	movq   $(0xc2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlistxattr, libc_sys_Xlistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xllistxattr)
	movq   $(0xc3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xllistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xllistxattr, libc_sys_Xllistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xflistxattr)
	movq   $(0xc4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xflistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xflistxattr, libc_sys_Xflistxattr)

/* errno_t removexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_Xremovexattr)
	movq   $(0xc5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xremovexattr, libc_sys_Xremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_Xlremovexattr)
	movq   $(0xc6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xlremovexattr, libc_sys_Xlremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
INTERN_FUNCTION(libc_sys_Xfremovexattr)
	movq   $(0xc7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xfremovexattr, libc_sys_Xfremovexattr)

/* errno_t tkill(pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xtkill)
	movq   $(0xc8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtkill)
DEFINE_PUBLIC_ALIAS(sys_Xtkill, libc_sys_Xtkill)

/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_Xtime)
	movq   $(0xc9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtime)
DEFINE_PUBLIC_ALIAS(sys_Xtime, libc_sys_Xtime)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_Xfutex)
	movq   $(0xca), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfutex)
DEFINE_PUBLIC_ALIAS(sys_Xfutex, libc_sys_Xfutex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_setaffinity)
	movq   $(0xcb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setaffinity, libc_sys_Xsched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_getaffinity)
	movq   $(0xcc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getaffinity, libc_sys_Xsched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xset_thread_area)
	movq   $(0xcd), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_thread_area)
DEFINE_PUBLIC_ALIAS(sys_Xset_thread_area, libc_sys_Xset_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_setup)
	movq   $(0xce), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_setup, libc_sys_Xio_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_destroy)
	movq   $(0xcf), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_destroy)
DEFINE_PUBLIC_ALIAS(sys_Xio_destroy, libc_sys_Xio_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_getevents)
	movq   $(0xd0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_getevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_getevents, libc_sys_Xio_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_submit)
	movq   $(0xd1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_submit)
DEFINE_PUBLIC_ALIAS(sys_Xio_submit, libc_sys_Xio_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_cancel)
	movq   $(0xd2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_cancel)
DEFINE_PUBLIC_ALIAS(sys_Xio_cancel, libc_sys_Xio_cancel)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xget_thread_area)
	movq   $(0xd3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xget_thread_area)
DEFINE_PUBLIC_ALIAS(sys_Xget_thread_area, libc_sys_Xget_thread_area)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xlookup_dcookie)
	movq   $(0xd4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_Xlookup_dcookie, libc_sys_Xlookup_dcookie)

/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_Xepoll_create)
	movq   $(0xd5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_create)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create, libc_sys_Xepoll_create)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_Xepoll_ctl_old)
	movq   $(0xd6), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_ctl_old)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_ctl_old, libc_sys_Xepoll_ctl_old)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait_old(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xepoll_wait_old)
	movq   $(0xd7), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_wait_old)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_wait_old, libc_sys_Xepoll_wait_old)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xremap_file_pages)
	movq   $(0xd8), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xremap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_Xremap_file_pages, libc_sys_Xremap_file_pages)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xgetdents64)
	movq   $(0xd9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetdents64)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents64, libc_sys_Xgetdents64)

/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_Xset_tid_address)
	movq   $(0xda), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_tid_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_tid_address, libc_sys_Xset_tid_address)

/* errno_t restart_syscall(void) */
INTERN_FUNCTION(libc_sys_Xrestart_syscall)
	movq   $(0xdb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrestart_syscall)
DEFINE_PUBLIC_ALIAS(sys_Xrestart_syscall, libc_sys_Xrestart_syscall)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemtimedop)
	movq   $(0xdc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsemtimedop)
DEFINE_PUBLIC_ALIAS(sys_Xsemtimedop, libc_sys_Xsemtimedop)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfadvise64)
	movq   $(0xdd), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfadvise64)
DEFINE_PUBLIC_ALIAS(sys_Xfadvise64, libc_sys_Xfadvise64)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_create)
	movq   $(0xde), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimer_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_create, libc_sys_Xtimer_create)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx64 const *value, struct itimerspecx64 *ovalue) */
INTERN_FUNCTION(libc_sys_Xtimer_settime)
	movq   $(0xdf), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimer_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_settime, libc_sys_Xtimer_settime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspecx64 *value) */
INTERN_FUNCTION(libc_sys_Xtimer_gettime)
	movq   $(0xe0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimer_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_gettime, libc_sys_Xtimer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_getoverrun)
	movq   $(0xe1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_getoverrun, libc_sys_Xtimer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_delete)
	movq   $(0xe2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimer_delete)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_delete, libc_sys_Xtimer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct timespecx64 const *tp) */
INTERN_FUNCTION(libc_sys_Xclock_settime)
	movq   $(0xe3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclock_settime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_settime, libc_sys_Xclock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespecx64 *tp) */
INTERN_FUNCTION(libc_sys_Xclock_gettime)
	movq   $(0xe4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclock_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_gettime, libc_sys_Xclock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct timespecx64 *res) */
INTERN_FUNCTION(libc_sys_Xclock_getres)
	movq   $(0xe5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclock_getres)
DEFINE_PUBLIC_ALIAS(sys_Xclock_getres, libc_sys_Xclock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx64 const *requested_time, struct timespecx64 *remaining) */
INTERN_FUNCTION(libc_sys_Xclock_nanosleep)
	movq   $(0xe6), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xclock_nanosleep, libc_sys_Xclock_nanosleep)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_Xexit_group)
	movq   $(0xe7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xexit_group)
DEFINE_PUBLIC_ALIAS(sys_Xexit_group, libc_sys_Xexit_group)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xepoll_wait)
	movq   $(0xe8), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_wait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_wait, libc_sys_Xepoll_wait)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_Xepoll_ctl)
	movq   $(0xe9), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_ctl, libc_sys_Xepoll_ctl)

/* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xtgkill)
	movq   $(0xea), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtgkill)
DEFINE_PUBLIC_ALIAS(sys_Xtgkill, libc_sys_Xtgkill)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timevalx64 const[2] times) */
INTERN_FUNCTION(libc_sys_Xutimes)
	movq   $(0xeb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xutimes)
DEFINE_PUBLIC_ALIAS(sys_Xutimes, libc_sys_Xutimes)

/* errno_t vserver(void) */
INTERN_FUNCTION(libc_sys_Xvserver)
	movq   $(0xec), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xvserver)
DEFINE_PUBLIC_ALIAS(sys_Xvserver, libc_sys_Xvserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmbind)
	movq   $(0xed), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmbind)
DEFINE_PUBLIC_ALIAS(sys_Xmbind, libc_sys_Xmbind)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xset_mempolicy)
	movq   $(0xee), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xset_mempolicy, libc_sys_Xset_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xget_mempolicy)
	movq   $(0xef), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xget_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xget_mempolicy, libc_sys_Xget_mempolicy)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmq_open)
	movq   $(0xf0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_open)
DEFINE_PUBLIC_ALIAS(sys_Xmq_open, libc_sys_Xmq_open)

/* errno_t mq_unlink(char const *name) */
INTERN_FUNCTION(libc_sys_Xmq_unlink)
	movq   $(0xf1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_unlink)
DEFINE_PUBLIC_ALIAS(sys_Xmq_unlink, libc_sys_Xmq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedsend)
	movq   $(0xf2), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedsend, libc_sys_Xmq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedreceive)
	movq   $(0xf3), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedreceive, libc_sys_Xmq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
INTERN_FUNCTION(libc_sys_Xmq_notify)
	movq   $(0xf4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_notify)
DEFINE_PUBLIC_ALIAS(sys_Xmq_notify, libc_sys_Xmq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
INTERN_FUNCTION(libc_sys_Xmq_getsetattr)
	movq   $(0xf5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_Xmq_getsetattr, libc_sys_Xmq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkexec_load)
	movq   $(0xf6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkexec_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_load, libc_sys_Xkexec_load)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox64_struct *infop, syscall_ulong_t options, struct rusagex64 *ru) */
INTERN_FUNCTION(libc_sys_Xwaitid)
	movq   $(0xf7), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwaitid)
DEFINE_PUBLIC_ALIAS(sys_Xwaitid, libc_sys_Xwaitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xadd_key)
	movq   $(0xf8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xadd_key)
DEFINE_PUBLIC_ALIAS(sys_Xadd_key, libc_sys_Xadd_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xrequest_key)
	movq   $(0xf9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrequest_key)
DEFINE_PUBLIC_ALIAS(sys_Xrequest_key, libc_sys_Xrequest_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkeyctl)
	movq   $(0xfa), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkeyctl)
DEFINE_PUBLIC_ALIAS(sys_Xkeyctl, libc_sys_Xkeyctl)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_Xioprio_set)
	movq   $(0xfb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xioprio_set)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_set, libc_sys_Xioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
INTERN_FUNCTION(libc_sys_Xioprio_get)
	movq   $(0xfc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xioprio_get)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_get, libc_sys_Xioprio_get)

/* fd_t inotify_init(void) */
INTERN_FUNCTION(libc_sys_Xinotify_init)
	movq   $(0xfd), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init, libc_sys_Xinotify_init)

/* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
INTERN_FUNCTION(libc_sys_Xinotify_add_watch)
	movq   $(0xfe), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_add_watch, libc_sys_Xinotify_add_watch)

/* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
INTERN_FUNCTION(libc_sys_Xinotify_rm_watch)
	movq   $(0xff), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_rm_watch, libc_sys_Xinotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmigrate_pages)
	movq   $(0x100), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmigrate_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmigrate_pages, libc_sys_Xmigrate_pages)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopenat)
	movq   $(0x101), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopenat)
DEFINE_PUBLIC_ALIAS(sys_Xopenat, libc_sys_Xopenat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdirat)
	movq   $(0x102), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xmkdirat, libc_sys_Xmkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknodat)
	movq   $(0x103), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xmknodat, libc_sys_Xmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchownat)
	movq   $(0x104), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchownat)
DEFINE_PUBLIC_ALIAS(sys_Xfchownat, libc_sys_Xfchownat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx64 const[2] times) */
INTERN_FUNCTION(libc_sys_Xfutimesat)
	movq   $(0x105), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfutimesat)
DEFINE_PUBLIC_ALIAS(sys_Xfutimesat, libc_sys_Xfutimesat)

/* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xnewfstatat)
	movq   $(0x106), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xnewfstatat)
DEFINE_PUBLIC_ALIAS(sys_Xnewfstatat, libc_sys_Xnewfstatat)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xunlinkat)
	movq   $(0x107), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xunlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xunlinkat, libc_sys_Xunlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrenameat)
	movq   $(0x108), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrenameat)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat, libc_sys_Xrenameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xlinkat)
	movq   $(0x109), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xlinkat, libc_sys_Xlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlinkat)
	movq   $(0x10a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xsymlinkat, libc_sys_Xsymlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlinkat)
	movq   $(0x10b), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xreadlinkat, libc_sys_Xreadlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchmodat)
	movq   $(0x10c), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchmodat)
DEFINE_PUBLIC_ALIAS(sys_Xfchmodat, libc_sys_Xfchmodat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_Xfaccessat)
	movq   $(0x10d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfaccessat)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat, libc_sys_Xfaccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx64 const *timeout, struct __sigset_with_sizex64 const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_Xpselect6)
	movq   $(0x10e), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpselect6)
DEFINE_PUBLIC_ALIAS(sys_Xpselect6, libc_sys_Xpselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xppoll)
	movq   $(0x10f), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xppoll)
DEFINE_PUBLIC_ALIAS(sys_Xppoll, libc_sys_Xppoll)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
INTERN_FUNCTION(libc_sys_Xunshare)
	movq   $(0x110), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xunshare)
DEFINE_PUBLIC_ALIAS(sys_Xunshare, libc_sys_Xunshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xset_robust_list)
	movq   $(0x111), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xset_robust_list, libc_sys_Xset_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xget_robust_list)
	movq   $(0x112), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xget_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xget_robust_list, libc_sys_Xget_robust_list)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsplice)
	movq   $(0x113), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsplice)
DEFINE_PUBLIC_ALIAS(sys_Xsplice, libc_sys_Xsplice)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtee)
	movq   $(0x114), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtee)
DEFINE_PUBLIC_ALIAS(sys_Xtee, libc_sys_Xtee)

/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsync_file_range)
	movq   $(0x115), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsync_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xsync_file_range, libc_sys_Xsync_file_range)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovecx64 const *iov, size_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xvmsplice)
	movq   $(0x116), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xvmsplice)
DEFINE_PUBLIC_ALIAS(sys_Xvmsplice, libc_sys_Xvmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmove_pages)
	movq   $(0x117), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmove_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmove_pages, libc_sys_Xmove_pages)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx64 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xutimensat)
	movq   $(0x118), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xutimensat)
DEFINE_PUBLIC_ALIAS(sys_Xutimensat, libc_sys_Xutimensat)

/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xepoll_pwait)
	movq   $(0x119), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_pwait, libc_sys_Xepoll_pwait)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
INTERN_FUNCTION(libc_sys_Xsignalfd)
	movq   $(0x11a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsignalfd)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd, libc_sys_Xsignalfd)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtimerfd_create)
	movq   $(0x11b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimerfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_create, libc_sys_Xtimerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_Xeventfd)
	movq   $(0x11c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xeventfd)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd, libc_sys_Xeventfd)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xfallocate)
	movq   $(0x11d), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfallocate)
DEFINE_PUBLIC_ALIAS(sys_Xfallocate, libc_sys_Xfallocate)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx64 const *utmr, struct itimerspecx64 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_settime)
	movq   $(0x11e), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_settime, libc_sys_Xtimerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx64 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime)
	movq   $(0x11f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xtimerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_gettime, libc_sys_Xtimerfd_gettime)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
INTERN_FUNCTION(libc_sys_Xaccept4)
	movq   $(0x120), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xaccept4)
DEFINE_PUBLIC_ALIAS(sys_Xaccept4, libc_sys_Xaccept4)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsignalfd4)
	movq   $(0x121), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsignalfd4)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd4, libc_sys_Xsignalfd4)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xeventfd2)
	movq   $(0x122), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xeventfd2)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd2, libc_sys_Xeventfd2)

/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xepoll_create1)
	movq   $(0x123), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xepoll_create1)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create1, libc_sys_Xepoll_create1)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xdup3)
	movq   $(0x124), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdup3)
DEFINE_PUBLIC_ALIAS(sys_Xdup3, libc_sys_Xdup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xpipe2)
	movq   $(0x125), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpipe2)
DEFINE_PUBLIC_ALIAS(sys_Xpipe2, libc_sys_Xpipe2)

/* fd_t inotify_init1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xinotify_init1)
	movq   $(0x126), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinotify_init1)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init1, libc_sys_Xinotify_init1)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpreadv)
	movq   $(0x127), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpreadv)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv, libc_sys_Xpreadv)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwritev)
	movq   $(0x128), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpwritev)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev, libc_sys_Xpwritev)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_tgsigqueueinfo)
	movq   $(0x129), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_tgsigqueueinfo, libc_sys_Xrt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xperf_event_open)
	movq   $(0x12a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xperf_event_open)
DEFINE_PUBLIC_ALIAS(sys_Xperf_event_open, libc_sys_Xperf_event_open)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx64 const *tmo) */
INTERN_FUNCTION(libc_sys_Xrecvmmsg)
	movq   $(0x12b), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrecvmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmmsg, libc_sys_Xrecvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfanotify_init)
	movq   $(0x12c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfanotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_init, libc_sys_Xfanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfanotify_mark)
	movq   $(0x12d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_mark, libc_sys_Xfanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimitx64 const *new_limit, struct rlimitx64 *old_limit) */
INTERN_FUNCTION(libc_sys_Xprlimit64)
	movq   $(0x12e), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xprlimit64)
DEFINE_PUBLIC_ALIAS(sys_Xprlimit64, libc_sys_Xprlimit64)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xname_to_handle_at)
	movq   $(0x12f), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xname_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xname_to_handle_at, libc_sys_Xname_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xopen_by_handle_at)
	movq   $(0x130), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopen_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xopen_by_handle_at, libc_sys_Xopen_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xclock_adjtime)
	movq   $(0x131), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_adjtime, libc_sys_Xclock_adjtime)

/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xsyncfs)
	movq   $(0x132), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsyncfs)
DEFINE_PUBLIC_ALIAS(sys_Xsyncfs, libc_sys_Xsyncfs)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xsendmmsg)
	movq   $(0x133), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsendmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmmsg, libc_sys_Xsendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_Xsetns)
	movq   $(0x134), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsetns)
DEFINE_PUBLIC_ALIAS(sys_Xsetns, libc_sys_Xsetns)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_Xgetcpu)
	movq   $(0x135), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetcpu)
DEFINE_PUBLIC_ALIAS(sys_Xgetcpu, libc_sys_Xgetcpu)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_readv)
	movq   $(0x136), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xprocess_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_readv, libc_sys_Xprocess_vm_readv)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_writev)
	movq   $(0x137), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xprocess_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_writev, libc_sys_Xprocess_vm_writev)

/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_Xkcmp)
	movq   $(0x138), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkcmp)
DEFINE_PUBLIC_ALIAS(sys_Xkcmp, libc_sys_Xkcmp)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xfinit_module)
	movq   $(0x139), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xfinit_module, libc_sys_Xfinit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsched_setattr)
	movq   $(0x13a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_setattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setattr, libc_sys_Xsched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsched_getattr)
	movq   $(0x13b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xsched_getattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getattr, libc_sys_Xsched_getattr)

/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xrenameat2)
	movq   $(0x13c), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrenameat2)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat2, libc_sys_Xrenameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xseccomp)
	movq   $(0x13d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xseccomp)
DEFINE_PUBLIC_ALIAS(sys_Xseccomp, libc_sys_Xseccomp)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xgetrandom)
	movq   $(0x13e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetrandom)
DEFINE_PUBLIC_ALIAS(sys_Xgetrandom, libc_sys_Xgetrandom)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmemfd_create)
	movq   $(0x13f), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmemfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xmemfd_create, libc_sys_Xmemfd_create)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkexec_file_load)
	movq   $(0x140), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_file_load, libc_sys_Xkexec_file_load)

/* errno_t bpf(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xbpf)
	movq   $(0x141), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xbpf)
DEFINE_PUBLIC_ALIAS(sys_Xbpf, libc_sys_Xbpf)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xexecveat)
	movq   $(0x142), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xexecveat)
DEFINE_PUBLIC_ALIAS(sys_Xexecveat, libc_sys_Xexecveat)

/* fd_t userfaultfd(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xuserfaultfd)
	movq   $(0x143), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xuserfaultfd)
DEFINE_PUBLIC_ALIAS(sys_Xuserfaultfd, libc_sys_Xuserfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmembarrier)
	movq   $(0x144), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmembarrier)
DEFINE_PUBLIC_ALIAS(sys_Xmembarrier, libc_sys_Xmembarrier)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmlock2)
	movq   $(0x145), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmlock2)
DEFINE_PUBLIC_ALIAS(sys_Xmlock2, libc_sys_Xmlock2)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcopy_file_range)
	movq   $(0x146), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcopy_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xcopy_file_range, libc_sys_Xcopy_file_range)

/* errno_t preadv2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpreadv2)
	movq   $(0x147), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpreadv2)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv2, libc_sys_Xpreadv2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpwritev2)
	movq   $(0x148), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpwritev2)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev2, libc_sys_Xpwritev2)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
INTERN_FUNCTION(libc_sys_Xpkey_mprotect)
	movq   $(0x149), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_mprotect, libc_sys_Xpkey_mprotect)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
INTERN_FUNCTION(libc_sys_Xpkey_alloc)
	movq   $(0x14a), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_alloc, libc_sys_Xpkey_alloc)

/* errno_t pkey_free(syscall_ulong_t key) */
INTERN_FUNCTION(libc_sys_Xpkey_free)
	movq   $(0x14b), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpkey_free)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_free, libc_sys_Xpkey_free)

/* errno_t statx(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xstatx)
	movq   $(0x14c), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xstatx)
DEFINE_PUBLIC_ALIAS(sys_Xstatx, libc_sys_Xstatx)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_pgetevents)
	movq   $(0x14d), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_pgetevents, libc_sys_Xio_pgetevents)

/* errno_t rseq(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xrseq)
	movq   $(0x14e), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrseq)
DEFINE_PUBLIC_ALIAS(sys_Xrseq, libc_sys_Xrseq)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_PIDFD'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:                 [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox64_struct const *uinfo, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_send_signal)
	movq   $(0x1a8), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_send_signal, libc_sys_Xpidfd_send_signal)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_setup)
	movq   $(0x1a9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_setup, libc_sys_Xio_uring_setup)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_enter)
	movq   $(0x1aa), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_enter, libc_sys_Xio_uring_enter)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_register)
	movq   $(0x1ab), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xio_uring_register)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_register, libc_sys_Xio_uring_register)

/* errno_t open_tree(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xopen_tree)
	movq   $(0x1ac), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopen_tree)
DEFINE_PUBLIC_ALIAS(sys_Xopen_tree, libc_sys_Xopen_tree)

/* errno_t move_mount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmove_mount)
	movq   $(0x1ad), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmove_mount)
DEFINE_PUBLIC_ALIAS(sys_Xmove_mount, libc_sys_Xmove_mount)

/* errno_t fsopen(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsopen)
	movq   $(0x1ae), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsopen)
DEFINE_PUBLIC_ALIAS(sys_Xfsopen, libc_sys_Xfsopen)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsconfig)
	movq   $(0x1af), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsconfig)
DEFINE_PUBLIC_ALIAS(sys_Xfsconfig, libc_sys_Xfsconfig)

/* errno_t fsmount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsmount)
	movq   $(0x1b0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsmount)
DEFINE_PUBLIC_ALIAS(sys_Xfsmount, libc_sys_Xfsmount)

/* errno_t fspick(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfspick)
	movq   $(0x1b1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfspick)
DEFINE_PUBLIC_ALIAS(sys_Xfspick, libc_sys_Xfspick)

/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_open)
	movq   $(0x1b2), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpidfd_open)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_open, libc_sys_Xpidfd_open)

/* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
INTERN_FUNCTION(libc_sys_Xclone3)
	movq   $(0x1b3), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclone3)
DEFINE_PUBLIC_ALIAS(sys_Xclone3, libc_sys_Xclone3)

/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
/* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
INTERN_FUNCTION(libc_sys_Xclose_range)
	movq   $(0x1b4), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xclose_range)
DEFINE_PUBLIC_ALIAS(sys_Xclose_range, libc_sys_Xclose_range)

/* errno_t openat2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xopenat2)
	movq   $(0x1b5), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopenat2)
DEFINE_PUBLIC_ALIAS(sys_Xopenat2, libc_sys_Xopenat2)

/* Duplicate the  handle  of  a  foreign  process into  a  handle  for  the  caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_PIDFD'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_getfd)
	movq   $(0x1b6), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_getfd, libc_sys_Xpidfd_getfd)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfaccessat2)
	movq   $(0x1b7), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfaccessat2)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat2, libc_sys_Xfaccessat2)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwritevf)
	movq   $(0xfffffffffffffed8), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xpwritevf, libc_sys_Xpwritevf)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpreadvf)
	movq   $(0xfffffffffffffed9), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xpreadvf, libc_sys_Xpreadvf)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfreadlinkat)
	movq   $(0xfffffffffffffef5), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfreadlinkat, libc_sys_Xfreadlinkat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfsymlinkat)
	movq   $(0xfffffffffffffef6), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfsymlinkat, libc_sys_Xfsymlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xkfstatat)
	movq   $(0xfffffffffffffefa), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkfstatat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstatat, libc_sys_Xkfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmknodat)
	movq   $(0xfffffffffffffefd), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xfmknodat, libc_sys_Xfmknodat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmkdirat)
	movq   $(0xfffffffffffffefe), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfmkdirat, libc_sys_Xfmkdirat)

/* int inotify_add_watch_at(fd_t notify_fd, fd_t dfd, char const *pathname, atflag_t atflags, uint32_t mask) */
INTERN_FUNCTION(libc_sys_Xinotify_add_watch_at)
	movq   $(0xffffffffffffff02), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xinotify_add_watch_at)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_add_watch_at, libc_sys_Xinotify_add_watch_at)

/* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xksysctl)
	movq   $(0xffffffffffffff64), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xksysctl)
DEFINE_PUBLIC_ALIAS(sys_Xksysctl, libc_sys_Xksysctl)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN |
 *                MAP_GROWSUP  |  MAP_LOCKED  |  MAP_NORESERVE  |
 *                MAP_POPULATE  |  MAP_NONBLOCK   |  MAP_SYNC   |
 *                MAP_FIXED_NOREPLACE | MAP_NOASLR'
 * @param: fd:    A handle for the library file being mapped (must be mmap(2)-able)
 * @param: hdrv:  Pointer  to  a vector  of `Elf32_Phdr'  or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr const *hdrv, size_t hdrc) */
INTERN_FUNCTION(libc_sys_Xmaplibrary)
	movq   $(0xffffffffffffff7a), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmaplibrary)
DEFINE_PUBLIC_ALIAS(sys_Xmaplibrary, libc_sys_Xmaplibrary)

/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_Xfsmode)
	movq   $(0xffffffffffffffa1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfsmode)
DEFINE_PUBLIC_ALIAS(sys_Xfsmode, libc_sys_Xfsmode)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchdirat)
	movq   $(0xffffffffffffffb0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfchdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfchdirat, libc_sys_Xfchdirat)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
INTERN_FUNCTION(libc_sys_Xkreaddirf)
	movq   $(0xffffffffffffffb1), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkreaddirf)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddirf, libc_sys_Xkreaddirf)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_Xkreaddir)
	movq   $(0xffffffffffffffb2), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkreaddir)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddir, libc_sys_Xkreaddir)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   - Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   - Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                           EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                           &except_handler4, NULL)'
 * @param: mode:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: handler:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: handler_sp: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given `mode' is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
INTERN_FUNCTION(libc_sys_Xset_exception_handler)
	movq   $(0xffffffffffffffd9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xset_exception_handler, libc_sys_Xset_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: pmode:       When non-`NULL', store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: phandler:    When   non-`NULL',   store  the   address   of  the   user-space   exception  handler.
 *                      Note that when no handler has been set (`!(*pmode & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: phandler_sp: When non-`NULL', store the starting address of the user-space exception handler stack.
 *                      Note that  when no  stack has  been set  (`!(*pmode & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-`NULL' and faulty */
/* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
INTERN_FUNCTION(libc_sys_Xget_exception_handler)
	movq   $(0xffffffffffffffda), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xget_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xget_exception_handler, libc_sys_Xget_exception_handler)

/* >> rpc_serve_sysret(2)
 * Very similar to `rpc_serve(2)', but with the addition that this one
 * will only serve RPCs that can be handled in `RPC_REASONCTX_SYSRET',
 * aka. `RPC_REASONCTX_ASYNC' contexts. Additionally, this system call
 * ignores the state of the  internal `TASK_FRPC' flag, and should  be
 * invoked  when  the calling  thread  makes use  of  the userprocmask
 * mechanism, and the  signal mask became  less restrictive while  the
 * `USERPROCMASK_FLAG_HASPENDING' flag was set.
 * 
 * When userprocmask is disabled, this system call is pretty much just
 * a no-op (semnatically speaking, it does nothing). But when enabled,
 * it is really only usable  in conjuction with the userprocmask.  The
 * exact usage can be seen in `chkuserprocmask(3)'.
 * 
 * @return: 0 : Always, unconditionally returned. */
/* errno_t rpc_serve_sysret(void) */
INTERN_FUNCTION(libc_sys_Xrpc_serve_sysret)
	movq   $(0xffffffffffffffdb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrpc_serve_sysret)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_serve_sysret, libc_sys_Xrpc_serve_sysret)

/* Register the address of  the calling thread's userprocmask  controller.
 * This also  initializes `*ctl->pm_sigmask'  and `ctl->pm_pending',  such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level  signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally,  the address  of `&ctl->pm_mytid'  is stored  as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using  atomic-or for the later) from  this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional,   arch-specific   fields    to   all    zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the  `pm_sigmask'
 *       of the previously set  controller into its internal  signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though  that  `pm_sigmask'  is ignored  for  `SIGKILL'  and  `SIGSTOP'
 * Note also  that  this  function replaces  `set_tid_address(2)',  such  that
 * it negates a  prior call  to said  function, while  a future  call to  said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
INTERN_FUNCTION(libc_sys_Xset_userprocmask_address)
	movq   $(0xffffffffffffffdc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xset_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_userprocmask_address, libc_sys_Xset_userprocmask_address)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
INTERN_FUNCTION(libc_sys_Xrtm_test)
	movq   $(0xffffffffffffffdd), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrtm_test)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_test, libc_sys_Xrtm_test)

/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
INTERN_FUNCTION(libc_sys_Xrtm_abort)
	movq   $(0xffffffffffffffde), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrtm_abort)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_abort, libc_sys_Xrtm_abort)

/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
INTERN_FUNCTION(libc_sys_Xrtm_end)
	movq   $(0xffffffffffffffdf), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrtm_end)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_end, libc_sys_Xrtm_end)

/* Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM  operation is in progress,  only a very small  hand
 * full  of system calls are allowed to  be used. Attempting to use arbitrary
 * system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
 * attempting to access too much system memory in general will result in this
 * function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
 * The following is  a list  of system calls  which are  whitelisted for  use
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
INTERN_FUNCTION(libc_sys_Xrtm_begin)
	movq   $(0xffffffffffffffe0), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrtm_begin)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_begin, libc_sys_Xrtm_begin)

/* Construct   a   user-vio-fd  object   supporting  mmap(2),   with  actual
 * memory  accesses  being dispatched  by  adding them  as  pending requests
 * to an internal  queue that  should be read(2)  from by  a worker  thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This  size may be  altered at a  later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xuserviofd)
	movq   $(0xffffffffffffffe1), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xuserviofd)
DEFINE_PUBLIC_ALIAS(sys_Xuserviofd, libc_sys_Xuserviofd)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The  state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `reason' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When   `curr_state'   is   also   `NULL',   then   the   current   CPU   state   is   used   instead.
 * @param: traceback_vector: (potentially  incomplete)   vector  of   additional  program   pointers  that   were
 *                           traversed   when   the  stack   was   walked  from   `orig_state'   to  `curr_state'
 *                           Note that earlier  entries within this  vector are further  up the call-stack,  with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it  can  be  assumed  that  the  traceback is  complete  and  contains  all  traversed  instruction locations.
 *                           In   this   case,  a   traceback  displayed   to   a  human   should  not   include   the  text   location  at
 *                           `traceback_vector[traceback_length-1]',    since    that    location    would    also    be    printed    when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: reason:           The reason that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           For certain `unwind_error' values, this can also  point to other things, but is  always
 *                           allowed to be `NULL' to indicate default/stub values.
 * @param: unwind_error:     The  unwind  error that  caused the  coredump,  or `UNWIND_SUCCESS'  if unwinding
 *                           was  never  actually  performed,  and   `reason'  is  actually  a   `siginfo_t *'
 *                           Ignored when `reason == NULL', in which case `UNWIND_SUCCESS' is assumed instead. */
/* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void const) const *traceback_vector, size_t traceback_length, union coredump_info64 const *reason, syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_Xcoredump)
	movq   $(0xffffffffffffffe3), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xcoredump)
DEFINE_PUBLIC_ALIAS(sys_Xcoredump, libc_sys_Xcoredump)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_Xmktty)
	movq   $(0xffffffffffffffe5), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xmktty)
DEFINE_PUBLIC_ALIAS(sys_Xmktty, libc_sys_Xmktty)

/* >> lfutexexpr(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: futexaddr: The futex on which to wait
 * @param: base:      Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:      Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:   Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 *                    When `LFUTEX_FDBIT'  is  set,  this argument  must  be  `NULL'.
 * @param: flags:     Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*' or `LFUTEX_FDBIT'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 *              When `LFUTEX_FDBIT' is set, the return value is an `fd_t' for a futex fd that
 *              can be used to poll for the specified `exprv'. Note that in this case `exprv'
 *              is limited to `LFUTEXFD_DEFAULT_MAXEXPR' (`/proc/kos/futexfd-maxexpr')
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(uint64_t *futexaddr, void *base, struct lfutexexprx64 const *expr, struct timespecx64 const *timeout, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xlfutexexpr)
	movq   $(0xffffffffffffffe6), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_Xlfutexexpr, libc_sys_Xlfutexexpr)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct timespecx64 const *timeout, uint64_t val2) */
INTERN_FUNCTION(libc_sys_Xlfutex)
	movq   $(0xffffffffffffffe8), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xlfutex)
DEFINE_PUBLIC_ALIAS(sys_Xlfutex, libc_sys_Xlfutex)

/* >> rpc_serve(2)
 * Check for pending signals and RPCs. This is a wrapper around the
 * kernel `task_serve()' function, which is always invoked before a
 * thread begins waiting for a blocking operation. All system calls
 * marked as cancellation  points probably  call `task_serve()'  at
 * some point.
 * Note that unlike (say) `pause(2)', this function doesn't  block,
 * and may be used to implement `pthread_testcancel(3)' (should KOS
 * RPCs be used to facility pthread cancellation points, as done by
 * KOS's builtin libc)
 * @return: 0:      Nothing was handled.
 * @return: -EINTR: RPCs (or posix signals) were handled. */
/* errno_t rpc_serve(void) */
INTERN_FUNCTION(libc_sys_Xrpc_serve)
	movq   $(0xffffffffffffffe9), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrpc_serve)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_serve, libc_sys_Xrpc_serve)

/* Trigger a debugger trap `trapno', optionally extended with  `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to  the
 * given  `state', though given the purpose of this system call being
 * to inform a connected debugger  of some breakable event,  allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
INTERN_FUNCTION(libc_sys_Xdebugtrap)
	movq   $(0xffffffffffffffea), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdebugtrap)
DEFINE_PUBLIC_ALIAS(sys_Xdebugtrap, libc_sys_Xdebugtrap)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritevf)
	movq   $(0xffffffffffffffec), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xwritevf, libc_sys_Xwritevf)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadvf)
	movq   $(0xffffffffffffffed), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xreadvf, libc_sys_Xreadvf)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwrite64f)
	movq   $(0xffffffffffffffee), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpwrite64f)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64f, libc_sys_Xpwrite64f)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpread64f)
	movq   $(0xffffffffffffffef), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xpread64f)
DEFINE_PUBLIC_ALIAS(sys_Xpread64f, libc_sys_Xpread64f)

/* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
INTERN_FUNCTION(libc_sys_Xioctlf)
	movq   $(0xfffffffffffffff0), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xioctlf)
DEFINE_PUBLIC_ALIAS(sys_Xioctlf, libc_sys_Xioctlf)

/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_Xopenpty)
	movq   $(0xfffffffffffffff3), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xopenpty)
DEFINE_PUBLIC_ALIAS(sys_Xopenpty, libc_sys_Xopenpty)

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 * 
 * NOTE: Only a cancellation point when `RPC_JOIN_WAITFOR' is used!
 * 
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 * 
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
/* errno_t rpc_schedule(pid_t target_tid, syscall_ulong_t mode, void const *program, __HYBRID_PTR64(void const) const *params, size_t max_param_count) */
INTERN_FUNCTION(libc_sys_Xrpc_schedule)
	movq   $(0xfffffffffffffff4), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xrpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_schedule, libc_sys_Xrpc_schedule)

/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpathat)
	movq   $(0xfffffffffffffff5), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfrealpathat)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpathat, libc_sys_Xfrealpathat)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpath4)
	movq   $(0xfffffffffffffff6), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xfrealpath4)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpath4, libc_sys_Xfrealpath4)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
INTERN_FUNCTION(libc_sys_Xgetdrives)
	movq   $(0xfffffffffffffff7), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xgetdrives)
DEFINE_PUBLIC_ALIAS(sys_Xgetdrives, libc_sys_Xgetdrives)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the  thread from turning into  a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling  thread from  the set of  running children  within
 *     its own process.  Note however  that when this  is done  by the  main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the  calling   process   the   same  way   a   double-fork   would:
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
 *     Detach all child processes/threads  of the calling process,  essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * The given `pid' must be:
 *   - A thread without the caller's process
 *   - A child process of the caller's process
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had  already
 *       be called.
 * @return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
 *                           a thread in your process, or a child process of your process. */
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xdetach)
	movq   $(0xfffffffffffffff8), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xdetach)
DEFINE_PUBLIC_ALIAS(sys_Xdetach, libc_sys_Xdetach)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadf)
	movq   $(0xfffffffffffffff9), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xreadf)
DEFINE_PUBLIC_ALIAS(sys_Xreadf, libc_sys_Xreadf)

/* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xklstat)
	movq   $(0xfffffffffffffffa), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xklstat)
DEFINE_PUBLIC_ALIAS(sys_Xklstat, libc_sys_Xklstat)

/* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkfstat)
	movq   $(0xfffffffffffffffb), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkfstat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstat, libc_sys_Xkfstat)

/* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkstat)
	movq   $(0xfffffffffffffffc), %rax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xkstat)
DEFINE_PUBLIC_ALIAS(sys_Xkstat, libc_sys_Xkstat)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritef)
	movq   $(0xffffffffffffffff), %rax
	movq   %rcx, %r10
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */
	ret
END(libc_sys_Xwritef)
DEFINE_PUBLIC_ALIAS(sys_Xwritef, libc_sys_Xwritef)


.cfi_endproc

/* Include the system call amendment in order to alias
 * some exception-enabled functions onto system calls. */
#include "../../syscalls-ammend.S.inl"

#endif /* GUARD_LIBC_LIBC_ARCH_I386_SYSCALLS64_S */
