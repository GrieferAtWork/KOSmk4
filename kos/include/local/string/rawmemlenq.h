/* HASH CRC-32:0xe8318252 */
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
#ifndef __local_rawmemlenq_defined
#define __local_rawmemlenq_defined 1
/* Dependency: "rawmemchrq" from "string" */
#ifndef ____localdep_rawmemchrq_defined
#define ____localdep_rawmemchrq_defined 1
#ifdef __CRT_HAVE_rawmemchrq
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemchrq,(/*aligned(8)*/ void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemchrq,(__haystack,__qword))
#else /* LIBC: rawmemchrq */
#include <local/string/rawmemchrq.h>
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
#define __localdep_rawmemchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))
#endif /* rawmemchrq... */
#endif /* !____localdep_rawmemchrq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(rawmemlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemlenq))(/*aligned(8)*/ void const *__restrict __haystack,
                                                        __UINT64_TYPE__ __qword) {
#line 1825 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemchrq(__haystack, __qword) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemlenq_defined */
