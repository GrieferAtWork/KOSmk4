/* HASH CRC-32:0xfe48c8b4 */
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
#ifndef GUARD_LIBC_AUTO_MALLOC_C
#define GUARD_LIBC_AUTO_MALLOC_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "malloc.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility.malloc_trim") int
NOTHROW_NCX(LIBCCALL libc_malloc_trim)(size_t pad) {
#line 130 "kos/src/libc/magic/malloc.c"
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility.mallopt") int
NOTHROW_NCX(LIBCCALL libc_mallopt)(int parameter_number,
                                   int parameter_value) {
#line 148 "kos/src/libc/magic/malloc.c"
	/* NO-OP */
	COMPILER_IMPURE();
	(void)parameter_number;
	(void)parameter_value;
	return 0;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(malloc_trim, libc_malloc_trim);
DEFINE_PUBLIC_WEAK_ALIAS(mallopt, libc_mallopt);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MALLOC_C */
