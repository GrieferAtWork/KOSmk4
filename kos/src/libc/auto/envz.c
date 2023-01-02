/* HASH CRC-32:0x39a35a57 */
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
#ifndef GUARD_LIBC_AUTO_ENVZ_C
#define GUARD_LIBC_AUTO_ENVZ_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "envz.h"
#include "argz.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_envz_entry)(char const *__restrict envz,
                                      size_t envz_len,
                                      char const *__restrict name) {
	size_t namelen;
	char *envz_end = (char *)(envz + envz_len);
	namelen = libc_stroff(name, '=');
	while (envz < envz_end) {
		if (libc_bcmpc(envz, name, namelen, sizeof(char)) == 0 &&
		    (envz[namelen] == '\0' || envz[namelen] == '='))
			return (char *)envz; /* Found it! */
		envz = libc_strend(envz) + 1;
	}
	return NULL;
}
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_envz_get)(char const *__restrict envz,
                                    size_t envz_len,
                                    char const *__restrict name) {
	char *result;
	result = (char *)libc_envz_entry(envz, envz_len, name);
	if (result) {
		result = libc_strchr(result, '=');
		if (result)
			++result; /* Point to the value-portion */
	}
	return result;
}
#include <libc/errno.h>
/* >> envz_add(3)
 * Add an entry `name=value' to `penvz'. If another entry for `name'
 * already existed before, that entry is removed. If `name' is NULL,
 * the entry created  doesn't have a  value-portion (i.e. `name'  is
 * added to `penvz' as-is, without the trailing `=value') */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(4) error_t
NOTHROW_NCX(LIBCCALL libc_envz_add)(char **__restrict penvz,
                                    size_t *__restrict penvz_len,
                                    char const *__restrict name,
                                    char const *value) {
	char *new_envz;
	size_t namelen, valuelen, morelen;
	libc_envz_remove(penvz, penvz_len, name);
	if (!value)
		return libc_argz_add(penvz, penvz_len, name);
	/* Append a new string `name=value\0' */
	namelen  = libc_strlen(name);
	valuelen = libc_strlen(value);
	morelen  = namelen + 1 + valuelen + 1;
	new_envz = (char *)libc_realloc(*penvz, (*penvz_len + morelen) * sizeof(char));
	if unlikely(!new_envz) {

		return ENOMEM;



	}
	*penvz = new_envz;
	new_envz += *penvz_len;
	*penvz_len += morelen;
	new_envz = (char *)libc_mempcpyc(new_envz, name, namelen, sizeof(char));
	*new_envz++ = '=';
	new_envz = (char *)libc_mempcpyc(new_envz, value, valuelen, sizeof(char));
	*new_envz = '\0';
	return 0;
}
/* >> envz_merge(3)
 * Add all entries from `envz2' to `penvz', as though `envz_add()' was
 * called for each contained `name=value' pair (using `NULL' for value
 * on pairs that doesn't have a value-portion.
 * If individual entries already existed in `penvz', behavior  depends
 * on `override_', which if non-zero will cause existing entries to be
 * overwritten, and otherwise if zero, will cause them to stay. */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t
NOTHROW_NCX(LIBCCALL libc_envz_merge)(char **__restrict penvz,
                                      size_t *__restrict penvz_len,
                                      char const *__restrict envz2,
                                      size_t envz2_len,
                                      int override_) {
	error_t result = 0;
	while (envz2_len && result == 0) {
		char *existing = libc_envz_entry(*penvz, *penvz_len, envz2);
		size_t newlen  = libc_strlen(envz2) + 1;
		if (!existing) {
			result = libc_argz_append(penvz, penvz_len, envz2, newlen);
		} else if (override_) {
			libc_argz_delete(penvz, penvz_len, existing);
			result = libc_argz_append(penvz, penvz_len, envz2, newlen);
		}
		envz2     += newlen;
		envz2_len -= newlen;
	}
	return result;
}
/* >> envz_remove(3)
 * Remove an entry matching `name' from `penvz',
 * or  do  nothing  if  no  such  entry  exists. */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW_NCX(LIBCCALL libc_envz_remove)(char **__restrict penvz,
                                       size_t *__restrict penvz_len,
                                       char const *__restrict name) {
	char *entry;
	entry = libc_envz_entry(*penvz, *penvz_len, name);
	if (entry)
		libc_argz_delete(penvz, penvz_len, entry);
}
/* >> envz_strip(3)
 * Remove all entries from `penvz' that don't have a value-portion. */
INTERN ATTR_SECTION(".text.crt.string.envz") ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW_NCX(LIBCCALL libc_envz_strip)(char **__restrict penvz,
                                      size_t *__restrict penvz_len) {
	char *start, *ptr, *end;
	size_t oldlen, newlen;
	ptr = start = *penvz;
	end = ptr + (oldlen = *penvz_len);
	while (ptr < end) {
		char *next;
		size_t partlen;
		next = libc_strchrnul(ptr, '=');
		if (*next) {
			ptr = libc_strend(next) + 1;
			continue;
		}
		/* Remove this entry. */
		next = libc_strend(next) + 1;
		partlen = (size_t)(end - next);
		libc_memmovedownc(ptr, next, partlen, sizeof(char));
		end -= partlen;
	}
	newlen = (size_t)(end - start);
	if (newlen < oldlen) {
		*penvz_len = newlen;

		start = (char *)libc_realloc(start, newlen);
		if likely(start)
			*penvz = start;

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
