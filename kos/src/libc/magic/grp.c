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
/* (#) Portability: Cygwin        (/newlib/libc/include/grp.h) */
/* (#) Portability: DJGPP         (/include/grp.h) */
/* (#) Portability: DragonFly BSD (/include/grp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/grp.h) */
/* (#) Portability: FreeBSD       (/include/grp.h) */
/* (#) Portability: GNU C Library (/grp/grp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/grp.h) */
/* (#) Portability: NetBSD        (/include/grp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/grp.h) */
/* (#) Portability: OpenBSD       (/include/grp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/grp.h) */
/* (#) Portability: diet libc     (/include/grp.h) */
/* (#) Portability: libbsd        (/include/bsd/grp.h) */
/* (#) Portability: libc4/5       (/include/grp.h) */
/* (#) Portability: libc6         (/include/grp.h) */
/* (#) Portability: mintlib       (/include/grp.h) */
/* (#) Portability: musl libc     (/include/grp.h) */
/* (#) Portability: uClibc        (/include/grp.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(gid_t = __gid_t)]
%[default:section(".text.crt{|.dos}.database.grp")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/db/group.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#if defined(__USE_POSIX) && defined(__USE_MISC)
#define NSS_BUFLEN_GROUP 1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
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


@@>> getgrgid(3), getgrgid_r(3)
[[cp, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
[[wunused, requires_function(setgrent, getgrent)]]
[[userimpl, impl_include("<bits/crt/db/group.h>")]]
struct group *getgrgid($gid_t gid) {
	struct group *result;
	setgrent();
	while ((result = getgrent()) != NULL) {
		if (result->@gr_gid@ == gid)
			break;
	}
	return result;
}

@@>> getgrnam(3), getgrnam_r(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
[[wunused, requires_function(setgrent, getgrent)]]
[[userimpl, impl_include("<bits/crt/db/group.h>")]]
struct group *getgrnam([[in]] char const *__restrict name) {
	struct group *result;
	setgrent();
	while ((result = getgrent()) != NULL) {
		if (strcmp(result->@gr_name@, name) == 0)
			break;
	}
	return result;
}



%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@>> setgrent(3)
[[cp]]
void setgrent();

@@>> endgrent(3)
[[cp_nokos]]
void endgrent();

@@>> getgrent(3), getgrent_r(3)
[[cp, wunused, decl_include("<bits/crt/db/group.h>")]]
struct group *getgrent();
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */





%
%#ifdef __USE_GNU
@@>> putgrent(3)
@@Write the given entry `ent' into the given `stream'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[cp, decl_include("<bits/crt/db/group.h>")]]
[[requires_function(fprintf_unlocked)]]
[[impl_include("<libc/errno.h>")]]
[[impl_include("<bits/types.h>")]]
[[impl_include("<bits/crt/inttypes.h>")]]
int putgrent([[in]] struct group const *__restrict entry,
             [[inout]] $FILE *__restrict stream) {
	__STDC_INT_AS_SSIZE_T error;
@@pp_if __SIZEOF_GID_T__ == 1@@
	char gidbuf[COMPILER_LENOF("255")];
@@pp_elif __SIZEOF_GID_T__ == 2@@
	char gidbuf[COMPILER_LENOF("65535")];
@@pp_elif __SIZEOF_GID_T__ == 4@@
	char gidbuf[COMPILER_LENOF("4294967295")];
@@pp_else@@
	char gidbuf[COMPILER_LENOF("18446744073709551615")];
@@pp_endif@@

	/* Validate arguments. */
	if unlikely(!entry)
		goto err_inval;
	if unlikely(!stream)
		goto err_inval;
	if unlikely(!entry->@gr_name@)
		goto err_inval;
	if unlikely(!nss_checkfield(entry->@gr_name@))
		goto err_inval;
	if unlikely(!nss_checkfield(entry->@gr_passwd@))
		goto err_inval;
	if unlikely(!nss_checkfieldlist(entry->@gr_mem@))
		goto err_inval;

	/* Generate the GID string. */
	sprintf(gidbuf, "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u", entry->@gr_gid@);
	if (entry->@gr_name@[0] == '+' || entry->@gr_name@[0] == '-')
		gidbuf[0] = '\0';

	/* Generate the entry. */
@@pp_if $has_function(flockfile, funlockfile)@@
	flockfile(stream);
@@pp_endif@@
	error = fprintf_unlocked(stream, "%s:%s:%s:",
	                         entry->@gr_name@,
	                         entry->@gr_passwd@ ? entry->@gr_passwd@ : "",
	                         gidbuf);
	if likely(error >= 0) {
		/* Print the member list (if it is present) */
		char *const *list = entry->@gr_mem@;
		if (list) {
			bool isfirst = true;
			for (; *list; ++list) {
				error = fprintf_unlocked(stream,
				                         isfirst ? "%s" : ",%s",
				                         *list);
				if unlikely(error < 0)
					break;
				isfirst = false;
			}
		}
		if likely(error >= 0)
			error = fputc_unlocked('\n', stream);
	}
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

%#endif /* __USE_GNU */




%
%#ifdef __USE_POSIX
[[cp, doc_alias("getgrgid"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrgid_r($gid_t gid, [[out]] struct group *__restrict resultbuf,
               [[out(buflen)]] char *__restrict buffer, size_t buflen,
               [[out]] struct group **__restrict result);

[[cp, doc_alias("getgrnam"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrnam_r([[in]] char const *__restrict name,
               [[out]] struct group *__restrict resultbuf,
               [[out(buflen)]] char *__restrict buffer, size_t buflen,
               [[out]] struct group **__restrict result);



%
%#ifdef __USE_GNU
[[cp, doc_alias("getgrent"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrent_r([[out]] struct group *__restrict resultbuf,
               [[out(buflen)]] char *__restrict buffer, size_t buflen,
               [[out]] struct group **__restrict result);
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
[[cp, doc_alias("fgetgrent"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
[[requires_function(fgetgrfiltered_r)]]
int fgetgrent_r([[inout]] $FILE *__restrict stream,
                [[out]] struct group *__restrict resultbuf,
                [[out(buflen)]] char *__restrict buffer, size_t buflen,
                [[out]] struct group **__restrict result) {
	return fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                        result, (gid_t)-1, NULL);
}

%#ifdef __USE_KOS
@@>> fgetgrgid_r(3)
@@Search for an entry with a matching user ID
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `gid'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
[[requires_function(fgetgrfiltered_r), impl_include("<libc/errno.h>")]]
$errno_t fgetgrgid_r([[inout]] $FILE *__restrict stream, $gid_t gid,
                     [[out]] struct group *__restrict resultbuf,
                     [[out(buflen)]] char *__restrict buffer, size_t buflen,
                     [[out]] struct group **__restrict result) {
	$errno_t error;
	error = fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, gid, NULL);
@@pp_ifdef ENOENT@@
	if (error == ENOENT)
		error = 0;
@@pp_endif@@
	return error;
}

@@>> fgetgrnam_r(3)
@@Search for an entry with a matching username
@@@return: 0 : (*result != NULL) Success
@@@return: 0 : (*result == NULL) No entry for `name'
@@@return: * : Error (one of `E*' from `<errno.h>')
[[cp, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
[[requires_function(fgetgrfiltered_r), impl_include("<libc/errno.h>")]]
$errno_t fgetgrnam_r([[inout]] $FILE *__restrict stream,
                     [[in]] char const *__restrict name,
                     [[out]] struct group *__restrict resultbuf,
                     [[out(buflen)]] char *__restrict buffer, size_t buflen,
                     [[out]] struct group **__restrict result) {
	$errno_t error;
	error = fgetgrfiltered_r(stream, resultbuf, buffer, buflen,
	                         result, (gid_t)-1, name);
@@pp_ifdef ENOENT@@
	if (error == ENOENT)
		error = 0;
@@pp_endif@@
	return error;
}
%#endif /* __USE_KOS */


@@>> fgetgrfiltered_r(3)
@@Filtered read from `stream'
@@@param: filtered_gid:  When not equal to `(gid_t)-1', require this GID
@@@param: filtered_name: When not `NULL', require this username
@@@return: 0 :     Success (`*result' is made to point at `resultbuf')
@@@return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
@@                 Note that in this case, `errno' will have not been changed
@@@return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
@@                 Note that in this case, `errno' will have also been set to `ERANGE'
@@@return: * :     Error (one of `E*' from `<errno.h>')
[[static, cp, decl_include("<bits/types.h>", "<bits/crt/db/group.h>")]]
[[impl_include("<libc/errno.h>", "<hybrid/typecore.h>", "<asm/os/syslog.h>")]]
[[requires_function(fgetpos64, fsetpos64, fparseln, feof)]]
$errno_t fgetgrfiltered_r([[inout]] $FILE *__restrict stream,
                          [[out]] struct group *__restrict resultbuf,
                          [[out(buflen)]] char *__restrict buffer, size_t buflen,
                          [[out]] struct group **__restrict result,
                          $gid_t filtered_gid,
                          [[in_opt]] char const *filtered_name) {
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
		if ((filtered_gid != (gid_t)-1 || filtered_name != NULL) && startpos != 0) {
			maxpos   = startpos;
			startpos = 0;
@@pp_if $has_function(rewind)@@
			rewind(stream);
@@pp_else@@
			if (fsetpos64(stream, &startpos))
				goto err;
@@pp_endif@@
			/* Search for the requested gid/name prior to the initial search-start position. */
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
	 *     gr_name:gr_passwd:gr_gid
	 *     gr_name:gr_passwd:gr_gid:gr_mem[0],gr_mem[1],...
	 */
	{
		char *field_starts[4];
		char *iter = dbline;
		unsigned int i;
		for (i = 0; i < 2; ++i) {
			field_starts[i] = iter;
			iter = strchrnul(iter, ':');
			if unlikely(!*iter)
				goto badline;
			*iter++ = '\0';
		}
		if (filtered_name) {
			if (strcmp(field_starts[0], filtered_name) != 0)
				goto nextline;
		}
		field_starts[2] = iter;
		field_starts[3] = NULL;
		iter = strchrnul(iter, ':');
		if likely(*iter) {
			*iter++ = '\0';
			/* Right now, `iter' points at the start of `gr_mem[0]' */
			field_starts[3] = iter; /* gr_mem[0] */
			if unlikely(*strchrnul(iter, ':'))
				goto badline; /* There shouldn't be another ':' */
		}

		/* All   right!  we've  got  all  of  the  fields!
		 * Now to fill  in the 1  numeric field (since  it
		 * might still contain errors that would turn this
		 * entry into a bad line) */
		if unlikely(!*field_starts[2]) {
			resultbuf->@gr_gid@ = (gid_t)-1;
		} else {
			resultbuf->@gr_gid@ = (gid_t)strtoul(field_starts[2], &iter, 10);
			if unlikely(*iter)
				goto badline;
			if (filtered_gid != (gid_t)-1) {
				if (resultbuf->@gr_gid@ != filtered_gid)
					goto nextline;
			}
		}

		/* All right! Now to fill in all of the string fields.
		 * We've already turned all of them into NUL-terminated strings  pointing
		 * into the heap-allocated `dbline' string, however the prototype of this
		 * function requires that they be pointing into `buffer...+=buflen' */
		for (i = 0; i < 2; ++i) {
			static uintptr_t const offsets[2] = {
				offsetof(struct group, @gr_name@),
				offsetof(struct group, @gr_passwd@),
			};
			char *str;
			size_t len;
			uintptr_t offset = offsets[i];
			str = field_starts[i];
			len = (strlen(str) + 1) * sizeof(char);
			/* Ensure that sufficient space is available in the user-provided buffer. */
			if unlikely(len > buflen)
				goto err_ERANGE;
			/* Set the associated pointer in `resultbuf' */
			*(char **)((byte_t *)resultbuf + offset) = buffer;
			/* Copy the string to the user-provided buffer. */
			buffer = (char *)mempcpy(buffer, str, len);
			buflen -= len;
		}

		/* Finally, and the most complicated of all, we have to split the group-member-list. */
		{
			char *aligned = (char *)(((uintptr_t)buffer + sizeof(void *) - 1) & ~(sizeof(void *) - 1));
			/* Align to whole pointers. */
			size_t padsiz = (size_t)(aligned - buffer);
			if unlikely(padsiz > buflen)
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
					iter = strchr(iter, ',');
					if (!iter)
						break;
					++iter;
				}
			}
			resultbuf->@gr_mem@ = (char **)buffer;
			reqspace = (member_count + 1) * sizeof(char *);
			if unlikely(reqspace > buflen)
				goto err_ERANGE;
			buflen -= reqspace;
			buffer += reqspace;
		}
		/* Assign member names. */
		{
			char **dst = resultbuf->@gr_mem@;
			char *iter = field_starts[3];
			if (iter) {
				for (;;) {
					size_t siz;
					siz = stroff(iter, ',') * sizeof(char);
					if unlikely((siz + 1) > buflen)
						goto err_ERANGE;
					/* Copy to user-provided buffer. */
					*(char *)mempcpy(buffer, iter, siz) = '\0';
					*dst++ = buffer;
					buflen -= siz + 1;
					buffer += siz + 1;
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
	syslog(LOG_ERR, "[group] Bad db line: %q\n", dbline);
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



%#endif /* __USE_MISC */
%#endif /* __USE_POSIX */




%
%#ifdef __USE_MISC
@@>> fgetgrent(3), fgetgrent_r(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
struct group *fgetgrent([[inout]] $FILE *__restrict stream);

@@>> setgroups(2)
[[cp, guard, decl_include("<bits/types.h>")]]
[[export_alias("__setgroups", "__libc_setgroups")]]
int setgroups(size_t count, [[in(count)]] $gid_t const *groups);

@@>> getgrouplist(3)
@@Use the groups database to find the GIDs of all of the groups which `user'
@@is apart of. In case this list doesn't already include `group', it will be
@@inserted into the list (thus making sure that it is always a member).
@@@param: user:    The name to seach for in the member lists of groups.
@@@param: group:   Usually, the default group of `user' (as retrieved from  the
@@                 functions from `<pwd.h>'). This group will always be made to
@@                 be a member of the list of GIDs written to `*groups'
@@@param: groups:  Output buffer for GIDs
@@@param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
@@                       in the given buffer before it become full. When this limit
@@                 [out] The required buffer size (in elements). Upon success, the
@@                       value written  here is  identical  to the  return  value.
@@@return: * : [== *ngroups] The number of items written to `groups'
@@@return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
@@             In this case, `OUT(*ngroups)' specifies the number of required elements
@@             in terms of buffer  size to write  all groups (use  this to resize  the
@@             buffer you're passing for `groups').
@@             Note that standards don't say anything about `errno' in this case,
@@             so the KOS implementation of this function simply leaves its value
@@             untouched when this happens (other implementations might set it to
@@             `ERANGE' for example...)
[[cp, guard, decl_include("<features.h>", "<bits/crt/db/group.h>", "<bits/types.h>")]]
[[requires_function(setgrent, getgrent), impl_include("<bits/crt/db/group.h>")]]
__STDC_INT_AS_SSIZE_T getgrouplist([[in]] char const *user, $gid_t group,
                                   [[out/*(return <= *ngroups)*/]] $gid_t *groups,
                                   [[inout]] __STDC_INT_AS_SIZE_T *ngroups) {
	__STDC_INT_AS_SIZE_T count = 0;
	__STDC_INT_AS_SIZE_T buflen = *ngroups;
	struct group *ent;
	setgrent();
	while ((ent = getgrent()) != NULL) {
		size_t i;
		if (ent->@gr_gid@ == group)
			goto nextgroup; /* Skip! (always added manually) */

		/* Check if `user' is in this group's member list. */
		for (i = 0;; ++i) {
			char *member = ent->@gr_mem@[i];
			if (!member)
				goto nextgroup;
			if (strcmp(member, user) == 0)
				break; /* Yup! User is apart of this group! */
		}

		/* Add this group's GID to the result list. */
		if (count < buflen)
			*groups++ = ent->@gr_gid@;
		++count;
nextgroup:
		;
	}

	/* Append `group', so it's always apart of the list.
	 *
	 * The fact  that in  our  implementation it's  always  the
	 * last member is an implementation detail we intentionally
	 * neglect to document! */
	if (count < buflen)
		*groups++ = group;
	++count;

	/* Write-back the required buffer size. */
	*ngroups = (__STDC_INT_AS_SIZE_T)count;
	if ((size_t)count > (size_t)buflen)
		return (__STDC_INT_AS_SSIZE_T)-1; /* Buffer too small. */
	return (__STDC_INT_AS_SSIZE_T)count;
}

@@>> initgroups(3)
@@A helper function that combines `getgrouplist(3)' with `setgroups(2)',
@@and can be used to set the calling process's group list to that of the
@@given user, whilst always being guarantied to also include `group'!
@@@return: 0 : Success
@@@return: -1: [errno=ENOMEM] Out of member
@@@return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
@@                            or at least not in the way you're trying to.
[[cp, guard, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
[[requires_function(getgrouplist, setgroups, realloc)]]
int initgroups([[in]] char const *user, $gid_t group) {
	int result = 0;
	gid_t initbuf[32], *buf = initbuf;
	__STDC_INT_AS_SIZE_T buflen = COMPILER_LENOF(initbuf);
	__STDC_INT_AS_SIZE_T ngroups;
	for (;;) {
		gid_t *newbuf;
		ngroups = buflen;
		if (getgrouplist(user, group, buf, &ngroups) != -1)
			break;
		/* Allocate more space. */
		if (buf == initbuf)
			buf = NULL;
		newbuf = (gid_t *)realloc(buf, ngroups * sizeof(gid_t));
		if unlikely(!newbuf) {
			result = -1;
			goto done;
		}
		buf = newbuf;
	}

	/* Apply the loaded list of groups. */
	result = setgroups((size_t)ngroups, buf);
done:
@@pp_if $has_function(free)@@
	if (buf != initbuf)
		free(buf);
@@pp_endif@@
	return result;
}
%#endif /* __USE_MISC */


%
%#ifdef __USE_BSD

[[requires_function(setgrent)]]
int setgroupent(int keep_open) {
	(void)keep_open;
	setgrent();
	return 0;
}

[[guard, decl_include("<bits/types.h>")]]
[[impl_include("<bits/types.h>")]]
[[impl_include("<bits/crt/db/group.h>")]]
[[requires_function(getgrnam)]]
int gid_from_group([[in]] char const *name, [[out]] gid_t *p_gid) {
	struct group *ent = getgrnam(name);
	if (ent) {
		*p_gid = ent->@gr_gid@;
		return 0;
	}
	return -1;
}


[[guard, wunused]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/types.h>")]]
[[impl_include("<bits/crt/db/group.h>")]]
[[impl_include("<bits/crt/inttypes.h>")]]
[[requires_function(getgrgid)]]
char const *group_from_gid(gid_t gid, int nogroup) {
	struct group *ent = getgrgid(gid);
	if (ent)
		return ent->@gr_name@;
	if (nogroup == 0) {
@@pp_if __SIZEOF_GID_T__ == 1@@
		static char fallback_strbuf[__COMPILER_LENOF("-128")];
@@pp_elif __SIZEOF_GID_T__ == 2@@
		static char fallback_strbuf[__COMPILER_LENOF("-32768")];
@@pp_elif __SIZEOF_GID_T__ == 4@@
		static char fallback_strbuf[__COMPILER_LENOF("-2147483648")];
@@pp_else@@
		static char fallback_strbuf[__COMPILER_LENOF("-9223372036854775808")];
@@pp_endif@@
		sprintf(fallback_strbuf, "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "d", gid);
		return fallback_strbuf;
	}
	return NULL;
}

%#endif /* __USE_BSD */


%{

__SYSDECL_END
#endif /* __CC__ */

}
