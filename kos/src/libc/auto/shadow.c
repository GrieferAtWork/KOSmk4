/* HASH CRC-32:0x65343dc1 */
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
#ifndef GUARD_LIBC_AUTO_SHADOW_C
#define GUARD_LIBC_AUTO_SHADOW_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/shadow.h"
#include "../user/pwd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.syslog.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.database.shadow") WUNUSED ATTR_IN(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_sgetspent)(char const *__restrict string) {
	struct spwd *result = NULL;
	FILE *fp = libc_fmemopen((void *)string, libc_strlen(string), "rb");
	if likely(fp) {
		result = libc_fgetspent(fp);

		libc_fclose(fp);

	}
	return result;
}
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_INOUT(2) int
NOTHROW_CB_NCX(LIBCCALL libc_putspent)(struct spwd const *__restrict ent,
                                       FILE *__restrict stream) {
	__STDC_INT_AS_SSIZE_T error;
#if __SIZEOF_POINTER__ <= 1
#define STR_LONGPTR_MAX  "127"
#define STR_ULONGPTR_MAX "255"
#elif __SIZEOF_POINTER__ <= 2
#define STR_LONGPTR_MAX  "32767"
#define STR_ULONGPTR_MAX "65535"
#elif __SIZEOF_POINTER__ <= 4
#define STR_LONGPTR_MAX  "2147483647"
#define STR_ULONGPTR_MAX "4294967295"
#else /* ... */
#define STR_LONGPTR_MAX  "9223372036854775807"
#define STR_ULONGPTR_MAX "18446744073709551615"
#endif /* !... */
	/* String buffers. */
	char ent_sp_lstchg[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_min[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_max[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_warn[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_inact[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_expire[COMPILER_LENOF(STR_LONGPTR_MAX)];
	char ent_sp_flag[COMPILER_LENOF(STR_ULONGPTR_MAX)];
#undef STR_LONGPTR_MAX
#undef STR_ULONGPTR_MAX

	/* Validate arguments. */
	if unlikely(!ent)
		goto err_inval;
	if unlikely(!stream)
		goto err_inval;
	if unlikely(!ent->sp_namp)
		goto err_inval;
	if unlikely(ent->sp_min < 0)
		goto err_inval;
	if unlikely(ent->sp_max < 0)
		goto err_inval;
	if unlikely(ent->sp_warn < 0)
		goto err_inval;
	if unlikely(ent->sp_inact < 0)
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->sp_namp))
		goto err_inval;
	if unlikely(!libc_nss_checkfield(ent->sp_pwdp))
		goto err_inval;

	/* All number-fields default to empty */
	ent_sp_lstchg[0] = '\0';
	ent_sp_min[0]    = '\0';
	ent_sp_max[0]    = '\0';
	ent_sp_warn[0]   = '\0';
	ent_sp_inact[0]  = '\0';
	ent_sp_expire[0] = '\0';
	ent_sp_flag[0]   = '\0';

	/* Generate number-strings for fields that differ from defaults. */
	if (ent->sp_lstchg != (__ULONGPTR_TYPE__)__INTPTR_MAX__)
		libc_sprintf(ent_sp_lstchg, "%" __PRIP_PREFIX "d", ent->sp_lstchg);
	if (ent->sp_min != 0)
		libc_sprintf(ent_sp_min, "%" __PRIP_PREFIX "d", ent->sp_min);
	if (ent->sp_max != (__ULONGPTR_TYPE__)__INTPTR_MAX__) {
		libc_sprintf(ent_sp_max, "%" __PRIP_PREFIX "d", ent->sp_max);
		if (ent->sp_warn != 0)
			libc_sprintf(ent_sp_warn, "%" __PRIP_PREFIX "d", ent->sp_warn);
		if (ent->sp_inact != 0)
			libc_sprintf(ent_sp_inact, "%" __PRIP_PREFIX "d", ent->sp_inact);
	}
	if (ent->sp_expire != (__ULONGPTR_TYPE__)__INTPTR_MAX__)
		libc_sprintf(ent_sp_expire, "%" __PRIP_PREFIX "d", ent->sp_expire);
	if (ent->sp_flag != 0)
		libc_sprintf(ent_sp_flag, "%" __PRIP_PREFIX "u", ent->sp_flag);

	/* Generate the entry. */

	libc_flockfile(stream);

	error = libc_fprintf_unlocked(stream,
	                         "%s:%s:%s:%s:%s:%s:%s:%s:%s\n",
	                         ent->sp_namp,
	                         ent->sp_pwdp ? ent->sp_pwdp : "",
	                         ent_sp_lstchg,
	                         ent_sp_min,
	                         ent_sp_max,
	                         ent_sp_warn,
	                         ent_sp_inact,
	                         ent_sp_expire,
	                         ent_sp_flag);

	libc_funlockfile(stream);


	return likely(error >= 0) ? 0 : -1;
err_inval:

	return libc_seterrno(EINVAL);



}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc_sgetspent_r)(char const *__restrict string,
                                       struct spwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result) {
	errno_t retval;
	FILE *fp = libc_fmemopen((void *)string, libc_strlen(string), "rb");
	if likely(fp) {
		retval = libc_fgetspent_r(fp, resultbuf, buffer, buflen, result);

		libc_fclose(fp);

	} else {

		retval = __libc_geterrno_or(ENOMEM);



	}
	return retval;
}
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetspent_r)(FILE *__restrict stream,
                                       struct spwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result) {
	return libc_fgetspnam_r(stream, NULL, resultbuf, buffer, buflen, result);
}
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/syslog.h>
/* >> fgetspnam_r(3)
 * KOS-extension, base-level read-entry function. When `filtered_name != NULL',
 * filter to return the first  (and hopefully only) entry for  `filtered_name'.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_name'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_INOUT(1) ATTR_IN_OPT(2) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t
NOTHROW_RPC(LIBCCALL libc_fgetspnam_r)(FILE *__restrict stream,
                                       char const *filtered_name,
                                       struct spwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result) {
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
		if (filtered_name != NULL && startpos != 0) {
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

	/* Accepted format:
	 *     sp_namp:sp_pwdp:sp_lstchg:sp_min:sp_max:sp_warn:sp_inact:sp_expire:sp_flag */
	{
		char *field_starts[9];
		char *iter = dbline;
		unsigned int i;
		for (i = 0; i < 9; ++i) {
			if unlikely(!*iter)
				goto badline;
			field_starts[i] = iter;
			iter = libc_strchrnul(iter, ':');
			*iter++ = '\0';
		}

		/* Fill in defaults (for when fields are empty). */
		resultbuf->sp_lstchg = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->sp_min    = 0;
		resultbuf->sp_max    = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->sp_warn   = 0;
		resultbuf->sp_inact  = 0;
		resultbuf->sp_expire = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->sp_flag   = 0;

		/* Now parse and fill in fields */
		for (i = 0; i < 9; ++i) {
			static uintptr_t const offsets[9] = {
				offsetof(struct spwd, sp_namp),
				offsetof(struct spwd, sp_pwdp),
				offsetof(struct spwd, sp_lstchg),
				offsetof(struct spwd, sp_min),
				offsetof(struct spwd, sp_max),
				offsetof(struct spwd, sp_warn),
				offsetof(struct spwd, sp_inact),
				offsetof(struct spwd, sp_expire),
				offsetof(struct spwd, sp_flag),
			};
			char *str;
			uintptr_t offset = offsets[i];
			if (offset == (uintptr_t)-1)
				continue;
			str = field_starts[i];

			/* Check if this is a string-field */
			if (i < 2) {
				size_t len;
				len = (libc_strlen(str) + 1) * sizeof(char);
				/* Ensure that sufficient space is available in the user-provided buffer. */
				if unlikely(buflen < len)
					goto err_ERANGE;

				/* Set the associated pointer in `resultbuf' */
				*(char **)((byte_t *)resultbuf + offset) = buffer;

				/* Copy the string to the user-provided buffer. */
				buffer = (char *)libc_mempcpy(buffer, str, len);
				buflen -= len;
			} else if (*str != '\0') {
				ulongptr_t value;
				errno_t error;
				/* Parse as unsigned since we don't want to accept negative numbers. */
#if __SIZEOF_POINTER__ > 4
				value = libc_strtou64_r(str, (char **)&str, 10, &error);
#else /* __SIZEOF_POINTER__ > 4 */
				value = libc_strtou32_r(str, (char **)&str, 10, &error);
#endif /* __SIZEOF_POINTER__ <= 4 */
				if unlikely(error != 0)
					goto badline;
				if unlikely(*str != '\0')
					goto badline;

				/* Since the record fields are all signed in the public interface,
				 * and  since we parsed  everything as unsigned,  we still have to
				 * make sure that the numbers we'll end up writing won't overflow. */
				if unlikely(value > (ulongptr_t)(uintptr_t)__INTPTR_MAX__)
					goto badline;

				/* Save parsed value in record structure. */
				*(longptr_t *)((byte_t *)resultbuf + offset) = (longptr_t)value;
			}
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

	libc_syslog(LOG_ERR, "[shadow] Bad db line: %q\n", dbline);

	/* FALLTHRU */
nextline:

	libc_free(dbline);

	if unlikely(libc_fgetpos64(stream, &curpos))
		goto err_nodbline;
	if (curpos >= maxpos) {
		dbline = NULL;
		goto eof;
	}
	goto again_parseln;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sgetspent, libc_sgetspent);
DEFINE_PUBLIC_ALIAS(putspent, libc_putspent);
DEFINE_PUBLIC_ALIAS(__sgetspent_r, libc_sgetspent_r);
DEFINE_PUBLIC_ALIAS(sgetspent_r, libc_sgetspent_r);
DEFINE_PUBLIC_ALIAS(__fgetspent_r, libc_fgetspent_r);
DEFINE_PUBLIC_ALIAS(fgetspent_r, libc_fgetspent_r);
DEFINE_PUBLIC_ALIAS(fgetspnam_r, libc_fgetspnam_r);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SHADOW_C */
