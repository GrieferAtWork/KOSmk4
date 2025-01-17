/* HASH CRC-32:0xa17bd1aa */
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
#ifndef GUARD_LIBC_AUTO_FLOAT_C
#define GUARD_LIBC_AUTO_FLOAT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/float.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.math.float") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpe_flt_rounds)(void) {
	return 1;
}
#include <fpu_control.h>
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval,
                                      uint32_t mask) {
	fpu_control_t result;
	_FPU_GETCW(result);
#if defined(_FPU_RESERVED) && _FPU_RESERVED
	mask &= ~_FPU_RESERVED; /* Don't allow modification of reserved words. */
#endif /* _FPU_RESERVED && _FPU_RESERVED */
	if (mask) {
		fpu_control_t newword;
		newword = result;
		newword &= ~mask;
		newword = newval & mask;
		_FPU_SETCW(newword);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval,
                                          uint32_t mask) {
	libc__controlfp(newval, mask);
}
INTERN ATTR_SECTION(".text.crt.math.float") errno_t
NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent,
                                        uint32_t newval,
                                        uint32_t mask) {
	uint32_t st = libc__controlfp(newval, mask);
	if (pcurrent)
		*pcurrent = st;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval,
                                      uint32_t mask) {
	return libc__controlfp(newval, mask);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__fpe_flt_rounds,libc___fpe_flt_rounds,ATTR_CONST WUNUSED,int,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_controlfp,libc__controlfp,,uint32_t,NOTHROW_NCX,LIBCCALL,(uint32_t newval, uint32_t mask),(newval,mask));
DEFINE_PUBLIC_ALIAS_P_VOID(_set_controlfp,libc__set_controlfp,,NOTHROW_NCX,LIBCCALL,(uint32_t newval, uint32_t mask),(newval,mask));
DEFINE_PUBLIC_ALIAS_P(_controlfp_s,libc__controlfp_s,,errno_t,NOTHROW_NCX,LIBCCALL,(uint32_t *pcurrent, uint32_t newval, uint32_t mask),(pcurrent,newval,mask));
DEFINE_PUBLIC_ALIAS_P(_control87,libc__control87,,uint32_t,NOTHROW_NCX,LIBCCALL,(uint32_t newval, uint32_t mask),(newval,mask));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FLOAT_C */
