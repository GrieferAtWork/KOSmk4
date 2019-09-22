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
#ifndef GUARD_LIBC_USER_SGTTY_C
#define GUARD_LIBC_USER_SGTTY_C 1

#include "../api.h"
#include "sgtty.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:gtty,hash:CRC-32=0xdfabfd4e]]]*/
/* Fill in *PARAMS with terminal parameters associated with FD */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.gtty") int
NOTHROW_NCX(LIBCCALL libc_gtty)(fd_t fd,
                                struct sgttyb *params)
/*[[[body:gtty]]]*/
{
	CRT_UNIMPLEMENTED("gtty"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gtty]]]*/

/*[[[head:stty,hash:CRC-32=0x91e6970d]]]*/
/* Set the terminal parameters associated with FD to *PARAMS */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.stty") int
NOTHROW_NCX(LIBCCALL libc_stty)(fd_t fd,
                                struct sgttyb const *params)
/*[[[body:stty]]]*/
{
	CRT_UNIMPLEMENTED("stty"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:stty]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x27273b1]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(gtty, libc_gtty);
DEFINE_PUBLIC_WEAK_ALIAS(stty, libc_stty);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SGTTY_C */
