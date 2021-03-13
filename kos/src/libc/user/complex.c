/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_COMPLEX_C
#define GUARD_LIBC_USER_COMPLEX_C 1

#include "../api.h"
/**/

#include "complex.h"

DECL_BEGIN

/*[[[head:libc_cacosf,hash:CRC-32=0x1b91e661]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_cacosf)(float _Complex x)
/*[[[body:libc_cacosf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacosf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacosf]]]*/

/*[[[head:libc_casinf,hash:CRC-32=0xd20d70a7]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_casinf)(float _Complex x)
/*[[[body:libc_casinf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casinf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casinf]]]*/

/*[[[head:libc_catanf,hash:CRC-32=0xe3ac04f6]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_catanf)(float _Complex x)
/*[[[body:libc_catanf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catanf]]]*/

/*[[[head:libc_ccosf,hash:CRC-32=0x307e763d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_ccosf)(float _Complex x)
/*[[[body:libc_ccosf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccosf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccosf]]]*/

/*[[[head:libc_csinf,hash:CRC-32=0xf9e2e0fb]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_csinf)(float _Complex x)
/*[[[body:libc_csinf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csinf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csinf]]]*/

/*[[[head:libc_ctanf,hash:CRC-32=0xc84394aa]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_ctanf)(float _Complex x)
/*[[[body:libc_ctanf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctanf]]]*/

/*[[[head:libc_cacoshf,hash:CRC-32=0x7a51356a]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_cacoshf)(float _Complex x)
/*[[[body:libc_cacoshf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacoshf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacoshf]]]*/

/*[[[head:libc_casinhf,hash:CRC-32=0x89fce79]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_casinhf)(float _Complex x)
/*[[[body:libc_casinhf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casinhf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casinhf]]]*/

/*[[[head:libc_catanhf,hash:CRC-32=0x14c20e6f]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_catanhf)(float _Complex x)
/*[[[body:libc_catanhf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catanhf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catanhf]]]*/

/*[[[head:libc_ccoshf,hash:CRC-32=0x18a7c725]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_ccoshf)(float _Complex x)
/*[[[body:libc_ccoshf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccoshf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccoshf]]]*/

/*[[[head:libc_csinhf,hash:CRC-32=0x6a693c36]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_csinhf)(float _Complex x)
/*[[[body:libc_csinhf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csinhf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csinhf]]]*/

/*[[[head:libc_ctanhf,hash:CRC-32=0x7634fc20]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_ctanhf)(float _Complex x)
/*[[[body:libc_ctanhf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctanhf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctanhf]]]*/

/*[[[head:libc_cexpf,hash:CRC-32=0xcef097cf]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_cexpf)(float _Complex x)
/*[[[body:libc_cexpf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cexpf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cexpf]]]*/

/*[[[head:libc_clogf,hash:CRC-32=0x263da4b5]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_clogf)(float _Complex x)
/*[[[body:libc_clogf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("clogf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clogf]]]*/

/*[[[head:libc_cabsf,hash:CRC-32=0x7bf1cf0c]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float
NOTHROW_NCX(LIBCCALL libc_cabsf)(float _Complex x)
/*[[[body:libc_cabsf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cabsf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cabsf]]]*/

/*[[[head:libc_cpowf,hash:CRC-32=0x817c457b]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_cpowf)(float _Complex x,
                                 float _Complex y)
/*[[[body:libc_cpowf]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTED("cpowf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cpowf]]]*/

/*[[[head:libc_csqrtf,hash:CRC-32=0x8a8de40d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_csqrtf)(float _Complex x)
/*[[[body:libc_csqrtf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csqrtf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csqrtf]]]*/

/*[[[head:libc_cargf,hash:CRC-32=0x8fd59001]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float
NOTHROW_NCX(LIBCCALL libc_cargf)(float _Complex x)
/*[[[body:libc_cargf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cargf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cargf]]]*/

/*[[[head:libc_cimagf,hash:CRC-32=0xb6529d3d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float
NOTHROW_NCX(LIBCCALL libc_cimagf)(float _Complex x)
/*[[[body:libc_cimagf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cimagf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cimagf]]]*/

/*[[[head:libc_conjf,hash:CRC-32=0x179a3689]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_conjf)(float _Complex x)
/*[[[body:libc_conjf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("conjf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_conjf]]]*/

/*[[[head:libc_cprojf,hash:CRC-32=0x1fdf439a]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float _Complex
NOTHROW_NCX(LIBCCALL libc_cprojf)(float _Complex x)
/*[[[body:libc_cprojf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cprojf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cprojf]]]*/

/*[[[head:libc_crealf,hash:CRC-32=0xa5952849]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") float
NOTHROW_NCX(LIBCCALL libc_crealf)(float _Complex x)
/*[[[body:libc_crealf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("crealf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_crealf]]]*/

/*[[[head:libc_cacos,hash:CRC-32=0x119234a2]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_cacos)(double _Complex x)
/*[[[body:libc_cacos]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacos"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacos]]]*/

/*[[[head:libc_casin,hash:CRC-32=0xd80ea264]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_casin)(double _Complex x)
/*[[[body:libc_casin]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casin"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casin]]]*/

/*[[[head:libc_catan,hash:CRC-32=0xe9afd635]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_catan)(double _Complex x)
/*[[[body:libc_catan]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catan"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catan]]]*/

/*[[[head:libc_ccos,hash:CRC-32=0x8333eff7]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_ccos)(double _Complex x)
/*[[[body:libc_ccos]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccos"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccos]]]*/

/*[[[head:libc_csin,hash:CRC-32=0x4aaf7931]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_csin)(double _Complex x)
/*[[[body:libc_csin]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csin"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csin]]]*/

/*[[[head:libc_ctan,hash:CRC-32=0x7b0e0d60]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_ctan)(double _Complex x)
/*[[[body:libc_ctan]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctan"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctan]]]*/

/*[[[head:libc_cacosh,hash:CRC-32=0x9371146]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_cacosh)(double _Complex x)
/*[[[body:libc_cacosh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacosh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacosh]]]*/

/*[[[head:libc_casinh,hash:CRC-32=0x7bf9ea55]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_casinh)(double _Complex x)
/*[[[body:libc_casinh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casinh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casinh]]]*/

/*[[[head:libc_catanh,hash:CRC-32=0x67a42a43]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_catanh)(double _Complex x)
/*[[[body:libc_catanh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catanh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catanh]]]*/

/*[[[head:libc_ccosh,hash:CRC-32=0x12a415e6]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_ccosh)(double _Complex x)
/*[[[body:libc_ccosh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccosh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccosh]]]*/

/*[[[head:libc_csinh,hash:CRC-32=0x606aeef5]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_csinh)(double _Complex x)
/*[[[body:libc_csinh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csinh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csinh]]]*/

/*[[[head:libc_ctanh,hash:CRC-32=0x7c372ee3]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_ctanh)(double _Complex x)
/*[[[body:libc_ctanh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctanh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctanh]]]*/

/*[[[head:libc_cexp,hash:CRC-32=0x7dbd0e05]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_cexp)(double _Complex x)
/*[[[body:libc_cexp]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cexp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cexp]]]*/

/*[[[head:libc_clog,hash:CRC-32=0x95703d7f]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_clog)(double _Complex x)
/*[[[body:libc_clog]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("clog"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clog]]]*/

/*[[[head:libc_cabs,hash:CRC-32=0x500d4da]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double
NOTHROW_NCX(LIBCCALL libc_cabs)(double _Complex x)
/*[[[body:libc_cabs]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cabs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cabs]]]*/

/*[[[head:libc_cpow,hash:CRC-32=0x576b3cb3]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_cpow)(double _Complex x,
                                double _Complex y)
/*[[[body:libc_cpow]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTED("cpow"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cpow]]]*/

/*[[[head:libc_csqrt,hash:CRC-32=0x808e36ce]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_csqrt)(double _Complex x)
/*[[[body:libc_csqrt]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csqrt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csqrt]]]*/

/*[[[head:libc_carg,hash:CRC-32=0xf1248bd7]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double
NOTHROW_NCX(LIBCCALL libc_carg)(double _Complex x)
/*[[[body:libc_carg]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("carg"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_carg]]]*/

/*[[[head:libc_cimag,hash:CRC-32=0xa89daf33]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double
NOTHROW_NCX(LIBCCALL libc_cimag)(double _Complex x)
/*[[[body:libc_cimag]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cimag"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cimag]]]*/

/*[[[head:libc_conj,hash:CRC-32=0xa4d7af43]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_conj)(double _Complex x)
/*[[[body:libc_conj]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("conj"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_conj]]]*/

/*[[[head:libc_cproj,hash:CRC-32=0x15dc9159]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double _Complex
NOTHROW_NCX(LIBCCALL libc_cproj)(double _Complex x)
/*[[[body:libc_cproj]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cproj"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cproj]]]*/

/*[[[head:libc_creal,hash:CRC-32=0xbb5a1a47]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") double
NOTHROW_NCX(LIBCCALL libc_creal)(double _Complex x)
/*[[[body:libc_creal]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("creal"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_creal]]]*/

/*[[[head:libc_cacosl,hash:CRC-32=0xbb1ba7e3]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_cacosl)(long double _Complex x)
/*[[[body:libc_cacosl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacosl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacosl]]]*/

/*[[[head:libc_casinl,hash:CRC-32=0x4b047b29]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_casinl)(long double _Complex x)
/*[[[body:libc_casinl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casinl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casinl]]]*/

/*[[[head:libc_catanl,hash:CRC-32=0x50fa17b3]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_catanl)(long double _Complex x)
/*[[[body:libc_catanl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catanl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catanl]]]*/

/*[[[head:libc_ccosl,hash:CRC-32=0xb4feb4df]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_ccosl)(long double _Complex x)
/*[[[body:libc_ccosl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccosl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccosl]]]*/

/*[[[head:libc_csinl,hash:CRC-32=0x44e16815]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_csinl)(long double _Complex x)
/*[[[body:libc_csinl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csinl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csinl]]]*/

/*[[[head:libc_ctanl,hash:CRC-32=0x5f1f048f]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_ctanl)(long double _Complex x)
/*[[[body:libc_ctanl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctanl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctanl]]]*/

/*[[[head:libc_cacoshl,hash:CRC-32=0x2b15699d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_cacoshl)(long double _Complex x)
/*[[[body:libc_cacoshl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cacoshl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cacoshl]]]*/

/*[[[head:libc_casinhl,hash:CRC-32=0x50545def]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_casinhl)(long double _Complex x)
/*[[[body:libc_casinhl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("casinhl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_casinhl]]]*/

/*[[[head:libc_catanhl,hash:CRC-32=0x4095d9d9]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_catanhl)(long double _Complex x)
/*[[[body:libc_catanhl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("catanhl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_catanhl]]]*/

/*[[[head:libc_ccoshl,hash:CRC-32=0x475f009]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_ccoshl)(long double _Complex x)
/*[[[body:libc_ccoshl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ccoshl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ccoshl]]]*/

/*[[[head:libc_csinhl,hash:CRC-32=0x7f34c47b]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_csinhl)(long double _Complex x)
/*[[[body:libc_csinhl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csinhl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csinhl]]]*/

/*[[[head:libc_ctanhl,hash:CRC-32=0x6ff5404d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_ctanhl)(long double _Complex x)
/*[[[body:libc_ctanhl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("ctanhl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ctanhl]]]*/

/*[[[head:libc_cexpl,hash:CRC-32=0x4bcc7d70]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_cexpl)(long double _Complex x)
/*[[[body:libc_cexpl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cexpl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cexpl]]]*/

/*[[[head:libc_clogl,hash:CRC-32=0x24222642]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_clogl)(long double _Complex x)
/*[[[body:libc_clogl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("clogl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clogl]]]*/

/*[[[head:libc_cabsl,hash:CRC-32=0xf7c2f9d8]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double
NOTHROW_NCX(LIBCCALL libc_cabsl)(long double _Complex x)
/*[[[body:libc_cabsl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cabsl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cabsl]]]*/

/*[[[head:libc_cpowl,hash:CRC-32=0x52e0919d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_cpowl)(long double _Complex x,
                                 long double _Complex y)
/*[[[body:libc_cpowl]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTED("cpowl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cpowl]]]*/

/*[[[head:libc_csqrtl,hash:CRC-32=0x58f30142]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_csqrtl)(long double _Complex x)
/*[[[body:libc_csqrtl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("csqrtl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_csqrtl]]]*/

/*[[[head:libc_cargl,hash:CRC-32=0x6c825179]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double
NOTHROW_NCX(LIBCCALL libc_cargl)(long double _Complex x)
/*[[[body:libc_cargl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cargl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cargl]]]*/

/*[[[head:libc_cimagl,hash:CRC-32=0x29588ca0]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double
NOTHROW_NCX(LIBCCALL libc_cimagl)(long double _Complex x)
/*[[[body:libc_cimagl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cimagl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cimagl]]]*/

/*[[[head:libc_conjl,hash:CRC-32=0x9493bff]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_conjl)(long double _Complex x)
/*[[[body:libc_conjl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("conjl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_conjl]]]*/

/*[[[head:libc_cprojl,hash:CRC-32=0x4bd90d]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double _Complex
NOTHROW_NCX(LIBCCALL libc_cprojl)(long double _Complex x)
/*[[[body:libc_cprojl]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("cprojl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_cprojl]]]*/

/*[[[head:libc_creall,hash:CRC-32=0x94368f85]]]*/
INTERN ATTR_SECTION(".text.crt.math.complex") long double
NOTHROW_NCX(LIBCCALL libc_creall)(long double _Complex x)
/*[[[body:libc_creall]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTED("creall"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_creall]]]*/

/*[[[start:exports,hash:CRC-32=0x7a7f2691]]]*/
DEFINE_PUBLIC_ALIAS(cabsf, libc_cabsf);
DEFINE_PUBLIC_ALIAS(cexpf, libc_cexpf);
DEFINE_PUBLIC_ALIAS(clogf, libc_clogf);
DEFINE_PUBLIC_ALIAS(cpowf, libc_cpowf);
DEFINE_PUBLIC_ALIAS(csqrtf, libc_csqrtf);
DEFINE_PUBLIC_ALIAS(csinf, libc_csinf);
DEFINE_PUBLIC_ALIAS(ccosf, libc_ccosf);
DEFINE_PUBLIC_ALIAS(ctanf, libc_ctanf);
DEFINE_PUBLIC_ALIAS(casinf, libc_casinf);
DEFINE_PUBLIC_ALIAS(cacosf, libc_cacosf);
DEFINE_PUBLIC_ALIAS(catanf, libc_catanf);
DEFINE_PUBLIC_ALIAS(csinhf, libc_csinhf);
DEFINE_PUBLIC_ALIAS(ccoshf, libc_ccoshf);
DEFINE_PUBLIC_ALIAS(ctanhf, libc_ctanhf);
DEFINE_PUBLIC_ALIAS(casinhf, libc_casinhf);
DEFINE_PUBLIC_ALIAS(cacoshf, libc_cacoshf);
DEFINE_PUBLIC_ALIAS(catanhf, libc_catanhf);
DEFINE_PUBLIC_ALIAS(cargf, libc_cargf);
DEFINE_PUBLIC_ALIAS(conjf, libc_conjf);
DEFINE_PUBLIC_ALIAS(crealf, libc_crealf);
DEFINE_PUBLIC_ALIAS(cimagf, libc_cimagf);
DEFINE_PUBLIC_ALIAS(cprojf, libc_cprojf);
DEFINE_PUBLIC_ALIAS(cabs, libc_cabs);
DEFINE_PUBLIC_ALIAS(cexp, libc_cexp);
DEFINE_PUBLIC_ALIAS(clog, libc_clog);
DEFINE_PUBLIC_ALIAS(cpow, libc_cpow);
DEFINE_PUBLIC_ALIAS(csqrt, libc_csqrt);
DEFINE_PUBLIC_ALIAS(csin, libc_csin);
DEFINE_PUBLIC_ALIAS(ccos, libc_ccos);
DEFINE_PUBLIC_ALIAS(ctan, libc_ctan);
DEFINE_PUBLIC_ALIAS(casin, libc_casin);
DEFINE_PUBLIC_ALIAS(cacos, libc_cacos);
DEFINE_PUBLIC_ALIAS(catan, libc_catan);
DEFINE_PUBLIC_ALIAS(csinh, libc_csinh);
DEFINE_PUBLIC_ALIAS(ccosh, libc_ccosh);
DEFINE_PUBLIC_ALIAS(ctanh, libc_ctanh);
DEFINE_PUBLIC_ALIAS(casinh, libc_casinh);
DEFINE_PUBLIC_ALIAS(cacosh, libc_cacosh);
DEFINE_PUBLIC_ALIAS(catanh, libc_catanh);
DEFINE_PUBLIC_ALIAS(carg, libc_carg);
DEFINE_PUBLIC_ALIAS(conj, libc_conj);
DEFINE_PUBLIC_ALIAS(creal, libc_creal);
DEFINE_PUBLIC_ALIAS(cimag, libc_cimag);
DEFINE_PUBLIC_ALIAS(cproj, libc_cproj);
DEFINE_PUBLIC_ALIAS(cabsl, libc_cabsl);
DEFINE_PUBLIC_ALIAS(cexpl, libc_cexpl);
DEFINE_PUBLIC_ALIAS(clogl, libc_clogl);
DEFINE_PUBLIC_ALIAS(cpowl, libc_cpowl);
DEFINE_PUBLIC_ALIAS(csqrtl, libc_csqrtl);
DEFINE_PUBLIC_ALIAS(csinl, libc_csinl);
DEFINE_PUBLIC_ALIAS(ccosl, libc_ccosl);
DEFINE_PUBLIC_ALIAS(ctanl, libc_ctanl);
DEFINE_PUBLIC_ALIAS(casinl, libc_casinl);
DEFINE_PUBLIC_ALIAS(cacosl, libc_cacosl);
DEFINE_PUBLIC_ALIAS(catanl, libc_catanl);
DEFINE_PUBLIC_ALIAS(csinhl, libc_csinhl);
DEFINE_PUBLIC_ALIAS(ccoshl, libc_ccoshl);
DEFINE_PUBLIC_ALIAS(ctanhl, libc_ctanhl);
DEFINE_PUBLIC_ALIAS(casinhl, libc_casinhl);
DEFINE_PUBLIC_ALIAS(cacoshl, libc_cacoshl);
DEFINE_PUBLIC_ALIAS(catanhl, libc_catanhl);
DEFINE_PUBLIC_ALIAS(cargl, libc_cargl);
DEFINE_PUBLIC_ALIAS(conjl, libc_conjl);
DEFINE_PUBLIC_ALIAS(creall, libc_creall);
DEFINE_PUBLIC_ALIAS(cimagl, libc_cimagl);
DEFINE_PUBLIC_ALIAS(cprojl, libc_cprojl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_COMPLEX_C */
