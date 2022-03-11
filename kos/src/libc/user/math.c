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
#ifndef GUARD_LIBC_USER_MATH_C
#define GUARD_LIBC_USER_MATH_C 1

#include "../api.h"
/**/

#include "math.h"

DECL_BEGIN

/*[[[head:libc_nextdown,hash:CRC-32=0x371d36cf]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW_NCX(LIBCCALL libc_nextdown)(double x)
/*[[[body:libc_nextdown]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("nextdown(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_nextdown]]]*/

/*[[[head:libc_nextup,hash:CRC-32=0x6de788a2]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW_NCX(LIBCCALL libc_nextup)(double x)
/*[[[body:libc_nextup]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("nextup(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_nextup]]]*/

/*[[[head:libc_llogb,hash:CRC-32=0x1845ed7f]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED long int
NOTHROW_NCX(LIBCCALL libc_llogb)(double x)
/*[[[body:libc_llogb]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("llogb(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_llogb]]]*/

/*[[[head:libc_roundeven,hash:CRC-32=0xd8baeb8f]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_roundeven)(double x)
/*[[[body:libc_roundeven]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("roundeven(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_roundeven]]]*/

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
	CRT_UNIMPLEMENTEDF("fromfp(%f, %x, %x)", x, round, width); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("ufromfp(%f, %x, %x)", x, round, width); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("fromfpx(%f, %x, %x)", x, round, width); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("ufromfpx(%f, %x, %x)", x, round, width); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ufromfpx]]]*/

/*[[[head:libc_fmaxmag,hash:CRC-32=0xc3a28404]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_fmaxmag)(double x,
                                   double y)
/*[[[body:libc_fmaxmag]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTEDF("fmaxmag(%f, %f)", x, y); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fmaxmag]]]*/

/*[[[head:libc_fminmag,hash:CRC-32=0x15e4f674]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_fminmag)(double x,
                                   double y)
/*[[[body:libc_fminmag]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTEDF("fminmag(%f, %f)", x, y); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fminmag]]]*/

/*[[[head:libc_canonicalize,hash:CRC-32=0xce61121e]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") int
NOTHROW_NCX(LIBCCALL libc_canonicalize)(double *cx,
                                        double const *x)
/*[[[body:libc_canonicalize]]]*/
/*AUTO*/{
	(void)cx;
	(void)x;
	CRT_UNIMPLEMENTEDF("canonicalize(%p, %p)", cx, x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_canonicalize]]]*/

/*[[[start:exports,hash:CRC-32=0x9550f5c8]]]*/
DEFINE_PUBLIC_ALIAS(nextdown, libc_nextdown);
DEFINE_PUBLIC_ALIAS(nextup, libc_nextup);
DEFINE_PUBLIC_ALIAS(llogb, libc_llogb);
DEFINE_PUBLIC_ALIAS(roundeven, libc_roundeven);
DEFINE_PUBLIC_ALIAS(fromfp, libc_fromfp);
DEFINE_PUBLIC_ALIAS(ufromfp, libc_ufromfp);
DEFINE_PUBLIC_ALIAS(fromfpx, libc_fromfpx);
DEFINE_PUBLIC_ALIAS(ufromfpx, libc_ufromfpx);
DEFINE_PUBLIC_ALIAS(fmaxmag, libc_fmaxmag);
DEFINE_PUBLIC_ALIAS(fminmag, libc_fminmag);
DEFINE_PUBLIC_ALIAS(canonicalize, libc_canonicalize);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_C */
