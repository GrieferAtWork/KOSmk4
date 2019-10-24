/* HASH CRC-32:0x52d48cd2 */
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
#ifndef __local_rawmemlenw_defined
#define __local_rawmemlenw_defined 1
/* Dependency: "rawmemchrw" from "string" */
#ifndef ____localdep_rawmemchrw_defined
#define ____localdep_rawmemchrw_defined 1
#if defined(__CRT_HAVE_rawmemchrw)
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemchrw,(__haystack,__word))
#else /* LIBC: rawmemchrw */
#include <local/string/rawmemchrw.h>
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
#define __localdep_rawmemchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))
#endif /* rawmemchrw... */
#endif /* !____localdep_rawmemchrw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(rawmemlenw) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemlenw))(void const *__restrict __haystack,
                                                        __UINT16_TYPE__ __word) {
#line 1327 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemchrw(__haystack, __word) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemlenw_defined */
