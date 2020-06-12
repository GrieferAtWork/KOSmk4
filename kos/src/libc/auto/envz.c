/* HASH CRC-32:0xa796bd55 */
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
#ifndef GUARD_LIBC_AUTO_ENVZ_C
#define GUARD_LIBC_AUTO_ENVZ_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "envz.h"
#include <argz.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_PURE WUNUSED NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_envz_entry)(char const *__restrict envz,
                                      size_t envz_len,
                                      char const *__restrict name) {
	size_t namelen;
	char *envz_end = (char *)(envz + envz_len);
	namelen = stroff(name, '=');
	while (envz < envz_end) {
		if (memcmp(envz, name, namelen) == 0 &&
		    (envz[namelen] == '\0' || envz[namelen] == '='))
			return (char *)envz; /* Found it! */
		envz = strend(envz) + 1;
	}
	return NULL;
}
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_PURE WUNUSED NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_envz_get)(char const *__restrict envz,
                                    size_t envz_len,
                                    char const *__restrict name) {
	char *result;
	result = (char *)envz_entry(envz, envz_len, name);
	if (result) {
		result = strchr(result, '=');
		if (result)
			++result; /* Point to the value-portion */
	}
	return result;
}
#include <parts/errno.h>
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
INTERN ATTR_SECTION(".text.crt.string.envz") NONNULL((1, 2, 3)) error_t
NOTHROW_NCX(LIBCCALL libc_envz_add)(char **__restrict penvz,
                                    size_t *__restrict penvz_len,
                                    char const *__restrict name,
                                    char const *value) {
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
#ifdef ENOMEM
		return ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
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
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
INTERN ATTR_SECTION(".text.crt.string.envz") NONNULL((1, 2, 3)) error_t
NOTHROW_NCX(LIBCCALL libc_envz_merge)(char **__restrict penvz,
                                      size_t *__restrict penvz_len,
                                      char const *__restrict envz2,
                                      size_t envz2_len,
                                      int override_) {
	error_t result = 0;
	while (envz2_len && result == 0) {
		char *existing = envz_entry(*penvz, *penvz_len, envz2);
		size_t newlen  = strlen(envz2) + 1;
		if (!existing)
			result = argz_append(penvz, penvz_len, envz2, newlen);
		else if (override_) {
			argz_delete(penvz, penvz_len, existing);
			result = argz_append(penvz, penvz_len, envz2, newlen);
		}
		envz2     += newlen;
		envz2_len -= newlen;
	}
	return result;
}
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
INTERN ATTR_SECTION(".text.crt.string.envz") NONNULL((1, 2, 3)) void
NOTHROW_NCX(LIBCCALL libc_envz_remove)(char **__restrict penvz,
                                       size_t *__restrict penvz_len,
                                       char const *__restrict name) {
	char *entry;
	entry = envz_entry(*penvz, *penvz_len, name);
	if (entry)
		argz_delete(penvz, penvz_len, entry);
}
/* Remove entries that have no value attached */
INTERN ATTR_SECTION(".text.crt.string.envz") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc_envz_strip)(char **__restrict penvz,
                                      size_t *__restrict penvz_len) {
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
#ifdef __CRT_HAVE_realloc
		start = (char *)realloc(start, newlen);
		if likely(start)
			*penvz = start;
#endif /* __CRT_HAVE_realloc */
	}
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(envz_entry, libc_envz_entry);
DEFINE_PUBLIC_ALIAS(envz_get, libc_envz_get);
DEFINE_PUBLIC_ALIAS(envz_add, libc_envz_add);
DEFINE_PUBLIC_ALIAS(envz_merge, libc_envz_merge);
DEFINE_PUBLIC_ALIAS(envz_remove, libc_envz_remove);
DEFINE_PUBLIC_ALIAS(envz_strip, libc_envz_strip);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ENVZ_C */
