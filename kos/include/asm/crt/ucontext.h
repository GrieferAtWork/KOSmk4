/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_CRT_UCONTEXT_H
#define _ASM_CRT_UCONTEXT_H 1

#include <__crt.h>

/* Define the macro `__CRT_SUPPORTS_UCONTEXT' if the linked libc is  guarantied
 * to implement `getcontext()', `setcontext()' and `swapcontext()', without any
 * of these functions ever being able to return with errno=ENOSYS */
#undef __CRT_SUPPORTS_UCONTEXT
#if (defined(__CRT_HAVE_getcontext) && defined(__CRT_HAVE_setcontext) && \
     defined(__CRT_HAVE_swapcontext) && !defined(__stub_getcontext) &&   \
     !defined(__stub_setcontext) && !defined(__stub_swapcontext))
#define __CRT_SUPPORTS_UCONTEXT 1
#endif /* ... */

#endif /* !_ASM_CRT_UCONTEXT_H */
