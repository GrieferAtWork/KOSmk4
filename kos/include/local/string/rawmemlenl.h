/* HASH CRC-32:0x716fa0d9 */
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
#ifndef __local_rawmemlenl_defined
#define __local_rawmemlenl_defined 1
/* Dependency: "rawmemchrl" from "string" */
#ifndef ____localdep_rawmemchrl_defined
#define ____localdep_rawmemchrl_defined 1
#ifdef __CRT_HAVE_rawmemchrl
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemchrl,(/*aligned(4)*/ void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemchrl,(__haystack,__dword))
#else /* LIBC: rawmemchrl */
#include <local/string/rawmemchrl.h>
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
#define __localdep_rawmemchrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))
#endif /* rawmemchrl... */
#endif /* !____localdep_rawmemchrl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(rawmemlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemlenl))(/*aligned(4)*/ void const *__restrict __haystack,
                                                        __UINT32_TYPE__ __dword) {
#line 1546 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemchrl(__haystack, __dword) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemlenl_defined */
