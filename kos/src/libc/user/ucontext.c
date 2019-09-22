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
#ifndef GUARD_LIBC_USER_UCONTEXT_C
#define GUARD_LIBC_USER_UCONTEXT_C 1

#include "../api.h"
#include "ucontext.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getcontext,hash:CRC-32=0x1da89edf]]]*/
/* Get user context and store it in variable pointed to by UCP */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.getcontext") int
NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp)
/*[[[body:getcontext]]]*/
{
	CRT_UNIMPLEMENTED("getcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getcontext]]]*/

/*[[[head:setcontext,hash:CRC-32=0x73d881e5]]]*/
/* Set user context from information of variable pointed to by UCP */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.setcontext") int
NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp)
/*[[[body:setcontext]]]*/
{
	CRT_UNIMPLEMENTED("setcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setcontext]]]*/

/*[[[head:swapcontext,hash:CRC-32=0x2a139d3a]]]*/
/* Save current context in context variable pointed to by OUCP and set
 * context from variable pointed to by UCP */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.swapcontext") int
NOTHROW_NCX(LIBCCALL libc_swapcontext)(ucontext_t *__restrict oucp,
                                       ucontext_t const *__restrict ucp)
/*[[[body:swapcontext]]]*/
{
	CRT_UNIMPLEMENTED("swapcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:swapcontext]]]*/

/*[[[head:makecontext,hash:CRC-32=0x2691e488]]]*/
/* Manipulate user context UCP to continue with calling functions FUNC
 * and the ARGC-1 parameters following ARGC when the context is used
 * the next time in `setcontext' or `swapcontext'.
 * We cannot say anything about the parameters FUNC takes; `void'
 * is as good as any other choice */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.makecontext") void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        __makecontext_func_t func,
                                        int argc,
                                        ...)
/*[[[body:makecontext]]]*/
{
	CRT_UNIMPLEMENTED("makecontext"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:makecontext]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xee137fe2]]]*/
#undef makecontext
DEFINE_PUBLIC_WEAK_ALIAS(getcontext, libc_getcontext);
DEFINE_PUBLIC_WEAK_ALIAS(setcontext, libc_setcontext);
DEFINE_PUBLIC_WEAK_ALIAS(swapcontext, libc_swapcontext);
DEFINE_PUBLIC_WEAK_ALIAS(makecontext, libc_makecontext);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UCONTEXT_C */
