/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_GENERIC_ERRNO_H
#define _PARTS_GENERIC_ERRNO_H 1

/* NOTE: Linux error codes are taken from comments
 *      in /usr/include/asm-generic/errno.h
 *     and /usr/include/asm-generic/errno-base.h
 * While those files didn't include any copyright notice,
 * I'm still adding the notice found in /usr/include/errno.h:*/

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#define __GLC_EPERM           1   /* Operation not permitted */
#define __GLC_ENOENT          2   /* No such file or directory */
#define __GLC_ESRCH           3   /* No such process */
#define __GLC_EINTR           4   /* Interrupted system call */
#define __GLC_EIO             5   /* I/O error */
#define __GLC_ENXIO           6   /* No such device or address */
#define __GLC_E2BIG           7   /* Argument list too long */
#define __GLC_ENOEXEC         8   /* Exec format error */
#define __GLC_EBADF           9   /* Bad file number */
#define __GLC_ECHILD          10  /* No child processes */
#define __GLC_EAGAIN          11  /* Try again */
#define __GLC_ENOMEM          12  /* Out of memory */
#define __GLC_EACCES          13  /* Permission denied */
#define __GLC_EFAULT          14  /* Bad address */
#define __GLC_ENOTBLK         15  /* Block device required */
#define __GLC_EBUSY           16  /* Device or resource busy */
#define __GLC_EEXIST          17  /* File exists */
#define __GLC_EXDEV           18  /* Cross-device link */
#define __GLC_ENODEV          19  /* No such device */
#define __GLC_ENOTDIR         20  /* Not a directory */
#define __GLC_EISDIR          21  /* Is a directory */
#define __GLC_EINVAL          22  /* [NT("ERROR_INVALID_PARAMETER")] Invalid argument */
#define __GLC_ENFILE          23  /* File table overflow */
#define __GLC_EMFILE          24  /* Too many open files */
#define __GLC_ENOTTY          25  /* Not a typewriter */
#define __GLC_ETXTBSY         26  /* Text file busy */
#define __GLC_EFBIG           27  /* File too large */
#define __GLC_ENOSPC          28  /* No space left on device */
#define __GLC_ESPIPE          29  /* Illegal seek */
#define __GLC_EROFS           30  /* Read-only file system */
#define __GLC_EMLINK          31  /* Too many links */
#define __GLC_EPIPE           32  /* Broken pipe */
#define __GLC_EDOM            33  /* Math argument out of domain of func */
#define __GLC_ERANGE          34  /* [NT("ERROR_INSUFFICIENT_BUFFER")] Math result not representable */
#define __GLC_EDEADLK         35  /* Resource deadlock would occur */
#define __GLC_ENAMETOOLONG    36  /* File name too long */
#define __GLC_ENOLCK          37  /* No record locks available */

/*
 * This error code is special: arch syscall entry code will return
 * -ENOSYS if users try to call a syscall that doesn't exist.  To keep
 * failures of syscalls that really do exist distinguishable from
 * failures due to attempts to use a nonexistent syscall, syscall
 * implementations should refrain from returning -ENOSYS.
 */
#define __GLC_ENOSYS          38  /* Invalid system call number */
#define __GLC_ENOTEMPTY       39  /* Directory not empty */
#define __GLC_ELOOP           40  /* Too many symbolic links encountered */
#define __GLC_EWOULDBLOCK     __GLC_EAGAIN /* Operation would block */
#define __GLC_ENOMSG          42  /* No message of desired type */
#define __GLC_EIDRM           43  /* Identifier removed */
#define __GLC_ECHRNG          44  /* Channel number out of range */
#define __GLC_EL2NSYNC        45  /* Level 2 not synchronized */
#define __GLC_EL3HLT          46  /* Level 3 halted */
#define __GLC_EL3RST          47  /* Level 3 reset */
#define __GLC_ELNRNG          48  /* Link number out of range */
#define __GLC_EUNATCH         49  /* Protocol driver not attached */
#define __GLC_ENOCSI          50  /* No CSI structure available */
#define __GLC_EL2HLT          51  /* Level 2 halted */
#define __GLC_EBADE           52  /* Invalid exchange */
#define __GLC_EBADR           53  /* Invalid request descriptor */
#define __GLC_EXFULL          54  /* Exchange full */
#define __GLC_ENOANO          55  /* No anode */
#define __GLC_EBADRQC         56  /* Invalid request code */
#define __GLC_EBADSLT         57  /* Invalid slot */
#define __GLC_EDEADLOCK       __GLC_EDEADLK /* Resource deadlock would occur */
#define __GLC_EBFONT          59  /* Bad font file format */
#define __GLC_ENOSTR          60  /* Device not a stream */
#define __GLC_ENODATA         61  /* No data available */
#define __GLC_ETIME           62  /* Timer expired */
#define __GLC_ENOSR           63  /* Out of streams resources */
#define __GLC_ENONET          64  /* Machine is not on the network */
#define __GLC_ENOPKG          65  /* Package not installed */
#define __GLC_EREMOTE         66  /* Object is remote */
#define __GLC_ENOLINK         67  /* Link has been severed */
#define __GLC_EADV            68  /* Advertise error */
#define __GLC_ESRMNT          69  /* Srmount error */
#define __GLC_ECOMM           70  /* Communication error on send */
#define __GLC_EPROTO          71  /* Protocol error */
#define __GLC_EMULTIHOP       72  /* Multihop attempted */
#define __GLC_EDOTDOT         73  /* RFS specific error */
#define __GLC_EBADMSG         74  /* Not a data message */
#define __GLC_EOVERFLOW       75  /* Value too large for defined data type */
#define __GLC_ENOTUNIQ        76  /* Name not unique on network */
#define __GLC_EBADFD          77  /* File descriptor in bad state */
#define __GLC_EREMCHG         78  /* Remote address changed */
#define __GLC_ELIBACC         79  /* Can not access a needed shared library */
#define __GLC_ELIBBAD         80  /* Accessing a corrupted shared library */
#define __GLC_ELIBSCN         81  /* .lib section in a.out corrupted */
#define __GLC_ELIBMAX         82  /* Attempting to link in too many shared libraries */
#define __GLC_ELIBEXEC        83  /* Cannot exec a shared library directly */
#define __GLC_EILSEQ          84  /* [NT("ERROR_NO_UNICODE_TRANSLATION")] Illegal byte sequence */
#define __GLC_ERESTART        85  /* Interrupted system call should be restarted */
#define __GLC_ESTRPIPE        86  /* Streams pipe error */
#define __GLC_EUSERS          87  /* Too many users */
#define __GLC_ENOTSOCK        88  /* Socket operation on non-socket */
#define __GLC_EDESTADDRREQ    89  /* Destination address required */
#define __GLC_EMSGSIZE        90  /* Message too long */
#define __GLC_EPROTOTYPE      91  /* Protocol wrong type for socket */
#define __GLC_ENOPROTOOPT     92  /* Protocol not available */
#define __GLC_EPROTONOSUPPORT 93  /* Protocol not supported */
#define __GLC_ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define __GLC_EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define __GLC_EPFNOSUPPORT    96  /* Protocol family not supported */
#define __GLC_EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define __GLC_EADDRINUSE      98  /* Address already in use */
#define __GLC_EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define __GLC_ENETDOWN        100 /* Network is down */
#define __GLC_ENETUNREACH     101 /* Network is unreachable */
#define __GLC_ENETRESET       102 /* Network dropped connection because of reset */
#define __GLC_ECONNABORTED    103 /* Software caused connection abort */
#define __GLC_ECONNRESET      104 /* Connection reset by peer */
#define __GLC_ENOBUFS         105 /* No buffer space available */
#define __GLC_EISCONN         106 /* Transport endpoint is already connected */
#define __GLC_ENOTCONN        107 /* Transport endpoint is not connected */
#define __GLC_ESHUTDOWN       108 /* Cannot send after transport endpoint shutdown */
#define __GLC_ETOOMANYREFS    109 /* Too many references: cannot splice */
#define __GLC_ETIMEDOUT       110 /* Connection timed out */
#define __GLC_ECONNREFUSED    111 /* Connection refused */
#define __GLC_EHOSTDOWN       112 /* Host is down */
#define __GLC_EHOSTUNREACH    113 /* No route to host */
#define __GLC_EALREADY        114 /* Operation already in progress */
#define __GLC_EINPROGRESS     115 /* Operation now in progress */
#define __GLC_ESTALE          116 /* Stale file handle */
#define __GLC_EUCLEAN         117 /* Structure needs cleaning */
#define __GLC_ENOTNAM         118 /* Not a XENIX named type file */
#define __GLC_ENAVAIL         119 /* No XENIX semaphores available */
#define __GLC_EISNAM          120 /* Is a named type file */
#define __GLC_EREMOTEIO       121 /* Remote I/O error */
#define __GLC_EDQUOT          122 /* Quota exceeded */

#define __GLC_ENOMEDIUM       123 /* No medium found */
#define __GLC_EMEDIUMTYPE     124 /* Wrong medium type */
#define __GLC_ECANCELED       125 /* Operation Canceled */
#define __GLC_ENOKEY          126 /* Required key not available */
#define __GLC_EKEYEXPIRED     127 /* Key has expired */
#define __GLC_EKEYREVOKED     128 /* Key has been revoked */
#define __GLC_EKEYREJECTED    129 /* Key was rejected by service */

/* for robust mutexes */
#define __GLC_EOWNERDEAD      130 /* Owner died */
#define __GLC_ENOTRECOVERABLE 131 /* State not recoverable */

#define __GLC_ERFKILL         132 /* Operation not possible due to RF-kill */

#define __GLC_EHWPOISON       133 /* Memory page has hardware error */
#define __GLC_ECOUNT          134 /* Max errno + 1 */
#define __GLC___EBASEMAX      133

#endif /* !_PARTS_GENERIC_ERRNO_H */
