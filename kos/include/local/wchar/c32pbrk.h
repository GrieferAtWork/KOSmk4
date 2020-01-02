/* HASH CRC-32:0x3b7ea663 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32pbrk_defined
#define __local_c32pbrk_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32pbrk) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32pbrk))(__CHAR32_TYPE__ const *__haystack,
                                                     __CHAR32_TYPE__ const *__accept) {
#line 377 "kos/src/libc/magic/string.c"
	__CHAR32_TYPE__ const *__ned_iter;
	__CHAR32_TYPE__ __haych, __ch;
	while ((__haych = *__haystack++) != '\0') {
		__ned_iter = __accept;
		while ((__ch = *__ned_iter++) != '\0') {
			if (__haych == __ch)
				return (__CHAR32_TYPE__ *)__haystack - 1;
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32pbrk_defined */
