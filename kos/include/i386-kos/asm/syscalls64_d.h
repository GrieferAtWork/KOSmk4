/* HASH CRC-32:0x66a79146 */
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

/************************************************************************/
/* SYSCALL IDS                                                          */
/************************************************************************/
#ifndef __NR64_read
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define __NR64_read                     0x0                            /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define __NR64_write                    0x1                            /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
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
#define __NR64_open                     0x2                            /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `fd' */
#define __NR64_close                    0x3                            /* errno_t close(fd_t fd) */
#define __NR64_stat                     0x4                            /* errno_t stat(char const *filename, struct linux_statx64 *statbuf) */
#define __NR64_fstat                    0x5                            /* errno_t fstat(fd_t fd, struct linux_statx64 *statbuf) */
#define __NR64_lstat                    0x6                            /* errno_t lstat(char const *filename, struct linux_statx64 *statbuf) */
#define __NR64_poll                     0x7                            /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define __NR64_lseek                    0x8                            /* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
#define __NR64_mmap                     0x9                            /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
#define __NR64_mprotect                 0xa                            /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
#define __NR64_munmap                   0xb                            /* errno_t munmap(void *addr, size_t len) */
#define __NR64_brk                      0xc                            /* errno_t brk(void *addr) */
#define __NR64_rt_sigaction             0xd                            /* errno_t rt_sigaction(signo_t signo, struct __kernel_sigactionx64 const *act, struct __kernel_sigactionx64 *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR64_rt_sigprocmask           0xe                            /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR64_rt_sigreturn             0xf                            /* void rt_sigreturn(void) */
#define __NR64_ioctl                    0x10                           /* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
#define __NR64_pread64                  0x11                           /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR64_pwrite64                 0x12                           /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define __NR64_readv                    0x13                           /* ssize_t readv(fd_t fd, struct iovecx64 const *iovec, size_t count) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define __NR64_writev                   0x14                           /* ssize_t writev(fd_t fd, struct iovecx64 const *iovec, size_t count) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR64_access                   0x15                           /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR64_pipe                     0x16                           /* errno_t pipe(fd_t[2] pipedes) */
#define __NR64_select                   0x17                           /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx64 *timeout) */
#define __NR64_sched_yield              0x18                           /* errno_t sched_yield(void) */
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
#define __NR64_mremap                   0x19                           /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR64_msync                    0x1a                           /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define __NR64_mincore                  0x1b                           /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR64_madvise                  0x1c                           /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define __NR64_shmget                   0x1d                           /* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
#define __NR64_shmat                    0x1e                           /* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
#define __NR64_shmctl                   0x1f                           /* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
#define __NR64_dup                      0x20                           /* fd_t dup(fd_t fd) */
#define __NR64_dup2                     0x21                           /* fd_t dup2(fd_t oldfd, fd_t newfd) */
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
#define __NR64_pause                    0x22                           /* errno_t pause(void) */
#define __NR64_nanosleep                0x23                           /* errno_t nanosleep(struct timespecx64 const *req, struct timespecx64 *rem) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR64_getitimer                0x24                           /* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
#define __NR64_alarm                    0x25                           /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR64_setitimer                0x26                           /* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
#define __NR64_getpid                   0x27                           /* pid_t getpid(void) */
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
#define __NR64_sendfile                 0x28                           /* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
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
#define __NR64_socket                   0x29                           /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
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
#define __NR64_connect                  0x2a                           /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
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
#define __NR64_accept                   0x2b                           /* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define __NR64_sendto                   0x2c                           /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
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
#define __NR64_recvfrom                 0x2d                           /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
#define __NR64_sendmsg                  0x2e                           /* ssize_t sendmsg(fd_t sockfd, struct msghdrx64 const *message, syscall_ulong_t msg_flags) */
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
#define __NR64_recvmsg                  0x2f                           /* ssize_t recvmsg(fd_t sockfd, struct msghdrx64 *message, syscall_ulong_t msg_flags) */
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR64_shutdown                 0x30                           /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
#define __NR64_bind                     0x31                           /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
#define __NR64_listen                   0x32                           /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
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
#define __NR64_getsockname              0x33                           /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR64_getpeername              0x34                           /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define __NR64_socketpair               0x35                           /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
#define __NR64_setsockopt               0x36                           /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
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
#define __NR64_getsockopt               0x37                           /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
#define __NR64_clone                    0x38                           /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
#define __NR64_fork                     0x39                           /* pid_t fork(void) */
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
#define __NR64_vfork                    0x3a                           /* pid_t vfork(void) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
#define __NR64_execve                   0x3b                           /* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR64_exit                     0x3c                           /* void exit(syscall_ulong_t exit_code) */
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR64_wait4                    0x3d                           /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex64 *usage) */
#define __NR64_kill                     0x3e                           /* errno_t kill(pid_t pid, signo_t signo) */
#define __NR64_uname                    0x3f                           /* errno_t uname(struct utsname *name) */
#define __NR64_semget                   0x40                           /* errno_t semget(int TODO_PROTOTYPE) */
#define __NR64_semop                    0x41                           /* errno_t semop(int TODO_PROTOTYPE) */
#define __NR64_semctl                   0x42                           /* errno_t semctl(int TODO_PROTOTYPE) */
#define __NR64_shmdt                    0x43                           /* errno_t shmdt(void const *shmaddr) */
#define __NR64_msgget                   0x44                           /* errno_t msgget(int TODO_PROTOTYPE) */
#define __NR64_msgsnd                   0x45                           /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define __NR64_msgrcv                   0x46                           /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define __NR64_msgctl                   0x47                           /* errno_t msgctl(int TODO_PROTOTYPE) */
#define __NR64_fcntl                    0x48                           /* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
#define __NR64_flock                    0x49                           /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
#define __NR64_fsync                    0x4a                           /* errno_t fsync(fd_t fd) */
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
#define __NR64_fdatasync                0x4b                           /* errno_t fdatasync(fd_t fd) */
#define __NR64_truncate                 0x4c                           /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR64_ftruncate                0x4d                           /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR64_getdents                 0x4e                           /* ssize_t getdents(fd_t fd, struct linux_direntx64 *buf, size_t buflen) */
#define __NR64_getcwd                   0x4f                           /* ssize_t getcwd(char *buf, size_t size) */
#define __NR64_chdir                    0x50                           /* errno_t chdir(char const *path) */
#define __NR64_fchdir                   0x51                           /* errno_t fchdir(fd_t fd) */
#define __NR64_rename                   0x52                           /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR64_mkdir                    0x53                           /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR64_rmdir                    0x54                           /* errno_t rmdir(char const *path) */
#define __NR64_creat                    0x55                           /* fd_t creat(char const *filename, mode_t mode) */
#define __NR64_link                     0x56                           /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR64_unlink                   0x57                           /* errno_t unlink(char const *filename) */
#define __NR64_symlink                  0x58                           /* errno_t symlink(char const *link_text, char const *target_path) */
#define __NR64_readlink                 0x59                           /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define __NR64_chmod                    0x5a                           /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR64_fchmod                   0x5b                           /* errno_t fchmod(fd_t fd, mode_t mode) */
#define __NR64_chown                    0x5c                           /* errno_t chown(char const *filename, uid_t owner, gid_t group) */
#define __NR64_fchown                   0x5d                           /* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
#define __NR64_lchown                   0x5e                           /* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
#define __NR64_umask                    0x5f                           /* mode_t umask(mode_t mode) */
#define __NR64_gettimeofday             0x60                           /* errno_t gettimeofday(struct timevalx64 *tv, struct timezone *tz) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR64_getrlimit                0x61                           /* errno_t getrlimit(syscall_ulong_t resource, struct rlimitx64 *rlimits) */
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
#define __NR64_getrusage                0x62                           /* errno_t getrusage(syscall_slong_t who, struct rusagex64 *tv) */
#define __NR64_sysinfo                  0x63                           /* errno_t sysinfo(struct __sysinfox64 *info) */
#define __NR64_times                    0x64                           /* clock_t times(struct tmsx64 *buf) */
#define __NR64_ptrace                   0x65                           /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
#define __NR64_getuid                   0x66                           /* uid_t getuid(void) */
#define __NR64_syslog                   0x67                           /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
#define __NR64_getgid                   0x68                           /* gid_t getgid(void) */
/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR64_setuid                   0x69                           /* errno_t setuid(uid_t uid) */
/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR64_setgid                   0x6a                           /* errno_t setgid(gid_t gid) */
/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define __NR64_geteuid                  0x6b                           /* uid_t geteuid(void) */
/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define __NR64_getegid                  0x6c                           /* gid_t getegid(void) */
#define __NR64_setpgid                  0x6d                           /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR64_getppid                  0x6e                           /* pid_t getppid(void) */
#define __NR64_getpgrp                  0x6f                           /* pid_t getpgrp(void) */
#define __NR64_setsid                   0x70                           /* pid_t setsid(void) */
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR64_setreuid                 0x71                           /* errno_t setreuid(uid_t ruid, uid_t euid) */
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR64_setregid                 0x72                           /* errno_t setregid(gid_t rgid, gid_t egid) */
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
#define __NR64_getgroups                0x73                           /* ssize_t getgroups(size_t count, gid_t[] list) */
#define __NR64_setgroups                0x74                           /* errno_t setgroups(size_t count, gid_t const *groups) */
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR64_setresuid                0x75                           /* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
#define __NR64_getresuid                0x76                           /* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR64_setresgid                0x77                           /* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
#define __NR64_getresgid                0x78                           /* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
#define __NR64_getpgid                  0x79                           /* pid_t getpgid(pid_t pid) */
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR64_setfsuid                 0x7a                           /* errno_t setfsuid(uid_t uid) */
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR64_setfsgid                 0x7b                           /* errno_t setfsgid(gid_t gid) */
#define __NR64_getsid                   0x7c                           /* pid_t getsid(pid_t pid) */
#define __NR64_capget                   0x7d                           /* errno_t capget(int TODO_PROTOTYPE) */
#define __NR64_capset                   0x7e                           /* errno_t capset(int TODO_PROTOTYPE) */
#define __NR64_rt_sigpending            0x7f                           /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR64_rt_sigtimedwait          0x80                           /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox64_struct *info, struct timespecx64 const *timeout, size_t sigsetsize) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR64_rt_sigqueueinfo          0x81                           /* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
#define __NR64_rt_sigsuspend            0x82                           /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR64_sigaltstack              0x83                           /* errno_t sigaltstack(struct __sigaltstackx64 const *ss, struct __sigaltstackx64 *oss) */
/* @param: times: When NULL, set the current time */
#define __NR64_utime                    0x84                           /* errno_t utime(char const *filename, struct utimbufx64 const *times) */
#define __NR64_mknod                    0x85                           /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR64_uselib                   0x86                           /* errno_t uselib(char const *library) */
#define __NR64_personality              0x87                           /* errno_t personality(int TODO_PROTOTYPE) */
#define __NR64_ustat                    0x88                           /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define __NR64_statfs                   0x89                           /* errno_t statfs(char const *file, struct __statfsx64 *buf) */
#define __NR64_fstatfs                  0x8a                           /* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
#define __NR64_sysfs                    0x8b                           /* errno_t sysfs(int TODO_PROTOTYPE) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR64_getpriority              0x8c                           /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR64_setpriority              0x8d                           /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define __NR64_sched_setparam           0x8e                           /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define __NR64_sched_getparam           0x8f                           /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
#define __NR64_sched_setscheduler       0x90                           /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR64_sched_getscheduler       0x91                           /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR64_sched_get_priority_max   0x92                           /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR64_sched_get_priority_min   0x93                           /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR64_sched_rr_get_interval    0x94                           /* errno_t sched_rr_get_interval(pid_t pid, struct timespecx64 *ts) */
#define __NR64_mlock                    0x95                           /* errno_t mlock(void const *addr, size_t len) */
#define __NR64_munlock                  0x96                           /* errno_t munlock(void const *addr, size_t len) */
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
#define __NR64_mlockall                 0x97                           /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR64_munlockall               0x98                           /* errno_t munlockall(void) */
#define __NR64_vhangup                  0x99                           /* errno_t vhangup(void) */
#define __NR64_modify_ldt               0x9a                           /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
#define __NR64_pivot_root               0x9b                           /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define __NR64__sysctl                  0x9c                           /* errno_t _sysctl(int TODO_PROTOTYPE) */
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
#define __NR64_prctl                    0x9d                           /* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
/* >> arch_prctl(2)
 * Arch-dependent system process control interface. (But don't go and
 * think that the  normal `prctl(2)'  doesn't feature  arch-dependent
 * commands  -- honestly, this syscall shouldn't exist if you ask me,
 * but it does on linux, and so it must also on KOS...)
 * @param: command: One of `ARCH_*' (from <asm/prctl.h>)
 * @param: addr: Either a `syscall_ulong_t' or `syscall_ulong_t *', depending on `command'
 * @return: * :  Return value depends on `command' */
#define __NR64_arch_prctl               0x9e                           /* syscall_slong_t arch_prctl(unsigned int command, uint64_t *addr) */
#define __NR64_adjtimex                 0x9f                           /* errno_t adjtimex(struct timex *ntx) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR64_setrlimit                0xa0                           /* errno_t setrlimit(syscall_ulong_t resource, struct rlimitx64 const *rlimits) */
#define __NR64_chroot                   0xa1                           /* errno_t chroot(char const *path) */
#define __NR64_sync                     0xa2                           /* errno_t sync(void) */
#define __NR64_acct                     0xa3                           /* errno_t acct(char const *filename) */
#define __NR64_settimeofday             0xa4                           /* errno_t settimeofday(struct timevalx64 const *tv, struct timezone const *tz) */
#define __NR64_mount                    0xa5                           /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
#define __NR64_umount2                  0xa6                           /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR64_swapon                   0xa7                           /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
#define __NR64_swapoff                  0xa8                           /* errno_t swapoff(char const *pathname) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR64_reboot                   0xa9                           /* errno_t reboot(syscall_ulong_t how) */
#define __NR64_sethostname              0xaa                           /* errno_t sethostname(char const *name, size_t len) */
#define __NR64_setdomainname            0xab                           /* errno_t setdomainname(char const *name, size_t len) */
#define __NR64_iopl                     0xac                           /* errno_t iopl(syscall_ulong_t level) */
#define __NR64_ioperm                   0xad                           /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define __NR64_create_module            0xae                           /* errno_t create_module(void) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define __NR64_init_module              0xaf                           /* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
#define __NR64_delete_module            0xb0                           /* errno_t delete_module(char const *name, oflag_t flags) */
#define __NR64_get_kernel_syms          0xb1                           /* errno_t get_kernel_syms(void) */
#define __NR64_query_module             0xb2                           /* errno_t query_module(void) */
#define __NR64_quotactl                 0xb3                           /* errno_t quotactl(int TODO_PROTOTYPE) */
#define __NR64_nfsservctl               0xb4                           /* errno_t nfsservctl(int TODO_PROTOTYPE) */
#define __NR64_getpmsg                  0xb5                           /* errno_t getpmsg(void) */
#define __NR64_putpmsg                  0xb6                           /* errno_t putpmsg(void) */
#define __NR64_afs_syscall              0xb7                           /* errno_t afs_syscall(void) */
#define __NR64_tuxcall                  0xb8                           /* errno_t tuxcall(void) */
#define __NR64_security                 0xb9                           /* errno_t security(void) */
#define __NR64_gettid                   0xba                           /* pid_t gettid(void) */
#define __NR64_readahead                0xbb                           /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR64_setxattr                 0xbc                           /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR64_lsetxattr                0xbd                           /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR64_fsetxattr                0xbe                           /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR64_getxattr                 0xbf                           /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR64_lgetxattr                0xc0                           /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR64_fgetxattr                0xc1                           /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR64_listxattr                0xc2                           /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR64_llistxattr               0xc3                           /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR64_flistxattr               0xc4                           /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR64_removexattr              0xc5                           /* errno_t removexattr(char const *path, char const *name) */
#define __NR64_lremovexattr             0xc6                           /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR64_fremovexattr             0xc7                           /* errno_t fremovexattr(fd_t fd, char const *name) */
#define __NR64_tkill                    0xc8                           /* errno_t tkill(pid_t tid, signo_t signo) */
#define __NR64_time                     0xc9                           /* time32_t time(time32_t *timer) */
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
#define __NR64_futex                    0xca                           /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR64_sched_setaffinity        0xcb                           /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR64_sched_getaffinity        0xcc                           /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR64_set_thread_area          0xcd                           /* errno_t set_thread_area(int TODO_PROTOTYPE) */
#define __NR64_io_setup                 0xce                           /* errno_t io_setup(int TODO_PROTOTYPE) */
#define __NR64_io_destroy               0xcf                           /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define __NR64_io_getevents             0xd0                           /* errno_t io_getevents(int TODO_PROTOTYPE) */
#define __NR64_io_submit                0xd1                           /* errno_t io_submit(int TODO_PROTOTYPE) */
#define __NR64_io_cancel                0xd2                           /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define __NR64_get_thread_area          0xd3                           /* errno_t get_thread_area(int TODO_PROTOTYPE) */
#define __NR64_lookup_dcookie           0xd4                           /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
#define __NR64_epoll_create             0xd5                           /* fd_t epoll_create(syscall_ulong_t size) */
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
#define __NR64_epoll_ctl_old            0xd6                           /* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
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
#define __NR64_epoll_wait_old           0xd7                           /* ssize_t epoll_wait_old(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
#define __NR64_remap_file_pages         0xd8                           /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR64_getdents64               0xd9                           /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
#define __NR64_set_tid_address          0xda                           /* pid_t set_tid_address(pid_t *tidptr) */
#define __NR64_restart_syscall          0xdb                           /* errno_t restart_syscall(void) */
#define __NR64_semtimedop               0xdc                           /* errno_t semtimedop(int TODO_PROTOTYPE) */
#define __NR64_fadvise64                0xdd                           /* errno_t fadvise64(int TODO_PROTOTYPE) */
#define __NR64_timer_create             0xde                           /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define __NR64_timer_settime            0xdf                           /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx64 const *value, struct itimerspecx64 *ovalue) */
#define __NR64_timer_gettime            0xe0                           /* errno_t timer_gettime(timer_t timerid, struct itimerspecx64 *value) */
#define __NR64_timer_getoverrun         0xe1                           /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define __NR64_timer_delete             0xe2                           /* errno_t timer_delete(timer_t timerid) */
#define __NR64_clock_settime            0xe3                           /* errno_t clock_settime(clockid_t clock_id, struct timespecx64 const *tp) */
#define __NR64_clock_gettime            0xe4                           /* errno_t clock_gettime(clockid_t clock_id, struct timespecx64 *tp) */
#define __NR64_clock_getres             0xe5                           /* errno_t clock_getres(clockid_t clock_id, struct timespecx64 *res) */
#define __NR64_clock_nanosleep          0xe6                           /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx64 const *requested_time, struct timespecx64 *remaining) */
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR64_exit_group               0xe7                           /* void exit_group(syscall_ulong_t exit_code) */
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
#define __NR64_epoll_wait               0xe8                           /* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
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
#define __NR64_epoll_ctl                0xe9                           /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
#define __NR64_tgkill                   0xea                           /* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
#define __NR64_utimes                   0xeb                           /* errno_t utimes(char const *filename, struct timevalx64 const[2] times) */
#define __NR64_vserver                  0xec                           /* errno_t vserver(void) */
#define __NR64_mbind                    0xed                           /* errno_t mbind(int TODO_PROTOTYPE) */
#define __NR64_set_mempolicy            0xee                           /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define __NR64_get_mempolicy            0xef                           /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define __NR64_mq_open                  0xf0                           /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define __NR64_mq_unlink                0xf1                           /* errno_t mq_unlink(char const *name) */
#define __NR64_mq_timedsend             0xf2                           /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx64 const *abs_timeout) */
#define __NR64_mq_timedreceive          0xf3                           /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx64 const *abs_timeout) */
#define __NR64_mq_notify                0xf4                           /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define __NR64_mq_getsetattr            0xf5                           /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define __NR64_kexec_load               0xf6                           /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
#define __NR64_waitid                   0xf7                           /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox64_struct *infop, syscall_ulong_t options, struct rusagex64 *ru) */
#define __NR64_add_key                  0xf8                           /* errno_t add_key(int TODO_PROTOTYPE) */
#define __NR64_request_key              0xf9                           /* errno_t request_key(int TODO_PROTOTYPE) */
#define __NR64_keyctl                   0xfa                           /* errno_t keyctl(int TODO_PROTOTYPE) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR64_ioprio_set               0xfb                           /* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR64_ioprio_get               0xfc                           /* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
#define __NR64_inotify_init             0xfd                           /* errno_t inotify_init(int TODO_PROTOTYPE) */
#define __NR64_inotify_add_watch        0xfe                           /* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
#define __NR64_inotify_rm_watch         0xff                           /* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
#define __NR64_migrate_pages            0x100                          /* errno_t migrate_pages(int TODO_PROTOTYPE) */
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
#define __NR64_openat                   0x101                          /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define __NR64_mkdirat                  0x102                          /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define __NR64_mknodat                  0x103                          /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_fchownat                 0x104                          /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define __NR64_futimesat                0x105                          /* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx64 const[2] times) */
#define __NR64_newfstatat               0x106                          /* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
#define __NR64_unlinkat                 0x107                          /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR64_renameat                 0x108                          /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR64_linkat                   0x109                          /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR64_symlinkat                0x10a                          /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define __NR64_readlinkat               0x10b                          /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_fchmodat                 0x10c                          /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
#define __NR64_faccessat                0x10d                          /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
#define __NR64_pselect6                 0x10e                          /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx64 const *timeout, struct __sigset_with_sizex64 const *sigmask_sigset_with_size) */
#define __NR64_ppoll                    0x10f                          /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param: what: Set of `CLONE_*' */
#define __NR64_unshare                  0x110                          /* errno_t unshare(syscall_ulong_t what) */
#define __NR64_set_robust_list          0x111                          /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define __NR64_get_robust_list          0x112                          /* errno_t get_robust_list(int TODO_PROTOTYPE) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR64_splice                   0x113                          /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR64_tee                      0x114                          /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
#define __NR64_sync_file_range          0x115                          /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR64_vmsplice                 0x116                          /* ssize_t vmsplice(fd_t fdout, struct iovecx64 const *iov, size_t count, syscall_ulong_t flags) */
#define __NR64_move_pages               0x117                          /* errno_t move_pages(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
#define __NR64_utimensat                0x118                          /* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx64 const[2] times, atflag_t flags) */
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
#define __NR64_epoll_pwait              0x119                          /* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
#define __NR64_signalfd                 0x11a                          /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
#define __NR64_timerfd_create           0x11b                          /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define __NR64_eventfd                  0x11c                          /* fd_t eventfd(syscall_ulong_t initval) */
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
#define __NR64_fallocate                0x11d                          /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
#define __NR64_timerfd_settime          0x11e                          /* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx64 const *utmr, struct itimerspecx64 *otmr) */
/* Return the next expiration time of UFD */
#define __NR64_timerfd_gettime          0x11f                          /* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx64 *otmr) */
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
#define __NR64_accept4                  0x120                          /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
#define __NR64_signalfd4                0x121                          /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
#define __NR64_eventfd2                 0x122                          /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
#define __NR64_epoll_create1            0x123                          /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
#define __NR64_dup3                     0x124                          /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define __NR64_pipe2                    0x125                          /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define __NR64_inotify_init1            0x126                          /* errno_t inotify_init1(int TODO_PROTOTYPE) */
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __NR64_preadv                   0x127                          /* ssize_t preadv(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define __NR64_pwritev                  0x128                          /* ssize_t pwritev(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR64_rt_tgsigqueueinfo        0x129                          /* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfox64_struct const *uinfo) */
#define __NR64_perf_event_open          0x12a                          /* errno_t perf_event_open(int TODO_PROTOTYPE) */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
#define __NR64_recvmmsg                 0x12b                          /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx64 const *tmo) */
#define __NR64_fanotify_init            0x12c                          /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define __NR64_fanotify_mark            0x12d                          /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR64_prlimit64                0x12e                          /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimitx64 const *new_limit, struct rlimitx64 *old_limit) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR64_name_to_handle_at        0x12f                          /* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
#define __NR64_open_by_handle_at        0x130                          /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
#define __NR64_clock_adjtime            0x131                          /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define __NR64_syncfs                   0x132                          /* errno_t syncfs(fd_t fd) */
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
#define __NR64_sendmmsg                 0x133                          /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx64 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
#define __NR64_setns                    0x134                          /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
#define __NR64_getcpu                   0x135                          /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
#define __NR64_process_vm_readv         0x136                          /* ssize_t process_vm_readv(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
#define __NR64_process_vm_writev        0x137                          /* ssize_t process_vm_writev(pid_t pid, struct iovecx64 const *local_iov, size_t liovcnt, struct iovecx64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
#define __NR64_kcmp                     0x138                          /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define __NR64_finit_module             0x139                          /* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
#define __NR64_sched_setattr            0x13a                          /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define __NR64_sched_getattr            0x13b                          /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
#define __NR64_renameat2                0x13c                          /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
#define __NR64_seccomp                  0x13d                          /* errno_t seccomp(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
#define __NR64_getrandom                0x13e                          /* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
#define __NR64_memfd_create             0x13f                          /* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
#define __NR64_kexec_file_load          0x140                          /* errno_t kexec_file_load(int TODO_PROTOTYPE) */
#define __NR64_bpf                      0x141                          /* errno_t bpf(int TODO_PROTOTYPE) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_execveat                 0x142                          /* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
#define __NR64_userfaultfd              0x143                          /* fd_t userfaultfd(syscall_ulong_t flags) */
#define __NR64_membarrier               0x144                          /* errno_t membarrier(int TODO_PROTOTYPE) */
#define __NR64_mlock2                   0x145                          /* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
#define __NR64_copy_file_range          0x146                          /* errno_t copy_file_range(int TODO_PROTOTYPE) */
#define __NR64_preadv2                  0x147                          /* errno_t preadv2(int TODO_PROTOTYPE) */
#define __NR64_pwritev2                 0x148                          /* errno_t pwritev2(int TODO_PROTOTYPE) */
#define __NR64_pkey_mprotect            0x149                          /* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
#define __NR64_pkey_alloc               0x14a                          /* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
#define __NR64_pkey_free                0x14b                          /* errno_t pkey_free(syscall_ulong_t key) */
#define __NR64_statx                    0x14c                          /* errno_t statx(int TODO_PROTOTYPE) */
#define __NR64_io_pgetevents            0x14d                          /* errno_t io_pgetevents(int TODO_PROTOTYPE) */
#define __NR64_rseq                     0x14e                          /* errno_t rseq(int TODO_PROTOTYPE) */
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
#define __NR64_pidfd_send_signal        0x1a8                          /* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox64_struct const *uinfo, syscall_ulong_t flags) */
#define __NR64_io_uring_setup           0x1a9                          /* errno_t io_uring_setup(int TODO_PROTOTYPE) */
#define __NR64_io_uring_enter           0x1aa                          /* errno_t io_uring_enter(int TODO_PROTOTYPE) */
#define __NR64_io_uring_register        0x1ab                          /* errno_t io_uring_register(int TODO_PROTOTYPE) */
#define __NR64_open_tree                0x1ac                          /* errno_t open_tree(int TODO_PROTOTYPE) */
#define __NR64_move_mount               0x1ad                          /* errno_t move_mount(int TODO_PROTOTYPE) */
#define __NR64_fsopen                   0x1ae                          /* errno_t fsopen(int TODO_PROTOTYPE) */
#define __NR64_fsconfig                 0x1af                          /* errno_t fsconfig(int TODO_PROTOTYPE) */
#define __NR64_fsmount                  0x1b0                          /* errno_t fsmount(int TODO_PROTOTYPE) */
#define __NR64_fspick                   0x1b1                          /* errno_t fspick(int TODO_PROTOTYPE) */
/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
#define __NR64_pidfd_open               0x1b2                          /* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
#define __NR64_clone3                   0x1b3                          /* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
#define __NR64_close_range              0x1b4                          /* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
#define __NR64_openat2                  0x1b5                          /* errno_t openat2(int TODO_PROTOTYPE) */
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
#define __NR64_pidfd_getfd              0x1b6                          /* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
#define __NR64_faccessat2               0x1b7                          /* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define __NR64_pwritevf                 __UINT64_C(0xfffffffffffffed8) /* ssize_t pwritevf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __NR64_preadvf                  __UINT64_C(0xfffffffffffffed9) /* ssize_t preadvf(fd_t fd, struct iovecx64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_freadlinkat              __UINT64_C(0xfffffffffffffef5) /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fsymlinkat               __UINT64_C(0xfffffffffffffef6) /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_kfstatat                 __UINT64_C(0xfffffffffffffefa) /* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fmknodat                 __UINT64_C(0xfffffffffffffefd) /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fmkdirat                 __UINT64_C(0xfffffffffffffefe) /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
#define __NR64_ksysctl                  __UINT64_C(0xffffffffffffff64) /* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
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
#define __NR64_maplibrary               __UINT64_C(0xffffffffffffff7a) /* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr const *hdrv, size_t hdrc) */
#define __NR64_fsmode                   __UINT64_C(0xffffffffffffffa1) /* uint64_t fsmode(uint64_t mode) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fchdirat                 __UINT64_C(0xffffffffffffffb0) /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
#define __NR64_kreaddirf                __UINT64_C(0xffffffffffffffb1) /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
#define __NR64_kreaddir                 __UINT64_C(0xffffffffffffffb2) /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
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
#define __NR64_set_exception_handler    __UINT64_C(0xffffffffffffffd9) /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
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
#define __NR64_get_exception_handler    __UINT64_C(0xffffffffffffffda) /* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
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
#define __NR64_rpc_serve_sysret         __UINT64_C(0xffffffffffffffdb) /* errno_t rpc_serve_sysret(void) */
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
#define __NR64_set_userprocmask_address __UINT64_C(0xffffffffffffffdc) /* errno_t set_userprocmask_address(struct userprocmask *ctl) */
/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
#define __NR64_rtm_test                 __UINT64_C(0xffffffffffffffdd) /* syscall_ulong_t rtm_test(void) */
/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
#define __NR64_rtm_abort                __UINT64_C(0xffffffffffffffde) /* errno_t rtm_abort(syscall_ulong_t code) */
/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
#define __NR64_rtm_end                  __UINT64_C(0xffffffffffffffdf) /* errno_t rtm_end(void) */
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
#define __NR64_rtm_begin                __UINT64_C(0xffffffffffffffe0) /* rtm_status_t rtm_begin(void) */
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
#define __NR64_userviofd                __UINT64_C(0xffffffffffffffe1) /* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
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
#define __NR64_coredump                 __UINT64_C(0xffffffffffffffe3) /* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void const) const *traceback_vector, size_t traceback_length, union coredump_info64 const *reason, syscall_ulong_t unwind_error) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define __NR64_mktty                    __UINT64_C(0xffffffffffffffe5) /* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
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
#define __NR64_lfutexexpr               __UINT64_C(0xffffffffffffffe6) /* errno_t lfutexexpr(uint64_t *futexaddr, void *base, struct lfutexexprx64 const *expr, struct timespecx64 const *timeout, syscall_ulong_t flags) */
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
#define __NR64_lfutex                   __UINT64_C(0xffffffffffffffe8) /* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct timespecx64 const *timeout, uint64_t val2) */
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
#define __NR64_rpc_serve                __UINT64_C(0xffffffffffffffe9) /* errno_t rpc_serve(void) */
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
#define __NR64_debugtrap                __UINT64_C(0xffffffffffffffea) /* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define __NR64_writevf                  __UINT64_C(0xffffffffffffffec) /* ssize_t writevf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define __NR64_readvf                   __UINT64_C(0xffffffffffffffed) /* ssize_t readvf(fd_t fd, struct iovecx64 const *iovec, size_t count, iomode_t mode) */
#define __NR64_pwrite64f                __UINT64_C(0xffffffffffffffee) /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR64_pread64f                 __UINT64_C(0xffffffffffffffef) /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR64_ioctlf                   __UINT64_C(0xfffffffffffffff0) /* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
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
#define __NR64_ksigreturn               __UINT64_C(0xfffffffffffffff1) /* void ksigreturn(void) */
/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
#define __NR64_openpty                  __UINT64_C(0xfffffffffffffff3) /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
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
#define __NR64_rpc_schedule             __UINT64_C(0xfffffffffffffff4) /* errno_t rpc_schedule(pid_t target_tid, syscall_ulong_t mode, void const *program, __HYBRID_PTR64(void const) const *params, size_t max_param_count) */
/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_frealpathat              __UINT64_C(0xfffffffffffffff5) /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_frealpath4               __UINT64_C(0xfffffffffffffff6) /* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define __NR64_getdrives                __UINT64_C(0xfffffffffffffff7) /* syscall_slong_t getdrives(void) */
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
#define __NR64_detach                   __UINT64_C(0xfffffffffffffff8) /* errno_t detach(pid_t pid) */
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define __NR64_readf                    __UINT64_C(0xfffffffffffffff9) /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define __NR64_klstat                   __UINT64_C(0xfffffffffffffffa) /* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
#define __NR64_kfstat                   __UINT64_C(0xfffffffffffffffb) /* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
#define __NR64_kstat                    __UINT64_C(0xfffffffffffffffc) /* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define __NR64_writef                   __UINT64_C(0xffffffffffffffff) /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */


/************************************************************************/
/* SYSCALL LIMITS                                                       */
/************************************************************************/
#define __NR64FEAT_SYSCALL_TABLE_COUNT 2
#define __NR64FEAT_SYSCALL_TABLE_FOREACH(callback) \
	callback(0)                                    \
	callback(1) 
#define __NR64_syscall0_min 0x0
#define __NR64_syscall0_max 0x1b7
#define __NR64_syscall0_cnt 0x1b8
#define __NR64_syscall1_min __UINT64_C(0xfffffffffffffed8)
#define __NR64_syscall1_max __UINT64_C(0xffffffffffffffff)
#define __NR64_syscall1_cnt 0x128
#endif /* !__NR64_read */


/************************************************************************/
/* SYSCALL RESTART MODES                                                */
/************************************************************************/
#ifdef __WANT_SYSCALL_RESTART_MODES
#ifndef __NR64FEAT_DEFINED_SYSCALL_RESTART_MODES
#define __NR64FEAT_DEFINED_SYSCALL_RESTART_MODES
/* Restart modes:
 * 0 (auto):
 *   - Restart only if `SA_RESTART' / `RPC_SYSRESTART_F_AUTO' is set
 * 1 (dont):
 *   - Never restart; always return -EINTR or propagate E_INTERRUPT
 * 2 (must):
 *   - Always restart, after return from a signal handler
 * Interaction with `SA_RESTART' / `RPC_SYSRESTART_F_AUTO':
 *  - auto + ~SA_RESTART: No
 *  - auto + SA_RESTART:  Yes
 *  - dont + ~SA_RESTART: No
 *  - dont + SA_RESTART:  No
 *  - must + ~SA_RESTART: Yes
 *  - must + SA_RESTART:  Yes
 */
#define __NR64RM_read                     0
#define __NR64RM_write                    0
#define __NR64RM_open                     0
#define __NR64RM_close                    2
#define __NR64RM_stat                     0
#define __NR64RM_fstat                    0
#define __NR64RM_lstat                    0
#define __NR64RM_poll                     1
#define __NR64RM_lseek                    0
#define __NR64RM_mmap                     0
#define __NR64RM_mprotect                 2
#define __NR64RM_munmap                   2
#define __NR64RM_brk                      0
#define __NR64RM_rt_sigaction             0
#define __NR64RM_rt_sigprocmask           0
#define __NR64RM_rt_sigreturn             2
#define __NR64RM_ioctl                    0
#define __NR64RM_pread64                  0
#define __NR64RM_pwrite64                 0
#define __NR64RM_readv                    0
#define __NR64RM_writev                   0
#define __NR64RM_access                   0
#define __NR64RM_pipe                     0
#define __NR64RM_select                   1
#define __NR64RM_sched_yield              1
#define __NR64RM_mremap                   0
#define __NR64RM_msync                    0
#define __NR64RM_mincore                  0
#define __NR64RM_madvise                  0
#define __NR64RM_shmget                   0
#define __NR64RM_shmat                    0
#define __NR64RM_shmctl                   0
#define __NR64RM_dup                      0
#define __NR64RM_dup2                     0
#define __NR64RM_pause                    1
#define __NR64RM_nanosleep                1
#define __NR64RM_getitimer                0
#define __NR64RM_alarm                    0
#define __NR64RM_setitimer                0
#define __NR64RM_getpid                   2
#define __NR64RM_sendfile                 1
#define __NR64RM_socket                   0
#define __NR64RM_connect                  1
#define __NR64RM_accept                   1
#define __NR64RM_sendto                   1
#define __NR64RM_recvfrom                 1
#define __NR64RM_sendmsg                  1
#define __NR64RM_recvmsg                  1
#define __NR64RM_shutdown                 0
#define __NR64RM_bind                     0
#define __NR64RM_listen                   0
#define __NR64RM_getsockname              0
#define __NR64RM_getpeername              0
#define __NR64RM_socketpair               0
#define __NR64RM_setsockopt               1
#define __NR64RM_getsockopt               0
#define __NR64RM_clone                    0
#define __NR64RM_fork                     2
#define __NR64RM_vfork                    2
#define __NR64RM_execve                   0
#define __NR64RM_exit                     2
#define __NR64RM_wait4                    1
#define __NR64RM_kill                     0
#define __NR64RM_uname                    0
#define __NR64RM_semget                   0
#define __NR64RM_semop                    1
#define __NR64RM_semctl                   0
#define __NR64RM_shmdt                    0
#define __NR64RM_msgget                   0
#define __NR64RM_msgsnd                   1
#define __NR64RM_msgrcv                   1
#define __NR64RM_msgctl                   0
#define __NR64RM_fcntl                    0
#define __NR64RM_flock                    0
#define __NR64RM_fsync                    0
#define __NR64RM_fdatasync                0
#define __NR64RM_truncate                 0
#define __NR64RM_ftruncate                0
#define __NR64RM_getdents                 0
#define __NR64RM_getcwd                   0
#define __NR64RM_chdir                    0
#define __NR64RM_fchdir                   0
#define __NR64RM_rename                   0
#define __NR64RM_mkdir                    0
#define __NR64RM_rmdir                    0
#define __NR64RM_creat                    0
#define __NR64RM_link                     0
#define __NR64RM_unlink                   0
#define __NR64RM_symlink                  0
#define __NR64RM_readlink                 0
#define __NR64RM_chmod                    0
#define __NR64RM_fchmod                   0
#define __NR64RM_chown                    0
#define __NR64RM_fchown                   0
#define __NR64RM_lchown                   0
#define __NR64RM_umask                    2
#define __NR64RM_gettimeofday             0
#define __NR64RM_getrlimit                0
#define __NR64RM_getrusage                0
#define __NR64RM_sysinfo                  0
#define __NR64RM_times                    0
#define __NR64RM_ptrace                   0
#define __NR64RM_getuid                   2
#define __NR64RM_syslog                   2
#define __NR64RM_getgid                   2
#define __NR64RM_setuid                   2
#define __NR64RM_setgid                   2
#define __NR64RM_geteuid                  2
#define __NR64RM_getegid                  2
#define __NR64RM_setpgid                  2
#define __NR64RM_getppid                  2
#define __NR64RM_getpgrp                  2
#define __NR64RM_setsid                   2
#define __NR64RM_setreuid                 2
#define __NR64RM_setregid                 2
#define __NR64RM_getgroups                2
#define __NR64RM_setgroups                2
#define __NR64RM_setresuid                2
#define __NR64RM_getresuid                2
#define __NR64RM_setresgid                2
#define __NR64RM_getresgid                2
#define __NR64RM_getpgid                  2
#define __NR64RM_setfsuid                 2
#define __NR64RM_setfsgid                 2
#define __NR64RM_getsid                   2
#define __NR64RM_capget                   0
#define __NR64RM_capset                   0
#define __NR64RM_rt_sigpending            0
#define __NR64RM_rt_sigtimedwait          1
#define __NR64RM_rt_sigqueueinfo          0
#define __NR64RM_rt_sigsuspend            1
#define __NR64RM_sigaltstack              0
#define __NR64RM_utime                    0
#define __NR64RM_mknod                    0
#define __NR64RM_uselib                   0
#define __NR64RM_personality              0
#define __NR64RM_ustat                    0
#define __NR64RM_statfs                   0
#define __NR64RM_fstatfs                  0
#define __NR64RM_sysfs                    0
#define __NR64RM_getpriority              0
#define __NR64RM_setpriority              0
#define __NR64RM_sched_setparam           0
#define __NR64RM_sched_getparam           0
#define __NR64RM_sched_setscheduler       0
#define __NR64RM_sched_getscheduler       0
#define __NR64RM_sched_get_priority_max   0
#define __NR64RM_sched_get_priority_min   0
#define __NR64RM_sched_rr_get_interval    0
#define __NR64RM_mlock                    0
#define __NR64RM_munlock                  0
#define __NR64RM_mlockall                 0
#define __NR64RM_munlockall               0
#define __NR64RM_vhangup                  0
#define __NR64RM_modify_ldt               0
#define __NR64RM_pivot_root               0
#define __NR64RM__sysctl                  0
#define __NR64RM_prctl                    0
#define __NR64RM_arch_prctl               0
#define __NR64RM_adjtimex                 0
#define __NR64RM_setrlimit                0
#define __NR64RM_chroot                   0
#define __NR64RM_sync                     0
#define __NR64RM_acct                     0
#define __NR64RM_settimeofday             0
#define __NR64RM_mount                    0
#define __NR64RM_umount2                  2
#define __NR64RM_swapon                   0
#define __NR64RM_swapoff                  0
#define __NR64RM_reboot                   0
#define __NR64RM_sethostname              0
#define __NR64RM_setdomainname            0
#define __NR64RM_iopl                     0
#define __NR64RM_ioperm                   0
#define __NR64RM_create_module            0
#define __NR64RM_init_module              0
#define __NR64RM_delete_module            0
#define __NR64RM_get_kernel_syms          0
#define __NR64RM_query_module             0
#define __NR64RM_quotactl                 0
#define __NR64RM_nfsservctl               0
#define __NR64RM_getpmsg                  0
#define __NR64RM_putpmsg                  0
#define __NR64RM_afs_syscall              0
#define __NR64RM_tuxcall                  0
#define __NR64RM_security                 0
#define __NR64RM_gettid                   2
#define __NR64RM_readahead                0
#define __NR64RM_setxattr                 0
#define __NR64RM_lsetxattr                0
#define __NR64RM_fsetxattr                0
#define __NR64RM_getxattr                 0
#define __NR64RM_lgetxattr                0
#define __NR64RM_fgetxattr                0
#define __NR64RM_listxattr                0
#define __NR64RM_llistxattr               0
#define __NR64RM_flistxattr               0
#define __NR64RM_removexattr              0
#define __NR64RM_lremovexattr             0
#define __NR64RM_fremovexattr             0
#define __NR64RM_tkill                    0
#define __NR64RM_time                     0
#define __NR64RM_futex                    0
#define __NR64RM_sched_setaffinity        0
#define __NR64RM_sched_getaffinity        0
#define __NR64RM_set_thread_area          0
#define __NR64RM_io_setup                 0
#define __NR64RM_io_destroy               0
#define __NR64RM_io_getevents             1
#define __NR64RM_io_submit                0
#define __NR64RM_io_cancel                0
#define __NR64RM_get_thread_area          0
#define __NR64RM_lookup_dcookie           0
#define __NR64RM_epoll_create             0
#define __NR64RM_epoll_ctl_old            0
#define __NR64RM_epoll_wait_old           1
#define __NR64RM_remap_file_pages         0
#define __NR64RM_getdents64               0
#define __NR64RM_set_tid_address          2
#define __NR64RM_restart_syscall          0
#define __NR64RM_semtimedop               1
#define __NR64RM_fadvise64                0
#define __NR64RM_timer_create             0
#define __NR64RM_timer_settime            0
#define __NR64RM_timer_gettime            0
#define __NR64RM_timer_getoverrun         0
#define __NR64RM_timer_delete             0
#define __NR64RM_clock_settime            0
#define __NR64RM_clock_gettime            0
#define __NR64RM_clock_getres             0
#define __NR64RM_clock_nanosleep          1
#define __NR64RM_exit_group               2
#define __NR64RM_epoll_wait               1
#define __NR64RM_epoll_ctl                0
#define __NR64RM_tgkill                   0
#define __NR64RM_utimes                   0
#define __NR64RM_vserver                  0
#define __NR64RM_mbind                    0
#define __NR64RM_set_mempolicy            0
#define __NR64RM_get_mempolicy            0
#define __NR64RM_mq_open                  0
#define __NR64RM_mq_unlink                0
#define __NR64RM_mq_timedsend             0
#define __NR64RM_mq_timedreceive          0
#define __NR64RM_mq_notify                0
#define __NR64RM_mq_getsetattr            0
#define __NR64RM_kexec_load               0
#define __NR64RM_waitid                   1
#define __NR64RM_add_key                  0
#define __NR64RM_request_key              0
#define __NR64RM_keyctl                   0
#define __NR64RM_ioprio_set               0
#define __NR64RM_ioprio_get               0
#define __NR64RM_inotify_init             0
#define __NR64RM_inotify_add_watch        0
#define __NR64RM_inotify_rm_watch         0
#define __NR64RM_migrate_pages            0
#define __NR64RM_openat                   0
#define __NR64RM_mkdirat                  0
#define __NR64RM_mknodat                  0
#define __NR64RM_fchownat                 0
#define __NR64RM_futimesat                0
#define __NR64RM_newfstatat               0
#define __NR64RM_unlinkat                 0
#define __NR64RM_renameat                 0
#define __NR64RM_linkat                   0
#define __NR64RM_symlinkat                0
#define __NR64RM_readlinkat               0
#define __NR64RM_fchmodat                 0
#define __NR64RM_faccessat                0
#define __NR64RM_pselect6                 1
#define __NR64RM_ppoll                    1
#define __NR64RM_unshare                  0
#define __NR64RM_set_robust_list          0
#define __NR64RM_get_robust_list          0
#define __NR64RM_splice                   0
#define __NR64RM_tee                      0
#define __NR64RM_sync_file_range          0
#define __NR64RM_vmsplice                 0
#define __NR64RM_move_pages               0
#define __NR64RM_utimensat                0
#define __NR64RM_epoll_pwait              1
#define __NR64RM_signalfd                 0
#define __NR64RM_timerfd_create           0
#define __NR64RM_eventfd                  0
#define __NR64RM_fallocate                0
#define __NR64RM_timerfd_settime          0
#define __NR64RM_timerfd_gettime          0
#define __NR64RM_accept4                  1
#define __NR64RM_signalfd4                0
#define __NR64RM_eventfd2                 0
#define __NR64RM_epoll_create1            0
#define __NR64RM_dup3                     0
#define __NR64RM_pipe2                    0
#define __NR64RM_inotify_init1            0
#define __NR64RM_preadv                   0
#define __NR64RM_pwritev                  0
#define __NR64RM_rt_tgsigqueueinfo        0
#define __NR64RM_perf_event_open          0
#define __NR64RM_recvmmsg                 1
#define __NR64RM_fanotify_init            0
#define __NR64RM_fanotify_mark            0
#define __NR64RM_prlimit64                0
#define __NR64RM_name_to_handle_at        0
#define __NR64RM_open_by_handle_at        0
#define __NR64RM_clock_adjtime            0
#define __NR64RM_syncfs                   0
#define __NR64RM_sendmmsg                 1
#define __NR64RM_setns                    0
#define __NR64RM_getcpu                   0
#define __NR64RM_process_vm_readv         0
#define __NR64RM_process_vm_writev        0
#define __NR64RM_kcmp                     0
#define __NR64RM_finit_module             0
#define __NR64RM_sched_setattr            0
#define __NR64RM_sched_getattr            0
#define __NR64RM_renameat2                0
#define __NR64RM_seccomp                  0
#define __NR64RM_getrandom                0
#define __NR64RM_memfd_create             0
#define __NR64RM_kexec_file_load          0
#define __NR64RM_bpf                      0
#define __NR64RM_execveat                 0
#define __NR64RM_userfaultfd              0
#define __NR64RM_membarrier               0
#define __NR64RM_mlock2                   0
#define __NR64RM_copy_file_range          0
#define __NR64RM_preadv2                  0
#define __NR64RM_pwritev2                 0
#define __NR64RM_pkey_mprotect            0
#define __NR64RM_pkey_alloc               0
#define __NR64RM_pkey_free                0
#define __NR64RM_statx                    0
#define __NR64RM_io_pgetevents            1
#define __NR64RM_rseq                     0
#define __NR64RM_pidfd_send_signal        0
#define __NR64RM_io_uring_setup           0
#define __NR64RM_io_uring_enter           0
#define __NR64RM_io_uring_register        0
#define __NR64RM_open_tree                0
#define __NR64RM_move_mount               0
#define __NR64RM_fsopen                   0
#define __NR64RM_fsconfig                 0
#define __NR64RM_fsmount                  0
#define __NR64RM_fspick                   0
#define __NR64RM_pidfd_open               0
#define __NR64RM_clone3                   0
#define __NR64RM_close_range              2
#define __NR64RM_openat2                  0
#define __NR64RM_pidfd_getfd              0
#define __NR64RM_faccessat2               0
#define __NR64RM_pwritevf                 0
#define __NR64RM_preadvf                  0
#define __NR64RM_freadlinkat              0
#define __NR64RM_fsymlinkat               0
#define __NR64RM_kfstatat                 0
#define __NR64RM_fmknodat                 0
#define __NR64RM_fmkdirat                 0
#define __NR64RM_ksysctl                  0
#define __NR64RM_maplibrary               0
#define __NR64RM_fsmode                   2
#define __NR64RM_fchdirat                 0
#define __NR64RM_kreaddirf                0
#define __NR64RM_kreaddir                 0
#define __NR64RM_set_exception_handler    2
#define __NR64RM_get_exception_handler    2
#define __NR64RM_rpc_serve_sysret         1
#define __NR64RM_set_userprocmask_address 0
#define __NR64RM_rtm_test                 0
#define __NR64RM_rtm_abort                0
#define __NR64RM_rtm_end                  0
#define __NR64RM_rtm_begin                0
#define __NR64RM_userviofd                0
#define __NR64RM_coredump                 2
#define __NR64RM_mktty                    0
#define __NR64RM_lfutexexpr               1
#define __NR64RM_lfutex                   1
#define __NR64RM_rpc_serve                1
#define __NR64RM_debugtrap                0
#define __NR64RM_writevf                  0
#define __NR64RM_readvf                   0
#define __NR64RM_pwrite64f                0
#define __NR64RM_pread64f                 0
#define __NR64RM_ioctlf                   0
#define __NR64RM_ksigreturn               2
#define __NR64RM_openpty                  0
#define __NR64RM_rpc_schedule             0
#define __NR64RM_frealpathat              0
#define __NR64RM_frealpath4               0
#define __NR64RM_getdrives                2
#define __NR64RM_detach                   2
#define __NR64RM_readf                    0
#define __NR64RM_klstat                   0
#define __NR64RM_kfstat                   0
#define __NR64RM_kstat                    0
#define __NR64RM_writef                   0
#endif /* !__NR64FEAT_DEFINED_SYSCALL_RESTART_MODES */
#endif /* __WANT_SYSCALL_RESTART_MODES */


/************************************************************************/
/* SYSCALL CANCELLATION POINTS                                          */
/************************************************************************/
#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#ifndef __NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NR64FEAT_HAVE_CANCELLATION_POINTS
#define __NR64CP_read
#define __NR64CP_write
#define __NR64CP_open
#define __NR64CP_stat
#define __NR64CP_fstat
#define __NR64CP_lstat
#define __NR64CP_poll
#define __NR64CP_lseek
#define __NR64CP_ioctl
#define __NR64CP_pread64
#define __NR64CP_pwrite64
#define __NR64CP_readv
#define __NR64CP_writev
#define __NR64CP_access
#define __NR64CP_select
#define __NR64CP_msync
#define __NR64CP_pause
#define __NR64CP_nanosleep
#define __NR64CP_sendfile
#define __NR64CP_connect
#define __NR64CP_accept
#define __NR64CP_sendto
#define __NR64CP_recvfrom
#define __NR64CP_sendmsg
#define __NR64CP_recvmsg
#define __NR64CP_execve
#define __NR64CP_wait4
#define __NR64CP_msgsnd
#define __NR64CP_msgrcv
#define __NR64CP_fcntl
#define __NR64CP_flock
#define __NR64CP_fsync
#define __NR64CP_fdatasync
#define __NR64CP_getdents
#define __NR64CP_getcwd
#define __NR64CP_chdir
#define __NR64CP_fchdir
#define __NR64CP_rename
#define __NR64CP_mkdir
#define __NR64CP_creat
#define __NR64CP_link
#define __NR64CP_unlink
#define __NR64CP_symlink
#define __NR64CP_readlink
#define __NR64CP_chmod
#define __NR64CP_fchmod
#define __NR64CP_chown
#define __NR64CP_fchown
#define __NR64CP_lchown
#define __NR64CP_sysinfo
#define __NR64CP_rt_sigtimedwait
#define __NR64CP_rt_sigsuspend
#define __NR64CP_utime
#define __NR64CP_mknod
#define __NR64CP_sync
#define __NR64CP_mount
#define __NR64CP_umount2
#define __NR64CP_setxattr
#define __NR64CP_lsetxattr
#define __NR64CP_fsetxattr
#define __NR64CP_getxattr
#define __NR64CP_lgetxattr
#define __NR64CP_fgetxattr
#define __NR64CP_listxattr
#define __NR64CP_llistxattr
#define __NR64CP_flistxattr
#define __NR64CP_removexattr
#define __NR64CP_lremovexattr
#define __NR64CP_fremovexattr
#define __NR64CP_futex
#define __NR64CP_epoll_wait_old
#define __NR64CP_getdents64
#define __NR64CP_clock_nanosleep
#define __NR64CP_epoll_wait
#define __NR64CP_utimes
#define __NR64CP_mq_timedsend
#define __NR64CP_mq_timedreceive
#define __NR64CP_waitid
#define __NR64CP_openat
#define __NR64CP_mkdirat
#define __NR64CP_mknodat
#define __NR64CP_fchownat
#define __NR64CP_futimesat
#define __NR64CP_newfstatat
#define __NR64CP_unlinkat
#define __NR64CP_renameat
#define __NR64CP_linkat
#define __NR64CP_symlinkat
#define __NR64CP_readlinkat
#define __NR64CP_fchmodat
#define __NR64CP_faccessat
#define __NR64CP_pselect6
#define __NR64CP_ppoll
#define __NR64CP_splice
#define __NR64CP_tee
#define __NR64CP_sync_file_range
#define __NR64CP_vmsplice
#define __NR64CP_utimensat
#define __NR64CP_epoll_pwait
#define __NR64CP_accept4
#define __NR64CP_preadv
#define __NR64CP_pwritev
#define __NR64CP_recvmmsg
#define __NR64CP_name_to_handle_at
#define __NR64CP_open_by_handle_at
#define __NR64CP_syncfs
#define __NR64CP_sendmmsg
#define __NR64CP_renameat2
#define __NR64CP_execveat
#define __NR64CP_pwritevf
#define __NR64CP_preadvf
#define __NR64CP_freadlinkat
#define __NR64CP_fsymlinkat
#define __NR64CP_kfstatat
#define __NR64CP_fmknodat
#define __NR64CP_fmkdirat
#define __NR64CP_ksysctl
#define __NR64CP_fchdirat
#define __NR64CP_kreaddirf
#define __NR64CP_kreaddir
#define __NR64CP_lfutexexpr
#define __NR64CP_lfutex
#define __NR64CP_rpc_serve
#define __NR64CP_writevf
#define __NR64CP_readvf
#define __NR64CP_pwrite64f
#define __NR64CP_pread64f
#define __NR64CP_ioctlf
#define __NR64CP_rpc_schedule
#define __NR64CP_frealpathat
#define __NR64CP_frealpath4
#define __NR64CP_readf
#define __NR64CP_klstat
#define __NR64CP_kfstat
#define __NR64CP_kstat
#define __NR64CP_writef
#endif /* !__NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS */
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */


/************************************************************************/
/* SYSCALL REGISTER COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_REGISTER_COUNT
#ifndef __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NR64FEAT_SYSCALL_REGISTER_MAX_COUNT 6
#define __NR64FEAT_SYSCALL_REGISTER_BITS 64
#define __NR64RC_read                     3
#define __NR64RC_write                    3
#define __NR64RC_open                     3
#define __NR64RC_close                    1
#define __NR64RC_stat                     2
#define __NR64RC_fstat                    2
#define __NR64RC_lstat                    2
#define __NR64RC_poll                     3
#define __NR64RC_lseek                    3
#define __NR64RC_mmap                     6
#define __NR64RC_mprotect                 3
#define __NR64RC_munmap                   2
#define __NR64RC_brk                      1
#define __NR64RC_rt_sigaction             4
#define __NR64RC_rt_sigprocmask           4
#define __NR64RC_rt_sigreturn             0
#define __NR64RC_ioctl                    3
#define __NR64RC_pread64                  4
#define __NR64RC_pwrite64                 4
#define __NR64RC_readv                    3
#define __NR64RC_writev                   3
#define __NR64RC_access                   2
#define __NR64RC_pipe                     1
#define __NR64RC_select                   5
#define __NR64RC_sched_yield              0
#define __NR64RC_mremap                   5
#define __NR64RC_msync                    3
#define __NR64RC_mincore                  3
#define __NR64RC_madvise                  3
#define __NR64RC_shmget                   3
#define __NR64RC_shmat                    3
#define __NR64RC_shmctl                   3
#define __NR64RC_dup                      1
#define __NR64RC_dup2                     2
#define __NR64RC_pause                    0
#define __NR64RC_nanosleep                2
#define __NR64RC_getitimer                2
#define __NR64RC_alarm                    1
#define __NR64RC_setitimer                3
#define __NR64RC_getpid                   0
#define __NR64RC_sendfile                 4
#define __NR64RC_socket                   3
#define __NR64RC_connect                  3
#define __NR64RC_accept                   3
#define __NR64RC_sendto                   6
#define __NR64RC_recvfrom                 6
#define __NR64RC_sendmsg                  3
#define __NR64RC_recvmsg                  3
#define __NR64RC_shutdown                 2
#define __NR64RC_bind                     3
#define __NR64RC_listen                   2
#define __NR64RC_getsockname              3
#define __NR64RC_getpeername              3
#define __NR64RC_socketpair               4
#define __NR64RC_setsockopt               5
#define __NR64RC_getsockopt               5
#define __NR64RC_clone                    5
#define __NR64RC_fork                     0
#define __NR64RC_vfork                    0
#define __NR64RC_execve                   3
#define __NR64RC_exit                     1
#define __NR64RC_wait4                    4
#define __NR64RC_kill                     2
#define __NR64RC_uname                    1
#define __NR64RC_semget                   1
#define __NR64RC_semop                    1
#define __NR64RC_semctl                   1
#define __NR64RC_shmdt                    1
#define __NR64RC_msgget                   1
#define __NR64RC_msgsnd                   1
#define __NR64RC_msgrcv                   1
#define __NR64RC_msgctl                   1
#define __NR64RC_fcntl                    3
#define __NR64RC_flock                    2
#define __NR64RC_fsync                    1
#define __NR64RC_fdatasync                1
#define __NR64RC_truncate                 2
#define __NR64RC_ftruncate                2
#define __NR64RC_getdents                 3
#define __NR64RC_getcwd                   2
#define __NR64RC_chdir                    1
#define __NR64RC_fchdir                   1
#define __NR64RC_rename                   2
#define __NR64RC_mkdir                    2
#define __NR64RC_rmdir                    1
#define __NR64RC_creat                    2
#define __NR64RC_link                     2
#define __NR64RC_unlink                   1
#define __NR64RC_symlink                  2
#define __NR64RC_readlink                 3
#define __NR64RC_chmod                    2
#define __NR64RC_fchmod                   2
#define __NR64RC_chown                    3
#define __NR64RC_fchown                   3
#define __NR64RC_lchown                   3
#define __NR64RC_umask                    1
#define __NR64RC_gettimeofday             2
#define __NR64RC_getrlimit                2
#define __NR64RC_getrusage                2
#define __NR64RC_sysinfo                  1
#define __NR64RC_times                    1
#define __NR64RC_ptrace                   4
#define __NR64RC_getuid                   0
#define __NR64RC_syslog                   3
#define __NR64RC_getgid                   0
#define __NR64RC_setuid                   1
#define __NR64RC_setgid                   1
#define __NR64RC_geteuid                  0
#define __NR64RC_getegid                  0
#define __NR64RC_setpgid                  2
#define __NR64RC_getppid                  0
#define __NR64RC_getpgrp                  0
#define __NR64RC_setsid                   0
#define __NR64RC_setreuid                 2
#define __NR64RC_setregid                 2
#define __NR64RC_getgroups                2
#define __NR64RC_setgroups                2
#define __NR64RC_setresuid                3
#define __NR64RC_getresuid                3
#define __NR64RC_setresgid                3
#define __NR64RC_getresgid                3
#define __NR64RC_getpgid                  1
#define __NR64RC_setfsuid                 1
#define __NR64RC_setfsgid                 1
#define __NR64RC_getsid                   1
#define __NR64RC_capget                   1
#define __NR64RC_capset                   1
#define __NR64RC_rt_sigpending            2
#define __NR64RC_rt_sigtimedwait          4
#define __NR64RC_rt_sigqueueinfo          3
#define __NR64RC_rt_sigsuspend            2
#define __NR64RC_sigaltstack              2
#define __NR64RC_utime                    2
#define __NR64RC_mknod                    3
#define __NR64RC_uselib                   1
#define __NR64RC_personality              1
#define __NR64RC_ustat                    2
#define __NR64RC_statfs                   2
#define __NR64RC_fstatfs                  2
#define __NR64RC_sysfs                    1
#define __NR64RC_getpriority              2
#define __NR64RC_setpriority              3
#define __NR64RC_sched_setparam           2
#define __NR64RC_sched_getparam           2
#define __NR64RC_sched_setscheduler       3
#define __NR64RC_sched_getscheduler       1
#define __NR64RC_sched_get_priority_max   1
#define __NR64RC_sched_get_priority_min   1
#define __NR64RC_sched_rr_get_interval    2
#define __NR64RC_mlock                    2
#define __NR64RC_munlock                  2
#define __NR64RC_mlockall                 1
#define __NR64RC_munlockall               0
#define __NR64RC_vhangup                  0
#define __NR64RC_modify_ldt               3
#define __NR64RC_pivot_root               1
#define __NR64RC__sysctl                  1
#define __NR64RC_prctl                    5
#define __NR64RC_arch_prctl               2
#define __NR64RC_adjtimex                 1
#define __NR64RC_setrlimit                2
#define __NR64RC_chroot                   1
#define __NR64RC_sync                     0
#define __NR64RC_acct                     1
#define __NR64RC_settimeofday             2
#define __NR64RC_mount                    5
#define __NR64RC_umount2                  2
#define __NR64RC_swapon                   2
#define __NR64RC_swapoff                  1
#define __NR64RC_reboot                   1
#define __NR64RC_sethostname              2
#define __NR64RC_setdomainname            2
#define __NR64RC_iopl                     1
#define __NR64RC_ioperm                   3
#define __NR64RC_create_module            0
#define __NR64RC_init_module              3
#define __NR64RC_delete_module            2
#define __NR64RC_get_kernel_syms          0
#define __NR64RC_query_module             0
#define __NR64RC_quotactl                 1
#define __NR64RC_nfsservctl               1
#define __NR64RC_getpmsg                  0
#define __NR64RC_putpmsg                  0
#define __NR64RC_afs_syscall              0
#define __NR64RC_tuxcall                  0
#define __NR64RC_security                 0
#define __NR64RC_gettid                   0
#define __NR64RC_readahead                3
#define __NR64RC_setxattr                 5
#define __NR64RC_lsetxattr                5
#define __NR64RC_fsetxattr                5
#define __NR64RC_getxattr                 4
#define __NR64RC_lgetxattr                4
#define __NR64RC_fgetxattr                4
#define __NR64RC_listxattr                3
#define __NR64RC_llistxattr               3
#define __NR64RC_flistxattr               3
#define __NR64RC_removexattr              2
#define __NR64RC_lremovexattr             2
#define __NR64RC_fremovexattr             2
#define __NR64RC_tkill                    2
#define __NR64RC_time                     1
#define __NR64RC_futex                    6
#define __NR64RC_sched_setaffinity        3
#define __NR64RC_sched_getaffinity        3
#define __NR64RC_set_thread_area          1
#define __NR64RC_io_setup                 1
#define __NR64RC_io_destroy               1
#define __NR64RC_io_getevents             1
#define __NR64RC_io_submit                1
#define __NR64RC_io_cancel                1
#define __NR64RC_get_thread_area          1
#define __NR64RC_lookup_dcookie           1
#define __NR64RC_epoll_create             1
#define __NR64RC_epoll_ctl_old            4
#define __NR64RC_epoll_wait_old           4
#define __NR64RC_remap_file_pages         5
#define __NR64RC_getdents64               3
#define __NR64RC_set_tid_address          1
#define __NR64RC_restart_syscall          0
#define __NR64RC_semtimedop               1
#define __NR64RC_fadvise64                1
#define __NR64RC_timer_create             3
#define __NR64RC_timer_settime            4
#define __NR64RC_timer_gettime            2
#define __NR64RC_timer_getoverrun         1
#define __NR64RC_timer_delete             1
#define __NR64RC_clock_settime            2
#define __NR64RC_clock_gettime            2
#define __NR64RC_clock_getres             2
#define __NR64RC_clock_nanosleep          4
#define __NR64RC_exit_group               1
#define __NR64RC_epoll_wait               4
#define __NR64RC_epoll_ctl                4
#define __NR64RC_tgkill                   3
#define __NR64RC_utimes                   2
#define __NR64RC_vserver                  0
#define __NR64RC_mbind                    1
#define __NR64RC_set_mempolicy            1
#define __NR64RC_get_mempolicy            1
#define __NR64RC_mq_open                  3
#define __NR64RC_mq_unlink                1
#define __NR64RC_mq_timedsend             5
#define __NR64RC_mq_timedreceive          5
#define __NR64RC_mq_notify                2
#define __NR64RC_mq_getsetattr            3
#define __NR64RC_kexec_load               1
#define __NR64RC_waitid                   5
#define __NR64RC_add_key                  1
#define __NR64RC_request_key              1
#define __NR64RC_keyctl                   1
#define __NR64RC_ioprio_set               3
#define __NR64RC_ioprio_get               2
#define __NR64RC_inotify_init             1
#define __NR64RC_inotify_add_watch        1
#define __NR64RC_inotify_rm_watch         1
#define __NR64RC_migrate_pages            1
#define __NR64RC_openat                   4
#define __NR64RC_mkdirat                  3
#define __NR64RC_mknodat                  4
#define __NR64RC_fchownat                 5
#define __NR64RC_futimesat                3
#define __NR64RC_newfstatat               4
#define __NR64RC_unlinkat                 3
#define __NR64RC_renameat                 4
#define __NR64RC_linkat                   5
#define __NR64RC_symlinkat                3
#define __NR64RC_readlinkat               4
#define __NR64RC_fchmodat                 4
#define __NR64RC_faccessat                3
#define __NR64RC_pselect6                 6
#define __NR64RC_ppoll                    5
#define __NR64RC_unshare                  1
#define __NR64RC_set_robust_list          1
#define __NR64RC_get_robust_list          1
#define __NR64RC_splice                   6
#define __NR64RC_tee                      4
#define __NR64RC_sync_file_range          4
#define __NR64RC_vmsplice                 4
#define __NR64RC_move_pages               1
#define __NR64RC_utimensat                4
#define __NR64RC_epoll_pwait              6
#define __NR64RC_signalfd                 3
#define __NR64RC_timerfd_create           2
#define __NR64RC_eventfd                  1
#define __NR64RC_fallocate                4
#define __NR64RC_timerfd_settime          4
#define __NR64RC_timerfd_gettime          2
#define __NR64RC_accept4                  4
#define __NR64RC_signalfd4                4
#define __NR64RC_eventfd2                 2
#define __NR64RC_epoll_create1            1
#define __NR64RC_dup3                     3
#define __NR64RC_pipe2                    2
#define __NR64RC_inotify_init1            1
#define __NR64RC_preadv                   4
#define __NR64RC_pwritev                  4
#define __NR64RC_rt_tgsigqueueinfo        4
#define __NR64RC_perf_event_open          1
#define __NR64RC_recvmmsg                 5
#define __NR64RC_fanotify_init            1
#define __NR64RC_fanotify_mark            1
#define __NR64RC_prlimit64                4
#define __NR64RC_name_to_handle_at        5
#define __NR64RC_open_by_handle_at        3
#define __NR64RC_clock_adjtime            1
#define __NR64RC_syncfs                   1
#define __NR64RC_sendmmsg                 4
#define __NR64RC_setns                    2
#define __NR64RC_getcpu                   3
#define __NR64RC_process_vm_readv         6
#define __NR64RC_process_vm_writev        6
#define __NR64RC_kcmp                     5
#define __NR64RC_finit_module             3
#define __NR64RC_sched_setattr            1
#define __NR64RC_sched_getattr            1
#define __NR64RC_renameat2                5
#define __NR64RC_seccomp                  1
#define __NR64RC_getrandom                3
#define __NR64RC_memfd_create             2
#define __NR64RC_kexec_file_load          1
#define __NR64RC_bpf                      1
#define __NR64RC_execveat                 5
#define __NR64RC_userfaultfd              1
#define __NR64RC_membarrier               1
#define __NR64RC_mlock2                   3
#define __NR64RC_copy_file_range          1
#define __NR64RC_preadv2                  1
#define __NR64RC_pwritev2                 1
#define __NR64RC_pkey_mprotect            4
#define __NR64RC_pkey_alloc               2
#define __NR64RC_pkey_free                1
#define __NR64RC_statx                    1
#define __NR64RC_io_pgetevents            1
#define __NR64RC_rseq                     1
#define __NR64RC_pidfd_send_signal        4
#define __NR64RC_io_uring_setup           1
#define __NR64RC_io_uring_enter           1
#define __NR64RC_io_uring_register        1
#define __NR64RC_open_tree                1
#define __NR64RC_move_mount               1
#define __NR64RC_fsopen                   1
#define __NR64RC_fsconfig                 1
#define __NR64RC_fsmount                  1
#define __NR64RC_fspick                   1
#define __NR64RC_pidfd_open               2
#define __NR64RC_clone3                   2
#define __NR64RC_close_range              3
#define __NR64RC_openat2                  1
#define __NR64RC_pidfd_getfd              3
#define __NR64RC_faccessat2               4
#define __NR64RC_pwritevf                 5
#define __NR64RC_preadvf                  5
#define __NR64RC_freadlinkat              5
#define __NR64RC_fsymlinkat               4
#define __NR64RC_kfstatat                 4
#define __NR64RC_fmknodat                 5
#define __NR64RC_fmkdirat                 4
#define __NR64RC_ksysctl                  2
#define __NR64RC_maplibrary               5
#define __NR64RC_fsmode                   1
#define __NR64RC_fchdirat                 3
#define __NR64RC_kreaddirf                5
#define __NR64RC_kreaddir                 4
#define __NR64RC_set_exception_handler    3
#define __NR64RC_get_exception_handler    3
#define __NR64RC_rpc_serve_sysret         0
#define __NR64RC_set_userprocmask_address 1
#define __NR64RC_rtm_test                 0
#define __NR64RC_rtm_abort                1
#define __NR64RC_rtm_end                  0
#define __NR64RC_rtm_begin                0
#define __NR64RC_userviofd                2
#define __NR64RC_coredump                 6
#define __NR64RC_mktty                    4
#define __NR64RC_lfutexexpr               5
#define __NR64RC_lfutex                   5
#define __NR64RC_rpc_serve                0
#define __NR64RC_debugtrap                2
#define __NR64RC_writevf                  4
#define __NR64RC_readvf                   4
#define __NR64RC_pwrite64f                5
#define __NR64RC_pread64f                 5
#define __NR64RC_ioctlf                   4
#define __NR64RC_ksigreturn               0
#define __NR64RC_openpty                  5
#define __NR64RC_rpc_schedule             5
#define __NR64RC_frealpathat              5
#define __NR64RC_frealpath4               4
#define __NR64RC_getdrives                0
#define __NR64RC_detach                   1
#define __NR64RC_readf                    4
#define __NR64RC_klstat                   2
#define __NR64RC_kfstat                   2
#define __NR64RC_kstat                    2
#define __NR64RC_writef                   4
#endif /* !__NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#endif /* __WANT_SYSCALL_REGISTER_COUNT */


/************************************************************************/
/* SYSCALL DOUBLE WIDE RETURN VALUE                                     */
/************************************************************************/
#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN
#ifndef __NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#define __NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#endif /* !__NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN */
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN */


