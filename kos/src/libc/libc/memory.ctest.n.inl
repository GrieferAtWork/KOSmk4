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
#ifdef __INTELLISENSE__
#include "memory.ctest"
#define N 1
#endif /* __INTELLISENSE__ */

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#if N == 0
#undef N
#define N          1
#define bwlq(name) name
#elif N == 1
#define bwlq(name) name##b
#elif N == 2
#define bwlq(name) name##w
#elif N == 4
#define bwlq(name) name##l
#elif N == 8
#define bwlq(name) name##q
#else /* N == ... */
#error "Unsupported N"
#endif /* N != ... */



#if N == 1
#define Ts int8_t
#define Tu uint8_t
#elif N == 2
#define Ts int16_t
#define Tu uint16_t
#elif N == 4
#define Ts int32_t
#define Tu uint32_t
#elif N == 8
#define Ts int64_t
#define Tu uint64_t
#endif /* N == ... */


DECL_BEGIN

PRIVATE void bwlq(do_test_memory)(void) {
	static Tu const blob[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	static Tu const xblob[]   = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
	Tu const *volatile vblob  = blob;
	Tu const *volatile vxblob = xblob;
	void *volatile null = NULL;

	ISnull(bwlq(memchr)(null, 0, 0));
	ISnull(bwlq(memchr)(blob, 0, 0));
	EQ(blob + 0, bwlq(memchr)(blob, 0, lengthof(blob)));
	EQ(blob + 1, bwlq(memchr)(blob, 1, lengthof(blob)));
	EQ(blob + 2, bwlq(memchr)(blob, 2, lengthof(blob)));
	EQ(blob + 3, bwlq(memchr)(blob, 3, lengthof(blob)));
	EQ(blob + 4, bwlq(memchr)(blob, 4, lengthof(blob)));
	EQ(blob + 5, bwlq(memchr)(blob, 5, lengthof(blob)));
	EQ(blob + 6, bwlq(memchr)(blob, 6, lengthof(blob)));
	EQ(blob + 7, bwlq(memchr)(blob, 7, lengthof(blob)));
	EQ(blob + 8, bwlq(memchr)(blob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memchr)(blob, 9, lengthof(blob)));
	ISnull(bwlq(memchr)(blob, 10, lengthof(blob)));

	ISnull(bwlq(memchr)(vblob, 0, 0));
	EQ(blob + 0, bwlq(memchr)(vblob, 0, lengthof(blob)));
	EQ(blob + 1, bwlq(memchr)(vblob, 1, lengthof(blob)));
	EQ(blob + 2, bwlq(memchr)(vblob, 2, lengthof(blob)));
	EQ(blob + 3, bwlq(memchr)(vblob, 3, lengthof(blob)));
	EQ(blob + 4, bwlq(memchr)(vblob, 4, lengthof(blob)));
	EQ(blob + 5, bwlq(memchr)(vblob, 5, lengthof(blob)));
	EQ(blob + 6, bwlq(memchr)(vblob, 6, lengthof(blob)));
	EQ(blob + 7, bwlq(memchr)(vblob, 7, lengthof(blob)));
	EQ(blob + 8, bwlq(memchr)(vblob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memchr)(vblob, 9, lengthof(blob)));
	ISnull(bwlq(memchr)(vblob, 10, lengthof(blob)));

	ISnull(bwlq(memrchr)(null, 0, 0));
	ISnull(bwlq(memrchr)(blob, 0, 0));
	EQ(blob + 18, bwlq(memrchr)(blob, 0, lengthof(blob)));
	EQ(blob + 17, bwlq(memrchr)(blob, 1, lengthof(blob)));
	EQ(blob + 16, bwlq(memrchr)(blob, 2, lengthof(blob)));
	EQ(blob + 15, bwlq(memrchr)(blob, 3, lengthof(blob)));
	EQ(blob + 14, bwlq(memrchr)(blob, 4, lengthof(blob)));
	EQ(blob + 13, bwlq(memrchr)(blob, 5, lengthof(blob)));
	EQ(blob + 12, bwlq(memrchr)(blob, 6, lengthof(blob)));
	EQ(blob + 11, bwlq(memrchr)(blob, 7, lengthof(blob)));
	EQ(blob + 10, bwlq(memrchr)(blob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memrchr)(blob, 9, lengthof(blob)));
	ISnull(bwlq(memrchr)(blob, 10, lengthof(blob)));

	ISnull(bwlq(memrchr)(vblob, 0, 0));
	EQ(blob + 18, bwlq(memrchr)(vblob, 0, lengthof(blob)));
	EQ(blob + 17, bwlq(memrchr)(vblob, 1, lengthof(blob)));
	EQ(blob + 16, bwlq(memrchr)(vblob, 2, lengthof(blob)));
	EQ(blob + 15, bwlq(memrchr)(vblob, 3, lengthof(blob)));
	EQ(blob + 14, bwlq(memrchr)(vblob, 4, lengthof(blob)));
	EQ(blob + 13, bwlq(memrchr)(vblob, 5, lengthof(blob)));
	EQ(blob + 12, bwlq(memrchr)(vblob, 6, lengthof(blob)));
	EQ(blob + 11, bwlq(memrchr)(vblob, 7, lengthof(blob)));
	EQ(blob + 10, bwlq(memrchr)(vblob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memrchr)(vblob, 9, lengthof(blob)));
	ISnull(bwlq(memrchr)(vblob, 10, lengthof(blob)));

	EQ(blob + 0, bwlq(memend)(blob, 0, 0));
	EQ(blob + 0, bwlq(memend)(blob, 10, 0));
	EQ(blob + 0, bwlq(memend)(blob, 0, lengthof(blob)));
	EQ(blob + 1, bwlq(memend)(blob, 1, lengthof(blob)));
	EQ(blob + 2, bwlq(memend)(blob, 2, lengthof(blob)));
	EQ(blob + 3, bwlq(memend)(blob, 3, lengthof(blob)));
	EQ(blob + 4, bwlq(memend)(blob, 4, lengthof(blob)));
	EQ(blob + 5, bwlq(memend)(blob, 5, lengthof(blob)));
	EQ(blob + 6, bwlq(memend)(blob, 6, lengthof(blob)));
	EQ(blob + 7, bwlq(memend)(blob, 7, lengthof(blob)));
	EQ(blob + 8, bwlq(memend)(blob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memend)(blob, 9, lengthof(blob)));
	EQ(COMPILER_ENDOF(blob), bwlq(memend)(blob, 10, lengthof(blob)));

	EQ(vblob - 1, bwlq(memrend)(blob, 0, 0));
	EQ(vblob - 1, bwlq(memrend)(blob, 10, 0));
	EQ(blob + 18, bwlq(memrend)(blob, 0, lengthof(blob)));
	EQ(blob + 17, bwlq(memrend)(blob, 1, lengthof(blob)));
	EQ(blob + 16, bwlq(memrend)(blob, 2, lengthof(blob)));
	EQ(blob + 15, bwlq(memrend)(blob, 3, lengthof(blob)));
	EQ(blob + 14, bwlq(memrend)(blob, 4, lengthof(blob)));
	EQ(blob + 13, bwlq(memrend)(blob, 5, lengthof(blob)));
	EQ(blob + 12, bwlq(memrend)(blob, 6, lengthof(blob)));
	EQ(blob + 11, bwlq(memrend)(blob, 7, lengthof(blob)));
	EQ(blob + 10, bwlq(memrend)(blob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memrend)(blob, 9, lengthof(blob)));
	EQ(vblob - 1, bwlq(memrend)(blob, 10, lengthof(blob)));

	EQ(blob + 0, bwlq(memend)(vblob, 0, 0));
	EQ(blob + 0, bwlq(memend)(vblob, 10, 0));
	EQ(blob + 0, bwlq(memend)(vblob, 0, lengthof(blob)));
	EQ(blob + 1, bwlq(memend)(vblob, 1, lengthof(blob)));
	EQ(blob + 2, bwlq(memend)(vblob, 2, lengthof(blob)));
	EQ(blob + 3, bwlq(memend)(vblob, 3, lengthof(blob)));
	EQ(blob + 4, bwlq(memend)(vblob, 4, lengthof(blob)));
	EQ(blob + 5, bwlq(memend)(vblob, 5, lengthof(blob)));
	EQ(blob + 6, bwlq(memend)(vblob, 6, lengthof(blob)));
	EQ(blob + 7, bwlq(memend)(vblob, 7, lengthof(blob)));
	EQ(blob + 8, bwlq(memend)(vblob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memend)(vblob, 9, lengthof(blob)));
	EQ(COMPILER_ENDOF(blob), bwlq(memend)(vblob, 10, lengthof(blob)));

	EQ(vblob - 1, bwlq(memrend)(blob, 0, 0));
	EQ(vblob - 1, bwlq(memrend)(blob, 10, 0));
	EQ(blob + 18, bwlq(memrend)(vblob, 0, lengthof(blob)));
	EQ(blob + 17, bwlq(memrend)(vblob, 1, lengthof(blob)));
	EQ(blob + 16, bwlq(memrend)(vblob, 2, lengthof(blob)));
	EQ(blob + 15, bwlq(memrend)(vblob, 3, lengthof(blob)));
	EQ(blob + 14, bwlq(memrend)(vblob, 4, lengthof(blob)));
	EQ(blob + 13, bwlq(memrend)(vblob, 5, lengthof(blob)));
	EQ(blob + 12, bwlq(memrend)(vblob, 6, lengthof(blob)));
	EQ(blob + 11, bwlq(memrend)(vblob, 7, lengthof(blob)));
	EQ(blob + 10, bwlq(memrend)(vblob, 8, lengthof(blob)));
	EQ(blob + 9, bwlq(memrend)(vblob, 9, lengthof(blob)));
	EQ(vblob - 1, bwlq(memrend)(vblob, 10, lengthof(blob)));

	EQ(0, bwlq(memlen)(null, 0, 0));
	EQ(0, bwlq(memlen)(blob, 0, 0));
	EQ(0, bwlq(memlen)(blob, 10, 0));
	EQ(0, bwlq(memlen)(blob, 0, lengthof(blob)));
	EQ(1, bwlq(memlen)(blob, 1, lengthof(blob)));
	EQ(2, bwlq(memlen)(blob, 2, lengthof(blob)));
	EQ(3, bwlq(memlen)(blob, 3, lengthof(blob)));
	EQ(4, bwlq(memlen)(blob, 4, lengthof(blob)));
	EQ(5, bwlq(memlen)(blob, 5, lengthof(blob)));
	EQ(6, bwlq(memlen)(blob, 6, lengthof(blob)));
	EQ(7, bwlq(memlen)(blob, 7, lengthof(blob)));
	EQ(8, bwlq(memlen)(blob, 8, lengthof(blob)));
	EQ(9, bwlq(memlen)(blob, 9, lengthof(blob)));
	EQ(lengthof(blob), bwlq(memlen)(blob, 10, lengthof(blob)));

	EQ((size_t)-1, bwlq(memrlen)(null, 0, 0));
	EQ((size_t)-1, bwlq(memrlen)(blob, 0, 0));
	EQ((size_t)-1, bwlq(memrlen)(blob, 10, 0));
	EQ(18, bwlq(memrlen)(blob, 0, lengthof(blob)));
	EQ(17, bwlq(memrlen)(blob, 1, lengthof(blob)));
	EQ(16, bwlq(memrlen)(blob, 2, lengthof(blob)));
	EQ(15, bwlq(memrlen)(blob, 3, lengthof(blob)));
	EQ(14, bwlq(memrlen)(blob, 4, lengthof(blob)));
	EQ(13, bwlq(memrlen)(blob, 5, lengthof(blob)));
	EQ(12, bwlq(memrlen)(blob, 6, lengthof(blob)));
	EQ(11, bwlq(memrlen)(blob, 7, lengthof(blob)));
	EQ(10, bwlq(memrlen)(blob, 8, lengthof(blob)));
	EQ(9, bwlq(memrlen)(blob, 9, lengthof(blob)));
	EQ((size_t)-1, bwlq(memrlen)(blob, 10, lengthof(blob)));

	EQ(0, bwlq(memlen)(vblob, 0, 0));
	EQ(0, bwlq(memlen)(vblob, 10, 0));
	EQ(0, bwlq(memlen)(vblob, 0, lengthof(blob)));
	EQ(1, bwlq(memlen)(vblob, 1, lengthof(blob)));
	EQ(2, bwlq(memlen)(vblob, 2, lengthof(blob)));
	EQ(3, bwlq(memlen)(vblob, 3, lengthof(blob)));
	EQ(4, bwlq(memlen)(vblob, 4, lengthof(blob)));
	EQ(5, bwlq(memlen)(vblob, 5, lengthof(blob)));
	EQ(6, bwlq(memlen)(vblob, 6, lengthof(blob)));
	EQ(7, bwlq(memlen)(vblob, 7, lengthof(blob)));
	EQ(8, bwlq(memlen)(vblob, 8, lengthof(blob)));
	EQ(9, bwlq(memlen)(vblob, 9, lengthof(blob)));
	EQ(lengthof(blob), bwlq(memlen)(vblob, 10, lengthof(blob)));

	EQ((size_t)-1, bwlq(memrlen)(vblob, 0, 0));
	EQ((size_t)-1, bwlq(memrlen)(vblob, 10, 0));
	EQ(18, bwlq(memrlen)(vblob, 0, lengthof(blob)));
	EQ(17, bwlq(memrlen)(vblob, 1, lengthof(blob)));
	EQ(16, bwlq(memrlen)(vblob, 2, lengthof(blob)));
	EQ(15, bwlq(memrlen)(vblob, 3, lengthof(blob)));
	EQ(14, bwlq(memrlen)(vblob, 4, lengthof(blob)));
	EQ(13, bwlq(memrlen)(vblob, 5, lengthof(blob)));
	EQ(12, bwlq(memrlen)(vblob, 6, lengthof(blob)));
	EQ(11, bwlq(memrlen)(vblob, 7, lengthof(blob)));
	EQ(10, bwlq(memrlen)(vblob, 8, lengthof(blob)));
	EQ(9, bwlq(memrlen)(vblob, 9, lengthof(blob)));
	EQ((size_t)-1, bwlq(memrlen)(vblob, 10, lengthof(blob)));

	EQ(blob + 0, bwlq(rawmemchr)(blob, 0));
	EQ(blob + 1, bwlq(rawmemchr)(blob, 1));
	EQ(blob + 2, bwlq(rawmemchr)(blob, 2));
	EQ(blob + 3, bwlq(rawmemchr)(blob, 3));
	EQ(blob + 4, bwlq(rawmemchr)(blob, 4));
	EQ(blob + 5, bwlq(rawmemchr)(blob, 5));
	EQ(blob + 6, bwlq(rawmemchr)(blob, 6));
	EQ(blob + 7, bwlq(rawmemchr)(blob, 7));
	EQ(blob + 8, bwlq(rawmemchr)(blob, 8));
	EQ(blob + 9, bwlq(rawmemchr)(blob, 9));

	EQ(blob + 0, bwlq(rawmemchr)(vblob, 0));
	EQ(blob + 1, bwlq(rawmemchr)(vblob, 1));
	EQ(blob + 2, bwlq(rawmemchr)(vblob, 2));
	EQ(blob + 3, bwlq(rawmemchr)(vblob, 3));
	EQ(blob + 4, bwlq(rawmemchr)(vblob, 4));
	EQ(blob + 5, bwlq(rawmemchr)(vblob, 5));
	EQ(blob + 6, bwlq(rawmemchr)(vblob, 6));
	EQ(blob + 7, bwlq(rawmemchr)(vblob, 7));
	EQ(blob + 8, bwlq(rawmemchr)(vblob, 8));
	EQ(blob + 9, bwlq(rawmemchr)(vblob, 9));

	EQ(blob + 18, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 0));
	EQ(blob + 17, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 1));
	EQ(blob + 16, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 2));
	EQ(blob + 15, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 3));
	EQ(blob + 14, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 4));
	EQ(blob + 13, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 5));
	EQ(blob + 12, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 6));
	EQ(blob + 11, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 7));
	EQ(blob + 10, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 8));
	EQ(blob + 9, bwlq(rawmemrchr)(COMPILER_ENDOF(blob), 9));

	EQ(blob + 18, bwlq(rawmemrchr)(vblob + lengthof(blob), 0));
	EQ(blob + 17, bwlq(rawmemrchr)(vblob + lengthof(blob), 1));
	EQ(blob + 16, bwlq(rawmemrchr)(vblob + lengthof(blob), 2));
	EQ(blob + 15, bwlq(rawmemrchr)(vblob + lengthof(blob), 3));
	EQ(blob + 14, bwlq(rawmemrchr)(vblob + lengthof(blob), 4));
	EQ(blob + 13, bwlq(rawmemrchr)(vblob + lengthof(blob), 5));
	EQ(blob + 12, bwlq(rawmemrchr)(vblob + lengthof(blob), 6));
	EQ(blob + 11, bwlq(rawmemrchr)(vblob + lengthof(blob), 7));
	EQ(blob + 10, bwlq(rawmemrchr)(vblob + lengthof(blob), 8));
	EQ(blob + 9, bwlq(rawmemrchr)(vblob + lengthof(blob), 9));

	EQ(0, bwlq(rawmemlen)(blob, 0));
	EQ(1, bwlq(rawmemlen)(blob, 1));
	EQ(2, bwlq(rawmemlen)(blob, 2));
	EQ(3, bwlq(rawmemlen)(blob, 3));
	EQ(4, bwlq(rawmemlen)(blob, 4));
	EQ(5, bwlq(rawmemlen)(blob, 5));
	EQ(6, bwlq(rawmemlen)(blob, 6));
	EQ(7, bwlq(rawmemlen)(blob, 7));
	EQ(8, bwlq(rawmemlen)(blob, 8));
	EQ(9, bwlq(rawmemlen)(blob, 9));

	EQ(0, bwlq(rawmemlen)(vblob, 0));
	EQ(1, bwlq(rawmemlen)(vblob, 1));
	EQ(2, bwlq(rawmemlen)(vblob, 2));
	EQ(3, bwlq(rawmemlen)(vblob, 3));
	EQ(4, bwlq(rawmemlen)(vblob, 4));
	EQ(5, bwlq(rawmemlen)(vblob, 5));
	EQ(6, bwlq(rawmemlen)(vblob, 6));
	EQ(7, bwlq(rawmemlen)(vblob, 7));
	EQ(8, bwlq(rawmemlen)(vblob, 8));
	EQ(9, bwlq(rawmemlen)(vblob, 9));

	EQ((size_t)-1, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 0));
	EQ((size_t)-2, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 1));
	EQ((size_t)-3, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 2));
	EQ((size_t)-4, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 3));
	EQ((size_t)-5, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 4));
	EQ((size_t)-6, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 5));
	EQ((size_t)-7, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 6));
	EQ((size_t)-8, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 7));
	EQ((size_t)-9, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 8));
	EQ((size_t)-10, bwlq(rawmemrlen)(COMPILER_ENDOF(blob), 9));

	EQ((size_t)-1, bwlq(rawmemrlen)(vblob + lengthof(blob), 0));
	EQ((size_t)-2, bwlq(rawmemrlen)(vblob + lengthof(blob), 1));
	EQ((size_t)-3, bwlq(rawmemrlen)(vblob + lengthof(blob), 2));
	EQ((size_t)-4, bwlq(rawmemrlen)(vblob + lengthof(blob), 3));
	EQ((size_t)-5, bwlq(rawmemrlen)(vblob + lengthof(blob), 4));
	EQ((size_t)-6, bwlq(rawmemrlen)(vblob + lengthof(blob), 5));
	EQ((size_t)-7, bwlq(rawmemrlen)(vblob + lengthof(blob), 6));
	EQ((size_t)-8, bwlq(rawmemrlen)(vblob + lengthof(blob), 7));
	EQ((size_t)-9, bwlq(rawmemrlen)(vblob + lengthof(blob), 8));
	EQ((size_t)-10, bwlq(rawmemrlen)(vblob + lengthof(blob), 9));

	/* XCHR functions */
	EQ(xblob + 9, bwlq(memxchr)(xblob, 5, lengthof(xblob)));
	EQ(xblob + 9, bwlq(memxchr)(vxblob, 5, lengthof(xblob)));
	ISnull(bwlq(memxchr)(xblob, 5, 9));
	ISnull(bwlq(memxchr)(vxblob, 5, 9));
	EQ(xblob + 9, bwlq(memxchr)(xblob, 5, 10));
	EQ(xblob + 9, bwlq(memxchr)(vxblob, 5, 10));
	ISnull(bwlq(memxchr)(xblob + 9, 5, 0));
	ISnull(bwlq(memxchr)(vxblob + 9, 5, 0));
	EQ(xblob + 9, bwlq(memxchr)(xblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memxchr)(vxblob + 9, 5, 1));

	EQ(xblob + 9, bwlq(memrxchr)(xblob, 5, lengthof(xblob)));
	EQ(xblob + 9, bwlq(memrxchr)(vxblob, 5, lengthof(xblob)));
	ISnull(bwlq(memrxchr)(xblob, 5, 9));
	ISnull(bwlq(memrxchr)(vxblob, 5, 9));
	EQ(xblob + 9, bwlq(memrxchr)(xblob, 5, 10));
	EQ(xblob + 9, bwlq(memrxchr)(vxblob, 5, 10));
	ISnull(bwlq(memrxchr)(xblob + 9, 5, 0));
	ISnull(bwlq(memrxchr)(vxblob + 9, 5, 0));
	EQ(xblob + 9, bwlq(memrxchr)(xblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memrxchr)(vxblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memrxchr)(xblob + 9, 5, 2));
	EQ(xblob + 9, bwlq(memrxchr)(vxblob + 9, 5, 2));

	EQ(xblob + 9, bwlq(memxend)(xblob, 5, lengthof(xblob)));
	EQ(xblob + 9, bwlq(memxend)(vxblob, 5, lengthof(xblob)));
	EQ(xblob + 9, bwlq(memxend)(xblob, 5, 10));
	EQ(xblob + 9, bwlq(memxend)(vxblob, 5, 10));
	EQ(xblob + 9, bwlq(memxend)(xblob, 5, 9));
	EQ(xblob + 9, bwlq(memxend)(vxblob, 5, 9));
	EQ(xblob + 8, bwlq(memxend)(xblob, 5, 8));
	EQ(xblob + 8, bwlq(memxend)(vxblob, 5, 8));
	EQ(xblob + 9, bwlq(memxend)(xblob + 9, 5, 0));
	EQ(xblob + 9, bwlq(memxend)(vxblob + 9, 5, 0));
	EQ(xblob + 9, bwlq(memxend)(xblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memxend)(vxblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memxend)(xblob + 8, 5, 1));
	EQ(xblob + 9, bwlq(memxend)(vxblob + 8, 5, 1));
	EQ(xblob + 9, bwlq(memxend)(xblob + 8, 5, 2));
	EQ(xblob + 9, bwlq(memxend)(vxblob + 8, 5, 2));

	EQ(xblob + 9, bwlq(memrxend)(xblob, 5, lengthof(xblob)));
	EQ(xblob + 9, bwlq(memrxend)(vxblob, 5, lengthof(xblob)));
	EQ(vxblob - 1, bwlq(memrxend)(xblob, 5, 9));
	EQ(vxblob - 1, bwlq(memrxend)(vxblob, 5, 9));
	EQ(xblob + 9, bwlq(memrxend)(xblob + 9, 5, 1));
	EQ(xblob + 9, bwlq(memrxend)(vxblob + 9, 5, 1));
	EQ(xblob + 8, bwlq(memrxend)(xblob + 9, 5, 0));
	EQ(xblob + 8, bwlq(memrxend)(vxblob + 9, 5, 0));

	EQ(9, bwlq(memxlen)(xblob, 5, lengthof(xblob)));
	EQ(9, bwlq(memxlen)(vxblob, 5, lengthof(xblob)));
	EQ(9, bwlq(memxlen)(xblob, 5, 9));
	EQ(9, bwlq(memxlen)(vxblob, 5, 9));
	EQ(8, bwlq(memxlen)(xblob, 5, 8));
	EQ(8, bwlq(memxlen)(vxblob, 5, 8));
	EQ(0, bwlq(memxlen)(xblob + 9, 5, 0));
	EQ(0, bwlq(memxlen)(vxblob + 9, 5, 0));
	EQ(0, bwlq(memxlen)(xblob + 9, 5, 1));
	EQ(0, bwlq(memxlen)(vxblob + 9, 5, 1));
	EQ(1, bwlq(memxlen)(xblob + 8, 5, 1));
	EQ(1, bwlq(memxlen)(vxblob + 8, 5, 1));
	EQ(1, bwlq(memxlen)(xblob + 8, 5, 2));
	EQ(1, bwlq(memxlen)(vxblob + 8, 5, 2));

	EQ(9, bwlq(memrxlen)(xblob, 5, lengthof(xblob)));
	EQ(9, bwlq(memrxlen)(vxblob, 5, lengthof(xblob)));
	EQ((size_t)-1, bwlq(memrxlen)(xblob, 5, 9));
	EQ((size_t)-1, bwlq(memrxlen)(vxblob, 5, 9));
	EQ(0, bwlq(memrxlen)(xblob + 9, 5, 1));
	EQ(0, bwlq(memrxlen)(vxblob + 9, 5, 1));
	EQ((size_t)-1, bwlq(memrxlen)(xblob + 9, 5, 0));
	EQ((size_t)-1, bwlq(memrxlen)(vxblob + 9, 5, 0));

	EQ(xblob + 9, bwlq(rawmemxchr)(xblob, 5));
	EQ(xblob + 9, bwlq(rawmemxchr)(vxblob, 5));
	EQ(xblob + 9, bwlq(rawmemxchr)(xblob + 9, 5));
	EQ(xblob + 9, bwlq(rawmemxchr)(vxblob + 9, 5));

	EQ(xblob + 9, bwlq(rawmemrxchr)(COMPILER_ENDOF(xblob), 5));
	EQ(xblob + 9, bwlq(rawmemrxchr)(vxblob + lengthof(xblob), 5));
	EQ(xblob + 9, bwlq(rawmemrxchr)(xblob + 10, 5));
	EQ(xblob + 9, bwlq(rawmemrxchr)(vxblob + 10, 5));

	EQ(9, bwlq(rawmemxlen)(xblob, 5));
	EQ(9, bwlq(rawmemxlen)(vxblob, 5));
	EQ(0, bwlq(rawmemxlen)(xblob + 9, 5));
	EQ(0, bwlq(rawmemxlen)(vxblob + 9, 5));

	EQ((size_t)-10, bwlq(rawmemrxlen)(COMPILER_ENDOF(xblob), 5));
	EQ((size_t)-10, bwlq(rawmemrxlen)(vxblob + lengthof(xblob), 5));
	EQ((size_t)-1, bwlq(rawmemrxlen)(xblob + 10, 5));
	EQ((size_t)-1, bwlq(rawmemrxlen)(vxblob + 10, 5));
}

DECL_END

#undef Ts
#undef Tu
#undef bwlq
#undef N
