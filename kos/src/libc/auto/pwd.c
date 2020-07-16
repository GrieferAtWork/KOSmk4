/* HASH CRC-32:0x50323a45 */
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
/* Read an entry from STREAM. This function is not standardized and probably never will */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result) {
	return libc_fgetpwfiltered_r(stream, resultbuf, buffer, buflen,
	                        result, (uid_t)-1, NULL);
}
#include <parts/errno.h>
#include <hybrid/typecore.h>
#include <asm/syslog.h>
/* Filtered read from `stream'
 * @param: filtered_uid:  When not equal to `(uid_t)-1', require this UID
 * @param: filtered_name: When not `NULL', require this username */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetpwfiltered_r)(FILE *__restrict stream,
                                            struct passwd *__restrict resultbuf,
                                            char *__restrict buffer,
                                            size_t buflen,
                                            struct passwd **__restrict result,
                                            uid_t filtered_uid,
                                            char const *filtered_name) {
	int retval = 0;
	char *dbline;
	fpos64_t oldpos;
	if (libc_fgetpos64_unlocked(stream, &oldpos))
		goto err;
again_parseln:
	dbline = libc_fparseln(stream, NULL, NULL, "\0\0#", 0);
	if unlikely(!dbline)
		goto err_restore;
	if (!*dbline) {
		/* End-of-file */
#ifdef ENOENT
		retval = ENOENT;
#else /* ENOENT */
		retval = 1;
#endif /* !ENOENT */
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
		 * might still contain errors that would turn this
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
		 * We've already turned all of them into NUL-terminated strings pointing
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(dbline);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
done:
	*result = retval ? NULL : resultbuf;
	return retval;
err_ERANGE:
#ifdef ERANGE
	__libc_seterrno(ERANGE);
#endif /* ERANGE */
err_restore:
	retval = __libc_geterrno_or(1);
	libc_fsetpos64_unlocked(stream, &oldpos);
	goto done;
err:
	retval = __libc_geterrno_or(1);
	goto done;
badline:
#if defined(LOG_ERR) && (defined(__CRT_HAVE_syslog) || defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer))
	libc_syslog(LOG_ERR, "[passwd] Bad password line %q\n", dbline);
#endif /* LOG_ERR && (__CRT_HAVE_syslog || __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer) */
nextline:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(dbline);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	goto again_parseln;
}
#include <bits/types.h>
#include <bits/crt/inttypes.h>
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
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
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fgetpwent_r, libc_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(getpw, libc_getpw);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PWD_C */
