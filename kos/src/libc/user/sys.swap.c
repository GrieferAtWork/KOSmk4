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
#ifndef GUARD_LIBC_USER_SYS_SWAP_C
#define GUARD_LIBC_USER_SYS_SWAP_C 1

#include "../api.h"
#include "sys.swap.h"
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_swapon,hash:CRC-32=0xbbdb3510]]]*/
/* >> swapon(2)
 * @param swapflags: Set of `SWAP_FLAG_*' */
INTERN ATTR_SECTION(".text.crt.fs.swap") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_swapon)(char const *path,
                                  __STDC_INT_AS_UINT_T swapflags)
/*[[[body:libc_swapon]]]*/
{
	errno_t error;
	error = sys_swapon(path, (syscall_ulong_t)swapflags);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_swapon]]]*/

/*[[[head:libc_swapoff,hash:CRC-32=0xc33f3bee]]]*/
/* >> swapoff(2) */
INTERN ATTR_SECTION(".text.crt.fs.swap") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_swapoff)(char const *path)
/*[[[body:libc_swapoff]]]*/
{
	errno_t error;
	error = sys_swapoff(path);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_swapoff]]]*/





/*[[[start:exports,hash:CRC-32=0xb074c8f7]]]*/
DEFINE_PUBLIC_ALIAS(swapon, libc_swapon);
DEFINE_PUBLIC_ALIAS(__swapon, libc_swapon);
DEFINE_PUBLIC_ALIAS(__libc_swapon, libc_swapon);
DEFINE_PUBLIC_ALIAS(swapon, libc_swapon);
DEFINE_PUBLIC_ALIAS(swapoff, libc_swapoff);
DEFINE_PUBLIC_ALIAS(__swapoff, libc_swapoff);
DEFINE_PUBLIC_ALIAS(__libc_swapoff, libc_swapoff);
DEFINE_PUBLIC_ALIAS(swapoff, libc_swapoff);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SWAP_C */
