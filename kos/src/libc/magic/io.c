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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

//%(auto_libc_source)#ifndef __KERNEL__
//%(auto_libc_source)#include "../user/unistd.h"
//%(auto_libc_source)#include "../user/sys.stat.h"
//%(auto_libc_source)#endif

%{
#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifndef _A_NORMAL
#define _A_NORMAL 0x00
#define _A_RDONLY 0x01
#define _A_HIDDEN 0x02
#define _A_SYSTEM 0x04
#define _A_SUBDIR 0x10
#define _A_ARCH   0x20
#endif /* !_A_NORMAL */

#ifdef __CC__

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef _FSIZE_T_DEFINED
#define _FSIZE_T_DEFINED
typedef __UINT32_TYPE__ _fsize_t;
#endif /* _FSIZE_T_DEFINED */

struct _finddata32_t;
struct __finddata64_t; /* I guess something else already using the more obvious choice... */
struct _finddata32i64_t;
struct _finddata64i32_t;

}

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

[cp][dos_function][ATTR_WUNUSED][section(.text.crt.dos.fs.property)]
_access:([nonnull] char const *filename, int type) -> int = access;

[cp][dos_function][ATTR_WUNUSED][section(.text.crt.dos.fs.basic_io)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(creat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(creat)]
[decl_include(<bits/types.h>)]
_creat:([nonnull] char const *filename, $mode_t mode) -> $fd_t = creat;

[cp][dos_function][section(.text.crt.dos.fs.modify)]
[decl_include(<bits/types.h>)]
_chmod:([nonnull] char const *filename, $mode_t mode) -> int = chmod;

[cp][dos_function][section(.text.crt.dos.fs.property)]
_access_s:([nonnull] char const *filename, int type) -> errno_t;

[dos_function][alias(chsize)][section(.text.crt.dos.fs.io)]
[decl_include(<bits/types.h>)]
_chsize:($fd_t fd, __LONG32_TYPE__ size) -> int = ftruncate;

[dos_function][section(.text.crt.dos.fs.io)]
[decl_include(<bits/types.h>)]
_chsize_s:($fd_t fd, $int64_t size) -> errno_t = ftruncate64;

[cp][dos_function][alias(fdatasync)]
[decl_include(<bits/types.h>)][section(.text.crt.dos.fs.io)]
_commit:($fd_t fd) -> int = fsync;

[section(.text.crt.dos.fs.basic_io)]
[alias(lseek)][noexport][nouser][dos_function]
[requires(defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))]
[dependency_string(defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))]
[decl_include(<bits/types.h>)]
_lseek:($fd_t fd, __LONG32_TYPE__ offset, int whence) -> __LONG32_TYPE__ {
	return lseek64(fd, ($off64_t)offset, whence);
}

[dos_function][section(.text.crt.dos.fs.basic_io)]
[decl_include(<bits/types.h>)]
_lseeki64:($fd_t fd, $int64_t offset, int whence) -> $int64_t = lseek64;

[section(.text.crt.dos.fs.io_lock)]
[cp][dos_function][alias(lockf)]
[decl_include(<bits/types.h>)]
_locking:($fd_t fd, int lockmode, __LONG32_TYPE__ length) -> int = locking;

%
%[insert:extern(_unlink)]

%
[section(.text.crt.dos.fs.basic_io)]
[decl_include(<bits/types.h>)]
[dos_function] _close:($fd_t fd) -> int = close;

[section(.text.crt.dos.fs.basic_io)]
[decl_include(<bits/types.h>)]
[dos_function] _dup:($fd_t fd) -> $fd_t = dup;

[section(.text.crt.dos.fs.basic_io)]
[decl_include(<bits/types.h>)]
[dos_function] _dup2:($fd_t oldfd, $fd_t newfd) -> $fd_t = dup2;

%
[section(.text.crt.dos.fs.basic_io)]
[cp][dos_function][decl_include(<bits/types.h>)]
_read:($fd_t fd, void *buf, size_t bufsize) -> ssize_t = read;

[section(.text.crt.dos.fs.basic_io)]
[cp][dos_function][decl_include(<bits/types.h>)]
_write:($fd_t fd, void const *buf, size_t bufsize) -> ssize_t = write;


[section(.text.crt.dos.fs.basic_io)]
[cp][vartypes($mode_t)][dos_function][ATTR_WUNUSED]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(open64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(open)]
[decl_include(<bits/types.h>)]
_open:([nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t = open;

[dos_function][section(.text.crt.dos.fs.io)]
[decl_include(<bits/types.h>)]
_setmode:($fd_t fd, $oflag_t mode) -> $oflag_t = setmode;

[dos_function][section(.text.crt.dos.fs.basic_property)]
[decl_include(<bits/types.h>)]
_umask:($mode_t mode) -> $mode_t = umask;

[dos_function][ATTR_WUNUSED]
[decl_include(<bits/types.h>)]
[section(.text.crt.dos.io.tty)]
_isatty:($fd_t fd) -> int = isatty;


%[default_impl_section(.text.crt.dos.fs.dir)]
%
%
[dos_function] _findclose:(intptr_t findfd) -> int;
[cp][dos_function][ATTR_WUNUSED][alias(_findfirst)]
[cp][dos_function] _findfirst32:([nonnull] char const *__restrict filename, [nonnull] struct _finddata32_t *__restrict finddata) -> intptr_t;
[cp][dos_function][ATTR_WUNUSED][alias(_findfirsti64)]
[cp][dos_function] _findfirst32i64:([nonnull] char const *__restrict filename, [nonnull] struct _finddata32i64_t *__restrict finddata) -> intptr_t;
[cp][dos_function][alias(_findnext)] _findnext32:(intptr_t findfd, [nonnull] struct _finddata32_t *__restrict finddata) -> int;
[cp][dos_function][alias(_findnexti64)] _findnext32i64:(intptr_t findfd, [nonnull] struct _finddata32i64_t *__restrict finddata) -> int;
[cp][dos_function][alias(_findfirst64)][ATTR_WUNUSED] _findfirst64i32:([nonnull] char const *__restrict filename, [nonnull] struct _finddata64i32_t *__restrict finddata) -> intptr_t;
[cp][dos_function][ATTR_WUNUSED] _findfirst64:([nonnull] char const *__restrict filename, [nonnull] struct __finddata64_t *__restrict finddata) -> intptr_t = _findfirst64i32;
[cp][dos_function][alias(_findnext64i32)] _findnext64:(intptr_t findfd, [nonnull] struct __finddata64_t *__restrict finddata) -> int;
[cp][dos_function] _findnext64i32:(intptr_t findfd, [nonnull] struct _finddata64i32_t *__restrict finddata) -> int = _findnext64;

%[default_impl_section(.text.crt.dos.fs.io)]
%
[cp][dos_function][alias(_sopen_s_nolock)][decl_include(<bits/types.h>)]
_sopen_s:([nonnull] $fd_t *fd, [nonnull] char const *filename, $oflag_t oflags, int sflags, $mode_t mode) -> errno_t;

[cp][dos_function][decl_include(<bits/types.h>)]
_sopen_s_nolock:([nonnull] $fd_t *fd, [nonnull] char const *filename, $oflag_t oflags, int sflags, $mode_t mode) -> errno_t = _sopen_s;

[section(.text.crt.dos.fs.utility)]
[dos_function] _mktemp_s:([nonnull] char *template_, size_t size) -> errno_t;

[section(.text.crt.dos.fs.io)]
[cp][dos_function][vartypes($mode_t)][ATTR_WUNUSED][decl_include(<bits/types.h>)]
_sopen:([nonnull] char const *filename, $oflag_t oflags, int sflags, ...) -> $fd_t = sopen;

[section(.text.crt.dos.fs.io)]
[dos_function][requires($has_function(pipe2))]
[decl_include(<bits/types.h>)]
_pipe:([nonnull] $fd_t pipedes[2], $uint32_t pipesize, $oflag_t textmode) -> int {
	(void)pipesize;
	return pipe2(pipedes, textmode);
}

%[default_impl_section(.text.crt.dos.fs.utility)]
[decl_include(<bits/types.h>)][dos_function][ATTR_WUNUSED] _eof:($fd_t fd) -> int = eof;
[decl_include(<bits/types.h>)][dos_function][ATTR_WUNUSED] _filelength:($fd_t fd) -> __LONG32_TYPE__ = filelength;
[decl_include(<bits/types.h>)][dos_function][ATTR_WUNUSED] _tell:($fd_t fd) -> __LONG32_TYPE__ = tell;

[dos_function]
[ATTR_WUNUSED][requires($has_function(lseek64))][noexport]
[decl_include(<bits/types.h>)]
_filelengthi64:($fd_t fd) -> $int64_t {
	int64_t oldpos, result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = lseek64(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek64(fd, oldpos, SEEK_SET);
	return result;
}

[dos_function]
[ATTR_WUNUSED][requires($has_function(lseek64))][noexport]
[decl_include(<bits/types.h>)]
_telli64:($fd_t fd) -> $int64_t {
	return lseek64(fd, 0, SEEK_CUR);
}

%[default_impl_section(.text.crt.dos.fs.basic_property)]
[dos_function]
[dependency_include(<parts/errno.h>)]
[requires($has_function(umask))]
[decl_include(<bits/types.h>)]
umask_s:($mode_t newmode, $mode_t *oldmode) -> errno_t {
	if (!oldmode)
		return __EINVAL;
	*oldmode = umask(newmode);
	return 0;
}

%[default_impl_section(.text.crt.dos.fs.utility)]
[decl_include(<bits/types.h>)]
[cp][dos_function] __lock_fhandle:($fd_t fd) -> int;

[decl_include(<bits/types.h>)]
[dos_function] _unlock_fhandle:($fd_t fd);

[dos_function]
[requires(!defined(__CRT_DOS))][ATTR_WUNUSED][export]
[decl_include(<bits/types.h>)]
_get_osfhandle:($fd_t fd) -> intptr_t {
	return (intptr_t)fd;
}

[dos_function]
[requires(!defined(__CRT_DOS))][ATTR_WUNUSED][export]
[decl_include(<bits/types.h>)]
_open_osfhandle:(intptr_t osfd, $oflag_t flags) -> $fd_t {
	(void)flags;
	return (fd_t)osfd;
}

%
%
%/* Weird, new functions not apart of any standard. */
%

%[default_impl_section(.text.crt.dos.fs.io)]
[dos_function][alias(_setmode)][noexport]
[requires($has_function(fcntl) && (defined(__KOS__) || defined(__linux__)))]
[decl_include(<bits/types.h>)]
setmode:($fd_t fd, $oflag_t mode) -> $oflag_t {
#ifdef __KOS__
	return fcntl(fd, 5163, mode); /* F_SETFL_XCH */
#else
	oflag_t result;
	result = fcntl(fd, 3); /* F_GETFL */
	if unlikely(result < 0)
		return -1;
	return fcntl(fd, 4, mode); /* F_SETFL */
#endif
}


[dos_function][alias(_chsize)]
[decl_include(<bits/types.h>)]
chsize:($fd_t fd, __LONG32_TYPE__ $size) -> int = ftruncate;

[section(.text.crt.dos.fs.io_lock)]
[cp][noexport][nouser]
[dos_function][alias(_locking, lockf)]
[requires(defined(__CRT_HAVE_lockf64))]
[decl_include(<bits/types.h>)]
locking:($fd_t fd, int lockmode, __LONG32_TYPE__ numofbytes) -> int {
	return lockf64(fd, lockmode, (__off64_t)length);
}

[section(.text.crt.dos.fs.io)]
[cp][dos_function][vartypes($mode_t)][ATTR_WUNUSED][noexport]
[alias(_sopen)][requires($has_function(open))]
[decl_include(<bits/types.h>)]
sopen:([nonnull] char const *filename, $oflag_t oflags, int sflags, ...) -> $fd_t {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = open(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}

%[default_impl_section(.text.crt.dos.fs.utility)]
[dos_function]
[alias(_filelength)][noexport][ATTR_WUNUSED]
[requires($has_function(_lseek))]
[decl_include(<bits/types.h>)]
filelength:($fd_t fd) -> __LONG32_TYPE__ {
	__LONG32_TYPE__ oldpos, result;
	oldpos = _lseek(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = _lseek(fd, 0, SEEK_END);
	if likely(result >= 0)
		_lseek(fd, oldpos, SEEK_SET);
	return result;
}

[dos_function]
[ATTR_WUNUSED][noexport][alias(_tell)]
[requires($has_function(_lseek))]
[decl_include(<bits/types.h>)]
tell:($fd_t fd) -> __LONG32_TYPE__ {
	return _lseek(fd, 0, SEEK_CUR);
}

[dos_function]
[ATTR_WUNUSED][noexport][alias(_eof)]
[requires($has_function(lseek64))]
[decl_include(<bits/types.h>)]
eof:($fd_t fd) -> int {
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

/* Safely first! */
}%[push_macro @undef { attrib time_create time_access time_write size name }]%{

#ifndef _FINDDATA_T_DEFINED
#define _FINDDATA_T_DEFINED 1
struct _finddata32_t {
	__UINT32_TYPE__      attrib;
	__time32_t           time_create;
	__time32_t           time_access;
	__time32_t           time_write;
	_fsize_t             size;
	char                 name[260];
};
struct _finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__time32_t           time_create;
	__time32_t           time_access;
	__time32_t           time_write;
	/* Microsoft:
	 * A: "I mean: we could use an unsigned type for this, seeing as how _fsize_t is also unsigned."
	 * B: "Nah! - Lets rather p1$$ off anyone that notices. - That'll be way more fun." */
	__INT64_TYPE__       size;
	char                 name[260];
};
struct _finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__time64_t           time_create;
	__time64_t           time_access;
	__time64_t           time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char                 name[260];
};
struct __finddata64_t {
	__UINT32_TYPE__      attrib;
	__time64_t           time_create;
	__time64_t           time_access;
	__time64_t           time_write;
	__INT64_TYPE__       size;
	char                 name[260];
};

}%[pop_macro]%{

#ifdef __USE_TIME_BITS64
#define _finddata_t                   _finddata64i32_t
#define _finddatai64_t                __finddata64_t
#define _findfirst(filename, finddata)     _findfirst64i32(filename, finddata)
#define _findnext(findfd, finddata)    _findnext64i32(findfd, finddata)
#define _findfirsti64(filename, finddata)  _findfirst64(filename, finddata)
#define _findnexti64(findfd, finddata) _findnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _finddata_t                   _finddata32_t
#define _finddatai64_t                _finddata32i64_t
#define _findfirst(filename, finddata)     _findfirst32(filename, finddata)
#define _findnext(findfd, finddata)    _findnext32(findfd, finddata)
#define _findfirsti64(filename, finddata)  _findfirst32i64(filename, finddata)
#define _findnexti64(findfd, finddata) _findnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_FINDDATA_T_DEFINED */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif
#endif /* __USE_UTF */

}

//TODO:#ifdef __USE_DOS
//TODO:#include "parts/dos/wio.h"
//TODO:#endif /* __USE_DOS */


