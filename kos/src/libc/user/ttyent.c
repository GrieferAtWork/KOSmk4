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
#ifndef GUARD_LIBC_USER_TTYENT_C
#define GUARD_LIBC_USER_TTYENT_C 1

#include "../api.h"
/**/

#include "ttyent.h"

DECL_BEGIN

/*[[[head:libc_getttyent,hash:CRC-32=0xf603834f]]]*/
/* >> getttyent(3) */
INTERN ATTR_SECTION(".text.crt.database.utmpx") struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttyent)(void)
/*[[[body:libc_getttyent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getttyent]]]*/

/*[[[head:libc_getttynam,hash:CRC-32=0xabd64183]]]*/
/* >> getttynam(3) */
INTERN ATTR_SECTION(".text.crt.database.utmpx") ATTR_IN(1) struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttynam)(char const *tty)
/*[[[body:libc_getttynam]]]*/
/*AUTO*/{
	(void)tty;
	CRT_UNIMPLEMENTEDF("getttynam(%q)", tty); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getttynam]]]*/

/*[[[head:libc_setttyent,hash:CRC-32=0x855393c]]]*/
/* >> setttyent(3) */
INTERN ATTR_SECTION(".text.crt.database.utmpx") int
NOTHROW_RPC_KOS(LIBCCALL libc_setttyent)(void)
/*[[[body:libc_setttyent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setttyent]]]*/

/*[[[head:libc_endttyent,hash:CRC-32=0x18249120]]]*/
/* >> endttyent(3) */
INTERN ATTR_SECTION(".text.crt.database.utmpx") int
NOTHROW_NCX(LIBCCALL libc_endttyent)(void)
/*[[[body:libc_endttyent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_endttyent]]]*/





/*[[[start:exports,hash:CRC-32=0xe8fc5230]]]*/
DEFINE_PUBLIC_ALIAS(getttyent, libc_getttyent);
DEFINE_PUBLIC_ALIAS(getttynam, libc_getttynam);
DEFINE_PUBLIC_ALIAS(setttyent, libc_setttyent);
DEFINE_PUBLIC_ALIAS(endttyent, libc_endttyent);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TTYENT_C */
