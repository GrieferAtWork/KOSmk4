/* HASH 0xf0882290 */
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
#ifndef __local_memmove_defined
#define __local_memmove_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. */
__LOCAL_LIBC(memmove) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmove))(void *__dst,
                                                     void const *__src,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 148 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__pdst, *__psrc;
	if (__dst < __src) {
		__pdst = (__BYTE_TYPE__ *)__dst;
		__psrc = (__BYTE_TYPE__ *)__src;
		while (__n_bytes--)
			*__pdst++ = *__psrc++;
	} else {
		__pdst = (__BYTE_TYPE__ *)__dst + __n_bytes;
		__psrc = (__BYTE_TYPE__ *)__src + __n_bytes;
		while (__n_bytes--)
			*--__pdst = *--__psrc;
	}
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memmove_defined */
