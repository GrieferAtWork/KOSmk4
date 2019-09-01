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
#ifndef GUARD_LIBC_USER_DOS_C
#define GUARD_LIBC_USER_DOS_C 1

#include "../api.h"
#include "dos.h"

#include <unistd.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:delay,hash:0xa7ad6627]]]*/
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.system.delay") void
NOTHROW_RPC(LIBCCALL libc_delay)(unsigned int mill)
/*[[[body:delay]]]*/
{
	usleep((useconds_t)mill * 1000);
}
/*[[[end:delay]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xaa7cd6eb]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(delay, libc_delay);
DEFINE_PUBLIC_WEAK_ALIAS(__crtSleep, libc_delay);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DOS_C */
