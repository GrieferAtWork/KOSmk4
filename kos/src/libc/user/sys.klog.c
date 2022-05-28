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
#ifndef GUARD_LIBC_USER_SYS_KLOG_C
#define GUARD_LIBC_USER_SYS_KLOG_C 1

#include "../api.h"
#include "sys.klog.h"

DECL_BEGIN

/*[[[head:libc_klogctl,hash:CRC-32=0xb4e5d19]]]*/
INTERN ATTR_SECTION(".text.crt.utility.klog") int
NOTHROW_NCX(LIBCCALL libc_klogctl)(__STDC_INT_AS_UINT_T type,
                                   char *bufp,
                                   __STDC_INT_AS_SIZE_T len)
/*[[[body:libc_klogctl]]]*/
/*AUTO*/{
	(void)type;
	(void)bufp;
	(void)len;
	CRT_UNIMPLEMENTEDF("klogctl(%x, %q, %x)", type, bufp, len); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_klogctl]]]*/





/*[[[start:exports,hash:CRC-32=0x7159d9e]]]*/
DEFINE_PUBLIC_ALIAS(klogctl, libc_klogctl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_KLOG_C */
