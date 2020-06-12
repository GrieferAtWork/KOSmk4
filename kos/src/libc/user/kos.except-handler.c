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
#ifndef GUARD_LIBC_USER_KOS_EXCEPT_HANDLER_C
#define GUARD_LIBC_USER_KOS_EXCEPT_HANDLER_C 1

#include "../api.h"
#include "kos.except-handler.h"
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:libc_set_exception_handler,hash:CRC-32=0x2048d50a]]]*/
/* Set the exception handler mode for the calling thread.
 * Examples:
 *     Set mode #1: set_exception_handler(EXCEPT_HANDLER_MODE_DISABLED, NULL, NULL)
 *     Set mode #2: set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler3, NULL)
 *     Set mode #3: set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler3, NULL)
 *     Set mode #4: set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler4, NULL)
 * WARNING: Many system libraries assume that either mode #3 or #4 is enabled,
 *          as other modes may not allow for exceptions such as E_SEGFAULT to
 *          be handled using the TRY-EXCEPT model.
 *          Examples for these include: `libinstrlen:instruction_trysucc()'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
INTERN int
NOTHROW(LIBCCALL libc_set_exception_handler)(int mode,
                                             except_handler_t handler,
                                             void *handler_sp)
/*[[[body:libc_set_exception_handler]]]*/
{
	errno_t result;
	result = sys_set_exception_handler((syscall_ulong_t)mode,
	                                   handler,
	                                   handler_sp);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_set_exception_handler]]]*/

/*[[[head:libc_get_exception_handler,hash:CRC-32=0x83658349]]]*/
/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
INTERN int
NOTHROW_NCX(LIBCCALL libc_get_exception_handler)(int *pmode,
                                                 except_handler_t *phandler,
                                                 void **phandler_sp)
/*[[[body:libc_get_exception_handler]]]*/
{
	errno_t result;
#if __SIZEOF_SYSCALL_LONG_T__ == __SIZEOF_INT__
	result = sys_get_exception_handler((syscall_ulong_t *)pmode,
	                                   phandler,
	                                   phandler_sp);
#else /* __SIZEOF_SYSCALL_LONG_T__ == __SIZEOF_INT__ */
	syscall_ulong_t mode_value;
	result = sys_get_exception_handler(pmode ? &mode_value : NULL,
	                                   phandler,
	                                   phandler_sp);
	if (likely(E_ISOK(result)) && pmode)
		*pmode = mode_value;
#endif /* __SIZEOF_SYSCALL_LONG_T__ != __SIZEOF_INT__ */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_get_exception_handler]]]*/


/* These are defined in assembly */
/*[[[skip:libc_except_handler3]]]*/
/*[[[skip:libc_except_handler4]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5365bf47]]]*/
DEFINE_PUBLIC_ALIAS(set_exception_handler, libc_set_exception_handler);
DEFINE_PUBLIC_ALIAS(get_exception_handler, libc_get_exception_handler);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_EXCEPT_HANDLER_C */
