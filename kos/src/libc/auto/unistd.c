/* HASH 0x55c029ed */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_C
#define GUARD_LIBC_AUTO_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__limits.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.configuration.getpagesize") int
NOTHROW_NCX(LIBCCALL libc_getpagesize)(void) {
#line 1356 "kos/src/libc/magic/unistd.c"
#ifdef __SIZEOF_PAGE__
	return __SIZEOF_PAGE__;
#else
	return 4096;
#endif
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.configuration.getdtablesize") int
NOTHROW_NCX(LIBCCALL libc_getdtablesize)(void) {
#line 1367 "kos/src/libc/magic/unistd.c"
#if defined(__KOS__)
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else
	return 256;        /* UINT8_MAX + 1 */
#endif
}

/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.swab") void
NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from,
                                void *__restrict to,
                                int n_bytes) {
#line 1630 "kos/src/libc/magic/unistd.c"
	n_bytes &= ~1;
	while (n_bytes >= 2) {
		byte_t a, b;
		a = ((byte_t *)from)[--n_bytes];
		b = ((byte_t *)from)[--n_bytes];
		((byte_t *)to)[n_bytes+0] = a;
		((byte_t *)to)[n_bytes+1] = b;
	}
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(getpagesize, libc_getpagesize);
DEFINE_PUBLIC_WEAK_ALIAS(getdtablesize, libc_getdtablesize);
DEFINE_PUBLIC_WEAK_ALIAS(swab, libc_swab);
DEFINE_PUBLIC_WEAK_ALIAS(_swab, libc_swab);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNISTD_C */
