/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ULIMIT_C
#define GUARD_LIBC_USER_ULIMIT_C 1

#include "../api.h"
/**/

#include <hybrid/host.h>
#include <hybrid/minmax.h>

#include <kos/kernel/paging.h>
#include <kos/syscalls.h>

#include <limits.h>
#include <stdint.h>

#include "ulimit.h"

DECL_BEGIN

/*[[[head:libc_ulimit,hash:CRC-32=0x2d1ef6b5]]]*/
/* >> ulimit(2)
 * @param: cmd: One OF `UL_*' */
INTERN ATTR_SECTION(".text.crt.unsorted") longptr_t
NOTHROW_NCX(VLIBCCALL libc_ulimit)(__STDC_INT_AS_UINT_T cmd,
                                   ...)
/*[[[body:libc_ulimit]]]*/
{
	long int result;
	switch (cmd) {

	case UL_GETFSIZE:
		/* Return limit on the size of a file, in units of 512 bytes. */
		result = (long int)MIN((int64_t)LONG_MAX,
		                       (int64_t)((UINT64_MAX / 512) + 1));
		break;

	case UL_SETFSIZE:
		/* Set limit on the size of a file to second argument. */
		result = (long)libc_seterrno(EPERM);
		break;

	case __UL_GETMAXBRK:
		/* Return the maximum possible address of the data segment. */
		result = (long int)(unsigned long)(USERSPACE_END - 1);
		break;

	case __UL_GETOPENMAX:
		/* Return the maximum number of files that the calling process can open. */
		result = INT_MAX;
		break;

	default:
		result = (long)libc_seterrno(EINVAL);
		break;
	}
	return result;
}
/*[[[end:libc_ulimit]]]*/

/*[[[start:exports,hash:CRC-32=0x147fd897]]]*/
DEFINE_PUBLIC_ALIAS(__ulimit, libc_ulimit);
DEFINE_PUBLIC_ALIAS(ulimit, libc_ulimit);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ULIMIT_C */
