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

#include <limits.h>
#include <stdint.h>

#include "math.h"

DECL_BEGIN
















/*[[[head:libc_exp2,hash:CRC-32=0x33a7512]]]*/
/* >> exp2f(3), exp2(3), exp2l(3)
 * Compute base-2 exponential of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_exp2)(double x)
/*[[[body:libc_exp2]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("exp2(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_exp2]]]*/

/*[[[head:libc_log2,hash:CRC-32=0x73bb506f]]]*/
/* >> log2f(3), log2(3), log2l(3)
 * Compute base-2 logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log2)(double x)
/*[[[body:libc_log2]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("log2(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_log2]]]*/


/*[[[head:libc_erf,hash:CRC-32=0xd7c3b940]]]*/
/* >> erff(3), erf(3), erfl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_erf)(double x)
/*[[[body:libc_erf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("erf(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_erf]]]*/

/*[[[head:libc_erfc,hash:CRC-32=0xce96c7f8]]]*/
/* >> erfcf(3), erfc(3), erfcl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_erfc)(double x)
/*[[[body:libc_erfc]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("erfc(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_erfc]]]*/


/*[[[head:libc_tgamma,hash:CRC-32=0x5809c86d]]]*/
/* >> tgammaf(3), tgamma(3), tgammal(3)
 * True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_tgamma)(double x)
/*[[[body:libc_tgamma]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("tgamma(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_tgamma]]]*/




/*[[[head:libc_j0,hash:CRC-32=0x11322994]]]*/
/* >> j0f(3), j0(3), j0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j0)(double x)
/*[[[body:libc_j0]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("j0(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_j0]]]*/

/*[[[head:libc_j1,hash:CRC-32=0x4171b981]]]*/
/* >> j1f(3), j1(3), j1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j1)(double x)
/*[[[body:libc_j1]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("j1(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_j1]]]*/

/*[[[head:libc_jn,hash:CRC-32=0x70531502]]]*/
/* >> jnf(3), jn(3), jnl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_jn)(int n,
                          double x)
/*[[[body:libc_jn]]]*/
/*AUTO*/{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTEDF("jn(%x, %f)", n, x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_jn]]]*/

/*[[[head:libc_y0,hash:CRC-32=0xc9cba8ec]]]*/
/* >> y0f(3), y0(3), y0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y0)(double x)
/*[[[body:libc_y0]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("y0(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_y0]]]*/

/*[[[head:libc_y1,hash:CRC-32=0x998838f9]]]*/
/* >> y1f(3), y1(3), y1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y1)(double x)
/*[[[body:libc_y1]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("y1(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_y1]]]*/

/*[[[head:libc_yn,hash:CRC-32=0x879fa852]]]*/
/* >> ynf(3), yn(3), ynl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_yn)(int n,
                          double x)
/*[[[body:libc_yn]]]*/
/*AUTO*/{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTEDF("yn(%x, %f)", n, x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_yn]]]*/






/*[[[start:exports,hash:CRC-32=0x505cd860]]]*/
DEFINE_PUBLIC_ALIAS(__exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(__log2, libc_log2);
DEFINE_PUBLIC_ALIAS(log2, libc_log2);
DEFINE_PUBLIC_ALIAS(__erf, libc_erf);
DEFINE_PUBLIC_ALIAS(erf, libc_erf);
DEFINE_PUBLIC_ALIAS(__erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(__tgamma, libc_tgamma);
DEFINE_PUBLIC_ALIAS(tgamma, libc_tgamma);
DEFINE_PUBLIC_ALIAS(__j0, libc_j0);
DEFINE_PUBLIC_ALIAS(j0, libc_j0);
DEFINE_PUBLIC_ALIAS(__j1, libc_j1);
DEFINE_PUBLIC_ALIAS(j1, libc_j1);
DEFINE_PUBLIC_ALIAS(__jn, libc_jn);
DEFINE_PUBLIC_ALIAS(jn, libc_jn);
DEFINE_PUBLIC_ALIAS(__y0, libc_y0);
DEFINE_PUBLIC_ALIAS(y0, libc_y0);
DEFINE_PUBLIC_ALIAS(__y1, libc_y1);
DEFINE_PUBLIC_ALIAS(y1, libc_y1);
DEFINE_PUBLIC_ALIAS(__yn, libc_yn);
DEFINE_PUBLIC_ALIAS(yn, libc_yn);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_C */
