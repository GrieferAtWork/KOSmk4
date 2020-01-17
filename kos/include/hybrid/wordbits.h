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
#ifndef __GUARD_HYBRID_WORDBITS_H
#define __GUARD_HYBRID_WORDBITS_H 1

#include "__wordbits.h"

/* Return the ith byte/word/dword of a given 16/32/64-bit integer. */
#define INT16_I8(x, i)                       __INT16_I8(x, i)
#define INT32_I8(x, i)                       __INT32_I8(x, i)
#define INT64_I8(x, i)                       __INT64_I8(x, i)
#define INT32_I16(x, i)                      __INT32_I16(x, i)
#define INT64_I16(x, i)                      __INT64_I16(x, i)
#define INT64_I32(x, i)                      __INT64_I32(x, i)
#define ENCODE_INT16(a, b)                   __ENCODE_INT16(a, b)
#define ENCODE_INT32(a, b, c, d)             __ENCODE_INT32(a, b, c, d)
#define ENCODE_INT64(a, b, c, d, e, f, g, h) __ENCODE_INT64(a, b, c, d, e, f, g, h)

/* Commonly used aliases. */
#define INT16_BYTE(x, i)  __INT16_BYTE(x, i)
#define INT32_BYTE(x, i)  __INT32_BYTE(x, i)
#define INT64_BYTE(x, i)  __INT64_BYTE(x, i)
#define INT32_WORD(x, i)  __INT32_WORD(x, i)
#define INT64_WORD(x, i)  __INT64_WORD(x, i)
#define INT64_DWORD(x, i) __INT64_DWORD(x, i)

#endif /* !__GUARD_HYBRID_WORDBITS_H */
