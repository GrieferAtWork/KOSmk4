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
#ifndef __GUARD_HYBRID_LIMITS_H
#define __GUARD_HYBRID_LIMITS_H 1

#include "host.h"
#include "__limits.h"

#ifndef PAGESIZE
#ifdef __SIZEOF_PAGE__
#define PAGESIZE __SIZEOF_PAGE__
#endif /* __SIZEOF_PAGE__ */
#endif /* !PAGESIZE */

#ifndef PAGEALIGN
#define PAGEALIGN  PAGESIZE
#endif

#ifndef PAGESHIFT
#if PAGESIZE == 0x1
#   define PAGESHIFT  0
#elif PAGESIZE == 0x2
#   define PAGESHIFT  1
#elif PAGESIZE == 0x4
#   define PAGESHIFT  2
#elif PAGESIZE == 0x8
#   define PAGESHIFT  3
#elif PAGESIZE == 0x10
#   define PAGESHIFT  4
#elif PAGESIZE == 0x20
#   define PAGESHIFT  5
#elif PAGESIZE == 0x40
#   define PAGESHIFT  6
#elif PAGESIZE == 0x80
#   define PAGESHIFT  7
#elif PAGESIZE == 0x100
#   define PAGESHIFT  8
#elif PAGESIZE == 0x200
#   define PAGESHIFT  9
#elif PAGESIZE == 0x400
#   define PAGESHIFT  10
#elif PAGESIZE == 0x800
#   define PAGESHIFT  11
#elif PAGESIZE == 0x1000
#   define PAGESHIFT  12
#elif PAGESIZE == 0x2000
#   define PAGESHIFT  13
#elif PAGESIZE == 0x4000
#   define PAGESHIFT  14
#elif PAGESIZE == 0x8000
#   define PAGESHIFT  15
#elif PAGESIZE == 0x10000
#   define PAGESHIFT  16
#elif PAGESIZE == 0x20000
#   define PAGESHIFT  17
#elif PAGESIZE == 0x40000
#   define PAGESHIFT  18
#elif PAGESIZE == 0x80000
#   define PAGESHIFT  19
#elif PAGESIZE == 0x100000
#   define PAGESHIFT  20
#elif PAGESIZE == 0x200000
#   define PAGESHIFT  21
#elif PAGESIZE == 0x400000
#   define PAGESHIFT  22
#elif PAGESIZE == 0x800000
#   define PAGESHIFT  23
#elif PAGESIZE == 0x1000000
#   define PAGESHIFT  24
#elif PAGESIZE == 0x2000000
#   define PAGESHIFT  25
#elif PAGESIZE == 0x4000000
#   define PAGESHIFT  26
#elif PAGESIZE == 0x8000000
#   define PAGESHIFT  27
#elif PAGESIZE == 0x10000000
#   define PAGESHIFT  28
#elif PAGESIZE == 0x20000000
#   define PAGESHIFT  29
#elif PAGESIZE == 0x40000000
#   define PAGESHIFT  30
#elif PAGESIZE == 0x80000000
#   define PAGESHIFT  31
#else
#   error "Unsupported PAGESIZE"
#endif
#endif

#define ATTR_CACHELINE_ALIGNED __ATTR_CACHELINE_ALIGNED

#endif /* !__GUARD_HYBRID_LIMITS_H */
