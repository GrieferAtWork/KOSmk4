/* HASH 0x1dc37849 */
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
#ifndef __local_memrxchrl_defined
#define __local_memrxchrl_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `memrchrl', but search for non-matching locations. */
__LOCAL_LIBC(memrxchrl) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrxchrl))(void const *__restrict __haystack,
                                                       __UINT32_TYPE__ __dword,
                                                       __SIZE_TYPE__ __n_dwords) {
#line 1714 "kos/src/libc/magic/string.c"
	__UINT32_TYPE__ *__iter = (__UINT32_TYPE__ *)__haystack + __n_dwords;
	while (__n_dwords--) {
		if __unlikely(*--__iter != __dword)
			return __iter;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrxchrl_defined */
