/* HASH CRC-32:0x80befded */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_VLIMIT_C
#define GUARD_LIBC_AUTO_SYS_VLIMIT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "sys.vlimit.h"
#include "../user/sys.resource.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/vlimit.h>
#include <asm/os/resource.h>
#include <bits/os/rlimit.h>
#include <libc/errno.h>
/* >> vlimit(3)
 * Ancient wrapper for `setrlimit(2)' (s.a. `struct rlimit::rlim_cur')
 * @param: resource: One of `LIM_*' (see above)
 * @param: value:    Value to assign to `resource'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_vlimit)(int resource,
                                  int value) {
	struct rlimit rlim;
	int rlimit_resource, result;
#ifdef __LIM_TO_RLIMIT
	rlimit_resource = __LIM_TO_RLIMIT(resource);
#else /* __LIM_TO_RLIMIT */
	switch (resource) {

#if defined(__LIM_CPU) && defined(__RLIMIT_CPU)
	case __LIM_CPU:
		rlimit_resource = __RLIMIT_CPU;
#endif /* __LIM_CPU && __RLIMIT_CPU */

#if defined(__LIM_FSIZE) && defined(__RLIMIT_FSIZE)
	case __LIM_FSIZE:
		rlimit_resource = __RLIMIT_FSIZE;
#endif /* __LIM_FSIZE && __RLIMIT_FSIZE */

#if defined(__LIM_DATA) && defined(__RLIMIT_DATA)
	case __LIM_DATA:
		rlimit_resource = __RLIMIT_DATA;
#endif /* __LIM_DATA && __RLIMIT_DATA */

#if defined(__LIM_STACK) && defined(__RLIMIT_STACK)
	case __LIM_STACK:
		rlimit_resource = __RLIMIT_STACK;
#endif /* __LIM_STACK && __RLIMIT_STACK */

#if defined(__LIM_CORE) && defined(__RLIMIT_CORE)
	case __LIM_CORE:
		rlimit_resource = __RLIMIT_CORE;
#endif /* __LIM_CORE && __RLIMIT_CORE */

#if defined(__LIM_MAXRSS) && defined(__RLIMIT_RSS)
	case __LIM_MAXRSS:
		rlimit_resource = __RLIMIT_RSS;
#endif /* __LIM_MAXRSS && __RLIMIT_RSS */

	default:

		return __libc_seterrno(EINVAL);



	}
#endif /* !__LIM_TO_RLIMIT */
	result = libc_getrlimit((__rlimit_resource_t)rlimit_resource, &rlim);
	if likely(result == 0) {
		rlim.rlim_cur = (__rlim_t)                     /* Cast to correct type. */
		                  (__CRT_PRIVATE_SINT(__SIZEOF_RLIM_T__)) /* Sign expansion... */
		                  (int)value;
		result = libc_setrlimit((__rlimit_resource_t)rlimit_resource, &rlim);
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(vlimit, libc_vlimit);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_VLIMIT_C */
