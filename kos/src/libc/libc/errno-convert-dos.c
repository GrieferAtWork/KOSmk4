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
#ifndef GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C
#define GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <parts/errno.h>
#include <parts/dos/errno.h>

#include "errno.h"

DECL_BEGIN

/************************************************************************/
/* DOS/NT                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(errno_nt2kos, libd_errno_nt2kos);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_nt2kos")
NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2kos)(/*nt*/ errno_t value) {
	return libd_errno_dos2kos(libd_errno_nt2dos(value));
}

DEFINE_PUBLIC_ALIAS(errno_kos2nt, libd_errno_kos2nt);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_kos2nt")
NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2nt)(/*kos*/ errno_t value) {
	return libd_errno_dos2nt(libd_errno_kos2dos(value));
}

DEFINE_PUBLIC_ALIAS(errno_nt2dos, libd_errno_nt2dos);
DEFINE_INTERN_ALIAS(libd__dosmaperr, libd_errno_nt2dos);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_nt2dos")
NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2dos)(/*nt*/ errno_t value) {
	/* TODO */
	return value;
}

DEFINE_PUBLIC_ALIAS(errno_dos2nt, libd_errno_dos2nt);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_dos2nt")
NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2nt)(/*kos*/ errno_t value) {
	/* TODO */
	return value;
}


DEFINE_PUBLIC_ALIAS(errno_kos2dos, libd_errno_dos2kos);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_kos2dos")
NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2dos)(/*kos*/ errno_t value) {
	errno_t result;
	switch (value) {
	case EPERM:           result = __DOS_EPERM;           break; /* Operation not permitted */
	case ENOENT:          result = __DOS_ENOENT;          break; /* No such file or directory */
	case ESRCH:           result = __DOS_ESRCH;           break; /* No such process */
	case EINTR:           result = __DOS_EINTR;           break; /* Interrupted system call */
	case EIO:             result = __DOS_EIO;             break; /* I/O error */
	case ENXIO:           result = __DOS_ENXIO;           break; /* No such device or address */
	case E2BIG:           result = __DOS_E2BIG;           break; /* Argument list too long */
	case ENOEXEC:         result = __DOS_ENOEXEC;         break; /* Exec format error */
	case EBADF:           result = __DOS_EBADF;           break; /* Bad file number */
	case ECHILD:          result = __DOS_ECHILD;          break; /* No child processes */
	case EAGAIN:          result = __DOS_EAGAIN;          break; /* Try again */
	case ENOMEM:          result = __DOS_ENOMEM;          break; /* Out of memory */
	case EACCES:          result = __DOS_EACCES;          break; /* Permission denied */
	case EFAULT:          result = __DOS_EFAULT;          break; /* Bad address */
	case EBUSY:           result = __DOS_EBUSY;           break; /* Device or resource busy */
	case EEXIST:          result = __DOS_EEXIST;          break; /* File exists */
	case EXDEV:           result = __DOS_EXDEV;           break; /* Cross-device link */
	case ENODEV:          result = __DOS_ENODEV;          break; /* No such device */
	case ENOTDIR:         result = __DOS_ENOTDIR;         break; /* Not a directory */
	case EISDIR:          result = __DOS_EISDIR;          break; /* Is a directory */
	case ENFILE:          result = __DOS_ENFILE;          break; /* File table overflow */
	case EMFILE:          result = __DOS_EMFILE;          break; /* Too many open files */
	case ENOTTY:          result = __DOS_ENOTTY;          break; /* Not a typewriter */
	case EFBIG:           result = __DOS_EFBIG;           break; /* File too large */
	case ENOSPC:          result = __DOS_ENOSPC;          break; /* No space left on device */
	case ESPIPE:          result = __DOS_ESPIPE;          break; /* Illegal seek */
	case EROFS:           result = __DOS_EROFS;           break; /* Read-only file system */
	case EMLINK:          result = __DOS_EMLINK;          break; /* Too many links */
	case EPIPE:           result = __DOS_EPIPE;           break; /* Broken pipe */
	case EDOM:            result = __DOS_EDOM;            break; /* Math argument out of domain of func */
	case EDEADLK:         result = __DOS_EDEADLK;         break; /* Resource deadlock would occur */
	case ENAMETOOLONG:    result = __DOS_ENAMETOOLONG;    break; /* File name too long */
	case ENOLCK:          result = __DOS_ENOLCK;          break; /* No record locks available */
	case ENOSYS:          result = __DOS_ENOSYS;          break; /* Function not implemented */
	case ENOTEMPTY:       result = __DOS_ENOTEMPTY;       break; /* Directory not empty */
	case EINVAL:          result = __DOS_EINVAL;          break; /* Invalid argument */
	case ERANGE:          result = __DOS_ERANGE;          break; /* Math result not representable */
	case EILSEQ:          result = __DOS_EILSEQ;          break; /* Illegal byte sequence */
	case EADDRINUSE:      result = __DOS_EADDRINUSE;      break; /* Address already in use */
	case EADDRNOTAVAIL:   result = __DOS_EADDRNOTAVAIL;   break; /* Cannot assign requested address */
	case EAFNOSUPPORT:    result = __DOS_EAFNOSUPPORT;    break; /* Address family not supported by protocol */
	case EALREADY:        result = __DOS_EALREADY;        break; /* Operation already in progress */
	case EBADMSG:         result = __DOS_EBADMSG;         break; /* Not a data message */
	case ECANCELED:       result = __DOS_ECANCELED;       break; /* Operation Canceled */
	case ECONNABORTED:    result = __DOS_ECONNABORTED;    break; /* Software caused connection abort */
	case ECONNREFUSED:    result = __DOS_ECONNREFUSED;    break; /* Connection refused */
	case ECONNRESET:      result = __DOS_ECONNRESET;      break; /* Connection reset by peer */
	case EDESTADDRREQ:    result = __DOS_EDESTADDRREQ;    break; /* Destination address required */
	case EHOSTUNREACH:    result = __DOS_EHOSTUNREACH;    break; /* No route to host */
	case EIDRM:           result = __DOS_EIDRM;           break; /* Identifier removed */
	case EINPROGRESS:     result = __DOS_EINPROGRESS;     break; /* Operation now in progress */
	case EISCONN:         result = __DOS_EISCONN;         break; /* Transport endpoint is already connected */
	case ELOOP:           result = __DOS_ELOOP;           break; /* Too many symbolic links encountered */
	case EMSGSIZE:        result = __DOS_EMSGSIZE;        break; /* Message too long */
	case ENETDOWN:        result = __DOS_ENETDOWN;        break; /* Network is down */
	case ENETRESET:       result = __DOS_ENETRESET;       break; /* Network dropped connection because of reset */
	case ENETUNREACH:     result = __DOS_ENETUNREACH;     break; /* Network is unreachable */
	case ENOBUFS:         result = __DOS_ENOBUFS;         break; /* No buffer space available */
	case ENODATA:         result = __DOS_ENODATA;         break; /* No data available */
	case ENOLINK:         result = __DOS_ENOLINK;         break; /* Link has been severed */
	case ENOMSG:          result = __DOS_ENOMSG;          break; /* No message of desired type */
	case ENOPROTOOPT:     result = __DOS_ENOPROTOOPT;     break; /* Protocol not available */
	case ENOSR:           result = __DOS_ENOSR;           break; /* Out of streams resources */
	case ENOSTR:          result = __DOS_ENOSTR;          break; /* Device not a stream */
	case ENOTCONN:        result = __DOS_ENOTCONN;        break; /* Transport endpoint is not connected */
	case ENOTRECOVERABLE: result = __DOS_ENOTRECOVERABLE; break; /* State not recoverable */
	case ENOTSOCK:        result = __DOS_ENOTSOCK;        break; /* Socket operation on non-socket */
	case EOPNOTSUPP:      result = __DOS_EOPNOTSUPP;      break; /* Operation not supported on transport endpoint */
	case EOVERFLOW:       result = __DOS_EOVERFLOW;       break; /* Value too large for defined data type */
	case EOWNERDEAD:      result = __DOS_EOWNERDEAD;      break; /* Owner died */
	case EPROTO:          result = __DOS_EPROTO;          break; /* Protocol error */
	case EPROTONOSUPPORT: result = __DOS_EPROTONOSUPPORT; break; /* Protocol not supported */
	case EPROTOTYPE:      result = __DOS_EPROTOTYPE;      break; /* Protocol wrong type for socket */
	case ETIME:           result = __DOS_ETIME;           break; /* Timer expired */
	case ETIMEDOUT:       result = __DOS_ETIMEDOUT;       break; /* Connection timed out */
	case ETXTBSY:         result = __DOS_ETXTBSY;         break; /* Text file busy */
	default:
		result = EPERM;
		break;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_dos2kos, libd_errno_dos2kos);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_dos2kos")
NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2kos)(/*dos*/ errno_t value) {
	errno_t result;
	switch (value) {
	case __DOS_EPERM:           result = EPERM;           break; /* Operation not permitted */
	case __DOS_ENOENT:          result = ENOENT;          break; /* No such file or directory */
	case __DOS_ESRCH:           result = ESRCH;           break; /* No such process */
	case __DOS_EINTR:           result = EINTR;           break; /* Interrupted system call */
	case __DOS_EIO:             result = EIO;             break; /* I/O error */
	case __DOS_ENXIO:           result = ENXIO;           break; /* No such device or address */
	case __DOS_E2BIG:           result = E2BIG;           break; /* Argument list too long */
	case __DOS_ENOEXEC:         result = ENOEXEC;         break; /* Exec format error */
	case __DOS_EBADF:           result = EBADF;           break; /* Bad file number */
	case __DOS_ECHILD:          result = ECHILD;          break; /* No child processes */
	case __DOS_EAGAIN:          result = EAGAIN;          break; /* Try again */
	case __DOS_ENOMEM:          result = ENOMEM;          break; /* Out of memory */
	case __DOS_EACCES:          result = EACCES;          break; /* Permission denied */
	case __DOS_EFAULT:          result = EFAULT;          break; /* Bad address */
	case __DOS_EBUSY:           result = EBUSY;           break; /* Device or resource busy */
	case __DOS_EEXIST:          result = EEXIST;          break; /* File exists */
	case __DOS_EXDEV:           result = EXDEV;           break; /* Cross-device link */
	case __DOS_ENODEV:          result = ENODEV;          break; /* No such device */
	case __DOS_ENOTDIR:         result = ENOTDIR;         break; /* Not a directory */
	case __DOS_EISDIR:          result = EISDIR;          break; /* Is a directory */
	case __DOS_ENFILE:          result = ENFILE;          break; /* File table overflow */
	case __DOS_EMFILE:          result = EMFILE;          break; /* Too many open files */
	case __DOS_ENOTTY:          result = ENOTTY;          break; /* Not a typewriter */
	case __DOS_EFBIG:           result = EFBIG;           break; /* File too large */
	case __DOS_ENOSPC:          result = ENOSPC;          break; /* No space left on device */
	case __DOS_ESPIPE:          result = ESPIPE;          break; /* Illegal seek */
	case __DOS_EROFS:           result = EROFS;           break; /* Read-only file system */
	case __DOS_EMLINK:          result = EMLINK;          break; /* Too many links */
	case __DOS_EPIPE:           result = EPIPE;           break; /* Broken pipe */
	case __DOS_EDOM:            result = EDOM;            break; /* Math argument out of domain of func */
	case __DOS_EDEADLK:         result = EDEADLK;         break; /* Resource deadlock would occur */
	case __DOS_ENAMETOOLONG:    result = ENAMETOOLONG;    break; /* File name too long */
	case __DOS_ENOLCK:          result = ENOLCK;          break; /* No record locks available */
	case __DOS_ENOSYS:          result = ENOSYS;          break; /* Function not implemented */
	case __DOS_ENOTEMPTY:       result = ENOTEMPTY;       break; /* Directory not empty */
	case __DOS_EINVAL:          result = EINVAL;          break; /* Invalid argument */
	case __DOS_STRUNCATE:                                        /* Truncated */
	case __DOS_ERANGE:          result = ERANGE;          break; /* Math result not representable */
	case __DOS_EILSEQ:          result = EILSEQ;          break; /* Illegal byte sequence */
	case __DOS_EADDRINUSE:      result = EADDRINUSE;      break; /* Address already in use */
	case __DOS_EADDRNOTAVAIL:   result = EADDRNOTAVAIL;   break; /* Cannot assign requested address */
	case __DOS_EAFNOSUPPORT:    result = EAFNOSUPPORT;    break; /* Address family not supported by protocol */
	case __DOS_EALREADY:        result = EALREADY;        break; /* Operation already in progress */
	case __DOS_EBADMSG:         result = EBADMSG;         break; /* Not a data message */
	case __DOS_ECANCELED:       result = ECANCELED;       break; /* Operation Canceled */
	case __DOS_ECONNABORTED:    result = ECONNABORTED;    break; /* Software caused connection abort */
	case __DOS_ECONNREFUSED:    result = ECONNREFUSED;    break; /* Connection refused */
	case __DOS_ECONNRESET:      result = ECONNRESET;      break; /* Connection reset by peer */
	case __DOS_EDESTADDRREQ:    result = EDESTADDRREQ;    break; /* Destination address required */
	case __DOS_EHOSTUNREACH:    result = EHOSTUNREACH;    break; /* No route to host */
	case __DOS_EIDRM:           result = EIDRM;           break; /* Identifier removed */
	case __DOS_EINPROGRESS:     result = EINPROGRESS;     break; /* Operation now in progress */
	case __DOS_EISCONN:         result = EISCONN;         break; /* Transport endpoint is already connected */
	case __DOS_ELOOP:           result = ELOOP;           break; /* Too many symbolic links encountered */
	case __DOS_EMSGSIZE:        result = EMSGSIZE;        break; /* Message too long */
	case __DOS_ENETDOWN:        result = ENETDOWN;        break; /* Network is down */
	case __DOS_ENETRESET:       result = ENETRESET;       break; /* Network dropped connection because of reset */
	case __DOS_ENETUNREACH:     result = ENETUNREACH;     break; /* Network is unreachable */
	case __DOS_ENOBUFS:         result = ENOBUFS;         break; /* No buffer space available */
	case __DOS_ENODATA:         result = ENODATA;         break; /* No data available */
	case __DOS_ENOLINK:         result = ENOLINK;         break; /* Link has been severed */
	case __DOS_ENOMSG:          result = ENOMSG;          break; /* No message of desired type */
	case __DOS_ENOPROTOOPT:     result = ENOPROTOOPT;     break; /* Protocol not available */
	case __DOS_ENOSR:           result = ENOSR;           break; /* Out of streams resources */
	case __DOS_ENOSTR:          result = ENOSTR;          break; /* Device not a stream */
	case __DOS_ENOTCONN:        result = ENOTCONN;        break; /* Transport endpoint is not connected */
	case __DOS_ENOTRECOVERABLE: result = ENOTRECOVERABLE; break; /* State not recoverable */
	case __DOS_ENOTSOCK:        result = ENOTSOCK;        break; /* Socket operation on non-socket */
	case __DOS_ENOTSUP:         result = ENOTSUP;         break; /* Not supported */
	case __DOS_EOPNOTSUPP:      result = EOPNOTSUPP;      break; /* Operation not supported on transport endpoint */
	case __DOS_EOVERFLOW:       result = EOVERFLOW;       break; /* Value too large for defined data type */
	case __DOS_EOWNERDEAD:      result = EOWNERDEAD;      break; /* Owner died */
	case __DOS_EPROTO:          result = EPROTO;          break; /* Protocol error */
	case __DOS_EPROTONOSUPPORT: result = EPROTONOSUPPORT; break; /* Protocol not supported */
	case __DOS_EPROTOTYPE:      result = EPROTOTYPE;      break; /* Protocol wrong type for socket */
	case __DOS_ETIME:           result = ETIME;           break; /* Timer expired */
	case __DOS_ETIMEDOUT:       result = ETIMEDOUT;       break; /* Connection timed out */
	case __DOS_ETXTBSY:         result = ETXTBSY;         break; /* Text file busy */
	case __DOS_EWOULDBLOCK:     result = EWOULDBLOCK;     break; /* Operation would block */
	default:
		result = EPERM;
		break;
	}
	return result;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C */
