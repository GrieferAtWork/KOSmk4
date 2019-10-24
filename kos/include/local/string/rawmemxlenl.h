/* HASH CRC-32:0x2ffeb20b */
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
#ifndef __local_rawmemxlenl_defined
#define __local_rawmemxlenl_defined 1
/* Dependency: "rawmemxchrl" from "string" */
#ifndef ____localdep_rawmemxchrl_defined
#define ____localdep_rawmemxchrl_defined 1
#if defined(__CRT_HAVE_rawmemxchrl)
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemxchrl,(__haystack,__dword))
#else /* LIBC: rawmemxchrl */
#include <local/string/rawmemxchrl.h>
/* Same as `rawmemchrl', but search for non-matching locations. */
#define __localdep_rawmemxchrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))
#endif /* rawmemxchrl... */
#endif /* !____localdep_rawmemxchrl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemlenl', but search for non-matching locations. */
__LOCAL_LIBC(rawmemxlenl) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemxlenl))(void const *__restrict __haystack,
                                                         __UINT32_TYPE__ __dword) {
#line 1942 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemxchrl(__haystack, __dword) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemxlenl_defined */
