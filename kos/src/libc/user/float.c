/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/*[[[head:_clearfp,hash:0xa0592190]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._clearfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__clearfp)(void)
/*[[[body:_clearfp]]]*/
{
	CRT_UNIMPLEMENTED("_clearfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_clearfp]]]*/

/*[[[head:_controlfp,hash:0x6ae0ee2f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._controlfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:_controlfp]]]*/
{
	CRT_UNIMPLEMENTED("_controlfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_controlfp]]]*/

/*[[[head:_set_controlfp,hash:0xfd7a86a3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._set_controlfp") void
NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval,
                                          uint32_t mask)
/*[[[body:_set_controlfp]]]*/
{
	CRT_UNIMPLEMENTED("_set_controlfp"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_set_controlfp]]]*/

/*[[[head:_controlfp_s,hash:0xdda82888]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._controlfp_s") errno_t
NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent,
                                        uint32_t newval,
                                        uint32_t mask)
/*[[[body:_controlfp_s]]]*/
{
	CRT_UNIMPLEMENTED("_controlfp_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_controlfp_s]]]*/

/*[[[head:_statusfp,hash:0x11bc61ae]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._statusfp") uint32_t
NOTHROW_NCX(LIBCCALL libc__statusfp)(void)
/*[[[body:_statusfp]]]*/
{
	CRT_UNIMPLEMENTED("_statusfp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_statusfp]]]*/


/*[[[head:_statusfp2,hash:0xcea51e02]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._statusfp2") void
NOTHROW_NCX(LIBCCALL libc__statusfp2)(uint32_t *x86_stat,
                                      uint32_t *sse2_stat)
/*[[[body:_statusfp2]]]*/
{
	CRT_UNIMPLEMENTED("_statusfp2"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_statusfp2]]]*/

/*[[[head:_control87,hash:0x3f9e2903]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float._control87") uint32_t
NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval,
                                      uint32_t mask)
/*[[[body:_control87]]]*/
{
	CRT_UNIMPLEMENTED("_control87"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_control87]]]*/

/*[[[head:__control87_2,hash:0xadcb54f8]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.__control87_2") int
NOTHROW_NCX(LIBCCALL libc___control87_2)(uint32_t newval,
                                         uint32_t mask,
                                         uint32_t *x86_control_word,
                                         uint32_t *sse2_control_word)
/*[[[body:__control87_2]]]*/
{
	CRT_UNIMPLEMENTED("__control87_2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:__control87_2]]]*/

/*[[[head:__fpecode,hash:0x7db19204]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.__fpecode") int *
NOTHROW_NCX(LIBCCALL libc___fpecode)(void)
/*[[[body:__fpecode]]]*/
{
	CRT_UNIMPLEMENTED("__fpecode"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__fpecode]]]*/








/*[[[head:_fpclass,hash:0xb7fd0e65]]]*/
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.math.float._fpclass") int
NOTHROW(LIBCCALL libc__fpclass)(double x)
/*[[[body:_fpclass]]]*/
{
	CRT_UNIMPLEMENTED("_fpclass"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_fpclass]]]*/


/*[[[head:fpreset,hash:0xbbb294c4]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.float.fpreset") void
NOTHROW_NCX(LIBCCALL libc_fpreset)(void)
/*[[[body:fpreset]]]*/
{
	CRT_UNIMPLEMENTED("fpreset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:fpreset]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xbf877f86]]]*/
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
