/* HASH CRC-32:0xe28ccad7 */
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
#ifndef __local_memcmp_defined
#define __local_memcmp_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__LOCAL_LIBC(memcmp) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcmp))(void const *__s1,
                                                    void const *__s2,
                                                    __SIZE_TYPE__ __n_bytes) {
#line 182 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__p1 = (__BYTE_TYPE__ *)__s1;
	__BYTE_TYPE__ *__p2 = (__BYTE_TYPE__ *)__s2;
	__BYTE_TYPE__ __v1, __v2;
	__v1 = __v2 = 0;
	while (__n_bytes-- && ((__v1 = *__p1++) == (__v2 = *__p2++)));
	return (int)__v1 - (int)__v2;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memcmp_defined */
