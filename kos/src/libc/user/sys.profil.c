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
#ifndef GUARD_LIBC_USER_SYS_PROFIL_C
#define GUARD_LIBC_USER_SYS_PROFIL_C 1

#include "../api.h"
/**/

#include "sys.profil.h"

DECL_BEGIN

/*[[[head:libc_sprofil,hash:CRC-32=0x7db977a5]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_sprofil)(struct prof *profp,
                                   int profcnt,
                                   struct timeval *tvp,
                                   unsigned int flags)
/*[[[body:libc_sprofil]]]*/
/*AUTO*/{
	(void)profp;
	(void)profcnt;
	(void)tvp;
	(void)flags;
	CRT_UNIMPLEMENTEDF("sprofil(profp: %p, profcnt: %x, tvp: %p, flags: %x)", profp, profcnt, tvp, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_sprofil]]]*/

/*[[[start:exports,hash:CRC-32=0xb8a98b5d]]]*/
DEFINE_PUBLIC_ALIAS(sprofil, libc_sprofil);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_PROFIL_C */
