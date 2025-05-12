/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_HYBRID_BITS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_HYBRID_BITS_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <hybrid/bit.h>

#include <kos/kernel/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <stdint.h>

DECL_BEGIN

#define ASSERT_BITCALL_1(expected, func, pure_func, Targ0, arg0)                                             \
	{                                                                                                        \
		Targ0 _arg0           = (arg0);                                                                      \
		Targ0 volatile _varg0 = _arg0;                                                                       \
		assertf(func(_arg0) == (expected), "func(_arg0) = %u", (unsigned int)func(_arg0));                   \
		assertf(func(_varg0) == (expected), "func(_varg0) = %u", (unsigned int)func(_varg0));                \
		assertf(pure_func(_arg0) == (expected), "pure_func(_arg0) = %u", (unsigned int)pure_func(_arg0));    \
		assertf(pure_func(_varg0) == (expected), "pure_func(_varg0) = %u", (unsigned int)pure_func(_varg0)); \
	}

#ifdef __HYBRID_BIT_NO_BUILTIN
DEFINE_TEST(hybrid_bits_nobuiltin)
#else /* __HYBRID_BIT_NO_BUILTIN */
DEFINE_TEST(hybrid_bits)
#endif /* !__HYBRID_BIT_NO_BUILTIN */
{
	/* Make sure that functions from <hybrid/bit.h> work correctly */

	/* FFS (FindFirstSet) */
	ASSERT_BITCALL_1(0, FFS, __hybrid_ffs8, u8, 0);
	ASSERT_BITCALL_1(0, FFS, __hybrid_ffs16, u16, 0);
	ASSERT_BITCALL_1(0, FFS, __hybrid_ffs32, u32, 0);
	ASSERT_BITCALL_1(0, FFS, __hybrid_ffs64, u64, 0);

	ASSERT_BITCALL_1(1, FFS, __hybrid_ffs8, u8, 1);
	ASSERT_BITCALL_1(1, FFS, __hybrid_ffs16, u16, 1);
	ASSERT_BITCALL_1(1, FFS, __hybrid_ffs32, u32, 1);
	ASSERT_BITCALL_1(1, FFS, __hybrid_ffs64, u64, 1);

	ASSERT_BITCALL_1(8, FFS, __hybrid_ffs8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(16, FFS, __hybrid_ffs16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(32, FFS, __hybrid_ffs32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(64, FFS, __hybrid_ffs64, u64, UINT64_C(0x8000000000000000));

	/* CLZ (CountLeadingZeroes) */
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz64, u64, UINT64_C(0x8000000000000000));

	ASSERT_BITCALL_1(7, CLZ, __hybrid_clz8, u8, UINT8_C(0x01));
	ASSERT_BITCALL_1(15, CLZ, __hybrid_clz16, u16, UINT16_C(0x0001));
	ASSERT_BITCALL_1(31, CLZ, __hybrid_clz32, u32, UINT32_C(0x00000001));
	ASSERT_BITCALL_1(63, CLZ, __hybrid_clz64, u64, UINT64_C(0x0000000000000001));

	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz8, u8, UINT8_C(0x81));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz16, u16, UINT16_C(0x8001));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz32, u32, UINT32_C(0x80000001));
	ASSERT_BITCALL_1(0, CLZ, __hybrid_clz64, u64, UINT64_C(0x8000000000000001));

	/* CTZ (CountTrailingZeroes) */
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz8, u8, UINT8_C(0x01));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz16, u16, UINT16_C(0x0001));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz32, u32, UINT32_C(0x00000001));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz64, u64, UINT64_C(0x0000000000000001));

	ASSERT_BITCALL_1(7, CTZ, __hybrid_ctz8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(15, CTZ, __hybrid_ctz16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(31, CTZ, __hybrid_ctz32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(63, CTZ, __hybrid_ctz64, u64, UINT64_C(0x8000000000000000));

	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz8, u8, UINT8_C(0x81));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz16, u16, UINT16_C(0x8001));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz32, u32, UINT32_C(0x80000001));
	ASSERT_BITCALL_1(0, CTZ, __hybrid_ctz64, u64, UINT64_C(0x8000000000000001));

	/* POPCOUNT (PopulationCount) */
	ASSERT_BITCALL_1(0, POPCOUNT, __hybrid_popcount8, u8, 0);
	ASSERT_BITCALL_1(0, POPCOUNT, __hybrid_popcount16, u16, 0);
	ASSERT_BITCALL_1(0, POPCOUNT, __hybrid_popcount32, u32, 0);
	ASSERT_BITCALL_1(0, POPCOUNT, __hybrid_popcount64, u64, 0);

	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount8, u8, 1);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount16, u16, 1);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount32, u32, 1);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount64, u64, 1);

	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount8, u8, 2);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount16, u16, 2);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount32, u32, 2);
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount64, u64, 2);

	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(1, POPCOUNT, __hybrid_popcount64, u64, UINT64_C(0x8000000000000000));

	ASSERT_BITCALL_1(2, POPCOUNT, __hybrid_popcount8, u8, UINT8_C(0x81));
	ASSERT_BITCALL_1(2, POPCOUNT, __hybrid_popcount16, u16, UINT16_C(0x8001));
	ASSERT_BITCALL_1(2, POPCOUNT, __hybrid_popcount32, u32, UINT32_C(0x80000001));
	ASSERT_BITCALL_1(2, POPCOUNT, __hybrid_popcount64, u64, UINT64_C(0x8000000000000001));

	ASSERT_BITCALL_1(8, POPCOUNT, __hybrid_popcount8, u8, UINT8_C(0xff));
	ASSERT_BITCALL_1(16, POPCOUNT, __hybrid_popcount16, u16, UINT16_C(0xffff));
	ASSERT_BITCALL_1(32, POPCOUNT, __hybrid_popcount32, u32, UINT32_C(0xffffffff));
	ASSERT_BITCALL_1(64, POPCOUNT, __hybrid_popcount64, u64, UINT64_C(0xffffffffffffffff));

	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity8, u8, 0);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity16, u16, 0);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity32, u32, 0);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity64, u64, 0);

	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity8, u8, 1);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity16, u16, 1);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity32, u32, 1);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity64, u64, 1);

	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity8, u8, 2);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity16, u16, 2);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity32, u32, 2);
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity64, u64, 2);

	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity8, u8, 3);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity16, u16, 3);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity32, u32, 3);
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity64, u64, 3);

	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(1, PARITY, __hybrid_parity64, u64, UINT64_C(0x8000000000000000));

	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity8, u8, UINT8_C(0x81));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity16, u16, UINT16_C(0x8001));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity32, u32, UINT32_C(0x80000001));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity64, u64, UINT64_C(0x8000000000000001));

	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity8, u8, UINT8_C(0xff));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity16, u16, UINT16_C(0xffff));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity32, u32, UINT32_C(0xffffffff));
	ASSERT_BITCALL_1(0, PARITY, __hybrid_parity64, u64, UINT64_C(0xffffffffffffffff));

	/* CLRSB (CountLeadingRedundantSignBits) */
	ASSERT_BITCALL_1(7, CLRSB, __hybrid_clrsb8, u8, 0);
	ASSERT_BITCALL_1(15, CLRSB, __hybrid_clrsb16, u16, 0);
	ASSERT_BITCALL_1(31, CLRSB, __hybrid_clrsb32, u32, 0);
	ASSERT_BITCALL_1(63, CLRSB, __hybrid_clrsb64, u64, 0);

	ASSERT_BITCALL_1(6, CLRSB, __hybrid_clrsb8, u8, 1);
	ASSERT_BITCALL_1(14, CLRSB, __hybrid_clrsb16, u16, 1);
	ASSERT_BITCALL_1(30, CLRSB, __hybrid_clrsb32, u32, 1);
	ASSERT_BITCALL_1(62, CLRSB, __hybrid_clrsb64, u64, 1);

	ASSERT_BITCALL_1(7, CLRSB, __hybrid_clrsb8, u8, UINT8_C(0xff));
	ASSERT_BITCALL_1(15, CLRSB, __hybrid_clrsb16, u16, UINT16_C(0xffff));
	ASSERT_BITCALL_1(31, CLRSB, __hybrid_clrsb32, u32, UINT32_C(0xffffffff));
	ASSERT_BITCALL_1(63, CLRSB, __hybrid_clrsb64, u64, UINT64_C(0xffffffffffffffff));

	ASSERT_BITCALL_1(6, CLRSB, __hybrid_clrsb8, u8, UINT8_C(0xfe));
	ASSERT_BITCALL_1(14, CLRSB, __hybrid_clrsb16, u16, UINT16_C(0xfffe));
	ASSERT_BITCALL_1(30, CLRSB, __hybrid_clrsb32, u32, UINT32_C(0xfffffffe));
	ASSERT_BITCALL_1(62, CLRSB, __hybrid_clrsb64, u64, UINT64_C(0xfffffffffffffffe));

	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb8, u8, UINT8_C(0x80));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb16, u16, UINT16_C(0x8000));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb32, u32, UINT32_C(0x80000000));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb64, u64, UINT64_C(0x8000000000000000));

	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb8, u8, UINT8_C(0x81));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb16, u16, UINT16_C(0x8001));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb32, u32, UINT32_C(0x80000001));
	ASSERT_BITCALL_1(0, CLRSB, __hybrid_clrsb64, u64, UINT64_C(0x8000000000000001));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_HYBRID_BITS_C */
