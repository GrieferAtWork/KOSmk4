/* HASH CRC-32:0xa4f48df2 */
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
#ifndef GUARD_LIBC_AUTO_KOS_UNISTD_H
#define GUARD_LIBC_AUTO_KOS_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void (VLIBCCALL libc_Execl)(char const *__restrict path, char const *args, ...) THROWS(...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void (VLIBCCALL libc_Execle)(char const *__restrict path, char const *args, ...) THROWS(...);
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void (VLIBCCALL libc_Execpl)(char const *__restrict file, char const *args, ...) THROWS(...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void (VLIBCCALL libc_Execlpe)(char const *__restrict file, char const *args, ...) THROWS(...);
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTDEF WUNUSED pid_t (LIBCCALL libc_TCGetPGrp)(fd_t fd) THROWS(...);
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTDEF void (LIBCCALL libc_TCSetPGrp)(fd_t fd, pid_t pgrp_id) THROWS(...);
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_ReadAll)(fd_t fd, void *buf, size_t bufsize) THROWS(...);
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_WriteAll)(fd_t fd, void const *buf, size_t bufsize) THROWS(...);
#endif /* !__KERNEL__ */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
INTDEF ATTR_INS(2, 3) ssize_t (__FORMATPRINTER_CC libc_WritePrinter)(void *fd, char const *__restrict buf, size_t bufsize) THROWS(...);
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#if !defined(__KERNEL__) && (defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__)
/* Define the libc internal header variant as an alias for WriteAll() when it would otherwise not be defined. */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_WritePrinter)(void *fd, char const *__restrict buf, size_t bufsize) THROWS(...) ASMNAME("libc_WriteAll");
#endif /* !__KERNEL__ && (__LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) */
#ifndef __KERNEL__
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_PReadAll)(fd_t fd, void *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_PWriteAll)(fd_t fd, void const *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_PReadAll64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_PWriteAll64)(fd_t fd, void const *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> GetCurrentDirName(3)
 * Alias for `GetCwd(NULL, 0)' */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *(LIBCCALL libc_GetCurrentDirName)(void) THROWS(...);
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetRUid)(uid_t ruid) THROWS(...);
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetRGid)(gid_t rgid) THROWS(...);
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTDEF void (LIBCCALL libc_FChRoot)(fd_t fd) THROWS(...);
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED pos_t (LIBCCALL libc_Tell)(fd_t fd) THROWS(...);
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED pos64_t (LIBCCALL libc_Tell64)(fd_t fd) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_UNISTD_H */
