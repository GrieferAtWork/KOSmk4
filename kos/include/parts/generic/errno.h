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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_GENERIC_ERRNO_H
#define _PARTS_GENERIC_ERRNO_H 1

/* Fallback: http://www.virtsync.com/c-error-codes-include-errno
 *   - When I looked it up, that page was the first google result
 *     for `errno.h', so judging by that fact, there shouldn't be
 *     better fallback values for errno codes! */
#define __GEN_EPERM            1  /* Operation not permitted */
#define __GEN_ENOENT           2  /* No such file or directory */
#define __GEN_ESRCH            3  /* No such process */
#define __GEN_EINTR            4  /* Interrupted system call */
#define __GEN_EIO              5  /* I/O error */
#define __GEN_ENXIO            6  /* No such device or address */
#define __GEN_E2BIG            7  /* Argument list too long */
#define __GEN_ENOEXEC          8  /* Exec format error */
#define __GEN_EBADF            9  /* Bad file number */
#define __GEN_ECHILD          10  /* No child processes */
#define __GEN_EAGAIN          11  /* Try again */
#define __GEN_ENOMEM          12  /* Out of memory */
#define __GEN_EACCES          13  /* Permission denied */
#define __GEN_EFAULT          14  /* Bad address */
#define __GEN_ENOTBLK         15  /* Block device required */
#define __GEN_EBUSY           16  /* Device or resource busy */
#define __GEN_EEXIST          17  /* File exists */
#define __GEN_EXDEV           18  /* Cross-device link */
#define __GEN_ENODEV          19  /* No such device */
#define __GEN_ENOTDIR         20  /* Not a directory */
#define __GEN_EISDIR          21  /* Is a directory */
#define __GEN_EINVAL          22  /* Invalid argument */
#define __GEN_ENFILE          23  /* File table overflow */
#define __GEN_EMFILE          24  /* Too many open files */
#define __GEN_ENOTTY          25  /* Not a typewriter */
#define __GEN_ETXTBSY         26  /* Text file busy */
#define __GEN_EFBIG           27  /* File too large */
#define __GEN_ENOSPC          28  /* No space left on device */
#define __GEN_ESPIPE          29  /* Illegal seek */
#define __GEN_EROFS           30  /* Read-only file system */
#define __GEN_EMLINK          31  /* Too many links */
#define __GEN_EPIPE           32  /* Broken pipe */
#define __GEN_EDOM            33  /* Math argument out of domain of func */
#define __GEN_ERANGE          34  /* Math result not representable */
#define __GEN_EDEADLK         35  /* Resource deadlock would occur */
#define __GEN_ENAMETOOLONG    36  /* File name too long */
#define __GEN_ENOLCK          37  /* No record locks available */
#define __GEN_ENOSYS          38  /* Function not implemented */
#define __GEN_ENOTEMPTY       39  /* Directory not empty */
#define __GEN_ELOOP           40  /* Too many symbolic links encountered */
#define __GEN_EWOULDBLOCK     __GEN_EAGAIN  /* Operation would block */
#define __GEN_ENOMSG          42  /* No message of desired type */
#define __GEN_EIDRM           43  /* Identifier removed */
#define __GEN_ECHRNG          44  /* Channel number out of range */
#define __GEN_EL2NSYNC        45  /* Level 2 not synchronized */
#define __GEN_EL3HLT          46  /* Level 3 halted */
#define __GEN_EL3RST          47  /* Level 3 reset */
#define __GEN_ELNRNG          48  /* Link number out of range */
#define __GEN_EUNATCH         49  /* Protocol driver not attached */
#define __GEN_ENOCSI          50  /* No CSI structure available */
#define __GEN_EL2HLT          51  /* Level 2 halted */
#define __GEN_EBADE           52  /* Invalid exchange */
#define __GEN_EBADR           53  /* Invalid request descriptor */
#define __GEN_EXFULL          54  /* Exchange full */
#define __GEN_ENOANO          55  /* No anode */
#define __GEN_EBADRQC         56  /* Invalid request code */
#define __GEN_EBADSLT         57  /* Invalid slot */
#define __GEN_EDEADLOCK       __GEN_EDEADLK /* Resource deadlock would occur */
#define __GEN_EBFONT          59  /* Bad font file format */
#define __GEN_ENOSTR          60  /* Device not a stream */
#define __GEN_ENODATA         61  /* No data available */
#define __GEN_ETIME           62  /* Timer expired */
#define __GEN_ENOSR           63  /* Out of streams resources */
#define __GEN_ENONET          64  /* Machine is not on the network */
#define __GEN_ENOPKG          65  /* Package not installed */
#define __GEN_EREMOTE         66  /* Object is remote */
#define __GEN_ENOLINK         67  /* Link has been severed */
#define __GEN_EADV            68  /* Advertise error */
#define __GEN_ESRMNT          69  /* Srmount error */
#define __GEN_ECOMM           70  /* Communication error on send */
#define __GEN_EPROTO          71  /* Protocol error */
#define __GEN_EMULTIHOP       72  /* Multihop attempted */
#define __GEN_EDOTDOT         73  /* RFS specific error */
#define __GEN_EBADMSG         74  /* Not a data message */
#define __GEN_EOVERFLOW       75  /* Value too large for defined data type */
#define __GEN_ENOTUNIQ        76  /* Name not unique on network */
#define __GEN_EBADFD          77  /* File descriptor in bad state */
#define __GEN_EREMCHG         78  /* Remote address changed */
#define __GEN_ELIBACC         79  /* Can not access a needed shared library */
#define __GEN_ELIBBAD         80  /* Accessing a corrupted shared library */
#define __GEN_ELIBSCN         81  /* .lib section in a.out corrupted */
#define __GEN_ELIBMAX         82  /* Attempting to link in too many shared libraries */
#define __GEN_ELIBEXEC        83  /* Cannot exec a shared library directly */
#define __GEN_EILSEQ          84  /* Illegal byte sequence */
#define __GEN_ERESTART        85  /* Interrupted system call should be restarted */
#define __GEN_ESTRPIPE        86  /* Streams pipe error */
#define __GEN_EUSERS          87  /* Too many users */
#define __GEN_ENOTSOCK        88  /* Socket operation on non-socket */
#define __GEN_EDESTADDRREQ    89  /* Destination address required */
#define __GEN_EMSGSIZE        90  /* Message too long */
#define __GEN_EPROTOTYPE      91  /* Protocol wrong type for socket */
#define __GEN_ENOPROTOOPT     92  /* Protocol not available */
#define __GEN_EPROTONOSUPPORT 93  /* Protocol not supported */
#define __GEN_ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define __GEN_EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define __GEN_EPFNOSUPPORT    96  /* Protocol family not supported */
#define __GEN_EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define __GEN_EADDRINUSE      98  /* Address already in use */
#define __GEN_EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define __GEN_ENETDOWN        100 /* Network is down */
#define __GEN_ENETUNREACH     101 /* Network is unreachable */
#define __GEN_ENETRESET       102 /* Network dropped connection because of reset */
#define __GEN_ECONNABORTED    103 /* Software caused connection abort */
#define __GEN_ECONNRESET      104 /* Connection reset by peer */
#define __GEN_ENOBUFS         105 /* No buffer space available */
#define __GEN_EISCONN         106 /* Transport endpoint is already connected */
#define __GEN_ENOTCONN        107 /* Transport endpoint is not connected */
#define __GEN_ESHUTDOWN       108 /* Cannot send after transport endpoint shutdown */
#define __GEN_ETOOMANYREFS    109 /* Too many references: cannot splice */
#define __GEN_ETIMEDOUT       110 /* Connection timed out */
#define __GEN_ECONNREFUSED    111 /* Connection refused */
#define __GEN_EHOSTDOWN       112 /* Host is down */
#define __GEN_EHOSTUNREACH    113 /* No route to host */
#define __GEN_EALREADY        114 /* Operation already in progress */
#define __GEN_EINPROGRESS     115 /* Operation now in progress */
#define __GEN_ESTALE          116 /* Stale NFS file handle */
#define __GEN_EUCLEAN         117 /* Structure needs cleaning */
#define __GEN_ENOTNAM         118 /* Not a XENIX named type file */
#define __GEN_ENAVAIL         119 /* No XENIX semaphores available */
#define __GEN_EISNAM          120 /* Is a named type file */
#define __GEN_EREMOTEIO       121 /* Remote I/O error */
#define __GEN_EDQUOT          122 /* Quota exceeded */
#define __GEN_ENOMEDIUM       123 /* No medium found */
#define __GEN_EMEDIUMTYPE     124 /* Wrong medium type */
#define __GEN_ECANCELED       125 /* Operation Canceled */
#define __GEN_ENOKEY          126 /* Required key not available */
#define __GEN_EKEYEXPIRED     127 /* Key has expired */
#define __GEN_EKEYREVOKED     128 /* Key has been revoked */
#define __GEN_EKEYREJECTED    129 /* Key was rejected by service */
#define __GEN_EOWNERDEAD      130 /* Owner died */
#define __GEN_ENOTRECOVERABLE 131 /* State not recoverable */
#define __GEN_ECOUNT          132 /* Max errno + 1 */

#endif /* !_PARTS_GENERIC_ERRNO_H */
