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
#ifndef GUARD_LIBC_USER_CORECRT_WIO_C
#define GUARD_LIBC_USER_CORECRT_WIO_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <kos/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <fcntl.h>
#include <io.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include <uchar.h>
#include <unicode.h>

#include "../libc/compat.h"
#include "corecrt_wio.h"

DECL_BEGIN

/************************************************************************/
/* From "user/io.c"                                                     */
/************************************************************************/
struct dfind {
	DIR  *df_dir;   /* [1..1][owned] The underlying directory stream. */
	char *df_query; /* [1..1][owned] The wildcard-enabled query pattern. */
};

#define DFIND_INVALID ((struct dfind *)-1)

INTDEF WUNUSED struct dfind *LIBCCALL libc_dfind_open(char const *__restrict filename, oflag_t oflags);
INTDEF void LIBCCALL libc_dfind_close(struct dfind *__restrict self);
INTDEF WUNUSED struct dirent *LIBCCALL libc_dfind_readdir(struct dfind *__restrict self);
#define libc_dfind_attrib(ent, st)                       \
	(((ent)->d_type == DT_DIR ? _A_SUBDIR : _A_NORMAL) | \
	 (((st)->st_mode & 0222) ? 0 : _A_RDONLY) |          \
	 ((ent)->d_name[0] == '.' ? _A_HIDDEN : 0))
/************************************************************************/


DEFINE_PUBLIC_ALIAS(__find_wopen, libc_dfind_wopen);
INTERN WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") struct dfind *LIBCCALL
libc_dfind_wopen(char32_t const *__restrict filename, oflag_t oflags) {
	struct dfind *result = NULL;
	char *utf8;
	utf8 = convert_c32tombs(filename);
	if likely(utf8) {
		result = libc_dfind_open(utf8, oflags);
		free(utf8);
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(DOS$__find_wopen, libd_dfind_wopen);
INTERN WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") struct dfind *LIBCCALL
libd_dfind_wopen(char16_t const *__restrict filename, oflag_t oflags) {
	struct dfind *result = NULL;
	char *utf8;
	utf8 = convert_c16tombs(filename);
	if likely(utf8) {
		result = libc_dfind_open(utf8, oflags);
		free(utf8);
	}
	return result;
}


PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 3)) void LIBCCALL
fast_encode16(char16_t *__restrict buf, size_t buflen,
              char const *__restrict str, size_t len) {
	char const *end = str + len;
	--buflen; /* For trailing NUL */
	while (buflen && str < end) {
		size_t count;
		char16_t temp[UNICODE_32TO16_MAXBUF(1)];
		char32_t ch;
		ch    = unicode_readutf8_n((char const **)&str, end);
		count = (size_t)(unicode_writeutf16(temp, ch) - temp);
		if (count > buflen)
			break;
		buf = (char16_t *)mempcpy(buf, temp, count, sizeof(char16_t));
		buflen -= count;
	}
	/* Append trailing NUL */
	*buf = 0;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 3)) void LIBCCALL
fast_encode32(char32_t *__restrict buf, size_t buflen,
              char const *__restrict str, size_t len) {
	char const *end = str + len;
	--buflen; /* For trailing NUL */
	while (buflen && str < end) {
		*buf++ = unicode_readutf8_n((char const **)&str, end);
		--buflen;
	}
	/* Append trailing NUL */
	*buf = 0;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 3)) void LIBCCALL
fast_encode(void *__restrict buf, size_t buflen,
            char const *__restrict str, size_t len, bool utf32) {
	if (utf32) {
		fast_encode32((char32_t *)buf, buflen, str, len);
	} else {
		fast_encode16((char16_t *)buf, buflen, str, len);
	}
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_wread32(struct dfind *__restrict self,
                   struct _wfinddata32_t *__restrict finddata,
                   bool utf32) {
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
	fast_encode(finddata->name, lengthof(finddata->name),
	            ent->d_name, ent->d_namlen, utf32);
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_wread32i64(struct dfind *__restrict self,
                      struct _wfinddata32i64_t *__restrict finddata,
                      bool utf32) {
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
	fast_encode(finddata->name, lengthof(finddata->name),
	            ent->d_name, ent->d_namlen, utf32);
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_SECTION(".text.crt.dos.fs.dir") int LIBCCALL
libc_dfind_wread64(struct dfind *__restrict self,
                   struct _wfinddata64_t *__restrict finddata,
                   bool utf32) {
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
	fast_encode(finddata->name, lengthof(finddata->name),
	            ent->d_name, ent->d_namlen, utf32);
	return 0;
err:
	return -1;
}





PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__wfindfirst32_impl)(char32_t const *__restrict filename,
                                              struct _wfinddata32_t *__restrict finddata,
                                              oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread32(result, finddata, true) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libd__wfindfirst32_impl)(char16_t const *__restrict filename,
                                              struct _wfinddata32_t *__restrict finddata,
                                              oflag_t oflags) {
	struct dfind *result;
	result = libd_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread32(result, finddata, false) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__wfindfirst32,hash:CRC-32=0x9570b266]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst32)(char16_t const *__restrict filename,
                                         struct _wfinddata32_t *__restrict finddata)
/*[[[body:libd__wfindfirst32]]]*/
{
	return libd__wfindfirst32_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__wfindfirst32]]]*/

/*[[[head:libc__wfindfirst32,hash:CRC-32=0x4c136983]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst32)(char32_t const *__restrict filename,
                                         struct _wfinddata32_t *__restrict finddata)
/*[[[body:libc__wfindfirst32]]]*/
{
	return libc__wfindfirst32_impl(filename, finddata, 0);
}
/*[[[end:libc__wfindfirst32]]]*/

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libd__wfindfirst32i64_impl)(char16_t const *__restrict filename,
                                                 struct _wfinddata32i64_t *__restrict finddata,
                                                 oflag_t oflags) {
	struct dfind *result;
	result = libd_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread32i64(result, finddata, false) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__wfindfirst32i64_impl)(char32_t const *__restrict filename,
                                                 struct _wfinddata32i64_t *__restrict finddata,
                                                 oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread32i64(result, finddata, true) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__wfindfirst32i64,hash:CRC-32=0x31056f66]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst32i64)(char16_t const *__restrict filename,
                                            struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libd__wfindfirst32i64]]]*/
{
	return libd__wfindfirst32i64_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__wfindfirst32i64]]]*/

/*[[[head:libc__wfindfirst32i64,hash:CRC-32=0x702bf244]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst32i64)(char32_t const *__restrict filename,
                                            struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libc__wfindfirst32i64]]]*/
{
	return libc__wfindfirst32i64_impl(filename, finddata, 0);
}
/*[[[end:libc__wfindfirst32i64]]]*/

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libd__wfindfirst64_impl)(char16_t const *__restrict filename,
                                              struct _wfinddata64_t *__restrict finddata,
                                              oflag_t oflags) {
	struct dfind *result;
	result = libd_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread64(result, finddata, false) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBCCALL libc__wfindfirst64_impl)(char32_t const *__restrict filename,
                                              struct _wfinddata64_t *__restrict finddata,
                                              oflag_t oflags) {
	struct dfind *result;
	result = libc_dfind_wopen(filename, oflags);
	if likely(result != DFIND_INVALID) {
		if (libc_dfind_wread64(result, finddata, true) != 0) {
			libc_dfind_close(result);
			result = DFIND_INVALID;
		}
	}
	return (intptr_t)(uintptr_t)result;
}

/*[[[head:libd__wfindfirst64,hash:CRC-32=0xdcb10781]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst64)(char16_t const *__restrict filename,
                                         struct _wfinddata64_t *__restrict finddata)
/*[[[body:libd__wfindfirst64]]]*/
{
	return libd__wfindfirst64_impl(filename, finddata, libd_O_DOSPATH);
}
/*[[[end:libd__wfindfirst64]]]*/

/*[[[head:libc__wfindfirst64,hash:CRC-32=0x5d2dc64]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst64)(char32_t const *__restrict filename,
                                         struct _wfinddata64_t *__restrict finddata)
/*[[[body:libc__wfindfirst64]]]*/
{
	return libc__wfindfirst64_impl(filename, finddata, 0);
}
/*[[[end:libc__wfindfirst64]]]*/

/*[[[head:libd__wfindnext32,hash:CRC-32=0xe923ac9d]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBDCALL libd__wfindnext32)(intptr_t findfd,
                                        struct _wfinddata32_t *__restrict finddata)
/*[[[body:libd__wfindnext32]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread32(f, finddata, false);
}
/*[[[end:libd__wfindnext32]]]*/

/*[[[head:libc__wfindnext32,hash:CRC-32=0x12b24e0b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBKCALL libc__wfindnext32)(intptr_t findfd,
                                        struct _wfinddata32_t *__restrict finddata)
/*[[[body:libc__wfindnext32]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread32(f, finddata, true);
}
/*[[[end:libc__wfindnext32]]]*/

/*[[[head:libd__wfindnext32i64,hash:CRC-32=0x833e09a5]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBDCALL libd__wfindnext32i64)(intptr_t findfd,
                                           struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libd__wfindnext32i64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread32i64(f, finddata, false);
}
/*[[[end:libd__wfindnext32i64]]]*/

/*[[[head:libc__wfindnext32i64,hash:CRC-32=0xcdae845f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBKCALL libc__wfindnext32i64)(intptr_t findfd,
                                           struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libc__wfindnext32i64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread32i64(f, finddata, true);
}
/*[[[end:libc__wfindnext32i64]]]*/

/*[[[head:libd__wfindnext64,hash:CRC-32=0xe03f2fd5]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBDCALL libd__wfindnext64)(intptr_t findfd,
                                        struct _wfinddata64_t *__restrict finddata)
/*[[[body:libd__wfindnext64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread64(f, finddata, false);
}
/*[[[end:libd__wfindnext64]]]*/

/*[[[head:libc__wfindnext64,hash:CRC-32=0x1baecd43]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(2) int
NOTHROW_RPC(LIBKCALL libc__wfindnext64)(intptr_t findfd,
                                        struct _wfinddata64_t *__restrict finddata)
/*[[[body:libc__wfindnext64]]]*/
{
	struct dfind *f = (struct dfind *)(uintptr_t)findfd;
	if unlikely(f == DFIND_INVALID)
		return libd_seterrno(DOS_EINVAL);
	return libc_dfind_wread64(f, finddata, true);
}
/*[[[end:libc__wfindnext64]]]*/




#undef _wfindfirst
#undef _wfindfirsti64
#undef _wfindnext
#undef _wfindnexti64

/*[[[start:exports,hash:CRC-32=0x8c6c1a57]]]*/
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirst,libd__wfindfirst32,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirst32,libd__wfindfirst32,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirst,libc__wfindfirst32,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirst32,libc__wfindfirst32,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirsti64,libd__wfindfirst32i64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirst32i64,libd__wfindfirst32i64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirsti64,libc__wfindfirst32i64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirst32i64,libc__wfindfirst32i64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirst64i32,libd__wfindfirst64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindfirst64,libd__wfindfirst64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirst64i32,libc__wfindfirst64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindfirst64,libc__wfindfirst64,WUNUSED ATTR_IN(1) ATTR_OUT(2),intptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata),(filename,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnext,libd__wfindnext32,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata32_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnext32,libd__wfindnext32,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata32_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnext,libc__wfindnext32,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata32_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnext32,libc__wfindnext32,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata32_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnexti64,libd__wfindnext32i64,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnext32i64,libd__wfindnext32i64,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnexti64,libc__wfindnext32i64,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnext32i64,libc__wfindnext32i64,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnext64i32,libd__wfindnext64,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfindnext64,libd__wfindnext64,ATTR_OUT(2),int,NOTHROW_RPC,LIBDCALL,(intptr_t findfd, struct _wfinddata64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnext64i32,libc__wfindnext64,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata64_t *__restrict finddata),(findfd,finddata));
DEFINE_PUBLIC_ALIAS_P(_wfindnext64,libc__wfindnext64,ATTR_OUT(2),int,NOTHROW_RPC,LIBKCALL,(intptr_t findfd, struct _wfinddata64_t *__restrict finddata),(findfd,finddata));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WIO_C */
