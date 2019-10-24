/* HASH CRC-32:0x3b4549d */
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
#ifndef __local_swab_defined
#define __local_swab_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__LOCAL_LIBC(swab) __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(swab))(void const *__restrict __from,
                                                  void *__restrict __to,
                                                  __STDC_INT_AS_SSIZE_T __n_bytes) {
#line 1698 "kos/src/libc/magic/unistd.c"
	__n_bytes &= ~1;
	while (__n_bytes >= 2) {
		__BYTE_TYPE__ __a, __b;
		__a = ((__BYTE_TYPE__ *)__from)[--__n_bytes];
		__b = ((__BYTE_TYPE__ *)__from)[--__n_bytes];
		((__BYTE_TYPE__ *)__to)[__n_bytes+0] = __a;
		((__BYTE_TYPE__ *)__to)[__n_bytes+1] = __b;
	}
}
__NAMESPACE_LOCAL_END
#endif /* !__local_swab_defined */
