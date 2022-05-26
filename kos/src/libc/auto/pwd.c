/* HASH CRC-32:0x9a11b736 */
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
#include "string.h"
#include "../user/sys.syslog.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_PURE WUNUSED ATTR_IN_OPT(1) bool
NOTHROW_NCX(LIBCCALL libc_nss_checkfield)(char const *field) {
	if (!field)
		return true;
	/* Since  ':'  and  '\n'  are  used  as field
	 * delimiters, they can't appear _in_ fields! */
	if (libc_strpbrk(field, ":\n"))
		return false;
	return true;
}
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_PURE WUNUSED ATTR_IN_OPT(1) bool
NOTHROW_NCX(LIBCCALL libc_nss_checkfieldlist)(char *const *list) {
	if (!list)
		return true;
	for (; *list; ++list) {
		char const *item = *list;
		if (libc_strpbrk(item, ":,\n"))
			return false;
	}
	return true;
}
#include <bits/crt/inttypes.h>
#include <libc/errno.h>
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_IN(1) ATTR_INOUT(2) int
(LIBCCALL libc_putpwent)(struct passwd const *__restrict ent,
                         FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SSIZE_T error;
#if __SIZEOF_GID_T__ == 1
	char gidbuf[COMPILER_LENOF("255")];
#elif __SIZEOF_GID_T__ == 2
	char gidbuf[COMPILER_LENOF("65535")];
#elif __SIZEOF_GID_T__ == 4
	char gidbuf[COMPILER_LENOF("4294967295")];
#else /* ... */
	char gidbuf[COMPILER_LENOF("18446744073709551615")];
#endif /* !... */
#if __SIZEOF_UID_T__ == 1
	char uidbuf[COMPILER_LENOF("255")];
#elif __SIZEOF_UID_T__ == 2
	char uidbuf[COMPILER_LENOF("65535")];
#elif __SIZEOF_UID_T__ == 4
	char uidbuf[COMPILER_LENOF("4294967295")];
#else /* ... */
	char uidbuf[COMPILER_LENOF("18446744073709551615")];
#endif /* !... */

	/* Validate arguments. */
	if unlikely(!ent)
		goto err_inval;
	if unlikely(!stream)
		goto err_inval;
	if unlikely(!ent->pw_name)
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->pw_name))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->pw_passwd))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->pw_dir))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->pw_shell))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->pw_gecos)) /* TODO: Replace invalid characters with ' ' */
		goto err_inval;

	/* Generate the UID+GID strings. */
	libc_sprintf(uidbuf, "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u", ent->pw_uid);
	libc_sprintf(gidbuf, "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u", ent->pw_gid);
	if (ent->pw_name[0] == '+' || ent->pw_name[0] == '-') {
		uidbuf[0] = '\0';
		gidbuf[0] = '\0';
	}

	/* Generate the entry. */

	libc_flockfile(stream);

	error = libc_fprintf_unlocked(stream,
	                         "%s:%s:%s:%s:%s:%s:%s\n",
	                         ent->pw_name,
	                         ent->pw_passwd ? ent->pw_passwd : "",
	                         uidbuf,
	                         gidbuf,
	                         ent->pw_gecos ? ent->pw_gecos : "",
	                         ent->pw_dir ? ent->pw_dir : "",
	                         ent->pw_shell ? ent->pw_shell : "");

	libc_funlockfile(stream);


	return likely(error >= 0) ? 0 : -1;
err_inval:

	return libc_seterrno(EINVAL);



}
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
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
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t
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
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_IN(2) ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwnam_r)(FILE *__restrict stream,
                                       char const *__restrict name,
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
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
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
		if (!libc_feof(stream))
			goto nextline; /* Skip empty lines! */
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
		if unlikely(!*field_starts[2]) {
			resultbuf->pw_uid = (uid_t)-1;
		} else {
			resultbuf->pw_uid = (uid_t)libc_strtoul(field_starts[2], &iter, 10);
			if unlikely(*iter)
				goto badline;
			if (filtered_uid != (uid_t)-1) {
				if (resultbuf->pw_uid != filtered_uid)
					goto nextline;
			}
		}
		if unlikely(!*field_starts[3]) {
			resultbuf->pw_gid = (gid_t)-1;
		} else {
			resultbuf->pw_gid = (gid_t)libc_strtoul(field_starts[3], &iter, 10);
			if unlikely(*iter)
				goto badline;
		}
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

	libc_syslog(LOG_ERR, "[passwd] Bad db line: %q\n", dbline);

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
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_OUT(2) int
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
INTERN ATTR_SECTION(".text.crt.compat.linux") ATTR_IN(1) struct passwd *
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
INTERN ATTR_SECTION(".text.crt.database.pwd") int
NOTHROW_NCX(LIBCCALL libc_setpassent)(int keep_open) {
	(void)keep_open;
	libc_setpwent();
	return 0;
}
#include <bits/types.h>
#include <bits/crt/db/passwd.h>
INTERN ATTR_SECTION(".text.crt.database.pwd") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_uid_from_user)(char const *name,
                                         uid_t *p_uid) {
	struct passwd *ent = libc_getpwnam(name);
	if (ent) {
		*p_uid = ent->pw_uid;
		return 0;
	}
	return -1;
}
#include <bits/types.h>
#include <bits/crt/db/passwd.h>
#include <bits/crt/inttypes.h>
INTERN ATTR_SECTION(".text.crt.database.pwd") WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_user_from_uid)(uid_t uid,
                                         int nouser) {
	struct passwd *ent = libc_getpwuid(uid);
	if (ent)
		return ent->pw_name;
	if (nouser == 0) {
#if __SIZEOF_UID_T__ == 1
		static char fallback_strbuf[__COMPILER_LENOF("-128")];
#elif __SIZEOF_UID_T__ == 2
		static char fallback_strbuf[__COMPILER_LENOF("-32768")];
#elif __SIZEOF_UID_T__ == 4
		static char fallback_strbuf[__COMPILER_LENOF("-2147483648")];
#else /* ... */
		static char fallback_strbuf[__COMPILER_LENOF("-9223372036854775808")];
#endif /* !... */
		libc_sprintf(fallback_strbuf, "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d", uid);
		return fallback_strbuf;
	}
	return NULL;
}
#include <bits/crt/db/passwd.h>
INTERN ATTR_SECTION(".text.crt.database.pwd") WUNUSED ATTR_IN(1) struct passwd *
NOTHROW_NCX(LIBCCALL libc_pw_dup)(struct passwd const *ent) {
	static uint8_t const strfield_offsets[] = {
		offsetof(struct passwd, pw_name),
		offsetof(struct passwd, pw_passwd),
		offsetof(struct passwd, pw_gecos),
		offsetof(struct passwd, pw_dir),
		offsetof(struct passwd, pw_shell),
	};
	struct passwd *result;
	unsigned int i;
	size_t reslen = sizeof(struct passwd);
	for (i = 0; i < COMPILER_LENOF(strfield_offsets); ++i) {
		char const *str = *(char const *const *)((byte_t const *)ent + strfield_offsets[i]);
		if (str != NULL) /* Should never be NULL, but programs may not respect that... */
			reslen += libc_strlen(str) * sizeof(char);
		reslen += sizeof(char);
	}
	/* Allocate the duplicate */
	result = (struct passwd *)libc_malloc(reslen);
	if (result) {
		char *p;
		result = (struct passwd *)libc_memcpy(result, ent, sizeof(struct passwd));
		/* Copy strings. */
		p = (char *)result + 1;
		for (i = 0; i < COMPILER_LENOF(strfield_offsets); ++i) {
			char const *str = *(char const *const *)((byte_t const *)ent + strfield_offsets[i]);
			*(char **)((byte_t *)result + strfield_offsets[i]) = p;
			if (str != NULL) /* Should never be NULL, but programs may not respect that... */
				p = (char *)libc_mempcpyc(p, str, libc_strlen(str), sizeof(char));
			*p++ = '\0';
		}
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
DEFINE_PUBLIC_ALIAS(setpassent, libc_setpassent);
DEFINE_PUBLIC_ALIAS(uid_from_user, libc_uid_from_user);
DEFINE_PUBLIC_ALIAS(user_from_uid, libc_user_from_uid);
DEFINE_PUBLIC_ALIAS(pw_dup, libc_pw_dup);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PWD_C */
