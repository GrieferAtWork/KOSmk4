/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_USTAT_C
#define GUARD_LIBC_USER_SYS_USTAT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.ustat.h"

DECL_BEGIN

/*[[[head:libc_ustat,hash:CRC-32=0xd4d821a1]]]*/
/* >> ustat(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_ustat)(dev_t dev,
                                 struct ustat *ubuf)
/*[[[body:libc_ustat]]]*/
{
	errno_t result = sys_ustat(dev, ubuf);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ustat]]]*/



#ifndef LINUX_USTAT_VERSION
#define LINUX_USTAT_VERSION 1 /* SVr4 */
#endif /* !LINUX_USTAT_VERSION */

DEFINE_PUBLIC_ALIAS(_xustat, libc__xustat); /* libc4/5 function */
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc__xustat)(int version, dev_t dev, struct ustat *ubuf) {
	if (version != LINUX_USTAT_VERSION)
		return libc_seterrno(EINVAL);
	return libc_ustat(dev, ubuf);
}




/*[[[start:exports,hash:CRC-32=0xb0725dbc]]]*/
DEFINE_PUBLIC_ALIAS_P(prev_ustat,libc_ustat,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(dev_t dev, struct ustat *ubuf),(dev,ubuf));
DEFINE_PUBLIC_ALIAS_P(__prev_ustat,libc_ustat,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(dev_t dev, struct ustat *ubuf),(dev,ubuf));
DEFINE_PUBLIC_ALIAS_P(__libc_prev_ustat,libc_ustat,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(dev_t dev, struct ustat *ubuf),(dev,ubuf));
DEFINE_PUBLIC_ALIAS_P(ustat,libc_ustat,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(dev_t dev, struct ustat *ubuf),(dev,ubuf));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_USTAT_C */
