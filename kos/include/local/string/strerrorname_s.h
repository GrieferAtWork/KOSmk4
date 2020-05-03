/* HASH CRC-32:0xf3704ab */
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
#ifndef __local_strerrorname_s_defined
#define __local_strerrorname_s_defined 1
#include <__crt.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerrorname_s) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(strerrorname_s))(int __errnum) {
#line 3460 "kos/src/libc/magic/string.c"
	char const *__result;
	switch (__errnum) {

#ifdef __EPERM
	case __EPERM:           __result = "EPERM"; break;
#endif /* EPERM */
#ifdef __ENOENT
	case __ENOENT:          __result = "ENOENT"; break;
#endif /* ENOENT */
#ifdef __ESRCH
	case __ESRCH:           __result = "ESRCH"; break;
#endif /* ESRCH */
#ifdef __EINTR
	case __EINTR:           __result = "EINTR"; break;
#endif /* EINTR */
#ifdef __EIO
	case __EIO:             __result = "EIO"; break;
#endif /* EIO */
#ifdef __ENXIO
	case __ENXIO:           __result = "ENXIO"; break;
#endif /* ENXIO */
#ifdef __E2BIG
	case __E2BIG:           __result = "E2BIG"; break;
#endif /* E2BIG */
#ifdef __ENOEXEC
	case __ENOEXEC:         __result = "ENOEXEC"; break;
#endif /* ENOEXEC */
#ifdef __EBADF
	case __EBADF:           __result = "EBADF"; break;
#endif /* EBADF */
#ifdef __ECHILD
	case __ECHILD:          __result = "ECHILD"; break;
#endif /* ECHILD */
#ifdef __EAGAIN
	case __EAGAIN:          __result = "EAGAIN"; break;
#endif /* EAGAIN */
#ifdef __ENOMEM
	case __ENOMEM:          __result = "ENOMEM"; break;
#endif /* ENOMEM */
#ifdef __EACCES
	case __EACCES:          __result = "EACCES"; break;
#endif /* EACCES */
#ifdef __EFAULT
	case __EFAULT:          __result = "EFAULT"; break;
#endif /* EFAULT */
#ifdef __EBUSY
	case __EBUSY:           __result = "EBUSY"; break;
#endif /* EBUSY */
#ifdef __EEXIST
	case __EEXIST:          __result = "EEXIST"; break;
#endif /* EEXIST */
#ifdef __EXDEV
	case __EXDEV:           __result = "EXDEV"; break;
#endif /* EXDEV */
#ifdef __ENODEV
	case __ENODEV:          __result = "ENODEV"; break;
#endif /* ENODEV */
#ifdef __ENOTDIR
	case __ENOTDIR:         __result = "ENOTDIR"; break;
#endif /* ENOTDIR */
#ifdef __EISDIR
	case __EISDIR:          __result = "EISDIR"; break;
#endif /* EISDIR */
#ifdef __ENFILE
	case __ENFILE:          __result = "ENFILE"; break;
#endif /* ENFILE */
#ifdef __EMFILE
	case __EMFILE:          __result = "EMFILE"; break;
#endif /* EMFILE */
#ifdef __ENOTTY
	case __ENOTTY:          __result = "ENOTTY"; break;
#endif /* ENOTTY */
#ifdef __EFBIG
	case __EFBIG:           __result = "EFBIG"; break;
#endif /* EFBIG */
#ifdef __ENOSPC
	case __ENOSPC:          __result = "ENOSPC"; break;
#endif /* ENOSPC */
#ifdef __ESPIPE
	case __ESPIPE:          __result = "ESPIPE"; break;
#endif /* ESPIPE */
#ifdef __EROFS
	case __EROFS:           __result = "EROFS"; break;
#endif /* EROFS */
#ifdef __EMLINK
	case __EMLINK:          __result = "EMLINK"; break;
#endif /* EMLINK */
#ifdef __EPIPE
	case __EPIPE:           __result = "EPIPE"; break;
#endif /* EPIPE */
#ifdef __EDOM
	case __EDOM:            __result = "EDOM"; break;
#endif /* EDOM */
#ifdef __ENAMETOOLONG
	case __ENAMETOOLONG:    __result = "ENAMETOOLONG"; break;
#endif /* ENAMETOOLONG */
#ifdef __ENOLCK
	case __ENOLCK:          __result = "ENOLCK"; break;
#endif /* ENOLCK */
#ifdef __ENOSYS
	case __ENOSYS:          __result = "ENOSYS"; break;
#endif /* ENOSYS */
#ifdef __ENOTEMPTY
	case __ENOTEMPTY:       __result = "ENOTEMPTY"; break;
#endif /* ENOTEMPTY */
#ifdef __EINVAL
	case __EINVAL:          __result = "EINVAL"; break;
#endif /* EINVAL */
#ifdef __ERANGE
	case __ERANGE:          __result = "ERANGE"; break;
#endif /* ERANGE */
#ifdef __EILSEQ
	case __EILSEQ:          __result = "EILSEQ"; break;
#endif /* EILSEQ */
#ifdef __EDEADLOCK
	case __EDEADLOCK:       __result = "EDEADLOCK"; break;
#endif /* EDEADLOCK */
#ifdef __EADDRINUSE
	case __EADDRINUSE:      __result = "EADDRINUSE"; break;
#endif /* EADDRINUSE */
#ifdef __EADDRNOTAVAIL
	case __EADDRNOTAVAIL:   __result = "EADDRNOTAVAIL"; break;
#endif /* EADDRNOTAVAIL */
#ifdef __EAFNOSUPPORT
	case __EAFNOSUPPORT:    __result = "EAFNOSUPPORT"; break;
#endif /* EAFNOSUPPORT */
#ifdef __EALREADY
	case __EALREADY:        __result = "EALREADY"; break;
#endif /* EALREADY */
#ifdef __EBADMSG
	case __EBADMSG:         __result = "EBADMSG"; break;
#endif /* EBADMSG */
#ifdef __ECANCELED
	case __ECANCELED:       __result = "ECANCELED"; break;
#endif /* ECANCELED */
#ifdef __ECONNABORTED
	case __ECONNABORTED:    __result = "ECONNABORTED"; break;
#endif /* ECONNABORTED */
#ifdef __ECONNREFUSED
	case __ECONNREFUSED:    __result = "ECONNREFUSED"; break;
#endif /* ECONNREFUSED */
#ifdef __ECONNRESET
	case __ECONNRESET:      __result = "ECONNRESET"; break;
#endif /* ECONNRESET */
#ifdef __EDESTADDRREQ
	case __EDESTADDRREQ:    __result = "EDESTADDRREQ"; break;
#endif /* EDESTADDRREQ */
#ifdef __EHOSTUNREACH
	case __EHOSTUNREACH:    __result = "EHOSTUNREACH"; break;
#endif /* EHOSTUNREACH */
#ifdef __EIDRM
	case __EIDRM:           __result = "EIDRM"; break;
#endif /* EIDRM */
#ifdef __EINPROGRESS
	case __EINPROGRESS:     __result = "EINPROGRESS"; break;
#endif /* EINPROGRESS */
#ifdef __EISCONN
	case __EISCONN:         __result = "EISCONN"; break;
#endif /* EISCONN */
#ifdef __ELOOP
	case __ELOOP:           __result = "ELOOP"; break;
#endif /* ELOOP */
#ifdef __EMSGSIZE
	case __EMSGSIZE:        __result = "EMSGSIZE"; break;
#endif /* EMSGSIZE */
#ifdef __ENETDOWN
	case __ENETDOWN:        __result = "ENETDOWN"; break;
#endif /* ENETDOWN */
#ifdef __ENETRESET
	case __ENETRESET:       __result = "ENETRESET"; break;
#endif /* ENETRESET */
#ifdef __ENETUNREACH
	case __ENETUNREACH:     __result = "ENETUNREACH"; break;
#endif /* ENETUNREACH */
#ifdef __ENOBUFS
	case __ENOBUFS:         __result = "ENOBUFS"; break;
#endif /* ENOBUFS */
#ifdef __ENODATA
	case __ENODATA:         __result = "ENODATA"; break;
#endif /* ENODATA */
#ifdef __ENOLINK
	case __ENOLINK:         __result = "ENOLINK"; break;
#endif /* ENOLINK */
#ifdef __ENOMSG
	case __ENOMSG:          __result = "ENOMSG"; break;
#endif /* ENOMSG */
#ifdef __ENOPROTOOPT
	case __ENOPROTOOPT:     __result = "ENOPROTOOPT"; break;
#endif /* ENOPROTOOPT */
#ifdef __ENOSR
	case __ENOSR:           __result = "ENOSR"; break;
#endif /* ENOSR */
#ifdef __ENOSTR
	case __ENOSTR:          __result = "ENOSTR"; break;
#endif /* ENOSTR */
#ifdef __ENOTCONN
	case __ENOTCONN:        __result = "ENOTCONN"; break;
#endif /* ENOTCONN */
#ifdef __ENOTRECOVERABLE
	case __ENOTRECOVERABLE: __result = "ENOTRECOVERABLE"; break;
#endif /* ENOTRECOVERABLE */
#ifdef __ENOTSOCK
	case __ENOTSOCK:        __result = "ENOTSOCK"; break;
#endif /* ENOTSOCK */
#ifdef __ENOTSUP
	case __ENOTSUP:         __result = "ENOTSUP"; break;
#endif /* ENOTSUP */
#ifdef __EOPNOTSUPP
	case __EOPNOTSUPP:      __result = "EOPNOTSUPP"; break;
#endif /* EOPNOTSUPP */
#ifdef __EOTHER
	case __EOTHER:          __result = "EOTHER"; break;
#endif /* EOTHER */
#ifdef __EOVERFLOW
	case __EOVERFLOW:       __result = "EOVERFLOW"; break;
#endif /* EOVERFLOW */
#ifdef __EOWNERDEAD
	case __EOWNERDEAD:      __result = "EOWNERDEAD"; break;
#endif /* EOWNERDEAD */
#ifdef __EPROTO
	case __EPROTO:          __result = "EPROTO"; break;
#endif /* EPROTO */
#ifdef __EPROTONOSUPPORT
	case __EPROTONOSUPPORT: __result = "EPROTONOSUPPORT"; break;
#endif /* EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
	case __EPROTOTYPE:      __result = "EPROTOTYPE"; break;
#endif /* EPROTOTYPE */
#ifdef __ETIME
	case __ETIME:           __result = "ETIME"; break;
#endif /* ETIME */
#ifdef __ETIMEDOUT
	case __ETIMEDOUT:       __result = "ETIMEDOUT"; break;
#endif /* ETIMEDOUT */
#ifdef __ETXTBSY
	case __ETXTBSY:         __result = "ETXTBSY"; break;
#endif /* ETXTBSY */
#ifdef __EFTYPE
	case __EFTYPE:          __result = "EFTYPE"; break;
#endif /* EFTYPE */
#ifdef __ENMFILE
	case __ENMFILE:         __result = "ENMFILE"; break;
#endif /* ENMFILE */
#ifdef __EPFNOSUPPORT
	case __EPFNOSUPPORT:    __result = "EPFNOSUPPORT"; break;
#endif /* EPFNOSUPPORT */
#ifdef __EHOSTDOWN
	case __EHOSTDOWN:       __result = "EHOSTDOWN"; break;
#endif /* EHOSTDOWN */
#ifdef __ETOOMANYREFS
	case __ETOOMANYREFS:    __result = "ETOOMANYREFS"; break;
#endif /* ETOOMANYREFS */
#ifdef __EDQUOT
	case __EDQUOT:          __result = "EDQUOT"; break;
#endif /* EDQUOT */
#ifdef __ESTALE
	case __ESTALE:          __result = "ESTALE"; break;
#endif /* ESTALE */
#ifdef __ENOSHARE
	case __ENOSHARE:        __result = "ENOSHARE"; break;
#endif /* ENOSHARE */
#ifdef __ECASECLASH
	case __ECASECLASH:      __result = "ECASECLASH"; break;
#endif /* ECASECLASH */
#ifdef __ENOTBLK
	case __ENOTBLK:         __result = "ENOTBLK"; break;
#endif /* ENOTBLK */
#ifdef __ECHRNG
	case __ECHRNG:          __result = "ECHRNG"; break;
#endif /* ECHRNG */
#ifdef __EL2NSYNC
	case __EL2NSYNC:        __result = "EL2NSYNC"; break;
#endif /* EL2NSYNC */
#ifdef __EL3HLT
	case __EL3HLT:          __result = "EL3HLT"; break;
#endif /* EL3HLT */
#ifdef __EL3RST
	case __EL3RST:          __result = "EL3RST"; break;
#endif /* EL3RST */
#ifdef __ELNRNG
	case __ELNRNG:          __result = "ELNRNG"; break;
#endif /* ELNRNG */
#ifdef __EUNATCH
	case __EUNATCH:         __result = "EUNATCH"; break;
#endif /* EUNATCH */
#ifdef __ENOCSI
	case __ENOCSI:          __result = "ENOCSI"; break;
#endif /* ENOCSI */
#ifdef __EL2HLT
	case __EL2HLT:          __result = "EL2HLT"; break;
#endif /* EL2HLT */
#ifdef __EBADE
	case __EBADE:           __result = "EBADE"; break;
#endif /* EBADE */
#ifdef __EBADR
	case __EBADR:           __result = "EBADR"; break;
#endif /* EBADR */
#ifdef __EXFULL
	case __EXFULL:          __result = "EXFULL"; break;
#endif /* EXFULL */
#ifdef __ENOANO
	case __ENOANO:          __result = "ENOANO"; break;
#endif /* ENOANO */
#ifdef __EBADRQC
	case __EBADRQC:         __result = "EBADRQC"; break;
#endif /* EBADRQC */
#ifdef __EBADSLT
	case __EBADSLT:         __result = "EBADSLT"; break;
#endif /* EBADSLT */
#ifdef __EBFONT
	case __EBFONT:          __result = "EBFONT"; break;
#endif /* EBFONT */
#ifdef __ENONET
	case __ENONET:          __result = "ENONET"; break;
#endif /* ENONET */
#ifdef __ENOPKG
	case __ENOPKG:          __result = "ENOPKG"; break;
#endif /* ENOPKG */
#ifdef __EREMOTE
	case __EREMOTE:         __result = "EREMOTE"; break;
#endif /* EREMOTE */
#ifdef __EADV
	case __EADV:            __result = "EADV"; break;
#endif /* EADV */
#ifdef __ESRMNT
	case __ESRMNT:          __result = "ESRMNT"; break;
#endif /* ESRMNT */
#ifdef __ECOMM
	case __ECOMM:           __result = "ECOMM"; break;
#endif /* ECOMM */
#ifdef __ELBIN
	case __ELBIN:           __result = "ELBIN)"; break;
#endif /* ELBIN */
#ifdef __EDOTDOT
	case __EDOTDOT:         __result = "EDOTDOT)"; break;
#endif /* EDOTDOT */
#ifdef __ENOTUNIQ
	case __ENOTUNIQ:        __result = "ENOTUNIQ"; break;
#endif /* ENOTUNIQ */
#ifdef __EBADFD
	case __EBADFD:          __result = "EBADFD"; break;
#endif /* EBADFD */
#ifdef __EREMCHG
	case __EREMCHG:         __result = "EREMCHG"; break;
#endif /* EREMCHG */
#ifdef __ELIBACC
	case __ELIBACC:         __result = "ELIBACC"; break;
#endif /* ELIBACC */
#ifdef __ELIBBAD
	case __ELIBBAD:         __result = "ELIBBAD"; break;
#endif /* ELIBBAD */
#ifdef __ELIBSCN
	case __ELIBSCN:         __result = "ELIBSCN"; break;
#endif /* ELIBSCN */
#ifdef __ELIBMAX
	case __ELIBMAX:         __result = "ELIBMAX"; break;
#endif /* ELIBMAX */
#ifdef __ELIBEXEC
	case __ELIBEXEC:        __result = "ELIBEXEC"; break;
#endif /* ELIBEXEC */
#ifdef __ESHUTDOWN
	case __ESHUTDOWN:       __result = "ESHUTDOWN"; break;
#endif /* ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
	case __ESOCKTNOSUPPORT: __result = "ESOCKTNOSUPPORT"; break;
#endif /* ESOCKTNOSUPPORT */
#ifdef __EPROCLIM
	case __EPROCLIM:        __result = "EPROCLIM"; break;
#endif /* EPROCLIM */
#ifdef __EUSERS
	case __EUSERS:          __result = "EUSERS"; break;
#endif /* EUSERS */
#ifdef __ENOMEDIUM
	case __ENOMEDIUM:       __result = "ENOMEDIUM)"; break;
#endif /* ENOMEDIUM */
#ifdef __ESTRPIPE
	case __ESTRPIPE:        __result = "ESTRPIPE"; break;
#endif /* ESTRPIPE */
#ifdef __EMULTIHOP
	case __EMULTIHOP:       __result = "EMULTIHOP"; break;
#endif /* EMULTIHOP */
#ifdef __ERESTART
	case __ERESTART:        __result = "ERESTART"; break;
#endif /* ERESTART */
#ifdef __EUCLEAN
	case __EUCLEAN:         __result = "EUCLEAN"; break;
#endif /* EUCLEAN */
#ifdef __ENOTNAM
	case __ENOTNAM:         __result = "ENOTNAM"; break;
#endif /* ENOTNAM */
#ifdef __ENAVAIL
	case __ENAVAIL:         __result = "ENAVAIL"; break;
#endif /* ENAVAIL */
#ifdef __EISNAM
	case __EISNAM:          __result = "EISNAM"; break;
#endif /* EISNAM */
#ifdef __EREMOTEIO
	case __EREMOTEIO:       __result = "EREMOTEIO"; break;
#endif /* EREMOTEIO */
#ifdef __EMEDIUMTYPE
	case __EMEDIUMTYPE:     __result = "EMEDIUMTYPE"; break;
#endif /* EMEDIUMTYPE */
#ifdef __ENOKEY
	case __ENOKEY:          __result = "ENOKEY"; break;
#endif /* ENOKEY */
#ifdef __EKEYEXPIRED
	case __EKEYEXPIRED:     __result = "EKEYEXPIRED"; break;
#endif /* EKEYEXPIRED */
#ifdef __EKEYREVOKED
	case __EKEYREVOKED:     __result = "EKEYREVOKED"; break;
#endif /* EKEYREVOKED */
#ifdef __EKEYREJECTED
	case __EKEYREJECTED:    __result = "EKEYREJECTED"; break;
#endif /* EKEYREJECTED */
#ifdef __ERFKILL
	case __ERFKILL:         __result = "ERFKILL"; break;
#endif /* ERFKILL */
#ifdef __EHWPOISON
	case __EHWPOISON:       __result = "EHWPOISON"; break;
#endif /* EHWPOISON */
#if defined(__STRUNCATE) && (!defined(__ERANGE) || __STRUNCATE != __ERANGE)
	case __STRUNCATE:       __result = "STRUNCATE"; break;
#endif /* STRUNCATE && (!ERANGE || STRUNCATE != ERANGE) */
#if defined(__EWOULDBLOCK) && (!defined(__EAGAIN) || __EWOULDBLOCK != __EAGAIN)
	case __EWOULDBLOCK:     __result = "EWOULDBLOCK"; break;
#endif /* EWOULDBLOCK && (!EAGAIN || EWOULDBLOCK != EAGAIN) */
#if defined(__EDEADLK) && (!defined(__EDEADLOCK) || __EDEADLOCK != __EDEADLK)
	case __EDEADLK:         __result = "EDEADLK"; break;
#endif /* EDEADLK && (!EDEADLOCK || EDEADLOCK != EDEADLK) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strerrorname_s_defined */
