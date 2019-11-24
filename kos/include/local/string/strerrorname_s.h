/* HASH CRC-32:0x94d985ff */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strerrorname_s_defined
#define __local_strerrorname_s_defined 1
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerrorname_s) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(strerrorname_s))(int __errnum) {
#line 3313 "kos/src/libc/magic/string.c"
	char const *__result;
	switch (__errnum) {

#ifdef __EPERM
	case __EPERM:           __result = "EPERM"; break;
#endif /* __EPERM */
#ifdef __ENOENT
	case __ENOENT:          __result = "ENOENT"; break;
#endif /* __ENOENT */
#ifdef __ESRCH
	case __ESRCH:           __result = "ESRCH"; break;
#endif /* __ESRCH */
#ifdef __EINTR
	case __EINTR:           __result = "EINTR"; break;
#endif /* __EINTR */
#ifdef __EIO
	case __EIO:             __result = "EIO"; break;
#endif /* __EIO */
#ifdef __ENXIO
	case __ENXIO:           __result = "ENXIO"; break;
#endif /* __ENXIO */
#ifdef __E2BIG
	case __E2BIG:           __result = "E2BIG"; break;
#endif /* __E2BIG */
#ifdef __ENOEXEC
	case __ENOEXEC:         __result = "ENOEXEC"; break;
#endif /* __ENOEXEC */
#ifdef __EBADF
	case __EBADF:           __result = "EBADF"; break;
#endif /* __EBADF */
#ifdef __ECHILD
	case __ECHILD:          __result = "ECHILD"; break;
#endif /* __ECHILD */
#ifdef __EAGAIN
	case __EAGAIN:          __result = "EAGAIN"; break;
#endif /* __EAGAIN */
#ifdef __ENOMEM
	case __ENOMEM:          __result = "ENOMEM"; break;
#endif /* __ENOMEM */
#ifdef __EACCES
	case __EACCES:          __result = "EACCES"; break;
#endif /* __EACCES */
#ifdef __EFAULT
	case __EFAULT:          __result = "EFAULT"; break;
#endif /* __EFAULT */
#ifdef __EBUSY
	case __EBUSY:           __result = "EBUSY"; break;
#endif /* __EBUSY */
#ifdef __EEXIST
	case __EEXIST:          __result = "EEXIST"; break;
#endif /* __EEXIST */
#ifdef __EXDEV
	case __EXDEV:           __result = "EXDEV"; break;
#endif /* __EXDEV */
#ifdef __ENODEV
	case __ENODEV:          __result = "ENODEV"; break;
#endif /* __ENODEV */
#ifdef __ENOTDIR
	case __ENOTDIR:         __result = "ENOTDIR"; break;
#endif /* __ENOTDIR */
#ifdef __EISDIR
	case __EISDIR:          __result = "EISDIR"; break;
#endif /* __EISDIR */
#ifdef __ENFILE
	case __ENFILE:          __result = "ENFILE"; break;
#endif /* __ENFILE */
#ifdef __EMFILE
	case __EMFILE:          __result = "EMFILE"; break;
#endif /* __EMFILE */
#ifdef __ENOTTY
	case __ENOTTY:          __result = "ENOTTY"; break;
#endif /* __ENOTTY */
#ifdef __EFBIG
	case __EFBIG:           __result = "EFBIG"; break;
#endif /* __EFBIG */
#ifdef __ENOSPC
	case __ENOSPC:          __result = "ENOSPC"; break;
#endif /* __ENOSPC */
#ifdef __ESPIPE
	case __ESPIPE:          __result = "ESPIPE"; break;
#endif /* __ESPIPE */
#ifdef __EROFS
	case __EROFS:           __result = "EROFS"; break;
#endif /* __EROFS */
#ifdef __EMLINK
	case __EMLINK:          __result = "EMLINK"; break;
#endif /* __EMLINK */
#ifdef __EPIPE
	case __EPIPE:           __result = "EPIPE"; break;
#endif /* __EPIPE */
#ifdef __EDOM
	case __EDOM:            __result = "EDOM"; break;
#endif /* __EDOM */
#ifdef __ENAMETOOLONG
	case __ENAMETOOLONG:    __result = "ENAMETOOLONG"; break;
#endif /* __ENAMETOOLONG */
#ifdef __ENOLCK
	case __ENOLCK:          __result = "ENOLCK"; break;
#endif /* __ENOLCK */
#ifdef __ENOSYS
	case __ENOSYS:          __result = "ENOSYS"; break;
#endif /* __ENOSYS */
#ifdef __ENOTEMPTY
	case __ENOTEMPTY:       __result = "ENOTEMPTY"; break;
#endif /* __ENOTEMPTY */
#ifdef __EINVAL
	case __EINVAL:          __result = "EINVAL"; break;
#endif /* __EINVAL */
#ifdef __ERANGE
	case __ERANGE:          __result = "ERANGE"; break;
#endif /* __ERANGE */
#ifdef __EILSEQ
	case __EILSEQ:          __result = "EILSEQ"; break;
#endif /* __EILSEQ */
#ifdef __EDEADLOCK
	case __EDEADLOCK:       __result = "EDEADLOCK"; break;
#endif /* __EDEADLOCK */
#ifdef __EADDRINUSE
	case __EADDRINUSE:      __result = "EADDRINUSE"; break;
#endif /* __EADDRINUSE */
#ifdef __EADDRNOTAVAIL
	case __EADDRNOTAVAIL:   __result = "EADDRNOTAVAIL"; break;
#endif /* __EADDRNOTAVAIL */
#ifdef __EAFNOSUPPORT
	case __EAFNOSUPPORT:    __result = "EAFNOSUPPORT"; break;
#endif /* __EAFNOSUPPORT */
#ifdef __EALREADY
	case __EALREADY:        __result = "EALREADY"; break;
#endif /* __EALREADY */
#ifdef __EBADMSG
	case __EBADMSG:         __result = "EBADMSG"; break;
#endif /* __EBADMSG */
#ifdef __ECANCELED
	case __ECANCELED:       __result = "ECANCELED"; break;
#endif /* __ECANCELED */
#ifdef __ECONNABORTED
	case __ECONNABORTED:    __result = "ECONNABORTED"; break;
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
	case __ECONNREFUSED:    __result = "ECONNREFUSED"; break;
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
	case __ECONNRESET:      __result = "ECONNRESET"; break;
#endif /* __ECONNRESET */
#ifdef __EDESTADDRREQ
	case __EDESTADDRREQ:    __result = "EDESTADDRREQ"; break;
#endif /* __EDESTADDRREQ */
#ifdef __EHOSTUNREACH
	case __EHOSTUNREACH:    __result = "EHOSTUNREACH"; break;
#endif /* __EHOSTUNREACH */
#ifdef __EIDRM
	case __EIDRM:           __result = "EIDRM"; break;
#endif /* __EIDRM */
#ifdef __EINPROGRESS
	case __EINPROGRESS:     __result = "EINPROGRESS"; break;
#endif /* __EINPROGRESS */
#ifdef __EISCONN
	case __EISCONN:         __result = "EISCONN"; break;
#endif /* __EISCONN */
#ifdef __ELOOP
	case __ELOOP:           __result = "ELOOP"; break;
#endif /* __ELOOP */
#ifdef __EMSGSIZE
	case __EMSGSIZE:        __result = "EMSGSIZE"; break;
#endif /* __EMSGSIZE */
#ifdef __ENETDOWN
	case __ENETDOWN:        __result = "ENETDOWN"; break;
#endif /* __ENETDOWN */
#ifdef __ENETRESET
	case __ENETRESET:       __result = "ENETRESET"; break;
#endif /* __ENETRESET */
#ifdef __ENETUNREACH
	case __ENETUNREACH:     __result = "ENETUNREACH"; break;
#endif /* __ENETUNREACH */
#ifdef __ENOBUFS
	case __ENOBUFS:         __result = "ENOBUFS"; break;
#endif /* __ENOBUFS */
#ifdef __ENODATA
	case __ENODATA:         __result = "ENODATA"; break;
#endif /* __ENODATA */
#ifdef __ENOLINK
	case __ENOLINK:         __result = "ENOLINK"; break;
#endif /* __ENOLINK */
#ifdef __ENOMSG
	case __ENOMSG:          __result = "ENOMSG"; break;
#endif /* __ENOMSG */
#ifdef __ENOPROTOOPT
	case __ENOPROTOOPT:     __result = "ENOPROTOOPT"; break;
#endif /* __ENOPROTOOPT */
#ifdef __ENOSR
	case __ENOSR:           __result = "ENOSR"; break;
#endif /* __ENOSR */
#ifdef __ENOSTR
	case __ENOSTR:          __result = "ENOSTR"; break;
#endif /* __ENOSTR */
#ifdef __ENOTCONN
	case __ENOTCONN:        __result = "ENOTCONN"; break;
#endif /* __ENOTCONN */
#ifdef __ENOTRECOVERABLE
	case __ENOTRECOVERABLE: __result = "ENOTRECOVERABLE"; break;
#endif /* __ENOTRECOVERABLE */
#ifdef __ENOTSOCK
	case __ENOTSOCK:        __result = "ENOTSOCK"; break;
#endif /* __ENOTSOCK */
#ifdef __ENOTSUP
	case __ENOTSUP:         __result = "ENOTSUP"; break;
#endif /* __ENOTSUP */
#ifdef __EOPNOTSUPP
	case __EOPNOTSUPP:      __result = "EOPNOTSUPP"; break;
#endif /* __EOPNOTSUPP */
#ifdef __EOTHER
	case __EOTHER:          __result = "EOTHER"; break;
#endif /* __EOTHER */
#ifdef __EOVERFLOW
	case __EOVERFLOW:       __result = "EOVERFLOW"; break;
#endif /* __EOVERFLOW */
#ifdef __EOWNERDEAD
	case __EOWNERDEAD:      __result = "EOWNERDEAD"; break;
#endif /* __EOWNERDEAD */
#ifdef __EPROTO
	case __EPROTO:          __result = "EPROTO"; break;
#endif /* __EPROTO */
#ifdef __EPROTONOSUPPORT
	case __EPROTONOSUPPORT: __result = "EPROTONOSUPPORT"; break;
#endif /* __EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
	case __EPROTOTYPE:      __result = "EPROTOTYPE"; break;
#endif /* __EPROTOTYPE */
#ifdef __ETIME
	case __ETIME:           __result = "ETIME"; break;
#endif /* __ETIME */
#ifdef __ETIMEDOUT
	case __ETIMEDOUT:       __result = "ETIMEDOUT"; break;
#endif /* __ETIMEDOUT */
#ifdef __ETXTBSY
	case __ETXTBSY:         __result = "ETXTBSY"; break;
#endif /* __ETXTBSY */
#ifdef __EFTYPE
	case __EFTYPE:          __result = "EFTYPE"; break;
#endif /* __EFTYPE */
#ifdef __ENMFILE
	case __ENMFILE:         __result = "ENMFILE"; break;
#endif /* __ENMFILE */
#ifdef __EPFNOSUPPORT
	case __EPFNOSUPPORT:    __result = "EPFNOSUPPORT"; break;
#endif /* __EPFNOSUPPORT */
#ifdef __EHOSTDOWN
	case __EHOSTDOWN:       __result = "EHOSTDOWN"; break;
#endif /* __EHOSTDOWN */
#ifdef __ETOOMANYREFS
	case __ETOOMANYREFS:    __result = "ETOOMANYREFS"; break;
#endif /* __ETOOMANYREFS */
#ifdef __EDQUOT
	case __EDQUOT:          __result = "EDQUOT"; break;
#endif /* __EDQUOT */
#ifdef __ESTALE
	case __ESTALE:          __result = "ESTALE"; break;
#endif /* __ESTALE */
#ifdef __ENOSHARE
	case __ENOSHARE:        __result = "ENOSHARE"; break;
#endif /* __ENOSHARE */
#ifdef __ECASECLASH
	case __ECASECLASH:      __result = "ECASECLASH"; break;
#endif /* __ECASECLASH */
#ifdef __ENOTBLK
	case __ENOTBLK:         __result = "ENOTBLK"; break;
#endif /* __ENOTBLK */
#ifdef __ECHRNG
	case __ECHRNG:          __result = "ECHRNG"; break;
#endif /* __ECHRNG */
#ifdef __EL2NSYNC
	case __EL2NSYNC:        __result = "EL2NSYNC"; break;
#endif /* __EL2NSYNC */
#ifdef __EL3HLT
	case __EL3HLT:          __result = "EL3HLT"; break;
#endif /* __EL3HLT */
#ifdef __EL3RST
	case __EL3RST:          __result = "EL3RST"; break;
#endif /* __EL3RST */
#ifdef __ELNRNG
	case __ELNRNG:          __result = "ELNRNG"; break;
#endif /* __ELNRNG */
#ifdef __EUNATCH
	case __EUNATCH:         __result = "EUNATCH"; break;
#endif /* __EUNATCH */
#ifdef __ENOCSI
	case __ENOCSI:          __result = "ENOCSI"; break;
#endif /* __ENOCSI */
#ifdef __EL2HLT
	case __EL2HLT:          __result = "EL2HLT"; break;
#endif /* __EL2HLT */
#ifdef __EBADE
	case __EBADE:           __result = "EBADE"; break;
#endif /* __EBADE */
#ifdef __EBADR
	case __EBADR:           __result = "EBADR"; break;
#endif /* __EBADR */
#ifdef __EXFULL
	case __EXFULL:          __result = "EXFULL"; break;
#endif /* __EXFULL */
#ifdef __ENOANO
	case __ENOANO:          __result = "ENOANO"; break;
#endif /* __ENOANO */
#ifdef __EBADRQC
	case __EBADRQC:         __result = "EBADRQC"; break;
#endif /* __EBADRQC */
#ifdef __EBADSLT
	case __EBADSLT:         __result = "EBADSLT"; break;
#endif /* __EBADSLT */
#ifdef __EBFONT
	case __EBFONT:          __result = "EBFONT"; break;
#endif /* __EBFONT */
#ifdef __ENONET
	case __ENONET:          __result = "ENONET"; break;
#endif /* __ENONET */
#ifdef __ENOPKG
	case __ENOPKG:          __result = "ENOPKG"; break;
#endif /* __ENOPKG */
#ifdef __EREMOTE
	case __EREMOTE:         __result = "EREMOTE"; break;
#endif /* __EREMOTE */
#ifdef __EADV
	case __EADV:            __result = "EADV"; break;
#endif /* __EADV */
#ifdef __ESRMNT
	case __ESRMNT:          __result = "ESRMNT"; break;
#endif /* __ESRMNT */
#ifdef __ECOMM
	case __ECOMM:           __result = "ECOMM"; break;
#endif /* __ECOMM */
#ifdef __ELBIN
	case __ELBIN:           __result = "ELBIN)"; break;
#endif /* __ELBIN */
#ifdef __EDOTDOT
	case __EDOTDOT:         __result = "EDOTDOT)"; break;
#endif /* __EDOTDOT */
#ifdef __ENOTUNIQ
	case __ENOTUNIQ:        __result = "ENOTUNIQ"; break;
#endif /* __ENOTUNIQ */
#ifdef __EBADFD
	case __EBADFD:          __result = "EBADFD"; break;
#endif /* __EBADFD */
#ifdef __EREMCHG
	case __EREMCHG:         __result = "EREMCHG"; break;
#endif /* __EREMCHG */
#ifdef __ELIBACC
	case __ELIBACC:         __result = "ELIBACC"; break;
#endif /* __ELIBACC */
#ifdef __ELIBBAD
	case __ELIBBAD:         __result = "ELIBBAD"; break;
#endif /* __ELIBBAD */
#ifdef __ELIBSCN
	case __ELIBSCN:         __result = "ELIBSCN"; break;
#endif /* __ELIBSCN */
#ifdef __ELIBMAX
	case __ELIBMAX:         __result = "ELIBMAX"; break;
#endif /* __ELIBMAX */
#ifdef __ELIBEXEC
	case __ELIBEXEC:        __result = "ELIBEXEC"; break;
#endif /* __ELIBEXEC */
#ifdef __ESHUTDOWN
	case __ESHUTDOWN:       __result = "ESHUTDOWN"; break;
#endif /* __ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
	case __ESOCKTNOSUPPORT: __result = "ESOCKTNOSUPPORT"; break;
#endif /* __ESOCKTNOSUPPORT */
#ifdef __EPROCLIM
	case __EPROCLIM:        __result = "EPROCLIM"; break;
#endif /* __EPROCLIM */
#ifdef __EUSERS
	case __EUSERS:          __result = "EUSERS"; break;
#endif /* __EUSERS */
#ifdef __ENOMEDIUM
	case __ENOMEDIUM:       __result = "ENOMEDIUM)"; break;
#endif /* __ENOMEDIUM */
#ifdef __ESTRPIPE
	case __ESTRPIPE:        __result = "ESTRPIPE"; break;
#endif /* __ESTRPIPE */
#ifdef __EMULTIHOP
	case __EMULTIHOP:       __result = "EMULTIHOP"; break;
#endif /* __EMULTIHOP */
#ifdef __ERESTART
	case __ERESTART:        __result = "ERESTART"; break;
#endif /* __ERESTART */
#ifdef __EUCLEAN
	case __EUCLEAN:         __result = "EUCLEAN"; break;
#endif /* __EUCLEAN */
#ifdef __ENOTNAM
	case __ENOTNAM:         __result = "ENOTNAM"; break;
#endif /* __ENOTNAM */
#ifdef __ENAVAIL
	case __ENAVAIL:         __result = "ENAVAIL"; break;
#endif /* __ENAVAIL */
#ifdef __EISNAM
	case __EISNAM:          __result = "EISNAM"; break;
#endif /* __EISNAM */
#ifdef __EREMOTEIO
	case __EREMOTEIO:       __result = "EREMOTEIO"; break;
#endif /* __EREMOTEIO */
#ifdef __EMEDIUMTYPE
	case __EMEDIUMTYPE:     __result = "EMEDIUMTYPE"; break;
#endif /* __EMEDIUMTYPE */
#ifdef __ENOKEY
	case __ENOKEY:          __result = "ENOKEY"; break;
#endif /* __ENOKEY */
#ifdef __EKEYEXPIRED
	case __EKEYEXPIRED:     __result = "EKEYEXPIRED"; break;
#endif /* __EKEYEXPIRED */
#ifdef __EKEYREVOKED
	case __EKEYREVOKED:     __result = "EKEYREVOKED"; break;
#endif /* __EKEYREVOKED */
#ifdef __EKEYREJECTED
	case __EKEYREJECTED:    __result = "EKEYREJECTED"; break;
#endif /* __EKEYREJECTED */
#ifdef __ERFKILL
	case __ERFKILL:         __result = "ERFKILL"; break;
#endif /* __ERFKILL */
#ifdef __EHWPOISON
	case __EHWPOISON:       __result = "EHWPOISON"; break;
#endif /* __EHWPOISON */
#if defined(__STRUNCATE) && (!defined(__ERANGE) || __STRUNCATE != __ERANGE)
	case __STRUNCATE:       __result = "STRUNCATE"; break;
#endif /* __STRUNCATE && (!__ERANGE || __STRUNCATE != __ERANGE) */
#if defined(__EWOULDBLOCK) && (!defined(__EAGAIN) || __EWOULDBLOCK != __EAGAIN)
	case __EWOULDBLOCK:     __result = "EWOULDBLOCK"; break;
#endif /* __EWOULDBLOCK && (!__EAGAIN || __EWOULDBLOCK != __EAGAIN) */
#if defined(__EDEADLK) && (!defined(__EDEADLOCK) || __EDEADLOCK != __EDEADLK)
	case __EDEADLK:         __result = "EDEADLK"; break;
#endif /* __EDEADLK && (!__EDEADLOCK || __EDEADLOCK != __EDEADLK) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strerrorname_s_defined */
