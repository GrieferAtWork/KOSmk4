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
/*!replace_with_include <fenv.h>*/
#ifndef _I386_KOS_ASM_CRT_FENV_H
#define _I386_KOS_ASM_CRT_FENV_H 1

/* Floating point exceptions... */
#define __FE_INVALID   0x01 /* == FSW_IE */
#define __FE_DENORM    0x02 /* == FSW_DE */
#define __FE_DIVBYZERO 0x04 /* == FSW_ZE */
#define __FE_OVERFLOW  0x08 /* == FSW_OE */
#define __FE_UNDERFLOW 0x10 /* == FSW_UE */
#define __FE_INEXACT   0x20 /* == FSW_PE */
#define __FE_ALL_EXCEPT (__FE_INVALID | __FE_DIVBYZERO | __FE_OVERFLOW | __FE_UNDERFLOW | __FE_INEXACT)

#define __FE_ALL_EXCEPT_X86 (__FE_ALL_EXCEPT | __FE_DENORM)

/* Rounding modes... */
#define __FE_TONEAREST  0x0000 /* round() (== FCW_RC_NEAREST) */
#define __FE_DOWNWARD   0x0400 /* floor() (== FCW_RC_DOWN) */
#define __FE_UPWARD     0x0800 /* ceil()  (== FCW_RC_UP) */
#define __FE_TOWARDZERO 0x0c00 /* trunc() (== FCW_RC_TRUNC) */

#endif /* !_I386_KOS_ASM_CRT_FENV_H */
