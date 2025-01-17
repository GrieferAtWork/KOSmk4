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
#ifndef _ASM_OS_KOS_ERRNO_H
#define _ASM_OS_KOS_ERRNO_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
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
#define __ENOTBLK         15  /* Block device required */
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
#define __ETXTBSY         26  /* Text file busy */
#define __EFBIG           27  /* File too large */
#define __ENOSPC          28  /* No space left on device */
#define __ESPIPE          29  /* Illegal seek */
#define __EROFS           30  /* Read-only file system */
#define __EMLINK          31  /* Too many links */
#define __EPIPE           32  /* Broken pipe */
#define __EDOM            33  /* Math argument out of domain of func */
#define __ERANGE          34  /* Math result not representable */
#define __EDEADLK         35  /* Resource deadlock would occur */
#define __ENAMETOOLONG    36  /* File name too long */
#define __ENOLCK          37  /* No record locks available */
#define __ENOSYS          38  /* Function not implemented */
#define __ENOTEMPTY       39  /* Directory not empty */
#define __ELOOP           40  /* Too many symbolic links encountered */
/*      __EWOULDBLOCK     41   * Operation would block */
#define __ENOMSG          42  /* No message of desired type */
#define __EIDRM           43  /* Identifier removed */
#define __ECHRNG          44  /* Channel number out of range */
#define __EL2NSYNC        45  /* Level 2 not synchronized */
#define __EL3HLT          46  /* Level 3 halted */
#define __EL3RST          47  /* Level 3 reset */
#define __ELNRNG          48  /* Link number out of range */
#define __EUNATCH         49  /* Protocol driver not attached */
#define __ENOCSI          50  /* No CSI structure available */
#define __EL2HLT          51  /* Level 2 halted */
#define __EBADE           52  /* Invalid exchange */
#define __EBADR           53  /* Invalid request descriptor */
#define __EXFULL          54  /* Exchange full */
#define __ENOANO          55  /* No anode */
#define __EBADRQC         56  /* Invalid request code */
#define __EBADSLT         57  /* Invalid slot */
/*      __EDEADLOCK       58   * Resource deadlock would occur */
#define __EBFONT          59  /* Bad font file format */
#define __ENOSTR          60  /* Device not a stream */
#define __ENODATA         61  /* No data available */
#define __ETIME           62  /* Timer expired */
#define __ENOSR           63  /* Out of streams resources */
#define __ENONET          64  /* Machine is not on the network */
#define __ENOPKG          65  /* Package not installed */
#define __EREMOTE         66  /* Object is remote */
#define __ENOLINK         67  /* Link has been severed */
#define __EADV            68  /* Advertise error */
#define __ESRMNT          69  /* Srmount error */
#define __ECOMM           70  /* Communication error on send */
#define __EPROTO          71  /* Protocol error */
#define __EMULTIHOP       72  /* Multihop attempted */
#define __EDOTDOT         73  /* RFS specific error */
#define __EBADMSG         74  /* Not a data message */
#define __EOVERFLOW       75  /* Value too large for defined data type */
#define __ENOTUNIQ        76  /* Name not unique on network */
#define __EBADFD          77  /* File descriptor in bad state */
#define __EREMCHG         78  /* Remote address changed */
#define __ELIBACC         79  /* Can not access a needed shared library */
#define __ELIBBAD         80  /* Accessing a corrupted shared library */
#define __ELIBSCN         81  /* .lib section in a.out corrupted */
#define __ELIBMAX         82  /* Attempting to link in too many shared libraries */
#define __ELIBEXEC        83  /* Cannot exec a shared library directly */
#define __EILSEQ          84  /* Illegal byte sequence */
#define __ERESTART        85  /* Interrupted system call should be restarted */
#define __ESTRPIPE        86  /* Streams pipe error */
#define __EUSERS          87  /* Too many users */
#define __ENOTSOCK        88  /* Socket operation on non-socket */
#define __EDESTADDRREQ    89  /* Destination address required */
#define __EMSGSIZE        90  /* Message too long */
#define __EPROTOTYPE      91  /* Protocol wrong type for socket */
#define __ENOPROTOOPT     92  /* Protocol not available */
#define __EPROTONOSUPPORT 93  /* Protocol not supported */
#define __ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define __EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define __EPFNOSUPPORT    96  /* Protocol family not supported */
#define __EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define __EADDRINUSE      98  /* Address already in use */
#define __EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define __ENETDOWN        100 /* Network is down */
#define __ENETUNREACH     101 /* Network is unreachable */
#define __ENETRESET       102 /* Network dropped connection because of reset */
#define __ECONNABORTED    103 /* Software caused connection abort */
#define __ECONNRESET      104 /* Connection reset by peer */
#define __ENOBUFS         105 /* No buffer space available */
#define __EISCONN         106 /* Transport endpoint is already connected */
#define __ENOTCONN        107 /* Transport endpoint is not connected */
#define __ESHUTDOWN       108 /* Cannot send after transport endpoint shutdown */
#define __ETOOMANYREFS    109 /* Too many references: cannot splice */
#define __ETIMEDOUT       110 /* Connection timed out */
#define __ECONNREFUSED    111 /* Connection refused */
#define __EHOSTDOWN       112 /* Host is down */
#define __EHOSTUNREACH    113 /* No route to host */
#define __EALREADY        114 /* Operation already in progress */
#define __EINPROGRESS     115 /* Operation now in progress */
#define __ESTALE          116 /* Stale file handle */
#define __EUCLEAN         117 /* Structure needs cleaning */
#define __ENOTNAM         118 /* Not a XENIX named type file */
#define __ENAVAIL         119 /* No XENIX semaphores available */
#define __EISNAM          120 /* Is a named type file */
#define __EREMOTEIO       121 /* Remote I/O error */
#define __EDQUOT          122 /* Quota exceeded */
#define __ENOMEDIUM       123 /* No medium found */
#define __EMEDIUMTYPE     124 /* Wrong medium type */
#define __ECANCELED       125 /* Operation canceled */
#define __ENOKEY          126 /* Required key not available */
#define __EKEYEXPIRED     127 /* Key has expired */
#define __EKEYREVOKED     128 /* Key has been revoked */
#define __EKEYREJECTED    129 /* Key was rejected by service */
#define __EOWNERDEAD      130 /* Owner died */
#define __ENOTRECOVERABLE 131 /* State not recoverable */
#define __ERFKILL         132 /* Operation not possible due to RF-kill */
#define __EHWPOISON       133 /* Memory page has hardware error */
/*[[[end]]]*/
#define __EMAX            133 /* Max errno */
#define __ECOUNT          134 /* Max errno + 1 */
#define __ELIMIT          4096 /* Max possible errno */

#endif /* !_ASM_OS_KOS_ERRNO_H */
