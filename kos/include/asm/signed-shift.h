/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_SIGNED_SHIFT
#define _ASM_SIGNED_SHIFT 1

/* Behavior of signed shift operations (`(-1 >> 1) == ???')
 *
 * The exact result of such an operation is arch-specific, but
 * for our purpose, we narrow down the range of  possibilities
 * to one of 3 options:
 *   #1: (-1 >> 1) == -1                --> Signed divide (most significant bit is copied)
 *   #2: (-1 >> 1) == 0x7fffffff[...]   --> Unsigned divide (most significant bit is set to `0')
 *   #3: (-1 >> 1) == ?                 --> Something entirely different.
 *
 * For these 3 cases, we define 0 or 1 of 2 macros:
 *   #1: #define __ARCH_SIGNED_SHIFT_IS_SDIV
 *   #2: #define __ARCH_SIGNED_SHIFT_IS_UDIV
 *   #3: Don't define anything.
 */


/* Without  any arch-specific override, assume that the preprocessor's
 * C-like expression evaluator gets it right, and use it to figure out
 * what the result should be. */
#undef __ARCH_SIGNED_SHIFT_IS_SDIV
#undef __ARCH_SIGNED_SHIFT_IS_UDIV
#if (-1 >> 1) == -1
#define __ARCH_SIGNED_SHIFT_IS_SDIV 1
#elif (-1 >> 1) > 0 /* Any positive value would mean that the sign-bit was set to `0' */
#define __ARCH_SIGNED_SHIFT_IS_UDIV 1
#endif

#endif /* !_ASM_SIGNED_SHIFT */
