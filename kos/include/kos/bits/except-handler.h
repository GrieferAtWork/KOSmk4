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
#ifndef _KOS_BITS_EXCEPT_HANDLER_H
#define _KOS_BITS_EXCEPT_HANDLER_H 1

#include <__stdinc.h>

#include <kos/bits/except-register-state.h> /* __EXCEPT_REGISTER_STATE_TYPE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __except_register_state_t_defined
#define __except_register_state_t_defined
typedef __EXCEPT_REGISTER_STATE_TYPE except_register_state_t;
#endif /* !__except_register_state_t_defined */

#ifndef __EXCEPT_HANDLER_CC
#define __EXCEPT_HANDLER_CC  /* nothing */
#endif /* !__EXCEPT_HANDLER_CC */

#ifndef __restrict_111080
#ifdef __COMPILER_HAVE_BUG_GCC_111080
#define __restrict_111080 /* Nothing */
#else /* __COMPILER_HAVE_BUG_GCC_111080 */
#define __restrict_111080 __restrict
#endif /* !__COMPILER_HAVE_BUG_GCC_111080 */
#endif /* !__restrict_111080 */

/* Prototype   for   a   low-level   user-space   exception   handler.
 * Note that the exact prototype may differ between architectures,  as
 * well as the calling convention  not always being the same,  either.
 * The  passed pointers will point to structures stored on a dedicated
 * exception handler stack, or (by default) on the stack of the thread
 * that caused the exception
 * Other  caveats  include  the  fact   that  the  expected  behavior  of   the
 * function may differ based on other flags passed to `set_exception_handler()' */
typedef /*__ATTR_NORETURN*/ void
(__EXCEPT_HANDLER_CC *__except_handler_t)(except_register_state_t *__restrict_111080 state,
                                          struct exception_data *__restrict_111080 error);


__SYSDECL_END
#endif /* !__CC__ */

#endif /* !_KOS_BITS_EXCEPT_HANDLER_H */
