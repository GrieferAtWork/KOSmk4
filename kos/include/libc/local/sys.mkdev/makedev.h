/* HASH CRC-32:0xbd5a86aa */
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
#ifndef __local_makedev_defined
#define __local_makedev_defined
#include <__crt.h>
#include <asm/os/mkdev.h>
#ifdef __MKDEV_CURRENT_VERSION
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(makedev) __ATTR_CONST __ATTR_WUNUSED __dev_t
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(makedev))(__major_t __maj, __minor_t __min) {
	return ((__dev_t)__maj << __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) |
	       ((__dev_t)__min << __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_makedev_defined
#define __local___localdep_makedev_defined
#define __localdep_makedev __LIBC_LOCAL_NAME(makedev)
#endif /* !__local___localdep_makedev_defined */
#else /* __MKDEV_CURRENT_VERSION */
#undef __local_makedev_defined
#endif /* !__MKDEV_CURRENT_VERSION */
#endif /* !__local_makedev_defined */
