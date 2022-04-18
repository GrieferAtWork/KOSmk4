/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin    (/newlib/libc/include/machine/endian.h) */
/* (#) Portability: DJGPP     (/include/machine/endian.h) */
/* (#) Portability: EMX kLIBC (/libc/include/machine/endian.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/machine/endian.h) */
#ifndef _MACHINE_ENDIAN_H
#define _MACHINE_ENDIAN_H 1

#include <features.h>

#include <hybrid/__byteswap.h>
#include <hybrid/byteorder.h>

#include <machine/_endian.h>
#include <sys/_types.h>
#include <sys/cdefs.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _QUAD_HIGHWORD 1
#define _QUAD_LOWWORD  0
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define _QUAD_HIGHWORD 0
#define _QUAD_LOWWORD  1
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

#ifdef __USE_MISC
#define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define BIG_ENDIAN    __ORDER_BIG_ENDIAN__
#define PDP_ENDIAN    __ORDER_PDP_ENDIAN__
#define BYTE_ORDER    __BYTE_ORDER__
#endif /* __USE_MISC */

#define __bswap16(x) __hybrid_bswap16(x)
#define __bswap32(x) __hybrid_bswap32(x)
#define __bswap64(x) __hybrid_bswap64(x)

#ifndef __machine_host_to_from_network_defined
#define __machine_host_to_from_network_defined
#define __htonl(x) __hybrid_htobe32(x)
#define __htons(x) __hybrid_htobe16(x)
#define __ntohl(x) __hybrid_betoh32(x)
#define __ntohs(x) __hybrid_betoh16(x)
#endif /* __machine_host_to_from_network_defined */

#endif /* !_MACHINE_ENDIAN_H */
