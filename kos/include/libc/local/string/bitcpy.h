/* HASH CRC-32:0x71cbf537 */
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
#ifndef __local_bitcpy_defined
#define __local_bitcpy_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bitcpy) __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WR(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bitcpy))(void *__restrict __dst_base, __SIZE_TYPE__ __dst_bit_offset, void const *__restrict __src_base, __SIZE_TYPE__ __src_bit_offset, __SIZE_TYPE__ __num_bits) {
	while (__num_bits) {
		__BYTE_TYPE__ __remaining, __src_value, __remaining_temp;
		__src_base = (__BYTE_TYPE__ const *)__src_base + (__src_bit_offset / __CHAR_BIT__);
		__src_bit_offset %= __CHAR_BIT__;
		__remaining = (__BYTE_TYPE__)(__CHAR_BIT__ - __src_bit_offset);
		if ((__SIZE_TYPE__)__remaining > __num_bits)
			__remaining = (__BYTE_TYPE__)__num_bits;
		__src_value      = *(__BYTE_TYPE__ const *)__src_base >> __src_bit_offset;
		__remaining_temp = __remaining;
		while (__remaining_temp) {
			__BYTE_TYPE__ __avail, __dst_value;
			__dst_base = (__BYTE_TYPE__ *)__dst_base + (__dst_bit_offset / __CHAR_BIT__);
			__dst_bit_offset %= __CHAR_BIT__;
			__avail = (__BYTE_TYPE__)(__CHAR_BIT__ - __dst_bit_offset);
			if (__avail > __remaining_temp)
				__avail = __remaining_temp;
			__dst_value = *(__BYTE_TYPE__ *)__dst_base;
			__dst_value &= ~(((1 << __avail) - 1) << __dst_bit_offset);
			__dst_value |= (__src_value & ((1 << __avail) - 1)) << __dst_bit_offset;
			*(__BYTE_TYPE__ *)__dst_base = __dst_value;
			__dst_bit_offset += __avail;
			__remaining_temp -= __avail;
			__src_value >>= __avail;
		}
		__src_bit_offset += __remaining;
		__num_bits -= __remaining;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bitcpy_defined
#define __local___localdep_bitcpy_defined
#define __localdep_bitcpy __LIBC_LOCAL_NAME(bitcpy)
#endif /* !__local___localdep_bitcpy_defined */
#endif /* !__local_bitcpy_defined */
