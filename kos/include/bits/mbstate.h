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
#ifndef _BITS_MBSTATE_H
#define _BITS_MBSTATE_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__byteorder.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef ____mbstate_t_defined
#define ____mbstate_t_defined 1
typedef struct __ATTR_PACKED __mbstate {
	/* This structure must not exceed 4 bytes, so we
	 * can conform to DOS's 4-byte `mbstate_t' structure. */
	__UINT32_TYPE__  __word;
} __mbstate_t;
#define __MBSTATE_ISINIT(x) ((x)->__word == 0)
#define __MBSTATE_INIT      { 0 }

#define __MBSTATE_TYPE_MASK     0xfc000000
#define __MBSTATE_TYPE_EMPTY    0x00000000
#define __MBSTATE_TYPE_UTF8_SHIFT 6 /* Number of missing least significant bits provided by the last character of a utf-8 sequence. */
#define __MBSTATE_TYPE_UTF8_2_2 0x04000000 /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
#define __MBSTATE_TYPE_UTF8_3_2 0x08000000 /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
#define __MBSTATE_TYPE_UTF8_3_3 0x0c000000 /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
#define __MBSTATE_TYPE_UTF8_4_2 0x10000000 /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
#define __MBSTATE_TYPE_UTF8_4_3 0x14000000 /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
#define __MBSTATE_TYPE_UTF8_4_4 0x18000000 /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
#define __MBSTATE_TYPE_UTF8_5_2 0x1c000000 /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
#define __MBSTATE_TYPE_UTF8_5_3 0x20000000 /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
#define __MBSTATE_TYPE_UTF8_5_4 0x24000000 /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
#define __MBSTATE_TYPE_UTF8_5_5 0x28000000 /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
#define __MBSTATE_TYPE_UTF8_6_2 0x2c000000 /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
#define __MBSTATE_TYPE_UTF8_6_3 0x30000000 /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
#define __MBSTATE_TYPE_UTF8_6_4 0x34000000 /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
#define __MBSTATE_TYPE_UTF8_6_5 0x38000000 /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
#define __MBSTATE_TYPE_UTF8_6_6 0x3c000000 /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
/* NOTE: mbstate is too small to support 7-character and 8-character utf-8 sequences.
 *       But that's OK, since officially UTF-8 only goes up to 4-character sequences,
 *       so even just supporting 5-character and 6-character sequences is already an
 *       extension! */
#define __MBSTATE_TYPE_UTF16_LO    0x40000000 /* expect the low-surrogate value of a 2-uint16_t utf-16 sequence. `RESULT_CHAR = ((WORD & 0x000003ff) << 10) + 0x10000 + (SECOND_U16 - 0xdc00);' */
#define __MBSTATE_TYPE_WR_UTF16_LO 0xc0000000 /* Write the low-surrogate value of a 2-uint16_t utf-16 sequence. `OUT_CHAR = 0xdc00 + (WORD & 0x000003ff)' */


#define __MBSTATE_NBIT_MASK   0xf8000000
#define __MBSTATE_NBIT_SHFT   27
#define __MBSTATE_DATA_MASK   0x07ffffff

#endif /* !____mbstate_t_defined */

#ifdef __USE_KOS
#ifndef MBSTATE_INIT
#define MBSTATE_INIT     __MBSTATE_INIT
#endif /* !MBSTATE_INIT */
#endif /* __USE_KOS */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_MBSTATE_H */
