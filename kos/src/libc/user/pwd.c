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
#ifndef GUARD_LIBC_USER_PWD_C
#define GUARD_LIBC_USER_PWD_C 1

#include "../api.h"
/**/

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <paths.h> /* _PATH_PASSWD */
#include <stdio.h>

#include "pwd.h"

DECL_BEGIN

#ifndef _PATH_PASSWD
#define _PATH_PASSWD "/etc/passwd"
#endif /* !_PATH_PASSWD */

/* [0..1][lock(ATOMIC)]
 * A stream to the password database file. (when non-NULL, opened for reading) */
PRIVATE ATTR_SECTION(".bss.crt.database.pwd") FILE *passwd_database = NULL;

/* [0..1][lock(THREAD_UNSAFE)] Heap buffer for the last-read password database entry. */
PRIVATE ATTR_SECTION(".bss.crt.database.pwd") char *passwd_buffer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.database.pwd") size_t passwd_buflen = 0;

/* The password database entry returned by functions such as `getpwent()' */
PRIVATE ATTR_SECTION(".bss.crt.database.pwd") struct passwd passwd_entry = {};


PRIVATE ATTR_SECTION(".text.crt.database.pwd") FILE *
NOTHROW_RPC(LIBCCALL passwd_opendb)(void) {
	FILE *result, *new_result;
	result = atomic_read(&passwd_database);
	if (result)
		return result;
	result = fopen(_PATH_PASSWD, "r");
	if unlikely(!result)
		return NULL;
	new_result = atomic_cmpxch_val(&passwd_database,
	                               NULL, result);
	if unlikely(new_result != NULL) {
		/* Race condition: Some other thread
		 * opened the file in the mean time. */
		fclose(result);
		result = new_result;
	}
	return result;
}


/* libc4/5 compatibility function */
DEFINE_PUBLIC_ALIAS(setpwfile, libc_setpwfile);
INTERN ATTR_SECTION(".text.crt.compat.linux") int
NOTHROW_RPC(LIBCCALL libc_setpwfile)(char const *filename) {
	/* NOTE: The  original version of  this function didn't actually
	 *       open the file. -- It  merely set the internal  filename
	 *       field to `filename',  and close the  PW database if  it
	 *       was already opened. -- Only the next PW database access
	 *       would then actually open the new file... */
	FILE *nstream, *ostream;
	if (filename == NULL)
		filename = _PATH_PASSWD;
	nstream = fopen(filename, "r");
	if unlikely(!nstream)
		return -1; /* XXX: Original function didn't have error-case */
	ostream = atomic_xch(&passwd_database, nstream);
	if (ostream)
		fclose(ostream);
	return 0;
}



/*[[[head:libc_setpwent,hash:CRC-32=0x29c5c3b]]]*/
/* >> setpwent(3)
 * Rewind the password-file stream */
INTERN ATTR_SECTION(".text.crt.database.pwd") void
NOTHROW_RPC(LIBCCALL libc_setpwent)(void)
/*[[[body:libc_setpwent]]]*/
{
	FILE *stream = passwd_opendb();
	if likely(stream)
		rewind(stream);
}
/*[[[end:libc_setpwent]]]*/

/*[[[head:libc_endpwent,hash:CRC-32=0xa51792a4]]]*/
/* >> endpwent(3)
 * Close the password-file stream */
INTERN ATTR_SECTION(".text.crt.database.pwd") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endpwent)(void)
/*[[[body:libc_endpwent]]]*/
{
	FILE *stream = atomic_xch(&passwd_database, NULL);
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
		buffer = passwd_buffer;
		passwd_buffer = NULL;
		passwd_buflen = 0;
		COMPILER_WRITE_BARRIER();
		free(buffer);
	}
}
/*[[[end:libc_endpwent]]]*/

PRIVATE ATTR_SECTION(".text.crt.database.pwd") NONNULL((1)) struct passwd *
NOTHROW_RPC(LIBCCALL libc_fgetpwfiltered)(FILE *__restrict stream,
                                          uid_t filtered_uid,
                                          char const *filtered_name) {
	struct passwd *result;
	errno_t saved_errno;
	errno_t error;
	char *buffer = passwd_buffer;
	size_t buflen = passwd_buflen;
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
		passwd_buffer = buffer;
		passwd_buflen = buflen;
	}
	/* Read the associated entry. */
again:
	error = libc_fgetpwfiltered_r(stream,
	                              &passwd_entry,
	                              buffer,
	                              buflen,
	                              &result,
	                              filtered_uid,
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
		passwd_buffer = buffer = new_buffer;
		passwd_buflen = buflen = new_buflen;
		goto again;
	}
	libc_seterrno(saved_errno);
	return result;
err_restore:
	libc_seterrno(saved_errno);
err:
	return NULL;
}


/*[[[head:libc_fgetpwent,hash:CRC-32=0xa30c703f]]]*/
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") WUNUSED ATTR_INOUT(1) struct passwd *
NOTHROW_RPC(LIBCCALL libc_fgetpwent)(FILE *__restrict stream)
/*[[[body:libc_fgetpwent]]]*/
{
	return libc_fgetpwfiltered(stream, (uid_t)-1, NULL);
}
/*[[[end:libc_fgetpwent]]]*/

/*[[[head:libc_getpwuid,hash:CRC-32=0xff8835cb]]]*/
/* >> getpwuid(3)
 * Search for an entry with a matching user ID
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `uid' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") WUNUSED struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwuid)(uid_t uid)
/*[[[body:libc_getpwuid]]]*/
{
	struct passwd *result;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetpwfiltered(stream, uid, NULL);
	return result;
}
/*[[[end:libc_getpwuid]]]*/

/*[[[head:libc_getpwnam,hash:CRC-32=0x9900970a]]]*/
/* >> getpwnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") WUNUSED ATTR_IN(1) struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwnam)(char const *name)
/*[[[body:libc_getpwnam]]]*/
{
	struct passwd *result;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetpwfiltered(stream, (uid_t)-1, name);
	return result;
}
/*[[[end:libc_getpwnam]]]*/

/*[[[head:libc_getpwent,hash:CRC-32=0xa18c3b90]]]*/
/* >> getpwent(3)
 * Read an entry from the password-file stream, opening it if necessary
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last  entry  has  already  been  read
 *                                      (use `setpwent()' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwent)(void)
/*[[[body:libc_getpwent]]]*/
{
	struct passwd *result;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return NULL;
	result = libc_fgetpwent(stream);
	return result;
}
/*[[[end:libc_getpwent]]]*/

/*[[[head:libc_getpwuid_r,hash:CRC-32=0x86e278c2]]]*/
/* >> getpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc_getpwuid_r)(uid_t uid,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwuid_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetpwuid_r(stream,
	                    uid,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getpwuid_r]]]*/

/*[[[head:libc_getpwnam_r,hash:CRC-32=0xf296ce76]]]*/
/* >> getpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc_getpwnam_r)(char const *__restrict name,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwnam_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetpwnam_r(stream,
	                    name,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getpwnam_r]]]*/

/*[[[head:libc_getpwent_r,hash:CRC-32=0x905e8471]]]*/
/* >> getpwent_r(3)
 * Read an entry from the password-file stream, opening it if necessary.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `setpwent()' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBCCALL libc_getpwent_r)(struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwent_r]]]*/
{
	errno_t error;
	FILE *stream;
	stream = passwd_opendb();
	if unlikely(!stream)
		return libc_geterrno();
	error = fgetpwent_r(stream,
	                    resultbuf,
	                    buffer,
	                    buflen,
	                    result);
	return error;
}
/*[[[end:libc_getpwent_r]]]*/


/*[[[start:exports,hash:CRC-32=0x2e215a93]]]*/
DEFINE_PUBLIC_ALIAS_P_VOID(_setpwent,libc_setpwent,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(setpwent,libc_setpwent,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(_endpwent,libc_endpwent,,NOTHROW_RPC_NOKOS,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(endpwent,libc_endpwent,,NOTHROW_RPC_NOKOS,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_getpwent,libc_getpwent,,struct passwd *,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getpwent,libc_getpwent,,struct passwd *,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_getpwuid,libc_getpwuid,WUNUSED,struct passwd *,NOTHROW_RPC,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(getpwuid,libc_getpwuid,WUNUSED,struct passwd *,NOTHROW_RPC,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(_getpwnam,libc_getpwnam,WUNUSED ATTR_IN(1),struct passwd *,NOTHROW_RPC,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(getpwnam,libc_getpwnam,WUNUSED ATTR_IN(1),struct passwd *,NOTHROW_RPC,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(_fgetpwent,libc_fgetpwent,WUNUSED ATTR_INOUT(1),struct passwd *,NOTHROW_RPC,LIBCCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(fgetpwent,libc_fgetpwent,WUNUSED ATTR_INOUT(1),struct passwd *,NOTHROW_RPC,LIBCCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(__getpwuid_r,libc_getpwuid_r,ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBCCALL,(uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(uid,resultbuf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getpwuid_r,libc_getpwuid_r,ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBCCALL,(uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(uid,resultbuf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(__getpwnam_r,libc_getpwnam_r,ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBCCALL,(char const *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(name,resultbuf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getpwnam_r,libc_getpwnam_r,ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBCCALL,(char const *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(name,resultbuf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(__getpwent_r,libc_getpwent_r,ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3),errno_t,NOTHROW_RPC,LIBCCALL,(struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(resultbuf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getpwent_r,libc_getpwent_r,ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3),errno_t,NOTHROW_RPC,LIBCCALL,(struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result),(resultbuf,buffer,buflen,result));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PWD_C */
