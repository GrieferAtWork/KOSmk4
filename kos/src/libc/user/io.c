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
#ifndef GUARD_LIBC_USER_IO_C
#define GUARD_LIBC_USER_IO_C 1

#include "../api.h"
#include "io.h"

#include <fcntl.h>
#include <io.h>
#include <kos/syscalls.h>
#include <stdio.h>
#include <unistd.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_access_s,hash:0xfbcbde4c]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._access_s") errno_t
NOTHROW_RPC(LIBCCALL libc__access_s)(char const *filename,
                                     int type)
/*[[[body:_access_s]]]*/
{
	return -sys_access(filename,
	                   (syscall_ulong_t)(unsigned int)type);
}
/*[[[end:_access_s]]]*/

/*[[[head:_findclose,hash:0xd38348f2]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findclose") int
NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd)
/*[[[body:_findclose]]]*/
{
	CRT_UNIMPLEMENTED("_findclose"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findclose]]]*/

/*[[[head:_findfirst32,hash:0xa5f85bc5]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst32") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:_findfirst32]]]*/
{
	CRT_UNIMPLEMENTED("_findfirst32"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst32]]]*/

/*[[[head:_findfirst32i64,hash:0x77a7a470]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst32i64") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findfirst32i64]]]*/
{
	CRT_UNIMPLEMENTED("_findfirst32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst32i64]]]*/

/*[[[head:_findnext32,hash:0xac05d74b]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext32") int
NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata)
/*[[[body:_findnext32]]]*/
{
	CRT_UNIMPLEMENTED("_findnext32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext32]]]*/

/*[[[head:_findnext32i64,hash:0x2253d363]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext32i64") int
NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findnext32i64]]]*/
{
	CRT_UNIMPLEMENTED("_findnext32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext32i64]]]*/

/*[[[head:_findfirst64i32,hash:0xba5ecf82]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findfirst64i32") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64i32)(char const *__restrict filename,
                                           struct _finddata64i32_t *__restrict finddata)
/*[[[body:_findfirst64i32]]]*/
{
	CRT_UNIMPLEMENTED("_findfirst64i32"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_findfirst64i32]]]*/

/*[[[head:_findnext64,hash:0xd926b914]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._findnext64") int
NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata)
/*[[[body:_findnext64]]]*/
{
	CRT_UNIMPLEMENTED("_findnext64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_findnext64]]]*/

/*[[[head:_sopen_s,hash:0xf9ac6e77]]]*/
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

/*[[[head:_mktemp_s,hash:0xa665eb2e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._mktemp_s") errno_t
NOTHROW_NCX(LIBCCALL libc__mktemp_s)(char *template_,
                                     size_t size)
/*[[[body:_mktemp_s]]]*/
{
	CRT_UNIMPLEMENTED("_mktemp_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_mktemp_s]]]*/

/*[[[head:_pipe,hash:0x6ae9032b]]]*/
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

/*[[[head:_filelengthi64,hash:0xf1071d0e]]]*/
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

/*[[[head:_telli64,hash:0x3c9b2a3a]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._telli64") int64_t
NOTHROW_NCX(LIBCCALL libc__telli64)(fd_t fd)
/*[[[body:_telli64]]]*/
{
	return (int64_t)lseek64(fd, 0, SEEK_CUR);
}
/*[[[end:_telli64]]]*/

/*[[[head:umask_s,hash:0x7992dc31]]]*/
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

/*[[[head:__lock_fhandle,hash:0x55be9173]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.__lock_fhandle") int
NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd)
/*[[[body:__lock_fhandle]]]*/
{
	(void)fd; /* no-op */
	return 0;
}
/*[[[end:__lock_fhandle]]]*/

/*[[[head:_unlock_fhandle,hash:0xdb5d1733]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._unlock_fhandle") void
NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd)
/*[[[body:_unlock_fhandle]]]*/
{
	(void)fd; /* no-op */
}
/*[[[end:_unlock_fhandle]]]*/

/*[[[head:sopen,hash:0x92392a65]]]*/
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

/*[[[head:filelength,hash:0xb7863541]]]*/
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

/*[[[head:eof,hash:0xa81f62d1]]]*/
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

/*[[[head:tell,hash:0x9e4d48ac]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.tell") __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd)
/*[[[body:tell]]]*/
{
	return (__LONG32_TYPE__)lseek(fd, 0, SEEK_CUR);
}
/*[[[end:tell]]]*/

/*[[[head:setmode,hash:0x9efc2c58]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.setmode") oflag_t
NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd,
                                   oflag_t mode)
/*[[[body:setmode]]]*/
{
	return (oflag_t)fcntl(fd, F_SETFL_XCH, mode);
}
/*[[[end:setmode]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x233405a0]]]*/
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
