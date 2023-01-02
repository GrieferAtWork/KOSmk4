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
#ifndef _ASM_CRT_FLOAT_H
#define _ASM_CRT_FLOAT_H 1

#include <__crt.h>

#ifdef __CRT_DOS
/* Bits for return value of `_fpclass(3)' */
#define __FPCLASS_SNAN   0x0001 /* signaling NaN. */
#define __FPCLASS_QNAN   0x0002 /* quiet NaN. */
#define __FPCLASS_NINF   0x0004 /* negative infinity. */
#define __FPCLASS_NN     0x0008 /* negative normal. */
#define __FPCLASS_ND     0x0010 /* negative denormal. */
#define __FPCLASS_NZ     0x0020 /* -0 */
#define __FPCLASS_PZ     0x0040 /* +0 */
#define __FPCLASS_PD     0x0080 /* positive denormal. */
#define __FPCLASS_PN     0x0100 /* positive normal. */
#define __FPCLASS_PINF   0x0200 /* positive infinity. */
#endif /* __CRT_DOS */

#endif /* !_ASM_CRT_FLOAT_H */
