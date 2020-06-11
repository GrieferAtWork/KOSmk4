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

%[define_replacement(errno_t = __errno_t)]
%[default_impl_section(".text.crt.errno.utility")]

%[define_replacement(EPERM           = __EPERM)]           /* Operation not permitted */
%[define_replacement(ENOENT          = __ENOENT)]          /* No such file or directory */
%[define_replacement(ESRCH           = __ESRCH)]           /* No such process */
%[define_replacement(EINTR           = __EINTR)]           /* Interrupted system call */
%[define_replacement(EIO             = __EIO)]             /* I/O error */
%[define_replacement(ENXIO           = __ENXIO)]           /* No such device or address */
%[define_replacement(E2BIG           = __E2BIG)]           /* Argument list too long */
%[define_replacement(ENOEXEC         = __ENOEXEC)]         /* Exec format error */
%[define_replacement(EBADF           = __EBADF)]           /* Bad file number */
%[define_replacement(ECHILD          = __ECHILD)]          /* No child processes */
%[define_replacement(EAGAIN          = __EAGAIN)]          /* Try again */
%[define_replacement(ENOMEM          = __ENOMEM)]          /* Out of memory */
%[define_replacement(EACCES          = __EACCES)]          /* Permission denied */
%[define_replacement(EFAULT          = __EFAULT)]          /* Bad address */
%[define_replacement(ENOTBLK         = __ENOTBLK)]         /* Block device required */
%[define_replacement(EBUSY           = __EBUSY)]           /* Device or resource busy */
%[define_replacement(EEXIST          = __EEXIST)]          /* File exists */
%[define_replacement(EXDEV           = __EXDEV)]           /* Cross-device link */
%[define_replacement(ENODEV          = __ENODEV)]          /* No such device */
%[define_replacement(ENOTDIR         = __ENOTDIR)]         /* Not a directory */
%[define_replacement(EISDIR          = __EISDIR)]          /* Is a directory */
%[define_replacement(EINVAL          = __EINVAL)]          /* Invalid argument */
%[define_replacement(ENFILE          = __ENFILE)]          /* File table overflow */
%[define_replacement(EMFILE          = __EMFILE)]          /* Too many open files */
%[define_replacement(ENOTTY          = __ENOTTY)]          /* Not a typewriter */
%[define_replacement(ETXTBSY         = __ETXTBSY)]         /* Text file busy */
%[define_replacement(EFBIG           = __EFBIG)]           /* File too large */
%[define_replacement(ENOSPC          = __ENOSPC)]          /* No space left on device */
%[define_replacement(ESPIPE          = __ESPIPE)]          /* Illegal seek */
%[define_replacement(EROFS           = __EROFS)]           /* Read-only file system */
%[define_replacement(EMLINK          = __EMLINK)]          /* Too many links */
%[define_replacement(EPIPE           = __EPIPE)]           /* Broken pipe */
%[define_replacement(EDOM            = __EDOM)]            /* Math argument out of domain of func */
%[define_replacement(ERANGE          = __ERANGE)]          /* Math result not representable */
%[define_replacement(EDEADLK         = __EDEADLK)]         /* Resource deadlock would occur */
%[define_replacement(ENAMETOOLONG    = __ENAMETOOLONG)]    /* File name too long */
%[define_replacement(ENOLCK          = __ENOLCK)]          /* No record locks available */
%[define_replacement(ENOSYS          = __ENOSYS)]          /* Function not implemented */
%[define_replacement(ENOTEMPTY       = __ENOTEMPTY)]       /* Directory not empty */
%[define_replacement(ELOOP           = __ELOOP)]           /* Too many symbolic links encountered */
%[define_replacement(EWOULDBLOCK     = __EWOULDBLOCK)]     /* Operation would block */
%[define_replacement(ENOMSG          = __ENOMSG)]          /* No message of desired type */
%[define_replacement(EIDRM           = __EIDRM)]           /* Identifier removed */
%[define_replacement(ECHRNG          = __ECHRNG)]          /* Channel number out of range */
%[define_replacement(EL2NSYNC        = __EL2NSYNC)]        /* Level 2 not synchronized */
%[define_replacement(EL3HLT          = __EL3HLT)]          /* Level 3 halted */
%[define_replacement(EL3RST          = __EL3RST)]          /* Level 3 reset */
%[define_replacement(ELNRNG          = __ELNRNG)]          /* Link number out of range */
%[define_replacement(EUNATCH         = __EUNATCH)]         /* Protocol driver not attached */
%[define_replacement(ENOCSI          = __ENOCSI)]          /* No CSI structure available */
%[define_replacement(EL2HLT          = __EL2HLT)]          /* Level 2 halted */
%[define_replacement(EBADE           = __EBADE)]           /* Invalid exchange */
%[define_replacement(EBADR           = __EBADR)]           /* Invalid request descriptor */
%[define_replacement(EXFULL          = __EXFULL)]          /* Exchange full */
%[define_replacement(ENOANO          = __ENOANO)]          /* No anode */
%[define_replacement(EBADRQC         = __EBADRQC)]         /* Invalid request code */
%[define_replacement(EBADSLT         = __EBADSLT)]         /* Invalid slot */
%[define_replacement(EDEADLOCK       = __EDEADLOCK)]       /* Resource deadlock would occur */
%[define_replacement(EBFONT          = __EBFONT)]          /* Bad font file format */
%[define_replacement(ENOSTR          = __ENOSTR)]          /* Device not a stream */
%[define_replacement(ENODATA         = __ENODATA)]         /* No data available */
%[define_replacement(ETIME           = __ETIME)]           /* Timer expired */
%[define_replacement(ENOSR           = __ENOSR)]           /* Out of streams resources */
%[define_replacement(ENONET          = __ENONET)]          /* Machine is not on the network */
%[define_replacement(ENOPKG          = __ENOPKG)]          /* Package not installed */
%[define_replacement(EREMOTE         = __EREMOTE)]         /* Object is remote */
%[define_replacement(ENOLINK         = __ENOLINK)]         /* Link has been severed */
%[define_replacement(EADV            = __EADV)]            /* Advertise error */
%[define_replacement(ESRMNT          = __ESRMNT)]          /* Srmount error */
%[define_replacement(ECOMM           = __ECOMM)]           /* Communication error on send */
%[define_replacement(EPROTO          = __EPROTO)]          /* Protocol error */
%[define_replacement(EMULTIHOP       = __EMULTIHOP)]       /* Multihop attempted */
%[define_replacement(EDOTDOT         = __EDOTDOT)]         /* RFS specific error */
%[define_replacement(EBADMSG         = __EBADMSG)]         /* Not a data message */
%[define_replacement(EOVERFLOW       = __EOVERFLOW)]       /* Value too large for defined data type */
%[define_replacement(ENOTUNIQ        = __ENOTUNIQ)]        /* Name not unique on network */
%[define_replacement(EBADFD          = __EBADFD)]          /* File descriptor in bad state */
%[define_replacement(EREMCHG         = __EREMCHG)]         /* Remote address changed */
%[define_replacement(ELIBACC         = __ELIBACC)]         /* Can not access a needed shared library */
%[define_replacement(ELIBBAD         = __ELIBBAD)]         /* Accessing a corrupted shared library */
%[define_replacement(ELIBSCN         = __ELIBSCN)]         /* .lib section in a.out corrupted */
%[define_replacement(ELIBMAX         = __ELIBMAX)]         /* Attempting to link in too many shared libraries */
%[define_replacement(ELIBEXEC        = __ELIBEXEC)]        /* Cannot exec a shared library directly */
%[define_replacement(EILSEQ          = __EILSEQ)]          /* Illegal byte sequence */
%[define_replacement(ERESTART        = __ERESTART)]        /* Interrupted system call should be restarted */
%[define_replacement(ESTRPIPE        = __ESTRPIPE)]        /* Streams pipe error */
%[define_replacement(EUSERS          = __EUSERS)]          /* Too many users */
%[define_replacement(ENOTSOCK        = __ENOTSOCK)]        /* Socket operation on non-socket */
%[define_replacement(EDESTADDRREQ    = __EDESTADDRREQ)]    /* Destination address required */
%[define_replacement(EMSGSIZE        = __EMSGSIZE)]        /* Message too long */
%[define_replacement(EPROTOTYPE      = __EPROTOTYPE)]      /* Protocol wrong type for socket */
%[define_replacement(ENOPROTOOPT     = __ENOPROTOOPT)]     /* Protocol not available */
%[define_replacement(EPROTONOSUPPORT = __EPROTONOSUPPORT)] /* Protocol not supported */
%[define_replacement(ESOCKTNOSUPPORT = __ESOCKTNOSUPPORT)] /* Socket type not supported */
%[define_replacement(EOPNOTSUPP      = __EOPNOTSUPP)]      /* Operation not supported on transport endpoint */
%[define_replacement(EPFNOSUPPORT    = __EPFNOSUPPORT)]    /* Protocol family not supported */
%[define_replacement(EAFNOSUPPORT    = __EAFNOSUPPORT)]    /* Address family not supported by protocol */
%[define_replacement(EADDRINUSE      = __EADDRINUSE)]      /* Address already in use */
%[define_replacement(EADDRNOTAVAIL   = __EADDRNOTAVAIL)]   /* Cannot assign requested address */
%[define_replacement(ENETDOWN        = __ENETDOWN)]        /* Network is down */
%[define_replacement(ENETUNREACH     = __ENETUNREACH)]     /* Network is unreachable */
%[define_replacement(ENETRESET       = __ENETRESET)]       /* Network dropped connection because of reset */
%[define_replacement(ECONNABORTED    = __ECONNABORTED)]    /* Software caused connection abort */
%[define_replacement(ECONNRESET      = __ECONNRESET)]      /* Connection reset by peer */
%[define_replacement(ENOBUFS         = __ENOBUFS)]         /* No buffer space available */
%[define_replacement(EISCONN         = __EISCONN)]         /* Transport endpoint is already connected */
%[define_replacement(ENOTCONN        = __ENOTCONN)]        /* Transport endpoint is not connected */
%[define_replacement(ESHUTDOWN       = __ESHUTDOWN)]       /* Cannot send after transport endpoint shutdown */
%[define_replacement(ETOOMANYREFS    = __ETOOMANYREFS)]    /* Too many references: cannot splice */
%[define_replacement(ETIMEDOUT       = __ETIMEDOUT)]       /* Connection timed out */
%[define_replacement(ECONNREFUSED    = __ECONNREFUSED)]    /* Connection refused */
%[define_replacement(EHOSTDOWN       = __EHOSTDOWN)]       /* Host is down */
%[define_replacement(EHOSTUNREACH    = __EHOSTUNREACH)]    /* No route to host */
%[define_replacement(EALREADY        = __EALREADY)]        /* Operation already in progress */
%[define_replacement(EINPROGRESS     = __EINPROGRESS)]     /* Operation now in progress */
%[define_replacement(ESTALE          = __ESTALE)]          /* Stale NFS file handle */
%[define_replacement(EUCLEAN         = __EUCLEAN)]         /* Structure needs cleaning */
%[define_replacement(ENOTNAM         = __ENOTNAM)]         /* Not a XENIX named type file */
%[define_replacement(ENAVAIL         = __ENAVAIL)]         /* No XENIX semaphores available */
%[define_replacement(EISNAM          = __EISNAM)]          /* Is a named type file */
%[define_replacement(EREMOTEIO       = __EREMOTEIO)]       /* Remote I/O error */
%[define_replacement(EDQUOT          = __EDQUOT)]          /* Quota exceeded */
%[define_replacement(ENOMEDIUM       = __ENOMEDIUM)]       /* No medium found */
%[define_replacement(EMEDIUMTYPE     = __EMEDIUMTYPE)]     /* Wrong medium type */
%[define_replacement(ECANCELED       = __ECANCELED)]       /* Operation Canceled */
%[define_replacement(ENOKEY          = __ENOKEY)]          /* Required key not available */
%[define_replacement(EKEYEXPIRED     = __EKEYEXPIRED)]     /* Key has expired */
%[define_replacement(EKEYREVOKED     = __EKEYREVOKED)]     /* Key has been revoked */
%[define_replacement(EKEYREJECTED    = __EKEYREJECTED)]    /* Key was rejected by service */
%[define_replacement(EOWNERDEAD      = __EOWNERDEAD)]      /* Owner died */
%[define_replacement(ENOTRECOVERABLE = __ENOTRECOVERABLE)] /* State not recoverable */

%[define_replacement(STRUNCATE       = __STRUNCATE)]       /* Truncated */
%[define_replacement(ENOTSUP         = __ENOTSUP)]         /* Not supported */
%[define_replacement(EOTHER          = __EOTHER)]          /* Other */
%[define_replacement(EFTYPE          = __EFTYPE)]          /* Inappropriate file type or format */
%[define_replacement(ENMFILE         = __ENMFILE)]         /* No more files */
%[define_replacement(ECASECLASH      = __ECASECLASH)]      /* Filename exists with different case */
%[define_replacement(ELBIN           = __ELBIN)]           /* Inode is remote (not really error) */
%[define_replacement(EPROCLIM        = __EPROCLIM)]        /* Process limit reached */
%[define_replacement(ERFKILL         = __ERFKILL)]         /* Operation not possible due to RF-kill */
%[define_replacement(EHWPOISON       = __EHWPOISON)]       /* Memory page has hardware error */



//%[define_wchar_replacement(EPERM           = __DOS_EPERM,             __GEN_EPERM)]           /* Operation not permitted */
//%[define_wchar_replacement(ENOENT          = __DOS_ENOENT,            __GEN_ENOENT)]          /* No such file or directory */
//%[define_wchar_replacement(ESRCH           = __DOS_ESRCH,             __GEN_ESRCH)]           /* No such process */
//%[define_wchar_replacement(EINTR           = __DOS_EINTR,             __GEN_EINTR)]           /* Interrupted system call */
//%[define_wchar_replacement(EIO             = __DOS_EIO,               __GEN_EIO)]             /* I/O error */
//%[define_wchar_replacement(ENXIO           = __DOS_ENXIO,             __GEN_ENXIO)]           /* No such device or address */
//%[define_wchar_replacement(E2BIG           = __DOS_E2BIG,             __GEN_E2BIG)]           /* Argument list too long */
//%[define_wchar_replacement(ENOEXEC         = __DOS_ENOEXEC,           __GEN_ENOEXEC)]         /* Exec format error */
//%[define_wchar_replacement(EBADF           = __DOS_EBADF,             __GEN_EBADF)]           /* Bad file number */
//%[define_wchar_replacement(ECHILD          = __DOS_ECHILD,            __GEN_ECHILD)]          /* No child processes */
//%[define_wchar_replacement(EAGAIN          = __DOS_EAGAIN,            __GEN_EAGAIN)]          /* Try again */
//%[define_wchar_replacement(ENOMEM          = __DOS_ENOMEM,            __GEN_ENOMEM)]          /* Out of memory */
//%[define_wchar_replacement(EACCES          = __DOS_EACCES,            __GEN_EACCES)]          /* Permission denied */
//%[define_wchar_replacement(EFAULT          = __DOS_EFAULT,            __GEN_EFAULT)]          /* Bad address */
//%[define_wchar_replacement(EBUSY           = __DOS_EBUSY,             __GEN_EBUSY)]           /* Device or resource busy */
//%[define_wchar_replacement(EEXIST          = __DOS_EEXIST,            __GEN_EEXIST)]          /* File exists */
//%[define_wchar_replacement(EXDEV           = __DOS_EXDEV,             __GEN_EXDEV)]           /* Cross-device link */
//%[define_wchar_replacement(ENODEV          = __DOS_ENODEV,            __GEN_ENODEV)]          /* No such device */
//%[define_wchar_replacement(ENOTDIR         = __DOS_ENOTDIR,           __GEN_ENOTDIR)]         /* Not a directory */
//%[define_wchar_replacement(EISDIR          = __DOS_EISDIR,            __GEN_EISDIR)]          /* Is a directory */
//%[define_wchar_replacement(EINVAL          = __DOS_EINVAL,            __GEN_EINVAL)]          /* Invalid argument */
//%[define_wchar_replacement(ENFILE          = __DOS_ENFILE,            __GEN_ENFILE)]          /* File table overflow */
//%[define_wchar_replacement(EMFILE          = __DOS_EMFILE,            __GEN_EMFILE)]          /* Too many open files */
//%[define_wchar_replacement(ENOTTY          = __DOS_ENOTTY,            __GEN_ENOTTY)]          /* Not a typewriter */
//%[define_wchar_replacement(ETXTBSY         = __DOS_ETXTBSY,           __GEN_ETXTBSY)]         /* Text file busy */
//%[define_wchar_replacement(EFBIG           = __DOS_EFBIG,             __GEN_EFBIG)]           /* File too large */
//%[define_wchar_replacement(ENOSPC          = __DOS_ENOSPC,            __GEN_ENOSPC)]          /* No space left on device */
//%[define_wchar_replacement(ESPIPE          = __DOS_ESPIPE,            __GEN_ESPIPE)]          /* Illegal seek */
//%[define_wchar_replacement(EROFS           = __DOS_EROFS,             __GEN_EROFS)]           /* Read-only file system */
//%[define_wchar_replacement(EMLINK          = __DOS_EMLINK,            __GEN_EMLINK)]          /* Too many links */
//%[define_wchar_replacement(EPIPE           = __DOS_EPIPE,             __GEN_EPIPE)]           /* Broken pipe */
//%[define_wchar_replacement(EDOM            = __DOS_EDOM,              __GEN_EDOM)]            /* Math argument out of domain of func */
//%[define_wchar_replacement(ERANGE          = __DOS_ERANGE,            __GEN_ERANGE)]          /* Math result not representable */
//%[define_wchar_replacement(EDEADLK         = __DOS_EDEADLK,           __GEN_EDEADLK)]         /* Resource deadlock would occur */
//%[define_wchar_replacement(ENAMETOOLONG    = __DOS_ENAMETOOLONG,      __GEN_ENAMETOOLONG)]    /* File name too long */
//%[define_wchar_replacement(ENOLCK          = __DOS_ENOLCK,            __GEN_ENOLCK)]          /* No record locks available */
//%[define_wchar_replacement(ENOSYS          = __DOS_ENOSYS,            __GEN_ENOSYS)]          /* Function not implemented */
//%[define_wchar_replacement(ENOTEMPTY       = __DOS_ENOTEMPTY,         __GEN_ENOTEMPTY)]       /* Directory not empty */
//%[define_wchar_replacement(ELOOP           = __DOS_ELOOP,             __GEN_ELOOP)]           /* Too many symbolic links encountered */
//%[define_wchar_replacement(EWOULDBLOCK     = __DOS_EWOULDBLOCK,       __GEN_EWOULDBLOCK)]     /* Operation would block */
//%[define_wchar_replacement(ENOMSG          = __DOS_ENOMSG,            __GEN_ENOMSG)]          /* No message of desired type */
//%[define_wchar_replacement(EIDRM           = __DOS_EIDRM,             __GEN_EIDRM)]           /* Identifier removed */
//%[define_wchar_replacement(EDEADLOCK       = __DOS_EDEADLOCK,         __GEN_EDEADLOCK)]       /* Resource deadlock would occur */
//%[define_wchar_replacement(ENOSTR          = __DOS_ENOSTR,            __GEN_ENOSTR)]          /* Device not a stream */
//%[define_wchar_replacement(ENODATA         = __DOS_ENODATA,           __GEN_ENODATA)]         /* No data available */
//%[define_wchar_replacement(ETIME           = __DOS_ETIME,             __GEN_ETIME)]           /* Timer expired */
//%[define_wchar_replacement(ENOSR           = __DOS_ENOSR,             __GEN_ENOSR)]           /* Out of streams resources */
//%[define_wchar_replacement(ENOLINK         = __DOS_ENOLINK,           __GEN_ENOLINK)]         /* Link has been severed */
//%[define_wchar_replacement(EPROTO          = __DOS_EPROTO,            __GEN_EPROTO)]          /* Protocol error */
//%[define_wchar_replacement(EBADMSG         = __DOS_EBADMSG,           __GEN_EBADMSG)]         /* Not a data message */
//%[define_wchar_replacement(EOVERFLOW       = __DOS_EOVERFLOW,         __GEN_EOVERFLOW)]       /* Value too large for defined data type */
//%[define_wchar_replacement(EILSEQ          = __DOS_EILSEQ,            __GEN_EILSEQ)]          /* Illegal byte sequence */
//%[define_wchar_replacement(ENOTSOCK        = __DOS_ENOTSOCK,          __GEN_ENOTSOCK)]        /* Socket operation on non-socket */
//%[define_wchar_replacement(EDESTADDRREQ    = __DOS_EDESTADDRREQ,      __GEN_EDESTADDRREQ)]    /* Destination address required */
//%[define_wchar_replacement(EMSGSIZE        = __DOS_EMSGSIZE,          __GEN_EMSGSIZE)]        /* Message too long */
//%[define_wchar_replacement(EPROTOTYPE      = __DOS_EPROTOTYPE,        __GEN_EPROTOTYPE)]      /* Protocol wrong type for socket */
//%[define_wchar_replacement(ENOPROTOOPT     = __DOS_ENOPROTOOPT,       __GEN_ENOPROTOOPT)]     /* Protocol not available */
//%[define_wchar_replacement(EPROTONOSUPPORT = __DOS_EPROTONOSUPPORT,   __GEN_EPROTONOSUPPORT)] /* Protocol not supported */
//%[define_wchar_replacement(EOPNOTSUPP      = __DOS_EOPNOTSUPP,        __GEN_EOPNOTSUPP)]      /* Operation not supported on transport endpoint */
//%[define_wchar_replacement(EAFNOSUPPORT    = __DOS_EAFNOSUPPORT,      __GEN_EAFNOSUPPORT)]    /* Address family not supported by protocol */
//%[define_wchar_replacement(EADDRINUSE      = __DOS_EADDRINUSE,        __GEN_EADDRINUSE)]      /* Address already in use */
//%[define_wchar_replacement(EADDRNOTAVAIL   = __DOS_EADDRNOTAVAIL,     __GEN_EADDRNOTAVAIL)]   /* Cannot assign requested address */
//%[define_wchar_replacement(ENETDOWN        = __DOS_ENETDOWN,          __GEN_ENETDOWN)]        /* Network is down */
//%[define_wchar_replacement(ENETUNREACH     = __DOS_ENETUNREACH,       __GEN_ENETUNREACH)]     /* Network is unreachable */
//%[define_wchar_replacement(ENETRESET       = __DOS_ENETRESET,         __GEN_ENETRESET)]       /* Network dropped connection because of reset */
//%[define_wchar_replacement(ECONNABORTED    = __DOS_ECONNABORTED,      __GEN_ECONNABORTED)]    /* Software caused connection abort */
//%[define_wchar_replacement(ECONNRESET      = __DOS_ECONNRESET,        __GEN_ECONNRESET)]      /* Connection reset by peer */
//%[define_wchar_replacement(ENOBUFS         = __DOS_ENOBUFS,           __GEN_ENOBUFS)]         /* No buffer space available */
//%[define_wchar_replacement(EISCONN         = __DOS_EISCONN,           __GEN_EISCONN)]         /* Transport endpoint is already connected */
//%[define_wchar_replacement(ENOTCONN        = __DOS_ENOTCONN,          __GEN_ENOTCONN)]        /* Transport endpoint is not connected */
//%[define_wchar_replacement(ETIMEDOUT       = __DOS_ETIMEDOUT,         __GEN_ETIMEDOUT)]       /* Connection timed out */
//%[define_wchar_replacement(ECONNREFUSED    = __DOS_ECONNREFUSED,      __GEN_ECONNREFUSED)]    /* Connection refused */
//%[define_wchar_replacement(EHOSTUNREACH    = __DOS_EHOSTUNREACH,      __GEN_EHOSTUNREACH)]    /* No route to host */
//%[define_wchar_replacement(EALREADY        = __DOS_EALREADY,          __GEN_EALREADY)]        /* Operation already in progress */
//%[define_wchar_replacement(EINPROGRESS     = __DOS_EINPROGRESS,       __GEN_EINPROGRESS)]     /* Operation now in progress */
//%[define_wchar_replacement(ECANCELED       = __DOS_ECANCELED,         __GEN_ECANCELED)]       /* Operation Canceled */
//%[define_wchar_replacement(EOWNERDEAD      = __DOS_EOWNERDEAD,        __GEN_EOWNERDEAD)]      /* Owner died */
//%[define_wchar_replacement(ENOTRECOVERABLE = __DOS_ENOTRECOVERABLE,   __GEN_ENOTRECOVERABLE)] /* State not recoverable */

//%[define_wchar_replacement(__EPERM           = __DOS_EPERM,             __GEN_EPERM)]           /* Operation not permitted */
//%[define_wchar_replacement(__ENOENT          = __DOS_ENOENT,            __GEN_ENOENT)]          /* No such file or directory */
//%[define_wchar_replacement(__ESRCH           = __DOS_ESRCH,             __GEN_ESRCH)]           /* No such process */
//%[define_wchar_replacement(__EINTR           = __DOS_EINTR,             __GEN_EINTR)]           /* Interrupted system call */
//%[define_wchar_replacement(__EIO             = __DOS_EIO,               __GEN_EIO)]             /* I/O error */
//%[define_wchar_replacement(__ENXIO           = __DOS_ENXIO,             __GEN_ENXIO)]           /* No such device or address */
//%[define_wchar_replacement(__E2BIG           = __DOS_E2BIG,             __GEN_E2BIG)]           /* Argument list too long */
//%[define_wchar_replacement(__ENOEXEC         = __DOS_ENOEXEC,           __GEN_ENOEXEC)]         /* Exec format error */
//%[define_wchar_replacement(__EBADF           = __DOS_EBADF,             __GEN_EBADF)]           /* Bad file number */
//%[define_wchar_replacement(__ECHILD          = __DOS_ECHILD,            __GEN_ECHILD)]          /* No child processes */
//%[define_wchar_replacement(__EAGAIN          = __DOS_EAGAIN,            __GEN_EAGAIN)]          /* Try again */
//%[define_wchar_replacement(__ENOMEM          = __DOS_ENOMEM,            __GEN_ENOMEM)]          /* Out of memory */
//%[define_wchar_replacement(__EACCES          = __DOS_EACCES,            __GEN_EACCES)]          /* Permission denied */
//%[define_wchar_replacement(__EFAULT          = __DOS_EFAULT,            __GEN_EFAULT)]          /* Bad address */
//%[define_wchar_replacement(__EBUSY           = __DOS_EBUSY,             __GEN_EBUSY)]           /* Device or resource busy */
//%[define_wchar_replacement(__EEXIST          = __DOS_EEXIST,            __GEN_EEXIST)]          /* File exists */
//%[define_wchar_replacement(__EXDEV           = __DOS_EXDEV,             __GEN_EXDEV)]           /* Cross-device link */
//%[define_wchar_replacement(__ENODEV          = __DOS_ENODEV,            __GEN_ENODEV)]          /* No such device */
//%[define_wchar_replacement(__ENOTDIR         = __DOS_ENOTDIR,           __GEN_ENOTDIR)]         /* Not a directory */
//%[define_wchar_replacement(__EISDIR          = __DOS_EISDIR,            __GEN_EISDIR)]          /* Is a directory */
//%[define_wchar_replacement(__EINVAL          = __DOS_EINVAL,            __GEN_EINVAL)]          /* Invalid argument */
//%[define_wchar_replacement(__ENFILE          = __DOS_ENFILE,            __GEN_ENFILE)]          /* File table overflow */
//%[define_wchar_replacement(__EMFILE          = __DOS_EMFILE,            __GEN_EMFILE)]          /* Too many open files */
//%[define_wchar_replacement(__ENOTTY          = __DOS_ENOTTY,            __GEN_ENOTTY)]          /* Not a typewriter */
//%[define_wchar_replacement(__ETXTBSY         = __DOS_ETXTBSY,           __GEN_ETXTBSY)]         /* Text file busy */
//%[define_wchar_replacement(__EFBIG           = __DOS_EFBIG,             __GEN_EFBIG)]           /* File too large */
//%[define_wchar_replacement(__ENOSPC          = __DOS_ENOSPC,            __GEN_ENOSPC)]          /* No space left on device */
//%[define_wchar_replacement(__ESPIPE          = __DOS_ESPIPE,            __GEN_ESPIPE)]          /* Illegal seek */
//%[define_wchar_replacement(__EROFS           = __DOS_EROFS,             __GEN_EROFS)]           /* Read-only file system */
//%[define_wchar_replacement(__EMLINK          = __DOS_EMLINK,            __GEN_EMLINK)]          /* Too many links */
//%[define_wchar_replacement(__EPIPE           = __DOS_EPIPE,             __GEN_EPIPE)]           /* Broken pipe */
//%[define_wchar_replacement(__EDOM            = __DOS_EDOM,              __GEN_EDOM)]            /* Math argument out of domain of func */
//%[define_wchar_replacement(__ERANGE          = __DOS_ERANGE,            __GEN_ERANGE)]          /* Math result not representable */
//%[define_wchar_replacement(__EDEADLK         = __DOS_EDEADLK,           __GEN_EDEADLK)]         /* Resource deadlock would occur */
//%[define_wchar_replacement(__ENAMETOOLONG    = __DOS_ENAMETOOLONG,      __GEN_ENAMETOOLONG)]    /* File name too long */
//%[define_wchar_replacement(__ENOLCK          = __DOS_ENOLCK,            __GEN_ENOLCK)]          /* No record locks available */
//%[define_wchar_replacement(__ENOSYS          = __DOS_ENOSYS,            __GEN_ENOSYS)]          /* Function not implemented */
//%[define_wchar_replacement(__ENOTEMPTY       = __DOS_ENOTEMPTY,         __GEN_ENOTEMPTY)]       /* Directory not empty */
//%[define_wchar_replacement(__ELOOP           = __DOS_ELOOP,             __GEN_ELOOP)]           /* Too many symbolic links encountered */
//%[define_wchar_replacement(__EWOULDBLOCK     = __DOS_EWOULDBLOCK,       __GEN_EWOULDBLOCK)]     /* Operation would block */
//%[define_wchar_replacement(__ENOMSG          = __DOS_ENOMSG,            __GEN_ENOMSG)]          /* No message of desired type */
//%[define_wchar_replacement(__EIDRM           = __DOS_EIDRM,             __GEN_EIDRM)]           /* Identifier removed */
//%[define_wchar_replacement(__EDEADLOCK       = __DOS_EDEADLOCK,         __GEN_EDEADLOCK)]       /* Resource deadlock would occur */
//%[define_wchar_replacement(__ENOSTR          = __DOS_ENOSTR,            __GEN_ENOSTR)]          /* Device not a stream */
//%[define_wchar_replacement(__ENODATA         = __DOS_ENODATA,           __GEN_ENODATA)]         /* No data available */
//%[define_wchar_replacement(__ETIME           = __DOS_ETIME,             __GEN_ETIME)]           /* Timer expired */
//%[define_wchar_replacement(__ENOSR           = __DOS_ENOSR,             __GEN_ENOSR)]           /* Out of streams resources */
//%[define_wchar_replacement(__ENOLINK         = __DOS_ENOLINK,           __GEN_ENOLINK)]         /* Link has been severed */
//%[define_wchar_replacement(__EPROTO          = __DOS_EPROTO,            __GEN_EPROTO)]          /* Protocol error */
//%[define_wchar_replacement(__EBADMSG         = __DOS_EBADMSG,           __GEN_EBADMSG)]         /* Not a data message */
//%[define_wchar_replacement(__EOVERFLOW       = __DOS_EOVERFLOW,         __GEN_EOVERFLOW)]       /* Value too large for defined data type */
//%[define_wchar_replacement(__EILSEQ          = __DOS_EILSEQ,            __GEN_EILSEQ)]          /* Illegal byte sequence */
//%[define_wchar_replacement(__ENOTSOCK        = __DOS_ENOTSOCK,          __GEN_ENOTSOCK)]        /* Socket operation on non-socket */
//%[define_wchar_replacement(__EDESTADDRREQ    = __DOS_EDESTADDRREQ,      __GEN_EDESTADDRREQ)]    /* Destination address required */
//%[define_wchar_replacement(__EMSGSIZE        = __DOS_EMSGSIZE,          __GEN_EMSGSIZE)]        /* Message too long */
//%[define_wchar_replacement(__EPROTOTYPE      = __DOS_EPROTOTYPE,        __GEN_EPROTOTYPE)]      /* Protocol wrong type for socket */
//%[define_wchar_replacement(__ENOPROTOOPT     = __DOS_ENOPROTOOPT,       __GEN_ENOPROTOOPT)]     /* Protocol not available */
//%[define_wchar_replacement(__EPROTONOSUPPORT = __DOS_EPROTONOSUPPORT,   __GEN_EPROTONOSUPPORT)] /* Protocol not supported */
//%[define_wchar_replacement(__EOPNOTSUPP      = __DOS_EOPNOTSUPP,        __GEN_EOPNOTSUPP)]      /* Operation not supported on transport endpoint */
//%[define_wchar_replacement(__EAFNOSUPPORT    = __DOS_EAFNOSUPPORT,      __GEN_EAFNOSUPPORT)]    /* Address family not supported by protocol */
//%[define_wchar_replacement(__EADDRINUSE      = __DOS_EADDRINUSE,        __GEN_EADDRINUSE)]      /* Address already in use */
//%[define_wchar_replacement(__EADDRNOTAVAIL   = __DOS_EADDRNOTAVAIL,     __GEN_EADDRNOTAVAIL)]   /* Cannot assign requested address */
//%[define_wchar_replacement(__ENETDOWN        = __DOS_ENETDOWN,          __GEN_ENETDOWN)]        /* Network is down */
//%[define_wchar_replacement(__ENETUNREACH     = __DOS_ENETUNREACH,       __GEN_ENETUNREACH)]     /* Network is unreachable */
//%[define_wchar_replacement(__ENETRESET       = __DOS_ENETRESET,         __GEN_ENETRESET)]       /* Network dropped connection because of reset */
//%[define_wchar_replacement(__ECONNABORTED    = __DOS_ECONNABORTED,      __GEN_ECONNABORTED)]    /* Software caused connection abort */
//%[define_wchar_replacement(__ECONNRESET      = __DOS_ECONNRESET,        __GEN_ECONNRESET)]      /* Connection reset by peer */
//%[define_wchar_replacement(__ENOBUFS         = __DOS_ENOBUFS,           __GEN_ENOBUFS)]         /* No buffer space available */
//%[define_wchar_replacement(__EISCONN         = __DOS_EISCONN,           __GEN_EISCONN)]         /* Transport endpoint is already connected */
//%[define_wchar_replacement(__ENOTCONN        = __DOS_ENOTCONN,          __GEN_ENOTCONN)]        /* Transport endpoint is not connected */
//%[define_wchar_replacement(__ETIMEDOUT       = __DOS_ETIMEDOUT,         __GEN_ETIMEDOUT)]       /* Connection timed out */
//%[define_wchar_replacement(__ECONNREFUSED    = __DOS_ECONNREFUSED,      __GEN_ECONNREFUSED)]    /* Connection refused */
//%[define_wchar_replacement(__EHOSTUNREACH    = __DOS_EHOSTUNREACH,      __GEN_EHOSTUNREACH)]    /* No route to host */
//%[define_wchar_replacement(__EALREADY        = __DOS_EALREADY,          __GEN_EALREADY)]        /* Operation already in progress */
//%[define_wchar_replacement(__EINPROGRESS     = __DOS_EINPROGRESS,       __GEN_EINPROGRESS)]     /* Operation now in progress */
//%[define_wchar_replacement(__ECANCELED       = __DOS_ECANCELED,         __GEN_ECANCELED)]       /* Operation Canceled */
//%[define_wchar_replacement(__EOWNERDEAD      = __DOS_EOWNERDEAD,        __GEN_EOWNERDEAD)]      /* Owner died */
//%[define_wchar_replacement(__ENOTRECOVERABLE = __DOS_ENOTRECOVERABLE,   __GEN_ENOTRECOVERABLE)] /* State not recoverable */



%{
#include <features.h>
#include <bits/types.h>

#ifdef __CRT_DOS_PRIMARY
#include <parts/dos/errno.h>
#define EPERM           __DOS_EPERM           /* Operation not permitted */
#define ENOENT          __DOS_ENOENT          /* No such file or directory */
#define ESRCH           __DOS_ESRCH           /* No such process */
#define EINTR           __DOS_EINTR           /* Interrupted system call */
#define EIO             __DOS_EIO             /* I/O error */
#define ENXIO           __DOS_ENXIO           /* No such device or address */
#define E2BIG           __DOS_E2BIG           /* Argument list too long */
#define ENOEXEC         __DOS_ENOEXEC         /* Exec format error */
#define EBADF           __DOS_EBADF           /* Bad file number */
#define ECHILD          __DOS_ECHILD          /* No child processes */
#define EAGAIN          __DOS_EAGAIN          /* Try again */
#define ENOMEM          __DOS_ENOMEM          /* Out of memory */
#define EACCES          __DOS_EACCES          /* Permission denied */
#define EFAULT          __DOS_EFAULT          /* Bad address */
#define EBUSY           __DOS_EBUSY           /* Device or resource busy */
#define EEXIST          __DOS_EEXIST          /* File exists */
#define EXDEV           __DOS_EXDEV           /* Cross-device link */
#define ENODEV          __DOS_ENODEV          /* No such device */
#define ENOTDIR         __DOS_ENOTDIR         /* Not a directory */
#define EISDIR          __DOS_EISDIR          /* Is a directory */
#define ENFILE          __DOS_ENFILE          /* File table overflow */
#define EMFILE          __DOS_EMFILE          /* Too many open files */
#define ENOTTY          __DOS_ENOTTY          /* Not a typewriter */
#define EFBIG           __DOS_EFBIG           /* File too large */
#define ENOSPC          __DOS_ENOSPC          /* No space left on device */
#define ESPIPE          __DOS_ESPIPE          /* Illegal seek */
#define EROFS           __DOS_EROFS           /* Read-only file system */
#define EMLINK          __DOS_EMLINK          /* Too many links */
#define EPIPE           __DOS_EPIPE           /* Broken pipe */
#define EDOM            __DOS_EDOM            /* Math argument out of domain of func */
#define EDEADLK         __DOS_EDEADLK         /* Resource deadlock would occur */
#define ENAMETOOLONG    __DOS_ENAMETOOLONG    /* File name too long */
#define ENOLCK          __DOS_ENOLCK          /* No record locks available */
#define ENOSYS          __DOS_ENOSYS          /* Function not implemented */
#define ENOTEMPTY       __DOS_ENOTEMPTY       /* Directory not empty */
#define EINVAL          __DOS_EINVAL          /* Invalid argument */
#define ERANGE          __DOS_ERANGE          /* Math result not representable */
#define EILSEQ          __DOS_EILSEQ          /* Illegal byte sequence */
#define STRUNCATE       __DOS_STRUNCATE       /* Truncated */
#define EDEADLOCK       __DOS_EDEADLOCK       /* Resource deadlock would occur */
#define EADDRINUSE      __DOS_EADDRINUSE      /* Address already in use */
#define EADDRNOTAVAIL   __DOS_EADDRNOTAVAIL   /* Cannot assign requested address */
#define EAFNOSUPPORT    __DOS_EAFNOSUPPORT    /* Address family not supported by protocol */
#define EALREADY        __DOS_EALREADY        /* Operation already in progress */
#define EBADMSG         __DOS_EBADMSG         /* Not a data message */
#define ECANCELED       __DOS_ECANCELED       /* Operation Canceled */
#define ECONNABORTED    __DOS_ECONNABORTED    /* Software caused connection abort */
#define ECONNREFUSED    __DOS_ECONNREFUSED    /* Connection refused */
#define ECONNRESET      __DOS_ECONNRESET      /* Connection reset by peer */
#define EDESTADDRREQ    __DOS_EDESTADDRREQ    /* Destination address required */
#define EHOSTUNREACH    __DOS_EHOSTUNREACH    /* No route to host */
#define EIDRM           __DOS_EIDRM           /* Identifier removed */
#define EINPROGRESS     __DOS_EINPROGRESS     /* Operation now in progress */
#define EISCONN         __DOS_EISCONN         /* Transport endpoint is already connected */
#define ELOOP           __DOS_ELOOP           /* Too many symbolic links encountered */
#define EMSGSIZE        __DOS_EMSGSIZE        /* Message too long */
#define ENETDOWN        __DOS_ENETDOWN        /* Network is down */
#define ENETRESET       __DOS_ENETRESET       /* Network dropped connection because of reset */
#define ENETUNREACH     __DOS_ENETUNREACH     /* Network is unreachable */
#define ENOBUFS         __DOS_ENOBUFS         /* No buffer space available */
#define ENODATA         __DOS_ENODATA         /* No data available */
#define ENOLINK         __DOS_ENOLINK         /* Link has been severed */
#define ENOMSG          __DOS_ENOMSG          /* No message of desired type */
#define ENOPROTOOPT     __DOS_ENOPROTOOPT     /* Protocol not available */
#define ENOSR           __DOS_ENOSR           /* Out of streams resources */
#define ENOSTR          __DOS_ENOSTR          /* Device not a stream */
#define ENOTCONN        __DOS_ENOTCONN        /* Transport endpoint is not connected */
#define ENOTRECOVERABLE __DOS_ENOTRECOVERABLE /* State not recoverable */
#define ENOTSOCK        __DOS_ENOTSOCK        /* Socket operation on non-socket */
#define ENOTSUP         __DOS_ENOTSUP         /* Not supported */
#define EOPNOTSUPP      __DOS_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define EOTHER          __DOS_EOTHER          /* Other */
#define EOVERFLOW       __DOS_EOVERFLOW       /* Value too large for defined data type */
#define EOWNERDEAD      __DOS_EOWNERDEAD      /* Owner died */
#define EPROTO          __DOS_EPROTO          /* Protocol error */
#define EPROTONOSUPPORT __DOS_EPROTONOSUPPORT /* Protocol not supported */
#define EPROTOTYPE      __DOS_EPROTOTYPE      /* Protocol wrong type for socket */
#define ETIME           __DOS_ETIME           /* Timer expired */
#define ETIMEDOUT       __DOS_ETIMEDOUT       /* Connection timed out */
#define ETXTBSY         __DOS_ETXTBSY         /* Text file busy */
#define EWOULDBLOCK     __DOS_EWOULDBLOCK     /* Operation would block */
#elif defined(__CRT_CYG_PRIMARY)
#include <parts/cyg/errno.h>
#define EPERM           __CYG_EPERM           /* Not owner */
#define ENOENT          __CYG_ENOENT          /* No such file or directory */
#define ESRCH           __CYG_ESRCH           /* No such process */
#define EINTR           __CYG_EINTR           /* Interrupted system call */
#define EIO             __CYG_EIO             /* I/O error */
#define ENXIO           __CYG_ENXIO           /* No such device or address */
#define E2BIG           __CYG_E2BIG           /* Arg list too long */
#define ENOEXEC         __CYG_ENOEXEC         /* Exec format error */
#define EBADF           __CYG_EBADF           /* Bad file number */
#define ECHILD          __CYG_ECHILD          /* No children */
#define EAGAIN          __CYG_EAGAIN          /* No more processes */
#define ENOMEM          __CYG_ENOMEM          /* Not enough space */
#define EACCES          __CYG_EACCES          /* Permission denied */
#define EFAULT          __CYG_EFAULT          /* Bad address */
#define EBUSY           __CYG_EBUSY           /* Device or resource busy */
#define EEXIST          __CYG_EEXIST          /* File exists */
#define EXDEV           __CYG_EXDEV           /* Cross-device link */
#define ENODEV          __CYG_ENODEV          /* No such device */
#define ENOTDIR         __CYG_ENOTDIR         /* Not a directory */
#define EISDIR          __CYG_EISDIR          /* Is a directory */
#define EINVAL          __CYG_EINVAL          /* Invalid argument */
#define ENFILE          __CYG_ENFILE          /* Too many open files in system */
#define EMFILE          __CYG_EMFILE          /* File descriptor value too large */
#define ENOTTY          __CYG_ENOTTY          /* Not a character device */
#define ETXTBSY         __CYG_ETXTBSY         /* Text file busy */
#define EFBIG           __CYG_EFBIG           /* File too large */
#define ENOSPC          __CYG_ENOSPC          /* No space left on device */
#define ESPIPE          __CYG_ESPIPE          /* Illegal seek */
#define EROFS           __CYG_EROFS           /* Read-only file system */
#define EMLINK          __CYG_EMLINK          /* Too many links */
#define EPIPE           __CYG_EPIPE           /* Broken pipe */
#define EDOM            __CYG_EDOM            /* Mathematics argument out of domain of function */
#define ERANGE          __CYG_ERANGE          /* Result too large */
#define ENOMSG          __CYG_ENOMSG          /* No message of desired type */
#define EIDRM           __CYG_EIDRM           /* Identifier removed */
#define EDEADLK         __CYG_EDEADLK         /* Deadlock */
#define ENOLCK          __CYG_ENOLCK          /* No lock */
#define ENOSTR          __CYG_ENOSTR          /* Not a stream */
#define ENODATA         __CYG_ENODATA         /* No data (for no delay io) */
#define ETIME           __CYG_ETIME           /* Stream ioctl timeout */
#define ENOSR           __CYG_ENOSR           /* No stream resources */
#define ENOLINK         __CYG_ENOLINK         /* Virtual circuit is gone */
#define EPROTO          __CYG_EPROTO          /* Protocol error */
#define EMULTIHOP       __CYG_EMULTIHOP       /* Multihop attempted */
#define EBADMSG         __CYG_EBADMSG         /* Bad message */
#define EFTYPE          __CYG_EFTYPE          /* Inappropriate file type or format */
#define ENOSYS          __CYG_ENOSYS          /* Function not implemented */
#define ENMFILE         __CYG_ENMFILE         /* No more files */
#define ENOTEMPTY       __CYG_ENOTEMPTY       /* Directory not empty */
#define ENAMETOOLONG    __CYG_ENAMETOOLONG    /* File or path name too long */
#define ELOOP           __CYG_ELOOP           /* Too many symbolic links */
#define EOPNOTSUPP      __CYG_EOPNOTSUPP      /* Operation not supported on socket */
#define EPFNOSUPPORT    __CYG_EPFNOSUPPORT    /* Protocol family not supported */
#define ECONNRESET      __CYG_ECONNRESET      /* Connection reset by peer */
#define ENOBUFS         __CYG_ENOBUFS         /* No buffer space available */
#define EAFNOSUPPORT    __CYG_EAFNOSUPPORT    /* Address family not supported by protocol family */
#define EPROTOTYPE      __CYG_EPROTOTYPE      /* Protocol wrong type for socket */
#define ENOTSOCK        __CYG_ENOTSOCK        /* Socket operation on non-socket */
#define ENOPROTOOPT     __CYG_ENOPROTOOPT     /* Protocol not available */
#define ECONNREFUSED    __CYG_ECONNREFUSED    /* Connection refused */
#define EADDRINUSE      __CYG_EADDRINUSE      /* Address already in use */
#define ECONNABORTED    __CYG_ECONNABORTED    /* Software caused connection abort */
#define ENETUNREACH     __CYG_ENETUNREACH     /* Network is unreachable */
#define ENETDOWN        __CYG_ENETDOWN        /* Network interface is not configured */
#define ETIMEDOUT       __CYG_ETIMEDOUT       /* Connection timed out */
#define EHOSTDOWN       __CYG_EHOSTDOWN       /* Host is down */
#define EHOSTUNREACH    __CYG_EHOSTUNREACH    /* Host is unreachable */
#define EINPROGRESS     __CYG_EINPROGRESS     /* Connection already in progress */
#define EALREADY        __CYG_EALREADY        /* Socket already connected */
#define EDESTADDRREQ    __CYG_EDESTADDRREQ    /* Destination address required */
#define EMSGSIZE        __CYG_EMSGSIZE        /* Message too long */
#define EPROTONOSUPPORT __CYG_EPROTONOSUPPORT /* Unknown protocol */
#define EADDRNOTAVAIL   __CYG_EADDRNOTAVAIL   /* Address not available */
#define ENETRESET       __CYG_ENETRESET       /* Connection aborted by network */
#define EISCONN         __CYG_EISCONN         /* Socket is already connected */
#define ENOTCONN        __CYG_ENOTCONN        /* Socket is not connected */
#define ETOOMANYREFS    __CYG_ETOOMANYREFS    /* Too many references: cannot splice */
#define EDQUOT          __CYG_EDQUOT          /* Quota exceeded */
#define ESTALE          __CYG_ESTALE          /* Stale file handle */
#define ENOTSUP         __CYG_ENOTSUP         /* Not supported */
#define ENOSHARE        __CYG_ENOSHARE        /* No such host or network path */
#define ECASECLASH      __CYG_ECASECLASH      /* Filename exists with different case */
#define EILSEQ          __CYG_EILSEQ          /* Illegal byte sequence */
#define EOVERFLOW       __CYG_EOVERFLOW       /* Value too large for defined data type */
#define ECANCELED       __CYG_ECANCELED       /* Operation canceled */
#define ENOTRECOVERABLE __CYG_ENOTRECOVERABLE /* State not recoverable */
#define EOWNERDEAD      __CYG_EOWNERDEAD      /* Previous owner died */
#define EWOULDBLOCK     __CYG_EWOULDBLOCK     /* Operation would block */
#ifdef __LINUX_ERRNO_EXTENSIONS__
#define ENOTBLK         __CYG_ENOTBLK         /* Block device required */
#define ECHRNG          __CYG_ECHRNG          /* Channel number out of range */
#define EL2NSYNC        __CYG_EL2NSYNC        /* Level 2 not synchronized */
#define EL3HLT          __CYG_EL3HLT          /* Level 3 halted */
#define EL3RST          __CYG_EL3RST          /* Level 3 reset */
#define ELNRNG          __CYG_ELNRNG          /* Link number out of range */
#define EUNATCH         __CYG_EUNATCH         /* Protocol driver not attached */
#define ENOCSI          __CYG_ENOCSI          /* No CSI structure available */
#define EL2HLT          __CYG_EL2HLT          /* Level 2 halted */
#define EBADE           __CYG_EBADE           /* Invalid exchange */
#define EBADR           __CYG_EBADR           /* Invalid request descriptor */
#define EXFULL          __CYG_EXFULL          /* Exchange full */
#define ENOANO          __CYG_ENOANO          /* No anode */
#define EBADRQC         __CYG_EBADRQC         /* Invalid request code */
#define EBADSLT         __CYG_EBADSLT         /* Invalid slot */
#define EDEADLOCK       __CYG_EDEADLOCK       /* File locking deadlock error */
#define EBFONT          __CYG_EBFONT          /* Bad font file fmt */
#define ENONET          __CYG_ENONET          /* Machine is not on the network */
#define ENOPKG          __CYG_ENOPKG          /* Package not installed */
#define EREMOTE         __CYG_EREMOTE         /* The object is remote */
#define EADV            __CYG_EADV            /* Advertise error */
#define ESRMNT          __CYG_ESRMNT          /* Srmount error */
#define ECOMM           __CYG_ECOMM           /* Communication error on send */
#define ELBIN           __CYG_ELBIN           /* Inode is remote (not really error) */
#define EDOTDOT         __CYG_EDOTDOT         /* Cross mount point (not really error) */
#define ENOTUNIQ        __CYG_ENOTUNIQ        /* Given log. name not unique */
#define EBADFD          __CYG_EBADFD          /* f.d. invalid for this operation */
#define EREMCHG         __CYG_EREMCHG         /* Remote address changed */
#define ELIBACC         __CYG_ELIBACC         /* Can't access a needed shared lib */
#define ELIBBAD         __CYG_ELIBBAD         /* Accessing a corrupted shared lib */
#define ELIBSCN         __CYG_ELIBSCN         /* .lib section in a.out corrupted */
#define ELIBMAX         __CYG_ELIBMAX         /* Attempting to link in too many libs */
#define ELIBEXEC        __CYG_ELIBEXEC        /* Attempting to exec a shared library */
#define ESHUTDOWN       __CYG_ESHUTDOWN       /* Can't send after socket shutdown */
#define ESOCKTNOSUPPORT __CYG_ESOCKTNOSUPPORT /* Socket type not supported */
#define EPROCLIM        __CYG_EPROCLIM        /* Process limit reached */
#define EUSERS          __CYG_EUSERS          /* Too many users */
#define ENOMEDIUM       __CYG_ENOMEDIUM       /* No medium (in tape drive) */
#define ESTRPIPE        __CYG_ESTRPIPE        /* Streams pipe error */
#endif /* __LINUX_ERRNO_EXTENSIONS__ */
#elif defined(__CRT_GLC_PRIMARY)
#include <parts/glibc/errno.h>
#define EPERM           __GLC_EPERM           /* Operation not permitted */
#define ENOENT          __GLC_ENOENT          /* No such file or directory */
#define ESRCH           __GLC_ESRCH           /* No such process */
#define EINTR           __GLC_EINTR           /* Interrupted system call */
#define EIO             __GLC_EIO             /* I/O error */
#define ENXIO           __GLC_ENXIO           /* No such device or address */
#define E2BIG           __GLC_E2BIG           /* Argument list too long */
#define ENOEXEC         __GLC_ENOEXEC         /* Exec format error */
#define EBADF           __GLC_EBADF           /* Bad file number */
#define ECHILD          __GLC_ECHILD          /* No child processes */
#define EAGAIN          __GLC_EAGAIN          /* Try again */
#define ENOMEM          __GLC_ENOMEM          /* Out of memory */
#define EACCES          __GLC_EACCES          /* Permission denied */
#define EFAULT          __GLC_EFAULT          /* Bad address */
#define ENOTBLK         __GLC_ENOTBLK         /* Block device required */
#define EBUSY           __GLC_EBUSY           /* Device or resource busy */
#define EEXIST          __GLC_EEXIST          /* File exists */
#define EXDEV           __GLC_EXDEV           /* Cross-device link */
#define ENODEV          __GLC_ENODEV          /* No such device */
#define ENOTDIR         __GLC_ENOTDIR         /* Not a directory */
#define EISDIR          __GLC_EISDIR          /* Is a directory */
#define EINVAL          __GLC_EINVAL          /* [NT("ERROR_INVALID_PARAMETER")] Invalid argument */
#define ENFILE          __GLC_ENFILE          /* File table overflow */
#define EMFILE          __GLC_EMFILE          /* Too many open files */
#define ENOTTY          __GLC_ENOTTY          /* Not a typewriter */
#define ETXTBSY         __GLC_ETXTBSY         /* Text file busy */
#define EFBIG           __GLC_EFBIG           /* File too large */
#define ENOSPC          __GLC_ENOSPC          /* No space left on device */
#define ESPIPE          __GLC_ESPIPE          /* Illegal seek */
#define EROFS           __GLC_EROFS           /* Read-only file system */
#define EMLINK          __GLC_EMLINK          /* Too many links */
#define EPIPE           __GLC_EPIPE           /* Broken pipe */
#define EDOM            __GLC_EDOM            /* Math argument out of domain of func */
#define ERANGE          __GLC_ERANGE          /* [NT("ERROR_INSUFFICIENT_BUFFER")] Math result not representable */
#define EDEADLK         __GLC_EDEADLK         /* Resource deadlock would occur */
#define ENAMETOOLONG    __GLC_ENAMETOOLONG    /* File name too long */
#define ENOLCK          __GLC_ENOLCK          /* No record locks available */
#define ENOSYS          __GLC_ENOSYS          /* Invalid system call number */
#define ENOTEMPTY       __GLC_ENOTEMPTY       /* Directory not empty */
#define ELOOP           __GLC_ELOOP           /* Too many symbolic links encountered */
#define EWOULDBLOCK     __GLC_EWOULDBLOCK     /* Operation would block */
#define ENOMSG          __GLC_ENOMSG          /* No message of desired type */
#define EIDRM           __GLC_EIDRM           /* Identifier removed */
#define ECHRNG          __GLC_ECHRNG          /* Channel number out of range */
#define EL2NSYNC        __GLC_EL2NSYNC        /* Level 2 not synchronized */
#define EL3HLT          __GLC_EL3HLT          /* Level 3 halted */
#define EL3RST          __GLC_EL3RST          /* Level 3 reset */
#define ELNRNG          __GLC_ELNRNG          /* Link number out of range */
#define EUNATCH         __GLC_EUNATCH         /* Protocol driver not attached */
#define ENOCSI          __GLC_ENOCSI          /* No CSI structure available */
#define EL2HLT          __GLC_EL2HLT          /* Level 2 halted */
#define EBADE           __GLC_EBADE           /* Invalid exchange */
#define EBADR           __GLC_EBADR           /* Invalid request descriptor */
#define EXFULL          __GLC_EXFULL          /* Exchange full */
#define ENOANO          __GLC_ENOANO          /* No anode */
#define EBADRQC         __GLC_EBADRQC         /* Invalid request code */
#define EBADSLT         __GLC_EBADSLT         /* Invalid slot */
#define EDEADLOCK       __GLC_EDEADLOCK       /* Resource deadlock would occur */
#define EBFONT          __GLC_EBFONT          /* Bad font file format */
#define ENOSTR          __GLC_ENOSTR          /* Device not a stream */
#define ENODATA         __GLC_ENODATA         /* No data available */
#define ETIME           __GLC_ETIME           /* Timer expired */
#define ENOSR           __GLC_ENOSR           /* Out of streams resources */
#define ENONET          __GLC_ENONET          /* Machine is not on the network */
#define ENOPKG          __GLC_ENOPKG          /* Package not installed */
#define EREMOTE         __GLC_EREMOTE         /* Object is remote */
#define ENOLINK         __GLC_ENOLINK         /* Link has been severed */
#define EADV            __GLC_EADV            /* Advertise error */
#define ESRMNT          __GLC_ESRMNT          /* Srmount error */
#define ECOMM           __GLC_ECOMM           /* Communication error on send */
#define EPROTO          __GLC_EPROTO          /* Protocol error */
#define EMULTIHOP       __GLC_EMULTIHOP       /* Multihop attempted */
#define EDOTDOT         __GLC_EDOTDOT         /* RFS specific error */
#define EBADMSG         __GLC_EBADMSG         /* Not a data message */
#define EOVERFLOW       __GLC_EOVERFLOW       /* Value too large for defined data type */
#define ENOTUNIQ        __GLC_ENOTUNIQ        /* Name not unique on network */
#define EBADFD          __GLC_EBADFD          /* File descriptor in bad state */
#define EREMCHG         __GLC_EREMCHG         /* Remote address changed */
#define ELIBACC         __GLC_ELIBACC         /* Can not access a needed shared library */
#define ELIBBAD         __GLC_ELIBBAD         /* Accessing a corrupted shared library */
#define ELIBSCN         __GLC_ELIBSCN         /* .lib section in a.out corrupted */
#define ELIBMAX         __GLC_ELIBMAX         /* Attempting to link in too many shared libraries */
#define ELIBEXEC        __GLC_ELIBEXEC        /* Cannot exec a shared library directly */
#define EILSEQ          __GLC_EILSEQ          /* [NT("ERROR_NO_UNICODE_TRANSLATION")] Illegal byte sequence */
#define ERESTART        __GLC_ERESTART        /* Interrupted system call should be restarted */
#define ESTRPIPE        __GLC_ESTRPIPE        /* Streams pipe error */
#define EUSERS          __GLC_EUSERS          /* Too many users */
#define ENOTSOCK        __GLC_ENOTSOCK        /* Socket operation on non-socket */
#define EDESTADDRREQ    __GLC_EDESTADDRREQ    /* Destination address required */
#define EMSGSIZE        __GLC_EMSGSIZE        /* Message too long */
#define EPROTOTYPE      __GLC_EPROTOTYPE      /* Protocol wrong type for socket */
#define ENOPROTOOPT     __GLC_ENOPROTOOPT     /* Protocol not available */
#define EPROTONOSUPPORT __GLC_EPROTONOSUPPORT /* Protocol not supported */
#define ESOCKTNOSUPPORT __GLC_ESOCKTNOSUPPORT /* Socket type not supported */
#define EOPNOTSUPP      __GLC_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define EPFNOSUPPORT    __GLC_EPFNOSUPPORT    /* Protocol family not supported */
#define EAFNOSUPPORT    __GLC_EAFNOSUPPORT    /* Address family not supported by protocol */
#define EADDRINUSE      __GLC_EADDRINUSE      /* Address already in use */
#define EADDRNOTAVAIL   __GLC_EADDRNOTAVAIL   /* Cannot assign requested address */
#define ENETDOWN        __GLC_ENETDOWN        /* Network is down */
#define ENETUNREACH     __GLC_ENETUNREACH     /* Network is unreachable */
#define ENETRESET       __GLC_ENETRESET       /* Network dropped connection because of reset */
#define ECONNABORTED    __GLC_ECONNABORTED    /* Software caused connection abort */
#define ECONNRESET      __GLC_ECONNRESET      /* Connection reset by peer */
#define ENOBUFS         __GLC_ENOBUFS         /* No buffer space available */
#define EISCONN         __GLC_EISCONN         /* Transport endpoint is already connected */
#define ENOTCONN        __GLC_ENOTCONN        /* Transport endpoint is not connected */
#define ESHUTDOWN       __GLC_ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#define ETOOMANYREFS    __GLC_ETOOMANYREFS    /* Too many references: cannot splice */
#define ETIMEDOUT       __GLC_ETIMEDOUT       /* Connection timed out */
#define ECONNREFUSED    __GLC_ECONNREFUSED    /* Connection refused */
#define EHOSTDOWN       __GLC_EHOSTDOWN       /* Host is down */
#define EHOSTUNREACH    __GLC_EHOSTUNREACH    /* No route to host */
#define EALREADY        __GLC_EALREADY        /* Operation already in progress */
#define EINPROGRESS     __GLC_EINPROGRESS     /* Operation now in progress */
#define ESTALE          __GLC_ESTALE          /* Stale file handle */
#define EUCLEAN         __GLC_EUCLEAN         /* Structure needs cleaning */
#define ENOTNAM         __GLC_ENOTNAM         /* Not a XENIX named type file */
#define ENAVAIL         __GLC_ENAVAIL         /* No XENIX semaphores available */
#define EISNAM          __GLC_EISNAM          /* Is a named type file */
#define EREMOTEIO       __GLC_EREMOTEIO       /* Remote I/O error */
#define EDQUOT          __GLC_EDQUOT          /* Quota exceeded */
#define ENOMEDIUM       __GLC_ENOMEDIUM       /* No medium found */
#define EMEDIUMTYPE     __GLC_EMEDIUMTYPE     /* Wrong medium type */
#define ECANCELED       __GLC_ECANCELED       /* Operation Canceled */
#define ENOKEY          __GLC_ENOKEY          /* Required key not available */
#define EKEYEXPIRED     __GLC_EKEYEXPIRED     /* Key has expired */
#define EKEYREVOKED     __GLC_EKEYREVOKED     /* Key has been revoked */
#define EKEYREJECTED    __GLC_EKEYREJECTED    /* Key was rejected by service */
#define EOWNERDEAD      __GLC_EOWNERDEAD      /* Owner died */
#define ENOTRECOVERABLE __GLC_ENOTRECOVERABLE /* State not recoverable */
#define ERFKILL         __GLC_ERFKILL         /* Operation not possible due to RF-kill */
#define EHWPOISON       __GLC_EHWPOISON       /* Memory page has hardware error */
#else /* CRT-specific... */
#include <parts/generic/errno.h>

/* Fallback: http://www.virtsync.com/c-error-codes-include-errno
 *   - When I looked it up, that page was the first google result
 *     for `errno.h', so judging by that fact, there shouldn't be
 *     better fallback values for errno codes! */
#define EPERM           __GEN_EPERM           /* Operation not permitted */
#define ENOENT          __GEN_ENOENT          /* No such file or directory */
#define ESRCH           __GEN_ESRCH           /* No such process */
#define EINTR           __GEN_EINTR           /* Interrupted system call */
#define EIO             __GEN_EIO             /* I/O error */
#define ENXIO           __GEN_ENXIO           /* No such device or address */
#define E2BIG           __GEN_E2BIG           /* Argument list too long */
#define ENOEXEC         __GEN_ENOEXEC         /* Exec format error */
#define EBADF           __GEN_EBADF           /* Bad file number */
#define ECHILD          __GEN_ECHILD          /* No child processes */
#define EAGAIN          __GEN_EAGAIN          /* Try again */
#define ENOMEM          __GEN_ENOMEM          /* Out of memory */
#define EACCES          __GEN_EACCES          /* Permission denied */
#define EFAULT          __GEN_EFAULT          /* Bad address */
#define ENOTBLK         __GEN_ENOTBLK         /* Block device required */
#define EBUSY           __GEN_EBUSY           /* Device or resource busy */
#define EEXIST          __GEN_EEXIST          /* File exists */
#define EXDEV           __GEN_EXDEV           /* Cross-device link */
#define ENODEV          __GEN_ENODEV          /* No such device */
#define ENOTDIR         __GEN_ENOTDIR         /* Not a directory */
#define EISDIR          __GEN_EISDIR          /* Is a directory */
#define EINVAL          __GEN_EINVAL          /* Invalid argument */
#define ENFILE          __GEN_ENFILE          /* File table overflow */
#define EMFILE          __GEN_EMFILE          /* Too many open files */
#define ENOTTY          __GEN_ENOTTY          /* Not a typewriter */
#define ETXTBSY         __GEN_ETXTBSY         /* Text file busy */
#define EFBIG           __GEN_EFBIG           /* File too large */
#define ENOSPC          __GEN_ENOSPC          /* No space left on device */
#define ESPIPE          __GEN_ESPIPE          /* Illegal seek */
#define EROFS           __GEN_EROFS           /* Read-only file system */
#define EMLINK          __GEN_EMLINK          /* Too many links */
#define EPIPE           __GEN_EPIPE           /* Broken pipe */
#define EDOM            __GEN_EDOM            /* Math argument out of domain of func */
#define ERANGE          __GEN_ERANGE          /* Math result not representable */
#define EDEADLK         __GEN_EDEADLK         /* Resource deadlock would occur */
#define ENAMETOOLONG    __GEN_ENAMETOOLONG    /* File name too long */
#define ENOLCK          __GEN_ENOLCK          /* No record locks available */
#define ENOSYS          __GEN_ENOSYS          /* Function not implemented */
#define ENOTEMPTY       __GEN_ENOTEMPTY       /* Directory not empty */
#define ELOOP           __GEN_ELOOP           /* Too many symbolic links encountered */
#define EWOULDBLOCK     __GEN_EWOULDBLOCK     /* Operation would block */
#define ENOMSG          __GEN_ENOMSG          /* No message of desired type */
#define EIDRM           __GEN_EIDRM           /* Identifier removed */
#define ECHRNG          __GEN_ECHRNG          /* Channel number out of range */
#define EL2NSYNC        __GEN_EL2NSYNC        /* Level 2 not synchronized */
#define EL3HLT          __GEN_EL3HLT          /* Level 3 halted */
#define EL3RST          __GEN_EL3RST          /* Level 3 reset */
#define ELNRNG          __GEN_ELNRNG          /* Link number out of range */
#define EUNATCH         __GEN_EUNATCH         /* Protocol driver not attached */
#define ENOCSI          __GEN_ENOCSI          /* No CSI structure available */
#define EL2HLT          __GEN_EL2HLT          /* Level 2 halted */
#define EBADE           __GEN_EBADE           /* Invalid exchange */
#define EBADR           __GEN_EBADR           /* Invalid request descriptor */
#define EXFULL          __GEN_EXFULL          /* Exchange full */
#define ENOANO          __GEN_ENOANO          /* No anode */
#define EBADRQC         __GEN_EBADRQC         /* Invalid request code */
#define EBADSLT         __GEN_EBADSLT         /* Invalid slot */
#define EDEADLOCK       __GEN_EDEADLOCK       /* Resource deadlock would occur */
#define EBFONT          __GEN_EBFONT          /* Bad font file format */
#define ENOSTR          __GEN_ENOSTR          /* Device not a stream */
#define ENODATA         __GEN_ENODATA         /* No data available */
#define ETIME           __GEN_ETIME           /* Timer expired */
#define ENOSR           __GEN_ENOSR           /* Out of streams resources */
#define ENONET          __GEN_ENONET          /* Machine is not on the network */
#define ENOPKG          __GEN_ENOPKG          /* Package not installed */
#define EREMOTE         __GEN_EREMOTE         /* Object is remote */
#define ENOLINK         __GEN_ENOLINK         /* Link has been severed */
#define EADV            __GEN_EADV            /* Advertise error */
#define ESRMNT          __GEN_ESRMNT          /* Srmount error */
#define ECOMM           __GEN_ECOMM           /* Communication error on send */
#define EPROTO          __GEN_EPROTO          /* Protocol error */
#define EMULTIHOP       __GEN_EMULTIHOP       /* Multihop attempted */
#define EDOTDOT         __GEN_EDOTDOT         /* RFS specific error */
#define EBADMSG         __GEN_EBADMSG         /* Not a data message */
#define EOVERFLOW       __GEN_EOVERFLOW       /* Value too large for defined data type */
#define ENOTUNIQ        __GEN_ENOTUNIQ        /* Name not unique on network */
#define EBADFD          __GEN_EBADFD          /* File descriptor in bad state */
#define EREMCHG         __GEN_EREMCHG         /* Remote address changed */
#define ELIBACC         __GEN_ELIBACC         /* Can not access a needed shared library */
#define ELIBBAD         __GEN_ELIBBAD         /* Accessing a corrupted shared library */
#define ELIBSCN         __GEN_ELIBSCN         /* .lib section in a.out corrupted */
#define ELIBMAX         __GEN_ELIBMAX         /* Attempting to link in too many shared libraries */
#define ELIBEXEC        __GEN_ELIBEXEC        /* Cannot exec a shared library directly */
#define EILSEQ          __GEN_EILSEQ          /* Illegal byte sequence */
#define ERESTART        __GEN_ERESTART        /* Interrupted system call should be restarted */
#define ESTRPIPE        __GEN_ESTRPIPE        /* Streams pipe error */
#define EUSERS          __GEN_EUSERS          /* Too many users */
#define ENOTSOCK        __GEN_ENOTSOCK        /* Socket operation on non-socket */
#define EDESTADDRREQ    __GEN_EDESTADDRREQ    /* Destination address required */
#define EMSGSIZE        __GEN_EMSGSIZE        /* Message too long */
#define EPROTOTYPE      __GEN_EPROTOTYPE      /* Protocol wrong type for socket */
#define ENOPROTOOPT     __GEN_ENOPROTOOPT     /* Protocol not available */
#define EPROTONOSUPPORT __GEN_EPROTONOSUPPORT /* Protocol not supported */
#define ESOCKTNOSUPPORT __GEN_ESOCKTNOSUPPORT /* Socket type not supported */
#define EOPNOTSUPP      __GEN_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define EPFNOSUPPORT    __GEN_EPFNOSUPPORT    /* Protocol family not supported */
#define EAFNOSUPPORT    __GEN_EAFNOSUPPORT    /* Address family not supported by protocol */
#define EADDRINUSE      __GEN_EADDRINUSE      /* Address already in use */
#define EADDRNOTAVAIL   __GEN_EADDRNOTAVAIL   /* Cannot assign requested address */
#define ENETDOWN        __GEN_ENETDOWN        /* Network is down */
#define ENETUNREACH     __GEN_ENETUNREACH     /* Network is unreachable */
#define ENETRESET       __GEN_ENETRESET       /* Network dropped connection because of reset */
#define ECONNABORTED    __GEN_ECONNABORTED    /* Software caused connection abort */
#define ECONNRESET      __GEN_ECONNRESET      /* Connection reset by peer */
#define ENOBUFS         __GEN_ENOBUFS         /* No buffer space available */
#define EISCONN         __GEN_EISCONN         /* Transport endpoint is already connected */
#define ENOTCONN        __GEN_ENOTCONN        /* Transport endpoint is not connected */
#define ESHUTDOWN       __GEN_ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#define ETOOMANYREFS    __GEN_ETOOMANYREFS    /* Too many references: cannot splice */
#define ETIMEDOUT       __GEN_ETIMEDOUT       /* Connection timed out */
#define ECONNREFUSED    __GEN_ECONNREFUSED    /* Connection refused */
#define EHOSTDOWN       __GEN_EHOSTDOWN       /* Host is down */
#define EHOSTUNREACH    __GEN_EHOSTUNREACH    /* No route to host */
#define EALREADY        __GEN_EALREADY        /* Operation already in progress */
#define EINPROGRESS     __GEN_EINPROGRESS     /* Operation now in progress */
#define ESTALE          __GEN_ESTALE          /* Stale NFS file handle */
#define EUCLEAN         __GEN_EUCLEAN         /* Structure needs cleaning */
#define ENOTNAM         __GEN_ENOTNAM         /* Not a XENIX named type file */
#define ENAVAIL         __GEN_ENAVAIL         /* No XENIX semaphores available */
#define EISNAM          __GEN_EISNAM          /* Is a named type file */
#define EREMOTEIO       __GEN_EREMOTEIO       /* Remote I/O error */
#define EDQUOT          __GEN_EDQUOT          /* Quota exceeded */
#define ENOMEDIUM       __GEN_ENOMEDIUM       /* No medium found */
#define EMEDIUMTYPE     __GEN_EMEDIUMTYPE     /* Wrong medium type */
#define ECANCELED       __GEN_ECANCELED       /* Operation Canceled */
#define ENOKEY          __GEN_ENOKEY          /* Required key not available */
#define EKEYEXPIRED     __GEN_EKEYEXPIRED     /* Key has expired */
#define EKEYREVOKED     __GEN_EKEYREVOKED     /* Key has been revoked */
#define EKEYREJECTED    __GEN_EKEYREJECTED    /* Key was rejected by service */
#define EOWNERDEAD      __GEN_EOWNERDEAD      /* Owner died */
#define ENOTRECOVERABLE __GEN_ENOTRECOVERABLE /* State not recoverable */
#endif /* Generic... */

#if !defined(ENOTSUP) && defined(EOPNOTSUPP)
#define ENOTSUP EOPNOTSUPP
#endif

#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL)) && !defined(EOK)
#define EOK          0 /* Operation completed successfully */
#endif /* (__USE_KOS || __USE_KOS_KERNEL) && !EOK */

#ifdef __CC__

__SYSDECL_BEGIN

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#ifdef __USE_KOS_KERNEL
/* Helper macros for testing the return values of
 * system calls (s.a. <kos/syscalls.h>) in errno-mode */
#define E_ISOK(x)  ((__syscall_ulong_t)(x) <= (__syscall_ulong_t)-4096)
#define E_ISERR(x) ((__syscall_ulong_t)(x) > (__syscall_ulong_t)-4096)
#endif /* __USE_KOS_KERNEL */


/* The `errno' global variable! */
#ifndef errno
#ifdef __errno
#define errno __errno
#else /* __errno */
}

[[guard, alias("_errno", "__errno"), wunused]]
[[ATTR_CONST, section(".text.crt.errno_access")]]
[[nonnull]] $errno_t *__errno_location();


%{
#ifdef ____errno_location_defined
#define errno     (*__errno_location())
#elif defined(__CRT_HAVE_errno) && 0
__LIBC __ATTR_THREAD __errno_t errno;
#define errno  errno
#elif defined(__CRT_HAVE_errno)
__LIBC __errno_t errno;
#define errno  errno
#endif /* ... */
#endif /* !__errno */
#endif /* !errno */

#ifdef __USE_GNU

/* Alias for argv[0], as passed to main() */
#ifndef program_invocation_name
#ifdef _pgmptr
#define program_invocation_name _pgmptr
#elif defined(_pgmptr)
#define program_invocation_name __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
__LIBC char *program_invocation_name;
#define program_invocation_name program_invocation_name
#elif defined(__CRT_HAVE__pgmptr)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_name __ASMNAME("_pgmptr");
#define program_invocation_name  program_invocation_name
#else /* !__NO_ASMNAME */
__LIBC char *_pgmptr;
#define _pgmptr                 _pgmptr
#define program_invocation_name _pgmptr
#endif /* __NO_ASMNAME */
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_name __ASMNAME("__progname_full");
#define program_invocation_name  program_invocation_name
#else /* !__NO_ASMNAME */
__LIBC char *__progname_full;
#define __progname_full         __progname_full
#define program_invocation_name __progname_full
#endif /* __NO_ASMNAME */
#else /* ... */
}
%[insert:extern(__p__pgmptr)]
%{
#ifdef ____p__pgmptr_defined
#define program_invocation_name (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !program_invocation_name */

/* Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
#ifndef program_invocation_short_name
#ifdef __progname
#define program_invocation_short_name __progname
#elif defined(__CRT_HAVE_program_invocation_short_name)
__LIBC char *program_invocation_short_name;
#define program_invocation_short_name program_invocation_short_name
#elif defined(__CRT_HAVE___progname)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_short_name __ASMNAME("__progname");
#define program_invocation_short_name  program_invocation_short_name
#else /* !__NO_ASMNAME */
__LIBC char *__progname;
#define __progname                    __progname
#define program_invocation_short_name __progname
#endif /* __NO_ASMNAME */
#else /* ... */
}
@@Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main()
[[guard, wunused, ATTR_CONST, nonnull]]
char **__p_program_invocation_short_name();
%{
#ifdef ____p__pgmptr_defined
#define program_invocation_name (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !program_invocation_short_name */

#ifndef __error_t_defined
#define __error_t_defined 1
typedef __errno_t error_t;
#endif /* !__error_t_defined */

#endif /* __USE_GNU */

__SYSDECL_END

#endif /* __CC__ */

}

