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
#ifndef _PARTS_ERRNO_H
#define _PARTS_ERRNO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __CRT_DOS_PRIMARY
#include <parts/dos/errno.h>
#define __EPERM           __DOS_EPERM           /* Operation not permitted */
#define __ENOENT          __DOS_ENOENT          /* No such file or directory */
#define __ESRCH           __DOS_ESRCH           /* No such process */
#define __EINTR           __DOS_EINTR           /* Interrupted system call */
#define __EIO             __DOS_EIO             /* I/O error */
#define __ENXIO           __DOS_ENXIO           /* No such device or address */
#define __E2BIG           __DOS_E2BIG           /* Argument list too long */
#define __ENOEXEC         __DOS_ENOEXEC         /* Exec format error */
#define __EBADF           __DOS_EBADF           /* Bad file number */
#define __ECHILD          __DOS_ECHILD          /* No child processes */
#define __EAGAIN          __DOS_EAGAIN          /* Try again */
#define __ENOMEM          __DOS_ENOMEM          /* Out of memory */
#define __EACCES          __DOS_EACCES          /* Permission denied */
#define __EFAULT          __DOS_EFAULT          /* Bad address */
#define __EBUSY           __DOS_EBUSY           /* Device or resource busy */
#define __EEXIST          __DOS_EEXIST          /* File exists */
#define __EXDEV           __DOS_EXDEV           /* Cross-device link */
#define __ENODEV          __DOS_ENODEV          /* No such device */
#define __ENOTDIR         __DOS_ENOTDIR         /* Not a directory */
#define __EISDIR          __DOS_EISDIR          /* Is a directory */
#define __ENFILE          __DOS_ENFILE          /* File table overflow */
#define __EMFILE          __DOS_EMFILE          /* Too many open files */
#define __ENOTTY          __DOS_ENOTTY          /* Not a typewriter */
#define __EFBIG           __DOS_EFBIG           /* File too large */
#define __ENOSPC          __DOS_ENOSPC          /* No space left on device */
#define __ESPIPE          __DOS_ESPIPE          /* Illegal seek */
#define __EROFS           __DOS_EROFS           /* Read-only file system */
#define __EMLINK          __DOS_EMLINK          /* Too many links */
#define __EPIPE           __DOS_EPIPE           /* Broken pipe */
#define __EDOM            __DOS_EDOM            /* Math argument out of domain of func */
#define __EDEADLK         __DOS_EDEADLK         /* Resource deadlock would occur */
#define __ENAMETOOLONG    __DOS_ENAMETOOLONG    /* File name too long */
#define __ENOLCK          __DOS_ENOLCK          /* No record locks available */
#define __ENOSYS          __DOS_ENOSYS          /* Function not implemented */
#define __ENOTEMPTY       __DOS_ENOTEMPTY       /* Directory not empty */
#define __EINVAL          __DOS_EINVAL          /* Invalid argument */
#define __ERANGE          __DOS_ERANGE          /* Math result not representable */
#define __EILSEQ          __DOS_EILSEQ          /* Illegal byte sequence */
#define __STRUNCATE       __DOS_STRUNCATE       /* Truncated */
#define __EDEADLOCK       __DOS_EDEADLOCK       /* Resource deadlock would occur */
#define __EADDRINUSE      __DOS_EADDRINUSE      /* Address already in use */
#define __EADDRNOTAVAIL   __DOS_EADDRNOTAVAIL   /* Cannot assign requested address */
#define __EAFNOSUPPORT    __DOS_EAFNOSUPPORT    /* Address family not supported by protocol */
#define __EALREADY        __DOS_EALREADY        /* Operation already in progress */
#define __EBADMSG         __DOS_EBADMSG         /* Not a data message */
#define __ECANCELED       __DOS_ECANCELED       /* Operation Canceled */
#define __ECONNABORTED    __DOS_ECONNABORTED    /* Software caused connection abort */
#define __ECONNREFUSED    __DOS_ECONNREFUSED    /* Connection refused */
#define __ECONNRESET      __DOS_ECONNRESET      /* Connection reset by peer */
#define __EDESTADDRREQ    __DOS_EDESTADDRREQ    /* Destination address required */
#define __EHOSTUNREACH    __DOS_EHOSTUNREACH    /* No route to host */
#define __EIDRM           __DOS_EIDRM           /* Identifier removed */
#define __EINPROGRESS     __DOS_EINPROGRESS     /* Operation now in progress */
#define __EISCONN         __DOS_EISCONN         /* Transport endpoint is already connected */
#define __ELOOP           __DOS_ELOOP           /* Too many symbolic links encountered */
#define __EMSGSIZE        __DOS_EMSGSIZE        /* Message too long */
#define __ENETDOWN        __DOS_ENETDOWN        /* Network is down */
#define __ENETRESET       __DOS_ENETRESET       /* Network dropped connection because of reset */
#define __ENETUNREACH     __DOS_ENETUNREACH     /* Network is unreachable */
#define __ENOBUFS         __DOS_ENOBUFS         /* No buffer space available */
#define __ENODATA         __DOS_ENODATA         /* No data available */
#define __ENOLINK         __DOS_ENOLINK         /* Link has been severed */
#define __ENOMSG          __DOS_ENOMSG          /* No message of desired type */
#define __ENOPROTOOPT     __DOS_ENOPROTOOPT     /* Protocol not available */
#define __ENOSR           __DOS_ENOSR           /* Out of streams resources */
#define __ENOSTR          __DOS_ENOSTR          /* Device not a stream */
#define __ENOTCONN        __DOS_ENOTCONN        /* Transport endpoint is not connected */
#define __ENOTRECOVERABLE __DOS_ENOTRECOVERABLE /* State not recoverable */
#define __ENOTSOCK        __DOS_ENOTSOCK        /* Socket operation on non-socket */
#define __ENOTSUP         __DOS_ENOTSUP         /* Not supported */
#define __EOPNOTSUPP      __DOS_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define __EOTHER          __DOS_EOTHER          /* Other */
#define __EOVERFLOW       __DOS_EOVERFLOW       /* Value too large for defined data type */
#define __EOWNERDEAD      __DOS_EOWNERDEAD      /* Owner died */
#define __EPROTO          __DOS_EPROTO          /* Protocol error */
#define __EPROTONOSUPPORT __DOS_EPROTONOSUPPORT /* Protocol not supported */
#define __EPROTOTYPE      __DOS_EPROTOTYPE      /* Protocol wrong type for socket */
#define __ETIME           __DOS_ETIME           /* Timer expired */
#define __ETIMEDOUT       __DOS_ETIMEDOUT       /* Connection timed out */
#define __ETXTBSY         __DOS_ETXTBSY         /* Text file busy */
#define __EWOULDBLOCK     __DOS_EWOULDBLOCK     /* Operation would block */
#define __ECOUNT          __DOS_ECOUNT          /* Max errno + 1 */
#elif defined(__CRT_CYG_PRIMARY)
#include <parts/cyg/errno.h>
#define __EPERM           __CYG_EPERM           /* Not owner */
#define __ENOENT          __CYG_ENOENT          /* No such file or directory */
#define __ESRCH           __CYG_ESRCH           /* No such process */
#define __EINTR           __CYG_EINTR           /* Interrupted system call */
#define __EIO             __CYG_EIO             /* I/O error */
#define __ENXIO           __CYG_ENXIO           /* No such device or address */
#define __E2BIG           __CYG_E2BIG           /* Argument list too long */
#define __ENOEXEC         __CYG_ENOEXEC         /* Exec format error */
#define __EBADF           __CYG_EBADF           /* Bad file number */
#define __ECHILD          __CYG_ECHILD          /* No children */
#define __EAGAIN          __CYG_EAGAIN          /* No more processes */
#define __ENOMEM          __CYG_ENOMEM          /* Not enough space */
#define __EACCES          __CYG_EACCES          /* Permission denied */
#define __EFAULT          __CYG_EFAULT          /* Bad address */
#define __EBUSY           __CYG_EBUSY           /* Device or resource busy */
#define __EEXIST          __CYG_EEXIST          /* File exists */
#define __EXDEV           __CYG_EXDEV           /* Cross-device link */
#define __ENODEV          __CYG_ENODEV          /* No such device */
#define __ENOTDIR         __CYG_ENOTDIR         /* Not a directory */
#define __EISDIR          __CYG_EISDIR          /* Is a directory */
#define __EINVAL          __CYG_EINVAL          /* Invalid argument */
#define __ENFILE          __CYG_ENFILE          /* Too many open files in system */
#define __EMFILE          __CYG_EMFILE          /* File descriptor value too large */
#define __ENOTTY          __CYG_ENOTTY          /* Not a character device */
#define __ETXTBSY         __CYG_ETXTBSY         /* Text file busy */
#define __EFBIG           __CYG_EFBIG           /* File too large */
#define __ENOSPC          __CYG_ENOSPC          /* No space left on device */
#define __ESPIPE          __CYG_ESPIPE          /* Illegal seek */
#define __EROFS           __CYG_EROFS           /* Read-only file system */
#define __EMLINK          __CYG_EMLINK          /* Too many links */
#define __EPIPE           __CYG_EPIPE           /* Broken pipe */
#define __EDOM            __CYG_EDOM            /* Mathematics argument out of domain of function */
#define __ERANGE          __CYG_ERANGE          /* Result too large */
#define __ENOMSG          __CYG_ENOMSG          /* No message of desired type */
#define __EIDRM           __CYG_EIDRM           /* Identifier removed */
#define __EDEADLK         __CYG_EDEADLK         /* Deadlock */
#define __ENOLCK          __CYG_ENOLCK          /* No lock */
#define __ENOSTR          __CYG_ENOSTR          /* Not a stream */
#define __ENODATA         __CYG_ENODATA         /* No data (for no delay io) */
#define __ETIME           __CYG_ETIME           /* Stream ioctl timeout */
#define __ENOSR           __CYG_ENOSR           /* No stream resources */
#define __ENOLINK         __CYG_ENOLINK         /* Virtual circuit is gone */
#define __EPROTO          __CYG_EPROTO          /* Protocol error */
#define __EMULTIHOP       __CYG_EMULTIHOP       /* Multihop attempted */
#define __EBADMSG         __CYG_EBADMSG         /* Bad message */
#define __EFTYPE          __CYG_EFTYPE          /* Inappropriate file type or format */
#define __ENOSYS          __CYG_ENOSYS          /* Function not implemented */
#define __ENMFILE         __CYG_ENMFILE         /* No more files */
#define __ENOTEMPTY       __CYG_ENOTEMPTY       /* Directory not empty */
#define __ENAMETOOLONG    __CYG_ENAMETOOLONG    /* File or path name too long */
#define __ELOOP           __CYG_ELOOP           /* Too many symbolic links */
#define __EOPNOTSUPP      __CYG_EOPNOTSUPP      /* Operation not supported on socket */
#define __EPFNOSUPPORT    __CYG_EPFNOSUPPORT    /* Protocol family not supported */
#define __ECONNRESET      __CYG_ECONNRESET      /* Connection reset by peer */
#define __ENOBUFS         __CYG_ENOBUFS         /* No buffer space available */
#define __EAFNOSUPPORT    __CYG_EAFNOSUPPORT    /* Address family not supported by protocol family */
#define __EPROTOTYPE      __CYG_EPROTOTYPE      /* Protocol wrong type for socket */
#define __ENOTSOCK        __CYG_ENOTSOCK        /* Socket operation on non-socket */
#define __ENOPROTOOPT     __CYG_ENOPROTOOPT     /* Protocol not available */
#define __ECONNREFUSED    __CYG_ECONNREFUSED    /* Connection refused */
#define __EADDRINUSE      __CYG_EADDRINUSE      /* Address already in use */
#define __ECONNABORTED    __CYG_ECONNABORTED    /* Software caused connection abort */
#define __ENETUNREACH     __CYG_ENETUNREACH     /* Network is unreachable */
#define __ENETDOWN        __CYG_ENETDOWN        /* Network interface is not configured */
#define __ETIMEDOUT       __CYG_ETIMEDOUT       /* Connection timed out */
#define __EHOSTDOWN       __CYG_EHOSTDOWN       /* Host is down */
#define __EHOSTUNREACH    __CYG_EHOSTUNREACH    /* Host is unreachable */
#define __EINPROGRESS     __CYG_EINPROGRESS     /* Connection already in progress */
#define __EALREADY        __CYG_EALREADY        /* Socket already connected */
#define __EDESTADDRREQ    __CYG_EDESTADDRREQ    /* Destination address required */
#define __EMSGSIZE        __CYG_EMSGSIZE        /* Message too long */
#define __EPROTONOSUPPORT __CYG_EPROTONOSUPPORT /* Unknown protocol */
#define __EADDRNOTAVAIL   __CYG_EADDRNOTAVAIL   /* Address not available */
#define __ENETRESET       __CYG_ENETRESET       /* Connection aborted by network */
#define __EISCONN         __CYG_EISCONN         /* Socket is already connected */
#define __ENOTCONN        __CYG_ENOTCONN        /* Socket is not connected */
#define __ETOOMANYREFS    __CYG_ETOOMANYREFS    /* Too many references: cannot splice */
#define __EDQUOT          __CYG_EDQUOT          /* Quota exceeded */
#define __ESTALE          __CYG_ESTALE          /* Stale file handle */
#define __ENOTSUP         __CYG_ENOTSUP         /* Not supported */
#define __ENOSHARE        __CYG_ENOSHARE        /* No such host or network path */
#define __ECASECLASH      __CYG_ECASECLASH      /* Filename exists with different case */
#define __EILSEQ          __CYG_EILSEQ          /* Illegal byte sequence */
#define __EOVERFLOW       __CYG_EOVERFLOW       /* Value too large for defined data type */
#define __ECANCELED       __CYG_ECANCELED       /* Operation canceled */
#define __ENOTRECOVERABLE __CYG_ENOTRECOVERABLE /* State not recoverable */
#define __EOWNERDEAD      __CYG_EOWNERDEAD      /* Previous owner died */
#define __EWOULDBLOCK     __CYG_EWOULDBLOCK     /* Operation would block */
#ifdef __LINUX_ERRNO_EXTENSIONS__
#define __ENOTBLK         __CYG_ENOTBLK         /* Block device required */
#define __ECHRNG          __CYG_ECHRNG          /* Channel number out of range */
#define __EL2NSYNC        __CYG_EL2NSYNC        /* Level 2 not synchronized */
#define __EL3HLT          __CYG_EL3HLT          /* Level 3 halted */
#define __EL3RST          __CYG_EL3RST          /* Level 3 reset */
#define __ELNRNG          __CYG_ELNRNG          /* Link number out of range */
#define __EUNATCH         __CYG_EUNATCH         /* Protocol driver not attached */
#define __ENOCSI          __CYG_ENOCSI          /* No CSI structure available */
#define __EL2HLT          __CYG_EL2HLT          /* Level 2 halted */
#define __EBADE           __CYG_EBADE           /* Invalid exchange */
#define __EBADR           __CYG_EBADR           /* Invalid request descriptor */
#define __EXFULL          __CYG_EXFULL          /* Exchange full */
#define __ENOANO          __CYG_ENOANO          /* No anode */
#define __EBADRQC         __CYG_EBADRQC         /* Invalid request code */
#define __EBADSLT         __CYG_EBADSLT         /* Invalid slot */
#define __EDEADLOCK       __CYG_EDEADLOCK       /* File locking deadlock error */
#define __EBFONT          __CYG_EBFONT          /* Bad font file fmt */
#define __ENONET          __CYG_ENONET          /* Machine is not on the network */
#define __ENOPKG          __CYG_ENOPKG          /* Package not installed */
#define __EREMOTE         __CYG_EREMOTE         /* The object is remote */
#define __EADV            __CYG_EADV            /* Advertise error */
#define __ESRMNT          __CYG_ESRMNT          /* Srmount error */
#define __ECOMM           __CYG_ECOMM           /* Communication error on send */
#define __ELBIN           __CYG_ELBIN           /* Inode is remote (not really error) */
#define __EDOTDOT         __CYG_EDOTDOT         /* Cross mount point (not really error) */
#define __ENOTUNIQ        __CYG_ENOTUNIQ        /* Given log. name not unique */
#define __EBADFD          __CYG_EBADFD          /* f.d. invalid for this operation */
#define __EREMCHG         __CYG_EREMCHG         /* Remote address changed */
#define __ELIBACC         __CYG_ELIBACC         /* Can't access a needed shared lib */
#define __ELIBBAD         __CYG_ELIBBAD         /* Accessing a corrupted shared lib */
#define __ELIBSCN         __CYG_ELIBSCN         /* .lib section in a.out corrupted */
#define __ELIBMAX         __CYG_ELIBMAX         /* Attempting to link in too many libs */
#define __ELIBEXEC        __CYG_ELIBEXEC        /* Attempting to exec a shared library */
#define __ESHUTDOWN       __CYG_ESHUTDOWN       /* Can't send after socket shutdown */
#define __ESOCKTNOSUPPORT __CYG_ESOCKTNOSUPPORT /* Socket type not supported */
#define __EPROCLIM        __CYG_EPROCLIM        /* Process limit reached */
#define __EUSERS          __CYG_EUSERS          /* Too many users */
#define __ENOMEDIUM       __CYG_ENOMEDIUM       /* No medium (in tape drive) */
#define __ESTRPIPE        __CYG_ESTRPIPE        /* Streams pipe error */
#endif /* __LINUX_ERRNO_EXTENSIONS__ */
#define __ECOUNT          __CYG_ECOUNT          /* Max errno + 1 */
#elif defined(__CRT_GLC_PRIMARY)
#include <parts/glibc/errno.h>
#define __EPERM           __GLC_EPERM           /* Operation not permitted */
#define __ENOENT          __GLC_ENOENT          /* No such file or directory */
#define __ESRCH           __GLC_ESRCH           /* No such process */
#define __EINTR           __GLC_EINTR           /* Interrupted system call */
#define __EIO             __GLC_EIO             /* I/O error */
#define __ENXIO           __GLC_ENXIO           /* No such device or address */
#define __E2BIG           __GLC_E2BIG           /* Argument list too long */
#define __ENOEXEC         __GLC_ENOEXEC         /* Exec format error */
#define __EBADF           __GLC_EBADF           /* Bad file number */
#define __ECHILD          __GLC_ECHILD          /* No child processes */
#define __EAGAIN          __GLC_EAGAIN          /* Try again */
#define __ENOMEM          __GLC_ENOMEM          /* Out of memory */
#define __EACCES          __GLC_EACCES          /* Permission denied */
#define __EFAULT          __GLC_EFAULT          /* Bad address */
#define __ENOTBLK         __GLC_ENOTBLK         /* Block device required */
#define __EBUSY           __GLC_EBUSY           /* Device or resource busy */
#define __EEXIST          __GLC_EEXIST          /* File exists */
#define __EXDEV           __GLC_EXDEV           /* Cross-device link */
#define __ENODEV          __GLC_ENODEV          /* No such device */
#define __ENOTDIR         __GLC_ENOTDIR         /* Not a directory */
#define __EISDIR          __GLC_EISDIR          /* Is a directory */
#define __EINVAL          __GLC_EINVAL          /* [NT("ERROR_INVALID_PARAMETER")] Invalid argument */
#define __ENFILE          __GLC_ENFILE          /* File table overflow */
#define __EMFILE          __GLC_EMFILE          /* Too many open files */
#define __ENOTTY          __GLC_ENOTTY          /* Not a typewriter */
#define __ETXTBSY         __GLC_ETXTBSY         /* Text file busy */
#define __EFBIG           __GLC_EFBIG           /* File too large */
#define __ENOSPC          __GLC_ENOSPC          /* No space left on device */
#define __ESPIPE          __GLC_ESPIPE          /* Illegal seek */
#define __EROFS           __GLC_EROFS           /* Read-only file system */
#define __EMLINK          __GLC_EMLINK          /* Too many links */
#define __EPIPE           __GLC_EPIPE           /* Broken pipe */
#define __EDOM            __GLC_EDOM            /* Math argument out of domain of func */
#define __ERANGE          __GLC_ERANGE          /* [NT("ERROR_INSUFFICIENT_BUFFER")] Math result not representable */
#define __EDEADLK         __GLC_EDEADLK         /* Resource deadlock would occur */
#define __ENAMETOOLONG    __GLC_ENAMETOOLONG    /* File name too long */
#define __ENOLCK          __GLC_ENOLCK          /* No record locks available */
#define __ENOSYS          __GLC_ENOSYS          /* Invalid system call number */
#define __ENOTEMPTY       __GLC_ENOTEMPTY       /* Directory not empty */
#define __ELOOP           __GLC_ELOOP           /* Too many symbolic links encountered */
#define __EWOULDBLOCK     __GLC_EWOULDBLOCK     /* Operation would block */
#define __ENOMSG          __GLC_ENOMSG          /* No message of desired type */
#define __EIDRM           __GLC_EIDRM           /* Identifier removed */
#define __ECHRNG          __GLC_ECHRNG          /* Channel number out of range */
#define __EL2NSYNC        __GLC_EL2NSYNC        /* Level 2 not synchronized */
#define __EL3HLT          __GLC_EL3HLT          /* Level 3 halted */
#define __EL3RST          __GLC_EL3RST          /* Level 3 reset */
#define __ELNRNG          __GLC_ELNRNG          /* Link number out of range */
#define __EUNATCH         __GLC_EUNATCH         /* Protocol driver not attached */
#define __ENOCSI          __GLC_ENOCSI          /* No CSI structure available */
#define __EL2HLT          __GLC_EL2HLT          /* Level 2 halted */
#define __EBADE           __GLC_EBADE           /* Invalid exchange */
#define __EBADR           __GLC_EBADR           /* Invalid request descriptor */
#define __EXFULL          __GLC_EXFULL          /* Exchange full */
#define __ENOANO          __GLC_ENOANO          /* No anode */
#define __EBADRQC         __GLC_EBADRQC         /* Invalid request code */
#define __EBADSLT         __GLC_EBADSLT         /* Invalid slot */
#define __EDEADLOCK       __GLC_EDEADLOCK       /* Resource deadlock would occur */
#define __EBFONT          __GLC_EBFONT          /* Bad font file format */
#define __ENOSTR          __GLC_ENOSTR          /* Device not a stream */
#define __ENODATA         __GLC_ENODATA         /* No data available */
#define __ETIME           __GLC_ETIME           /* Timer expired */
#define __ENOSR           __GLC_ENOSR           /* Out of streams resources */
#define __ENONET          __GLC_ENONET          /* Machine is not on the network */
#define __ENOPKG          __GLC_ENOPKG          /* Package not installed */
#define __EREMOTE         __GLC_EREMOTE         /* Object is remote */
#define __ENOLINK         __GLC_ENOLINK         /* Link has been severed */
#define __EADV            __GLC_EADV            /* Advertise error */
#define __ESRMNT          __GLC_ESRMNT          /* Srmount error */
#define __ECOMM           __GLC_ECOMM           /* Communication error on send */
#define __EPROTO          __GLC_EPROTO          /* Protocol error */
#define __EMULTIHOP       __GLC_EMULTIHOP       /* Multihop attempted */
#define __EDOTDOT         __GLC_EDOTDOT         /* RFS specific error */
#define __EBADMSG         __GLC_EBADMSG         /* Not a data message */
#define __EOVERFLOW       __GLC_EOVERFLOW       /* Value too large for defined data type */
#define __ENOTUNIQ        __GLC_ENOTUNIQ        /* Name not unique on network */
#define __EBADFD          __GLC_EBADFD          /* File descriptor in bad state */
#define __EREMCHG         __GLC_EREMCHG         /* Remote address changed */
#define __ELIBACC         __GLC_ELIBACC         /* Can not access a needed shared library */
#define __ELIBBAD         __GLC_ELIBBAD         /* Accessing a corrupted shared library */
#define __ELIBSCN         __GLC_ELIBSCN         /* .lib section in a.out corrupted */
#define __ELIBMAX         __GLC_ELIBMAX         /* Attempting to link in too many shared libraries */
#define __ELIBEXEC        __GLC_ELIBEXEC        /* Cannot exec a shared library directly */
#define __EILSEQ          __GLC_EILSEQ          /* [NT("ERROR_NO_UNICODE_TRANSLATION")] Illegal byte sequence */
#define __ERESTART        __GLC_ERESTART        /* Interrupted system call should be restarted */
#define __ESTRPIPE        __GLC_ESTRPIPE        /* Streams pipe error */
#define __EUSERS          __GLC_EUSERS          /* Too many users */
#define __ENOTSOCK        __GLC_ENOTSOCK        /* Socket operation on non-socket */
#define __EDESTADDRREQ    __GLC_EDESTADDRREQ    /* Destination address required */
#define __EMSGSIZE        __GLC_EMSGSIZE        /* Message too long */
#define __EPROTOTYPE      __GLC_EPROTOTYPE      /* Protocol wrong type for socket */
#define __ENOPROTOOPT     __GLC_ENOPROTOOPT     /* Protocol not available */
#define __EPROTONOSUPPORT __GLC_EPROTONOSUPPORT /* Protocol not supported */
#define __ESOCKTNOSUPPORT __GLC_ESOCKTNOSUPPORT /* Socket type not supported */
#define __EOPNOTSUPP      __GLC_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define __EPFNOSUPPORT    __GLC_EPFNOSUPPORT    /* Protocol family not supported */
#define __EAFNOSUPPORT    __GLC_EAFNOSUPPORT    /* Address family not supported by protocol */
#define __EADDRINUSE      __GLC_EADDRINUSE      /* Address already in use */
#define __EADDRNOTAVAIL   __GLC_EADDRNOTAVAIL   /* Cannot assign requested address */
#define __ENETDOWN        __GLC_ENETDOWN        /* Network is down */
#define __ENETUNREACH     __GLC_ENETUNREACH     /* Network is unreachable */
#define __ENETRESET       __GLC_ENETRESET       /* Network dropped connection because of reset */
#define __ECONNABORTED    __GLC_ECONNABORTED    /* Software caused connection abort */
#define __ECONNRESET      __GLC_ECONNRESET      /* Connection reset by peer */
#define __ENOBUFS         __GLC_ENOBUFS         /* No buffer space available */
#define __EISCONN         __GLC_EISCONN         /* Transport endpoint is already connected */
#define __ENOTCONN        __GLC_ENOTCONN        /* Transport endpoint is not connected */
#define __ESHUTDOWN       __GLC_ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#define __ETOOMANYREFS    __GLC_ETOOMANYREFS    /* Too many references: cannot splice */
#define __ETIMEDOUT       __GLC_ETIMEDOUT       /* Connection timed out */
#define __ECONNREFUSED    __GLC_ECONNREFUSED    /* Connection refused */
#define __EHOSTDOWN       __GLC_EHOSTDOWN       /* Host is down */
#define __EHOSTUNREACH    __GLC_EHOSTUNREACH    /* No route to host */
#define __EALREADY        __GLC_EALREADY        /* Operation already in progress */
#define __EINPROGRESS     __GLC_EINPROGRESS     /* Operation now in progress */
#define __ESTALE          __GLC_ESTALE          /* Stale file handle */
#define __EUCLEAN         __GLC_EUCLEAN         /* Structure needs cleaning */
#define __ENOTNAM         __GLC_ENOTNAM         /* Not a XENIX named type file */
#define __ENAVAIL         __GLC_ENAVAIL         /* No XENIX semaphores available */
#define __EISNAM          __GLC_EISNAM          /* Is a named type file */
#define __EREMOTEIO       __GLC_EREMOTEIO       /* Remote I/O error */
#define __EDQUOT          __GLC_EDQUOT          /* Quota exceeded */
#define __ENOMEDIUM       __GLC_ENOMEDIUM       /* No medium found */
#define __EMEDIUMTYPE     __GLC_EMEDIUMTYPE     /* Wrong medium type */
#define __ECANCELED       __GLC_ECANCELED       /* Operation Canceled */
#define __ENOKEY          __GLC_ENOKEY          /* Required key not available */
#define __EKEYEXPIRED     __GLC_EKEYEXPIRED     /* Key has expired */
#define __EKEYREVOKED     __GLC_EKEYREVOKED     /* Key has been revoked */
#define __EKEYREJECTED    __GLC_EKEYREJECTED    /* Key was rejected by service */
#define __EOWNERDEAD      __GLC_EOWNERDEAD      /* Owner died */
#define __ENOTRECOVERABLE __GLC_ENOTRECOVERABLE /* State not recoverable */
#define __ERFKILL         __GLC_ERFKILL         /* Operation not possible due to RF-kill */
#define __EHWPOISON       __GLC_EHWPOISON       /* Memory page has hardware error */
#define __ECOUNT          __GLC_ECOUNT          /* Max errno + 1 */
#else /* CRT-specific... */
#include <parts/generic/errno.h>
/* Fallback: http://www.virtsync.com/c-error-codes-include-errno
 *   - When I looked it up, that page was the first google result
 *     for `errno.h', so judging by that fact, there shouldn't be
 *     better fallback values for errno codes! */
#define __EPERM           __GEN_EPERM           /* Operation not permitted */
#define __ENOENT          __GEN_ENOENT          /* No such file or directory */
#define __ESRCH           __GEN_ESRCH           /* No such process */
#define __EINTR           __GEN_EINTR           /* Interrupted system call */
#define __EIO             __GEN_EIO             /* I/O error */
#define __ENXIO           __GEN_ENXIO           /* No such device or address */
#define __E2BIG           __GEN_E2BIG           /* Argument list too long */
#define __ENOEXEC         __GEN_ENOEXEC         /* Exec format error */
#define __EBADF           __GEN_EBADF           /* Bad file number */
#define __ECHILD          __GEN_ECHILD          /* No child processes */
#define __EAGAIN          __GEN_EAGAIN          /* Try again */
#define __ENOMEM          __GEN_ENOMEM          /* Out of memory */
#define __EACCES          __GEN_EACCES          /* Permission denied */
#define __EFAULT          __GEN_EFAULT          /* Bad address */
#define __ENOTBLK         __GEN_ENOTBLK         /* Block device required */
#define __EBUSY           __GEN_EBUSY           /* Device or resource busy */
#define __EEXIST          __GEN_EEXIST          /* File exists */
#define __EXDEV           __GEN_EXDEV           /* Cross-device link */
#define __ENODEV          __GEN_ENODEV          /* No such device */
#define __ENOTDIR         __GEN_ENOTDIR         /* Not a directory */
#define __EISDIR          __GEN_EISDIR          /* Is a directory */
#define __EINVAL          __GEN_EINVAL          /* Invalid argument */
#define __ENFILE          __GEN_ENFILE          /* File table overflow */
#define __EMFILE          __GEN_EMFILE          /* Too many open files */
#define __ENOTTY          __GEN_ENOTTY          /* Not a typewriter */
#define __ETXTBSY         __GEN_ETXTBSY         /* Text file busy */
#define __EFBIG           __GEN_EFBIG           /* File too large */
#define __ENOSPC          __GEN_ENOSPC          /* No space left on device */
#define __ESPIPE          __GEN_ESPIPE          /* Illegal seek */
#define __EROFS           __GEN_EROFS           /* Read-only file system */
#define __EMLINK          __GEN_EMLINK          /* Too many links */
#define __EPIPE           __GEN_EPIPE           /* Broken pipe */
#define __EDOM            __GEN_EDOM            /* Math argument out of domain of func */
#define __ERANGE          __GEN_ERANGE          /* Math result not representable */
#define __EDEADLK         __GEN_EDEADLK         /* Resource deadlock would occur */
#define __ENAMETOOLONG    __GEN_ENAMETOOLONG    /* File name too long */
#define __ENOLCK          __GEN_ENOLCK          /* No record locks available */
#define __ENOSYS          __GEN_ENOSYS          /* Function not implemented */
#define __ENOTEMPTY       __GEN_ENOTEMPTY       /* Directory not empty */
#define __ELOOP           __GEN_ELOOP           /* Too many symbolic links encountered */
#define __EWOULDBLOCK     __GEN_EWOULDBLOCK     /* Operation would block */
#define __ENOMSG          __GEN_ENOMSG          /* No message of desired type */
#define __EIDRM           __GEN_EIDRM           /* Identifier removed */
#define __ECHRNG          __GEN_ECHRNG          /* Channel number out of range */
#define __EL2NSYNC        __GEN_EL2NSYNC        /* Level 2 not synchronized */
#define __EL3HLT          __GEN_EL3HLT          /* Level 3 halted */
#define __EL3RST          __GEN_EL3RST          /* Level 3 reset */
#define __ELNRNG          __GEN_ELNRNG          /* Link number out of range */
#define __EUNATCH         __GEN_EUNATCH         /* Protocol driver not attached */
#define __ENOCSI          __GEN_ENOCSI          /* No CSI structure available */
#define __EL2HLT          __GEN_EL2HLT          /* Level 2 halted */
#define __EBADE           __GEN_EBADE           /* Invalid exchange */
#define __EBADR           __GEN_EBADR           /* Invalid request descriptor */
#define __EXFULL          __GEN_EXFULL          /* Exchange full */
#define __ENOANO          __GEN_ENOANO          /* No anode */
#define __EBADRQC         __GEN_EBADRQC         /* Invalid request code */
#define __EBADSLT         __GEN_EBADSLT         /* Invalid slot */
#define __EDEADLOCK       __GEN_EDEADLOCK       /* Resource deadlock would occur */
#define __EBFONT          __GEN_EBFONT          /* Bad font file format */
#define __ENOSTR          __GEN_ENOSTR          /* Device not a stream */
#define __ENODATA         __GEN_ENODATA         /* No data available */
#define __ETIME           __GEN_ETIME           /* Timer expired */
#define __ENOSR           __GEN_ENOSR           /* Out of streams resources */
#define __ENONET          __GEN_ENONET          /* Machine is not on the network */
#define __ENOPKG          __GEN_ENOPKG          /* Package not installed */
#define __EREMOTE         __GEN_EREMOTE         /* Object is remote */
#define __ENOLINK         __GEN_ENOLINK         /* Link has been severed */
#define __EADV            __GEN_EADV            /* Advertise error */
#define __ESRMNT          __GEN_ESRMNT          /* Srmount error */
#define __ECOMM           __GEN_ECOMM           /* Communication error on send */
#define __EPROTO          __GEN_EPROTO          /* Protocol error */
#define __EMULTIHOP       __GEN_EMULTIHOP       /* Multihop attempted */
#define __EDOTDOT         __GEN_EDOTDOT         /* RFS specific error */
#define __EBADMSG         __GEN_EBADMSG         /* Not a data message */
#define __EOVERFLOW       __GEN_EOVERFLOW       /* Value too large for defined data type */
#define __ENOTUNIQ        __GEN_ENOTUNIQ        /* Name not unique on network */
#define __EBADFD          __GEN_EBADFD          /* File descriptor in bad state */
#define __EREMCHG         __GEN_EREMCHG         /* Remote address changed */
#define __ELIBACC         __GEN_ELIBACC         /* Can not access a needed shared library */
#define __ELIBBAD         __GEN_ELIBBAD         /* Accessing a corrupted shared library */
#define __ELIBSCN         __GEN_ELIBSCN         /* .lib section in a.out corrupted */
#define __ELIBMAX         __GEN_ELIBMAX         /* Attempting to link in too many shared libraries */
#define __ELIBEXEC        __GEN_ELIBEXEC        /* Cannot exec a shared library directly */
#define __EILSEQ          __GEN_EILSEQ          /* Illegal byte sequence */
#define __ERESTART        __GEN_ERESTART        /* Interrupted system call should be restarted */
#define __ESTRPIPE        __GEN_ESTRPIPE        /* Streams pipe error */
#define __EUSERS          __GEN_EUSERS          /* Too many users */
#define __ENOTSOCK        __GEN_ENOTSOCK        /* Socket operation on non-socket */
#define __EDESTADDRREQ    __GEN_EDESTADDRREQ    /* Destination address required */
#define __EMSGSIZE        __GEN_EMSGSIZE        /* Message too long */
#define __EPROTOTYPE      __GEN_EPROTOTYPE      /* Protocol wrong type for socket */
#define __ENOPROTOOPT     __GEN_ENOPROTOOPT     /* Protocol not available */
#define __EPROTONOSUPPORT __GEN_EPROTONOSUPPORT /* Protocol not supported */
#define __ESOCKTNOSUPPORT __GEN_ESOCKTNOSUPPORT /* Socket type not supported */
#define __EOPNOTSUPP      __GEN_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define __EPFNOSUPPORT    __GEN_EPFNOSUPPORT    /* Protocol family not supported */
#define __EAFNOSUPPORT    __GEN_EAFNOSUPPORT    /* Address family not supported by protocol */
#define __EADDRINUSE      __GEN_EADDRINUSE      /* Address already in use */
#define __EADDRNOTAVAIL   __GEN_EADDRNOTAVAIL   /* Cannot assign requested address */
#define __ENETDOWN        __GEN_ENETDOWN        /* Network is down */
#define __ENETUNREACH     __GEN_ENETUNREACH     /* Network is unreachable */
#define __ENETRESET       __GEN_ENETRESET       /* Network dropped connection because of reset */
#define __ECONNABORTED    __GEN_ECONNABORTED    /* Software caused connection abort */
#define __ECONNRESET      __GEN_ECONNRESET      /* Connection reset by peer */
#define __ENOBUFS         __GEN_ENOBUFS         /* No buffer space available */
#define __EISCONN         __GEN_EISCONN         /* Transport endpoint is already connected */
#define __ENOTCONN        __GEN_ENOTCONN        /* Transport endpoint is not connected */
#define __ESHUTDOWN       __GEN_ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#define __ETOOMANYREFS    __GEN_ETOOMANYREFS    /* Too many references: cannot splice */
#define __ETIMEDOUT       __GEN_ETIMEDOUT       /* Connection timed out */
#define __ECONNREFUSED    __GEN_ECONNREFUSED    /* Connection refused */
#define __EHOSTDOWN       __GEN_EHOSTDOWN       /* Host is down */
#define __EHOSTUNREACH    __GEN_EHOSTUNREACH    /* No route to host */
#define __EALREADY        __GEN_EALREADY        /* Operation already in progress */
#define __EINPROGRESS     __GEN_EINPROGRESS     /* Operation now in progress */
#define __ESTALE          __GEN_ESTALE          /* Stale NFS file handle */
#define __EUCLEAN         __GEN_EUCLEAN         /* Structure needs cleaning */
#define __ENOTNAM         __GEN_ENOTNAM         /* Not a XENIX named type file */
#define __ENAVAIL         __GEN_ENAVAIL         /* No XENIX semaphores available */
#define __EISNAM          __GEN_EISNAM          /* Is a named type file */
#define __EREMOTEIO       __GEN_EREMOTEIO       /* Remote I/O error */
#define __EDQUOT          __GEN_EDQUOT          /* Quota exceeded */
#define __ENOMEDIUM       __GEN_ENOMEDIUM       /* No medium found */
#define __EMEDIUMTYPE     __GEN_EMEDIUMTYPE     /* Wrong medium type */
#define __ECANCELED       __GEN_ECANCELED       /* Operation Canceled */
#define __ENOKEY          __GEN_ENOKEY          /* Required key not available */
#define __EKEYEXPIRED     __GEN_EKEYEXPIRED     /* Key has expired */
#define __EKEYREVOKED     __GEN_EKEYREVOKED     /* Key has been revoked */
#define __EKEYREJECTED    __GEN_EKEYREJECTED    /* Key was rejected by service */
#define __EOWNERDEAD      __GEN_EOWNERDEAD      /* Owner died */
#define __ENOTRECOVERABLE __GEN_ENOTRECOVERABLE /* State not recoverable */
#define __ECOUNT          __GEN_ECOUNT          /* Max errno + 1 */
#endif /* Generic... */

#ifndef __STRUNCATE
#define __STRUNCATE       __ERANGE
#endif /* !__STRUNCATE */


#ifdef __CC__
__DECL_BEGIN

#ifndef __errno
#ifndef ____errno_location_defined
#define ____errno_location_defined 1
#ifdef __CRT_HAVE___errno_location
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__errno_location,(void),__errno,())
#else /* LIBC: __errno_location */
#undef ____errno_location_defined
#endif /* __errno_location... */
#endif /* !____errno_location_defined */
#ifdef ____errno_location_defined
#define __errno     (*__errno_location())
#elif defined(errno)
#define __errno  errno
#elif defined(__CRT_HAVE_errno) && !defined(__NO_ASMNAME)
__LIBC __ATTR_THREAD int __errno __ASMNAME("errno");
#define __errno  __errno
#elif defined(__CRT_HAVE_errno)
__LIBC __ATTR_THREAD int errno;
#define errno    errno
#define __errno  errno
#endif
#endif /* !__errno */

#if !defined(__libc_geterrno) && defined(__errno)
#define __libc_geterrno() __errno
#endif /* !__libc_geterrno && __errno */

#ifndef __libc_geterrno_or
#ifdef __errno
#define __libc_geterrno_or(alt) __errno
#else /* __errno */
#define __libc_geterrno_or(alt) alt
#endif /* !__errno */
#endif /* !__libc_geterrno_or */

#ifndef __libc_seterrno
#ifdef __errno
#define __libc_seterrno(val) (void)(__errno=(val))
#else /* __errno */
#define __libc_seterrno(val) (void)0
#endif /* !__errno */
#endif /* !__libc_seterrno */

__DECL_END
#endif /* __CC__ */


#endif /* !_PARTS_ERRNO_H */
