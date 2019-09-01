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
#ifndef __GUARD_HYBRID___BYTEORDER_H
#define __GUARD_HYBRID___BYTEORDER_H 1

#include "../__stdinc.h"

#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 1234
#endif
#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__    4321
#endif
#ifndef __ORDER_PDP_ENDIAN__
#define __ORDER_PDP_ENDIAN__    3412
#endif

#ifndef __BYTE_ORDER__
#ifdef __BYTEORDER__
#   define __BYTE_ORDER__   __BYTEORDER__
#elif defined(__BYTE_ORDER)
#   define __BYTE_ORDER__   __BYTE_ORDER
#elif defined(__BYTEORDER)
#   define __BYTE_ORDER__   __BYTEORDER
#elif defined(__ENDIAN__)
#   define __BYTE_ORDER__   __ENDIAN__
#else
#   include "host.h"
#if defined(__hppa__) || defined(__m68k__) || \
    defined(mc68000) ||  defined(_M_M68K) || \
   (defined(__MIPS__) && defined(__MISPEB__)) || \
    defined(__ppc__) || defined(__powerpc__) || \
    defined(_M_PPC) || defined(__ARMEB__) || \
    defined(__sparc__)
#   define __BYTE_ORDER__ 4321
#else
#   define __BYTE_ORDER__ 1234
#endif
#endif
#endif /* !__BYTE_ORDER__ */

#ifndef __FLOAT_WORD_ORDER__
#ifdef __FLOAT_WORD_ORDER
#define __FLOAT_WORD_ORDER__ __FLOAT_WORD_ORDER
#else
#define __FLOAT_WORD_ORDER__ __BYTE_ORDER__
#endif
#endif /* !__FLOAT_WORD_ORDER__ */

#endif /* !__GUARD_HYBRID___BYTEORDER_H */
