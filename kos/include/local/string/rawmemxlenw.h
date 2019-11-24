/* HASH CRC-32:0xa09b7600 */
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
#ifndef __local_rawmemxlenw_defined
#define __local_rawmemxlenw_defined 1
/* Dependency: "rawmemxchrw" from "string" */
#ifndef ____localdep_rawmemxchrw_defined
#define ____localdep_rawmemxchrw_defined 1
#ifdef __CRT_HAVE_rawmemxchrw
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemxchrw,(/*aligned(2)*/ void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemxchrw,(__haystack,__word))
#else /* LIBC: rawmemxchrw */
#include <local/string/rawmemxchrw.h>
/* Same as `rawmemchrw', but search for non-matching locations. */
#define __localdep_rawmemxchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))
#endif /* rawmemxchrw... */
#endif /* !____localdep_rawmemxchrw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemlenw', but search for non-matching locations. */
__LOCAL_LIBC(rawmemxlenw) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemxlenw))(/*aligned(2)*/ void const *__restrict __haystack,
                                                         __UINT16_TYPE__ __word) {
#line 2212 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemxchrw(__haystack, __word) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemxlenw_defined */
