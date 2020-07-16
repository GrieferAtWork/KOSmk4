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

%[define_replacement(uid_t = __uid_t)]
%[default:section(".text.crt{|.dos}.database.pwd")]

%{
#include <features.h>
#include <bits/types.h>
#include <bits/crt/db/passwd.h>

/* Documentation taken from Glibc /usr/include/pwd.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

#if defined(__USE_POSIX) && defined(__USE_MISC)
/* Reasonable value for the buffer sized used in the
 * reentrant functions below. But better use `sysconf'. */
#define NSS_BUFLEN_PASSWD  1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

}

%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@Rewind the password-file stream
[[cp]]
void setpwent();

@@Close the password-file stream
[[cp_nokos]]
void endpwent();

@@Read an entry from the password-file stream, opening it if necessary
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwent();
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */


@@Search for an entry with a matching user ID
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
struct passwd *getpwuid($uid_t uid);

@@Search for an entry with a matching username
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwnam([[nonnull]] const char *name);

%
%#ifdef __USE_MISC
@@Read an entry from STREAM
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *fgetpwent([[nonnull]] $FILE *__restrict stream);

@@Write the given entry onto the given stream
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
int putpwent([[nonnull]] struct passwd const *__restrict p,
             [[nonnull]] $FILE *__restrict f);
%#endif /* __USE_MISC */

%
%#ifdef __USE_POSIX
[[cp, doc_alias("getpwuid"), decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
int getpwuid_r(__uid_t __uid,
               [[nonnull]] struct passwd *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct passwd **__restrict result);

[[cp, doc_alias("getpwnam"), decl_include("<bits/crt/db/passwd.h>")]]
int getpwnam_r([[nonnull]] const char *__restrict name,
               [[nonnull]] struct passwd *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct passwd **__restrict result);

%#ifdef __USE_MISC
[[cp, doc_alias("getpwent")]]
[[decl_include("<bits/types.h>", "<bits/crt/db/passwd.h>")]]
$errno_t getpwent_r([[nonnull]] struct passwd *__restrict resultbuf,
                    [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                    [[nonnull]] struct passwd **__restrict result);

@@Read an entry from STREAM. This function is not standardized and probably never will
[[cp, decl_include("<bits/types.h>", "<bits/crt/db/passwd.h>")]]
[[impl_include("<parts/errno.h>", "<hybrid/typecore.h>", "<asm/syslog.h>")]]
[[requires_function(fgetpos64_unlocked, fsetpos64_unlocked, fparseln)]]
$errno_t fgetpwent_r([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] struct passwd *__restrict resultbuf,
                     [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                     [[nonnull]] struct passwd **__restrict result) {
	int retval = 0;
	char *dbline;
	fpos64_t oldpos;
	if (fgetpos64_unlocked(stream, &oldpos))
		goto err;
again_parseln:
	dbline = fparseln(stream, NULL, NULL, "\0\0#", 0);
	if unlikely(!dbline)
		goto err_restore;
	if (!*dbline) {
		/* End-of-file */
@@pp_ifdef ENOENT@@
		retval = ENOENT;
@@pp_else@@
		retval = 1;
@@pp_endif@@
		goto done_free_dbline;
	}
	/* Accepted formats:
	 *     pw_name:pw_passwd:pw_uid:pw_gid:pw_gecos:pw_dir:pw_shell
	 *     pw_name:pw_passwd:pw_uid:pw_gid:pw_dir:pw_shell
	 *     pw_name:pw_passwd:pw_uid:pw_gid */
	{
		char *field_starts[7];
		char *iter = dbline;
		unsigned int i;
		field_starts[4] =             /* pw_gecos */
		field_starts[5] =             /* pw_dir */
		field_starts[6] = (char *)""; /* pw_shell */
		for (i = 0; i < 4; ++i) {
			field_starts[i] = iter;
			iter = strchrnul(iter, ':');
			if unlikely(!*iter) {
				if (i == 3)
					goto got_all_fields; /* This is allowed! */
				goto badline;
			}
			*iter++ = '\0';
		}
		/* Right now, `iter' points at the start of `pw_gecos' or `pw_dir' */
		field_starts[4] = iter; /* pw_gecos */
		iter = strchrnul(iter, ':');
		if unlikely(!*iter)
			goto badline;
		*iter++ = '\0';
		field_starts[5] = iter; /* pw_dir */
		iter = strchrnul(iter, ':');
		if (!*iter) {
			/* pw_gecos wasn't given. */
			field_starts[6] = field_starts[5]; /* pw_shell */
			field_starts[5] = field_starts[4]; /* pw_dir */
			field_starts[4] = (char *)"";      /* pw_gecos */
		} else {
			*iter++ = '\0';
			field_starts[6] = iter; /* pw_shell */
			/* Make sure there aren't any more fields! */
			iter = strchrnul(iter, ':');
			if unlikely(*iter)
				goto badline;
		}
got_all_fields:
		/* All right! we've got all of the fields!
		 * Now to fill in the 2 numeric fields (since those
		 * might still contain errors that would turn this
		 * entry into a bad line) */
		if unlikely(!*field_starts[2] || !*field_starts[3])
			goto badline;
		resultbuf->@pw_gid@ = (gid_t)strtoul(field_starts[2], &iter, 10);
		if unlikely(*iter)
			goto badline;
		resultbuf->@pw_uid@ = (gid_t)strtoul(field_starts[3], &iter, 10);
		if unlikely(*iter)
			goto badline;
		/* All right! Now to fill in all of the string fields.
		 * We've already turned all of them into NUL-terminated strings pointing
		 * into the heap-allocated `dbline' string, however the prototype of this
		 * function requires that they be pointing into `buffer...+=buflen' */
		for (i = 0; i < 7; ++i) {
			static uintptr_t const offsets[7] = {
				offsetof(struct passwd, @pw_name@),
				offsetof(struct passwd, @pw_passwd@),
				(uintptr_t)-1,
				(uintptr_t)-1,
				offsetof(struct passwd, @pw_gecos@),
				offsetof(struct passwd, @pw_dir@),
				offsetof(struct passwd, @pw_shell@),
			};
			char *str;
			size_t len;
			uintptr_t offset = offsets[i];
			if (offset == (uintptr_t)-1)
				continue;
			str = field_starts[i];
			len = (strlen(str) + 1) * sizeof(char);
			/* Ensure that sufficient space is available in the user-provided buffer. */
			if unlikely(buflen < len)
				goto err_ERANGE;
			/* Set the associated pointer in `resultbuf' */
			*(char **)((byte_t *)resultbuf + offset) = buffer;
			/* Copy the string to the user-provided buffer. */
			buffer = (char *)mempcpy(buffer, str, len);
			buflen -= len;
		}
	}
done_free_dbline:
@@pp_if $has_function(free)@@
	free(dbline);
@@pp_endif@@
done:
	*result = retval ? NULL : resultbuf;
	return retval;
err_ERANGE:
@@pp_ifdef ERANGE@@
	__libc_seterrno(ERANGE);
@@pp_endif@@
err_restore:
	retval = __libc_geterrno_or(1);
	fsetpos64_unlocked(stream, &oldpos);
	goto done;
err:
	retval = __libc_geterrno_or(1);
	goto done;
badline:
@@pp_if defined(LOG_ERR) && $has_function(syslog)@@
	syslog(LOG_ERR, "[passwd] Bad password line %q\n", dbline);
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(dbline);
@@pp_endif@@
	goto again_parseln;
}

%#endif /* __USE_MISC */
%#endif	/* __USE_POSIX */

%#ifdef __USE_GNU
@@Re-construct the password-file line for the given uid in the
@@given buffer. This knows the format that the caller will
@@expect, but this need not be the format of the password file
[[cp, decl_include("<bits/types.h>")]]
int getpw(__uid_t uid, char *buffer);
%#endif /* __USE_GNU */


%{
#endif /* __CC__ */

__SYSDECL_END

}