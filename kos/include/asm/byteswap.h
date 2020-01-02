/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _BITS_BYTESWAP_H
#define _BITS_BYTESWAP_H 1

#include <__stdinc.h>
#include <hybrid/__byteswap.h>

#define __bswap_constant_16(x)  __hybrid_bswap16_c(x)
#define __bswap_constant_32(x)  __hybrid_bswap32_c(x)
#ifdef __hybrid_bswap64_c
#define __bswap_constant_64(x)  __hybrid_bswap64_c(x)
#endif

#define __bswap_16(x)  __hybrid_bswap16(x)
#define __bswap_32(x)  __hybrid_bswap32(x)
#ifdef __hybrid_bswap64
#define __bswap_64(x)  __hybrid_bswap64(x)
#endif

#endif /* _BITS_BYTESWAP_H */
