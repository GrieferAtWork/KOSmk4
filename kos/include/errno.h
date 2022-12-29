/* HASH CRC-32:0xa0169001 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/errno.h) */
/* (#) Portability: DJGPP         (/include/errno.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/errno.h) */
/* (#) Portability: GNU C Library (/stdlib/errno.h) */
/* (#) Portability: GNU Hurd      (/usr/include/errno.h) */
/* (#) Portability: MSVC          (/include/errno.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/errno.h) */
/* (#) Portability: NetBSD        (/include/errno.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/errno.h) */
/* (#) Portability: OpenBSD       (/include/errno.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/errno.h) */
/* (#) Portability: PDCLib        (/include/errno.h) */
/* (#) Portability: Windows Kits  (/ucrt/errno.h) */
/* (#) Portability: avr-libc      (/include/errno.h) */
/* (#) Portability: diet libc     (/include/errno.h) */
/* (#) Portability: libc4/5       (/include/errno.h) */
/* (#) Portability: libc6         (/include/errno.h) */
/* (#) Portability: libcmini      (/include/errno.h) */
/* (#) Portability: mintlib       (/include/errno.h) */
/* (#) Portability: musl libc     (/include/errno.h) */
/* (#) Portability: uClibc        (/include/errno.h) */
#ifndef _ERRNO_H
#define _ERRNO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/errno.h>
#include <bits/types.h>

/************************************************************************/
/* System errno codes                                                   */
/************************************************************************/
#ifdef __E2BIG
#define E2BIG           __E2BIG           /* Argument list too long */
#endif /* __E2BIG */
#ifdef __EACCES
#define EACCES          __EACCES          /* Permission denied */
#endif /* __EACCES */
#ifdef __EADDRINUSE
#define EADDRINUSE      __EADDRINUSE      /* Address already in use */
#endif /* __EADDRINUSE */
#ifdef __EADDRNOTAVAIL
#define EADDRNOTAVAIL   __EADDRNOTAVAIL   /* Cannot assign requested address */
#endif /* __EADDRNOTAVAIL */
#ifdef __EADV
#define EADV            __EADV            /* Advertise error */
#endif /* __EADV */
#ifdef __EAFNOSUPPORT
#define EAFNOSUPPORT    __EAFNOSUPPORT    /* Address family not supported by protocol */
#endif /* __EAFNOSUPPORT */
#ifdef __EAGAIN
#define EAGAIN          __EAGAIN          /* Try again */
#endif /* __EAGAIN */
#ifdef __EALREADY
#define EALREADY        __EALREADY        /* Operation already in progress */
#endif /* __EALREADY */
#ifdef __EAUTH
#define EAUTH           __EAUTH           /* ??? */
#endif /* __EAUTH */
#ifdef __EBADE
#define EBADE           __EBADE           /* Invalid exchange */
#endif /* __EBADE */
#ifdef __EBADF
#define EBADF           __EBADF           /* Bad file number */
#endif /* __EBADF */
#ifdef __EBADFD
#define EBADFD          __EBADFD          /* File descriptor in bad state */
#endif /* __EBADFD */
#ifdef __EBADMSG
#define EBADMSG         __EBADMSG         /* Not a data message */
#endif /* __EBADMSG */
#ifdef __EBADR
#define EBADR           __EBADR           /* Invalid request descriptor */
#endif /* __EBADR */
#ifdef __EBADRPC
#define EBADRPC         __EBADRPC         /* ??? */
#endif /* __EBADRPC */
#ifdef __EBADRQC
#define EBADRQC         __EBADRQC         /* Invalid request code */
#endif /* __EBADRQC */
#ifdef __EBADSLT
#define EBADSLT         __EBADSLT         /* Invalid slot */
#endif /* __EBADSLT */
#ifdef __EBFONT
#define EBFONT          __EBFONT          /* Bad font file format */
#endif /* __EBFONT */
#ifdef __EBUSY
#define EBUSY           __EBUSY           /* Device or resource busy */
#endif /* __EBUSY */
#ifdef __ECANCELED
#define ECANCELED       __ECANCELED       /* Operation canceled */
#endif /* __ECANCELED */
#ifdef __ECASECLASH
#define ECASECLASH      __ECASECLASH      /* Filename exists with different case */
#endif /* __ECASECLASH */
#ifdef __ECHILD
#define ECHILD          __ECHILD          /* No child processes */
#endif /* __ECHILD */
#ifdef __ECHRNG
#define ECHRNG          __ECHRNG          /* Channel number out of range */
#endif /* __ECHRNG */
#ifdef __ECOMM
#define ECOMM           __ECOMM           /* Communication error on send */
#endif /* __ECOMM */
#ifdef __ECONNABORTED
#define ECONNABORTED    __ECONNABORTED    /* Software caused connection abort */
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
#define ECONNREFUSED    __ECONNREFUSED    /* Connection refused */
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
#define ECONNRESET      __ECONNRESET      /* Connection reset by peer */
#endif /* __ECONNRESET */
#ifdef __EDEADLK
#define EDEADLK         __EDEADLK         /* Resource deadlock would occur */
#endif /* __EDEADLK */
#ifdef __EDEADLOCK
#define EDEADLOCK       __EDEADLOCK       /* Resource deadlock would occur */
#endif /* __EDEADLOCK */
#ifdef __EDESTADDRREQ
#define EDESTADDRREQ    __EDESTADDRREQ    /* Destination address required */
#endif /* __EDESTADDRREQ */
#ifdef __EDOM
#define EDOM            __EDOM            /* Math argument out of domain of func */
#endif /* __EDOM */
#ifdef __EDOTDOT
#define EDOTDOT         __EDOTDOT         /* RFS specific error */
#endif /* __EDOTDOT */
#ifdef __EDQUOT
#define EDQUOT          __EDQUOT          /* Quota exceeded */
#endif /* __EDQUOT */
#ifdef __EEXIST
#define EEXIST          __EEXIST          /* File exists */
#endif /* __EEXIST */
#ifdef __EFAULT
#define EFAULT          __EFAULT          /* Bad address */
#endif /* __EFAULT */
#ifdef __EFBIG
#define EFBIG           __EFBIG           /* File too large */
#endif /* __EFBIG */
#ifdef __EFTYPE
#define EFTYPE          __EFTYPE          /* Inappropriate file type or format */
#endif /* __EFTYPE */
#ifdef __EHOSTDOWN
#define EHOSTDOWN       __EHOSTDOWN       /* Host is down */
#endif /* __EHOSTDOWN */
#ifdef __EHOSTUNREACH
#define EHOSTUNREACH    __EHOSTUNREACH    /* No route to host */
#endif /* __EHOSTUNREACH */
#ifdef __EHWPOISON
#define EHWPOISON       __EHWPOISON       /* Memory page has hardware error */
#endif /* __EHWPOISON */
#ifdef __EIDRM
#define EIDRM           __EIDRM           /* Identifier removed */
#endif /* __EIDRM */
#ifdef __EILSEQ
#define EILSEQ          __EILSEQ          /* Illegal byte sequence */
#endif /* __EILSEQ */
#ifdef __EINPROGRESS
#define EINPROGRESS     __EINPROGRESS     /* Operation now in progress */
#endif /* __EINPROGRESS */
#ifdef __EINTR
#define EINTR           __EINTR           /* Interrupted system call */
#endif /* __EINTR */
#ifdef __EINVAL
#define EINVAL          __EINVAL          /* Invalid argument */
#endif /* __EINVAL */
#ifdef __EIO
#define EIO             __EIO             /* I/O error */
#endif /* __EIO */
#ifdef __EISCONN
#define EISCONN         __EISCONN         /* Transport endpoint is already connected */
#endif /* __EISCONN */
#ifdef __EISDIR
#define EISDIR          __EISDIR          /* Is a directory */
#endif /* __EISDIR */
#ifdef __EISNAM
#define EISNAM          __EISNAM          /* Is a named type file */
#endif /* __EISNAM */
#ifdef __EKEYEXPIRED
#define EKEYEXPIRED     __EKEYEXPIRED     /* Key has expired */
#endif /* __EKEYEXPIRED */
#ifdef __EKEYREJECTED
#define EKEYREJECTED    __EKEYREJECTED    /* Key was rejected by service */
#endif /* __EKEYREJECTED */
#ifdef __EKEYREVOKED
#define EKEYREVOKED     __EKEYREVOKED     /* Key has been revoked */
#endif /* __EKEYREVOKED */
#ifdef __EL2HLT
#define EL2HLT          __EL2HLT          /* Level 2 halted */
#endif /* __EL2HLT */
#ifdef __EL2NSYNC
#define EL2NSYNC        __EL2NSYNC        /* Level 2 not synchronized */
#endif /* __EL2NSYNC */
#ifdef __EL3HLT
#define EL3HLT          __EL3HLT          /* Level 3 halted */
#endif /* __EL3HLT */
#ifdef __EL3RST
#define EL3RST          __EL3RST          /* Level 3 reset */
#endif /* __EL3RST */
#ifdef __ELBIN
#define ELBIN           __ELBIN           /* Inode is remote (not really error) */
#endif /* __ELBIN */
#ifdef __ELIBACC
#define ELIBACC         __ELIBACC         /* Can not access a needed shared library */
#endif /* __ELIBACC */
#ifdef __ELIBBAD
#define ELIBBAD         __ELIBBAD         /* Accessing a corrupted shared library */
#endif /* __ELIBBAD */
#ifdef __ELIBEXEC
#define ELIBEXEC        __ELIBEXEC        /* Cannot exec a shared library directly */
#endif /* __ELIBEXEC */
#ifdef __ELIBMAX
#define ELIBMAX         __ELIBMAX         /* Attempting to link in too many shared libraries */
#endif /* __ELIBMAX */
#ifdef __ELIBSCN
#define ELIBSCN         __ELIBSCN         /* .lib section in a.out corrupted */
#endif /* __ELIBSCN */
#ifdef __ELNRNG
#define ELNRNG          __ELNRNG          /* Link number out of range */
#endif /* __ELNRNG */
#ifdef __ELOCKUNMAPPED
#define ELOCKUNMAPPED   __ELOCKUNMAPPED   /* ??? */
#endif /* __ELOCKUNMAPPED */
#ifdef __ELOOP
#define ELOOP           __ELOOP           /* Too many symbolic links encountered */
#endif /* __ELOOP */
#ifdef __EMEDIUMTYPE
#define EMEDIUMTYPE     __EMEDIUMTYPE     /* Wrong medium type */
#endif /* __EMEDIUMTYPE */
#ifdef __EMFILE
#define EMFILE          __EMFILE          /* Too many open files */
#endif /* __EMFILE */
#ifdef __EMLINK
#define EMLINK          __EMLINK          /* Too many links */
#endif /* __EMLINK */
#ifdef __EMSGSIZE
#define EMSGSIZE        __EMSGSIZE        /* Message too long */
#endif /* __EMSGSIZE */
#ifdef __EMULTIHOP
#define EMULTIHOP       __EMULTIHOP       /* Multihop attempted */
#endif /* __EMULTIHOP */
#ifdef __ENAMETOOLONG
#define ENAMETOOLONG    __ENAMETOOLONG    /* File name too long */
#endif /* __ENAMETOOLONG */
#ifdef __ENAVAIL
#define ENAVAIL         __ENAVAIL         /* No XENIX semaphores available */
#endif /* __ENAVAIL */
#ifdef __ENEEDAUTH
#define ENEEDAUTH       __ENEEDAUTH       /* ??? */
#endif /* __ENEEDAUTH */
#ifdef __ENETDOWN
#define ENETDOWN        __ENETDOWN        /* Network is down */
#endif /* __ENETDOWN */
#ifdef __ENETRESET
#define ENETRESET       __ENETRESET       /* Network dropped connection because of reset */
#endif /* __ENETRESET */
#ifdef __ENETUNREACH
#define ENETUNREACH     __ENETUNREACH     /* Network is unreachable */
#endif /* __ENETUNREACH */
#ifdef __ENFILE
#define ENFILE          __ENFILE          /* File table overflow */
#endif /* __ENFILE */
#ifdef __ENMFILE
#define ENMFILE         __ENMFILE         /* No more files */
#endif /* __ENMFILE */
#ifdef __ENOANO
#define ENOANO          __ENOANO          /* No anode */
#endif /* __ENOANO */
#ifdef __ENOATTR
#define ENOATTR         __ENOATTR         /* ??? */
#endif /* __ENOATTR */
#ifdef __ENOBUFS
#define ENOBUFS         __ENOBUFS         /* No buffer space available */
#endif /* __ENOBUFS */
#ifdef __ENOCSI
#define ENOCSI          __ENOCSI          /* No CSI structure available */
#endif /* __ENOCSI */
#ifdef __ENODATA
#define ENODATA         __ENODATA         /* No data available */
#endif /* __ENODATA */
#ifdef __ENODEV
#define ENODEV          __ENODEV          /* No such device */
#endif /* __ENODEV */
#ifdef __ENOENT
#define ENOENT          __ENOENT          /* No such file or directory */
#endif /* __ENOENT */
#ifdef __ENOEXEC
#define ENOEXEC         __ENOEXEC         /* Exec format error */
#endif /* __ENOEXEC */
#ifdef __ENOKEY
#define ENOKEY          __ENOKEY          /* Required key not available */
#endif /* __ENOKEY */
#ifdef __ENOLCK
#define ENOLCK          __ENOLCK          /* No record locks available */
#endif /* __ENOLCK */
#ifdef __ENOLINK
#define ENOLINK         __ENOLINK         /* Link has been severed */
#endif /* __ENOLINK */
#ifdef __ENOMEDIUM
#define ENOMEDIUM       __ENOMEDIUM       /* No medium found */
#endif /* __ENOMEDIUM */
#ifdef __ENOMEM
#define ENOMEM          __ENOMEM          /* Out of memory */
#endif /* __ENOMEM */
#ifdef __ENOMSG
#define ENOMSG          __ENOMSG          /* No message of desired type */
#endif /* __ENOMSG */
#ifdef __ENONET
#define ENONET          __ENONET          /* Machine is not on the network */
#endif /* __ENONET */
#ifdef __ENOPKG
#define ENOPKG          __ENOPKG          /* Package not installed */
#endif /* __ENOPKG */
#ifdef __ENOPROTOOPT
#define ENOPROTOOPT     __ENOPROTOOPT     /* Protocol not available */
#endif /* __ENOPROTOOPT */
#ifdef __ENOSHARE
#define ENOSHARE        __ENOSHARE        /* No such host or network path */
#endif /* __ENOSHARE */
#ifdef __ENOSPC
#define ENOSPC          __ENOSPC          /* No space left on device */
#endif /* __ENOSPC */
#ifdef __ENOSR
#define ENOSR           __ENOSR           /* Out of streams resources */
#endif /* __ENOSR */
#ifdef __ENOSTR
#define ENOSTR          __ENOSTR          /* Device not a stream */
#endif /* __ENOSTR */
#ifdef __ENOSYS
#define ENOSYS          __ENOSYS          /* Function not implemented */
#endif /* __ENOSYS */
#ifdef __ENOTACTIVE
#define ENOTACTIVE      __ENOTACTIVE      /* ??? */
#endif /* __ENOTACTIVE */
#ifdef __ENOTBLK
#define ENOTBLK         __ENOTBLK         /* Block device required */
#endif /* __ENOTBLK */
#ifdef __ENOTCONN
#define ENOTCONN        __ENOTCONN        /* Transport endpoint is not connected */
#endif /* __ENOTCONN */
#ifdef __ENOTDIR
#define ENOTDIR         __ENOTDIR         /* Not a directory */
#endif /* __ENOTDIR */
#ifdef __ENOTEMPTY
#define ENOTEMPTY       __ENOTEMPTY       /* Directory not empty */
#endif /* __ENOTEMPTY */
#ifdef __ENOTNAM
#define ENOTNAM         __ENOTNAM         /* Not a XENIX named type file */
#endif /* __ENOTNAM */
#ifdef __ENOTRECOVERABLE
#define ENOTRECOVERABLE __ENOTRECOVERABLE /* State not recoverable */
#endif /* __ENOTRECOVERABLE */
#ifdef __ENOTSOCK
#define ENOTSOCK        __ENOTSOCK        /* Socket operation on non-socket */
#endif /* __ENOTSOCK */
#ifdef __ENOTSUP
#define ENOTSUP         __ENOTSUP         /* Not supported */
#endif /* __ENOTSUP */
#ifdef __ENOTTY
#define ENOTTY          __ENOTTY          /* Not a typewriter */
#endif /* __ENOTTY */
#ifdef __ENOTUNIQ
#define ENOTUNIQ        __ENOTUNIQ        /* Name not unique on network */
#endif /* __ENOTUNIQ */
#ifdef __ENXIO
#define ENXIO           __ENXIO           /* No such device or address */
#endif /* __ENXIO */
#ifdef __EOPNOTSUPP
#define EOPNOTSUPP      __EOPNOTSUPP      /* Operation not supported on transport endpoint */
#endif /* __EOPNOTSUPP */
#ifdef __EOTHER
#define EOTHER          __EOTHER          /* Other */
#endif /* __EOTHER */
#ifdef __EOVERFLOW
#define EOVERFLOW       __EOVERFLOW       /* Value too large for defined data type */
#endif /* __EOVERFLOW */
#ifdef __EOWNERDEAD
#define EOWNERDEAD      __EOWNERDEAD      /* Owner died */
#endif /* __EOWNERDEAD */
#ifdef __EPERM
#define EPERM           __EPERM           /* Operation not permitted */
#endif /* __EPERM */
#ifdef __EPFNOSUPPORT
#define EPFNOSUPPORT    __EPFNOSUPPORT    /* Protocol family not supported */
#endif /* __EPFNOSUPPORT */
#ifdef __EPIPE
#define EPIPE           __EPIPE           /* Broken pipe */
#endif /* __EPIPE */
#ifdef __EPROCLIM
#define EPROCLIM        __EPROCLIM        /* Process limit reached */
#endif /* __EPROCLIM */
#ifdef __EPROCUNAVAIL
#define EPROCUNAVAIL    __EPROCUNAVAIL    /* ??? */
#endif /* __EPROCUNAVAIL */
#ifdef __EPROGMISMATCH
#define EPROGMISMATCH   __EPROGMISMATCH   /* ??? */
#endif /* __EPROGMISMATCH */
#ifdef __EPROGUNAVAIL
#define EPROGUNAVAIL    __EPROGUNAVAIL    /* ??? */
#endif /* __EPROGUNAVAIL */
#ifdef __EPROTO
#define EPROTO          __EPROTO          /* Protocol error */
#endif /* __EPROTO */
#ifdef __EPROTONOSUPPORT
#define EPROTONOSUPPORT __EPROTONOSUPPORT /* Protocol not supported */
#endif /* __EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
#define EPROTOTYPE      __EPROTOTYPE      /* Protocol wrong type for socket */
#endif /* __EPROTOTYPE */
#ifdef __ERANGE
#define ERANGE          __ERANGE          /* Math result not representable */
#endif /* __ERANGE */
#ifdef __EREMCHG
#define EREMCHG         __EREMCHG         /* Remote address changed */
#endif /* __EREMCHG */
#ifdef __EREMOTE
#define EREMOTE         __EREMOTE         /* Object is remote */
#endif /* __EREMOTE */
#ifdef __EREMOTEIO
#define EREMOTEIO       __EREMOTEIO       /* Remote I/O error */
#endif /* __EREMOTEIO */
#ifdef __ERESTART
#define ERESTART        __ERESTART        /* Interrupted system call should be restarted */
#endif /* __ERESTART */
#ifdef __ERFKILL
#define ERFKILL         __ERFKILL         /* Operation not possible due to RF-kill */
#endif /* __ERFKILL */
#ifdef __EROFS
#define EROFS           __EROFS           /* Read-only file system */
#endif /* __EROFS */
#ifdef __ERPCMISMATCH
#define ERPCMISMATCH    __ERPCMISMATCH    /* ??? */
#endif /* __ERPCMISMATCH */
#ifdef __ESHUTDOWN
#define ESHUTDOWN       __ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#endif /* __ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT __ESOCKTNOSUPPORT /* Socket type not supported */
#endif /* __ESOCKTNOSUPPORT */
#ifdef __ESPIPE
#define ESPIPE          __ESPIPE          /* Illegal seek */
#endif /* __ESPIPE */
#ifdef __ESRCH
#define ESRCH           __ESRCH           /* No such process */
#endif /* __ESRCH */
#ifdef __ESRMNT
#define ESRMNT          __ESRMNT          /* Srmount error */
#endif /* __ESRMNT */
#ifdef __ESTALE
#define ESTALE          __ESTALE          /* Stale file handle */
#endif /* __ESTALE */
#ifdef __ESTRPIPE
#define ESTRPIPE        __ESTRPIPE        /* Streams pipe error */
#endif /* __ESTRPIPE */
#ifdef __ETIME
#define ETIME           __ETIME           /* Timer expired */
#endif /* __ETIME */
#ifdef __ETIMEDOUT
#define ETIMEDOUT       __ETIMEDOUT       /* Connection timed out */
#endif /* __ETIMEDOUT */
#ifdef __ETOOMANYREFS
#define ETOOMANYREFS    __ETOOMANYREFS    /* Too many references: cannot splice */
#endif /* __ETOOMANYREFS */
#ifdef __ETXTBSY
#define ETXTBSY         __ETXTBSY         /* Text file busy */
#endif /* __ETXTBSY */
#ifdef __EUCLEAN
#define EUCLEAN         __EUCLEAN         /* Structure needs cleaning */
#endif /* __EUCLEAN */
#ifdef __EUNATCH
#define EUNATCH         __EUNATCH         /* Protocol driver not attached */
#endif /* __EUNATCH */
#ifdef __EUSERS
#define EUSERS          __EUSERS          /* Too many users */
#endif /* __EUSERS */
#ifdef __EWOULDBLOCK
#define EWOULDBLOCK     __EWOULDBLOCK     /* Operation would block */
#endif /* __EWOULDBLOCK */
#ifdef __EXDEV
#define EXDEV           __EXDEV           /* Cross-device link */
#endif /* __EXDEV */
#ifdef __EXFULL
#define EXFULL          __EXFULL          /* Exchange full */
#endif /* __EXFULL */
#ifdef __STRUNCATE
#define STRUNCATE       __STRUNCATE       /* Truncated */
#endif /* __STRUNCATE */






/* Define some errno code aliases, or not already defined. */
#if !defined(EWOULDBLOCK) && defined(EAGAIN)
#define EWOULDBLOCK EAGAIN /* Operation would block */
#endif /* !EWOULDBLOCK && EAGAIN */

#if !defined(EDEADLOCK) && defined(EDEADLK)
#define EDEADLOCK EDEADLK /* Resource deadlock would occur */
#endif /* !EDEADLOCK && EDEADLK */

#if !defined(ENOTSUP) && defined(EOPNOTSUPP)
#define ENOTSUP EOPNOTSUPP /* Not supported */
#endif /* !ENOTSUP && EOPNOTSUPP */


/* Platform-specific extensions for errno limits. */
#ifdef __USE_NETBSD
#ifdef __ELIMIT
#define ELAST __ELIMIT /* Max possible errno */
#endif /* __ELIMIT */
#endif /* __USE_NETBSD */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifdef __EOK
#define EOK    __EOK    /* Operation completed successfully */
#endif /* __EOK */
#ifdef __EMAX
#define EMAX   __EMAX   /* Max errno */
#endif /* __EMAX */
#ifdef __ECOUNT
#define ECOUNT __ECOUNT /* Max errno + 1 */
#endif /* __ECOUNT */
#ifdef __ELIMIT
#define ELIMIT __ELIMIT /* Max possible errno */
#endif /* __ELIMIT */
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#if defined(__USE_KOS_KERNEL) && defined(__ELIMIT)
/* Helper  macros  for testing  the return  values of
 * system calls (s.a. <kos/syscalls.h>) in errno-mode */
#define E_ISOK(x)  (__CCAST(__syscall_ulong_t)(x) <= __CCAST(__syscall_ulong_t)-__ELIMIT)
#define E_ISERR(x) (__CCAST(__syscall_ulong_t)(x) > __CCAST(__syscall_ulong_t)-__ELIMIT)
#endif /* __USE_KOS_KERNEL && __ELIMIT */

#ifdef __CC__

__SYSDECL_BEGIN

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#endif /* __USE_KOS || __USE_KOS_KERNEL */


/* The `errno' global variable! */
#ifndef errno
#ifdef __libc_errno
#define errno __libc_errno
#else /* __libc_errno */
#ifndef ____errno_location_defined
#define ____errno_location_defined
#ifdef __CRT_HAVE___errno_location
/* >> __errno_location(3) */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),__errno,())
#else /* ... */
#undef ____errno_location_defined
#endif /* !... */
#endif /* !____errno_location_defined */
#ifdef ____errno_location_defined
#define errno (*__errno_location())
#elif defined(__CRT_HAVE_errno) && 0
__CSDECLARE(__ATTR_THREAD,__errno_t,errno)
#define errno errno
#elif defined(__CRT_HAVE_errno)
__CSDECLARE(,__errno_t,errno)
#define errno errno
#endif /* ... */
#endif /* !__libc_errno */
#endif /* !errno */

#ifdef __USE_GNU

/* Alias for argv[0], as passed to main() */
#ifndef program_invocation_name
#ifdef _pgmptr
#define program_invocation_name _pgmptr
#elif defined(_pgmptr)
#define program_invocation_name __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
__CSDECLARE(,char *,program_invocation_name)
#define program_invocation_name program_invocation_name
#elif defined(__CRT_HAVE__pgmptr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,program_invocation_name,_pgmptr)
#define program_invocation_name  program_invocation_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,_pgmptr)
#define _pgmptr                 _pgmptr
#define program_invocation_name _pgmptr
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,program_invocation_name,__progname_full)
#define program_invocation_name  program_invocation_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,__progname_full)
#define __progname_full         __progname_full
#define program_invocation_name __progname_full
#endif /* __NO_COMPILER_SREDIRECT */
#else /* ... */
#ifndef ____p__pgmptr_defined
#define ____p__pgmptr_defined
#ifdef __CRT_HAVE___p__pgmptr
/* Alias for argv[0], as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),())
#elif defined(__CRT_HAVE___p_program_invocation_name)
/* Alias for argv[0], as passed to main() */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),__p_program_invocation_name,())
#else /* ... */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name_p
#include <libc/local/stdlib/__p__pgmptr.h>
/* Alias for argv[0], as passed to main() */
__NAMESPACE_LOCAL_USING_OR_IMPL(__p__pgmptr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL __p__pgmptr)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__p__pgmptr))(); })
#else /* __LOCAL_program_invocation_name_p */
#undef ____p__pgmptr_defined
#endif /* !__LOCAL_program_invocation_name_p */
#endif /* !... */
#endif /* !____p__pgmptr_defined */
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
__CSDECLARE(,char *,program_invocation_short_name)
#define program_invocation_short_name program_invocation_short_name
#elif defined(__CRT_HAVE___progname)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,program_invocation_short_name,__progname)
#define program_invocation_short_name  program_invocation_short_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,__progname)
#define __progname                    __progname
#define program_invocation_short_name __progname
#endif /* __NO_COMPILER_SREDIRECT */
#else /* ... */
#ifndef ____p_program_invocation_short_name_defined
#define ____p_program_invocation_short_name_defined
#ifdef __CRT_HAVE___p_program_invocation_short_name
/* >> __p_program_invocation_short_name(3)
 * Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p_program_invocation_short_name,(void),())
#else /* __CRT_HAVE___p_program_invocation_short_name */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name_p
#include <libc/local/errno/__p_program_invocation_short_name.h>
/* >> __p_program_invocation_short_name(3)
 * Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
__NAMESPACE_LOCAL_USING_OR_IMPL(__p_program_invocation_short_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL __p_program_invocation_short_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__p_program_invocation_short_name))(); })
#else /* __LOCAL_program_invocation_short_name_p */
#undef ____p_program_invocation_short_name_defined
#endif /* !__LOCAL_program_invocation_short_name_p */
#endif /* !__CRT_HAVE___p_program_invocation_short_name */
#endif /* !____p_program_invocation_short_name_defined */
#ifdef ____p__pgmptr_defined
#define program_invocation_name (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !program_invocation_short_name */

#ifndef __error_t_defined
#define __error_t_defined
typedef __errno_t error_t;
#endif /* !__error_t_defined */

#endif /* __USE_GNU */

__SYSDECL_END

#if defined(__USE_BSD) || defined(__USE_GNU)
#include <bits/crt/sys_errlist.h>
#endif /* __USE_BSD || __USE_GNU */

#endif /* __CC__ */

#endif /* !_ERRNO_H */
