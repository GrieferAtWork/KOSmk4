/* HASH CRC-32:0x528162de */
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
#ifndef GUARD_LIBC_AUTO_PWD_C
#define GUARD_LIBC_AUTO_PWD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/pwd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/sys.syslog.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/inttypes.h>
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2)) int
(LIBCCALL libc_putpwent)(struct passwd const *__restrict ent,
                         FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SSIZE_T error;
	error = libc_fprintf(stream,
	                "%s:%s:"
	                "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u:"
	                "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u:"
	                "%s:%s:%s\n",
	                ent->pw_name,
	                ent->pw_passwd,
	                ent->pw_uid,
	                ent->pw_gid,
	                ent->pw_gecos,
	                ent->pw_dir,
	                ent->pw_shell);
	return likely(error >= 0) ? 0 : -1;
}
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result) {
	return libc_fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                        result, (uid_t)-1, NULL);
}
#include <libc/errno.h>
/* >> fgetpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 3, 4, 6)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwuid_r)(FILE *__restrict stream,
                                       uid_t uid,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result) {
	errno_t error;
	error = libc_fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, uid, NULL);

	if (error == ENOENT)
		error = 0;

	return error;
}
#include <libc/errno.h>
/* >> fgetpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 4, 6)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwnam_r)(FILE *__restrict stream,
                                       const char *__restrict name,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result) {
	errno_t error;
	error = libc_fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, (uid_t)-1, name);

	if (error == ENOENT)
		error = 0;

	return error;
}
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/syslog.h>
/* >> fgetpwfiltered_r(3)
 * Filtered read from `stream'
 * @param: filtered_uid:  When not equal to `(uid_t)-1', require this UID
 * @param: filtered_name: When not `NULL', require this username
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwfiltered_r)(FILE *__restrict stream,
                                            struct passwd *__restrict resultbuf,
                                            char *__restrict buffer,
                                            size_t buflen,
                                            struct passwd **__restrict result,
                                            uid_t filtered_uid,
                                            char const *filtered_name) {
	errno_t retval = 0;
	char *dbline;
	fpos64_t startpos, curpos;
	fpos64_t maxpos = (fpos64_t)-1;
	if (libc_fgetpos64(stream, &startpos))
		goto err_nodbline;
	curpos = startpos;
again_parseln:
	dbline = libc_fparseln(stream, NULL, NULL, "\0\0#", 0);
	if unlikely(!dbline)
		goto err_restore;
	if (!*dbline) {
		if ((filtered_uid != (uid_t)-1 || filtered_name != NULL) && startpos != 0) {
			maxpos   = startpos;
			startpos = 0;

			libc_rewind(stream);




			/* Search for the requested uid/name prior to the initial search-start position. */
			goto again_parseln;
		}
eof:
		/* End-of-file */

		retval = ENOENT;



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
			iter = libc_strchrnul(iter, ':');
			if unlikely(!*iter) {
				if (i == 3)
					goto got_all_fields; /* This is allowed! */
				goto badline;
			}
			*iter++ = '\0';
		}
		/* Right now, `iter' points at the start of `pw_gecos' or `pw_dir' */
		field_starts[4] = iter; /* pw_gecos */
		iter = libc_strchrnul(iter, ':');
		if unlikely(!*iter)
			goto badline;
		*iter++ = '\0';
		field_starts[5] = iter; /* pw_dir */
		iter = libc_strchrnul(iter, ':');
		if (!*iter) {
			/* pw_gecos wasn't given. */
			field_starts[6] = field_starts[5]; /* pw_shell */
			field_starts[5] = field_starts[4]; /* pw_dir */
			field_starts[4] = (char *)"";      /* pw_gecos */
		} else {
			*iter++ = '\0';
			field_starts[6] = iter; /* pw_shell */
			/* Make sure there aren't any more fields! */
			iter = libc_strchrnul(iter, ':');
			if unlikely(*iter)
				goto badline;
		}
got_all_fields:
		if (filtered_name) {
			if (libc_strcmp(field_starts[0], filtered_name) != 0)
				goto nextline;
		}
		/* All right! we've got all of the fields!
		 * Now to fill in the 2 numeric fields (since those
		 * might  still contain errors that would turn this
		 * entry into a bad line) */
		if unlikely(!*field_starts[2])
			goto badline;
		resultbuf->pw_uid = (gid_t)libc_strtoul(field_starts[2], &iter, 10);
		if unlikely(*iter)
			goto badline;
		if (filtered_uid != (uid_t)-1) {
			if (resultbuf->pw_uid != filtered_uid)
				goto nextline;
		}
		if unlikely(!*field_starts[3])
			goto badline;
		resultbuf->pw_gid = (gid_t)libc_strtoul(field_starts[3], &iter, 10);
		if unlikely(*iter)
			goto badline;
		/* All right! Now to fill in all of the string fields.
		 * We've already turned all of them into NUL-terminated strings  pointing
		 * into the heap-allocated `dbline' string, however the prototype of this
		 * function requires that they be pointing into `buffer...+=buflen' */
		for (i = 0; i < 7; ++i) {
			static uintptr_t const offsets[7] = {
				offsetof(struct passwd, pw_name),
				offsetof(struct passwd, pw_passwd),
				(uintptr_t)-1,
				(uintptr_t)-1,
				offsetof(struct passwd, pw_gecos),
				offsetof(struct passwd, pw_dir),
				offsetof(struct passwd, pw_shell),
			};
			char *str;
			size_t len;
			uintptr_t offset = offsets[i];
			if (offset == (uintptr_t)-1)
				continue;
			str = field_starts[i];
			len = (libc_strlen(str) + 1) * sizeof(char);
			/* Ensure that sufficient space is available in the user-provided buffer. */
			if unlikely(buflen < len)
				goto err_ERANGE;
			/* Set the associated pointer in `resultbuf' */
			*(char **)((byte_t *)resultbuf + offset) = buffer;
			/* Copy the string to the user-provided buffer. */
			buffer = (char *)libc_mempcpy(buffer, str, len);
			buflen -= len;
		}
	}
done_free_dbline:

	libc_free(dbline);

	*result = retval ? NULL : resultbuf;
	return retval;

err_ERANGE:

	(void)libc_seterrno(ERANGE);

	/* FALLTHRU */
err_restore:
	retval = __libc_geterrno_or(1);
	if unlikely(libc_fsetpos64(stream, &curpos))
		goto err;
	goto done_free_dbline;

err_nodbline:
	dbline = NULL;
	/* FALLTHRU */
err:
	retval = __libc_geterrno_or(1);
	goto done_free_dbline;

badline:

	libc_syslog(LOG_ERR, "[passwd] Bad password line %q\n", dbline);

	/* FALLTHRU */
nextline:

	libc_free(dbline);

	if unlikely(libc_fgetpos64(stream, &curpos))
		goto err_nodbline;
	if (curpos >= maxpos)
		goto eof;
	goto again_parseln;
}
#include <bits/types.h>
#include <bits/crt/inttypes.h>
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
INTERN ATTR_SECTION(".text.crt.database.pwd") int
NOTHROW_RPC(LIBCCALL libc_getpw)(uid_t uid,
                                 char *buffer) {
	struct passwd *ent;
	ent = libc_getpwuid(uid);
	if unlikely(!ent)
		goto err;
	libc_sprintf(buffer,
	        "%s:%s:"
	        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u:"
	        "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u:"
	        "%s:%s:%s\n",
	        ent->pw_name,
	        ent->pw_passwd,
	        ent->pw_uid,
	        ent->pw_gid,
	        ent->pw_gecos,
	        ent->pw_dir,
	        ent->pw_shell);
	return 0;
err:
	return -1;
}
/* >> sgetpwent(3)
 * Old libc4/5 function (only here for compat) */
INTERN ATTR_SECTION(".text.crt.compat.linux") struct passwd *
NOTHROW_NCX(LIBCCALL libc_sgetpwent)(char const *line) {
	struct passwd *result = NULL;
	FILE *tempfp;
	tempfp = libc_fmemopen((void *)line, libc_strlen(line) * sizeof(char), "r");
	if likely(tempfp) {
		result = libc_fgetpwent(tempfp);

		libc_fclose(tempfp);

	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(putpwent, libc_putpwent);
DEFINE_PUBLIC_ALIAS(fgetpwent_r, libc_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(fgetpwuid_r, libc_fgetpwuid_r);
DEFINE_PUBLIC_ALIAS(fgetpwnam_r, libc_fgetpwnam_r);
DEFINE_PUBLIC_ALIAS(getpw, libc_getpw);
DEFINE_PUBLIC_ALIAS(_sgetpwent, libc_sgetpwent);
DEFINE_PUBLIC_ALIAS(sgetpwent, libc_sgetpwent);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PWD_C */
