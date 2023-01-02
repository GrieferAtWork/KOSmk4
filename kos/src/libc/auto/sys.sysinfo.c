/* HASH CRC-32:0x71ee7bc5 */
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
#ifndef GUARD_LIBC_AUTO_SYS_SYSINFO_C
#define GUARD_LIBC_AUTO_SYS_SYSINFO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.sysinfo.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <linux/sysinfo.h>
/* >> get_phys_pages(3)
 * Return the total # of pages of physical memory */
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED intptr_t
NOTHROW(LIBCCALL libc_get_phys_pages)(void) {
	struct sysinfo info;
	uintptr_t result;
	size_t ps;
	if (libc_sysinfo(&info))
		return -1;
	ps = libc_getpagesize();
	while (info.mem_unit > 1 && ps > 1) {
		info.mem_unit >>= 1;
		ps >>= 1;
	}
	result = (uintptr_t)info.totalram *
	         (uintptr_t)info.mem_unit;
	while (ps > 1) {
		result >>= 1;
		ps >>= 1;
	}
	return (intptr_t)result;
}
#include <linux/sysinfo.h>
/* >> get_avphys_pages(3)
 * Return the total # of free pages of physical memory */
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED intptr_t
NOTHROW(LIBCCALL libc_get_avphys_pages)(void) {
	struct sysinfo info;
	uintptr_t result;
	size_t ps;
	if (libc_sysinfo(&info))
		return -1;
	ps = libc_getpagesize();
	while (info.mem_unit > 1 && ps > 1) {
		info.mem_unit >>= 1;
		ps >>= 1;
	}
	result = (uintptr_t)info.freeram *
	         (uintptr_t)info.mem_unit;
	while (ps > 1) {
		result >>= 1;
		ps >>= 1;
	}
	return (intptr_t)result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(get_phys_pages, libc_get_phys_pages);
DEFINE_PUBLIC_ALIAS(get_avphys_pages, libc_get_avphys_pages);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_SYSINFO_C */
