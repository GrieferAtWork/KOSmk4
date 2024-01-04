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
#ifndef GUARD_LIBC_USER_FENV_C
#define GUARD_LIBC_USER_FENV_C 1

#include "../api.h"
/**/

#include "fenv.h"

DECL_BEGIN

/*[[[head:libc_fesetexcept,hash:CRC-32=0x826b80b5]]]*/
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW_NCX(LIBCCALL libc_fesetexcept)(int excepts)
/*[[[body:libc_fesetexcept]]]*/
/*AUTO*/{
	(void)excepts;
	CRT_UNIMPLEMENTEDF("fesetexcept(excepts: %x)", excepts); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fesetexcept]]]*/

/*[[[head:libc_fetestexceptflag,hash:CRC-32=0xd93bb9a]]]*/
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW_NCX(LIBCCALL libc_fetestexceptflag)(fexcept_t const *flagp,
                                            int excepts)
/*[[[body:libc_fetestexceptflag]]]*/
/*AUTO*/{
	(void)flagp;
	(void)excepts;
	CRT_UNIMPLEMENTEDF("fetestexceptflag(flagp: %p, excepts: %x)", flagp, excepts); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fetestexceptflag]]]*/

/*[[[head:libc_fegetmode,hash:CRC-32=0xf94b0e17]]]*/
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW_NCX(LIBCCALL libc_fegetmode)(femode_t *modep)
/*[[[body:libc_fegetmode]]]*/
/*AUTO*/{
	(void)modep;
	CRT_UNIMPLEMENTEDF("fegetmode(modep: %p)", modep); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fegetmode]]]*/

/*[[[head:libc_fesetmode,hash:CRC-32=0xa034522]]]*/
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW_NCX(LIBCCALL libc_fesetmode)(femode_t const *modep)
/*[[[body:libc_fesetmode]]]*/
/*AUTO*/{
	(void)modep;
	CRT_UNIMPLEMENTEDF("fesetmode(modep: %p)", modep); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fesetmode]]]*/

/*[[[start:exports,hash:CRC-32=0x1d557cfe]]]*/
DEFINE_PUBLIC_ALIAS(fesetexcept, libc_fesetexcept);
DEFINE_PUBLIC_ALIAS(fetestexceptflag, libc_fetestexceptflag);
DEFINE_PUBLIC_ALIAS(fegetmode, libc_fegetmode);
DEFINE_PUBLIC_ALIAS(fesetmode, libc_fesetmode);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FENV_C */
