/* HASH CRC-32:0x327629b4 */
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
#ifndef GUARD_LIBC_AUTO_PTHREAD_C
#define GUARD_LIBC_AUTO_PTHREAD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "pthread.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Compare two thread identifiers */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_equal") int
NOTHROW_NCX(LIBCCALL libc_pthread_equal)(pthread_t pthread1,
                                         pthread_t pthread2) {
#line 234 "kos/src/libc/magic/pthread.c"
	return pthread1 == pthread2;
}

/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.__pthread_cleanup_routine") void
NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame) {
#line 549 "kos/src/libc/magic/pthread.c"
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(pthread_equal, libc_pthread_equal);
DEFINE_PUBLIC_WEAK_ALIAS(__pthread_cleanup_routine, libc___pthread_cleanup_routine);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTHREAD_C */
