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
#ifndef __GUARD_HYBRID___WORDBITS_H
#define __GUARD_HYBRID___WORDBITS_H 1

#include "byteorder.h"
#include "typecore.h"

/* Return the ith byte/word/dword of a given 16/32/64-bit integer. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __INT16_I8(x, i)    __CCAST(__UINT8_TYPE__)(((x) >> (i)*8) & 0xff)
#define __INT32_I8(x, i)    __CCAST(__UINT8_TYPE__)(((x) >> (i)*8) & 0xff)
#define __INT64_I8(x, i)    __CCAST(__UINT8_TYPE__)(((x) >> (i)*8) & 0xff)
#define __INT32_I16(x, i)   __CCAST(__UINT16_TYPE__)(((x) >> (i)*16) & 0xffff)
#define __INT64_I16(x, i)   __CCAST(__UINT16_TYPE__)(((x) >> (i)*16) & 0xffff)
#define __INT64_I32(x, i)   __CCAST(__UINT32_TYPE__)(((x) >> (i)*32) & 0xffffffff)
#define __ENCODE_INT16(a, b) \
	(__CCAST(__UINT16_TYPE__)(b) << 8 | __CCAST(__UINT16_TYPE__)(a))
#define __ENCODE_INT32(a, b, c, d)       \
	(__CCAST(__UINT32_TYPE__)(d) << 24 | \
	 __CCAST(__UINT32_TYPE__)(c) << 16 | \
	 __CCAST(__UINT32_TYPE__)(b) << 8 |  \
	 __CCAST(__UINT32_TYPE__)(a))
#ifdef __UINT64_TYPE__
#define __ENCODE_INT64(a, b, c, d, e, f, g, h) \
	(__CCAST(__UINT64_TYPE__)(h) << 56 |       \
	 __CCAST(__UINT64_TYPE__)(g) << 48 |       \
	 __CCAST(__UINT64_TYPE__)(f) << 40 |       \
	 __CCAST(__UINT64_TYPE__)(e) << 32 |       \
	 __CCAST(__UINT64_TYPE__)(d) << 24 |       \
	 __CCAST(__UINT64_TYPE__)(c) << 16 |       \
	 __CCAST(__UINT64_TYPE__)(b) << 8 |        \
	 __CCAST(__UINT64_TYPE__)(a))
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __INT16_I8(x, i)  __CCAST(__UINT8_TYPE__)(((x) >> (8-(i)*8)) & 0xff)
#define __INT32_I8(x, i)  __CCAST(__UINT8_TYPE__)(((x) >> (24-(i)*8)) & 0xff)
#define __INT64_I8(x, i)  __CCAST(__UINT8_TYPE__)(((x) >> (56-(i)*8)) & 0xff)
#define __INT32_I16(x, i) __CCAST(__UINT16_TYPE__)(((x) >> (16-(i)*16)) & 0xffff)
#define __INT64_I16(x, i) __CCAST(__UINT16_TYPE__)(((x) >> (48-(i)*16)) & 0xffff)
#define __INT64_I32(x, i) __CCAST(__UINT32_TYPE__)(((x) >> (32-(i)*32)) & 0xffffffff)
#define __ENCODE_INT16(a, b) \
	(__CCAST(__UINT16_TYPE__)(b) | __CCAST(__UINT16_TYPE__)(a) << 8)
#define __ENCODE_INT32(a, b, c, d)       \
	(__CCAST(__UINT32_TYPE__)(d) |       \
	 __CCAST(__UINT32_TYPE__)(c) << 8 |  \
	 __CCAST(__UINT32_TYPE__)(b) << 16 | \
	 __CCAST(__UINT32_TYPE__)(a) << 24)
#define __ENCODE_INT64(a, b, c, d, e, f, g, h) \
	(__CCAST(__UINT64_TYPE__)(h) |             \
	 __CCAST(__UINT64_TYPE__)(g) << 8 |        \
	 __CCAST(__UINT64_TYPE__)(f) << 16 |       \
	 __CCAST(__UINT64_TYPE__)(e) << 24 |       \
	 __CCAST(__UINT64_TYPE__)(d) << 32 |       \
	 __CCAST(__UINT64_TYPE__)(c) << 40 |       \
	 __CCAST(__UINT64_TYPE__)(b) << 48 |       \
	 __CCAST(__UINT64_TYPE__)(a) << 56)
#endif

/* Commonly used aliases. */
#define __INT16_BYTE(x, i) __INT16_I8(x, i)
#define __INT32_BYTE(x, i) __INT32_I8(x, i)
#define __INT64_BYTE(x, i) __INT64_I8(x, i)
#define __INT32_WORD(x, i) __INT32_I16(x, i)
#define __INT64_WORD(x, i) __INT64_I16(x, i)
#define __INT64_DWORD(x, i) __INT64_I32(x, i)

#endif /* !__GUARD_HYBRID___WORDBITS_H */
