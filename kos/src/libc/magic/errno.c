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

%[define_replacement(errno = __libc_errno)]
%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.errno.utility")]

%(auto_source)#include "../libc/globals.h"

%{
#include <features.h>

}%(c,libc_fast){
#include <asm/os/errno.h>
#include <bits/types.h>
}

/* Explicit errno code substitutions */
/* Errno codes from emulated libcs */
/*[[[deemon
import * from deemon;
import fs;
local printed_contexts = { "dos", "cyg" };

@@Mapping for context -> {id -> (dosName, comment)}
local errnoMappings: {string: {int: (string, string)}} = Dict();

for (local context: fs.dir("../../../include/asm/os"))
with (local fp = try File.open("../../../include/asm/os/" + context + "/errno.h") catch (...) none) {
	if (context !in ["dos", "cygwin"])
		continue;
	if (context == "cygwin")
		context = "cyg";
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
		while (comment.startswith("["))
			comment = comment.partition("]")[2].lstrip();
		value = int(value.strip());
		local contextMap = errnoMappings.get(context);
		if (contextMap is none)
			errnoMappings[context] = contextMap = Dict();
		if (value !in contextMap)
			contextMap[value] = (name, comment);
	}
}

local isFirst = true;
for (local contextName: printed_contexts) {
	if (!isFirst)
		print();
	isFirst = false;
	print("/" "* Errno codes for ", contextName.upper(), " *" "/");
	local contextMap = errnoMappings[contextName];
	local context_emax = contextMap.keys > ...;
	local longestErrnoName = contextMap.values.each.first.length > ...;
	local longestContextErrcode = #str(context_emax);
	for (local i: [:context_emax + 1]) {
		local name, comment = contextMap.get(i)...;
		if (name is none)
			continue;
		print("%[define(", contextName.upper(), "_",
			name, " " * (longestErrnoName - #name), " = ",
			i, ")]", " " * (longestContextErrcode - #str(i)),
			" /" "* ", comment, " *" "/");
	}
	print("%[define(", contextName.upper(), "_EMAX   = ", context_emax, ")]");
	print("%[define(", contextName.upper(), "_ECOUNT = ", context_emax + 1, ")]");
}
]]]*/
/* Errno codes for DOS */
%[define(DOS_EPERM           = 1)]   /* Operation not permitted */
%[define(DOS_ENOENT          = 2)]   /* No such file or directory */
%[define(DOS_ESRCH           = 3)]   /* No such process */
%[define(DOS_EINTR           = 4)]   /* Interrupted system call */
%[define(DOS_EIO             = 5)]   /* I/O error */
%[define(DOS_ENXIO           = 6)]   /* No such device or address */
%[define(DOS_E2BIG           = 7)]   /* Argument list too long */
%[define(DOS_ENOEXEC         = 8)]   /* Exec format error */
%[define(DOS_EBADF           = 9)]   /* Bad file number */
%[define(DOS_ECHILD          = 10)]  /* No child processes */
%[define(DOS_EAGAIN          = 11)]  /* Try again */
%[define(DOS_ENOMEM          = 12)]  /* Out of memory */
%[define(DOS_EACCES          = 13)]  /* Permission denied */
%[define(DOS_EFAULT          = 14)]  /* Bad address */
%[define(DOS_EBUSY           = 16)]  /* Device or resource busy */
%[define(DOS_EEXIST          = 17)]  /* File exists */
%[define(DOS_EXDEV           = 18)]  /* Cross-device link */
%[define(DOS_ENODEV          = 19)]  /* No such device */
%[define(DOS_ENOTDIR         = 20)]  /* Not a directory */
%[define(DOS_EISDIR          = 21)]  /* Is a directory */
%[define(DOS_EINVAL          = 22)]  /* Invalid argument */
%[define(DOS_ENFILE          = 23)]  /* File table overflow */
%[define(DOS_EMFILE          = 24)]  /* Too many open files */
%[define(DOS_ENOTTY          = 25)]  /* Not a typewriter */
%[define(DOS_EFBIG           = 27)]  /* File too large */
%[define(DOS_ENOSPC          = 28)]  /* No space left on device */
%[define(DOS_ESPIPE          = 29)]  /* Illegal seek */
%[define(DOS_EROFS           = 30)]  /* Read-only file system */
%[define(DOS_EMLINK          = 31)]  /* Too many links */
%[define(DOS_EPIPE           = 32)]  /* Broken pipe */
%[define(DOS_EDOM            = 33)]  /* Math argument out of domain of func */
%[define(DOS_ERANGE          = 34)]  /* Math result not representable */
%[define(DOS_EDEADLK         = 36)]  /* Resource deadlock would occur */
%[define(DOS_ENAMETOOLONG    = 38)]  /* File name too long */
%[define(DOS_ENOLCK          = 39)]  /* No record locks available */
%[define(DOS_ENOSYS          = 40)]  /* Function not implemented */
%[define(DOS_ENOTEMPTY       = 41)]  /* Directory not empty */
%[define(DOS_EILSEQ          = 42)]  /* Illegal byte sequence */
%[define(DOS_STRUNCATE       = 80)]  /* Truncated */
%[define(DOS_EADDRINUSE      = 100)] /* Address already in use */
%[define(DOS_EADDRNOTAVAIL   = 101)] /* Cannot assign requested address */
%[define(DOS_EAFNOSUPPORT    = 102)] /* Address family not supported by protocol */
%[define(DOS_EALREADY        = 103)] /* Operation already in progress */
%[define(DOS_EBADMSG         = 104)] /* Not a data message */
%[define(DOS_ECANCELED       = 105)] /* Operation canceled */
%[define(DOS_ECONNABORTED    = 106)] /* Software caused connection abort */
%[define(DOS_ECONNREFUSED    = 107)] /* Connection refused */
%[define(DOS_ECONNRESET      = 108)] /* Connection reset by peer */
%[define(DOS_EDESTADDRREQ    = 109)] /* Destination address required */
%[define(DOS_EHOSTUNREACH    = 110)] /* No route to host */
%[define(DOS_EIDRM           = 111)] /* Identifier removed */
%[define(DOS_EINPROGRESS     = 112)] /* Operation now in progress */
%[define(DOS_EISCONN         = 113)] /* Transport endpoint is already connected */
%[define(DOS_ELOOP           = 114)] /* Too many symbolic links encountered */
%[define(DOS_EMSGSIZE        = 115)] /* Message too long */
%[define(DOS_ENETDOWN        = 116)] /* Network is down */
%[define(DOS_ENETRESET       = 117)] /* Network dropped connection because of reset */
%[define(DOS_ENETUNREACH     = 118)] /* Network is unreachable */
%[define(DOS_ENOBUFS         = 119)] /* No buffer space available */
%[define(DOS_ENODATA         = 120)] /* No data available */
%[define(DOS_ENOLINK         = 121)] /* Link has been severed */
%[define(DOS_ENOMSG          = 122)] /* No message of desired type */
%[define(DOS_ENOPROTOOPT     = 123)] /* Protocol not available */
%[define(DOS_ENOSR           = 124)] /* Out of streams resources */
%[define(DOS_ENOSTR          = 125)] /* Device not a stream */
%[define(DOS_ENOTCONN        = 126)] /* Transport endpoint is not connected */
%[define(DOS_ENOTRECOVERABLE = 127)] /* State not recoverable */
%[define(DOS_ENOTSOCK        = 128)] /* Socket operation on non-socket */
%[define(DOS_ENOTSUP         = 129)] /* Not supported */
%[define(DOS_EOPNOTSUPP      = 130)] /* Operation not supported on transport endpoint */
%[define(DOS_EOTHER          = 131)] /* Other */
%[define(DOS_EOVERFLOW       = 132)] /* Value too large for defined data type */
%[define(DOS_EOWNERDEAD      = 133)] /* Owner died */
%[define(DOS_EPROTO          = 134)] /* Protocol error */
%[define(DOS_EPROTONOSUPPORT = 135)] /* Protocol not supported */
%[define(DOS_EPROTOTYPE      = 136)] /* Protocol wrong type for socket */
%[define(DOS_ETIME           = 137)] /* Timer expired */
%[define(DOS_ETIMEDOUT       = 138)] /* Connection timed out */
%[define(DOS_ETXTBSY         = 139)] /* Text file busy */
%[define(DOS_EWOULDBLOCK     = 140)] /* Operation would block */
%[define(DOS_EMAX   = 140)]
%[define(DOS_ECOUNT = 141)]

/* Errno codes for CYG */
%[define(CYG_EPERM           = 1)]   /* Operation not permitted */
%[define(CYG_ENOENT          = 2)]   /* No such file or directory */
%[define(CYG_ESRCH           = 3)]   /* No such process */
%[define(CYG_EINTR           = 4)]   /* Interrupted system call */
%[define(CYG_EIO             = 5)]   /* I/O error */
%[define(CYG_ENXIO           = 6)]   /* No such device or address */
%[define(CYG_E2BIG           = 7)]   /* Argument list too long */
%[define(CYG_ENOEXEC         = 8)]   /* Exec format error */
%[define(CYG_EBADF           = 9)]   /* Bad file number */
%[define(CYG_ECHILD          = 10)]  /* No child processes */
%[define(CYG_EAGAIN          = 11)]  /* Try again */
%[define(CYG_ENOMEM          = 12)]  /* Out of memory */
%[define(CYG_EACCES          = 13)]  /* Permission denied */
%[define(CYG_EFAULT          = 14)]  /* Bad address */
%[define(CYG_ENOTBLK         = 15)]  /* Block device required */
%[define(CYG_EBUSY           = 16)]  /* Device or resource busy */
%[define(CYG_EEXIST          = 17)]  /* File exists */
%[define(CYG_EXDEV           = 18)]  /* Cross-device link */
%[define(CYG_ENODEV          = 19)]  /* No such device */
%[define(CYG_ENOTDIR         = 20)]  /* Not a directory */
%[define(CYG_EISDIR          = 21)]  /* Is a directory */
%[define(CYG_EINVAL          = 22)]  /* Invalid argument */
%[define(CYG_ENFILE          = 23)]  /* File table overflow */
%[define(CYG_EMFILE          = 24)]  /* Too many open files */
%[define(CYG_ENOTTY          = 25)]  /* Not a typewriter */
%[define(CYG_ETXTBSY         = 26)]  /* Text file busy */
%[define(CYG_EFBIG           = 27)]  /* File too large */
%[define(CYG_ENOSPC          = 28)]  /* No space left on device */
%[define(CYG_ESPIPE          = 29)]  /* Illegal seek */
%[define(CYG_EROFS           = 30)]  /* Read-only file system */
%[define(CYG_EMLINK          = 31)]  /* Too many links */
%[define(CYG_EPIPE           = 32)]  /* Broken pipe */
%[define(CYG_EDOM            = 33)]  /* Math argument out of domain of func */
%[define(CYG_ERANGE          = 34)]  /* Math result not representable */
%[define(CYG_ENOMSG          = 35)]  /* No message of desired type */
%[define(CYG_EIDRM           = 36)]  /* Identifier removed */
%[define(CYG_ECHRNG          = 37)]  /* Channel number out of range */
%[define(CYG_EL2NSYNC        = 38)]  /* Level 2 not synchronized */
%[define(CYG_EL3HLT          = 39)]  /* Level 3 halted */
%[define(CYG_EL3RST          = 40)]  /* Level 3 reset */
%[define(CYG_ELNRNG          = 41)]  /* Link number out of range */
%[define(CYG_EUNATCH         = 42)]  /* Protocol driver not attached */
%[define(CYG_ENOCSI          = 43)]  /* No CSI structure available */
%[define(CYG_EL2HLT          = 44)]  /* Level 2 halted */
%[define(CYG_EDEADLK         = 45)]  /* Resource deadlock would occur */
%[define(CYG_ENOLCK          = 46)]  /* No record locks available */
%[define(CYG_EBADE           = 50)]  /* Invalid exchange */
%[define(CYG_EBADR           = 51)]  /* Invalid request descriptor */
%[define(CYG_EXFULL          = 52)]  /* Exchange full */
%[define(CYG_ENOANO          = 53)]  /* No anode */
%[define(CYG_EBADRQC         = 54)]  /* Invalid request code */
%[define(CYG_EBADSLT         = 55)]  /* Invalid slot */
%[define(CYG_EDEADLOCK       = 56)]  /* Resource deadlock would occur */
%[define(CYG_EBFONT          = 57)]  /* Bad font file format */
%[define(CYG_ENOSTR          = 60)]  /* Device not a stream */
%[define(CYG_ENODATA         = 61)]  /* No data available */
%[define(CYG_ETIME           = 62)]  /* Timer expired */
%[define(CYG_ENOSR           = 63)]  /* Out of streams resources */
%[define(CYG_ENONET          = 64)]  /* Machine is not on the network */
%[define(CYG_ENOPKG          = 65)]  /* Package not installed */
%[define(CYG_EREMOTE         = 66)]  /* Object is remote */
%[define(CYG_ENOLINK         = 67)]  /* Link has been severed */
%[define(CYG_EADV            = 68)]  /* Advertise error */
%[define(CYG_ESRMNT          = 69)]  /* Srmount error */
%[define(CYG_ECOMM           = 70)]  /* Communication error on send */
%[define(CYG_EPROTO          = 71)]  /* Protocol error */
%[define(CYG_EMULTIHOP       = 74)]  /* Multihop attempted */
%[define(CYG_ELBIN           = 75)]  /* Inode is remote (not really error) */
%[define(CYG_EDOTDOT         = 76)]  /* RFS specific error */
%[define(CYG_EBADMSG         = 77)]  /* Not a data message */
%[define(CYG_EFTYPE          = 79)]  /* Inappropriate file type or format */
%[define(CYG_ENOTUNIQ        = 80)]  /* Name not unique on network */
%[define(CYG_EBADFD          = 81)]  /* File descriptor in bad state */
%[define(CYG_EREMCHG         = 82)]  /* Remote address changed */
%[define(CYG_ELIBACC         = 83)]  /* Can not access a needed shared library */
%[define(CYG_ELIBBAD         = 84)]  /* Accessing a corrupted shared library */
%[define(CYG_ELIBSCN         = 85)]  /* .lib section in a.out corrupted */
%[define(CYG_ELIBMAX         = 86)]  /* Attempting to link in too many shared libraries */
%[define(CYG_ELIBEXEC        = 87)]  /* Cannot exec a shared library directly */
%[define(CYG_ENOSYS          = 88)]  /* Function not implemented */
%[define(CYG_ENMFILE         = 89)]  /* No more files */
%[define(CYG_ENOTEMPTY       = 90)]  /* Directory not empty */
%[define(CYG_ENAMETOOLONG    = 91)]  /* File name too long */
%[define(CYG_ELOOP           = 92)]  /* Too many symbolic links encountered */
%[define(CYG_EOPNOTSUPP      = 95)]  /* Operation not supported on transport endpoint */
%[define(CYG_EPFNOSUPPORT    = 96)]  /* Protocol family not supported */
%[define(CYG_ECONNRESET      = 104)] /* Connection reset by peer */
%[define(CYG_ENOBUFS         = 105)] /* No buffer space available */
%[define(CYG_EAFNOSUPPORT    = 106)] /* Address family not supported by protocol */
%[define(CYG_EPROTOTYPE      = 107)] /* Protocol wrong type for socket */
%[define(CYG_ENOTSOCK        = 108)] /* Socket operation on non-socket */
%[define(CYG_ENOPROTOOPT     = 109)] /* Protocol not available */
%[define(CYG_ESHUTDOWN       = 110)] /* Cannot send after transport endpoint shutdown */
%[define(CYG_ECONNREFUSED    = 111)] /* Connection refused */
%[define(CYG_EADDRINUSE      = 112)] /* Address already in use */
%[define(CYG_ECONNABORTED    = 113)] /* Software caused connection abort */
%[define(CYG_ENETUNREACH     = 114)] /* Network is unreachable */
%[define(CYG_ENETDOWN        = 115)] /* Network is down */
%[define(CYG_ETIMEDOUT       = 116)] /* Connection timed out */
%[define(CYG_EHOSTDOWN       = 117)] /* Host is down */
%[define(CYG_EHOSTUNREACH    = 118)] /* No route to host */
%[define(CYG_EINPROGRESS     = 119)] /* Operation now in progress */
%[define(CYG_EALREADY        = 120)] /* Operation already in progress */
%[define(CYG_EDESTADDRREQ    = 121)] /* Destination address required */
%[define(CYG_EMSGSIZE        = 122)] /* Message too long */
%[define(CYG_EPROTONOSUPPORT = 123)] /* Protocol not supported */
%[define(CYG_ESOCKTNOSUPPORT = 124)] /* Socket type not supported */
%[define(CYG_EADDRNOTAVAIL   = 125)] /* Cannot assign requested address */
%[define(CYG_ENETRESET       = 126)] /* Network dropped connection because of reset */
%[define(CYG_EISCONN         = 127)] /* Transport endpoint is already connected */
%[define(CYG_ENOTCONN        = 128)] /* Transport endpoint is not connected */
%[define(CYG_ETOOMANYREFS    = 129)] /* Too many references: cannot splice */
%[define(CYG_EPROCLIM        = 130)] /* Process limit reached */
%[define(CYG_EUSERS          = 131)] /* Too many users */
%[define(CYG_EDQUOT          = 132)] /* Quota exceeded */
%[define(CYG_ESTALE          = 133)] /* Stale file handle */
%[define(CYG_ENOTSUP         = 134)] /* Not supported */
%[define(CYG_ENOMEDIUM       = 135)] /* No medium found */
%[define(CYG_ENOSHARE        = 136)] /* No such host or network path */
%[define(CYG_ECASECLASH      = 137)] /* Filename exists with different case */
%[define(CYG_EILSEQ          = 138)] /* Illegal byte sequence */
%[define(CYG_EOVERFLOW       = 139)] /* Value too large for defined data type */
%[define(CYG_ECANCELED       = 140)] /* Operation canceled */
%[define(CYG_ENOTRECOVERABLE = 141)] /* State not recoverable */
%[define(CYG_EOWNERDEAD      = 142)] /* Owner died */
%[define(CYG_ESTRPIPE        = 143)] /* Streams pipe error */
%[define(CYG_EMAX   = 143)]
%[define(CYG_ECOUNT = 144)]
/*[[[end]]]*/


%{

/************************************************************************/
/* System errno codes                                                   */
/************************************************************************/
}
/*[[[deemon
import * from deemon;
import fs;
local errnoNames: {string: string} = Dict();
for (local context: fs.dir("../../../include/asm/os"))
with (local fp = try File.open("../../../include/asm/os/" + context + "/errno.h") catch (...) none) {
	for (local l: fp) {
		l = l.strip();
		local name, comment;
		try {
			name, none, comment = l.scanf(" # define __%[^ ] %[^/ ] /" "* %[^]")...;
		} catch (...) {
			try {
				name = l.scanf(" # define __%[^ ] ")...;
				if (!name.startswith("E"))
					continue;
				comment = "";
			} catch (...) {
				continue;
			}
		}
		comment = comment.strip();
		if (comment) {
			comment = comment.partition("*" "/")[0].strip();
			while (comment.startswith("["))
				comment = comment.partition("]")[2].lstrip();
		}
		if (!comment)
			comment = "??" "?";
		if (name !in errnoNames || errnoNames[name] == "??" "?")
			errnoNames[name] = comment;
	}
}

local longestNameLen = errnoNames.keys.each.length > ...;
errnoNames.setdefault("EOK", "Success");

for (local name: errnoNames.keys.sorted()) {
	print("%[define_replacement(",
		name, (" " * (longestNameLen - #name)), " = __",
		name, ")]", (" " * (longestNameLen - #name)),
		"/" "* ", errnoNames[name], " *" "/");
}

print("%{");
for (local name: errnoNames.keys.sorted()) {
	if (name in ["EOK", "EMAX", "ECOUNT", "ELASTERROR", "ELIMIT"])
		continue;
	print("#ifdef __", name);
	print("#define ",
		name, (" " * (longestNameLen - #name)), " __",
		name, (" " * (longestNameLen - #name)),
		" /" "* ", errnoNames[name], " *" "/");
	print("#endif /" "* __", name, " *" "/");
}
print("}");
]]]*/
%[define_replacement(E2BIG           = __E2BIG)]          /* Argument list too long */
%[define_replacement(EACCES          = __EACCES)]         /* Permission denied */
%[define_replacement(EADDRINUSE      = __EADDRINUSE)]     /* Address already in use */
%[define_replacement(EADDRNOTAVAIL   = __EADDRNOTAVAIL)]  /* Cannot assign requested address */
%[define_replacement(EADV            = __EADV)]           /* Advertise error */
%[define_replacement(EAFNOSUPPORT    = __EAFNOSUPPORT)]   /* Address family not supported by protocol */
%[define_replacement(EAGAIN          = __EAGAIN)]         /* Try again */
%[define_replacement(EALREADY        = __EALREADY)]       /* Operation already in progress */
%[define_replacement(EAUTH           = __EAUTH)]          /* ??? */
%[define_replacement(EBADE           = __EBADE)]          /* Invalid exchange */
%[define_replacement(EBADF           = __EBADF)]          /* Bad file number */
%[define_replacement(EBADFD          = __EBADFD)]         /* File descriptor in bad state */
%[define_replacement(EBADMSG         = __EBADMSG)]        /* Not a data message */
%[define_replacement(EBADR           = __EBADR)]          /* Invalid request descriptor */
%[define_replacement(EBADRPC         = __EBADRPC)]        /* ??? */
%[define_replacement(EBADRQC         = __EBADRQC)]        /* Invalid request code */
%[define_replacement(EBADSLT         = __EBADSLT)]        /* Invalid slot */
%[define_replacement(EBFONT          = __EBFONT)]         /* Bad font file format */
%[define_replacement(EBUSY           = __EBUSY)]          /* Device or resource busy */
%[define_replacement(ECANCELED       = __ECANCELED)]      /* Operation canceled */
%[define_replacement(ECASECLASH      = __ECASECLASH)]     /* Filename exists with different case */
%[define_replacement(ECHILD          = __ECHILD)]         /* No child processes */
%[define_replacement(ECHRNG          = __ECHRNG)]         /* Channel number out of range */
%[define_replacement(ECOMM           = __ECOMM)]          /* Communication error on send */
%[define_replacement(ECONNABORTED    = __ECONNABORTED)]   /* Software caused connection abort */
%[define_replacement(ECONNREFUSED    = __ECONNREFUSED)]   /* Connection refused */
%[define_replacement(ECONNRESET      = __ECONNRESET)]     /* Connection reset by peer */
%[define_replacement(ECOUNT          = __ECOUNT)]         /* Max errno + 1 */
%[define_replacement(EDEADLK         = __EDEADLK)]        /* Resource deadlock would occur */
%[define_replacement(EDEADLOCK       = __EDEADLOCK)]      /* Resource deadlock would occur */
%[define_replacement(EDESTADDRREQ    = __EDESTADDRREQ)]   /* Destination address required */
%[define_replacement(EDOM            = __EDOM)]           /* Math argument out of domain of func */
%[define_replacement(EDOTDOT         = __EDOTDOT)]        /* RFS specific error */
%[define_replacement(EDQUOT          = __EDQUOT)]         /* Quota exceeded */
%[define_replacement(EEXIST          = __EEXIST)]         /* File exists */
%[define_replacement(EFAULT          = __EFAULT)]         /* Bad address */
%[define_replacement(EFBIG           = __EFBIG)]          /* File too large */
%[define_replacement(EFTYPE          = __EFTYPE)]         /* Inappropriate file type or format */
%[define_replacement(EHOSTDOWN       = __EHOSTDOWN)]      /* Host is down */
%[define_replacement(EHOSTUNREACH    = __EHOSTUNREACH)]   /* No route to host */
%[define_replacement(EHWPOISON       = __EHWPOISON)]      /* Memory page has hardware error */
%[define_replacement(EIDRM           = __EIDRM)]          /* Identifier removed */
%[define_replacement(EILSEQ          = __EILSEQ)]         /* Illegal byte sequence */
%[define_replacement(EINPROGRESS     = __EINPROGRESS)]    /* Operation now in progress */
%[define_replacement(EINTR           = __EINTR)]          /* Interrupted system call */
%[define_replacement(EINVAL          = __EINVAL)]         /* Invalid argument */
%[define_replacement(EIO             = __EIO)]            /* I/O error */
%[define_replacement(EISCONN         = __EISCONN)]        /* Transport endpoint is already connected */
%[define_replacement(EISDIR          = __EISDIR)]         /* Is a directory */
%[define_replacement(EISNAM          = __EISNAM)]         /* Is a named type file */
%[define_replacement(EKEYEXPIRED     = __EKEYEXPIRED)]    /* Key has expired */
%[define_replacement(EKEYREJECTED    = __EKEYREJECTED)]   /* Key was rejected by service */
%[define_replacement(EKEYREVOKED     = __EKEYREVOKED)]    /* Key has been revoked */
%[define_replacement(EL2HLT          = __EL2HLT)]         /* Level 2 halted */
%[define_replacement(EL2NSYNC        = __EL2NSYNC)]       /* Level 2 not synchronized */
%[define_replacement(EL3HLT          = __EL3HLT)]         /* Level 3 halted */
%[define_replacement(EL3RST          = __EL3RST)]         /* Level 3 reset */
%[define_replacement(ELASTERROR      = __ELASTERROR)]     /* Users can add values starting here */
%[define_replacement(ELBIN           = __ELBIN)]          /* Inode is remote (not really error) */
%[define_replacement(ELIBACC         = __ELIBACC)]        /* Can not access a needed shared library */
%[define_replacement(ELIBBAD         = __ELIBBAD)]        /* Accessing a corrupted shared library */
%[define_replacement(ELIBEXEC        = __ELIBEXEC)]       /* Cannot exec a shared library directly */
%[define_replacement(ELIBMAX         = __ELIBMAX)]        /* Attempting to link in too many shared libraries */
%[define_replacement(ELIBSCN         = __ELIBSCN)]        /* .lib section in a.out corrupted */
%[define_replacement(ELIMIT          = __ELIMIT)]         /* Max possible errno */
%[define_replacement(ELNRNG          = __ELNRNG)]         /* Link number out of range */
%[define_replacement(ELOCKUNMAPPED   = __ELOCKUNMAPPED)]  /* ??? */
%[define_replacement(ELOOP           = __ELOOP)]          /* Too many symbolic links encountered */
%[define_replacement(EMAX            = __EMAX)]           /* Max errno */
%[define_replacement(EMEDIUMTYPE     = __EMEDIUMTYPE)]    /* Wrong medium type */
%[define_replacement(EMFILE          = __EMFILE)]         /* Too many open files */
%[define_replacement(EMLINK          = __EMLINK)]         /* Too many links */
%[define_replacement(EMSGSIZE        = __EMSGSIZE)]       /* Message too long */
%[define_replacement(EMULTIHOP       = __EMULTIHOP)]      /* Multihop attempted */
%[define_replacement(ENAMETOOLONG    = __ENAMETOOLONG)]   /* File name too long */
%[define_replacement(ENAVAIL         = __ENAVAIL)]        /* No XENIX semaphores available */
%[define_replacement(ENEEDAUTH       = __ENEEDAUTH)]      /* ??? */
%[define_replacement(ENETDOWN        = __ENETDOWN)]       /* Network is down */
%[define_replacement(ENETRESET       = __ENETRESET)]      /* Network dropped connection because of reset */
%[define_replacement(ENETUNREACH     = __ENETUNREACH)]    /* Network is unreachable */
%[define_replacement(ENFILE          = __ENFILE)]         /* File table overflow */
%[define_replacement(ENMFILE         = __ENMFILE)]        /* No more files */
%[define_replacement(ENOANO          = __ENOANO)]         /* No anode */
%[define_replacement(ENOATTR         = __ENOATTR)]        /* ??? */
%[define_replacement(ENOBUFS         = __ENOBUFS)]        /* No buffer space available */
%[define_replacement(ENOCSI          = __ENOCSI)]         /* No CSI structure available */
%[define_replacement(ENODATA         = __ENODATA)]        /* No data available */
%[define_replacement(ENODEV          = __ENODEV)]         /* No such device */
%[define_replacement(ENOENT          = __ENOENT)]         /* No such file or directory */
%[define_replacement(ENOEXEC         = __ENOEXEC)]        /* Exec format error */
%[define_replacement(ENOKEY          = __ENOKEY)]         /* Required key not available */
%[define_replacement(ENOLCK          = __ENOLCK)]         /* No record locks available */
%[define_replacement(ENOLINK         = __ENOLINK)]        /* Link has been severed */
%[define_replacement(ENOMEDIUM       = __ENOMEDIUM)]      /* No medium found */
%[define_replacement(ENOMEM          = __ENOMEM)]         /* Out of memory */
%[define_replacement(ENOMSG          = __ENOMSG)]         /* No message of desired type */
%[define_replacement(ENONET          = __ENONET)]         /* Machine is not on the network */
%[define_replacement(ENOPKG          = __ENOPKG)]         /* Package not installed */
%[define_replacement(ENOPROTOOPT     = __ENOPROTOOPT)]    /* Protocol not available */
%[define_replacement(ENOSHARE        = __ENOSHARE)]       /* No such host or network path */
%[define_replacement(ENOSPC          = __ENOSPC)]         /* No space left on device */
%[define_replacement(ENOSR           = __ENOSR)]          /* Out of streams resources */
%[define_replacement(ENOSTR          = __ENOSTR)]         /* Device not a stream */
%[define_replacement(ENOSYS          = __ENOSYS)]         /* Function not implemented */
%[define_replacement(ENOTACTIVE      = __ENOTACTIVE)]     /* ??? */
%[define_replacement(ENOTBLK         = __ENOTBLK)]        /* Block device required */
%[define_replacement(ENOTCONN        = __ENOTCONN)]       /* Transport endpoint is not connected */
%[define_replacement(ENOTDIR         = __ENOTDIR)]        /* Not a directory */
%[define_replacement(ENOTEMPTY       = __ENOTEMPTY)]      /* Directory not empty */
%[define_replacement(ENOTNAM         = __ENOTNAM)]        /* Not a XENIX named type file */
%[define_replacement(ENOTRECOVERABLE = __ENOTRECOVERABLE)]/* State not recoverable */
%[define_replacement(ENOTSOCK        = __ENOTSOCK)]       /* Socket operation on non-socket */
%[define_replacement(ENOTSUP         = __ENOTSUP)]        /* Not supported */
%[define_replacement(ENOTTY          = __ENOTTY)]         /* Not a typewriter */
%[define_replacement(ENOTUNIQ        = __ENOTUNIQ)]       /* Name not unique on network */
%[define_replacement(ENXIO           = __ENXIO)]          /* No such device or address */
%[define_replacement(EOK             = __EOK)]            /* Success */
%[define_replacement(EOPNOTSUPP      = __EOPNOTSUPP)]     /* Operation not supported on transport endpoint */
%[define_replacement(EOTHER          = __EOTHER)]         /* Other */
%[define_replacement(EOVERFLOW       = __EOVERFLOW)]      /* Value too large for defined data type */
%[define_replacement(EOWNERDEAD      = __EOWNERDEAD)]     /* Owner died */
%[define_replacement(EPERM           = __EPERM)]          /* Operation not permitted */
%[define_replacement(EPFNOSUPPORT    = __EPFNOSUPPORT)]   /* Protocol family not supported */
%[define_replacement(EPIPE           = __EPIPE)]          /* Broken pipe */
%[define_replacement(EPROCLIM        = __EPROCLIM)]       /* Process limit reached */
%[define_replacement(EPROCUNAVAIL    = __EPROCUNAVAIL)]   /* ??? */
%[define_replacement(EPROGMISMATCH   = __EPROGMISMATCH)]  /* ??? */
%[define_replacement(EPROGUNAVAIL    = __EPROGUNAVAIL)]   /* ??? */
%[define_replacement(EPROTO          = __EPROTO)]         /* Protocol error */
%[define_replacement(EPROTONOSUPPORT = __EPROTONOSUPPORT)]/* Protocol not supported */
%[define_replacement(EPROTOTYPE      = __EPROTOTYPE)]     /* Protocol wrong type for socket */
%[define_replacement(ERANGE          = __ERANGE)]         /* Math result not representable */
%[define_replacement(EREMCHG         = __EREMCHG)]        /* Remote address changed */
%[define_replacement(EREMOTE         = __EREMOTE)]        /* Object is remote */
%[define_replacement(EREMOTEIO       = __EREMOTEIO)]      /* Remote I/O error */
%[define_replacement(ERESTART        = __ERESTART)]       /* Interrupted system call should be restarted */
%[define_replacement(ERFKILL         = __ERFKILL)]        /* Operation not possible due to RF-kill */
%[define_replacement(EROFS           = __EROFS)]          /* Read-only file system */
%[define_replacement(ERPCMISMATCH    = __ERPCMISMATCH)]   /* ??? */
%[define_replacement(ESHUTDOWN       = __ESHUTDOWN)]      /* Cannot send after transport endpoint shutdown */
%[define_replacement(ESOCKTNOSUPPORT = __ESOCKTNOSUPPORT)]/* Socket type not supported */
%[define_replacement(ESPIPE          = __ESPIPE)]         /* Illegal seek */
%[define_replacement(ESRCH           = __ESRCH)]          /* No such process */
%[define_replacement(ESRMNT          = __ESRMNT)]         /* Srmount error */
%[define_replacement(ESTALE          = __ESTALE)]         /* Stale file handle */
%[define_replacement(ESTRPIPE        = __ESTRPIPE)]       /* Streams pipe error */
%[define_replacement(ETIME           = __ETIME)]          /* Timer expired */
%[define_replacement(ETIMEDOUT       = __ETIMEDOUT)]      /* Connection timed out */
%[define_replacement(ETOOMANYREFS    = __ETOOMANYREFS)]   /* Too many references: cannot splice */
%[define_replacement(ETXTBSY         = __ETXTBSY)]        /* Text file busy */
%[define_replacement(EUCLEAN         = __EUCLEAN)]        /* Structure needs cleaning */
%[define_replacement(EUNATCH         = __EUNATCH)]        /* Protocol driver not attached */
%[define_replacement(EUSERS          = __EUSERS)]         /* Too many users */
%[define_replacement(EWOULDBLOCK     = __EWOULDBLOCK)]    /* Operation would block */
%[define_replacement(EXDEV           = __EXDEV)]          /* Cross-device link */
%[define_replacement(EXFULL          = __EXFULL)]         /* Exchange full */
%[define_replacement(STRUNCATE       = __STRUNCATE)]      /* Truncated */
%{
#ifdef __E2BIG
#define E2BIG           __E2BIG           /* Argument list too long */
#endif /* __E2BIG */
#ifdef __EACCES
#define EACCES          __EACCES          /* Permission denied */
#endif /* __EACCES */
#ifdef __EADDRINUSE
#define EADDRINUSE      __EADDRINUSE      /* Address already in use */
#endif /* __EADDRINUSE */
#ifdef __EADDRNOTAVAIL
#define EADDRNOTAVAIL   __EADDRNOTAVAIL   /* Cannot assign requested address */
#endif /* __EADDRNOTAVAIL */
#ifdef __EADV
#define EADV            __EADV            /* Advertise error */
#endif /* __EADV */
#ifdef __EAFNOSUPPORT
#define EAFNOSUPPORT    __EAFNOSUPPORT    /* Address family not supported by protocol */
#endif /* __EAFNOSUPPORT */
#ifdef __EAGAIN
#define EAGAIN          __EAGAIN          /* Try again */
#endif /* __EAGAIN */
#ifdef __EALREADY
#define EALREADY        __EALREADY        /* Operation already in progress */
#endif /* __EALREADY */
#ifdef __EAUTH
#define EAUTH           __EAUTH           /* ??? */
#endif /* __EAUTH */
#ifdef __EBADE
#define EBADE           __EBADE           /* Invalid exchange */
#endif /* __EBADE */
#ifdef __EBADF
#define EBADF           __EBADF           /* Bad file number */
#endif /* __EBADF */
#ifdef __EBADFD
#define EBADFD          __EBADFD          /* File descriptor in bad state */
#endif /* __EBADFD */
#ifdef __EBADMSG
#define EBADMSG         __EBADMSG         /* Not a data message */
#endif /* __EBADMSG */
#ifdef __EBADR
#define EBADR           __EBADR           /* Invalid request descriptor */
#endif /* __EBADR */
#ifdef __EBADRPC
#define EBADRPC         __EBADRPC         /* ??? */
#endif /* __EBADRPC */
#ifdef __EBADRQC
#define EBADRQC         __EBADRQC         /* Invalid request code */
#endif /* __EBADRQC */
#ifdef __EBADSLT
#define EBADSLT         __EBADSLT         /* Invalid slot */
#endif /* __EBADSLT */
#ifdef __EBFONT
#define EBFONT          __EBFONT          /* Bad font file format */
#endif /* __EBFONT */
#ifdef __EBUSY
#define EBUSY           __EBUSY           /* Device or resource busy */
#endif /* __EBUSY */
#ifdef __ECANCELED
#define ECANCELED       __ECANCELED       /* Operation canceled */
#endif /* __ECANCELED */
#ifdef __ECASECLASH
#define ECASECLASH      __ECASECLASH      /* Filename exists with different case */
#endif /* __ECASECLASH */
#ifdef __ECHILD
#define ECHILD          __ECHILD          /* No child processes */
#endif /* __ECHILD */
#ifdef __ECHRNG
#define ECHRNG          __ECHRNG          /* Channel number out of range */
#endif /* __ECHRNG */
#ifdef __ECOMM
#define ECOMM           __ECOMM           /* Communication error on send */
#endif /* __ECOMM */
#ifdef __ECONNABORTED
#define ECONNABORTED    __ECONNABORTED    /* Software caused connection abort */
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
#define ECONNREFUSED    __ECONNREFUSED    /* Connection refused */
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
#define ECONNRESET      __ECONNRESET      /* Connection reset by peer */
#endif /* __ECONNRESET */
#ifdef __EDEADLK
#define EDEADLK         __EDEADLK         /* Resource deadlock would occur */
#endif /* __EDEADLK */
#ifdef __EDEADLOCK
#define EDEADLOCK       __EDEADLOCK       /* Resource deadlock would occur */
#endif /* __EDEADLOCK */
#ifdef __EDESTADDRREQ
#define EDESTADDRREQ    __EDESTADDRREQ    /* Destination address required */
#endif /* __EDESTADDRREQ */
#ifdef __EDOM
#define EDOM            __EDOM            /* Math argument out of domain of func */
#endif /* __EDOM */
#ifdef __EDOTDOT
#define EDOTDOT         __EDOTDOT         /* RFS specific error */
#endif /* __EDOTDOT */
#ifdef __EDQUOT
#define EDQUOT          __EDQUOT          /* Quota exceeded */
#endif /* __EDQUOT */
#ifdef __EEXIST
#define EEXIST          __EEXIST          /* File exists */
#endif /* __EEXIST */
#ifdef __EFAULT
#define EFAULT          __EFAULT          /* Bad address */
#endif /* __EFAULT */
#ifdef __EFBIG
#define EFBIG           __EFBIG           /* File too large */
#endif /* __EFBIG */
#ifdef __EFTYPE
#define EFTYPE          __EFTYPE          /* Inappropriate file type or format */
#endif /* __EFTYPE */
#ifdef __EHOSTDOWN
#define EHOSTDOWN       __EHOSTDOWN       /* Host is down */
#endif /* __EHOSTDOWN */
#ifdef __EHOSTUNREACH
#define EHOSTUNREACH    __EHOSTUNREACH    /* No route to host */
#endif /* __EHOSTUNREACH */
#ifdef __EHWPOISON
#define EHWPOISON       __EHWPOISON       /* Memory page has hardware error */
#endif /* __EHWPOISON */
#ifdef __EIDRM
#define EIDRM           __EIDRM           /* Identifier removed */
#endif /* __EIDRM */
#ifdef __EILSEQ
#define EILSEQ          __EILSEQ          /* Illegal byte sequence */
#endif /* __EILSEQ */
#ifdef __EINPROGRESS
#define EINPROGRESS     __EINPROGRESS     /* Operation now in progress */
#endif /* __EINPROGRESS */
#ifdef __EINTR
#define EINTR           __EINTR           /* Interrupted system call */
#endif /* __EINTR */
#ifdef __EINVAL
#define EINVAL          __EINVAL          /* Invalid argument */
#endif /* __EINVAL */
#ifdef __EIO
#define EIO             __EIO             /* I/O error */
#endif /* __EIO */
#ifdef __EISCONN
#define EISCONN         __EISCONN         /* Transport endpoint is already connected */
#endif /* __EISCONN */
#ifdef __EISDIR
#define EISDIR          __EISDIR          /* Is a directory */
#endif /* __EISDIR */
#ifdef __EISNAM
#define EISNAM          __EISNAM          /* Is a named type file */
#endif /* __EISNAM */
#ifdef __EKEYEXPIRED
#define EKEYEXPIRED     __EKEYEXPIRED     /* Key has expired */
#endif /* __EKEYEXPIRED */
#ifdef __EKEYREJECTED
#define EKEYREJECTED    __EKEYREJECTED    /* Key was rejected by service */
#endif /* __EKEYREJECTED */
#ifdef __EKEYREVOKED
#define EKEYREVOKED     __EKEYREVOKED     /* Key has been revoked */
#endif /* __EKEYREVOKED */
#ifdef __EL2HLT
#define EL2HLT          __EL2HLT          /* Level 2 halted */
#endif /* __EL2HLT */
#ifdef __EL2NSYNC
#define EL2NSYNC        __EL2NSYNC        /* Level 2 not synchronized */
#endif /* __EL2NSYNC */
#ifdef __EL3HLT
#define EL3HLT          __EL3HLT          /* Level 3 halted */
#endif /* __EL3HLT */
#ifdef __EL3RST
#define EL3RST          __EL3RST          /* Level 3 reset */
#endif /* __EL3RST */
#ifdef __ELBIN
#define ELBIN           __ELBIN           /* Inode is remote (not really error) */
#endif /* __ELBIN */
#ifdef __ELIBACC
#define ELIBACC         __ELIBACC         /* Can not access a needed shared library */
#endif /* __ELIBACC */
#ifdef __ELIBBAD
#define ELIBBAD         __ELIBBAD         /* Accessing a corrupted shared library */
#endif /* __ELIBBAD */
#ifdef __ELIBEXEC
#define ELIBEXEC        __ELIBEXEC        /* Cannot exec a shared library directly */
#endif /* __ELIBEXEC */
#ifdef __ELIBMAX
#define ELIBMAX         __ELIBMAX         /* Attempting to link in too many shared libraries */
#endif /* __ELIBMAX */
#ifdef __ELIBSCN
#define ELIBSCN         __ELIBSCN         /* .lib section in a.out corrupted */
#endif /* __ELIBSCN */
#ifdef __ELNRNG
#define ELNRNG          __ELNRNG          /* Link number out of range */
#endif /* __ELNRNG */
#ifdef __ELOCKUNMAPPED
#define ELOCKUNMAPPED   __ELOCKUNMAPPED   /* ??? */
#endif /* __ELOCKUNMAPPED */
#ifdef __ELOOP
#define ELOOP           __ELOOP           /* Too many symbolic links encountered */
#endif /* __ELOOP */
#ifdef __EMEDIUMTYPE
#define EMEDIUMTYPE     __EMEDIUMTYPE     /* Wrong medium type */
#endif /* __EMEDIUMTYPE */
#ifdef __EMFILE
#define EMFILE          __EMFILE          /* Too many open files */
#endif /* __EMFILE */
#ifdef __EMLINK
#define EMLINK          __EMLINK          /* Too many links */
#endif /* __EMLINK */
#ifdef __EMSGSIZE
#define EMSGSIZE        __EMSGSIZE        /* Message too long */
#endif /* __EMSGSIZE */
#ifdef __EMULTIHOP
#define EMULTIHOP       __EMULTIHOP       /* Multihop attempted */
#endif /* __EMULTIHOP */
#ifdef __ENAMETOOLONG
#define ENAMETOOLONG    __ENAMETOOLONG    /* File name too long */
#endif /* __ENAMETOOLONG */
#ifdef __ENAVAIL
#define ENAVAIL         __ENAVAIL         /* No XENIX semaphores available */
#endif /* __ENAVAIL */
#ifdef __ENEEDAUTH
#define ENEEDAUTH       __ENEEDAUTH       /* ??? */
#endif /* __ENEEDAUTH */
#ifdef __ENETDOWN
#define ENETDOWN        __ENETDOWN        /* Network is down */
#endif /* __ENETDOWN */
#ifdef __ENETRESET
#define ENETRESET       __ENETRESET       /* Network dropped connection because of reset */
#endif /* __ENETRESET */
#ifdef __ENETUNREACH
#define ENETUNREACH     __ENETUNREACH     /* Network is unreachable */
#endif /* __ENETUNREACH */
#ifdef __ENFILE
#define ENFILE          __ENFILE          /* File table overflow */
#endif /* __ENFILE */
#ifdef __ENMFILE
#define ENMFILE         __ENMFILE         /* No more files */
#endif /* __ENMFILE */
#ifdef __ENOANO
#define ENOANO          __ENOANO          /* No anode */
#endif /* __ENOANO */
#ifdef __ENOATTR
#define ENOATTR         __ENOATTR         /* ??? */
#endif /* __ENOATTR */
#ifdef __ENOBUFS
#define ENOBUFS         __ENOBUFS         /* No buffer space available */
#endif /* __ENOBUFS */
#ifdef __ENOCSI
#define ENOCSI          __ENOCSI          /* No CSI structure available */
#endif /* __ENOCSI */
#ifdef __ENODATA
#define ENODATA         __ENODATA         /* No data available */
#endif /* __ENODATA */
#ifdef __ENODEV
#define ENODEV          __ENODEV          /* No such device */
#endif /* __ENODEV */
#ifdef __ENOENT
#define ENOENT          __ENOENT          /* No such file or directory */
#endif /* __ENOENT */
#ifdef __ENOEXEC
#define ENOEXEC         __ENOEXEC         /* Exec format error */
#endif /* __ENOEXEC */
#ifdef __ENOKEY
#define ENOKEY          __ENOKEY          /* Required key not available */
#endif /* __ENOKEY */
#ifdef __ENOLCK
#define ENOLCK          __ENOLCK          /* No record locks available */
#endif /* __ENOLCK */
#ifdef __ENOLINK
#define ENOLINK         __ENOLINK         /* Link has been severed */
#endif /* __ENOLINK */
#ifdef __ENOMEDIUM
#define ENOMEDIUM       __ENOMEDIUM       /* No medium found */
#endif /* __ENOMEDIUM */
#ifdef __ENOMEM
#define ENOMEM          __ENOMEM          /* Out of memory */
#endif /* __ENOMEM */
#ifdef __ENOMSG
#define ENOMSG          __ENOMSG          /* No message of desired type */
#endif /* __ENOMSG */
#ifdef __ENONET
#define ENONET          __ENONET          /* Machine is not on the network */
#endif /* __ENONET */
#ifdef __ENOPKG
#define ENOPKG          __ENOPKG          /* Package not installed */
#endif /* __ENOPKG */
#ifdef __ENOPROTOOPT
#define ENOPROTOOPT     __ENOPROTOOPT     /* Protocol not available */
#endif /* __ENOPROTOOPT */
#ifdef __ENOSHARE
#define ENOSHARE        __ENOSHARE        /* No such host or network path */
#endif /* __ENOSHARE */
#ifdef __ENOSPC
#define ENOSPC          __ENOSPC          /* No space left on device */
#endif /* __ENOSPC */
#ifdef __ENOSR
#define ENOSR           __ENOSR           /* Out of streams resources */
#endif /* __ENOSR */
#ifdef __ENOSTR
#define ENOSTR          __ENOSTR          /* Device not a stream */
#endif /* __ENOSTR */
#ifdef __ENOSYS
#define ENOSYS          __ENOSYS          /* Function not implemented */
#endif /* __ENOSYS */
#ifdef __ENOTACTIVE
#define ENOTACTIVE      __ENOTACTIVE      /* ??? */
#endif /* __ENOTACTIVE */
#ifdef __ENOTBLK
#define ENOTBLK         __ENOTBLK         /* Block device required */
#endif /* __ENOTBLK */
#ifdef __ENOTCONN
#define ENOTCONN        __ENOTCONN        /* Transport endpoint is not connected */
#endif /* __ENOTCONN */
#ifdef __ENOTDIR
#define ENOTDIR         __ENOTDIR         /* Not a directory */
#endif /* __ENOTDIR */
#ifdef __ENOTEMPTY
#define ENOTEMPTY       __ENOTEMPTY       /* Directory not empty */
#endif /* __ENOTEMPTY */
#ifdef __ENOTNAM
#define ENOTNAM         __ENOTNAM         /* Not a XENIX named type file */
#endif /* __ENOTNAM */
#ifdef __ENOTRECOVERABLE
#define ENOTRECOVERABLE __ENOTRECOVERABLE /* State not recoverable */
#endif /* __ENOTRECOVERABLE */
#ifdef __ENOTSOCK
#define ENOTSOCK        __ENOTSOCK        /* Socket operation on non-socket */
#endif /* __ENOTSOCK */
#ifdef __ENOTSUP
#define ENOTSUP         __ENOTSUP         /* Not supported */
#endif /* __ENOTSUP */
#ifdef __ENOTTY
#define ENOTTY          __ENOTTY          /* Not a typewriter */
#endif /* __ENOTTY */
#ifdef __ENOTUNIQ
#define ENOTUNIQ        __ENOTUNIQ        /* Name not unique on network */
#endif /* __ENOTUNIQ */
#ifdef __ENXIO
#define ENXIO           __ENXIO           /* No such device or address */
#endif /* __ENXIO */
#ifdef __EOPNOTSUPP
#define EOPNOTSUPP      __EOPNOTSUPP      /* Operation not supported on transport endpoint */
#endif /* __EOPNOTSUPP */
#ifdef __EOTHER
#define EOTHER          __EOTHER          /* Other */
#endif /* __EOTHER */
#ifdef __EOVERFLOW
#define EOVERFLOW       __EOVERFLOW       /* Value too large for defined data type */
#endif /* __EOVERFLOW */
#ifdef __EOWNERDEAD
#define EOWNERDEAD      __EOWNERDEAD      /* Owner died */
#endif /* __EOWNERDEAD */
#ifdef __EPERM
#define EPERM           __EPERM           /* Operation not permitted */
#endif /* __EPERM */
#ifdef __EPFNOSUPPORT
#define EPFNOSUPPORT    __EPFNOSUPPORT    /* Protocol family not supported */
#endif /* __EPFNOSUPPORT */
#ifdef __EPIPE
#define EPIPE           __EPIPE           /* Broken pipe */
#endif /* __EPIPE */
#ifdef __EPROCLIM
#define EPROCLIM        __EPROCLIM        /* Process limit reached */
#endif /* __EPROCLIM */
#ifdef __EPROCUNAVAIL
#define EPROCUNAVAIL    __EPROCUNAVAIL    /* ??? */
#endif /* __EPROCUNAVAIL */
#ifdef __EPROGMISMATCH
#define EPROGMISMATCH   __EPROGMISMATCH   /* ??? */
#endif /* __EPROGMISMATCH */
#ifdef __EPROGUNAVAIL
#define EPROGUNAVAIL    __EPROGUNAVAIL    /* ??? */
#endif /* __EPROGUNAVAIL */
#ifdef __EPROTO
#define EPROTO          __EPROTO          /* Protocol error */
#endif /* __EPROTO */
#ifdef __EPROTONOSUPPORT
#define EPROTONOSUPPORT __EPROTONOSUPPORT /* Protocol not supported */
#endif /* __EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
#define EPROTOTYPE      __EPROTOTYPE      /* Protocol wrong type for socket */
#endif /* __EPROTOTYPE */
#ifdef __ERANGE
#define ERANGE          __ERANGE          /* Math result not representable */
#endif /* __ERANGE */
#ifdef __EREMCHG
#define EREMCHG         __EREMCHG         /* Remote address changed */
#endif /* __EREMCHG */
#ifdef __EREMOTE
#define EREMOTE         __EREMOTE         /* Object is remote */
#endif /* __EREMOTE */
#ifdef __EREMOTEIO
#define EREMOTEIO       __EREMOTEIO       /* Remote I/O error */
#endif /* __EREMOTEIO */
#ifdef __ERESTART
#define ERESTART        __ERESTART        /* Interrupted system call should be restarted */
#endif /* __ERESTART */
#ifdef __ERFKILL
#define ERFKILL         __ERFKILL         /* Operation not possible due to RF-kill */
#endif /* __ERFKILL */
#ifdef __EROFS
#define EROFS           __EROFS           /* Read-only file system */
#endif /* __EROFS */
#ifdef __ERPCMISMATCH
#define ERPCMISMATCH    __ERPCMISMATCH    /* ??? */
#endif /* __ERPCMISMATCH */
#ifdef __ESHUTDOWN
#define ESHUTDOWN       __ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#endif /* __ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT __ESOCKTNOSUPPORT /* Socket type not supported */
#endif /* __ESOCKTNOSUPPORT */
#ifdef __ESPIPE
#define ESPIPE          __ESPIPE          /* Illegal seek */
#endif /* __ESPIPE */
#ifdef __ESRCH
#define ESRCH           __ESRCH           /* No such process */
#endif /* __ESRCH */
#ifdef __ESRMNT
#define ESRMNT          __ESRMNT          /* Srmount error */
#endif /* __ESRMNT */
#ifdef __ESTALE
#define ESTALE          __ESTALE          /* Stale file handle */
#endif /* __ESTALE */
#ifdef __ESTRPIPE
#define ESTRPIPE        __ESTRPIPE        /* Streams pipe error */
#endif /* __ESTRPIPE */
#ifdef __ETIME
#define ETIME           __ETIME           /* Timer expired */
#endif /* __ETIME */
#ifdef __ETIMEDOUT
#define ETIMEDOUT       __ETIMEDOUT       /* Connection timed out */
#endif /* __ETIMEDOUT */
#ifdef __ETOOMANYREFS
#define ETOOMANYREFS    __ETOOMANYREFS    /* Too many references: cannot splice */
#endif /* __ETOOMANYREFS */
#ifdef __ETXTBSY
#define ETXTBSY         __ETXTBSY         /* Text file busy */
#endif /* __ETXTBSY */
#ifdef __EUCLEAN
#define EUCLEAN         __EUCLEAN         /* Structure needs cleaning */
#endif /* __EUCLEAN */
#ifdef __EUNATCH
#define EUNATCH         __EUNATCH         /* Protocol driver not attached */
#endif /* __EUNATCH */
#ifdef __EUSERS
#define EUSERS          __EUSERS          /* Too many users */
#endif /* __EUSERS */
#ifdef __EWOULDBLOCK
#define EWOULDBLOCK     __EWOULDBLOCK     /* Operation would block */
#endif /* __EWOULDBLOCK */
#ifdef __EXDEV
#define EXDEV           __EXDEV           /* Cross-device link */
#endif /* __EXDEV */
#ifdef __EXFULL
#define EXFULL          __EXFULL          /* Exchange full */
#endif /* __EXFULL */
#ifdef __STRUNCATE
#define STRUNCATE       __STRUNCATE       /* Truncated */
#endif /* __STRUNCATE */
}
/*[[[end]]]*/
%{






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
#ifdef __ELIMIT
#define ELAST __ELIMIT /* Max possible errno */
#endif /* __ELIMIT */
#endif /* __USE_NETBSD */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifdef __EOK
#define EOK    __EOK    /* Operation completed successfully */
#endif /* __EOK */
#ifdef __EMAX
#define EMAX   __EMAX   /* Max errno */
#endif /* __EMAX */
#ifdef __ECOUNT
#define ECOUNT __ECOUNT /* Max errno + 1 */
#endif /* __ECOUNT */
#ifdef __ELIMIT
#define ELIMIT __ELIMIT /* Max possible errno */
#endif /* __ELIMIT */
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#if defined(__USE_KOS_KERNEL) && defined(__ELIMIT)
/* Helper macros for testing the return values of
 * system calls (s.a. <kos/syscalls.h>) in errno-mode */
#define E_ISOK(x)  (__CCAST(__syscall_ulong_t)(x) <= __CCAST(__syscall_ulong_t)-__ELIMIT)
#define E_ISERR(x) (__CCAST(__syscall_ulong_t)(x) > __CCAST(__syscall_ulong_t)-__ELIMIT)
#endif /* __USE_KOS_KERNEL && __ELIMIT */

#ifdef __CC__

__SYSDECL_BEGIN

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#endif /* __USE_KOS || __USE_KOS_KERNEL */


/* The `errno' global variable! */
#ifndef errno
#ifdef __libc_errno
#define errno __libc_errno
#else /* __libc_errno */
}
%(libc_fast){
#ifndef __libc_errno
#ifdef errno
#define __libc_errno errno
#else /* errno */
}

[[libc, guard, alias("_errno", "__errno"), wunused]]
[[ATTR_CONST, section(".text.crt{|.dos}.errno_access")]]
[[decl_include("<bits/types.h>")]]
[[nonnull]] $errno_t *__errno_location();

%(libc_fast){
#ifdef ____libc___errno_location_defined
#define __libc_errno (*__libc___errno_location())
#elif defined(__CRT_HAVE_errno) && 0
__DECL_BEGIN
__LIBC __ATTR_THREAD __errno_t errno;
__DECL_END
#define errno        errno
#define __libc_errno errno
#elif defined(__CRT_HAVE_errno)
__DECL_BEGIN
__LIBC __errno_t errno;
__DECL_END
#define errno        errno
#define __libc_errno errno
#endif /* ... */
#endif /* !__libc_errno */
#endif /* !errno */
}

%{
#ifdef ____errno_location_defined
#define errno (*__errno_location())
#elif defined(__CRT_HAVE_errno) && 0
__LIBC __ATTR_THREAD __errno_t errno;
#define errno  errno
#elif defined(__CRT_HAVE_errno)
__LIBC __errno_t errno;
#define errno  errno
#endif /* ... */
#endif /* !__libc_errno */
#endif /* !errno */
}

%(libc_fast){
#if !defined(__libc_geterrno) && defined(__libc_errno)
#define __libc_geterrno() __libc_errno
#endif /* !__libc_geterrno && __libc_errno */

#ifndef __libc_geterrno_or
#ifdef __libc_errno
#define __libc_geterrno_or(alt) __libc_errno
#else /* __libc_errno */
#define __libc_geterrno_or(alt) alt
#endif /* !__libc_errno */
#endif /* !__libc_geterrno_or */

#ifndef __libc_seterrno
#ifdef __libc_errno
#define __libc_seterrno(val) (__libc_errno = (val), -1)
#else /* __libc_errno */
#define __libc_seterrno(val) (-1)
#endif /* !__libc_errno */
#endif /* !__libc_seterrno */
}


%{

#ifdef __USE_GNU

/* Alias for argv[0], as passed to main() */
#ifndef program_invocation_name
#ifdef _pgmptr
#define program_invocation_name _pgmptr
#elif defined(_pgmptr)
#define program_invocation_name __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
__LIBC char *program_invocation_name;
#define program_invocation_name program_invocation_name
#elif defined(__CRT_HAVE__pgmptr)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_name __ASMNAME("_pgmptr");
#define program_invocation_name  program_invocation_name
#else /* !__NO_ASMNAME */
__LIBC char *_pgmptr;
#define _pgmptr                 _pgmptr
#define program_invocation_name _pgmptr
#endif /* __NO_ASMNAME */
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_name __ASMNAME("__progname_full");
#define program_invocation_name  program_invocation_name
#else /* !__NO_ASMNAME */
__LIBC char *__progname_full;
#define __progname_full         __progname_full
#define program_invocation_name __progname_full
#endif /* __NO_ASMNAME */
#else /* ... */
}
%[insert:extern(__p__pgmptr)]
%{
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
__LIBC char *program_invocation_short_name;
#define program_invocation_short_name program_invocation_short_name
#elif defined(__CRT_HAVE___progname)
#ifndef __NO_ASMNAME
__LIBC char *program_invocation_short_name __ASMNAME("__progname");
#define program_invocation_short_name  program_invocation_short_name
#else /* !__NO_ASMNAME */
__LIBC char *__progname;
#define __progname                    __progname
#define program_invocation_short_name __progname
#endif /* __NO_ASMNAME */
#else /* ... */
}
@@Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main()
[[guard, wunused, ATTR_CONST, nonnull]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_short_name_p))]]
char **__p_program_invocation_short_name() {
	return &__LOCAL_program_invocation_short_name_p;
}
%{
#ifdef ____p__pgmptr_defined
#define program_invocation_name (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !program_invocation_short_name */

#ifndef __error_t_defined
#define __error_t_defined 1
typedef __errno_t error_t;
#endif /* !__error_t_defined */

#endif /* __USE_GNU */

__SYSDECL_END

#ifdef __USE_NETBSD
#include <bits/crt/sys_errlist.h>
#endif /* __USE_NETBSD */

#endif /* __CC__ */

}
