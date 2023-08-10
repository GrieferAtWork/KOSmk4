/* HASH CRC-32:0xb1297496 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_FCNTL_H
#define _KOS_FCNTL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <fcntl.h>
#include <kos/anno.h>
#include <asm/os/oflags.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_Fcntl
__LIBC __ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T (__VLIBCCALL Fcntl)(__fd_t __fd, int __cmd, ...) __THROWS(...) __CASMNAME_SAME("Fcntl");
#endif /* __CRT_HAVE_Fcntl */
#if defined(__CRT_HAVE_Open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__VLIBCCALL Open)(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) __CASMNAME_SAME("Open");
#elif defined(__CRT_HAVE_Open64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Open,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <libc/local/kos.fcntl/Open.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Open, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__VLIBCCALL Open)(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open))(__filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Open(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#endif /* !... */
#if defined(__CRT_HAVE_Creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE_Creat64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Creat,(char const *__filename, __mode_t __mode),Creat64,(__filename,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <libc/local/kos.fcntl/Creat.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Creat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__LIBCCALL Creat)(char const *__filename, __mode_t __mode) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Creat))(__filename, __mode); })
#endif /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#endif /* !... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_Open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Open64,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_Open64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__VLIBCCALL Open64)(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) __CASMNAME_SAME("Open64");
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <libc/local/kos.fcntl/Open64.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Open64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__VLIBCCALL Open64)(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open64))(__filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Open64(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open64))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#endif /* !... */
#if defined(__CRT_HAVE_Creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Creat64,(char const *__filename, __mode_t __mode),Creat,(__filename,__mode))
#elif defined(__CRT_HAVE_Creat64)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),Creat64,(char const *__filename, __mode_t __mode),(__filename,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <libc/local/kos.fcntl/Creat64.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Creat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t (__LIBCCALL Creat64)(char const *__filename, __mode_t __mode) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Creat64))(__filename, __mode); })
#endif /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_OpenAt) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __fd_t (__VLIBCCALL OpenAt)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) __CASMNAME_SAME("OpenAt");
#elif defined(__CRT_HAVE_OpenAt64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),OpenAt,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt)
#include <libc/local/kos.fcntl/OpenAt.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(OpenAt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __fd_t (__VLIBCCALL OpenAt)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt))(__dirfd, __filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define OpenAt(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_OpenAt) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __fd_t (__VLIBCCALL OpenAt64)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) __CASMNAME_SAME("OpenAt64");
#elif defined(__CRT_HAVE_OpenAt)
#include <libc/local/kos.fcntl/OpenAt64.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
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
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(OpenAt64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __fd_t (__VLIBCCALL OpenAt64)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt64))(__dirfd, __filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define OpenAt64(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt64))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_FCNTL_H */
