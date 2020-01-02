/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_LIBC_USER_SYS_KLOG_C
#define GUARD_LIBC_USER_SYS_KLOG_C 1

#include "../api.h"
#include "sys.klog.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:klogctl,hash:CRC-32=0xd9345e8a]]]*/
/* Control the kernel's logging facility.  This corresponds exactly to
 * the kernel's syslog system call, but that name is easily confused
 * with the user-level syslog facility, which is something completely
 * different */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.klog.klogctl") int
NOTHROW_NCX(LIBCCALL libc_klogctl)(int type,
                                   char *bufp,
                                   int len)
/*[[[body:klogctl]]]*/
{
	(void)type;
	(void)bufp;
	(void)len;
	CRT_UNIMPLEMENTED("klogctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:klogctl]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xbc85017f]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(klogctl, libc_klogctl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_KLOG_C */
