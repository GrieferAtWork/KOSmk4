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
#ifndef GUARD_LIBC_USER_SYS_USTAT_C
#define GUARD_LIBC_USER_SYS_USTAT_C 1

#include "../api.h"
#include "sys.ustat.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:ustat,hash:CRC-32=0x7e56b8b1]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ustat") int
NOTHROW_NCX(LIBCCALL libc_ustat)(dev_t dev,
                                 struct ustat *ubuf)
/*[[[body:ustat]]]*/
{
	errno_t result;
	result = sys_ustat(dev, ubuf);
	return libc_seterrno_syserr(result);
}
/*[[[end:ustat]]]*/

/*[[[end:implementation]]]*/

/*[[[start:exports,hash:CRC-32=0xe88b8b47]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(ustat, libc_ustat);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_USTAT_C */
