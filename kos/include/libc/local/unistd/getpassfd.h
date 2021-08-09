/* HASH CRC-32:0x529a292f */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getpassfd_defined
#define __local_getpassfd_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: close from unistd */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Dependency: isatty from unistd */
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined 1
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/isatty.h>
__NAMESPACE_LOCAL_BEGIN
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#else /* __CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA) */
#undef __local___localdep_isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && (!__CRT_HAVE_ioctl || !__TCGETA) */
#endif /* !... */
#endif /* !__local___localdep_isatty_defined */
/* Dependency: isprint from ctype */
#ifndef __local___localdep_isprint_defined
#define __local___localdep_isprint_defined 1
#if __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint __LIBC_LOCAL_NAME(isprint)
#endif /* !... */
#endif /* !__local___localdep_isprint_defined */
/* Dependency: malloc from stdlib */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
/* Dependency: memcmp from string */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined 1
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
/* Dependency: memcpy from string */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
/* Dependency: memcpyc from string */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined 1
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
/* Dependency: open from fcntl */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_MFILE:                  For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_MFILE:                  For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && !defined(__USE_FILE_OFFSET64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_MFILE:                  For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && !defined(__USE_FILE_OFFSET64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_MFILE:                  For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_MFILE:                  For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local___localdep_open_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__local___localdep_open_defined */
/* Dependency: poll from sys.poll */
#ifndef __local___localdep_poll_defined
#define __local___localdep_poll_defined 1
#ifdef __CRT_HAVE_poll
__NAMESPACE_LOCAL_END
#include <bits/os/pollfd.h>
__NAMESPACE_LOCAL_BEGIN
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_poll,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, int __timeout),poll,(__fds,__nfds,__timeout))
#elif defined(__CRT_HAVE___poll)
__NAMESPACE_LOCAL_END
#include <bits/os/pollfd.h>
__NAMESPACE_LOCAL_BEGIN
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_poll,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, int __timeout),__poll,(__fds,__nfds,__timeout))
#else /* ... */
#undef __local___localdep_poll_defined
#endif /* !... */
#endif /* !__local___localdep_poll_defined */
/* Dependency: raise from signal */
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined 1
#ifdef __CRT_HAVE_raise
/* >> raise(3)
 * Raise a signal within the current thread.
 * In a *-theaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_raise,(__signo_t __signo),raise,(__signo))
#elif (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))) || (defined(__CRT_HAVE_kill) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)))
__NAMESPACE_LOCAL_END
#include <libc/local/signal/raise.h>
__NAMESPACE_LOCAL_BEGIN
/* >> raise(3)
 * Raise a signal within the current thread.
 * In a *-theaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
#define __localdep_raise __LIBC_LOCAL_NAME(raise)
#else /* ... */
#undef __local___localdep_raise_defined
#endif /* !... */
#endif /* !__local___localdep_raise_defined */
/* Dependency: read from unistd */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined 1
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
/* Dependency: tcgetattr from termios */
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined 1
#ifdef __CRT_HAVE_tcgetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcgetattr(3)
 * Get terminal attributes */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#else /* __CRT_HAVE_tcgetattr */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_ioctl) && defined(__TCGETA)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcgetattr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcgetattr(3)
 * Get terminal attributes */
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#else /* __CRT_HAVE_ioctl && __TCGETA */
#undef __local___localdep_tcgetattr_defined
#endif /* !__CRT_HAVE_ioctl || !__TCGETA */
#endif /* !__CRT_HAVE_tcgetattr */
#endif /* !__local___localdep_tcgetattr_defined */
/* Dependency: tcsetattr from termios */
#ifndef __local___localdep_tcsetattr_defined
#define __local___localdep_tcsetattr_defined 1
#ifdef __CRT_HAVE_tcsetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),tcsetattr,(__fd,__optional_actions,__termios_p))
#elif defined(__CRT_HAVE_ioctl)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcsetattr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
#define __localdep_tcsetattr __LIBC_LOCAL_NAME(tcsetattr)
#else /* ... */
#undef __local___localdep_tcsetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcsetattr_defined */
/* Dependency: tolower from ctype */
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),_tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
/* Dependency: toupper from ctype */
#ifndef __local___localdep_toupper_defined
#define __local___localdep_toupper_defined 1
#if __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,(__ch))
#elif defined(__CRT_HAVE__toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),_toupper,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/toupper.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper __LIBC_LOCAL_NAME(toupper)
#endif /* !... */
#endif /* !__local___localdep_toupper_defined */
/* Dependency: write from unistd */
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined 1
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stdio.h>
#include <asm/os/oflags.h>
#include <libc/errno.h>
#include <paths.h>
#include <asm/crt/getpassfd.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <asm/os/signal.h>
#include <bits/os/pollfd.h>
#include <asm/os/poll.h>
#include <libc/strings.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpassfd(3)
 * This function behaves similar to `readpassphrase(3)', but is still
 * quite distinct from that function in how this one behaves, vs. how
 * that other function behaves. In general, this function is a bit more
 * user-friendly, in that it offers more (but different) `flags' to
 * control how the password prompt is generated, with the main advantage
 * of this function being that it implements some "advanced" readline
 * functionality, such as deleting typed characters without relying on
 * the system TTY canonical buffer (which `readpassphrase(3)' needs,
 * since it doesn't include support for _any_ control characters other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally, I prefer this one over `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to `NULL', a dynamically allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL, an [stdin,stdout,stderr] triple
 *                              of files, used for [read,write,beep] operations.
 *                              When `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in seconds) to wait for the
 *                              user to type each character of their password. If
 *                              this timeout expires, fail with `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
__LOCAL_LIBC(getpassfd) __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpassfd))(char const *__prompt, char *__buf, __SIZE_TYPE__ __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds) {
#ifndef __STDIN_FILENO
#define __STDIN_FILENO 0
#endif /* !__STDIN_FILENO */
#ifndef __STDERR_FILENO
#define __STDERR_FILENO 2
#endif /* !__STDERR_FILENO */

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
	__BOOL __heap_buf;
#endif /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
	char *__result;
	__fd_t __default_fds[3];
	__signo_t __interrupt_signo;

	/* Initialize locals. */
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl))
	struct termios __old_ios, __new_ios;
	__localdep_memset(&__old_ios, -1, sizeof(__old_ios));
	__localdep_memset(&__new_ios, -1, sizeof(__new_ios));
#endif /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) */
	__result          = __NULLPTR;
	__interrupt_signo = 0;
	__default_fds[0]  = __STDIN_FILENO;

	/* Allocate a dynamic buffer if none was given by the caller. */
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
	__heap_buf = 0;
	if (!__buf) {
		__buflen = 512;
		__buf = (char *)__localdep_malloc(__buflen * sizeof(char));
		if __unlikely(!__buf) {
			__buflen = 1;
			__buf = (char *)__localdep_malloc(__buflen * sizeof(char));
			if __unlikely(!__buf)
				goto __out;
		}
		__heap_buf = 1;
	} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
	if (__buflen < 1) {
		/* Invalid buffer length */
#ifdef __EINVAL
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		goto __out;
	}

	/* Open input files if not provided by the caller. */
	if (!__fds) {
		__fds = __default_fds;
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#ifdef __O_CLOEXEC
#define __PRIVATE_GETPASSFD_O_CLOEXEC __O_CLOEXEC
#else /* __O_CLOEXEC */
#define __PRIVATE_GETPASSFD_O_CLOEXEC 0
#endif /* !__O_CLOEXEC */
#ifdef __O_CLOFORK
#define __PRIVATE_GETPASSFD_O_CLOFORK __O_CLOFORK
#else /* __O_CLOFORK */
#define __PRIVATE_GETPASSFD_O_CLOFORK 0
#endif /* !__O_CLOFORK */
#ifdef __O_RDWR
#define __PRIVATE_GETPASSFD_O_RDWR __O_RDWR
#else /* __O_RDWR */
#define __PRIVATE_GETPASSFD_O_RDWR 0
#endif /* !__O_RDWR */
#if defined(__O_NONBLOCK) && (defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll))
#define __PRIVATE_GETPASSFD_O_NONBLOCK __O_NONBLOCK
#else /* __O_NONBLOCK && (__CRT_HAVE_poll || __CRT_HAVE___poll) */
#define __PRIVATE_GETPASSFD_O_NONBLOCK 0
#endif /* !__O_NONBLOCK || (!__CRT_HAVE_poll && !__CRT_HAVE___poll) */
#ifdef _PATH_TTY
#define __PRIVATE_GETPASSFD_PATH_TTY _PATH_TTY
#else /* _PATH_TTY */
#define __PRIVATE_GETPASSFD_PATH_TTY "/dev/tty"
#endif /* !_PATH_TTY */
#if __PRIVATE_GETPASSFD_O_NONBLOCK != 0
		__default_fds[2] = __localdep_open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      (__timeout_in_seconds != 0 ? __PRIVATE_GETPASSFD_O_NONBLOCK : 0));
#else /* __PRIVATE_GETPASSFD_O_NONBLOCK != 0 */
		__default_fds[2] = __localdep_open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR);
#endif /* __PRIVATE_GETPASSFD_O_NONBLOCK == 0 */
		if (__default_fds[2] != -1) {
			__default_fds[0] = __default_fds[2];
			__default_fds[1] = __default_fds[2];
		} else
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
		{
			__default_fds[1] = __STDERR_FILENO;
			__default_fds[2] = __STDERR_FILENO;
		}
	}

	/* Load terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl))
	if (__localdep_tcgetattr(__fds[0], &__old_ios) == 0) {
		__localdep_memcpy(&__new_ios, &__old_ios, sizeof(struct termios));

		/* Configure new settings. */
#if defined(__ECHO) || defined(__ECHOK) || defined(__ECHOE) || defined(__ECHOKE) || defined(__ECHOCTL) || defined(__ISIG) || defined(__ICANON)
		__new_ios.c_lflag &= ~(0 |
#ifdef __ECHO
		                       __ECHO |
#endif /* __ECHO */
#ifdef __ECHOK
		                       __ECHOK |
#endif /* __ECHOK */
#ifdef __ECHOE
		                       __ECHOE |
#endif /* __ECHOE */
#ifdef __ECHOKE
		                       __ECHOKE |
#endif /* __ECHOKE */
#ifdef __ECHOCTL
		                       __ECHOCTL |
#endif /* __ECHOCTL */
#ifdef __ISIG
		                       __ISIG |
#endif /* __ISIG */
#ifdef __ICANON
		                       __ICANON
#endif /* __ICANON */
		                       );
#endif /* __ECHO || __ECHOK || __ECHOE || __ECHOKE || __ECHOCTL || __ISIG || __ICANON */

#ifdef __VMIN
		__new_ios.c_cc[__VMIN] = 1;
#endif /* __VMIN */
#ifdef __VTIME
		__new_ios.c_cc[__VTIME] = 0;
#endif /* __VTIME */

#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		if (__localdep_tcsetattr(__fds[0], __TCSAFLUSH | __TCSASOFT, &__new_ios) != 0)
#elif defined(__TCSAFLUSH)
		if (__localdep_tcsetattr(__fds[0], __TCSAFLUSH, &__new_ios) != 0)
#else /* ... */
		if (__localdep_tcsetattr(__fds[0], 0, &__new_ios) != 0)
#endif /* !... */
		{
			goto __out;
		}
	} else {
		if (__flags & __GETPASS_NEED_TTY)
			goto __out; /* tcgetattr() should have already set errno=ENOTTY */
	}
#elif defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))
	if ((__flags & __GETPASS_NEED_TTY) && !__localdep_isatty(__fds[0]))
		goto __out; /* isatty() should have already set errno=ENOTTY */
#endif /* ... */

	/* Print the given prompt */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
	if (__prompt && *__prompt) {
		if (__localdep_write(__fds[1], __prompt, __localdep_strlen(__prompt)) == -1)
			goto __out;
	}
#else /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
	(void)__prompt;
#endif /* !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write */

	/* The actual interpreter loop for the password reader: */
	{
		unsigned char __ch, *__dst, *__bufend;
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl)) && defined(__VLNEXT)
		__BOOL __escape; /* Set to `true' if the next character is escaped. */
		__escape = 0;
#endif /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) && __VLNEXT */
		__dst    = (unsigned char *)__buf;
		__bufend = (unsigned char *)__buf + __buflen - 1;
		for (;;) {

#if defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll)
			if (__timeout_in_seconds != 0) {
				int __status;
				struct pollfd __pfd;
				__pfd.fd      = __fds[0];
#if defined(__POLLIN) && defined(__POLLRDNORM)
				__pfd.events  = __POLLIN | __POLLRDNORM;
#elif defined(__POLLIN)
				__pfd.events  = __POLLIN;
#else /* ... */
				__pfd.events  = 0;
#endif /* !... */
				__status = __localdep_poll(&__pfd, 1, __timeout_in_seconds * 1000);
				if __unlikely(__status == -1)
					goto __out; /* Error... */
				if __unlikely(__status == 0) {
#ifdef __ETIMEDOUT
					__libc_seterrno(__ETIMEDOUT);
#else /* __ETIMEDOUT */
					__libc_seterrno(1);
#endif /* !__ETIMEDOUT */
					goto __out; /* Timeout... */
				}
				/* Assume that data can be read now! */
			}
#else /* __CRT_HAVE_poll || __CRT_HAVE___poll */
			(void)__timeout_in_seconds;
#endif /* !__CRT_HAVE_poll && !__CRT_HAVE___poll */

			/* Actually read the next character. */
			{
				__SSIZE_TYPE__ __status;
				__status = __localdep_read(__fds[0], &__ch, sizeof(__ch));
				if (__status < (__SSIZE_TYPE__)sizeof(char)) {
					if (__status < 0)
						goto __out; /* Error */
#ifdef __VEOF
__handle_eof:
#endif /* __VEOF */
					if (__flags & __GETPASS_FAIL_EOF) {
						/* Error out on regular, old EOF */
#ifdef __ENODATA
						__libc_seterrno(__ENODATA);
#endif /* __ENODATA */
						goto __out;
					}
					break;
				}
			}

#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl)) && defined(__VLNEXT)
			if (__escape) {
				/* Unconditionally add `ch' */
				__escape = 0;
			} else
#endif /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) && __VLNEXT */
			{
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl))
#if !__VDISABLE
#define __PRIVATE_GETPASSFD_CTRL(__index, __defl) \
	(__new_ios.c_cc[__index] != '\0' ? __new_ios.c_cc[__index] : __CTRL(__defl))
#else /* !__VDISABLE */
#define __PRIVATE_GETPASSFD_CTRL(__index, __defl) \
	((__new_ios.c_cc[__index] != '\0' && __new_ios.c_cc[__index] != __VDISABLE) ? __new_ios.c_cc[__index] : __CTRL(__defl))
#endif /* __VDISABLE */

				/* Check for control characters that should be ignored. */
#ifdef __VREPRINT
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VREPRINT, 'R'))
					continue;
#endif /* __VREPRINT */

#ifdef __VSTART
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTART, 'Q'))
					continue;
#endif /* __VSTART */

#ifdef __VSTOP
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTOP, 'S'))
					continue;
#endif /* __VSTOP */

#ifdef __VSTATUS
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTATUS, 'T'))
					continue;
#endif /* __VSTATUS */

#ifdef __VDISCARD
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VDISCARD, 'O'))
					continue;
#endif /* __VDISCARD */

				/* Check for ^V */
#ifdef __VLNEXT
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VLNEXT, 'V')) {
					__escape = 1;
					continue;
				}
#endif /* __VLNEXT */

				/* Both line- and word-kill are treated as a full reset. */
#if defined(__VKILL) || defined(__VWERASE)
				if (
#ifdef __VKILL
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VKILL, 'U')
#endif /* __VKILL */
#if defined(__VKILL) && defined(__VWERASE)
				    ||
#endif /* __VKILL && __VWERASE */
#ifdef __VWERASE
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VWERASE, 'W')
#endif /* __VWERASE */
				    )
				{
					__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
					if (__flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
						while (__dst > (unsigned char *)__buf) {
							if (__localdep_write(__fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto __out;
							--__dst;
						}
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
					__dst = (unsigned char *)__buf;
					continue;
				}
#endif /* __VKILL || __VWERASE */

				/* Check for end-of-file (via ^D) */
#ifdef __VEOF
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VEOF, 'D'))
					goto __handle_eof;
#endif /* __VEOF */

				/* Check for TTY signal characters. */
#if defined(__VINTR) && defined(__SIGINT)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VINTR, 'C')) {
					__interrupt_signo = __SIGINT;
					goto __out;
				}
#endif /* __VINTR && __SIGINT */

#if defined(__VQUIT) && defined(__SIGQUIT)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VQUIT, '\\')) {
					__interrupt_signo = __SIGQUIT;
					goto __out;
				}
#endif /* __VQUIT && __SIGQUIT */

#if (defined(__VSUSP) || defined(__VDSUSP)) && defined(__SIGTSTP)
				if (
#ifdef __VSUSP
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VSUSP, 'Z')
#endif /* __VSUSP */
#if defined(__VSUSP) && defined(__VDSUSP)
				    ||
#endif /* __VSUSP && __VDSUSP */
#ifdef __VDSUSP
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VDSUSP, 'Y')
#endif /* __VDSUSP */
				    ) {
					__interrupt_signo = __SIGTSTP;
					goto __out;
				}
#endif /* (__VSUSP || __VDSUSP) && __SIGTSTP */

				/* Check for custom newline characters. */
#ifdef __VEOL
				if (__new_ios.c_cc[__VEOL] != __VDISABLE && __ch == __new_ios.c_cc[__VEOL])
					break;
#endif /* __VEOL */
#ifdef __VEOL2
				if (__new_ios.c_cc[__VEOL2] != __VDISABLE && __ch == __new_ios.c_cc[__VEOL2])
					break;
#endif /* __VEOL2 */
#endif /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) */

				/* Check for single-character erase (backspace) */
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl)) && defined(__VERASE)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VERASE, 'H'))
#else /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) && __VERASE */
				if (__ch == '\b')
#endif /* (!__CRT_HAVE_tcgetattr && (!__CRT_HAVE_ioctl || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl) || !__VERASE */
				{
					if (__dst > (unsigned char *)__buf) {
						--__dst;
						__libc_explicit_bzero(__dst, sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
						if (__flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
							if (__localdep_write(__fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto __out;
						}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
						continue;
					}
__maybe_beep:
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
					if (!(__flags & __GETPASS_NO_BEEP)) {
						if (__localdep_write(__fds[2], "\7" /*BEL*/, sizeof(char)) == -1)
							goto __out;
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
					continue;
				}

				/* Check for generic newline characters. */
				if (__ch == '\r' || __ch == '\n')
					break;

			} /* if (!escape) */

			/* Special case: _always_ stop when a NUL-character would be appended.
			 * Note  that this is  undocumented behavior, but  is also mirrored by
			 * what is done by NetBSD's implementation in this case. */
			if (__ch == '\0')
				break;

			/* Check if the buffer is full. */
			if (__dst >= __bufend) {
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
				if (__heap_buf) {
					/* Allocate more space. */
					__SIZE_TYPE__ __new_buflen;
					char *__new_buf;
					__new_buflen = __buflen * 2;
					__new_buf = (char *)__localdep_malloc(__new_buflen * sizeof(char));
					if __unlikely(!__new_buf) {
						__new_buflen = __buflen + 1;
						__new_buf = (char *)__localdep_malloc(__new_buflen * sizeof(char));
						if __unlikely(!__new_buf)
							goto __out;
					}
					__localdep_memcpyc(__new_buf, __buf, __buflen, sizeof(char));
					__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
					__localdep_free(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
					__dst    = (unsigned char *)__new_buf + (__SIZE_TYPE__)(__dst - (unsigned char *)__buf);
					__bufend = (unsigned char *)__new_buf + __new_buflen - 1;
					__buf    = __new_buf;
				} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
				{
					if (__flags & __GETPASS_BUF_LIMIT)
						goto __maybe_beep;
					continue;
				}
			}

			/* Deal with special character conversions. */
			if (__flags & __GETPASS_7BIT)
				__ch &= 0x7f;
			if (__flags & __GETPASS_FORCE_LOWER)
				__ch = (unsigned char)__localdep_tolower((char)__ch);
			if (__flags & __GETPASS_FORCE_UPPER)
				__ch = (unsigned char)__localdep_toupper((char)__ch);

			/* Append to the result buffer. */
			*__dst++ = __ch;

#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
			if (__flags & __GETPASS_ECHO_STAR) {
				if (__localdep_write(__fds[1], "*", sizeof(char)) == -1)
					goto __out;
			} else if (__flags & __GETPASS_ECHO) {
				if (!__localdep_isprint((char)__ch))
					__ch = (unsigned char)'?';
				if (__localdep_write(__fds[1], &__ch, sizeof(char)) == -1)
					goto __out;
			}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */

		} /* for (;;) */

		/* If requested to do so by the caller, write a trailing '\n' upon success. */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
		if (__flags & __GETPASS_ECHO_NL) {
			if (__localdep_write(__fds[1], "\n", 1) == -1)
				goto __out;
		}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */

		/* Force NUL-termination of the password buffer. */
		*__dst = '\0';

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
		if (__heap_buf && __dst < __bufend) {
			/* Try to release unused buffer memory. */
			__SIZE_TYPE__ __new_buflen;
			char *__new_buf;
			__new_buflen = (__SIZE_TYPE__)((__dst + 1) - (unsigned char *)__buf);
			__new_buf    = (char *)__localdep_malloc(__new_buflen * sizeof(char));
			if __likely(__new_buf) {
				__localdep_memcpyc(__new_buf, __buf, __new_buflen, sizeof(char));
				__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
				__localdep_free(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
				__buf    = __new_buf;
				__buflen = __new_buflen;
			}
		}
#endif /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */

		/* Indicate success! */
		__result = __buf;
	}
__out:

	/* Restore old terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl))
	if (__localdep_memcmp(&__old_ios, &__new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)__localdep_tcsetattr(__fds[0], __TCSAFLUSH | __TCSASOFT, &__old_ios);
#elif defined(__TCSAFLUSH)
		(void)__localdep_tcsetattr(__fds[0], __TCSAFLUSH, &__old_ios);
#else /* ... */
		(void)__localdep_tcsetattr(__fds[0], 0, &__old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl) */

	/* Close our file handle to /dev/tty */
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	if (__default_fds[0] != __STDIN_FILENO)
		__localdep_close(__default_fds[0]);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */

	/* Error-only cleanup... */
	if (!__result) {

		/* Don't leave a (possibly incomplete) password dangling in-memory! */
		__libc_explicit_bzero(__buf, __buflen * sizeof(char));

		/* Free a dynamically allocated password buffer. */
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
		if (__heap_buf)
			__localdep_free(__buf);
#endif /* (__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_free || __CRT_HAVE_cfree) */

		/* Raise the signal of a given control character, and/or set
		 * `errno'  to indicate that the password-read operation was
		 * interrupted. */
		if (__interrupt_signo != 0) {
#if defined(__CRT_HAVE_raise) || (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))) || (defined(__CRT_HAVE_kill) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)))
			if (!(__flags & __GETPASS_NO_SIGNAL))
				(void)__localdep_raise(__interrupt_signo);
#endif /* __CRT_HAVE_raise || (__CRT_HAVE_pthread_kill && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current)) || (__CRT_HAVE_kill && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid)) */
#ifdef __EINTR
			__libc_seterrno(__EINTR);
#endif /* __EINTR */
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpassfd_defined
#define __local___localdep_getpassfd_defined 1
#define __localdep_getpassfd __LIBC_LOCAL_NAME(getpassfd)
#endif /* !__local___localdep_getpassfd_defined */
#else /* __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read */
#undef __local_getpassfd_defined
#endif /* !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read */
#endif /* !__local_getpassfd_defined */
