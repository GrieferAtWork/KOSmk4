/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_GRP_C
#define GUARD_LIBC_USER_GRP_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <paths.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>

#include "grp.h"

DECL_BEGIN

/* [0..1][lock(ATOMIC)]
 * A stream to the group database file. (when non-NULL, opened for reading) */
PRIVATE ATTR_SECTION(".bss.crt.database.grp") FILE *group_database = NULL;

/* [0..1][lock(THREAD_UNSAFE)] Heap buffer for the last-read group database entry. */
PRIVATE ATTR_SECTION(".bss.crt.database.grp") char *group_buffer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.database.grp") size_t group_buflen = 0;

/* The group database entry returned by functions such as `getpwent()' */
PRIVATE ATTR_SECTION(".bss.crt.database.grp") struct group group_entry = {};


PRIVATE ATTR_SECTION(".text.crt.database.grp") FILE *
NOTHROW_RPC(LIBCCALL group_opendb)(void) {
	FILE *result, *new_result;
	result = atomic_read(&group_database);
	if (result)
		return result;
	result = fopen(_PATH_GROUP, "r");
	if unlikely(!result)
		return NULL;
	new_result = atomic_cmpxch_val(&group_database, NULL, result);
	if unlikely(new_result != NULL) {
		/* Race condition: Some other thread
		 * opened the file in the mean time. */
		fclose(result);
		result = new_result;
	}
	return result;
}


PRIVATE ATTR_SECTION(".text.crt.database.grp") NONNULL((1)) struct group *
NOTHROW_RPC(LIBCCALL libc_fgetgrfiltered)(FILE *__restrict stream,
                                          gid_t filtered_gid,
                                          char const *filtered_name) {
	struct group *result;
	errno_t saved_errno;
	errno_t error;
	char *buffer = group_buffer;
	size_t buflen = group_buflen;
	saved_errno = libc_geterrno();
	if (!buflen) {
		assert(!buffer);
		buflen = 512;
		buffer = (char *)malloc(512);
		if unlikely(!buffer) {
			buflen = 16;
			buffer = (char *)malloc(16);
			if unlikely(!buffer)
				goto err;
		}
		group_buffer = buffer;
		group_buflen = buflen;
	}
	/* Read the associated entry. */
again:
	error = libc_fgetgrfiltered_r(stream,
	                              &group_entry,
	                              buffer,
	                              buflen,
	                              &result,
	                              filtered_gid,
	                              filtered_name);
	if (error == ENOENT)
		goto err_restore;
	if (error == ERANGE) {
		/* Try to increase the buffer size. */
		char *new_buffer;
		size_t new_buflen = buflen * 2;
		assert(new_buflen > buflen);
		new_buffer = (char *)realloc(buffer, new_buflen);
		if unlikely(!new_buffer) {
			new_buflen = buflen + 1;
			new_buffer = (char *)realloc(buffer, new_buflen);
			if unlikely(!new_buffer)
				goto err;
		}
		group_buffer = buffer = new_buffer;
		group_buflen = buflen = new_buflen;
		goto again;
	}
	libc_seterrno(saved_errno);
	return result;
err_restore:
	libc_seterrno(saved_errno);
err:
	return NULL;
}


/*[[[head:libc_setgrent,hash:CRC-32=0xea716e11]]]*/
/* >> setgrent(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") void
NOTHROW_RPC(LIBCCALL libc_setgrent)(void)
/*[[[body:libc_setgrent]]]*/
{
	FILE *stream = group_opendb();
	if likely(stream)
		rewind(stream);
}
/*[[[end:libc_setgrent]]]*/

/*[[[head:libc_endgrent,hash:CRC-32=0xb7612dbf]]]*/
/* >> endgrent(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endgrent)(void)
/*[[[body:libc_endgrent]]]*/
{
	FILE *stream = atomic_xch(&group_database, NULL);
	if (stream)
		fclose(stream);
	/* Also free up the buffer used to describe the strings
	 * from   statically   allocated   passwd   structures.
	 *
	 * Note that  this  part  is  entirely  thread-unsafe:  If  some
	 * other thread  is currently  using  these buffers,  then  they
	 * will end up accessing free()d (and possible unmapped) memory! */
	{
		char *buffer;
		buffer = group_buffer;
		group_buffer = NULL;
		group_buflen = 0;
		COMPILER_WRITE_BARRIER();
		free(buffer);
	}
}
/*[[[end:libc_endgrent]]]*/

/*[[[head:libc_fgetgrent,hash:CRC-32=0xcfb85688]]]*/
/* >> fgetgrent(3), fgetgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") ATTR_INOUT(1) struct group *
NOTHROW_RPC(LIBCCALL libc_fgetgrent)(FILE *__restrict stream)
/*[[[body:libc_fgetgrent]]]*/
{
	return libc_fgetgrfiltered(stream, (uid_t)-1, NULL);
}
/*[[[end:libc_fgetgrent]]]*/

/*[[[head:libc_getgrgid,hash:CRC-32=0x591c3755]]]*/
/* >> getgrgid(3), getgrgid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") WUNUSED struct group *
NOTHROW_RPC(LIBCCALL libc_getgrgid)(gid_t gid)
/*[[[body:libc_getgrgid]]]*/
{
	struct group *result;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetgrfiltered(stream, gid, NULL);
	return result;
}
/*[[[end:libc_getgrgid]]]*/

/*[[[head:libc_getgrnam,hash:CRC-32=0x5e609a8d]]]*/
/* >> getgrnam(3), getgrnam_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") WUNUSED ATTR_IN(1) struct group *
NOTHROW_RPC(LIBCCALL libc_getgrnam)(char const *__restrict name)
/*[[[body:libc_getgrnam]]]*/
{
	struct group *result;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetgrfiltered(stream, (uid_t)-1, name);
	return result;
}
/*[[[end:libc_getgrnam]]]*/

/*[[[head:libc_getgrent,hash:CRC-32=0xb94ca4a2]]]*/
/* >> getgrent(3), getgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") WUNUSED struct group *
NOTHROW_RPC(LIBCCALL libc_getgrent)(void)
/*[[[body:libc_getgrent]]]*/
{
	struct group *result;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetgrent(stream);
	return result;
}
/*[[[end:libc_getgrent]]]*/


/*[[[head:libc_getgrgid_r,hash:CRC-32=0xa17d73d4]]]*/
/* >> getgrgid(3), getgrgid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int
NOTHROW_RPC(LIBCCALL libc_getgrgid_r)(gid_t gid,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrgid_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetgrgid_r(stream,
	                    gid,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getgrgid_r]]]*/

/*[[[head:libc_getgrnam_r,hash:CRC-32=0x141dfb99]]]*/
/* >> getgrnam(3), getgrnam_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int
NOTHROW_RPC(LIBCCALL libc_getgrnam_r)(char const *__restrict name,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrnam_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetgrnam_r(stream,
	                    name,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getgrnam_r]]]*/

/*[[[head:libc_getgrent_r,hash:CRC-32=0x911e03a6]]]*/
/* >> getgrent(3), getgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) int
NOTHROW_RPC(LIBCCALL libc_getgrent_r)(struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrent_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = group_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetgrent_r(stream,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getgrent_r]]]*/

/*[[[head:libc_setgroups,hash:CRC-32=0xa01621e2]]]*/
/* >> setgroups(2) */
INTERN ATTR_SECTION(".text.crt.database.grp") ATTR_INS(2, 1) int
NOTHROW_RPC(LIBCCALL libc_setgroups)(size_t count,
                                     gid_t const *groups)
/*[[[body:libc_setgroups]]]*/
{
	errno_t error;
#if defined(SYS_setgroups32) && __SIZEOF_GID_T__ == 4
	error = sys_setgroups32(count, (u32 const *)groups);
#else /* SYS_setgroups32 && __SIZEOF_GID_T__ == 4 */
	error = sys_setgroups(count, groups);
#endif /* !SYS_setgroups32 || __SIZEOF_GID_T__ != 4 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setgroups]]]*/







/*[[[start:exports,hash:CRC-32=0x838d2ade]]]*/
DEFINE_PUBLIC_ALIAS(getgrgid, libc_getgrgid);
DEFINE_PUBLIC_ALIAS(getgrnam, libc_getgrnam);
DEFINE_PUBLIC_ALIAS(setgrent, libc_setgrent);
DEFINE_PUBLIC_ALIAS(endgrent, libc_endgrent);
DEFINE_PUBLIC_ALIAS(getgrent, libc_getgrent);
DEFINE_PUBLIC_ALIAS(getgrgid_r, libc_getgrgid_r);
DEFINE_PUBLIC_ALIAS(getgrnam_r, libc_getgrnam_r);
DEFINE_PUBLIC_ALIAS(getgrent_r, libc_getgrent_r);
DEFINE_PUBLIC_ALIAS(fgetgrent, libc_fgetgrent);
DEFINE_PUBLIC_ALIAS(__setgroups, libc_setgroups);
DEFINE_PUBLIC_ALIAS(__libc_setgroups, libc_setgroups);
DEFINE_PUBLIC_ALIAS(setgroups, libc_setgroups);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_GRP_C */
