/* HASH CRC-32:0xf41c9515 */
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
#ifndef __local_memrxlenl_defined
#define __local_memrxlenl_defined 1
/* Dependency: "memrxendl" from "string" */
#ifndef ____localdep_memrxendl_defined
#define ____localdep_memrxendl_defined 1
#if defined(__CRT_HAVE_memrxendl)
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrxendl,(__haystack,__dword,__n_dwords))
#else /* LIBC: memrxendl */
#include <local/string/memrxendl.h>
/* Same as `memrendl', but search for non-matching locations. */
#define __localdep_memrxendl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))
#endif /* memrxendl... */
#endif /* !____localdep_memrxendl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memrlenl', but search for non-matching locations. */
__LOCAL_LIBC(memrxlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrxlenl))(void const *__restrict __haystack,
                                                       __UINT32_TYPE__ __dword,
                                                       __SIZE_TYPE__ __n_dwords) {
#line 1982 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memrxendl(__haystack, __dword, __n_dwords) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrxlenl_defined */
