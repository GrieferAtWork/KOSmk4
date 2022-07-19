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
#ifndef GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C
#define GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include "compat.h"
#include "errno.h"

DECL_BEGIN

#if EMAX > 0xffff
typedef uint32_t kos_errno_t;
#elif EMAX > 0xff
typedef uint16_t kos_errno_t;
#else /* EMAX > ... */
typedef uint8_t kos_errno_t;
#endif /* EMAX <= ... */

#define KOS_ECYG(e_cyg) (e_cyg ? EPERM : EOK)
#define CYG_EKOS(e_kos) (e_kos ? CYG_EPERM : 0)


/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

/* clang-format off */
/*[[[deemon
import * from deemon;
@@Mapping for cygName -> id
local cygErrnoNames: {string: int} = Dict();
@@Mapping for kosName -> id
local kosErrnoNames: {string: int} = Dict();

@@Mapping for id -> (cygName, kosName, comment)
local cygErrnoMappings: {int: (string, string, string)} = Dict();
@@Mapping for id -> (kosName, cygName)
local kosErrnoMappings: {int: (string, string, string)} = Dict();

for (local context: ["kos", "cyg"])
with (local fp = File.open("../../../include/asm/os/" + (context == "cyg" ? "cygwin" : context) + "/errno.h")) {
	local inside = false;
	for (local l: fp) {
		l = l.strip();
		if (l == "/" "*[[[begin]]]*" "/")
			inside = true;
		if (l == "/" "*[[[end]]]*" "/")
			inside = false;
		if (!inside)
			continue;
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __%[^ ] %[^/ ] /" "* %[^]")...;
		} catch (...) {
			continue;
		}
		comment = comment.partition("*" "/")[0].strip();
		local altName = name;
		while (comment.startswith("[")) {
			local cmd;
			cmd, none, comment = comment[1:].partition("]")...;
			cmd = cmd.strip();
			comment = comment.lstrip();
			if (cmd.endswith(")")) {
				local args;
				cmd, none, args = cmd[:-1].partition("(")...;
				cmd  = cmd.strip();
				args = args.strip();
				if (cmd == (context == "cyg" ? "kos" : "cyg"))
					altName = args;
			}
		}
		value = int(value.strip());
		if (context == "cyg") {
			if (value in cygErrnoMappings)
				continue;
			cygErrnoNames[name] = value;
			cygErrnoMappings[value] = (name, altName, comment);
		} else {
			if (value in kosErrnoMappings)
				continue;
			kosErrnoNames[name] = value;
			kosErrnoMappings[value] = (name, altName, comment);
		}
	}
}
local cyg_emax = cygErrnoMappings.keys > ...;
local kos_emax = kosErrnoMappings.keys > ...;
local cyg_errno_t;
if (cyg_emax > 0xffff)
	cyg_errno_t = "uint32_t";
else if (cyg_emax > 0xff)
	cyg_errno_t = "uint16_t";
else {
	cyg_errno_t = "uint8_t";
}
print("typedef ", cyg_errno_t, " cyg_errno_t;");
local longestCygErrnoName = cygErrnoNames.keys.each.length > ...;
local longestKosErrnoName = kosErrnoNames.keys.each.length > ...;
print("PRIVATE ATTR_SECTION(\".rodata.crt.dos.compat.cyg.errno\")");
print("kos_errno_t const cyg2kos_db[", cyg_emax + 1, "] = {");
for (local i: [:cyg_emax + 1]) {
	print("\t"),;
	local cygName, kosName, comment = cygErrnoMappings.get(i)...;
	if (kosName is none) {
		print("KOS_ECYG(", i, ")", ",");
		continue;
	}
	print(kosName, ",", (" " * (longestKosErrnoName - #kosName)),
		" /" "* ", (kosName == cygName ? " " : "!"), "CYG_",
		cygName, ": ", (" " * (longestCygErrnoName - #cygName)),
		comment, " *" "/");
}
print("};");
print();

print("PRIVATE ATTR_SECTION(\".rodata.crt.dos.compat.cyg.errno\")");
print("kos_errno_t const kos2cyg_db[", kos_emax + 1, "] = {");
for (local i: [:kos_emax + 1]) {
	print("\t"),;
	local kosName, cygName, comment = kosErrnoMappings.get(i)...;
	if (kosName is none) {
		print("CYG_EKOS(", i, ")", ",");
		continue;
	}
	local cygValue = cygErrnoNames.get(cygName);
	if (cygValue is none) {
		cygName  = "EKOS(" + i + ")";
		cygValue = "CYG_EKOS(" + i + ")";
	}
	print(cygValue, ",", (" " * (16 - #str(cygValue))),
		" /" "* ", (kosName == cygName ? " " : "!"),
		kosName, (" " * (longestKosErrnoName - #kosName)),
		" -> CYG_", cygName, ": ", (" " * (longestCygErrnoName - #cygName)),
		comment, " *" "/");
}
print("};");
]]]*/
typedef uint8_t cyg_errno_t;
PRIVATE ATTR_SECTION(".rodata.crt.dos.compat.cyg.errno")
kos_errno_t const cyg2kos_db[144] = {
	KOS_ECYG(0),
	EPERM,           /*  CYG_EPERM:           Operation not permitted */
	ENOENT,          /*  CYG_ENOENT:          No such file or directory */
	ESRCH,           /*  CYG_ESRCH:           No such process */
	EINTR,           /*  CYG_EINTR:           Interrupted system call */
	EIO,             /*  CYG_EIO:             I/O error */
	ENXIO,           /*  CYG_ENXIO:           No such device or address */
	E2BIG,           /*  CYG_E2BIG:           Argument list too long */
	ENOEXEC,         /*  CYG_ENOEXEC:         Exec format error */
	EBADF,           /*  CYG_EBADF:           Bad file number */
	ECHILD,          /*  CYG_ECHILD:          No child processes */
	EAGAIN,          /*  CYG_EAGAIN:          Try again */
	ENOMEM,          /*  CYG_ENOMEM:          Out of memory */
	EACCES,          /*  CYG_EACCES:          Permission denied */
	EFAULT,          /*  CYG_EFAULT:          Bad address */
	ENOTBLK,         /*  CYG_ENOTBLK:         Block device required */
	EBUSY,           /*  CYG_EBUSY:           Device or resource busy */
	EEXIST,          /*  CYG_EEXIST:          File exists */
	EXDEV,           /*  CYG_EXDEV:           Cross-device link */
	ENODEV,          /*  CYG_ENODEV:          No such device */
	ENOTDIR,         /*  CYG_ENOTDIR:         Not a directory */
	EISDIR,          /*  CYG_EISDIR:          Is a directory */
	EINVAL,          /*  CYG_EINVAL:          Invalid argument */
	ENFILE,          /*  CYG_ENFILE:          File table overflow */
	EMFILE,          /*  CYG_EMFILE:          Too many open files */
	ENOTTY,          /*  CYG_ENOTTY:          Not a typewriter */
	ETXTBSY,         /*  CYG_ETXTBSY:         Text file busy */
	EFBIG,           /*  CYG_EFBIG:           File too large */
	ENOSPC,          /*  CYG_ENOSPC:          No space left on device */
	ESPIPE,          /*  CYG_ESPIPE:          Illegal seek */
	EROFS,           /*  CYG_EROFS:           Read-only file system */
	EMLINK,          /*  CYG_EMLINK:          Too many links */
	EPIPE,           /*  CYG_EPIPE:           Broken pipe */
	EDOM,            /*  CYG_EDOM:            Math argument out of domain of func */
	ERANGE,          /*  CYG_ERANGE:          Math result not representable */
	ENOMSG,          /*  CYG_ENOMSG:          No message of desired type */
	EIDRM,           /*  CYG_EIDRM:           Identifier removed */
	ECHRNG,          /*  CYG_ECHRNG:          Channel number out of range */
	EL2NSYNC,        /*  CYG_EL2NSYNC:        Level 2 not synchronized */
	EL3HLT,          /*  CYG_EL3HLT:          Level 3 halted */
	EL3RST,          /*  CYG_EL3RST:          Level 3 reset */
	ELNRNG,          /*  CYG_ELNRNG:          Link number out of range */
	EUNATCH,         /*  CYG_EUNATCH:         Protocol driver not attached */
	ENOCSI,          /*  CYG_ENOCSI:          No CSI structure available */
	EL2HLT,          /*  CYG_EL2HLT:          Level 2 halted */
	EDEADLK,         /*  CYG_EDEADLK:         Resource deadlock would occur */
	ENOLCK,          /*  CYG_ENOLCK:          No record locks available */
	KOS_ECYG(47),
	KOS_ECYG(48),
	KOS_ECYG(49),
	EBADE,           /*  CYG_EBADE:           Invalid exchange */
	EBADR,           /*  CYG_EBADR:           Invalid request descriptor */
	EXFULL,          /*  CYG_EXFULL:          Exchange full */
	ENOANO,          /*  CYG_ENOANO:          No anode */
	EBADRQC,         /*  CYG_EBADRQC:         Invalid request code */
	EBADSLT,         /*  CYG_EBADSLT:         Invalid slot */
	EDEADLOCK,       /*  CYG_EDEADLOCK:       Resource deadlock would occur */
	EBFONT,          /*  CYG_EBFONT:          Bad font file format */
	KOS_ECYG(58),
	KOS_ECYG(59),
	ENOSTR,          /*  CYG_ENOSTR:          Device not a stream */
	ENODATA,         /*  CYG_ENODATA:         No data available */
	ETIME,           /*  CYG_ETIME:           Timer expired */
	ENOSR,           /*  CYG_ENOSR:           Out of streams resources */
	ENONET,          /*  CYG_ENONET:          Machine is not on the network */
	ENOPKG,          /*  CYG_ENOPKG:          Package not installed */
	EREMOTE,         /*  CYG_EREMOTE:         Object is remote */
	ENOLINK,         /*  CYG_ENOLINK:         Link has been severed */
	EADV,            /*  CYG_EADV:            Advertise error */
	ESRMNT,          /*  CYG_ESRMNT:          Srmount error */
	ECOMM,           /*  CYG_ECOMM:           Communication error on send */
	EPROTO,          /*  CYG_EPROTO:          Protocol error */
	KOS_ECYG(72),
	KOS_ECYG(73),
	EMULTIHOP,       /*  CYG_EMULTIHOP:       Multihop attempted */
	ENOENT,          /* !CYG_ELBIN:           Inode is remote (not really error) */
	EDOTDOT,         /*  CYG_EDOTDOT:         RFS specific error */
	EBADMSG,         /*  CYG_EBADMSG:         Not a data message */
	KOS_ECYG(78),
	EBADFD,          /* !CYG_EFTYPE:          Inappropriate file type or format */
	ENOTUNIQ,        /*  CYG_ENOTUNIQ:        Name not unique on network */
	EBADFD,          /*  CYG_EBADFD:          File descriptor in bad state */
	EREMCHG,         /*  CYG_EREMCHG:         Remote address changed */
	ELIBACC,         /*  CYG_ELIBACC:         Can not access a needed shared library */
	ELIBBAD,         /*  CYG_ELIBBAD:         Accessing a corrupted shared library */
	ELIBSCN,         /*  CYG_ELIBSCN:         .lib section in a.out corrupted */
	ELIBMAX,         /*  CYG_ELIBMAX:         Attempting to link in too many shared libraries */
	ELIBEXEC,        /*  CYG_ELIBEXEC:        Cannot exec a shared library directly */
	ENOSYS,          /*  CYG_ENOSYS:          Function not implemented */
	ENODATA,         /* !CYG_ENMFILE:         No more files */
	ENOTEMPTY,       /*  CYG_ENOTEMPTY:       Directory not empty */
	ENAMETOOLONG,    /*  CYG_ENAMETOOLONG:    File name too long */
	ELOOP,           /*  CYG_ELOOP:           Too many symbolic links encountered */
	KOS_ECYG(93),
	KOS_ECYG(94),
	EOPNOTSUPP,      /*  CYG_EOPNOTSUPP:      Operation not supported on transport endpoint */
	EPFNOSUPPORT,    /*  CYG_EPFNOSUPPORT:    Protocol family not supported */
	KOS_ECYG(97),
	KOS_ECYG(98),
	KOS_ECYG(99),
	KOS_ECYG(100),
	KOS_ECYG(101),
	KOS_ECYG(102),
	KOS_ECYG(103),
	ECONNRESET,      /*  CYG_ECONNRESET:      Connection reset by peer */
	ENOBUFS,         /*  CYG_ENOBUFS:         No buffer space available */
	EAFNOSUPPORT,    /*  CYG_EAFNOSUPPORT:    Address family not supported by protocol */
	EPROTOTYPE,      /*  CYG_EPROTOTYPE:      Protocol wrong type for socket */
	ENOTSOCK,        /*  CYG_ENOTSOCK:        Socket operation on non-socket */
	ENOPROTOOPT,     /*  CYG_ENOPROTOOPT:     Protocol not available */
	ESHUTDOWN,       /*  CYG_ESHUTDOWN:       Cannot send after transport endpoint shutdown */
	ECONNREFUSED,    /*  CYG_ECONNREFUSED:    Connection refused */
	EADDRINUSE,      /*  CYG_EADDRINUSE:      Address already in use */
	ECONNABORTED,    /*  CYG_ECONNABORTED:    Software caused connection abort */
	ENETUNREACH,     /*  CYG_ENETUNREACH:     Network is unreachable */
	ENETDOWN,        /*  CYG_ENETDOWN:        Network is down */
	ETIMEDOUT,       /*  CYG_ETIMEDOUT:       Connection timed out */
	EHOSTDOWN,       /*  CYG_EHOSTDOWN:       Host is down */
	EHOSTUNREACH,    /*  CYG_EHOSTUNREACH:    No route to host */
	EINPROGRESS,     /*  CYG_EINPROGRESS:     Operation now in progress */
	EALREADY,        /*  CYG_EALREADY:        Operation already in progress */
	EDESTADDRREQ,    /*  CYG_EDESTADDRREQ:    Destination address required */
	EMSGSIZE,        /*  CYG_EMSGSIZE:        Message too long */
	EPROTONOSUPPORT, /*  CYG_EPROTONOSUPPORT: Protocol not supported */
	ESOCKTNOSUPPORT, /*  CYG_ESOCKTNOSUPPORT: Socket type not supported */
	EADDRNOTAVAIL,   /*  CYG_EADDRNOTAVAIL:   Cannot assign requested address */
	ENETRESET,       /*  CYG_ENETRESET:       Network dropped connection because of reset */
	EISCONN,         /*  CYG_EISCONN:         Transport endpoint is already connected */
	ENOTCONN,        /*  CYG_ENOTCONN:        Transport endpoint is not connected */
	ETOOMANYREFS,    /*  CYG_ETOOMANYREFS:    Too many references: cannot splice */
	ENOMEM,          /* !CYG_EPROCLIM:        Process limit reached */
	EUSERS,          /*  CYG_EUSERS:          Too many users */
	EDQUOT,          /*  CYG_EDQUOT:          Quota exceeded */
	ESTALE,          /*  CYG_ESTALE:          Stale file handle */
	ENOTSUP,         /*  CYG_ENOTSUP:         Not supported */
	ENOMEDIUM,       /*  CYG_ENOMEDIUM:       No medium found */
	ENOENT,          /* !CYG_ENOSHARE:        No such host or network path */
	EEXIST,          /* !CYG_ECASECLASH:      Filename exists with different case */
	EILSEQ,          /*  CYG_EILSEQ:          Illegal byte sequence */
	EOVERFLOW,       /*  CYG_EOVERFLOW:       Value too large for defined data type */
	ECANCELED,       /*  CYG_ECANCELED:       Operation canceled */
	ENOTRECOVERABLE, /*  CYG_ENOTRECOVERABLE: State not recoverable */
	EOWNERDEAD,      /*  CYG_EOWNERDEAD:      Owner died */
	ESTRPIPE,        /*  CYG_ESTRPIPE:        Streams pipe error */
};

PRIVATE ATTR_SECTION(".rodata.crt.dos.compat.cyg.errno")
kos_errno_t const kos2cyg_db[134] = {
	CYG_EKOS(0),
	1,                /*  EPERM           -> CYG_EPERM:           Operation not permitted */
	2,                /*  ENOENT          -> CYG_ENOENT:          No such file or directory */
	3,                /*  ESRCH           -> CYG_ESRCH:           No such process */
	4,                /*  EINTR           -> CYG_EINTR:           Interrupted system call */
	5,                /*  EIO             -> CYG_EIO:             I/O error */
	6,                /*  ENXIO           -> CYG_ENXIO:           No such device or address */
	7,                /*  E2BIG           -> CYG_E2BIG:           Argument list too long */
	8,                /*  ENOEXEC         -> CYG_ENOEXEC:         Exec format error */
	9,                /*  EBADF           -> CYG_EBADF:           Bad file number */
	10,               /*  ECHILD          -> CYG_ECHILD:          No child processes */
	11,               /*  EAGAIN          -> CYG_EAGAIN:          Try again */
	12,               /*  ENOMEM          -> CYG_ENOMEM:          Out of memory */
	13,               /*  EACCES          -> CYG_EACCES:          Permission denied */
	14,               /*  EFAULT          -> CYG_EFAULT:          Bad address */
	15,               /*  ENOTBLK         -> CYG_ENOTBLK:         Block device required */
	16,               /*  EBUSY           -> CYG_EBUSY:           Device or resource busy */
	17,               /*  EEXIST          -> CYG_EEXIST:          File exists */
	18,               /*  EXDEV           -> CYG_EXDEV:           Cross-device link */
	19,               /*  ENODEV          -> CYG_ENODEV:          No such device */
	20,               /*  ENOTDIR         -> CYG_ENOTDIR:         Not a directory */
	21,               /*  EISDIR          -> CYG_EISDIR:          Is a directory */
	22,               /*  EINVAL          -> CYG_EINVAL:          Invalid argument */
	23,               /*  ENFILE          -> CYG_ENFILE:          File table overflow */
	24,               /*  EMFILE          -> CYG_EMFILE:          Too many open files */
	25,               /*  ENOTTY          -> CYG_ENOTTY:          Not a typewriter */
	26,               /*  ETXTBSY         -> CYG_ETXTBSY:         Text file busy */
	27,               /*  EFBIG           -> CYG_EFBIG:           File too large */
	28,               /*  ENOSPC          -> CYG_ENOSPC:          No space left on device */
	29,               /*  ESPIPE          -> CYG_ESPIPE:          Illegal seek */
	30,               /*  EROFS           -> CYG_EROFS:           Read-only file system */
	31,               /*  EMLINK          -> CYG_EMLINK:          Too many links */
	32,               /*  EPIPE           -> CYG_EPIPE:           Broken pipe */
	33,               /*  EDOM            -> CYG_EDOM:            Math argument out of domain of func */
	34,               /*  ERANGE          -> CYG_ERANGE:          Math result not representable */
	45,               /*  EDEADLK         -> CYG_EDEADLK:         Resource deadlock would occur */
	91,               /*  ENAMETOOLONG    -> CYG_ENAMETOOLONG:    File name too long */
	46,               /*  ENOLCK          -> CYG_ENOLCK:          No record locks available */
	88,               /*  ENOSYS          -> CYG_ENOSYS:          Function not implemented */
	90,               /*  ENOTEMPTY       -> CYG_ENOTEMPTY:       Directory not empty */
	92,               /*  ELOOP           -> CYG_ELOOP:           Too many symbolic links encountered */
	CYG_EKOS(41),
	35,               /*  ENOMSG          -> CYG_ENOMSG:          No message of desired type */
	36,               /*  EIDRM           -> CYG_EIDRM:           Identifier removed */
	37,               /*  ECHRNG          -> CYG_ECHRNG:          Channel number out of range */
	38,               /*  EL2NSYNC        -> CYG_EL2NSYNC:        Level 2 not synchronized */
	39,               /*  EL3HLT          -> CYG_EL3HLT:          Level 3 halted */
	40,               /*  EL3RST          -> CYG_EL3RST:          Level 3 reset */
	41,               /*  ELNRNG          -> CYG_ELNRNG:          Link number out of range */
	42,               /*  EUNATCH         -> CYG_EUNATCH:         Protocol driver not attached */
	43,               /*  ENOCSI          -> CYG_ENOCSI:          No CSI structure available */
	44,               /*  EL2HLT          -> CYG_EL2HLT:          Level 2 halted */
	50,               /*  EBADE           -> CYG_EBADE:           Invalid exchange */
	51,               /*  EBADR           -> CYG_EBADR:           Invalid request descriptor */
	52,               /*  EXFULL          -> CYG_EXFULL:          Exchange full */
	53,               /*  ENOANO          -> CYG_ENOANO:          No anode */
	54,               /*  EBADRQC         -> CYG_EBADRQC:         Invalid request code */
	55,               /*  EBADSLT         -> CYG_EBADSLT:         Invalid slot */
	CYG_EKOS(58),
	57,               /*  EBFONT          -> CYG_EBFONT:          Bad font file format */
	60,               /*  ENOSTR          -> CYG_ENOSTR:          Device not a stream */
	61,               /*  ENODATA         -> CYG_ENODATA:         No data available */
	62,               /*  ETIME           -> CYG_ETIME:           Timer expired */
	63,               /*  ENOSR           -> CYG_ENOSR:           Out of streams resources */
	64,               /*  ENONET          -> CYG_ENONET:          Machine is not on the network */
	65,               /*  ENOPKG          -> CYG_ENOPKG:          Package not installed */
	66,               /*  EREMOTE         -> CYG_EREMOTE:         Object is remote */
	67,               /*  ENOLINK         -> CYG_ENOLINK:         Link has been severed */
	68,               /*  EADV            -> CYG_EADV:            Advertise error */
	69,               /*  ESRMNT          -> CYG_ESRMNT:          Srmount error */
	70,               /*  ECOMM           -> CYG_ECOMM:           Communication error on send */
	71,               /*  EPROTO          -> CYG_EPROTO:          Protocol error */
	74,               /*  EMULTIHOP       -> CYG_EMULTIHOP:       Multihop attempted */
	76,               /*  EDOTDOT         -> CYG_EDOTDOT:         RFS specific error */
	77,               /*  EBADMSG         -> CYG_EBADMSG:         Not a data message */
	139,              /*  EOVERFLOW       -> CYG_EOVERFLOW:       Value too large for defined data type */
	80,               /*  ENOTUNIQ        -> CYG_ENOTUNIQ:        Name not unique on network */
	81,               /*  EBADFD          -> CYG_EBADFD:          File descriptor in bad state */
	82,               /*  EREMCHG         -> CYG_EREMCHG:         Remote address changed */
	83,               /*  ELIBACC         -> CYG_ELIBACC:         Can not access a needed shared library */
	84,               /*  ELIBBAD         -> CYG_ELIBBAD:         Accessing a corrupted shared library */
	85,               /*  ELIBSCN         -> CYG_ELIBSCN:         .lib section in a.out corrupted */
	86,               /*  ELIBMAX         -> CYG_ELIBMAX:         Attempting to link in too many shared libraries */
	87,               /*  ELIBEXEC        -> CYG_ELIBEXEC:        Cannot exec a shared library directly */
	138,              /*  EILSEQ          -> CYG_EILSEQ:          Illegal byte sequence */
	CYG_EKOS(85),     /* !ERESTART        -> CYG_EKOS(85):        Interrupted system call should be restarted */
	143,              /*  ESTRPIPE        -> CYG_ESTRPIPE:        Streams pipe error */
	131,              /*  EUSERS          -> CYG_EUSERS:          Too many users */
	108,              /*  ENOTSOCK        -> CYG_ENOTSOCK:        Socket operation on non-socket */
	121,              /*  EDESTADDRREQ    -> CYG_EDESTADDRREQ:    Destination address required */
	122,              /*  EMSGSIZE        -> CYG_EMSGSIZE:        Message too long */
	107,              /*  EPROTOTYPE      -> CYG_EPROTOTYPE:      Protocol wrong type for socket */
	109,              /*  ENOPROTOOPT     -> CYG_ENOPROTOOPT:     Protocol not available */
	123,              /*  EPROTONOSUPPORT -> CYG_EPROTONOSUPPORT: Protocol not supported */
	124,              /*  ESOCKTNOSUPPORT -> CYG_ESOCKTNOSUPPORT: Socket type not supported */
	95,               /*  EOPNOTSUPP      -> CYG_EOPNOTSUPP:      Operation not supported on transport endpoint */
	96,               /*  EPFNOSUPPORT    -> CYG_EPFNOSUPPORT:    Protocol family not supported */
	106,              /*  EAFNOSUPPORT    -> CYG_EAFNOSUPPORT:    Address family not supported by protocol */
	112,              /*  EADDRINUSE      -> CYG_EADDRINUSE:      Address already in use */
	125,              /*  EADDRNOTAVAIL   -> CYG_EADDRNOTAVAIL:   Cannot assign requested address */
	115,              /*  ENETDOWN        -> CYG_ENETDOWN:        Network is down */
	114,              /*  ENETUNREACH     -> CYG_ENETUNREACH:     Network is unreachable */
	126,              /*  ENETRESET       -> CYG_ENETRESET:       Network dropped connection because of reset */
	113,              /*  ECONNABORTED    -> CYG_ECONNABORTED:    Software caused connection abort */
	104,              /*  ECONNRESET      -> CYG_ECONNRESET:      Connection reset by peer */
	105,              /*  ENOBUFS         -> CYG_ENOBUFS:         No buffer space available */
	127,              /*  EISCONN         -> CYG_EISCONN:         Transport endpoint is already connected */
	128,              /*  ENOTCONN        -> CYG_ENOTCONN:        Transport endpoint is not connected */
	110,              /*  ESHUTDOWN       -> CYG_ESHUTDOWN:       Cannot send after transport endpoint shutdown */
	129,              /*  ETOOMANYREFS    -> CYG_ETOOMANYREFS:    Too many references: cannot splice */
	116,              /*  ETIMEDOUT       -> CYG_ETIMEDOUT:       Connection timed out */
	111,              /*  ECONNREFUSED    -> CYG_ECONNREFUSED:    Connection refused */
	117,              /*  EHOSTDOWN       -> CYG_EHOSTDOWN:       Host is down */
	118,              /*  EHOSTUNREACH    -> CYG_EHOSTUNREACH:    No route to host */
	120,              /*  EALREADY        -> CYG_EALREADY:        Operation already in progress */
	119,              /*  EINPROGRESS     -> CYG_EINPROGRESS:     Operation now in progress */
	133,              /*  ESTALE          -> CYG_ESTALE:          Stale file handle */
	CYG_EKOS(117),    /* !EUCLEAN         -> CYG_EKOS(117):       Structure needs cleaning */
	CYG_EKOS(118),    /* !ENOTNAM         -> CYG_EKOS(118):       Not a XENIX named type file */
	CYG_EKOS(119),    /* !ENAVAIL         -> CYG_EKOS(119):       No XENIX semaphores available */
	CYG_EKOS(120),    /* !EISNAM          -> CYG_EKOS(120):       Is a named type file */
	CYG_EKOS(121),    /* !EREMOTEIO       -> CYG_EKOS(121):       Remote I/O error */
	132,              /*  EDQUOT          -> CYG_EDQUOT:          Quota exceeded */
	135,              /*  ENOMEDIUM       -> CYG_ENOMEDIUM:       No medium found */
	CYG_EKOS(124),    /* !EMEDIUMTYPE     -> CYG_EKOS(124):       Wrong medium type */
	140,              /*  ECANCELED       -> CYG_ECANCELED:       Operation canceled */
	CYG_EKOS(126),    /* !ENOKEY          -> CYG_EKOS(126):       Required key not available */
	CYG_EKOS(127),    /* !EKEYEXPIRED     -> CYG_EKOS(127):       Key has expired */
	CYG_EKOS(128),    /* !EKEYREVOKED     -> CYG_EKOS(128):       Key has been revoked */
	CYG_EKOS(129),    /* !EKEYREJECTED    -> CYG_EKOS(129):       Key was rejected by service */
	142,              /*  EOWNERDEAD      -> CYG_EOWNERDEAD:      Owner died */
	141,              /*  ENOTRECOVERABLE -> CYG_ENOTRECOVERABLE: State not recoverable */
	CYG_EKOS(132),    /* !ERFKILL         -> CYG_EKOS(132):       Operation not possible due to RF-kill */
	CYG_EKOS(133),    /* !EHWPOISON       -> CYG_EKOS(133):       Memory page has hardware error */
};
/*[[[end]]]*/
/* clang-format on */


DEFINE_PUBLIC_ALIAS(errno_cyg2kos, libd_errno_cyg2kos);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2kos)(/*cyg*/ errno_t value) {
	errno_t result;
	if ((unsigned int)value > CYG_EMAX) {
		result = EPERM;
	} else {
		result = cyg2kos_db[(unsigned int)value];
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_kos2cyg, libd_errno_kos2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2cyg)(/*kos*/ errno_t value) {
	errno_t result;
	if ((unsigned int)value > EMAX) {
		result = CYG_EPERM;
	} else {
		result = kos2cyg_db[(unsigned int)value];
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_dos2cyg, libd_errno_dos2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2cyg)(/*dos*/ errno_t value) {
	return libd_errno_kos2cyg(libd_errno_dos2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_nt2cyg, libd_errno_nt2cyg);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2cyg)(/*nt*/ errno_t value) {
	return libd_errno_kos2cyg(libd_errno_nt2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_cyg2dos, libd_errno_cyg2dos);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2dos)(/*cyg*/ errno_t value) {
	return libd_errno_kos2dos(libd_errno_cyg2kos(value));
}

DEFINE_PUBLIC_ALIAS(errno_cyg2nt, libd_errno_cyg2nt);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.compat.cyg.errno")
NOBLOCK /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2nt)(/*cyg*/ errno_t value) {
	return libd_errno_kos2nt(libd_errno_cyg2kos(value));
}


DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_CONVERT_CYG_C */
