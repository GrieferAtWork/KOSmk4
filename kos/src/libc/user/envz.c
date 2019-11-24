/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ENVZ_C
#define GUARD_LIBC_USER_ENVZ_C 1

#include "../api.h"
/**/

#include "envz.h"
#include "argz.h"
#include "string.h"
#include "stdlib.h"
#include "malloc.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:envz_add,hash:CRC-32=0x1a414c19]]]*/
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_add") error_t
NOTHROW_NCX(LIBCCALL libc_envz_add)(char **__restrict penvz,
                                    size_t *__restrict penvz_len,
                                    char const *__restrict name,
                                    char const *value)
/*[[[body:envz_add]]]*/
/*AUTO*/{
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
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
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
/*[[[end:envz_add]]]*/

/*[[[head:envz_remove,hash:CRC-32=0x798cad82]]]*/
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_remove") void
NOTHROW_NCX(LIBCCALL libc_envz_remove)(char **__restrict penvz,
                                       size_t *__restrict penvz_len,
                                       char const *__restrict name)
/*[[[body:envz_remove]]]*/
/*AUTO*/{
	char *entry;
	entry = libc_envz_entry(*penvz, *penvz_len, name);
	if (entry)
		libc_argz_delete(penvz, penvz_len, entry);
}
/*[[[end:envz_remove]]]*/

/*[[[head:envz_merge,hash:CRC-32=0x4f152cdf]]]*/
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_merge") error_t
NOTHROW_NCX(LIBCCALL libc_envz_merge)(char **__restrict penvz,
                                      size_t *__restrict penvz_len,
                                      char const *__restrict envz2,
                                      size_t envz2_len,
                                      int override_)
/*[[[body:envz_merge]]]*/
/*AUTO*/{
	error_t result = 0;
	while (envz2_len && result == 0) {
		char *existing = libc_envz_entry(*penvz, *penvz_len, envz2);
		size_t newlen  = libc_strlen(envz2) + 1;
		if (!existing)
			result = libc_argz_append(penvz, penvz_len, envz2, newlen);
		else if (override_) {
			libc_argz_delete(penvz, penvz_len, existing);
			result = libc_argz_append(penvz, penvz_len, envz2, newlen);
		}
		envz2     += newlen;
		envz2_len -= newlen;
	}
	return result;
}
/*[[[end:envz_merge]]]*/

/*[[[head:envz_strip,hash:CRC-32=0x51d57b26]]]*/
/* Remove entries that have no value attached */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_strip") void
NOTHROW_NCX(LIBCCALL libc_envz_strip)(char **__restrict penvz,
                                      size_t *__restrict penvz_len)
/*[[[body:envz_strip]]]*/
/*AUTO*/{
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
		memmovedownc(ptr, next, partlen, sizeof(char));
		end -= partlen;
	}
	newlen = (size_t)(end - start);
	if (newlen < oldlen) {
		*penvz_len = newlen;
#if defined(__CRT_HAVE_realloc)
		start = (char *)libc_realloc(start, newlen);
		if likely(start)
			*penvz = start;
#endif /* defined(__CRT_HAVE_realloc) */
	}
}
/*[[[end:envz_strip]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x66631882]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(envz_add, libc_envz_add);
DEFINE_PUBLIC_WEAK_ALIAS(envz_merge, libc_envz_merge);
DEFINE_PUBLIC_WEAK_ALIAS(envz_remove, libc_envz_remove);
DEFINE_PUBLIC_WEAK_ALIAS(envz_strip, libc_envz_strip);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ENVZ_C */
