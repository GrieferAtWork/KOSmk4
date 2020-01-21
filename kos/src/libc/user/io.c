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

#include <hybrid/minmax.h>

#include <kos/syscalls.h>
#include <parts/dos/errno.h>
#include <sys/stat.h>

#include <alloca.h>
#include <dirent.h>
#include <fcntl.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../libc/errno.h"
#include "io.h"

DECL_BEGIN

struct dfind {
	DIR  *df_dir;   /* [1..1][owned] The underlying directory stream. */
	char *df_query; /* [1..1][owned] The wildcard-enabled query pattern. */
};

#define DFIND_INVALID ((struct dfind *)-1)

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir.dfind_open")
struct dfind *LIBCCALL dfind_open(char const *__restrict filename) {
	char const *pathend;
	struct dfind *result;
	result = (struct dfind *)malloc(sizeof(struct dfind));
	if unlikely(!result)
		goto err;
	pathend = strend(filename);
	while (pathend > filename &&
	       (pathend[-1] != '/' && pathend[-1] != '\\'))
		--pathend;
	if unlikely(pathend <= filename) {
		PRIVATE ATTR_SECTION(".rodata.crt.dos.fs.dir.pwd") char const pwd[] = ".";
		result->df_dir = fopendirat(AT_FDCWD, pwd, O_DOSPATH);
	} else {
		char *path;
		size_t pathlen;
		pathlen = (size_t)(pathend - filename);
		path    = (char *)alloca((pathlen + 1) * sizeof(char));
		memcpy(path, filename, pathlen, sizeof(char));
		path[pathlen] = '\0';
		result->df_dir = fopendirat(AT_FDCWD, path, O_DOSPATH);
	}
	if unlikely(!result->df_dir)
		goto err_r;
	result->df_query = strdup(pathend);
	if unlikely(!result->df_query)
		goto err_r_dir;
done:
	return result;
err_r_dir:
	closedir(result->df_dir);
err_r:
	free(result);
err:
	result = DFIND_INVALID;
	goto done;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir.dfind_close")
void LIBCCALL dfind_close(struct dfind *__restrict self) {
	closedir(self->df_dir);
	free(self->df_query);
	free(self);
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir.dfind_readdir")
struct dirent *LIBCCALL dfind_readdir(struct dfind *__restrict self) {
	struct dirent *result;
	while ((result = readdir(self->df_dir)) != NULL) {
		if (wildstrcasecmp(self->df_query, result->d_name) == 0)
			break;
	}
	return result;
}

#define dfind_attrib(ent, st) \
	((ent)->d_type == DT_DIR ? _A_SUBDIR : _A_NORMAL)

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir.dfind_read32") int LIBCCALL
dfind_read32(struct dfind *__restrict self,
             struct _finddata32_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st,
	            AT_DOSPATH | AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = dfind_attrib(ent, &st);
	finddata->time_create = (s32)st.st_ctime32;
	finddata->time_access = (s32)st.st_atime32;
	finddata->time_write  = (s32)st.st_mtime32;
	finddata->size        = (_fsize_t)st.st_size;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir.dfind_read32i64") int LIBCCALL
dfind_read32i64(struct dfind *__restrict self,
                struct _finddata32i64_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st,
	            AT_DOSPATH | AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = dfind_attrib(ent, &st);
	finddata->time_create = (s32)st.st_ctime32;
	finddata->time_access = (s32)st.st_atime32;
	finddata->time_write  = (s32)st.st_mtime32;
	finddata->size        = (s64)st.st_size64;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir.dfind_read64") int LIBCCALL
dfind_read64(struct dfind *__restrict self,
             struct __finddata64_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st,
	            AT_DOSPATH | AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = dfind_attrib(ent, &st);
	finddata->time_create = (s64)st.st_ctime64;
	finddata->time_access = (s64)st.st_atime64;
	finddata->time_write  = (s64)st.st_mtime64;
	finddata->size        = (s64)st.st_size64;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}





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

/*[[[head:_findclose,hash:CRC-32=0x8eedab75]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findclose") int
NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd)
/*[[[body:_findclose]]]*/
{
	struct dfind *f;
	f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID) {
		libd_seterrno(__DOS_EINVAL);
		return -1;
	}
	dfind_close(f);
	return 0;
}
/*[[[end:_findclose]]]*/

/*[[[head:_findfirst32,hash:CRC-32=0xc346019a]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findfirst32") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:_findfirst32]]]*/
{
	struct dfind *result;
	result = dfind_open(filename);
	if likely(result != DFIND_INVALID) {
		if (dfind_read32(result, finddata) != 0) {
			dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}
/*[[[end:_findfirst32]]]*/

/*[[[head:_findfirst32i64,hash:CRC-32=0x2d7f90d0]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findfirst32i64") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findfirst32i64]]]*/
{
	struct dfind *result;
	result = dfind_open(filename);
	if likely(result != DFIND_INVALID) {
		if (dfind_read32i64(result, finddata) != 0) {
			dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}
/*[[[end:_findfirst32i64]]]*/

/*[[[head:_findfirst64,hash:CRC-32=0x7c8dcd1b]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findfirst64") intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64)(char const *__restrict filename,
                                        struct __finddata64_t *__restrict finddata)
/*[[[body:_findfirst64]]]*/
{
	struct dfind *result;
	result = dfind_open(filename);
	if likely(result != DFIND_INVALID) {
		if (dfind_read64(result, finddata) != 0) {
			dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}
/*[[[end:_findfirst64]]]*/

/*[[[head:_findnext32,hash:CRC-32=0x663d78f4]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findnext32") int
NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata)
/*[[[body:_findnext32]]]*/
{
	int result;
	struct dfind *f;
	f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID) {
		libd_seterrno(__DOS_EINVAL);
		return -1;
	}
	result = dfind_read32(f, finddata);
	return result;
}
/*[[[end:_findnext32]]]*/

/*[[[head:_findnext32i64,hash:CRC-32=0x8f4be020]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findnext32i64") int
NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata)
/*[[[body:_findnext32i64]]]*/
{
	int result;
	struct dfind *f;
	f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID) {
		libd_seterrno(__DOS_EINVAL);
		return -1;
	}
	result = dfind_read32i64(f, finddata);
	return result;
}
/*[[[end:_findnext32i64]]]*/

/*[[[head:_findnext64,hash:CRC-32=0x6de6055f]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dir._findnext64") int
NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata)
/*[[[body:_findnext64]]]*/
{
	int result;
	struct dfind *f;
	f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID) {
		libd_seterrno(__DOS_EINVAL);
		return -1;
	}
	result = dfind_read64(f, finddata);
	return result;
}
/*[[[end:_findnext64]]]*/

/*[[[head:_sopen_s,hash:CRC-32=0x8bf43ee2]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.io._sopen_s") errno_t
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

/*[[[head:_mktemp_s,hash:CRC-32=0x14c62739]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._mktemp_s") errno_t
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

/*[[[head:_pipe,hash:CRC-32=0x701f875d]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.io._pipe") int
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

/*[[[head:_filelengthi64,hash:CRC-32=0xb2791f4c]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._filelengthi64") int64_t
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

/*[[[head:_telli64,hash:CRC-32=0x5e4104e5]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._telli64") int64_t
NOTHROW_NCX(LIBCCALL libc__telli64)(fd_t fd)
/*[[[body:_telli64]]]*/
{
	return (int64_t)lseek64(fd, 0, SEEK_CUR);
}
/*[[[end:_telli64]]]*/

/*[[[head:umask_s,hash:CRC-32=0x11245d13]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.basic_property.umask_s") errno_t
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

/*[[[head:__lock_fhandle,hash:CRC-32=0x6d20771c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility.__lock_fhandle") int
NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd)
/*[[[body:__lock_fhandle]]]*/
{
	(void)fd; /* no-op */
	COMPILER_IMPURE();
	return 0;
}
/*[[[end:__lock_fhandle]]]*/

/*[[[head:_unlock_fhandle,hash:CRC-32=0x77e5b002]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._unlock_fhandle") void
NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd)
/*[[[body:_unlock_fhandle]]]*/
{
	(void)fd; /* no-op */
	COMPILER_IMPURE();
}
/*[[[end:_unlock_fhandle]]]*/

/*[[[head:sopen,hash:CRC-32=0x69befb88]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.io.sopen") fd_t
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

/*[[[head:filelength,hash:CRC-32=0xb0a1324]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility.filelength") __LONG32_TYPE__
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

/*[[[head:eof,hash:CRC-32=0xbbbe9720]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility.eof") int
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

/*[[[head:tell,hash:CRC-32=0x4ed471cc]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility.tell") __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd)
/*[[[body:tell]]]*/
{
	return (__LONG32_TYPE__)lseek(fd, 0, SEEK_CUR);
}
/*[[[end:tell]]]*/

/*[[[head:setmode,hash:CRC-32=0x9d8ef2ab]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.io.setmode") oflag_t
NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd,
                                   oflag_t mode)
/*[[[body:setmode]]]*/
{
	return (oflag_t)fcntl(fd, F_SETFL_XCH, mode);
}
/*[[[end:setmode]]]*/

/*[[[end:implementation]]]*/




#undef _findfirst
#undef _findfirsti64
#undef _findnext
#undef _findnexti64

/*[[[start:exports,hash:CRC-32=0x68124529]]]*/
#undef sopen
#undef _sopen
DEFINE_PUBLIC_WEAK_ALIAS(_access_s, libc__access_s);
DEFINE_PUBLIC_WEAK_ALIAS(_findclose, libc__findclose);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst32, libc__findfirst32);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst, libc__findfirst32);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst32i64, libc__findfirst32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirsti64, libc__findfirst32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst64, libc__findfirst64);
DEFINE_PUBLIC_WEAK_ALIAS(_findfirst64i32, libc__findfirst64);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext32, libc__findnext32);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext, libc__findnext32);
DEFINE_PUBLIC_WEAK_ALIAS(_findnext32i64, libc__findnext32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_findnexti64, libc__findnext32i64);
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
