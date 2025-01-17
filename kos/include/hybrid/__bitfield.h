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
#ifndef __GUARD_HYBRID___BITFIELD_H
#define __GUARD_HYBRID___BITFIELD_H 1

#include "../__stdinc.h"


/* Helpers for portably declarations of bitfields */
#ifdef __clang__
#include "typecore.h"
#define __HYBRID_BITFIELD8_T  __UINT8_TYPE__
#define __HYBRID_BITFIELD16_T __UINT16_TYPE__
#define __HYBRID_BITFIELD32_T __UINT32_TYPE__
#define __HYBRID_BITFIELD64_T __UINT64_TYPE__
#else /* __clang__ */
#define __HYBRID_BITFIELD8_T  unsigned int
#define __HYBRID_BITFIELD16_T unsigned int
#define __HYBRID_BITFIELD32_T unsigned int
#define __HYBRID_BITFIELD64_T unsigned int
#endif /* !__clang__ */

#endif /* !__GUARD_HYBRID___BITFIELD_H */
