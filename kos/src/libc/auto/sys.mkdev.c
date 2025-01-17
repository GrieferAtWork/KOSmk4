/* HASH CRC-32:0x7bb0d418 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_MKDEV_C
#define GUARD_LIBC_AUTO_SYS_MKDEV_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "sys.mkdev.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED dev_t
NOTHROW(LIBCCALL libc_makedev)(major_t maj,
                               minor_t min) {
	return ((dev_t)maj << __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) |
	       ((dev_t)min << __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION));
}
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED major_t
NOTHROW(LIBCCALL libc_major)(dev_t dev) {
	return (major_t)(dev >> __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) &
	       (major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(__MKDEV_CURRENT_VERSION)) - 1);
}
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED minor_t
NOTHROW(LIBCCALL libc_minor)(dev_t dev) {
	return (minor_t)(dev >> __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION)) &
	       (minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(__MKDEV_CURRENT_VERSION)) - 1);
}
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED dev_t
NOTHROW(LIBCCALL libc___makedev)(int version,
                                 major_t maj,
                                 minor_t min) {
	(void)version;
	return ((dev_t)maj << __MKDEV_MAJOR_SHFT(version)) |
	       ((dev_t)min << __MKDEV_MINOR_SHFT(version));
}
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED major_t
NOTHROW(LIBCCALL libc___major)(int version,
                               dev_t dev) {
	(void)version;
	return (major_t)(dev >> __MKDEV_MAJOR_SHFT(version)) &
	       (major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(version)) - 1);
}
INTERN ATTR_SECTION(".text.crt.system.utility") ATTR_CONST WUNUSED minor_t
NOTHROW(LIBCCALL libc___minor)(int version,
                               dev_t dev) {
	(void)version;
	return (minor_t)(dev >> __MKDEV_MINOR_SHFT(version)) &
	       (minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(version)) - 1);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(gnu_dev_makedev,libc_makedev,ATTR_CONST WUNUSED,dev_t,NOTHROW,LIBCCALL,(major_t maj, minor_t min),(maj,min));
DEFINE_PUBLIC_ALIAS_P(makedev,libc_makedev,ATTR_CONST WUNUSED,dev_t,NOTHROW,LIBCCALL,(major_t maj, minor_t min),(maj,min));
DEFINE_PUBLIC_ALIAS_P(gnu_dev_major,libc_major,ATTR_CONST WUNUSED,major_t,NOTHROW,LIBCCALL,(dev_t dev),(dev));
DEFINE_PUBLIC_ALIAS_P(major,libc_major,ATTR_CONST WUNUSED,major_t,NOTHROW,LIBCCALL,(dev_t dev),(dev));
DEFINE_PUBLIC_ALIAS_P(gnu_dev_minor,libc_minor,ATTR_CONST WUNUSED,minor_t,NOTHROW,LIBCCALL,(dev_t dev),(dev));
DEFINE_PUBLIC_ALIAS_P(minor,libc_minor,ATTR_CONST WUNUSED,minor_t,NOTHROW,LIBCCALL,(dev_t dev),(dev));
DEFINE_PUBLIC_ALIAS_P(__makedev,libc___makedev,ATTR_CONST WUNUSED,dev_t,NOTHROW,LIBCCALL,(int version, major_t maj, minor_t min),(version,maj,min));
DEFINE_PUBLIC_ALIAS_P(__major,libc___major,ATTR_CONST WUNUSED,major_t,NOTHROW,LIBCCALL,(int version, dev_t dev),(version,dev));
DEFINE_PUBLIC_ALIAS_P(__minor,libc___minor,ATTR_CONST WUNUSED,minor_t,NOTHROW,LIBCCALL,(int version, dev_t dev),(version,dev));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_MKDEV_C */
