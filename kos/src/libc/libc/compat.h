/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_COMPAT_H
#define GUARD_LIBC_LIBC_COMPAT_H 1

#include "../api.h"

DECL_BEGIN

/* Errno codes from emulated libcs */
/*[[[deemon
import * from deemon;
local printed_contexts = { "dos", "cygwin" };

@@Mapping for context -> {id -> (dosName, comment)}
local errnoMappings: {string: {int: (string, string)}} = Dict();

for (local contextName: printed_contexts)
with (local fp = File.open("../../../include/asm/os/" + contextName + "/errno.h")) {
	local inside = false;
	for (local l: fp) {
		l = l.strip();
		local final PREFIX = "/" "*[[[begin:";
		local final SUFFIX = "]]]*" "/";
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
		local contextMap = errnoMappings.get(contextName);
		if (contextMap is none)
			errnoMappings[contextName] = contextMap = Dict();
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
	if (contextName == "cygwin")
		contextName = "cyg";
	local context_emax = contextMap.keys > ...;
	local context_errno_t;
	if (context_emax > 0xffff) {
		context_errno_t = "uint32_t";
	} else if (context_emax > 0xff) {
		context_errno_t = "uint16_t";
	} else {
		context_errno_t = "uint8_t";
	}
	print("#ifdef __CC__");
	print("typedef ", context_errno_t, " ", contextName, "_errno_t;");
	print("#endif /" "* __CC__ *" "/");
	local longestErrnoName = contextMap.values.each.first.length > ...;
	local longestContextErrcode = #str(context_emax);
	for (local i: [:context_emax + 1]) {
		local name, comment = contextMap.get(i)...;
		if (name is none)
			continue;
		print("#define ", contextName.upper(), "_",
			name, " " * (longestErrnoName - #name), " ",
			i, " " * (longestContextErrcode - #str(i)),
			" /" "* ", comment, " *" "/");
	}
	print("#define ", contextName.upper(), "_EMAX   ", context_emax);
	print("#define ", contextName.upper(), "_ECOUNT ", context_emax + 1);
}
]]]*/
/* Errno codes for DOS */
#ifdef __CC__
typedef uint8_t dos_errno_t;
#endif /* __CC__ */
#define DOS_EPERM           1   /* Operation not permitted */
#define DOS_ENOENT          2   /* No such file or directory */
#define DOS_ESRCH           3   /* No such process */
#define DOS_EINTR           4   /* Interrupted system call */
#define DOS_EIO             5   /* I/O error */
#define DOS_ENXIO           6   /* No such device or address */
#define DOS_E2BIG           7   /* Argument list too long */
#define DOS_ENOEXEC         8   /* Exec format error */
#define DOS_EBADF           9   /* Bad file number */
#define DOS_ECHILD          10  /* No child processes */
#define DOS_EAGAIN          11  /* Try again */
#define DOS_ENOMEM          12  /* Out of memory */
#define DOS_EACCES          13  /* Permission denied */
#define DOS_EFAULT          14  /* Bad address */
#define DOS_EBUSY           16  /* Device or resource busy */
#define DOS_EEXIST          17  /* File exists */
#define DOS_EXDEV           18  /* Cross-device link */
#define DOS_ENODEV          19  /* No such device */
#define DOS_ENOTDIR         20  /* Not a directory */
#define DOS_EISDIR          21  /* Is a directory */
#define DOS_EINVAL          22  /* Invalid argument */
#define DOS_ENFILE          23  /* File table overflow */
#define DOS_EMFILE          24  /* Too many open files */
#define DOS_ENOTTY          25  /* Not a typewriter */
#define DOS_EFBIG           27  /* File too large */
#define DOS_ENOSPC          28  /* No space left on device */
#define DOS_ESPIPE          29  /* Illegal seek */
#define DOS_EROFS           30  /* Read-only file system */
#define DOS_EMLINK          31  /* Too many links */
#define DOS_EPIPE           32  /* Broken pipe */
#define DOS_EDOM            33  /* Math argument out of domain of func */
#define DOS_ERANGE          34  /* Math result not representable */
#define DOS_EDEADLK         36  /* Resource deadlock would occur */
#define DOS_ENAMETOOLONG    38  /* File name too long */
#define DOS_ENOLCK          39  /* No record locks available */
#define DOS_ENOSYS          40  /* Function not implemented */
#define DOS_ENOTEMPTY       41  /* Directory not empty */
#define DOS_EILSEQ          42  /* Illegal byte sequence */
#define DOS_STRUNCATE       80  /* Truncated */
#define DOS_EADDRINUSE      100 /* Address already in use */
#define DOS_EADDRNOTAVAIL   101 /* Cannot assign requested address */
#define DOS_EAFNOSUPPORT    102 /* Address family not supported by protocol */
#define DOS_EALREADY        103 /* Operation already in progress */
#define DOS_EBADMSG         104 /* Not a data message */
#define DOS_ECANCELED       105 /* Operation canceled */
#define DOS_ECONNABORTED    106 /* Software caused connection abort */
#define DOS_ECONNREFUSED    107 /* Connection refused */
#define DOS_ECONNRESET      108 /* Connection reset by peer */
#define DOS_EDESTADDRREQ    109 /* Destination address required */
#define DOS_EHOSTUNREACH    110 /* No route to host */
#define DOS_EIDRM           111 /* Identifier removed */
#define DOS_EINPROGRESS     112 /* Operation now in progress */
#define DOS_EISCONN         113 /* Transport endpoint is already connected */
#define DOS_ELOOP           114 /* Too many symbolic links encountered */
#define DOS_EMSGSIZE        115 /* Message too long */
#define DOS_ENETDOWN        116 /* Network is down */
#define DOS_ENETRESET       117 /* Network dropped connection because of reset */
#define DOS_ENETUNREACH     118 /* Network is unreachable */
#define DOS_ENOBUFS         119 /* No buffer space available */
#define DOS_ENODATA         120 /* No data available */
#define DOS_ENOLINK         121 /* Link has been severed */
#define DOS_ENOMSG          122 /* No message of desired type */
#define DOS_ENOPROTOOPT     123 /* Protocol not available */
#define DOS_ENOSR           124 /* Out of streams resources */
#define DOS_ENOSTR          125 /* Device not a stream */
#define DOS_ENOTCONN        126 /* Transport endpoint is not connected */
#define DOS_ENOTRECOVERABLE 127 /* State not recoverable */
#define DOS_ENOTSOCK        128 /* Socket operation on non-socket */
#define DOS_ENOTSUP         129 /* Not supported */
#define DOS_EOPNOTSUPP      130 /* Operation not supported on transport endpoint */
#define DOS_EOTHER          131 /* Other */
#define DOS_EOVERFLOW       132 /* Value too large for defined data type */
#define DOS_EOWNERDEAD      133 /* Owner died */
#define DOS_EPROTO          134 /* Protocol error */
#define DOS_EPROTONOSUPPORT 135 /* Protocol not supported */
#define DOS_EPROTOTYPE      136 /* Protocol wrong type for socket */
#define DOS_ETIME           137 /* Timer expired */
#define DOS_ETIMEDOUT       138 /* Connection timed out */
#define DOS_ETXTBSY         139 /* Text file busy */
#define DOS_EWOULDBLOCK     140 /* Operation would block */
#define DOS_EMAX   140
#define DOS_ECOUNT 141

/* Errno codes for CYGWIN */
#ifdef __CC__
typedef uint8_t cyg_errno_t;
#endif /* __CC__ */
#define CYG_EPERM           1   /* Operation not permitted */
#define CYG_ENOENT          2   /* No such file or directory */
#define CYG_ESRCH           3   /* No such process */
#define CYG_EINTR           4   /* Interrupted system call */
#define CYG_EIO             5   /* I/O error */
#define CYG_ENXIO           6   /* No such device or address */
#define CYG_E2BIG           7   /* Argument list too long */
#define CYG_ENOEXEC         8   /* Exec format error */
#define CYG_EBADF           9   /* Bad file number */
#define CYG_ECHILD          10  /* No child processes */
#define CYG_EAGAIN          11  /* Try again */
#define CYG_ENOMEM          12  /* Out of memory */
#define CYG_EACCES          13  /* Permission denied */
#define CYG_EFAULT          14  /* Bad address */
#define CYG_ENOTBLK         15  /* Block device required */
#define CYG_EBUSY           16  /* Device or resource busy */
#define CYG_EEXIST          17  /* File exists */
#define CYG_EXDEV           18  /* Cross-device link */
#define CYG_ENODEV          19  /* No such device */
#define CYG_ENOTDIR         20  /* Not a directory */
#define CYG_EISDIR          21  /* Is a directory */
#define CYG_EINVAL          22  /* Invalid argument */
#define CYG_ENFILE          23  /* File table overflow */
#define CYG_EMFILE          24  /* Too many open files */
#define CYG_ENOTTY          25  /* Not a typewriter */
#define CYG_ETXTBSY         26  /* Text file busy */
#define CYG_EFBIG           27  /* File too large */
#define CYG_ENOSPC          28  /* No space left on device */
#define CYG_ESPIPE          29  /* Illegal seek */
#define CYG_EROFS           30  /* Read-only file system */
#define CYG_EMLINK          31  /* Too many links */
#define CYG_EPIPE           32  /* Broken pipe */
#define CYG_EDOM            33  /* Math argument out of domain of func */
#define CYG_ERANGE          34  /* Math result not representable */
#define CYG_ENOMSG          35  /* No message of desired type */
#define CYG_EIDRM           36  /* Identifier removed */
#define CYG_ECHRNG          37  /* Channel number out of range */
#define CYG_EL2NSYNC        38  /* Level 2 not synchronized */
#define CYG_EL3HLT          39  /* Level 3 halted */
#define CYG_EL3RST          40  /* Level 3 reset */
#define CYG_ELNRNG          41  /* Link number out of range */
#define CYG_EUNATCH         42  /* Protocol driver not attached */
#define CYG_ENOCSI          43  /* No CSI structure available */
#define CYG_EL2HLT          44  /* Level 2 halted */
#define CYG_EDEADLK         45  /* Resource deadlock would occur */
#define CYG_ENOLCK          46  /* No record locks available */
#define CYG_EBADE           50  /* Invalid exchange */
#define CYG_EBADR           51  /* Invalid request descriptor */
#define CYG_EXFULL          52  /* Exchange full */
#define CYG_ENOANO          53  /* No anode */
#define CYG_EBADRQC         54  /* Invalid request code */
#define CYG_EBADSLT         55  /* Invalid slot */
#define CYG_EDEADLOCK       56  /* Resource deadlock would occur */
#define CYG_EBFONT          57  /* Bad font file format */
#define CYG_ENOSTR          60  /* Device not a stream */
#define CYG_ENODATA         61  /* No data available */
#define CYG_ETIME           62  /* Timer expired */
#define CYG_ENOSR           63  /* Out of streams resources */
#define CYG_ENONET          64  /* Machine is not on the network */
#define CYG_ENOPKG          65  /* Package not installed */
#define CYG_EREMOTE         66  /* Object is remote */
#define CYG_ENOLINK         67  /* Link has been severed */
#define CYG_EADV            68  /* Advertise error */
#define CYG_ESRMNT          69  /* Srmount error */
#define CYG_ECOMM           70  /* Communication error on send */
#define CYG_EPROTO          71  /* Protocol error */
#define CYG_EMULTIHOP       74  /* Multihop attempted */
#define CYG_ELBIN           75  /* Inode is remote (not really error) */
#define CYG_EDOTDOT         76  /* RFS specific error */
#define CYG_EBADMSG         77  /* Not a data message */
#define CYG_EFTYPE          79  /* Inappropriate file type or format */
#define CYG_ENOTUNIQ        80  /* Name not unique on network */
#define CYG_EBADFD          81  /* File descriptor in bad state */
#define CYG_EREMCHG         82  /* Remote address changed */
#define CYG_ELIBACC         83  /* Can not access a needed shared library */
#define CYG_ELIBBAD         84  /* Accessing a corrupted shared library */
#define CYG_ELIBSCN         85  /* .lib section in a.out corrupted */
#define CYG_ELIBMAX         86  /* Attempting to link in too many shared libraries */
#define CYG_ELIBEXEC        87  /* Cannot exec a shared library directly */
#define CYG_ENOSYS          88  /* Function not implemented */
#define CYG_ENMFILE         89  /* No more files */
#define CYG_ENOTEMPTY       90  /* Directory not empty */
#define CYG_ENAMETOOLONG    91  /* File name too long */
#define CYG_ELOOP           92  /* Too many symbolic links encountered */
#define CYG_EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define CYG_EPFNOSUPPORT    96  /* Protocol family not supported */
#define CYG_ECONNRESET      104 /* Connection reset by peer */
#define CYG_ENOBUFS         105 /* No buffer space available */
#define CYG_EAFNOSUPPORT    106 /* Address family not supported by protocol */
#define CYG_EPROTOTYPE      107 /* Protocol wrong type for socket */
#define CYG_ENOTSOCK        108 /* Socket operation on non-socket */
#define CYG_ENOPROTOOPT     109 /* Protocol not available */
#define CYG_ESHUTDOWN       110 /* Cannot send after transport endpoint shutdown */
#define CYG_ECONNREFUSED    111 /* Connection refused */
#define CYG_EADDRINUSE      112 /* Address already in use */
#define CYG_ECONNABORTED    113 /* Software caused connection abort */
#define CYG_ENETUNREACH     114 /* Network is unreachable */
#define CYG_ENETDOWN        115 /* Network is down */
#define CYG_ETIMEDOUT       116 /* Connection timed out */
#define CYG_EHOSTDOWN       117 /* Host is down */
#define CYG_EHOSTUNREACH    118 /* No route to host */
#define CYG_EINPROGRESS     119 /* Operation now in progress */
#define CYG_EALREADY        120 /* Operation already in progress */
#define CYG_EDESTADDRREQ    121 /* Destination address required */
#define CYG_EMSGSIZE        122 /* Message too long */
#define CYG_EPROTONOSUPPORT 123 /* Protocol not supported */
#define CYG_ESOCKTNOSUPPORT 124 /* Socket type not supported */
#define CYG_EADDRNOTAVAIL   125 /* Cannot assign requested address */
#define CYG_ENETRESET       126 /* Network dropped connection because of reset */
#define CYG_EISCONN         127 /* Transport endpoint is already connected */
#define CYG_ENOTCONN        128 /* Transport endpoint is not connected */
#define CYG_ETOOMANYREFS    129 /* Too many references: cannot splice */
#define CYG_EPROCLIM        130 /* Process limit reached */
#define CYG_EUSERS          131 /* Too many users */
#define CYG_EDQUOT          132 /* Quota exceeded */
#define CYG_ESTALE          133 /* Stale file handle */
#define CYG_ENOTSUP         134 /* Not supported */
#define CYG_ENOMEDIUM       135 /* No medium found */
#define CYG_ENOSHARE        136 /* No such host or network path */
#define CYG_ECASECLASH      137 /* Filename exists with different case */
#define CYG_EILSEQ          138 /* Illegal byte sequence */
#define CYG_EOVERFLOW       139 /* Value too large for defined data type */
#define CYG_ECANCELED       140 /* Operation canceled */
#define CYG_ENOTRECOVERABLE 141 /* State not recoverable */
#define CYG_EOWNERDEAD      142 /* Owner died */
#define CYG_ESTRPIPE        143 /* Streams pipe error */
#define CYG_EMAX   143
#define CYG_ECOUNT 144
/*[[[end]]]*/

/*[[[deemon
import * from deemon;

function repeatEscapedMacrosFromFile(
		filename: string, prefix: string, repeatPrefix: string) {
	local macros: {string: string} = Dict();
	for (local l: File.open(filename)) {
		local name, value;
		try {
			name, value = l.scanf(" # define %[^ ] %[^]")...;
		} catch (...) {
			continue;
		}
		name  = name.strip();
		value = value.strip();
		if (!name.startswith(prefix))
			continue;
		macros[name[#prefix:]] = value;
	}
	local longestMacroName = macros.keys.each.length > ...;
	for (local name: macros.keys.sorted()) {
		print("#define ", repeatPrefix, name, " " * (longestMacroName - #name), " ", macros[name]);
	}
}
repeatEscapedMacrosFromFile("../../../include/asm/os/dos/signal.h", "__", "DOS_");

]]]*/
#define DOS_NSIG           33 /* Biggest signal number + 1 (including real-time signals). */
#define DOS_SIGABRT        22 /* Abort (ANSI). */
#define DOS_SIGABRT_COMPAT 6  /* Abort (ANSI). */
#define DOS_SIGBREAK       21 /* Background read from tty (POSIX). */
#define DOS_SIGFPE         8  /* Floating-point exception (ANSI). */
#define DOS_SIGILL         4  /* Illegal instruction (ANSI). */
#define DOS_SIGINT         2  /* Interrupt (ANSI). */
#define DOS_SIGSEGV        11 /* Segmentation violation (ANSI). */
#define DOS_SIGTERM        15 /* Termination (ANSI). */
#define DOS_SIG_ACK        4    /* Acknowledge. */
#define DOS_SIG_DFL        0    /* Default action. */
#define DOS_SIG_ERR        (-1) /* Error return. */
#define DOS_SIG_GET        2    /* Return current value. */
#define DOS_SIG_IGN        1    /* Ignore signal. */
#define DOS_SIG_SGE        3    /* Signal gets error. */
/*[[[end]]]*/



/* Compatibility mode flags. */
#define COMPAT_FLAG_NORMAL                   0x00000000 /* No special compat flags. */
#define COMPAT_FLAG_CALLED___libc_init       0x00000001 /* `__libc_init()' was called */
#define COMPAT_FLAG_CALLED___libc_start_main 0x00000002 /* `__libc_start_main()' was called */
#define COMPAT_FLAG_LINKED_IO_FILE_84        0x00000004 /* One of `_IO_stdin_', `_IO_stdout_' or `_IO_stderr_' was linked. */
#define COMPAT_FLAG_LINKED_IO_FILE_84_2_1    0x00000008 /* One of `_IO_2_1_stdin_', `_IO_2_1_stdout_' or `_IO_2_1_stderr_' was linked. */
INTDEF uintptr_t libc_compat; /* Set of `COMPAT_FLAG_*' */

/* Check if the main application was compiled against libc4/5 */
#define libc_compat_islibc5()                                                                \
	((libc_compat & (COMPAT_FLAG_CALLED___libc_init | COMPAT_FLAG_CALLED___libc_start_main | \
	                 COMPAT_FLAG_LINKED_IO_FILE_84_2_1)) ==                                  \
	 COMPAT_FLAG_CALLED___libc_init)

/* Lazily load `libkernel32.so' (if not done already), and return the
 * address  of the named  `symbol_name'. If non-existent, `_Exit(1)'. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *LIBCCALL
libd_requirek32(char const *__restrict symbol_name);

DECL_END

#endif /* !GUARD_LIBC_LIBC_COMPAT_H */
