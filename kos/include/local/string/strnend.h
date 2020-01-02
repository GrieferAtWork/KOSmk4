/* HASH CRC-32:0x1044abaa */
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
#ifndef __local_strnend_defined
#define __local_strnend_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__LOCAL_LIBC(strnend) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnend))(char const *__restrict __string,
                                                     __SIZE_TYPE__ __maxlen) {
#line 2503 "kos/src/libc/magic/string.c"
	for (; __maxlen && *__string; ++__string, --__maxlen)
		;
	return (char *)__string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strnend_defined */
