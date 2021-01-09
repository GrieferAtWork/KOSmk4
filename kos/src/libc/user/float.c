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
#ifndef GUARD_LIBC_USER_FLOAT_C
#define GUARD_LIBC_USER_FLOAT_C 1

#include "../api.h"
#include "float.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc__clearfp,hash:CRC-32=0xeee4346e]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__clearfp)(void)
/*[[[body:libc__clearfp]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_clearfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__clearfp]]]*/

/*[[[head:libc__controlfp,hash:CRC-32=0xab4517aa]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:libc__controlfp]]]*/
/*AUTO*/{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTEDF("_controlfp(%" PRIx32 ", %" PRIx32 ")", newval, mask); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__controlfp]]]*/

/*[[[head:libc__set_controlfp,hash:CRC-32=0x8ae7121d]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval,
                                          uint32_t mask)
/*[[[body:libc__set_controlfp]]]*/
/*AUTO*/{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTEDF("_set_controlfp(%" PRIx32 ", %" PRIx32 ")", newval, mask); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__set_controlfp]]]*/

/*[[[head:libc__controlfp_s,hash:CRC-32=0xf346904f]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") errno_t
NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent,
                                        uint32_t newval,
                                        uint32_t mask)
/*[[[body:libc__controlfp_s]]]*/
/*AUTO*/{
	(void)pcurrent;
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTEDF("_controlfp_s(%p, %" PRIx32 ", %" PRIx32 ")", pcurrent, newval, mask); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__controlfp_s]]]*/

/*[[[head:libc__statusfp,hash:CRC-32=0x3a5b5b50]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__statusfp)(void)
/*[[[body:libc__statusfp]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_statusfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__statusfp]]]*/


/*[[[head:libc__statusfp2,hash:CRC-32=0xf4584c17]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc__statusfp2)(uint32_t *x86_stat,
                                      uint32_t *sse2_stat)
/*[[[body:libc__statusfp2]]]*/
/*AUTO*/{
	(void)x86_stat;
	(void)sse2_stat;
	CRT_UNIMPLEMENTEDF("_statusfp2(%p, %p)", x86_stat, sse2_stat); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__statusfp2]]]*/

/*[[[head:libc__control87,hash:CRC-32=0x3c84b0f8]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") uint32_t
NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:libc__control87]]]*/
/*AUTO*/{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTEDF("_control87(%" PRIx32 ", %" PRIx32 ")", newval, mask); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__control87]]]*/

/*[[[head:libc___control87_2,hash:CRC-32=0x1dbbbb5e]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") int
NOTHROW_NCX(LIBCCALL libc___control87_2)(uint32_t newval,
                                         uint32_t mask,
                                         uint32_t *x86_control_word,
                                         uint32_t *sse2_control_word)
/*[[[body:libc___control87_2]]]*/
/*AUTO*/{
	(void)newval;
	(void)mask;
	(void)x86_control_word;
	(void)sse2_control_word;
	CRT_UNIMPLEMENTEDF("__control87_2(%" PRIx32 ", %" PRIx32 ", %p, %p)", newval, mask, x86_control_word, sse2_control_word); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc___control87_2]]]*/

/*[[[head:libc___fpecode,hash:CRC-32=0x367981b7]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") int *
NOTHROW_NCX(LIBCCALL libc___fpecode)(void)
/*[[[body:libc___fpecode]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__fpecode"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___fpecode]]]*/








/*[[[head:libc__fpclass,hash:CRC-32=0x53bd24cc]]]*/
/* @return: * : Set of `_FPCLASS_*' */
INTERN ATTR_SECTION(".text.crt.math.float") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc__fpclass)(double x)
/*[[[body:libc__fpclass]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("_fpclass(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__fpclass]]]*/


/*[[[head:libc_fpreset,hash:CRC-32=0xa8470258]]]*/
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc_fpreset)(void)
/*[[[body:libc_fpreset]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("fpreset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_fpreset]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc596b74e]]]*/
DEFINE_PUBLIC_ALIAS(_clearfp, libc__clearfp);
DEFINE_PUBLIC_ALIAS(_controlfp, libc__controlfp);
DEFINE_PUBLIC_ALIAS(_set_controlfp, libc__set_controlfp);
DEFINE_PUBLIC_ALIAS(_controlfp_s, libc__controlfp_s);
DEFINE_PUBLIC_ALIAS(_statusfp, libc__statusfp);
DEFINE_PUBLIC_ALIAS(_statusfp2, libc__statusfp2);
DEFINE_PUBLIC_ALIAS(_control87, libc__control87);
DEFINE_PUBLIC_ALIAS(__control87_2, libc___control87_2);
DEFINE_PUBLIC_ALIAS(__fpecode, libc___fpecode);
DEFINE_PUBLIC_ALIAS(_fpclass, libc__fpclass);
DEFINE_PUBLIC_ALIAS(_fpreset, libc_fpreset);
DEFINE_PUBLIC_ALIAS(fpreset, libc_fpreset);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FLOAT_C */
