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
#ifndef GUARD_LIBC_USER_SYS_CAPABILITY_C
#define GUARD_LIBC_USER_SYS_CAPABILITY_C 1

#include "../api.h"
/**/

#include "sys.capability.h"

DECL_BEGIN

/*[[[head:libc_capset,hash:CRC-32=0x6c587c32]]]*/
/* >> capset(2) */
INTERN ATTR_SECTION(".text.crt.capability") int
NOTHROW_NCX(LIBCCALL libc_capset)(cap_user_header_t header,
                                  cap_user_data_t data)
/*[[[body:libc_capset]]]*/
/*AUTO*/{
	(void)header;
	(void)data;
	CRT_UNIMPLEMENTEDF("capset(%p, %p)", header, data); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_capset]]]*/

/*[[[head:libc_capget,hash:CRC-32=0x4ed7f236]]]*/
/* >> capget(2) */
INTERN ATTR_SECTION(".text.crt.capability") int
NOTHROW_NCX(LIBCCALL libc_capget)(cap_user_header_t header,
                                  cap_user_data_t const data)
/*[[[body:libc_capget]]]*/
/*AUTO*/{
	(void)header;
	(void)data;
	CRT_UNIMPLEMENTEDF("capget(%p, %p)", header, data); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_capget]]]*/

/*[[[start:exports,hash:CRC-32=0x27cabb50]]]*/
DEFINE_PUBLIC_ALIAS(capset, libc_capset);
DEFINE_PUBLIC_ALIAS(capget, libc_capget);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_CAPABILITY_C */
