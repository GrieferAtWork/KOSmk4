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
#ifndef _ASM_OS_ERRNO_H
#define _ASM_OS_ERRNO_H 1

#include <__stdinc.h>

/* After making changes to these files, update the following files:
 * $ deemon -F kos/src/libc/magic/errno.c
 * $ deemon -F kos/src/libc/libc/compat.h
 * $ deemon -F kos/src/libc/libc/errno-convert-cyg.c
 * $ deemon -F kos/src/libc/libc/errno-convert-dos.c
 * $ deemon -F kos/src/libc/libc/sys_errlist.def
 * Or the one-liner:
 * $ deemon -F kos/src/libc/magic/errno.c kos/src/libc/libc/compat.h kos/src/libc/libc/errno-convert-cyg.c kos/src/libc/libc/errno-convert-dos.c kos/src/libc/libc/sys_errlist.def
 *
 * Also note that generate_headers.dee will  have to be re-run,  though
 * it will be executed automatically because `magic/errno.c' is touched
 * by the above. */

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/errno.h>
#elif defined(__NetBSD__)
#include <asm/os/netbsd/errno.h>
#elif defined(__solaris__)
#include <asm/os/solaris/errno.h>
#else /* ... */
#include <__crt.h>
#if defined(__CRT_CYG_PRIMARY)
#include <asm/os/cygwin/errno.h>
#elif defined(__CRT_DOS_PRIMARY)
#include <asm/os/dos/errno.h>
#else /* ... */

/************************************************************************/
/* GENERIC (guessed)                                                    */
/************************************************************************/
#define __EPERM           1  /* Operation not permitted */
#define __ENOENT          2  /* No such file or directory */
#define __ESRCH           3  /* No such process */
#define __EINTR           4  /* Interrupted system call */
#define __EIO             5  /* I/O error */
#define __ENXIO           6  /* No such device or address */
#define __E2BIG           7  /* Argument list too long */
#define __ENOEXEC         8  /* Exec format error */
#define __EBADF           9  /* Bad file number */
#define __ECHILD          10 /* No child processes */
#define __EAGAIN          11 /* Try again */
#define __ENOMEM          12 /* Out of memory */
#define __EACCES          13 /* Permission denied */
#define __EFAULT          14 /* Bad address */
#define __EBUSY           16 /* Device or resource busy */
#define __EEXIST          17 /* File exists */
#define __EXDEV           18 /* Cross-device link */
#define __ENODEV          19 /* No such device */
#define __ENOTDIR         20 /* Not a directory */
#define __EISDIR          21 /* Is a directory */
#define __EINVAL          22 /* Invalid argument */
#define __ENFILE          23 /* File table overflow */
#define __EMFILE          24 /* Too many open files */
#define __ENOTTY          25 /* Not a typewriter */
#define __ETXTBSY         26 /* Text file busy */
#define __EFBIG           27 /* File too large */
#define __ENOSPC          28 /* No space left on device */
#define __ESPIPE          29 /* Illegal seek */
#define __EROFS           30 /* Read-only file system */
#define __EMLINK          31 /* Too many links */
#define __EPIPE           32 /* Broken pipe */
#define __EDOM            33 /* Math argument out of domain of func */
#define __ERANGE          34 /* Math result not representable */
#define __EMAX            34 /* Max errno */
#define __ECOUNT          35 /* Max errno + 1 */
#endif /* !... */
#endif /* !... */

#ifndef __EOK
#define __EOK 0 /* Success */
#endif /* !__EOK */

#if !defined(__ELASTERROR) && defined(__EMAX)
#define __ELASTERROR __EMAX /* Users can add values starting here */
#endif /* !__ELASTERROR && __EMAX */

#if !defined(__ELIMIT) && defined(__EMAX)
#define __ELIMIT __EMAX /* Max possible errno */
#endif /* !__ELIMIT && __EMAX */


#endif /* !_ASM_OS_ERRNO_H */
