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
/* (#) Portability: Linux (/usr/include/[...]/asm/errno.h) */
#ifndef _ASM_ERRNO_H
#define _ASM_ERRNO_H 1

#include "errno-base.h"

#if !defined(EDEADLK) && defined(__EDEADLK)
#define EDEADLK         __EDEADLK         /* Resource deadlock would occur */
#endif /* !EDEADLK && __EDEADLK */
#if !defined(ENAMETOOLONG) && defined(__ENAMETOOLONG)
#define ENAMETOOLONG    __ENAMETOOLONG    /* File name too long */
#endif /* !ENAMETOOLONG && __ENAMETOOLONG */
#if !defined(ENOLCK) && defined(__ENOLCK)
#define ENOLCK          __ENOLCK          /* No record locks available */
#endif /* !ENOLCK && __ENOLCK */
#if !defined(ENOSYS) && defined(__ENOSYS)
#define ENOSYS          __ENOSYS          /* Function not implemented */
#endif /* !ENOSYS && __ENOSYS */
#if !defined(ENOTEMPTY) && defined(__ENOTEMPTY)
#define ENOTEMPTY       __ENOTEMPTY       /* Directory not empty */
#endif /* !ENOTEMPTY && __ENOTEMPTY */
#if !defined(ELOOP) && defined(__ELOOP)
#define ELOOP           __ELOOP           /* Too many symbolic links encountered */
#endif /* !ELOOP && __ELOOP */
#if !defined(ENOMSG) && defined(__ENOMSG)
#define ENOMSG          __ENOMSG          /* No message of desired type */
#endif /* !ENOMSG && __ENOMSG */
#if !defined(EIDRM) && defined(__EIDRM)
#define EIDRM           __EIDRM           /* Identifier removed */
#endif /* !EIDRM && __EIDRM */
#if !defined(ECHRNG) && defined(__ECHRNG)
#define ECHRNG          __ECHRNG          /* Channel number out of range */
#endif /* !ECHRNG && __ECHRNG */
#if !defined(EL2NSYNC) && defined(__EL2NSYNC)
#define EL2NSYNC        __EL2NSYNC        /* Level 2 not synchronized */
#endif /* !EL2NSYNC && __EL2NSYNC */
#if !defined(EL3HLT) && defined(__EL3HLT)
#define EL3HLT          __EL3HLT          /* Level 3 halted */
#endif /* !EL3HLT && __EL3HLT */
#if !defined(EL3RST) && defined(__EL3RST)
#define EL3RST          __EL3RST          /* Level 3 reset */
#endif /* !EL3RST && __EL3RST */
#if !defined(ELNRNG) && defined(__ELNRNG)
#define ELNRNG          __ELNRNG          /* Link number out of range */
#endif /* !ELNRNG && __ELNRNG */
#if !defined(EUNATCH) && defined(__EUNATCH)
#define EUNATCH         __EUNATCH         /* Protocol driver not attached */
#endif /* !EUNATCH && __EUNATCH */
#if !defined(ENOCSI) && defined(__ENOCSI)
#define ENOCSI          __ENOCSI          /* No CSI structure available */
#endif /* !ENOCSI && __ENOCSI */
#if !defined(EL2HLT) && defined(__EL2HLT)
#define EL2HLT          __EL2HLT          /* Level 2 halted */
#endif /* !EL2HLT && __EL2HLT */
#if !defined(EBADE) && defined(__EBADE)
#define EBADE           __EBADE           /* Invalid exchange */
#endif /* !EBADE && __EBADE */
#if !defined(EBADR) && defined(__EBADR)
#define EBADR           __EBADR           /* Invalid request descriptor */
#endif /* !EBADR && __EBADR */
#if !defined(EXFULL) && defined(__EXFULL)
#define EXFULL          __EXFULL          /* Exchange full */
#endif /* !EXFULL && __EXFULL */
#if !defined(ENOANO) && defined(__ENOANO)
#define ENOANO          __ENOANO          /* No anode */
#endif /* !ENOANO && __ENOANO */
#if !defined(EBADRQC) && defined(__EBADRQC)
#define EBADRQC         __EBADRQC         /* Invalid request code */
#endif /* !EBADRQC && __EBADRQC */
#if !defined(EBADSLT) && defined(__EBADSLT)
#define EBADSLT         __EBADSLT         /* Invalid slot */
#endif /* !EBADSLT && __EBADSLT */
#if !defined(EBFONT) && defined(__EBFONT)
#define EBFONT          __EBFONT          /* Bad font file format */
#endif /* !EBFONT && __EBFONT */
#if !defined(ENOSTR) && defined(__ENOSTR)
#define ENOSTR          __ENOSTR          /* Device not a stream */
#endif /* !ENOSTR && __ENOSTR */
#if !defined(ENODATA) && defined(__ENODATA)
#define ENODATA         __ENODATA         /* No data available */
#endif /* !ENODATA && __ENODATA */
#if !defined(ETIME) && defined(__ETIME)
#define ETIME           __ETIME           /* Timer expired */
#endif /* !ETIME && __ETIME */
#if !defined(ENOSR) && defined(__ENOSR)
#define ENOSR           __ENOSR           /* Out of streams resources */
#endif /* !ENOSR && __ENOSR */
#if !defined(ENONET) && defined(__ENONET)
#define ENONET          __ENONET          /* Machine is not on the network */
#endif /* !ENONET && __ENONET */
#if !defined(ENOPKG) && defined(__ENOPKG)
#define ENOPKG          __ENOPKG          /* Package not installed */
#endif /* !ENOPKG && __ENOPKG */
#if !defined(EREMOTE) && defined(__EREMOTE)
#define EREMOTE         __EREMOTE         /* Object is remote */
#endif /* !EREMOTE && __EREMOTE */
#if !defined(ENOLINK) && defined(__ENOLINK)
#define ENOLINK         __ENOLINK         /* Link has been severed */
#endif /* !ENOLINK && __ENOLINK */
#if !defined(EADV) && defined(__EADV)
#define EADV            __EADV            /* Advertise error */
#endif /* !EADV && __EADV */
#if !defined(ESRMNT) && defined(__ESRMNT)
#define ESRMNT          __ESRMNT          /* Srmount error */
#endif /* !ESRMNT && __ESRMNT */
#if !defined(ECOMM) && defined(__ECOMM)
#define ECOMM           __ECOMM           /* Communication error on send */
#endif /* !ECOMM && __ECOMM */
#if !defined(EPROTO) && defined(__EPROTO)
#define EPROTO          __EPROTO          /* Protocol error */
#endif /* !EPROTO && __EPROTO */
#if !defined(EMULTIHOP) && defined(__EMULTIHOP)
#define EMULTIHOP       __EMULTIHOP       /* Multihop attempted */
#endif /* !EMULTIHOP && __EMULTIHOP */
#if !defined(EDOTDOT) && defined(__EDOTDOT)
#define EDOTDOT         __EDOTDOT         /* RFS specific error */
#endif /* !EDOTDOT && __EDOTDOT */
#if !defined(EBADMSG) && defined(__EBADMSG)
#define EBADMSG         __EBADMSG         /* Not a data message */
#endif /* !EBADMSG && __EBADMSG */
#if !defined(EOVERFLOW) && defined(__EOVERFLOW)
#define EOVERFLOW       __EOVERFLOW       /* Value too large for defined data type */
#endif /* !EOVERFLOW && __EOVERFLOW */
#if !defined(ENOTUNIQ) && defined(__ENOTUNIQ)
#define ENOTUNIQ        __ENOTUNIQ        /* Name not unique on network */
#endif /* !ENOTUNIQ && __ENOTUNIQ */
#if !defined(EBADFD) && defined(__EBADFD)
#define EBADFD          __EBADFD          /* File descriptor in bad state */
#endif /* !EBADFD && __EBADFD */
#if !defined(EREMCHG) && defined(__EREMCHG)
#define EREMCHG         __EREMCHG         /* Remote address changed */
#endif /* !EREMCHG && __EREMCHG */
#if !defined(ELIBACC) && defined(__ELIBACC)
#define ELIBACC         __ELIBACC         /* Can not access a needed shared library */
#endif /* !ELIBACC && __ELIBACC */
#if !defined(ELIBBAD) && defined(__ELIBBAD)
#define ELIBBAD         __ELIBBAD         /* Accessing a corrupted shared library */
#endif /* !ELIBBAD && __ELIBBAD */
#if !defined(ELIBSCN) && defined(__ELIBSCN)
#define ELIBSCN         __ELIBSCN         /* .lib section in a.out corrupted */
#endif /* !ELIBSCN && __ELIBSCN */
#if !defined(ELIBMAX) && defined(__ELIBMAX)
#define ELIBMAX         __ELIBMAX         /* Attempting to link in too many shared libraries */
#endif /* !ELIBMAX && __ELIBMAX */
#if !defined(ELIBEXEC) && defined(__ELIBEXEC)
#define ELIBEXEC        __ELIBEXEC        /* Cannot exec a shared library directly */
#endif /* !ELIBEXEC && __ELIBEXEC */
#if !defined(EILSEQ) && defined(__EILSEQ)
#define EILSEQ          __EILSEQ          /* Illegal byte sequence */
#endif /* !EILSEQ && __EILSEQ */
#if !defined(ERESTART) && defined(__ERESTART)
#define ERESTART        __ERESTART        /* Interrupted system call should be restarted */
#endif /* !ERESTART && __ERESTART */
#if !defined(ESTRPIPE) && defined(__ESTRPIPE)
#define ESTRPIPE        __ESTRPIPE        /* Streams pipe error */
#endif /* !ESTRPIPE && __ESTRPIPE */
#if !defined(EUSERS) && defined(__EUSERS)
#define EUSERS          __EUSERS          /* Too many users */
#endif /* !EUSERS && __EUSERS */
#if !defined(ENOTSOCK) && defined(__ENOTSOCK)
#define ENOTSOCK        __ENOTSOCK        /* Socket operation on non-socket */
#endif /* !ENOTSOCK && __ENOTSOCK */
#if !defined(EDESTADDRREQ) && defined(__EDESTADDRREQ)
#define EDESTADDRREQ    __EDESTADDRREQ    /* Destination address required */
#endif /* !EDESTADDRREQ && __EDESTADDRREQ */
#if !defined(EMSGSIZE) && defined(__EMSGSIZE)
#define EMSGSIZE        __EMSGSIZE        /* Message too long */
#endif /* !EMSGSIZE && __EMSGSIZE */
#if !defined(EPROTOTYPE) && defined(__EPROTOTYPE)
#define EPROTOTYPE      __EPROTOTYPE      /* Protocol wrong type for socket */
#endif /* !EPROTOTYPE && __EPROTOTYPE */
#if !defined(ENOPROTOOPT) && defined(__ENOPROTOOPT)
#define ENOPROTOOPT     __ENOPROTOOPT     /* Protocol not available */
#endif /* !ENOPROTOOPT && __ENOPROTOOPT */
#if !defined(EPROTONOSUPPORT) && defined(__EPROTONOSUPPORT)
#define EPROTONOSUPPORT __EPROTONOSUPPORT /* Protocol not supported */
#endif /* !EPROTONOSUPPORT && __EPROTONOSUPPORT */
#if !defined(ESOCKTNOSUPPORT) && defined(__ESOCKTNOSUPPORT)
#define ESOCKTNOSUPPORT __ESOCKTNOSUPPORT /* Socket type not supported */
#endif /* !ESOCKTNOSUPPORT && __ESOCKTNOSUPPORT */
#if !defined(EOPNOTSUPP) && defined(__EOPNOTSUPP)
#define EOPNOTSUPP      __EOPNOTSUPP      /* Operation not supported on transport endpoint */
#endif /* !EOPNOTSUPP && __EOPNOTSUPP */
#if !defined(EPFNOSUPPORT) && defined(__EPFNOSUPPORT)
#define EPFNOSUPPORT    __EPFNOSUPPORT    /* Protocol family not supported */
#endif /* !EPFNOSUPPORT && __EPFNOSUPPORT */
#if !defined(EAFNOSUPPORT) && defined(__EAFNOSUPPORT)
#define EAFNOSUPPORT    __EAFNOSUPPORT    /* Address family not supported by protocol */
#endif /* !EAFNOSUPPORT && __EAFNOSUPPORT */
#if !defined(EADDRINUSE) && defined(__EADDRINUSE)
#define EADDRINUSE      __EADDRINUSE      /* Address already in use */
#endif /* !EADDRINUSE && __EADDRINUSE */
#if !defined(EADDRNOTAVAIL) && defined(__EADDRNOTAVAIL)
#define EADDRNOTAVAIL   __EADDRNOTAVAIL   /* Cannot assign requested address */
#endif /* !EADDRNOTAVAIL && __EADDRNOTAVAIL */
#if !defined(ENETDOWN) && defined(__ENETDOWN)
#define ENETDOWN        __ENETDOWN        /* Network is down */
#endif /* !ENETDOWN && __ENETDOWN */
#if !defined(ENETUNREACH) && defined(__ENETUNREACH)
#define ENETUNREACH     __ENETUNREACH     /* Network is unreachable */
#endif /* !ENETUNREACH && __ENETUNREACH */
#if !defined(ENETRESET) && defined(__ENETRESET)
#define ENETRESET       __ENETRESET       /* Network dropped connection because of reset */
#endif /* !ENETRESET && __ENETRESET */
#if !defined(ECONNABORTED) && defined(__ECONNABORTED)
#define ECONNABORTED    __ECONNABORTED    /* Software caused connection abort */
#endif /* !ECONNABORTED && __ECONNABORTED */
#if !defined(ECONNRESET) && defined(__ECONNRESET)
#define ECONNRESET      __ECONNRESET      /* Connection reset by peer */
#endif /* !ECONNRESET && __ECONNRESET */
#if !defined(ENOBUFS) && defined(__ENOBUFS)
#define ENOBUFS         __ENOBUFS         /* No buffer space available */
#endif /* !ENOBUFS && __ENOBUFS */
#if !defined(EISCONN) && defined(__EISCONN)
#define EISCONN         __EISCONN         /* Transport endpoint is already connected */
#endif /* !EISCONN && __EISCONN */
#if !defined(ENOTCONN) && defined(__ENOTCONN)
#define ENOTCONN        __ENOTCONN        /* Transport endpoint is not connected */
#endif /* !ENOTCONN && __ENOTCONN */
#if !defined(ESHUTDOWN) && defined(__ESHUTDOWN)
#define ESHUTDOWN       __ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#endif /* !ESHUTDOWN && __ESHUTDOWN */
#if !defined(ETOOMANYREFS) && defined(__ETOOMANYREFS)
#define ETOOMANYREFS    __ETOOMANYREFS    /* Too many references: cannot splice */
#endif /* !ETOOMANYREFS && __ETOOMANYREFS */
#if !defined(ETIMEDOUT) && defined(__ETIMEDOUT)
#define ETIMEDOUT       __ETIMEDOUT       /* Connection timed out */
#endif /* !ETIMEDOUT && __ETIMEDOUT */
#if !defined(ECONNREFUSED) && defined(__ECONNREFUSED)
#define ECONNREFUSED    __ECONNREFUSED    /* Connection refused */
#endif /* !ECONNREFUSED && __ECONNREFUSED */
#if !defined(EHOSTDOWN) && defined(__EHOSTDOWN)
#define EHOSTDOWN       __EHOSTDOWN       /* Host is down */
#endif /* !EHOSTDOWN && __EHOSTDOWN */
#if !defined(EHOSTUNREACH) && defined(__EHOSTUNREACH)
#define EHOSTUNREACH    __EHOSTUNREACH    /* No route to host */
#endif /* !EHOSTUNREACH && __EHOSTUNREACH */
#if !defined(EALREADY) && defined(__EALREADY)
#define EALREADY        __EALREADY        /* Operation already in progress */
#endif /* !EALREADY && __EALREADY */
#if !defined(EINPROGRESS) && defined(__EINPROGRESS)
#define EINPROGRESS     __EINPROGRESS     /* Operation now in progress */
#endif /* !EINPROGRESS && __EINPROGRESS */
#if !defined(ESTALE) && defined(__ESTALE)
#define ESTALE          __ESTALE          /* Stale file handle */
#endif /* !ESTALE && __ESTALE */
#if !defined(EUCLEAN) && defined(__EUCLEAN)
#define EUCLEAN         __EUCLEAN         /* Structure needs cleaning */
#endif /* !EUCLEAN && __EUCLEAN */
#if !defined(ENOTNAM) && defined(__ENOTNAM)
#define ENOTNAM         __ENOTNAM         /* Not a XENIX named type file */
#endif /* !ENOTNAM && __ENOTNAM */
#if !defined(ENAVAIL) && defined(__ENAVAIL)
#define ENAVAIL         __ENAVAIL         /* No XENIX semaphores available */
#endif /* !ENAVAIL && __ENAVAIL */
#if !defined(EISNAM) && defined(__EISNAM)
#define EISNAM          __EISNAM          /* Is a named type file */
#endif /* !EISNAM && __EISNAM */
#if !defined(EREMOTEIO) && defined(__EREMOTEIO)
#define EREMOTEIO       __EREMOTEIO       /* Remote I/O error */
#endif /* !EREMOTEIO && __EREMOTEIO */
#if !defined(EDQUOT) && defined(__EDQUOT)
#define EDQUOT          __EDQUOT          /* Quota exceeded */
#endif /* !EDQUOT && __EDQUOT */
#if !defined(ENOMEDIUM) && defined(__ENOMEDIUM)
#define ENOMEDIUM       __ENOMEDIUM       /* No medium found */
#endif /* !ENOMEDIUM && __ENOMEDIUM */
#if !defined(EMEDIUMTYPE) && defined(__EMEDIUMTYPE)
#define EMEDIUMTYPE     __EMEDIUMTYPE     /* Wrong medium type */
#endif /* !EMEDIUMTYPE && __EMEDIUMTYPE */
#if !defined(ECANCELED) && defined(__ECANCELED)
#define ECANCELED       __ECANCELED       /* Operation canceled */
#endif /* !ECANCELED && __ECANCELED */
#if !defined(ENOKEY) && defined(__ENOKEY)
#define ENOKEY          __ENOKEY          /* Required key not available */
#endif /* !ENOKEY && __ENOKEY */
#if !defined(EKEYEXPIRED) && defined(__EKEYEXPIRED)
#define EKEYEXPIRED     __EKEYEXPIRED     /* Key has expired */
#endif /* !EKEYEXPIRED && __EKEYEXPIRED */
#if !defined(EKEYREVOKED) && defined(__EKEYREVOKED)
#define EKEYREVOKED     __EKEYREVOKED     /* Key has been revoked */
#endif /* !EKEYREVOKED && __EKEYREVOKED */
#if !defined(EKEYREJECTED) && defined(__EKEYREJECTED)
#define EKEYREJECTED    __EKEYREJECTED    /* Key was rejected by service */
#endif /* !EKEYREJECTED && __EKEYREJECTED */
#if !defined(EOWNERDEAD) && defined(__EOWNERDEAD)
#define EOWNERDEAD      __EOWNERDEAD      /* Owner died */
#endif /* !EOWNERDEAD && __EOWNERDEAD */
#if !defined(ENOTRECOVERABLE) && defined(__ENOTRECOVERABLE)
#define ENOTRECOVERABLE __ENOTRECOVERABLE /* State not recoverable */
#endif /* !ENOTRECOVERABLE && __ENOTRECOVERABLE */
#if !defined(ERFKILL) && defined(__ERFKILL)
#define ERFKILL         __ERFKILL         /* Operation not possible due to RF-kill */
#endif /* !ERFKILL && __ERFKILL */
#if !defined(EHWPOISON) && defined(__EHWPOISON)
#define EHWPOISON       __EHWPOISON       /* Memory page has hardware error */
#endif /* !EHWPOISON && __EHWPOISON */

/* Aliases */
#ifndef EWOULDBLOCK
#ifdef __EWOULDBLOCK
#define EWOULDBLOCK __EWOULDBLOCK /* Operation would block */
#elif defined(EAGAIN)
#define EWOULDBLOCK EAGAIN /* Operation would block */
#endif /* ... */
#endif /* !EWOULDBLOCK */
#ifndef EDEADLOCK
#ifdef __EDEADLOCK
#define EDEADLOCK __EDEADLOCK /* Resource deadlock would occur */
#elif defined(EDEADLK)
#define EDEADLOCK EDEADLK /* Resource deadlock would occur */
#endif /* EDEADLK */
#endif /* !EDEADLOCK */

#endif /* !_ASM_ERRNO_H */
