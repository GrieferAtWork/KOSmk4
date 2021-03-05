/* HASH CRC-32:0x32e88ceb */
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
#ifndef __local_openat_defined
#define __local_openat_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: openat64 from fcntl */
#ifndef __local___localdep_openat64_defined
#define __local___localdep_openat64_defined 1
#ifdef __CRT_HAVE_openat64
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/openat64.h>
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
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
#define __localdep_openat64 __LIBC_LOCAL_NAME(openat64)
#else /* ... */
#undef __local___localdep_openat64_defined
#endif /* !... */
#endif /* !__local___localdep_openat64_defined */
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open a new file handle to the file specified by `filename'
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
__LOCAL_LIBC(openat) __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(openat))(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
	__result = __localdep_openat64(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_openat_defined
#define __local___localdep_openat_defined 1
#define __localdep_openat __LIBC_LOCAL_NAME(openat)
#endif /* !__local___localdep_openat_defined */
#else /* __CRT_HAVE_openat64 || __CRT_HAVE_openat */
#undef __local_openat_defined
#endif /* !__CRT_HAVE_openat64 && !__CRT_HAVE_openat */
#endif /* !__local_openat_defined */
