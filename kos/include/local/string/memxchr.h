/* HASH CRC-32:0xeea48af4 */
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
#ifndef __local_memxchr_defined
#define __local_memxchr_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `memchr', but search for non-matching locations. */
__LOCAL_LIBC(memxchr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxchr))(void const *__restrict __haystack,
                                                     int __needle,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 1638 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__hay_iter = (__BYTE_TYPE__ *)__haystack;
	for (; __n_bytes--; ++__hay_iter) {
		if __unlikely(*__hay_iter != (__BYTE_TYPE__)__needle)
			return __hay_iter;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memxchr_defined */
