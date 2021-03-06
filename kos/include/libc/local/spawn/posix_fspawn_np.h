/* HASH CRC-32:0x5a4ba238 */
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
#ifndef __local_posix_fspawn_np_defined
#define __local_posix_fspawn_np_defined 1
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#include <asm/os/vfork.h>
#if (defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))) || defined(__CRT_HAVE_posix_spawn)
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _Exit from stdlib */
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined 1
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_Exit,{ return __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
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
/* Dependency: closefrom from unistd */
#ifndef __local___localdep_closefrom_defined
#define __local___localdep_closefrom_defined 1
#ifdef __CRT_HAVE_closefrom
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_closefrom,(__fd_t __lowfd),closefrom,(__lowfd))
#else /* __CRT_HAVE_closefrom */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && defined(__F_CLOSEM)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/closefrom.h>
__NAMESPACE_LOCAL_BEGIN
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
#define __localdep_closefrom __LIBC_LOCAL_NAME(closefrom)
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl) && __F_CLOSEM */
#undef __local___localdep_closefrom_defined
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl) || !__F_CLOSEM */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__local___localdep_closefrom_defined */
/* Dependency: crt_posix_spawn from spawn */
#if !defined(__local___localdep_crt_posix_spawn_defined) && defined(__CRT_HAVE_posix_spawn)
#define __local___localdep_crt_posix_spawn_defined 1
__CREDIRECT(__ATTR_NONNULL((1, 2, 5, 6)),__errno_t,__NOTHROW_RPC,__localdep_crt_posix_spawn,(__pid_t *__restrict __pid, char const *__restrict __path, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP),posix_spawn,(__pid,__path,__file_actions,__attrp,___argv,___envp))
#endif /* !__local___localdep_crt_posix_spawn_defined && __CRT_HAVE_posix_spawn */
/* Dependency: dup2 from unistd */
#ifndef __local___localdep_dup2_defined
#define __local___localdep_dup2_defined 1
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
/* Dependency: fexecve from unistd */
#if !defined(__local___localdep_fexecve_defined) && defined(__CRT_HAVE_fexecve)
#define __local___localdep_fexecve_defined 1
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `fd' and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,__localdep_fexecve,(__fd_t __fd, __TARGV, __TENVP),fexecve,(__fd,___argv,___envp))
#endif /* !__local___localdep_fexecve_defined && __CRT_HAVE_fexecve */
/* Dependency: fork from unistd */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined 1
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
/* Dependency: getgid from unistd */
#if !defined(__local___localdep_getgid_defined) && defined(__CRT_HAVE_getgid)
#define __local___localdep_getgid_defined 1
/* >> getgid(2)
 * Return the real group ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),getgid,())
#endif /* !__local___localdep_getgid_defined && __CRT_HAVE_getgid */
/* Dependency: getuid from unistd */
#if !defined(__local___localdep_getuid_defined) && defined(__CRT_HAVE_getuid)
#define __local___localdep_getuid_defined 1
/* >> getuid(2)
 * Return the real user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_getuid,(void),getuid,())
#endif /* !__local___localdep_getuid_defined && __CRT_HAVE_getuid */
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
/* Dependency: pipe2 from unistd */
#ifndef __local___localdep_pipe2_defined
#define __local___localdep_pipe2_defined 1
#ifdef __CRT_HAVE_pipe2
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pipe2,(__fd_t __pipedes[2], __oflag_t __flags),pipe2,(__pipedes,__flags))
#elif defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pipe2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pipe2 __LIBC_LOCAL_NAME(pipe2)
#else /* ... */
#undef __local___localdep_pipe2_defined
#endif /* !... */
#endif /* !__local___localdep_pipe2_defined */
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
/* Dependency: sched_getparam from sched */
#ifndef __local___localdep_sched_getparam_defined
#define __local___localdep_sched_getparam_defined 1
#ifdef __CRT_HAVE_sched_getparam
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___sched_getparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),__sched_getparam,(__pid,__param))
#else /* ... */
#undef __local___localdep_sched_getparam_defined
#endif /* !... */
#endif /* !__local___localdep_sched_getparam_defined */
/* Dependency: sched_setparam from sched */
#if !defined(__local___localdep_sched_setparam_defined) && defined(__CRT_HAVE_sched_setparam)
#define __local___localdep_sched_setparam_defined 1
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),sched_setparam,(__pid,__param))
#endif /* !__local___localdep_sched_setparam_defined && __CRT_HAVE_sched_setparam */
/* Dependency: sched_setscheduler from sched */
#ifndef __local___localdep_sched_setscheduler_defined
#define __local___localdep_sched_setscheduler_defined 1
#ifdef __CRT_HAVE_sched_setscheduler
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___sched_setscheduler)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__sched_setscheduler,(__pid,__policy,__param))
#else /* ... */
#undef __local___localdep_sched_setscheduler_defined
#endif /* !... */
#endif /* !__local___localdep_sched_setscheduler_defined */
/* Dependency: setegid from unistd */
#if !defined(__local___localdep_setegid_defined) && defined(__CRT_HAVE_setegid)
#define __local___localdep_setegid_defined 1
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setegid,(__gid_t __egid),setegid,(__egid))
#endif /* !__local___localdep_setegid_defined && __CRT_HAVE_setegid */
/* Dependency: seteuid from unistd */
#if !defined(__local___localdep_seteuid_defined) && defined(__CRT_HAVE_seteuid)
#define __local___localdep_seteuid_defined 1
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_seteuid,(__uid_t __euid),seteuid,(__euid))
#endif /* !__local___localdep_seteuid_defined && __CRT_HAVE_seteuid */
/* Dependency: setpgid from unistd */
#ifndef __local___localdep_setpgid_defined
#define __local___localdep_setpgid_defined 1
#ifdef __CRT_HAVE_setpgid
/* >> setpgid(2)
 * Change the ID of the process group associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___setpgid)
/* >> setpgid(2)
 * Change the ID of the process group associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),__setpgid,(__pid,__pgid))
#else /* ... */
#undef __local___localdep_setpgid_defined
#endif /* !... */
#endif /* !__local___localdep_setpgid_defined */
/* Dependency: sigaction from signal */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined 1
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
/* >> sigaction(2)
 * Get/Set the action that shall be performed when a
 * signal `signo' must be handled by the calling process.
 * This function will modifiy the caller's kernel-space signal handler descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
/* >> sigaction(2)
 * Get/Set the action that shall be performed when a
 * signal `signo' must be handled by the calling process.
 * This function will modifiy the caller's kernel-space signal handler descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
/* Dependency: sigemptyset from signal */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined 1
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
/* Dependency: sigismember from signal */
#ifndef __local___localdep_sigismember_defined
#define __local___localdep_sigismember_defined 1
#ifdef __CRT_HAVE_sigismember
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#ifdef __KERNEL__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#elif defined(__CRT_HAVE___sigismember)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#ifdef __KERNEL__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#ifdef __KERNEL__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __localdep_sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#endif /* !__local___localdep_sigismember_defined */
/* Dependency: sigprocmask from signal */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined 1
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
/* Change the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific `pthread_sigmask()' function instead, as POSIX
 * states that this function behaves undefined in such scenarios.
 * However, on KOS, `pthread_sigmask()' is simply an alias for this
 * function, and `sigprocmask()' always operates thread-local.
 * Note also that on KOS 2 additional functions `getsigmaskptr()'
 * and `setsigmaskptr()' exist, which can be used to get/set the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
/* Change the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific `pthread_sigmask()' function instead, as POSIX
 * states that this function behaves undefined in such scenarios.
 * However, on KOS, `pthread_sigmask()' is simply an alias for this
 * function, and `sigprocmask()' always operates thread-local.
 * Note also that on KOS 2 additional functions `getsigmaskptr()'
 * and `setsigmaskptr()' exist, which can be used to get/set the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
/* Dependency: sprintf from stdio */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined 1
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
/* Dependency: tcsetpgrp from unistd */
#if !defined(__local___localdep_tcsetpgrp_defined) && defined(__CRT_HAVE_tcsetpgrp)
#define __local___localdep_tcsetpgrp_defined 1
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_tcsetpgrp,(__fd_t __fd, __pid_t __pgrp_id),tcsetpgrp,(__fd,__pgrp_id))
#endif /* !__local___localdep_tcsetpgrp_defined && __CRT_HAVE_tcsetpgrp */
/* Dependency: vfork from unistd */
#ifndef __local___localdep_vfork_defined
#define __local___localdep_vfork_defined 1
#ifdef __CRT_HAVE_vfork
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would include
 *                 the invocation of `atexit(3)' handlers, which would then run in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will only be resumed in case the
 *                 new program image could be loaded successfully. Otherwise,
 *                 the call to `execve(2)' returns normally in the child.
 *                 Other functions from the exec()-family behave the same
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
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),vfork,())
#elif defined(__CRT_HAVE___vfork)
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would include
 *                 the invocation of `atexit(3)' handlers, which would then run in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will only be resumed in case the
 *                 new program image could be loaded successfully. Otherwise,
 *                 the call to `execve(2)' returns normally in the child.
 *                 Other functions from the exec()-family behave the same
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
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__vfork,())
#else /* ... */
#undef __local___localdep_vfork_defined
#endif /* !... */
#endif /* !__local___localdep_vfork_defined */
/* Dependency: waitpid from sys.wait */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined 1
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
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
#include <bits/os/sigaction.h>
#include <libc/errno.h>
#include <asm/os/oflags.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
/* >> posix_fspawn_np(3)
 * Implementation for the fastest possible method of (safely) doing fork(2)+fexecve(2)
 * in order to spawn a new process from the given `execfd' file descriptor.
 * For this purpose, any error that may happen during either the fork(3), the fexecve(2)
 * or any of the numerous additional system calls that may be performed in-between will
 * be returned by this function to the parent process, while the function itself never
 * actually returns in the child process.
 * For this purpose, this function tries to make use of `vfork(2)' in combination
 * with `__ARCH_HAVE_SHARED_VM_VFORK', and if that isn't available, a temporary pipe
 * is used to communicate process initialization errors, as well as to await a successful
 * exec call by using the fact that a successful exec will close all `O_CLOEXEC' files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always have its read immediately return (which is used to indicate success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: execfd:       The file descriptor pointing to the file that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `fexecve(2)'
 * @param: envp:         Same as the `envp' accepted by `fexecve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
__LOCAL_LIBC(posix_fspawn_np) __ATTR_NONNULL((1, 5, 6)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(posix_fspawn_np))(__pid_t *__restrict __pid, __fd_t __execfd, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP) {
#if defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))




	int __status;
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork))
	__fd_t __pipes[2];
	__SSIZE_TYPE__ __temp;
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork) */
	__errno_t __result, __old_errno;
	__pid_t __child;
	__old_errno = __libc_geterrno_or(0);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))
	__libc_seterrno(0);
	__child = __localdep_vfork();
	if (__child == 0)
		goto __do_exec;
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	__result = __libc_geterrno_or(0);
	if (__result != 0) {
		if (__child < 0) {
			/* The vfork() itself failed. */
			__libc_seterrno(__old_errno);
			return __result;
		}
		/* Something within the child failed after vfork(). */
		goto __err_join_zombie_child;
	}
	/* Restore the old errno */
	__libc_seterrno(__old_errno);
	/* Write back the child's PID */
	*__pid = __child;
	return __result;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork) */
	/* Create a pair of pipes for temporary communication. */
	if (__localdep_pipe2(__pipes, __O_CLOEXEC)) {
__err_without_child:
		__result = __libc_geterrno_or(0);
		__libc_seterrno(__old_errno);
		return __result;
	}
	__child = __localdep_fork();
	if (__child == 0)
		goto __do_exec;
	if (__child < 0)
		goto __err_without_child; /* The fork() itself failed. */
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	__localdep_close(__pipes[1]); /* Close the writer. */
	__temp = __localdep_read(__pipes[0], &__result, sizeof(__result));
	__localdep_close(__pipes[0]); /* Close the reader. */
	if (__temp < 0)
		goto __err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (__temp != sizeof(__result)) {
		*__pid = __child;
		__libc_seterrno(__old_errno);
		return 0;
	}
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork) */
__err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join  it, or else it will  be
	 * left dangling as a zombie process! */
	if (__localdep_waitpid(__child, &__status, 0) < 0) {
#ifdef __EINTR
		if (__libc_geterrno() == __EINTR)
			goto __err_join_zombie_child;
#endif /* __EINTR */
	}
	__libc_seterrno(__old_errno);
	return __result;
__do_exec:
	/* Perform additional actions within the child. */
	if (__file_actions) {
		unsigned int __i;
		for (__i = 0; __i < __file_actions->__used; ++__i) {
			struct __spawn_action *__act;
			__act = &__file_actions->__actions[__i];
			switch (__act->__sa_tag) {
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION

#if !defined(__CRT_HAVE_close) && !defined(__CRT_HAVE__close) && !defined(__CRT_HAVE___close)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#else /* !__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close */
			case __POSIX_SPAWN_ACTION_CLOSE:
				/* Close a file handle */
				if __unlikely(__localdep_close(__act->__sa_action.__sa_close_action.__sa_fd))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */


#if !defined(__CRT_HAVE_dup2) && !defined(__CRT_HAVE__dup2) && !defined(__CRT_HAVE___dup2)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#else /* !__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 */
			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if __unlikely(__localdep_dup2(__act->__sa_action.__sa_dup2_action.__sa_oldfd,
				                 __act->__sa_action.__sa_dup2_action.__sa_newfd))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 */


#if (!defined(__CRT_HAVE_open64) && !defined(__CRT_HAVE___open64) && !defined(__CRT_HAVE_open) && !defined(__CRT_HAVE__open) && !defined(__CRT_HAVE___open) && (!defined(__AT_FDCWD) || (!defined(__CRT_HAVE_openat64) && !defined(__CRT_HAVE_openat)))) || (!defined(__CRT_HAVE_dup2) && !defined(__CRT_HAVE__dup2) && !defined(__CRT_HAVE___dup2)) || (!defined(__CRT_HAVE_close) && !defined(__CRT_HAVE__close) && !defined(__CRT_HAVE___close))
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close) */
			case __POSIX_SPAWN_ACTION_OPEN: {
				/* Open a file using `open(2)' */
				__fd_t __tempfd;
				__tempfd = __localdep_open(__act->__sa_action.__sa_open_action.__sa_path,
				              __act->__sa_action.__sa_open_action.__sa_oflag,
				              __act->__sa_action.__sa_open_action.__sa_mode);
				if __unlikely(__tempfd < 0)
					goto __child_error;
				if __likely(__tempfd != __act->__sa_action.__sa_open_action.__sa_fd) {
					if __unlikely(__localdep_dup2(__tempfd, __act->__sa_action.__sa_open_action.__sa_fd))
						goto __child_error;
					__localdep_close(__tempfd);
				}
			}	break;
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close) */


#ifdef __POSIX_SPAWN_ACTION_TCSETPGRP
#ifndef __CRT_HAVE_tcsetpgrp
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_tcsetpgrp */
			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if __unlikely(__localdep_tcsetpgrp(__act->__sa_action.__sa_tcsetpgrp_action.__sa_fd, 0))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_tcsetpgrp */
#endif /* __POSIX_SPAWN_ACTION_TCSETPGRP */


#ifdef __POSIX_SPAWN_ACTION_CLOSEFROM
#if !defined(__CRT_HAVE_closefrom) && ((!defined(__CRT_HAVE_fcntl) && !defined(__CRT_HAVE___fcntl)) || !defined(__F_CLOSEM))
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_closefrom && ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl) || !__F_CLOSEM) */
			case __POSIX_SPAWN_ACTION_CLOSEFROM:
				__localdep_closefrom(__act->__sa_action.__sa_closefrom_action.__sa_fd);
				break;
#endif /* __CRT_HAVE_closefrom || ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl) && __F_CLOSEM) */
#endif /* __POSIX_SPAWN_ACTION_CLOSEFROM */


#ifdef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
			default:
#ifdef __ENOSYS
				__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
				__libc_seterrno(__EPERM);
#else /* ... */
				__libc_seterrno(1);
#endif /* !... */
				goto __child_error;
#else /* __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			default:
				__builtin_unreachable();
#endif /* !__POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			}
		}
	}
	if (__attrp) {
		if (__attrp->__flags & __POSIX_SPAWN_RESETIDS) {
#if (defined(__CRT_HAVE_seteuid) && defined(__CRT_HAVE_getuid)) || (defined(__CRT_HAVE_setegid) && defined(__CRT_HAVE_getgid))
#if defined(__CRT_HAVE_seteuid) && defined(__CRT_HAVE_getuid)
			if (__localdep_seteuid(__localdep_getuid()))
				goto __child_error;
#endif /* __CRT_HAVE_seteuid && __CRT_HAVE_getuid */
#if defined(__CRT_HAVE_setegid) && defined(__CRT_HAVE_getgid)
			if (__localdep_setegid(__localdep_getgid()))
				goto __child_error;
#endif /* __CRT_HAVE_setegid && __CRT_HAVE_getgid */
#else /* (__CRT_HAVE_seteuid && __CRT_HAVE_getuid) || (__CRT_HAVE_setegid && __CRT_HAVE_getgid) */
#ifdef __ENOSYS
			__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			__libc_seterrno(__EPERM);
#else /* ... */
			__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_seteuid || !__CRT_HAVE_getuid) && (!__CRT_HAVE_setegid || !__CRT_HAVE_getgid) */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETPGROUP) {
#if defined(__CRT_HAVE_setpgid) || defined(__CRT_HAVE___setpgid)
			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if __unlikely(__localdep_setpgid(0, __attrp->__pgrp))
				goto __child_error;
#else /* __CRT_HAVE_setpgid || __CRT_HAVE___setpgid */
#ifdef __ENOSYS
			__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			__libc_seterrno(__EPERM);
#else /* ... */
			__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* !__CRT_HAVE_setpgid && !__CRT_HAVE___setpgid */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETSIGDEF) {
#if (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)) && defined(__SIG_DFL)
			__signo_t __i;
			struct sigaction __sa;
			__sa.sa_handler = (__sighandler_t)__SIG_DFL;
			__sa.sa_flags   = 0;
			__localdep_sigemptyset(&__sa.sa_mask);
			for (__i = 0; (unsigned int)__i < (unsigned int)(sizeof(__attrp->__sd) / 8); ++__i) {
				if (!__localdep_sigismember(&__attrp->__sd, __i))
					continue;
				if __unlikely(__localdep_sigaction(__i, &__sa, __NULLPTR))
					goto __child_error;
			}
#else /* (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) && __SIG_DFL */
#ifdef __ENOSYS
			__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			__libc_seterrno(__EPERM);
#else /* ... */
			__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) || !__SIG_DFL */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETSIGMASK) {
#if (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask)) && defined(__SIG_SETMASK)
			if __unlikely(__localdep_sigprocmask(__SIG_SETMASK, &__attrp->__ss, __NULLPTR))
				goto __child_error;
#else /* (__CRT_HAVE_sigprocmask || __CRT_HAVE_pthread_sigmask) && __SIG_SETMASK */
#ifdef __ENOSYS
			__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			__libc_seterrno(__EPERM);
#else /* ... */
			__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sigprocmask && !__CRT_HAVE_pthread_sigmask) || !__SIG_SETMASK */
		}
		if (__attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
#if (defined(__CRT_HAVE_sched_setscheduler) || defined(__CRT_HAVE___sched_setscheduler)) && defined(__CRT_HAVE_sched_setparam) && (defined(__CRT_HAVE_sched_getparam) || defined(__CRT_HAVE___sched_getparam))
			int __error;
			if ((__attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) ==
			    /*               */ (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
				__error = __localdep_sched_setscheduler(0, __attrp->__policy, &__attrp->__sp);
			} else if (__attrp->__flags & __POSIX_SPAWN_SETSCHEDPARAM) {
				__error = __localdep_sched_setparam(0, &__attrp->__sp);
			} else {
				struct sched_param __param;
				__error = __localdep_sched_getparam(0, &__param);
				if __likely(__error == 0)
					__error = __localdep_sched_setscheduler(0, __attrp->__policy, &__param);
			}
			if __unlikely(__error)
				goto __child_error;
#else /* (__CRT_HAVE_sched_setscheduler || __CRT_HAVE___sched_setscheduler) && __CRT_HAVE_sched_setparam && (__CRT_HAVE_sched_getparam || __CRT_HAVE___sched_getparam) */
#ifdef __ENOSYS
			__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			__libc_seterrno(__EPERM);
#else /* ... */
			__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sched_setscheduler && !__CRT_HAVE___sched_setscheduler) || !__CRT_HAVE_sched_setparam || (!__CRT_HAVE_sched_getparam && !__CRT_HAVE___sched_getparam) */
		}
	}
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	__localdep_fexecve(__execfd, ___argv, ___envp);
#ifdef __POSIX_SPAWN_NOEXECERR
	if (__attrp && __attrp->__flags & __POSIX_SPAWN_NOEXECERR) {
		/* Suppress the exec error. */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))
		__libc_seterrno(0);
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork) */
	} else
#endif /* __POSIX_SPAWN_NOEXECERR */
	{
__child_error:
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))
		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with  our parent process, the error  reason
		 * will have already  been written  back to  our parent's  VM, so  there's
		 * actually nothing left for us to do, but to simply exit! */
		;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork) */
		/* Write the exec-error back to our parent. */
#ifdef __ENOENT
		__error = __libc_geterrno_or(__ENOENT);
#else /* __ENOENT */
		__error = __libc_geterrno_or(1);
#endif /* !__ENOENT */
		/* Communicate back why this failed. */
		__localdep_write(__pipes[1], &__error, sizeof(__error));
		/* No need to close the pipe, it's auto-closed by the kernel! */
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork) */
	}
	__localdep__Exit(127);
#else /* __POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
	char __buf[32];
	__localdep_sprintf(__buf, "/proc/self/fd/%d", __execfd);
	return __localdep_crt_posix_spawn(__pid, __buf, __file_actions, __attrp, ___argv, ___envp);
#endif /* !__POSIX_SPAWN_USE_KOS || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fspawn_np_defined
#define __local___localdep_posix_fspawn_np_defined 1
#define __localdep_posix_fspawn_np __LIBC_LOCAL_NAME(posix_fspawn_np)
#endif /* !__local___localdep_posix_fspawn_np_defined */
#else /* (__POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)) || __CRT_HAVE_posix_spawn */
#undef __local_posix_fspawn_np_defined
#endif /* (!__POSIX_SPAWN_USE_KOS || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid)) && !__CRT_HAVE_posix_spawn */
#endif /* !__local_posix_fspawn_np_defined */
