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
/* (#) Portability: Cygwin      (/winsup/cygwin/include/asm/byteorder.h) */
/* (#) Portability: Linux       (/usr/include/[...]/asm/byteorder.h) */
/* (#) Portability: OpenSolaris (/usr/src/uts/[...]/asm/byteorder.h) */
#ifndef _ASM_BYTEORDER_H
#define _ASM_BYTEORDER_H 1

#include <hybrid/byteorder.h>

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#include <linux/byteorder/big_endian.h>
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#include <linux/byteorder/little_endian.h>
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

#endif /* !_ASM_BYTEORDER_H */
