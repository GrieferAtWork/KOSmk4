/* HASH CRC-32:0xe8280075 */
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
#ifndef __local_strerror_s_defined
#define __local_strerror_s_defined 1
#include <__crt.h>
#include <bits/types.h>
#ifndef ___local_sys_errlist_defined
#define ___local_sys_errlist_defined 1
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
__LIBC char const *const ___sys_errlist[];
__LIBC int ___sys_nerr;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
__LIBC __ATTR_WUNUSED __ATTR_CONST char const *const *(__LIBCCALL __sys_errlist)(void);
__LIBC __ATTR_WUNUSED __ATTR_CONST int *(__LIBCCALL __sys_nerr)(void);
#else /* ... */
#undef ___local_sys_errlist_defined
#endif /* !... */
#endif
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerror_s) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(strerror_s))(__errno_t __errnum) {
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
	return (unsigned int)__errnum < (unsigned int)_sys_nerr ? _sys_errlist[__errnum] : __NULLPTR;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
	return (unsigned int)__errnum < (unsigned int)*__sys_nerr() ? __sys_errlist()[__errnum] : __NULLPTR;
#else
	char const *__result;
	switch (__errnum) {

#ifdef __EPERM
	case __EPERM:           __result = "Operation not permitted"; break;
#endif /* EPERM */
#ifdef __ENOENT
	case __ENOENT:          __result = "No such file or directory"; break;
#endif /* ENOENT */
#ifdef __ESRCH
	case __ESRCH:           __result = "No such process"; break;
#endif /* ESRCH */
#ifdef __EINTR
	case __EINTR:           __result = "Interrupted system call"; break;
#endif /* EINTR */
#ifdef __EIO
	case __EIO:             __result = "I/O error"; break;
#endif /* EIO */
#ifdef __ENXIO
	case __ENXIO:           __result = "No such device or address"; break;
#endif /* ENXIO */
#ifdef __E2BIG
	case __E2BIG:           __result = "Argument list too long"; break;
#endif /* E2BIG */
#ifdef __ENOEXEC
	case __ENOEXEC:         __result = "Exec format error"; break;
#endif /* ENOEXEC */
#ifdef __EBADF
	case __EBADF:           __result = "Bad file number"; break;
#endif /* EBADF */
#ifdef __ECHILD
	case __ECHILD:          __result = "No child processes"; break;
#endif /* ECHILD */
#ifdef __EAGAIN
	case __EAGAIN:          __result = "Try again"; break;
#endif /* EAGAIN */
#ifdef __ENOMEM
	case __ENOMEM:          __result = "Out of memory"; break;
#endif /* ENOMEM */
#ifdef __EACCES
	case __EACCES:          __result = "Permission denied"; break;
#endif /* EACCES */
#ifdef __EFAULT
	case __EFAULT:          __result = "Bad address"; break;
#endif /* EFAULT */
#ifdef __EBUSY
	case __EBUSY:           __result = "Device or resource busy"; break;
#endif /* EBUSY */
#ifdef __EEXIST
	case __EEXIST:          __result = "File exists"; break;
#endif /* EEXIST */
#ifdef __EXDEV
	case __EXDEV:           __result = "Cross-device link"; break;
#endif /* EXDEV */
#ifdef __ENODEV
	case __ENODEV:          __result = "No such device"; break;
#endif /* ENODEV */
#ifdef __ENOTDIR
	case __ENOTDIR:         __result = "Not a directory"; break;
#endif /* ENOTDIR */
#ifdef __EISDIR
	case __EISDIR:          __result = "Is a directory"; break;
#endif /* EISDIR */
#ifdef __ENFILE
	case __ENFILE:          __result = "File table overflow"; break;
#endif /* ENFILE */
#ifdef __EMFILE
	case __EMFILE:          __result = "Too many open files"; break;
#endif /* EMFILE */
#ifdef __ENOTTY
	case __ENOTTY:          __result = "Not a typewriter"; break;
#endif /* ENOTTY */
#ifdef __EFBIG
	case __EFBIG:           __result = "File too large"; break;
#endif /* EFBIG */
#ifdef __ENOSPC
	case __ENOSPC:          __result = "No space left on device"; break;
#endif /* ENOSPC */
#ifdef __ESPIPE
	case __ESPIPE:          __result = "Illegal seek"; break;
#endif /* ESPIPE */
#ifdef __EROFS
	case __EROFS:           __result = "Read-only file system"; break;
#endif /* EROFS */
#ifdef __EMLINK
	case __EMLINK:          __result = "Too many links"; break;
#endif /* EMLINK */
#ifdef __EPIPE
	case __EPIPE:           __result = "Broken pipe"; break;
#endif /* EPIPE */
#ifdef __EDOM
	case __EDOM:            __result = "Math argument out of domain of func"; break;
#endif /* EDOM */
#ifdef __ENAMETOOLONG
	case __ENAMETOOLONG:    __result = "File name too long"; break;
#endif /* ENAMETOOLONG */
#ifdef __ENOLCK
	case __ENOLCK:          __result = "No record locks available"; break;
#endif /* ENOLCK */
#ifdef __ENOSYS
	case __ENOSYS:          __result = "Function not implemented"; break;
#endif /* ENOSYS */
#ifdef __ENOTEMPTY
	case __ENOTEMPTY:       __result = "Directory not empty"; break;
#endif /* ENOTEMPTY */
#ifdef __EINVAL
	case __EINVAL:          __result = "Invalid argument"; break;
#endif /* EINVAL */
#ifdef __ERANGE
	case __ERANGE:          __result = "Math result not representable"; break;
#endif /* ERANGE */
#ifdef __EILSEQ
	case __EILSEQ:          __result = "Illegal byte sequence"; break;
#endif /* EILSEQ */
#ifdef __EDEADLOCK
	case __EDEADLOCK:       __result = "Resource deadlock would occur"; break;
#endif /* EDEADLOCK */
#ifdef __EADDRINUSE
	case __EADDRINUSE:      __result = "Address already in use"; break;
#endif /* EADDRINUSE */
#ifdef __EADDRNOTAVAIL
	case __EADDRNOTAVAIL:   __result = "Cannot assign requested address"; break;
#endif /* EADDRNOTAVAIL */
#ifdef __EAFNOSUPPORT
	case __EAFNOSUPPORT:    __result = "Address family not supported by protocol"; break;
#endif /* EAFNOSUPPORT */
#ifdef __EALREADY
	case __EALREADY:        __result = "Operation already in progress"; break;
#endif /* EALREADY */
#ifdef __EBADMSG
	case __EBADMSG:         __result = "Not a data message"; break;
#endif /* EBADMSG */
#ifdef __ECANCELED
	case __ECANCELED:       __result = "Operation Canceled"; break;
#endif /* ECANCELED */
#ifdef __ECONNABORTED
	case __ECONNABORTED:    __result = "Software caused connection abort"; break;
#endif /* ECONNABORTED */
#ifdef __ECONNREFUSED
	case __ECONNREFUSED:    __result = "Connection refused"; break;
#endif /* ECONNREFUSED */
#ifdef __ECONNRESET
	case __ECONNRESET:      __result = "Connection reset by peer"; break;
#endif /* ECONNRESET */
#ifdef __EDESTADDRREQ
	case __EDESTADDRREQ:    __result = "Destination address required"; break;
#endif /* EDESTADDRREQ */
#ifdef __EHOSTUNREACH
	case __EHOSTUNREACH:    __result = "No route to host"; break;
#endif /* EHOSTUNREACH */
#ifdef __EIDRM
	case __EIDRM:           __result = "Identifier removed"; break;
#endif /* EIDRM */
#ifdef __EINPROGRESS
	case __EINPROGRESS:     __result = "Operation now in progress"; break;
#endif /* EINPROGRESS */
#ifdef __EISCONN
	case __EISCONN:         __result = "Transport endpoint is already connected"; break;
#endif /* EISCONN */
#ifdef __ELOOP
	case __ELOOP:           __result = "Too many symbolic links encountered"; break;
#endif /* ELOOP */
#ifdef __EMSGSIZE
	case __EMSGSIZE:        __result = "Message too long"; break;
#endif /* EMSGSIZE */
#ifdef __ENETDOWN
	case __ENETDOWN:        __result = "Network is down"; break;
#endif /* ENETDOWN */
#ifdef __ENETRESET
	case __ENETRESET:       __result = "Network dropped connection because of reset"; break;
#endif /* ENETRESET */
#ifdef __ENETUNREACH
	case __ENETUNREACH:     __result = "Network is unreachable"; break;
#endif /* ENETUNREACH */
#ifdef __ENOBUFS
	case __ENOBUFS:         __result = "No buffer space available"; break;
#endif /* ENOBUFS */
#ifdef __ENODATA
	case __ENODATA:         __result = "No data available"; break;
#endif /* ENODATA */
#ifdef __ENOLINK
	case __ENOLINK:         __result = "Link has been severed"; break;
#endif /* ENOLINK */
#ifdef __ENOMSG
	case __ENOMSG:          __result = "No message of desired type"; break;
#endif /* ENOMSG */
#ifdef __ENOPROTOOPT
	case __ENOPROTOOPT:     __result = "Protocol not available"; break;
#endif /* ENOPROTOOPT */
#ifdef __ENOSR
	case __ENOSR:           __result = "Out of streams resources"; break;
#endif /* ENOSR */
#ifdef __ENOSTR
	case __ENOSTR:          __result = "Device not a stream"; break;
#endif /* ENOSTR */
#ifdef __ENOTCONN
	case __ENOTCONN:        __result = "Transport endpoint is not connected"; break;
#endif /* ENOTCONN */
#ifdef __ENOTRECOVERABLE
	case __ENOTRECOVERABLE: __result = "State not recoverable"; break;
#endif /* ENOTRECOVERABLE */
#ifdef __ENOTSOCK
	case __ENOTSOCK:        __result = "Socket operation on non-socket"; break;
#endif /* ENOTSOCK */
#ifdef __ENOTSUP
	case __ENOTSUP:         __result = "Not supported"; break;
#endif /* ENOTSUP */
#ifdef __EOPNOTSUPP
	case __EOPNOTSUPP:      __result = "Operation not supported on transport endpoint"; break;
#endif /* EOPNOTSUPP */
#ifdef __EOTHER
	case __EOTHER:          __result = "Other"; break;
#endif /* EOTHER */
#ifdef __EOVERFLOW
	case __EOVERFLOW:       __result = "Value too large for defined data type"; break;
#endif /* EOVERFLOW */
#ifdef __EOWNERDEAD
	case __EOWNERDEAD:      __result = "Owner died"; break;
#endif /* EOWNERDEAD */
#ifdef __EPROTO
	case __EPROTO:          __result = "Protocol error"; break;
#endif /* EPROTO */
#ifdef __EPROTONOSUPPORT
	case __EPROTONOSUPPORT: __result = "Protocol not supported"; break;
#endif /* EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
	case __EPROTOTYPE:      __result = "Protocol wrong type for socket"; break;
#endif /* EPROTOTYPE */
#ifdef __ETIME
	case __ETIME:           __result = "Timer expired"; break;
#endif /* ETIME */
#ifdef __ETIMEDOUT
	case __ETIMEDOUT:       __result = "Connection timed out"; break;
#endif /* ETIMEDOUT */
#ifdef __ETXTBSY
	case __ETXTBSY:         __result = "Text file busy"; break;
#endif /* ETXTBSY */
#ifdef __EFTYPE
	case __EFTYPE:          __result = "Inappropriate file type or format"; break;
#endif /* EFTYPE */
#ifdef __ENMFILE
	case __ENMFILE:         __result = "No more files"; break;
#endif /* ENMFILE */
#ifdef __EPFNOSUPPORT
	case __EPFNOSUPPORT:    __result = "Protocol family not supported"; break;
#endif /* EPFNOSUPPORT */
#ifdef __EHOSTDOWN
	case __EHOSTDOWN:       __result = "Host is down"; break;
#endif /* EHOSTDOWN */
#ifdef __ETOOMANYREFS
	case __ETOOMANYREFS:    __result = "Too many references: cannot splice"; break;
#endif /* ETOOMANYREFS */
#ifdef __EDQUOT
	case __EDQUOT:          __result = "Quota exceeded"; break;
#endif /* EDQUOT */
#ifdef __ESTALE
	case __ESTALE:          __result = "Stale file handle"; break;
#endif /* ESTALE */
#ifdef __ENOSHARE
	case __ENOSHARE:        __result = "No such host or network path"; break;
#endif /* ENOSHARE */
#ifdef __ECASECLASH
	case __ECASECLASH:      __result = "Filename exists with different case"; break;
#endif /* ECASECLASH */
#ifdef __ENOTBLK
	case __ENOTBLK:         __result = "Block device required"; break;
#endif /* ENOTBLK */
#ifdef __ECHRNG
	case __ECHRNG:          __result = "Channel number out of range"; break;
#endif /* ECHRNG */
#ifdef __EL2NSYNC
	case __EL2NSYNC:        __result = "Level 2 not synchronized"; break;
#endif /* EL2NSYNC */
#ifdef __EL3HLT
	case __EL3HLT:          __result = "Level 3 halted"; break;
#endif /* EL3HLT */
#ifdef __EL3RST
	case __EL3RST:          __result = "Level 3 reset"; break;
#endif /* EL3RST */
#ifdef __ELNRNG
	case __ELNRNG:          __result = "Link number out of range"; break;
#endif /* ELNRNG */
#ifdef __EUNATCH
	case __EUNATCH:         __result = "Protocol driver not attached"; break;
#endif /* EUNATCH */
#ifdef __ENOCSI
	case __ENOCSI:          __result = "No CSI structure available"; break;
#endif /* ENOCSI */
#ifdef __EL2HLT
	case __EL2HLT:          __result = "Level 2 halted"; break;
#endif /* EL2HLT */
#ifdef __EBADE
	case __EBADE:           __result = "Invalid exchange"; break;
#endif /* EBADE */
#ifdef __EBADR
	case __EBADR:           __result = "Invalid request descriptor"; break;
#endif /* EBADR */
#ifdef __EXFULL
	case __EXFULL:          __result = "Exchange full"; break;
#endif /* EXFULL */
#ifdef __ENOANO
	case __ENOANO:          __result = "No anode"; break;
#endif /* ENOANO */
#ifdef __EBADRQC
	case __EBADRQC:         __result = "Invalid request code"; break;
#endif /* EBADRQC */
#ifdef __EBADSLT
	case __EBADSLT:         __result = "Invalid slot"; break;
#endif /* EBADSLT */
#ifdef __EBFONT
	case __EBFONT:          __result = "Bad font file fmt"; break;
#endif /* EBFONT */
#ifdef __ENONET
	case __ENONET:          __result = "Machine is not on the network"; break;
#endif /* ENONET */
#ifdef __ENOPKG
	case __ENOPKG:          __result = "Package not installed"; break;
#endif /* ENOPKG */
#ifdef __EREMOTE
	case __EREMOTE:         __result = "The object is remote"; break;
#endif /* EREMOTE */
#ifdef __EADV
	case __EADV:            __result = "Advertise error"; break;
#endif /* EADV */
#ifdef __ESRMNT
	case __ESRMNT:          __result = "Srmount error"; break;
#endif /* ESRMNT */
#ifdef __ECOMM
	case __ECOMM:           __result = "Communication error on send"; break;
#endif /* ECOMM */
#ifdef __ELBIN
	case __ELBIN:           __result = "Inode is remote (not really error)"; break;
#endif /* ELBIN */
#ifdef __EDOTDOT
	case __EDOTDOT:         __result = "Cross mount point (not really error)"; break;
#endif /* EDOTDOT */
#ifdef __ENOTUNIQ
	case __ENOTUNIQ:        __result = "Given log. name not unique"; break;
#endif /* ENOTUNIQ */
#ifdef __EBADFD
	case __EBADFD:          __result = "f.d. invalid for this operation"; break;
#endif /* EBADFD */
#ifdef __EREMCHG
	case __EREMCHG:         __result = "Remote address changed"; break;
#endif /* EREMCHG */
#ifdef __ELIBACC
	case __ELIBACC:         __result = "Can't access a needed shared lib"; break;
#endif /* ELIBACC */
#ifdef __ELIBBAD
	case __ELIBBAD:         __result = "Accessing a corrupted shared lib"; break;
#endif /* ELIBBAD */
#ifdef __ELIBSCN
	case __ELIBSCN:         __result = ".lib section in a.out corrupted"; break;
#endif /* ELIBSCN */
#ifdef __ELIBMAX
	case __ELIBMAX:         __result = "Attempting to link in too many libs"; break;
#endif /* ELIBMAX */
#ifdef __ELIBEXEC
	case __ELIBEXEC:        __result = "Attempting to exec a shared library"; break;
#endif /* ELIBEXEC */
#ifdef __ESHUTDOWN
	case __ESHUTDOWN:       __result = "Can't send after socket shutdown"; break;
#endif /* ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
	case __ESOCKTNOSUPPORT: __result = "Socket type not supported"; break;
#endif /* ESOCKTNOSUPPORT */
#ifdef __EPROCLIM
	case __EPROCLIM:        __result = "Process limit reached"; break;
#endif /* EPROCLIM */
#ifdef __EUSERS
	case __EUSERS:          __result = "Too many users"; break;
#endif /* EUSERS */
#ifdef __ENOMEDIUM
	case __ENOMEDIUM:       __result = "No medium (in tape drive)"; break;
#endif /* ENOMEDIUM */
#ifdef __ESTRPIPE
	case __ESTRPIPE:        __result = "Streams pipe error"; break;
#endif /* ESTRPIPE */
#ifdef __EMULTIHOP
	case __EMULTIHOP:       __result = "Multihop attempted"; break;
#endif /* EMULTIHOP */
#ifdef __ERESTART
	case __ERESTART:        __result = "Interrupted system call should be restarted"; break;
#endif /* ERESTART */
#ifdef __EUCLEAN
	case __EUCLEAN:         __result = "Structure needs cleaning"; break;
#endif /* EUCLEAN */
#ifdef __ENOTNAM
	case __ENOTNAM:         __result = "Not a XENIX named type file"; break;
#endif /* ENOTNAM */
#ifdef __ENAVAIL
	case __ENAVAIL:         __result = "No XENIX semaphores available"; break;
#endif /* ENAVAIL */
#ifdef __EISNAM
	case __EISNAM:          __result = "Is a named type file"; break;
#endif /* EISNAM */
#ifdef __EREMOTEIO
	case __EREMOTEIO:       __result = "Remote I/O error"; break;
#endif /* EREMOTEIO */
#ifdef __EMEDIUMTYPE
	case __EMEDIUMTYPE:     __result = "Wrong medium type"; break;
#endif /* EMEDIUMTYPE */
#ifdef __ENOKEY
	case __ENOKEY:          __result = "Required key not available"; break;
#endif /* ENOKEY */
#ifdef __EKEYEXPIRED
	case __EKEYEXPIRED:     __result = "Key has expired"; break;
#endif /* EKEYEXPIRED */
#ifdef __EKEYREVOKED
	case __EKEYREVOKED:     __result = "Key has been revoked"; break;
#endif /* EKEYREVOKED */
#ifdef __EKEYREJECTED
	case __EKEYREJECTED:    __result = "Key was rejected by service"; break;
#endif /* EKEYREJECTED */
#ifdef __ERFKILL
	case __ERFKILL:         __result = "Operation not possible due to RF-kill"; break;
#endif /* ERFKILL */
#ifdef __EHWPOISON
	case __EHWPOISON:       __result = "Memory page has hardware error"; break;
#endif /* EHWPOISON */
#if defined(__STRUNCATE) && (!defined(__ERANGE) || __STRUNCATE != __ERANGE)
	case __STRUNCATE:       __result = "Truncated"; break;
#endif /* STRUNCATE && (!ERANGE || STRUNCATE != ERANGE) */
#if defined(__EWOULDBLOCK) && (!defined(__EAGAIN) || __EWOULDBLOCK != __EAGAIN)
	case __EWOULDBLOCK:     __result = "Operation would block"; break;
#endif /* EWOULDBLOCK && (!EAGAIN || EWOULDBLOCK != EAGAIN) */
#if defined(__EDEADLK) && (!defined(__EDEADLOCK) || __EDEADLOCK != __EDEADLK)
	case __EDEADLK:         __result = "Resource deadlock would occur"; break;
#endif /* EDEADLK && (!EDEADLOCK || EDEADLOCK != EDEADLK) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerror_s_defined
#define __local___localdep_strerror_s_defined 1
#define __localdep_strerror_s __LIBC_LOCAL_NAME(strerror_s)
#endif /* !__local___localdep_strerror_s_defined */
#endif /* !__local_strerror_s_defined */
