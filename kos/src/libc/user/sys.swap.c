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
#ifndef GUARD_LIBC_USER_SYS_SWAP_C
#define GUARD_LIBC_USER_SYS_SWAP_C 1

#include "../api.h"
#include "sys.swap.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:swapon,hash:CRC-32=0xc3d67668]]]*/
/* @param swapflags: Set of `SWAP_FLAG_*' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.swap.swapon") int
NOTHROW_RPC(LIBCCALL libc_swapon)(char const *path,
                                  int swapflags)
/*[[[body:swapon]]]*/
{
	errno_t error;
	error = sys_swapon(path, (syscall_ulong_t)swapflags);
	return libc_seterrno_syserr(error);
}
/*[[[end:swapon]]]*/

/*[[[head:swapoff,hash:CRC-32=0x11430d9e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.swap.swapoff") int
NOTHROW_RPC(LIBCCALL libc_swapoff)(char const *path)
/*[[[body:swapoff]]]*/
{
	errno_t error;
	error = sys_swapoff(path);
	return libc_seterrno_syserr(error);
}
/*[[[end:swapoff]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x48eef5a1]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(swapon, libc_swapon);
DEFINE_PUBLIC_WEAK_ALIAS(swapoff, libc_swapoff);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SWAP_C */
