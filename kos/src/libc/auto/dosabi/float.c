/* HASH CRC-32:0xead027fc */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DOSABI_FLOAT_C
#define GUARD_LIBC_AUTO_DOSABI_FLOAT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/float.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.math.float") uint32_t
NOTHROW_NCX(LIBDCALL libd__controlfp)(uint32_t newval,
                                      uint32_t mask) {
	return libc__controlfp(newval, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") void
NOTHROW_NCX(LIBDCALL libd__set_controlfp)(uint32_t newval,
                                          uint32_t mask) {
	libc__set_controlfp(newval, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") errno_t
NOTHROW_NCX(LIBDCALL libd__controlfp_s)(uint32_t *pcurrent,
                                        uint32_t newval,
                                        uint32_t mask) {
	return libc__controlfp_s(pcurrent, newval, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") void
NOTHROW_NCX(LIBDCALL libd__statusfp2)(uint32_t *x86_stat,
                                      uint32_t *sse2_stat) {
	libc__statusfp2(x86_stat, sse2_stat);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") uint32_t
NOTHROW_NCX(LIBDCALL libd__control87)(uint32_t newval,
                                      uint32_t mask) {
	return libc__control87(newval, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") int
NOTHROW_NCX(LIBDCALL libd___control87_2)(uint32_t newval,
                                         uint32_t mask,
                                         uint32_t *x86_control_word,
                                         uint32_t *sse2_control_word) {
	return libc___control87_2(newval, mask, x86_control_word, sse2_control_word);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd__chgsign)(double x) {
	return libc__chgsign(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.float") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd__fpclass)(double x) {
	return libc__fpclass(x);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_controlfp, libd__controlfp);
DEFINE_PUBLIC_ALIAS(DOS$_set_controlfp, libd__set_controlfp);
DEFINE_PUBLIC_ALIAS(DOS$_controlfp_s, libd__controlfp_s);
DEFINE_PUBLIC_ALIAS(DOS$_statusfp2, libd__statusfp2);
DEFINE_PUBLIC_ALIAS(DOS$_control87, libd__control87);
DEFINE_PUBLIC_ALIAS(DOS$__control87_2, libd___control87_2);
DEFINE_PUBLIC_ALIAS(DOS$_chgsign, libd__chgsign);
DEFINE_PUBLIC_ALIAS(DOS$_fpclass, libd__fpclass);

#endif /* !GUARD_LIBC_AUTO_DOSABI_FLOAT_C */
