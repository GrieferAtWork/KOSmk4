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
#ifndef GUARD_LIBC_USER_IO_C
#define GUARD_LIBC_USER_IO_C 1

#include "../api.h"
/**/

#include <hybrid/minmax.h>

#include <kos/syscalls.h>
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
#include "../libc/compat.h"
#include "io.h"

DECL_BEGIN

struct dfind {
	DIR  *df_dir;   /* [1..1][owned] The underlying directory stream. */
	char *df_query; /* [1..1][owned] The wildcard-enabled query pattern. */
};

#define DFIND_INVALID ((struct dfind *)-1)

DEFINE_PUBLIC_ALIAS(__find_open, libc_dfind_open);
INTERN WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") struct dfind *LIBCCALL
libc_dfind_open(char const *__restrict filename, oflag_t oflags) {
	char const *pathend;
	struct dfind *result;
	result = (struct dfind *)malloc(sizeof(struct dfind));
	if unlikely(!result)
		goto err;
	pathend = strend(filename);
	while (pathend > filename &&
	       (pathend[-1] != '/' &&
	        (pathend[-1] != '\\' && (oflags & O_DOSPATH))))
		--pathend;
	if unlikely(pathend <= filename) {
		PRIVATE ATTR_SECTION(".rodata.crt.dos.fs.dir") char const pwd[] = ".";
		result->df_dir = fopendirat(AT_FDCWD, pwd, oflags);
	} else {
		char *path;
		size_t pathlen;
		pathlen = (size_t)(pathend - filename);
		path    = (char *)alloca((pathlen + 1) * sizeof(char));
		memcpy(path, filename, pathlen, sizeof(char));
		path[pathlen] = '\0';
		result->df_dir = fopendirat(AT_FDCWD, path, oflags);
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

INTERN ATTR_SECTION(".text.crt.dos.fs.dir") void LIBCCALL
libc_dfind_close(struct dfind *__restrict self) {
	closedir(self->df_dir);
	free(self->df_query);
	free(self);
}

DEFINE_PUBLIC_ALIAS(__find_readdir, libc_dfind_readdir);
INTERN WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") struct dirent *LIBCCALL
libc_dfind_readdir(struct dfind *__restrict self) {
	struct dirent *result;
	while ((result = readdir(self->df_dir)) != NULL) {
		if (wildstrcasecmp(self->df_query, result->d_name) == 0)
			break;
	}
	return result;
}

#define libc_dfind_attrib(ent, st)                       \
	(((ent)->d_type == DT_DIR ? _A_SUBDIR : _A_NORMAL) | \
	 (((st)->st_mode & 0222) ? 0 : _A_RDONLY) |          \
	 ((ent)->d_name[0] == '.' ? _A_HIDDEN : 0))

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_read32(struct dfind *__restrict self,
                  struct _finddata32_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = libc_dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st, AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = libc_dfind_attrib(ent, &st);
	finddata->time_create = (typeof(finddata->time_create))st.st_btime32;
	finddata->time_access = (typeof(finddata->time_access))st.st_atime32;
	finddata->time_write  = (typeof(finddata->time_write))st.st_mtime32;
	finddata->size        = (typeof(finddata->size))st.st_size;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_read32i64(struct dfind *__restrict self,
                     struct _finddata32i64_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = libc_dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st,
	            AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = libc_dfind_attrib(ent, &st);
	finddata->time_create = (typeof(finddata->time_create))st.st_btime32;
	finddata->time_access = (typeof(finddata->time_access))st.st_atime32;
	finddata->time_write  = (typeof(finddata->time_write))st.st_mtime32;
	finddata->size        = (typeof(finddata->size))st.st_size64;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_read64(struct dfind *__restrict self,
                  struct __finddata64_t *__restrict finddata) {
	struct stat st;
	struct dirent *ent;
	ent = libc_dfind_readdir(self);
	if (!ent)
		goto err;
	if (fstatat(dirfd(self->df_dir), ent->d_name, &st,
	            AT_SYMLINK_NOFOLLOW))
		goto err;
	finddata->attrib      = libc_dfind_attrib(ent, &st);
	finddata->time_create = (typeof(finddata->time_create))st.st_btime64;
	finddata->time_access = (typeof(finddata->time_access))st.st_atime64;
	finddata->time_write  = (typeof(finddata->time_write))st.st_mtime64;
	finddata->size        = (typeof(finddata->size))st.st_size64;
	memcpy(finddata->name, ent->d_name,
	       MIN(ent->d_namlen, COMPILER_LENOF(finddata->name)),
	       sizeof(char));
	finddata->name[COMPILER_LENOF(finddata->name) - 1] = 0;
	return 0;
err:
	return -1;
}


/*[[[head:libc__findclose,hash:CRC-32=0xd06b2791]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") int
NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd)
/*[[[body:libc__findclose]]]*/
{
	struct dfind *f;
	f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	libc_dfind_close(f);
	return 0;
}
/*[[[end:libc__findclose]]]*/

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32_impl)(char const *__restrict filename,
                                             struct _finddata32_t *__restrict finddata,
                                             oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_open(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_read32(result, finddata) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__findfirst32,hash:CRC-32=0x7c66585b]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:libd__findfirst32]]]*/
{
	return libc__findfirst32_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__findfirst32]]]*/

/*[[[head:libc__findfirst32,hash:CRC-32=0xffa7bb5c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata)
/*[[[body:libc__findfirst32]]]*/
{
	return libc__findfirst32_impl(filename, finddata, 0);
}
/*[[[end:libc__findfirst32]]]*/


PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64_impl)(char const *__restrict filename,
                                                struct _finddata32i64_t *__restrict finddata,
                                                oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_open(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_read32i64(result, finddata) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__findfirst32i64,hash:CRC-32=0x23106d00]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:libd__findfirst32i64]]]*/
{
	return libc__findfirst32i64_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__findfirst32i64]]]*/

/*[[[head:libc__findfirst32i64,hash:CRC-32=0xb860d002]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata)
/*[[[body:libc__findfirst32i64]]]*/
{
	return libc__findfirst32i64_impl(filename, finddata, 0);
}
/*[[[end:libc__findfirst32i64]]]*/


PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64_impl)(char const *__restrict filename,
                                             struct __finddata64_t *__restrict finddata,
                                             oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_open(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_read64(result, finddata) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__findfirst64,hash:CRC-32=0xb66000cc]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst64)(char const *__restrict filename,
                                        struct __finddata64_t *__restrict finddata)
/*[[[body:libd__findfirst64]]]*/
{
	return libc__findfirst64_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__findfirst64]]]*/

/*[[[head:libc__findfirst64,hash:CRC-32=0x2887548c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBCCALL libc__findfirst64)(char const *__restrict filename,
                                        struct __finddata64_t *__restrict finddata)
/*[[[body:libc__findfirst64]]]*/
{
	return libc__findfirst64_impl(filename, finddata, 0);
}
/*[[[end:libc__findfirst64]]]*/


/*[[[head:libc__findnext32,hash:CRC-32=0xe8edc6b3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_OUT(2) int
NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata)
/*[[[body:libc__findnext32]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_read32(f, finddata);
}
/*[[[end:libc__findnext32]]]*/

/*[[[head:libc__findnext32i64,hash:CRC-32=0xd9823cc2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_OUT(2) int
NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata)
/*[[[body:libc__findnext32i64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_read32i64(f, finddata);
}
/*[[[end:libc__findnext32i64]]]*/

/*[[[head:libc__findnext64,hash:CRC-32=0x2da7b795]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_OUT(2) int
NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata)
/*[[[body:libc__findnext64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_read64(f, finddata);
}
/*[[[end:libc__findnext64]]]*/

/*[[[head:libc__mktemp_s,hash:CRC-32=0xeec6d5cd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mktemp_s)(char *template_,
                                     size_t size)
/*[[[body:libc__mktemp_s]]]*/
/*AUTO*/{
	(void)template_;
	(void)size;
	CRT_UNIMPLEMENTEDF("_mktemp_s(template_: %q, size: %Ix)", template_, size); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mktemp_s]]]*/






#undef _findfirst
#undef _findfirsti64
#undef _findnext
#undef _findnexti64

/*[[[start:exports,hash:CRC-32=0xdf2d67f2]]]*/
DEFINE_PUBLIC_ALIAS(_findclose, libc__findclose);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst, libd__findfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst32, libd__findfirst32);
DEFINE_PUBLIC_ALIAS(_findfirst, libc__findfirst32);
DEFINE_PUBLIC_ALIAS(_findfirst32, libc__findfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_findfirsti64, libd__findfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst32i64, libd__findfirst32i64);
DEFINE_PUBLIC_ALIAS(_findfirsti64, libc__findfirst32i64);
DEFINE_PUBLIC_ALIAS(_findfirst32i64, libc__findfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst64i32, libd__findfirst64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst64, libd__findfirst64);
DEFINE_PUBLIC_ALIAS(_findfirst64i32, libc__findfirst64);
DEFINE_PUBLIC_ALIAS(_findfirst64, libc__findfirst64);
DEFINE_PUBLIC_ALIAS(_findnext, libc__findnext32);
DEFINE_PUBLIC_ALIAS(_findnext32, libc__findnext32);
DEFINE_PUBLIC_ALIAS(_findnexti64, libc__findnext32i64);
DEFINE_PUBLIC_ALIAS(_findnext32i64, libc__findnext32i64);
DEFINE_PUBLIC_ALIAS(_findnext64i32, libc__findnext64);
DEFINE_PUBLIC_ALIAS(_findnext64, libc__findnext64);
DEFINE_PUBLIC_ALIAS(_mktemp_s, libc__mktemp_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_IO_C */
