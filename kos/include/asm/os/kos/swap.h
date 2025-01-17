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
#ifndef _ASM_OS_KOS_SWAP_H
#define _ASM_OS_KOS_SWAP_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* The swap priority is encoded as:
 *  - (prio << SWAP_FLAG_PRIO_SHIFT) & SWAP_FLAG_PRIO_MASK */
#define __SWAP_FLAG_PREFER     0x08000 /* Set if swap priority is specified. */
#define __SWAP_FLAG_PRIO_MASK  0x07fff
#define __SWAP_FLAG_PRIO_SHIFT 0
#define __SWAP_FLAG_DISCARD    0x10000 /* Discard swap cluster after use. */

#endif /* !_ASM_OS_KOS_SWAP_H */
