/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_TTYENT_C
#define GUARD_LIBC_USER_TTYENT_C 1

#include "../api.h"
#include "ttyent.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getttyent,hash:CRC-32=0xacd058f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getttyent") struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttyent)(void)
/*[[[body:getttyent]]]*/
{
	CRT_UNIMPLEMENTED("getttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getttyent]]]*/

/*[[[head:getttynam,hash:CRC-32=0xf75ae736]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getttynam") struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttynam)(char const *tty)
/*[[[body:getttynam]]]*/
{
	(void)tty;
	CRT_UNIMPLEMENTED("getttynam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getttynam]]]*/

/*[[[head:setttyent,hash:CRC-32=0xd671f5ae]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.setttyent") int
NOTHROW_RPC_KOS(LIBCCALL libc_setttyent)(void)
/*[[[body:setttyent]]]*/
{
	CRT_UNIMPLEMENTED("setttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setttyent]]]*/

/*[[[head:endttyent,hash:CRC-32=0xa6a6312b]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.endttyent") int
NOTHROW_RPC_KOS(LIBCCALL libc_endttyent)(void)
/*[[[body:endttyent]]]*/
{
	CRT_UNIMPLEMENTED("endttyent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:endttyent]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x6e8a6eb0]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getttyent, libc_getttyent);
DEFINE_PUBLIC_WEAK_ALIAS(getttynam, libc_getttynam);
DEFINE_PUBLIC_WEAK_ALIAS(setttyent, libc_setttyent);
DEFINE_PUBLIC_WEAK_ALIAS(endttyent, libc_endttyent);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TTYENT_C */
