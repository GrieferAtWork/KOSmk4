/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_CONFIG_H
#define GUARD_LIBC_HYBRID_ARCH_ARM_CONFIG_H 1

#include <__stdinc.h>

/* Libc functions implemented  by arch-specific, optimized  functions.
 * Defining these macros causes libc's auto/user-system to not provide
 * the associated functions. */

/* abort() */
#define LIBC_ARCH_HAVE_ABORT 1


#ifndef __KERNEL__
/* void ASMCALL libc_sig_restore(void); */
#define LIBC_ARCH_HAVE_SIG_RESTORE 1

/* void *LIBCCALL libc_handle(void); */
#define LIBC_ARCH_HAVE_LIBC_HANDLE 1

#ifdef __CC__
#include <bits/types.h>

DECL_BEGIN

#define libc_handle libc_handle
LOCAL ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(libc_handle)(void) {
	void *result;
	/* Sadly, there is no way to trick gcc into emitting
	 * our custom literal as part of its literal pool :(
	 *
	 * And trying to encode it as `ldr %0, =current(tlsgd)' also break. */
	__asm__("ldr    %0, 992f\n"
	        "991:\t"
	        "add    %0, pc, %0\n\t"
	        "b      993f\n"
	        "992:\t"
	        ".word current(tlsgd) + (. - 991b - 8)\n"
	        "993:"
	        : "=r" (result));
	return result;
}

DECL_END
#endif /* __CC__ */

#define LIBC_ARCH_HAVE_GETCONTEXT  1
#define LIBC_ARCH_HAVE_SETCONTEXT  1
#define LIBC_ARCH_HAVE_SWAPCONTEXT 1
#define LIBC_ARCH_HAVE_MAKECONTEXT 1
#endif /* !__KERNEL__ */


#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_CONFIG_H */
