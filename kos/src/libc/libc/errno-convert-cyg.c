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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C
#define GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C 1
#define __LINUX_ERRNO_EXTENSIONS__ 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <parts/errno.h>
#include <parts/cyg/errno.h>

#include "errno.h"

DECL_BEGIN

/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(errno_cyg2kos, libd_errno_cyg2kos);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_cyg2kos")
NOBLOCK /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2kos)(/*cyg*/ errno_t value) {
	errno_t result;
	switch (value) {

	case __CYG_EPERM:           result = EPERM;           break; /* Not owner */
	case __CYG_ENOSHARE:                                         /* No such host or network path */
	case __CYG_ELBIN:                                            /* Inode is remote (not really error) */
	case __CYG_ENOENT:          result = ENOENT;          break; /* No such file or directory */
	case __CYG_ESRCH:           result = ESRCH;           break; /* No such process */
	case __CYG_EINTR:           result = EINTR;           break; /* Interrupted system call */
	case __CYG_EIO:             result = EIO;             break; /* I/O error */
	case __CYG_ENXIO:           result = ENXIO;           break; /* No such device or address */
	case __CYG_E2BIG:           result = E2BIG;           break; /* Arg list too long */
	case __CYG_ENOEXEC:         result = ENOEXEC;         break; /* Exec format error */
	case __CYG_EBADF:           result = EBADF;           break; /* Bad file number */
	case __CYG_ECHILD:          result = ECHILD;          break; /* No children */
	case __CYG_EAGAIN:          result = EAGAIN;          break; /* No more processes */
	case __CYG_EPROCLIM:                                         /* Process limit reached */
	case __CYG_ENOMEM:          result = ENOMEM;          break; /* Not enough space */
	case __CYG_EACCES:          result = EACCES;          break; /* Permission denied */
	case __CYG_EFAULT:          result = EFAULT;          break; /* Bad address */
	case __CYG_EBUSY:           result = EBUSY;           break; /* Device or resource busy */
	case __CYG_ECASECLASH:                                       /* Filename exists with different case */
	case __CYG_EEXIST:          result = EEXIST;          break; /* File exists */
	case __CYG_EXDEV:           result = EXDEV;           break; /* Cross-device link */
	case __CYG_ENODEV:          result = ENODEV;          break; /* No such device */
	case __CYG_ENOTDIR:         result = ENOTDIR;         break; /* Not a directory */
	case __CYG_EISDIR:          result = EISDIR;          break; /* Is a directory */
	case __CYG_EINVAL:          result = EINVAL;          break; /* Invalid argument */
	case __CYG_ENFILE:          result = ENFILE;          break; /* Too many open files in system */
	case __CYG_EMFILE:          result = EMFILE;          break; /* File descriptor value too large */
	case __CYG_ENOTTY:          result = ENOTTY;          break; /* Not a character device */
	case __CYG_ETXTBSY:         result = ETXTBSY;         break; /* Text file busy */
	case __CYG_EFBIG:           result = EFBIG;           break; /* File too large */
	case __CYG_ENOSPC:          result = ENOSPC;          break; /* No space left on device */
	case __CYG_ESPIPE:          result = ESPIPE;          break; /* Illegal seek */
	case __CYG_EROFS:           result = EROFS;           break; /* Read-only file system */
	case __CYG_EMLINK:          result = EMLINK;          break; /* Too many links */
	case __CYG_EPIPE:           result = EPIPE;           break; /* Broken pipe */
	case __CYG_EDOM:            result = EDOM;            break; /* Mathematics argument out of domain of function */
	case __CYG_ERANGE:          result = ERANGE;          break; /* Result too large */
	case __CYG_ENOMSG:          result = ENOMSG;          break; /* No message of desired type */
	case __CYG_EIDRM:           result = EIDRM;           break; /* Identifier removed */
	case __CYG_EDEADLK:         result = EDEADLK;         break; /* Deadlock */
	case __CYG_ENOLCK:          result = ENOLCK;          break; /* No lock */
	case __CYG_ENOSTR:          result = ENOSTR;          break; /* Not a stream */
	case __CYG_ENMFILE:                                          /* No more files */
	case __CYG_ENODATA:         result = ENODATA;         break; /* No data (for no delay io) */
	case __CYG_ETIME:           result = ETIME;           break; /* Stream ioctl timeout */
	case __CYG_ENOSR:           result = ENOSR;           break; /* No stream resources */
	case __CYG_ENOLINK:         result = ENOLINK;         break; /* Virtual circuit is gone */
	case __CYG_EPROTO:          result = EPROTO;          break; /* Protocol error */
	case __CYG_EMULTIHOP:       result = EMULTIHOP;       break; /* Multihop attempted */
	case __CYG_EBADMSG:         result = EBADMSG;         break; /* Bad message */
	case __CYG_ENOSYS:          result = ENOSYS;          break; /* Function not implemented */
	case __CYG_ENOTEMPTY:       result = ENOTEMPTY;       break; /* Directory not empty */
	case __CYG_ENAMETOOLONG:    result = ENAMETOOLONG;    break; /* File or path name too long */
	case __CYG_ELOOP:           result = ELOOP;           break; /* Too many symbolic links */
	case __CYG_EOPNOTSUPP:      result = EOPNOTSUPP;      break; /* Operation not supported on socket */
	case __CYG_EPFNOSUPPORT:    result = EPFNOSUPPORT;    break; /* Protocol family not supported */
	case __CYG_ECONNRESET:      result = ECONNRESET;      break; /* Connection reset by peer */
	case __CYG_ENOBUFS:         result = ENOBUFS;         break; /* No buffer space available */
	case __CYG_EAFNOSUPPORT:    result = EAFNOSUPPORT;    break; /* Address family not supported by protocol family */
	case __CYG_EPROTOTYPE:      result = EPROTOTYPE;      break; /* Protocol wrong type for socket */
	case __CYG_ENOTSOCK:        result = ENOTSOCK;        break; /* Socket operation on non-socket */
	case __CYG_ENOPROTOOPT:     result = ENOPROTOOPT;     break; /* Protocol not available */
	case __CYG_ECONNREFUSED:    result = ECONNREFUSED;    break; /* Connection refused */
	case __CYG_EADDRINUSE:      result = EADDRINUSE;      break; /* Address already in use */
	case __CYG_ECONNABORTED:    result = ECONNABORTED;    break; /* Software caused connection abort */
	case __CYG_ENETUNREACH:     result = ENETUNREACH;     break; /* Network is unreachable */
	case __CYG_ENETDOWN:        result = ENETDOWN;        break; /* Network interface is not configured */
	case __CYG_ETIMEDOUT:       result = ETIMEDOUT;       break; /* Connection timed out */
	case __CYG_EHOSTDOWN:       result = EHOSTDOWN;       break; /* Host is down */
	case __CYG_EHOSTUNREACH:    result = EHOSTUNREACH;    break; /* Host is unreachable */
	case __CYG_EINPROGRESS:     result = EINPROGRESS;     break; /* Connection already in progress */
	case __CYG_EALREADY:        result = EALREADY;        break; /* Socket already connected */
	case __CYG_EDESTADDRREQ:    result = EDESTADDRREQ;    break; /* Destination address required */
	case __CYG_EMSGSIZE:        result = EMSGSIZE;        break; /* Message too long */
	case __CYG_EPROTONOSUPPORT: result = EPROTONOSUPPORT; break; /* Unknown protocol */
	case __CYG_EADDRNOTAVAIL:   result = EADDRNOTAVAIL;   break; /* Address not available */
	case __CYG_ENETRESET:       result = ENETRESET;       break; /* Connection aborted by network */
	case __CYG_EISCONN:         result = EISCONN;         break; /* Socket is already connected */
	case __CYG_ENOTCONN:        result = ENOTCONN;        break; /* Socket is not connected */
	case __CYG_ETOOMANYREFS:    result = ETOOMANYREFS;    break; /* Too many references: cannot splice */
	case __CYG_EDQUOT:          result = EDQUOT;          break; /* Quota exceeded */
	case __CYG_ESTALE:          result = ESTALE;          break; /* Stale file handle */
	case __CYG_ENOTSUP:         result = ENOTSUP;         break; /* Not supported */
	case __CYG_EILSEQ:          result = EILSEQ;          break; /* Illegal byte sequence */
	case __CYG_EOVERFLOW:       result = EOVERFLOW;       break; /* Value too large for defined data type */
	case __CYG_ECANCELED:       result = ECANCELED;       break; /* Operation canceled */
	case __CYG_ENOTRECOVERABLE: result = ENOTRECOVERABLE; break; /* State not recoverable */
	case __CYG_EOWNERDEAD:      result = EOWNERDEAD;      break; /* Previous owner died */
	case __CYG_ENOTBLK:         result = ENOTBLK;         break; /* Block device required */
	case __CYG_ECHRNG:          result = ECHRNG;          break; /* Channel number out of range */
	case __CYG_EL2NSYNC:        result = EL2NSYNC;        break; /* Level 2 not synchronized */
	case __CYG_EL3HLT:          result = EL3HLT;          break; /* Level 3 halted */
	case __CYG_EL3RST:          result = EL3RST;          break; /* Level 3 reset */
	case __CYG_ELNRNG:          result = ELNRNG;          break; /* Link number out of range */
	case __CYG_EUNATCH:         result = EUNATCH;         break; /* Protocol driver not attached */
	case __CYG_ENOCSI:          result = ENOCSI;          break; /* No CSI structure available */
	case __CYG_EL2HLT:          result = EL2HLT;          break; /* Level 2 halted */
	case __CYG_EBADE:           result = EBADE;           break; /* Invalid exchange */
	case __CYG_EBADR:           result = EBADR;           break; /* Invalid request descriptor */
	case __CYG_EXFULL:          result = EXFULL;          break; /* Exchange full */
	case __CYG_ENOANO:          result = ENOANO;          break; /* No anode */
	case __CYG_EBADRQC:         result = EBADRQC;         break; /* Invalid request code */
	case __CYG_EBADSLT:         result = EBADSLT;         break; /* Invalid slot */
	case __CYG_EDEADLOCK:       result = EDEADLOCK;       break; /* File locking deadlock error */
	case __CYG_EBFONT:          result = EBFONT;          break; /* Bad font file fmt */
	case __CYG_ENONET:          result = ENONET;          break; /* Machine is not on the network */
	case __CYG_ENOPKG:          result = ENOPKG;          break; /* Package not installed */
	case __CYG_EREMOTE:         result = EREMOTE;         break; /* The object is remote */
	case __CYG_EADV:            result = EADV;            break; /* Advertise error */
	case __CYG_ESRMNT:          result = ESRMNT;          break; /* Srmount error */
	case __CYG_ECOMM:           result = ECOMM;           break; /* Communication error on send */
	case __CYG_EDOTDOT:         result = EDOTDOT;         break; /* Cross mount point (not really error) */
	case __CYG_ENOTUNIQ:        result = ENOTUNIQ;        break; /* Given log. name not unique */
	case __CYG_EFTYPE:                                           /* Inappropriate file type or format */
	case __CYG_EBADFD:          result = EBADFD;          break; /* f.d. invalid for this operation */
	case __CYG_EREMCHG:         result = EREMCHG;         break; /* Remote address changed */
	case __CYG_ELIBACC:         result = ELIBACC;         break; /* Can't access a needed shared lib */
	case __CYG_ELIBBAD:         result = ELIBBAD;         break; /* Accessing a corrupted shared lib */
	case __CYG_ELIBSCN:         result = ELIBSCN;         break; /* .lib section in a.out corrupted */
	case __CYG_ELIBMAX:         result = ELIBMAX;         break; /* Attempting to link in too many libs */
	case __CYG_ELIBEXEC:        result = ELIBEXEC;        break; /* Attempting to exec a shared library */
	case __CYG_ESHUTDOWN:       result = ESHUTDOWN;       break; /* Can't send after socket shutdown */
	case __CYG_ESOCKTNOSUPPORT: result = ESOCKTNOSUPPORT; break; /* Socket type not supported */
	case __CYG_EUSERS:          result = EUSERS;          break; /* Too many users */
	case __CYG_ENOMEDIUM:       result = ENOMEDIUM;       break; /* No medium (in tape drive) */
	case __CYG_ESTRPIPE:        result = ESTRPIPE;        break; /* Streams pipe error */

	default:
		result = EPERM;
		break;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_kos2cyg, libd_errno_kos2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_kos2cyg")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2cyg)(/*kos*/ errno_t value) {
	errno_t result;
	switch (value) {

	case EPERM:           result = __CYG_EPERM;           break; /* Not owner */
	case ENOENT:          result = __CYG_ENOENT;          break; /* No such file or directory */
	case ESRCH:           result = __CYG_ESRCH;           break; /* No such process */
	case EINTR:           result = __CYG_EINTR;           break; /* Interrupted system call */
	case EIO:             result = __CYG_EIO;             break; /* I/O error */
	case ENXIO:           result = __CYG_ENXIO;           break; /* No such device or address */
	case E2BIG:           result = __CYG_E2BIG;           break; /* Arg list too long */
	case ENOEXEC:         result = __CYG_ENOEXEC;         break; /* Exec format error */
	case EBADF:           result = __CYG_EBADF;           break; /* Bad file number */
	case ECHILD:          result = __CYG_ECHILD;          break; /* No children */
	case EAGAIN:          result = __CYG_EAGAIN;          break; /* No more processes */
	case ENOMEM:          result = __CYG_ENOMEM;          break; /* Not enough space */
	case EACCES:          result = __CYG_EACCES;          break; /* Permission denied */
	case EFAULT:          result = __CYG_EFAULT;          break; /* Bad address */
	case EBUSY:           result = __CYG_EBUSY;           break; /* Device or resource busy */
	case EEXIST:          result = __CYG_EEXIST;          break; /* File exists */
	case EXDEV:           result = __CYG_EXDEV;           break; /* Cross-device link */
	case ENODEV:          result = __CYG_ENODEV;          break; /* No such device */
	case ENOTDIR:         result = __CYG_ENOTDIR;         break; /* Not a directory */
	case EISDIR:          result = __CYG_EISDIR;          break; /* Is a directory */
	case EINVAL:          result = __CYG_EINVAL;          break; /* Invalid argument */
	case ENFILE:          result = __CYG_ENFILE;          break; /* Too many open files in system */
	case EMFILE:          result = __CYG_EMFILE;          break; /* File descriptor value too large */
	case ENOTTY:          result = __CYG_ENOTTY;          break; /* Not a character device */
	case ETXTBSY:         result = __CYG_ETXTBSY;         break; /* Text file busy */
	case EFBIG:           result = __CYG_EFBIG;           break; /* File too large */
	case ENOSPC:          result = __CYG_ENOSPC;          break; /* No space left on device */
	case ESPIPE:          result = __CYG_ESPIPE;          break; /* Illegal seek */
	case EROFS:           result = __CYG_EROFS;           break; /* Read-only file system */
	case EMLINK:          result = __CYG_EMLINK;          break; /* Too many links */
	case EPIPE:           result = __CYG_EPIPE;           break; /* Broken pipe */
	case EDOM:            result = __CYG_EDOM;            break; /* Mathematics argument out of domain of function */
	case ERANGE:          result = __CYG_ERANGE;          break; /* Result too large */
	case ENOMSG:          result = __CYG_ENOMSG;          break; /* No message of desired type */
	case EIDRM:           result = __CYG_EIDRM;           break; /* Identifier removed */
	case EDEADLK:         result = __CYG_EDEADLK;         break; /* Deadlock */
	case ENOLCK:          result = __CYG_ENOLCK;          break; /* No lock */
	case ENOSTR:          result = __CYG_ENOSTR;          break; /* Not a stream */
	case ENODATA:         result = __CYG_ENODATA;         break; /* No data (for no delay io) */
	case ETIME:           result = __CYG_ETIME;           break; /* Stream ioctl timeout */
	case ENOSR:           result = __CYG_ENOSR;           break; /* No stream resources */
	case ENOLINK:         result = __CYG_ENOLINK;         break; /* Virtual circuit is gone */
	case EPROTO:          result = __CYG_EPROTO;          break; /* Protocol error */
	case EMULTIHOP:       result = __CYG_EMULTIHOP;       break; /* Multihop attempted */
	case EBADMSG:         result = __CYG_EBADMSG;         break; /* Bad message */
	case ENOSYS:          result = __CYG_ENOSYS;          break; /* Function not implemented */
	case ENOTEMPTY:       result = __CYG_ENOTEMPTY;       break; /* Directory not empty */
	case ENAMETOOLONG:    result = __CYG_ENAMETOOLONG;    break; /* File or path name too long */
	case ELOOP:           result = __CYG_ELOOP;           break; /* Too many symbolic links */
	case EOPNOTSUPP:      result = __CYG_EOPNOTSUPP;      break; /* Operation not supported on socket */
	case EPFNOSUPPORT:    result = __CYG_EPFNOSUPPORT;    break; /* Protocol family not supported */
	case ECONNRESET:      result = __CYG_ECONNRESET;      break; /* Connection reset by peer */
	case ENOBUFS:         result = __CYG_ENOBUFS;         break; /* No buffer space available */
	case EAFNOSUPPORT:    result = __CYG_EAFNOSUPPORT;    break; /* Address family not supported by protocol family */
	case EPROTOTYPE:      result = __CYG_EPROTOTYPE;      break; /* Protocol wrong type for socket */
	case ENOTSOCK:        result = __CYG_ENOTSOCK;        break; /* Socket operation on non-socket */
	case ENOPROTOOPT:     result = __CYG_ENOPROTOOPT;     break; /* Protocol not available */
	case ECONNREFUSED:    result = __CYG_ECONNREFUSED;    break; /* Connection refused */
	case EADDRINUSE:      result = __CYG_EADDRINUSE;      break; /* Address already in use */
	case ECONNABORTED:    result = __CYG_ECONNABORTED;    break; /* Software caused connection abort */
	case ENETUNREACH:     result = __CYG_ENETUNREACH;     break; /* Network is unreachable */
	case ENETDOWN:        result = __CYG_ENETDOWN;        break; /* Network interface is not configured */
	case ETIMEDOUT:       result = __CYG_ETIMEDOUT;       break; /* Connection timed out */
	case EHOSTDOWN:       result = __CYG_EHOSTDOWN;       break; /* Host is down */
	case EHOSTUNREACH:    result = __CYG_EHOSTUNREACH;    break; /* Host is unreachable */
	case EINPROGRESS:     result = __CYG_EINPROGRESS;     break; /* Connection already in progress */
	case EALREADY:        result = __CYG_EALREADY;        break; /* Socket already connected */
	case EDESTADDRREQ:    result = __CYG_EDESTADDRREQ;    break; /* Destination address required */
	case EMSGSIZE:        result = __CYG_EMSGSIZE;        break; /* Message too long */
	case EPROTONOSUPPORT: result = __CYG_EPROTONOSUPPORT; break; /* Unknown protocol */
	case EADDRNOTAVAIL:   result = __CYG_EADDRNOTAVAIL;   break; /* Address not available */
	case ENETRESET:       result = __CYG_ENETRESET;       break; /* Connection aborted by network */
	case EISCONN:         result = __CYG_EISCONN;         break; /* Socket is already connected */
	case ENOTCONN:        result = __CYG_ENOTCONN;        break; /* Socket is not connected */
	case ETOOMANYREFS:    result = __CYG_ETOOMANYREFS;    break; /* Too many references: cannot splice */
	case EDQUOT:          result = __CYG_EDQUOT;          break; /* Quota exceeded */
	case ESTALE:          result = __CYG_ESTALE;          break; /* Stale file handle */
	case EILSEQ:          result = __CYG_EILSEQ;          break; /* Illegal byte sequence */
	case EOVERFLOW:       result = __CYG_EOVERFLOW;       break; /* Value too large for defined data type */
	case ECANCELED:       result = __CYG_ECANCELED;       break; /* Operation canceled */
	case ENOTRECOVERABLE: result = __CYG_ENOTRECOVERABLE; break; /* State not recoverable */
	case EOWNERDEAD:      result = __CYG_EOWNERDEAD;      break; /* Previous owner died */
	case ENOTBLK:         result = __CYG_ENOTBLK;         break; /* Block device required */
	case ECHRNG:          result = __CYG_ECHRNG;          break; /* Channel number out of range */
	case EL2NSYNC:        result = __CYG_EL2NSYNC;        break; /* Level 2 not synchronized */
	case EL3HLT:          result = __CYG_EL3HLT;          break; /* Level 3 halted */
	case EL3RST:          result = __CYG_EL3RST;          break; /* Level 3 reset */
	case ELNRNG:          result = __CYG_ELNRNG;          break; /* Link number out of range */
	case EUNATCH:         result = __CYG_EUNATCH;         break; /* Protocol driver not attached */
	case ENOCSI:          result = __CYG_ENOCSI;          break; /* No CSI structure available */
	case EL2HLT:          result = __CYG_EL2HLT;          break; /* Level 2 halted */
	case EBADE:           result = __CYG_EBADE;           break; /* Invalid exchange */
	case EBADR:           result = __CYG_EBADR;           break; /* Invalid request descriptor */
	case EXFULL:          result = __CYG_EXFULL;          break; /* Exchange full */
	case ENOANO:          result = __CYG_ENOANO;          break; /* No anode */
	case EBADRQC:         result = __CYG_EBADRQC;         break; /* Invalid request code */
	case EBADSLT:         result = __CYG_EBADSLT;         break; /* Invalid slot */
	case EBFONT:          result = __CYG_EBFONT;          break; /* Bad font file fmt */
	case ENONET:          result = __CYG_ENONET;          break; /* Machine is not on the network */
	case ENOPKG:          result = __CYG_ENOPKG;          break; /* Package not installed */
	case EREMOTE:         result = __CYG_EREMOTE;         break; /* The object is remote */
	case EADV:            result = __CYG_EADV;            break; /* Advertise error */
	case ESRMNT:          result = __CYG_ESRMNT;          break; /* Srmount error */
	case ECOMM:           result = __CYG_ECOMM;           break; /* Communication error on send */
	case EDOTDOT:         result = __CYG_EDOTDOT;         break; /* Cross mount point (not really error) */
	case ENOTUNIQ:        result = __CYG_ENOTUNIQ;        break; /* Given log. name not unique */
	case EBADFD:          result = __CYG_EBADFD;          break; /* f.d. invalid for this operation */
	case EREMCHG:         result = __CYG_EREMCHG;         break; /* Remote address changed */
	case ELIBACC:         result = __CYG_ELIBACC;         break; /* Can't access a needed shared lib */
	case ELIBBAD:         result = __CYG_ELIBBAD;         break; /* Accessing a corrupted shared lib */
	case ELIBSCN:         result = __CYG_ELIBSCN;         break; /* .lib section in a.out corrupted */
	case ELIBMAX:         result = __CYG_ELIBMAX;         break; /* Attempting to link in too many libs */
	case ELIBEXEC:        result = __CYG_ELIBEXEC;        break; /* Attempting to exec a shared library */
	case ESHUTDOWN:       result = __CYG_ESHUTDOWN;       break; /* Can't send after socket shutdown */
	case ESOCKTNOSUPPORT: result = __CYG_ESOCKTNOSUPPORT; break; /* Socket type not supported */
	case EUSERS:          result = __CYG_EUSERS;          break; /* Too many users */
	case ENOMEDIUM:       result = __CYG_ENOMEDIUM;       break; /* No medium (in tape drive) */
	case ESTRPIPE:        result = __CYG_ESTRPIPE;        break; /* Streams pipe error */

	default:
		result = EPERM;
		break;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_dos2cyg, libd_errno_dos2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_dos2cyg")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2cyg)(/*dos*/ errno_t value) {
	return libd_errno_kos2cyg(libd_errno_dos2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_nt2cyg, libd_errno_nt2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_nt2cyg")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2cyg)(/*nt*/ errno_t value) {
	return libd_errno_kos2cyg(libd_errno_nt2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_cyg2dos, libd_errno_cyg2dos);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_cyg2dos")
NOBLOCK /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2dos)(/*cyg*/ errno_t value) {
	return libd_errno_kos2dos(libd_errno_cyg2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_cyg2nt, libd_errno_cyg2nt);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.errno_cyg2nt")
NOBLOCK /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2nt)(/*cyg*/ errno_t value) {
	return libd_errno_kos2nt(libd_errno_cyg2kos(value));
}


DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C */
