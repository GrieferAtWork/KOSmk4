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
%(c_prefix){
/* (#) Portability: Cygwin       (/winsup/cygwin/include/io.h) */
/* (#) Portability: DJGPP        (/include/io.h) */
/* (#) Portability: MSVC         (/include/io.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/io.h) */
/* (#) Portability: NetBSD       (/sys/arch/[...]/include/io.h) */
/* (#) Portability: Windows Kits (/ucrt/io.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <asm/os/fcntl.h>
)]%[insert:prefix(
#include <asm/os/oflags.h>
)]%{


#ifndef _A_NORMAL
#define _A_NORMAL 0x00
#define _A_RDONLY 0x01
#define _A_HIDDEN 0x02
#define _A_SYSTEM 0x04
#define _A_SUBDIR 0x10
#define _A_ARCH   0x20
#endif /* !_A_NORMAL */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef _FSIZE_T_DEFINED
#define _FSIZE_T_DEFINED
typedef __UINT32_TYPE__ _fsize_t;
#endif /* _FSIZE_T_DEFINED */

struct _finddata32_t;
struct __finddata64_t; /* I guess something else is already using the more obvious choice... */
struct _finddata32i64_t;
struct _finddata64i32_t;

#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */

}

%[define_type_class(__PIO_OFFSET   = "TIn(__SIZEOF_OFF32_T__)")]
%[define_type_class(__PIO_OFFSET64 = "TIn(__SIZEOF_OFF64_T__)")]

%[insert:std]
%[insert:extern(remove)]
%[insert:extern(rename)]
%[insert:extern(unlink)]
%[insert:extern(open)]
%[insert:extern(creat)]
%[insert:extern(access)]
%[insert:extern(chmod)]
%[insert:extern(close)]
%[insert:extern(dup)]
%[insert:extern(dup2)]
%[insert:extern(isatty)]
%[insert:extern(lseek)]
%[insert:extern(mktemp)]
%[insert:extern(umask)]
%[insert:extern(read)]
%[insert:extern(write)]

%[insert:function(_access = access)]
%[insert:function(_creat = creat)]
%[insert:function(_chmod = chmod)]

[[cp, section(".text.crt.dos.fs.property")]]
[[crt_dos_variant, decl_include("<bits/types.h>", "<features.h>")]]
[[requires_function(access), impl_include("<libc/errno.h>")]]
errno_t _access_s([[nonnull]] char const *filename, __STDC_INT_AS_UINT_T type) {
	if (access(filename, type) == 0)
		return $EOK;
	return $__libc_geterrno_or(1);
}

%[insert:function(_chsize = ftruncate)]
%[insert:function(_chsize_s = ftruncate64)]
%[insert:function(_commit = fsync)]
%[insert:function(_lseek = lseek)]
%[insert:function(_lseeki64 = lseek64)]
%[insert:function(_locking = lockf)]
%[insert:guarded_function(_unlink = unlink)]
%[insert:function(_close = close)]
%[insert:function(_dup = dup)]
%[insert:function(_dup2 = dup2)]
%[insert:function(_read = read)]
%[insert:function(_write = write)]
%[insert:function(_open = open)]
%[insert:function(_umask = umask)]
%[insert:function(_isatty = isatty)]
%[insert:function(_mktemp = mktemp)]

[[section(".text.crt.dos.fs.property")]]
[[decl_include("<bits/types.h>"), requires_function(umask)]]
errno_t _umask_s($mode_t nmode, [[nonnull]] $mode_t *omode) {
	*omode = umask(nmode);
	return $EOK;
}



[[requires_include("<asm/os/fcntl.h>"), decl_include("<bits/types.h>")]]
[[requires($has_function(fcntl) && (defined(__F_SETFL_XCH) || (defined(__F_GETFL) && defined(__F_SETFL))))]]
$oflag_t _setmode($fd_t fd, $oflag_t mode) {
@@pp_ifdef __F_SETFL_XCH@@
	return fcntl(fd, __F_SETFL_XCH, mode);
@@pp_else@@
	oflag_t result;
	result = fcntl(fd, __F_GETFL);
	if unlikely(result < 0)
		return -1;
	return fcntl(fd, __F_SETFL, mode);
@@pp_endif@@
}



%
%
%[default:section(".text.crt.dos.fs.dir")]
[[decl_include("<hybrid/typecore.h>")]]
int _findclose(intptr_t findfd);

[[crt_dos_variant, cp, wunused, export_alias("_findfirst"), decl_include("<hybrid/typecore.h>")]]
intptr_t _findfirst32([[nonnull]] char const *__restrict filename,
                      [[nonnull]] struct _finddata32_t *__restrict finddata);

[[crt_dos_variant, cp, wunused, export_alias("_findfirsti64"), decl_include("<hybrid/typecore.h>")]]
intptr_t _findfirst32i64([[nonnull]] char const *__restrict filename,
                         [[nonnull]] struct _finddata32i64_t *__restrict finddata);

[[crt_dos_variant, cp, wunused, export_alias("_findfirst64i32"), decl_include("<hybrid/typecore.h>")]]
intptr_t _findfirst64([[nonnull]] char const *__restrict filename,
                      [[nonnull]] struct __finddata64_t *__restrict finddata);

[[cp, wunused, decl_include("<hybrid/typecore.h>")]]
intptr_t _findfirst64i32([[nonnull]] char const *__restrict filename,
                         [[nonnull]] struct _finddata64i32_t *__restrict finddata)
	= _findfirst64;

[[cp, export_alias("_findnext"), decl_include("<hybrid/typecore.h>")]]
int _findnext32(intptr_t findfd,
                [[nonnull]] struct _finddata32_t *__restrict finddata);

[[cp, export_alias("_findnexti64"), decl_include("<hybrid/typecore.h>")]]
int _findnext32i64(intptr_t findfd,
                   [[nonnull]] struct _finddata32i64_t *__restrict finddata);

[[cp, export_alias("_findnext64i32"), decl_include("<hybrid/typecore.h>")]]
int _findnext64(intptr_t findfd,
                [[nonnull]] struct __finddata64_t *__restrict finddata);

[[cp, decl_include("<hybrid/typecore.h>")]]
int _findnext64i32(intptr_t findfd,
                   [[nonnull]] struct _finddata64i32_t *__restrict finddata)
	= _findnext64;


%[default:section(".text.crt.dos.fs.io")]
%
[[crt_dos_variant, cp, export_alias("_sopen_s_nolock")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[requires_function(sopen)]]
errno_t _sopen_s([[nonnull]] $fd_t *fd,
                 [[nonnull]] char const *filename,
                 $oflag_t oflags, int sflags,
                 $mode_t mode) {
	fd_t result;
	if (!fd) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	result = sopen(filename, oflags, sflags, mode);
	if (result < 0)
		return $__libc_geterrno_or(1);
	*fd = result;
	return 0;
}

%[insert:function(_sopen_s_nolock = _sopen_s)]

[[cp, wunused, crt_dos_variant, decl_include("<bits/types.h>")]]
[[requires_function(_sopen_s), section(".text.crt.dos.fs.io")]]
errno_t _sopen_dispatch([[nonnull]] char const *filename,
                        $oflag_t oflags, int sflags, $mode_t mode,
                        [[nonnull]] $fd_t *fd, int bsecure) {
	(void)bsecure;
	return _sopen_s(fd, filename, oflags, sflags, mode);
}


[[section(".text.crt.dos.fs.utility")]]
errno_t _mktemp_s([[nonnull]] char *template_, size_t size);

%[insert:function(_sopen = sopen)]

[[requires_function(pipe2)]]
[[decl_include("<bits/types.h>"), section(".text.crt.dos.fs.io")]]
int _pipe([[nonnull]] $fd_t pipedes[2],
          $uint32_t pipesize, $oflag_t textmode) {
	(void)pipesize;
	return pipe2(pipedes, textmode);
}

%[default:section(".text.crt.dos.fs.utility")]
%[insert:function(_eof = eof)]
%[insert:function(_filelength = filelength)]
%[insert:function(_tell = tell)]
%[insert:function(_telli64 = tell64)]

[[impl_include("<asm/os/stdio.h>")]]
[[decl_include("<bits/types.h>"), wunused]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(lseek64) && defined(__SEEK_CUR) && defined(__SEEK_END) && defined(__SEEK_SET))]]
$int64_t _filelengthi64($fd_t fd) {
	int64_t oldpos, result;
	oldpos = lseek64(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = lseek64(fd, 0, __SEEK_END);
	if likely(result >= 0)
		lseek64(fd, oldpos, __SEEK_SET);
	return result;
}


%[default:section(".text.crt.dos.fs.basic_property")]

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant, requires_function(umask)]]
[[impl_include("<libc/errno.h>")]]
errno_t umask_s($mode_t newmode, $mode_t *oldmode) {
	if (!oldmode) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*oldmode = umask(newmode);
	return 0;
}

%[default:section(".text.crt.dos.fs.utility")];

[[cp, decl_include("<bits/types.h>")]]
int __lock_fhandle($fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-op */
	return 0;
}

[[decl_include("<bits/types.h>")]]
void _unlock_fhandle($fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-op */
}


[[decl_include("<bits/types.h>"), pure, wunused]]
[[requires(!defined(__CRT_DOS_PRIMARY))]]
intptr_t _get_osfhandle($fd_t fd) {
	COMPILER_IMPURE();
	return (intptr_t)fd;
}


[[decl_include("<bits/types.h>"), wunused]]
[[requires(!defined(__CRT_DOS_PRIMARY))]]
$fd_t _open_osfhandle(intptr_t osfd, $oflag_t flags) {
	(void)flags;
	COMPILER_IMPURE();
	return (fd_t)osfd;
}



%
%
%/* Weird, new functions not apart of any well-established standard. */
%

%
%/* WARNING: `setmode(3)' is also a completely different BSD-specific function in <unistd.h>! */
%[insert:guarded_function(setmode = _setmode)]
%[insert:function(chsize = ftruncate)]
%[insert:function(locking = lockf)]


%[default:section(".text.crt.dos.fs.io")]

[[crt_dos_variant, decl_include("<bits/types.h>")]]
[[cp, vartypes($mode_t), wunused, dos_export_alias("_sopen")]]
[[requires_function(open), section(".text.crt.dos.fs.io")]]
$fd_t sopen([[nonnull]] char const *filename, $oflag_t oflags, int sflags, ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = open(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}




%[default:section(".text.crt.dos.fs.utility")]

[[decl_include("<bits/types.h>")]]
[[wunused, crt_name("_filelength")]]
[[requires_function(lseek)]]
__LONG32_TYPE__ filelength($fd_t fd) {
	__LONG32_TYPE__ oldpos, result;
	oldpos = lseek(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = lseek(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek(fd, oldpos, SEEK_SET);
	return result;
}

%[insert:extern(tell)]

[[decl_include("<bits/types.h>")]]
[[wunused, crt_name("_eof")]]
[[requires_function(lseek64)]]
[[impl_include("<asm/os/stdio.h>")]]
int eof($fd_t fd) {
	$int64_t oldpos, endpos;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	endpos = lseek64(fd, 0, SEEK_END);
	if likely(endpos >= 0) {
		if (endpos == oldpos)
			return 1;
		lseek64(fd, oldpos, SEEK_SET);
	}
	return 0;
}


%{

#ifndef _FINDDATA_T_DEFINED
#define _FINDDATA_T_DEFINED 1
/* Safely first! */
}%[push_macro @undef { attrib time_create time_access time_write size name }]%{
struct _finddata32_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	_fsize_t             size;
	char                 name[260];
};
struct _finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	/* Microsoft:
	 * A: "I mean: we could use an unsigned type for this, seeing as how _fsize_t is also unsigned."
	 * B: "Nah! - Lets rather p1$$ off anyone that notices. - That'll be way more fun." */
	__INT64_TYPE__       size;
	char                 name[260];
};
struct _finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char                 name[260];
};
struct __finddata64_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	__INT64_TYPE__       size;
	char                 name[260];
};

}%[pop_macro]%{

#ifdef __USE_TIME_BITS64
#define _finddata_t                       _finddata64i32_t
#define _finddatai64_t                    __finddata64_t
#define _findfirst(filename, finddata)    _findfirst64i32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext64i32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _finddata_t                       _finddata32_t
#define _finddatai64_t                    _finddata32i64_t
#define _findfirst(filename, finddata)    _findfirst32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst32i64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_FINDDATA_T_DEFINED */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wio.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_IO_H */
#endif /* __USE_UTF */

}
