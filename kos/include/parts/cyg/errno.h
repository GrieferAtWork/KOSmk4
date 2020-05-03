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
#ifndef _PARTS_CYG_ERRNO_H
#define _PARTS_CYG_ERRNO_H 1

#include <sys/config.h>

/* Cygwin errno values. NOTE: Taken from `/usr/include/sys/errno.h' */
#define __CYG_EPERM           1   /* Not owner */
#define __CYG_ENOENT          2   /* No such file or directory */
#define __CYG_ESRCH           3   /* No such process */
#define __CYG_EINTR           4   /* Interrupted system call */
#define __CYG_EIO             5   /* I/O error */
#define __CYG_ENXIO           6   /* No such device or address */
#define __CYG_E2BIG           7   /* Argument list too long */
#define __CYG_ENOEXEC         8   /* Exec format error */
#define __CYG_EBADF           9   /* Bad file number */
#define __CYG_ECHILD          10  /* No children */
#define __CYG_EAGAIN          11  /* No more processes */
#define __CYG_ENOMEM          12  /* Not enough space */
#define __CYG_EACCES          13  /* Permission denied */
#define __CYG_EFAULT          14  /* Bad address */
#define __CYG_EBUSY           16  /* Device or resource busy */
#define __CYG_EEXIST          17  /* File exists */
#define __CYG_EXDEV           18  /* Cross-device link */
#define __CYG_ENODEV          19  /* No such device */
#define __CYG_ENOTDIR         20  /* Not a directory */
#define __CYG_EISDIR          21  /* Is a directory */
#define __CYG_EINVAL          22  /* Invalid argument */
#define __CYG_ENFILE          23  /* Too many open files in system */
#define __CYG_EMFILE          24  /* File descriptor value too large */
#define __CYG_ENOTTY          25  /* Not a character device */
#define __CYG_ETXTBSY         26  /* Text file busy */
#define __CYG_EFBIG           27  /* File too large */
#define __CYG_ENOSPC          28  /* No space left on device */
#define __CYG_ESPIPE          29  /* Illegal seek */
#define __CYG_EROFS           30  /* Read-only file system */
#define __CYG_EMLINK          31  /* Too many links */
#define __CYG_EPIPE           32  /* Broken pipe */
#define __CYG_EDOM            33  /* Mathematics argument out of domain of function */
#define __CYG_ERANGE          34  /* Result too large */
#define __CYG_ENOMSG          35  /* No message of desired type */
#define __CYG_EIDRM           36  /* Identifier removed */
#define __CYG_EDEADLK         45  /* Deadlock */
#define __CYG_ENOLCK          46  /* No lock */
#define __CYG_ENOSTR          60  /* Not a stream */
#define __CYG_ENODATA         61  /* No data (for no delay io) */
#define __CYG_ETIME           62  /* Stream ioctl timeout */
#define __CYG_ENOSR           63  /* No stream resources */
#define __CYG_ENOLINK         67  /* Virtual circuit is gone */
#define __CYG_EPROTO          71  /* Protocol error */
#define __CYG_EMULTIHOP       74  /* Multihop attempted */
#define __CYG_EBADMSG         77  /* Bad message */
#define __CYG_EFTYPE          79  /* Inappropriate file type or format */
#define __CYG_ENOSYS          88  /* Function not implemented */
#define __CYG_ENMFILE         89  /* No more files */
#define __CYG_ENOTEMPTY       90  /* Directory not empty */
#define __CYG_ENAMETOOLONG    91  /* File or path name too long */
#define __CYG_ELOOP           92  /* Too many symbolic links */
#define __CYG_EOPNOTSUPP      95  /* Operation not supported on socket */
#define __CYG_EPFNOSUPPORT    96  /* Protocol family not supported */
#define __CYG_ECONNRESET      104 /* Connection reset by peer */
#define __CYG_ENOBUFS         105 /* No buffer space available */
#define __CYG_EAFNOSUPPORT    106 /* Address family not supported by protocol family */
#define __CYG_EPROTOTYPE      107 /* Protocol wrong type for socket */
#define __CYG_ENOTSOCK        108 /* Socket operation on non-socket */
#define __CYG_ENOPROTOOPT     109 /* Protocol not available */
#define __CYG_ECONNREFUSED    111 /* Connection refused */
#define __CYG_EADDRINUSE      112 /* Address already in use */
#define __CYG_ECONNABORTED    113 /* Software caused connection abort */
#define __CYG_ENETUNREACH     114 /* Network is unreachable */
#define __CYG_ENETDOWN        115 /* Network interface is not configured */
#define __CYG_ETIMEDOUT       116 /* Connection timed out */
#define __CYG_EHOSTDOWN       117 /* Host is down */
#define __CYG_EHOSTUNREACH    118 /* Host is unreachable */
#define __CYG_EINPROGRESS     119 /* Connection already in progress */
#define __CYG_EALREADY        120 /* Socket already connected */
#define __CYG_EDESTADDRREQ    121 /* Destination address required */
#define __CYG_EMSGSIZE        122 /* Message too long */
#define __CYG_EPROTONOSUPPORT 123 /* Unknown protocol */
#define __CYG_EADDRNOTAVAIL   125 /* Address not available */
#define __CYG_ENETRESET       126 /* Connection aborted by network */
#define __CYG_EISCONN         127 /* Socket is already connected */
#define __CYG_ENOTCONN        128 /* Socket is not connected */
#define __CYG_ETOOMANYREFS    129 /* Too many references: cannot splice */
#define __CYG_EDQUOT          132 /* Quota exceeded */
#define __CYG_ESTALE          133 /* Stale file handle */
#define __CYG_ENOTSUP         134 /* Not supported */
#define __CYG_ENOSHARE        136 /* No such host or network path */
#define __CYG_ECASECLASH      137 /* Filename exists with different case */
#define __CYG_EILSEQ          138 /* Illegal byte sequence */
#define __CYG_EOVERFLOW       139 /* Value too large for defined data type */
#define __CYG_ECANCELED       140 /* Operation canceled */
#define __CYG_ENOTRECOVERABLE 141 /* State not recoverable */
#define __CYG_EOWNERDEAD      142 /* Previous owner died */
#define __CYG_EWOULDBLOCK     __CYG_EAGAIN /* Operation would block */

#ifdef __LINUX_ERRNO_EXTENSIONS__
#define __CYG_ENOTBLK         15  /* Block device required */
#define __CYG_ECHRNG          37  /* Channel number out of range */
#define __CYG_EL2NSYNC        38  /* Level 2 not synchronized */
#define __CYG_EL3HLT          39  /* Level 3 halted */
#define __CYG_EL3RST          40  /* Level 3 reset */
#define __CYG_ELNRNG          41  /* Link number out of range */
#define __CYG_EUNATCH         42  /* Protocol driver not attached */
#define __CYG_ENOCSI          43  /* No CSI structure available */
#define __CYG_EL2HLT          44  /* Level 2 halted */
#define __CYG_EBADE           50  /* Invalid exchange */
#define __CYG_EBADR           51  /* Invalid request descriptor */
#define __CYG_EXFULL          52  /* Exchange full */
#define __CYG_ENOANO          53  /* No anode */
#define __CYG_EBADRQC         54  /* Invalid request code */
#define __CYG_EBADSLT         55  /* Invalid slot */
#define __CYG_EDEADLOCK       56  /* File locking deadlock error */
#define __CYG_EBFONT          57  /* Bad font file fmt */
#define __CYG_ENONET          64  /* Machine is not on the network */
#define __CYG_ENOPKG          65  /* Package not installed */
#define __CYG_EREMOTE         66  /* The object is remote */
#define __CYG_EADV            68  /* Advertise error */
#define __CYG_ESRMNT          69  /* Srmount error */
#define __CYG_ECOMM           70  /* Communication error on send */
#define __CYG_ELBIN           75  /* Inode is remote (not really error) */
#define __CYG_EDOTDOT         76  /* Cross mount point (not really error) */
#define __CYG_ENOTUNIQ        80  /* Given log. name not unique */
#define __CYG_EBADFD          81  /* f.d. invalid for this operation */
#define __CYG_EREMCHG         82  /* Remote address changed */
#define __CYG_ELIBACC         83  /* Can't access a needed shared lib */
#define __CYG_ELIBBAD         84  /* Accessing a corrupted shared lib */
#define __CYG_ELIBSCN         85  /* .lib section in a.out corrupted */
#define __CYG_ELIBMAX         86  /* Attempting to link in too many libs */
#define __CYG_ELIBEXEC        87  /* Attempting to exec a shared library */
#define __CYG_ESHUTDOWN       110 /* Can't send after socket shutdown */
#define __CYG_ESOCKTNOSUPPORT 124 /* Socket type not supported */
#define __CYG_EPROCLIM        130 /* Process limit reached */
#define __CYG_EUSERS          131 /* Too many users */
#define __CYG_ENOMEDIUM       135 /* No medium (in tape drive) */
#define __CYG_ESTRPIPE        143 /* Streams pipe error */
#endif /* !__LINUX_ERRNO_EXTENSIONS__ */
#define __CYG_ECOUNT          144 /* Max errno + 1 */

#define __CYG_ELASTERROR 2000   /* Users can add values starting here */

#endif /* !_PARTS_CYG_ERRNO_H */
