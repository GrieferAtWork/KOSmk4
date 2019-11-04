/* HASH CRC-32:0x4f107816 */
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
#ifndef GUARD_LIBC_AUTO_ENVZ_C
#define GUARD_LIBC_AUTO_ENVZ_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "envz.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
INTERN ATTR_PURE WUNUSED NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_entry") char *
NOTHROW_NCX(LIBCCALL libc_envz_entry)(char const *__restrict envz,
                                      size_t envz_len,
                                      char const *__restrict name) {
#line 63 "kos/src/libc/magic/envz.c"
	size_t namelen;
	char *envz_end = (char *)(envz + envz_len);
	namelen = libc_stroff(name, '=');
	while (envz < envz_end) {
		if (memcmp(envz, name, namelen) == 0 &&
		    (envz[namelen] == '\0' || envz[namelen] == '='))
			return (char *)envz; /* Found it! */
		envz = libc_strend(envz) + 1;
	}
	return NULL;
}

/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.string.envz.envz_get") char *
NOTHROW_NCX(LIBCCALL libc_envz_get)(char const *__restrict envz,
                                    size_t envz_len,
                                    char const *__restrict name) {
#line 82 "kos/src/libc/magic/envz.c"
	char *result;
	result = (char *)libc_envz_entry(envz, envz_len, name);
	if (result) {
		result = libc_strchr(result, '=');
		if (result)
			++result; /* Point to the value-portion */
	}
	return result;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(envz_entry, libc_envz_entry);
DEFINE_PUBLIC_WEAK_ALIAS(envz_get, libc_envz_get);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ENVZ_C */
