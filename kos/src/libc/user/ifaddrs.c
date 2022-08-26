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
#ifndef GUARD_LIBC_USER_IFADDRS_C
#define GUARD_LIBC_USER_IFADDRS_C 1

#include "../api.h"
#include "ifaddrs.h"

DECL_BEGIN

/*[[[head:libc_getifaddrs,hash:CRC-32=0x8515e015]]]*/
/* >> getifaddrs(3) */
INTERN ATTR_SECTION(".text.crt.unsorted") int
NOTHROW_NCX(LIBCCALL libc_getifaddrs)(struct ifaddrs **ifap)
/*[[[body:libc_getifaddrs]]]*/
/*AUTO*/{
	(void)ifap;
	CRT_UNIMPLEMENTEDF("getifaddrs(ifap: %p)", ifap); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getifaddrs]]]*/

/*[[[head:libc_freeifaddrs,hash:CRC-32=0xbbd2a106]]]*/
/* >> freeifaddrs(3) */
INTERN ATTR_SECTION(".text.crt.unsorted") void
NOTHROW_NCX(LIBCCALL libc_freeifaddrs)(struct ifaddrs *ifa)
/*[[[body:libc_freeifaddrs]]]*/
/*AUTO*/{
	(void)ifa;
	CRT_UNIMPLEMENTEDF("freeifaddrs(ifa: %p)", ifa); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_freeifaddrs]]]*/





/*[[[start:exports,hash:CRC-32=0x50e02489]]]*/
DEFINE_PUBLIC_ALIAS(getifaddrs, libc_getifaddrs);
DEFINE_PUBLIC_ALIAS(freeifaddrs, libc_freeifaddrs);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_IFADDRS_C */
