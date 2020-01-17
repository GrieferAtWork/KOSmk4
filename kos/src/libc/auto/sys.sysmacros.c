/* HASH CRC-32:0x6bb03b40 */
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
#ifndef GUARD_LIBC_AUTO_SYS_SYSMACROS_C
#define GUARD_LIBC_AUTO_SYS_SYSMACROS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "sys.sysmacros.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.utility.gnu_dev_major") major_t
NOTHROW(LIBCCALL libc_gnu_dev_major)(dev_t dev) {
#line 38 "kos/src/libc/magic/sys.sysmacros.c"
	return (major_t)((uintptr_t)dev >> 20);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.utility.gnu_dev_minor") minor_t
NOTHROW(LIBCCALL libc_gnu_dev_minor)(dev_t dev) {
#line 43 "kos/src/libc/magic/sys.sysmacros.c"
	return (minor_t)((uintptr_t)dev & ((1 << 20) - 1));
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.utility.gnu_dev_makedev") dev_t
NOTHROW(LIBCCALL libc_gnu_dev_makedev)(major_t major,
                                       minor_t minor) {
#line 48 "kos/src/libc/magic/sys.sysmacros.c"
	return (dev_t)major << 20 | (dev_t)minor;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(gnu_dev_major, libc_gnu_dev_major);
DEFINE_PUBLIC_WEAK_ALIAS(gnu_dev_minor, libc_gnu_dev_minor);
DEFINE_PUBLIC_WEAK_ALIAS(gnu_dev_makedev, libc_gnu_dev_makedev);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_SYSMACROS_C */
