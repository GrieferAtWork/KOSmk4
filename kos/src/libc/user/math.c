/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MATH_C
#define GUARD_LIBC_USER_MATH_C 1

#include "../api.h"
/**/

#include "math.h"

DECL_BEGIN





/*[[[head:libc_fromfp,hash:CRC-32=0xf1b85af2]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfp)(double x,
                                  int round,
                                  unsigned int width)
/*[[[body:libc_fromfp]]]*/
/*AUTO*/{
	(void)x;
	(void)round;
	(void)width;
	CRT_UNIMPLEMENTEDF("fromfp(x: %f, round: %x, width: %x)", x, round, width); /* TODO */
	return (intmax_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_fromfp]]]*/

/*[[[head:libc_ufromfp,hash:CRC-32=0xad768598]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfp)(double x,
                                   int round,
                                   unsigned int width)
/*[[[body:libc_ufromfp]]]*/
/*AUTO*/{
	(void)x;
	(void)round;
	(void)width;
	CRT_UNIMPLEMENTEDF("ufromfp(x: %f, round: %x, width: %x)", x, round, width); /* TODO */
	return (uintmax_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_ufromfp]]]*/

/*[[[head:libc_fromfpx,hash:CRC-32=0x6a22dee0]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfpx)(double x,
                                   int round,
                                   unsigned int width)
/*[[[body:libc_fromfpx]]]*/
/*AUTO*/{
	(void)x;
	(void)round;
	(void)width;
	CRT_UNIMPLEMENTEDF("fromfpx(x: %f, round: %x, width: %x)", x, round, width); /* TODO */
	return (intmax_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_fromfpx]]]*/

/*[[[head:libc_ufromfpx,hash:CRC-32=0x2f735a6d]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfpx)(double x,
                                    int round,
                                    unsigned int width)
/*[[[body:libc_ufromfpx]]]*/
/*AUTO*/{
	(void)x;
	(void)round;
	(void)width;
	CRT_UNIMPLEMENTEDF("ufromfpx(x: %f, round: %x, width: %x)", x, round, width); /* TODO */
	return (uintmax_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_ufromfpx]]]*/




/*[[[start:exports,hash:CRC-32=0xeb4bef0d]]]*/
DEFINE_PUBLIC_ALIAS(fromfp, libc_fromfp);
DEFINE_PUBLIC_ALIAS(ufromfp, libc_ufromfp);
DEFINE_PUBLIC_ALIAS(fromfpx, libc_fromfpx);
DEFINE_PUBLIC_ALIAS(ufromfpx, libc_ufromfpx);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_C */
