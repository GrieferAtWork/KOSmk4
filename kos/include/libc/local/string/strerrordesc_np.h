/* HASH CRC-32:0xd5176895 */
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
#ifndef __local_strerrordesc_np_defined
#define __local_strerrordesc_np_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
#ifndef __local___localdep_strerrorname_np_defined
#define __local___localdep_strerrorname_np_defined
#ifdef __CRT_HAVE_strerrorname_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrorname_np,(__errnum))
#elif defined(__CRT_HAVE_strerrno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrno,(__errnum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerrorname_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerrorname_np __LIBC_LOCAL_NAME(strerrorname_np)
#endif /* !... */
#endif /* !__local___localdep_strerrorname_np_defined */
__NAMESPACE_LOCAL_END
#ifndef __BUILDING_LIBC
#ifndef ___local_sys_errlist_defined
#define ___local_sys_errlist_defined
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
#ifndef _sys_errlist
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist _sys_errlist
#endif /* !_sys_errlist */
#ifndef _sys_nerr
__CSDECLARE(,int,_sys_nerr)
#define _sys_nerr _sys_nerr
#endif /* !_sys_nerr */
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *const *,__sys_errlist,(void),())
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,int *,__sys_nerr,(void),())
#else /* ... */
#undef ___local_sys_errlist_defined
#endif /* !... */
#endif /* !___local_sys_errlist_defined */
#endif /* !__BUILDING_LIBC */
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerrordesc_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(strerrordesc_np))(__errno_t __errnum) {
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
	return (unsigned int)__errnum < (unsigned int)_sys_nerr ? _sys_errlist[__errnum] : __NULLPTR;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
	return (unsigned int)__errnum < (unsigned int)*__sys_nerr() ? __sys_errlist()[__errnum] : __NULLPTR;
#elif !defined(__CRT_HAVE_strerrorname_np) || defined(__CRT_KOS)
	char const *__result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_strerrorname_np)(__errnum);
	if (__result)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	return __result;
#else /* ... */
	char const *__result;
	switch (__errnum) {

#ifdef __EPERM
	case __EPERM:           __result = "Operation not permitted"; break;
#endif /* __EPERM */
#ifdef __ENOENT
	case __ENOENT:          __result = "No such file or directory"; break;
#endif /* __ENOENT */
#ifdef __ESRCH
	case __ESRCH:           __result = "No such process"; break;
#endif /* __ESRCH */
#ifdef __EINTR
	case __EINTR:           __result = "Interrupted system call"; break;
#endif /* __EINTR */
#ifdef __EIO
	case __EIO:             __result = "I/O error"; break;
#endif /* __EIO */
#ifdef __ENXIO
	case __ENXIO:           __result = "No such device or address"; break;
#endif /* __ENXIO */
#ifdef __E2BIG
	case __E2BIG:           __result = "Argument list too long"; break;
#endif /* __E2BIG */
#ifdef __ENOEXEC
	case __ENOEXEC:         __result = "Exec format error"; break;
#endif /* __ENOEXEC */
#ifdef __EBADF
	case __EBADF:           __result = "Bad file number"; break;
#endif /* __EBADF */
#ifdef __ECHILD
	case __ECHILD:          __result = "No child processes"; break;
#endif /* __ECHILD */
#ifdef __EAGAIN
	case __EAGAIN:          __result = "Try again"; break;
#endif /* __EAGAIN */
#ifdef __ENOMEM
	case __ENOMEM:          __result = "Out of memory"; break;
#endif /* __ENOMEM */
#ifdef __EACCES
	case __EACCES:          __result = "Permission denied"; break;
#endif /* __EACCES */
#ifdef __EFAULT
	case __EFAULT:          __result = "Bad address"; break;
#endif /* __EFAULT */
#ifdef __EBUSY
	case __EBUSY:           __result = "Device or resource busy"; break;
#endif /* __EBUSY */
#ifdef __EEXIST
	case __EEXIST:          __result = "File exists"; break;
#endif /* __EEXIST */
#ifdef __EXDEV
	case __EXDEV:           __result = "Cross-device link"; break;
#endif /* __EXDEV */
#ifdef __ENODEV
	case __ENODEV:          __result = "No such device"; break;
#endif /* __ENODEV */
#ifdef __ENOTDIR
	case __ENOTDIR:         __result = "Not a directory"; break;
#endif /* __ENOTDIR */
#ifdef __EISDIR
	case __EISDIR:          __result = "Is a directory"; break;
#endif /* __EISDIR */
#ifdef __ENFILE
	case __ENFILE:          __result = "File table overflow"; break;
#endif /* __ENFILE */
#ifdef __EMFILE
	case __EMFILE:          __result = "Too many open files"; break;
#endif /* __EMFILE */
#ifdef __ENOTTY
	case __ENOTTY:          __result = "Not a typewriter"; break;
#endif /* __ENOTTY */
#ifdef __EFBIG
	case __EFBIG:           __result = "File too large"; break;
#endif /* __EFBIG */
#ifdef __ENOSPC
	case __ENOSPC:          __result = "No space left on device"; break;
#endif /* __ENOSPC */
#ifdef __ESPIPE
	case __ESPIPE:          __result = "Illegal seek"; break;
#endif /* __ESPIPE */
#ifdef __EROFS
	case __EROFS:           __result = "Read-only file system"; break;
#endif /* __EROFS */
#ifdef __EMLINK
	case __EMLINK:          __result = "Too many links"; break;
#endif /* __EMLINK */
#ifdef __EPIPE
	case __EPIPE:           __result = "Broken pipe"; break;
#endif /* __EPIPE */
#ifdef __EDOM
	case __EDOM:            __result = "Math argument out of domain of func"; break;
#endif /* __EDOM */
#ifdef __ENAMETOOLONG
	case __ENAMETOOLONG:    __result = "File name too long"; break;
#endif /* __ENAMETOOLONG */
#ifdef __ENOLCK
	case __ENOLCK:          __result = "No record locks available"; break;
#endif /* __ENOLCK */
#ifdef __ENOSYS
	case __ENOSYS:          __result = "Function not implemented"; break;
#endif /* __ENOSYS */
#ifdef __ENOTEMPTY
	case __ENOTEMPTY:       __result = "Directory not empty"; break;
#endif /* __ENOTEMPTY */
#ifdef __EINVAL
	case __EINVAL:          __result = "Invalid argument"; break;
#endif /* __EINVAL */
#ifdef __ERANGE
	case __ERANGE:          __result = "Math result not representable"; break;
#endif /* __ERANGE */
#ifdef __EILSEQ
	case __EILSEQ:          __result = "Illegal byte sequence"; break;
#endif /* __EILSEQ */
#ifdef __EDEADLOCK
	case __EDEADLOCK:       __result = "Resource deadlock would occur"; break;
#endif /* __EDEADLOCK */
#ifdef __EADDRINUSE
	case __EADDRINUSE:      __result = "Address already in use"; break;
#endif /* __EADDRINUSE */
#ifdef __EADDRNOTAVAIL
	case __EADDRNOTAVAIL:   __result = "Cannot assign requested address"; break;
#endif /* __EADDRNOTAVAIL */
#ifdef __EAFNOSUPPORT
	case __EAFNOSUPPORT:    __result = "Address family not supported by protocol"; break;
#endif /* __EAFNOSUPPORT */
#ifdef __EALREADY
	case __EALREADY:        __result = "Operation already in progress"; break;
#endif /* __EALREADY */
#ifdef __EBADMSG
	case __EBADMSG:         __result = "Not a data message"; break;
#endif /* __EBADMSG */
#ifdef __ECANCELED
	case __ECANCELED:       __result = "Operation Canceled"; break;
#endif /* __ECANCELED */
#ifdef __ECONNABORTED
	case __ECONNABORTED:    __result = "Software caused connection abort"; break;
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
	case __ECONNREFUSED:    __result = "Connection refused"; break;
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
	case __ECONNRESET:      __result = "Connection reset by peer"; break;
#endif /* __ECONNRESET */
#ifdef __EDESTADDRREQ
	case __EDESTADDRREQ:    __result = "Destination address required"; break;
#endif /* __EDESTADDRREQ */
#ifdef __EHOSTUNREACH
	case __EHOSTUNREACH:    __result = "No route to host"; break;
#endif /* __EHOSTUNREACH */
#ifdef __EIDRM
	case __EIDRM:           __result = "Identifier removed"; break;
#endif /* __EIDRM */
#ifdef __EINPROGRESS
	case __EINPROGRESS:     __result = "Operation now in progress"; break;
#endif /* __EINPROGRESS */
#ifdef __EISCONN
	case __EISCONN:         __result = "Transport endpoint is already connected"; break;
#endif /* __EISCONN */
#ifdef __ELOOP
	case __ELOOP:           __result = "Too many symbolic links encountered"; break;
#endif /* __ELOOP */
#ifdef __EMSGSIZE
	case __EMSGSIZE:        __result = "Message too long"; break;
#endif /* __EMSGSIZE */
#ifdef __ENETDOWN
	case __ENETDOWN:        __result = "Network is down"; break;
#endif /* __ENETDOWN */
#ifdef __ENETRESET
	case __ENETRESET:       __result = "Network dropped connection because of reset"; break;
#endif /* __ENETRESET */
#ifdef __ENETUNREACH
	case __ENETUNREACH:     __result = "Network is unreachable"; break;
#endif /* __ENETUNREACH */
#ifdef __ENOBUFS
	case __ENOBUFS:         __result = "No buffer space available"; break;
#endif /* __ENOBUFS */
#ifdef __ENODATA
	case __ENODATA:         __result = "No data available"; break;
#endif /* __ENODATA */
#ifdef __ENOLINK
	case __ENOLINK:         __result = "Link has been severed"; break;
#endif /* __ENOLINK */
#ifdef __ENOMSG
	case __ENOMSG:          __result = "No message of desired type"; break;
#endif /* __ENOMSG */
#ifdef __ENOPROTOOPT
	case __ENOPROTOOPT:     __result = "Protocol not available"; break;
#endif /* __ENOPROTOOPT */
#ifdef __ENOSR
	case __ENOSR:           __result = "Out of streams resources"; break;
#endif /* __ENOSR */
#ifdef __ENOSTR
	case __ENOSTR:          __result = "Device not a stream"; break;
#endif /* __ENOSTR */
#ifdef __ENOTCONN
	case __ENOTCONN:        __result = "Transport endpoint is not connected"; break;
#endif /* __ENOTCONN */
#ifdef __ENOTRECOVERABLE
	case __ENOTRECOVERABLE: __result = "State not recoverable"; break;
#endif /* __ENOTRECOVERABLE */
#ifdef __ENOTSOCK
	case __ENOTSOCK:        __result = "Socket operation on non-socket"; break;
#endif /* __ENOTSOCK */
#ifdef __ENOTSUP
	case __ENOTSUP:         __result = "Not supported"; break;
#endif /* __ENOTSUP */
#ifdef __EOPNOTSUPP
	case __EOPNOTSUPP:      __result = "Operation not supported on transport endpoint"; break;
#endif /* __EOPNOTSUPP */
#ifdef __EOTHER
	case __EOTHER:          __result = "Other"; break;
#endif /* __EOTHER */
#ifdef __EOVERFLOW
	case __EOVERFLOW:       __result = "Value too large for defined data type"; break;
#endif /* __EOVERFLOW */
#ifdef __EOWNERDEAD
	case __EOWNERDEAD:      __result = "Owner died"; break;
#endif /* __EOWNERDEAD */
#ifdef __EPROTO
	case __EPROTO:          __result = "Protocol error"; break;
#endif /* __EPROTO */
#ifdef __EPROTONOSUPPORT
	case __EPROTONOSUPPORT: __result = "Protocol not supported"; break;
#endif /* __EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
	case __EPROTOTYPE:      __result = "Protocol wrong type for socket"; break;
#endif /* __EPROTOTYPE */
#ifdef __ETIME
	case __ETIME:           __result = "Timer expired"; break;
#endif /* __ETIME */
#ifdef __ETIMEDOUT
	case __ETIMEDOUT:       __result = "Connection timed out"; break;
#endif /* __ETIMEDOUT */
#ifdef __ETXTBSY
	case __ETXTBSY:         __result = "Text file busy"; break;
#endif /* __ETXTBSY */
#ifdef __EFTYPE
	case __EFTYPE:          __result = "Inappropriate file type or format"; break;
#endif /* __EFTYPE */
#ifdef __ENMFILE
	case __ENMFILE:         __result = "No more files"; break;
#endif /* __ENMFILE */
#ifdef __EPFNOSUPPORT
	case __EPFNOSUPPORT:    __result = "Protocol family not supported"; break;
#endif /* __EPFNOSUPPORT */
#ifdef __EHOSTDOWN
	case __EHOSTDOWN:       __result = "Host is down"; break;
#endif /* __EHOSTDOWN */
#ifdef __ETOOMANYREFS
	case __ETOOMANYREFS:    __result = "Too many references: cannot splice"; break;
#endif /* __ETOOMANYREFS */
#ifdef __EDQUOT
	case __EDQUOT:          __result = "Quota exceeded"; break;
#endif /* __EDQUOT */
#ifdef __ESTALE
	case __ESTALE:          __result = "Stale file handle"; break;
#endif /* __ESTALE */
#ifdef __ENOSHARE
	case __ENOSHARE:        __result = "No such host or network path"; break;
#endif /* __ENOSHARE */
#ifdef __ECASECLASH
	case __ECASECLASH:      __result = "Filename exists with different case"; break;
#endif /* __ECASECLASH */
#ifdef __ENOTBLK
	case __ENOTBLK:         __result = "Block device required"; break;
#endif /* __ENOTBLK */
#ifdef __ECHRNG
	case __ECHRNG:          __result = "Channel number out of range"; break;
#endif /* __ECHRNG */
#ifdef __EL2NSYNC
	case __EL2NSYNC:        __result = "Level 2 not synchronized"; break;
#endif /* __EL2NSYNC */
#ifdef __EL3HLT
	case __EL3HLT:          __result = "Level 3 halted"; break;
#endif /* __EL3HLT */
#ifdef __EL3RST
	case __EL3RST:          __result = "Level 3 reset"; break;
#endif /* __EL3RST */
#ifdef __ELNRNG
	case __ELNRNG:          __result = "Link number out of range"; break;
#endif /* __ELNRNG */
#ifdef __EUNATCH
	case __EUNATCH:         __result = "Protocol driver not attached"; break;
#endif /* __EUNATCH */
#ifdef __ENOCSI
	case __ENOCSI:          __result = "No CSI structure available"; break;
#endif /* __ENOCSI */
#ifdef __EL2HLT
	case __EL2HLT:          __result = "Level 2 halted"; break;
#endif /* __EL2HLT */
#ifdef __EBADE
	case __EBADE:           __result = "Invalid exchange"; break;
#endif /* __EBADE */
#ifdef __EBADR
	case __EBADR:           __result = "Invalid request descriptor"; break;
#endif /* __EBADR */
#ifdef __EXFULL
	case __EXFULL:          __result = "Exchange full"; break;
#endif /* __EXFULL */
#ifdef __ENOANO
	case __ENOANO:          __result = "No anode"; break;
#endif /* __ENOANO */
#ifdef __EBADRQC
	case __EBADRQC:         __result = "Invalid request code"; break;
#endif /* __EBADRQC */
#ifdef __EBADSLT
	case __EBADSLT:         __result = "Invalid slot"; break;
#endif /* __EBADSLT */
#ifdef __EBFONT
	case __EBFONT:          __result = "Bad font file fmt"; break;
#endif /* __EBFONT */
#ifdef __ENONET
	case __ENONET:          __result = "Machine is not on the network"; break;
#endif /* __ENONET */
#ifdef __ENOPKG
	case __ENOPKG:          __result = "Package not installed"; break;
#endif /* __ENOPKG */
#ifdef __EREMOTE
	case __EREMOTE:         __result = "The object is remote"; break;
#endif /* __EREMOTE */
#ifdef __EADV
	case __EADV:            __result = "Advertise error"; break;
#endif /* __EADV */
#ifdef __ESRMNT
	case __ESRMNT:          __result = "Srmount error"; break;
#endif /* __ESRMNT */
#ifdef __ECOMM
	case __ECOMM:           __result = "Communication error on send"; break;
#endif /* __ECOMM */
#ifdef __ELBIN
	case __ELBIN:           __result = "Inode is remote (not really error)"; break;
#endif /* __ELBIN */
#ifdef __EDOTDOT
	case __EDOTDOT:         __result = "Cross mount point (not really error)"; break;
#endif /* __EDOTDOT */
#ifdef __ENOTUNIQ
	case __ENOTUNIQ:        __result = "Given log. name not unique"; break;
#endif /* __ENOTUNIQ */
#ifdef __EBADFD
	case __EBADFD:          __result = "f.d. invalid for this operation"; break;
#endif /* __EBADFD */
#ifdef __EREMCHG
	case __EREMCHG:         __result = "Remote address changed"; break;
#endif /* __EREMCHG */
#ifdef __ELIBACC
	case __ELIBACC:         __result = "Can't access a needed shared lib"; break;
#endif /* __ELIBACC */
#ifdef __ELIBBAD
	case __ELIBBAD:         __result = "Accessing a corrupted shared lib"; break;
#endif /* __ELIBBAD */
#ifdef __ELIBSCN
	case __ELIBSCN:         __result = ".lib section in a.out corrupted"; break;
#endif /* __ELIBSCN */
#ifdef __ELIBMAX
	case __ELIBMAX:         __result = "Attempting to link in too many libs"; break;
#endif /* __ELIBMAX */
#ifdef __ELIBEXEC
	case __ELIBEXEC:        __result = "Attempting to exec a shared library"; break;
#endif /* __ELIBEXEC */
#ifdef __ESHUTDOWN
	case __ESHUTDOWN:       __result = "Can't send after socket shutdown"; break;
#endif /* __ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
	case __ESOCKTNOSUPPORT: __result = "Socket type not supported"; break;
#endif /* __ESOCKTNOSUPPORT */
#ifdef __EPROCLIM
	case __EPROCLIM:        __result = "Process limit reached"; break;
#endif /* __EPROCLIM */
#ifdef __EUSERS
	case __EUSERS:          __result = "Too many users"; break;
#endif /* __EUSERS */
#ifdef __ENOMEDIUM
	case __ENOMEDIUM:       __result = "No medium (in tape drive)"; break;
#endif /* __ENOMEDIUM */
#ifdef __ESTRPIPE
	case __ESTRPIPE:        __result = "Streams pipe error"; break;
#endif /* __ESTRPIPE */
#ifdef __EMULTIHOP
	case __EMULTIHOP:       __result = "Multihop attempted"; break;
#endif /* __EMULTIHOP */
#ifdef __ERESTART
	case __ERESTART:        __result = "Interrupted system call should be restarted"; break;
#endif /* __ERESTART */
#ifdef __EUCLEAN
	case __EUCLEAN:         __result = "Structure needs cleaning"; break;
#endif /* __EUCLEAN */
#ifdef __ENOTNAM
	case __ENOTNAM:         __result = "Not a XENIX named type file"; break;
#endif /* __ENOTNAM */
#ifdef __ENAVAIL
	case __ENAVAIL:         __result = "No XENIX semaphores available"; break;
#endif /* __ENAVAIL */
#ifdef __EISNAM
	case __EISNAM:          __result = "Is a named type file"; break;
#endif /* __EISNAM */
#ifdef __EREMOTEIO
	case __EREMOTEIO:       __result = "Remote I/O error"; break;
#endif /* __EREMOTEIO */
#ifdef __EMEDIUMTYPE
	case __EMEDIUMTYPE:     __result = "Wrong medium type"; break;
#endif /* __EMEDIUMTYPE */
#ifdef __ENOKEY
	case __ENOKEY:          __result = "Required key not available"; break;
#endif /* __ENOKEY */
#ifdef __EKEYEXPIRED
	case __EKEYEXPIRED:     __result = "Key has expired"; break;
#endif /* __EKEYEXPIRED */
#ifdef __EKEYREVOKED
	case __EKEYREVOKED:     __result = "Key has been revoked"; break;
#endif /* __EKEYREVOKED */
#ifdef __EKEYREJECTED
	case __EKEYREJECTED:    __result = "Key was rejected by service"; break;
#endif /* __EKEYREJECTED */
#ifdef __ERFKILL
	case __ERFKILL:         __result = "Operation not possible due to RF-kill"; break;
#endif /* __ERFKILL */
#ifdef __EHWPOISON
	case __EHWPOISON:       __result = "Memory page has hardware error"; break;
#endif /* __EHWPOISON */
#if defined(__STRUNCATE) && (!defined(__ERANGE) || __STRUNCATE != __ERANGE)
	case __STRUNCATE:       __result = "Truncated"; break;
#endif /* __STRUNCATE && (!__ERANGE || __STRUNCATE != __ERANGE) */
#if defined(__EWOULDBLOCK) && (!defined(__EAGAIN) || __EWOULDBLOCK != __EAGAIN)
	case __EWOULDBLOCK:     __result = "Operation would block"; break;
#endif /* __EWOULDBLOCK && (!__EAGAIN || __EWOULDBLOCK != __EAGAIN) */
#if defined(__EDEADLK) && (!defined(__EDEADLOCK) || __EDEADLOCK != __EDEADLK)
	case __EDEADLK:         __result = "Resource deadlock would occur"; break;
#endif /* __EDEADLK && (!__EDEADLOCK || __EDEADLOCK != __EDEADLK) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerrordesc_np_defined
#define __local___localdep_strerrordesc_np_defined
#define __localdep_strerrordesc_np __LIBC_LOCAL_NAME(strerrordesc_np)
#endif /* !__local___localdep_strerrordesc_np_defined */
#endif /* !__local_strerrordesc_np_defined */
