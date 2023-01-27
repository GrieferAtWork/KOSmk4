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
#ifndef GUARD_LIBC_USER_SHADOW_C
#define GUARD_LIBC_USER_SHADOW_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <assert.h>
#include <malloc.h>
#include <paths.h>
#include <stdio.h>

#include "shadow.h"

DECL_BEGIN

#ifndef _PATH_SHADOW
#define _PATH_SHADOW "/etc/shadow"
#endif /* !_PATH_SHADOW */

/* [0..1][lock(ATOMIC)]
 * A stream to the password database file. (when non-NULL, opened for reading) */
PRIVATE ATTR_SECTION(".bss.crt.database.shadow") FILE *shadow_database = NULL;

/* [0..1][lock(THREAD_UNSAFE)] Heap buffer for the last-read password database entry. */
PRIVATE ATTR_SECTION(".bss.crt.database.shadow") char *shadow_buffer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.database.shadow") size_t shadow_buflen = 0;

/* The password database entry returned by functions such as `getpwent()' */
PRIVATE ATTR_SECTION(".bss.crt.database.shadow") struct spwd shadow_entry = {};


PRIVATE ATTR_SECTION(".text.crt.database.shadow") FILE *
NOTHROW_RPC(LIBCCALL shadow_opendb)(void) {
	FILE *result, *new_result;
	result = ATOMIC_READ(shadow_database);
	if (result)
		return result;
	result = fopen(_PATH_SHADOW, "r");
	if unlikely(!result)
		return NULL;
	new_result = ATOMIC_CMPXCH_VAL(shadow_database,
	                               NULL, result);
	if unlikely(new_result != NULL) {
		/* Race condition: Some other thread
		 * opened the file in the mean time. */
		fclose(result);
		result = new_result;
	}
	return result;
}


/*[[[head:libc_setspent,hash:CRC-32=0x8a151368]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC(LIBCCALL libc_setspent)(void)
/*[[[body:libc_setspent]]]*/
{
	FILE *stream = shadow_opendb();
	if likely(stream)
		rewind(stream);
}
/*[[[end:libc_setspent]]]*/

/*[[[head:libc_endspent,hash:CRC-32=0x49326e3a]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endspent)(void)
/*[[[body:libc_endspent]]]*/
{
	FILE *stream = ATOMIC_XCH(shadow_database, NULL);
	if (stream)
		fclose(stream);
	/* Also free up the buffer used to describe the strings
	 * from   statically   allocated   shadow   structures.
	 *
	 * Note that  this  part  is  entirely  thread-unsafe:  If  some
	 * other thread  is currently  using  these buffers,  then  they
	 * will end up accessing free()d (and possible unmapped) memory! */
	{
		char *buffer;
		buffer = shadow_buffer;
		shadow_buffer = NULL;
		shadow_buflen = 0;
		COMPILER_WRITE_BARRIER();
		free(buffer);
	}
}
/*[[[end:libc_endspent]]]*/

PRIVATE ATTR_SECTION(".text.crt.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBCCALL libc_fgetspnam)(FILE *__restrict stream,
                                     char const *filtered_name) {
	struct spwd *result;
	errno_t saved_errno;
	errno_t error;
	char *buffer = shadow_buffer;
	size_t buflen = shadow_buflen;
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
		shadow_buffer = buffer;
		shadow_buflen = buflen;
	}
	/* Read the associated entry. */
again:
	error = libc_fgetspnam_r(stream,
	                         filtered_name,
	                         &shadow_entry,
	                         buffer,
	                         buflen,
	                         &result);
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
		shadow_buffer = buffer = new_buffer;
		shadow_buflen = buflen = new_buflen;
		goto again;
	}
	libc_seterrno(saved_errno);
	return result;
err_restore:
	libc_seterrno(saved_errno);
err:
	return NULL;
}

/*[[[head:libc_getspent,hash:CRC-32=0xa234ff7]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") WUNUSED struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspent)(void)
/*[[[body:libc_getspent]]]*/
{
	struct spwd *result;
	FILE *stream;
	stream = shadow_opendb();
	if unlikely(!stream)
		return NULL;
	result = fgetspent(stream);
	return result;
}
/*[[[end:libc_getspent]]]*/

/*[[[head:libc_getspnam,hash:CRC-32=0x28985f5e]]]*/
/* >> getspnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read shadow entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.shadow") WUNUSED ATTR_IN(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspnam)(char const *__restrict name)
/*[[[body:libc_getspnam]]]*/
{
	struct spwd *result;
	FILE *stream;
	stream = shadow_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetspnam(stream, name);
	return result;
}
/*[[[end:libc_getspnam]]]*/


/*[[[head:libc_fgetspent,hash:CRC-32=0x900e4ed3]]]*/
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.shadow") WUNUSED ATTR_INOUT(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_fgetspent)(FILE *__restrict stream)
/*[[[body:libc_fgetspent]]]*/
{
	return libc_fgetspnam(stream, NULL);
}
/*[[[end:libc_fgetspent]]]*/


/*[[[head:libc_getspent_r,hash:CRC-32=0xb50806d6]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBCCALL libc_getspent_r)(struct spwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:libc_getspent_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = shadow_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetspent_r(stream,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getspent_r]]]*/

/*[[[head:libc_getspnam_r,hash:CRC-32=0x62448038]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc_getspnam_r)(char const *__restrict name,
                                      struct spwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:libc_getspnam_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = shadow_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetspnam_r(stream,
	                    name,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getspnam_r]]]*/



/*[[[head:libc_lckpwdf,hash:CRC-32=0xa0976341]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_RPC_KOS(LIBCCALL libc_lckpwdf)(void)
/*[[[body:libc_lckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("lckpwdf"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_lckpwdf]]]*/

/*[[[head:libc_ulckpwdf,hash:CRC-32=0x80daa9be]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_NCX(LIBCCALL libc_ulckpwdf)(void)
/*[[[body:libc_ulckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ulckpwdf"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_ulckpwdf]]]*/





/*[[[start:exports,hash:CRC-32=0xff91129f]]]*/
DEFINE_PUBLIC_ALIAS(__setspent, libc_setspent);
DEFINE_PUBLIC_ALIAS(setspent, libc_setspent);
DEFINE_PUBLIC_ALIAS(__endspent, libc_endspent);
DEFINE_PUBLIC_ALIAS(endspent, libc_endspent);
DEFINE_PUBLIC_ALIAS(__getspent, libc_getspent);
DEFINE_PUBLIC_ALIAS(getspent, libc_getspent);
DEFINE_PUBLIC_ALIAS(__getspnam, libc_getspnam);
DEFINE_PUBLIC_ALIAS(getspnam, libc_getspnam);
DEFINE_PUBLIC_ALIAS(fgetspent, libc_fgetspent);
DEFINE_PUBLIC_ALIAS(getspent_r, libc_getspent_r);
DEFINE_PUBLIC_ALIAS(getspnam_r, libc_getspnam_r);
DEFINE_PUBLIC_ALIAS(__lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_ALIAS(lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_ALIAS(__ulckpwdf, libc_ulckpwdf);
DEFINE_PUBLIC_ALIAS(ulckpwdf, libc_ulckpwdf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SHADOW_C */
