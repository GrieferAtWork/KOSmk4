/* HASH CRC-32:0xfa2d1a9 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strerrorname_np_defined
#define __local_strerrorname_np_defined
#include <__crt.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerrorname_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(strerrorname_np))(__errno_t __errnum) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosErrnoMappings: {int: (string, string)} = Dict();
local inside = false;
with (local fp = File.open("../../../include/asm/os/kos/errno.h")) {
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
		if (value in kosErrnoMappings)
			continue;
		kosErrnoMappings[value] = (name, comment);
	}
}
local emax = kosErrnoMappings.keys > ...;
print("#define HAVE_KOS_ERRNO_VALUES");
for (local ids: kosErrnoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined({0}) || {0} != {1}".format({ kosErrnoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_ERRNO_VALUES");
	print("@@pp_endif@@");
}
kosErrnoMappings[0] = ("EOK", "Success");
print("@@pp_ifdef HAVE_KOS_ERRNO_VALUES@@");
print("	static char const errno_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:emax + 1]) {
	local name, comment = kosErrnoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != emax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:emax + 1]) {
	if (kosErrnoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const errno_offsets[", (emax + 1), "] = {");
for (local i: [:emax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define __HAVE_KOS_ERRNO_VALUES
#if !defined(__EPERM) || __EPERM != 1 || !defined(__ENOENT) || __ENOENT != 2 || !defined(__ESRCH) || __ESRCH != 3 || !defined(__EINTR) || __EINTR != 4
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EPERM || __EPERM != 1 || !__ENOENT || __ENOENT != 2 || !__ESRCH || __ESRCH != 3 || !__EINTR || __EINTR != 4 */
#if !defined(__EIO) || __EIO != 5 || !defined(__ENXIO) || __ENXIO != 6 || !defined(__E2BIG) || __E2BIG != 7 || !defined(__ENOEXEC) || __ENOEXEC != 8
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EIO || __EIO != 5 || !__ENXIO || __ENXIO != 6 || !__E2BIG || __E2BIG != 7 || !__ENOEXEC || __ENOEXEC != 8 */
#if !defined(__EBADF) || __EBADF != 9 || !defined(__ECHILD) || __ECHILD != 10 || !defined(__EAGAIN) || __EAGAIN != 11 || !defined(__ENOMEM) || __ENOMEM != 12
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EBADF || __EBADF != 9 || !__ECHILD || __ECHILD != 10 || !__EAGAIN || __EAGAIN != 11 || !__ENOMEM || __ENOMEM != 12 */
#if !defined(__EACCES) || __EACCES != 13 || !defined(__EFAULT) || __EFAULT != 14 || !defined(__ENOTBLK) || __ENOTBLK != 15 || !defined(__EBUSY) || __EBUSY != 16
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EACCES || __EACCES != 13 || !__EFAULT || __EFAULT != 14 || !__ENOTBLK || __ENOTBLK != 15 || !__EBUSY || __EBUSY != 16 */
#if !defined(__EEXIST) || __EEXIST != 17 || !defined(__EXDEV) || __EXDEV != 18 || !defined(__ENODEV) || __ENODEV != 19 || !defined(__ENOTDIR) || __ENOTDIR != 20
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EEXIST || __EEXIST != 17 || !__EXDEV || __EXDEV != 18 || !__ENODEV || __ENODEV != 19 || !__ENOTDIR || __ENOTDIR != 20 */
#if !defined(__EISDIR) || __EISDIR != 21 || !defined(__EINVAL) || __EINVAL != 22 || !defined(__ENFILE) || __ENFILE != 23 || !defined(__EMFILE) || __EMFILE != 24
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EISDIR || __EISDIR != 21 || !__EINVAL || __EINVAL != 22 || !__ENFILE || __ENFILE != 23 || !__EMFILE || __EMFILE != 24 */
#if !defined(__ENOTTY) || __ENOTTY != 25 || !defined(__ETXTBSY) || __ETXTBSY != 26 || !defined(__EFBIG) || __EFBIG != 27 || !defined(__ENOSPC) || __ENOSPC != 28
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOTTY || __ENOTTY != 25 || !__ETXTBSY || __ETXTBSY != 26 || !__EFBIG || __EFBIG != 27 || !__ENOSPC || __ENOSPC != 28 */
#if !defined(__ESPIPE) || __ESPIPE != 29 || !defined(__EROFS) || __EROFS != 30 || !defined(__EMLINK) || __EMLINK != 31 || !defined(__EPIPE) || __EPIPE != 32
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ESPIPE || __ESPIPE != 29 || !__EROFS || __EROFS != 30 || !__EMLINK || __EMLINK != 31 || !__EPIPE || __EPIPE != 32 */
#if !defined(__EDOM) || __EDOM != 33 || !defined(__ERANGE) || __ERANGE != 34 || !defined(__EDEADLK) || __EDEADLK != 35 || !defined(__ENAMETOOLONG) || __ENAMETOOLONG != 36
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EDOM || __EDOM != 33 || !__ERANGE || __ERANGE != 34 || !__EDEADLK || __EDEADLK != 35 || !__ENAMETOOLONG || __ENAMETOOLONG != 36 */
#if !defined(__ENOLCK) || __ENOLCK != 37 || !defined(__ENOSYS) || __ENOSYS != 38 || !defined(__ENOTEMPTY) || __ENOTEMPTY != 39 || !defined(__ELOOP) || __ELOOP != 40
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOLCK || __ENOLCK != 37 || !__ENOSYS || __ENOSYS != 38 || !__ENOTEMPTY || __ENOTEMPTY != 39 || !__ELOOP || __ELOOP != 40 */
#if !defined(__ENOMSG) || __ENOMSG != 42 || !defined(__EIDRM) || __EIDRM != 43 || !defined(__ECHRNG) || __ECHRNG != 44 || !defined(__EL2NSYNC) || __EL2NSYNC != 45
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOMSG || __ENOMSG != 42 || !__EIDRM || __EIDRM != 43 || !__ECHRNG || __ECHRNG != 44 || !__EL2NSYNC || __EL2NSYNC != 45 */
#if !defined(__EL3HLT) || __EL3HLT != 46 || !defined(__EL3RST) || __EL3RST != 47 || !defined(__ELNRNG) || __ELNRNG != 48 || !defined(__EUNATCH) || __EUNATCH != 49
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EL3HLT || __EL3HLT != 46 || !__EL3RST || __EL3RST != 47 || !__ELNRNG || __ELNRNG != 48 || !__EUNATCH || __EUNATCH != 49 */
#if !defined(__ENOCSI) || __ENOCSI != 50 || !defined(__EL2HLT) || __EL2HLT != 51 || !defined(__EBADE) || __EBADE != 52 || !defined(__EBADR) || __EBADR != 53
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOCSI || __ENOCSI != 50 || !__EL2HLT || __EL2HLT != 51 || !__EBADE || __EBADE != 52 || !__EBADR || __EBADR != 53 */
#if !defined(__EXFULL) || __EXFULL != 54 || !defined(__ENOANO) || __ENOANO != 55 || !defined(__EBADRQC) || __EBADRQC != 56 || !defined(__EBADSLT) || __EBADSLT != 57
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EXFULL || __EXFULL != 54 || !__ENOANO || __ENOANO != 55 || !__EBADRQC || __EBADRQC != 56 || !__EBADSLT || __EBADSLT != 57 */
#if !defined(__EBFONT) || __EBFONT != 59 || !defined(__ENOSTR) || __ENOSTR != 60 || !defined(__ENODATA) || __ENODATA != 61 || !defined(__ETIME) || __ETIME != 62
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EBFONT || __EBFONT != 59 || !__ENOSTR || __ENOSTR != 60 || !__ENODATA || __ENODATA != 61 || !__ETIME || __ETIME != 62 */
#if !defined(__ENOSR) || __ENOSR != 63 || !defined(__ENONET) || __ENONET != 64 || !defined(__ENOPKG) || __ENOPKG != 65 || !defined(__EREMOTE) || __EREMOTE != 66
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOSR || __ENOSR != 63 || !__ENONET || __ENONET != 64 || !__ENOPKG || __ENOPKG != 65 || !__EREMOTE || __EREMOTE != 66 */
#if !defined(__ENOLINK) || __ENOLINK != 67 || !defined(__EADV) || __EADV != 68 || !defined(__ESRMNT) || __ESRMNT != 69 || !defined(__ECOMM) || __ECOMM != 70
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOLINK || __ENOLINK != 67 || !__EADV || __EADV != 68 || !__ESRMNT || __ESRMNT != 69 || !__ECOMM || __ECOMM != 70 */
#if !defined(__EPROTO) || __EPROTO != 71 || !defined(__EMULTIHOP) || __EMULTIHOP != 72 || !defined(__EDOTDOT) || __EDOTDOT != 73 || !defined(__EBADMSG) || __EBADMSG != 74
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EPROTO || __EPROTO != 71 || !__EMULTIHOP || __EMULTIHOP != 72 || !__EDOTDOT || __EDOTDOT != 73 || !__EBADMSG || __EBADMSG != 74 */
#if !defined(__EOVERFLOW) || __EOVERFLOW != 75 || !defined(__ENOTUNIQ) || __ENOTUNIQ != 76 || !defined(__EBADFD) || __EBADFD != 77 || !defined(__EREMCHG) || __EREMCHG != 78
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EOVERFLOW || __EOVERFLOW != 75 || !__ENOTUNIQ || __ENOTUNIQ != 76 || !__EBADFD || __EBADFD != 77 || !__EREMCHG || __EREMCHG != 78 */
#if !defined(__ELIBACC) || __ELIBACC != 79 || !defined(__ELIBBAD) || __ELIBBAD != 80 || !defined(__ELIBSCN) || __ELIBSCN != 81 || !defined(__ELIBMAX) || __ELIBMAX != 82
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ELIBACC || __ELIBACC != 79 || !__ELIBBAD || __ELIBBAD != 80 || !__ELIBSCN || __ELIBSCN != 81 || !__ELIBMAX || __ELIBMAX != 82 */
#if !defined(__ELIBEXEC) || __ELIBEXEC != 83 || !defined(__EILSEQ) || __EILSEQ != 84 || !defined(__ERESTART) || __ERESTART != 85 || !defined(__ESTRPIPE) || __ESTRPIPE != 86
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ELIBEXEC || __ELIBEXEC != 83 || !__EILSEQ || __EILSEQ != 84 || !__ERESTART || __ERESTART != 85 || !__ESTRPIPE || __ESTRPIPE != 86 */
#if !defined(__EUSERS) || __EUSERS != 87 || !defined(__ENOTSOCK) || __ENOTSOCK != 88 || !defined(__EDESTADDRREQ) || __EDESTADDRREQ != 89 || !defined(__EMSGSIZE) || __EMSGSIZE != 90
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EUSERS || __EUSERS != 87 || !__ENOTSOCK || __ENOTSOCK != 88 || !__EDESTADDRREQ || __EDESTADDRREQ != 89 || !__EMSGSIZE || __EMSGSIZE != 90 */
#if !defined(__EPROTOTYPE) || __EPROTOTYPE != 91 || !defined(__ENOPROTOOPT) || __ENOPROTOOPT != 92 || !defined(__EPROTONOSUPPORT) || __EPROTONOSUPPORT != 93 || !defined(__ESOCKTNOSUPPORT) || __ESOCKTNOSUPPORT != 94
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EPROTOTYPE || __EPROTOTYPE != 91 || !__ENOPROTOOPT || __ENOPROTOOPT != 92 || !__EPROTONOSUPPORT || __EPROTONOSUPPORT != 93 || !__ESOCKTNOSUPPORT || __ESOCKTNOSUPPORT != 94 */
#if !defined(__EOPNOTSUPP) || __EOPNOTSUPP != 95 || !defined(__EPFNOSUPPORT) || __EPFNOSUPPORT != 96 || !defined(__EAFNOSUPPORT) || __EAFNOSUPPORT != 97 || !defined(__EADDRINUSE) || __EADDRINUSE != 98
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EOPNOTSUPP || __EOPNOTSUPP != 95 || !__EPFNOSUPPORT || __EPFNOSUPPORT != 96 || !__EAFNOSUPPORT || __EAFNOSUPPORT != 97 || !__EADDRINUSE || __EADDRINUSE != 98 */
#if !defined(__EADDRNOTAVAIL) || __EADDRNOTAVAIL != 99 || !defined(__ENETDOWN) || __ENETDOWN != 100 || !defined(__ENETUNREACH) || __ENETUNREACH != 101 || !defined(__ENETRESET) || __ENETRESET != 102
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EADDRNOTAVAIL || __EADDRNOTAVAIL != 99 || !__ENETDOWN || __ENETDOWN != 100 || !__ENETUNREACH || __ENETUNREACH != 101 || !__ENETRESET || __ENETRESET != 102 */
#if !defined(__ECONNABORTED) || __ECONNABORTED != 103 || !defined(__ECONNRESET) || __ECONNRESET != 104 || !defined(__ENOBUFS) || __ENOBUFS != 105 || !defined(__EISCONN) || __EISCONN != 106
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ECONNABORTED || __ECONNABORTED != 103 || !__ECONNRESET || __ECONNRESET != 104 || !__ENOBUFS || __ENOBUFS != 105 || !__EISCONN || __EISCONN != 106 */
#if !defined(__ENOTCONN) || __ENOTCONN != 107 || !defined(__ESHUTDOWN) || __ESHUTDOWN != 108 || !defined(__ETOOMANYREFS) || __ETOOMANYREFS != 109 || !defined(__ETIMEDOUT) || __ETIMEDOUT != 110
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOTCONN || __ENOTCONN != 107 || !__ESHUTDOWN || __ESHUTDOWN != 108 || !__ETOOMANYREFS || __ETOOMANYREFS != 109 || !__ETIMEDOUT || __ETIMEDOUT != 110 */
#if !defined(__ECONNREFUSED) || __ECONNREFUSED != 111 || !defined(__EHOSTDOWN) || __EHOSTDOWN != 112 || !defined(__EHOSTUNREACH) || __EHOSTUNREACH != 113 || !defined(__EALREADY) || __EALREADY != 114
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ECONNREFUSED || __ECONNREFUSED != 111 || !__EHOSTDOWN || __EHOSTDOWN != 112 || !__EHOSTUNREACH || __EHOSTUNREACH != 113 || !__EALREADY || __EALREADY != 114 */
#if !defined(__EINPROGRESS) || __EINPROGRESS != 115 || !defined(__ESTALE) || __ESTALE != 116 || !defined(__EUCLEAN) || __EUCLEAN != 117 || !defined(__ENOTNAM) || __ENOTNAM != 118
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EINPROGRESS || __EINPROGRESS != 115 || !__ESTALE || __ESTALE != 116 || !__EUCLEAN || __EUCLEAN != 117 || !__ENOTNAM || __ENOTNAM != 118 */
#if !defined(__ENAVAIL) || __ENAVAIL != 119 || !defined(__EISNAM) || __EISNAM != 120 || !defined(__EREMOTEIO) || __EREMOTEIO != 121 || !defined(__EDQUOT) || __EDQUOT != 122
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENAVAIL || __ENAVAIL != 119 || !__EISNAM || __EISNAM != 120 || !__EREMOTEIO || __EREMOTEIO != 121 || !__EDQUOT || __EDQUOT != 122 */
#if !defined(__ENOMEDIUM) || __ENOMEDIUM != 123 || !defined(__EMEDIUMTYPE) || __EMEDIUMTYPE != 124 || !defined(__ECANCELED) || __ECANCELED != 125 || !defined(__ENOKEY) || __ENOKEY != 126
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOMEDIUM || __ENOMEDIUM != 123 || !__EMEDIUMTYPE || __EMEDIUMTYPE != 124 || !__ECANCELED || __ECANCELED != 125 || !__ENOKEY || __ENOKEY != 126 */
#if !defined(__EKEYEXPIRED) || __EKEYEXPIRED != 127 || !defined(__EKEYREVOKED) || __EKEYREVOKED != 128 || !defined(__EKEYREJECTED) || __EKEYREJECTED != 129 || !defined(__EOWNERDEAD) || __EOWNERDEAD != 130
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__EKEYEXPIRED || __EKEYEXPIRED != 127 || !__EKEYREVOKED || __EKEYREVOKED != 128 || !__EKEYREJECTED || __EKEYREJECTED != 129 || !__EOWNERDEAD || __EOWNERDEAD != 130 */
#if !defined(__ENOTRECOVERABLE) || __ENOTRECOVERABLE != 131 || !defined(__ERFKILL) || __ERFKILL != 132 || !defined(__EHWPOISON) || __EHWPOISON != 133
#undef __HAVE_KOS_ERRNO_VALUES
#endif /* !__ENOTRECOVERABLE || __ENOTRECOVERABLE != 131 || !__ERFKILL || __ERFKILL != 132 || !__EHWPOISON || __EHWPOISON != 133 */
#ifdef __HAVE_KOS_ERRNO_VALUES
	static char const __errno_strtab[] =
	"EOK\0Success\0"
	"EPERM\0Operation not permitted\0"
	"ENOENT\0No such file or directory\0"
	"ESRCH\0No such process\0"
	"EINTR\0Interrupted system call\0"
	"EIO\0I/O error\0"
	"ENXIO\0No such device or address\0"
	"E2BIG\0Argument list too long\0"
	"ENOEXEC\0Exec format error\0"
	"EBADF\0Bad file number\0"
	"ECHILD\0No child processes\0"
	"EAGAIN\0Try again\0"
	"ENOMEM\0Out of memory\0"
	"EACCES\0Permission denied\0"
	"EFAULT\0Bad address\0"
	"ENOTBLK\0Block device required\0"
	"EBUSY\0Device or resource busy\0"
	"EEXIST\0File exists\0"
	"EXDEV\0Cross-device link\0"
	"ENODEV\0No such device\0"
	"ENOTDIR\0Not a directory\0"
	"EISDIR\0Is a directory\0"
	"EINVAL\0Invalid argument\0"
	"ENFILE\0File table overflow\0"
	"EMFILE\0Too many open files\0"
	"ENOTTY\0Not a typewriter\0"
	"ETXTBSY\0Text file busy\0"
	"EFBIG\0File too large\0"
	"ENOSPC\0No space left on device\0"
	"ESPIPE\0Illegal seek\0"
	"EROFS\0Read-only file system\0"
	"EMLINK\0Too many links\0"
	"EPIPE\0Broken pipe\0"
	"EDOM\0Math argument out of domain of func\0"
	"ERANGE\0Math result not representable\0"
	"EDEADLK\0Resource deadlock would occur\0"
	"ENAMETOOLONG\0File name too long\0"
	"ENOLCK\0No record locks available\0"
	"ENOSYS\0Function not implemented\0"
	"ENOTEMPTY\0Directory not empty\0"
	"ELOOP\0Too many symbolic links encountered\0"
	"ENOMSG\0No message of desired type\0"
	"EIDRM\0Identifier removed\0"
	"ECHRNG\0Channel number out of range\0"
	"EL2NSYNC\0Level 2 not synchronized\0"
	"EL3HLT\0Level 3 halted\0"
	"EL3RST\0Level 3 reset\0"
	"ELNRNG\0Link number out of range\0"
	"EUNATCH\0Protocol driver not attached\0"
	"ENOCSI\0No CSI structure available\0"
	"EL2HLT\0Level 2 halted\0"
	"EBADE\0Invalid exchange\0"
	"EBADR\0Invalid request descriptor\0"
	"EXFULL\0Exchange full\0"
	"ENOANO\0No anode\0"
	"EBADRQC\0Invalid request code\0"
	"EBADSLT\0Invalid slot\0"
	"EBFONT\0Bad font file format\0"
	"ENOSTR\0Device not a stream\0"
	"ENODATA\0No data available\0"
	"ETIME\0Timer expired\0"
	"ENOSR\0Out of streams resources\0"
	"ENONET\0Machine is not on the network\0"
	"ENOPKG\0Package not installed\0"
	"EREMOTE\0Object is remote\0"
	"ENOLINK\0Link has been severed\0"
	"EADV\0Advertise error\0"
	"ESRMNT\0Srmount error\0"
	"ECOMM\0Communication error on send\0"
	"EPROTO\0Protocol error\0"
	"EMULTIHOP\0Multihop attempted\0"
	"EDOTDOT\0RFS specific error\0"
	"EBADMSG\0Not a data message\0"
	"EOVERFLOW\0Value too large for defined data type\0"
	"ENOTUNIQ\0Name not unique on network\0"
	"EBADFD\0File descriptor in bad state\0"
	"EREMCHG\0Remote address changed\0"
	"ELIBACC\0Can not access a needed shared library\0"
	"ELIBBAD\0Accessing a corrupted shared library\0"
	"ELIBSCN\0.lib section in a.out corrupted\0"
	"ELIBMAX\0Attempting to link in too many shared libraries\0"
	"ELIBEXEC\0Cannot exec a shared library directly\0"
	"EILSEQ\0Illegal byte sequence\0"
	"ERESTART\0Interrupted system call should be restarted\0"
	"ESTRPIPE\0Streams pipe error\0"
	"EUSERS\0Too many users\0"
	"ENOTSOCK\0Socket operation on non-socket\0"
	"EDESTADDRREQ\0Destination address required\0"
	"EMSGSIZE\0Message too long\0"
	"EPROTOTYPE\0Protocol wrong type for socket\0"
	"ENOPROTOOPT\0Protocol not available\0"
	"EPROTONOSUPPORT\0Protocol not supported\0"
	"ESOCKTNOSUPPORT\0Socket type not supported\0"
	"EOPNOTSUPP\0Operation not supported on transport endpoint\0"
	"EPFNOSUPPORT\0Protocol family not supported\0"
	"EAFNOSUPPORT\0Address family not supported by protocol\0"
	"EADDRINUSE\0Address already in use\0"
	"EADDRNOTAVAIL\0Cannot assign requested address\0"
	"ENETDOWN\0Network is down\0"
	"ENETUNREACH\0Network is unreachable\0"
	"ENETRESET\0Network dropped connection because of reset\0"
	"ECONNABORTED\0Software caused connection abort\0"
	"ECONNRESET\0Connection reset by peer\0"
	"ENOBUFS\0No buffer space available\0"
	"EISCONN\0Transport endpoint is already connected\0"
	"ENOTCONN\0Transport endpoint is not connected\0"
	"ESHUTDOWN\0Cannot send after transport endpoint shutdown\0"
	"ETOOMANYREFS\0Too many references: cannot splice\0"
	"ETIMEDOUT\0Connection timed out\0"
	"ECONNREFUSED\0Connection refused\0"
	"EHOSTDOWN\0Host is down\0"
	"EHOSTUNREACH\0No route to host\0"
	"EALREADY\0Operation already in progress\0"
	"EINPROGRESS\0Operation now in progress\0"
	"ESTALE\0Stale file handle\0"
	"EUCLEAN\0Structure needs cleaning\0"
	"ENOTNAM\0Not a XENIX named type file\0"
	"ENAVAIL\0No XENIX semaphores available\0"
	"EISNAM\0Is a named type file\0"
	"EREMOTEIO\0Remote I/O error\0"
	"EDQUOT\0Quota exceeded\0"
	"ENOMEDIUM\0No medium found\0"
	"EMEDIUMTYPE\0Wrong medium type\0"
	"ECANCELED\0Operation canceled\0"
	"ENOKEY\0Required key not available\0"
	"EKEYEXPIRED\0Key has expired\0"
	"EKEYREVOKED\0Key has been revoked\0"
	"EKEYREJECTED\0Key was rejected by service\0"
	"EOWNERDEAD\0Owner died\0"
	"ENOTRECOVERABLE\0State not recoverable\0"
	"ERFKILL\0Operation not possible due to RF-kill\0"
	"EHWPOISON\0Memory page has hardware error"
	"";
	static __UINT16_TYPE__ const __errno_offsets[134] = {
		0, 12, 42, 75, 97, 127, 141, 173, 202, 228, 250, 276, 293, 314, 339, 358,
		388, 418, 437, 461, 483, 507, 529, 553, 580, 607, 631, 654, 675, 706, 726, 754,
		776, 794, 835, 872, 910, 942, 975, 1007, 1037, 4166, 1079, 1113, 1138, 1173, 1207, 1229,
		1250, 1282, 1319, 1353, 1375, 1398, 1431, 1452, 1468, 1497, 4166, 1518, 1546, 1573, 1599, 1619,
		1650, 1687, 1716, 1741, 1771, 1792, 1813, 1847, 1869, 1898, 1925, 1952, 2000, 2036, 2072, 2103,
		2150, 2195, 2235, 2291, 2338, 2367, 2420, 2448, 2470, 2510, 2552, 2578, 2620, 2655, 2694, 2736,
		2793, 2836, 2890, 2924, 2970, 2995, 3030, 3084, 3130, 3166, 3200, 3248, 3293, 3349, 3397, 3428,
		3460, 3483, 3513, 3552, 3590, 3615, 3648, 3684, 3722, 3750, 3777, 3799, 3825, 3855, 3884, 3918,
		3946, 3979, 4020, 4042, 4080, 4126,
	};
/*[[[end]]]*/
	char const *__result;
	if ((unsigned int)__errnum >= __COMPILER_LENOF(__errno_offsets))
		return __NULLPTR;
	__result = &__errno_strtab[__errno_offsets[__errnum]];
	if (!*__result)
		__result = __NULLPTR;
	return __result;
#else /* __HAVE_KOS_ERRNO_VALUES */
	char const *__result;
	switch (__errnum) {

#ifdef __EPERM
	case __EPERM:           __result = "EPERM\0Operation not permitted"; break;
#endif /* __EPERM */
#ifdef __ENOENT
	case __ENOENT:          __result = "ENOENT\0No such file or directory"; break;
#endif /* __ENOENT */
#ifdef __ESRCH
	case __ESRCH:           __result = "ESRCH\0No such process"; break;
#endif /* __ESRCH */
#ifdef __EINTR
	case __EINTR:           __result = "EINTR\0Interrupted system call"; break;
#endif /* __EINTR */
#ifdef __EIO
	case __EIO:             __result = "EIO\0I/O error"; break;
#endif /* __EIO */
#ifdef __ENXIO
	case __ENXIO:           __result = "ENXIO\0No such device or address"; break;
#endif /* __ENXIO */
#ifdef __E2BIG
	case __E2BIG:           __result = "E2BIG\0Argument list too long"; break;
#endif /* __E2BIG */
#ifdef __ENOEXEC
	case __ENOEXEC:         __result = "ENOEXEC\0Exec format error"; break;
#endif /* __ENOEXEC */
#ifdef __EBADF
	case __EBADF:           __result = "EBADF\0Bad file number"; break;
#endif /* __EBADF */
#ifdef __ECHILD
	case __ECHILD:          __result = "ECHILD\0No child processes"; break;
#endif /* __ECHILD */
#ifdef __EAGAIN
	case __EAGAIN:          __result = "EAGAIN\0Try again"; break;
#endif /* __EAGAIN */
#ifdef __ENOMEM
	case __ENOMEM:          __result = "ENOMEM\0Out of memory"; break;
#endif /* __ENOMEM */
#ifdef __EACCES
	case __EACCES:          __result = "EACCES\0Permission denied"; break;
#endif /* __EACCES */
#ifdef __EFAULT
	case __EFAULT:          __result = "EFAULT\0Bad address"; break;
#endif /* __EFAULT */
#ifdef __EBUSY
	case __EBUSY:           __result = "EBUSY\0Device or resource busy"; break;
#endif /* __EBUSY */
#ifdef __EEXIST
	case __EEXIST:          __result = "EEXIST\0File exists"; break;
#endif /* __EEXIST */
#ifdef __EXDEV
	case __EXDEV:           __result = "EXDEV\0Cross-device link"; break;
#endif /* __EXDEV */
#ifdef __ENODEV
	case __ENODEV:          __result = "ENODEV\0No such device"; break;
#endif /* __ENODEV */
#ifdef __ENOTDIR
	case __ENOTDIR:         __result = "ENOTDIR\0Not a directory"; break;
#endif /* __ENOTDIR */
#ifdef __EISDIR
	case __EISDIR:          __result = "EISDIR\0Is a directory"; break;
#endif /* __EISDIR */
#ifdef __ENFILE
	case __ENFILE:          __result = "ENFILE\0File table overflow"; break;
#endif /* __ENFILE */
#ifdef __EMFILE
	case __EMFILE:          __result = "EMFILE\0Too many open files"; break;
#endif /* __EMFILE */
#ifdef __ENOTTY
	case __ENOTTY:          __result = "ENOTTY\0Not a typewriter"; break;
#endif /* __ENOTTY */
#ifdef __EFBIG
	case __EFBIG:           __result = "EFBIG\0File too large"; break;
#endif /* __EFBIG */
#ifdef __ENOSPC
	case __ENOSPC:          __result = "ENOSPC\0No space left on device"; break;
#endif /* __ENOSPC */
#ifdef __ESPIPE
	case __ESPIPE:          __result = "ESPIPE\0Illegal seek"; break;
#endif /* __ESPIPE */
#ifdef __EROFS
	case __EROFS:           __result = "EROFS\0Read-only file system"; break;
#endif /* __EROFS */
#ifdef __EMLINK
	case __EMLINK:          __result = "EMLINK\0Too many links"; break;
#endif /* __EMLINK */
#ifdef __EPIPE
	case __EPIPE:           __result = "EPIPE\0Broken pipe"; break;
#endif /* __EPIPE */
#ifdef __EDOM
	case __EDOM:            __result = "EDOM\0Math argument out of domain of func"; break;
#endif /* __EDOM */
#ifdef __ENAMETOOLONG
	case __ENAMETOOLONG:    __result = "ENAMETOOLONG\0File name too long"; break;
#endif /* __ENAMETOOLONG */
#ifdef __ENOLCK
	case __ENOLCK:          __result = "ENOLCK\0No record locks available"; break;
#endif /* __ENOLCK */
#ifdef __ENOSYS
	case __ENOSYS:          __result = "ENOSYS\0Function not implemented"; break;
#endif /* __ENOSYS */
#ifdef __ENOTEMPTY
	case __ENOTEMPTY:       __result = "ENOTEMPTY\0Directory not empty"; break;
#endif /* __ENOTEMPTY */
#ifdef __EINVAL
	case __EINVAL:          __result = "EINVAL\0Invalid argument"; break;
#endif /* __EINVAL */
#ifdef __ERANGE
	case __ERANGE:          __result = "ERANGE\0Math result not representable"; break;
#endif /* __ERANGE */
#ifdef __EILSEQ
	case __EILSEQ:          __result = "EILSEQ\0Illegal byte sequence"; break;
#endif /* __EILSEQ */
#ifdef __EDEADLOCK
	case __EDEADLOCK:       __result = "EDEADLOCK\0Resource deadlock would occur"; break;
#endif /* __EDEADLOCK */
#ifdef __EADDRINUSE
	case __EADDRINUSE:      __result = "EADDRINUSE\0Address already in use"; break;
#endif /* __EADDRINUSE */
#ifdef __EADDRNOTAVAIL
	case __EADDRNOTAVAIL:   __result = "EADDRNOTAVAIL\0Cannot assign requested address"; break;
#endif /* __EADDRNOTAVAIL */
#ifdef __EAFNOSUPPORT
	case __EAFNOSUPPORT:    __result = "EAFNOSUPPORT\0Address family not supported by protocol"; break;
#endif /* __EAFNOSUPPORT */
#ifdef __EALREADY
	case __EALREADY:        __result = "EALREADY\0Operation already in progress"; break;
#endif /* __EALREADY */
#ifdef __EBADMSG
	case __EBADMSG:         __result = "EBADMSG\0Not a data message"; break;
#endif /* __EBADMSG */
#ifdef __ECANCELED
	case __ECANCELED:       __result = "ECANCELED\0Operation Canceled"; break;
#endif /* __ECANCELED */
#ifdef __ECONNABORTED
	case __ECONNABORTED:    __result = "ECONNABORTED\0Software caused connection abort"; break;
#endif /* __ECONNABORTED */
#ifdef __ECONNREFUSED
	case __ECONNREFUSED:    __result = "ECONNREFUSED\0Connection refused"; break;
#endif /* __ECONNREFUSED */
#ifdef __ECONNRESET
	case __ECONNRESET:      __result = "ECONNRESET\0Connection reset by peer"; break;
#endif /* __ECONNRESET */
#ifdef __EDESTADDRREQ
	case __EDESTADDRREQ:    __result = "EDESTADDRREQ\0Destination address required"; break;
#endif /* __EDESTADDRREQ */
#ifdef __EHOSTUNREACH
	case __EHOSTUNREACH:    __result = "EHOSTUNREACH\0No route to host"; break;
#endif /* __EHOSTUNREACH */
#ifdef __EIDRM
	case __EIDRM:           __result = "EIDRM\0Identifier removed"; break;
#endif /* __EIDRM */
#ifdef __EINPROGRESS
	case __EINPROGRESS:     __result = "EINPROGRESS\0Operation now in progress"; break;
#endif /* __EINPROGRESS */
#ifdef __EISCONN
	case __EISCONN:         __result = "EISCONN\0Transport endpoint is already connected"; break;
#endif /* __EISCONN */
#ifdef __ELOOP
	case __ELOOP:           __result = "ELOOP\0Too many symbolic links encountered"; break;
#endif /* __ELOOP */
#ifdef __EMSGSIZE
	case __EMSGSIZE:        __result = "EMSGSIZE\0Message too long"; break;
#endif /* __EMSGSIZE */
#ifdef __ENETDOWN
	case __ENETDOWN:        __result = "ENETDOWN\0Network is down"; break;
#endif /* __ENETDOWN */
#ifdef __ENETRESET
	case __ENETRESET:       __result = "ENETRESET\0Network dropped connection because of reset"; break;
#endif /* __ENETRESET */
#ifdef __ENETUNREACH
	case __ENETUNREACH:     __result = "ENETUNREACH\0Network is unreachable"; break;
#endif /* __ENETUNREACH */
#ifdef __ENOBUFS
	case __ENOBUFS:         __result = "ENOBUFS\0No buffer space available"; break;
#endif /* __ENOBUFS */
#ifdef __ENODATA
	case __ENODATA:         __result = "ENODATA\0No data available"; break;
#endif /* __ENODATA */
#ifdef __ENOLINK
	case __ENOLINK:         __result = "ENOLINK\0Link has been severed"; break;
#endif /* __ENOLINK */
#ifdef __ENOMSG
	case __ENOMSG:          __result = "ENOMSG\0No message of desired type"; break;
#endif /* __ENOMSG */
#ifdef __ENOPROTOOPT
	case __ENOPROTOOPT:     __result = "ENOPROTOOPT\0Protocol not available"; break;
#endif /* __ENOPROTOOPT */
#ifdef __ENOSR
	case __ENOSR:           __result = "ENOSR\0Out of streams resources"; break;
#endif /* __ENOSR */
#ifdef __ENOSTR
	case __ENOSTR:          __result = "ENOSTR\0Device not a stream"; break;
#endif /* __ENOSTR */
#ifdef __ENOTCONN
	case __ENOTCONN:        __result = "ENOTCONN\0Transport endpoint is not connected"; break;
#endif /* __ENOTCONN */
#ifdef __ENOTRECOVERABLE
	case __ENOTRECOVERABLE: __result = "ENOTRECOVERABLE\0State not recoverable"; break;
#endif /* __ENOTRECOVERABLE */
#ifdef __ENOTSOCK
	case __ENOTSOCK:        __result = "ENOTSOCK\0Socket operation on non-socket"; break;
#endif /* __ENOTSOCK */
#ifdef __ENOTSUP
	case __ENOTSUP:         __result = "ENOTSUP\0Not supported"; break;
#endif /* __ENOTSUP */
#ifdef __EOPNOTSUPP
	case __EOPNOTSUPP:      __result = "EOPNOTSUPP\0Operation not supported on transport endpoint"; break;
#endif /* __EOPNOTSUPP */
#ifdef __EOTHER
	case __EOTHER:          __result = "EOTHER\0Other"; break;
#endif /* __EOTHER */
#ifdef __EOVERFLOW
	case __EOVERFLOW:       __result = "EOVERFLOW\0Value too large for defined data type"; break;
#endif /* __EOVERFLOW */
#ifdef __EOWNERDEAD
	case __EOWNERDEAD:      __result = "EOWNERDEAD\0Owner died"; break;
#endif /* __EOWNERDEAD */
#ifdef __EPROTO
	case __EPROTO:          __result = "EPROTO\0Protocol error"; break;
#endif /* __EPROTO */
#ifdef __EPROTONOSUPPORT
	case __EPROTONOSUPPORT: __result = "EPROTONOSUPPORT\0Protocol not supported"; break;
#endif /* __EPROTONOSUPPORT */
#ifdef __EPROTOTYPE
	case __EPROTOTYPE:      __result = "EPROTOTYPE\0Protocol wrong type for socket"; break;
#endif /* __EPROTOTYPE */
#ifdef __ETIME
	case __ETIME:           __result = "ETIME\0Timer expired"; break;
#endif /* __ETIME */
#ifdef __ETIMEDOUT
	case __ETIMEDOUT:       __result = "ETIMEDOUT\0Connection timed out"; break;
#endif /* __ETIMEDOUT */
#ifdef __ETXTBSY
	case __ETXTBSY:         __result = "ETXTBSY\0Text file busy"; break;
#endif /* __ETXTBSY */
#ifdef __EFTYPE
	case __EFTYPE:          __result = "EFTYPE\0Inappropriate file type or format"; break;
#endif /* __EFTYPE */
#ifdef __ENMFILE
	case __ENMFILE:         __result = "ENMFILE\0No more files"; break;
#endif /* __ENMFILE */
#ifdef __EPFNOSUPPORT
	case __EPFNOSUPPORT:    __result = "EPFNOSUPPORT\0Protocol family not supported"; break;
#endif /* __EPFNOSUPPORT */
#ifdef __EHOSTDOWN
	case __EHOSTDOWN:       __result = "EHOSTDOWN\0Host is down"; break;
#endif /* __EHOSTDOWN */
#ifdef __ETOOMANYREFS
	case __ETOOMANYREFS:    __result = "ETOOMANYREFS\0Too many references: cannot splice"; break;
#endif /* __ETOOMANYREFS */
#ifdef __EDQUOT
	case __EDQUOT:          __result = "EDQUOT\0Quota exceeded"; break;
#endif /* __EDQUOT */
#ifdef __ESTALE
	case __ESTALE:          __result = "ESTALE\0Stale file handle"; break;
#endif /* __ESTALE */
#ifdef __ENOSHARE
	case __ENOSHARE:        __result = "ENOSHARE\0No such host or network path"; break;
#endif /* __ENOSHARE */
#ifdef __ECASECLASH
	case __ECASECLASH:      __result = "ECASECLASH\0Filename exists with different case"; break;
#endif /* __ECASECLASH */
#ifdef __ENOTBLK
	case __ENOTBLK:         __result = "ENOTBLK\0Block device required"; break;
#endif /* __ENOTBLK */
#ifdef __ECHRNG
	case __ECHRNG:          __result = "ECHRNG\0Channel number out of range"; break;
#endif /* __ECHRNG */
#ifdef __EL2NSYNC
	case __EL2NSYNC:        __result = "EL2NSYNC\0Level 2 not synchronized"; break;
#endif /* __EL2NSYNC */
#ifdef __EL3HLT
	case __EL3HLT:          __result = "EL3HLT\0Level 3 halted"; break;
#endif /* __EL3HLT */
#ifdef __EL3RST
	case __EL3RST:          __result = "EL3RST\0Level 3 reset"; break;
#endif /* __EL3RST */
#ifdef __ELNRNG
	case __ELNRNG:          __result = "ELNRNG\0Link number out of range"; break;
#endif /* __ELNRNG */
#ifdef __EUNATCH
	case __EUNATCH:         __result = "EUNATCH\0Protocol driver not attached"; break;
#endif /* __EUNATCH */
#ifdef __ENOCSI
	case __ENOCSI:          __result = "ENOCSI\0No CSI structure available"; break;
#endif /* __ENOCSI */
#ifdef __EL2HLT
	case __EL2HLT:          __result = "EL2HLT\0Level 2 halted"; break;
#endif /* __EL2HLT */
#ifdef __EBADE
	case __EBADE:           __result = "EBADE\0Invalid exchange"; break;
#endif /* __EBADE */
#ifdef __EBADR
	case __EBADR:           __result = "EBADR\0Invalid request descriptor"; break;
#endif /* __EBADR */
#ifdef __EXFULL
	case __EXFULL:          __result = "EXFULL\0Exchange full"; break;
#endif /* __EXFULL */
#ifdef __ENOANO
	case __ENOANO:          __result = "ENOANO\0No anode"; break;
#endif /* __ENOANO */
#ifdef __EBADRQC
	case __EBADRQC:         __result = "EBADRQC\0Invalid request code"; break;
#endif /* __EBADRQC */
#ifdef __EBADSLT
	case __EBADSLT:         __result = "EBADSLT\0Invalid slot"; break;
#endif /* __EBADSLT */
#ifdef __EBFONT
	case __EBFONT:          __result = "EBFONT\0Bad font file fmt"; break;
#endif /* __EBFONT */
#ifdef __ENONET
	case __ENONET:          __result = "ENONET\0Machine is not on the network"; break;
#endif /* __ENONET */
#ifdef __ENOPKG
	case __ENOPKG:          __result = "ENOPKG\0Package not installed"; break;
#endif /* __ENOPKG */
#ifdef __EREMOTE
	case __EREMOTE:         __result = "EREMOTE\0The object is remote"; break;
#endif /* __EREMOTE */
#ifdef __EADV
	case __EADV:            __result = "EADV\0Advertise error"; break;
#endif /* __EADV */
#ifdef __ESRMNT
	case __ESRMNT:          __result = "ESRMNT\0Srmount error"; break;
#endif /* __ESRMNT */
#ifdef __ECOMM
	case __ECOMM:           __result = "ECOMM\0Communication error on send"; break;
#endif /* __ECOMM */
#ifdef __ELBIN
	case __ELBIN:           __result = "ELBIN\0Inode is remote (not really error)"; break;
#endif /* __ELBIN */
#ifdef __EDOTDOT
	case __EDOTDOT:         __result = "EDOTDOT\0Cross mount point (not really error)"; break;
#endif /* __EDOTDOT */
#ifdef __ENOTUNIQ
	case __ENOTUNIQ:        __result = "ENOTUNIQ\0Given log. name not unique"; break;
#endif /* __ENOTUNIQ */
#ifdef __EBADFD
	case __EBADFD:          __result = "EBADFD\0f.d. invalid for this operation"; break;
#endif /* __EBADFD */
#ifdef __EREMCHG
	case __EREMCHG:         __result = "EREMCHG\0Remote address changed"; break;
#endif /* __EREMCHG */
#ifdef __ELIBACC
	case __ELIBACC:         __result = "ELIBACC\0Can't access a needed shared lib"; break;
#endif /* __ELIBACC */
#ifdef __ELIBBAD
	case __ELIBBAD:         __result = "ELIBBAD\0Accessing a corrupted shared lib"; break;
#endif /* __ELIBBAD */
#ifdef __ELIBSCN
	case __ELIBSCN:         __result = "ELIBSCN\0.lib section in a.out corrupted"; break;
#endif /* __ELIBSCN */
#ifdef __ELIBMAX
	case __ELIBMAX:         __result = "ELIBMAX\0Attempting to link in too many libs"; break;
#endif /* __ELIBMAX */
#ifdef __ELIBEXEC
	case __ELIBEXEC:        __result = "ELIBEXEC\0Attempting to exec a shared library"; break;
#endif /* __ELIBEXEC */
#ifdef __ESHUTDOWN
	case __ESHUTDOWN:       __result = "ESHUTDOWN\0Can't send after socket shutdown"; break;
#endif /* __ESHUTDOWN */
#ifdef __ESOCKTNOSUPPORT
	case __ESOCKTNOSUPPORT: __result = "ESOCKTNOSUPPORT\0Socket type not supported"; break;
#endif /* __ESOCKTNOSUPPORT */
#ifdef __EPROCLIM
	case __EPROCLIM:        __result = "EPROCLIM\0Process limit reached"; break;
#endif /* __EPROCLIM */
#ifdef __EUSERS
	case __EUSERS:          __result = "EUSERS\0Too many users"; break;
#endif /* __EUSERS */
#ifdef __ENOMEDIUM
	case __ENOMEDIUM:       __result = "ENOMEDIUM\0No medium (in tape drive)"; break;
#endif /* __ENOMEDIUM */
#ifdef __ESTRPIPE
	case __ESTRPIPE:        __result = "ESTRPIPE\0Streams pipe error"; break;
#endif /* __ESTRPIPE */
#ifdef __EMULTIHOP
	case __EMULTIHOP:       __result = "EMULTIHOP\0Multihop attempted"; break;
#endif /* __EMULTIHOP */
#ifdef __ERESTART
	case __ERESTART:        __result = "ERESTART\0Interrupted system call should be restarted"; break;
#endif /* __ERESTART */
#ifdef __EUCLEAN
	case __EUCLEAN:         __result = "EUCLEAN\0Structure needs cleaning"; break;
#endif /* __EUCLEAN */
#ifdef __ENOTNAM
	case __ENOTNAM:         __result = "ENOTNAM\0Not a XENIX named type file"; break;
#endif /* __ENOTNAM */
#ifdef __ENAVAIL
	case __ENAVAIL:         __result = "ENAVAIL\0No XENIX semaphores available"; break;
#endif /* __ENAVAIL */
#ifdef __EISNAM
	case __EISNAM:          __result = "EISNAM\0Is a named type file"; break;
#endif /* __EISNAM */
#ifdef __EREMOTEIO
	case __EREMOTEIO:       __result = "EREMOTEIO\0Remote I/O error"; break;
#endif /* __EREMOTEIO */
#ifdef __EMEDIUMTYPE
	case __EMEDIUMTYPE:     __result = "EMEDIUMTYPE\0Wrong medium type"; break;
#endif /* __EMEDIUMTYPE */
#ifdef __ENOKEY
	case __ENOKEY:          __result = "ENOKEY\0Required key not available"; break;
#endif /* __ENOKEY */
#ifdef __EKEYEXPIRED
	case __EKEYEXPIRED:     __result = "EKEYEXPIRED\0Key has expired"; break;
#endif /* __EKEYEXPIRED */
#ifdef __EKEYREVOKED
	case __EKEYREVOKED:     __result = "EKEYREVOKED\0Key has been revoked"; break;
#endif /* __EKEYREVOKED */
#ifdef __EKEYREJECTED
	case __EKEYREJECTED:    __result = "EKEYREJECTED\0Key was rejected by service"; break;
#endif /* __EKEYREJECTED */
#ifdef __ERFKILL
	case __ERFKILL:         __result = "ERFKILL\0Operation not possible due to RF-kill"; break;
#endif /* __ERFKILL */
#ifdef __EHWPOISON
	case __EHWPOISON:       __result = "EHWPOISON\0Memory page has hardware error"; break;
#endif /* __EHWPOISON */
#if defined(__STRUNCATE) && (!defined(__ERANGE) || __STRUNCATE != __ERANGE)
	case __STRUNCATE:       __result = "STRUNCATE\0Truncated"; break;
#endif /* __STRUNCATE && (!__ERANGE || __STRUNCATE != __ERANGE) */
#if defined(__EWOULDBLOCK) && (!defined(__EAGAIN) || __EWOULDBLOCK != __EAGAIN)
	case __EWOULDBLOCK:     __result = "EWOULDBLOCK\0Operation would block"; break;
#endif /* __EWOULDBLOCK && (!__EAGAIN || __EWOULDBLOCK != __EAGAIN) */
#if defined(__EDEADLK) && (!defined(__EDEADLOCK) || __EDEADLOCK != __EDEADLK)
	case __EDEADLK:         __result = "EDEADLK\0Resource deadlock would occur"; break;
#endif /* __EDEADLK && (!__EDEADLOCK || __EDEADLOCK != __EDEADLK) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !__HAVE_KOS_ERRNO_VALUES */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerrorname_np_defined
#define __local___localdep_strerrorname_np_defined
#define __localdep_strerrorname_np __LIBC_LOCAL_NAME(strerrorname_np)
#endif /* !__local___localdep_strerrorname_np_defined */
#endif /* !__local_strerrorname_np_defined */
