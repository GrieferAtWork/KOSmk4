/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <asm/os/errno.h>*/
#ifndef _ASM_OS_DOS_ERRNO_H
#define _ASM_OS_DOS_ERRNO_H 1

#include <__stdinc.h>

/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/

/*[[[begin]]]*/
#define __EPERM           1   /* Operation not permitted */
#define __ENOENT          2   /* No such file or directory */
#define __ESRCH           3   /* No such process */
#define __EINTR           4   /* Interrupted system call */
#define __EIO             5   /* I/O error */
#define __ENXIO           6   /* No such device or address */
#define __E2BIG           7   /* Argument list too long */
#define __ENOEXEC         8   /* Exec format error */
#define __EBADF           9   /* Bad file number */
#define __ECHILD          10  /* No child processes */
#define __EAGAIN          11  /* Try again */
#define __ENOMEM          12  /* Out of memory */
#define __EACCES          13  /* Permission denied */
#define __EFAULT          14  /* Bad address */
#define __EBUSY           16  /* Device or resource busy */
#define __EEXIST          17  /* File exists */
#define __EXDEV           18  /* Cross-device link */
#define __ENODEV          19  /* No such device */
#define __ENOTDIR         20  /* Not a directory */
#define __EISDIR          21  /* Is a directory */
#define __EINVAL          22  /* Invalid argument */
#define __ENFILE          23  /* File table overflow */
#define __EMFILE          24  /* Too many open files */
#define __ENOTTY          25  /* Not a typewriter */
#define __EFBIG           27  /* File too large */
#define __ENOSPC          28  /* No space left on device */
#define __ESPIPE          29  /* Illegal seek */
#define __EROFS           30  /* Read-only file system */
#define __EMLINK          31  /* Too many links */
#define __EPIPE           32  /* Broken pipe */
#define __EDOM            33  /* Math argument out of domain of func */
#define __ERANGE          34  /* Math result not representable */
#define __EDEADLK         36  /* Resource deadlock would occur */
#define __ENAMETOOLONG    38  /* File name too long */
#define __ENOLCK          39  /* No record locks available */
#define __ENOSYS          40  /* Function not implemented */
#define __ENOTEMPTY       41  /* Directory not empty */
#define __EILSEQ          42  /* Illegal byte sequence */
#define __STRUNCATE       80  /* [kos(ERANGE)] Truncated */
#define __EADDRINUSE      100 /* Address already in use */
#define __EADDRNOTAVAIL   101 /* Cannot assign requested address */
#define __EAFNOSUPPORT    102 /* Address family not supported by protocol */
#define __EALREADY        103 /* Operation already in progress */
#define __EBADMSG         104 /* Not a data message */
#define __ECANCELED       105 /* Operation canceled */
#define __ECONNABORTED    106 /* Software caused connection abort */
#define __ECONNREFUSED    107 /* Connection refused */
#define __ECONNRESET      108 /* Connection reset by peer */
#define __EDESTADDRREQ    109 /* Destination address required */
#define __EHOSTUNREACH    110 /* No route to host */
#define __EIDRM           111 /* Identifier removed */
#define __EINPROGRESS     112 /* Operation now in progress */
#define __EISCONN         113 /* Transport endpoint is already connected */
#define __ELOOP           114 /* Too many symbolic links encountered */
#define __EMSGSIZE        115 /* Message too long */
#define __ENETDOWN        116 /* Network is down */
#define __ENETRESET       117 /* Network dropped connection because of reset */
#define __ENETUNREACH     118 /* Network is unreachable */
#define __ENOBUFS         119 /* No buffer space available */
#define __ENODATA         120 /* No data available */
#define __ENOLINK         121 /* Link has been severed */
#define __ENOMSG          122 /* No message of desired type */
#define __ENOPROTOOPT     123 /* Protocol not available */
#define __ENOSR           124 /* Out of streams resources */
#define __ENOSTR          125 /* Device not a stream */
#define __ENOTCONN        126 /* Transport endpoint is not connected */
#define __ENOTRECOVERABLE 127 /* State not recoverable */
#define __ENOTSOCK        128 /* Socket operation on non-socket */
#define __ENOTSUP         129 /* Not supported */
#define __EOPNOTSUPP      130 /* Operation not supported on transport endpoint */
#define __EOTHER          131 /* [kos(EPERM)] Other */
#define __EOVERFLOW       132 /* Value too large for defined data type */
#define __EOWNERDEAD      133 /* Owner died */
#define __EPROTO          134 /* Protocol error */
#define __EPROTONOSUPPORT 135 /* Protocol not supported */
#define __EPROTOTYPE      136 /* Protocol wrong type for socket */
#define __ETIME           137 /* Timer expired */
#define __ETIMEDOUT       138 /* Connection timed out */
#define __ETXTBSY         139 /* Text file busy */
#define __EWOULDBLOCK     140 /* Operation would block */
/*[[[end]]]*/

#define __EMAX   140 /* Max errno */
#define __ECOUNT 141 /* Max errno + 1 */

#endif /* !_ASM_OS_DOS_ERRNO_H */
