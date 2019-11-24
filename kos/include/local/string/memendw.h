/* HASH CRC-32:0x38678a5d */
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
#ifndef __local_memendw_defined
#define __local_memendw_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__LOCAL_LIBC(memendw) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memendw))(/*aligned(2)*/ void const *__restrict __haystack,
                                                     __UINT16_TYPE__ __word,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 1419 "kos/src/libc/magic/string.c"
	__UINT16_TYPE__ *__result = (__UINT16_TYPE__ *)__haystack;
	for (; __n_bytes--; ++__result) {
		if __unlikely(*__result == __word)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memendw_defined */
