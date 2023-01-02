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
#ifndef _ASM_ERRNO_BASE_H
#define _ASM_ERRNO_BASE_H 1

#include <asm/os/errno.h>

#if !defined(EPERM) && defined(__EPERM)
#define EPERM   __EPERM    /* Operation not permitted */
#endif /* !EPERM && __EPERM */
#if !defined(ENOENT) && defined(__ENOENT)
#define ENOENT  __ENOENT   /* No such file or directory */
#endif /* !ENOENT && __ENOENT */
#if !defined(ESRCH) && defined(__ESRCH)
#define ESRCH   __ESRCH    /* No such process */
#endif /* !ESRCH && __ESRCH */
#if !defined(EINTR) && defined(__EINTR)
#define EINTR   __EINTR    /* Interrupted system call */
#endif /* !EINTR && __EINTR */
#if !defined(EIO) && defined(__EIO)
#define EIO     __EIO      /* I/O error */
#endif /* !EIO && __EIO */
#if !defined(ENXIO) && defined(__ENXIO)
#define ENXIO   __ENXIO    /* No such device or address */
#endif /* !ENXIO && __ENXIO */
#if !defined(E2BIG) && defined(__E2BIG)
#define E2BIG   __E2BIG    /* Argument list too long */
#endif /* !E2BIG && __E2BIG */
#if !defined(ENOEXEC) && defined(__ENOEXEC)
#define ENOEXEC __ENOEXEC  /* Exec format error */
#endif /* !ENOEXEC && __ENOEXEC */
#if !defined(EBADF) && defined(__EBADF)
#define EBADF   __EBADF    /* Bad file number */
#endif /* !EBADF && __EBADF */
#if !defined(ECHILD) && defined(__ECHILD)
#define ECHILD  __ECHILD   /* No child processes */
#endif /* !ECHILD && __ECHILD */
#if !defined(EAGAIN) && defined(__EAGAIN)
#define EAGAIN  __EAGAIN   /* Try again */
#endif /* !EAGAIN && __EAGAIN */
#if !defined(ENOMEM) && defined(__ENOMEM)
#define ENOMEM  __ENOMEM   /* Out of memory */
#endif /* !ENOMEM && __ENOMEM */
#if !defined(EACCES) && defined(__EACCES)
#define EACCES  __EACCES   /* Permission denied */
#endif /* !EACCES && __EACCES */
#if !defined(EFAULT) && defined(__EFAULT)
#define EFAULT  __EFAULT   /* Bad address */
#endif /* !EFAULT && __EFAULT */
#if !defined(ENOTBLK) && defined(__ENOTBLK)
#define ENOTBLK __ENOTBLK  /* Block device required */
#endif /* !ENOTBLK && __ENOTBLK */
#if !defined(EBUSY) && defined(__EBUSY)
#define EBUSY   __EBUSY    /* Device or resource busy */
#endif /* !EBUSY && __EBUSY */
#if !defined(EEXIST) && defined(__EEXIST)
#define EEXIST  __EEXIST   /* File exists */
#endif /* !EEXIST && __EEXIST */
#if !defined(EXDEV) && defined(__EXDEV)
#define EXDEV   __EXDEV    /* Cross-device link */
#endif /* !EXDEV && __EXDEV */
#if !defined(ENODEV) && defined(__ENODEV)
#define ENODEV  __ENODEV   /* No such device */
#endif /* !ENODEV && __ENODEV */
#if !defined(ENOTDIR) && defined(__ENOTDIR)
#define ENOTDIR __ENOTDIR  /* Not a directory */
#endif /* !ENOTDIR && __ENOTDIR */
#if !defined(EISDIR) && defined(__EISDIR)
#define EISDIR  __EISDIR   /* Is a directory */
#endif /* !EISDIR && __EISDIR */
#if !defined(EINVAL) && defined(__EINVAL)
#define EINVAL  __EINVAL   /* Invalid argument */
#endif /* !EINVAL && __EINVAL */
#if !defined(ENFILE) && defined(__ENFILE)
#define ENFILE  __ENFILE   /* File table overflow */
#endif /* !ENFILE && __ENFILE */
#if !defined(EMFILE) && defined(__EMFILE)
#define EMFILE  __EMFILE   /* Too many open files */
#endif /* !EMFILE && __EMFILE */
#if !defined(ENOTTY) && defined(__ENOTTY)
#define ENOTTY  __ENOTTY   /* Not a typewriter */
#endif /* !ENOTTY && __ENOTTY */
#if !defined(ETXTBSY) && defined(__ETXTBSY)
#define ETXTBSY __ETXTBSY  /* Text file busy */
#endif /* !ETXTBSY && __ETXTBSY */
#if !defined(EFBIG) && defined(__EFBIG)
#define EFBIG   __EFBIG    /* File too large */
#endif /* !EFBIG && __EFBIG */
#if !defined(ENOSPC) && defined(__ENOSPC)
#define ENOSPC  __ENOSPC   /* No space left on device */
#endif /* !ENOSPC && __ENOSPC */
#if !defined(ESPIPE) && defined(__ESPIPE)
#define ESPIPE  __ESPIPE   /* Illegal seek */
#endif /* !ESPIPE && __ESPIPE */
#if !defined(EROFS) && defined(__EROFS)
#define EROFS   __EROFS    /* Read-only file system */
#endif /* !EROFS && __EROFS */
#if !defined(EMLINK) && defined(__EMLINK)
#define EMLINK  __EMLINK   /* Too many links */
#endif /* !EMLINK && __EMLINK */
#if !defined(EPIPE) && defined(__EPIPE)
#define EPIPE   __EPIPE    /* Broken pipe */
#endif /* !EPIPE && __EPIPE */
#if !defined(EDOM) && defined(__EDOM)
#define EDOM    __EDOM     /* Math argument out of domain of func */
#endif /* !EDOM && __EDOM */
#if !defined(ERANGE) && defined(__ERANGE)
#define ERANGE  __ERANGE   /* Math result not representable */
#endif /* !ERANGE && __ERANGE */

#endif /* !_ASM_ERRNO_BASE_H */
