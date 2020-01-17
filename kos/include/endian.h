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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ENDIAN_H
#define _ENDIAN_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/endian.h>

#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 1234
#endif /* !__ORDER_LITTLE_ENDIAN__ */
#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__    4321
#endif /* !__ORDER_BIG_ENDIAN__ */
#ifndef __ORDER_PDP_ENDIAN__
#define __ORDER_PDP_ENDIAN__    3412
#endif /* !__ORDER_PDP_ENDIAN__ */

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define __BIG_ENDIAN    __ORDER_BIG_ENDIAN__
#define __PDP_ENDIAN    __ORDER_PDP_ENDIAN__
#endif /* !__LITTLE_ENDIAN */

#ifndef __FLOAT_WORD_ORDER
#ifdef __FLOAT_WORD_ORDER__
#define __FLOAT_WORD_ORDER __FLOAT_WORD_ORDER__
#else /* __FLOAT_WORD_ORDER__ */
#define __FLOAT_WORD_ORDER __BYTE_ORDER
#endif /* !__FLOAT_WORD_ORDER__ */
#endif /* !__FLOAT_WORD_ORDER */

#ifdef __USE_MISC
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#define BIG_ENDIAN    __BIG_ENDIAN
#define PDP_ENDIAN    __PDP_ENDIAN
#ifndef BYTE_ORDER
#define BYTE_ORDER    __BYTE_ORDER
#endif /* !BYTE_ORDER */
#endif /* !__USE_MISC */

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define __LONG_LONG_PAIR(hi,lo) lo,hi
#elif __BYTE_ORDER == __BIG_ENDIAN
#define __LONG_LONG_PAIR(hi,lo) hi,lo
#endif

#ifdef __USE_MISC
#include <bits/byteswap.h>
#define htobe16(x)  __hybrid_beswap16(x)
#define htole16(x)  __hybrid_leswap16(x)
#define be16toh(x)  __hybrid_beswap16(x)
#define le16toh(x)  __hybrid_leswap16(x)
#define htobe32(x)  __hybrid_beswap32(x)
#define htole32(x)  __hybrid_leswap32(x)
#define be32toh(x)  __hybrid_beswap32(x)
#define le32toh(x)  __hybrid_leswap32(x)
#define htobe64(x)  __hybrid_beswap64(x)
#define htole64(x)  __hybrid_leswap64(x)
#define be64toh(x)  __hybrid_beswap64(x)
#define le64toh(x)  __hybrid_leswap64(x)
#endif /* __USE_MISC */

#endif /* !_ENDIAN_H */
