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
#ifndef GUARD_LIBC_USER_UCONTEXT_C
#define GUARD_LIBC_USER_UCONTEXT_C 1

#include "../api.h"
#include "ucontext.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_getcontext,hash:CRC-32=0x88314362]]]*/
/* Get user context and store it in variable pointed to by UCP */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp)
/*[[[body:libc_getcontext]]]*/
/*AUTO*/{
	(void)ucp;
	CRT_UNIMPLEMENTED("getcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getcontext]]]*/

/*[[[head:libc_setcontext,hash:CRC-32=0x75ce72b]]]*/
/* Set user context from information of variable pointed to by UCP */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp)
/*[[[body:libc_setcontext]]]*/
/*AUTO*/{
	(void)ucp;
	CRT_UNIMPLEMENTED("setcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setcontext]]]*/

/*[[[head:libc_swapcontext,hash:CRC-32=0x51df0938]]]*/
/* Save current context in context variable pointed to by OUCP and set
 * context from variable pointed to by UCP */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_swapcontext)(ucontext_t *__restrict oucp,
                                       ucontext_t const *__restrict ucp)
/*[[[body:libc_swapcontext]]]*/
/*AUTO*/{
	(void)oucp;
	(void)ucp;
	CRT_UNIMPLEMENTED("swapcontext"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_swapcontext]]]*/

/*[[[head:libc_makecontext,hash:CRC-32=0x6fc70086]]]*/
/* Manipulate user context UCP to continue with calling functions FUNC
 * and the ARGC-1 parameters following ARGC when the context is used
 * the next time in `setcontext' or `swapcontext'.
 * We cannot say anything about the parameters FUNC takes; `void'
 * is as good as any other choice */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 2)) void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        __makecontext_func_t func,
                                        int argc,
                                        ...)
/*[[[body:libc_makecontext]]]*/
/*AUTO*/{
	(void)ucp;
	(void)func;
	(void)argc;
	CRT_UNIMPLEMENTED("makecontext"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_makecontext]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x6800f348]]]*/
DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext);
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext);
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext);
DEFINE_PUBLIC_ALIAS(makecontext, libc_makecontext);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UCONTEXT_C */
