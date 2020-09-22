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
#ifndef GUARD_LIBC_USER_ULIMIT_C
#define GUARD_LIBC_USER_ULIMIT_C 1

#include "../api.h"
#include "ulimit.h"

#include <kos/syscalls.h>
#include <limits.h>
#include <stdint.h>

#include <hybrid/host.h>
#include <hybrid/minmax.h>

DECL_BEGIN





/*[[[start:implementation]]]*/


/*[[[head:libc_ulimit,hash:CRC-32=0x9b432880]]]*/
/* @param: cmd: One OF `UL_*' */
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
#if defined(__x86_64__)
		result = (long int)(unsigned long)UINT64_C(0x0000ffffffffffff);
#elif defined(__i386__)
		result = (long int)(unsigned long)UINT32_C(0xbfffffff);
#else
#warning "Unsupported architecture"
		result = (long)libc_seterrno(ENOSYS);
#endif
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

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x2e8d7197]]]*/
DEFINE_PUBLIC_ALIAS(ulimit, libc_ulimit);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ULIMIT_C */
