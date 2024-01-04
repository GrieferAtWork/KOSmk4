/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/envz.h) */
/* (#) Portability: GNU C Library (/string/envz.h) */
/* (#) Portability: GNU Hurd      (/usr/include/envz.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/envz.h) */
/* (#) Portability: libc6         (/include/envz.h) */
}

%[default:section(".text.crt{|.dos}.string.envz")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <argz.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define_replacement(error_t = __errno_t)]


@@>> envz_entry(3)
@@Find and return the entry for `name' in `envz', or `NULL' if not found.
@@If `name' contains a `=' character, only characters leading up to  this
@@position are actually compared!
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
char *envz_entry([in(envz_len)] char const *__restrict envz, size_t envz_len, [[in]] char const *__restrict name)
	[([in(envz_len)] char *__restrict envz, size_t envz_len, [[in]] char const *__restrict name): char *]
	[([in(envz_len)] char const *__restrict envz, size_t envz_len, [[in]] char const *__restrict name): char const *]
{
	size_t namelen;
	char *envz_end = (char *)(envz + envz_len);
	namelen = stroff(name, '=');
	while (envz < envz_end) {
		if (bcmpc(envz, name, namelen, sizeof(char)) == 0 &&
		    (envz[namelen] == '\0' || envz[namelen] == '='))
			return (char *)envz; /* Found it! */
		envz = strend(envz) + 1;
	}
	return NULL;
}

@@>> envz_get(3)
@@Return the value in `envz'  attached to `name', or  `NULL'
@@if no such entry exists, or the entry doesn't have a value
@@portion (i.e. doesn't contain a `='-character)
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
char *envz_get([in(envz_len)] char const *__restrict envz, size_t envz_len, [[in]] char const *__restrict name)
	[([in(envz_len)] char *__restrict envz, size_t envz_len, [[in]] char const *__restrict name): char *]
	[([in(envz_len)] char const *__restrict envz, size_t envz_len, [[in]] char const *__restrict name): char const *]
{
	char *result;
	result = (char *)envz_entry(envz, envz_len, name);
	if (result) {
		result = strchr(result, '=');
		if (result)
			++result; /* Point to the value-portion */
	}
	return result;
}

@@>> envz_add(3)
@@Add an entry `name=value' to `penvz'. If another entry for `name'
@@already existed before, that entry is removed. If `name' is NULL,
@@the entry created  doesn't have a  value-portion (i.e. `name'  is
@@added to `penvz' as-is, without the trailing `=value')
[[impl_include("<libc/errno.h>"), decl_include("<bits/types.h>")]]
[[requires_function(realloc, argz_add)]]
error_t envz_add([[inout]] char **__restrict penvz,
                 [[inout]] size_t *__restrict penvz_len,
                 [[in]] char const *__restrict name,
                 [[in_opt]] char const *value) {
	char *new_envz;
	size_t namelen, valuelen, morelen;
	envz_remove(penvz, penvz_len, name);
	if (!value)
		return argz_add(penvz, penvz_len, name);
	/* Append a new string `name=value\0' */
	namelen  = strlen(name);
	valuelen = strlen(value);
	morelen  = namelen + 1 + valuelen + 1;
	new_envz = (char *)realloc(*penvz, (*penvz_len + morelen) * sizeof(char));
	if unlikely(!new_envz) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*penvz = new_envz;
	new_envz += *penvz_len;
	*penvz_len += morelen;
	new_envz = (char *)mempcpyc(new_envz, name, namelen, sizeof(char));
	*new_envz++ = '=';
	new_envz = (char *)mempcpyc(new_envz, value, valuelen, sizeof(char));
	*new_envz = '\0';
	return 0;
}

@@>> envz_merge(3)
@@Add all entries from `envz2' to `penvz', as though `envz_add()' was
@@called for each contained `name=value' pair (using `NULL' for value
@@on pairs that doesn't have a value-portion.
@@If individual entries already existed in `penvz', behavior  depends
@@on `override_', which if non-zero will cause existing entries to be
@@overwritten, and otherwise if zero, will cause them to stay.
[[requires_function(argz_append), decl_include("<bits/types.h>")]]
error_t envz_merge([[inout]] char **__restrict penvz,
                   [[inout]] size_t *__restrict penvz_len,
                   [[in(envz2_len)]] char const *__restrict envz2,
                   size_t envz2_len, int override_) {
	error_t result = 0;
	while (envz2_len && result == 0) {
		char *existing = envz_entry(*penvz, *penvz_len, envz2);
		size_t newlen  = strlen(envz2) + 1;
		if (!existing) {
			result = argz_append(penvz, penvz_len, envz2, newlen);
		} else if (override_) {
			argz_delete(penvz, penvz_len, existing);
			result = argz_append(penvz, penvz_len, envz2, newlen);
		}
		envz2     += newlen;
		envz2_len -= newlen;
	}
	return result;
}

@@>> envz_remove(3)
@@Remove an entry matching `name' from `penvz',
@@or  do  nothing  if  no  such  entry  exists.
[[decl_include("<hybrid/typecore.h>")]]
void envz_remove([[inout]] char **__restrict penvz,
                 [[inout]] size_t *__restrict penvz_len,
                 [[in]] char const *__restrict name) {
	char *entry;
	entry = envz_entry(*penvz, *penvz_len, name);
	if (entry)
		argz_delete(penvz, penvz_len, entry);
}


@@>> envz_strip(3)
@@Remove all entries from `penvz' that don't have a value-portion.
[[decl_include("<hybrid/typecore.h>")]]
void envz_strip([[inout]] char **__restrict penvz,
                [[inout]] size_t *__restrict penvz_len) {
	char *start, *ptr, *end;
	size_t oldlen, newlen;
	ptr = start = *penvz;
	end = ptr + (oldlen = *penvz_len);
	while (ptr < end) {
		char *next;
		size_t partlen;
		next = strchrnul(ptr, '=');
		if (*next) {
			ptr = strend(next) + 1;
			continue;
		}
		/* Remove this entry. */
		next = strend(next) + 1;
		partlen = (size_t)(end - next);
		memmovedownc(ptr, next, partlen, sizeof(char));
		end -= partlen;
	}
	newlen = (size_t)(end - start);
	if (newlen < oldlen) {
		*penvz_len = newlen;
@@pp_if $has_function(realloc)@@
		start = (char *)realloc(start, newlen);
		if likely(start)
			*penvz = start;
@@pp_endif@@
	}
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
