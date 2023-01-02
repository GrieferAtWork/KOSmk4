/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C
#define GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <signal.h>

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

#define KOS_EDOS(e_cyg) (e_cyg ? EPERM : EOK)
#define DOS_EKOS(e_kos) (e_kos ? DOS_EOTHER : 0)

/************************************************************************/
/* DOS/NT                                                               */
/************************************************************************/

/* clang-format off */
/*[[[deemon
import * from deemon;
@@Mapping for dosName -> id
local dosErrnoNames: {string: int} = Dict();
@@Mapping for kosName -> id
local kosErrnoNames: {string: int} = Dict();

@@Mapping for id -> (dosName, kosName, comment)
local dosErrnoMappings: {int: (string, string, string)} = Dict();
@@Mapping for id -> (kosName, dosName)
local kosErrnoMappings: {int: (string, string, string)} = Dict();

for (local context: ["kos", "dos"])
with (local fp = File.open("../../../include/asm/os/" + context + "/errno.h")) {
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
				if (cmd == (context == "dos" ? "kos" : "dos"))
					altName = args;
			}
		}
		value = int(value.strip());
		if (context == "dos") {
			if (value in dosErrnoMappings)
				continue;
			dosErrnoNames[name] = value;
			dosErrnoMappings[value] = (name, altName, comment);
		} else {
			if (value in kosErrnoMappings)
				continue;
			kosErrnoNames[name] = value;
			kosErrnoMappings[value] = (name, altName, comment);
		}
	}
}
local dos_emax = dosErrnoMappings.keys > ...;
local kos_emax = kosErrnoMappings.keys > ...;
local dos_errno_t;
if (dos_emax > 0xffff)
	dos_errno_t = "uint32_t";
else if (dos_emax > 0xff)
	dos_errno_t = "uint16_t";
else {
	dos_errno_t = "uint8_t";
}
print("typedef ", dos_errno_t, " dos_errno_t;");
local longestDosErrnoName = dosErrnoNames.keys.each.length > ...;
local longestKosErrnoName = kosErrnoNames.keys.each.length > ...;
print("PRIVATE ATTR_SECTION(\".rodata.crt.dos.compat.dos.errno\")");
print("kos_errno_t const dos2kos_db[", dos_emax + 1, "] = {");
for (local i: [:dos_emax + 1]) {
	print("\t"),;
	local dosName, kosName, comment = dosErrnoMappings.get(i)...;
	if (kosName is none) {
		print("KOS_EDOS(", i, ")", ",");
		continue;
	}
	print(kosName, ",", (" " * (longestKosErrnoName - #kosName)),
		" /" "* ", (kosName == dosName ? " " : "!"), "DOS_",
		dosName, ": ", (" " * (longestDosErrnoName - #dosName)),
		comment, " *" "/");
}
print("};");
print();

print("PRIVATE ATTR_SECTION(\".rodata.crt.dos.compat.dos.errno\")");
print("kos_errno_t const kos2dos_db[", kos_emax + 1, "] = {");
for (local i: [:kos_emax + 1]) {
	print("\t"),;
	local kosName, dosName, comment = kosErrnoMappings.get(i)...;
	if (kosName is none) {
		print("DOS_EKOS(", i, ")", ",");
		continue;
	}
	local dosValue = dosErrnoNames.get(dosName);
	if (dosValue is none) {
		dosName  = "EKOS(" + i + ")";
		dosValue = "DOS_EKOS(" + i + ")";
	}
	print(dosValue, ",", (" " * (16 - #str(dosValue))),
		" /" "* ", (kosName == dosName ? " " : "!"),
		kosName, (" " * (longestKosErrnoName - #kosName)),
		" -> DOS_", dosName, ": ", (" " * (longestDosErrnoName - #dosName)),
		comment, " *" "/");
}
print("};");
]]]*/
typedef uint8_t dos_errno_t;
PRIVATE ATTR_SECTION(".rodata.crt.dos.compat.dos.errno")
kos_errno_t const dos2kos_db[141] = {
	KOS_EDOS(0),
	EPERM,           /*  DOS_EPERM:           Operation not permitted */
	ENOENT,          /*  DOS_ENOENT:          No such file or directory */
	ESRCH,           /*  DOS_ESRCH:           No such process */
	EINTR,           /*  DOS_EINTR:           Interrupted system call */
	EIO,             /*  DOS_EIO:             I/O error */
	ENXIO,           /*  DOS_ENXIO:           No such device or address */
	E2BIG,           /*  DOS_E2BIG:           Argument list too long */
	ENOEXEC,         /*  DOS_ENOEXEC:         Exec format error */
	EBADF,           /*  DOS_EBADF:           Bad file number */
	ECHILD,          /*  DOS_ECHILD:          No child processes */
	EAGAIN,          /*  DOS_EAGAIN:          Try again */
	ENOMEM,          /*  DOS_ENOMEM:          Out of memory */
	EACCES,          /*  DOS_EACCES:          Permission denied */
	EFAULT,          /*  DOS_EFAULT:          Bad address */
	KOS_EDOS(15),
	EBUSY,           /*  DOS_EBUSY:           Device or resource busy */
	EEXIST,          /*  DOS_EEXIST:          File exists */
	EXDEV,           /*  DOS_EXDEV:           Cross-device link */
	ENODEV,          /*  DOS_ENODEV:          No such device */
	ENOTDIR,         /*  DOS_ENOTDIR:         Not a directory */
	EISDIR,          /*  DOS_EISDIR:          Is a directory */
	EINVAL,          /*  DOS_EINVAL:          Invalid argument */
	ENFILE,          /*  DOS_ENFILE:          File table overflow */
	EMFILE,          /*  DOS_EMFILE:          Too many open files */
	ENOTTY,          /*  DOS_ENOTTY:          Not a typewriter */
	KOS_EDOS(26),
	EFBIG,           /*  DOS_EFBIG:           File too large */
	ENOSPC,          /*  DOS_ENOSPC:          No space left on device */
	ESPIPE,          /*  DOS_ESPIPE:          Illegal seek */
	EROFS,           /*  DOS_EROFS:           Read-only file system */
	EMLINK,          /*  DOS_EMLINK:          Too many links */
	EPIPE,           /*  DOS_EPIPE:           Broken pipe */
	EDOM,            /*  DOS_EDOM:            Math argument out of domain of func */
	ERANGE,          /*  DOS_ERANGE:          Math result not representable */
	KOS_EDOS(35),
	EDEADLK,         /*  DOS_EDEADLK:         Resource deadlock would occur */
	KOS_EDOS(37),
	ENAMETOOLONG,    /*  DOS_ENAMETOOLONG:    File name too long */
	ENOLCK,          /*  DOS_ENOLCK:          No record locks available */
	ENOSYS,          /*  DOS_ENOSYS:          Function not implemented */
	ENOTEMPTY,       /*  DOS_ENOTEMPTY:       Directory not empty */
	EILSEQ,          /*  DOS_EILSEQ:          Illegal byte sequence */
	KOS_EDOS(43),
	KOS_EDOS(44),
	KOS_EDOS(45),
	KOS_EDOS(46),
	KOS_EDOS(47),
	KOS_EDOS(48),
	KOS_EDOS(49),
	KOS_EDOS(50),
	KOS_EDOS(51),
	KOS_EDOS(52),
	KOS_EDOS(53),
	KOS_EDOS(54),
	KOS_EDOS(55),
	KOS_EDOS(56),
	KOS_EDOS(57),
	KOS_EDOS(58),
	KOS_EDOS(59),
	KOS_EDOS(60),
	KOS_EDOS(61),
	KOS_EDOS(62),
	KOS_EDOS(63),
	KOS_EDOS(64),
	KOS_EDOS(65),
	KOS_EDOS(66),
	KOS_EDOS(67),
	KOS_EDOS(68),
	KOS_EDOS(69),
	KOS_EDOS(70),
	KOS_EDOS(71),
	KOS_EDOS(72),
	KOS_EDOS(73),
	KOS_EDOS(74),
	KOS_EDOS(75),
	KOS_EDOS(76),
	KOS_EDOS(77),
	KOS_EDOS(78),
	KOS_EDOS(79),
	ERANGE,          /* !DOS_STRUNCATE:       Truncated */
	KOS_EDOS(81),
	KOS_EDOS(82),
	KOS_EDOS(83),
	KOS_EDOS(84),
	KOS_EDOS(85),
	KOS_EDOS(86),
	KOS_EDOS(87),
	KOS_EDOS(88),
	KOS_EDOS(89),
	KOS_EDOS(90),
	KOS_EDOS(91),
	KOS_EDOS(92),
	KOS_EDOS(93),
	KOS_EDOS(94),
	KOS_EDOS(95),
	KOS_EDOS(96),
	KOS_EDOS(97),
	KOS_EDOS(98),
	KOS_EDOS(99),
	EADDRINUSE,      /*  DOS_EADDRINUSE:      Address already in use */
	EADDRNOTAVAIL,   /*  DOS_EADDRNOTAVAIL:   Cannot assign requested address */
	EAFNOSUPPORT,    /*  DOS_EAFNOSUPPORT:    Address family not supported by protocol */
	EALREADY,        /*  DOS_EALREADY:        Operation already in progress */
	EBADMSG,         /*  DOS_EBADMSG:         Not a data message */
	ECANCELED,       /*  DOS_ECANCELED:       Operation canceled */
	ECONNABORTED,    /*  DOS_ECONNABORTED:    Software caused connection abort */
	ECONNREFUSED,    /*  DOS_ECONNREFUSED:    Connection refused */
	ECONNRESET,      /*  DOS_ECONNRESET:      Connection reset by peer */
	EDESTADDRREQ,    /*  DOS_EDESTADDRREQ:    Destination address required */
	EHOSTUNREACH,    /*  DOS_EHOSTUNREACH:    No route to host */
	EIDRM,           /*  DOS_EIDRM:           Identifier removed */
	EINPROGRESS,     /*  DOS_EINPROGRESS:     Operation now in progress */
	EISCONN,         /*  DOS_EISCONN:         Transport endpoint is already connected */
	ELOOP,           /*  DOS_ELOOP:           Too many symbolic links encountered */
	EMSGSIZE,        /*  DOS_EMSGSIZE:        Message too long */
	ENETDOWN,        /*  DOS_ENETDOWN:        Network is down */
	ENETRESET,       /*  DOS_ENETRESET:       Network dropped connection because of reset */
	ENETUNREACH,     /*  DOS_ENETUNREACH:     Network is unreachable */
	ENOBUFS,         /*  DOS_ENOBUFS:         No buffer space available */
	ENODATA,         /*  DOS_ENODATA:         No data available */
	ENOLINK,         /*  DOS_ENOLINK:         Link has been severed */
	ENOMSG,          /*  DOS_ENOMSG:          No message of desired type */
	ENOPROTOOPT,     /*  DOS_ENOPROTOOPT:     Protocol not available */
	ENOSR,           /*  DOS_ENOSR:           Out of streams resources */
	ENOSTR,          /*  DOS_ENOSTR:          Device not a stream */
	ENOTCONN,        /*  DOS_ENOTCONN:        Transport endpoint is not connected */
	ENOTRECOVERABLE, /*  DOS_ENOTRECOVERABLE: State not recoverable */
	ENOTSOCK,        /*  DOS_ENOTSOCK:        Socket operation on non-socket */
	ENOTSUP,         /*  DOS_ENOTSUP:         Not supported */
	EOPNOTSUPP,      /*  DOS_EOPNOTSUPP:      Operation not supported on transport endpoint */
	EPERM,           /* !DOS_EOTHER:          Other */
	EOVERFLOW,       /*  DOS_EOVERFLOW:       Value too large for defined data type */
	EOWNERDEAD,      /*  DOS_EOWNERDEAD:      Owner died */
	EPROTO,          /*  DOS_EPROTO:          Protocol error */
	EPROTONOSUPPORT, /*  DOS_EPROTONOSUPPORT: Protocol not supported */
	EPROTOTYPE,      /*  DOS_EPROTOTYPE:      Protocol wrong type for socket */
	ETIME,           /*  DOS_ETIME:           Timer expired */
	ETIMEDOUT,       /*  DOS_ETIMEDOUT:       Connection timed out */
	ETXTBSY,         /*  DOS_ETXTBSY:         Text file busy */
	EWOULDBLOCK,     /*  DOS_EWOULDBLOCK:     Operation would block */
};

PRIVATE ATTR_SECTION(".rodata.crt.dos.compat.dos.errno")
kos_errno_t const kos2dos_db[134] = {
	DOS_EKOS(0),
	1,                /*  EPERM           -> DOS_EPERM:           Operation not permitted */
	2,                /*  ENOENT          -> DOS_ENOENT:          No such file or directory */
	3,                /*  ESRCH           -> DOS_ESRCH:           No such process */
	4,                /*  EINTR           -> DOS_EINTR:           Interrupted system call */
	5,                /*  EIO             -> DOS_EIO:             I/O error */
	6,                /*  ENXIO           -> DOS_ENXIO:           No such device or address */
	7,                /*  E2BIG           -> DOS_E2BIG:           Argument list too long */
	8,                /*  ENOEXEC         -> DOS_ENOEXEC:         Exec format error */
	9,                /*  EBADF           -> DOS_EBADF:           Bad file number */
	10,               /*  ECHILD          -> DOS_ECHILD:          No child processes */
	11,               /*  EAGAIN          -> DOS_EAGAIN:          Try again */
	12,               /*  ENOMEM          -> DOS_ENOMEM:          Out of memory */
	13,               /*  EACCES          -> DOS_EACCES:          Permission denied */
	14,               /*  EFAULT          -> DOS_EFAULT:          Bad address */
	DOS_EKOS(15),     /* !ENOTBLK         -> DOS_EKOS(15):        Block device required */
	16,               /*  EBUSY           -> DOS_EBUSY:           Device or resource busy */
	17,               /*  EEXIST          -> DOS_EEXIST:          File exists */
	18,               /*  EXDEV           -> DOS_EXDEV:           Cross-device link */
	19,               /*  ENODEV          -> DOS_ENODEV:          No such device */
	20,               /*  ENOTDIR         -> DOS_ENOTDIR:         Not a directory */
	21,               /*  EISDIR          -> DOS_EISDIR:          Is a directory */
	22,               /*  EINVAL          -> DOS_EINVAL:          Invalid argument */
	23,               /*  ENFILE          -> DOS_ENFILE:          File table overflow */
	24,               /*  EMFILE          -> DOS_EMFILE:          Too many open files */
	25,               /*  ENOTTY          -> DOS_ENOTTY:          Not a typewriter */
	139,              /*  ETXTBSY         -> DOS_ETXTBSY:         Text file busy */
	27,               /*  EFBIG           -> DOS_EFBIG:           File too large */
	28,               /*  ENOSPC          -> DOS_ENOSPC:          No space left on device */
	29,               /*  ESPIPE          -> DOS_ESPIPE:          Illegal seek */
	30,               /*  EROFS           -> DOS_EROFS:           Read-only file system */
	31,               /*  EMLINK          -> DOS_EMLINK:          Too many links */
	32,               /*  EPIPE           -> DOS_EPIPE:           Broken pipe */
	33,               /*  EDOM            -> DOS_EDOM:            Math argument out of domain of func */
	34,               /*  ERANGE          -> DOS_ERANGE:          Math result not representable */
	36,               /*  EDEADLK         -> DOS_EDEADLK:         Resource deadlock would occur */
	38,               /*  ENAMETOOLONG    -> DOS_ENAMETOOLONG:    File name too long */
	39,               /*  ENOLCK          -> DOS_ENOLCK:          No record locks available */
	40,               /*  ENOSYS          -> DOS_ENOSYS:          Function not implemented */
	41,               /*  ENOTEMPTY       -> DOS_ENOTEMPTY:       Directory not empty */
	114,              /*  ELOOP           -> DOS_ELOOP:           Too many symbolic links encountered */
	DOS_EKOS(41),
	122,              /*  ENOMSG          -> DOS_ENOMSG:          No message of desired type */
	111,              /*  EIDRM           -> DOS_EIDRM:           Identifier removed */
	DOS_EKOS(44),     /* !ECHRNG          -> DOS_EKOS(44):        Channel number out of range */
	DOS_EKOS(45),     /* !EL2NSYNC        -> DOS_EKOS(45):        Level 2 not synchronized */
	DOS_EKOS(46),     /* !EL3HLT          -> DOS_EKOS(46):        Level 3 halted */
	DOS_EKOS(47),     /* !EL3RST          -> DOS_EKOS(47):        Level 3 reset */
	DOS_EKOS(48),     /* !ELNRNG          -> DOS_EKOS(48):        Link number out of range */
	DOS_EKOS(49),     /* !EUNATCH         -> DOS_EKOS(49):        Protocol driver not attached */
	DOS_EKOS(50),     /* !ENOCSI          -> DOS_EKOS(50):        No CSI structure available */
	DOS_EKOS(51),     /* !EL2HLT          -> DOS_EKOS(51):        Level 2 halted */
	DOS_EKOS(52),     /* !EBADE           -> DOS_EKOS(52):        Invalid exchange */
	DOS_EKOS(53),     /* !EBADR           -> DOS_EKOS(53):        Invalid request descriptor */
	DOS_EKOS(54),     /* !EXFULL          -> DOS_EKOS(54):        Exchange full */
	DOS_EKOS(55),     /* !ENOANO          -> DOS_EKOS(55):        No anode */
	DOS_EKOS(56),     /* !EBADRQC         -> DOS_EKOS(56):        Invalid request code */
	DOS_EKOS(57),     /* !EBADSLT         -> DOS_EKOS(57):        Invalid slot */
	DOS_EKOS(58),
	DOS_EKOS(59),     /* !EBFONT          -> DOS_EKOS(59):        Bad font file format */
	125,              /*  ENOSTR          -> DOS_ENOSTR:          Device not a stream */
	120,              /*  ENODATA         -> DOS_ENODATA:         No data available */
	137,              /*  ETIME           -> DOS_ETIME:           Timer expired */
	124,              /*  ENOSR           -> DOS_ENOSR:           Out of streams resources */
	DOS_EKOS(64),     /* !ENONET          -> DOS_EKOS(64):        Machine is not on the network */
	DOS_EKOS(65),     /* !ENOPKG          -> DOS_EKOS(65):        Package not installed */
	DOS_EKOS(66),     /* !EREMOTE         -> DOS_EKOS(66):        Object is remote */
	121,              /*  ENOLINK         -> DOS_ENOLINK:         Link has been severed */
	DOS_EKOS(68),     /* !EADV            -> DOS_EKOS(68):        Advertise error */
	DOS_EKOS(69),     /* !ESRMNT          -> DOS_EKOS(69):        Srmount error */
	DOS_EKOS(70),     /* !ECOMM           -> DOS_EKOS(70):        Communication error on send */
	134,              /*  EPROTO          -> DOS_EPROTO:          Protocol error */
	DOS_EKOS(72),     /* !EMULTIHOP       -> DOS_EKOS(72):        Multihop attempted */
	DOS_EKOS(73),     /* !EDOTDOT         -> DOS_EKOS(73):        RFS specific error */
	104,              /*  EBADMSG         -> DOS_EBADMSG:         Not a data message */
	132,              /*  EOVERFLOW       -> DOS_EOVERFLOW:       Value too large for defined data type */
	DOS_EKOS(76),     /* !ENOTUNIQ        -> DOS_EKOS(76):        Name not unique on network */
	DOS_EKOS(77),     /* !EBADFD          -> DOS_EKOS(77):        File descriptor in bad state */
	DOS_EKOS(78),     /* !EREMCHG         -> DOS_EKOS(78):        Remote address changed */
	DOS_EKOS(79),     /* !ELIBACC         -> DOS_EKOS(79):        Can not access a needed shared library */
	DOS_EKOS(80),     /* !ELIBBAD         -> DOS_EKOS(80):        Accessing a corrupted shared library */
	DOS_EKOS(81),     /* !ELIBSCN         -> DOS_EKOS(81):        .lib section in a.out corrupted */
	DOS_EKOS(82),     /* !ELIBMAX         -> DOS_EKOS(82):        Attempting to link in too many shared libraries */
	DOS_EKOS(83),     /* !ELIBEXEC        -> DOS_EKOS(83):        Cannot exec a shared library directly */
	42,               /*  EILSEQ          -> DOS_EILSEQ:          Illegal byte sequence */
	DOS_EKOS(85),     /* !ERESTART        -> DOS_EKOS(85):        Interrupted system call should be restarted */
	DOS_EKOS(86),     /* !ESTRPIPE        -> DOS_EKOS(86):        Streams pipe error */
	DOS_EKOS(87),     /* !EUSERS          -> DOS_EKOS(87):        Too many users */
	128,              /*  ENOTSOCK        -> DOS_ENOTSOCK:        Socket operation on non-socket */
	109,              /*  EDESTADDRREQ    -> DOS_EDESTADDRREQ:    Destination address required */
	115,              /*  EMSGSIZE        -> DOS_EMSGSIZE:        Message too long */
	136,              /*  EPROTOTYPE      -> DOS_EPROTOTYPE:      Protocol wrong type for socket */
	123,              /*  ENOPROTOOPT     -> DOS_ENOPROTOOPT:     Protocol not available */
	135,              /*  EPROTONOSUPPORT -> DOS_EPROTONOSUPPORT: Protocol not supported */
	DOS_EKOS(94),     /* !ESOCKTNOSUPPORT -> DOS_EKOS(94):        Socket type not supported */
	130,              /*  EOPNOTSUPP      -> DOS_EOPNOTSUPP:      Operation not supported on transport endpoint */
	DOS_EKOS(96),     /* !EPFNOSUPPORT    -> DOS_EKOS(96):        Protocol family not supported */
	102,              /*  EAFNOSUPPORT    -> DOS_EAFNOSUPPORT:    Address family not supported by protocol */
	100,              /*  EADDRINUSE      -> DOS_EADDRINUSE:      Address already in use */
	101,              /*  EADDRNOTAVAIL   -> DOS_EADDRNOTAVAIL:   Cannot assign requested address */
	116,              /*  ENETDOWN        -> DOS_ENETDOWN:        Network is down */
	118,              /*  ENETUNREACH     -> DOS_ENETUNREACH:     Network is unreachable */
	117,              /*  ENETRESET       -> DOS_ENETRESET:       Network dropped connection because of reset */
	106,              /*  ECONNABORTED    -> DOS_ECONNABORTED:    Software caused connection abort */
	108,              /*  ECONNRESET      -> DOS_ECONNRESET:      Connection reset by peer */
	119,              /*  ENOBUFS         -> DOS_ENOBUFS:         No buffer space available */
	113,              /*  EISCONN         -> DOS_EISCONN:         Transport endpoint is already connected */
	126,              /*  ENOTCONN        -> DOS_ENOTCONN:        Transport endpoint is not connected */
	DOS_EKOS(108),    /* !ESHUTDOWN       -> DOS_EKOS(108):       Cannot send after transport endpoint shutdown */
	DOS_EKOS(109),    /* !ETOOMANYREFS    -> DOS_EKOS(109):       Too many references: cannot splice */
	138,              /*  ETIMEDOUT       -> DOS_ETIMEDOUT:       Connection timed out */
	107,              /*  ECONNREFUSED    -> DOS_ECONNREFUSED:    Connection refused */
	DOS_EKOS(112),    /* !EHOSTDOWN       -> DOS_EKOS(112):       Host is down */
	110,              /*  EHOSTUNREACH    -> DOS_EHOSTUNREACH:    No route to host */
	103,              /*  EALREADY        -> DOS_EALREADY:        Operation already in progress */
	112,              /*  EINPROGRESS     -> DOS_EINPROGRESS:     Operation now in progress */
	DOS_EKOS(116),    /* !ESTALE          -> DOS_EKOS(116):       Stale file handle */
	DOS_EKOS(117),    /* !EUCLEAN         -> DOS_EKOS(117):       Structure needs cleaning */
	DOS_EKOS(118),    /* !ENOTNAM         -> DOS_EKOS(118):       Not a XENIX named type file */
	DOS_EKOS(119),    /* !ENAVAIL         -> DOS_EKOS(119):       No XENIX semaphores available */
	DOS_EKOS(120),    /* !EISNAM          -> DOS_EKOS(120):       Is a named type file */
	DOS_EKOS(121),    /* !EREMOTEIO       -> DOS_EKOS(121):       Remote I/O error */
	DOS_EKOS(122),    /* !EDQUOT          -> DOS_EKOS(122):       Quota exceeded */
	DOS_EKOS(123),    /* !ENOMEDIUM       -> DOS_EKOS(123):       No medium found */
	DOS_EKOS(124),    /* !EMEDIUMTYPE     -> DOS_EKOS(124):       Wrong medium type */
	105,              /*  ECANCELED       -> DOS_ECANCELED:       Operation canceled */
	DOS_EKOS(126),    /* !ENOKEY          -> DOS_EKOS(126):       Required key not available */
	DOS_EKOS(127),    /* !EKEYEXPIRED     -> DOS_EKOS(127):       Key has expired */
	DOS_EKOS(128),    /* !EKEYREVOKED     -> DOS_EKOS(128):       Key has been revoked */
	DOS_EKOS(129),    /* !EKEYREJECTED    -> DOS_EKOS(129):       Key was rejected by service */
	133,              /*  EOWNERDEAD      -> DOS_EOWNERDEAD:      Owner died */
	127,              /*  ENOTRECOVERABLE -> DOS_ENOTRECOVERABLE: State not recoverable */
	DOS_EKOS(132),    /* !ERFKILL         -> DOS_EKOS(132):       Operation not possible due to RF-kill */
	DOS_EKOS(133),    /* !EHWPOISON       -> DOS_EKOS(133):       Memory page has hardware error */
};
/*[[[end]]]*/
/* clang-format on */

DEFINE_PUBLIC_ALIAS(errno_nt2kos, libd_errno_nt2kos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2kos)(/*nt*/ errno_t value) {
	return libd_errno_dos2kos(libd_errno_nt2dos(value));
}

DEFINE_PUBLIC_ALIAS(errno_kos2nt, libd_errno_kos2nt);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2nt)(/*kos*/ errno_t value) {
	return libd_errno_dos2nt(libd_errno_kos2dos(value));
}

DEFINE_PUBLIC_ALIAS(errno_nt2dos, libd_errno_nt2dos);
DEFINE_INTERN_ALIAS(libd__dosmaperr, libd_errno_nt2dos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*dos*/ errno_t
NOTHROW(LIBDCALL libd_errno_nt2dos)(/*nt*/ errno_t value) {
	/* TODO */
	return value;
}

DEFINE_PUBLIC_ALIAS(errno_dos2nt, libd_errno_dos2nt);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*nt*/ errno_t
NOTHROW(LIBDCALL libd_errno_dos2nt)(/*kos*/ errno_t value) {
	/* TODO */
	return value;
}


DEFINE_PUBLIC_ALIAS(errno_kos2dos, libd_errno_dos2kos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*dos*/ errno_t
NOTHROW(LIBDCALL libd_errno_kos2dos)(/*kos*/ errno_t value) {
	errno_t result;
	if ((unsigned int)value > EMAX) {
		result = DOS_EOTHER;
	} else {
		result = kos2dos_db[(unsigned int)value];
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(errno_dos2kos, libd_errno_dos2kos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*kos*/ errno_t
NOTHROW(LIBDCALL libd_errno_dos2kos)(/*dos*/ errno_t value) {
	errno_t result;
	if ((unsigned int)value > DOS_EMAX) {
		result = EPERM;
	} else {
		result = dos2kos_db[(unsigned int)value];
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(signo_dos2kos, libd_signo_dos2kos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*kos*/ signo_t
NOTHROW(LIBDCALL libd_signo_dos2kos)(/*dos*/ signo_t value) {
	if (value == DOS_SIGABRT)
		return SIGABRT;
	return value;
}

DEFINE_PUBLIC_ALIAS(signo_kos2dos, libd_signo_kos2dos);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos.errno")
NOBLOCK ATTR_CONST /*dos*/ signo_t
NOTHROW(LIBDCALL libd_signo_kos2dos)(/*kos*/ signo_t value) {
	if (value == SIGABRT)
		return DOS_SIGABRT;
	return value;
}


DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_CONVERT_DOS_C */
