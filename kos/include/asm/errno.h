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
#ifndef _ASM_ERRNO_H
#define _ASM_ERRNO_H 1

#include <__crt.h>

/* After making changes to this file, update the following files:
 * $ deemon -F kos/src/libc/magic/errno.c
 * $ deemon -F kos/src/libc/libc/errno.h
 * $ deemon -F kos/src/libc/libc/errno-convert-cyg.c
 * $ deemon -F kos/src/libc/libc/errno-convert-dos.c
 * $ deemon -F kos/src/libc/libc/sys_errlist.def
 * Or the one-liner:
 * $ deemon -F kos/src/libc/magic/errno.c kos/src/libc/libc/errno.h kos/src/libc/libc/errno-convert-cyg.c kos/src/libc/libc/errno-convert-dos.c kos/src/libc/libc/sys_errlist.def
 *
 * Also note that generate_headers.dee will have to be re-run, though
 * it will be executed automatically because `magic/errno.c' is touched
 * by the above. */

#ifdef __CRT_CYG_PRIMARY
#include <sys/config.h> /* __LINUX_ERRNO_EXTENSIONS__ */

/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

/*[[[begin:cyg]]]*/
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
/*[[[end:cyg]]]*/
#define __EMAX       143  /* Max errno */
#define __ECOUNT     144  /* Max errno + 1 */
#define __ELASTERROR 2000 /* Users can add values starting here */
#define __ELIMIT     4096 /* Max possible errno */

#elif defined(__CRT_DOS_PRIMARY)

/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/
/*[[[begin:dos]]]*/
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
/*[[[end:dos]]]*/
#define __EMAX            140 /* Max errno */
#define __ECOUNT          141 /* Max errno + 1 */

#elif defined(__KOS__) || defined(__linux__)

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/*[[[begin:kos]]]*/
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
/*[[[end:kos]]]*/
#define __EMAX            133 /* Max errno */
#define __ECOUNT          134 /* Max errno + 1 */
#define __ELIMIT          4096 /* Max possible errno */

#elif defined(__NetBSD__)

#define __EPERM           1
#define __ENOENT          2
#define __ESRCH           3
#define __EINTR           4
#define __EIO             5
#define __ENXIO           6
#define __E2BIG           7
#define __ENOEXEC         8
#define __EBADF           9
#define __ECHILD          10
#define __EDEADLK         11
#define __ENOMEM          12
#define __EACCES          13
#define __EFAULT          14
#define __ENOTBLK         15
#define __EBUSY           16
#define __EEXIST          17
#define __EXDEV           18
#define __ENODEV          19
#define __ENOTDIR         20
#define __EISDIR          21
#define __EINVAL          22
#define __ENFILE          23
#define __EMFILE          24
#define __ENOTTY          25
#define __ETXTBSY         26
#define __EFBIG           27
#define __ENOSPC          28
#define __ESPIPE          29
#define __EROFS           30
#define __EMLINK          31
#define __EPIPE           32
#define __EDOM            33
#define __ERANGE          34
#define __EAGAIN          35
#define __EINPROGRESS     36
#define __EALREADY        37
#define __ENOTSOCK        38
#define __EDESTADDRREQ    39
#define __EMSGSIZE        40
#define __EPROTOTYPE      41
#define __ENOPROTOOPT     42
#define __EPROTONOSUPPORT 43
#define __ESOCKTNOSUPPORT 44
#define __EOPNOTSUPP      45
#define __EPFNOSUPPORT    46
#define __EAFNOSUPPORT    47
#define __EADDRINUSE      48
#define __EADDRNOTAVAIL   49
#define __ENETDOWN        50
#define __ENETUNREACH     51
#define __ENETRESET       52
#define __ECONNABORTED    53
#define __ECONNRESET      54
#define __ENOBUFS         55
#define __EISCONN         56
#define __ENOTCONN        57
#define __ESHUTDOWN       58
#define __ETOOMANYREFS    59
#define __ETIMEDOUT       60
#define __ECONNREFUSED    61
#define __ELOOP           62
#define __ENAMETOOLONG    63
#define __EHOSTDOWN       64
#define __EHOSTUNREACH    65
#define __ENOTEMPTY       66
#define __EPROCLIM        67
#define __EUSERS          68
#define __EDQUOT          69
#define __ESTALE          70
#define __EREMOTE         71
#define __EBADRPC         72
#define __ERPCMISMATCH    73
#define __EPROGUNAVAIL    74
#define __EPROGMISMATCH   75
#define __EPROCUNAVAIL    76
#define __ENOLCK          77
#define __ENOSYS          78
#define __EFTYPE          79
#define __EAUTH           80
#define __ENEEDAUTH       81
#define __EIDRM           82
#define __ENOMSG          83
#define __EOVERFLOW       84
#define __EILSEQ          85
#define __ENOTSUP         86
#define __ECANCELED       87
#define __EBADMSG         88
#define __ENODATA         89
#define __ENOSR           90
#define __ENOSTR          91
#define __ETIME           92
#define __ENOATTR         93
#define __EMULTIHOP       94
#define __ENOLINK         95
#define __EPROTO          96

#define __EMAX            96 /* Max errno */
#define __ECOUNT          97 /* Max errno + 1 */

#elif defined(__solaris__)

#define __EPERM           1
#define __ENOENT          2
#define __ESRCH           3
#define __EINTR           4
#define __EIO             5
#define __ENXIO           6
#define __E2BIG           7
#define __ENOEXEC         8
#define __EBADF           9
#define __ECHILD          10
#define __EAGAIN          11
#define __ENOMEM          12
#define __EACCES          13
#define __EFAULT          14
#define __ENOTBLK         15
#define __EBUSY           16
#define __EEXIST          17
#define __EXDEV           18
#define __ENODEV          19
#define __ENOTDIR         20
#define __EISDIR          21
#define __EINVAL          22
#define __ENFILE          23
#define __EMFILE          24
#define __ENOTTY          25
#define __ETXTBSY         26
#define __EFBIG           27
#define __ENOSPC          28
#define __ESPIPE          29
#define __EROFS           30
#define __EMLINK          31
#define __EPIPE           32
#define __EDOM            33
#define __ERANGE          34
#define __ENOMSG          35
#define __EIDRM           36
#define __ECHRNG          37
#define __EL2NSYNC        38
#define __EL3HLT          39
#define __EL3RST          40
#define __ELNRNG          41
#define __EUNATCH         42
#define __ENOCSI          43
#define __EL2HLT          44
#define __EDEADLK         45
#define __ENOLCK          46
#define __ECANCELED       47
#define __ENOTSUP         48
#define __EDQUOT          49
#define __EBADE           50
#define __EBADR           51
#define __EXFULL          52
#define __ENOANO          53
#define __EBADRQC         54
#define __EBADSLT         55
#define __EDEADLOCK       56
#define __EBFONT          57
#define __EOWNERDEAD      58
#define __ENOTRECOVERABLE 59
#define __ENOSTR          60
#define __ENODATA         61
#define __ETIME           62
#define __ENOSR           63
#define __ENONET          64
#define __ENOPKG          65
#define __EREMOTE         66
#define __ENOLINK         67
#define __EADV            68
#define __ESRMNT          69
#define __ECOMM           70
#define __EPROTO          71
#define __ELOCKUNMAPPED   72
#define __ENOTACTIVE      73
#define __EMULTIHOP       74
#define __EBADMSG         77
#define __ENAMETOOLONG    78
#define __EOVERFLOW       79
#define __ENOTUNIQ        80
#define __EBADFD          81
#define __EREMCHG         82
#define __ELIBACC         83
#define __ELIBBAD         84
#define __ELIBSCN         85
#define __ELIBMAX         86
#define __ELIBEXEC        87
#define __EILSEQ          88
#define __ENOSYS          89
#define __ELOOP           90
#define __ERESTART        91
#define __ESTRPIPE        92
#define __ENOTEMPTY       93
#define __EUSERS          94
#define __ENOTSOCK        95
#define __EDESTADDRREQ    96
#define __EMSGSIZE        97
#define __EPROTOTYPE      98
#define __ENOPROTOOPT     99
#define __EPROTONOSUPPORT 120
#define __ESOCKTNOSUPPORT 121
#define __EOPNOTSUPP      122
#define __EPFNOSUPPORT    123
#define __EAFNOSUPPORT    124
#define __EADDRINUSE      125
#define __EADDRNOTAVAIL   126
#define __ENETDOWN        127
#define __ENETUNREACH     128
#define __ENETRESET       129
#define __ECONNABORTED    130
#define __ECONNRESET      131
#define __ENOBUFS         132
#define __EISCONN         133
#define __ENOTCONN        134
#define __ESHUTDOWN       143
#define __ETOOMANYREFS    144
#define __ETIMEDOUT       145
#define __ECONNREFUSED    146
#define __EHOSTDOWN       147
#define __EHOSTUNREACH    148
#define __EALREADY        149
#define __EINPROGRESS     150
#define __ESTALE          151

#define __EMAX            151 /* Max errno */
#define __ECOUNT          152 /* Max errno + 1 */

#else /* ... */
/* XXX: Other platforms... */

/************************************************************************/
/* GENERIC (guessed)                                                    */
/************************************************************************/
#define __EPERM           1  /* Operation not permitted */
#define __ENOENT          2  /* No such file or directory */
#define __ESRCH           3  /* No such process */
#define __EINTR           4  /* Interrupted system call */
#define __EIO             5  /* I/O error */
#define __ENXIO           6  /* No such device or address */
#define __E2BIG           7  /* Argument list too long */
#define __ENOEXEC         8  /* Exec format error */
#define __EBADF           9  /* Bad file number */
#define __ECHILD          10 /* No child processes */
#define __EAGAIN          11 /* Try again */
#define __ENOMEM          12 /* Out of memory */
#define __EACCES          13 /* Permission denied */
#define __EFAULT          14 /* Bad address */
#define __EBUSY           16 /* Device or resource busy */
#define __EEXIST          17 /* File exists */
#define __EXDEV           18 /* Cross-device link */
#define __ENODEV          19 /* No such device */
#define __ENOTDIR         20 /* Not a directory */
#define __EISDIR          21 /* Is a directory */
#define __EINVAL          22 /* Invalid argument */
#define __ENFILE          23 /* File table overflow */
#define __EMFILE          24 /* Too many open files */
#define __ENOTTY          25 /* Not a typewriter */
#define __ETXTBSY         26 /* Text file busy */
#define __EFBIG           27 /* File too large */
#define __ENOSPC          28 /* No space left on device */
#define __ESPIPE          29 /* Illegal seek */
#define __EROFS           30 /* Read-only file system */
#define __EMLINK          31 /* Too many links */
#define __EPIPE           32 /* Broken pipe */
#define __EDOM            33 /* Math argument out of domain of func */
#define __ERANGE          34 /* Math result not representable */
#define __EMAX            34 /* Max errno */
#define __ECOUNT          35 /* Max errno + 1 */
#endif /* !... */

#ifndef __EOK
#define __EOK 0 /* Success */
#endif /* !__EOK */

#if !defined(__ELASTERROR) && defined(__EMAX)
#define __ELASTERROR __EMAX /* Users can add values starting here */
#endif /* !__ELASTERROR && __EMAX */

#if !defined(__ELIMIT) && defined(__EMAX)
#define __ELIMIT __EMAX /* Max possible errno */
#endif /* !__ELIMIT && __EMAX */


#endif /* !_ASM_ERRNO_H */
