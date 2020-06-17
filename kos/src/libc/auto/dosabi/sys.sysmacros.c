/* HASH CRC-32:0xf3933d62 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_SYSMACROS_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_SYSMACROS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../sys.sysmacros.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.system.utility") ATTR_CONST WUNUSED major_t
NOTHROW(LIBDCALL libd_gnu_dev_major)(dev_t dev) {
	return libc_gnu_dev_major(dev);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") ATTR_CONST WUNUSED minor_t
NOTHROW(LIBDCALL libd_gnu_dev_minor)(dev_t dev) {
	return libc_gnu_dev_minor(dev);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") ATTR_CONST WUNUSED dev_t
NOTHROW(LIBDCALL libd_gnu_dev_makedev)(major_t major,
                                       minor_t minor) {
	return libc_gnu_dev_makedev(major, minor);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_major, libd_gnu_dev_major);
DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_minor, libd_gnu_dev_minor);
DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_makedev, libd_gnu_dev_makedev);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_SYSMACROS_C */
