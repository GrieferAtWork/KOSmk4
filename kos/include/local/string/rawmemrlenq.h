/* HASH CRC-32:0xd9f04b5f */
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
#ifndef __local_rawmemrlenq_defined
#define __local_rawmemrlenq_defined 1
/* Dependency: "rawmemrchrq" from "string" */
#ifndef ____localdep_rawmemrchrq_defined
#define ____localdep_rawmemrchrq_defined 1
#ifdef __CRT_HAVE_rawmemrchrq
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrchrq,(__haystack,__qword))
#else /* LIBC: rawmemrchrq */
#include <local/string/rawmemrchrq.h>
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
#define __localdep_rawmemrchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))
#endif /* rawmemrchrq... */
#endif /* !____localdep_rawmemrchrq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(rawmemrlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrlenq))(void const *__restrict __haystack,
                                                         __UINT64_TYPE__ __qword) {
#line 1621 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemrchrq(__haystack, __qword) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemrlenq_defined */
