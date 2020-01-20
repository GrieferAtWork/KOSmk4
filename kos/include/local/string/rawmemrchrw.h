/* HASH CRC-32:0xbd3b560d */
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
#ifndef __local_rawmemrchrw_defined
#define __local_rawmemrchrw_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__LOCAL_LIBC(rawmemrchrw) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrchrw))(/*aligned(2)*/ void const *__restrict __haystack,
                                                         __UINT16_TYPE__ __word) {
#line 1422 "kos/src/libc/magic/string.c"
	__UINT16_TYPE__ *__iter = (__UINT16_TYPE__ *)__haystack;
	for (;;) {
		if __unlikely(*--__iter == __word)
			break;
	}
	return __iter;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemrchrw_defined */
