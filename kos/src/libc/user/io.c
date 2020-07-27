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

#define dfind_attrib(ent, st)                            \
	(((ent)->d_type == DT_DIR ? _A_SUBDIR : _A_NORMAL) | \
	 (((st)->st_mode & 0222) ? 0 : _A_RDONLY) |          \
	 ((ent)->d_name[0] == '.' ? _A_HIDDEN : 0))

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

/*[[[head:libc__access_s,hash:CRC-32=0x467308b4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc__access_s)(char const *filename,
                                     int type)
/*[[[body:libc__access_s]]]*/
{
	errno_t error;
	error = sys_access(filename,
	                   (syscall_ulong_t)(unsigned int)type);
	return libd_errno_kos2dos(-error);
}
/*[[[end:libc__access_s]]]*/

/*[[[head:libc__findclose,hash:CRC-32=0xd06b2791]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") int
NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd)
/*[[[body:libc__findclose]]]*/
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
/*[[[end:libc__findclose]]]*/

/*[[[head:libc__findfirst32,hash:CRC-32=0xfe0b33e5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:libc__findfirst32]]]*/
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
/*[[[end:libc__findfirst32]]]*/

/*[[[head:libc__findfirst32i64,hash:CRC-32=0x972e5214]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:libc__findfirst32i64]]]*/
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
/*[[[end:libc__findfirst32i64]]]*/

/*[[[head:libc__findfirst64,hash:CRC-32=0x9a3bf32c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64)(char const *__restrict filename,
                                        struct __finddata64_t *__restrict finddata)
/*[[[body:libc__findfirst64]]]*/
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
/*[[[end:libc__findfirst64]]]*/

/*[[[head:libc__findnext32,hash:CRC-32=0xc2f9d86d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata)
/*[[[body:libc__findnext32]]]*/
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
/*[[[end:libc__findnext32]]]*/

/*[[[head:libc__findnext32i64,hash:CRC-32=0x59d01bfd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata)
/*[[[body:libc__findnext32i64]]]*/
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
/*[[[end:libc__findnext32i64]]]*/

/*[[[head:libc__findnext64,hash:CRC-32=0x4ce65c58]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata)
/*[[[body:libc__findnext64]]]*/
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
/*[[[end:libc__findnext64]]]*/

/*[[[head:libc__sopen_s,hash:CRC-32=0x5885d95b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc__sopen_s)(fd_t *fd,
                                    char const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    mode_t mode)
/*[[[body:libc__sopen_s]]]*/
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
/*[[[end:libc__sopen_s]]]*/

/*[[[head:libc__mktemp_s,hash:CRC-32=0x7a5599fd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mktemp_s)(char *template_,
                                     size_t size)
/*[[[body:libc__mktemp_s]]]*/
/*AUTO*/{
	(void)template_;
	(void)size;
	CRT_UNIMPLEMENTED("_mktemp_s"); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mktemp_s]]]*/



/*[[[end:implementation]]]*/


#undef _findfirst
#undef _findfirsti64
#undef _findnext
#undef _findnexti64

/*[[[start:exports,hash:CRC-32=0x7c0c20c7]]]*/
DEFINE_PUBLIC_ALIAS(_access_s, libc__access_s);
DEFINE_PUBLIC_ALIAS(_findclose, libc__findclose);
DEFINE_PUBLIC_ALIAS(_findfirst, libc__findfirst32);
DEFINE_PUBLIC_ALIAS(_findfirst32, libc__findfirst32);
DEFINE_PUBLIC_ALIAS(_findfirsti64, libc__findfirst32i64);
DEFINE_PUBLIC_ALIAS(_findfirst32i64, libc__findfirst32i64);
DEFINE_PUBLIC_ALIAS(_findfirst64i32, libc__findfirst64);
DEFINE_PUBLIC_ALIAS(_findfirst64, libc__findfirst64);
DEFINE_PUBLIC_ALIAS(_findnext, libc__findnext32);
DEFINE_PUBLIC_ALIAS(_findnext32, libc__findnext32);
DEFINE_PUBLIC_ALIAS(_findnexti64, libc__findnext32i64);
DEFINE_PUBLIC_ALIAS(_findnext32i64, libc__findnext32i64);
DEFINE_PUBLIC_ALIAS(_findnext64i32, libc__findnext64);
DEFINE_PUBLIC_ALIAS(_findnext64, libc__findnext64);
DEFINE_PUBLIC_ALIAS(_sopen_s_nolock, libc__sopen_s);
DEFINE_PUBLIC_ALIAS(_sopen_s, libc__sopen_s);
DEFINE_PUBLIC_ALIAS(_mktemp_s, libc__mktemp_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_IO_C */
