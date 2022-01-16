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
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/pwd.h) */
/* (#) Portability: DJGPP         (/include/pwd.h) */
/* (#) Portability: FreeBSD       (/include/pwd.h) */
/* (#) Portability: GNU C Library (/pwd/pwd.h) */
/* (#) Portability: NetBSD        (/include/pwd.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/pwd.h) */
/* (#) Portability: OpenBSD       (/include/pwd.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/pwd.h) */
/* (#) Portability: diet libc     (/include/pwd.h) */
/* (#) Portability: libbsd        (/include/bsd/pwd.h) */
/* (#) Portability: libc4/5       (/include/pwd.h) */
/* (#) Portability: libc6         (/include/pwd.h) */
/* (#) Portability: musl libc     (/include/pwd.h) */
/* (#) Portability: uClibc        (/include/pwd.h) */
}

%[define_replacement(uid_t = __uid_t)]
%[default:section(".text.crt{|.dos}.database.pwd")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/db/passwd.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

__SYSDECL_BEGIN

#if defined(__USE_POSIX) && defined(__USE_MISC)
/* Ignore this value. It's  just some nonsensical constant  here
 * for  historic  purposes and  posix compliance.  All functions
 * found in this header are able to operate on arbitrarily-sized
 * user password database entries,  and so should your  program,
 * meaning this value is entirely pointless and should  actually
 * be considered as INFINITE.
 * Also: there's a `_SC_GETPW_R_SIZE_MAX' which also just returns
 *       this value, so it's just as useless. */
#define NSS_BUFLEN_PASSWD 1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
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
@@return: * :                         A pointer to the read password entry
@@return: NULL: (errno = <unchanged>) The last  entry  has  already  been  read
@@                                    (use `setpwent()' to rewind the database)
@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwent();
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */


@@Search for an entry with a matching user ID
@@return: * :                         A pointer to the read password entry
@@return: NULL: (errno = <unchanged>) No entry for `uid' exists
@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
struct passwd *getpwuid($uid_t uid);

@@Search for an entry with a matching username
@@return: * :                         A pointer to the read password entry
@@return: NULL: (errno = <unchanged>) No entry for `name' exists
@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwnam([[nonnull]] const char *name);

%
%#ifdef __USE_MISC
@@Read an entry from `stream'
@@return: * :                         A pointer to the read password entry
@@return: NULL: (errno = <unchanged>) The last entry has already been read
@@                                    (use `rewind(stream)' to rewind the database)
@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *fgetpwent([[nonnull]] $FILE *__restrict stream);

@@>> putpwent(3)
@@Write the given entry `ent' into the given `stream'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[cp_stdio, decl_include("<bits/crt/db/passwd.h>")]]
[[requires_function(fprintf), impl_include("<bits/crt/inttypes.h>")]]
int putpwent([[nonnull]] struct passwd const *__restrict ent,
             [[nonnull]] $FILE *__restrict stream) {
	__STDC_INT_AS_SSIZE_T error;
	error = fprintf(stream,
	                "%s:%s:"
	                "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u:"
	                "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u:"
	                "%s:%s:%s\n",
	                ent->@pw_name@,
	                ent->@pw_passwd@,
	                ent->@pw_uid@,
	                ent->@pw_gid@,
	                ent->@pw_gecos@,
	                ent->@pw_dir@,
	                ent->@pw_shell@);
	return likely(error >= 0) ? 0 : -1;
}
%#endif /* __USE_MISC */

%
%#ifdef __USE_POSIX
@@Search for an entry with a matching user ID
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `uid'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
$errno_t getpwuid_r($uid_t uid,
                    [[nonnull]] struct passwd *__restrict resultbuf,
                    [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                    [[nonnull]] struct passwd **__restrict result);

@@Search for an entry with a matching username
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `name'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
$errno_t getpwnam_r([[nonnull]] const char *__restrict name,
                    [[nonnull]] struct passwd *__restrict resultbuf,
                    [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                    [[nonnull]] struct passwd **__restrict result);

%#ifdef __USE_MISC
@@Read an entry from the password-file stream, opening it if necessary.
@@@return: 0 :     Success (`*result' is made to point at `resultbuf')
@@@return: ENOENT: The last entry has already been read (use `setpwent()' to rewind the database)
@@@return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
@@@return: * :     Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/types.h>", "<bits/crt/db/passwd.h>")]]
$errno_t getpwent_r([[nonnull]] struct passwd *__restrict resultbuf,
                    [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                    [[nonnull]] struct passwd **__restrict result);

@@Read an entry from `stream'. This function is not standardized and probably never will be.
@@@return: 0 :     Success (`*result' is made to point at `resultbuf')
@@@return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
@@@return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
@@@return: * :     Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/types.h>", "<bits/crt/db/passwd.h>")]]
[[requires_function(fgetpwfiltered_r)]]
$errno_t fgetpwent_r([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] struct passwd *__restrict resultbuf,
                     [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                     [[nonnull]] struct passwd **__restrict result) {
	return fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                        result, (uid_t)-1, NULL);
}

%#ifdef __USE_KOS
@@Search for an entry with a matching user ID
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `uid'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
[[requires_function(fgetpwfiltered_r), impl_include("<libc/errno.h>")]]
$errno_t fgetpwuid_r([[nonnull]] $FILE *__restrict stream, $uid_t uid,
                     [[nonnull]] struct passwd *__restrict resultbuf,
                     [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                     [[nonnull]] struct passwd **__restrict result) {
	$errno_t error;
	error = fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, uid, NULL);
@@pp_ifdef ENOENT@@
	if (error == ENOENT)
		error = 0;
@@pp_endif@@
	return error;
}

@@Search for an entry with a matching username
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `name'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
[[requires_function(fgetpwfiltered_r), impl_include("<libc/errno.h>")]]
$errno_t fgetpwnam_r([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] const char *__restrict name,
                     [[nonnull]] struct passwd *__restrict resultbuf,
                     [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                     [[nonnull]] struct passwd **__restrict result) {
	$errno_t error;
	error = fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, (uid_t)-1, name);
@@pp_ifdef ENOENT@@
	if (error == ENOENT)
		error = 0;
@@pp_endif@@
	return error;
}
%#endif /* __USE_KOS */

@@Filtered read from `stream'
@@@param: filtered_uid:  When not equal to `(uid_t)-1', require this UID
@@@param: filtered_name: When not `NULL', require this username
@@@return: 0 :     Success (`*result' is made to point at `resultbuf')
@@@return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
@@                 Note that in this case, `errno' will have not been changed
@@@return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
@@                 Note that in this case, `errno' will have also been set to `ERANGE'
@@@return: * :     Error (one of `E*' from `<errno.h>')
[[static, cp, decl_include("<bits/types.h>", "<bits/crt/db/passwd.h>")]]
[[impl_include("<libc/errno.h>", "<hybrid/typecore.h>", "<asm/os/syslog.h>")]]
[[requires_function(fgetpos64, fsetpos64, fparseln)]]
$errno_t fgetpwfiltered_r([[nonnull]] $FILE *__restrict stream,
                          [[nonnull]] struct passwd *__restrict resultbuf,
                          [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                          [[nonnull]] struct passwd **__restrict result,
                          $uid_t filtered_uid, char const *filtered_name) {
	$errno_t retval = 0;
	char *dbline;
	fpos64_t startpos, curpos;
	fpos64_t maxpos = (fpos64_t)-1;
	if (fgetpos64(stream, &startpos))
		goto err_nodbline;
	curpos = startpos;
again_parseln:
	dbline = fparseln(stream, NULL, NULL, "\0\0#", 0);
	if unlikely(!dbline)
		goto err_restore;
	if (!*dbline) {
		if ((filtered_uid != (uid_t)-1 || filtered_name != NULL) && startpos != 0) {
			maxpos   = startpos;
			startpos = 0;
@@pp_if $has_function(rewind)@@
			rewind(stream);
@@pp_else@@
			if (fsetpos64(stream, &startpos))
				goto err;
@@pp_endif@@
			/* Search for the requested uid/name prior to the initial search-start position. */
			goto again_parseln;
		}
eof:
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
		if (filtered_name) {
			if (strcmp(field_starts[0], filtered_name) != 0)
				goto nextline;
		}
		/* All right! we've got all of the fields!
		 * Now to fill in the 2 numeric fields (since those
		 * might  still contain errors that would turn this
		 * entry into a bad line) */
		if unlikely(!*field_starts[2])
			goto badline;
		resultbuf->@pw_uid@ = (gid_t)strtoul(field_starts[2], &iter, 10);
		if unlikely(*iter)
			goto badline;
		if (filtered_uid != (uid_t)-1) {
			if (resultbuf->@pw_uid@ != filtered_uid)
				goto nextline;
		}
		if unlikely(!*field_starts[3])
			goto badline;
		resultbuf->@pw_gid@ = (gid_t)strtoul(field_starts[3], &iter, 10);
		if unlikely(*iter)
			goto badline;
		/* All right! Now to fill in all of the string fields.
		 * We've already turned all of them into NUL-terminated strings  pointing
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
	*result = retval ? NULL : resultbuf;
	return retval;

err_ERANGE:
@@pp_ifdef ERANGE@@
	(void)__libc_seterrno(ERANGE);
@@pp_endif@@
	/* FALLTHRU */
err_restore:
	retval = __libc_geterrno_or(1);
	if unlikely(fsetpos64(stream, &curpos))
		goto err;
	goto done_free_dbline;

err_nodbline:
	dbline = NULL;
	/* FALLTHRU */
err:
	retval = __libc_geterrno_or(1);
	goto done_free_dbline;

badline:
@@pp_if defined(LOG_ERR) && $has_function(syslog)@@
	syslog(LOG_ERR, "[passwd] Bad password line %q\n", dbline);
@@pp_endif@@
	/* FALLTHRU */
nextline:
@@pp_if $has_function(free)@@
	free(dbline);
@@pp_endif@@
	if unlikely(fgetpos64(stream, &curpos))
		goto err_nodbline;
	if (curpos >= maxpos)
		goto eof;
	goto again_parseln;
}

%#endif /* __USE_MISC */
%#endif	/* __USE_POSIX */

%#ifdef __USE_GNU
@@Re-construct the password-file line for the given uid in the
@@given  buffer. This  knows the  format that  the caller will
@@expect, but this need not be the format of the password file
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<bits/types.h>", "<bits/crt/inttypes.h>")]]
[[requires_function(getpwuid)]]
int getpw($uid_t uid, char *buffer) {
	struct passwd *ent;
	ent = getpwuid(uid);
	if unlikely(!ent)
		goto err;
	sprintf(buffer,
	        "%s:%s:"
	        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u:"
	        "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u:"
	        "%s:%s:%s\n",
	        ent->@pw_name@,
	        ent->@pw_passwd@,
	        ent->@pw_uid@,
	        ent->@pw_gid@,
	        ent->@pw_gecos@,
	        ent->@pw_dir@,
	        ent->@pw_shell@);
	return 0;
err:
	return -1;
}
%#endif /* __USE_GNU */


%{
#endif /* __CC__ */

__SYSDECL_END

}
