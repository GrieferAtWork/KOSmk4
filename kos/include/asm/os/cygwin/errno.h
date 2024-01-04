/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_CYGWIN_ERRNO_H
#define _ASM_OS_CYGWIN_ERRNO_H 1

#include <__stdinc.h>

#include <sys/config.h> /* __LINUX_ERRNO_EXTENSIONS__ */

/************************************************************************/
/* CYGWIN                                                               */
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
#define __ETXTBSY         26  /* Text file busy */
#define __EFBIG           27  /* File too large */
#define __ENOSPC          28  /* No space left on device */
#define __ESPIPE          29  /* Illegal seek */
#define __EROFS           30  /* Read-only file system */
#define __EMLINK          31  /* Too many links */
#define __EPIPE           32  /* Broken pipe */
#define __EDOM            33  /* Math argument out of domain of func */
#define __ERANGE          34  /* Math result not representable */
#define __ENOMSG          35  /* No message of desired type */
#define __EIDRM           36  /* Identifier removed */
#define __EDEADLK         45  /* Resource deadlock would occur */
#define __ENOLCK          46  /* No record locks available */
#define __ENOSTR          60  /* Device not a stream */
#define __ENODATA         61  /* No data available */
#define __ETIME           62  /* Timer expired */
#define __ENOSR           63  /* Out of streams resources */
#define __ENOLINK         67  /* Link has been severed */
#define __EPROTO          71  /* Protocol error */
#define __EMULTIHOP       74  /* Multihop attempted */
#define __EBADMSG         77  /* Not a data message */
#define __EFTYPE          79  /* [kos(EBADFD)] Inappropriate file type or format */
#define __ENOSYS          88  /* Function not implemented */
#define __ENMFILE         89  /* [kos(ENODATA)] No more files */
#define __ENOTEMPTY       90  /* Directory not empty */
#define __ENAMETOOLONG    91  /* File name too long */
#define __ELOOP           92  /* Too many symbolic links encountered */
#define __EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define __EPFNOSUPPORT    96  /* Protocol family not supported */
#define __ECONNRESET      104 /* Connection reset by peer */
#define __ENOBUFS         105 /* No buffer space available */
#define __EAFNOSUPPORT    106 /* Address family not supported by protocol */
#define __EPROTOTYPE      107 /* Protocol wrong type for socket */
#define __ENOTSOCK        108 /* Socket operation on non-socket */
#define __ENOPROTOOPT     109 /* Protocol not available */
#define __ECONNREFUSED    111 /* Connection refused */
#define __EADDRINUSE      112 /* Address already in use */
#define __ECONNABORTED    113 /* Software caused connection abort */
#define __ENETUNREACH     114 /* Network is unreachable */
#define __ENETDOWN        115 /* Network is down */
#define __ETIMEDOUT       116 /* Connection timed out */
#define __EHOSTDOWN       117 /* Host is down */
#define __EHOSTUNREACH    118 /* No route to host */
#define __EINPROGRESS     119 /* Operation now in progress */
#define __EALREADY        120 /* Operation already in progress */
#define __EDESTADDRREQ    121 /* Destination address required */
#define __EMSGSIZE        122 /* Message too long */
#define __EPROTONOSUPPORT 123 /* Protocol not supported */
#define __EADDRNOTAVAIL   125 /* Cannot assign requested address */
#define __ENETRESET       126 /* Network dropped connection because of reset */
#define __EISCONN         127 /* Transport endpoint is already connected */
#define __ENOTCONN        128 /* Transport endpoint is not connected */
#define __ETOOMANYREFS    129 /* Too many references: cannot splice */
#define __EDQUOT          132 /* Quota exceeded */
#define __ESTALE          133 /* Stale file handle */
#define __ENOTSUP         134 /* Not supported */
#define __ENOSHARE        136 /* [kos(ENOENT)] No such host or network path */
#define __ECASECLASH      137 /* [kos(EEXIST)] Filename exists with different case */
#define __EILSEQ          138 /* Illegal byte sequence */
#define __EOVERFLOW       139 /* Value too large for defined data type */
#define __ECANCELED       140 /* Operation canceled */
#define __ENOTRECOVERABLE 141 /* State not recoverable */
#define __EOWNERDEAD      142 /* Owner died */
#ifdef __LINUX_ERRNO_EXTENSIONS__
#define __ENOTBLK         15  /* Block device required */
#define __ECHRNG          37  /* Channel number out of range */
#define __EL2NSYNC        38  /* Level 2 not synchronized */
#define __EL3HLT          39  /* Level 3 halted */
#define __EL3RST          40  /* Level 3 reset */
#define __ELNRNG          41  /* Link number out of range */
#define __EUNATCH         42  /* Protocol driver not attached */
#define __ENOCSI          43  /* No CSI structure available */
#define __EL2HLT          44  /* Level 2 halted */
#define __EBADE           50  /* Invalid exchange */
#define __EBADR           51  /* Invalid request descriptor */
#define __EXFULL          52  /* Exchange full */
#define __ENOANO          53  /* No anode */
#define __EBADRQC         54  /* Invalid request code */
#define __EBADSLT         55  /* Invalid slot */
#define __EDEADLOCK       56  /* Resource deadlock would occur */
#define __EBFONT          57  /* Bad font file format */
#define __ENONET          64  /* Machine is not on the network */
#define __ENOPKG          65  /* Package not installed */
#define __EREMOTE         66  /* Object is remote */
#define __EADV            68  /* Advertise error */
#define __ESRMNT          69  /* Srmount error */
#define __ECOMM           70  /* Communication error on send */
#define __ELBIN           75  /* [kos(ENOENT)] Inode is remote (not really error) */
#define __EDOTDOT         76  /* RFS specific error */
#define __ENOTUNIQ        80  /* Name not unique on network */
#define __EBADFD          81  /* File descriptor in bad state */
#define __EREMCHG         82  /* Remote address changed */
#define __ELIBACC         83  /* Can not access a needed shared library */
#define __ELIBBAD         84  /* Accessing a corrupted shared library */
#define __ELIBSCN         85  /* .lib section in a.out corrupted */
#define __ELIBMAX         86  /* Attempting to link in too many shared libraries */
#define __ELIBEXEC        87  /* Cannot exec a shared library directly */
#define __ESHUTDOWN       110 /* Cannot send after transport endpoint shutdown */
#define __ESOCKTNOSUPPORT 124 /* Socket type not supported */
#define __EPROCLIM        130 /* [kos(ENOMEM)] Process limit reached */
#define __EUSERS          131 /* Too many users */
#define __ENOMEDIUM       135 /* No medium found */
#define __ESTRPIPE        143 /* Streams pipe error */
#endif /* __LINUX_ERRNO_EXTENSIONS__ */
/*[[[end]]]*/

#define __EMAX       143  /* Max errno */
#define __ECOUNT     144  /* Max errno + 1 */
#define __ELASTERROR 2000 /* Users can add values starting here */
#define __ELIMIT     4096 /* Max possible errno */

#endif /* !_ASM_OS_CYGWIN_ERRNO_H */
