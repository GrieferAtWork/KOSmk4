/* HASH 0x131da635 */
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
#ifndef __local_rawmemrxlenw_defined
#define __local_rawmemrxlenw_defined 1
/* Dependency: "rawmemrxchrw" from "string" */
#ifndef ____localdep_rawmemrxchrw_defined
#define ____localdep_rawmemrxchrw_defined 1
#if defined(__CRT_HAVE_rawmemrxchrw)
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrxchrw,(__haystack,__word))
#else /* LIBC: rawmemrxchrw */
#include <local/string/rawmemrxchrw.h>
/* Same as `rawmemrchrw', but search for non-matching locations. */
#define __localdep_rawmemrxchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))
#endif /* rawmemrxchrw... */
#endif /* !____localdep_rawmemrxchrw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemrlenw', but search for non-matching locations. */
__LOCAL_LIBC(rawmemrxlenw) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrxlenw))(void const *__restrict __haystack,
                                                          __UINT16_TYPE__ __word) {
#line 1925 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemrxchrw(__haystack, __word) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemrxlenw_defined */
