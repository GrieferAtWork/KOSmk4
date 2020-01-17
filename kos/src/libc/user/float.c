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
#ifndef GUARD_LIBC_USER_FLOAT_C
#define GUARD_LIBC_USER_FLOAT_C 1

#include "../api.h"
#include "float.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_clearfp,hash:CRC-32=0xfa8af88]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._clearfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__clearfp)(void)
/*[[[body:_clearfp]]]*/
{
	CRT_UNIMPLEMENTED("_clearfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_clearfp]]]*/

/*[[[head:_controlfp,hash:CRC-32=0xc0eae30e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._controlfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:_controlfp]]]*/
{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTED("_controlfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_controlfp]]]*/

/*[[[head:_set_controlfp,hash:CRC-32=0x594279f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._set_controlfp") void
NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval,
                                          uint32_t mask)
/*[[[body:_set_controlfp]]]*/
{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTED("_set_controlfp"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_set_controlfp]]]*/

/*[[[head:_controlfp_s,hash:CRC-32=0x6ebe8b52]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._controlfp_s") errno_t
NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent,
                                        uint32_t newval,
                                        uint32_t mask)
/*[[[body:_controlfp_s]]]*/
{
	(void)pcurrent;
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTED("_controlfp_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_controlfp_s]]]*/

/*[[[head:_statusfp,hash:CRC-32=0x29cee024]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._statusfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__statusfp)(void)
/*[[[body:_statusfp]]]*/
{
	CRT_UNIMPLEMENTED("_statusfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_statusfp]]]*/


/*[[[head:_statusfp2,hash:CRC-32=0x47242aa1]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._statusfp2") void
NOTHROW_NCX(LIBCCALL libc__statusfp2)(uint32_t *x86_stat,
                                      uint32_t *sse2_stat)
/*[[[body:_statusfp2]]]*/
{
	(void)x86_stat;
	(void)sse2_stat;
	CRT_UNIMPLEMENTED("_statusfp2"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_statusfp2]]]*/

/*[[[head:_control87,hash:CRC-32=0x2e9050ec]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._control87") uint32_t
NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:_control87]]]*/
{
	(void)newval;
	(void)mask;
	CRT_UNIMPLEMENTED("_control87"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_control87]]]*/

/*[[[head:__control87_2,hash:CRC-32=0x523dc9df]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.__control87_2") int
NOTHROW_NCX(LIBCCALL libc___control87_2)(uint32_t newval,
                                         uint32_t mask,
                                         uint32_t *x86_control_word,
                                         uint32_t *sse2_control_word)
/*[[[body:__control87_2]]]*/
{
	(void)newval;
	(void)mask;
	(void)x86_control_word;
	(void)sse2_control_word;
	CRT_UNIMPLEMENTED("__control87_2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:__control87_2]]]*/

/*[[[head:__fpecode,hash:CRC-32=0xd7853063]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.__fpecode") int *
NOTHROW_NCX(LIBCCALL libc___fpecode)(void)
/*[[[body:__fpecode]]]*/
{
	CRT_UNIMPLEMENTED("__fpecode"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__fpecode]]]*/








/*[[[head:_fpclass,hash:CRC-32=0x32b0ddb6]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.float._fpclass") int
NOTHROW(LIBCCALL libc__fpclass)(double x)
/*[[[body:_fpclass]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("_fpclass"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_fpclass]]]*/


/*[[[head:fpreset,hash:CRC-32=0x609ddbf3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.fpreset") void
NOTHROW_NCX(LIBCCALL libc_fpreset)(void)
/*[[[body:fpreset]]]*/
{
	CRT_UNIMPLEMENTED("fpreset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:fpreset]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xe746b508]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(_clearfp, libc__clearfp);
DEFINE_PUBLIC_WEAK_ALIAS(_controlfp, libc__controlfp);
DEFINE_PUBLIC_WEAK_ALIAS(_set_controlfp, libc__set_controlfp);
DEFINE_PUBLIC_WEAK_ALIAS(_controlfp_s, libc__controlfp_s);
DEFINE_PUBLIC_WEAK_ALIAS(_statusfp, libc__statusfp);
DEFINE_PUBLIC_WEAK_ALIAS(_statusfp2, libc__statusfp2);
DEFINE_PUBLIC_WEAK_ALIAS(_control87, libc__control87);
DEFINE_PUBLIC_WEAK_ALIAS(__control87_2, libc___control87_2);
DEFINE_PUBLIC_WEAK_ALIAS(__fpecode, libc___fpecode);
DEFINE_PUBLIC_WEAK_ALIAS(_fpclass, libc__fpclass);
DEFINE_PUBLIC_WEAK_ALIAS(fpreset, libc_fpreset);
DEFINE_PUBLIC_WEAK_ALIAS(_fpreset, libc_fpreset);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FLOAT_C */
