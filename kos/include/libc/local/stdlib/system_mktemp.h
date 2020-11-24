/* HASH CRC-32:0x87a69117 */
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
#ifndef __local_system_mktemp_defined
#define __local_system_mktemp_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: close from unistd */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
/* Dependency: getpid from unistd */
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined 1
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
/* Dependency: gettid from unistd */
#if !defined(__local___localdep_gettid_defined) && defined(__CRT_HAVE_gettid)
#define __local___localdep_gettid_defined 1
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),gettid,())
#endif /* !__local___localdep_gettid_defined && __CRT_HAVE_gettid */
/* Dependency: gettimeofday from sys.time */
#ifndef __local___localdep_gettimeofday_defined
#define __local___localdep_gettimeofday_defined 1
#if defined(__CRT_HAVE_gettimeofday64) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gettimeofday __LIBC_LOCAL_NAME(gettimeofday)
#else /* ... */
#undef __local___localdep_gettimeofday_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday_defined */
/* Dependency: gettimeofday64 from sys.time */
#ifndef __local___localdep_gettimeofday64_defined
#define __local___localdep_gettimeofday64_defined 1
#ifdef __CRT_HAVE_gettimeofday64
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gettimeofday64 __LIBC_LOCAL_NAME(gettimeofday64)
#else /* ... */
#undef __local___localdep_gettimeofday64_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday64_defined */
/* Dependency: memcmp from string */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined 1
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
/* Dependency: mkdir from sys.stat */
#ifndef __local___localdep_mkdir_defined
#define __local___localdep_mkdir_defined 1
#ifdef __CRT_HAVE_mkdir
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),mkdir,(__pathname,__mode))
#elif defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdir __LIBC_LOCAL_NAME(mkdir)
#else /* ... */
#undef __local___localdep_mkdir_defined
#endif /* !... */
#endif /* !__local___localdep_mkdir_defined */
/* Dependency: open from fcntl */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
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
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local___localdep_open_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__local___localdep_open_defined */
/* Dependency: rand from stdlib */
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined 1
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#elif defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rand __LIBC_LOCAL_NAME(rand)
#endif /* !... */
#endif /* !__local___localdep_rand_defined */
/* Dependency: stat from sys.stat */
#ifndef __local___localdep_stat_defined
#define __local___localdep_stat_defined 1
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#else /* ... */
#undef __local___localdep_stat_defined
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
/* Dependency: strend from string */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __string),strend,(__string))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR + strlen(STR)' */
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/os/oflags.h>
#include <asm/crt/stdio.h>
#include <bits/os/timeval.h>
#include <bits/os/stat.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
/* Internal implementation for creating temporary files.
 * @param: what: Select what kind of temporary object to create.
 *                  `0': Create a temporary file. (The handle of that file will be returned)
 *                       Creating mode used is 0600
 *                       This mode is only recognized when `$has_function(open)'
 *                  `1': Create a temporary directory. (0 is returned on success)
 *                       Creating mode used is 0700
 *                       This mode is only recognized when `$has_function(mkdir)'
 *                       NOTE: `flags' is ignored in this mode
 *                  `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
 *                       file. Instead, return `0' on success
 *                       This mode is only recognized when `$has_function(open) || $has_function(stat)'
 *                       NOTE: `flags' is ignored in this mode */
__LOCAL_LIBC(system_mktemp) __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(system_mktemp))(unsigned int __what, char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags) {
	/* Selection of random letters which may appear as replacements for XXXXXX
	 * For this purpose, only use lower-case letters, as well as digits.
	 * We could also use upper-case letters, but that may not work correctly
	 * depending on the calling process running in DOS-mode, or flags containing
	 * O_DOSPATH... */
	static char const __letters[] = "abcdefghijklmnopqrstuvwxyz0123456789";
#define __NUM_LETTERS 36
	char *__xloc = __localdep_strend(__template_) - (__suffixlen + 6);
	__UINT32_TYPE__ __seed, __overflow;
	__SIZE_TYPE__ __i, __attempt;
	__fd_t __result;
	/* Verify the validity of the input template. */
	if __unlikely(__xloc < __template_ || __localdep_memcmp(__xloc, "XXXXXX", 6 * sizeof(char)) != 0) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	/* Calculate an initial, random seed.
	 * For this purpose, try to make use of:
	 *   - gettimeofday()
	 *   - gettid() or getpid()
	 *   - rand() */
	__attempt = 0;
__again:
	{
#if (defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
		struct __timeval64 __tv;
		if (__localdep_gettimeofday64(&__tv, __NULLPTR) == 0) {
			__seed = (__UINT32_TYPE__)(__tv.tv_sec) ^
			       (__UINT32_TYPE__)(__tv.tv_sec >> 32) ^
			       (__UINT32_TYPE__)(__tv.tv_usec << 12); /* The max value is 0xf423f, so shift
			                                        * that to become `0xf423f000', thus
			                                        * filling in the upper bits of `seed' */
		} else
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
		struct timeval __tv;
		if (__localdep_gettimeofday(&__tv, __NULLPTR) == 0) {
			__seed = (__UINT32_TYPE__)(__tv.tv_sec) ^
#if __SIZEOF_TIME_T__ > 4
			       (__UINT32_TYPE__)(__tv.tv_sec >> 32) ^
#endif /* __SIZEOF_TIME_T__ > 4 */
			       (__UINT32_TYPE__)(__tv.tv_usec << 12); /* The max value is 0xf423f, so shift
			                                        * that to become `0xf423f000', thus
			                                        * filling in the upper bits of `seed' */
		} else
#endif /* ... */
		{
			__UINT32_TYPE__ __sum;
#ifdef __RAND_MAX
#define __LIBC_RAND_MAX __RAND_MAX
#else /* __RAND_MAX */
#define __LIBC_RAND_MAX 0x7fff
#endif /* !__RAND_MAX */
			__seed = __sum = 0;
			/* Generate at least 32 bits of random data. */
			do {
				__seed *= __LIBC_RAND_MAX;
				__seed += (__UINT32_TYPE__)__localdep_rand();
			} while (!__hybrid_overflow_uadd(__sum, __LIBC_RAND_MAX, &__sum));
#undef __LIBC_RAND_MAX
		}
	}
#ifdef __CRT_HAVE_gettid
	__seed ^= __localdep_gettid();
#elif defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)
	__seed ^= __localdep_getpid();
#endif /* ... */

	/* Using the seed, generate some initial random data.
	 * We've generated 32 bits of entropy above, and with
	 * a total of 6 characters to generate from a pool of
	 * 36 letters each, this 5.333(rep) bits per digit. */
	__overflow = __seed >> 30;
	for (__i = 0; __i < 6; ++__i) {
		unsigned int __digit;
	    __digit = __seed & 0x1f;                      /* digit in 0-31 */
		__digit += __overflow & ((1 << (__i & 3)) - 1); /* Add a random addend between 0-7 */
		/* Right now, digit in 0-38. But because we're using 2 addend, `0' is less
		 * likely than the other digits. As such, subtract a bit if we're not at 0
		 * already. */
		if (__digit)
			--__digit;
		if (__digit)
			--__digit;
		/* Now, digit in 0-36, but 36 itself would still be invalid. */
		if (__digit > 35)
			__digit = 35;
		/* All right! we've got the digit. */
		__xloc[__i] = __letters[__digit];
		__seed >>= 5;
	}

	/* Try to create/test the file/directory. */
	(void)__flags;
	switch (__what) {

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
	case 0: {
#ifdef __O_RDWR
#ifdef __O_ACCMODE
		__flags &= ~__O_ACCMODE;
#endif /* __O_ACCMODE */
		__flags |= __O_RDWR;
#endif /* __O_RDWR */
#ifdef __O_CREAT
		__flags |= __O_CREAT;
#endif /* __O_CREAT */
#ifdef __O_EXCL
		__flags |= __O_EXCL;
#endif /* __O_EXCL */
		__result = __localdep_open(__template_, __flags, 0600);
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */

#if defined(__CRT_HAVE_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir))
	case 1:
		__result = __localdep_mkdir(__template_, 0700);
		break;
#endif /* __CRT_HAVE_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) */

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64))
	case 2: {
#if (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64))
		struct stat __st;
		__result = __localdep_stat(__template_, &__st);
#else /* (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat64 && __USE_FILE_OFFSET64) || (__CRT_HAVE_stat && !__USE_FILE_OFFSET64) */
		__result = __localdep_open(__template_,
#ifdef __O_RDONLY
		              __O_RDONLY
#elif defined(__O_RDWR)
		              __O_RDWR
#elif defined(__O_WRONLY)
		              __O_WRONLY
#else /* ... */
		              0
#endif /* !... */
		              ,
		              0600);
#endif /* (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || __USE_FILE_OFFSET64) */
		if (__result < 0) {
			/* File doesn't already exist. */
			__result = 0;
		} else {
			/* File does already exist. */
#if (!defined(__CRT_HAVE_kstat) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE_kstat64) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE__stat64) || !defined(__CRT_DOS_PRIMARY) || !defined(__USE_TIME_BITS64)) && (!defined(__CRT_HAVE__stat64i32) || !defined(__CRT_DOS_PRIMARY) || !defined(__USE_TIME_BITS64)) && (!defined(__CRT_HAVE__stati64) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || !defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat32i64) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || !defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat32) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE_stat64) || !defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE_stat) || defined(__USE_FILE_OFFSET64)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close))
			__localdep_close(__result);
#endif /* (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || __USE_FILE_OFFSET64) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close) */
#ifdef __EEXIST
			__result = __libc_seterrno(__EEXIST);
#else /* __EEXIST */
			__result = __libc_seterrno(1);
#endif /* !__EEXIST */
#define __NEED_do_try_again
			goto __do_try_again;
		}
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat64 && __USE_FILE_OFFSET64) || (__CRT_HAVE_stat && !__USE_FILE_OFFSET64) */

	default: __builtin_unreachable();
	}
	if (__result == -1) {
		/* Only re-attempt if the error was that the file already existed. */
#if defined(__libc_geterrno) && defined(__EEXIST)
		if (__libc_geterrno() == __EEXIST)
#endif /* __libc_geterrno && __EEXIST */
		{
#ifdef __NEED_do_try_again
#undef __NEED_do_try_again
__do_try_again:
#endif /* __NEED_do_try_again */
			/* Limit the max # of attempts */
#ifdef __TMP_MAX
			if (__attempt < __TMP_MAX)
#else /* __TMP_MAX */
			if (__attempt < 238328)
#endif /* !__TMP_MAX */
			{
				++__attempt;
				goto __again;
			}
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined 1
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
#endif /* !__local_system_mktemp_defined */
