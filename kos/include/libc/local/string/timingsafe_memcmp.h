/* HASH CRC-32:0xf6ebce2e */
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
#ifndef __local_timingsafe_memcmp_defined
#define __local_timingsafe_memcmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <asm/signed-shift.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(timingsafe_memcmp) __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timingsafe_memcmp))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) {
	int __result = 0, __finished = 0;
	/* Suppress warnings about ATTR_PURE. Even though they're correct,
	 * don't mark  this function  as `pure'  to prevent  any  compiler
	 * optimizations which  may result  in  the `timingsafe'  part  of
	 * this function's purpose no longer being correct. */
	__COMPILER_IMPURE();
	while (__n_bytes) {
		int __a_le_b, __a_gr_b, __diff;
		__SBYTE_TYPE__ __a, __b;
		__a = *(__SBYTE_TYPE__ const *)__s1;
		__b = *(__SBYTE_TYPE__ const *)__s2;

		/* a_le_b:
		 *    0  <=> a <= b <=> 0b0???????
		 *   -1  <=> a >  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_le_b = a <= b ? 0 : -1; */
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
		__a_le_b = (int)((__b - __a) >> (__CHAR_BIT__ - 1));
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
		__a_le_b = (int)((__b - __a) / (1 << (__CHAR_BIT__ - 1)));
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */

		/* a_gr_b:
		 *    0  <=> a >= b <=> 0b0???????
		 *   -1  <=> a <  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_gr_b = a >= b ? 0 : -1; */
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
		__a_gr_b = (int)((__a - __b) >> (__CHAR_BIT__ - 1));
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
		__a_gr_b = (int)((__a - __b) / (1 << (__CHAR_BIT__ - 1)));
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */

		/* a <  b  <=>  [a_le_b= 0,a_gr_b=-1]   -> diff=-1
		 * a == b  <=>  [a_le_b= 0,a_gr_b= 0]   -> diff= 0
		 * a >  b  <=>  [a_le_b=-1,a_gr_b= 0]   -> diff=+1 */
		__diff = __a_gr_b - __a_le_b;

		/* (finished == 0) <=> (~finished != 0)
		 * (finished == 0) <=> {All preceding bytes were equal}
		 *
		 * >> if ({All preceding bytes were equal})
		 * >>     result = diff; */
		__result |= __diff & ~__finished;

		/* ((a_gr_b | a_le_b) == -1)  <=>  {a != b}
		 *
		 * >> if (a != b)
		 * >>     finished = -1; */
		__finished |= __a_gr_b | __a_le_b;

		__s1 = (__SBYTE_TYPE__ const *)__s1 + 1;
		__s2 = (__SBYTE_TYPE__ const *)__s2 + 1;
		--__n_bytes;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timingsafe_memcmp_defined
#define __local___localdep_timingsafe_memcmp_defined
#define __localdep_timingsafe_memcmp __LIBC_LOCAL_NAME(timingsafe_memcmp)
#endif /* !__local___localdep_timingsafe_memcmp_defined */
#endif /* !__local_timingsafe_memcmp_defined */
