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
#ifndef _PARTS_DOS_ERRNO_H
#define _PARTS_DOS_ERRNO_H 1

/* DOS errno values */
#define __DOS_EPERM            1  /* Operation not permitted */
#define __DOS_ENOENT           2  /* No such file or directory */
#define __DOS_ESRCH            3  /* No such process */
#define __DOS_EINTR            4  /* Interrupted system call */
#define __DOS_EIO              5  /* I/O error */
#define __DOS_ENXIO            6  /* No such device or address */
#define __DOS_E2BIG            7  /* Argument list too long */
#define __DOS_ENOEXEC          8  /* Exec format error */
#define __DOS_EBADF            9  /* Bad file number */
#define __DOS_ECHILD          10  /* No child processes */
#define __DOS_EAGAIN          11  /* Try again */
#define __DOS_ENOMEM          12  /* Out of memory */
#define __DOS_EACCES          13  /* Permission denied */
#define __DOS_EFAULT          14  /* Bad address */
#define __DOS_EBUSY           16  /* Device or resource busy */
#define __DOS_EEXIST          17  /* File exists */
#define __DOS_EXDEV           18  /* Cross-device link */
#define __DOS_ENODEV          19  /* No such device */
#define __DOS_ENOTDIR         20  /* Not a directory */
#define __DOS_EISDIR          21  /* Is a directory */
#define __DOS_ENFILE          23  /* File table overflow */
#define __DOS_EMFILE          24  /* Too many open files */
#define __DOS_ENOTTY          25  /* Not a typewriter */
#define __DOS_EFBIG           27  /* File too large */
#define __DOS_ENOSPC          28  /* No space left on device */
#define __DOS_ESPIPE          29  /* Illegal seek */
#define __DOS_EROFS           30  /* Read-only file system */
#define __DOS_EMLINK          31  /* Too many links */
#define __DOS_EPIPE           32  /* Broken pipe */
#define __DOS_EDOM            33  /* Math argument out of domain of func */
#define __DOS_EDEADLK         36  /* Resource deadlock would occur */
#define __DOS_ENAMETOOLONG    38  /* File name too long */
#define __DOS_ENOLCK          39  /* No record locks available */
#define __DOS_ENOSYS          40  /* Function not implemented */
#define __DOS_ENOTEMPTY       41  /* Directory not empty */
#define __DOS_EINVAL          22  /* Invalid argument */
#define __DOS_ERANGE          34  /* Math result not representable */
#define __DOS_EILSEQ          42  /* Illegal byte sequence */
#define __DOS_STRUNCATE       80  /* Truncated */
#define __DOS_EDEADLOCK       __DOS_EDEADLK /* Resource deadlock would occur */
#define __DOS_EADDRINUSE      100 /* Address already in use */
#define __DOS_EADDRNOTAVAIL   101 /* Cannot assign requested address */
#define __DOS_EAFNOSUPPORT    102 /* Address family not supported by protocol */
#define __DOS_EALREADY        103 /* Operation already in progress */
#define __DOS_EBADMSG         104 /* Not a data message */
#define __DOS_ECANCELED       105 /* Operation Canceled */
#define __DOS_ECONNABORTED    106 /* Software caused connection abort */
#define __DOS_ECONNREFUSED    107 /* Connection refused */
#define __DOS_ECONNRESET      108 /* Connection reset by peer */
#define __DOS_EDESTADDRREQ    109 /* Destination address required */
#define __DOS_EHOSTUNREACH    110 /* No route to host */
#define __DOS_EIDRM           111 /* Identifier removed */
#define __DOS_EINPROGRESS     112 /* Operation now in progress */
#define __DOS_EISCONN         113 /* Transport endpoint is already connected */
#define __DOS_ELOOP           114 /* Too many symbolic links encountered */
#define __DOS_EMSGSIZE        115 /* Message too long */
#define __DOS_ENETDOWN        116 /* Network is down */
#define __DOS_ENETRESET       117 /* Network dropped connection because of reset */
#define __DOS_ENETUNREACH     118 /* Network is unreachable */
#define __DOS_ENOBUFS         119 /* No buffer space available */
#define __DOS_ENODATA         120 /* No data available */
#define __DOS_ENOLINK         121 /* Link has been severed */
#define __DOS_ENOMSG          122 /* No message of desired type */
#define __DOS_ENOPROTOOPT     123 /* Protocol not available */
#define __DOS_ENOSR           124 /* Out of streams resources */
#define __DOS_ENOSTR          125 /* Device not a stream */
#define __DOS_ENOTCONN        126 /* Transport endpoint is not connected */
#define __DOS_ENOTRECOVERABLE 127 /* State not recoverable */
#define __DOS_ENOTSOCK        128 /* Socket operation on non-socket */
#define __DOS_ENOTSUP         129 /* Not supported */
#define __DOS_EOPNOTSUPP      130 /* Operation not supported on transport endpoint */
#define __DOS_EOTHER          131 /* Other */
#define __DOS_EOVERFLOW       132 /* Value too large for defined data type */
#define __DOS_EOWNERDEAD      133 /* Owner died */
#define __DOS_EPROTO          134 /* Protocol error */
#define __DOS_EPROTONOSUPPORT 135 /* Protocol not supported */
#define __DOS_EPROTOTYPE      136 /* Protocol wrong type for socket */
#define __DOS_ETIME           137 /* Timer expired */
#define __DOS_ETIMEDOUT       138 /* Connection timed out */
#define __DOS_ETXTBSY         139 /* Text file busy */
#define __DOS_EWOULDBLOCK     140 /* Operation would block */
#define __DOS_EMAX            140 /* Max errno */
#define __DOS_ECOUNT          141 /* Max errno + 1 */

#endif /* !_PARTS_DOS_ERRNO_H */
