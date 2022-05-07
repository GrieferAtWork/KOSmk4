/* HASH CRC-32:0x1bf48a2 */
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
#ifndef GUARD_LIBC_AUTO_GRP_C
#define GUARD_LIBC_AUTO_GRP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/grp.h"
#include "../user/pwd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.syslog.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
#include <bits/types.h>
#include <bits/crt/inttypes.h>
/* >> putgrent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.grp") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_putgrent)(struct group const *__restrict entry,
                                    FILE *__restrict stream) {
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

	/* Validate arguments. */
	if unlikely(!entry)
		goto err_inval;
	if unlikely(!stream)
		goto err_inval;
	if unlikely(!entry->gr_name)
		goto err_inval;
	if unlikely(!libc_nss_checkfield(entry->gr_name))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(entry->gr_passwd))
		goto err_inval;
	if unlikely(!libc_nss_checkfieldlist(entry->gr_mem))
		goto err_inval;

	/* Generate the GID string. */
	libc_sprintf(gidbuf, "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u", entry->gr_gid);
	if (entry->gr_name[0] == '+' || entry->gr_name[0] == '-')
		gidbuf[0] = '\0';

	/* Generate the entry. */

	libc_flockfile(stream);

	error = libc_fprintf_unlocked(stream, "%s:%s:%s:",
	                         entry->gr_name,
	                         entry->gr_passwd ? entry->gr_passwd : "",
	                         gidbuf);
	if likely(error >= 0) {
		/* Print the member list (if it is present) */
		char *const *list = entry->gr_mem;
		if (list) {
			bool isfirst = true;
			for (; *list; ++list) {
				error = libc_fprintf_unlocked(stream,
				                         isfirst ? "%s" : ",%s",
				                         *list);
				if unlikely(error < 0)
					break;
				isfirst = false;
			}
		}
		if likely(error >= 0)
			error = libc_fputc_unlocked('\n', stream);
	}

	libc_funlockfile(stream);


	return likely(error >= 0) ? 0 : -1;
err_inval:

	return libc_seterrno(EINVAL);



}
/* >> fgetgrent(3), fgetgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.grp") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_fgetgrent_r)(FILE *__restrict stream,
                                       struct group *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct group **__restrict result) {
	return libc_fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                        result, (gid_t)-1, NULL);
}
#include <libc/errno.h>
/* >> fgetgrgid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `gid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.grp") NONNULL((1, 3, 4, 6)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetgrgid_r)(FILE *__restrict stream,
                                       gid_t gid,
                                       struct group *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct group **__restrict result) {
	errno_t error;
	error = libc_fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, gid, NULL);

	if (error == ENOENT)
		error = 0;

	return error;
}
#include <libc/errno.h>
/* >> fgetgrnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.grp") NONNULL((1, 2, 3, 4, 6)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetgrnam_r)(FILE *__restrict stream,
                                       const char *__restrict name,
                                       struct group *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct group **__restrict result) {
	errno_t error;
	error = libc_fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, (gid_t)-1, name);

	if (error == ENOENT)
		error = 0;

	return error;
}
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/syslog.h>
/* >> fgetgrfiltered_r(3)
 * Filtered read from `stream'
 * @param: filtered_gid:  When not equal to `(gid_t)-1', require this GID
 * @param: filtered_name: When not `NULL', require this username
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.grp") NONNULL((1, 2, 3, 5)) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetgrfiltered_r)(FILE *__restrict stream,
                                            struct group *__restrict resultbuf,
                                            char *__restrict buffer,
                                            size_t buflen,
                                            struct group **__restrict result,
                                            gid_t filtered_gid,
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
		if ((filtered_gid != (gid_t)-1 || filtered_name != NULL) && startpos != 0) {
			maxpos   = startpos;
			startpos = 0;

			libc_rewind(stream);




			/* Search for the requested gid/name prior to the initial search-start position. */
			goto again_parseln;
		}
eof:
		/* End-of-file */

		retval = ENOENT;



		goto done_free_dbline;
	}
	/* Accepted formats:
	 *     gr_name:gr_passwd:gr_gid
	 *     gr_name:gr_passwd:gr_gid:gr_mem[0],gr_mem[1],...
	 */
	{
		char *field_starts[4];
		char *iter = dbline;
		unsigned int i;
		for (i = 0; i < 2; ++i) {
			field_starts[i] = iter;
			iter = libc_strchrnul(iter, ':');
			if unlikely(!*iter)
				goto badline;
			*iter++ = '\0';
		}
		if (filtered_name) {
			if (libc_strcmp(field_starts[0], filtered_name) != 0)
				goto nextline;
		}
		field_starts[2] = iter;
		field_starts[3] = NULL;
		iter = libc_strchrnul(iter, ':');
		if likely(*iter) {
			*iter++ = '\0';
			/* Right now, `iter' points at the start of `gr_mem[0]' */
			field_starts[3] = iter; /* gr_mem[0] */
			if unlikely(*libc_strchrnul(iter, ':'))
				goto badline; /* There shouldn't be another ':' */
		}

		/* All right! we've got all of the fields!
		 * Now to fill in the 1 numeric field (since it
		 * might still contain errors that would turn this
		 * entry into a bad line) */
		if unlikely(!*field_starts[2]) {
			resultbuf->gr_gid = (gid_t)-1;
		} else {
			resultbuf->gr_gid = (gid_t)libc_strtoul(field_starts[2], &iter, 10);
			if unlikely(*iter)
				goto badline;
			if (filtered_gid != (gid_t)-1) {
				if (resultbuf->gr_gid != filtered_gid)
					goto nextline;
			}
		}

		/* All right! Now to fill in all of the string fields.
		 * We've already turned all of them into NUL-terminated strings  pointing
		 * into the heap-allocated `dbline' string, however the prototype of this
		 * function requires that they be pointing into `buffer...+=buflen' */
		for (i = 0; i < 2; ++i) {
			static uintptr_t const offsets[2] = {
				offsetof(struct group, gr_name),
				offsetof(struct group, gr_passwd),
			};
			char *str;
			size_t len;
			uintptr_t offset = offsets[i];
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

		/* Finally, and the most complicated of all, we have to split the group-member-list. */
		{
			char *aligned = (char *)(((uintptr_t)buffer + sizeof(void *) - 1) & ~(sizeof(void *) - 1));
			/* Align to whole pointers. */
			size_t padsiz = (size_t)(aligned - buffer);
			if (padsiz > buflen)
				goto err_ERANGE;
			buffer = aligned;
			buflen -= padsiz;
		}
		/* Figure out how many members there are */
		{
			size_t reqspace, member_count = 0;
			iter = field_starts[3];
			if (iter) {
				for (;;) {
					++member_count;
					iter = libc_strchr(iter, ',');
					if (!iter)
						break;
					++iter;
				}
			}
			resultbuf->gr_mem = (char **)buffer;
			reqspace = (member_count + 1) * sizeof(char *);
			if (buflen < reqspace)
				goto err_ERANGE;
			buflen -= reqspace;
			buffer += reqspace;
		}
		/* Assign member names. */
		{
			char **dst = resultbuf->gr_mem;
			char *iter = field_starts[3];
			if (iter) {
				for (;;) {
					size_t siz;
					siz = (libc_stroff(iter, ',') + 1) * sizeof(char);
					if (buflen < siz)
						goto err_ERANGE;
					/* Copy to user-provided buffer. */
					*(char *)libc_mempcpy(buffer, iter, siz) = '\0';
					*dst++ = buffer;
					buflen -= siz;
					buffer += siz;
					iter += siz;
					if (!*iter)
						break;
					++iter; /* Skip ',' */
				}
			}
			*dst = NULL; /* Sentinel / terminator */
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

	libc_syslog(LOG_ERR, "[group] Bad db line: %q\n", dbline);

	/* FALLTHRU */
nextline:

	libc_free(dbline);

	if unlikely(libc_fgetpos64(stream, &curpos))
		goto err_nodbline;
	if (curpos >= maxpos)
		goto eof;
	goto again_parseln;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(putgrent, libc_putgrent);
DEFINE_PUBLIC_ALIAS(fgetgrent_r, libc_fgetgrent_r);
DEFINE_PUBLIC_ALIAS(fgetgrgid_r, libc_fgetgrgid_r);
DEFINE_PUBLIC_ALIAS(fgetgrnam_r, libc_fgetgrnam_r);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_GRP_C */
