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
#ifndef GUARD_LIBC_USER_SYS_UTSNAME_C
#define GUARD_LIBC_USER_SYS_UTSNAME_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.utsname.h"

DECL_BEGIN

/*[[[head:libc_uname,hash:CRC-32=0x93405ee2]]]*/
/* >> uname(2)
 * Put information about the system in `name'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_uname)(struct utsname *name)
/*[[[body:libc_uname]]]*/
{
	errno_t result = sys_uname(name);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_uname]]]*/

/*[[[start:exports,hash:CRC-32=0xe2e9031d]]]*/
DEFINE_PUBLIC_ALIAS(__uname, libc_uname);
DEFINE_PUBLIC_ALIAS(__libc_uname, libc_uname);
DEFINE_PUBLIC_ALIAS(uname, libc_uname);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_UTSNAME_C */
