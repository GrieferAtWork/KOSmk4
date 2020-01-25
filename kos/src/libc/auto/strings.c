/* HASH CRC-32:0x120f012b */
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
#ifndef GUARD_LIBC_AUTO_STRINGS_C
#define GUARD_LIBC_AUTO_STRINGS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "strings.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.bcopy") void
NOTHROW_NCX(LIBCCALL libc_bcopy)(void const *src,
                                 void *dst,
                                 size_t num_bytes) {
#line 41 "kos/src/libc/magic/strings.c"
	memmove(dst, src, num_bytes);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.bzero") void
NOTHROW_NCX(LIBCCALL libc_bzero)(void *__restrict dst,
                                 size_t num_bytes) {
#line 46 "kos/src/libc/magic/strings.c"
	memset(dst, 0, num_bytes);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.index") char *
NOTHROW_NCX(LIBCCALL libc_index)(char const *__restrict haystack,
                                 int needle) {
#line 61 "kos/src/libc/magic/strings.c"
	for (; *haystack; ++haystack) {
		if (*haystack == needle)
			return (char *)haystack;
	}
	if (!needle)
		return (char *)haystack;
	return NULL;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.rindex") char *
NOTHROW_NCX(LIBCCALL libc_rindex)(char const *__restrict haystack,
                                  int needle) {
#line 75 "kos/src/libc/magic/strings.c"
	char const *result = NULL;
	for (; *haystack; ++haystack) {
		if (*haystack == needle)
			result = haystack;
	}
	if (!needle)
		return (char *)haystack;
	return (char *)result;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(bcopy, libc_bcopy);
DEFINE_PUBLIC_WEAK_ALIAS(bzero, libc_bzero);
DEFINE_PUBLIC_WEAK_ALIAS(__bzero, libc_bzero);
DEFINE_PUBLIC_WEAK_ALIAS(index, libc_index);
DEFINE_PUBLIC_WEAK_ALIAS(rindex, libc_rindex);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRINGS_C */
