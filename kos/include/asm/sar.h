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
#ifndef _ASM_SAR
#define _ASM_SAR 1

#include <asm/signed-shift.h>

/* >> SIGNED sar(Signed x, shift_t shift);
 * Signed Arithmetic Shift */
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
#define sar(x, shift) ((x) >> (shift))
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
#define sar(x, shift) ((x) < 0 ? -1 - ((-1 - (x)) >> (shift)) : (x) >> (shift))
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */

#endif /* !_ASM_SAR */
