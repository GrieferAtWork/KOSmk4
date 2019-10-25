/* HASH CRC-32:0xf1f1bf8a */
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
#ifndef __local_rawmemrxlenq_defined
#define __local_rawmemrxlenq_defined 1
/* Dependency: "rawmemrxchrq" from "string" */
#ifndef ____localdep_rawmemrxchrq_defined
#define ____localdep_rawmemrxchrq_defined 1
#if defined(__CRT_HAVE_rawmemrxchrq)
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrxchrq,(__haystack,__qword))
#else /* LIBC: rawmemrxchrq */
#include <local/string/rawmemrxchrq.h>
/* Same as `rawmemrchrq', but search for non-matching locations. */
#define __localdep_rawmemrxchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))
#endif /* rawmemrxchrq... */
#endif /* !____localdep_rawmemrxchrq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemrlenq', but search for non-matching locations. */
__LOCAL_LIBC(rawmemrxlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrxlenq))(void const *__restrict __haystack,
                                                          __UINT64_TYPE__ __qword) {
#line 2071 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemrxchrq(__haystack, __qword) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemrxlenq_defined */
