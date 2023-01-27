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
%(c_prefix){
/* (#) Portability: GNU C Library (/shadow/shadow.h) */
/* (#) Portability: GNU Hurd      (/usr/include/shadow.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/shadow.h) */
/* (#) Portability: diet libc     (/include/shadow.h) */
/* (#) Portability: libc4/5       (/include/shadow.h) */
/* (#) Portability: libc6         (/include/shadow.h) */
/* (#) Portability: mintlib       (/include/shadow.h) */
/* (#) Portability: musl libc     (/include/shadow.h) */
/* (#) Portability: uClibc        (/include/shadow.h) */
}

%[default:section(".text.crt{|.dos}.database.shadow")]

%[define_decl_include("<bits/crt/db/spwd.h>": ["struct spwd"])]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <paths.h>
)]%[insert:prefix(
#include <bits/crt/db/spwd.h>
)]%{

#ifdef _PATH_SHADOW
#define SHADOW _PATH_SHADOW /* `/etc/shadow' */
#endif /* _PATH_SHADOW */

#ifdef __CC__
__SYSDECL_BEGIN

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

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}


[[cp, export_alias("__setspent")]]
void setspent();

[[cp_nokos, export_alias("__endspent")]]
void endspent();

[[cp, wunused]]
[[decl_include("<bits/crt/db/spwd.h>")]]
[[export_alias("__getspent")]]
struct spwd *getspent();

@@>> getspnam(3)
@@Search for an entry with a matching username
@@@return: * :                         A pointer to the read shadow entry
@@@return: NULL: (errno = <unchanged>) No entry for `name' exists
@@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/spwd.h>"), export_alias("__getspnam")]]
[[wunused, requires_function(setspent, getspent)]]
[[userimpl, impl_include("<bits/crt/db/spwd.h>")]]
struct spwd *getspnam([[in]] char const *__restrict name) {
	struct spwd *result;
	setspent();
	while ((result = getspent()) != NULL) {
		if (strcmp(result->@sp_namp@, name) == 0)
			break;
	}
	return result;
}

@@>> fgetpwent(3)
@@Read an entry from `stream'
@@@return: * :                         A pointer to the read password entry
@@@return: NULL: (errno = <unchanged>) The last entry has already been read
@@                                     (use `rewind(stream)' to rewind the database)
@@@return: NULL: (errno = <changed>)   Error (s.a. `errno')
[[cp, wunused, decl_include("<bits/crt/db/spwd.h>")]]
struct spwd *fgetspent([[inout]] $FILE *__restrict stream);

[[cp, wunused, decl_include("<bits/crt/db/spwd.h>")]]
[[requires_function(fgetspent, fmemopen)]]
struct spwd *sgetspent([[in]] char const *__restrict string) {
	struct spwd *result = NULL;
	FILE *fp = fmemopen((void *)string, strlen(string), "rb");
	if likely(fp) {
		result = fgetspent(fp);
@@pp_if $has_function(fclose)@@
		fclose(fp);
@@pp_endif@@
	}
	return result;
}

[[cp_stdio, decl_include("<bits/crt/db/spwd.h>")]]
[[requires_function(fprintf_unlocked)]]
[[impl_include("<hybrid/limitcore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
int putspent([[in]] struct spwd const *__restrict ent,
             [[inout]] $FILE *__restrict stream) {
	__STDC_INT_AS_SSIZE_T error;
@@pp_if __SIZEOF_POINTER__ == 1@@
#define STR_LONGPTR_MAX  "127"
#define STR_ULONGPTR_MAX "255"
@@pp_elif __SIZEOF_POINTER__ == 2@@
#define STR_LONGPTR_MAX  "32767"
#define STR_ULONGPTR_MAX "65535"
@@pp_elif __SIZEOF_POINTER__ == 4@@
#define STR_LONGPTR_MAX  "2147483647"
#define STR_ULONGPTR_MAX "4294967295"
@@pp_else@@
#define STR_LONGPTR_MAX  "9223372036854775807"
#define STR_ULONGPTR_MAX "18446744073709551615"
@@pp_endif@@
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
	if unlikely(!ent->@sp_namp@)
		goto err_inval;
	if unlikely(!ent->@sp_pwdp@)
		goto err_inval;
	if unlikely(ent->@sp_min@ < 0)
		goto err_inval;
	if unlikely(ent->@sp_max@ < 0)
		goto err_inval;
	if unlikely(ent->@sp_warn@ < 0)
		goto err_inval;
	if unlikely(ent->@sp_inact@ < 0)
		goto err_inval;
	if unlikely(!nss_checkfield(ent->@sp_namp@))
		goto err_inval;
	if unlikely(!nss_checkfield(ent->@sp_pwdp@))
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
	if (ent->@sp_lstchg@ != (__ULONGPTR_TYPE__)__INTPTR_MAX__)
		sprintf(ent_sp_lstchg, "%" __PRIP_PREFIX "d", ent->@sp_lstchg@);
	if (ent->@sp_min@ != 0)
		sprintf(ent_sp_min, "%" __PRIP_PREFIX "d", ent->@sp_min@);
	if (ent->@sp_max@ != (__ULONGPTR_TYPE__)__INTPTR_MAX__) {
		sprintf(ent_sp_max, "%" __PRIP_PREFIX "d", ent->@sp_max@);
		if (ent->@sp_warn@ != 0)
			sprintf(ent_sp_warn, "%" __PRIP_PREFIX "d", ent->@sp_warn@);
		if (ent->@sp_inact@ != 0)
			sprintf(ent_sp_inact, "%" __PRIP_PREFIX "d", ent->@sp_inact@);
	}
	if (ent->@sp_expire@ != (__ULONGPTR_TYPE__)__INTPTR_MAX__)
		sprintf(ent_sp_expire, "%" __PRIP_PREFIX "d", ent->@sp_expire@);
	if (ent->@sp_flag@ != 0)
		sprintf(ent_sp_flag, "%" __PRIP_PREFIX "u", ent->@sp_flag@);

	/* Generate the entry. */
@@pp_if $has_function(flockfile, funlockfile)@@
	flockfile(stream);
@@pp_endif@@
	error = fprintf_unlocked(stream,
	                         "%s:%s:%s:%s:%s:%s:%s:%s:%s\n",
	                         ent->@sp_namp@,
	                         ent->@sp_pwdp@,
	                         ent_sp_lstchg,
	                         ent_sp_min,
	                         ent_sp_max,
	                         ent_sp_warn,
	                         ent_sp_inact,
	                         ent_sp_expire,
	                         ent_sp_flag);
@@pp_if $has_function(flockfile, funlockfile)@@
	funlockfile(stream);
@@pp_endif@@

	return likely(error >= 0) ? 0 : -1;
err_inval:
@@pp_ifdef EINVAL@@
	return libc_seterrno(EINVAL);
@@pp_else@@
	return libc_seterrno(1);
@@pp_endif@@
}

%
%#ifdef __USE_MISC
[[cp, decl_include("<bits/crt/db/spwd.h>", "<bits/types.h>")]]
$errno_t getspent_r([[out]] struct spwd *__restrict resultbuf,
                    [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                    [[out]] struct spwd **__restrict result);

[[cp, doc_alias("getspent_r")]]
[[decl_include("<bits/crt/db/spwd.h>", "<bits/types.h>")]]
$errno_t getspnam_r([[in]] char const *__restrict name,
                    [[out]] struct spwd *__restrict resultbuf,
                    [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                    [[out]] struct spwd **__restrict result);

[[cp, doc_alias("getspent_r")]]
[[decl_include("<bits/crt/db/spwd.h>", "<bits/types.h>")]]
[[requires_function(fgetspent_r, fmemopen)]]
$errno_t sgetspent_r([[in]] char const *__restrict string,
                     [[out]] struct spwd *__restrict resultbuf,
                     [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                     [[out]] struct spwd **__restrict result) {
	errno_t retval;
	FILE *fp = fmemopen((void *)string, strlen(string), "rb");
	if likely(fp) {
		retval = fgetspent_r(fp, resultbuf, buffer, buflen, result);
@@pp_if $has_function(fclose)@@
		fclose(fp);
@@pp_endif@@
	}
	return retval;
}

[[cp, doc_alias("getspent_r")]]
[[decl_include("<bits/crt/db/spwd.h>", "<bits/types.h>")]]
[[requires_function(fgetspnam_r)]]
$errno_t fgetspent_r([[inout]] $FILE *__restrict stream,
                     [[out]] struct spwd *__restrict resultbuf,
                     [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                     [[out]] struct spwd **__restrict result) {
	return fgetspnam_r(stream, NULL, resultbuf, buffer, buflen, result);
}

%
%#ifdef __USE_KOS
@@>> fgetspnam_r(3)
@@KOS-extension, base-level read-entry function. When `filtered_name != NULL',
@@filter to return the first  (and hopefully only) entry for  `filtered_name'.
@@@return: 0 :     Success (`*result' is made to point at `resultbuf')
@@@return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_name'
@@                 Note that in this case, `errno' will have not been changed
@@@return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
@@                 Note that in this case, `errno' will have also been set to `ERANGE'
@@@return: * :     Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/spwd.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>", "<hybrid/typecore.h>", "<asm/os/syslog.h>")]]
[[requires_function(fgetpos64, fsetpos64, fparseln, feof)]]
$errno_t fgetspnam_r([[inout]] $FILE *__restrict stream,
                     [[in_opt]] char const *filtered_name,
                     [[out]] struct spwd *__restrict resultbuf,
                     [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                     [[out]] struct spwd **__restrict result) {
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
		if (!feof(stream))
			goto nextline; /* Skip empty lines! */
		if (filtered_name != NULL && startpos != 0) {
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
			iter = strchrnul(iter, ':');
			*iter++ = '\0';
		}

		/* Fill in defaults (for when fields are empty). */
		resultbuf->@sp_lstchg@ = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->@sp_min@    = 0;
		resultbuf->@sp_max@    = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->@sp_warn@   = 0;
		resultbuf->@sp_inact@  = 0;
		resultbuf->@sp_expire@ = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		resultbuf->@sp_flag@   = 0;

		/* Now parse and fill in fields */
		for (i = 0; i < 9; ++i) {
			static uintptr_t const offsets[9] = {
				offsetof(struct spwd, @sp_namp@),
				offsetof(struct spwd, @sp_pwdp@),
				offsetof(struct spwd, @sp_lstchg@),
				offsetof(struct spwd, @sp_min@),
				offsetof(struct spwd, @sp_max@),
				offsetof(struct spwd, @sp_warn@),
				offsetof(struct spwd, @sp_inact@),
				offsetof(struct spwd, @sp_expire@),
				offsetof(struct spwd, @sp_flag@),
			};
			char *str;
			uintptr_t offset = offsets[i];
			if (offset == (uintptr_t)-1)
				continue;
			str = field_starts[i];

			/* Check if this is a string-field */
			if (i < 2) {
				size_t len;
				len = (strlen(str) + 1) * sizeof(char);
				/* Ensure that sufficient space is available in the user-provided buffer. */
				if unlikely(buflen < len)
					goto err_ERANGE;

				/* Set the associated pointer in `resultbuf' */
				*(char **)((byte_t *)resultbuf + offset) = buffer;

				/* Copy the string to the user-provided buffer. */
				buffer = (char *)mempcpy(buffer, str, len);
				buflen -= len;
			} else if (*str != '\0') {
				ulongptr_t value;
				errno_t error;
				/* Parse as unsigned since we don't want to accept negative numbers. */
@@pp_if __SIZEOF_POINTER__ > 4@@
				value = strtou64_r(str, (char **)&str, 10, &error);
@@pp_else@@
				value = strtou32_r(str, (char **)&str, 10, &error);
@@pp_endif@@
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
@@pp_if $has_function(free)@@
	free(dbline);
@@pp_endif@@
	*result = retval ? NULL : resultbuf;
	return retval;

err_ERANGE:
@@pp_ifdef ERANGE@@
	(void)libc_seterrno(ERANGE);
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
	syslog(LOG_ERR, "[shadow] Bad db line: %q\n", dbline);
@@pp_endif@@
	/* FALLTHRU */
nextline:
@@pp_if $has_function(free)@@
	free(dbline);
@@pp_endif@@
	if unlikely(fgetpos64(stream, &curpos))
		goto err_nodbline;
	if (curpos >= maxpos) {
		dbline = NULL;
		goto eof;
	}
	goto again_parseln;
}
%#endif /* __USE_KOS */

%#endif /* __USE_MISC */

[[cp_kos, export_alias("__lckpwdf")]]
int lckpwdf();

[[export_alias("__ulckpwdf")]]
int ulckpwdf();


%{

__SYSDECL_END
#endif /* __CC__ */

}
