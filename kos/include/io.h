/* HASH CRC-32:0x3054aa0a */
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
/* (#) Portability: Cygwin       (/winsup/cygwin/include/io.h) */
/* (#) Portability: DJGPP        (/include/io.h) */
/* (#) Portability: EMX kLIBC    (/libc/include/io.h) */
/* (#) Portability: MSVC         (/include/io.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/io.h) */
/* (#) Portability: NetBSD       (/sys/arch/[...]/include/io.h) */
/* (#) Portability: Windows Kits (/ucrt/io.h) */
#ifndef _IO_H
#define _IO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>


#ifndef _A_NORMAL
#define _A_NORMAL 0x00
#define _A_RDONLY 0x01
#define _A_HIDDEN 0x02
#define _A_SYSTEM 0x04
#define _A_SUBDIR 0x10
#define _A_ARCH   0x20
#endif /* !_A_NORMAL */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef _FSIZE_T_DEFINED
#define _FSIZE_T_DEFINED
typedef __UINT32_TYPE__ _fsize_t;
#endif /* _FSIZE_T_DEFINED */

struct _finddata32_t;
struct __finddata64_t; /* I guess something else is already using the more obvious choice... */
struct _finddata32i64_t;
struct _finddata64i32_t;

#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */

#ifndef __remove_defined
#define __remove_defined
#ifdef __std_remove_defined
/* >> remove(3)
 * Remove a file or directory `filename' */
__NAMESPACE_STD_USING(remove)
#elif defined(__CRT_HAVE_remove)
/* >> remove(3)
 * Remove a file or directory `filename' */
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,remove,(char const *__filename),(__filename))
#else /* ... */
#include <asm/os/errno.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))) || (defined(__EISDIR) && defined(__ENOTDIR) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))))
#include <libc/local/stdio/remove.h>
/* >> remove(3)
 * Remove a file or directory `filename' */
__NAMESPACE_LOCAL_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remove))(__filename); })
#else /* (__AT_FDCWD && (__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR))))) || (__EISDIR && __ENOTDIR && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat))) */
#undef __remove_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR))))) && (!__EISDIR || !__ENOTDIR || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || (!__CRT_HAVE_rmdir && !__CRT_HAVE__rmdir && !__CRT_HAVE___rmdir && !__CRT_HAVE___libc_rmdir && (!__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat))) */
#endif /* !... */
#endif /* !__remove_defined */
#ifndef __rename_defined
#define __rename_defined
#ifdef __std_rename_defined
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__NAMESPACE_STD_USING(rename)
#elif defined(__CRT_HAVE_rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CDECLARE(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),__rename,(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___libc_rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),__libc_rename,(__oldname,__newname_or_path))
#elif defined(__AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2))
#include <libc/local/stdio/rename.h>
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rename))(__oldname, __newname_or_path); })
#else /* ... */
#undef __rename_defined
#endif /* !... */
#endif /* !__rename_defined */
#ifndef __unlink_defined
#define __unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* ... */
#undef __unlink_defined
#endif /* !... */
#endif /* !__unlink_defined */
#ifndef __open_defined
#define __open_defined
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__LIBC __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open");
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/fcntl/open.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(open, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))(__filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define open(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __open_defined
#endif /* !... */
#endif /* !__open_defined */
#ifndef __creat_defined
#define __creat_defined
#if defined(__CRT_HAVE_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE___creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),__creat,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),__libc_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat64)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))
#include <libc/local/fcntl/creat.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(creat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__LIBCCALL creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); })
#else /* ... */
#undef __creat_defined
#endif /* !... */
#endif /* !__creat_defined */
#ifndef __access_defined
#define __access_defined
#ifdef __CRT_HAVE_access
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#elif defined(__CRT_HAVE___access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),__access,(__file,__type))
#elif defined(__CRT_HAVE___libc_access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),__libc_access,(__file,__type))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/access.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__NAMESPACE_LOCAL_USING_OR_IMPL(access, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL access)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__file, __type); })
#else /* ... */
#undef __access_defined
#endif /* !... */
#endif /* !__access_defined */
#ifndef __chmod_defined
#define __chmod_defined
#ifdef __CRT_HAVE_chmod
/* >> chmod(2) */
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#elif defined(__CRT_HAVE___chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),__chmod,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),__libc_chmod,(__filename,__mode))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_fchmodat)
#include <libc/local/sys.stat/chmod.h>
/* >> chmod(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(chmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL chmod)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chmod))(__filename, __mode); })
#else /* ... */
#undef __chmod_defined
#endif /* !... */
#endif /* !__chmod_defined */
#ifndef __close_defined
#define __close_defined
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CDECLARE(,int,__NOTHROW_NCX,close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __close_defined
#endif /* !... */
#endif /* !__close_defined */
#ifndef __dup_defined
#define __dup_defined
#ifdef __CRT_HAVE_dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),_dup,(__fd))
#elif defined(__CRT_HAVE___dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),__dup,(__fd))
#elif defined(__CRT_HAVE___libc_dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),__libc_dup,(__fd))
#else /* ... */
#undef __dup_defined
#endif /* !... */
#endif /* !__dup_defined */
#ifndef __dup2_defined
#define __dup2_defined
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __dup2_defined
#endif /* !... */
#endif /* !__dup2_defined */
#ifndef __isatty_defined
#define __isatty_defined
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
#include <libc/local/unistd/isatty.h>
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__NAMESPACE_LOCAL_USING_OR_IMPL(isatty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isatty)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isatty))(__fd); })
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#undef __isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA) */
#endif /* !... */
#endif /* !__isatty_defined */
#ifndef __lseek_defined
#define __lseek_defined
#if defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/unistd/lseek.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek, __FORCELOCAL __ATTR_ARTIFICIAL __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL lseek)(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(__fd, __offset, __whence); })
#else /* ... */
#undef __lseek_defined
#endif /* !... */
#endif /* !__lseek_defined */
#ifndef __mktemp_defined
#define __mktemp_defined
#ifdef __CRT_HAVE_mktemp
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CDECLARE(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,mktemp,(char *__template_),__mktemp,(__template_))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
#include <libc/local/stdlib/mktemp.h>
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_ACCESS_RW(1) char *__NOTHROW_NCX(__LIBCCALL mktemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktemp))(__template_); })
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#undef __mktemp_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_stat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) */
#endif /* !... */
#endif /* !__mktemp_defined */
#ifndef __umask_defined
#define __umask_defined
#ifdef __CRT_HAVE_umask
/* >> umask(2) */
__CDECLARE(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE__umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),_umask,(__mode))
#elif defined(__CRT_HAVE___umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),__umask,(__mode))
#elif defined(__CRT_HAVE___libc_umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),__libc_umask,(__mode))
#else /* ... */
#undef __umask_defined
#endif /* !... */
#endif /* !__umask_defined */
#ifndef __read_defined
#define __read_defined
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __read_defined
#endif /* !... */
#endif /* !__read_defined */
#ifndef __write_defined
#define __write_defined
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __write_defined
#endif /* !... */
#endif /* !__write_defined */
#ifdef __CRT_HAVE_access
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_access,(char const *__file, __STDC_INT_AS_UINT_T __type),access,(__file,__type))
#elif defined(__CRT_HAVE__access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_access,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE___access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__access,(__file,__type))
#elif defined(__CRT_HAVE___libc_access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__libc_access,(__file,__type))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/access.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL _access)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__file, __type); }
#endif /* ... */
#if defined(__CRT_HAVE_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE___creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),__creat,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),__libc_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat64)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))
#include <libc/local/fcntl/creat.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__LIBCCALL _creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); }
#endif /* ... */
#ifdef __CRT_HAVE_chmod
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),chmod,(__filename,__mode))
#elif defined(__CRT_HAVE__chmod)
/* >> chmod(2) */
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE___chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),__chmod,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),__libc_chmod,(__filename,__mode))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_fchmodat)
#include <libc/local/sys.stat/chmod.h>
/* >> chmod(2) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL _chmod)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chmod))(__filename, __mode); }
#endif /* ... */
#ifdef __CRT_HAVE__access_s
__CDECLARE(__ATTR_ACCESS_RO(1),errno_t,__NOTHROW_RPC,_access_s,(char const *__filename, __STDC_INT_AS_UINT_T __type),(__filename,__type))
#elif defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))
#include <libc/local/io/_access_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_access_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) errno_t __NOTHROW_RPC(__LIBCCALL _access_s)(char const *__filename, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_access_s))(__filename, __type); })
#endif /* ... */
#if defined(__CRT_HAVE_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#include <libc/local/unistd/ftruncate.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _chsize)(__fd_t __fd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, __length); }
#endif /* ... */
#if defined(__CRT_HAVE_ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE(,int,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __PIO_OFFSET64 __length),(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#include <libc/local/unistd/ftruncate64.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _chsize_s)(__fd_t __fd, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))(__fd, __length); }
#endif /* ... */
#ifdef __CRT_HAVE_fsync
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),fsync,(__fd))
#elif defined(__CRT_HAVE__commit)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CDECLARE(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___fsync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),__fsync,(__fd))
#elif defined(__CRT_HAVE___libc_fsync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),__libc_fsync,(__fd))
#elif defined(__CRT_HAVE_fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),fdatasync,(__fd))
#elif defined(__CRT_HAVE___fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),__fdatasync,(__fd))
#else /* ... */
#include <libc/local/unistd/fsync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL _commit)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsync))(__fd); }
#endif /* !... */
#if defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/unistd/lseek.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__FORCELOCAL __ATTR_ARTIFICIAL __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL _lseek)(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(__fd, __offset, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/unistd/lseek64.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__FORCELOCAL __ATTR_ARTIFICIAL __off64_t __NOTHROW_NCX(__LIBCCALL _lseeki64)(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))(__fd, __offset, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_lockf) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL _locking)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); }
#endif /* ... */
#ifndef ___unlink_defined
#define ___unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,_unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL _unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); }
#else /* ... */
#undef ___unlink_defined
#endif /* !... */
#endif /* !___unlink_defined */
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CDECLARE(,int,__NOTHROW_NCX,_close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,_close,(__fd_t __fd),__libc_close,(__fd))
#endif /* ... */
#ifdef __CRT_HAVE_dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),dup,(__fd))
#elif defined(__CRT_HAVE__dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),__dup,(__fd))
#elif defined(__CRT_HAVE___libc_dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),__libc_dup,(__fd))
#endif /* ... */
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#endif /* ... */
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),__libc_read,(__fd,__buf,__bufsize))
#endif /* ... */
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),__libc_write,(__fd,__buf,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__LIBC __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL _open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("_open");
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
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
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/fcntl/open.h>
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
#define _open(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE_umask
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),umask,(__mode))
#elif defined(__CRT_HAVE__umask)
/* >> umask(2) */
__CDECLARE(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE___umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),__umask,(__mode))
#elif defined(__CRT_HAVE___libc_umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),__libc_umask,(__mode))
#endif /* ... */
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
#include <libc/local/unistd/isatty.h>
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isatty)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isatty))(__fd); }
#endif /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#endif /* !... */
#ifdef __CRT_HAVE_mktemp
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,_mktemp,(char *__template_),mktemp,(__template_))
#elif defined(__CRT_HAVE__mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CDECLARE(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,_mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE___mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,_mktemp,(char *__template_),__mktemp,(__template_))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
#include <libc/local/stdlib/mktemp.h>
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_ACCESS_RW(1) char *__NOTHROW_NCX(__LIBCCALL _mktemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktemp))(__template_); }
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#endif /* !... */
#ifdef __CRT_HAVE__umask_s
__CDECLARE(__ATTR_ACCESS_WR(2),errno_t,__NOTHROW_NCX,_umask_s,(__mode_t __nmode, __mode_t *__omode),(__nmode,__omode))
#elif defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask) || defined(__CRT_HAVE___umask) || defined(__CRT_HAVE___libc_umask)
#include <libc/local/io/_umask_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_umask_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(2) errno_t __NOTHROW_NCX(__LIBCCALL _umask_s)(__mode_t __nmode, __mode_t *__omode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_umask_s))(__nmode, __omode); })
#endif /* ... */
#ifdef __CRT_HAVE__setmode
__CDECLARE(,__oflag_t,__NOTHROW_NCX,_setmode,(__fd_t __fd, __oflag_t __mode),(__fd,__mode))
#elif (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && (defined(__F_SETFL_XCH) || (defined(__F_GETFL) && defined(__F_SETFL)))
#include <libc/local/io/_setmode.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_setmode, __FORCELOCAL __ATTR_ARTIFICIAL __oflag_t __NOTHROW_NCX(__LIBCCALL _setmode)(__fd_t __fd, __oflag_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_setmode))(__fd, __mode); })
#endif /* ... */


#if !defined(___findclose_defined) && defined(__CRT_HAVE__findclose)
#define ___findclose_defined
__CDECLARE(,int,__NOTHROW_NCX,_findclose,(intptr_t __findfd),(__findfd))
#endif /* !___findclose_defined && __CRT_HAVE__findclose */
#ifdef __CRT_HAVE__findfirst32
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst32,(char const *__restrict __filename, struct _finddata32_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst32,(char const *__restrict __filename, struct _finddata32_t *__restrict __finddata),_findfirst,(__filename,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__findfirst32i64
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst32i64,(char const *__restrict __filename, struct _finddata32i64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirsti64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst32i64,(char const *__restrict __filename, struct _finddata32i64_t *__restrict __finddata),_findfirsti64,(__filename,__finddata))
#endif /* ... */
#ifndef ___findfirst64_defined
#define ___findfirst64_defined
#ifdef __CRT_HAVE__findfirst64
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst64,(char const *__restrict __filename, struct __finddata64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst64i32)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst64,(char const *__restrict __filename, struct __finddata64_t *__restrict __finddata),_findfirst64i32,(__filename,__finddata))
#else /* ... */
#undef ___findfirst64_defined
#endif /* !... */
#endif /* !___findfirst64_defined */
#ifndef ___findfirst64i32_defined
#define ___findfirst64i32_defined
#ifdef __CRT_HAVE__findfirst64
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst64i32,(char const *__restrict __filename, struct _finddata64i32_t *__restrict __finddata),_findfirst64,(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst64i32)
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),intptr_t,__NOTHROW_RPC,_findfirst64i32,(char const *__restrict __filename, struct _finddata64i32_t *__restrict __finddata),(__filename,__finddata))
#else /* ... */
#undef ___findfirst64i32_defined
#endif /* !... */
#endif /* !___findfirst64i32_defined */
#ifdef __CRT_HAVE__findnext32
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext32,(intptr_t __findfd, struct _finddata32_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext)
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext32,(intptr_t __findfd, struct _finddata32_t *__restrict __finddata),_findnext,(__findfd,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__findnext32i64
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext32i64,(intptr_t __findfd, struct _finddata32i64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnexti64)
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext32i64,(intptr_t __findfd, struct _finddata32i64_t *__restrict __finddata),_findnexti64,(__findfd,__finddata))
#endif /* ... */
#ifndef ___findnext64_defined
#define ___findnext64_defined
#ifdef __CRT_HAVE__findnext64
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext64,(intptr_t __findfd, struct __finddata64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext64i32)
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext64,(intptr_t __findfd, struct __finddata64_t *__restrict __finddata),_findnext64i32,(__findfd,__finddata))
#else /* ... */
#undef ___findnext64_defined
#endif /* !... */
#endif /* !___findnext64_defined */
#ifndef ___findnext64i32_defined
#define ___findnext64i32_defined
#ifdef __CRT_HAVE__findnext64
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext64i32,(intptr_t __findfd, struct _finddata64i32_t *__restrict __finddata),_findnext64,(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext64i32)
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_RPC,_findnext64i32,(intptr_t __findfd, struct _finddata64i32_t *__restrict __finddata),(__findfd,__finddata))
#else /* ... */
#undef ___findnext64i32_defined
#endif /* !... */
#endif /* !___findnext64i32_defined */

#ifdef __CRT_HAVE__sopen_s
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),errno_t,__NOTHROW_RPC,_sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__sopen_s_nolock)
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),errno_t,__NOTHROW_RPC,_sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s_nolock,(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/io/_sopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_sopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) errno_t __NOTHROW_RPC(__LIBCCALL _sopen_s)(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sopen_s))(__fd, __filename, __oflags, __sflags, __mode); })
#endif /* ... */
#ifdef __CRT_HAVE__sopen_s
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),errno_t,__NOTHROW_RPC,_sopen_s_nolock,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s,(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__sopen_s_nolock)
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),errno_t,__NOTHROW_RPC,_sopen_s_nolock,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/io/_sopen_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) errno_t __NOTHROW_RPC(__LIBCCALL _sopen_s_nolock)(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sopen_s))(__fd, __filename, __oflags, __sflags, __mode); }
#endif /* ... */
#ifdef __CRT_HAVE__sopen_dispatch
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(5),errno_t,__NOTHROW_RPC,_sopen_dispatch,(char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode, __fd_t *__fd, int __bsecure),(__filename,__oflags,__sflags,__mode,__fd,__bsecure))
#elif defined(__CRT_HAVE__sopen_s) || defined(__CRT_HAVE__sopen_s_nolock) || defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/io/_sopen_dispatch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_sopen_dispatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(5) errno_t __NOTHROW_RPC(__LIBCCALL _sopen_dispatch)(char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode, __fd_t *__fd, int __bsecure) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sopen_dispatch))(__filename, __oflags, __sflags, __mode, __fd, __bsecure); })
#endif /* ... */
__CDECLARE_OPT(__ATTR_ACCESS_RWS(1, 2),errno_t,__NOTHROW_NCX,_mktemp_s,(char *__template_, size_t __size),(__template_,__size))
#ifdef __CRT_HAVE_sopen
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,_sopen,(char const *__filename, __oflag_t __oflags, int __sflags),sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE__sopen)
__LIBC __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL _sopen)(char const *__filename, __oflag_t __oflags, int __sflags, ...) __CASMNAME_SAME("_sopen");
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/io/sopen.h>
#define _sopen(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE__pipe
__CDECLARE(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,_pipe,(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode),(__pipedes,__pipesize,__textmode))
#elif defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe)
#include <libc/local/io/_pipe.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_pipe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) int __NOTHROW_NCX(__LIBCCALL _pipe)(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_pipe))(__pipedes, __pipesize, __textmode); })
#endif /* ... */
#ifdef __CRT_HAVE__eof
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_eof,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/io/eof.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _eof)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eof))(__fd); }
#endif /* ... */
#ifdef __CRT_HAVE__filelength
__CDECLARE(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,_filelength,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/io/filelength.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL _filelength)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(filelength))(__fd); }
#endif /* ... */
#if defined(__CRT_HAVE_tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,_tell,(__fd_t __fd),tell,(__fd))
#elif defined(__CRT_HAVE__tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,_tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_tell64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,_tell,(__fd_t __fd),tell64,(__fd))
#elif defined(__CRT_HAVE__telli64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,_tell,(__fd_t __fd),_telli64,(__fd))
#else /* ... */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL _tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); }
#endif /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR */
#endif /* !... */
#if defined(__CRT_HAVE_tell) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,_telli64,(__fd_t __fd),tell,(__fd))
#elif defined(__CRT_HAVE_tell64)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,_telli64,(__fd_t __fd),tell64,(__fd))
#elif defined(__CRT_HAVE__telli64)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,_telli64,(__fd_t __fd),(__fd))
#else /* ... */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell64.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __off64_t __NOTHROW_NCX(__LIBCCALL _telli64)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell64))(__fd); }
#endif /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR */
#endif /* !... */
#ifdef __CRT_HAVE__filelengthi64
__CDECLARE(__ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW_NCX,_filelengthi64,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE__filelengthi64 */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR) && defined(__SEEK_END) && defined(__SEEK_SET)
#include <libc/local/io/_filelengthi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_filelengthi64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _filelengthi64)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_filelengthi64))(__fd); })
#endif /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR && __SEEK_END && __SEEK_SET */
#endif /* !__CRT_HAVE__filelengthi64 */
#ifdef __CRT_HAVE_umask_s
__CDECLARE(,errno_t,__NOTHROW_NCX,umask_s,(__mode_t __newmode, __mode_t *__oldmode),(__newmode,__oldmode))
#elif defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask) || defined(__CRT_HAVE___umask) || defined(__CRT_HAVE___libc_umask)
#include <libc/local/io/umask_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(umask_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL umask_s)(__mode_t __newmode, __mode_t *__oldmode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umask_s))(__newmode, __oldmode); })
#endif /* ... */
#ifdef __CRT_HAVE___lock_fhandle
__CDECLARE(,int,__NOTHROW_RPC,__lock_fhandle,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE___lock_fhandle */
#include <libc/local/io/__lock_fhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__lock_fhandle, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL __lock_fhandle)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__lock_fhandle))(__fd); })
#endif /* !__CRT_HAVE___lock_fhandle */
#ifdef __CRT_HAVE__unlock_fhandle
__CDECLARE_VOID(,__NOTHROW_NCX,_unlock_fhandle,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE__unlock_fhandle */
#include <libc/local/io/_unlock_fhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_unlock_fhandle, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _unlock_fhandle)(__fd_t __fd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_unlock_fhandle))(__fd); })
#endif /* !__CRT_HAVE__unlock_fhandle */
#ifdef __CRT_HAVE__get_osfhandle
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,intptr_t,__NOTHROW_NCX,_get_osfhandle,(__fd_t __fd),(__fd))
#elif !defined(__CRT_DOS_PRIMARY)
#include <libc/local/io/_get_osfhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_osfhandle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED intptr_t __NOTHROW_NCX(__LIBCCALL _get_osfhandle)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_osfhandle))(__fd); })
#endif /* ... */
#ifdef __CRT_HAVE__open_osfhandle
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_open_osfhandle,(intptr_t __osfd, __oflag_t __flags),(__osfd,__flags))
#elif !defined(__CRT_DOS_PRIMARY)
#include <libc/local/io/_open_osfhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_open_osfhandle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __fd_t __NOTHROW_NCX(__LIBCCALL _open_osfhandle)(intptr_t __osfd, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_open_osfhandle))(__osfd, __flags); })
#endif /* ... */


/* Weird, new functions not apart of any well-established standard. */


/* WARNING: `setmode(3)' is also a completely different BSD-specific function in <unistd.h>! */
#ifndef __setmode_defined
#define __setmode_defined
#ifdef __CRT_HAVE__setmode
__CREDIRECT(,__oflag_t,__NOTHROW_NCX,setmode,(__fd_t __fd, __oflag_t __mode),_setmode,(__fd,__mode))
#elif (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && (defined(__F_SETFL_XCH) || (defined(__F_GETFL) && defined(__F_SETFL)))
#include <libc/local/io/_setmode.h>
__FORCELOCAL __ATTR_ARTIFICIAL __oflag_t __NOTHROW_NCX(__LIBCCALL setmode)(__fd_t __fd, __oflag_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_setmode))(__fd, __mode); }
#else /* ... */
#undef __setmode_defined
#endif /* !... */
#endif /* !__setmode_defined */
#if defined(__CRT_HAVE_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#include <libc/local/unistd/ftruncate.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL chsize)(__fd_t __fd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, __length); }
#endif /* ... */
#if defined(__CRT_HAVE_lockf) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,locking,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL locking)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); }
#endif /* ... */
#ifdef __CRT_HAVE_sopen
__LIBC __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL sopen)(char const *__filename, __oflag_t __oflags, int __sflags, ...) __CASMNAME_SAME("sopen");
#elif defined(__CRT_HAVE__sopen)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,sopen,(char const *__filename, __oflag_t __oflags, int __sflags),_sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/io/sopen.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(sopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t __NOTHROW_RPC(__VLIBCCALL sopen)(char const *__filename, __oflag_t __oflags, int __sflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))(__filename, __oflags, __sflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define sopen(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__filelength
__CREDIRECT(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,filelength,(__fd_t __fd),_filelength,(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/io/filelength.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(filelength, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL filelength)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(filelength))(__fd); })
#endif /* ... */
#ifndef __tell_defined
#define __tell_defined
#if defined(__CRT_HAVE_tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,tell,(__fd_t __fd),_tell,(__fd))
#elif defined(__CRT_HAVE_tell64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,tell,(__fd_t __fd),tell64,(__fd))
#elif defined(__CRT_HAVE__telli64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__FS_TYPE(off),__NOTHROW_NCX,tell,(__fd_t __fd),_telli64,(__fd))
#else /* ... */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(tell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); })
#else /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR */
#undef __tell_defined
#endif /* (!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || !__SEEK_CUR */
#endif /* !... */
#endif /* !__tell_defined */
#ifdef __CRT_HAVE__eof
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,eof,(__fd_t __fd),_eof,(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/io/eof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(eof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL eof)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eof))(__fd); })
#endif /* ... */

#ifndef _FINDDATA_T_DEFINED
#define _FINDDATA_T_DEFINED 1
/* Safely first! */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("attrib")
#pragma push_macro("time_create")
#pragma push_macro("time_access")
#pragma push_macro("time_write")
#pragma push_macro("size")
#pragma push_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef attrib
#undef time_create
#undef time_access
#undef time_write
#undef size
#undef name
struct _finddata32_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	_fsize_t             size;
	char                 name[260];
};
struct _finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	/* Microsoft:
	 * A: "I mean: we could use an unsigned type for this, seeing as how _fsize_t is also unsigned."
	 * B: "Nah! - Lets rather p1$$ off anyone that notices. - That'll be way more fun." */
	__INT64_TYPE__       size;
	char                 name[260];
};
struct _finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__UINT32_TYPE__     _fd64i32_pad; /* Padding made visible */
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char                 name[260];
};
struct __finddata64_t {
	__UINT32_TYPE__      attrib;
	__UINT32_TYPE__     _fd64_pad; /* Padding made visible */
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	__INT64_TYPE__       size;
	char                 name[260];
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("name")
#pragma pop_macro("size")
#pragma pop_macro("time_write")
#pragma pop_macro("time_access")
#pragma pop_macro("time_create")
#pragma pop_macro("attrib")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_TIME_BITS64
#define _finddata_t                       _finddata64i32_t
#define _finddatai64_t                    __finddata64_t
#define _findfirst(filename, finddata)    _findfirst64i32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext64i32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _finddata_t                       _finddata32_t
#define _finddatai64_t                    _finddata32i64_t
#define _findfirst(filename, finddata)    _findfirst32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst32i64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_FINDDATA_T_DEFINED */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wio.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_IO_H */
#endif /* __USE_UTF */

#endif /* !_IO_H */
