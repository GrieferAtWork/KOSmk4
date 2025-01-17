/* HASH CRC-32:0x98cfa904 */
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
#if !defined(E2BIG) && defined(__E2BIG)
#define E2BIG           __E2BIG           /* Argument list too long */
#endif /* !E2BIG && __E2BIG */
#if !defined(EACCES) && defined(__EACCES)
#define EACCES          __EACCES          /* Permission denied */
#endif /* !EACCES && __EACCES */
#if !defined(EADDRINUSE) && defined(__EADDRINUSE)
#define EADDRINUSE      __EADDRINUSE      /* Address already in use */
#endif /* !EADDRINUSE && __EADDRINUSE */
#if !defined(EADDRNOTAVAIL) && defined(__EADDRNOTAVAIL)
#define EADDRNOTAVAIL   __EADDRNOTAVAIL   /* Cannot assign requested address */
#endif /* !EADDRNOTAVAIL && __EADDRNOTAVAIL */
#if !defined(EADV) && defined(__EADV)
#define EADV            __EADV            /* Advertise error */
#endif /* !EADV && __EADV */
#if !defined(EAFNOSUPPORT) && defined(__EAFNOSUPPORT)
#define EAFNOSUPPORT    __EAFNOSUPPORT    /* Address family not supported by protocol */
#endif /* !EAFNOSUPPORT && __EAFNOSUPPORT */
#if !defined(EAGAIN) && defined(__EAGAIN)
#define EAGAIN          __EAGAIN          /* Try again */
#endif /* !EAGAIN && __EAGAIN */
#if !defined(EALREADY) && defined(__EALREADY)
#define EALREADY        __EALREADY        /* Operation already in progress */
#endif /* !EALREADY && __EALREADY */
#if !defined(EAUTH) && defined(__EAUTH)
#define EAUTH           __EAUTH           /* ??? */
#endif /* !EAUTH && __EAUTH */
#if !defined(EBADE) && defined(__EBADE)
#define EBADE           __EBADE           /* Invalid exchange */
#endif /* !EBADE && __EBADE */
#if !defined(EBADF) && defined(__EBADF)
#define EBADF           __EBADF           /* Bad file number */
#endif /* !EBADF && __EBADF */
#if !defined(EBADFD) && defined(__EBADFD)
#define EBADFD          __EBADFD          /* File descriptor in bad state */
#endif /* !EBADFD && __EBADFD */
#if !defined(EBADMSG) && defined(__EBADMSG)
#define EBADMSG         __EBADMSG         /* Not a data message */
#endif /* !EBADMSG && __EBADMSG */
#if !defined(EBADR) && defined(__EBADR)
#define EBADR           __EBADR           /* Invalid request descriptor */
#endif /* !EBADR && __EBADR */
#if !defined(EBADRPC) && defined(__EBADRPC)
#define EBADRPC         __EBADRPC         /* ??? */
#endif /* !EBADRPC && __EBADRPC */
#if !defined(EBADRQC) && defined(__EBADRQC)
#define EBADRQC         __EBADRQC         /* Invalid request code */
#endif /* !EBADRQC && __EBADRQC */
#if !defined(EBADSLT) && defined(__EBADSLT)
#define EBADSLT         __EBADSLT         /* Invalid slot */
#endif /* !EBADSLT && __EBADSLT */
#if !defined(EBFONT) && defined(__EBFONT)
#define EBFONT          __EBFONT          /* Bad font file format */
#endif /* !EBFONT && __EBFONT */
#if !defined(EBUSY) && defined(__EBUSY)
#define EBUSY           __EBUSY           /* Device or resource busy */
#endif /* !EBUSY && __EBUSY */
#if !defined(ECANCELED) && defined(__ECANCELED)
#define ECANCELED       __ECANCELED       /* Operation canceled */
#endif /* !ECANCELED && __ECANCELED */
#if !defined(ECASECLASH) && defined(__ECASECLASH)
#define ECASECLASH      __ECASECLASH      /* Filename exists with different case */
#endif /* !ECASECLASH && __ECASECLASH */
#if !defined(ECHILD) && defined(__ECHILD)
#define ECHILD          __ECHILD          /* No child processes */
#endif /* !ECHILD && __ECHILD */
#if !defined(ECHRNG) && defined(__ECHRNG)
#define ECHRNG          __ECHRNG          /* Channel number out of range */
#endif /* !ECHRNG && __ECHRNG */
#if !defined(ECOMM) && defined(__ECOMM)
#define ECOMM           __ECOMM           /* Communication error on send */
#endif /* !ECOMM && __ECOMM */
#if !defined(ECONNABORTED) && defined(__ECONNABORTED)
#define ECONNABORTED    __ECONNABORTED    /* Software caused connection abort */
#endif /* !ECONNABORTED && __ECONNABORTED */
#if !defined(ECONNREFUSED) && defined(__ECONNREFUSED)
#define ECONNREFUSED    __ECONNREFUSED    /* Connection refused */
#endif /* !ECONNREFUSED && __ECONNREFUSED */
#if !defined(ECONNRESET) && defined(__ECONNRESET)
#define ECONNRESET      __ECONNRESET      /* Connection reset by peer */
#endif /* !ECONNRESET && __ECONNRESET */
#if !defined(EDEADLK) && defined(__EDEADLK)
#define EDEADLK         __EDEADLK         /* Resource deadlock would occur */
#endif /* !EDEADLK && __EDEADLK */
#if !defined(EDEADLOCK) && defined(__EDEADLOCK)
#define EDEADLOCK       __EDEADLOCK       /* Resource deadlock would occur */
#endif /* !EDEADLOCK && __EDEADLOCK */
#if !defined(EDESTADDRREQ) && defined(__EDESTADDRREQ)
#define EDESTADDRREQ    __EDESTADDRREQ    /* Destination address required */
#endif /* !EDESTADDRREQ && __EDESTADDRREQ */
#if !defined(EDOM) && defined(__EDOM)
#define EDOM            __EDOM            /* Math argument out of domain of func */
#endif /* !EDOM && __EDOM */
#if !defined(EDOTDOT) && defined(__EDOTDOT)
#define EDOTDOT         __EDOTDOT         /* RFS specific error */
#endif /* !EDOTDOT && __EDOTDOT */
#if !defined(EDQUOT) && defined(__EDQUOT)
#define EDQUOT          __EDQUOT          /* Quota exceeded */
#endif /* !EDQUOT && __EDQUOT */
#if !defined(EEXIST) && defined(__EEXIST)
#define EEXIST          __EEXIST          /* File exists */
#endif /* !EEXIST && __EEXIST */
#if !defined(EFAULT) && defined(__EFAULT)
#define EFAULT          __EFAULT          /* Bad address */
#endif /* !EFAULT && __EFAULT */
#if !defined(EFBIG) && defined(__EFBIG)
#define EFBIG           __EFBIG           /* File too large */
#endif /* !EFBIG && __EFBIG */
#if !defined(EFTYPE) && defined(__EFTYPE)
#define EFTYPE          __EFTYPE          /* Inappropriate file type or format */
#endif /* !EFTYPE && __EFTYPE */
#if !defined(EHOSTDOWN) && defined(__EHOSTDOWN)
#define EHOSTDOWN       __EHOSTDOWN       /* Host is down */
#endif /* !EHOSTDOWN && __EHOSTDOWN */
#if !defined(EHOSTUNREACH) && defined(__EHOSTUNREACH)
#define EHOSTUNREACH    __EHOSTUNREACH    /* No route to host */
#endif /* !EHOSTUNREACH && __EHOSTUNREACH */
#if !defined(EHWPOISON) && defined(__EHWPOISON)
#define EHWPOISON       __EHWPOISON       /* Memory page has hardware error */
#endif /* !EHWPOISON && __EHWPOISON */
#if !defined(EIDRM) && defined(__EIDRM)
#define EIDRM           __EIDRM           /* Identifier removed */
#endif /* !EIDRM && __EIDRM */
#if !defined(EILSEQ) && defined(__EILSEQ)
#define EILSEQ          __EILSEQ          /* Illegal byte sequence */
#endif /* !EILSEQ && __EILSEQ */
#if !defined(EINPROGRESS) && defined(__EINPROGRESS)
#define EINPROGRESS     __EINPROGRESS     /* Operation now in progress */
#endif /* !EINPROGRESS && __EINPROGRESS */
#if !defined(EINTR) && defined(__EINTR)
#define EINTR           __EINTR           /* Interrupted system call */
#endif /* !EINTR && __EINTR */
#if !defined(EINVAL) && defined(__EINVAL)
#define EINVAL          __EINVAL          /* Invalid argument */
#endif /* !EINVAL && __EINVAL */
#if !defined(EIO) && defined(__EIO)
#define EIO             __EIO             /* I/O error */
#endif /* !EIO && __EIO */
#if !defined(EISCONN) && defined(__EISCONN)
#define EISCONN         __EISCONN         /* Transport endpoint is already connected */
#endif /* !EISCONN && __EISCONN */
#if !defined(EISDIR) && defined(__EISDIR)
#define EISDIR          __EISDIR          /* Is a directory */
#endif /* !EISDIR && __EISDIR */
#if !defined(EISNAM) && defined(__EISNAM)
#define EISNAM          __EISNAM          /* Is a named type file */
#endif /* !EISNAM && __EISNAM */
#if !defined(EKEYEXPIRED) && defined(__EKEYEXPIRED)
#define EKEYEXPIRED     __EKEYEXPIRED     /* Key has expired */
#endif /* !EKEYEXPIRED && __EKEYEXPIRED */
#if !defined(EKEYREJECTED) && defined(__EKEYREJECTED)
#define EKEYREJECTED    __EKEYREJECTED    /* Key was rejected by service */
#endif /* !EKEYREJECTED && __EKEYREJECTED */
#if !defined(EKEYREVOKED) && defined(__EKEYREVOKED)
#define EKEYREVOKED     __EKEYREVOKED     /* Key has been revoked */
#endif /* !EKEYREVOKED && __EKEYREVOKED */
#if !defined(EL2HLT) && defined(__EL2HLT)
#define EL2HLT          __EL2HLT          /* Level 2 halted */
#endif /* !EL2HLT && __EL2HLT */
#if !defined(EL2NSYNC) && defined(__EL2NSYNC)
#define EL2NSYNC        __EL2NSYNC        /* Level 2 not synchronized */
#endif /* !EL2NSYNC && __EL2NSYNC */
#if !defined(EL3HLT) && defined(__EL3HLT)
#define EL3HLT          __EL3HLT          /* Level 3 halted */
#endif /* !EL3HLT && __EL3HLT */
#if !defined(EL3RST) && defined(__EL3RST)
#define EL3RST          __EL3RST          /* Level 3 reset */
#endif /* !EL3RST && __EL3RST */
#if !defined(ELBIN) && defined(__ELBIN)
#define ELBIN           __ELBIN           /* Inode is remote (not really error) */
#endif /* !ELBIN && __ELBIN */
#if !defined(ELIBACC) && defined(__ELIBACC)
#define ELIBACC         __ELIBACC         /* Can not access a needed shared library */
#endif /* !ELIBACC && __ELIBACC */
#if !defined(ELIBBAD) && defined(__ELIBBAD)
#define ELIBBAD         __ELIBBAD         /* Accessing a corrupted shared library */
#endif /* !ELIBBAD && __ELIBBAD */
#if !defined(ELIBEXEC) && defined(__ELIBEXEC)
#define ELIBEXEC        __ELIBEXEC        /* Cannot exec a shared library directly */
#endif /* !ELIBEXEC && __ELIBEXEC */
#if !defined(ELIBMAX) && defined(__ELIBMAX)
#define ELIBMAX         __ELIBMAX         /* Attempting to link in too many shared libraries */
#endif /* !ELIBMAX && __ELIBMAX */
#if !defined(ELIBSCN) && defined(__ELIBSCN)
#define ELIBSCN         __ELIBSCN         /* .lib section in a.out corrupted */
#endif /* !ELIBSCN && __ELIBSCN */
#if !defined(ELNRNG) && defined(__ELNRNG)
#define ELNRNG          __ELNRNG          /* Link number out of range */
#endif /* !ELNRNG && __ELNRNG */
#if !defined(ELOCKUNMAPPED) && defined(__ELOCKUNMAPPED)
#define ELOCKUNMAPPED   __ELOCKUNMAPPED   /* ??? */
#endif /* !ELOCKUNMAPPED && __ELOCKUNMAPPED */
#if !defined(ELOOP) && defined(__ELOOP)
#define ELOOP           __ELOOP           /* Too many symbolic links encountered */
#endif /* !ELOOP && __ELOOP */
#if !defined(EMEDIUMTYPE) && defined(__EMEDIUMTYPE)
#define EMEDIUMTYPE     __EMEDIUMTYPE     /* Wrong medium type */
#endif /* !EMEDIUMTYPE && __EMEDIUMTYPE */
#if !defined(EMFILE) && defined(__EMFILE)
#define EMFILE          __EMFILE          /* Too many open files */
#endif /* !EMFILE && __EMFILE */
#if !defined(EMLINK) && defined(__EMLINK)
#define EMLINK          __EMLINK          /* Too many links */
#endif /* !EMLINK && __EMLINK */
#if !defined(EMSGSIZE) && defined(__EMSGSIZE)
#define EMSGSIZE        __EMSGSIZE        /* Message too long */
#endif /* !EMSGSIZE && __EMSGSIZE */
#if !defined(EMULTIHOP) && defined(__EMULTIHOP)
#define EMULTIHOP       __EMULTIHOP       /* Multihop attempted */
#endif /* !EMULTIHOP && __EMULTIHOP */
#if !defined(ENAMETOOLONG) && defined(__ENAMETOOLONG)
#define ENAMETOOLONG    __ENAMETOOLONG    /* File name too long */
#endif /* !ENAMETOOLONG && __ENAMETOOLONG */
#if !defined(ENAVAIL) && defined(__ENAVAIL)
#define ENAVAIL         __ENAVAIL         /* No XENIX semaphores available */
#endif /* !ENAVAIL && __ENAVAIL */
#if !defined(ENEEDAUTH) && defined(__ENEEDAUTH)
#define ENEEDAUTH       __ENEEDAUTH       /* ??? */
#endif /* !ENEEDAUTH && __ENEEDAUTH */
#if !defined(ENETDOWN) && defined(__ENETDOWN)
#define ENETDOWN        __ENETDOWN        /* Network is down */
#endif /* !ENETDOWN && __ENETDOWN */
#if !defined(ENETRESET) && defined(__ENETRESET)
#define ENETRESET       __ENETRESET       /* Network dropped connection because of reset */
#endif /* !ENETRESET && __ENETRESET */
#if !defined(ENETUNREACH) && defined(__ENETUNREACH)
#define ENETUNREACH     __ENETUNREACH     /* Network is unreachable */
#endif /* !ENETUNREACH && __ENETUNREACH */
#if !defined(ENFILE) && defined(__ENFILE)
#define ENFILE          __ENFILE          /* File table overflow */
#endif /* !ENFILE && __ENFILE */
#if !defined(ENMFILE) && defined(__ENMFILE)
#define ENMFILE         __ENMFILE         /* No more files */
#endif /* !ENMFILE && __ENMFILE */
#if !defined(ENOANO) && defined(__ENOANO)
#define ENOANO          __ENOANO          /* No anode */
#endif /* !ENOANO && __ENOANO */
#if !defined(ENOATTR) && defined(__ENOATTR)
#define ENOATTR         __ENOATTR         /* ??? */
#endif /* !ENOATTR && __ENOATTR */
#if !defined(ENOBUFS) && defined(__ENOBUFS)
#define ENOBUFS         __ENOBUFS         /* No buffer space available */
#endif /* !ENOBUFS && __ENOBUFS */
#if !defined(ENOCSI) && defined(__ENOCSI)
#define ENOCSI          __ENOCSI          /* No CSI structure available */
#endif /* !ENOCSI && __ENOCSI */
#if !defined(ENODATA) && defined(__ENODATA)
#define ENODATA         __ENODATA         /* No data available */
#endif /* !ENODATA && __ENODATA */
#if !defined(ENODEV) && defined(__ENODEV)
#define ENODEV          __ENODEV          /* No such device */
#endif /* !ENODEV && __ENODEV */
#if !defined(ENOENT) && defined(__ENOENT)
#define ENOENT          __ENOENT          /* No such file or directory */
#endif /* !ENOENT && __ENOENT */
#if !defined(ENOEXEC) && defined(__ENOEXEC)
#define ENOEXEC         __ENOEXEC         /* Exec format error */
#endif /* !ENOEXEC && __ENOEXEC */
#if !defined(ENOKEY) && defined(__ENOKEY)
#define ENOKEY          __ENOKEY          /* Required key not available */
#endif /* !ENOKEY && __ENOKEY */
#if !defined(ENOLCK) && defined(__ENOLCK)
#define ENOLCK          __ENOLCK          /* No record locks available */
#endif /* !ENOLCK && __ENOLCK */
#if !defined(ENOLINK) && defined(__ENOLINK)
#define ENOLINK         __ENOLINK         /* Link has been severed */
#endif /* !ENOLINK && __ENOLINK */
#if !defined(ENOMEDIUM) && defined(__ENOMEDIUM)
#define ENOMEDIUM       __ENOMEDIUM       /* No medium found */
#endif /* !ENOMEDIUM && __ENOMEDIUM */
#if !defined(ENOMEM) && defined(__ENOMEM)
#define ENOMEM          __ENOMEM          /* Out of memory */
#endif /* !ENOMEM && __ENOMEM */
#if !defined(ENOMSG) && defined(__ENOMSG)
#define ENOMSG          __ENOMSG          /* No message of desired type */
#endif /* !ENOMSG && __ENOMSG */
#if !defined(ENONET) && defined(__ENONET)
#define ENONET          __ENONET          /* Machine is not on the network */
#endif /* !ENONET && __ENONET */
#if !defined(ENOPKG) && defined(__ENOPKG)
#define ENOPKG          __ENOPKG          /* Package not installed */
#endif /* !ENOPKG && __ENOPKG */
#if !defined(ENOPROTOOPT) && defined(__ENOPROTOOPT)
#define ENOPROTOOPT     __ENOPROTOOPT     /* Protocol not available */
#endif /* !ENOPROTOOPT && __ENOPROTOOPT */
#if !defined(ENOSHARE) && defined(__ENOSHARE)
#define ENOSHARE        __ENOSHARE        /* No such host or network path */
#endif /* !ENOSHARE && __ENOSHARE */
#if !defined(ENOSPC) && defined(__ENOSPC)
#define ENOSPC          __ENOSPC          /* No space left on device */
#endif /* !ENOSPC && __ENOSPC */
#if !defined(ENOSR) && defined(__ENOSR)
#define ENOSR           __ENOSR           /* Out of streams resources */
#endif /* !ENOSR && __ENOSR */
#if !defined(ENOSTR) && defined(__ENOSTR)
#define ENOSTR          __ENOSTR          /* Device not a stream */
#endif /* !ENOSTR && __ENOSTR */
#if !defined(ENOSYS) && defined(__ENOSYS)
#define ENOSYS          __ENOSYS          /* Function not implemented */
#endif /* !ENOSYS && __ENOSYS */
#if !defined(ENOTACTIVE) && defined(__ENOTACTIVE)
#define ENOTACTIVE      __ENOTACTIVE      /* ??? */
#endif /* !ENOTACTIVE && __ENOTACTIVE */
#if !defined(ENOTBLK) && defined(__ENOTBLK)
#define ENOTBLK         __ENOTBLK         /* Block device required */
#endif /* !ENOTBLK && __ENOTBLK */
#if !defined(ENOTCONN) && defined(__ENOTCONN)
#define ENOTCONN        __ENOTCONN        /* Transport endpoint is not connected */
#endif /* !ENOTCONN && __ENOTCONN */
#if !defined(ENOTDIR) && defined(__ENOTDIR)
#define ENOTDIR         __ENOTDIR         /* Not a directory */
#endif /* !ENOTDIR && __ENOTDIR */
#if !defined(ENOTEMPTY) && defined(__ENOTEMPTY)
#define ENOTEMPTY       __ENOTEMPTY       /* Directory not empty */
#endif /* !ENOTEMPTY && __ENOTEMPTY */
#if !defined(ENOTNAM) && defined(__ENOTNAM)
#define ENOTNAM         __ENOTNAM         /* Not a XENIX named type file */
#endif /* !ENOTNAM && __ENOTNAM */
#if !defined(ENOTRECOVERABLE) && defined(__ENOTRECOVERABLE)
#define ENOTRECOVERABLE __ENOTRECOVERABLE /* State not recoverable */
#endif /* !ENOTRECOVERABLE && __ENOTRECOVERABLE */
#if !defined(ENOTSOCK) && defined(__ENOTSOCK)
#define ENOTSOCK        __ENOTSOCK        /* Socket operation on non-socket */
#endif /* !ENOTSOCK && __ENOTSOCK */
#if !defined(ENOTSUP) && defined(__ENOTSUP)
#define ENOTSUP         __ENOTSUP         /* Not supported */
#endif /* !ENOTSUP && __ENOTSUP */
#if !defined(ENOTTY) && defined(__ENOTTY)
#define ENOTTY          __ENOTTY          /* Not a typewriter */
#endif /* !ENOTTY && __ENOTTY */
#if !defined(ENOTUNIQ) && defined(__ENOTUNIQ)
#define ENOTUNIQ        __ENOTUNIQ        /* Name not unique on network */
#endif /* !ENOTUNIQ && __ENOTUNIQ */
#if !defined(ENXIO) && defined(__ENXIO)
#define ENXIO           __ENXIO           /* No such device or address */
#endif /* !ENXIO && __ENXIO */
#if !defined(EOPNOTSUPP) && defined(__EOPNOTSUPP)
#define EOPNOTSUPP      __EOPNOTSUPP      /* Operation not supported on transport endpoint */
#endif /* !EOPNOTSUPP && __EOPNOTSUPP */
#if !defined(EOTHER) && defined(__EOTHER)
#define EOTHER          __EOTHER          /* Other */
#endif /* !EOTHER && __EOTHER */
#if !defined(EOVERFLOW) && defined(__EOVERFLOW)
#define EOVERFLOW       __EOVERFLOW       /* Value too large for defined data type */
#endif /* !EOVERFLOW && __EOVERFLOW */
#if !defined(EOWNERDEAD) && defined(__EOWNERDEAD)
#define EOWNERDEAD      __EOWNERDEAD      /* Owner died */
#endif /* !EOWNERDEAD && __EOWNERDEAD */
#if !defined(EPERM) && defined(__EPERM)
#define EPERM           __EPERM           /* Operation not permitted */
#endif /* !EPERM && __EPERM */
#if !defined(EPFNOSUPPORT) && defined(__EPFNOSUPPORT)
#define EPFNOSUPPORT    __EPFNOSUPPORT    /* Protocol family not supported */
#endif /* !EPFNOSUPPORT && __EPFNOSUPPORT */
#if !defined(EPIPE) && defined(__EPIPE)
#define EPIPE           __EPIPE           /* Broken pipe */
#endif /* !EPIPE && __EPIPE */
#if !defined(EPROCLIM) && defined(__EPROCLIM)
#define EPROCLIM        __EPROCLIM        /* Process limit reached */
#endif /* !EPROCLIM && __EPROCLIM */
#if !defined(EPROCUNAVAIL) && defined(__EPROCUNAVAIL)
#define EPROCUNAVAIL    __EPROCUNAVAIL    /* ??? */
#endif /* !EPROCUNAVAIL && __EPROCUNAVAIL */
#if !defined(EPROGMISMATCH) && defined(__EPROGMISMATCH)
#define EPROGMISMATCH   __EPROGMISMATCH   /* ??? */
#endif /* !EPROGMISMATCH && __EPROGMISMATCH */
#if !defined(EPROGUNAVAIL) && defined(__EPROGUNAVAIL)
#define EPROGUNAVAIL    __EPROGUNAVAIL    /* ??? */
#endif /* !EPROGUNAVAIL && __EPROGUNAVAIL */
#if !defined(EPROTO) && defined(__EPROTO)
#define EPROTO          __EPROTO          /* Protocol error */
#endif /* !EPROTO && __EPROTO */
#if !defined(EPROTONOSUPPORT) && defined(__EPROTONOSUPPORT)
#define EPROTONOSUPPORT __EPROTONOSUPPORT /* Protocol not supported */
#endif /* !EPROTONOSUPPORT && __EPROTONOSUPPORT */
#if !defined(EPROTOTYPE) && defined(__EPROTOTYPE)
#define EPROTOTYPE      __EPROTOTYPE      /* Protocol wrong type for socket */
#endif /* !EPROTOTYPE && __EPROTOTYPE */
#if !defined(ERANGE) && defined(__ERANGE)
#define ERANGE          __ERANGE          /* Math result not representable */
#endif /* !ERANGE && __ERANGE */
#if !defined(EREMCHG) && defined(__EREMCHG)
#define EREMCHG         __EREMCHG         /* Remote address changed */
#endif /* !EREMCHG && __EREMCHG */
#if !defined(EREMOTE) && defined(__EREMOTE)
#define EREMOTE         __EREMOTE         /* Object is remote */
#endif /* !EREMOTE && __EREMOTE */
#if !defined(EREMOTEIO) && defined(__EREMOTEIO)
#define EREMOTEIO       __EREMOTEIO       /* Remote I/O error */
#endif /* !EREMOTEIO && __EREMOTEIO */
#if !defined(ERESTART) && defined(__ERESTART)
#define ERESTART        __ERESTART        /* Interrupted system call should be restarted */
#endif /* !ERESTART && __ERESTART */
#if !defined(ERFKILL) && defined(__ERFKILL)
#define ERFKILL         __ERFKILL         /* Operation not possible due to RF-kill */
#endif /* !ERFKILL && __ERFKILL */
#if !defined(EROFS) && defined(__EROFS)
#define EROFS           __EROFS           /* Read-only file system */
#endif /* !EROFS && __EROFS */
#if !defined(ERPCMISMATCH) && defined(__ERPCMISMATCH)
#define ERPCMISMATCH    __ERPCMISMATCH    /* ??? */
#endif /* !ERPCMISMATCH && __ERPCMISMATCH */
#if !defined(ESHUTDOWN) && defined(__ESHUTDOWN)
#define ESHUTDOWN       __ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#endif /* !ESHUTDOWN && __ESHUTDOWN */
#if !defined(ESOCKTNOSUPPORT) && defined(__ESOCKTNOSUPPORT)
#define ESOCKTNOSUPPORT __ESOCKTNOSUPPORT /* Socket type not supported */
#endif /* !ESOCKTNOSUPPORT && __ESOCKTNOSUPPORT */
#if !defined(ESPIPE) && defined(__ESPIPE)
#define ESPIPE          __ESPIPE          /* Illegal seek */
#endif /* !ESPIPE && __ESPIPE */
#if !defined(ESRCH) && defined(__ESRCH)
#define ESRCH           __ESRCH           /* No such process */
#endif /* !ESRCH && __ESRCH */
#if !defined(ESRMNT) && defined(__ESRMNT)
#define ESRMNT          __ESRMNT          /* Srmount error */
#endif /* !ESRMNT && __ESRMNT */
#if !defined(ESTALE) && defined(__ESTALE)
#define ESTALE          __ESTALE          /* Stale file handle */
#endif /* !ESTALE && __ESTALE */
#if !defined(ESTRPIPE) && defined(__ESTRPIPE)
#define ESTRPIPE        __ESTRPIPE        /* Streams pipe error */
#endif /* !ESTRPIPE && __ESTRPIPE */
#if !defined(ETIME) && defined(__ETIME)
#define ETIME           __ETIME           /* Timer expired */
#endif /* !ETIME && __ETIME */
#if !defined(ETIMEDOUT) && defined(__ETIMEDOUT)
#define ETIMEDOUT       __ETIMEDOUT       /* Connection timed out */
#endif /* !ETIMEDOUT && __ETIMEDOUT */
#if !defined(ETOOMANYREFS) && defined(__ETOOMANYREFS)
#define ETOOMANYREFS    __ETOOMANYREFS    /* Too many references: cannot splice */
#endif /* !ETOOMANYREFS && __ETOOMANYREFS */
#if !defined(ETXTBSY) && defined(__ETXTBSY)
#define ETXTBSY         __ETXTBSY         /* Text file busy */
#endif /* !ETXTBSY && __ETXTBSY */
#if !defined(EUCLEAN) && defined(__EUCLEAN)
#define EUCLEAN         __EUCLEAN         /* Structure needs cleaning */
#endif /* !EUCLEAN && __EUCLEAN */
#if !defined(EUNATCH) && defined(__EUNATCH)
#define EUNATCH         __EUNATCH         /* Protocol driver not attached */
#endif /* !EUNATCH && __EUNATCH */
#if !defined(EUSERS) && defined(__EUSERS)
#define EUSERS          __EUSERS          /* Too many users */
#endif /* !EUSERS && __EUSERS */
#if !defined(EWOULDBLOCK) && defined(__EWOULDBLOCK)
#define EWOULDBLOCK     __EWOULDBLOCK     /* Operation would block */
#endif /* !EWOULDBLOCK && __EWOULDBLOCK */
#if !defined(EXDEV) && defined(__EXDEV)
#define EXDEV           __EXDEV           /* Cross-device link */
#endif /* !EXDEV && __EXDEV */
#if !defined(EXFULL) && defined(__EXFULL)
#define EXFULL          __EXFULL          /* Exchange full */
#endif /* !EXFULL && __EXFULL */
#if !defined(STRUNCATE) && defined(__STRUNCATE)
#define STRUNCATE       __STRUNCATE       /* Truncated */
#endif /* !STRUNCATE && __STRUNCATE */






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
#if !defined(ELAST) && defined(__ELIMIT)
#define ELAST __ELIMIT /* Max possible errno */
#endif /* !ELAST && __ELIMIT */
#endif /* __USE_NETBSD */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#if !defined(EOK) && defined(__EOK)
#define EOK    __EOK    /* Operation completed successfully */
#endif /* !EOK && __EOK */
#if !defined(EMAX) && defined(__EMAX)
#define EMAX   __EMAX   /* Max errno */
#endif /* !EMAX && __EMAX */
#if !defined(ECOUNT) && defined(__ECOUNT)
#define ECOUNT __ECOUNT /* Max errno + 1 */
#endif /* !ECOUNT && __ECOUNT */
#if !defined(ELIMIT) && defined(__ELIMIT)
#define ELIMIT __ELIMIT /* Max possible errno */
#endif /* !ELIMIT && __ELIMIT */
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
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW,__errno_location,(void),__errno,())
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
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW,__p__pgmptr,(void),())
#elif defined(__CRT_HAVE___p_program_invocation_name)
/* Alias for argv[0], as passed to main() */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW,__p__pgmptr,(void),__p_program_invocation_name,())
#else /* ... */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name_p
#include <libc/local/stdlib/__p__pgmptr.h>
/* Alias for argv[0], as passed to main() */
__NAMESPACE_LOCAL_USING_OR_IMPL(__p__pgmptr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **__NOTHROW(__LIBCCALL __p__pgmptr)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__p__pgmptr))(); })
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
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW,__p_program_invocation_short_name,(void),())
#else /* __CRT_HAVE___p_program_invocation_short_name */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name_p
#include <libc/local/errno/__p_program_invocation_short_name.h>
/* >> __p_program_invocation_short_name(3)
 * Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
__NAMESPACE_LOCAL_USING_OR_IMPL(__p_program_invocation_short_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **__NOTHROW(__LIBCCALL __p_program_invocation_short_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__p_program_invocation_short_name))(); })
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
