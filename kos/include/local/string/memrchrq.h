/* HASH CRC-32:0x5bc8059d */
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
#ifndef __local_memrchrq_defined
#define __local_memrchrq_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__LOCAL_LIBC(memrchrq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrchrq))(/*aligned(8)*/ void const *__restrict __haystack,
                                                      __UINT64_TYPE__ __qword,
                                                      __SIZE_TYPE__ __n_qwords) {
#line 1767 "kos/src/libc/magic/string.c"
	__UINT64_TYPE__ *__iter = (__UINT64_TYPE__ *)__haystack + __n_qwords;
	while (__n_qwords--) {
		if __unlikely(*--__iter == __qword)
			return __iter;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrchrq_defined */
