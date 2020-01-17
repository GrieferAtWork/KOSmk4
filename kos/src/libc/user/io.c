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
#ifndef GUARD_LIBC_USER_IO_C
#define GUARD_LIBC_USER_IO_C 1

#include "../api.h"
/**/

#include "../libc/errno.h"
#include "io.h"

#include <fcntl.h>
#include <io.h>
#include <kos/syscalls.h>
#include <stdio.h>
#include <unistd.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_access_s,hash:CRC-32=0xa45154a8]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._access_s") errno_t
NOTHROW_RPC(LIBCCALL libc__access_s)(char const *filename,
                                     int type)
/*[[[body:_access_s]]]*/
{
	errno_t error;
	error = sys_access(filename,
	                   (syscall_ulong_t)(unsigned int)type);
	return libd_errno_kos2dos(-error);
}
/*[[[end:_access_s]]]*/

/*[[[head:_findclose,hash:CRC-32=0x6ff1c05d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findclose") int
NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd)
/*[[[body:_findclose]]]*/
{
	(void)findfd;
	CRT_UNIMPLEMENTED("_findclose"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findclose]]]*/

/*[[[head:_findfirst32,hash:CRC-32=0x75e2a634]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst32") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:_findfirst32]]]*/
{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findfirst32"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst32]]]*/

/*[[[head:_findfirst32i64,hash:CRC-32=0xff334ba1]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst32i64") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findfirst32i64]]]*/
{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findfirst32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst32i64]]]*/

/*[[[head:_findnext32,hash:CRC-32=0xe91e0889]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext32") int
NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata)
/*[[[body:_findnext32]]]*/
{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findnext32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext32]]]*/

/*[[[head:_findnext32i64,hash:CRC-32=0xd60a4584]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext32i64") int
NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findnext32i64]]]*/
{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findnext32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext32i64]]]*/

/*[[[head:_findfirst64i32,hash:CRC-32=0x9e9b42dd]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst64i32") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64i32)(char const *__restrict filename,
                                           struct _finddata64i32_t *__restrict finddata)
/*[[[body:_findfirst64i32]]]*/
{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findfirst64i32"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst64i32]]]*/

/*[[[head:_findnext64,hash:CRC-32=0x43dd2bae]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext64") int
NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata)
/*[[[body:_findnext64]]]*/
{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTED("_findnext64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext64]]]*/

/*[[[head:_sopen_s,hash:CRC-32=0x840ebcbd]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._sopen_s") errno_t
NOTHROW_RPC(LIBCCALL libc__sopen_s)(fd_t *fd,
                                    char const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    mode_t mode)
/*[[[body:_sopen_s]]]*/
{
	fd_t resfd;
	if unlikely(!fd)
		return EINVAL;
	(void)sflags; /* XXX: Share-mode? */
	resfd = sys_open(filename,
	                 oflags,
	                 mode);
	if (E_ISERR(resfd))
		return -(errno_t)resfd;
	*fd = resfd;
	return EOK;
}
/*[[[end:_sopen_s]]]*/

/*[[[head:_mktemp_s,hash:CRC-32=0x7367b64e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._mktemp_s") errno_t
NOTHROW_NCX(LIBCCALL libc__mktemp_s)(char *template_,
                                     size_t size)
/*[[[body:_mktemp_s]]]*/
{
	(void)template_;
	(void)size;
	CRT_UNIMPLEMENTED("_mktemp_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_mktemp_s]]]*/

/*[[[head:_pipe,hash:CRC-32=0x6797ad3b]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._pipe") int
NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2],
                                 uint32_t pipesize,
                                 oflag_t textmode)
/*[[[body:_pipe]]]*/
{
	(void)pipesize;
	(void)textmode;
	return pipe(pipedes);
}
/*[[[end:_pipe]]]*/

/*[[[head:_filelengthi64,hash:CRC-32=0x73b5b47f]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._filelengthi64") int64_t
NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd)
/*[[[body:_filelengthi64]]]*/
{
	off64_t oldpos, result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		goto err;
	result = lseek64(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek64(fd, oldpos, SEEK_SET);
	return (int64_t)result;
err:
	return -1;
}
/*[[[end:_filelengthi64]]]*/

/*[[[head:_telli64,hash:CRC-32=0x30de0469]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._telli64") int64_t
NOTHROW_NCX(LIBCCALL libc__telli64)(fd_t fd)
/*[[[body:_telli64]]]*/
{
	return (int64_t)lseek64(fd, 0, SEEK_CUR);
}
/*[[[end:_telli64]]]*/

/*[[[head:umask_s,hash:CRC-32=0x47378268]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.umask_s") errno_t
NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode,
                                   mode_t *oldmode)
/*[[[body:umask_s]]]*/
{
	mode_t result;
	if (!oldmode)
		return EINVAL;
	result = sys_umask(newmode);
	if (E_ISERR(result))
		return -(errno_t)result;
	*oldmode = result;
	return EOK;
}
/*[[[end:umask_s]]]*/

/*[[[head:__lock_fhandle,hash:CRC-32=0x60cafd83]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.__lock_fhandle") int
NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd)
/*[[[body:__lock_fhandle]]]*/
{
	(void)fd; /* no-op */
	COMPILER_IMPURE();
	return 0;
}
/*[[[end:__lock_fhandle]]]*/

/*[[[head:_unlock_fhandle,hash:CRC-32=0x193465]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._unlock_fhandle") void
NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd)
/*[[[body:_unlock_fhandle]]]*/
{
	(void)fd; /* no-op */
	COMPILER_IMPURE();
}
/*[[[end:_unlock_fhandle]]]*/

/*[[[head:sopen,hash:CRC-32=0xfbce2e5f]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.sopen") fd_t
NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename,
                                  oflag_t oflags,
                                  int sflags,
                                  ...)
/*[[[body:sopen]]]*/
{
	fd_t result;
	va_list args;
	(void)sflags; /* XXX: Share-mode? */
	va_start(args, sflags);
	result = sys_open(filename,
	                  oflags,
	                  va_arg(args, mode_t));
	va_end(args);
	return result;
}
/*[[[end:sopen]]]*/

/*[[[head:filelength,hash:CRC-32=0xcac6b817]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.filelength") __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc_filelength)(fd_t fd)
/*[[[body:filelength]]]*/
{
	off32_t oldpos, result;
	oldpos = lseek(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		goto err;
	result = lseek(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek(fd, oldpos, SEEK_SET);
	return (__LONG32_TYPE__)result;
err:
	return -1;
}
/*[[[end:filelength]]]*/

/*[[[head:eof,hash:CRC-32=0x9371f1dd]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.eof") int
NOTHROW_NCX(LIBCCALL libc_eof)(fd_t fd)
/*[[[body:eof]]]*/
{
	off64_t oldpos, endpos;
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
/*[[[end:eof]]]*/

/*[[[head:tell,hash:CRC-32=0x204b7140]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.tell") __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd)
/*[[[body:tell]]]*/
{
	return (__LONG32_TYPE__)lseek(fd, 0, SEEK_CUR);
}
/*[[[end:tell]]]*/

/*[[[head:setmode,hash:CRC-32=0x65542c1d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.setmode") oflag_t
NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd,
                                   oflag_t mode)
/*[[[body:setmode]]]*/
{
	return (oflag_t)fcntl(fd, F_SETFL_XCH, mode);
}
/*[[[end:setmode]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc0b8c3f2]]]*/
#undef sopen
#undef _sopen
DEFINE_PUBLIC_WEAK_ALIAS(_access_s, libc__access_s);
DEFINE_PUBLIC_WEAK_ALIAS(_findclose, libc__findclose);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst32, libc__findfirst32);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst32i64, libc__findfirst32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext32, libc__findnext32);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext32i64, libc__findnext32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst64i32, libc__findfirst64i32);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst64, libc__findfirst64i32);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext64, libc__findnext64);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext64i32, libc__findnext64);
DEFINE_PUBLIC_WEAK_ALIAS(_sopen_s, libc__sopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(_sopen_s_nolock, libc__sopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(_mktemp_s, libc__mktemp_s);
DEFINE_PUBLIC_WEAK_ALIAS(_pipe, libc__pipe);
DEFINE_PUBLIC_WEAK_ALIAS(_filelengthi64, libc__filelengthi64);
DEFINE_PUBLIC_WEAK_ALIAS(_telli64, libc__telli64);
DEFINE_PUBLIC_WEAK_ALIAS(umask_s, libc_umask_s);
DEFINE_PUBLIC_WEAK_ALIAS(__lock_fhandle, libc___lock_fhandle);
DEFINE_PUBLIC_WEAK_ALIAS(_unlock_fhandle, libc__unlock_fhandle);
DEFINE_PUBLIC_WEAK_ALIAS(setmode, libc_setmode);
DEFINE_PUBLIC_WEAK_ALIAS(_setmode, libc_setmode);
DEFINE_PUBLIC_WEAK_ALIAS(sopen, libc_sopen);
DEFINE_PUBLIC_WEAK_ALIAS(_sopen, libc_sopen);
DEFINE_PUBLIC_WEAK_ALIAS(filelength, libc_filelength);
DEFINE_PUBLIC_WEAK_ALIAS(_filelength, libc_filelength);
DEFINE_PUBLIC_WEAK_ALIAS(tell, libc_tell);
DEFINE_PUBLIC_WEAK_ALIAS(_tell, libc_tell);
DEFINE_PUBLIC_WEAK_ALIAS(eof, libc_eof);
DEFINE_PUBLIC_WEAK_ALIAS(_eof, libc_eof);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_IO_C */
