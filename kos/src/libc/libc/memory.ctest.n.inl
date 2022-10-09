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
#define FUNC(name) name
#elif N == 1
#define FUNC(name) name##b
#elif N == 2
#define FUNC(name) name##w
#elif N == 4
#define FUNC(name) name##l
#elif N == 8
#define FUNC(name) name##q
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

#ifndef _ASSERT_EQ
#define _ASSERT_EQ(a, b, T, PRIFMT)                   \
	({                                                \
		T _a = (a);                                   \
		T _b = (b);                                   \
		if (_a != _b)                                 \
			__assertion_failedf(#a " == " #b,         \
			                    PRIFMT " != " PRIFMT, \
			                    _a, _b);              \
	})
#define ASSERT_EQ_PTR(a, b)    _ASSERT_EQ(a, b, void const *, "%p")
#define ASSERT_EQ_SIZE_T(a, b) _ASSERT_EQ(a, b, size_t, "%" PRIuSIZ)
#endif /* !_ASSERT_EQ */


PRIVATE void FUNC(do_test_memory)(void) {
	static Tu const blob[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	static Tu const xblob[]   = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
	Tu const *volatile vblob  = blob;
	Tu const *volatile vxblob = xblob;
	void *volatile null = NULL;

	ASSERT_EQ_PTR(FUNC(memchr)(null, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 0, lengthof(blob)), blob + 0);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 1, lengthof(blob)), blob + 1);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 2, lengthof(blob)), blob + 2);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 3, lengthof(blob)), blob + 3);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 4, lengthof(blob)), blob + 4);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 5, lengthof(blob)), blob + 5);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 6, lengthof(blob)), blob + 6);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 7, lengthof(blob)), blob + 7);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 8, lengthof(blob)), blob + 8);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memchr)(blob, 10, lengthof(blob)), NULL);

	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 0, lengthof(blob)), blob + 0);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 1, lengthof(blob)), blob + 1);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 2, lengthof(blob)), blob + 2);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 3, lengthof(blob)), blob + 3);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 4, lengthof(blob)), blob + 4);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 5, lengthof(blob)), blob + 5);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 6, lengthof(blob)), blob + 6);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 7, lengthof(blob)), blob + 7);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 8, lengthof(blob)), blob + 8);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memchr)(vblob, 10, lengthof(blob)), NULL);

	ASSERT_EQ_PTR(FUNC(memrchr)(null, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 0, lengthof(blob)), blob + 18);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 1, lengthof(blob)), blob + 17);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 2, lengthof(blob)), blob + 16);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 3, lengthof(blob)), blob + 15);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 4, lengthof(blob)), blob + 14);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 5, lengthof(blob)), blob + 13);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 6, lengthof(blob)), blob + 12);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 7, lengthof(blob)), blob + 11);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 8, lengthof(blob)), blob + 10);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memrchr)(blob, 10, lengthof(blob)), NULL);

	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 0, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 0, lengthof(blob)), blob + 18);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 1, lengthof(blob)), blob + 17);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 2, lengthof(blob)), blob + 16);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 3, lengthof(blob)), blob + 15);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 4, lengthof(blob)), blob + 14);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 5, lengthof(blob)), blob + 13);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 6, lengthof(blob)), blob + 12);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 7, lengthof(blob)), blob + 11);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 8, lengthof(blob)), blob + 10);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memrchr)(vblob, 10, lengthof(blob)), NULL);

	ASSERT_EQ_PTR(FUNC(memend)(blob, 0, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 10, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 0, lengthof(blob)), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 1, lengthof(blob)), blob + 1);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 2, lengthof(blob)), blob + 2);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 3, lengthof(blob)), blob + 3);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 4, lengthof(blob)), blob + 4);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 5, lengthof(blob)), blob + 5);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 6, lengthof(blob)), blob + 6);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 7, lengthof(blob)), blob + 7);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 8, lengthof(blob)), blob + 8);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memend)(blob, 10, lengthof(blob)), COMPILER_ENDOF(blob));

	ASSERT_EQ_PTR(FUNC(memrend)(blob, 0, 0), vblob - 1);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 10, 0), vblob - 1);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 0, lengthof(blob)), blob + 18);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 1, lengthof(blob)), blob + 17);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 2, lengthof(blob)), blob + 16);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 3, lengthof(blob)), blob + 15);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 4, lengthof(blob)), blob + 14);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 5, lengthof(blob)), blob + 13);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 6, lengthof(blob)), blob + 12);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 7, lengthof(blob)), blob + 11);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 8, lengthof(blob)), blob + 10);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 10, lengthof(blob)), vblob - 1);

	ASSERT_EQ_PTR(FUNC(memend)(vblob, 0, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 10, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 0, lengthof(blob)), blob + 0);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 1, lengthof(blob)), blob + 1);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 2, lengthof(blob)), blob + 2);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 3, lengthof(blob)), blob + 3);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 4, lengthof(blob)), blob + 4);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 5, lengthof(blob)), blob + 5);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 6, lengthof(blob)), blob + 6);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 7, lengthof(blob)), blob + 7);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 8, lengthof(blob)), blob + 8);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memend)(vblob, 10, lengthof(blob)), COMPILER_ENDOF(blob));

	ASSERT_EQ_PTR(FUNC(memrend)(blob, 0, 0), vblob - 1);
	ASSERT_EQ_PTR(FUNC(memrend)(blob, 10, 0), vblob - 1);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 0, lengthof(blob)), blob + 18);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 1, lengthof(blob)), blob + 17);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 2, lengthof(blob)), blob + 16);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 3, lengthof(blob)), blob + 15);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 4, lengthof(blob)), blob + 14);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 5, lengthof(blob)), blob + 13);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 6, lengthof(blob)), blob + 12);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 7, lengthof(blob)), blob + 11);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 8, lengthof(blob)), blob + 10);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 9, lengthof(blob)), blob + 9);
	ASSERT_EQ_PTR(FUNC(memrend)(vblob, 10, lengthof(blob)), vblob - 1);

	ASSERT_EQ_SIZE_T(FUNC(memlen)(null, 0, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 0, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 10, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 0, lengthof(blob)), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 1, lengthof(blob)), 1);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 2, lengthof(blob)), 2);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 3, lengthof(blob)), 3);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 4, lengthof(blob)), 4);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 5, lengthof(blob)), 5);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 6, lengthof(blob)), 6);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 7, lengthof(blob)), 7);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 8, lengthof(blob)), 8);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 9, lengthof(blob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(blob, 10, lengthof(blob)), lengthof(blob));

	ASSERT_EQ_SIZE_T(FUNC(memrlen)(null, 0, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 0, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 10, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 0, lengthof(blob)), 18);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 1, lengthof(blob)), 17);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 2, lengthof(blob)), 16);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 3, lengthof(blob)), 15);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 4, lengthof(blob)), 14);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 5, lengthof(blob)), 13);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 6, lengthof(blob)), 12);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 7, lengthof(blob)), 11);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 8, lengthof(blob)), 10);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 9, lengthof(blob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(blob, 10, lengthof(blob)), (size_t)-1);

	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 0, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 10, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 0, lengthof(blob)), 0);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 1, lengthof(blob)), 1);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 2, lengthof(blob)), 2);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 3, lengthof(blob)), 3);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 4, lengthof(blob)), 4);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 5, lengthof(blob)), 5);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 6, lengthof(blob)), 6);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 7, lengthof(blob)), 7);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 8, lengthof(blob)), 8);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 9, lengthof(blob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memlen)(vblob, 10, lengthof(blob)), lengthof(blob));

	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 0, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 10, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 0, lengthof(blob)), 18);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 1, lengthof(blob)), 17);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 2, lengthof(blob)), 16);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 3, lengthof(blob)), 15);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 4, lengthof(blob)), 14);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 5, lengthof(blob)), 13);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 6, lengthof(blob)), 12);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 7, lengthof(blob)), 11);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 8, lengthof(blob)), 10);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 9, lengthof(blob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memrlen)(vblob, 10, lengthof(blob)), (size_t)-1);

	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 1), blob + 1);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 2), blob + 2);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 3), blob + 3);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 4), blob + 4);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 5), blob + 5);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 6), blob + 6);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 7), blob + 7);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 8), blob + 8);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(blob, 9), blob + 9);

	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 0), blob + 0);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 1), blob + 1);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 2), blob + 2);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 3), blob + 3);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 4), blob + 4);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 5), blob + 5);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 6), blob + 6);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 7), blob + 7);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 8), blob + 8);
	ASSERT_EQ_PTR(FUNC(rawmemchr)(vblob, 9), blob + 9);

	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 0), blob + 18);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 1), blob + 17);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 2), blob + 16);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 3), blob + 15);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 4), blob + 14);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 5), blob + 13);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 6), blob + 12);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 7), blob + 11);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 8), blob + 10);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(COMPILER_ENDOF(blob), 9), blob + 9);

	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 0), blob + 18);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 1), blob + 17);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 2), blob + 16);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 3), blob + 15);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 4), blob + 14);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 5), blob + 13);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 6), blob + 12);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 7), blob + 11);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 8), blob + 10);
	ASSERT_EQ_PTR(FUNC(rawmemrchr)(vblob + lengthof(blob), 9), blob + 9);

	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 1), 1);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 2), 2);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 3), 3);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 4), 4);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 5), 5);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 6), 6);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 7), 7);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 8), 8);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(blob, 9), 9);

	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 1), 1);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 2), 2);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 3), 3);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 4), 4);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 5), 5);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 6), 6);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 7), 7);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 8), 8);
	ASSERT_EQ_SIZE_T(FUNC(rawmemlen)(vblob, 9), 9);

	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 1), (size_t)-2);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 2), (size_t)-3);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 3), (size_t)-4);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 4), (size_t)-5);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 5), (size_t)-6);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 6), (size_t)-7);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 7), (size_t)-8);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 8), (size_t)-9);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(COMPILER_ENDOF(blob), 9), (size_t)-10);

	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 1), (size_t)-2);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 2), (size_t)-3);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 3), (size_t)-4);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 4), (size_t)-5);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 5), (size_t)-6);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 6), (size_t)-7);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 7), (size_t)-8);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 8), (size_t)-9);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrlen)(vblob + lengthof(blob), 9), (size_t)-10);

	/* XCHR functions */
	ASSERT_EQ_PTR(FUNC(memxchr)(xblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxchr)(vxblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxchr)(xblob, 5, 9), NULL);
	ASSERT_EQ_PTR(FUNC(memxchr)(vxblob, 5, 9), NULL);
	ASSERT_EQ_PTR(FUNC(memxchr)(xblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxchr)(vxblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxchr)(xblob + 9, 5, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memxchr)(vxblob + 9, 5, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memxchr)(xblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxchr)(vxblob + 9, 5, 1), xblob + 9);

	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob, 5, 9), NULL);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob, 5, 9), NULL);
	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob + 9, 5, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob + 9, 5, 0), NULL);
	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(xblob + 9, 5, 2), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxchr)(vxblob + 9, 5, 2), xblob + 9);

	ASSERT_EQ_PTR(FUNC(memxend)(xblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob, 5, 10), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob, 5, 9), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob, 5, 9), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob, 5, 8), xblob + 8);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob, 5, 8), xblob + 8);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob + 9, 5, 0), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob + 9, 5, 0), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob + 8, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob + 8, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(xblob + 8, 5, 2), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memxend)(vxblob + 8, 5, 2), xblob + 9);

	ASSERT_EQ_PTR(FUNC(memrxend)(xblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxend)(vxblob, 5, lengthof(xblob)), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxend)(xblob, 5, 9), vxblob - 1);
	ASSERT_EQ_PTR(FUNC(memrxend)(vxblob, 5, 9), vxblob - 1);
	ASSERT_EQ_PTR(FUNC(memrxend)(xblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxend)(vxblob + 9, 5, 1), xblob + 9);
	ASSERT_EQ_PTR(FUNC(memrxend)(xblob + 9, 5, 0), xblob + 8);
	ASSERT_EQ_PTR(FUNC(memrxend)(vxblob + 9, 5, 0), xblob + 8);

	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob, 5, lengthof(xblob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob, 5, lengthof(xblob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob, 5, 9), 9);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob, 5, 9), 9);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob, 5, 8), 8);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob, 5, 8), 8);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob + 9, 5, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob + 9, 5, 0), 0);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob + 9, 5, 1), 0);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob + 9, 5, 1), 0);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob + 8, 5, 1), 1);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob + 8, 5, 1), 1);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(xblob + 8, 5, 2), 1);
	ASSERT_EQ_SIZE_T(FUNC(memxlen)(vxblob + 8, 5, 2), 1);

	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(xblob, 5, lengthof(xblob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(vxblob, 5, lengthof(xblob)), 9);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(xblob, 5, 9), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(vxblob, 5, 9), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(xblob + 9, 5, 1), 0);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(vxblob + 9, 5, 1), 0);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(xblob + 9, 5, 0), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(memrxlen)(vxblob + 9, 5, 0), (size_t)-1);

	ASSERT_EQ_PTR(FUNC(rawmemxchr)(xblob, 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemxchr)(vxblob, 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemxchr)(xblob + 9, 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemxchr)(vxblob + 9, 5), xblob + 9);

	ASSERT_EQ_PTR(FUNC(rawmemrxchr)(COMPILER_ENDOF(xblob), 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemrxchr)(vxblob + lengthof(xblob), 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemrxchr)(xblob + 10, 5), xblob + 9);
	ASSERT_EQ_PTR(FUNC(rawmemrxchr)(vxblob + 10, 5), xblob + 9);

	ASSERT_EQ_SIZE_T(FUNC(rawmemxlen)(xblob, 5), 9);
	ASSERT_EQ_SIZE_T(FUNC(rawmemxlen)(vxblob, 5), 9);
	ASSERT_EQ_SIZE_T(FUNC(rawmemxlen)(xblob + 9, 5), 0);
	ASSERT_EQ_SIZE_T(FUNC(rawmemxlen)(vxblob + 9, 5), 0);

	ASSERT_EQ_SIZE_T(FUNC(rawmemrxlen)(COMPILER_ENDOF(xblob), 5), (size_t)-10);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrxlen)(vxblob + lengthof(xblob), 5), (size_t)-10);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrxlen)(xblob + 10, 5), (size_t)-1);
	ASSERT_EQ_SIZE_T(FUNC(rawmemrxlen)(vxblob + 10, 5), (size_t)-1);
}

DECL_END

#undef Ts
#undef Tu
#undef FUNC
#undef N
