/* HASH CRC-32:0xfccf897e */
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
#ifndef __local_memcmpl_defined
#define __local_memcmpl_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching dword */
__LOCAL_LIBC(memcmpl) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcmpl))(void const *__s1,
                                                     void const *__s2,
                                                     __SIZE_TYPE__ __n_dwords) {
#line 1118 "kos/src/libc/magic/string.c"
	__INT32_TYPE__ *__p1 = (__INT32_TYPE__ *)__s1;
	__INT32_TYPE__ *__p2 = (__INT32_TYPE__ *)__s2;
	__INT32_TYPE__ __v1, __v2;
	__v1 = __v2 = 0;
	while (__n_dwords-- && ((__v1 = *__p1++) == (__v2 = *__p2++)));
	return __v1 - __v2;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memcmpl_defined */
