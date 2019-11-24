/* HASH CRC-32:0x14d1ea6a */
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
#ifndef __local_memmovedownw_defined
#define __local_memmovedownw_defined 1
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__LOCAL_LIBC(memmovedownw) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovedownw))(/*aligned(2)*/ void *__dst,
                                                          /*aligned(2)*/ void const *__src,
                                                          __SIZE_TYPE__ __n_words) {
#line 1115 "kos/src/libc/magic/string.c"
	__UINT16_TYPE__ *__pdst, *__psrc;
	__pdst = (__UINT16_TYPE__ *)__dst;
	__psrc = (__UINT16_TYPE__ *)__src;
	__hybrid_assert(__pdst <= __psrc || !__n_words);
	while (__n_words--)
		*__pdst++ = *__psrc++;
	return (__UINT16_TYPE__ *)__dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memmovedownw_defined */
